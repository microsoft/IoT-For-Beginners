<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-27T22:54:08+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "hu"
}
-->
# Talajnedvesség mérése - Virtuális IoT Hardver

Ebben a leckében hozzáad egy kapacitív talajnedvesség-érzékelőt a virtuális IoT eszközéhez, és értékeket olvas le róla.

## Virtuális Hardver

A virtuális IoT eszköz egy szimulált Grove kapacitív talajnedvesség-érzékelőt fog használni. Ez a labor ugyanúgy működik, mintha egy Raspberry Pi-t használnánk egy fizikai Grove kapacitív talajnedvesség-érzékelővel.

Egy fizikai IoT eszközben a talajnedvesség-érzékelő egy kapacitív érzékelő lenne, amely a talaj nedvességtartalmát méri a talaj kapacitásának érzékelésével, amely tulajdonság változik a talaj nedvességtartalmának változásával. Ahogy a talaj nedvességtartalma nő, a feszültség csökken.

Ez egy analóg érzékelő, amely egy szimulált 10 bites ADC-t használ, hogy 1-1,023 közötti értéket adjon vissza.

### Talajnedvesség-érzékelő hozzáadása a CounterFithez

Ahhoz, hogy virtuális talajnedvesség-érzékelőt használjon, hozzá kell adnia azt a CounterFit alkalmazáshoz.

#### Feladat - Talajnedvesség-érzékelő hozzáadása a CounterFithez

Adja hozzá a talajnedvesség-érzékelőt a CounterFit alkalmazáshoz.

1. Hozzon létre egy új Python alkalmazást a számítógépén egy `soil-moisture-sensor` nevű mappában, amely egyetlen `app.py` fájlt és egy Python virtuális környezetet tartalmaz, majd adja hozzá a CounterFit pip csomagokat.

    > ⚠️ Ha szükséges, hivatkozhat [az első leckében található CounterFit Python projekt létrehozására és beállítására vonatkozó utasításokra](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Győződjön meg arról, hogy a CounterFit webalkalmazás fut.

1. Hozzon létre egy talajnedvesség-érzékelőt:

    1. A *Create sensor* mezőben, a *Sensors* panelen, nyissa le a *Sensor type* mezőt, és válassza ki a *Soil Moisture* opciót.

    1. Hagyja a *Units* beállítást *NoUnits* értéken.

    1. Győződjön meg arról, hogy a *Pin* értéke *0*.

    1. Válassza ki az **Add** gombot, hogy létrehozza a *Soil Moisture* érzékelőt a 0-s csatlakozón.

    ![A talajnedvesség-érzékelő beállításai](../../../../../translated_images/hu/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    A talajnedvesség-érzékelő létrejön, és megjelenik az érzékelők listájában.

    ![A létrehozott talajnedvesség-érzékelő](../../../../../translated_images/hu/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## Talajnedvesség-érzékelő alkalmazás programozása

Most már programozhatja a talajnedvesség-érzékelő alkalmazást a CounterFit érzékelők használatával.

### Feladat - Talajnedvesség-érzékelő alkalmazás programozása

Programozza a talajnedvesség-érzékelő alkalmazást.

1. Győződjön meg arról, hogy a `soil-moisture-sensor` alkalmazás meg van nyitva a VS Code-ban.

1. Nyissa meg az `app.py` fájlt.

1. Adja hozzá a következő kódot az `app.py` fájl tetejére, hogy csatlakoztassa az alkalmazást a CounterFithez:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Adja hozzá a következő kódot az `app.py` fájlhoz, hogy importálja a szükséges könyvtárakat:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    Az `import time` utasítás importálja a `time` modult, amelyet később használni fogunk ebben a feladatban.

    A `from counterfit_shims_grove.adc import ADC` utasítás importálja az `ADC` osztályt, amely lehetővé teszi a szimulált analóg-digitális átalakítóval való interakciót, amely csatlakozhat egy CounterFit érzékelőhöz.

1. Adja hozzá a következő kódot az alá, hogy létrehozzon egy példányt az `ADC` osztályból:

    ```python
    adc = ADC()
    ```

1. Hozzon létre egy végtelen ciklust, amely olvas az ADC-ről a 0-s csatlakozón, és kiírja az eredményt a konzolra. Ez a ciklus 10 másodpercet várhat az olvasások között.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. A CounterFit alkalmazásban változtassa meg a talajnedvesség-érzékelő értékét, amelyet az alkalmazás olvasni fog. Ezt kétféleképpen teheti meg:

    * Írjon be egy számot a talajnedvesség-érzékelő *Value* mezőjébe, majd válassza ki a **Set** gombot. Az Ön által megadott szám lesz az érzékelő által visszaadott érték.

    * Jelölje be a *Random* jelölőnégyzetet, és adjon meg egy *Min* és *Max* értéket, majd válassza ki a **Set** gombot. Minden alkalommal, amikor az érzékelő értéket olvas, egy *Min* és *Max* közötti véletlenszámot fog olvasni.

1. Futtassa a Python alkalmazást. Látni fogja a talajnedvesség-méréseket a konzolon. Változtassa meg a *Value* vagy a *Random* beállításokat, hogy lássa az értékek változását.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Ezt a kódot megtalálja a [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device) mappában.

😀 A talajnedvesség-érzékelő programja sikeresen működött!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.