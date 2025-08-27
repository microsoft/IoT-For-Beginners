<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-27T22:54:46+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "nl"
}
-->
# Decode GPS-gegevens - Virtuele IoT-hardware en Raspberry Pi

In dit deel van de les decodeer je de NMEA-berichten die door de GPS-sensor worden gelezen via de Raspberry Pi of Virtuele IoT-apparaat, en haal je de breedte- en lengtegraad eruit.

## Decodeer GPS-gegevens

Zodra de ruwe NMEA-gegevens van de seriële poort zijn gelezen, kunnen ze worden gedecodeerd met behulp van een open source NMEA-bibliotheek.

### Taak - decodeer GPS-gegevens

Programmeer het apparaat om de GPS-gegevens te decoderen.

1. Open het `gps-sensor`-app-project als het nog niet geopend is.

1. Installeer het `pynmea2` Pip-pakket. Dit pakket bevat code om NMEA-berichten te decoderen.

    ```sh
    pip3 install pynmea2
    ```

1. Voeg de volgende code toe aan de imports in het bestand `app.py` om de module `pynmea2` te importeren:

    ```python
    import pynmea2
    ```

1. Vervang de inhoud van de functie `print_gps_data` door het volgende:

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    Deze code gebruikt de `pynmea2`-bibliotheek om de regel die is gelezen van de UART-seriële poort te parseren.

    Als het zinstype van het bericht `GGA` is, dan is dit een positie-fixbericht en wordt het verwerkt. De breedte- en lengtegraadwaarden worden uit het bericht gelezen en omgezet naar decimale graden vanuit het NMEA-formaat `(d)ddmm.mmmm`. De functie `dm_to_sd` voert deze conversie uit.

    Vervolgens wordt de richting van de breedtegraad gecontroleerd, en als de breedtegraad zuidelijk is, wordt de waarde omgezet naar een negatief getal. Hetzelfde geldt voor de lengtegraad: als deze westelijk is, wordt deze omgezet naar een negatief getal.

    Uiteindelijk worden de coördinaten naar de console geprint, samen met het aantal satellieten dat is gebruikt om de locatie te bepalen.

1. Voer de code uit. Als je een virtueel IoT-apparaat gebruikt, zorg er dan voor dat de CounterFit-app actief is en de GPS-gegevens worden verzonden.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Je kunt deze code vinden in de map [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device), of in de map [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 Je GPS-sensorprogramma met gegevensdecodering is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.