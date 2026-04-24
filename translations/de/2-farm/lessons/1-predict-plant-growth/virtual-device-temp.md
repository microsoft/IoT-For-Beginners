# Temperatur messen - Virtuelle IoT-Hardware

In diesem Teil der Lektion fügen Sie Ihrem virtuellen IoT-Gerät einen Temperatursensor hinzu.

## Virtuelle Hardware

Das virtuelle IoT-Gerät verwendet einen simulierten Grove Digital Humidity and Temperature Sensor. Dies hält das Labor identisch mit der Verwendung eines Raspberry Pi mit einem physischen Grove DHT11-Sensor.

Der Sensor kombiniert einen **Temperatursensor** mit einem **Feuchtigkeitssensor**, aber in diesem Labor konzentrieren Sie sich nur auf die Komponente des Temperatursensors. In einem physischen IoT-Gerät wäre der Temperatursensor ein [Thermistor](https://wikipedia.org/wiki/Thermistor), der die Temperatur misst, indem er eine Änderung des Widerstands bei Temperaturänderungen erkennt. Temperatursensoren sind normalerweise digitale Sensoren, die den gemessenen Widerstand intern in eine Temperatur in Grad Celsius (oder Kelvin oder Fahrenheit) umwandeln.

### Sensoren zu CounterFit hinzufügen

Um einen virtuellen Feuchtigkeits- und Temperatursensor zu verwenden, müssen Sie die beiden Sensoren zur CounterFit-App hinzufügen.

#### Aufgabe - Sensoren zu CounterFit hinzufügen

Fügen Sie die Feuchtigkeits- und Temperatursensoren zur CounterFit-App hinzu.

1. Erstellen Sie eine neue Python-App auf Ihrem Computer in einem Ordner namens `temperature-sensor` mit einer einzigen Datei namens `app.py` und einer Python-virtuellen Umgebung, und fügen Sie die CounterFit-Pip-Pakete hinzu.

    > ⚠️ Sie können sich bei Bedarf auf [die Anweisungen zum Erstellen und Einrichten eines CounterFit-Python-Projekts in Lektion 1](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md) beziehen.

1. Installieren Sie ein zusätzliches Pip-Paket, um einen CounterFit-Shim für den DHT11-Sensor zu installieren. Stellen Sie sicher, dass Sie dies von einem Terminal mit aktivierter virtueller Umgebung aus installieren.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Stellen Sie sicher, dass die CounterFit-Web-App läuft.

1. Erstellen Sie einen Feuchtigkeitssensor:

    1. Im *Create sensor*-Feld im *Sensors*-Bereich, öffnen Sie das Dropdown-Menü *Sensor type* und wählen Sie *Humidity*.

    1. Lassen Sie die *Units* auf *Percentage* eingestellt.

    1. Stellen Sie sicher, dass der *Pin* auf *5* gesetzt ist.

    1. Wählen Sie die Schaltfläche **Add**, um den Feuchtigkeitssensor auf Pin 5 zu erstellen.

    ![Die Einstellungen des Feuchtigkeitssensors](../../../../../translated_images/de/counterfit-create-humidity-sensor.2750e27b6f30e09c.webp)

    Der Feuchtigkeitssensor wird erstellt und erscheint in der Sensorenliste.

    ![Der erstellte Feuchtigkeitssensor](../../../../../translated_images/de/counterfit-humidity-sensor.7b12f7f339e430cb.webp)

1. Erstellen Sie einen Temperatursensor:

    1. Im *Create sensor*-Feld im *Sensors*-Bereich, öffnen Sie das Dropdown-Menü *Sensor type* und wählen Sie *Temperature*.

    1. Lassen Sie die *Units* auf *Celsius* eingestellt.

    1. Stellen Sie sicher, dass der *Pin* auf *6* gesetzt ist.

    1. Wählen Sie die Schaltfläche **Add**, um den Temperatursensor auf Pin 6 zu erstellen.

    ![Die Einstellungen des Temperatursensors](../../../../../translated_images/de/counterfit-create-temperature-sensor.199350ed34f7343d.webp)

    Der Temperatursensor wird erstellt und erscheint in der Sensorenliste.

    ![Der erstellte Temperatursensor](../../../../../translated_images/de/counterfit-temperature-sensor.f0560236c96a9016.webp)

## Programmieren der Temperatursensor-App

Die Temperatursensor-App kann nun mit den CounterFit-Sensoren programmiert werden.

### Aufgabe - Programmieren der Temperatursensor-App

Programmieren Sie die Temperatursensor-App.

1. Stellen Sie sicher, dass die `temperature-sensor`-App in VS Code geöffnet ist.

1. Öffnen Sie die Datei `app.py`.

1. Fügen Sie den folgenden Code oben in `app.py` ein, um die App mit CounterFit zu verbinden:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Fügen Sie den folgenden Code in die Datei `app.py` ein, um die erforderlichen Bibliotheken zu importieren:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    Die Anweisung `from seeed_dht import DHT` importiert die `DHT`-Sensor-Klasse, um mit einem virtuellen Grove-Temperatursensor über einen Shim aus dem Modul `counterfit_shims_seeed_python_dht` zu interagieren.

1. Fügen Sie den folgenden Code nach dem oben genannten Code ein, um eine Instanz der Klasse zu erstellen, die den virtuellen Feuchtigkeits- und Temperatursensor verwaltet:

    ```python
    sensor = DHT("11", 5)
    ```

    Dies deklariert eine Instanz der `DHT`-Klasse, die den virtuellen **D**igitalen **H**umidity- und **T**emperature-Sensor verwaltet. Der erste Parameter gibt an, dass der verwendete Sensor ein virtueller *DHT11*-Sensor ist. Der zweite Parameter gibt an, dass der Sensor an Port `5` angeschlossen ist.

    > 💁 CounterFit simuliert diesen kombinierten Feuchtigkeits- und Temperatursensor, indem es sich mit zwei Sensoren verbindet: einem Feuchtigkeitssensor an dem Pin, der bei der Erstellung der `DHT`-Klasse angegeben wird, und einem Temperatursensor, der am nächsten Pin läuft. Wenn der Feuchtigkeitssensor an Pin 5 ist, erwartet der Shim, dass der Temperatursensor an Pin 6 ist.

1. Fügen Sie eine Endlosschleife nach dem oben genannten Code ein, um den Wert des Temperatursensors abzufragen und ihn in der Konsole auszugeben:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Der Aufruf von `sensor.read()` gibt ein Tupel aus Feuchtigkeit und Temperatur zurück. Sie benötigen nur den Temperaturwert, daher wird die Feuchtigkeit ignoriert. Der Temperaturwert wird dann in der Konsole ausgegeben.

1. Fügen Sie am Ende der Schleife eine kurze Pause von zehn Sekunden ein, da die Temperaturwerte nicht kontinuierlich überprüft werden müssen. Eine Pause reduziert den Stromverbrauch des Geräts.

    ```python
    time.sleep(10)
    ```

1. Führen Sie im VS Code-Terminal mit aktivierter virtueller Umgebung den folgenden Befehl aus, um Ihre Python-App auszuführen:

    ```sh
    python app.py
    ```

1. Ändern Sie in der CounterFit-App den Wert des Temperatursensors, der von der App gelesen wird. Sie können dies auf zwei Arten tun:

    * Geben Sie eine Zahl in das *Value*-Feld des Temperatursensors ein und wählen Sie die Schaltfläche **Set**. Die eingegebene Zahl wird der Wert sein, den der Sensor zurückgibt.

    * Aktivieren Sie das *Random*-Kontrollkästchen und geben Sie einen *Min*- und *Max*-Wert ein, dann wählen Sie die Schaltfläche **Set**. Jedes Mal, wenn der Sensor einen Wert liest, wird eine Zufallszahl zwischen *Min* und *Max* gelesen.

    Sie sollten die von Ihnen festgelegten Werte in der Konsole sehen. Ändern Sie die *Value*- oder *Random*-Einstellungen, um den Wert zu ändern.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Sie finden diesen Code im Ordner [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device).

😀 Ihr Temperatursensor-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.