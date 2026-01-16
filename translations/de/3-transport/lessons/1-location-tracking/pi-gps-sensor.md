<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3b2448c7ab4e9673e77e35a50c5e350d",
  "translation_date": "2025-08-25T23:02:17+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/pi-gps-sensor.md",
  "language_code": "de"
}
-->
# GPS-Daten lesen - Raspberry Pi

In diesem Teil der Lektion fügen Sie Ihrem Raspberry Pi einen GPS-Sensor hinzu und lesen Werte von diesem aus.

## Hardware

Der Raspberry Pi benötigt einen GPS-Sensor.

Der Sensor, den Sie verwenden werden, ist ein [Grove GPS Air530 Sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Dieser Sensor kann sich mit mehreren GPS-Systemen verbinden, um eine schnelle und präzise Standortbestimmung zu ermöglichen. Der Sensor besteht aus zwei Teilen: der Kern-Elektronik des Sensors und einer externen Antenne, die über ein dünnes Kabel angeschlossen ist, um die Funkwellen der Satelliten zu empfangen.

Dies ist ein UART-Sensor, der GPS-Daten über UART sendet.

## GPS-Sensor anschließen

Der Grove GPS-Sensor kann mit dem Raspberry Pi verbunden werden.

### Aufgabe - GPS-Sensor anschließen

Schließen Sie den GPS-Sensor an.

![Ein Grove GPS-Sensor](../../../../../translated_images/de/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Stecken Sie ein Ende eines Grove-Kabels in die Buchse des GPS-Sensors. Es passt nur in einer Richtung hinein.

1. Schalten Sie den Raspberry Pi aus und verbinden Sie das andere Ende des Grove-Kabels mit der UART-Buchse, die mit **UART** auf dem Grove Base Hat am Pi markiert ist. Diese Buchse befindet sich in der mittleren Reihe, auf der Seite in der Nähe des SD-Karten-Slots, gegenüber den USB-Ports und dem Ethernet-Anschluss.

    ![Der Grove GPS-Sensor, verbunden mit der UART-Buchse](../../../../../translated_images/de/pi-gps-sensor.1f99ee2b2f6528915047ec78967bd362e0e4ee0ed594368a3837b9cf9cdaca64.png)

1. Positionieren Sie den GPS-Sensor so, dass die angeschlossene Antenne Sicht zum Himmel hat – idealerweise neben einem offenen Fenster oder draußen. Es ist einfacher, ein klares Signal zu empfangen, wenn nichts die Antenne blockiert.

## GPS-Sensor programmieren

Der Raspberry Pi kann nun programmiert werden, um den angeschlossenen GPS-Sensor zu verwenden.

### Aufgabe - GPS-Sensor programmieren

Programmieren Sie das Gerät.

1. Schalten Sie den Pi ein und warten Sie, bis er hochgefahren ist.

1. Der GPS-Sensor hat zwei LEDs – eine blaue LED, die blinkt, wenn Daten übertragen werden, und eine grüne LED, die jede Sekunde blinkt, wenn Daten von Satelliten empfangen werden. Stellen Sie sicher, dass die blaue LED blinkt, wenn Sie den Pi einschalten. Nach einigen Minuten sollte die grüne LED blinken – falls nicht, müssen Sie möglicherweise die Antenne neu positionieren.

1. Starten Sie VS Code, entweder direkt auf dem Pi oder verbinden Sie sich über die Remote SSH-Erweiterung.

    > ⚠️ Sie können [die Anweisungen zum Einrichten und Starten von VS Code in Lektion 1 bei Bedarf](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md) nachlesen.

1. Bei neueren Versionen des Raspberry Pi, die Bluetooth unterstützen, gibt es einen Konflikt zwischen dem seriellen Port, der für Bluetooth verwendet wird, und dem, der vom Grove UART-Port genutzt wird. Um dies zu beheben, führen Sie die folgenden Schritte aus:

    1. Bearbeiten Sie die Datei `/boot/config.txt` im VS Code-Terminal mit `nano`, einem integrierten Terminal-Texteditor, mit folgendem Befehl:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Diese Datei kann nicht direkt in VS Code bearbeitet werden, da Sie `sudo`-Berechtigungen benötigen, also erhöhte Berechtigungen. VS Code läuft nicht mit diesen Berechtigungen.

    1. Navigieren Sie mit den Pfeiltasten zum Ende der Datei und kopieren Sie den untenstehenden Code, um ihn am Ende der Datei einzufügen:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Sie können den Code mit den üblichen Tastenkombinationen für Ihr Gerät einfügen (`Ctrl+v` auf Windows, Linux oder Raspberry Pi OS, `Cmd+v` auf macOS).

    1. Speichern Sie die Datei und verlassen Sie nano, indem Sie `Ctrl+x` drücken. Drücken Sie `y`, wenn Sie gefragt werden, ob Sie den geänderten Puffer speichern möchten, und drücken Sie `Enter`, um zu bestätigen, dass Sie `/boot/config.txt` überschreiben möchten.

        > Wenn Sie einen Fehler machen, können Sie ohne Speichern beenden und die Schritte wiederholen.

    1. Bearbeiten Sie die Datei `/boot/cmdline.txt` in nano mit folgendem Befehl:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Diese Datei enthält eine Reihe von Schlüssel-Wert-Paaren, die durch Leerzeichen getrennt sind. Entfernen Sie alle Schlüssel-Wert-Paare für den Schlüssel `console`. Sie sehen wahrscheinlich so aus:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Sie können zu diesen Einträgen mit den Pfeiltasten navigieren und sie dann mit den Tasten `del` oder `backspace` löschen.

        Wenn Ihre Originaldatei beispielsweise so aussieht:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Wird die neue Version so aussehen:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Folgen Sie den oben genannten Schritten, um diese Datei zu speichern und nano zu verlassen.

    1. Starten Sie Ihren Pi neu und verbinden Sie sich erneut in VS Code, sobald der Pi neu gestartet ist.

1. Erstellen Sie im Terminal einen neuen Ordner im Home-Verzeichnis des Benutzers `pi` mit dem Namen `gps-sensor`. Erstellen Sie in diesem Ordner eine Datei mit dem Namen `app.py`.

1. Öffnen Sie diesen Ordner in VS Code.

1. Das GPS-Modul sendet UART-Daten über einen seriellen Port. Installieren Sie das `pyserial` Pip-Paket, um über Python-Code mit dem seriellen Port zu kommunizieren:

    ```sh
    pip3 install pyserial
    ```

1. Fügen Sie den folgenden Code in Ihre Datei `app.py` ein:

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Dieser Code importiert das `serial`-Modul aus dem `pyserial` Pip-Paket. Anschließend wird eine Verbindung zum seriellen Port `/dev/ttyAMA0` hergestellt – dies ist die Adresse des seriellen Ports, den der Grove Pi Base Hat für seinen UART-Port verwendet. Danach werden alle vorhandenen Daten aus dieser seriellen Verbindung gelöscht.

    Als Nächstes wird eine Funktion namens `print_gps_data` definiert, die die übergebene Zeile in der Konsole ausgibt.

    Anschließend wird der Code in einer Endlosschleife ausgeführt, die in jeder Schleife so viele Textzeilen wie möglich vom seriellen Port liest. Für jede Zeile wird die Funktion `print_gps_data` aufgerufen.

    Nachdem alle Daten gelesen wurden, schläft die Schleife für 1 Sekunde und versucht es erneut.

1. Führen Sie diesen Code aus. Sie sehen die Rohdaten des GPS-Sensors, etwa so:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Wenn Sie einen der folgenden Fehler beim Stoppen und Neustarten Ihres Codes erhalten, fügen Sie einen `try - except` Block in Ihre While-Schleife ein.

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 Sie finden diesen Code im Ordner [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 Ihr GPS-Sensor-Programm war erfolgreich!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.