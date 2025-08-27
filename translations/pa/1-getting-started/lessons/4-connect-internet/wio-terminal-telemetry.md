<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-27T12:30:43+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "pa"
}
-->
# ਆਪਣੀ ਨਾਈਟਲਾਈਟ ਨੂੰ ਇੰਟਰਨੈਟ 'ਤੇ ਕੰਟਰੋਲ ਕਰੋ - Wio Terminal

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਆਪਣੇ Wio Terminal ਤੋਂ MQTT ਬ੍ਰੋਕਰ ਨੂੰ ਰੌਸ਼ਨੀ ਦੇ ਪੱਧਰਾਂ ਨਾਲ ਟੈਲੀਮੇਟਰੀ ਭੇਜੋਗੇ।

## JSON Arduino ਲਾਇਬ੍ਰੇਰੀਆਂ ਇੰਸਟਾਲ ਕਰੋ

MQTT 'ਤੇ ਸੁਨੇਹੇ ਭੇਜਣ ਦਾ ਇੱਕ ਲੋਕਪ੍ਰਿਯ ਤਰੀਕਾ JSON ਦੀ ਵਰਤੋਂ ਕਰਨਾ ਹੈ। JSON ਲਈ ਇੱਕ Arduino ਲਾਇਬ੍ਰੇਰੀ ਹੈ ਜੋ JSON ਦਸਤਾਵੇਜ਼ਾਂ ਨੂੰ ਪੜ੍ਹਨ ਅਤੇ ਲਿਖਣ ਨੂੰ ਆਸਾਨ ਬਣਾਉਂਦੀ ਹੈ।

### ਕੰਮ

Arduino JSON ਲਾਇਬ੍ਰੇਰੀ ਇੰਸਟਾਲ ਕਰੋ।

1. VS Code ਵਿੱਚ ਨਾਈਟਲਾਈਟ ਪ੍ਰੋਜੈਕਟ ਖੋਲ੍ਹੋ।

1. `platformio.ini` ਫਾਈਲ ਵਿੱਚ `lib_deps` ਸੂਚੀ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤੀ ਲਾਈਨ ਨੂੰ ਇੱਕ ਵਾਧੂ ਲਾਈਨ ਵਜੋਂ ਸ਼ਾਮਲ ਕਰੋ:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    ਇਹ [ArduinoJson](https://arduinojson.org), ਇੱਕ Arduino JSON ਲਾਇਬ੍ਰੇਰੀ ਨੂੰ ਇੰਪੋਰਟ ਕਰਦਾ ਹੈ।

## ਟੈਲੀਮੇਟਰੀ ਪ੍ਰਕਾਸ਼ਿਤ ਕਰੋ

ਅਗਲਾ ਕਦਮ ਟੈਲੀਮੇਟਰੀ ਨਾਲ ਇੱਕ JSON ਦਸਤਾਵੇਜ਼ ਬਣਾਉਣਾ ਅਤੇ ਇਸਨੂੰ MQTT ਬ੍ਰੋਕਰ ਨੂੰ ਭੇਜਣਾ ਹੈ।

### ਕੰਮ - ਟੈਲੀਮੇਟਰੀ ਪ੍ਰਕਾਸ਼ਿਤ ਕਰੋ

MQTT ਬ੍ਰੋਕਰ ਨੂੰ ਟੈਲੀਮੇਟਰੀ ਭੇਜੋ।

1. `config.h` ਫਾਈਲ ਦੇ ਤਲ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ ਤਾਂ ਜੋ MQTT ਬ੍ਰੋਕਰ ਲਈ ਟੈਲੀਮੇਟਰੀ ਟਾਪਿਕ ਨਾਮ ਨੂੰ ਪਰਿਭਾਸ਼ਿਤ ਕੀਤਾ ਜਾ ਸਕੇ:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` ਉਹ ਟਾਪਿਕ ਹੈ ਜਿਸ 'ਤੇ ਡਿਵਾਈਸ ਰੌਸ਼ਨੀ ਦੇ ਪੱਧਰਾਂ ਨੂੰ ਪ੍ਰਕਾਸ਼ਿਤ ਕਰੇਗਾ।

1. `main.cpp` ਫਾਈਲ ਖੋਲ੍ਹੋ।

1. ਫਾਈਲ ਦੇ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤਾ `#include` ਡਾਇਰੈਕਟਿਵ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `loop` ਫੰਕਸ਼ਨ ਦੇ ਅੰਦਰ, `delay` ਤੋਂ ਥੋੜ੍ਹਾ ਪਹਿਲਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਕੋਡ ਰੌਸ਼ਨੀ ਦੇ ਪੱਧਰ ਨੂੰ ਪੜ੍ਹਦਾ ਹੈ ਅਤੇ ArduinoJson ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਇਸ ਪੱਧਰ ਨਾਲ ਇੱਕ JSON ਦਸਤਾਵੇਜ਼ ਬਣਾਉਂਦਾ ਹੈ। ਇਸਨੂੰ ਇੱਕ ਸਤਰ ਵਿੱਚ ਸੀਰੀਅਲਾਈਜ਼ ਕੀਤਾ ਜਾਂਦਾ ਹੈ ਅਤੇ MQTT ਕਲਾਇੰਟ ਦੁਆਰਾ ਟੈਲੀਮੇਟਰੀ MQTT ਟਾਪਿਕ 'ਤੇ ਪ੍ਰਕਾਸ਼ਿਤ ਕੀਤਾ ਜਾਂਦਾ ਹੈ।

1. ਕੋਡ ਨੂੰ ਆਪਣੇ Wio Terminal 'ਤੇ ਅੱਪਲੋਡ ਕਰੋ ਅਤੇ Serial Monitor ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਦੇਖੋ ਕਿ ਰੌਸ਼ਨੀ ਦੇ ਪੱਧਰ MQTT ਬ੍ਰੋਕਰ ਨੂੰ ਭੇਜੇ ਜਾ ਰਹੇ ਹਨ।

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) ਫੋਲਡਰ ਵਿੱਚ ਪਾ ਸਕਦੇ ਹੋ।

😀 ਤੁਸੀਂ ਸਫਲਤਾਪੂਰਵਕ ਆਪਣੇ ਡਿਵਾਈਸ ਤੋਂ ਟੈਲੀਮੇਟਰੀ ਭੇਜ ਦਿੱਤੀ ਹੈ।

---

**ਅਸਵੀਕਰਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਹਾਲਾਂਕਿ ਅਸੀਂ ਸਹੀਅਤ ਲਈ ਯਤਨਸ਼ੀਲ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚਤਤਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼, ਜੋ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਹੈ, ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।