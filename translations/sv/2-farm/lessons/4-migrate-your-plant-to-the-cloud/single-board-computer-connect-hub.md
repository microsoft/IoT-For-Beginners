<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-27T22:43:42+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "sv"
}
-->
# Anslut din IoT-enhet till molnet - Virtuell IoT-hårdvara och Raspberry Pi

I den här delen av lektionen kommer du att ansluta din virtuella IoT-enhet eller Raspberry Pi till din IoT Hub för att skicka telemetri och ta emot kommandon.

## Anslut din enhet till IoT Hub

Nästa steg är att ansluta din enhet till IoT Hub.

### Uppgift - anslut till IoT Hub

1. Öppna mappen `soil-moisture-sensor` i VS Code. Se till att den virtuella miljön körs i terminalen om du använder en virtuell IoT-enhet.

1. Installera några ytterligare Pip-paket:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` är ett bibliotek för att kommunicera med din IoT Hub.

1. Lägg till följande imports högst upp i filen `app.py`, under de befintliga imports:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Den här koden importerar SDK för att kommunicera med din IoT Hub.

1. Ta bort raden `import paho.mqtt.client as mqtt` eftersom detta bibliotek inte längre behövs. Ta bort all MQTT-kod inklusive ämnesnamn, all kod som använder `mqtt_client` och `handle_command`. Behåll loopen `while True:`, men ta bort raden `mqtt_client.publish` från denna loop.

1. Lägg till följande kod under importuttalandena:

    ```python
    connection_string = "<connection string>"
    ```

    Ersätt `<connection string>` med anslutningssträngen du hämtade för enheten tidigare i denna lektion.

    > 💁 Detta är inte bästa praxis. Anslutningssträngar bör aldrig lagras i källkod, eftersom de kan checkas in i versionskontroll och hittas av vem som helst. Vi gör detta här för enkelhetens skull. Idealiskt bör du använda något som en miljövariabel och ett verktyg som [`python-dotenv`](https://pypi.org/project/python-dotenv/). Du kommer att lära dig mer om detta i en kommande lektion.

1. Lägg till följande kod under detta för att skapa ett enhetsklientobjekt som kan kommunicera med IoT Hub och ansluta det:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Kör denna kod. Du kommer att se din enhet ansluta.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Skicka telemetri

Nu när din enhet är ansluten kan du skicka telemetri till IoT Hub istället för till MQTT-brokern.

### Uppgift - skicka telemetri

1. Lägg till följande kod inuti loopen `while True`, precis före sömnen:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Den här koden skapar ett IoT Hub `Message` som innehåller jordfuktighetsavläsningen som en JSON-sträng och skickar detta till IoT Hub som ett meddelande från enhet till moln.

## Hantera kommandon

Din enhet behöver hantera ett kommando från serverkoden för att styra reläet. Detta skickas som en direkt metodförfrågan.

## Uppgift - hantera en direkt metodförfrågan

1. Lägg till följande kod före loopen `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Detta definierar en metod, `handle_method_request`, som kommer att anropas när en direkt metod anropas av IoT Hub. Varje direkt metod har ett namn, och denna kod förväntar sig en metod som heter `relay_on` för att slå på reläet och `relay_off` för att stänga av det.

    > 💁 Detta kan också implementeras i en enda direkt metodförfrågan, där det önskade tillståndet för reläet skickas i en payload som kan skickas med metodförfrågan och vara tillgänglig från objektet `request`.

1. Direkta metoder kräver ett svar för att meddela den anropande koden att de har hanterats. Lägg till följande kod i slutet av funktionen `handle_method_request` för att skapa ett svar på förfrågan:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Den här koden skickar ett svar på den direkta metodförfrågan med en HTTP-statuskod på 200 och skickar detta tillbaka till IoT Hub.

1. Lägg till följande kod under denna funktionsdefinition:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Den här koden instruerar IoT Hub-klienten att anropa funktionen `handle_method_request` när en direkt metod anropas.

> 💁 Du kan hitta denna kod i mappen [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) eller [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Ditt jordfuktighetssensorprogram är anslutet till din IoT Hub!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.