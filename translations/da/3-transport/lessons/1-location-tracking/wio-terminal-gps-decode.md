<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T21:25:17+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "da"
}
-->
# Dekodér GPS-data - Wio Terminal

I denne del af lektionen vil du dekodere NMEA-beskeder, der er læst fra GPS-sensoren af Wio Terminal, og udtrække bredde- og længdegrad.

## Dekodér GPS-data

Når de rå NMEA-data er blevet læst fra den serielle port, kan de dekodes ved hjælp af et open source NMEA-bibliotek.

### Opgave - dekodér GPS-data

Programmer enheden til at dekodere GPS-data.

1. Åbn `gps-sensor` app-projektet, hvis det ikke allerede er åbent.

1. Tilføj en biblioteksafhængighed for [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus)-biblioteket til projektets `platformio.ini`-fil. Dette bibliotek indeholder kode til dekodering af NMEA-data.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. I `main.cpp` skal du tilføje en include-direktiv for TinyGPSPlus-biblioteket:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Under deklarationen af `Serial3` skal du deklarere et TinyGPSPlus-objekt til at behandle NMEA-sætningerne:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Ændr indholdet af funktionen `printGPSData` til følgende:

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

    Denne kode læser det næste tegn fra UART-serielporten ind i `gps` NMEA-dekoderen. Efter hvert tegn vil den kontrollere, om dekoderen har læst en gyldig sætning, og derefter kontrollere, om den har læst en gyldig position. Hvis positionen er gyldig, sender den den til den serielle monitor sammen med antallet af satellitter, der bidrog til denne fix.

1. Byg og upload koden til Wio Terminal.

1. Når koden er uploadet, kan du overvåge GPS-positioneringsdataene ved hjælp af den serielle monitor.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Du kan finde denne kode i [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal)-mappen.

😀 Dit GPS-sensorprogram med datadekodering var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at opnå nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.