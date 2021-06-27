import logging

import azure.functions as func
import json
import os
from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
from msrest.authentication import CognitiveServicesCredentials


def main(req: func.HttpRequest) -> func.HttpResponse:
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)

    text = req.params.get('text')
    prediction_request = { 'query' : text }

    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)

    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0

        for i in range(0, len(numbers)):
            number = numbers[i]
            time_unit = time_units[i][0]
            
            if time_unit == 'minute':
                total_seconds += number * 60
            else:
                total_seconds += number

        logging.info(f'Timer required for {total_seconds} seconds')
    
        payload = {
            'seconds': total_seconds
        }
        return func.HttpResponse(json.dumps(payload), status_code=200)
    
    return func.HttpResponse(status_code=404)