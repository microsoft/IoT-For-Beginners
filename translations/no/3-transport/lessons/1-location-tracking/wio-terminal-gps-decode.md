<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T21:25:25+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "no"
}
-->
# Dekode GPS-data - Wio Terminal

I denne delen av leksjonen skal du dekode NMEA-meldinger som leses fra GPS-sensoren av Wio Terminal, og hente ut breddegrad og lengdegrad.

## Dekode GPS-data

Når de rå NMEA-dataene er lest fra seriellporten, kan de dekodes ved hjelp av et åpen kildekode NMEA-bibliotek.

### Oppgave - dekode GPS-data

Programmer enheten til å dekode GPS-dataene.

1. Åpne `gps-sensor`-app-prosjektet hvis det ikke allerede er åpent.

1. Legg til en biblioteksavhengighet for [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus)-biblioteket i prosjektets `platformio.ini`-fil. Dette biblioteket inneholder kode for å dekode NMEA-data.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. I `main.cpp`, legg til en include-direktiv for TinyGPSPlus-biblioteket:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Under deklarasjonen av `Serial3`, deklarer et TinyGPSPlus-objekt for å prosessere NMEA-setningene:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Endre innholdet i funksjonen `printGPSData` til følgende:

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

    Denne koden leser neste tegn fra UART-seriellporten inn i `gps` NMEA-dekoderen. Etter hvert tegn vil den sjekke om dekoderen har lest en gyldig setning, og deretter sjekke om den har lest en gyldig posisjon. Hvis posisjonen er gyldig, sender den den til seriellmonitoren, sammen med antall satellitter som bidro til denne posisjonen.

1. Bygg og last opp koden til Wio Terminal.

1. Når koden er lastet opp, kan du overvåke GPS-posisjonsdataene ved hjelp av seriellmonitoren.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Du finner denne koden i [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal)-mappen.

😀 Programmet for GPS-sensoren med datadekoding var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi tilstreber nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.