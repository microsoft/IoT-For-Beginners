<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-25T23:03:02+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "de"
}
-->
# GPS-Daten dekodieren - Wio Terminal

In diesem Teil der Lektion dekodieren Sie die NMEA-Nachrichten, die vom GPS-Sensor des Wio Terminals gelesen werden, und extrahieren die Breiten- und Längengrade.

## GPS-Daten dekodieren

Sobald die rohen NMEA-Daten vom seriellen Port gelesen wurden, können sie mit einer Open-Source-NMEA-Bibliothek dekodiert werden.

### Aufgabe - GPS-Daten dekodieren

Programmieren Sie das Gerät, um die GPS-Daten zu dekodieren.

1. Öffnen Sie das Projekt der App `gps-sensor`, falls es noch nicht geöffnet ist.

1. Fügen Sie dem `platformio.ini`-Projekt eine Bibliotheksabhängigkeit für die [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus)-Bibliothek hinzu. Diese Bibliothek enthält Code zum Dekodieren von NMEA-Daten.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. Fügen Sie in `main.cpp` eine Include-Direktive für die TinyGPSPlus-Bibliothek hinzu:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Deklarieren Sie unter der Deklaration von `Serial3` ein TinyGPSPlus-Objekt, um die NMEA-Sätze zu verarbeiten:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Ändern Sie den Inhalt der Funktion `printGPSData` wie folgt:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    Dieser Code liest das nächste Zeichen vom UART-Serienport in den `gps`-NMEA-Dekoder ein. Nach jedem Zeichen wird überprüft, ob der Dekoder einen gültigen Satz gelesen hat, und anschließend, ob er einen gültigen Standort gelesen hat. Wenn der Standort gültig ist, wird er zusammen mit der Anzahl der Satelliten, die zu diesem Fix beigetragen haben, an den seriellen Monitor gesendet.

1. Bauen und laden Sie den Code auf das Wio Terminal hoch.

1. Nach dem Hochladen können Sie die GPS-Standortdaten mit dem seriellen Monitor überwachen.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Sie finden diesen Code im Ordner [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Ihr GPS-Sensorprogramm mit Daten-Dekodierung war erfolgreich!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.