<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-27T23:21:31+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "hu"
}
-->
# Hőmérséklet közzététele - Virtuális IoT Hardver és Raspberry Pi

Ebben a leckében a Raspberry Pi vagy Virtuális IoT Eszköz által érzékelt hőmérsékleti értékeket fogod közzétenni MQTT-n keresztül, hogy később felhasználhatók legyenek a GDD kiszámításához.

## Hőmérséklet közzététele

Miután a hőmérsékletet kiolvastad, közzéteheted MQTT-n keresztül egy 'szerver' kód számára, amely elolvassa az értékeket és eltárolja őket, hogy később felhasználhatók legyenek a GDD számításához.

### Feladat - hőmérséklet közzététele

Programozd az eszközt, hogy közzétegye a hőmérsékleti adatokat.

1. Nyisd meg a `temperature-sensor` alkalmazás projektet, ha még nincs megnyitva.

1. Ismételd meg azokat a lépéseket, amelyeket a 4. leckében végeztél az MQTT-hez való csatlakozáshoz és a telemetria küldéséhez. Ugyanazt a nyilvános Mosquitto brókert fogod használni.

    A lépések a következők:

    - Add hozzá az MQTT pip csomagot
    - Add hozzá a kódot az MQTT brókerhez való csatlakozáshoz
    - Add hozzá a kódot a telemetria közzétételéhez

    > ⚠️ Tekintsd meg az [MQTT-hez való csatlakozásra vonatkozó utasításokat](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) és a [telemetria küldésére vonatkozó utasításokat](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) a 4. leckéből, ha szükséges.

1. Győződj meg róla, hogy a `client_name` tükrözi ennek a projektnek a nevét:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. A telemetria esetében a fényérték helyett a DHT szenzorból kiolvasott hőmérsékleti értéket küldd el egy `temperature` nevű tulajdonságban a JSON dokumentumban:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. A hőmérsékleti értéket nem szükséges gyakran kiolvasni - rövid idő alatt nem változik jelentősen, ezért állítsd a `time.sleep` értékét 10 percre:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 A `sleep` függvény másodpercekben veszi az időt, ezért az érték könnyebb olvashatósága érdekében egy számítás eredményeként van megadva. 60 másodperc egy percben, tehát 10 x (60 másodperc egy percben) 10 perces késleltetést ad.

1. Futtasd a kódot ugyanúgy, ahogy a feladat előző részében futtattad. Ha virtuális IoT eszközt használsz, győződj meg róla, hogy a CounterFit alkalmazás fut, és a páratartalom- és hőmérsékletérzékelők a megfelelő lábakon lettek létrehozva.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Ezt a kódot megtalálod a [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) mappában vagy a [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi) mappában.

😀 Sikeresen közzétetted a hőmérsékletet telemetria formájában az eszközödről.

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.