<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-27T21:42:38+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "cs"
}
-->
# Dekódování GPS dat - Virtuální IoT zařízení a Raspberry Pi

V této části lekce budete dekódovat NMEA zprávy přečtené ze senzoru GPS pomocí Raspberry Pi nebo Virtuálního IoT zařízení a extrahovat zeměpisnou šířku a délku.

## Dekódování GPS dat

Jakmile jsou surová NMEA data přečtena ze sériového portu, mohou být dekódována pomocí open source knihovny NMEA.

### Úkol - dekódování GPS dat

Naprogramujte zařízení tak, aby dekódovalo GPS data.

1. Otevřete projekt aplikace `gps-sensor`, pokud již není otevřený.

1. Nainstalujte balíček `pynmea2` pomocí Pip. Tento balíček obsahuje kód pro dekódování NMEA zpráv.

    ```sh
    pip3 install pynmea2
    ```

1. Přidejte následující kód do importů v souboru `app.py`, abyste importovali modul `pynmea2`:

    ```python
    import pynmea2
    ```

1. Nahraďte obsah funkce `print_gps_data` následujícím:

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

    Tento kód použije knihovnu `pynmea2` k analýze řádku přečteného ze sériového portu UART.

    Pokud je typ věty zprávy `GGA`, jedná se o zprávu o určení polohy, která je zpracována. Hodnoty zeměpisné šířky a délky jsou přečteny ze zprávy a převedeny na desetinné stupně z formátu NMEA `(d)ddmm.mmmm`. Funkce `dm_to_sd` provádí tento převod.

    Poté je zkontrolován směr zeměpisné šířky, a pokud je šířka jižní, hodnota je převedena na záporné číslo. Stejně tak u zeměpisné délky, pokud je západní, je převedena na záporné číslo.

    Nakonec jsou souřadnice vytištěny na konzoli spolu s počtem satelitů použitých k určení polohy.

1. Spusťte kód. Pokud používáte virtuální IoT zařízení, ujistěte se, že aplikace CounterFit běží a GPS data jsou odesílána.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Tento kód najdete ve složce [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) nebo ve složce [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 Vaše programování senzoru GPS s dekódováním dat bylo úspěšné!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za závazný zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.