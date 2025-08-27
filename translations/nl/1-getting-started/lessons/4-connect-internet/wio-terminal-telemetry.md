<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-27T21:45:39+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "nl"
}
-->
# Bedien je nachtlampje via het internet - Wio Terminal

In dit deel van de les stuur je telemetrie met lichtniveaus van je Wio Terminal naar de MQTT-broker.

## Installeer de JSON Arduino-bibliotheken

Een populaire manier om berichten via MQTT te verzenden is door gebruik te maken van JSON. Er is een Arduino-bibliotheek voor JSON die het lezen en schrijven van JSON-documenten eenvoudiger maakt.

### Taak

Installeer de Arduino JSON-bibliotheek.

1. Open het nachtlampproject in VS Code.

1. Voeg de volgende regel toe aan de `lib_deps` lijst in het `platformio.ini` bestand:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Dit importeert [ArduinoJson](https://arduinojson.org), een Arduino JSON-bibliotheek.

## Telemetrie publiceren

De volgende stap is het maken van een JSON-document met telemetrie en dit verzenden naar de MQTT-broker.

### Taak - telemetrie publiceren

Publiceer telemetrie naar de MQTT-broker.

1. Voeg de volgende code toe aan de onderkant van het `config.h` bestand om de telemetrie-topicnaam voor de MQTT-broker te definiëren:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    De `CLIENT_TELEMETRY_TOPIC` is de topic waar het apparaat lichtniveaus naar zal publiceren.

1. Open het `main.cpp` bestand.

1. Voeg de volgende `#include` directive toe aan de bovenkant van het bestand:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Voeg de volgende code toe binnen de `loop` functie, net vóór de `delay`:

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

    Deze code leest het lichtniveau en maakt een JSON-document met behulp van ArduinoJson dat dit niveau bevat. Dit wordt vervolgens geserialiseerd naar een string en gepubliceerd op de telemetrie-MQTT-topic door de MQTT-client.

1. Upload de code naar je Wio Terminal en gebruik de Serial Monitor om de lichtniveaus te zien die naar de MQTT-broker worden verzonden.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Je kunt deze code vinden in de [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) map.

😀 Je hebt met succes telemetrie vanaf je apparaat verzonden.

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.