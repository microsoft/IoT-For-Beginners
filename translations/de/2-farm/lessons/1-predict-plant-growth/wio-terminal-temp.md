# Temperatur messen - Wio Terminal

In diesem Teil der Lektion fügen Sie Ihrem Wio Terminal einen Temperatursensor hinzu und lesen Temperaturwerte daraus aus.

## Hardware

Das Wio Terminal benötigt einen Temperatursensor.

Der Sensor, den Sie verwenden werden, ist ein [DHT11 Feuchtigkeits- und Temperatursensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), der zwei Sensoren in einem Gehäuse kombiniert. Dieser Sensor ist recht beliebt, da es viele kommerziell erhältliche Sensoren gibt, die Temperatur, Feuchtigkeit und manchmal auch den Luftdruck messen. Der Temperatursensor ist ein NTC-Thermistor (Negative Temperature Coefficient), ein Thermistor, dessen Widerstand mit steigender Temperatur abnimmt.

Dies ist ein digitaler Sensor, der über einen integrierten ADC (Analog-Digital-Wandler) verfügt, um ein digitales Signal zu erzeugen, das die Temperatur- und Feuchtigkeitsdaten enthält, die der Mikrocontroller lesen kann.

### Den Temperatursensor anschließen

Der Grove-Temperatursensor kann an den digitalen Port des Wio Terminals angeschlossen werden.

#### Aufgabe - Den Temperatursensor anschließen

Schließen Sie den Temperatursensor an.

![Ein Grove-Temperatursensor](../../../../../translated_images/de/grove-dht11.07f8eafceee17004.webp)

1. Stecken Sie ein Ende eines Grove-Kabels in die Buchse des Feuchtigkeits- und Temperatursensors. Es passt nur in einer Richtung.

1. Trennen Sie das Wio Terminal von Ihrem Computer oder einer anderen Stromquelle und verbinden Sie das andere Ende des Grove-Kabels mit der rechten Grove-Buchse des Wio Terminals, wenn Sie auf den Bildschirm schauen. Dies ist die Buchse, die am weitesten vom Netzschalter entfernt ist.

![Der Grove-Temperatursensor ist mit der rechten Buchse verbunden](../../../../../translated_images/de/wio-temperature-sensor.2934928f38c7f79a.webp)

## Den Temperatursensor programmieren

Das Wio Terminal kann nun so programmiert werden, dass es den angeschlossenen Temperatursensor verwendet.

### Aufgabe - Den Temperatursensor programmieren

Programmieren Sie das Gerät.

1. Erstellen Sie ein brandneues Wio Terminal-Projekt mit PlatformIO. Nennen Sie dieses Projekt `temperature-sensor`. Fügen Sie im `setup`-Abschnitt Code hinzu, um die serielle Schnittstelle zu konfigurieren.

    > ⚠️ Sie können [die Anweisungen zum Erstellen eines PlatformIO-Projekts in Projekt 1, Lektion 1 bei Bedarf nachlesen](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Fügen Sie eine Bibliotheksabhängigkeit für die Seeed Grove Feuchtigkeits- und Temperatursensor-Bibliothek in die Datei `platformio.ini` des Projekts ein:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Sie können [die Anweisungen zum Hinzufügen von Bibliotheken zu einem PlatformIO-Projekt in Projekt 1, Lektion 4 bei Bedarf nachlesen](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Fügen Sie die folgenden `#include`-Direktiven oben in die Datei ein, unter der bestehenden `#include <Arduino.h>`:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Dies importiert die Dateien, die benötigt werden, um mit dem Sensor zu interagieren. Die `DHT.h`-Headerdatei enthält den Code für den Sensor selbst, und das Hinzufügen der `SPI.h`-Headerdatei stellt sicher, dass der Code, der benötigt wird, um mit dem Sensor zu kommunizieren, beim Kompilieren der App verlinkt wird.

1. Deklarieren Sie vor der `setup`-Funktion den DHT-Sensor:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Dies deklariert eine Instanz der `DHT`-Klasse, die den **D**igitalen **H**umidity- und **T**emperature-Sensor verwaltet. Dieser ist mit Port `D0` verbunden, der rechten Grove-Buchse des Wio Terminals. Der zweite Parameter teilt dem Code mit, dass der verwendete Sensor der *DHT11*-Sensor ist – die Bibliothek, die Sie verwenden, unterstützt auch andere Varianten dieses Sensors.

1. Fügen Sie in der `setup`-Funktion Code hinzu, um die serielle Verbindung einzurichten:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. Fügen Sie am Ende der `setup`-Funktion, nach der letzten `delay`, einen Aufruf hinzu, um den DHT-Sensor zu starten:

    ```cpp
    dht.begin();
    ```

1. Fügen Sie in der `loop`-Funktion Code hinzu, um den Sensor aufzurufen und die Temperatur auf der seriellen Schnittstelle auszugeben:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Dieser Code deklariert ein leeres Array mit 2 Gleitkommazahlen und übergibt dieses an den Aufruf von `readTempAndHumidity` auf der `DHT`-Instanz. Dieser Aufruf füllt das Array mit 2 Werten – die Feuchtigkeit wird in das 0. Element des Arrays geschrieben (denken Sie daran, dass Arrays in C++ 0-basiert sind, sodass das 0. Element das 'erste' Element im Array ist), und die Temperatur wird in das 1. Element geschrieben.

    Die Temperatur wird aus dem 1. Element des Arrays gelesen und auf der seriellen Schnittstelle ausgegeben.

    > 🇺🇸 Die Temperatur wird in Celsius gelesen. Für Amerikaner: Um dies in Fahrenheit umzurechnen, teilen Sie den Celsius-Wert durch 5, multiplizieren Sie dann mit 9 und addieren Sie 32. Zum Beispiel wird eine Temperatur von 20°C zu ((20/5)*9) + 32 = 68°F.

1. Bauen und laden Sie den Code auf das Wio Terminal hoch.

    > ⚠️ Sie können [die Anweisungen zum Erstellen eines PlatformIO-Projekts in Projekt 1, Lektion 1 bei Bedarf nachlesen](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Sobald der Code hochgeladen ist, können Sie die Temperatur mit dem seriellen Monitor überwachen:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Sie finden diesen Code im Ordner [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 Ihr Programm für den Temperatursensor war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.