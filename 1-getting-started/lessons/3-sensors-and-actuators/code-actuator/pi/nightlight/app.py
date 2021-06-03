import time
import seeed_si114x
from grove.grove_led import GroveLed

light_sensor = seeed_si114x.grove_si114x()
led = GroveLed(5)

while True:
    light = light_sensor.ReadVisible
    print('Light level:', light)

    if light < 300:
        led.on()
    else:
        led.off()
    
    time.sleep(1)