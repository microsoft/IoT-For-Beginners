<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-28T20:40:32+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "en"
}
-->
# Measure temperature - Wio Terminal

In this part of the lesson, you will add a temperature sensor to your Wio Terminal and read temperature values from it.

## Hardware

The Wio Terminal requires a temperature sensor.

The sensor you'll use is a [DHT11 humidity and temperature sensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), which combines two sensors in one package. This is a fairly popular sensor, with many commercially available options that combine temperature, humidity, and sometimes atmospheric pressure. The temperature sensor component is a negative temperature coefficient (NTC) thermistor, meaning its resistance decreases as the temperature increases.

This is a digital sensor, so it has an onboard ADC that generates a digital signal containing the temperature and humidity data, which the microcontroller can read.

### Connect the temperature sensor

The Grove temperature sensor can be connected to the Wio Terminal's digital port.

#### Task - connect the temperature sensor

Connect the temperature sensor.

![A grove temperature sensor](../../../../../translated_images/en/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Insert one end of a Grove cable into the socket on the humidity and temperature sensor. It will only fit in one way.

1. With the Wio Terminal disconnected from your computer or other power source, connect the other end of the Grove cable to the right-hand Grove socket on the Wio Terminal as you face the screen. This is the socket farthest from the power button.

![The grove temperature sensor connected to the right hand socket](../../../../../translated_images/en/wio-temperature-sensor.2934928f38c7f79a.webp)

## Program the temperature sensor

The Wio Terminal can now be programmed to use the attached temperature sensor.

### Task - program the temperature sensor

Program the device.

1. Create a new Wio Terminal project using PlatformIO. Name this project `temperature-sensor`. Add code in the `setup` function to configure the serial port.

    > ⚠️ You can refer to [the instructions for creating a PlatformIO project in project 1, lesson 1 if needed](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Add a library dependency for the Seeed Grove Humidity and Temperature sensor library to the project's `platformio.ini` file:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ You can refer to [the instructions for adding libraries to a PlatformIO project in project 1, lesson 4 if needed](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Add the following `#include` directives to the top of the file, under the existing `#include <Arduino.h>`:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    This imports the files needed to interact with the sensor. The `DHT.h` header file contains the code for the sensor itself, and adding the `SPI.h` header ensures the code needed to communicate with the sensor is included when the app is compiled.

1. Before the `setup` function, declare the DHT sensor:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    This declares an instance of the `DHT` class that manages the **D**igital **H**umidity and **T**emperature sensor. It is connected to port `D0`, the right-hand Grove socket on the Wio Terminal. The second parameter specifies that the sensor being used is the *DHT11* sensor—the library you are using supports other variants of this sensor.

1. In the `setup` function, add code to set up the serial connection:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. At the end of the `setup` function, after the last `delay`, add a call to start the DHT sensor:

    ```cpp
    dht.begin();
    ```

1. In the `loop` function, add code to call the sensor and print the temperature to the serial port:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    This code declares an empty array of two floats and passes it to the `readTempAndHumidity` method on the `DHT` instance. This method populates the array with two values: the humidity is stored in the 0th item in the array (remember, in C++ arrays are 0-based, so the 0th item is the 'first' item), and the temperature is stored in the 1st item.

    The temperature is read from the 1st item in the array and printed to the serial port.

    > 🇺🇸 The temperature is read in Celsius. For Americans, to convert this to Fahrenheit, divide the Celsius value by 5, multiply by 9, and then add 32. For example, a temperature reading of 20°C becomes ((20/5)*9) + 32 = 68°F.

1. Build and upload the code to the Wio Terminal.

    > ⚠️ You can refer to [the instructions for creating a PlatformIO project in project 1, lesson 1 if needed](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Once uploaded, you can monitor the temperature using the serial monitor:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 You can find this code in the [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal) folder.

😀 Your temperature sensor program was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.