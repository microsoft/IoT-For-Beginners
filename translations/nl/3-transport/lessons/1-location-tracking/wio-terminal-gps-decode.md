<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T22:56:18+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "nl"
}
-->
# Decode GPS-gegevens - Wio Terminal

In dit deel van de les decodeer je de NMEA-berichten die door de GPS-sensor van de Wio Terminal worden gelezen en haal je de breedte- en lengtegraad eruit.

## Decodeer GPS-gegevens

Zodra de ruwe NMEA-gegevens van de seriële poort zijn gelezen, kunnen ze worden gedecodeerd met behulp van een open source NMEA-bibliotheek.

### Taak - decodeer GPS-gegevens

Programmeur het apparaat om de GPS-gegevens te decoderen.

1. Open het `gps-sensor` app-project als het nog niet geopend is.

1. Voeg een bibliotheekafhankelijkheid toe voor de [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) bibliotheek aan het `platformio.ini` bestand van het project. Deze bibliotheek bevat code voor het decoderen van NMEA-gegevens.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. Voeg in `main.cpp` een include-directive toe voor de TinyGPSPlus-bibliotheek:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Onder de declaratie van `Serial3`, declareer een TinyGPSPlus-object om de NMEA-zinnen te verwerken:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Verander de inhoud van de `printGPSData`-functie in het volgende:

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

    Deze code leest het volgende karakter van de UART-seriële poort in de `gps` NMEA-decoder. Na elk karakter controleert het of de decoder een geldige zin heeft gelezen en vervolgens of het een geldige locatie heeft gelezen. Als de locatie geldig is, wordt deze naar de seriële monitor gestuurd, samen met het aantal satellieten dat heeft bijgedragen aan deze fix.

1. Bouw en upload de code naar de Wio Terminal.

1. Zodra de code is geüpload, kun je de GPS-locatiegegevens monitoren met behulp van de seriële monitor.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Je kunt deze code vinden in de map [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Je GPS-sensorprogramma met gegevensdecodering is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we ons best doen voor nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.