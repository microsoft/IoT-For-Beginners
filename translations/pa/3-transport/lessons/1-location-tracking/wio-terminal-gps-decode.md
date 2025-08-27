<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T14:50:30+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "pa"
}
-->
# GPS ਡਾਟਾ ਡਿਕੋਡ ਕਰੋ - Wio Terminal

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ Wio Terminal ਦੁਆਰਾ GPS ਸੈਂਸਰ ਤੋਂ ਪੜ੍ਹੇ ਗਏ NMEA ਸੁਨੇਹਿਆਂ ਨੂੰ ਡਿਕੋਡ ਕਰੋਗੇ ਅਤੇ ਲੈਟੀਟਿਊਡ ਅਤੇ ਲੌਂਗਿਟਿਊਡ ਨੂੰ ਕੱਢੋਗੇ।

## GPS ਡਾਟਾ ਡਿਕੋਡ ਕਰੋ

ਜਦੋਂ ਕੱਚਾ NMEA ਡਾਟਾ ਸੀਰੀਅਲ ਪੋਰਟ ਤੋਂ ਪੜ੍ਹਿਆ ਜਾਂਦਾ ਹੈ, ਤਾਂ ਇਸਨੂੰ ਇੱਕ ਓਪਨ ਸੋਰਸ NMEA ਲਾਇਬ੍ਰੇਰੀ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਡਿਕੋਡ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ।

### ਟਾਸਕ - GPS ਡਾਟਾ ਡਿਕੋਡ ਕਰੋ

ਡਿਵਾਈਸ ਨੂੰ GPS ਡਾਟਾ ਡਿਕੋਡ ਕਰਨ ਲਈ ਪ੍ਰੋਗਰਾਮ ਕਰੋ।

1. ਜੇ `gps-sensor` ਐਪ ਪ੍ਰੋਜੈਕਟ ਖੁੱਲਾ ਨਹੀਂ ਹੈ, ਤਾਂ ਇਸਨੂੰ ਖੋਲ੍ਹੋ।

1. ਪ੍ਰੋਜੈਕਟ ਦੇ `platformio.ini` ਫਾਈਲ ਵਿੱਚ [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) ਲਾਇਬ੍ਰੇਰੀ ਲਈ ਇੱਕ ਲਾਇਬ੍ਰੇਰੀ ਡਿਪੈਂਡੈਂਸੀ ਸ਼ਾਮਲ ਕਰੋ। ਇਸ ਲਾਇਬ੍ਰੇਰੀ ਵਿੱਚ NMEA ਡਾਟਾ ਡਿਕੋਡ ਕਰਨ ਲਈ ਕੋਡ ਹੈ।

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. `main.cpp` ਵਿੱਚ, TinyGPSPlus ਲਾਇਬ੍ਰੇਰੀ ਲਈ ਇੱਕ ਸ਼ਾਮਲ ਕਰਨ ਵਾਲਾ ਨਿਰਦੇਸ਼ ਜੋੜੋ:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. `Serial3` ਦੇ ਐਲਾਨ ਤੋਂ ਹੇਠਾਂ, NMEA ਵਾਕਾਂ ਨੂੰ ਪ੍ਰੋਸੈਸ ਕਰਨ ਲਈ ਇੱਕ TinyGPSPlus ਆਬਜੈਕਟ ਦਾ ਐਲਾਨ ਕਰੋ:

    ```cpp
    TinyGPSPlus gps;
    ```

1. `printGPSData` ਫੰਕਸ਼ਨ ਦੀ ਸਮੱਗਰੀ ਨੂੰ ਹੇਠਾਂ ਦਿੱਤੇ ਅਨੁਸਾਰ ਬਦਲੋ:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    ਇਹ ਕੋਡ UART ਸੀਰੀਅਲ ਪੋਰਟ ਤੋਂ ਅਗਲਾ ਅੱਖਰ `gps` NMEA ਡਿਕੋਡਰ ਵਿੱਚ ਪੜ੍ਹਦਾ ਹੈ। ਹਰ ਅੱਖਰ ਤੋਂ ਬਾਅਦ, ਇਹ ਜਾਂਚੇਗਾ ਕਿ ਡਿਕੋਡਰ ਨੇ ਇੱਕ ਵੈਧ ਵਾਕ ਪੜ੍ਹਿਆ ਹੈ ਜਾਂ ਨਹੀਂ, ਫਿਰ ਜਾਂਚੇਗਾ ਕਿ ਇਸਨੇ ਇੱਕ ਵੈਧ ਸਥਾਨ ਪੜ੍ਹਿਆ ਹੈ ਜਾਂ ਨਹੀਂ। ਜੇ ਸਥਾਨ ਵੈਧ ਹੈ, ਤਾਂ ਇਹ ਇਸਨੂੰ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਨੂੰ ਭੇਜੇਗਾ, ਨਾਲ ਹੀ ਉਨ੍ਹਾਂ ਸੈਟੇਲਾਈਟਾਂ ਦੀ ਗਿਣਤੀ ਜੋ ਇਸ ਫਿਕਸ ਵਿੱਚ ਯੋਗਦਾਨ ਪਾਉਂਦੀਆਂ ਹਨ।

1. ਕੋਡ ਨੂੰ Wio Terminal ਵਿੱਚ ਬਣਾਓ ਅਤੇ ਅਪਲੋਡ ਕਰੋ।

1. ਜਦੋਂ ਅਪਲੋਡ ਹੋ ਜਾਵੇ, ਤਾਂ ਤੁਸੀਂ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਦੀ ਵਰਤੋਂ ਕਰਕੇ GPS ਸਥਾਨ ਡਾਟਾ ਦੀ ਨਿਗਰਾਨੀ ਕਰ ਸਕਦੇ ਹੋ।

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ GPS ਸੈਂਸਰ ਪ੍ਰੋਗਰਾਮ ਡਾਟਾ ਡਿਕੋਡਿੰਗ ਨਾਲ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਾਰਨਾ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁੱਤੀਆਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼, ਜੋ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਹੈ, ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।