# Építs egy éjszakai fényt - Raspberry Pi

Ebben a leckében egy fényérzékelőt fogsz hozzáadni a Raspberry Pi-hez.

## Hardver

A szenzor ebben a leckében egy **fényérzékelő**, amely egy [fotodiódát](https://wikipedia.org/wiki/Photodiode) használ arra, hogy a fényt elektromos jellé alakítsa. Ez egy analóg szenzor, amely 0 és 1,000 közötti egész számot küld, jelezve a fény relatív mennyiségét, amely nem felel meg semmilyen szabványos mértékegységnek, például [lux](https://wikipedia.org/wiki/Lux).

A fényérzékelő egy külső Grove szenzor, amelyet a Raspberry Pi-hez csatlakoztatott Grove Base hat-hoz kell csatlakoztatni.

### Csatlakoztasd a fényérzékelőt

A Grove fényérzékelőt, amelyet a fény szintjeinek érzékelésére használnak, csatlakoztatni kell a Raspberry Pi-hez.

#### Feladat - csatlakoztasd a fényérzékelőt

Csatlakoztasd a fényérzékelőt.

![Egy Grove fényérzékelő](../../../../../translated_images/hu/grove-light-sensor.b8127b7c434e632d.webp)

1. Helyezd be a Grove kábel egyik végét a fényérzékelő modul aljzatába. Csak egy irányban illeszkedik.

1. Kapcsold ki a Raspberry Pi-t, majd csatlakoztasd a Grove kábel másik végét a Grove Base hat analóg aljzatába, amelyet **A0** jelöléssel látsz. Ez az aljzat a második a jobb oldalon, a GPIO pin-ek melletti aljzatsoron.

![A Grove fényérzékelő az A0 aljzathoz csatlakoztatva](../../../../../translated_images/hu/pi-light-sensor.66cc1e31fa48cd7d.webp)

## Programozd a fényérzékelőt

Most már programozhatod az eszközt a Grove fényérzékelő segítségével.

### Feladat - programozd a fényérzékelőt

Programozd az eszközt.

1. Kapcsold be a Pi-t, és várd meg, amíg elindul.

1. Nyisd meg a VS Code-ban az éjszakai fény projektet, amelyet a feladat előző részében hoztál létre, akár közvetlenül a Pi-n futtatva, akár a Remote SSH bővítmény segítségével csatlakozva.

1. Nyisd meg az `app.py` fájlt, és töröld ki belőle az összes kódot.

1. Add hozzá a következő kódot az `app.py` fájlhoz, hogy importáld a szükséges könyvtárakat:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Az `import time` utasítás importálja a `time` modult, amelyet később fogsz használni ebben a feladatban.

    A `from grove.grove_light_sensor_v1_2 import GroveLightSensor` utasítás importálja a `GroveLightSensor`-t a Grove Python könyvtárakból. Ez a könyvtár tartalmazza a Grove fényérzékelővel való interakcióhoz szükséges kódot, és globálisan telepítve lett a Pi beállítása során.

1. Add hozzá a következő kódot az előző kód után, hogy létrehozz egy példányt a fényérzékelőt kezelő osztályból:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    A `light_sensor = GroveLightSensor(0)` sor létrehoz egy példányt a `GroveLightSensor` osztályból, amely az **A0** pinhez csatlakozik - az analóg Grove pinhez, amelyhez a fényérzékelő csatlakozik.

1. Adj hozzá egy végtelen ciklust az előző kód után, hogy lekérdezd a fényérzékelő értékét, és kiírd a konzolra:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Ez a kód a `GroveLightSensor` osztály `light` tulajdonságát használja, hogy leolvassa az aktuális fényértéket 0-1,023 skálán. Ez a tulajdonság az analóg értéket olvassa le a pinről. Az érték ezután kiírásra kerül a konzolra.

1. Adj hozzá egy rövid, egy másodperces szünetet a `loop` végéhez, mivel a fényértékeket nem szükséges folyamatosan ellenőrizni. A szünet csökkenti az eszköz energiafogyasztását.

    ```python
    time.sleep(1)
    ```

1. A VS Code termináljában futtasd a következő parancsot, hogy elindítsd a Python alkalmazásodat:

    ```sh
    python3 app.py
    ```

    A fényértékek kiírásra kerülnek a konzolra. Takard le, majd fedd fel a fényérzékelőt, és az értékek változni fognak:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Ezt a kódot megtalálod a [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi) mappában.

😀 Sikeresen hozzáadtál egy érzékelőt az éjszakai fény programodhoz!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.