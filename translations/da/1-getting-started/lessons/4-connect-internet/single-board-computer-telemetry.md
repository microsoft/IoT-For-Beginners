<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-27T21:51:50+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "da"
}
-->
# Styr din natlampe over internettet - Virtuel IoT-hardware og Raspberry Pi

I denne del af lektionen vil du sende telemetri med lysniveauer fra din Raspberry Pi eller virtuelle IoT-enhed til en MQTT-broker.

## Udgiv telemetri

Det næste trin er at oprette et JSON-dokument med telemetri og sende det til MQTT-brokeren.

### Opgave

Udgiv telemetri til MQTT-brokeren.

1. Åbn natlampeprojektet i VS Code.

1. Hvis du bruger en virtuel IoT-enhed, skal du sikre dig, at terminalen kører det virtuelle miljø. Hvis du bruger en Raspberry Pi, vil du ikke bruge et virtuelt miljø.

1. Tilføj følgende import øverst i `app.py`-filen:

    ```python
    import json
    ```

    `json`-biblioteket bruges til at kode telemetrien som et JSON-dokument.

1. Tilføj følgende efter deklarationen af `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` er det MQTT-emne, som enheden vil udgive lysniveauer til.

1. Erstat indholdet af `while True:`-løkken i slutningen af filen med følgende:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Denne kode pakker lysniveauet ind i et JSON-dokument og udgiver det til MQTT-brokeren. Derefter sættes programmet på pause for at reducere frekvensen af de sendte beskeder.

1. Kør koden på samme måde, som du kørte koden fra den tidligere del af opgaven. Hvis du bruger en virtuel IoT-enhed, skal du sikre dig, at CounterFit-appen kører, og at lyssensoren og LED'en er oprettet på de korrekte pins.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Du kan finde denne kode i [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device)-mappen eller [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi)-mappen.

😀 Du har med succes sendt telemetri fra din enhed.

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.