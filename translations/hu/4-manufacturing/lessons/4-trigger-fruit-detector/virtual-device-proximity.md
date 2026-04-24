# Közelség érzékelése - Virtuális IoT Hardver

Ebben a leckében hozzáadunk egy közelségérzékelőt a virtuális IoT eszközhöz, és leolvassuk a távolságot.

## Hardver

A virtuális IoT eszköz egy szimulált távolságérzékelőt fog használni.

Egy fizikai IoT eszköz esetében egy lézeres távolságmérő modullal rendelkező érzékelőt használnánk a távolság érzékelésére.

### Távolságérzékelő hozzáadása a CounterFithez

Ahhoz, hogy virtuális távolságérzékelőt használjunk, hozzá kell adnunk egyet a CounterFit alkalmazáshoz.

#### Feladat - távolságérzékelő hozzáadása a CounterFithez

Adja hozzá a távolságérzékelőt a CounterFit alkalmazáshoz.

1. Nyissa meg a `fruit-quality-detector` kódot a VS Code-ban, és győződjön meg róla, hogy a virtuális környezet aktiválva van.

1. Telepítsen egy további Pip csomagot, amely egy CounterFit shim-et telepít, amely képes kommunikálni a távolságérzékelőkkel a [rpi-vl53l0x Pip csomag](https://pypi.org/project/rpi-vl53l0x/) szimulálásával. Ez egy Python csomag, amely a [VL53L0X idő-alapú távolságérzékelővel](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/) működik együtt. Győződjön meg róla, hogy ezt egy olyan terminálból telepíti, amelyben a virtuális környezet aktiválva van.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Győződjön meg róla, hogy a CounterFit webalkalmazás fut.

1. Hozzon létre egy távolságérzékelőt:

    1. A *Create sensor* mezőben a *Sensors* panelen nyissa meg a *Sensor type* legördülő menüt, és válassza a *Distance* lehetőséget.

    1. Hagyja az *Units* mezőt `Millimeter` értéken.

    1. Ez az érzékelő egy I²C érzékelő, ezért állítsa a címet `0x29` értékre. Ha fizikai VL53L0X érzékelőt használna, az erre a címre lenne kódolva.

    1. Válassza ki az **Add** gombot a távolságérzékelő létrehozásához.

    ![A távolságérzékelő beállításai](../../../../../translated_images/hu/counterfit-create-distance-sensor.967c9fb98f27888d.webp)

    A távolságérzékelő létrejön, és megjelenik az érzékelők listájában.

    ![A létrehozott távolságérzékelő](../../../../../translated_images/hu/counterfit-distance-sensor.079eefeeea0b68af.webp)

## Távolságérzékelő programozása

A virtuális IoT eszköz most már programozható a szimulált távolságérzékelő használatára.

### Feladat - idő-alapú érzékelő programozása

1. Hozzon létre egy új fájlt a `fruit-quality-detector` projektben `distance-sensor.py` néven.

    > 💁 Az IoT eszközök szimulálásának egyszerű módja, ha mindegyiket külön Python fájlban készítjük el, majd egyszerre futtatjuk őket.

1. Indítson el egy kapcsolatot a CounterFithez az alábbi kóddal:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Adja hozzá az alábbi kódot ehhez:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Ez importálja az érzékelő könyvtár shim-jét a VL53L0X idő-alapú érzékelőhöz.

1. Ezután adja hozzá az alábbi kódot az érzékelő eléréséhez:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Ez a kód deklarál egy távolságérzékelőt, majd elindítja az érzékelőt.

1. Végül adjon hozzá egy végtelen ciklust a távolságok leolvasásához:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Ez a kód megvárja, hogy egy érték készen álljon az érzékelőből való olvasásra, majd kiírja azt a konzolra.

1. Futtassa ezt a kódot.

    > 💁 Ne feledje, hogy ennek a fájlnak a neve `distance-sensor.py`! Győződjön meg róla, hogy ezt Pythonon keresztül futtatja, nem pedig az `app.py` fájlon keresztül.

1. A konzolon megjelennek a távolságmérések. Módosítsa az értéket a CounterFitben, hogy lássa, hogyan változik az érték, vagy használjon véletlenszerű értékeket.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Ezt a kódot megtalálja a [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device) mappában.

😀 Sikeresen programozta a közelségérzékelőt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget az ebből a fordításból eredő félreértésekért vagy téves értelmezésekért.