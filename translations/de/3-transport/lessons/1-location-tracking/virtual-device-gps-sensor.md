# GPS-Daten lesen - Virtuelle IoT-Hardware

In diesem Teil der Lektion fügen Sie Ihrem virtuellen IoT-Gerät einen GPS-Sensor hinzu und lesen Werte daraus aus.

## Virtuelle Hardware

Das virtuelle IoT-Gerät verwendet einen simulierten GPS-Sensor, der über UART über eine serielle Schnittstelle zugänglich ist.

Ein physischer GPS-Sensor verfügt über eine Antenne, um Radiowellen von GPS-Satelliten zu empfangen und die GPS-Signale in GPS-Daten umzuwandeln. Die virtuelle Version simuliert dies, indem sie Ihnen erlaubt, entweder eine Breite und Länge festzulegen, rohe NMEA-Sätze zu senden oder eine GPX-Datei mit mehreren Standorten hochzuladen, die nacheinander zurückgegeben werden können.

> 🎓 NMEA-Sätze werden später in dieser Lektion behandelt

### Sensor zu CounterFit hinzufügen

Um einen virtuellen GPS-Sensor zu verwenden, müssen Sie einen in der CounterFit-App hinzufügen.

#### Aufgabe - Sensor zu CounterFit hinzufügen

Fügen Sie den GPS-Sensor zur CounterFit-App hinzu.

1. Erstellen Sie eine neue Python-App auf Ihrem Computer in einem Ordner namens `gps-sensor` mit einer einzigen Datei namens `app.py` und einer Python-virtuellen Umgebung, und fügen Sie die CounterFit-Pip-Pakete hinzu.

    > ⚠️ Sie können [die Anweisungen zum Erstellen und Einrichten eines CounterFit-Python-Projekts in Lektion 1 bei Bedarf nachlesen](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Installieren Sie ein zusätzliches Pip-Paket, um einen CounterFit-Shim zu installieren, der mit UART-basierten Sensoren über eine serielle Verbindung kommunizieren kann. Stellen Sie sicher, dass Sie dies von einem Terminal mit aktivierter virtueller Umgebung aus installieren.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Stellen Sie sicher, dass die CounterFit-Web-App läuft.

1. Erstellen Sie einen GPS-Sensor:

    1. Wählen Sie im Feld *Sensor erstellen* im Bereich *Sensoren* im Dropdown-Menü *Sensortyp* die Option *UART GPS* aus.

    1. Lassen Sie den *Port* auf */dev/ttyAMA0* eingestellt.

    1. Wählen Sie die Schaltfläche **Hinzufügen**, um den GPS-Sensor auf Port `/dev/ttyAMA0` zu erstellen.

    ![Die GPS-Sensoreinstellungen](../../../../../translated_images/de/counterfit-create-gps-sensor.6385dc9357d85ad1.webp)

    Der GPS-Sensor wird erstellt und erscheint in der Sensorenliste.

    ![Der erstellte GPS-Sensor](../../../../../translated_images/de/counterfit-gps-sensor.3fbb15af0a536756.webp)

## GPS-Sensor programmieren

Das virtuelle IoT-Gerät kann nun so programmiert werden, dass es den virtuellen GPS-Sensor verwendet.

### Aufgabe - GPS-Sensor programmieren

Programmieren Sie die GPS-Sensor-App.

1. Stellen Sie sicher, dass die `gps-sensor`-App in VS Code geöffnet ist.

1. Öffnen Sie die Datei `app.py`.

1. Fügen Sie den folgenden Code oben in `app.py` ein, um die App mit CounterFit zu verbinden:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Fügen Sie den folgenden Code darunter ein, um einige benötigte Bibliotheken zu importieren, einschließlich der Bibliothek für die CounterFit-Serielle Schnittstelle:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Dieser Code importiert das `serial`-Modul aus dem `counterfit_shims_serial`-Pip-Paket. Es verbindet sich dann mit der seriellen Schnittstelle `/dev/ttyAMA0` – dies ist die Adresse der seriellen Schnittstelle, die der virtuelle GPS-Sensor für seinen UART-Port verwendet.

1. Fügen Sie den folgenden Code darunter ein, um von der seriellen Schnittstelle zu lesen und die Werte in der Konsole auszugeben:

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Eine Funktion namens `print_gps_data` wird definiert, die die übergebene Zeile in der Konsole ausgibt.

    Anschließend wird eine Endlosschleife gestartet, die in jeder Iteration so viele Textzeilen wie möglich von der seriellen Schnittstelle liest. Für jede Zeile wird die Funktion `print_gps_data` aufgerufen.

    Nachdem alle Daten gelesen wurden, schläft die Schleife 1 Sekunde lang und versucht es dann erneut.

1. Führen Sie diesen Code aus und stellen Sie sicher, dass Sie ein anderes Terminal verwenden als das, in dem die CounterFit-App läuft, damit die CounterFit-App weiterhin ausgeführt wird.

1. Ändern Sie in der CounterFit-App den Wert des GPS-Sensors. Sie können dies auf eine der folgenden Arten tun:

    * Setzen Sie die **Quelle** auf `Lat/Lon` und geben Sie eine explizite Breite, Länge und die Anzahl der Satelliten ein, die für die GPS-Fixierung verwendet werden. Dieser Wert wird nur einmal gesendet, daher aktivieren Sie das Kontrollkästchen **Wiederholen**, damit die Daten jede Sekunde wiederholt werden.

      ![Der GPS-Sensor mit ausgewähltem Lat/Lon](../../../../../translated_images/de/counterfit-gps-sensor-latlon.008c867d75464fbe.webp)

    * Setzen Sie die **Quelle** auf `NMEA` und fügen Sie einige NMEA-Sätze in das Textfeld ein. Alle diese Werte werden gesendet, wobei eine Verzögerung von 1 Sekunde vor jedem neuen GGA-(Positionsfixierungs-)Satz besteht.

      ![Der GPS-Sensor mit NMEA-Sätzen](../../../../../translated_images/de/counterfit-gps-sensor-nmea.c62eea442171e17e.webp)

      Sie können ein Tool wie [nmeagen.org](https://www.nmeagen.org) verwenden, um diese Sätze zu generieren, indem Sie auf einer Karte zeichnen. Diese Werte werden nur einmal gesendet, daher aktivieren Sie das Kontrollkästchen **Wiederholen**, damit die Daten eine Sekunde nach dem Senden aller Werte wiederholt werden.

    * Setzen Sie die **Quelle** auf GPX-Datei und laden Sie eine GPX-Datei mit Streckenpositionen hoch. Sie können GPX-Dateien von einer Reihe beliebter Karten- und Wanderseiten wie [AllTrails](https://www.alltrails.com/) herunterladen. Diese Dateien enthalten mehrere GPS-Positionen als Route, und der GPS-Sensor gibt jede neue Position in Intervallen von 1 Sekunde zurück.

      ![Der GPS-Sensor mit einer GPX-Datei](../../../../../translated_images/de/counterfit-gps-sensor-gpxfile.8310b063ce8a425c.webp)

      Diese Werte werden nur einmal gesendet, daher aktivieren Sie das Kontrollkästchen **Wiederholen**, damit die Daten eine Sekunde nach dem Senden aller Werte wiederholt werden.

    Sobald Sie die GPS-Einstellungen konfiguriert haben, wählen Sie die Schaltfläche **Setzen**, um diese Werte dem Sensor zuzuweisen.

1. Sie sehen die Rohdaten des GPS-Sensors, etwa so:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Sie finden diesen Code im Ordner [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device).

😀 Ihr GPS-Sensorprogramm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.