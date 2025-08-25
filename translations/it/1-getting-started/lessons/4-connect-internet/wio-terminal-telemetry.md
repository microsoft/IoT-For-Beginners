<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-25T17:17:18+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "it"
}
-->
# Controlla la tua luce notturna tramite Internet - Wio Terminal

In questa parte della lezione, invierai telemetria con i livelli di luce dal tuo Wio Terminal al broker MQTT.

## Installa le librerie JSON per Arduino

Un modo popolare per inviare messaggi tramite MQTT è utilizzare JSON. Esiste una libreria Arduino per JSON che semplifica la lettura e la scrittura di documenti JSON.

### Attività

Installa la libreria JSON per Arduino.

1. Apri il progetto della luce notturna in VS Code.

1. Aggiungi la seguente riga aggiuntiva alla lista `lib_deps` nel file `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Questo importa [ArduinoJson](https://arduinojson.org), una libreria JSON per Arduino.

## Pubblica la telemetria

Il passo successivo è creare un documento JSON con la telemetria e inviarlo al broker MQTT.

### Attività - pubblica la telemetria

Pubblica la telemetria sul broker MQTT.

1. Aggiungi il seguente codice alla fine del file `config.h` per definire il nome del topic di telemetria per il broker MQTT:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    Il `CLIENT_TELEMETRY_TOPIC` è il topic su cui il dispositivo pubblicherà i livelli di luce.

1. Apri il file `main.cpp`.

1. Aggiungi la seguente direttiva `#include` all'inizio del file:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Aggiungi il seguente codice all'interno della funzione `loop`, appena prima del `delay`:

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

    Questo codice legge il livello di luce e crea un documento JSON utilizzando ArduinoJson che contiene questo livello. Successivamente, viene serializzato in una stringa e pubblicato sul topic MQTT di telemetria dal client MQTT.

1. Carica il codice sul tuo Wio Terminal e utilizza il Serial Monitor per vedere i livelli di luce inviati al broker MQTT.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Puoi trovare questo codice nella cartella [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Hai inviato con successo la telemetria dal tuo dispositivo.

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche potrebbero contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.