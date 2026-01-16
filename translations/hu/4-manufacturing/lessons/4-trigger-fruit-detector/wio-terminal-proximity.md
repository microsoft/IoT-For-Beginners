<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-27T20:43:56+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "hu"
}
-->
# Közelség érzékelése - Wio Terminal

Ebben a leckében hozzáadunk egy közelségérzékelőt a Wio Terminalhoz, és távolságot olvasunk le róla.

## Hardver

A Wio Terminalhoz szükség van egy közelségérzékelőre.

Az érzékelő, amit használni fogsz, egy [Grove Time of Flight távolságérzékelő](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Ez az érzékelő lézeres távolságmérő modult használ a távolság érzékeléséhez. Az érzékelő 10mm-től 2000mm-ig (1cm - 2m) terjedő tartományban működik, és ezen a tartományon belül elég pontos értékeket ad, 1000mm feletti távolságokat pedig 8109mm-ként jelzi.

A lézeres távolságmérő az érzékelő hátoldalán található, a Grove csatlakozóval ellentétes oldalon.

Ez egy I2C érzékelő.

### Csatlakoztasd a Time of Flight érzékelőt

A Grove Time of Flight érzékelő csatlakoztatható a Wio Terminalhoz.

#### Feladat - csatlakoztasd a Time of Flight érzékelőt

Csatlakoztasd a Time of Flight érzékelőt.

![Egy Grove Time of Flight érzékelő](../../../../../translated_images/hu/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Dugj be egy Grove kábelt az érzékelő csatlakozójába. A kábel csak egy irányban illeszkedik.

1. Amíg a Wio Terminal nincs csatlakoztatva a számítógéphez vagy más áramforráshoz, dugd be a Grove kábel másik végét a Wio Terminal bal oldali Grove csatlakozójába, ahogy a képernyőt nézed. Ez a csatlakozó van legközelebb a bekapcsológombhoz. Ez egy kombinált digitális és I2C csatlakozó.

![A Grove Time of Flight érzékelő csatlakoztatva a bal oldali csatlakozóhoz](../../../../../translated_images/hu/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Most csatlakoztathatod a Wio Terminalt a számítógéphez.

## Programozd a Time of Flight érzékelőt

Most már programozhatod a Wio Terminalt, hogy használja a csatlakoztatott Time of Flight érzékelőt.

### Feladat - programozd a Time of Flight érzékelőt

1. Hozz létre egy teljesen új Wio Terminal projektet a PlatformIO használatával. Nevezd el a projektet `distance-sensor`-nak. Adj hozzá kódot a `setup` függvényhez, hogy konfiguráld a soros portot.

1. Adj hozzá egy könyvtárfüggőséget a Seeed Grove Time of Flight távolságérzékelő könyvtárhoz a projekt `platformio.ini` fájljában:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. A `main.cpp` fájlban add hozzá a következőt a meglévő include direktívák alá, hogy deklarálj egy példányt a `Seeed_vl53l0x` osztályból, amely az érzékelővel való interakciót végzi:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Add hozzá a következőt a `setup` függvény aljára, hogy inicializáld az érzékelőt:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. A `loop` függvényben olvass le egy értéket az érzékelőről:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Ez a kód inicializál egy adatstruktúrát, amelybe az adatokat beolvashatod, majd átadja azt a `PerformSingleRangingMeasurement` metódusnak, amely kitölti a távolságméréssel.

1. Ezután írd ki a távolságmérést, majd várj 1 másodpercet:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Fordítsd le, töltsd fel és futtasd a kódot. A soros monitoron láthatod a távolságméréseket. Helyezz tárgyakat az érzékelő közelébe, és látni fogod a távolságmérést:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    A távolságmérő az érzékelő hátoldalán található, ezért ügyelj arra, hogy a megfelelő oldalt használd a távolság méréséhez.

    ![A Time of Flight érzékelő hátoldalán lévő távolságmérő egy banánra irányítva](../../../../../translated_images/hu/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Ezt a kódot megtalálod a [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal) mappában.

😀 A közelségérzékelő programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.