<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-27T23:12:34+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "hu"
}
-->
# Csatlakoztassa IoT eszközét a felhőhöz - Virtuális IoT hardver és Raspberry Pi

A lecke ezen részében csatlakoztatni fogja virtuális IoT eszközét vagy Raspberry Pi-jét az IoT Hubhoz, hogy telemetriát küldjön és parancsokat fogadjon.

## Csatlakoztassa eszközét az IoT Hubhoz

A következő lépés az eszköz csatlakoztatása az IoT Hubhoz.

### Feladat - csatlakozás az IoT Hubhoz

1. Nyissa meg a `soil-moisture-sensor` mappát a VS Code-ban. Győződjön meg arról, hogy a virtuális környezet fut a terminálban, ha virtuális IoT eszközt használ.

1. Telepítsen néhány további Pip csomagot:

    ```sh
    pip3 install azure-iot-device
    ```

    Az `azure-iot-device` egy könyvtár, amely lehetővé teszi az IoT Hubbal való kommunikációt.

1. Adja hozzá a következő importokat az `app.py` fájl tetejére, a meglévő importok alá:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Ez a kód importálja az SDK-t az IoT Hubbal való kommunikációhoz.

1. Távolítsa el az `import paho.mqtt.client as mqtt` sort, mivel erre a könyvtárra már nincs szükség. Távolítsa el az összes MQTT kódot, beleértve a témaneveket, az összes kódot, amely a `mqtt_client`-et használja, és a `handle_command`-ot. Tartsa meg a `while True:` ciklust, csak törölje a `mqtt_client.publish` sort ebből a ciklusból.

1. Adja hozzá a következő kódot az import utasítások alá:

    ```python
    connection_string = "<connection string>"
    ```

    Cserélje ki a `<connection string>` helyére azt a kapcsolat karakterláncot, amelyet korábban a lecke során az eszközhöz lekért.

    > 💁 Ez nem a legjobb gyakorlat. A kapcsolat karakterláncokat soha nem szabad a forráskódban tárolni, mivel ezek bekerülhetnek a verziókezelésbe, és bárki megtalálhatja őket. Itt az egyszerűség kedvéért tesszük ezt. Ideális esetben környezeti változót és egy olyan eszközt kellene használni, mint a [`python-dotenv`](https://pypi.org/project/python-dotenv/). Erről többet fog tanulni egy következő leckében.

1. E kód alá adja hozzá a következőt, hogy létrehozzon egy eszköz kliens objektumot, amely képes kommunikálni az IoT Hubbal, és csatlakoztassa azt:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Futtassa ezt a kódot. Látni fogja, hogy az eszköz csatlakozik.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Telemetria küldése

Most, hogy az eszköz csatlakozott, telemetriát küldhet az IoT Hubnak az MQTT broker helyett.

### Feladat - telemetria küldése

1. Adja hozzá a következő kódot a `while True` ciklusba, közvetlenül az alvás előtt:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Ez a kód létrehoz egy IoT Hub `Message`-t, amely a talajnedvesség-értéket JSON karakterláncként tartalmazza, majd ezt eszköz-felhő üzenetként elküldi az IoT Hubnak.

## Parancsok kezelése

Az eszköznek kezelnie kell egy parancsot a szerver kódjától, hogy vezérelje a relét. Ez közvetlen metódus kérésként kerül elküldésre.

## Feladat - közvetlen metódus kérés kezelése

1. Adja hozzá a következő kódot a `while True` ciklus elé:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Ez definiál egy metódust, `handle_method_request`, amelyet akkor hívnak meg, amikor az IoT Hub közvetlen metódust hív meg. Minden közvetlen metódusnak van egy neve, és ez a kód egy `relay_on` nevű metódust vár, amely bekapcsolja a relét, valamint egy `relay_off` nevű metódust, amely kikapcsolja azt.

    > 💁 Ez egyetlen közvetlen metódus kérésben is megvalósítható, amely a relé kívánt állapotát egy payloadban adja át, amelyet a metódus kéréshez lehet csatolni, és amely elérhető a `request` objektumból.

1. A közvetlen metódusok válaszra van szükségük, hogy jelezzék a hívó kódnak, hogy kezelték őket. Adja hozzá a következő kódot a `handle_method_request` függvény végéhez, hogy választ hozzon létre a kérésre:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Ez a kód válaszol a közvetlen metódus kérésre egy 200-as HTTP státuszkóddal, és visszaküldi ezt az IoT Hubnak.

1. Adja hozzá a következő kódot a függvény definíciója alá:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Ez a kód azt mondja az IoT Hub kliensnek, hogy hívja meg a `handle_method_request` függvényt, amikor egy közvetlen metódust hívnak meg.

> 💁 Ezt a kódot megtalálja a [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) vagy [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device) mappában.

😀 A talajnedvesség-érzékelő programja csatlakozott az IoT Hubhoz!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.