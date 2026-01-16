<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-27T12:52:05+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "pa"
}
-->
# Wio Terminal 'ਤੇ ਸੈਂਸਰ ਸ਼ਾਮਲ ਕਰੋ

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਆਪਣੇ Wio Terminal 'ਤੇ ਲਾਈਟ ਸੈਂਸਰ ਦੀ ਵਰਤੋਂ ਕਰੋਗੇ।

## ਹਾਰਡਵੇਅਰ

ਇਸ ਪਾਠ ਲਈ ਸੈਂਸਰ ਇੱਕ **ਲਾਈਟ ਸੈਂਸਰ** ਹੈ ਜੋ [ਫੋਟੋਡਾਇਓਡ](https://wikipedia.org/wiki/Photodiode) ਦੀ ਵਰਤੋਂ ਕਰਦਾ ਹੈ ਜੋ ਰੌਸ਼ਨੀ ਨੂੰ ਬਿਜਲੀ ਸੰਕੇਤ ਵਿੱਚ ਬਦਲਦਾ ਹੈ। ਇਹ ਇੱਕ ਐਨਾਲੌਗ ਸੈਂਸਰ ਹੈ ਜੋ 0 ਤੋਂ 1,023 ਤੱਕ ਦਾ ਪੂਰਨ ਅੰਕ ਮੁੱਲ ਭੇਜਦਾ ਹੈ ਜੋ ਰੌਸ਼ਨੀ ਦੀ ਸਪੱਸ਼ਟ ਮਾਤਰਾ ਦਰਸਾਉਂਦਾ ਹੈ, ਪਰ ਇਹ ਕਿਸੇ ਮਿਆਰੀ ਮਾਪ ਜਿਵੇਂ ਕਿ [ਲਕਸ](https://wikipedia.org/wiki/Lux) ਨਾਲ ਨਹੀਂ ਜੁੜਦਾ।

ਲਾਈਟ ਸੈਂਸਰ Wio Terminal ਵਿੱਚ ਬਣਿਆ ਹੋਇਆ ਹੈ ਅਤੇ ਇਹ ਪਿੱਛੇ ਦੇ ਪਾਰਦਰਸ਼ੀ ਪਲਾਸਟਿਕ ਵਿੰਡੋ ਰਾਹੀਂ ਦਿਖਾਈ ਦਿੰਦਾ ਹੈ।

![Wio Terminal ਦੇ ਪਿੱਛੇ ਲਾਈਟ ਸੈਂਸਰ](../../../../../translated_images/pa/wio-light-sensor.b1f529f3c95f5165.png)

## ਲਾਈਟ ਸੈਂਸਰ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ

ਹੁਣ ਜੰਤਰ ਨੂੰ ਅੰਦਰੂਨੀ ਲਾਈਟ ਸੈਂਸਰ ਦੀ ਵਰਤੋਂ ਕਰਨ ਲਈ ਪ੍ਰੋਗਰਾਮ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ।

### ਕੰਮ

ਜੰਤਰ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ।

1. VS Code ਵਿੱਚ ਨਾਈਟਲਾਈਟ ਪ੍ਰੋਜੈਕਟ ਖੋਲ੍ਹੋ ਜੋ ਤੁਸੀਂ ਇਸ ਅਸਾਈਨਮੈਂਟ ਦੇ ਪਿਛਲੇ ਹਿੱਸੇ ਵਿੱਚ ਬਣਾਇਆ ਸੀ।

1. `setup` ਫੰਕਸ਼ਨ ਦੇ ਅੰਤ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤੀ ਲਾਈਨ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    ਇਹ ਲਾਈਨ ਸੈਂਸਰ ਹਾਰਡਵੇਅਰ ਨਾਲ ਸੰਚਾਰ ਕਰਨ ਲਈ ਵਰਤੇ ਗਏ ਪਿਨਾਂ ਨੂੰ ਕਨਫਿਗਰ ਕਰਦੀ ਹੈ।

    `WIO_LIGHT` ਪਿਨ ਉਹ GPIO ਪਿਨ ਹੈ ਜੋ ਅੰਦਰੂਨੀ ਲਾਈਟ ਸੈਂਸਰ ਨਾਲ ਜੁੜਿਆ ਹੋਇਆ ਹੈ। ਇਸ ਪਿਨ ਨੂੰ `INPUT` ਤੇ ਸੈਟ ਕੀਤਾ ਗਿਆ ਹੈ, ਜਿਸਦਾ ਮਤਲਬ ਹੈ ਕਿ ਇਹ ਸੈਂਸਰ ਨਾਲ ਜੁੜਦਾ ਹੈ ਅਤੇ ਪਿਨ ਤੋਂ ਡਾਟਾ ਪੜ੍ਹਿਆ ਜਾਵੇਗਾ।

1. `loop` ਫੰਕਸ਼ਨ ਦੀ ਸਮੱਗਰੀ ਨੂੰ ਮਿਟਾ ਦਿਓ।

1. ਹੁਣ ਖਾਲੀ `loop` ਫੰਕਸ਼ਨ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ।

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    ਇਹ ਕੋਡ `WIO_LIGHT` ਪਿਨ ਤੋਂ ਇੱਕ ਐਨਾਲੌਗ ਮੁੱਲ ਪੜ੍ਹਦਾ ਹੈ। ਇਹ ਅੰਦਰੂਨੀ ਲਾਈਟ ਸੈਂਸਰ ਤੋਂ 0-1,023 ਤੱਕ ਦਾ ਮੁੱਲ ਪੜ੍ਹਦਾ ਹੈ। ਇਹ ਮੁੱਲ ਫਿਰ ਸੀਰੀਅਲ ਪੋਰਟ ਨੂੰ ਭੇਜਿਆ ਜਾਂਦਾ ਹੈ ਤਾਂ ਜੋ ਤੁਸੀਂ ਇਸ ਕੋਡ ਦੇ ਚੱਲਣ ਦੌਰਾਨ ਇਸਨੂੰ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਵਿੱਚ ਪੜ੍ਹ ਸਕੋ। `Serial.print` ਟੈਕਸਟ ਨੂੰ ਬਿਨਾਂ ਨਵੇਂ ਲਾਈਨ ਦੇ ਅੰਤ ਵਿੱਚ ਲਿਖਦਾ ਹੈ, ਇਸ ਲਈ ਹਰ ਲਾਈਨ `Light value:` ਨਾਲ ਸ਼ੁਰੂ ਹੋਵੇਗੀ ਅਤੇ ਅਸਲ ਲਾਈਟ ਮੁੱਲ ਨਾਲ ਖਤਮ ਹੋਵੇਗੀ।

1. `loop` ਦੇ ਅੰਤ ਵਿੱਚ ਇੱਕ ਸਕਿੰਟ (1,000ms) ਦੀ ਛੋਟੀ ਜਿਹੀ ਡਿਲੇ ਸ਼ਾਮਲ ਕਰੋ ਕਿਉਂਕਿ ਲਾਈਟ ਪੱਧਰ ਨੂੰ ਲਗਾਤਾਰ ਜਾਂਚਣ ਦੀ ਲੋੜ ਨਹੀਂ ਹੈ। ਡਿਲੇ ਜੰਤਰ ਦੀ ਪਾਵਰ ਖਪਤ ਨੂੰ ਘਟਾਉਂਦਾ ਹੈ।

    ```cpp
    delay(1000);
    ```

1. Wio Terminal ਨੂੰ ਮੁੜ ਆਪਣੇ ਕੰਪਿਊਟਰ ਨਾਲ ਜੁੜੋ ਅਤੇ ਪਹਿਲਾਂ ਵਾਂਗ ਨਵਾਂ ਕੋਡ ਅੱਪਲੋਡ ਕਰੋ।

1. ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਨਾਲ ਜੁੜੋ। ਲਾਈਟ ਮੁੱਲ ਟਰਮੀਨਲ 'ਤੇ ਆਉਣਗੇ। Wio Terminal ਦੇ ਪਿੱਛੇ ਲਾਈਟ ਸੈਂਸਰ ਨੂੰ ਢੱਕੋ ਅਤੇ ਖੋਲ੍ਹੋ, ਅਤੇ ਮੁੱਲ ਬਦਲਣਗੇ।

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

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਆਪਣੇ ਨਾਈਟਲਾਈਟ ਪ੍ਰੋਗਰਾਮ ਵਿੱਚ ਸੈਂਸਰ ਸ਼ਾਮਲ ਕਰਨਾ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਰਤਾ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚੀਤਤਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।