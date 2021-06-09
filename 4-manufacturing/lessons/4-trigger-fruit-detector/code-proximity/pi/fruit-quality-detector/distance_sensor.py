import time
from grove.i2c import Bus
from rpi_vl53l0x.vl53l0x import VL53L0X

distance_sensor = VL53L0X(bus = Bus().bus)
distance_sensor.begin()

while True:
    distance_sensor.wait_ready()
    print(f'Distance = {distance_sensor.get_distance()} mm')
    time.sleep(1)