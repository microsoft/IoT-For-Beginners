<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-25T21:39:22+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "de"
}
-->
# Bodenfeuchtigkeit messen - Wio Terminal

In diesem Teil der Lektion fügen Sie einen kapazitiven Bodenfeuchtigkeitssensor zu Ihrem Wio Terminal hinzu und lesen Werte von ihm aus.

## Hardware

Das Wio Terminal benötigt einen kapazitiven Bodenfeuchtigkeitssensor.

Der Sensor, den Sie verwenden, ist ein [Kapazitiver Bodenfeuchtigkeitssensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), der die Bodenfeuchtigkeit misst, indem er die Kapazität des Bodens erkennt – eine Eigenschaft, die sich mit der Bodenfeuchtigkeit verändert. Je höher die Bodenfeuchtigkeit, desto niedriger die Spannung.

Dies ist ein analoger Sensor, der an die analogen Pins des Wio Terminals angeschlossen wird und mithilfe eines integrierten ADC einen Wert zwischen 0 und 1.023 erzeugt.

### Bodenfeuchtigkeitssensor anschließen

Der Grove Bodenfeuchtigkeitssensor kann an den konfigurierbaren Analog-/Digital-Port des Wio Terminals angeschlossen werden.

#### Aufgabe - Bodenfeuchtigkeitssensor anschließen

Schließen Sie den Bodenfeuchtigkeitssensor an.

![Ein Grove Bodenfeuchtigkeitssensor](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.de.png)

1. Stecken Sie ein Ende eines Grove-Kabels in die Buchse des Bodenfeuchtigkeitssensors. Es passt nur in einer Richtung hinein.

1. Verbinden Sie, während das Wio Terminal von Ihrem Computer oder einer anderen Stromquelle getrennt ist, das andere Ende des Grove-Kabels mit der rechten Grove-Buchse des Wio Terminals, wenn Sie auf den Bildschirm schauen. Dies ist die Buchse, die am weitesten vom Netzschalter entfernt ist.

![Der Grove Bodenfeuchtigkeitssensor ist mit der rechten Buchse verbunden](../../../../../translated_images/wio-soil-moisture-sensor.46919b61c3f6cb74.de.png)

1. Stecken Sie den Bodenfeuchtigkeitssensor in die Erde. Er hat eine „höchste Position“-Markierung – eine weiße Linie quer über den Sensor. Stecken Sie den Sensor bis zu dieser Linie, aber nicht darüber hinaus, in die Erde.

![Der Grove Bodenfeuchtigkeitssensor in der Erde](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.de.png)

1. Sie können das Wio Terminal jetzt mit Ihrem Computer verbinden.

## Bodenfeuchtigkeitssensor programmieren

Das Wio Terminal kann jetzt so programmiert werden, dass es den angeschlossenen Bodenfeuchtigkeitssensor verwendet.

### Aufgabe - Bodenfeuchtigkeitssensor programmieren

Programmieren Sie das Gerät.

1. Erstellen Sie ein brandneues Wio Terminal-Projekt mit PlatformIO. Nennen Sie dieses Projekt `soil-moisture-sensor`. Fügen Sie Code in die `setup`-Funktion ein, um die serielle Schnittstelle zu konfigurieren.

    > ⚠️ Sie können [die Anleitung zum Erstellen eines PlatformIO-Projekts in Projekt 1, Lektion 1 bei Bedarf](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project) nachlesen.

1. Es gibt keine Bibliothek für diesen Sensor. Stattdessen können Sie die Werte vom analogen Pin mit der eingebauten Arduino-Funktion [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) auslesen. Beginnen Sie damit, den analogen Pin für die Eingabe zu konfigurieren, damit Werte von ihm gelesen werden können, indem Sie Folgendes zur `setup`-Funktion hinzufügen:

    ```cpp
    pinMode(A0, INPUT);
    ```

    Dies setzt den `A0`-Pin, den kombinierten Analog-/Digital-Pin, als Eingabepin, von dem die Spannung gelesen werden kann.

1. Fügen Sie Folgendes zur `loop`-Funktion hinzu, um die Spannung von diesem Pin zu lesen:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Fügen Sie unter diesem Code den folgenden Code hinzu, um den Wert auf die serielle Schnittstelle auszugeben:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Fügen Sie schließlich am Ende eine Verzögerung von 10 Sekunden hinzu:

    ```cpp
    delay(10000);
    ```

1. Bauen und laden Sie den Code auf das Wio Terminal hoch.

    > ⚠️ Sie können [die Anleitung zum Erstellen eines PlatformIO-Projekts in Projekt 1, Lektion 1 bei Bedarf](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app) nachlesen.

1. Sobald der Code hochgeladen ist, können Sie die Bodenfeuchtigkeit mit dem seriellen Monitor überwachen. Geben Sie etwas Wasser in die Erde oder entfernen Sie den Sensor aus der Erde und beobachten Sie, wie sich der Wert verändert.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    Im obigen Beispielausgang können Sie sehen, wie die Spannung sinkt, wenn Wasser hinzugefügt wird.

> 💁 Sie finden diesen Code im [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal)-Ordner.

😀 Ihr Programm für den Bodenfeuchtigkeitssensor war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.