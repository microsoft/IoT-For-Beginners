<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-25T21:59:49+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "de"
}
-->
# Steuern Sie Ihr Nachtlicht über das Internet - Virtuelle IoT-Hardware und Raspberry Pi

Das IoT-Gerät muss so programmiert werden, dass es über MQTT mit *test.mosquitto.org* kommuniziert, um Telemetriedaten mit den Lichtsensorwerten zu senden und Befehle zum Steuern der LED zu empfangen.

In diesem Teil der Lektion verbinden Sie Ihren Raspberry Pi oder Ihr virtuelles IoT-Gerät mit einem MQTT-Broker.

## Installieren Sie das MQTT-Client-Paket

Um mit dem MQTT-Broker zu kommunizieren, müssen Sie ein MQTT-Bibliothek-Pip-Paket entweder auf Ihrem Pi oder in Ihrer virtuellen Umgebung installieren, falls Sie ein virtuelles Gerät verwenden.

### Aufgabe

Installieren Sie das Pip-Paket.

1. Öffnen Sie das Nachtlicht-Projekt in VS Code.

1. Falls Sie ein virtuelles IoT-Gerät verwenden, stellen Sie sicher, dass das Terminal die virtuelle Umgebung ausführt. Wenn Sie einen Raspberry Pi verwenden, arbeiten Sie nicht mit einer virtuellen Umgebung.

1. Führen Sie den folgenden Befehl aus, um das MQTT-Pip-Paket zu installieren:

    ```sh
    pip3 install paho-mqtt
    ```

## Programmieren Sie das Gerät

Das Gerät ist bereit für die Programmierung.

### Aufgabe

Schreiben Sie den Code für das Gerät.

1. Fügen Sie die folgende Import-Anweisung oben in die Datei `app.py` ein:

    ```python
    import paho.mqtt.client as mqtt
    ```

    Die Bibliothek `paho.mqtt.client` ermöglicht Ihrer App die Kommunikation über MQTT.

1. Fügen Sie den folgenden Code nach den Definitionen des Lichtensors und der LED ein:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Ersetzen Sie `<ID>` durch eine eindeutige ID, die als Name dieses Geräte-Clients verwendet wird und später für die Themen, die dieses Gerät veröffentlicht und abonniert. Der Broker *test.mosquitto.org* ist öffentlich und wird von vielen Menschen genutzt, einschließlich anderer Schüler, die diese Aufgabe bearbeiten. Eine eindeutige MQTT-Client-ID und eindeutige Themen-Namen stellen sicher, dass Ihr Code nicht mit dem anderer kollidiert. Sie benötigen diese ID auch, wenn Sie später den Server-Code für diese Aufgabe erstellen.

    > 💁 Sie können eine Website wie [GUIDGen](https://www.guidgen.com) verwenden, um eine eindeutige ID zu generieren.

    Der `client_name` ist ein eindeutiger Name für diesen MQTT-Client auf dem Broker.

1. Fügen Sie den folgenden Code unterhalb dieses neuen Codes ein, um ein MQTT-Client-Objekt zu erstellen und sich mit dem MQTT-Broker zu verbinden:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Dieser Code erstellt das Client-Objekt, verbindet sich mit dem öffentlichen MQTT-Broker und startet eine Verarbeitungsschleife, die in einem Hintergrund-Thread läuft und Nachrichten auf abonnierten Themen empfängt.

1. Führen Sie den Code auf die gleiche Weise aus wie den Code aus dem vorherigen Teil der Aufgabe. Falls Sie ein virtuelles IoT-Gerät verwenden, stellen Sie sicher, dass die CounterFit-App läuft und der Lichtsensor sowie die LED auf den richtigen Pins erstellt wurden.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Sie finden diesen Code im Ordner [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) oder im Ordner [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Sie haben Ihr Gerät erfolgreich mit einem MQTT-Broker verbunden.

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.