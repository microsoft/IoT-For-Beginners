<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-11-18T18:28:22+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "pcm"
}
-->
# Control your nightlight for Internet - Wio Terminal

For dis part of di lesson, you go send telemetry wey get light levels from your Wio Terminal go di MQTT broker.

## Install di JSON Arduino libraries

One popular way wey people dey use send message for MQTT na JSON. Arduino get one library for JSON wey dey make am easy to read and write JSON documents.

### Task

Install di Arduino JSON library.

1. Open di nightlight project for VS Code.

1. Add dis one line join di `lib_deps` list for di `platformio.ini` file:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Dis one go import [ArduinoJson](https://arduinojson.org), wey be Arduino JSON library.

## Publish telemetry

Di next step na to create one JSON document wey get telemetry and send am go di MQTT broker.

### Task - publish telemetry

Publish telemetry go di MQTT broker.

1. Add dis code for di bottom of di `config.h` file to define di telemetry topic name for di MQTT broker:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    Di `CLIENT_TELEMETRY_TOPIC` na di topic wey di device go dey use publish light levels.

1. Open di `main.cpp` file

1. Add dis `#include` directive for di top of di file:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Add dis code inside di `loop` function, just before di `delay`:

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

    Dis code go read di light level, create one JSON document wey get di light level using ArduinoJson. Di document go then serialize to string and publish am for di telemetry MQTT topic by di MQTT client.

1. Upload di code go your Wio Terminal, and use di Serial Monitor to see di light levels wey dem dey send go di MQTT broker.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 You fit find dis code for di [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) folder.

😀 You don successfully send telemetry from your device.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator) do di translation. Even as we dey try make am correct, abeg make you sabi say machine translation fit get mistake or no dey accurate well. Di original dokyument wey dey for di native language na di main source wey you go trust. For important mata, e good make professional human translator check am. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->