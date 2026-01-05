<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-25T21:41:30+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "de"
}
-->
# Bodenfeuchtigkeit messen - Raspberry Pi

In diesem Teil der Lektion fügen Sie Ihrem Raspberry Pi einen kapazitiven Bodenfeuchtigkeitssensor hinzu und lesen Werte von diesem aus.

## Hardware

Der Raspberry Pi benötigt einen kapazitiven Bodenfeuchtigkeitssensor.

Der Sensor, den Sie verwenden, ist ein [Kapazitiver Bodenfeuchtigkeitssensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), der die Bodenfeuchtigkeit misst, indem er die Kapazität des Bodens erkennt – eine Eigenschaft, die sich mit der Bodenfeuchtigkeit ändert. Mit zunehmender Bodenfeuchtigkeit sinkt die Spannung.

Dies ist ein analoger Sensor, der einen analogen Pin verwendet und den 10-Bit-ADC im Grove Base Hat auf dem Raspberry Pi nutzt, um die Spannung in ein digitales Signal von 1 bis 1.023 umzuwandeln. Dieses Signal wird dann über die GPIO-Pins des Raspberry Pi per I²C übertragen.

### Den Bodenfeuchtigkeitssensor anschließen

Der Grove-Bodenfeuchtigkeitssensor kann an den Raspberry Pi angeschlossen werden.

#### Aufgabe - Bodenfeuchtigkeitssensor anschließen

Schließen Sie den Bodenfeuchtigkeitssensor an.

![Ein Grove-Bodenfeuchtigkeitssensor](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.de.png)

1. Stecken Sie ein Ende eines Grove-Kabels in die Buchse des Bodenfeuchtigkeitssensors. Es passt nur in einer Richtung.

1. Schalten Sie den Raspberry Pi aus und verbinden Sie das andere Ende des Grove-Kabels mit der analogen Buchse, die mit **A0** auf dem Grove Base Hat des Raspberry Pi markiert ist. Diese Buchse befindet sich in der zweiten Position von rechts in der Reihe der Buchsen neben den GPIO-Pins.

![Der Grove-Bodenfeuchtigkeitssensor, angeschlossen an die A0-Buchse](../../../../../translated_images/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.de.png)

1. Stecken Sie den Bodenfeuchtigkeitssensor in die Erde. Der Sensor hat eine Markierung für die maximale Einstecktiefe – eine weiße Linie quer über den Sensor. Stecken Sie den Sensor bis zu dieser Linie, aber nicht darüber hinaus, in die Erde.

![Der Grove-Bodenfeuchtigkeitssensor in der Erde](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.de.png)

## Den Bodenfeuchtigkeitssensor programmieren

Der Raspberry Pi kann nun programmiert werden, um den angeschlossenen Bodenfeuchtigkeitssensor zu verwenden.

### Aufgabe - Bodenfeuchtigkeitssensor programmieren

Programmieren Sie das Gerät.

1. Schalten Sie den Raspberry Pi ein und warten Sie, bis er hochgefahren ist.

1. Starten Sie VS Code, entweder direkt auf dem Raspberry Pi oder über die Remote-SSH-Erweiterung.

    > ⚠️ Sie können [die Anweisungen zum Einrichten und Starten von VS Code in Nightlight - Lektion 1](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md) bei Bedarf nachlesen.

1. Erstellen Sie im Terminal einen neuen Ordner im Home-Verzeichnis des Benutzers `pi` mit dem Namen `soil-moisture-sensor`. Erstellen Sie in diesem Ordner eine Datei mit dem Namen `app.py`.

1. Öffnen Sie diesen Ordner in VS Code.

1. Fügen Sie der Datei `app.py` den folgenden Code hinzu, um die benötigten Bibliotheken zu importieren:

    ```python
    import time
    from grove.adc import ADC
    ```

    Die Anweisung `import time` importiert das Modul `time`, das später in dieser Aufgabe verwendet wird.

    Die Anweisung `from grove.adc import ADC` importiert den `ADC` aus den Grove-Python-Bibliotheken. Diese Bibliothek enthält Code, um mit dem Analog-Digital-Wandler auf dem Pi Base Hat zu interagieren und Spannungen von analogen Sensoren auszulesen.

1. Fügen Sie den folgenden Code hinzu, um eine Instanz der Klasse `ADC` zu erstellen:

    ```python
    adc = ADC()
    ```

1. Fügen Sie eine Endlosschleife hinzu, die den ADC am A0-Pin ausliest und das Ergebnis in die Konsole schreibt. Diese Schleife kann dann zwischen den Messungen 10 Sekunden pausieren.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Führen Sie die Python-App aus. Sie sehen die Bodenfeuchtigkeitsmessungen in der Konsole. Geben Sie etwas Wasser in die Erde oder entfernen Sie den Sensor aus der Erde und beobachten Sie, wie sich der Wert ändert.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    Im obigen Beispielausgang können Sie sehen, wie die Spannung sinkt, wenn Wasser hinzugefügt wird.

> 💁 Sie finden diesen Code im Ordner [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi).

😀 Ihr Programm für den Bodenfeuchtigkeitssensor war erfolgreich!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.