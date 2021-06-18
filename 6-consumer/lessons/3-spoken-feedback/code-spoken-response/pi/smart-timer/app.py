import io
import json
import pyaudio
import requests
import time
import wave
import threading

from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse

from grove.factory import Factory
button = Factory.getButton('GPIO-HIGH', 5)

audio = pyaudio.PyAudio()
microphone_card_number = 1
speaker_card_number = 1
rate = 16000

def capture_audio():
    stream = audio.open(format = pyaudio.paInt16,
                        rate = rate,
                        channels = 1, 
                        input_device_index = microphone_card_number,
                        input = True,
                        frames_per_buffer = 4096)

    frames = []

    while button.is_pressed():
        frames.append(stream.read(4096))

    stream.stop_stream()
    stream.close()

    wav_buffer = io.BytesIO()
    with wave.open(wav_buffer, 'wb') as wavefile:
        wavefile.setnchannels(1)
        wavefile.setsampwidth(audio.get_sample_size(pyaudio.paInt16))
        wavefile.setframerate(rate)
        wavefile.writeframes(b''.join(frames))
        wav_buffer.seek(0)

    return wav_buffer

api_key = '<key>'
location = '<location>'
language = '<language>'
connection_string = '<connection_string>'

device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

print('Connecting')
device_client.connect()
print('Connected')

def get_access_token():
    headers = {
        'Ocp-Apim-Subscription-Key': api_key
    }

    token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
    response = requests.post(token_endpoint, headers=headers)
    return str(response.text)

def convert_speech_to_text(buffer):
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }

    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = json.loads(response.text)

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''

def get_voice():
    url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'

    headers = {
        'Authorization': 'Bearer ' + get_access_token()
    }

    response = requests.get(url, headers=headers)
    voices_json = json.loads(response.text)

    first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower())
    return first_voice['ShortName']

voice = get_voice()
print(f"Using voice {voice}")

playback_format = 'riff-48khz-16bit-mono-pcm'

def get_speech(text):
    url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': 'application/ssml+xml',
        'X-Microsoft-OutputFormat': playback_format
    }

    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'

    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)

def play_speech(speech):
    with wave.open(speech, 'rb') as wave_file:
        stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                            channels=wave_file.getnchannels(),
                            rate=wave_file.getframerate(),
                            output_device_index=speaker_card_number,
                            output=True)

        data = wave_file.readframes(4096)

        while len(data) > 0:
            stream.write(data)
            data = wave_file.readframes(4096)

        stream.stop_stream()
        stream.close()

def say(text):
    speech = get_speech(text)
    play_speech(speech)

def announce_timer(minutes, seconds):
    announcement = 'Times up on your '
    if minutes > 0:
        announcement += f'{minutes} minute'
    if seconds > 0:
        announcement += f'{seconds} second'
    announcement += ' timer.'
    say(announcement)

def create_timer(total_seconds):
    minutes, seconds = divmod(total_seconds, 60)
    threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute'
    if seconds > 0:
        announcement += f'{seconds} second'    
    announcement += ' timer started.'
    say(announcement)

def handle_method_request(request):    
    if request.name == 'set-timer':
        payload = json.loads(request.payload)
        seconds = payload['seconds']
        if seconds > 0:
            create_timer(payload['seconds'])

    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)

device_client.on_method_request_received = handle_method_request

while True:
    while not button.is_pressed():
        time.sleep(.1)

    buffer = capture_audio()
    text = convert_speech_to_text(buffer)
    if len(text) > 0:
        print(text)
        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)