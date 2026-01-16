<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-28T20:23:44+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "en"
}
-->
# Measure soil moisture - Wio Terminal

In this part of the lesson, you will add a capacitive soil moisture sensor to your Wio Terminal and read values from it.

## Hardware

The Wio Terminal requires a capacitive soil moisture sensor.

The sensor you'll use is a [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), which measures soil moisture by detecting the capacitance of the soil, a property that changes as the soil's moisture level changes. As the soil moisture increases, the voltage decreases.

This is an analog sensor, so it connects to the analog pins on the Wio Terminal, using an onboard ADC to generate a value between 0 and 1,023.

### Connect the soil moisture sensor

The Grove soil moisture sensor can be connected to the Wio Terminal's configurable analog/digital port.

#### Task - connect the soil moisture sensor

Connect the soil moisture sensor.

![A grove soil moisture sensor](../../../../../translated_images/en/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. Insert one end of a Grove cable into the socket on the soil moisture sensor. It will only fit in one way.

1. With the Wio Terminal disconnected from your computer or any other power source, connect the other end of the Grove cable to the right-hand side Grove socket on the Wio Terminal as you face the screen. This is the socket farthest from the power button.

![The grove soil moisture sensor connected to the right hand socket](../../../../../translated_images/en/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. Insert the soil moisture sensor into the soil. The sensor has a 'highest position line'—a white line across it. Insert the sensor up to, but not beyond, this line.

![The grove soil moisture sensor in soil](../../../../../translated_images/en/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. You can now connect the Wio Terminal to your computer.

## Program the soil moisture sensor

The Wio Terminal can now be programmed to use the attached soil moisture sensor.

### Task - program the soil moisture sensor

Program the device.

1. Create a new Wio Terminal project using PlatformIO. Name this project `soil-moisture-sensor`. Add code in the `setup` function to configure the serial port.

    > ⚠️ You can refer to [the instructions for creating a PlatformIO project in project 1, lesson 1 if needed](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. There isn't a library for this sensor, but you can read from the analog pin using the built-in Arduino [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) function. Start by configuring the analog pin for input so values can be read from it by adding the following to the `setup` function.

    ```cpp
    pinMode(A0, INPUT);
    ```

    This sets the `A0` pin, the combined analog/digital pin, as an input pin from which voltage can be read.

1. Add the following to the `loop` function to read the voltage from this pin:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Below this code, add the following code to print the value to the serial port:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Finally, add a delay of 10 seconds at the end:

    ```cpp
    delay(10000);
    ```

1. Build and upload the code to the Wio Terminal.

    > ⚠️ You can refer to [the instructions for creating a PlatformIO project in project 1, lesson 1 if needed](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Once uploaded, you can monitor the soil moisture using the serial monitor. Add some water to the soil or remove the sensor from the soil and observe the value change.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    In the example output above, you can see the voltage drop as water is added.

> 💁 You can find this code in the [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) folder.

😀 Your soil moisture sensor program was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.