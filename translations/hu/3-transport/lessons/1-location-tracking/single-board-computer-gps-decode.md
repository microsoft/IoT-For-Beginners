<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-27T21:42:26+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "hu"
}
-->
# GPS-adatok dekódolása - Virtuális IoT Hardver és Raspberry Pi

Ebben a leckében az NMEA üzeneteket fogod dekódolni, amelyeket a GPS-érzékelő olvas be a Raspberry Pi vagy a Virtuális IoT Eszköz segítségével, és kinyered a szélességi és hosszúsági adatokat.

## GPS-adatok dekódolása

Miután a nyers NMEA adatokat beolvastad a soros portból, egy nyílt forráskódú NMEA könyvtár segítségével dekódolhatod azokat.

### Feladat - GPS-adatok dekódolása

Programozd be az eszközt, hogy dekódolja a GPS-adatokat.

1. Nyisd meg a `gps-sensor` alkalmazás projektet, ha még nincs megnyitva.

1. Telepítsd a `pynmea2` Pip csomagot. Ez a csomag tartalmazza az NMEA üzenetek dekódolásához szükséges kódot.

    ```sh
    pip3 install pynmea2
    ```

1. Add hozzá a következő kódot az `app.py` fájl importjaihoz, hogy importáld a `pynmea2` modult:

    ```python
    import pynmea2
    ```

1. Cseréld le a `print_gps_data` függvény tartalmát a következőre:

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

    Ez a kód a `pynmea2` könyvtárat használja az UART soros portból beolvasott sor elemzésére.

    Ha az üzenet mondattípusa `GGA`, akkor ez egy pozíciófix üzenet, amelyet feldolgozunk. Az üzenetből kiolvassuk a szélességi és hosszúsági értékeket, és átalakítjuk azokat tizedes fokokra az NMEA `(d)ddmm.mmmm` formátumából. Ezt az átalakítást a `dm_to_sd` függvény végzi el.

    Ezután ellenőrizzük a szélesség irányát, és ha a szélesség déli, akkor az értéket negatív számra alakítjuk. Ugyanez történik a hosszúsággal is: ha nyugati, akkor negatív számra konvertáljuk.

    Végül a koordinátákat kiírjuk a konzolra, valamint a helymeghatározáshoz használt műholdak számát is.

1. Futtasd a kódot. Ha virtuális IoT eszközt használsz, győződj meg róla, hogy a CounterFit alkalmazás fut, és a GPS-adatok küldése aktív.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Ezt a kódot megtalálod a [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) mappában, vagy a [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi) mappában.

😀 A GPS-érzékelő programod az adatok dekódolásával sikeresen működött!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.