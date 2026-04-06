# Nähe erkennen - Virtuelle IoT-Hardware

In diesem Abschnitt der Lektion fügen Sie Ihrem virtuellen IoT-Gerät einen Näherungssensor hinzu und lesen die Entfernung davon ab.

## Hardware

Das virtuelle IoT-Gerät wird einen simulierten Entfernungssensor verwenden.

Bei einem physischen IoT-Gerät würden Sie einen Sensor mit einem Laser-Messmodul verwenden, um Entfernungen zu erkennen.

### Entfernungssensor zu CounterFit hinzufügen

Um einen virtuellen Entfernungssensor zu verwenden, müssen Sie einen in der CounterFit-App hinzufügen.

#### Aufgabe - Entfernungssensor zu CounterFit hinzufügen

Fügen Sie den Entfernungssensor zur CounterFit-App hinzu.

1. Öffnen Sie den Code `fruit-quality-detector` in VS Code und stellen Sie sicher, dass die virtuelle Umgebung aktiviert ist.

1. Installieren Sie ein zusätzliches Pip-Paket, um einen CounterFit-Shim zu installieren, der mit Entfernungssensoren kommunizieren kann, indem er das [rpi-vl53l0x Pip-Paket](https://pypi.org/project/rpi-vl53l0x/) simuliert, ein Python-Paket, das mit [einem VL53L0X Time-of-Flight Entfernungssensor](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/) interagiert. Stellen Sie sicher, dass Sie dies von einem Terminal mit aktivierter virtueller Umgebung aus installieren.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Stellen Sie sicher, dass die CounterFit-Web-App läuft.

1. Erstellen Sie einen Entfernungssensor:

    1. Im Feld *Create sensor* im Bereich *Sensors* öffnen Sie das Dropdown-Menü *Sensor type* und wählen *Distance*.

    1. Lassen Sie die *Units* auf `Millimeter`.

    1. Dieser Sensor ist ein I²C-Sensor, daher setzen Sie die Adresse auf `0x29`. Wenn Sie einen physischen VL53L0X-Sensor verwenden würden, wäre diese Adresse festgelegt.

    1. Wählen Sie die Schaltfläche **Add**, um den Entfernungssensor zu erstellen.

    ![Die Einstellungen des Entfernungssensors](../../../../../translated_images/de/counterfit-create-distance-sensor.967c9fb98f27888d.webp)

    Der Entfernungssensor wird erstellt und erscheint in der Sensorliste.

    ![Der erstellte Entfernungssensor](../../../../../translated_images/de/counterfit-distance-sensor.079eefeeea0b68af.webp)

## Den Entfernungssensor programmieren

Das virtuelle IoT-Gerät kann jetzt programmiert werden, um den simulierten Entfernungssensor zu verwenden.

### Aufgabe - Time-of-Flight-Sensor programmieren

1. Erstellen Sie eine neue Datei im Projekt `fruit-quality-detector` mit dem Namen `distance-sensor.py`.

    > 💁 Eine einfache Möglichkeit, mehrere IoT-Geräte zu simulieren, besteht darin, jedes in einer separaten Python-Datei zu programmieren und sie dann gleichzeitig auszuführen.

1. Starten Sie eine Verbindung zu CounterFit mit folgendem Code:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Fügen Sie den folgenden Code darunter hinzu:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Dieser Code importiert die Sensorbibliothek-Shim für den VL53L0X Time-of-Flight-Sensor.

1. Fügen Sie darunter den folgenden Code hinzu, um auf den Sensor zuzugreifen:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Dieser Code deklariert einen Entfernungssensor und startet ihn anschließend.

1. Fügen Sie schließlich eine Endlosschleife hinzu, um Entfernungen zu lesen:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Dieser Code wartet darauf, dass ein Wert vom Sensor bereit ist, und gibt ihn dann in der Konsole aus.

1. Führen Sie diesen Code aus.

    > 💁 Vergessen Sie nicht, dass diese Datei `distance-sensor.py` heißt! Stellen Sie sicher, dass Sie sie mit Python ausführen und nicht mit `app.py`.

1. Sie werden Entfernungswerte in der Konsole sehen. Ändern Sie den Wert in CounterFit, um zu sehen, wie sich dieser Wert ändert, oder verwenden Sie zufällige Werte.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Sie finden diesen Code im Ordner [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 Ihr Programm für den Näherungssensor war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.