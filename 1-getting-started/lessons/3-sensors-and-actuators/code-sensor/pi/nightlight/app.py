import time
import seeed_si114x

light_sensor = seeed_si114x.grove_si114x()

while True:
    light = light_sensor.ReadVisible
    print('Light level:', light)
    time.sleep(1)