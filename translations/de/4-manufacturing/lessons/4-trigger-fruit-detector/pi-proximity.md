# Nähe erkennen - Raspberry Pi

In diesem Teil der Lektion fügst du deinem Raspberry Pi einen Näherungssensor hinzu und liest die Distanz davon ab.

## Hardware

Der Raspberry Pi benötigt einen Näherungssensor.

Der Sensor, den du verwenden wirst, ist ein [Grove Time of Flight Distanzsensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Dieser Sensor verwendet ein Laser-Messmodul, um Entfernungen zu erkennen. Der Sensor hat einen Messbereich von 10 mm bis 2000 mm (1 cm - 2 m) und liefert in diesem Bereich recht genaue Werte. Entfernungen über 1000 mm werden als 8109 mm gemeldet.

Der Laser-Entfernungsmesser befindet sich auf der Rückseite des Sensors, gegenüber der Grove-Buchse.

Dies ist ein I²C-Sensor.

### Den Time of Flight Sensor anschließen

Der Grove Time of Flight Sensor kann mit dem Raspberry Pi verbunden werden.

#### Aufgabe - Den Time of Flight Sensor anschließen

Schließe den Time of Flight Sensor an.

![Ein Grove Time of Flight Sensor](../../../../../translated_images/de/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Stecke ein Ende eines Grove-Kabels in die Buchse des Time of Flight Sensors. Es passt nur in einer Richtung hinein.

1. Schalte den Raspberry Pi aus und verbinde das andere Ende des Grove-Kabels mit einer der I²C-Buchsen, die mit **I²C** markiert sind, auf dem Grove Base Hat, das am Pi angebracht ist. Diese Buchsen befinden sich in der unteren Reihe, am gegenüberliegenden Ende der GPIO-Pins und neben dem Kamera-Kabelanschluss.

![Der Grove Time of Flight Sensor, verbunden mit der I²C-Buchse](../../../../../translated_images/de/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Den Time of Flight Sensor programmieren

Der Raspberry Pi kann nun so programmiert werden, dass er den angeschlossenen Time of Flight Sensor verwendet.

### Aufgabe - Den Time of Flight Sensor programmieren

Programmiere das Gerät.

1. Schalte den Pi ein und warte, bis er hochgefahren ist.

1. Öffne den Code des Projekts `fruit-quality-detector` in VS Code, entweder direkt auf dem Pi oder über die Remote SSH-Erweiterung.

1. Installiere das Pip-Paket `rpi-vl53l0x`, ein Python-Paket, das mit einem VL53L0X Time-of-Flight Distanzsensor interagiert. Installiere es mit folgendem Pip-Befehl:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Erstelle in diesem Projekt eine neue Datei mit dem Namen `distance-sensor.py`.

    > 💁 Eine einfache Möglichkeit, mehrere IoT-Geräte zu simulieren, besteht darin, jedes in einer separaten Python-Datei zu programmieren und sie dann gleichzeitig auszuführen.

1. Füge dieser Datei den folgenden Code hinzu:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Dieser Code importiert die Grove I²C-Bus-Bibliothek und eine Sensor-Bibliothek für die Kernhardware des Grove Time of Flight Sensors.

1. Füge darunter den folgenden Code hinzu, um auf den Sensor zuzugreifen:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Dieser Code deklariert einen Distanzsensor, der den Grove I²C-Bus verwendet, und startet den Sensor.

1. Füge schließlich eine Endlosschleife hinzu, um die Distanzen auszulesen:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Dieser Code wartet darauf, dass ein Wert vom Sensor bereitgestellt wird, und gibt ihn dann in der Konsole aus.

1. Führe diesen Code aus.

    > 💁 Vergiss nicht, dass diese Datei `distance-sensor.py` heißt! Stelle sicher, dass du sie mit Python ausführst und nicht `app.py`.

1. Du wirst Distanzmessungen in der Konsole sehen. Positioniere Objekte in der Nähe des Sensors, und du wirst die Distanzmessung sehen:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Der Entfernungsmesser befindet sich auf der Rückseite des Sensors, also achte darauf, die richtige Seite zu verwenden, wenn du die Distanz misst.

    ![Der Entfernungsmesser auf der Rückseite des Time of Flight Sensors zeigt auf eine Banane](../../../../../translated_images/de/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Du findest diesen Code im Ordner [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 Dein Programm für den Näherungssensor war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.