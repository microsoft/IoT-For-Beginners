from counterfit_connection import CounterFitConnection
CounterFitConnection.init('127.0.0.1', 5000)

import time
from counterfit_shims_grove.adc import ADC
from counterfit_shims_grove.grove_relay import GroveRelay

adc = ADC()
relay = GroveRelay(5)

while True:
    soil_moisture = adc.read(0)
    print("Soil moisture:", soil_moisture)

    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()

    time.sleep(10)