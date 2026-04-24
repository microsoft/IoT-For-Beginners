# Baue ein Nachtlicht - Raspberry Pi

In diesem Teil der Lektion fügst du deinem Raspberry Pi einen Lichtsensor hinzu.

## Hardware

Der Sensor für diese Lektion ist ein **Lichtsensor**, der eine [Photodiode](https://wikipedia.org/wiki/Photodiode) verwendet, um Licht in ein elektrisches Signal umzuwandeln. Es handelt sich um einen analogen Sensor, der einen ganzzahligen Wert von 0 bis 1.000 sendet, der eine relative Lichtmenge angibt. Dieser Wert entspricht keiner standardisierten Maßeinheit wie [Lux](https://wikipedia.org/wiki/Lux).

Der Lichtsensor ist ein externer Grove-Sensor und muss mit dem Grove Base Hat auf dem Raspberry Pi verbunden werden.

### Verbinde den Lichtsensor

Der Grove-Lichtsensor, der die Lichtstärke misst, muss mit dem Raspberry Pi verbunden werden.

#### Aufgabe - Lichtsensor verbinden

Verbinde den Lichtsensor.

![Ein Grove-Lichtsensor](../../../../../translated_images/de/grove-light-sensor.b8127b7c434e632d.webp)

1. Stecke ein Ende eines Grove-Kabels in die Buchse des Lichtsensormoduls. Es passt nur in einer Richtung.

1. Schalte den Raspberry Pi aus und verbinde das andere Ende des Grove-Kabels mit der analogen Buchse, die mit **A0** auf dem Grove Base Hat markiert ist. Diese Buchse ist die zweite von rechts in der Reihe der Buchsen neben den GPIO-Pins.

![Der Grove-Lichtsensor, verbunden mit Buchse A0](../../../../../translated_images/de/pi-light-sensor.66cc1e31fa48cd7d.webp)

## Programmiere den Lichtsensor

Das Gerät kann jetzt mit dem Grove-Lichtsensor programmiert werden.

### Aufgabe - Lichtsensor programmieren

Programmiere das Gerät.

1. Schalte den Raspberry Pi ein und warte, bis er hochgefahren ist.

1. Öffne das Nachtlicht-Projekt in VS Code, das du im vorherigen Teil dieser Aufgabe erstellt hast, entweder direkt auf dem Pi oder über die Remote-SSH-Erweiterung.

1. Öffne die Datei `app.py` und entferne den gesamten vorhandenen Code.

1. Füge den folgenden Code in die Datei `app.py` ein, um einige benötigte Bibliotheken zu importieren:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Die Anweisung `import time` importiert das `time`-Modul, das später in dieser Aufgabe verwendet wird.

    Die Anweisung `from grove.grove_light_sensor_v1_2 import GroveLightSensor` importiert den `GroveLightSensor` aus den Grove-Python-Bibliotheken. Diese Bibliothek enthält Code zur Interaktion mit einem Grove-Lichtsensor und wurde während der Pi-Einrichtung global installiert.

1. Füge den folgenden Code nach dem obigen Code ein, um eine Instanz der Klasse zu erstellen, die den Lichtsensor verwaltet:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Die Zeile `light_sensor = GroveLightSensor(0)` erstellt eine Instanz der Klasse `GroveLightSensor`, die mit Pin **A0** verbunden ist – dem analogen Grove-Pin, an den der Lichtsensor angeschlossen ist.

1. Füge eine Endlosschleife nach dem obigen Code ein, um den Wert des Lichtsensors abzufragen und in der Konsole auszugeben:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Dies liest den aktuellen Lichtwert auf einer Skala von 0-1.023 mithilfe der Eigenschaft `light` der Klasse `GroveLightSensor`. Diese Eigenschaft liest den analogen Wert vom Pin. Dieser Wert wird dann in der Konsole ausgegeben.

1. Füge am Ende der Schleife eine kurze Pause von einer Sekunde ein, da die Lichtwerte nicht kontinuierlich überprüft werden müssen. Eine Pause reduziert den Stromverbrauch des Geräts.

    ```python
    time.sleep(1)
    ```

1. Führe im Terminal von VS Code den folgenden Befehl aus, um deine Python-App auszuführen:

    ```sh
    python3 app.py
    ```

    Lichtwerte werden in der Konsole ausgegeben. Decke den Lichtsensor ab und lege ihn wieder frei, und die Werte werden sich ändern:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Du findest diesen Code im Ordner [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi).

😀 Das Hinzufügen eines Sensors zu deinem Nachtlicht-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.