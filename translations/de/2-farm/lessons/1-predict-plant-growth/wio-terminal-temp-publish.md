<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-25T21:20:32+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "de"
}
-->
# Temperatur veröffentlichen - Wio Terminal

In diesem Teil der Lektion wirst du die vom Wio Terminal erkannten Temperaturwerte über MQTT veröffentlichen, damit sie später zur Berechnung der GDD verwendet werden können.

## Temperatur veröffentlichen

Sobald die Temperatur ausgelesen wurde, kann sie über MQTT an einen 'Server'-Code gesendet werden, der die Werte liest und speichert, um sie für eine GDD-Berechnung zu verwenden. Mikrocontroller lesen die Zeit nicht direkt aus dem Internet und verfolgen die Zeit nicht standardmäßig mit einer Echtzeituhr. Das Gerät muss entsprechend programmiert werden, vorausgesetzt, es verfügt über die notwendige Hardware.

Um die Dinge für diese Lektion zu vereinfachen, wird die Zeit nicht zusammen mit den Sensordaten gesendet. Stattdessen kann sie später vom Server-Code hinzugefügt werden, wenn die Nachrichten empfangen werden.

### Aufgabe

Programmiere das Gerät so, dass es die Temperaturdaten veröffentlicht.

1. Öffne das `temperature-sensor` Wio Terminal Projekt.

1. Wiederhole die Schritte aus Lektion 4, um eine Verbindung zu MQTT herzustellen und Telemetrie zu senden. Du wirst denselben öffentlichen Mosquitto-Broker verwenden.

    Die Schritte dafür sind:

    - Füge die Seeed WiFi- und MQTT-Bibliotheken zur `.ini`-Datei hinzu.
    - Füge die Konfigurationsdatei und den Code hinzu, um eine Verbindung zu WiFi herzustellen.
    - Füge den Code hinzu, um eine Verbindung zum MQTT-Broker herzustellen.
    - Füge den Code hinzu, um Telemetrie zu veröffentlichen.

    > ⚠️ Sieh dir die [Anleitung zur Verbindung mit MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) und die [Anleitung zum Senden von Telemetrie](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) aus Lektion 4 an, falls nötig.

1. Stelle sicher, dass der `CLIENT_NAME` in der `config.h` Header-Datei dieses Projekt widerspiegelt:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Für die Telemetrie: Anstatt einen Lichtwert zu senden, sende den Temperaturwert, der vom DHT-Sensor ausgelesen wurde, in einer Eigenschaft des JSON-Dokuments namens `temperature`, indem du die `loop`-Funktion in `main.cpp` änderst:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Der Temperaturwert muss nicht sehr häufig ausgelesen werden – er wird sich in kurzer Zeit nicht stark ändern. Setze daher die `delay`-Zeit in der `loop`-Funktion auf 10 Minuten:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 Die `delay`-Funktion nimmt die Zeit in Millisekunden. Um es einfacher zu machen, wird der Wert als Ergebnis einer Berechnung übergeben. 1.000ms in einer Sekunde, 60s in einer Minute, also ergibt 10 x (60s in einer Minute) x (1000ms in einer Sekunde) eine Verzögerung von 10 Minuten.

1. Lade dies auf dein Wio Terminal hoch und nutze den seriellen Monitor, um zu sehen, wie die Temperatur an den MQTT-Broker gesendet wird.

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

> 💁 Du findest diesen Code im [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) Ordner.

😀 Du hast erfolgreich die Temperatur als Telemetrie von deinem Gerät veröffentlicht.

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.