<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-27T21:52:55+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "da"
}
-->
# Styr din natlampe over internettet - Wio Terminal

I denne del af lektionen vil du sende telemetri med lysniveauer fra din Wio Terminal til MQTT-broker.

## Installer JSON Arduino-bibliotekerne

En populær måde at sende beskeder over MQTT er ved at bruge JSON. Der findes et Arduino-bibliotek til JSON, som gør det nemmere at læse og skrive JSON-dokumenter.

### Opgave

Installer Arduino JSON-biblioteket.

1. Åbn natlampeprojektet i VS Code.

1. Tilføj følgende som en ekstra linje til `lib_deps`-listen i `platformio.ini`-filen:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Dette importerer [ArduinoJson](https://arduinojson.org), et Arduino JSON-bibliotek.

## Udsend telemetri

Næste trin er at oprette et JSON-dokument med telemetri og sende det til MQTT-broker.

### Opgave - udsend telemetri

Udsend telemetri til MQTT-broker.

1. Tilføj følgende kode nederst i `config.h`-filen for at definere telemetri-emnenavnet til MQTT-broker:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` er det emne, enheden vil udsende lysniveauer til.

1. Åbn `main.cpp`-filen.

1. Tilføj følgende `#include`-direktiv øverst i filen:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Tilføj følgende kode inde i `loop`-funktionen, lige før `delay`:

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

    Denne kode læser lysniveauet og opretter et JSON-dokument ved hjælp af ArduinoJson, som indeholder dette niveau. Det bliver derefter serialiseret til en streng og udsendt på telemetri-MQTT-emnet af MQTT-klienten.

1. Upload koden til din Wio Terminal, og brug Serial Monitor til at se lysniveauerne blive sendt til MQTT-broker.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Du kan finde denne kode i [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal)-mappen.

😀 Du har med succes sendt telemetri fra din enhed.

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.