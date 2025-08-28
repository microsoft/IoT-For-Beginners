<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-28T09:39:03+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "sk"
}
-->
# Dekódovanie GPS údajov - Virtuálny IoT hardvér a Raspberry Pi

V tejto časti lekcie dekódujete NMEA správy, ktoré číta GPS senzor cez Raspberry Pi alebo Virtuálne IoT zariadenie, a extrahujete zemepisnú šírku a dĺžku.

## Dekódovanie GPS údajov

Keď sú surové NMEA údaje prečítané zo sériového portu, môžu byť dekódované pomocou open source NMEA knižnice.

### Úloha - dekódovanie GPS údajov

Naprogramujte zariadenie na dekódovanie GPS údajov.

1. Otvorte projekt aplikácie `gps-sensor`, ak ešte nie je otvorený.

1. Nainštalujte balík `pynmea2` cez Pip. Tento balík obsahuje kód na dekódovanie NMEA správ.

    ```sh
    pip3 install pynmea2
    ```

1. Pridajte nasledujúci kód do importov v súbore `app.py`, aby ste importovali modul `pynmea2`:

    ```python
    import pynmea2
    ```

1. Nahraďte obsah funkcie `print_gps_data` nasledujúcim kódom:

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

    Tento kód použije knižnicu `pynmea2` na analýzu riadku prečítaného zo sériového portu UART.

    Ak je typ vety správy `GGA`, ide o správu o určení polohy, ktorá sa spracuje. Hodnoty zemepisnej šírky a dĺžky sa prečítajú zo správy a prevedú na desatinné stupne z NMEA formátu `(d)ddmm.mmmm`. Funkcia `dm_to_sd` vykonáva tento prevod.

    Následne sa skontroluje smer zemepisnej šírky, a ak je šírka južná, hodnota sa prevedie na záporné číslo. To isté platí pre zemepisnú dĺžku, ak je západná, prevedie sa na záporné číslo.

    Nakoniec sa súradnice vytlačia do konzoly spolu s počtom satelitov použitých na určenie polohy.

1. Spustite kód. Ak používate virtuálne IoT zariadenie, uistite sa, že aplikácia CounterFit je spustená a GPS údaje sa odosielajú.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Tento kód nájdete v priečinku [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) alebo v priečinku [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 Váš program pre GPS senzor s dekódovaním údajov bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre dôležité informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.