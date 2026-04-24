# Baue ein Nachtlicht - Raspberry Pi

In diesem Teil der Lektion fügst du eine LED zu deinem Raspberry Pi hinzu und nutzt sie, um ein Nachtlicht zu erstellen.

## Hardware

Das Nachtlicht benötigt jetzt einen Aktuator.

Der Aktuator ist eine **LED**, eine [lichtemittierende Diode](https://wikipedia.org/wiki/Lichtemittierende_Diode), die Licht abgibt, wenn Strom durch sie fließt. Dies ist ein digitaler Aktuator mit zwei Zuständen: an und aus. Ein Wert von 1 schaltet die LED ein, und ein Wert von 0 schaltet sie aus. Die LED ist ein externer Grove-Aktuator und muss mit dem Grove Base Hat am Raspberry Pi verbunden werden.

Die Logik des Nachtlichts in Pseudocode lautet:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Verbinde die LED

Die Grove LED wird als Modul mit einer Auswahl an LEDs geliefert, sodass du die Farbe auswählen kannst.

#### Aufgabe - LED verbinden

Verbinde die LED.

![Eine Grove LED](../../../../../translated_images/de/grove-led.6c853be93f473cf2.webp)

1. Wähle deine Lieblings-LED aus und stecke die Beine in die beiden Löcher des LED-Moduls.

    LEDs sind lichtemittierende Dioden, und Dioden sind elektronische Bauteile, die Strom nur in eine Richtung leiten können. Das bedeutet, dass die LED richtig herum angeschlossen werden muss, sonst funktioniert sie nicht.

    Eines der Beine der LED ist der positive Pin, das andere der negative Pin. Die LED ist nicht perfekt rund und auf einer Seite leicht abgeflacht. Die leicht abgeflachte Seite ist der negative Pin. Wenn du die LED mit dem Modul verbindest, stelle sicher, dass der Pin auf der abgerundeten Seite mit der Buchse **+** auf der Außenseite des Moduls verbunden ist und die abgeflachte Seite mit der Buchse näher zur Mitte des Moduls.

1. Das LED-Modul hat einen Drehknopf, mit dem du die Helligkeit steuern kannst. Drehe diesen zunächst ganz auf, indem du ihn mit einem kleinen Kreuzschlitzschraubendreher so weit wie möglich gegen den Uhrzeigersinn drehst.

1. Stecke ein Ende eines Grove-Kabels in die Buchse des LED-Moduls. Es passt nur in einer Richtung hinein.

1. Schalte den Raspberry Pi aus und verbinde das andere Ende des Grove-Kabels mit der digitalen Buchse **D5** auf dem Grove Base Hat, der am Pi angebracht ist. Diese Buchse ist die zweite von links in der Reihe der Buchsen neben den GPIO-Pins.

![Die Grove LED verbunden mit Buchse D5](../../../../../translated_images/de/pi-led.97f1d474981dc35d.webp)

## Programmiere das Nachtlicht

Das Nachtlicht kann jetzt mit dem Grove-Lichtsensor und der Grove-LED programmiert werden.

### Aufgabe - Nachtlicht programmieren

Programmiere das Nachtlicht.

1. Schalte den Pi ein und warte, bis er hochgefahren ist.

1. Öffne das Nachtlicht-Projekt in VS Code, das du im vorherigen Teil dieser Aufgabe erstellt hast, entweder direkt auf dem Pi oder über die Remote SSH-Erweiterung verbunden.

1. Füge den folgenden Code in die Datei `app.py` ein, um eine benötigte Bibliothek zu importieren. Dieser Code sollte oben unter den anderen `import`-Zeilen hinzugefügt werden.

    ```python
    from grove.grove_led import GroveLed
    ```

    Die Anweisung `from grove.grove_led import GroveLed` importiert die `GroveLed`-Klasse aus den Grove-Python-Bibliotheken. Diese Bibliothek enthält Code, um mit einer Grove-LED zu interagieren.

1. Füge den folgenden Code nach der `light_sensor`-Deklaration hinzu, um eine Instanz der Klasse zu erstellen, die die LED verwaltet:

    ```python
    led = GroveLed(5)
    ```

    Die Zeile `led = GroveLed(5)` erstellt eine Instanz der `GroveLed`-Klasse, die mit Pin **D5** verbunden ist - dem digitalen Grove-Pin, an den die LED angeschlossen ist.

    > 💁 Alle Buchsen haben eindeutige Pinnummern. Pins 0, 2, 4 und 6 sind analoge Pins, Pins 5, 16, 18, 22, 24 und 26 sind digitale Pins.

1. Füge eine Überprüfung innerhalb der `while`-Schleife und vor dem `time.sleep` hinzu, um die Lichtwerte zu überprüfen und die LED ein- oder auszuschalten:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Dieser Code überprüft den `light`-Wert. Wenn dieser kleiner als 300 ist, wird die `on`-Methode der `GroveLed`-Klasse aufgerufen, die einen digitalen Wert von 1 an die LED sendet und sie einschaltet. Wenn der Lichtwert größer oder gleich 300 ist, wird die `off`-Methode aufgerufen, die einen digitalen Wert von 0 sendet und die LED ausschaltet.

    > 💁 Dieser Code sollte auf die gleiche Ebene eingerückt sein wie die Zeile `print('Light level:', light)`, um innerhalb der `while`-Schleife zu sein!

    > 💁 Beim Senden digitaler Werte an Aktuatoren entspricht ein Wert von 0 0V, und ein Wert von 1 der maximalen Spannung für das Gerät. Für den Raspberry Pi mit Grove-Sensoren und -Aktuatoren beträgt die Spannung bei einem Wert von 1 3,3V.

1. Führe im VS Code-Terminal den folgenden Befehl aus, um deine Python-App auszuführen:

    ```sh
    python3 app.py
    ```

    Lichtwerte werden auf der Konsole ausgegeben.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Bedecke und enthülle den Lichtsensor. Beobachte, wie die LED aufleuchtet, wenn der Lichtwert 300 oder weniger beträgt, und sich ausschaltet, wenn der Lichtwert größer als 300 ist.

    > 💁 Wenn die LED nicht leuchtet, stelle sicher, dass sie richtig herum angeschlossen ist und der Drehknopf auf volle Helligkeit eingestellt ist.

![Die LED, die mit dem Pi verbunden ist, schaltet sich ein und aus, wenn sich der Lichtwert ändert](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Du findest diesen Code im Ordner [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 Dein Nachtlicht-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.