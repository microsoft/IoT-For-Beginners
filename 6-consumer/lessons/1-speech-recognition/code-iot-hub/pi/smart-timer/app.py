import io
import json
import pyaudio
import requests
import time
import wave

from azure.iot.device import IoTHubDeviceClient, Message

from grove.factory import Factory
button = Factory.getButton('GPIO-HIGH', 5)

connection_string = '<connection_string>'

device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

print('Connecting')
device_client.connect()
print('Connected')

audio = pyaudio.PyAudio()
microphone_card_number = 1
speaker_card_number = 1
rate = 48000

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

while True:
    while not button.is_pressed():
        time.sleep(.1)

    buffer = capture_audio()
    text = convert_speech_to_text(buffer)
    if len(text) > 0:
        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)