<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-27T21:52:02+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "no"
}
-->
# Kontroller nattlyset ditt over Internett - Virtuell IoT-maskinvare og Raspberry Pi

I denne delen av leksjonen skal du sende telemetri med lysnivåer fra din Raspberry Pi eller virtuelle IoT-enhet til en MQTT-broker.

## Publiser telemetri

Neste steg er å lage et JSON-dokument med telemetri og sende det til MQTT-brokeren.

### Oppgave

Publiser telemetri til MQTT-brokeren.

1. Åpne nattlysprosjektet i VS Code.

1. Hvis du bruker en virtuell IoT-enhet, sørg for at terminalen kjører det virtuelle miljøet. Hvis du bruker en Raspberry Pi, trenger du ikke bruke et virtuelt miljø.

1. Legg til følgende import øverst i `app.py`-filen:

    ```python
    import json
    ```

    `json`-biblioteket brukes til å kode telemetrien som et JSON-dokument.

1. Legg til følgende etter deklarasjonen av `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` er MQTT-emnet som enheten vil publisere lysnivåene til.

1. Erstatt innholdet i `while True:`-løkken på slutten av filen med følgende:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Denne koden pakker lysnivået inn i et JSON-dokument og publiserer det til MQTT-brokeren. Deretter settes det en pause for å redusere frekvensen av meldinger som sendes.

1. Kjør koden på samme måte som du kjørte koden fra forrige del av oppgaven. Hvis du bruker en virtuell IoT-enhet, må du sørge for at CounterFit-appen kjører og at lyssensoren og LED-en er opprettet på de riktige pinnene.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Du finner denne koden i [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device)-mappen eller [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi)-mappen.

😀 Du har nå sendt telemetri fra enheten din.

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.