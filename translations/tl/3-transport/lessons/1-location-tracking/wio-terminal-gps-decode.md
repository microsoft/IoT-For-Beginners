<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T23:50:59+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "tl"
}
-->
# I-decode ang GPS data - Wio Terminal

Sa bahaging ito ng aralin, ide-decode mo ang mga NMEA message na nabasa mula sa GPS sensor gamit ang Wio Terminal, at kukunin ang latitude at longitude.

## I-decode ang GPS data

Kapag nabasa na ang raw NMEA data mula sa serial port, maaari itong i-decode gamit ang isang open source na NMEA library.

### Gawain - i-decode ang GPS data

I-program ang device upang i-decode ang GPS data.

1. Buksan ang proyekto ng `gps-sensor` app kung hindi pa ito nakabukas.

1. Magdagdag ng library dependency para sa [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) library sa `platformio.ini` file ng proyekto. Ang library na ito ay may code para sa pag-decode ng NMEA data.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. Sa `main.cpp`, magdagdag ng include directive para sa TinyGPSPlus library:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Sa ibaba ng deklarasyon ng `Serial3`, magdeklara ng TinyGPSPlus object upang iproseso ang mga NMEA sentence:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Palitan ang nilalaman ng `printGPSData` function ng sumusunod:

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

    Ang code na ito ay nagbabasa ng susunod na character mula sa UART serial port papunta sa `gps` NMEA decoder. Pagkatapos ng bawat character, susuriin nito kung ang decoder ay nakabasa ng valid na sentence, at pagkatapos ay susuriin kung nakabasa ito ng valid na lokasyon. Kung ang lokasyon ay valid, ipapadala ito sa serial monitor, kasama ang bilang ng mga satellite na nag-ambag sa fix na ito.

1. I-build at i-upload ang code sa Wio Terminal.

1. Kapag na-upload na, maaari mong i-monitor ang GPS location data gamit ang serial monitor.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Makikita mo ang code na ito sa [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) folder.

😀 Tagumpay ang iyong GPS sensor program na may data decoding!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.