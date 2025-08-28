<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-28T13:19:27+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "sl"
}
-->
# Dekodiranje GPS podatkov - Virtualna IoT strojna oprema in Raspberry Pi

V tem delu lekcije boste dekodirali NMEA sporočila, ki jih Raspberry Pi ali Virtualna IoT naprava prebere iz GPS senzorja, in iz njih pridobili zemljepisno širino in dolžino.

## Dekodiranje GPS podatkov

Ko so surovi NMEA podatki prebrani iz serijskega porta, jih je mogoče dekodirati z uporabo odprtokodne knjižnice NMEA.

### Naloga - dekodiranje GPS podatkov

Programirajte napravo za dekodiranje GPS podatkov.

1. Odprite projekt aplikacije `gps-sensor`, če še ni odprt.

1. Namestite Pip paket `pynmea2`. Ta paket vsebuje kodo za dekodiranje NMEA sporočil.

    ```sh
    pip3 install pynmea2
    ```

1. Dodajte naslednjo kodo v uvoze v datoteki `app.py`, da uvozite modul `pynmea2`:

    ```python
    import pynmea2
    ```

1. Zamenjajte vsebino funkcije `print_gps_data` z naslednjo:

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

    Ta koda bo uporabila knjižnico `pynmea2` za razčlenitev vrstice, prebrane iz serijskega porta UART.

    Če je tip stavka sporočila `GGA`, gre za sporočilo o določitvi položaja, ki se obdela. Vrednosti zemljepisne širine in dolžine se preberejo iz sporočila in pretvorijo v decimalne stopinje iz NMEA formata `(d)ddmm.mmmm`. Funkcija `dm_to_sd` izvede to pretvorbo.

    Nato se preveri smer zemljepisne širine, in če je širina južna, se vrednost pretvori v negativno število. Enako velja za zemljepisno dolžino – če je zahodna, se pretvori v negativno število.

    Na koncu se koordinate natisnejo na konzolo skupaj s številom satelitov, uporabljenih za določitev lokacije.

1. Zaženite kodo. Če uporabljate virtualno IoT napravo, poskrbite, da je aplikacija CounterFit zagnana in da se GPS podatki pošiljajo.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 To kodo lahko najdete v mapi [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) ali v mapi [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 Vaš program za GPS senzor z dekodiranjem podatkov je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni prevod s strani človeka. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.