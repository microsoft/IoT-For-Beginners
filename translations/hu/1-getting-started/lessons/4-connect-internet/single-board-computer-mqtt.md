<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-27T22:14:36+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "hu"
}
-->
# Vezéreld az éjszakai fényedet az interneten keresztül - Virtuális IoT eszköz és Raspberry Pi

Az IoT eszközt úgy kell programozni, hogy az *test.mosquitto.org* MQTT használatával kommunikáljon, telemetriai értékeket küldjön a fényérzékelő leolvasásával, és parancsokat fogadjon az LED vezérléséhez.

Ebben a leckében csatlakoztatni fogod a Raspberry Pi-t vagy a virtuális IoT eszközt egy MQTT brokerhez.

## Az MQTT kliens csomag telepítése

Az MQTT brokerrel való kommunikációhoz telepítened kell egy MQTT könyvtár pip csomagot, akár a Pi-re, akár a virtuális környezetedbe, ha virtuális eszközt használsz.

### Feladat

Telepítsd a pip csomagot

1. Nyisd meg az éjszakai fény projektet a VS Code-ban.

1. Ha virtuális IoT eszközt használsz, győződj meg róla, hogy a terminál a virtuális környezetet futtatja. Ha Raspberry Pi-t használsz, nem fogsz virtuális környezetet használni.

1. Futtasd az alábbi parancsot az MQTT pip csomag telepítéséhez:

    ```sh
    pip3 install paho-mqtt
    ```

## Az eszköz programozása

Az eszköz készen áll a programozásra.

### Feladat

Írd meg az eszköz kódját.

1. Add hozzá a következő importot az `app.py` fájl tetejéhez:

    ```python
    import paho.mqtt.client as mqtt
    ```

    A `paho.mqtt.client` könyvtár lehetővé teszi az alkalmazásod számára, hogy MQTT-n keresztül kommunikáljon.

1. Add hozzá a következő kódot a fényérzékelő és az LED definíciói után:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Cseréld ki `<ID>`-t egy egyedi azonosítóra, amelyet az eszköz kliens neveként fogsz használni, és később azokra a témákra, amelyeket az eszköz publikál és feliratkozik. Az *test.mosquitto.org* broker nyilvános, és sokan használják, beleértve más diákokat is, akik ezen a feladaton dolgoznak. Egy egyedi MQTT kliens név és téma nevek biztosítják, hogy a kódod ne ütközzön másokéval. Erre az azonosítóra később szükséged lesz, amikor a szerver kódját készíted el ebben a feladatban.

    > 💁 Használhatsz egy weboldalt, például [GUIDGen](https://www.guidgen.com), hogy egyedi azonosítót generálj.

    A `client_name` az MQTT kliens egyedi neve a brokeren.

1. Add hozzá a következő kódot az új kód alá, hogy létrehozz egy MQTT kliens objektumot és csatlakozz az MQTT brokerhez:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Ez a kód létrehozza a kliens objektumot, csatlakozik a nyilvános MQTT brokerhez, és elindít egy feldolgozási ciklust, amely egy háttérszálban fut, és figyeli az üzeneteket az összes feliratkozott témán.

1. Futtasd a kódot ugyanúgy, ahogy a feladat előző részében futtattad. Ha virtuális IoT eszközt használsz, győződj meg róla, hogy a CounterFit alkalmazás fut, és a fényérzékelő és az LED a megfelelő lábakon lett létrehozva.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Ezt a kódot megtalálhatod a [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) mappában vagy a [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi) mappában.

😀 Sikeresen csatlakoztattad az eszközödet egy MQTT brokerhez.

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.