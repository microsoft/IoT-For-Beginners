import time
from grove.grove_light_sensor_v1_2 import GroveLightSensor
from grove.grove_led import GroveLed

light_sensor = GroveLightSensor(0)
led = GroveLed(5)

while True:
    light = light_sensor.light
    print('Light level:', light)

    if light < 200:
        led.on()
    else:
        led.off()
    
    time.sleep(1)