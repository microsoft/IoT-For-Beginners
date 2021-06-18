from typing import List
import logging

import azure.functions as func

import json
import os
from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
from msrest.authentication import CognitiveServicesCredentials

from azure.iot.hub import IoTHubRegistryManager
from azure.iot.hub.models import CloudToDeviceMethod

def main(events: List[func.EventHubEvent]):
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)

    for event in events:
        logging.info('Python EventHub trigger processed an event: %s',
                        event.get_body().decode('utf-8'))

        device_id = event.iothub_metadata['connection-device-id']

        event_body = json.loads(event.get_body().decode('utf-8'))
        prediction_request = { 'query' : event_body['speech'] }

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
            direct_method = CloudToDeviceMethod(method_name='set-timer', payload=json.dumps(payload))

            registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
            registry_manager = IoTHubRegistryManager(registry_manager_connection_string)

            registry_manager.invoke_device_method(device_id, direct_method)


