<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-28T19:37:38+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "en"
}
-->
# Decode GPS data - Wio Terminal

In this part of the lesson, you will decode the NMEA messages read from the GPS sensor by the Wio Terminal and extract the latitude and longitude.

## Decode GPS data

Once the raw NMEA data has been read from the serial port, it can be decoded using an open-source NMEA library.

### Task - decode GPS data

Program the device to decode the GPS data.

1. Open the `gps-sensor` app project if it's not already open.

1. Add a library dependency for the [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) library to the project's `platformio.ini` file. This library contains code for decoding NMEA data.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. In `main.cpp`, add an include directive for the TinyGPSPlus library:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Below the declaration of `Serial3`, declare a TinyGPSPlus object to process the NMEA sentences:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Change the contents of the `printGPSData` function to the following:

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

    This code reads the next character from the UART serial port into the `gps` NMEA decoder. After each character, it checks if the decoder has read a valid sentence, then verifies if it has read a valid location. If the location is valid, it sends the data to the serial monitor, along with the number of satellites that contributed to this fix.

1. Build and upload the code to the Wio Terminal.

1. Once uploaded, you can monitor the GPS location data using the serial monitor.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 You can find this code in the [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) folder.

😀 Your GPS sensor program with data decoding was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.