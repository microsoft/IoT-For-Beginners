<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T23:20:20+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "hu"
}
-->
# Hőmérséklet közzététele - Wio Terminal

Ebben a leckében a Wio Terminal által érzékelt hőmérsékleti értékeket fogod közzétenni MQTT-n keresztül, hogy később felhasználhatók legyenek a GDD kiszámításához.

## A hőmérséklet közzététele

Miután a hőmérsékletet leolvastad, közzéteheted MQTT-n keresztül egy olyan 'szerver' kód számára, amely elolvassa az értékeket, és eltárolja őket, hogy készen álljanak a GDD számításra. A mikrokontrollerek alapértelmezetten nem olvassák az időt az internetről, és nem követik az időt valós idejű órával, hacsak a készülék nincs erre programozva, és rendelkezik a szükséges hardverrel.

A dolgok egyszerűsítése érdekében ebben a leckében az időt nem küldjük el az érzékelő adataival, hanem a szerver kódja adhatja hozzá később, amikor megkapja az üzeneteket.

### Feladat

Programozd be az eszközt, hogy közzétegye a hőmérsékleti adatokat.

1. Nyisd meg a `temperature-sensor` Wio Terminal projektet.

1. Ismételd meg azokat a lépéseket, amelyeket a 4. leckében végeztél az MQTT-hez való csatlakozáshoz és a telemetria küldéséhez. Ugyanazt a nyilvános Mosquitto brokert fogod használni.

    A lépések a következők:

    - Add hozzá a Seeed WiFi és MQTT könyvtárakat a `.ini` fájlhoz
    - Add hozzá a konfigurációs fájlt és a WiFi-hez való csatlakozáshoz szükséges kódot
    - Add hozzá az MQTT brokerhez való csatlakozáshoz szükséges kódot
    - Add hozzá a telemetria közzétételéhez szükséges kódot

    > ⚠️ Hivatkozz az [MQTT-hez való csatlakozásra vonatkozó utasításokra](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) és a [telemetria küldésére vonatkozó utasításokra](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) a 4. leckéből, ha szükséges.

1. Győződj meg róla, hogy a `CLIENT_NAME` a `config.h` fejlécfájlban tükrözi ezt a projektet:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. A telemetria esetében a fényérték helyett küldd el a DHT érzékelő által leolvasott hőmérsékleti értéket egy `temperature` nevű tulajdonságként a JSON dokumentumban, a `main.cpp` fájl `loop` függvényének módosításával:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. A hőmérsékleti értéket nem szükséges túl gyakran leolvasni - rövid idő alatt nem változik sokat, ezért állítsd a `loop` függvényben a `delay` értékét 10 percre:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 A `delay` függvény az időt milliszekundumban veszi, ezért az érték könnyebb olvashatósága érdekében egy számítás eredményeként adjuk meg. 1 000 ms egy másodperc, 60 s egy perc, tehát 10 x (60 s egy percben) x (1 000 ms egy másodpercben) 10 perces késleltetést ad.

1. Töltsd fel ezt a Wio Terminalodra, és használd a soros monitort, hogy lásd, ahogy a hőmérsékletet elküldik az MQTT brokernek.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Ezt a kódot megtalálod a [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) mappában.

😀 Sikeresen közzétetted a hőmérsékletet telemetriaként az eszközödről.

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.