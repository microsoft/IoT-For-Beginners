from typing import List
import logging

import azure.functions as func

import json
import os
from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
from msrest.authentication import CognitiveServicesCredentials

def main(events: List[func.EventHubEvent]):
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)

    for event in events:
        logging.info('Python EventHub trigger processed an event: %s',
                        event.get_body().decode('utf-8'))

        event_body = json.loads(event.get_body().decode('utf-8'))
        prediction_request = { 'query' : event_body['speech'] }

        prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)

        if prediction_response.prediction.top_intent == 'set timer':
            numbers = prediction_response.prediction.entities['number']
            time_units = prediction_response.prediction.entities['time unit']
            total_time = 0

            for i in range(0, len(numbers)):
                number = numbers[i]
                time_unit = time_units[i][0]

                if time_unit == 'minute':
                    total_time += number * 60
                else:
                    total_time += number

            logging.info(f'Timer required for {total_time} seconds')

