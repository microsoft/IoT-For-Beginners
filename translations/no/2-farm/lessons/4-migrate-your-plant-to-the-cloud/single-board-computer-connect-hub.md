<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-27T22:44:09+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "no"
}
-->
# Koble IoT-enheten din til skyen - Virtuell IoT-maskinvare og Raspberry Pi

I denne delen av leksjonen skal du koble din virtuelle IoT-enhet eller Raspberry Pi til IoT Hub for å sende telemetri og motta kommandoer.

## Koble enheten din til IoT Hub

Neste steg er å koble enheten din til IoT Hub.

### Oppgave - koble til IoT Hub

1. Åpne mappen `soil-moisture-sensor` i VS Code. Sørg for at det virtuelle miljøet kjører i terminalen hvis du bruker en virtuell IoT-enhet.

1. Installer noen ekstra Pip-pakker:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` er et bibliotek for å kommunisere med IoT Hub.

1. Legg til følgende imports øverst i `app.py`-filen, under de eksisterende imports:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Denne koden importerer SDK-en for å kommunisere med IoT Hub.

1. Fjern linjen `import paho.mqtt.client as mqtt`, da dette biblioteket ikke lenger er nødvendig. Fjern all MQTT-kode, inkludert emnenavnene, all kode som bruker `mqtt_client` og `handle_command`. Behold `while True:`-løkken, men slett linjen `mqtt_client.publish` fra denne løkken.

1. Legg til følgende kode under import-uttalelsene:

    ```python
    connection_string = "<connection string>"
    ```

    Erstatt `<connection string>` med tilkoblingsstrengen du hentet for enheten tidligere i denne leksjonen.

    > 💁 Dette er ikke beste praksis. Tilkoblingsstrenger bør aldri lagres i kildekoden, da dette kan sjekkes inn i kildekodekontroll og bli funnet av hvem som helst. Vi gjør dette her for enkelhetens skyld. Ideelt sett bør du bruke noe som en miljøvariabel og et verktøy som [`python-dotenv`](https://pypi.org/project/python-dotenv/). Du vil lære mer om dette i en kommende leksjon.

1. Under denne koden, legg til følgende for å opprette et enhetsklientobjekt som kan kommunisere med IoT Hub, og koble det til:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Kjør denne koden. Du vil se at enheten din kobler seg til.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Send telemetri

Nå som enheten din er koblet til, kan du sende telemetri til IoT Hub i stedet for til MQTT-brokeren.

### Oppgave - send telemetri

1. Legg til følgende kode inne i `while True`-løkken, rett før sleep:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Denne koden oppretter en IoT Hub-`Message` som inneholder jordfuktighetsavlesningen som en JSON-streng, og sender dette til IoT Hub som en enhet-til-sky-melding.

## Håndtere kommandoer

Enheten din må håndtere en kommando fra serverkoden for å kontrollere reléet. Dette sendes som en direkte metodeforespørsel.

## Oppgave - håndtere en direkte metodeforespørsel

1. Legg til følgende kode før `while True`-løkken:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Dette definerer en metode, `handle_method_request`, som vil bli kalt når en direkte metode kalles av IoT Hub. Hver direkte metode har et navn, og denne koden forventer en metode kalt `relay_on` for å slå på reléet, og `relay_off` for å slå av reléet.

    > 💁 Dette kan også implementeres i en enkelt direkte metodeforespørsel, der ønsket tilstand for reléet sendes i en nyttelast som kan sendes med metodeforespørselen og er tilgjengelig fra `request`-objektet.

1. Direkte metoder krever et svar for å informere den kallende koden om at de har blitt håndtert. Legg til følgende kode på slutten av `handle_method_request`-funksjonen for å opprette et svar på forespørselen:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Denne koden sender et svar på den direkte metodeforespørselen med en HTTP-statuskode på 200, og sender dette tilbake til IoT Hub.

1. Legg til følgende kode under denne funksjonsdefinisjonen:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Denne koden forteller IoT Hub-klienten å kalle `handle_method_request`-funksjonen når en direkte metode kalles.

> 💁 Du finner denne koden i mappen [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) eller [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Programmet for jordfuktighetssensoren din er nå koblet til IoT Hub!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.