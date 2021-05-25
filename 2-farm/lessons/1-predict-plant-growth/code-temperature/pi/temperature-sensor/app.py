import time
from seeed_dht import DHT

sensor = DHT("11", 5)

while True:
    _, temp = sensor.read()
    print(f'Temperature {temp}°C')

    time.sleep(10)