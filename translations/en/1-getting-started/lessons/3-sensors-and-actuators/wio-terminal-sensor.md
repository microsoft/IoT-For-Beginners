<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-28T20:10:46+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "en"
}
-->
# Add a sensor - Wio Terminal

In this part of the lesson, you will use the light sensor on your Wio Terminal.

## Hardware

The sensor for this lesson is a **light sensor** that uses a [photodiode](https://wikipedia.org/wiki/Photodiode) to convert light into an electrical signal. This is an analog sensor that provides an integer value between 0 and 1,023, representing a relative amount of light. However, this value does not correspond to any standard unit of measurement like [lux](https://wikipedia.org/wiki/Lux).

The light sensor is integrated into the Wio Terminal and can be seen through the transparent plastic window on the back.

![The light sensor on the back of the Wio Terminal](../../../../../translated_images/en/wio-light-sensor.b1f529f3c95f5165.webp)

## Program the light sensor

Now, you can program the device to use the built-in light sensor.

### Task

Program the device.

1. Open the nightlight project in VS Code that you created in the previous part of this assignment.

1. Add the following line to the bottom of the `setup` function:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    This line sets up the pins used to communicate with the sensor hardware.

    The `WIO_LIGHT` pin represents the GPIO pin connected to the on-board light sensor. This pin is configured as `INPUT`, meaning it connects to a sensor and data will be read from it.

1. Delete the contents of the `loop` function.

1. Add the following code to the now-empty `loop` function:

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    This code reads an analog value from the `WIO_LIGHT` pin. It retrieves a value between 0 and 1,023 from the on-board light sensor. The value is then sent to the serial port, allowing you to view it in the Serial Monitor while the code is running. `Serial.print` writes the text without adding a new line at the end, so each line will start with `Light value:` and end with the actual light value.

1. Add a short delay of one second (1,000ms) at the end of the `loop`, as the light levels don't need to be checked continuously. Adding a delay also reduces the device's power consumption.

    ```cpp
    delay(1000);
    ```

1. Reconnect the Wio Terminal to your computer, and upload the new code as you did before.

1. Open the Serial Monitor. Light values will be displayed in the terminal. Cover and uncover the light sensor on the back of the Wio Terminal, and you will see the values change.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 You can find this code in the [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal) folder.

😀 Congratulations! You successfully added a sensor to your nightlight program!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is recommended. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.