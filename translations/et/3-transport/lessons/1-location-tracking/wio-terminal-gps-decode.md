<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-10-11T12:00:39+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "et"
}
-->
# GPS-andmete dekodeerimine - Wio Terminal

Selles õppetunni osas dekodeerid NMEA sõnumeid, mida Wio Terminali GPS-sensor loeb, ja eraldad laius- ja pikkuskraadi.

## GPS-andmete dekodeerimine

Kui toored NMEA andmed on jadapordist loetud, saab neid dekodeerida avatud lähtekoodiga NMEA teegi abil.

### Ülesanne - GPS-andmete dekodeerimine

Programmeerige seade GPS-andmete dekodeerimiseks.

1. Ava `gps-sensor` rakenduse projekt, kui see pole juba avatud.

1. Lisa projekti `platformio.ini` faili teegisõltuvus [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) teegile. See teek sisaldab koodi NMEA andmete dekodeerimiseks.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. Lisa `main.cpp` failis TinyGPSPlus teegi jaoks include direktiiv:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Deklareerige `Serial3` deklaratsiooni all TinyGPSPlus objekt NMEA lausetega töötamiseks:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Muuda `printGPSData` funktsiooni sisu järgnevaks:

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

   See kood loeb UART jadapordist järgmise tähemärgi `gps` NMEA dekooderisse. Pärast iga tähemärki kontrollib see, kas dekooder on lugenud kehtiva lause, ja seejärel, kas see on lugenud kehtiva asukoha. Kui asukoht on kehtiv, saadab see selle jadamonitorile koos satelliitide arvuga, mis sellele fikseerimisele kaasa aitasid.

1. Koosta ja laadi kood Wio Terminali.

1. Pärast üleslaadimist saad GPS-i asukohaandmeid jälgida jadamonitori abil.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Selle koodi leiad [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) kaustast.

😀 Sinu GPS-sensori programm andmete dekodeerimisega oli edukas!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.