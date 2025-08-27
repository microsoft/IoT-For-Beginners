<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-27T22:51:05+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "no"
}
-->
# Publiser temperatur - Virtuell IoT-maskinvare og Raspberry Pi

I denne delen av leksjonen skal du publisere temperaturverdiene som oppdages av Raspberry Pi eller Virtuell IoT-enhet over MQTT, slik at de senere kan brukes til å beregne GDD.

## Publiser temperaturen

Når temperaturen er lest, kan den publiseres over MQTT til noe 'server'-kode som vil lese verdiene og lagre dem klare til bruk i en GDD-beregning.

### Oppgave - publiser temperaturen

Programmer enheten til å publisere temperaturdata.

1. Åpne prosjektet for appen `temperature-sensor` hvis det ikke allerede er åpent.

1. Gjenta trinnene du gjorde i leksjon 4 for å koble til MQTT og sende telemetri. Du vil bruke den samme offentlige Mosquitto-brokeren.

    Trinnene for dette er:

    - Legg til MQTT pip-pakken
    - Legg til koden for å koble til MQTT-brokeren
    - Legg til koden for å publisere telemetri

    > ⚠️ Se [instruksjonene for å koble til MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) og [instruksjonene for å sende telemetri](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) fra leksjon 4 hvis nødvendig.

1. Sørg for at `client_name` gjenspeiler navnet på dette prosjektet:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. For telemetrien, i stedet for å sende en lysverdi, send temperaturverdien som er lest fra DHT-sensoren i en egenskap i JSON-dokumentet kalt `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Temperaturverdien trenger ikke leses veldig ofte - den vil ikke endre seg mye på kort tid, så sett `time.sleep` til 10 minutter:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Funksjonen `sleep` tar tiden i sekunder, så for å gjøre det lettere å lese, sendes verdien som resultatet av en beregning. 60 sekunder i et minutt, så 10 x (60 sekunder i et minutt) gir en forsinkelse på 10 minutter.

1. Kjør koden på samme måte som du kjørte koden fra forrige del av oppgaven. Hvis du bruker en virtuell IoT-enhet, må du sørge for at CounterFit-appen kjører og at fuktighets- og temperatursensorene er opprettet på de riktige pinnene.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Du finner denne koden i mappen [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) eller mappen [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Du har nå publisert temperaturen som telemetri fra enheten din.

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.