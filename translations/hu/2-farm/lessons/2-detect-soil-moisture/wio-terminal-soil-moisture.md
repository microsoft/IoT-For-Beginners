<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-27T22:56:09+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "hu"
}
-->
# Talajnedvesség mérése - Wio Terminal

Ebben a leckében egy kapacitív talajnedvesség-érzékelőt fogsz hozzáadni a Wio Terminalhoz, és értékeket olvasol le róla.

## Hardver

A Wio Terminalhoz egy kapacitív talajnedvesség-érzékelő szükséges.

Az általad használt érzékelő egy [Kapacitív Talajnedvesség-érzékelő](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), amely a talaj kapacitását méri. Ez a tulajdonság változik a talaj nedvességtartalmának függvényében. Ahogy a talaj nedvessége nő, a feszültség csökken.

Ez egy analóg érzékelő, amely az analóg pinekhez csatlakozik a Wio Terminalon, és egy beépített ADC segítségével 0-1,023 közötti értéket hoz létre.

### Csatlakoztasd a talajnedvesség-érzékelőt

A Grove talajnedvesség-érzékelő a Wio Terminal konfigurálható analóg/digitális portjához csatlakoztatható.

#### Feladat - csatlakoztasd a talajnedvesség-érzékelőt

Csatlakoztasd a talajnedvesség-érzékelőt.

![Egy Grove talajnedvesség-érzékelő](../../../../../translated_images/hu/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. Illeszd be a Grove kábel egyik végét a talajnedvesség-érzékelő aljzatába. Csak egyféleképpen illeszthető be.

1. Amíg a Wio Terminal nincs csatlakoztatva a számítógépedhez vagy más áramforráshoz, csatlakoztasd a Grove kábel másik végét a Wio Terminal jobb oldali Grove aljzatába, ahogy a képernyőre nézel. Ez az aljzat van a legtávolabb a bekapcsológombtól.

![A Grove talajnedvesség-érzékelő csatlakoztatva a jobb oldali aljzathoz](../../../../../translated_images/hu/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. Helyezd a talajnedvesség-érzékelőt a talajba. Az érzékelőn van egy "legmagasabb pozíció vonal" - egy fehér vonal az érzékelőn. Helyezd be az érzékelőt eddig a vonalig, de ne tovább.

![A Grove talajnedvesség-érzékelő a talajban](../../../../../translated_images/hu/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. Most csatlakoztathatod a Wio Terminalt a számítógépedhez.

## Programozd a talajnedvesség-érzékelőt

Most már programozhatod a Wio Terminalt, hogy használja a csatlakoztatott talajnedvesség-érzékelőt.

### Feladat - programozd a talajnedvesség-érzékelőt

Programozd az eszközt.

1. Hozz létre egy teljesen új Wio Terminal projektet a PlatformIO segítségével. Nevezd el ezt a projektet `soil-moisture-sensor`-nak. Adj hozzá kódot a `setup` függvényben a soros port konfigurálásához.

    > ⚠️ Ha szükséges, hivatkozhatsz [az 1. projekt, 1. lecke PlatformIO projekt létrehozására vonatkozó utasításaira](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Ehhez az érzékelőhöz nincs külön könyvtár, helyette az analóg pinekről az Arduino beépített [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) függvényével olvashatsz adatokat. Kezdd azzal, hogy az analóg pint bemeneti üzemmódra állítod, hogy értékeket olvashass le róla. Ehhez add hozzá a következőt a `setup` függvényhez:

    ```cpp
    pinMode(A0, INPUT);
    ```

    Ez az `A0` pint, a kombinált analóg/digitális pint bemeneti üzemmódra állítja, hogy feszültséget lehessen róla olvasni.

1. Add hozzá a következőt a `loop` függvényhez, hogy olvasd a feszültséget erről a pinről:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Ezután add hozzá a következő kódot, hogy az értéket kiírd a soros portra:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Végül adj hozzá egy 10 másodperces késleltetést a végére:

    ```cpp
    delay(10000);
    ```

1. Fordítsd le és töltsd fel a kódot a Wio Terminalra.

    > ⚠️ Ha szükséges, hivatkozhatsz [az 1. projekt, 1. lecke PlatformIO projekt létrehozására vonatkozó utasításaira](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Feltöltés után a soros monitor segítségével figyelheted a talajnedvességet. Adj vizet a talajhoz, vagy vedd ki az érzékelőt a talajból, és figyeld meg, hogyan változik az érték.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    A fenti példakimenetben láthatod, hogy a feszültség csökken, ahogy vizet adsz hozzá.

> 💁 Ezt a kódot megtalálod a [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) mappában.

😀 A talajnedvesség-érzékelő programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális, emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.