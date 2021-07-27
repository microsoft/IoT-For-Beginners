import json
import os
import requests

import azure.functions as func

def main(req: func.HttpRequest) -> func.HttpResponse:
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']

    req_body = req.get_json()
    language = req_body['language']

    url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'

    headers = {
        'Ocp-Apim-Subscription-Key': speech_key
    }

    response = requests.get(url, headers=headers)
    voices_json = json.loads(response.text)

    voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
    voices = map(lambda x: x['ShortName'], voices)

    return func.HttpResponse(json.dumps(list(voices)), status_code=200)
