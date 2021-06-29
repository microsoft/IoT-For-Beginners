import io
import pyaudio
import requests
import threading
import time
import wave

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

speech_api_key = '<key>'
location = '<location>'
language = '<language>'

def get_access_token():
    headers = {
        'Ocp-Apim-Subscription-Key': speech_api_key
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
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''

def get_timer_time(text):
    url = '<URL>'

    params = {
        'text': text
    }

    response = requests.post(url, params=params)

    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']

def say(text):
    print(text)

def announce_timer(minutes, seconds):
    announcement = 'Times up on your '
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '
    announcement += 'timer.'
    say(announcement)

def create_timer(total_seconds):
    minutes, seconds = divmod(total_seconds, 60)
    threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()

    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)

def process_text(text):
    print(text)
    
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)

while True:
    while not button.is_pressed():
        time.sleep(.1)

    buffer = capture_audio()
    text = convert_speech_to_text(buffer)
    process_text(text)