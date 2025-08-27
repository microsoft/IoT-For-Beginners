<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-27T21:42:15+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "sw"
}
-->
# Kufasiri Data za GPS - Vifaa vya IoT vya Kijumlisha na Raspberry Pi

Katika sehemu hii ya somo, utafasiri jumbe za NMEA zilizosomeka kutoka kwa kihisi cha GPS na Raspberry Pi au Kifaa cha IoT cha Kijumlisha, na kutoa latitudo na longitudo.

## Kufasiri Data za GPS

Baada ya data ghafi ya NMEA kusomwa kutoka kwenye bandari ya serial, inaweza kufasiriwa kwa kutumia maktaba ya NMEA ya chanzo huria.

### Kazi - kufasiri data za GPS

Programu kifaa ili kufasiri data za GPS.

1. Fungua mradi wa programu ya `gps-sensor` ikiwa haujafunguliwa tayari.

1. Sakinisha kifurushi cha Pip `pynmea2`. Kifurushi hiki kina msimbo wa kufasiri jumbe za NMEA.

    ```sh
    pip3 install pynmea2
    ```

1. Ongeza msimbo ufuatao kwenye sehemu ya imports katika faili ya `app.py` ili kuingiza moduli ya `pynmea2`:

    ```python
    import pynmea2
    ```

1. Badilisha yaliyomo kwenye kazi ya `print_gps_data` na yafuatayo:

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

    Msimbo huu utatumia maktaba ya `pynmea2` kuchanganua mstari uliochukuliwa kutoka kwenye bandari ya serial ya UART.

    Ikiwa aina ya sentensi ya ujumbe ni `GGA`, basi huu ni ujumbe wa kurekebisha nafasi, na unachakatwa. Thamani za latitudo na longitudo zinasomwa kutoka kwenye ujumbe na kubadilishwa kuwa digrii za desimali kutoka kwenye muundo wa NMEA `(d)ddmm.mmmm`. Kazi ya `dm_to_sd` hufanya ubadilishaji huu.

    Mwelekeo wa latitudo unakaguliwa, na ikiwa latitudo iko kusini, basi thamani inabadilishwa kuwa namba hasi. Vivyo hivyo kwa longitudo, ikiwa iko magharibi basi inabadilishwa kuwa namba hasi.

    Hatimaye, kuratibu zinachapishwa kwenye koni, pamoja na idadi ya setilaiti zilizotumika kupata eneo.

1. Endesha msimbo. Ikiwa unatumia kifaa cha IoT cha kijumlisha, hakikisha programu ya CounterFit inaendeshwa na data ya GPS inatumwa.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Unaweza kupata msimbo huu katika folda ya [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device), au folda ya [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 Programu yako ya kihisi cha GPS yenye kufasiri data imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.