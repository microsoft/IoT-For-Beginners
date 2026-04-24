# Bodenfeuchtigkeit messen - Virtuelle IoT-Hardware

In diesem Teil der Lektion fügen Sie Ihrem virtuellen IoT-Gerät einen kapazitiven Bodenfeuchtigkeitssensor hinzu und lesen Werte von diesem aus.

## Virtuelle Hardware

Das virtuelle IoT-Gerät verwendet einen simulierten Grove kapazitiven Bodenfeuchtigkeitssensor. Dies hält diese Übung identisch mit der Verwendung eines Raspberry Pi mit einem physischen Grove kapazitiven Bodenfeuchtigkeitssensor.

In einem physischen IoT-Gerät wäre der Bodenfeuchtigkeitssensor ein kapazitiver Sensor, der die Bodenfeuchtigkeit misst, indem er die Kapazität des Bodens erkennt – eine Eigenschaft, die sich mit der Bodenfeuchtigkeit ändert. Mit zunehmender Bodenfeuchtigkeit sinkt die Spannung.

Dies ist ein analoger Sensor, der einen simulierten 10-Bit-ADC verwendet, um einen Wert zwischen 1 und 1.023 zu melden.

### Den Bodenfeuchtigkeitssensor zu CounterFit hinzufügen

Um einen virtuellen Bodenfeuchtigkeitssensor zu verwenden, müssen Sie ihn zur CounterFit-App hinzufügen.

#### Aufgabe - Den Bodenfeuchtigkeitssensor zu CounterFit hinzufügen

Fügen Sie den Bodenfeuchtigkeitssensor zur CounterFit-App hinzu.

1. Erstellen Sie eine neue Python-App auf Ihrem Computer in einem Ordner namens `soil-moisture-sensor` mit einer einzigen Datei namens `app.py` und einer Python-virtuellen Umgebung, und fügen Sie die CounterFit-Pip-Pakete hinzu.

    > ⚠️ Sie können [die Anweisungen zum Erstellen und Einrichten eines CounterFit-Python-Projekts in Lektion 1 bei Bedarf nachlesen](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Stellen Sie sicher, dass die CounterFit-Web-App läuft.

1. Erstellen Sie einen Bodenfeuchtigkeitssensor:

    1. Wählen Sie im Feld *Create sensor* im Bereich *Sensors* im Dropdown-Menü *Sensor type* die Option *Soil Moisture* aus.

    1. Lassen Sie die *Units* auf *NoUnits* eingestellt.

    1. Stellen Sie sicher, dass der *Pin* auf *0* gesetzt ist.

    1. Wählen Sie die Schaltfläche **Add**, um den *Soil Moisture*-Sensor auf Pin 0 zu erstellen.

    ![Die Einstellungen des Bodenfeuchtigkeitssensors](../../../../../translated_images/de/counterfit-create-soil-moisture-sensor.35266135a5e0ae68.webp)

    Der Bodenfeuchtigkeitssensor wird erstellt und erscheint in der Sensorliste.

    ![Der erstellte Bodenfeuchtigkeitssensor](../../../../../translated_images/de/counterfit-soil-moisture-sensor.81742b2de0e9de60.webp)

## Das Bodenfeuchtigkeitssensor-Programm schreiben

Das Programm für den Bodenfeuchtigkeitssensor kann nun mit den CounterFit-Sensoren geschrieben werden.

### Aufgabe - Das Bodenfeuchtigkeitssensor-Programm schreiben

Schreiben Sie das Programm für den Bodenfeuchtigkeitssensor.

1. Stellen Sie sicher, dass die `soil-moisture-sensor`-App in VS Code geöffnet ist.

1. Öffnen Sie die Datei `app.py`.

1. Fügen Sie den folgenden Code am Anfang von `app.py` hinzu, um die App mit CounterFit zu verbinden:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Fügen Sie den folgenden Code in die Datei `app.py` ein, um einige erforderliche Bibliotheken zu importieren:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    Die Anweisung `import time` importiert das `time`-Modul, das später in dieser Aufgabe verwendet wird.

    Die Anweisung `from counterfit_shims_grove.adc import ADC` importiert die `ADC`-Klasse, um mit einem virtuellen Analog-Digital-Wandler zu interagieren, der mit einem CounterFit-Sensor verbunden werden kann.

1. Fügen Sie den folgenden Code darunter ein, um eine Instanz der `ADC`-Klasse zu erstellen:

    ```python
    adc = ADC()
    ```

1. Fügen Sie eine Endlosschleife hinzu, die von diesem ADC auf Pin 0 liest und das Ergebnis in die Konsole schreibt. Diese Schleife kann dann 10 Sekunden zwischen den Lesevorgängen pausieren.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. Ändern Sie in der CounterFit-App den Wert des Bodenfeuchtigkeitssensors, der von der App gelesen wird. Sie können dies auf zwei Arten tun:

    * Geben Sie eine Zahl in das Feld *Value* des Bodenfeuchtigkeitssensors ein und klicken Sie auf die Schaltfläche **Set**. Die eingegebene Zahl wird der vom Sensor zurückgegebene Wert sein.

    * Aktivieren Sie das Kontrollkästchen *Random* und geben Sie einen *Min*- und *Max*-Wert ein, und klicken Sie dann auf die Schaltfläche **Set**. Jedes Mal, wenn der Sensor einen Wert liest, wird eine Zufallszahl zwischen *Min* und *Max* gelesen.

1. Führen Sie die Python-App aus. Sie werden die Bodenfeuchtigkeitsmessungen in der Konsole sehen. Ändern Sie den *Value*- oder die *Random*-Einstellungen, um die Werte zu ändern.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Sie finden diesen Code im Ordner [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device).

😀 Ihr Bodenfeuchtigkeitssensor-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.