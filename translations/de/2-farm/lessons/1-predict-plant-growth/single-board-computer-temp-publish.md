<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-25T21:18:28+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "de"
}
-->
# Temperatur veröffentlichen - Virtuelle IoT-Hardware und Raspberry Pi

In diesem Teil der Lektion wirst du die vom Raspberry Pi oder virtuellen IoT-Gerät erkannten Temperaturwerte über MQTT veröffentlichen, damit sie später zur Berechnung der GDD verwendet werden können.

## Temperatur veröffentlichen

Sobald die Temperatur ausgelesen wurde, kann sie über MQTT an einen 'Server'-Code gesendet werden, der die Werte liest und speichert, um sie für eine GDD-Berechnung zu verwenden.

### Aufgabe - Temperatur veröffentlichen

Programmiere das Gerät so, dass es die Temperaturdaten veröffentlicht.

1. Öffne das Projekt der App `temperature-sensor`, falls es noch nicht geöffnet ist.

1. Wiederhole die Schritte aus Lektion 4, um eine Verbindung zu MQTT herzustellen und Telemetrie zu senden. Du wirst denselben öffentlichen Mosquitto-Broker verwenden.

    Die Schritte dafür sind:

    - Füge das MQTT-Pip-Paket hinzu
    - Füge den Code hinzu, um eine Verbindung zum MQTT-Broker herzustellen
    - Füge den Code hinzu, um Telemetrie zu veröffentlichen

    > ⚠️ Sieh dir die [Anleitung zur Verbindung mit MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) und die [Anleitung zum Senden von Telemetrie](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) aus Lektion 4 an, falls nötig.

1. Stelle sicher, dass der `client_name` den Namen dieses Projekts widerspiegelt:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Für die Telemetrie: Anstatt einen Lichtwert zu senden, sende den vom DHT-Sensor ausgelesenen Temperaturwert in einer Eigenschaft des JSON-Dokuments namens `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Der Temperaturwert muss nicht sehr häufig ausgelesen werden – er wird sich in kurzer Zeit nicht stark ändern. Setze daher `time.sleep` auf 10 Minuten:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Die Funktion `sleep` nimmt die Zeit in Sekunden. Um es leichter lesbar zu machen, wird der Wert als Ergebnis einer Berechnung übergeben. 60 Sekunden in einer Minute, also ergibt 10 x (60 Sekunden in einer Minute) eine Verzögerung von 10 Minuten.

1. Führe den Code auf die gleiche Weise aus wie den Code aus dem vorherigen Teil der Aufgabe. Wenn du ein virtuelles IoT-Gerät verwendest, stelle sicher, dass die CounterFit-App läuft und die Feuchtigkeits- und Temperatursensoren an den richtigen Pins erstellt wurden.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Du findest diesen Code im Ordner [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) oder im Ordner [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Du hast die Temperatur erfolgreich als Telemetrie von deinem Gerät veröffentlicht.

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.