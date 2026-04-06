# Temperatur messen - Raspberry Pi

In diesem Teil der Lektion fügen Sie Ihrem Raspberry Pi einen Temperatursensor hinzu.

## Hardware

Der Sensor, den Sie verwenden werden, ist ein [DHT11 Feuchtigkeits- und Temperatursensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), der zwei Sensoren in einem Gehäuse kombiniert. Dieser Sensor ist recht beliebt, und es gibt viele kommerziell erhältliche Sensoren, die Temperatur, Feuchtigkeit und manchmal auch den Luftdruck messen können. Die Temperaturkomponente des Sensors ist ein Thermistor mit negativem Temperaturkoeffizienten (NTC), ein Thermistor, bei dem der Widerstand mit steigender Temperatur abnimmt.

Es handelt sich um einen digitalen Sensor, der über einen integrierten ADC (Analog-Digital-Wandler) verfügt, um ein digitales Signal zu erzeugen, das die Temperatur- und Feuchtigkeitsdaten enthält, die der Mikrocontroller auslesen kann.

### Temperatursensor anschließen

Der Grove-Temperatursensor kann mit dem Raspberry Pi verbunden werden.

#### Aufgabe

Schließen Sie den Temperatursensor an.

![Ein Grove-Temperatursensor](../../../../../translated_images/de/grove-dht11.07f8eafceee17004.webp)

1. Stecken Sie ein Ende eines Grove-Kabels in die Buchse des Feuchtigkeits- und Temperatursensors. Es passt nur in einer Richtung.

1. Schalten Sie den Raspberry Pi aus und verbinden Sie das andere Ende des Grove-Kabels mit der digitalen Buchse, die mit **D5** auf dem Grove Base Hat des Pi markiert ist. Diese Buchse ist die zweite von links in der Reihe der Buchsen neben den GPIO-Pins.

![Der Grove-Temperatursensor ist mit der Buchse A0 verbunden](../../../../../translated_images/de/pi-temperature-sensor.3ff82fff672c8e56.webp)

## Temperatursensor programmieren

Das Gerät kann nun programmiert werden, um den angeschlossenen Temperatursensor zu verwenden.

### Aufgabe

Programmieren Sie das Gerät.

1. Schalten Sie den Pi ein und warten Sie, bis er hochgefahren ist.

1. Starten Sie VS Code, entweder direkt auf dem Pi oder über die Remote SSH-Erweiterung.

    > ⚠️ Sie können [die Anweisungen zum Einrichten und Starten von VS Code in Lektion 1 bei Bedarf nachlesen](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Erstellen Sie im Terminal einen neuen Ordner im Home-Verzeichnis des Benutzers `pi` mit dem Namen `temperature-sensor`. Erstellen Sie in diesem Ordner eine Datei mit dem Namen `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Öffnen Sie diesen Ordner in VS Code.

1. Um den Feuchtigkeits- und Temperatursensor zu verwenden, muss ein zusätzliches Pip-Paket installiert werden. Führen Sie im Terminal von VS Code den folgenden Befehl aus, um dieses Pip-Paket auf dem Pi zu installieren:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Fügen Sie der Datei `app.py` den folgenden Code hinzu, um die erforderlichen Bibliotheken zu importieren:

    ```python
    import time
    from seeed_dht import DHT
    ```

    Die Anweisung `from seeed_dht import DHT` importiert die `DHT`-Sensor-Klasse, um mit einem Grove-Temperatursensor aus dem Modul `seeed_dht` zu interagieren.

1. Fügen Sie nach dem obigen Code den folgenden Code hinzu, um eine Instanz der Klasse zu erstellen, die den Temperatursensor verwaltet:

    ```python
    sensor = DHT("11", 5)
    ```

    Dies deklariert eine Instanz der `DHT`-Klasse, die den **D**igitalen **H**umidity- und **T**emperature-Sensor verwaltet. Der erste Parameter gibt an, dass der verwendete Sensor der *DHT11*-Sensor ist – die Bibliothek, die Sie verwenden, unterstützt andere Varianten dieses Sensors. Der zweite Parameter gibt an, dass der Sensor mit dem digitalen Port `D5` auf dem Grove Base Hat verbunden ist.

    > ✅ Denken Sie daran, dass alle Buchsen eindeutige Pin-Nummern haben. Pins 0, 2, 4 und 6 sind analoge Pins, Pins 5, 16, 18, 22, 24 und 26 sind digitale Pins.

1. Fügen Sie nach dem obigen Code eine Endlosschleife hinzu, um den Wert des Temperatursensors abzufragen und ihn in der Konsole auszugeben:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Der Aufruf von `sensor.read()` gibt ein Tupel mit Feuchtigkeits- und Temperaturwerten zurück. Sie benötigen nur den Temperaturwert, daher wird die Feuchtigkeit ignoriert. Der Temperaturwert wird dann in der Konsole ausgegeben.

1. Fügen Sie am Ende der Schleife eine kurze Pause von zehn Sekunden hinzu, da die Temperaturwerte nicht kontinuierlich überprüft werden müssen. Eine Pause reduziert den Stromverbrauch des Geräts.

    ```python
    time.sleep(10)
    ```

1. Führen Sie im VS Code Terminal den folgenden Befehl aus, um Ihre Python-App auszuführen:

    ```sh
    python3 app.py
    ```

    Sie sollten sehen, wie Temperaturwerte in der Konsole ausgegeben werden. Verwenden Sie etwas, um den Sensor zu erwärmen, z. B. indem Sie Ihren Daumen darauf drücken oder einen Ventilator verwenden, um zu sehen, wie sich die Werte ändern:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Sie finden diesen Code im Ordner [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi).

😀 Ihr Programm für den Temperatursensor war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.