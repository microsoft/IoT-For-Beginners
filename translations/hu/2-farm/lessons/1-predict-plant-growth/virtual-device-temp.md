# Hőmérséklet mérése - Virtuális IoT Hardver

Ebben a leckében egy hőmérséklet-érzékelőt fogsz hozzáadni a virtuális IoT eszközödhöz.

## Virtuális Hardver

A virtuális IoT eszköz egy szimulált Grove Digital Humidity and Temperature érzékelőt fog használni. Ez a labor ugyanúgy működik, mintha egy Raspberry Pi-t használnál egy fizikai Grove DHT11 érzékelővel.

Az érzékelő egy **hőmérséklet-érzékelőt** és egy **páratartalom-érzékelőt** kombinál, de ebben a laborban csak a hőmérséklet-érzékelő komponens érdekes. Egy fizikai IoT eszközben a hőmérséklet-érzékelő egy [termisztor](https://wikipedia.org/wiki/Thermistor) lenne, amely az ellenállás változását érzékeli a hőmérséklet változásával. A hőmérséklet-érzékelők általában digitális érzékelők, amelyek belsőleg átalakítják a mért ellenállást hőmérsékletté Celsius-fokban (vagy Kelvinben, vagy Fahrenheitben).

### Érzékelők hozzáadása a CounterFit-hez

Ahhoz, hogy egy virtuális páratartalom- és hőmérséklet-érzékelőt használj, hozzá kell adnod a két érzékelőt a CounterFit alkalmazáshoz.

#### Feladat - érzékelők hozzáadása a CounterFit-hez

Add hozzá a páratartalom- és hőmérséklet-érzékelőket a CounterFit alkalmazáshoz.

1. Hozz létre egy új Python alkalmazást a számítógépeden egy `temperature-sensor` nevű mappában, amely egyetlen `app.py` fájlt tartalmaz, valamint egy Python virtuális környezetet, és add hozzá a CounterFit pip csomagokat.

    > ⚠️ Ha szükséges, hivatkozhatsz [az 1. leckében található utasításokra a CounterFit Python projekt létrehozásához és beállításához](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Telepíts egy további Pip csomagot, amely a DHT11 érzékelőhöz való CounterFit shim-et tartalmazza. Győződj meg róla, hogy ezt egy aktivált virtuális környezettel rendelkező terminálból telepíted.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Győződj meg róla, hogy a CounterFit webalkalmazás fut.

1. Hozz létre egy páratartalom-érzékelőt:

    1. A *Create sensor* mezőben a *Sensors* panelen nyisd le a *Sensor type* mezőt, és válaszd ki a *Humidity* opciót.

    1. Hagyd a *Units* mezőt *Percentage* értéken.

    1. Győződj meg róla, hogy a *Pin* mező *5*-re van állítva.

    1. Válaszd ki az **Add** gombot, hogy létrehozd a páratartalom-érzékelőt az 5-ös lábon.

    ![A páratartalom-érzékelő beállításai](../../../../../translated_images/hu/counterfit-create-humidity-sensor.2750e27b6f30e09c.webp)

    A páratartalom-érzékelő létrejön, és megjelenik az érzékelők listájában.

    ![A páratartalom-érzékelő létrehozva](../../../../../translated_images/hu/counterfit-humidity-sensor.7b12f7f339e430cb.webp)

1. Hozz létre egy hőmérséklet-érzékelőt:

    1. A *Create sensor* mezőben a *Sensors* panelen nyisd le a *Sensor type* mezőt, és válaszd ki a *Temperature* opciót.

    1. Hagyd a *Units* mezőt *Celsius* értéken.

    1. Győződj meg róla, hogy a *Pin* mező *6*-ra van állítva.

    1. Válaszd ki az **Add** gombot, hogy létrehozd a hőmérséklet-érzékelőt a 6-os lábon.

    ![A hőmérséklet-érzékelő beállításai](../../../../../translated_images/hu/counterfit-create-temperature-sensor.199350ed34f7343d.webp)

    A hőmérséklet-érzékelő létrejön, és megjelenik az érzékelők listájában.

    ![A hőmérséklet-érzékelő létrehozva](../../../../../translated_images/hu/counterfit-temperature-sensor.f0560236c96a9016.webp)

## A hőmérséklet-érzékelő alkalmazás programozása

Most már programozhatod a hőmérséklet-érzékelő alkalmazást a CounterFit érzékelők használatával.

### Feladat - a hőmérséklet-érzékelő alkalmazás programozása

Programozd a hőmérséklet-érzékelő alkalmazást.

1. Győződj meg róla, hogy a `temperature-sensor` alkalmazás meg van nyitva a VS Code-ban.

1. Nyisd meg az `app.py` fájlt.

1. Add hozzá a következő kódot az `app.py` tetejéhez, hogy az alkalmazás csatlakozzon a CounterFit-hez:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Add hozzá a következő kódot az `app.py` fájlhoz a szükséges könyvtárak importálásához:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    A `from seeed_dht import DHT` utasítás importálja a `DHT` érzékelő osztályt, amely lehetővé teszi a virtuális Grove hőmérséklet-érzékelővel való interakciót a `counterfit_shims_seeed_python_dht` modul shim-jén keresztül.

1. Add hozzá a következő kódot a fentiek után, hogy létrehozz egy példányt az osztályból, amely kezeli a virtuális páratartalom- és hőmérséklet-érzékelőt:

    ```python
    sensor = DHT("11", 5)
    ```

    Ez deklarál egy példányt a `DHT` osztályból, amely kezeli a virtuális **D**igitális **H**umidity és **T**emperature érzékelőt. Az első paraméter megadja, hogy a használt érzékelő egy virtuális *DHT11* érzékelő. A második paraméter megadja, hogy az érzékelő az `5`-ös porthoz van csatlakoztatva.

    > 💁 A CounterFit ezt a kombinált páratartalom- és hőmérséklet-érzékelőt úgy szimulálja, hogy két érzékelőhöz csatlakozik: egy páratartalom-érzékelőhöz az osztály létrehozásakor megadott lábon, és egy hőmérséklet-érzékelőhöz, amely a következő lábon fut. Ha a páratartalom-érzékelő az 5-ös lábon van, a shim a hőmérséklet-érzékelőt a 6-os lábon várja.

1. Adj hozzá egy végtelen ciklust a fenti kód után, hogy lekérdezd a hőmérséklet-érzékelő értékét, és kiírd a konzolra:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    A `sensor.read()` hívás egy tuple-t ad vissza, amely tartalmazza a páratartalom- és hőmérséklet-értékeket. Csak a hőmérséklet-értékre van szükséged, így a páratartalom értéket figyelmen kívül hagyhatod. A hőmérséklet-értéket ezután kiírod a konzolra.

1. Adj hozzá egy rövid, tíz másodperces szünetet a ciklus végén, mivel a hőmérséklet-értékeket nem szükséges folyamatosan ellenőrizni. Egy szünet csökkenti az eszköz energiafogyasztását.

    ```python
    time.sleep(10)
    ```

1. A VS Code termináljában, egy aktivált virtuális környezettel, futtasd a következőt a Python alkalmazás futtatásához:

    ```sh
    python app.py
    ```

1. A CounterFit alkalmazásban változtasd meg a hőmérséklet-érzékelő értékét, amelyet az alkalmazás olvasni fog. Ezt kétféleképpen teheted meg:

    * Írj be egy számot a hőmérséklet-érzékelő *Value* mezőjébe, majd válaszd ki a **Set** gombot. Az általad megadott szám lesz az érzékelő által visszaadott érték.

    * Jelöld be a *Random* jelölőnégyzetet, és adj meg egy *Min* és *Max* értéket, majd válaszd ki a **Set** gombot. Minden alkalommal, amikor az érzékelő értéket olvas, egy véletlenszerű számot fog olvasni a *Min* és *Max* értékek között.

    A konzolon meg kell jelennie az általad beállított értékeknek. Módosítsd a *Value* vagy a *Random* beállításokat, hogy lásd az értékek változását.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Ezt a kódot megtalálod a [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device) mappában.

😀 A hőmérséklet-érzékelő programod sikeresen működik!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.