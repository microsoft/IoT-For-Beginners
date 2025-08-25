<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-25T22:01:39+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "de"
}
-->
# Steuern Sie Ihr Nachtlicht über das Internet - Wio Terminal

In diesem Teil der Lektion abonnieren Sie Befehle, die von einem MQTT-Broker an Ihr Wio Terminal gesendet werden.

## Befehle abonnieren

Der nächste Schritt besteht darin, die vom MQTT-Broker gesendeten Befehle zu abonnieren und darauf zu reagieren.

### Aufgabe

Abonnieren Sie Befehle.

1. Öffnen Sie das Nachtlicht-Projekt in VS Code.

1. Fügen Sie den folgenden Code am Ende der Datei `config.h` hinzu, um den Themennamen für die Befehle zu definieren:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    Das `SERVER_COMMAND_TOPIC` ist das Thema, das das Gerät abonniert, um LED-Befehle zu empfangen.

1. Fügen Sie die folgende Zeile am Ende der Funktion `reconnectMQTTClient` hinzu, um das Befehls-Thema zu abonnieren, wenn der MQTT-Client erneut verbunden wird:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Fügen Sie den folgenden Code unterhalb der Funktion `reconnectMQTTClient` hinzu.

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    Diese Funktion wird der Callback sein, den der MQTT-Client aufruft, wenn er eine Nachricht vom Server empfängt.

    Die Nachricht wird als ein Array von unsignierten 8-Bit-Integern empfangen und muss in ein Zeichen-Array umgewandelt werden, um als Text behandelt zu werden.

    Die Nachricht enthält ein JSON-Dokument und wird mit der ArduinoJson-Bibliothek dekodiert. Die Eigenschaft `led_on` des JSON-Dokuments wird ausgelesen, und je nach Wert wird die LED ein- oder ausgeschaltet.

1. Fügen Sie den folgenden Code zur Funktion `createMQTTClient` hinzu:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Dieser Code setzt den `clientCallback` als Callback, der aufgerufen wird, wenn eine Nachricht vom MQTT-Broker empfangen wird.

    > 💁 Der `clientCallback`-Handler wird für alle abonnierten Themen aufgerufen. Wenn Sie später Code schreiben, der auf mehrere Themen hört, können Sie das Thema, zu dem die Nachricht gesendet wurde, aus dem Parameter `topic` abrufen, der an den Callback übergeben wird.

1. Laden Sie den Code auf Ihr Wio Terminal hoch und verwenden Sie den Serial Monitor, um die Lichtwerte zu sehen, die an den MQTT-Broker gesendet werden.

1. Passen Sie die Lichtwerte an, die von Ihrem physischen oder virtuellen Gerät erkannt werden. Sie werden sehen, wie Nachrichten empfangen und Befehle im Terminal gesendet werden. Außerdem sehen Sie, wie die LED je nach Lichtwert ein- oder ausgeschaltet wird.

> 💁 Sie finden diesen Code im Ordner [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Sie haben Ihr Gerät erfolgreich programmiert, um auf Befehle von einem MQTT-Broker zu reagieren.

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.