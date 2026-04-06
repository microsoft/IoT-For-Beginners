# Baue ein Nachtlicht - Virtuelle IoT-Hardware

In diesem Teil der Lektion fügen Sie Ihrem virtuellen IoT-Gerät einen Lichtsensor hinzu.

## Virtuelle Hardware

Das Nachtlicht benötigt einen Sensor, der in der CounterFit-App erstellt wird.

Der Sensor ist ein **Lichtsensor**. In einem physischen IoT-Gerät wäre dies eine [Photodiode](https://wikipedia.org/wiki/Photodiode), die Licht in ein elektrisches Signal umwandelt. Lichtsensoren sind analoge Sensoren, die einen ganzzahligen Wert senden, der eine relative Lichtmenge angibt, jedoch nicht mit einer standardisierten Maßeinheit wie [Lux](https://wikipedia.org/wiki/Lux) übereinstimmt.

### Sensoren zu CounterFit hinzufügen

Um einen virtuellen Lichtsensor zu verwenden, müssen Sie ihn zur CounterFit-App hinzufügen.

#### Aufgabe - Sensoren zu CounterFit hinzufügen

Fügen Sie den Lichtsensor zur CounterFit-App hinzu.

1. Stellen Sie sicher, dass die CounterFit-Web-App aus dem vorherigen Teil dieser Aufgabe läuft. Falls nicht, starten Sie sie.

1. Erstellen Sie einen Lichtsensor:

    1. Im Feld *Create sensor* im Bereich *Sensors* öffnen Sie das Dropdown-Menü *Sensor type* und wählen *Light* aus.

    1. Lassen Sie die *Units* auf *NoUnits* eingestellt.

    1. Stellen Sie sicher, dass die *Pin*-Einstellung auf *0* gesetzt ist.

    1. Wählen Sie die Schaltfläche **Add**, um den Lichtsensor auf Pin 0 zu erstellen.

    ![Die Einstellungen des Lichtsensors](../../../../../translated_images/de/counterfit-create-light-sensor.9f36a5e0d4458d8d.webp)

    Der Lichtsensor wird erstellt und erscheint in der Sensorenliste.

    ![Der erstellte Lichtsensor](../../../../../translated_images/de/counterfit-light-sensor.5d0f5584df56b90f.webp)

## Den Lichtsensor programmieren

Das Gerät kann jetzt so programmiert werden, dass es den eingebauten Lichtsensor verwendet.

### Aufgabe - Den Lichtsensor programmieren

Programmieren Sie das Gerät.

1. Öffnen Sie das Nachtlicht-Projekt in VS Code, das Sie im vorherigen Teil dieser Aufgabe erstellt haben. Beenden und starten Sie das Terminal neu, um sicherzustellen, dass es bei Bedarf mit der virtuellen Umgebung läuft.

1. Öffnen Sie die Datei `app.py`.

1. Fügen Sie den folgenden Code oben in die Datei `app.py` ein, zusammen mit den anderen `import`-Anweisungen, um einige benötigte Bibliotheken zu importieren:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Die Anweisung `import time` importiert das Python-Modul `time`, das später in dieser Aufgabe verwendet wird.

    Die Anweisung `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` importiert den `GroveLightSensor` aus den CounterFit Grove Shim Python-Bibliotheken. Diese Bibliothek enthält Code, um mit einem in der CounterFit-App erstellten Lichtsensor zu interagieren.

1. Fügen Sie den folgenden Code am Ende der Datei ein, um Instanzen von Klassen zu erstellen, die den Lichtsensor verwalten:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Die Zeile `light_sensor = GroveLightSensor(0)` erstellt eine Instanz der Klasse `GroveLightSensor`, die mit Pin **0** verbunden ist - dem CounterFit Grove-Pin, an den der Lichtsensor angeschlossen ist.

1. Fügen Sie eine Endlosschleife nach dem obigen Code hinzu, um den Wert des Lichtsensors abzufragen und ihn in der Konsole auszugeben:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Dies liest den aktuellen Lichtwert mithilfe der Eigenschaft `light` der Klasse `GroveLightSensor`. Diese Eigenschaft liest den analogen Wert vom Pin. Dieser Wert wird dann in der Konsole ausgegeben.

1. Fügen Sie am Ende der `while`-Schleife eine kurze Pause von einer Sekunde hinzu, da die Lichtwerte nicht kontinuierlich überprüft werden müssen. Eine Pause reduziert den Stromverbrauch des Geräts.

    ```python
    time.sleep(1)
    ```

1. Führen Sie im VS Code-Terminal den folgenden Befehl aus, um Ihre Python-App auszuführen:

    ```sh
    python3 app.py
    ```

    Lichtwerte werden in der Konsole ausgegeben. Anfangs wird dieser Wert 0 sein.

1. Ändern Sie in der CounterFit-App den Wert des Lichtsensors, der von der App gelesen wird. Sie können dies auf zwei Arten tun:

    * Geben Sie eine Zahl in das Feld *Value* für den Lichtsensor ein und wählen Sie die Schaltfläche **Set**. Die eingegebene Zahl wird der Wert sein, den der Sensor zurückgibt.

    * Aktivieren Sie das Kontrollkästchen *Random* und geben Sie einen *Min*- und *Max*-Wert ein, dann wählen Sie die Schaltfläche **Set**. Jedes Mal, wenn der Sensor einen Wert liest, wird eine Zufallszahl zwischen *Min* und *Max* gelesen.

    Die von Ihnen festgelegten Werte werden in der Konsole ausgegeben. Ändern Sie die *Value*- oder *Random*-Einstellungen, um den Wert zu ändern.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Sie finden diesen Code im Ordner [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 Ihr Nachtlicht-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.