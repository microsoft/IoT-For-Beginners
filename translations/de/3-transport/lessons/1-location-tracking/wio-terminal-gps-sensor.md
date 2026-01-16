<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-25T22:56:50+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "de"
}
-->
# GPS-Daten auslesen - Wio Terminal

In diesem Abschnitt der Lektion fügen Sie Ihrem Wio Terminal einen GPS-Sensor hinzu und lesen Werte daraus aus.

## Hardware

Das Wio Terminal benötigt einen GPS-Sensor.

Der Sensor, den Sie verwenden werden, ist ein [Grove GPS Air530 Sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Dieser Sensor kann sich mit mehreren GPS-Systemen verbinden, um eine schnelle und präzise Standortbestimmung zu ermöglichen. Der Sensor besteht aus zwei Teilen – der zentralen Elektronik des Sensors und einer externen Antenne, die über ein dünnes Kabel angeschlossen ist, um die Funkwellen der Satelliten zu empfangen.

Dies ist ein UART-Sensor, der GPS-Daten über UART sendet.

### GPS-Sensor anschließen

Der Grove GPS-Sensor kann an das Wio Terminal angeschlossen werden.

#### Aufgabe - GPS-Sensor anschließen

Schließen Sie den GPS-Sensor an.

![Ein Grove GPS-Sensor](../../../../../translated_images/de/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Stecken Sie ein Ende eines Grove-Kabels in die Buchse des GPS-Sensors. Es passt nur in einer Richtung.

1. Verbinden Sie, während das Wio Terminal nicht mit Ihrem Computer oder einer anderen Stromquelle verbunden ist, das andere Ende des Grove-Kabels mit der linken Grove-Buchse des Wio Terminals, wenn Sie auf den Bildschirm schauen. Dies ist die Buchse, die sich am nächsten zum Ein-/Ausschalter befindet.

    ![Der Grove GPS-Sensor ist mit der linken Buchse verbunden](../../../../../translated_images/de/wio-gps-sensor.19fd52b81ce58095.webp)

1. Positionieren Sie den GPS-Sensor so, dass die angeschlossene Antenne Sicht zum Himmel hat – idealerweise in der Nähe eines offenen Fensters oder im Freien. Es ist einfacher, ein klares Signal zu erhalten, wenn sich nichts zwischen der Antenne und dem Himmel befindet.

1. Sie können nun das Wio Terminal mit Ihrem Computer verbinden.

1. Der GPS-Sensor hat zwei LEDs – eine blaue LED, die blinkt, wenn Daten übertragen werden, und eine grüne LED, die jede Sekunde blinkt, wenn Daten von Satelliten empfangen werden. Stellen Sie sicher, dass die blaue LED blinkt, wenn Sie das Wio Terminal einschalten. Nach ein paar Minuten sollte die grüne LED blinken – falls nicht, müssen Sie möglicherweise die Antenne neu positionieren.

## GPS-Sensor programmieren

Das Wio Terminal kann nun so programmiert werden, dass es den angeschlossenen GPS-Sensor verwendet.

### Aufgabe - GPS-Sensor programmieren

Programmieren Sie das Gerät.

1. Erstellen Sie ein neues Wio Terminal-Projekt mit PlatformIO. Nennen Sie dieses Projekt `gps-sensor`. Fügen Sie im `setup`-Abschnitt Code hinzu, um die serielle Schnittstelle zu konfigurieren.

1. Fügen Sie die folgende Include-Direktive am Anfang der Datei `main.cpp` hinzu. Diese bindet eine Header-Datei ein, die Funktionen zur Konfiguration der linken Grove-Buchse für UART enthält.

    ```cpp
    #include <wiring_private.h>
    ```

1. Fügen Sie darunter die folgende Codezeile hinzu, um eine serielle Verbindung zur UART-Schnittstelle zu deklarieren:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Sie müssen etwas Code hinzufügen, um einige interne Signal-Handler auf diese serielle Schnittstelle umzuleiten. Fügen Sie den folgenden Code unterhalb der `Serial3`-Deklaration hinzu:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. Konfigurieren Sie im `setup`-Abschnitt unterhalb der Konfiguration der `Serial`-Schnittstelle die UART-Schnittstelle mit folgendem Code:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Fügen Sie unter diesem Code im `setup`-Abschnitt den folgenden Code hinzu, um den Grove-Pin mit der seriellen Schnittstelle zu verbinden:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Fügen Sie vor der `loop`-Funktion die folgende Funktion hinzu, um die GPS-Daten an den seriellen Monitor zu senden:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. Fügen Sie in der `loop`-Funktion den folgenden Code hinzu, um Daten von der UART-Schnittstelle zu lesen und die Ausgabe an den seriellen Monitor zu senden:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Dieser Code liest von der UART-Schnittstelle. Die Funktion `readStringUntil` liest bis zu einem Trennzeichen, in diesem Fall einem Zeilenumbruch. Dadurch wird ein vollständiger NMEA-Satz gelesen (NMEA-Sätze enden mit einem Zeilenumbruch). Solange Daten von der UART-Schnittstelle gelesen werden können, werden sie gelesen und über die Funktion `printGPSData` an den seriellen Monitor gesendet. Sobald keine weiteren Daten gelesen werden können, verzögert die `loop`-Funktion für 1 Sekunde (1.000 ms).

1. Bauen und laden Sie den Code auf das Wio Terminal hoch.

1. Nach dem Hochladen können Sie die GPS-Daten mit dem seriellen Monitor überwachen.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 Sie finden diesen Code im Ordner [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 Ihr GPS-Sensor-Programm war erfolgreich!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.