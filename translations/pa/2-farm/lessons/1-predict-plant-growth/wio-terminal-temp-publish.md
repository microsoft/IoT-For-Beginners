<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T11:07:54+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "pa"
}
-->
# ਤਾਪਮਾਨ ਪ੍ਰਕਾਸ਼ਿਤ ਕਰੋ - Wio Terminal

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ Wio Terminal ਦੁਆਰਾ ਪਤਾ ਲਗਾਏ ਗਏ ਤਾਪਮਾਨ ਮੁੱਲਾਂ ਨੂੰ MQTT ਦੇ ਜ਼ਰੀਏ ਪ੍ਰਕਾਸ਼ਿਤ ਕਰੋਗੇ ਤਾਂ ਜੋ ਉਹ ਬਾਅਦ ਵਿੱਚ GDD ਦੀ ਗਣਨਾ ਕਰਨ ਲਈ ਵਰਤੇ ਜਾ ਸਕਣ।

## ਤਾਪਮਾਨ ਪ੍ਰਕਾਸ਼ਿਤ ਕਰੋ

ਜਦੋਂ ਤਾਪਮਾਨ ਪੜ੍ਹਿਆ ਜਾਂਦਾ ਹੈ, ਇਸਨੂੰ MQTT ਦੇ ਜ਼ਰੀਏ ਕੁਝ 'ਸਰਵਰ' ਕੋਡ ਨੂੰ ਪ੍ਰਕਾਸ਼ਿਤ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ ਜੋ ਮੁੱਲਾਂ ਨੂੰ ਪੜ੍ਹੇਗਾ ਅਤੇ GDD ਦੀ ਗਣਨਾ ਲਈ ਤਿਆਰ ਰੱਖੇਗਾ। ਮਾਈਕ੍ਰੋਕੰਟਰੋਲਰ ਇੰਟਰਨੈਟ ਤੋਂ ਸਮਾਂ ਨਹੀਂ ਪੜ੍ਹਦੇ ਅਤੇ ਬਾਕਸ ਤੋਂ ਬਾਹਰ ਇੱਕ ਰੀਅਲ-ਟਾਈਮ ਘੜੀ ਨਾਲ ਸਮਾਂ ਟ੍ਰੈਕ ਨਹੀਂ ਕਰਦੇ, ਜੰਤਰ ਨੂੰ ਇਹ ਕਰਨ ਲਈ ਪ੍ਰੋਗਰਾਮ ਕੀਤਾ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ, ਜੇਕਰ ਇਸ ਵਿੱਚ ਜ਼ਰੂਰੀ ਹਾਰਡਵੇਅਰ ਹੈ।

ਇਸ ਪਾਠ ਲਈ ਚੀਜ਼ਾਂ ਸਧਾਰਨ ਬਣਾਉਣ ਲਈ, ਸੈਂਸਰ ਡਾਟਾ ਦੇ ਨਾਲ ਸਮਾਂ ਨਹੀਂ ਭੇਜਿਆ ਜਾਵੇਗਾ, ਇਸਦੀ ਬਜਾਏ ਇਹ ਬਾਅਦ ਵਿੱਚ ਜਦੋਂ ਸਰਵਰ ਕੋਡ ਸੁਨੇਹੇ ਪ੍ਰਾਪਤ ਕਰਦਾ ਹੈ, ਜੋੜਿਆ ਜਾ ਸਕਦਾ ਹੈ।

### ਕੰਮ

ਜੰਤਰ ਨੂੰ ਤਾਪਮਾਨ ਡਾਟਾ ਪ੍ਰਕਾਸ਼ਿਤ ਕਰਨ ਲਈ ਪ੍ਰੋਗਰਾਮ ਕਰੋ।

1. `temperature-sensor` Wio Terminal ਪ੍ਰੋਜੈਕਟ ਖੋਲ੍ਹੋ

1. ਪਾਠ 4 ਵਿੱਚ ਕੀਤੇ ਕਦਮਾਂ ਨੂੰ ਦੁਹਰਾਓ ਤਾਂ ਕਿ MQTT ਨਾਲ ਜੁੜ ਸਕੋ ਅਤੇ ਟੈਲੀਮੇਟਰੀ ਭੇਜ ਸਕੋ। ਤੁਸੀਂ ਉਹੀ ਪਬਲਿਕ Mosquitto ਬ੍ਰੋਕਰ ਵਰਤ ਰਹੇ ਹੋਵੋਗੇ।

    ਇਸ ਲਈ ਕਦਮ ਹਨ:

    - `.ini` ਫਾਈਲ ਵਿੱਚ Seeed WiFi ਅਤੇ MQTT ਲਾਇਬ੍ਰੇਰੀਆਂ ਸ਼ਾਮਲ ਕਰੋ
    - WiFi ਨਾਲ ਜੁੜਨ ਲਈ ਕਨਫਿਗ ਫਾਈਲ ਅਤੇ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ
    - MQTT ਬ੍ਰੋਕਰ ਨਾਲ ਜੁੜਨ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ
    - ਟੈਲੀਮੇਟਰੀ ਪ੍ਰਕਾਸ਼ਿਤ ਕਰਨ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ

    > ⚠️ [MQTT ਨਾਲ ਜੁੜਨ ਲਈ ਹਦਾਇਤਾਂ](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) ਅਤੇ [ਟੈਲੀਮੇਟਰੀ ਭੇਜਣ ਲਈ ਹਦਾਇਤਾਂ](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) ਪਾਠ 4 ਤੋਂ ਜ਼ਰੂਰ ਵੇਖੋ ਜੇ ਲੋੜ ਹੋਵੇ।

1. ਯਕੀਨੀ ਬਣਾਓ ਕਿ `config.h` ਹੈਡਰ ਫਾਈਲ ਵਿੱਚ `CLIENT_NAME` ਇਸ ਪ੍ਰੋਜੈਕਟ ਨੂੰ ਦਰਸਾਉਂਦਾ ਹੈ:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. ਟੈਲੀਮੇਟਰੀ ਲਈ, ਲਾਈਟ ਮੁੱਲ ਭੇਜਣ ਦੀ ਬਜਾਏ, DHT ਸੈਂਸਰ ਤੋਂ ਪੜ੍ਹੇ ਤਾਪਮਾਨ ਮੁੱਲ ਨੂੰ JSON ਦਸਤਾਵੇਜ਼ ਵਿੱਚ `temperature` ਨਾਮਕ ਪ੍ਰਾਪਰਟੀ ਵਿੱਚ ਭੇਜੋ। ਇਸ ਲਈ `main.cpp` ਵਿੱਚ `loop` ਫੰਕਸ਼ਨ ਨੂੰ ਬਦਲੋ:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. ਤਾਪਮਾਨ ਮੁੱਲ ਨੂੰ ਬਹੁਤ ਵਾਰ ਪੜ੍ਹਨ ਦੀ ਲੋੜ ਨਹੀਂ ਹੈ - ਇਹ ਛੋਟੇ ਸਮੇਂ ਵਿੱਚ ਬਹੁਤ ਜ਼ਿਆਦਾ ਨਹੀਂ ਬਦਲਦਾ, ਇਸ ਲਈ `loop` ਫੰਕਸ਼ਨ ਵਿੱਚ `delay` ਨੂੰ 10 ਮਿੰਟ ਲਈ ਸੈਟ ਕਰੋ:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 `delay` ਫੰਕਸ਼ਨ ਸਮਾਂ ਮਿਲੀਸੈਕੰਡ ਵਿੱਚ ਲੈਂਦਾ ਹੈ, ਇਸ ਲਈ ਇਸਨੂੰ ਪੜ੍ਹਨ ਲਈ ਆਸਾਨ ਬਣਾਉਣ ਲਈ ਮੁੱਲ ਇੱਕ ਗਣਨਾ ਦੇ ਨਤੀਜੇ ਵਜੋਂ ਦਿੱਤਾ ਜਾਂਦਾ ਹੈ। 1,000ms ਇੱਕ ਸਕਿੰਟ ਵਿੱਚ, 60s ਇੱਕ ਮਿੰਟ ਵਿੱਚ, ਇਸ ਲਈ 10 x (60s ਇੱਕ ਮਿੰਟ ਵਿੱਚ) x (1000ms ਇੱਕ ਸਕਿੰਟ ਵਿੱਚ) 10 ਮਿੰਟ ਦੇਰੀ ਦਿੰਦਾ ਹੈ।

1. ਇਸਨੂੰ ਆਪਣੇ Wio Terminal ਵਿੱਚ ਅੱਪਲੋਡ ਕਰੋ, ਅਤੇ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਵੇਖੋ ਕਿ ਤਾਪਮਾਨ MQTT ਬ੍ਰੋਕਰ ਨੂੰ ਭੇਜਿਆ ਜਾ ਰਿਹਾ ਹੈ।

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

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) ਫੋਲਡਰ ਵਿੱਚ ਪਾ ਸਕਦੇ ਹੋ।

😀 ਤੁਸੀਂ ਸਫਲਤਾਪੂਰਵਕ ਆਪਣੇ ਜੰਤਰ ਤੋਂ ਟੈਲੀਮੇਟਰੀ ਵਜੋਂ ਤਾਪਮਾਨ ਪ੍ਰਕਾਸ਼ਿਤ ਕਰ ਦਿੱਤਾ ਹੈ।

---

**ਅਸਵੀਕਾਰਨਾ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀਤਾ ਲਈ ਯਤਨਸ਼ੀਲ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁੱਤੀਆਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।