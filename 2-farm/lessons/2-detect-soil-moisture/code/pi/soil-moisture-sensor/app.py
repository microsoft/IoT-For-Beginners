import time
from grove.adc import ADC

adc = ADC()

while True:
    soil_moisture = adc.read(0)
    print("Soil moisture:", soil_moisture)

    time.sleep(10)