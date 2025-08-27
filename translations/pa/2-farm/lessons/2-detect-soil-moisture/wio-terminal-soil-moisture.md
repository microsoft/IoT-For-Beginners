<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-27T11:47:25+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "pa"
}
-->
# ਮਿੱਟੀ ਦੀ ਨਮੀ ਮਾਪੋ - Wio ਟਰਮੀਨਲ

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਆਪਣੇ Wio ਟਰਮੀਨਲ ਵਿੱਚ ਇੱਕ ਕੈਪੇਸਿਟਿਵ ਮਿੱਟੀ ਨਮੀ ਸੈਂਸਰ ਸ਼ਾਮਲ ਕਰੋਗੇ ਅਤੇ ਇਸ ਤੋਂ ਮੁੱਲ ਪੜ੍ਹੋਗੇ।

## ਹਾਰਡਵੇਅਰ

Wio ਟਰਮੀਨਲ ਲਈ ਇੱਕ ਕੈਪੇਸਿਟਿਵ ਮਿੱਟੀ ਨਮੀ ਸੈਂਸਰ ਦੀ ਲੋੜ ਹੈ।

ਤੁਸੀਂ ਜੋ ਸੈਂਸਰ ਵਰਤੋਗੇ ਉਹ ਹੈ [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), ਜੋ ਮਿੱਟੀ ਦੀ ਨਮੀ ਨੂੰ ਮਿੱਟੀ ਦੀ ਕੈਪੇਸਿਟੈਂਸ ਦਾ ਪਤਾ ਲਗਾ ਕੇ ਮਾਪਦਾ ਹੈ। ਕੈਪੇਸਿਟੈਂਸ ਇੱਕ ਗੁਣ ਹੈ ਜੋ ਮਿੱਟੀ ਦੀ ਨਮੀ ਦੇ ਬਦਲਣ ਨਾਲ ਬਦਲਦਾ ਹੈ। ਜਿਵੇਂ ਜਿਵੇਂ ਮਿੱਟੀ ਦੀ ਨਮੀ ਵਧਦੀ ਹੈ, ਵੋਲਟੇਜ ਘਟਦਾ ਹੈ।

ਇਹ ਇੱਕ ਐਨਾਲੌਗ ਸੈਂਸਰ ਹੈ, ਇਸ ਲਈ ਇਹ Wio ਟਰਮੀਨਲ ਦੇ ਐਨਾਲੌਗ ਪਿੰਸ ਨਾਲ ਜੁੜਦਾ ਹੈ, ਜੋ 0-1,023 ਤੱਕ ਦਾ ਮੁੱਲ ਬਣਾਉਣ ਲਈ ਆਨਬੋਰਡ ADC ਵਰਤਦਾ ਹੈ।

### ਮਿੱਟੀ ਨਮੀ ਸੈਂਸਰ ਨੂੰ ਜੁੜੋ

Grove ਮਿੱਟੀ ਨਮੀ ਸੈਂਸਰ ਨੂੰ Wio ਟਰਮੀਨਲ ਦੇ ਕਨਫਿਗਰੇਬਲ ਐਨਾਲੌਗ/ਡਿਜੀਟਲ ਪੋਰਟ ਨਾਲ ਜੁੜਿਆ ਜਾ ਸਕਦਾ ਹੈ।

#### ਕੰਮ - ਮਿੱਟੀ ਨਮੀ ਸੈਂਸਰ ਨੂੰ ਜੁੜੋ

ਮਿੱਟੀ ਨਮੀ ਸੈਂਸਰ ਨੂੰ ਜੁੜੋ।

![Grove ਮਿੱਟੀ ਨਮੀ ਸੈਂਸਰ](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.pa.png)

1. Grove ਕੇਬਲ ਦੇ ਇੱਕ ਸਿਰੇ ਨੂੰ ਮਿੱਟੀ ਨਮੀ ਸੈਂਸਰ ਦੇ ਸਾਕਟ ਵਿੱਚ ਪਾਓ। ਇਹ ਸਿਰਫ ਇੱਕ ਹੀ ਦਿਸ਼ਾ ਵਿੱਚ ਜਾਵੇਗਾ।

1. Wio ਟਰਮੀਨਲ ਨੂੰ ਆਪਣੇ ਕੰਪਿਊਟਰ ਜਾਂ ਹੋਰ ਪਾਵਰ ਸਪਲਾਈ ਤੋਂ ਡਿਸਕਨੈਕਟ ਕਰਕੇ ਰੱਖੋ। ਫਿਰ Grove ਕੇਬਲ ਦੇ ਦੂਜੇ ਸਿਰੇ ਨੂੰ Wio ਟਰਮੀਨਲ ਦੇ ਸਕ੍ਰੀਨ ਵੱਲ ਦੇਖਦੇ ਹੋਏ ਸੱਜੇ ਪਾਸੇ ਵਾਲੇ Grove ਸਾਕਟ ਵਿੱਚ ਪਾਓ। ਇਹ ਸਾਕਟ ਪਾਵਰ ਬਟਨ ਤੋਂ ਸਭ ਤੋਂ ਦੂਰ ਹੈ।

![ਸੱਜੇ ਪਾਸੇ ਵਾਲੇ ਸਾਕਟ ਨਾਲ ਜੁੜਿਆ Grove ਮਿੱਟੀ ਨਮੀ ਸੈਂਸਰ](../../../../../translated_images/wio-soil-moisture-sensor.46919b61c3f6cb7497662251b29038ee0e57a4c8b9d071feb996c3b0d7f65aaf.pa.png)

1. ਮਿੱਟੀ ਨਮੀ ਸੈਂਸਰ ਨੂੰ ਮਿੱਟੀ ਵਿੱਚ ਪਾਓ। ਇਸ 'ਤੇ ਇੱਕ 'ਸਭ ਤੋਂ ਉੱਚੀ ਪੋਜ਼ੀਸ਼ਨ ਲਾਈਨ' ਹੈ - ਸੈਂਸਰ 'ਤੇ ਇੱਕ ਚਿੱਟੀ ਲਾਈਨ। ਸੈਂਸਰ ਨੂੰ ਇਸ ਲਾਈਨ ਤੱਕ ਪਾਓ ਪਰ ਇਸ ਤੋਂ ਪਾਰ ਨਾ ਕਰੋ।

![ਮਿੱਟੀ ਵਿੱਚ Grove ਮਿੱਟੀ ਨਮੀ ਸੈਂਸਰ](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e960f8c51ee64b02ee59b32c8c717e3515a2c945f33e614e403.pa.png)

1. ਹੁਣ ਤੁਸੀਂ Wio ਟਰਮੀਨਲ ਨੂੰ ਆਪਣੇ ਕੰਪਿਊਟਰ ਨਾਲ ਜੁੜ ਸਕਦੇ ਹੋ।

## ਮਿੱਟੀ ਨਮੀ ਸੈਂਸਰ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ

ਹੁਣ Wio ਟਰਮੀਨਲ ਨੂੰ ਜੁੜੇ ਹੋਏ ਮਿੱਟੀ ਨਮੀ ਸੈਂਸਰ ਨੂੰ ਵਰਤਣ ਲਈ ਪ੍ਰੋਗਰਾਮ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ।

### ਕੰਮ - ਮਿੱਟੀ ਨਮੀ ਸੈਂਸਰ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ

ਡਿਵਾਈਸ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ।

1. PlatformIO ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਇੱਕ ਨਵਾਂ Wio ਟਰਮੀਨਲ ਪ੍ਰੋਜੈਕਟ ਬਣਾਓ। ਇਸ ਪ੍ਰੋਜੈਕਟ ਦਾ ਨਾਮ `soil-moisture-sensor` ਰੱਖੋ। `setup` ਫੰਕਸ਼ਨ ਵਿੱਚ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ ਤਾਂ ਜੋ ਸੀਰੀਅਲ ਪੋਰਟ ਨੂੰ ਕਨਫਿਗਰ ਕੀਤਾ ਜਾ ਸਕੇ।

    > ⚠️ ਤੁਸੀਂ [ਪ੍ਰੋਜੈਕਟ 1, ਪਾਠ 1 ਵਿੱਚ PlatformIO ਪ੍ਰੋਜੈਕਟ ਬਣਾਉਣ ਲਈ ਹਦਾਇਤਾਂ](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project) ਨੂੰ ਜ਼ਰੂਰਤ ਪੈਣ 'ਤੇ ਵੇਖ ਸਕਦੇ ਹੋ।

1. ਇਸ ਸੈਂਸਰ ਲਈ ਕੋਈ ਲਾਇਬ੍ਰੇਰੀ ਨਹੀਂ ਹੈ, ਇਸ ਲਈ ਤੁਸੀਂ ਐਨਾਲੌਗ ਪਿਨ ਤੋਂ ਪੜ੍ਹਨ ਲਈ Arduino ਦੀ ਬਿਲਟ-ਇਨ [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) ਫੰਕਸ਼ਨ ਦੀ ਵਰਤੋਂ ਕਰ ਸਕਦੇ ਹੋ। ਪਹਿਲਾਂ ਐਨਾਲੌਗ ਪਿਨ ਨੂੰ ਇਨਪੁਟ ਲਈ ਕਨਫਿਗਰ ਕਰੋ ਤਾਂ ਜੋ ਇਸ ਤੋਂ ਮੁੱਲ ਪੜ੍ਹੇ ਜਾ ਸਕਣ। ਇਸ ਨੂੰ `setup` ਫੰਕਸ਼ਨ ਵਿੱਚ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    pinMode(A0, INPUT);
    ```

    ਇਹ `A0` ਪਿਨ, ਜੋ ਕਿ ਕੌਮਬੋ ਐਨਾਲੌਗ/ਡਿਜੀਟਲ ਪਿਨ ਹੈ, ਨੂੰ ਇਨਪੁਟ ਪਿਨ ਵਜੋਂ ਸੈਟ ਕਰਦਾ ਹੈ ਜਿਸ ਤੋਂ ਵੋਲਟੇਜ ਪੜ੍ਹਿਆ ਜਾ ਸਕਦਾ ਹੈ।

1. `loop` ਫੰਕਸ਼ਨ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ ਤਾਂ ਜੋ ਇਸ ਪਿਨ ਤੋਂ ਵੋਲਟੇਜ ਪੜ੍ਹਿਆ ਜਾ ਸਕੇ:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. ਇਸ ਕੋਡ ਦੇ ਹੇਠਾਂ, ਸੀਰੀਅਲ ਪੋਰਟ 'ਤੇ ਮੁੱਲ ਪ੍ਰਿੰਟ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. ਆਖਰ ਵਿੱਚ 10 ਸਕਿੰਟ ਦੀ ਡਿਲੇ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    delay(10000);
    ```

1. ਕੋਡ ਨੂੰ ਬਣਾਓ ਅਤੇ Wio ਟਰਮੀਨਲ 'ਤੇ ਅੱਪਲੋਡ ਕਰੋ।

    > ⚠️ ਤੁਸੀਂ [ਪ੍ਰੋਜੈਕਟ 1, ਪਾਠ 1 ਵਿੱਚ PlatformIO ਪ੍ਰੋਜੈਕਟ ਬਣਾਉਣ ਲਈ ਹਦਾਇਤਾਂ](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app) ਨੂੰ ਜ਼ਰੂਰਤ ਪੈਣ 'ਤੇ ਵੇਖ ਸਕਦੇ ਹੋ।

1. ਅੱਪਲੋਡ ਹੋਣ ਤੋਂ ਬਾਅਦ, ਤੁਸੀਂ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਮਿੱਟੀ ਦੀ ਨਮੀ ਦੀ ਨਿਗਰਾਨੀ ਕਰ ਸਕਦੇ ਹੋ। ਮਿੱਟੀ ਵਿੱਚ ਪਾਣੀ ਸ਼ਾਮਲ ਕਰੋ ਜਾਂ ਸੈਂਸਰ ਨੂੰ ਮਿੱਟੀ ਤੋਂ ਹਟਾਓ ਅਤੇ ਮੁੱਲ ਵਿੱਚ ਬਦਲਾਅ ਵੇਖੋ।

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

    ਉਪਰੋਕਤ ਉਦਾਹਰਣ ਆਉਟਪੁੱਟ ਵਿੱਚ, ਤੁਸੀਂ ਵੇਖ ਸਕਦੇ ਹੋ ਕਿ ਜਿਵੇਂ ਪਾਣੀ ਸ਼ਾਮਲ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਵੋਲਟੇਜ ਘਟਦਾ ਹੈ।

> 💁 ਤੁਸੀਂ ਇਸ ਕੋਡ ਨੂੰ [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਮਿੱਟੀ ਨਮੀ ਸੈਂਸਰ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਰਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀਤਾ ਲਈ ਯਤਨਸ਼ੀਲ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚਤਤਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।