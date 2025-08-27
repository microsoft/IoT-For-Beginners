<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-27T21:53:04+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "no"
}
-->
# Kontroller nattlampen din over Internett - Wio Terminal

I denne delen av leksjonen vil du sende telemetri med lysnivåer fra din Wio Terminal til MQTT-broker.

## Installer JSON Arduino-biblioteker

En populær måte å sende meldinger over MQTT er ved å bruke JSON. Det finnes et Arduino-bibliotek for JSON som gjør det enklere å lese og skrive JSON-dokumenter.

### Oppgave

Installer Arduino JSON-biblioteket.

1. Åpne nattlampe-prosjektet i VS Code.

1. Legg til følgende som en ekstra linje i `lib_deps`-listen i `platformio.ini`-filen:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Dette importerer [ArduinoJson](https://arduinojson.org), et Arduino JSON-bibliotek.

## Publiser telemetri

Neste steg er å lage et JSON-dokument med telemetri og sende det til MQTT-broker.

### Oppgave - publiser telemetri

Publiser telemetri til MQTT-broker.

1. Legg til følgende kode nederst i `config.h`-filen for å definere telemetri-emnenavnet for MQTT-broker:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` er emnet enheten vil publisere lysnivåer til.

1. Åpne `main.cpp`-filen.

1. Legg til følgende `#include`-direktiv øverst i filen:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Legg til følgende kode inne i `loop`-funksjonen, rett før `delay`:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    Denne koden leser lysnivået og lager et JSON-dokument ved hjelp av ArduinoJson som inneholder dette nivået. Dette blir deretter serialisert til en streng og publisert på telemetri-MQTT-emnet av MQTT-klienten.

1. Last opp koden til din Wio Terminal, og bruk Serial Monitor for å se lysnivåene som blir sendt til MQTT-broker.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Du finner denne koden i [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal)-mappen.

😀 Du har sendt telemetri fra enheten din med suksess.

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.