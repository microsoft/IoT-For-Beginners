<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-28T19:02:28+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "en"
}
-->
# Detect proximity - Raspberry Pi

In this part of the lesson, you will add a proximity sensor to your Raspberry Pi and read distance measurements from it.

## Hardware

The Raspberry Pi requires a proximity sensor.

The sensor you'll use is a [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). This sensor uses a laser ranging module to measure distance. It has a range of 10mm to 2000mm (1cm - 2m) and provides accurate readings within this range. Distances above 1000mm are reported as 8109mm.

The laser rangefinder is located on the back of the sensor, opposite the Grove socket.

This is an I²C sensor.

### Connect the time of flight sensor

The Grove time of flight sensor can be connected to the Raspberry Pi.

#### Task - connect the time of flight sensor

Connect the time of flight sensor.

![A grove time of flight sensor](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.en.png)

1. Insert one end of a Grove cable into the socket on the time of flight sensor. It will only fit in one way.

1. With the Raspberry Pi powered off, connect the other end of the Grove cable to one of the I²C sockets marked **I²C** on the Grove Base hat attached to the Pi. These sockets are on the bottom row, opposite the GPIO pins and next to the camera cable slot.

![The grove time of flight sensor connected to the I squared C socket](../../../../../translated_images/pi-time-of-flight-sensor.58c8dc04eb3bfb57.en.png)

## Program the time of flight sensor

The Raspberry Pi can now be programmed to use the attached time of flight sensor.

### Task - program the time of flight sensor

Program the device.

1. Power up the Pi and wait for it to boot.

1. Open the `fruit-quality-detector` code in VS Code, either directly on the Pi or by connecting via the Remote SSH extension.

1. Install the rpi-vl53l0x Pip package, a Python package that interacts with a VL53L0X time-of-flight distance sensor. Install it using this pip command:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Create a new file in this project called `distance-sensor.py`.

    > 💁 An easy way to simulate multiple IoT devices is to create each in a separate Python file, then run them simultaneously.

1. Add the following code to this file:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    This imports the Grove I²C bus library and a sensor library for the core hardware built into the Grove time of flight sensor.

1. Below this, add the following code to access the sensor:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    This code declares a distance sensor using the Grove I²C bus and initializes the sensor.

1. Finally, add an infinite loop to read distances:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    This code waits for a value to be ready from the sensor, then prints it to the console.

1. Run this code.

    > 💁 Remember, this file is called `distance-sensor.py`! Make sure to run it using Python, not `app.py`.

1. You will see distance measurements appear in the console. Place objects near the sensor, and you will see the distance measurement:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    The rangefinder is on the back of the sensor, so ensure you use the correct side when measuring distance.

    ![The rangefinder on the back of the time of flight sensor pointing at a banana](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4.en.png)

> 💁 You can find this code in the [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi) folder.

😀 Your proximity sensor program was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.