<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-25T21:54:45+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "de"
}
-->
# Steuern Sie Ihr Nachtlicht über das Internet - Virtuelle IoT-Hardware und Raspberry Pi

In diesem Teil der Lektion senden Sie Telemetriedaten mit Lichtwerten von Ihrem Raspberry Pi oder virtuellen IoT-Gerät an einen MQTT-Broker.

## Telemetrie veröffentlichen

Der nächste Schritt besteht darin, ein JSON-Dokument mit Telemetriedaten zu erstellen und an den MQTT-Broker zu senden.

### Aufgabe

Veröffentlichen Sie Telemetriedaten auf dem MQTT-Broker.

1. Öffnen Sie das Nachtlicht-Projekt in VS Code.

1. Wenn Sie ein virtuelles IoT-Gerät verwenden, stellen Sie sicher, dass das Terminal die virtuelle Umgebung ausführt. Wenn Sie einen Raspberry Pi verwenden, benötigen Sie keine virtuelle Umgebung.

1. Fügen Sie die folgende Import-Anweisung am Anfang der Datei `app.py` hinzu:

    ```python
    import json
    ```

    Die Bibliothek `json` wird verwendet, um die Telemetriedaten als JSON-Dokument zu kodieren.

1. Fügen Sie das Folgende nach der Deklaration von `client_name` hinzu:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    Das `client_telemetry_topic` ist das MQTT-Topic, auf dem das Gerät die Lichtwerte veröffentlichen wird.

1. Ersetzen Sie den Inhalt der Schleife `while True:` am Ende der Datei durch Folgendes:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Dieser Code verpackt den Lichtwert in ein JSON-Dokument und veröffentlicht ihn auf dem MQTT-Broker. Anschließend wird eine Pause eingelegt, um die Häufigkeit der gesendeten Nachrichten zu reduzieren.

1. Führen Sie den Code auf die gleiche Weise aus wie den Code aus dem vorherigen Teil der Aufgabe. Wenn Sie ein virtuelles IoT-Gerät verwenden, stellen Sie sicher, dass die CounterFit-App läuft und der Lichtsensor sowie die LED an den richtigen Pins erstellt wurden.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Sie finden diesen Code im Ordner [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) oder im Ordner [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Sie haben erfolgreich Telemetriedaten von Ihrem Gerät gesendet.

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.