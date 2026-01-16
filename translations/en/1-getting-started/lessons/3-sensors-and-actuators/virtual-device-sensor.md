<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-28T20:09:56+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "en"
}
-->
# Build a nightlight - Virtual IoT Hardware

In this part of the lesson, you will add a light sensor to your virtual IoT device.

## Virtual Hardware

The nightlight requires one sensor, which will be created in the CounterFit app.

The sensor is a **light sensor**. In a physical IoT device, this would be a [photodiode](https://wikipedia.org/wiki/Photodiode) that converts light into an electrical signal. Light sensors are analog sensors that provide an integer value representing the relative amount of light, but this value does not correspond to any standard unit of measurement like [lux](https://wikipedia.org/wiki/Lux).

### Add the sensors to CounterFit

To use a virtual light sensor, you need to add it to the CounterFit app.

#### Task - Add the sensors to CounterFit

Add the light sensor to the CounterFit app.

1. Ensure the CounterFit web app is running from the previous part of this assignment. If it isn’t, start it.

1. Create a light sensor:

    1. In the *Create sensor* box within the *Sensors* pane, open the *Sensor type* dropdown and select *Light*.

    1. Leave the *Units* set to *NoUnits*.

    1. Make sure the *Pin* is set to *0*.

    1. Click the **Add** button to create the light sensor on Pin 0.

    ![The light sensor settings](../../../../../translated_images/en/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    The light sensor will be created and displayed in the sensors list.

    ![The light sensor created](../../../../../translated_images/en/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## Program the light sensor

Now, the device can be programmed to use the built-in light sensor.

### Task - Program the light sensor

Program the device.

1. Open the nightlight project in VS Code that you created in the previous part of this assignment. If necessary, kill and re-create the terminal to ensure it is running with the virtual environment.

1. Open the `app.py` file.

1. Add the following code at the top of the `app.py` file, alongside the other `import` statements, to include the required libraries:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    The `import time` statement imports Python's `time` module, which will be used later in this assignment.

    The `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` statement imports the `GroveLightSensor` from the CounterFit Grove shim Python libraries. This library contains code to interact with a light sensor created in the CounterFit app.

1. Add the following code at the bottom of the file to create instances of classes that manage the light sensor:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    The line `light_sensor = GroveLightSensor(0)` creates an instance of the `GroveLightSensor` class, connecting it to pin **0**—the CounterFit Grove pin where the light sensor is connected.

1. Add an infinite loop after the code above to continuously read the light sensor value and print it to the console:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    This code reads the current light level using the `light` property of the `GroveLightSensor` class. The property retrieves the analog value from the pin, which is then printed to the console.

1. Add a short sleep of one second at the end of the `while` loop, as the light levels don’t need to be checked constantly. Adding a sleep reduces the device's power consumption.

    ```python
    time.sleep(1)
    ```

1. From the VS Code Terminal, run the following command to execute your Python app:

    ```sh
    python3 app.py
    ```

    Light values will be displayed in the console. Initially, this value will be 0.

1. In the CounterFit app, modify the value of the light sensor that the app will read. You can do this in one of two ways:

    * Enter a number in the *Value* box for the light sensor, then click the **Set** button. The number you enter will be the value returned by the sensor.

    * Check the *Random* checkbox, and specify a *Min* and *Max* value, then click the **Set** button. Each time the sensor reads a value, it will return a random number between *Min* and *Max*.

    The values you set will appear in the console. Adjust the *Value* or the *Random* settings to see the value change.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 You can find this code in the [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device) folder.

😀 Your nightlight program was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.