<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-27T21:26:35+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "no"
}
-->
# Dekode GPS-data - Virtuell IoT-maskinvare og Raspberry Pi

I denne delen av leksjonen skal du dekode NMEA-meldingene som leses fra GPS-sensoren av Raspberry Pi eller Virtuell IoT-enhet, og hente ut breddegrad og lengdegrad.

## Dekode GPS-data

Når de rå NMEA-dataene er lest fra seriellporten, kan de dekodes ved hjelp av et åpen kildekode NMEA-bibliotek.

### Oppgave - dekode GPS-data

Programmer enheten til å dekode GPS-dataene.

1. Åpne `gps-sensor`-app-prosjektet hvis det ikke allerede er åpent.

1. Installer `pynmea2` Pip-pakken. Denne pakken inneholder kode for å dekode NMEA-meldinger.

    ```sh
    pip3 install pynmea2
    ```

1. Legg til følgende kode i importene i `app.py`-filen for å importere `pynmea2`-modulen:

    ```python
    import pynmea2
    ```

1. Erstatt innholdet i `print_gps_data`-funksjonen med følgende:

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

    Denne koden bruker `pynmea2`-biblioteket til å analysere linjen som leses fra UART-seriellporten.

    Hvis setningstypen til meldingen er `GGA`, er dette en posisjonsfikseringsmelding, og den behandles. Bredde- og lengdegradsverdiene leses fra meldingen og konverteres til desimalgrader fra NMEA-formatet `(d)ddmm.mmmm`. Funksjonen `dm_to_sd` utfører denne konverteringen.

    Retningen til breddegraden sjekkes deretter, og hvis breddegraden er sør, konverteres verdien til et negativt tall. Det samme gjelder lengdegraden; hvis den er vest, konverteres den til et negativt tall.

    Til slutt skrives koordinatene ut til konsollen, sammen med antall satellitter som ble brukt for å finne posisjonen.

1. Kjør koden. Hvis du bruker en virtuell IoT-enhet, må du sørge for at CounterFit-appen kjører og at GPS-dataene sendes.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Du finner denne koden i [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device)-mappen, eller i [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi)-mappen.

😀 Programmet ditt for GPS-sensor med datadekoding var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.