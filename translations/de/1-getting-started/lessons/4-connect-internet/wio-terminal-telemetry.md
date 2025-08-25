<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-25T21:58:57+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "de"
}
-->
# Steuern Sie Ihr Nachtlicht über das Internet - Wio Terminal

In diesem Teil der Lektion senden Sie Telemetriedaten mit Lichtwerten von Ihrem Wio Terminal an den MQTT-Broker.

## Installieren der JSON Arduino-Bibliotheken

Eine beliebte Methode, Nachrichten über MQTT zu senden, ist die Verwendung von JSON. Es gibt eine Arduino-Bibliothek für JSON, die das Lesen und Schreiben von JSON-Dokumenten erleichtert.

### Aufgabe

Installieren Sie die Arduino JSON-Bibliothek.

1. Öffnen Sie das Nachtlicht-Projekt in VS Code.

1. Fügen Sie die folgende Zeile als zusätzliche Zeile zur `lib_deps`-Liste in der Datei `platformio.ini` hinzu:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Dies importiert [ArduinoJson](https://arduinojson.org), eine Arduino JSON-Bibliothek.

## Telemetrie veröffentlichen

Der nächste Schritt besteht darin, ein JSON-Dokument mit Telemetriedaten zu erstellen und es an den MQTT-Broker zu senden.

### Aufgabe - Telemetrie veröffentlichen

Veröffentlichen Sie Telemetriedaten auf dem MQTT-Broker.

1. Fügen Sie den folgenden Code am Ende der Datei `config.h` hinzu, um den Telemetrie-Themennamen für den MQTT-Broker zu definieren:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    Das `CLIENT_TELEMETRY_TOPIC` ist das Thema, auf dem das Gerät die Lichtwerte veröffentlichen wird.

1. Öffnen Sie die Datei `main.cpp`.

1. Fügen Sie die folgende `#include`-Direktive am Anfang der Datei hinzu:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Fügen Sie den folgenden Code in die `loop`-Funktion ein, direkt vor dem `delay`:

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

    Dieser Code liest den Lichtwert aus und erstellt ein JSON-Dokument mit ArduinoJson, das diesen Wert enthält. Dieses wird dann in einen String serialisiert und vom MQTT-Client im Telemetrie-MQTT-Thema veröffentlicht.

1. Laden Sie den Code auf Ihr Wio Terminal hoch und verwenden Sie den Serial Monitor, um die Lichtwerte zu sehen, die an den MQTT-Broker gesendet werden.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Sie finden diesen Code im Ordner [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Sie haben erfolgreich Telemetriedaten von Ihrem Gerät gesendet.

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.