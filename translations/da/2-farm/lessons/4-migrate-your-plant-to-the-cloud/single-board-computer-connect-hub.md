<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-27T22:43:57+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "da"
}
-->
# Tilslut din IoT-enhed til skyen - Virtuel IoT-hardware og Raspberry Pi

I denne del af lektionen vil du tilslutte din virtuelle IoT-enhed eller Raspberry Pi til din IoT Hub for at sende telemetri og modtage kommandoer.

## Tilslut din enhed til IoT Hub

Det næste trin er at tilslutte din enhed til IoT Hub.

### Opgave - tilslut til IoT Hub

1. Åbn mappen `soil-moisture-sensor` i VS Code. Sørg for, at det virtuelle miljø kører i terminalen, hvis du bruger en virtuel IoT-enhed.

1. Installer nogle ekstra Pip-pakker:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` er et bibliotek til at kommunikere med din IoT Hub.

1. Tilføj følgende imports øverst i filen `app.py`, under de eksisterende imports:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Denne kode importerer SDK'et til at kommunikere med din IoT Hub.

1. Fjern linjen `import paho.mqtt.client as mqtt`, da dette bibliotek ikke længere er nødvendigt. Fjern al MQTT-kode, inklusive emnenavne, al kode der bruger `mqtt_client` og `handle_command`. Behold `while True:`-løkken, men slet linjen `mqtt_client.publish` fra denne løkke.

1. Tilføj følgende kode under import-udsagnene:

    ```python
    connection_string = "<connection string>"
    ```

    Erstat `<connection string>` med den forbindelsesstreng, du hentede til enheden tidligere i denne lektion.

    > 💁 Dette er ikke bedste praksis. Forbindelsesstrenge bør aldrig gemmes i kildekode, da de kan blive tjekket ind i kildekodekontrol og fundet af andre. Vi gør dette her for enkelhedens skyld. Ideelt set bør du bruge noget som en miljøvariabel og et værktøj som [`python-dotenv`](https://pypi.org/project/python-dotenv/). Du vil lære mere om dette i en kommende lektion.

1. Tilføj nedenstående kode for at oprette et enhedsklientobjekt, der kan kommunikere med IoT Hub, og tilslut det:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Kør denne kode. Du vil se din enhed tilslutte sig.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Send telemetri

Nu hvor din enhed er tilsluttet, kan du sende telemetri til IoT Hub i stedet for MQTT-broker.

### Opgave - send telemetri

1. Tilføj følgende kode inde i `while True`-løkken, lige før sleep:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Denne kode opretter en IoT Hub `Message`, der indeholder jordfugtighedsaflæsningen som en JSON-streng, og sender dette til IoT Hub som en enhed-til-sky-besked.

## Håndter kommandoer

Din enhed skal håndtere en kommando fra serverkoden for at styre relæet. Dette sendes som en direkte metodeanmodning.

## Opgave - håndter en direkte metodeanmodning

1. Tilføj følgende kode før `while True`-løkken:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Dette definerer en metode, `handle_method_request`, der vil blive kaldt, når en direkte metode kaldes af IoT Hub. Hver direkte metode har et navn, og denne kode forventer en metode kaldet `relay_on` for at tænde relæet og `relay_off` for at slukke det.

    > 💁 Dette kunne også implementeres i en enkelt direkte metodeanmodning, hvor den ønskede tilstand for relæet sendes i en payload, der kan sendes med metodeanmodningen og være tilgængelig fra `request`-objektet.

1. Direkte metoder kræver et svar for at fortælle den kaldende kode, at de er blevet håndteret. Tilføj følgende kode i slutningen af funktionen `handle_method_request` for at oprette et svar på anmodningen:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Denne kode sender et svar til den direkte metodeanmodning med en HTTP-statuskode på 200 og sender dette tilbage til IoT Hub.

1. Tilføj følgende kode under denne funktionsdefinition:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Denne kode fortæller IoT Hub-klienten at kalde funktionen `handle_method_request`, når en direkte metode kaldes.

> 💁 Du kan finde denne kode i mappen [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) eller [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Dit jordfugtighedssensorprogram er nu tilsluttet din IoT Hub!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os intet ansvar for misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.