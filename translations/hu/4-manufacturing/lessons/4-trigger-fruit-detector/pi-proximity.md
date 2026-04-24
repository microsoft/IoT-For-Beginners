# Közelség érzékelése - Raspberry Pi

Ebben a leckében hozzáadunk egy közelségérzékelőt a Raspberry Pi-hez, és leolvassuk a távolságot.

## Hardver

A Raspberry Pi-hez egy közelségérzékelőre lesz szükség.

Az érzékelő, amit használni fogsz, egy [Grove Time of Flight távolságérzékelő](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Ez az érzékelő egy lézeres távolságmérő modult használ a távolság érzékelésére. Az érzékelő hatótávolsága 10 mm-től 2000 mm-ig (1 cm - 2 m) terjed, és ezen a tartományon belül meglehetősen pontos értékeket ad, 1000 mm feletti távolságokat pedig 8109 mm-ként jelent.

A lézeres távolságmérő az érzékelő hátoldalán található, a Grove csatlakozóval ellentétes oldalon.

Ez egy I²C érzékelő.

### Csatlakoztasd a Time of Flight érzékelőt

A Grove Time of Flight érzékelő csatlakoztatható a Raspberry Pi-hez.

#### Feladat - csatlakoztasd a Time of Flight érzékelőt

Csatlakoztasd a Time of Flight érzékelőt.

![Egy Grove Time of Flight érzékelő](../../../../../translated_images/hu/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Helyezd be a Grove kábel egyik végét a Time of Flight érzékelő aljzatába. Csak egyféleképpen illeszkedik.

1. Kapcsold ki a Raspberry Pi-t, majd csatlakoztasd a Grove kábel másik végét a Grove Base hat-on található egyik **I²C** aljzathoz, amely a Pi-hez van csatlakoztatva. Ezek az aljzatok az alsó sorban találhatók, a GPIO pinekkel ellentétes oldalon, a kamera kábel nyílása mellett.

![A Grove Time of Flight érzékelő csatlakoztatva az I²C aljzathoz](../../../../../translated_images/hu/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Programozd a Time of Flight érzékelőt

Most programozhatod a Raspberry Pi-t, hogy használja a csatlakoztatott Time of Flight érzékelőt.

### Feladat - programozd a Time of Flight érzékelőt

Programozd az eszközt.

1. Kapcsold be a Pi-t, és várd meg, amíg elindul.

1. Nyisd meg a `fruit-quality-detector` kódot a VS Code-ban, akár közvetlenül a Pi-n, akár a Remote SSH bővítményen keresztül csatlakozva.

1. Telepítsd az rpi-vl53l0x Pip csomagot, amely egy Python csomag a VL53L0X Time of Flight távolságérzékelővel való kommunikációhoz. Telepítsd a következő pip paranccsal:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Hozz létre egy új fájlt ebben a projektben `distance-sensor.py` néven.

    > 💁 Egy egyszerű módja annak, hogy több IoT eszközt szimulálj, ha mindegyiket külön Python fájlban hozod létre, majd egyszerre futtatod őket.

1. Add hozzá a következő kódot ehhez a fájlhoz:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Ez importálja a Grove I²C busz könyvtárat, valamint egy érzékelő könyvtárat, amely a Grove Time of Flight érzékelő alapvető hardveréhez készült.

1. Ezután add hozzá az alábbi kódot az érzékelő eléréséhez:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Ez a kód deklarál egy távolságérzékelőt a Grove I²C busz használatával, majd elindítja az érzékelőt.

1. Végül adj hozzá egy végtelen ciklust a távolságok leolvasásához:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Ez a kód megvárja, amíg egy érték készen áll az érzékelőről való leolvasásra, majd kiírja azt a konzolra.

1. Futtasd ezt a kódot.

    > 💁 Ne feledd, hogy ennek a fájlnak a neve `distance-sensor.py`! Győződj meg róla, hogy Python-nal futtatod, nem pedig az `app.py`-val.

1. A konzolon megjelennek a távolságmérések. Helyezz tárgyakat az érzékelő közelébe, és látni fogod a távolságmérést:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    A távolságmérő az érzékelő hátoldalán található, ezért ügyelj arra, hogy a megfelelő oldalt használd a távolság méréséhez.

    ![A Time of Flight érzékelő hátoldalán lévő távolságmérő egy banánra irányítva](../../../../../translated_images/hu/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Ezt a kódot megtalálod a [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi) mappában.

😀 A közelségérzékelő programod sikeresen működik!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.