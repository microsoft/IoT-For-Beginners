import json
import threading
import time
from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse

api_key = '<key>'
location = '<location>'
language = '<language>'
connection_string = '<connection_string>'

device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

print('Connecting')
device_client.connect()
print('Connected')

recognizer_config = SpeechConfig(subscription=api_key,
                                 region=location,
                                 speech_recognition_language=language)

recognizer = SpeechRecognizer(speech_config=recognizer_config)

def recognized(args):
    if len(args.result.text) > 0:
        message = Message(json.dumps({ 'speech': args.result.text }))
        device_client.send_message(message)

recognizer.recognized.connect(recognized)

recognizer.start_continuous_recognition()

speech_config = SpeechConfig(subscription=api_key,
                             region=location)
speech_config.speech_synthesis_language = language
speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)

voices = speech_synthesizer.get_voices_async().get().voices
first_voice = next(x for x in voices if x.locale.lower() == language.lower())
speech_config.speech_synthesis_voice_name = first_voice.short_name

def say(text):
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'

    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()

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
    time.sleep(1)