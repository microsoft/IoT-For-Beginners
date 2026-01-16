<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-27T22:33:19+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "hu"
}
-->
# Építs egy éjszakai fényt - Virtuális IoT Hardver

A lecke ezen részében egy fényérzékelőt fogsz hozzáadni a virtuális IoT eszközödhöz.

## Virtuális Hardver

Az éjszakai fényhez egy érzékelőre van szükség, amelyet a CounterFit alkalmazásban hozunk létre.

Az érzékelő egy **fényérzékelő**. Egy fizikai IoT eszközben ez egy [fotodióda](https://wikipedia.org/wiki/Photodiode) lenne, amely a fényt elektromos jellé alakítja. A fényérzékelők analóg érzékelők, amelyek egy egész számot küldenek, jelezve a relatív fényerősséget. Ez az érték nem felel meg semmilyen szabványos mértékegységnek, például a [lux](https://wikipedia.org/wiki/Lux) mértékegységnek.

### Érzékelők hozzáadása a CounterFit-hez

Ahhoz, hogy egy virtuális fényérzékelőt használhass, hozzá kell adnod azt a CounterFit alkalmazáshoz.

#### Feladat - érzékelők hozzáadása a CounterFit-hez

Add hozzá a fényérzékelőt a CounterFit alkalmazáshoz.

1. Győződj meg róla, hogy a CounterFit webalkalmazás fut az előző feladatból. Ha nem, indítsd el.

1. Hozz létre egy fényérzékelőt:

    1. A *Create sensor* mezőben, a *Sensors* panelen, nyisd le a *Sensor type* mezőt, és válaszd a *Light* lehetőséget.

    1. Hagyd a *Units* mezőt *NoUnits* értéken.

    1. Győződj meg róla, hogy a *Pin* értéke *0*.

    1. Kattints az **Add** gombra, hogy létrehozd a fényérzékelőt a 0-s tűn.

    ![A fényérzékelő beállításai](../../../../../translated_images/hu/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    A fényérzékelő létrejön, és megjelenik az érzékelők listájában.

    ![A létrehozott fényérzékelő](../../../../../translated_images/hu/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## A fényérzékelő programozása

Most már programozhatod az eszközt, hogy használja a beépített fényérzékelőt.

### Feladat - a fényérzékelő programozása

Programozd az eszközt.

1. Nyisd meg a VS Code-ban az éjszakai fény projektet, amelyet az előző feladatban hoztál létre. Ha szükséges, állítsd le és hozd létre újra a terminált, hogy az a virtuális környezetet használja.

1. Nyisd meg az `app.py` fájlt.

1. Add hozzá a következő kódot az `app.py` fájl tetejére az `import` utasítások közé, hogy importáld a szükséges könyvtárakat:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Az `import time` utasítás importálja a Python `time` modulját, amelyet később használni fogsz ebben a feladatban.

    A `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` utasítás importálja a `GroveLightSensor` osztályt a CounterFit Grove shim Python könyvtárakból. Ez a könyvtár tartalmazza a kódot, amely a CounterFit alkalmazásban létrehozott fényérzékelővel való interakcióhoz szükséges.

1. Add hozzá a következő kódot a fájl aljára, hogy létrehozd az osztályok példányait, amelyek a fényérzékelőt kezelik:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    A `light_sensor = GroveLightSensor(0)` sor létrehoz egy példányt a `GroveLightSensor` osztályból, amely a **0**-s tűhöz csatlakozik - ez az a CounterFit Grove tű, amelyhez a fényérzékelő csatlakozik.

1. Adj hozzá egy végtelen ciklust a fenti kód után, hogy lekérdezd a fényérzékelő értékét, és kiírd a konzolra:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Ez a kód a `GroveLightSensor` osztály `light` tulajdonságát használja, hogy leolvassa az aktuális fényerősséget. Ez a tulajdonság az analóg értéket olvassa ki a tűről. Az értéket ezután kiírja a konzolra.

1. Adj hozzá egy rövid, egy másodperces szünetet a `while` ciklus végére, mivel a fényerősséget nem szükséges folyamatosan ellenőrizni. A szünet csökkenti az eszköz energiafogyasztását.

    ```python
    time.sleep(1)
    ```

1. A VS Code termináljában futtasd a következő parancsot, hogy elindítsd a Python alkalmazásodat:

    ```sh
    python3 app.py
    ```

    A fényértékek megjelennek a konzolon. Kezdetben ez az érték 0 lesz.

1. A CounterFit alkalmazásban változtasd meg a fényérzékelő értékét, amelyet az alkalmazás le fog olvasni. Ezt kétféleképpen teheted meg:

    * Írj be egy számot a fényérzékelő *Value* mezőjébe, majd kattints a **Set** gombra. Az általad megadott szám lesz az érzékelő által visszaadott érték.

    * Jelöld be a *Random* jelölőnégyzetet, és adj meg egy *Min* és *Max* értéket, majd kattints a **Set** gombra. Minden alkalommal, amikor az érzékelő értéket olvas, egy véletlenszerű számot fog visszaadni a *Min* és *Max* értékek között.

    Az általad beállított értékek megjelennek a konzolon. Változtasd a *Value* vagy a *Random* beállításokat, hogy az érték változzon.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Ezt a kódot megtalálod a [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device) mappában.

😀 Az éjszakai fény programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális, emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.