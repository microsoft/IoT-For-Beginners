# Decode GPS data - Wio Terminal

In this part of the lesson, you will decode the NMEA messages read from the GPS sensor by the Wio Terminal, and extract the latitude and longitude.

## Decode GPS data

Once the raw NMEA data has been read from the serial port, it can be decoded using an open source NMEA library.

### Task - decode GPS data

Program the device to decode the GPS data.

1. Open the `gps-sensor` app project if it's not already open

1. Add a library dependency for the [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) library to the projects `platformio.ini` file. This library has code for decoding NMEA data.

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

1. Change the contents of the `print_gps_data` function to be the following:

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

    This code reads the next character from the UART serial port into the `gps` NMEA decoder. After each character, it will check to see if the decoder has read a valid sentence, then check to see if it has read a valid location. If the location is valid, it send it to the serial monitor, along with the number of satellites that contributed to this fix.

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

> 💁 You can find this code in the [code-gps-decode/wio-terminal](code-gps-decode/wio-terminal) folder.

😀 Your GPS sensor program with data decoding was a success!
