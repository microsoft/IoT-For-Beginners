<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-28T20:07:32+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "en"
}
-->
# Build a nightlight - Virtual IoT Hardware

In this part of the lesson, you will add an LED to your virtual IoT device and use it to create a nightlight.

## Virtual Hardware

The nightlight requires one actuator, which will be created in the CounterFit app.

The actuator is an **LED**. In a physical IoT device, this would be a [light-emitting diode](https://wikipedia.org/wiki/Light-emitting_diode) that emits light when current flows through it. This is a digital actuator with two states: on and off. Sending a value of 1 turns the LED on, while sending a value of 0 turns it off.

The nightlight logic in pseudo-code is:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Add the actuator to CounterFit

To use a virtual LED, you need to add it to the CounterFit app.

#### Task - Add the actuator to CounterFit

Add the LED to the CounterFit app.

1. Ensure the CounterFit web app is running from the previous part of this assignment. If it isn’t, start it and re-add the light sensor.

1. Create an LED:

    1. In the *Create actuator* box in the *Actuator* pane, open the *Actuator type* dropdown and select *LED*.

    1. Set the *Pin* to *5*.

    1. Click the **Add** button to create the LED on Pin 5.

    ![The LED settings](../../../../../translated_images/en/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    The LED will be created and will appear in the actuators list.

    ![The LED created](../../../../../translated_images/en/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    Once the LED is created, you can change its color using the *Color* picker. Click the **Set** button to apply the color after selecting it.

### Program the nightlight

Now you can program the nightlight using the CounterFit light sensor and LED.

#### Task - Program the nightlight

Program the nightlight.

1. Open the nightlight project in VS Code that you created in the previous part of this assignment. If necessary, kill and re-create the terminal to ensure it is running with the virtual environment.

1. Open the `app.py` file.

1. Add the following code to the `app.py` file to import a required library. This should be added at the top, below the other `import` lines.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    The `from counterfit_shims_grove.grove_led import GroveLed` statement imports the `GroveLed` class from the CounterFit Grove shim Python libraries. This library contains the code needed to interact with an LED created in the CounterFit app.

1. Add the following code after the `light_sensor` declaration to create an instance of the class that manages the LED:

    ```python
    led = GroveLed(5)
    ```

    The line `led = GroveLed(5)` creates an instance of the `GroveLed` class, connecting it to pin **5**—the CounterFit Grove pin where the LED is connected.

1. Add a check inside the `while` loop, before the `time.sleep`, to monitor the light levels and turn the LED on or off:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    This code checks the `light` value. If the value is less than 300, it calls the `on` method of the `GroveLed` class, which sends a digital value of 1 to the LED, turning it on. If the light value is 300 or higher, it calls the `off` method, sending a digital value of 0 to the LED, turning it off.

    > 💁 Make sure this code is indented to the same level as the `print('Light level:', light)` line so that it is inside the while loop!

1. From the VS Code Terminal, run the following command to execute your Python app:

    ```sh
    python3 app.py
    ```

    Light values will be displayed in the console.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Adjust the *Value* or the *Random* settings to change the light level above and below 300. The LED will turn on and off accordingly.

![The LED in the CounterFit app turning on and off as the light level changes](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 You can find this code in the [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device) folder.

😀 Congratulations! Your nightlight program works perfectly!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.