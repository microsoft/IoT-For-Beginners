<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-25T22:09:23+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "de"
}
-->
# Einen Sensor hinzufügen - Wio Terminal

In diesem Teil der Lektion wirst du den Lichtsensor deines Wio Terminals verwenden.

## Hardware

Der Sensor für diese Lektion ist ein **Lichtsensor**, der eine [Photodiode](https://wikipedia.org/wiki/Photodiode) verwendet, um Licht in ein elektrisches Signal umzuwandeln. Es handelt sich um einen analogen Sensor, der einen ganzzahligen Wert von 0 bis 1.023 sendet, der eine relative Lichtmenge angibt. Dieser Wert entspricht keiner standardisierten Maßeinheit wie [Lux](https://wikipedia.org/wiki/Lux).

Der Lichtsensor ist im Wio Terminal integriert und durch das klare Kunststofffenster auf der Rückseite sichtbar.

![Der Lichtsensor auf der Rückseite des Wio Terminals](../../../../../translated_images/wio-light-sensor.b1f529f3c95f5165.de.png)

## Den Lichtsensor programmieren

Das Gerät kann nun so programmiert werden, dass es den eingebauten Lichtsensor verwendet.

### Aufgabe

Programmiere das Gerät.

1. Öffne das Nightlight-Projekt in VS Code, das du im vorherigen Teil dieser Aufgabe erstellt hast.

1. Füge die folgende Zeile am Ende der `setup`-Funktion hinzu:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Diese Zeile konfiguriert die Pins, die zur Kommunikation mit der Sensor-Hardware verwendet werden.

    Der `WIO_LIGHT`-Pin ist die Nummer des GPIO-Pins, der mit dem eingebauten Lichtsensor verbunden ist. Dieser Pin wird auf `INPUT` gesetzt, was bedeutet, dass er mit einem Sensor verbunden ist und Daten von diesem Pin gelesen werden.

1. Lösche den Inhalt der `loop`-Funktion.

1. Füge den folgenden Code in die nun leere `loop`-Funktion ein.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Dieser Code liest einen analogen Wert vom `WIO_LIGHT`-Pin. Dabei wird ein Wert von 0 bis 1.023 vom eingebauten Lichtsensor gelesen. Dieser Wert wird dann an den seriellen Port gesendet, sodass du ihn im Serial Monitor lesen kannst, während dieser Code ausgeführt wird. `Serial.print` schreibt den Text ohne eine neue Zeile am Ende, sodass jede Zeile mit `Light value:` beginnt und mit dem tatsächlichen Lichtwert endet.

1. Füge am Ende der `loop`-Funktion eine kleine Verzögerung von einer Sekunde (1.000 ms) hinzu, da die Lichtwerte nicht kontinuierlich überprüft werden müssen. Eine Verzögerung reduziert den Stromverbrauch des Geräts.

    ```cpp
    delay(1000);
    ```

1. Verbinde das Wio Terminal erneut mit deinem Computer und lade den neuen Code hoch, wie du es zuvor getan hast.

1. Öffne den Serial Monitor. Die Lichtwerte werden im Terminal ausgegeben. Bedecke und enthülle den Lichtsensor auf der Rückseite des Wio Terminals, und die Werte werden sich ändern.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 Du findest diesen Code im Ordner [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 Das Hinzufügen eines Sensors zu deinem Nightlight-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.