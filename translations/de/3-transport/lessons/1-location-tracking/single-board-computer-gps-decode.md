<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-25T23:01:38+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "de"
}
-->
# GPS-Daten dekodieren - Virtuelle IoT-Hardware und Raspberry Pi

In diesem Teil der Lektion dekodieren Sie die NMEA-Nachrichten, die vom GPS-Sensor über den Raspberry Pi oder das virtuelle IoT-Gerät gelesen wurden, und extrahieren die Breiten- und Längengrade.

## GPS-Daten dekodieren

Sobald die rohen NMEA-Daten vom seriellen Port gelesen wurden, können sie mit einer Open-Source-NMEA-Bibliothek dekodiert werden.

### Aufgabe - GPS-Daten dekodieren

Programmieren Sie das Gerät so, dass es die GPS-Daten dekodiert.

1. Öffnen Sie das Projekt der App `gps-sensor`, falls es noch nicht geöffnet ist.

1. Installieren Sie das Pip-Paket `pynmea2`. Dieses Paket enthält Code zum Dekodieren von NMEA-Nachrichten.

    ```sh
    pip3 install pynmea2
    ```

1. Fügen Sie den folgenden Code zu den Imports in der Datei `app.py` hinzu, um das Modul `pynmea2` zu importieren:

    ```python
    import pynmea2
    ```

1. Ersetzen Sie den Inhalt der Funktion `print_gps_data` durch Folgendes:

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    Dieser Code verwendet die Bibliothek `pynmea2`, um die Zeile zu analysieren, die vom UART-Serial-Port gelesen wurde.

    Wenn der Nachrichtentyp des Satzes `GGA` ist, handelt es sich um eine Positionsfixierungsnachricht, die verarbeitet wird. Die Breiten- und Längengradwerte werden aus der Nachricht gelesen und aus dem NMEA-Format `(d)ddmm.mmmm` in Dezimalgrad umgewandelt. Die Funktion `dm_to_sd` führt diese Umwandlung durch.

    Anschließend wird die Richtung des Breitengrads überprüft. Wenn der Breitengrad südlich ist, wird der Wert in eine negative Zahl umgewandelt. Dasselbe gilt für den Längengrad: Wenn er westlich ist, wird er ebenfalls in eine negative Zahl umgewandelt.

    Schließlich werden die Koordinaten zusammen mit der Anzahl der Satelliten, die zur Bestimmung der Position verwendet wurden, in der Konsole ausgegeben.

1. Führen Sie den Code aus. Wenn Sie ein virtuelles IoT-Gerät verwenden, stellen Sie sicher, dass die CounterFit-App läuft und die GPS-Daten gesendet werden.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Sie finden diesen Code im Ordner [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) oder im Ordner [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 Ihr GPS-Sensorprogramm mit Daten-Dekodierung war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.