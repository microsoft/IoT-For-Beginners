<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-28T20:08:50+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "en"
}
-->
# Build a nightlight - Raspberry Pi

In this part of the lesson, you will add a light sensor to your Raspberry Pi.

## Hardware

The sensor for this lesson is a **light sensor** that uses a [photodiode](https://wikipedia.org/wiki/Photodiode) to convert light into an electrical signal. This is an analog sensor that provides an integer value between 0 and 1,000, representing a relative amount of light. This value does not correspond to any standard unit of measurement like [lux](https://wikipedia.org/wiki/Lux).

The light sensor is an external Grove sensor and needs to be connected to the Grove Base hat on the Raspberry Pi.

### Connect the light sensor

The Grove light sensor, which is used to detect light levels, needs to be connected to the Raspberry Pi.

#### Task - connect the light sensor

Connect the light sensor.

![A grove light sensor](../../../../../translated_images/en/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Insert one end of a Grove cable into the socket on the light sensor module. It will only fit in one direction.

1. With the Raspberry Pi powered off, connect the other end of the Grove cable to the analog socket labeled **A0** on the Grove Base hat attached to the Pi. This socket is the second from the right in the row of sockets next to the GPIO pins.

![The grove light sensor connected to socket A0](../../../../../translated_images/en/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## Program the light sensor

The device can now be programmed using the Grove light sensor.

### Task - program the light sensor

Program the device.

1. Power up the Pi and wait for it to boot.

1. Open the nightlight project in VS Code that you created in the previous part of this assignment, either running directly on the Pi or connected using the Remote SSH extension.

1. Open the `app.py` file and delete all existing code.

1. Add the following code to the `app.py` file to import the necessary libraries:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    The `import time` statement imports the `time` module, which will be used later in this assignment.

    The `from grove.grove_light_sensor_v1_2 import GroveLightSensor` statement imports the `GroveLightSensor` from the Grove Python libraries. This library contains code to interact with a Grove light sensor and was installed globally during the Pi setup.

1. Add the following code after the previous code to create an instance of the class that manages the light sensor:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    The line `light_sensor = GroveLightSensor(0)` creates an instance of the `GroveLightSensor` class, connecting to pin **A0**—the analog Grove pin where the light sensor is connected.

1. Add an infinite loop after the previous code to continuously read the light sensor value and print it to the console:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    This will read the current light level on a scale of 0-1,023 using the `light` property of the `GroveLightSensor` class. This property reads the analog value from the pin. The value is then printed to the console.

1. Add a short delay of one second at the end of the loop, as the light levels don't need to be checked constantly. Adding a delay reduces the device's power consumption.

    ```python
    time.sleep(1)
    ```

1. From the VS Code Terminal, run the following command to execute your Python app:

    ```sh
    python3 app.py
    ```

    Light values will be displayed in the console. Cover and uncover the light sensor, and you will see the values change:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 You can find this code in the [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi) folder.

😀 Adding a sensor to your nightlight program was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.