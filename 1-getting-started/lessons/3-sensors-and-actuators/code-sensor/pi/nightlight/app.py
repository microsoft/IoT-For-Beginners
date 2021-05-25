import time
from grove.grove_light_sensor_v1_2 import GroveLightSensor

light_sensor = GroveLightSensor(0)

while True:
    light = light_sensor.light
    print('Light level:', light)
    
    time.sleep(1)