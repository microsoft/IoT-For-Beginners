import time
from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer

speech_api_key = '<key>'
location = '<location>'
language = '<language>'

recognizer_config = SpeechConfig(subscription=speech_api_key,
                                 region=location,
                                 speech_recognition_language=language)

recognizer = SpeechRecognizer(speech_config=recognizer_config)

def process_text(text):
    print(text)

def recognized(args):
    process_text(args.result.text)

recognizer.recognized.connect(recognized)

recognizer.start_continuous_recognition()

while True:
    time.sleep(1)