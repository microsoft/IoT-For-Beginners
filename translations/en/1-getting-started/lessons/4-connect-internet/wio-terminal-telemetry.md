<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-28T19:58:04+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "en"
}
-->
# Control your nightlight over the Internet - Wio Terminal

In this part of the lesson, you will send telemetry data with light levels from your Wio Terminal to the MQTT broker.

## Install the JSON Arduino libraries

A common way to send messages over MQTT is by using JSON. There is an Arduino library for JSON that simplifies reading and writing JSON documents.

### Task

Install the Arduino JSON library.

1. Open the nightlight project in VS Code.

1. Add the following as an additional line to the `lib_deps` list in the `platformio.ini` file:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    This imports [ArduinoJson](https://arduinojson.org), an Arduino JSON library.

## Publish telemetry

The next step is to create a JSON document with telemetry data and send it to the MQTT broker.

### Task - publish telemetry

Send telemetry data to the MQTT broker.

1. Add the following code to the bottom of the `config.h` file to define the telemetry topic name for the MQTT broker:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    The `CLIENT_TELEMETRY_TOPIC` is the topic where the device will publish light levels.

1. Open the `main.cpp` file.

1. Add the following `#include` directive to the top of the file:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Add the following code inside the `loop` function, just before the `delay`:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    This code reads the light level and creates a JSON document using ArduinoJson that contains this level. It is then serialized into a string and published to the telemetry MQTT topic by the MQTT client.

1. Upload the code to your Wio Terminal, and use the Serial Monitor to observe the light levels being sent to the MQTT broker.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 You can find this code in the [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) folder.

😀 You have successfully sent telemetry data from your device.

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.