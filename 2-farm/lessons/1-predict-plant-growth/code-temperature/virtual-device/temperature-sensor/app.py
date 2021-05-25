from counterfit_connection import CounterFitConnection
CounterFitConnection.init('127.0.0.1', 5000)

import time
from counterfit_shims_seeed_python_dht import DHT

sensor = DHT("11", 5)

while True:
    _, temp = sensor.read()
    print(f'Temperature {temp}°C')

    time.sleep(10)