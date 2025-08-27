<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-27T21:26:18+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "sv"
}
-->
# Avkoda GPS-data - Virtuell IoT-hårdvara och Raspberry Pi

I den här delen av lektionen kommer du att avkoda NMEA-meddelanden som lästs från GPS-sensorn av Raspberry Pi eller Virtuell IoT-enhet, och extrahera latitud och longitud.

## Avkoda GPS-data

När rå NMEA-data har lästs från seriella porten kan den avkodas med hjälp av ett öppet källkods-bibliotek för NMEA.

### Uppgift - avkoda GPS-data

Programmera enheten för att avkoda GPS-data.

1. Öppna projektet `gps-sensor`-appen om det inte redan är öppet.

1. Installera `pynmea2` Pip-paketet. Detta paket innehåller kod för att avkoda NMEA-meddelanden.

    ```sh
    pip3 install pynmea2
    ```

1. Lägg till följande kod i importerna i filen `app.py` för att importera modulen `pynmea2`:

    ```python
    import pynmea2
    ```

1. Ersätt innehållet i funktionen `print_gps_data` med följande:

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

    Den här koden använder biblioteket `pynmea2` för att analysera raden som lästs från UART-seriella porten.

    Om meddelandets sats-typ är `GGA`, är detta ett positionsfixeringsmeddelande och bearbetas. Latitud- och longitudvärdena läses från meddelandet och konverteras till decimalgrader från NMEA-formatet `(d)ddmm.mmmm`. Funktionen `dm_to_sd` utför denna konvertering.

    Latitudens riktning kontrolleras sedan, och om latituden är söderut konverteras värdet till ett negativt tal. Samma sak gäller för longituden; om den är västerut konverteras den till ett negativt tal.

    Slutligen skrivs koordinaterna ut till konsolen, tillsammans med antalet satelliter som används för att få positionen.

1. Kör koden. Om du använder en virtuell IoT-enhet, se till att CounterFit-appen körs och att GPS-data skickas.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Du kan hitta denna kod i mappen [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device), eller mappen [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 Ditt GPS-sensorprogram med dataavkodning blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiska översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.