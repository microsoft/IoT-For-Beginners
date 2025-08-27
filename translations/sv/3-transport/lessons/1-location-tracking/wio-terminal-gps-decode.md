<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T21:25:07+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "sv"
}
-->
# Avkoda GPS-data - Wio Terminal

I den här delen av lektionen kommer du att avkoda NMEA-meddelanden som lästs från GPS-sensorn med Wio Terminal och extrahera latitud och longitud.

## Avkoda GPS-data

När de råa NMEA-data har lästs från seriella porten kan de avkodas med hjälp av ett open source NMEA-bibliotek.

### Uppgift - avkoda GPS-data

Programmera enheten för att avkoda GPS-data.

1. Öppna projektet `gps-sensor` om det inte redan är öppet.

1. Lägg till ett biblioteksberoende för [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus)-biblioteket i projektets `platformio.ini`-fil. Detta bibliotek innehåller kod för att avkoda NMEA-data.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. I `main.cpp`, lägg till en include-direktiv för TinyGPSPlus-biblioteket:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Nedanför deklarationen av `Serial3`, deklarera ett TinyGPSPlus-objekt för att bearbeta NMEA-meningarna:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Ändra innehållet i funktionen `printGPSData` till följande:

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

    Den här koden läser nästa tecken från UART-serieporten in i `gps` NMEA-avkodaren. Efter varje tecken kontrollerar den om avkodaren har läst en giltig mening och sedan om den har läst en giltig plats. Om platsen är giltig skickar den den till seriemonitorn tillsammans med antalet satelliter som bidrog till denna fix.

1. Bygg och ladda upp koden till Wio Terminal.

1. När koden har laddats upp kan du övervaka GPS-platsdata med hjälp av seriemonitorn.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Du kan hitta denna kod i mappen [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Ditt GPS-sensorprogram med datatolkning blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiska översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.