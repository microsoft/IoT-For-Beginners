<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-27T21:33:02+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "nl"
}
-->
# Verbind je IoT-apparaat met de cloud - Virtuele IoT-hardware en Raspberry Pi

In dit deel van de les verbind je je virtuele IoT-apparaat of Raspberry Pi met je IoT Hub om telemetrie te verzenden en opdrachten te ontvangen.

## Verbind je apparaat met IoT Hub

De volgende stap is om je apparaat te verbinden met IoT Hub.

### Taak - verbinden met IoT Hub

1. Open de map `soil-moisture-sensor` in VS Code. Zorg ervoor dat de virtuele omgeving actief is in de terminal als je een virtueel IoT-apparaat gebruikt.

1. Installeer een paar extra Pip-pakketten:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` is een bibliotheek om te communiceren met je IoT Hub.

1. Voeg de volgende imports toe aan de bovenkant van het bestand `app.py`, onder de bestaande imports:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Deze code importeert de SDK om te communiceren met je IoT Hub.

1. Verwijder de regel `import paho.mqtt.client as mqtt`, omdat deze bibliotheek niet langer nodig is. Verwijder alle MQTT-code, inclusief de topicnamen, alle code die `mqtt_client` gebruikt en de `handle_command`. Laat de `while True:`-lus staan, maar verwijder de regel `mqtt_client.publish` uit deze lus.

1. Voeg de volgende code toe onder de importverklaringen:

    ```python
    connection_string = "<connection string>"
    ```

    Vervang `<connection string>` door de verbindingsreeks die je eerder in deze les hebt opgehaald voor het apparaat.

    > 💁 Dit is niet de beste praktijk. Verbindingsreeksen mogen nooit in de broncode worden opgeslagen, omdat deze in versiebeheer terecht kunnen komen en door iedereen gevonden kunnen worden. We doen dit hier voor de eenvoud. Idealiter gebruik je iets als een omgevingsvariabele en een tool zoals [`python-dotenv`](https://pypi.org/project/python-dotenv/). Je leert hier meer over in een volgende les.

1. Voeg onder deze code het volgende toe om een apparaatclientobject te maken dat kan communiceren met IoT Hub en verbind het:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Voer deze code uit. Je zult zien dat je apparaat verbinding maakt.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Telemetrie verzenden

Nu je apparaat is verbonden, kun je telemetrie naar de IoT Hub sturen in plaats van naar de MQTT-broker.

### Taak - telemetrie verzenden

1. Voeg de volgende code toe binnen de `while True`-lus, net voor de slaapfunctie:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Deze code maakt een IoT Hub `Message` met de bodemvochtigheidsmeting als een JSON-string en stuurt dit naar de IoT Hub als een bericht van apparaat naar cloud.

## Opdrachten verwerken

Je apparaat moet een opdracht van de servercode verwerken om het relais te bedienen. Dit wordt verzonden als een directe methodeaanvraag.

## Taak - een directe methodeaanvraag verwerken

1. Voeg de volgende code toe vóór de `while True`-lus:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Dit definieert een methode, `handle_method_request`, die wordt aangeroepen wanneer een directe methode wordt aangeroepen door de IoT Hub. Elke directe methode heeft een naam, en deze code verwacht een methode genaamd `relay_on` om het relais in te schakelen, en `relay_off` om het relais uit te schakelen.

    > 💁 Dit kan ook worden geïmplementeerd in één enkele directe methodeaanvraag, waarbij de gewenste status van het relais wordt doorgegeven in een payload die kan worden meegegeven met de methodeaanvraag en beschikbaar is via het `request`-object.

1. Directe methoden vereisen een antwoord om de aanroepende code te laten weten dat ze zijn verwerkt. Voeg de volgende code toe aan het einde van de functie `handle_method_request` om een antwoord te maken op de aanvraag:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Deze code stuurt een antwoord op de directe methodeaanvraag met een HTTP-statuscode van 200 en stuurt dit terug naar de IoT Hub.

1. Voeg de volgende code toe onder deze functiedefinitie:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Deze code vertelt de IoT Hub-client om de functie `handle_method_request` aan te roepen wanneer een directe methode wordt aangeroepen.

> 💁 Je kunt deze code vinden in de map [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) of [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Je bodemvochtigheidssensorprogramma is verbonden met je IoT Hub!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.