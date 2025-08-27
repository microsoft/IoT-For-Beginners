<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-27T22:50:54+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "da"
}
-->
# Udgiv temperatur - Virtuel IoT-hardware og Raspberry Pi

I denne del af lektionen vil du udgive temperaturværdier, der er registreret af Raspberry Pi eller Virtuel IoT-enhed via MQTT, så de senere kan bruges til at beregne GDD.

## Udgiv temperaturen

Når temperaturen er blevet aflæst, kan den udgives via MQTT til noget 'server'-kode, der vil læse værdierne og gemme dem klar til brug i en GDD-beregning.

### Opgave - udgiv temperaturen

Programmer enheden til at udgive temperaturdata.

1. Åbn `temperature-sensor` app-projektet, hvis det ikke allerede er åbent.

1. Gentag de trin, du udførte i lektion 4 for at oprette forbindelse til MQTT og sende telemetri. Du vil bruge den samme offentlige Mosquitto-broker.

    Trinnene for dette er:

    - Tilføj MQTT pip-pakken
    - Tilføj koden for at oprette forbindelse til MQTT-brokeren
    - Tilføj koden for at udgive telemetri

    > ⚠️ Se [instruktionerne for at oprette forbindelse til MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) og [instruktionerne for at sende telemetri](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) fra lektion 4, hvis det er nødvendigt.

1. Sørg for, at `client_name` afspejler dette projekts navn:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. For telemetrien, i stedet for at sende en lysværdi, skal du sende temperaturværdien, der er aflæst fra DHT-sensoren, i en egenskab på JSON-dokumentet kaldet `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Temperaturværdien behøver ikke aflæses særlig ofte - den vil ikke ændre sig meget på kort tid, så sæt `time.sleep` til 10 minutter:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Funktionen `sleep` tager tiden i sekunder, så for at gøre det lettere at læse, sendes værdien som resultatet af en beregning. 60 sekunder i et minut, så 10 x (60 sekunder i et minut) giver en forsinkelse på 10 minutter.

1. Kør koden på samme måde som du kørte koden fra den tidligere del af opgaven. Hvis du bruger en virtuel IoT-enhed, skal du sørge for, at CounterFit-appen kører, og at fugtigheds- og temperatursensorerne er oprettet på de korrekte pins.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Du kan finde denne kode i mappen [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) eller mappen [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Du har med succes udgivet temperaturen som telemetri fra din enhed.

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal det bemærkes, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os intet ansvar for misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.