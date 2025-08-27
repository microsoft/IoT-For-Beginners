<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-27T22:12:58+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "hu"
}
-->
# Vezéreld az éjszakai fényedet az interneten keresztül - Virtuális IoT eszköz és Raspberry Pi

A lecke ezen részében telemetriát fogsz küldeni a fényerősségi szintekről a Raspberry Pi vagy virtuális IoT eszközödről egy MQTT brokerhez.

## Telemetria küldése

A következő lépés egy JSON dokumentum létrehozása telemetriával, majd annak elküldése az MQTT brokerhez.

### Feladat

Telemetria küldése az MQTT brokerhez.

1. Nyisd meg az éjszakai fény projektet a VS Code-ban.

1. Ha virtuális IoT eszközt használsz, győződj meg róla, hogy a terminálban a virtuális környezet fut. Ha Raspberry Pi-t használsz, akkor nem fogsz virtuális környezetet használni.

1. Add hozzá a következő importot az `app.py` fájl tetejéhez:

    ```python
    import json
    ```

    A `json` könyvtárat arra használjuk, hogy a telemetriát JSON dokumentummá kódoljuk.

1. Add hozzá a következőt a `client_name` deklaráció után:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    A `client_telemetry_topic` az az MQTT téma, amelyre az eszköz a fényerősségi szinteket fogja publikálni.

1. Cseréld le a fájl végén található `while True:` ciklus tartalmát a következőre:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Ez a kód becsomagolja a fényerősségi szintet egy JSON dokumentumba, majd elküldi az MQTT brokerhez. Ezután szünetet tart, hogy csökkentse az üzenetek küldésének gyakoriságát.

1. Futtasd a kódot ugyanúgy, ahogy a feladat előző részében futtattad. Ha virtuális IoT eszközt használsz, győződj meg róla, hogy a CounterFit alkalmazás fut, és a fényérzékelő és LED a megfelelő lábakon lett létrehozva.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Ezt a kódot megtalálhatod a [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) mappában vagy a [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) mappában.

😀 Sikeresen küldtél telemetriát az eszközödről.

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.