<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-10-11T12:00:56+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "et"
}
-->
# GPS-andmete dekodeerimine - Virtuaalne IoT-seade ja Raspberry Pi

Selles õppetunni osas dekodeerid NMEA sõnumeid, mida GPS-sensor loeb Raspberry Pi või Virtuaalse IoT-seadme abil, ning eraldad laius- ja pikkuskraadi.

## GPS-andmete dekodeerimine

Kui toorandmed NMEA formaadis on loetud serial porti kaudu, saab neid dekodeerida avatud lähtekoodiga NMEA teegi abil.

### Ülesanne - GPS-andmete dekodeerimine

Programmeerige seade GPS-andmete dekodeerimiseks.

1. Ava `gps-sensor` rakenduse projekt, kui see pole juba avatud.

1. Paigalda `pynmea2` Pip pakett. See pakett sisaldab koodi NMEA sõnumite dekodeerimiseks.

    ```sh
    pip3 install pynmea2
    ```

1. Lisa järgmine kood `app.py` faili importide sektsiooni, et importida `pynmea2` moodul:

    ```python
    import pynmea2
    ```

1. Asenda `print_gps_data` funktsiooni sisu järgmisega:

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

    See kood kasutab `pynmea2` teeki, et parsida UART serial portist loetud rida.

    Kui sõnumi lause tüüp on `GGA`, siis tegemist on positsiooni fikseerimise sõnumiga, mida töödeldakse. Laius- ja pikkuskraadi väärtused loetakse sõnumist ning konverteeritakse kümnendkraadideks NMEA `(d)ddmm.mmmm` formaadist. Funktsioon `dm_to_sd` teeb selle konversiooni.

    Seejärel kontrollitakse laiuskraadi suunda, ja kui laiuskraad on lõunas, siis väärtus konverteeritakse negatiivseks. Sama kehtib pikkuskraadi puhul, kui see on läänes, siis konverteeritakse see negatiivseks.

    Lõpuks prinditakse koordinaadid konsoolile koos satelliitide arvuga, mida kasutati asukoha määramiseks.

1. Käivita kood. Kui kasutad virtuaalset IoT-seadet, siis veendu, et CounterFit rakendus töötab ja GPS-andmeid saadetakse.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Selle koodi leiad [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) kaustast või [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi) kaustast.

😀 Sinu GPS-sensori programm koos andmete dekodeerimisega oli edukas!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.