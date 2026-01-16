<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-11-18T19:00:30+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "pcm"
}
-->
# Detect proximity - Raspberry Pi

For dis part of di lesson, you go add proximity sensor to your Raspberry Pi, and read di distance wey e dey measure.

## Hardware

Di Raspberry Pi go need one proximity sensor.

Di sensor wey you go use na [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Dis sensor dey use laser ranging module to detect distance. E fit measure distance from 10mm to 2000mm (1cm - 2m), and e go report di values for dat range well well, but if di distance pass 1000mm, e go report am as 8109mm.

Di laser rangefinder dey for di back of di sensor, di opposite side to di Grove socket.

Dis na I<sup>2</sup>C sensor.

### Connect di time of flight sensor

Di Grove time of flight sensor fit connect to di Raspberry Pi.

#### Task - connect di time of flight sensor

Connect di time of flight sensor.

![A grove time of flight sensor](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.pcm.png)

1. Put one end of di Grove cable inside di socket for di time of flight sensor. E go only fit enter one way.

1. When di Raspberry Pi dey off, connect di other end of di Grove cable to one of di I<sup>2</sup>C sockets wey dem mark **I<sup>2</sup>C** for di Grove Base hat wey dey attach to di Pi. Dis sockets dey for di bottom row, di opposite side to di GPI pins and near di camera cable slot.

![Di grove time of flight sensor wey dem connect to di I squared C socket](../../../../../translated_images/pcm/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Program di time of flight sensor

Di Raspberry Pi fit now dey program to use di time of flight sensor wey dem attach.

### Task - program di time of flight sensor

Program di device.

1. Power di Pi and wait make e boot.

1. Open di `fruit-quality-detector` code for VS Code, either directly for di Pi, or connect am through di Remote SSH extension.

1. Install di rpi-vl53l0x Pip package, one Python package wey dey work with VL53L0X time-of-flight distance sensor. Install am with dis pip command

    ```sh
    pip install rpi-vl53l0x
    ```

1. Create new file for dis project wey you go call `distance-sensor.py`.

    > 💁 One easy way to simulate plenty IoT devices na to do each one for different Python file, then run dem at di same time.

1. Add dis code to di file:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Dis one dey import di Grove I<sup>2</sup>C bus library, and one sensor library for di core sensor hardware wey dey inside di Grove time of flight sensor.

1. Under dis one, add dis code to access di sensor:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Dis code dey declare one distance sensor wey dey use di Grove I<sup>2</sup>C bus, then e go start di sensor.

1. Finally, add one infinite loop to dey read distances:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Dis code dey wait make value ready to read from di sensor, then e go print am for di console.

1. Run dis code.

    > 💁 No forget say dis file name na `distance-sensor.py`! Make sure say you dey run am with Python, no be `app.py`.

1. You go see distance measurements for di console. Put objects near di sensor and you go see di distance measurement:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Di rangefinder dey for di back of di sensor, so make sure say you dey use di correct side when you dey measure distance.

    ![Di rangefinder for di back of di time of flight sensor wey dey point at one banana](../../../../../translated_images/pcm/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 You fit find dis code for di [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi) folder.

😀 Your proximity sensor program don work well!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis docu don dey translate wit AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). Even though we dey try make am accurate, abeg sabi say automated translation fit get mistake or no correct well. Di original docu for im native language na di main correct source. For important information, e go beta make professional human translator check am. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->