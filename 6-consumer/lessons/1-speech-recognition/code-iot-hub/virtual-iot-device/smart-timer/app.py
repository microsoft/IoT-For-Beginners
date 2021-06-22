import json
import time
from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
from azure.iot.device import IoTHubDeviceClient, Message

speech_api_key = '<key>'
location = '<location>'
language = '<language>'
connection_string = '<connection_string>'

device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

print('Connecting')
device_client.connect()
print('Connected')

recognizer_config = SpeechConfig(subscription=speech_api_key,
                                 region=location,
                                 speech_recognition_language=language)

recognizer = SpeechRecognizer(speech_config=recognizer_config)

def recognized(args):
    if len(args.result.text) > 0:
        message = Message(json.dumps({ 'speech': args.result.text }))
        device_client.send_message(message)

recognizer.recognized.connect(recognized)

recognizer.start_continuous_recognition()

while True:
    time.sleep(1)