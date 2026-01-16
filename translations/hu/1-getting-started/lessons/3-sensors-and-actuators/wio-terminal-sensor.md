<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-27T22:34:27+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "hu"
}
-->
# Érzékelő hozzáadása - Wio Terminal

Ebben a leckében a Wio Terminal fényérzékelőjét fogod használni.

## Hardver

A lecke során használt érzékelő egy **fényérzékelő**, amely egy [fotodiódát](https://wikipedia.org/wiki/Photodiode) használ arra, hogy a fényt elektromos jellé alakítsa. Ez egy analóg érzékelő, amely 0 és 1 023 közötti egész számot küld, jelezve a fény relatív mennyiségét. Ez az érték nem felel meg semmilyen szabványos mértékegységnek, például a [luxnak](https://wikipedia.org/wiki/Lux).

A fényérzékelő be van építve a Wio Terminalba, és a hátoldalon található átlátszó műanyag ablakon keresztül látható.

![A Wio Terminal hátoldalán található fényérzékelő](../../../../../translated_images/hu/wio-light-sensor.b1f529f3c95f5165.png)

## A fényérzékelő programozása

Az eszközt most be lehet programozni a beépített fényérzékelő használatára.

### Feladat

Programozd be az eszközt.

1. Nyisd meg a nightlight projektet a VS Code-ban, amelyet a feladat előző részében hoztál létre.

1. Add hozzá a következő sort a `setup` függvény végéhez:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Ez a sor konfigurálja azokat a pineket, amelyeket az érzékelő hardverrel való kommunikációhoz használnak.

    A `WIO_LIGHT` pin a beépített fényérzékelőhöz csatlakoztatott GPIO pin száma. Ez a pin `INPUT` értékre van állítva, ami azt jelenti, hogy egy érzékelőhöz csatlakozik, és adatokat fog olvasni a pinről.

1. Töröld a `loop` függvény tartalmát.

1. Add hozzá a következő kódot az immár üres `loop` függvényhez.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Ez a kód egy analóg értéket olvas be a `WIO_LIGHT` pinről. Ez a beépített fényérzékelőtől egy 0 és 1 023 közötti értéket olvas be. Ezután az értéket a soros porton keresztül továbbítja, így a Serial Monitorban olvashatod, amikor ez a kód fut. A `Serial.print` a szöveget új sor nélkül írja ki, így minden sor `Light value:` szöveggel kezdődik, és a tényleges fényértékkel végződik.

1. Adj hozzá egy rövid, egy másodperces (1 000 ms) késleltetést a `loop` végéhez, mivel a fényerősséget nem szükséges folyamatosan ellenőrizni. A késleltetés csökkenti az eszköz energiafogyasztását.

    ```cpp
    delay(1000);
    ```

1. Csatlakoztasd újra a Wio Terminalt a számítógépedhez, és töltsd fel az új kódot, ahogy korábban is tetted.

1. Kapcsold be a Serial Monitort. A fényértékek megjelennek a terminálon. Takarj le vagy fedj fel a Wio Terminal hátoldalán található fényérzékelőt, és az értékek változni fognak.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 Ezt a kódot megtalálod a [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal) mappában.

😀 Sikeresen hozzáadtál egy érzékelőt a nightlight programodhoz!

---

**Felelősségkizárás**:  
Ez a dokumentum az [Co-op Translator](https://github.com/Azure/co-op-translator) AI fordítási szolgáltatás segítségével készült. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt a professzionális, emberi fordítás igénybevétele. Nem vállalunk felelősséget a fordítás használatából eredő félreértésekért vagy téves értelmezésekért.