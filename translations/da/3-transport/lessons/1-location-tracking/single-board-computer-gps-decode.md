<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-27T21:26:27+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "da"
}
-->
# Dekodér GPS-data - Virtuel IoT-hardware og Raspberry Pi

I denne del af lektionen vil du dekodere NMEA-beskeder, der er læst fra GPS-sensoren af Raspberry Pi eller Virtuel IoT-enhed, og udtrække bredde- og længdegrad.

## Dekodér GPS-data

Når de rå NMEA-data er blevet læst fra den serielle port, kan de dekodes ved hjælp af et open source NMEA-bibliotek.

### Opgave - dekodér GPS-data

Programmer enheden til at dekodere GPS-data.

1. Åbn `gps-sensor`-app-projektet, hvis det ikke allerede er åbent.

1. Installer `pynmea2` Pip-pakken. Denne pakke indeholder kode til dekodering af NMEA-beskeder.

    ```sh
    pip3 install pynmea2
    ```

1. Tilføj følgende kode til imports i `app.py`-filen for at importere `pynmea2`-modulet:

    ```python
    import pynmea2
    ```

1. Erstat indholdet af funktionen `print_gps_data` med følgende:

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

    Denne kode vil bruge `pynmea2`-biblioteket til at analysere linjen, der er læst fra UART-serielporten.

    Hvis sætningstypen for beskeden er `GGA`, er dette en positionsfix-besked og behandles. Bredde- og længdegradsværdierne læses fra beskeden og konverteres til decimalgrader fra NMEA-formatet `(d)ddmm.mmmm`. Funktionen `dm_to_sd` udfører denne konvertering.

    Retningen for breddegraden kontrolleres derefter, og hvis breddegraden er syd, konverteres værdien til et negativt tal. Det samme gælder for længdegraden; hvis den er vest, konverteres den til et negativt tal.

    Til sidst udskrives koordinaterne til konsollen sammen med antallet af satellitter, der blev brugt til at bestemme positionen.

1. Kør koden. Hvis du bruger en virtuel IoT-enhed, skal du sørge for, at CounterFit-appen kører, og at GPS-dataene bliver sendt.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Du kan finde denne kode i mappen [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) eller mappen [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 Dit GPS-sensorprogram med datadekodering var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.