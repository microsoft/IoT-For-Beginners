import time
from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer

api_key = '<key>'
location = '<location>'
language = '<language>'

speech_config = SpeechConfig(subscription=api_key,
                             region=location,
                             speech_recognition_language=language)

recognizer = SpeechRecognizer(speech_config=speech_config)

def recognized(args):
    print(args.result.text)

recognizer.recognized.connect(recognized)

recognizer.start_continuous_recognition()

while True:
    time.sleep(1)