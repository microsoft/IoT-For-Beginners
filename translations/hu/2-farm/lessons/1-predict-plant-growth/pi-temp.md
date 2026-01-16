<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-27T23:15:14+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "hu"
}
-->
# Hőmérséklet mérése - Raspberry Pi

A lecke ezen részében egy hőmérséklet-érzékelőt fogsz hozzáadni a Raspberry Pi-hoz.

## Hardver

Az érzékelő, amit használni fogsz, egy [DHT11 páratartalom- és hőmérséklet-érzékelő](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), amely két érzékelőt kombinál egy csomagban. Ez egy meglehetősen népszerű érzékelő, és számos kereskedelmi forgalomban kapható változata létezik, amelyek hőmérsékletet, páratartalmat és néha légnyomást is mérnek. A hőmérséklet-érzékelő komponens egy negatív hőmérsékleti együtthatójú (NTC) termisztor, amelynek ellenállása csökken, ahogy a hőmérséklet növekszik.

Ez egy digitális érzékelő, így rendelkezik egy beépített ADC-vel, amely digitális jelet hoz létre a hőmérséklet- és páratartalom-adatokkal, amelyeket a mikrokontroller olvasni tud.

### Csatlakoztasd a hőmérséklet-érzékelőt

A Grove hőmérséklet-érzékelő csatlakoztatható a Raspberry Pi-hoz.

#### Feladat

Csatlakoztasd a hőmérséklet-érzékelőt.

![Egy Grove hőmérséklet-érzékelő](../../../../../translated_images/hu/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Illeszd be a Grove kábel egyik végét a páratartalom- és hőmérséklet-érzékelő aljzatába. Csak egyféleképpen illeszkedik.

1. Kapcsold ki a Raspberry Pi-t, majd csatlakoztasd a Grove kábel másik végét a Grove Base hat-on található **D5** jelzésű digitális aljzathoz, amely a Pi-hoz van csatlakoztatva. Ez az aljzat a második balról, a GPIO tüskék melletti aljzatsoron.

![A Grove hőmérséklet-érzékelő az A0 aljzathoz csatlakoztatva](../../../../../translated_images/hu/pi-temperature-sensor.3ff82fff672c8e565ef25a39d26d111de006b825a7e0867227ef4e7fbff8553c.png)

## Programozd a hőmérséklet-érzékelőt

Most már programozhatod az eszközt, hogy használja a csatlakoztatott hőmérséklet-érzékelőt.

### Feladat

Programozd az eszközt.

1. Kapcsold be a Pi-t, és várd meg, amíg elindul.

1. Indítsd el a VS Code-ot, akár közvetlenül a Pi-n, akár a Remote SSH bővítményen keresztül csatlakozva.

    > ⚠️ Ha szükséges, hivatkozhatsz [az 1. leckében található beállítási és indítási útmutatóra](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. A terminálból hozz létre egy új mappát a `pi` felhasználó otthoni könyvtárában `temperature-sensor` néven. Hozz létre egy fájlt ebben a mappában `app.py` néven:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Nyisd meg ezt a mappát a VS Code-ban.

1. A hőmérséklet- és páratartalom-érzékelő használatához egy további Pip csomagot kell telepíteni. A VS Code termináljából futtasd az alábbi parancsot, hogy telepítsd ezt a Pip csomagot a Pi-ra:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Add hozzá a következő kódot az `app.py` fájlhoz a szükséges könyvtárak importálásához:

    ```python
    import time
    from seeed_dht import DHT
    ```

    A `from seeed_dht import DHT` utasítás importálja a `DHT` érzékelő osztályt, amely lehetővé teszi a Grove hőmérséklet-érzékelővel való interakciót a `seeed_dht` modulból.

1. Add hozzá a következő kódot az előző kód után, hogy létrehozz egy példányt az érzékelőt kezelő osztályból:

    ```python
    sensor = DHT("11", 5)
    ```

    Ez létrehoz egy példányt a `DHT` osztályból, amely a **D**igitális **H**umidity és **T**emperature érzékelőt kezeli. Az első paraméter megadja, hogy a használt érzékelő a *DHT11* típusú - a használt könyvtár más változatokat is támogat. A második paraméter megadja, hogy az érzékelő a Grove base hat `D5` digitális portjához van csatlakoztatva.

    > ✅ Ne feledd, minden aljzatnak egyedi tűszáma van. A 0, 2, 4 és 6 tűk analóg tűk, az 5, 16, 18, 22, 24 és 26 tűk digitális tűk.

1. Adj hozzá egy végtelen ciklust az előző kód után, hogy lekérdezd a hőmérséklet-érzékelő értékét, és kiírd a konzolra:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    A `sensor.read()` hívás egy páratartalom- és hőmérsékletértékeket tartalmazó tuple-t ad vissza. Csak a hőmérsékletértékre van szükséged, így a páratartalom figyelmen kívül marad. A hőmérsékletérték ezután kiírásra kerül a konzolra.

1. Adj hozzá egy rövid, tíz másodperces várakozást a ciklus végén, mivel a hőmérsékleti szinteket nem szükséges folyamatosan ellenőrizni. A várakozás csökkenti az eszköz energiafogyasztását.

    ```python
    time.sleep(10)
    ```

1. A VS Code termináljából futtasd az alábbi parancsot a Python alkalmazásod futtatásához:

    ```sh
    python3 app.py
    ```

    A konzolon hőmérsékleti értékeket kell látnod. Használj valamit az érzékelő felmelegítésére, például nyomd rá az ujjad, vagy használj egy ventilátort, hogy lásd az értékek változását:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Ezt a kódot megtalálod a [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi) mappában.

😀 A hőmérséklet-érzékelő programod sikeresen működik!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális, emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.