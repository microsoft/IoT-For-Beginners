<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-28T20:38:36+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "en"
}
-->
# Publish temperature - Wio Terminal

In this part of the lesson, you will send the temperature values detected by the Wio Terminal via MQTT so they can later be used to calculate GDD.

## Publish the temperature

After reading the temperature, it can be sent via MQTT to some 'server' code that will process the values and store them for GDD calculations. Microcontrollers don't inherently fetch time from the Internet or track it using a real-time clock; they need to be programmed to do so, provided they have the required hardware.

To keep things simple for this lesson, the time won't be sent along with the sensor data. Instead, the server code can add the timestamp when it receives the messages.

### Task

Program the device to send the temperature data.

1. Open the `temperature-sensor` Wio Terminal project.

1. Repeat the steps from lesson 4 to connect to MQTT and send telemetry. You will use the same public Mosquitto broker.

    The steps are as follows:

    - Add the Seeed WiFi and MQTT libraries to the `.ini` file.
    - Include the configuration file and code to connect to WiFi.
    - Add the code to connect to the MQTT broker.
    - Add the code to send telemetry.

    > ⚠️ Refer to the [instructions for connecting to MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) and the [instructions for sending telemetry](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) from lesson 4 if needed.

1. Ensure the `CLIENT_NAME` in the `config.h` header file matches this project:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. For telemetry, instead of sending a light value, send the temperature value read from the DHT sensor in a property called `temperature` within the JSON document by modifying the `loop` function in `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. The temperature doesn't need to be read frequently since it doesn't change much in a short period. Set the `delay` in the `loop` function to 10 minutes:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 The `delay` function takes time in milliseconds. To make it easier to understand, the value is calculated as follows: 1,000ms in a second, 60 seconds in a minute, so 10 x (60 seconds per minute) x (1,000ms per second) results in a 10-minute delay.

1. Upload the code to your Wio Terminal and use the serial monitor to observe the temperature being sent to the MQTT broker.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 You can find this code in the [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) folder.

😀 Congratulations! You have successfully sent the temperature as telemetry from your device.

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.