import logging
import os
import requests

import azure.functions as func

location = os.environ['TRANSLATOR_LOCATION']
translator_key = os.environ['TRANSLATOR_KEY']

def main(req: func.HttpRequest) -> func.HttpResponse:
    req_body = req.get_json()
    from_language = req_body['from_language']
    to_language = req_body['to_language']
    text = req_body['text']
    
    logging.info(f'Translating {text} from {from_language} to {to_language}')

    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }

    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    
    response = requests.post(url, headers=headers, params=params, json=body)
    return func.HttpResponse(response.json()[0]['translations'][0]['text'])
