import time
from seeed_dht import DHT
import paho.mqtt.client as mqtt
import json

sensor = DHT("11", 5)

id = '<ID>'

client_telemetry_topic = id + '/telemetry'
client_name = id + 'temperature_sensor_client'

mqtt_client = mqtt.Client(client_name)
mqtt_client.connect('test.mosquitto.org')

mqtt_client.loop_start()

print("MQTT connected!")

while True:
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})

    print("Sending telemetry ", telemetry)

    mqtt_client.publish(client_telemetry_topic, telemetry)

    time.sleep(10 * 60)
