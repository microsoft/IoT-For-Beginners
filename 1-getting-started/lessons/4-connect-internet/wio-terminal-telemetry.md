# Control your nightlight over the Internet - Wio Terminal

In this part of the lesson, you will send telemetry with light levels from your Wio Terminal to the MQTT broker.

## Install the JSON Arduino libraries

A popular way to send messages over MQTT is using JSON. There is an Arduino library for JSON that makes reading and writing JSON documents easier.

### Task

Install the Arduino JSON library.

1. Open the nightlight project in VS Code.

1. Add the following as an additional line to the `lib_deps` list in the `platformio.ini` file:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    This imports [ArduinoJson](https://arduinojson.org), an Arduino JSON library.

## Publish telemetry

The next step is to create a JSON document with telemetry and send it to the MQTT broker.

### Task

Publish telemetry to the MQTT broker.

1. Add the following code to the bottom of the `config.h` file to define the telemetry topic name for the MQTT broker:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    The `CLIENT_TELEMETRY_TOPIC` is the topic the device will publish light levels to.

1. Open the `main.cpp` file

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
    JsonObject obj = doc.as<JsonObject>();
    serializeJson(obj, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    This code reads the light level, and creates a JSON document using ArduinoJson containing this level. This is then serialized to a string and published on the telemetry MQTT topic by the MQTT client.

1. Upload the code to your Wio Terminal, and use the Serial Monitor to see the light levels being sent to the MQTT broker.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 You can find this code in the [code-telemetry/wio-terminal](code-telemetry/wio-terminal) folder.

😀 You have successfully sent telemetry from your device.
