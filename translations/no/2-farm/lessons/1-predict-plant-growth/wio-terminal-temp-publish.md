<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T22:50:02+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "no"
}
-->
# Publiser temperatur - Wio Terminal

I denne delen av leksjonen skal du publisere temperaturverdiene som oppdages av Wio Terminal over MQTT, slik at de senere kan brukes til å beregne GDD.

## Publiser temperaturen

Når temperaturen er lest, kan den publiseres over MQTT til noe 'server'-kode som vil lese verdiene og lagre dem klare til bruk for en GDD-beregning. Mikrokontrollere leser ikke tiden fra Internett og sporer tiden med en sanntidsklokke som standard, enheten må programmeres til å gjøre dette, forutsatt at den har nødvendig maskinvare.

For å forenkle ting i denne leksjonen, vil ikke tiden bli sendt med sensordataene. I stedet kan den legges til av serverkoden senere når den mottar meldingene.

### Oppgave

Programmer enheten til å publisere temperaturdata.

1. Åpne Wio Terminal-prosjektet `temperature-sensor`.

1. Gjenta trinnene du gjorde i leksjon 4 for å koble til MQTT og sende telemetri. Du vil bruke den samme offentlige Mosquitto-brokeren.

    Trinnene for dette er:

    - Legg til Seeed WiFi- og MQTT-bibliotekene i `.ini`-filen
    - Legg til konfigurasjonsfilen og kode for å koble til WiFi
    - Legg til kode for å koble til MQTT-brokeren
    - Legg til kode for å publisere telemetri

    > ⚠️ Se [instruksjonene for å koble til MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) og [instruksjonene for å sende telemetri](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) fra leksjon 4 hvis nødvendig.

1. Sørg for at `CLIENT_NAME` i `config.h`-headerfilen reflekterer dette prosjektet:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. For telemetrien, i stedet for å sende en lysverdi, send temperaturverdien som er lest fra DHT-sensoren i en egenskap i JSON-dokumentet kalt `temperature` ved å endre `loop`-funksjonen i `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Temperaturverdien trenger ikke å leses veldig ofte - den vil ikke endre seg mye på kort tid, så sett `delay` i `loop`-funksjonen til 10 minutter:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 Funksjonen `delay` tar tiden i millisekunder, så for å gjøre det lettere å lese, sendes verdien som resultatet av en beregning. 1 000 ms i et sekund, 60 sekunder i et minutt, så 10 x (60 sekunder i et minutt) x (1 000 ms i et sekund) gir en forsinkelse på 10 minutter.

1. Last opp dette til din Wio Terminal, og bruk seriemonitoren for å se temperaturen bli sendt til MQTT-brokeren.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Du finner denne koden i mappen [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Du har publisert temperaturen som telemetri fra enheten din.

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.