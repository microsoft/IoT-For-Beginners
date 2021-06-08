import time
import serial
import pynmea2
import json
from azure.iot.device import IoTHubDeviceClient, Message

connection_string = "<connection_string>"

serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
serial.reset_input_buffer()
serial.flush()

device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

print("Connecting")
device_client.connect()
print("Connected")

def printGPSData(line):
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        message_json = { "gps" : { "lat":lat, "lon":lon } }
        print("Sending telemetry", message_json)
        message = Message(json.dumps(message_json))
        device_client.send_message(message)

while True:
    line = serial.readline().decode('utf-8')

    while len(line) > 0:
        printGPSData(line)
        line = serial.readline().decode('utf-8')

    time.sleep(1)
