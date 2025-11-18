<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-11-18T19:07:47+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "pcm"
}
-->
# Decode GPS data - Wio Terminal

For dis part of di lesson, you go decode di NMEA messages wey di GPS sensor for di Wio Terminal don read, and you go fit extract di latitude and longitude.

## Decode GPS data

Once you don read di raw NMEA data from di serial port, you fit decode am using one open source NMEA library.

### Task - decode GPS data

Program di device make e decode di GPS data.

1. Open di `gps-sensor` app project if e never dey open before.

1. Add library dependency for di [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) library to di project `platformio.ini` file. Dis library get code wey fit decode NMEA data.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. For `main.cpp`, add one include directive for di TinyGPSPlus library:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Under di declaration of `Serial3`, declare one TinyGPSPlus object wey go process di NMEA sentences:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Change wetin dey inside di `printGPSData` function to dis one:

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

   Dis code go read di next character from di UART serial port enter di `gps` NMEA decoder. After each character, e go check whether di decoder don read valid sentence, then e go check whether e don read valid location. If di location valid, e go send am go di serial monitor, plus di number of satellites wey contribute to di fix.

1. Build and upload di code go di Wio Terminal.

1. Once you don upload am, you fit dey monitor di GPS location data using di serial monitor.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 You fit find dis code for di [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) folder.

😀 Your GPS sensor program wey dey decode data don work well!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI transleshion service [Co-op Translator](https://github.com/Azure/co-op-translator) do di transleshion. Even as we dey try make am accurate, abeg make you sabi say automatik transleshion fit get mistake or no dey correct well. Di original dokyument wey dey di native language na di main source wey you go fit trust. For important mata, e good make you use professional human transleshion. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis transleshion.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->