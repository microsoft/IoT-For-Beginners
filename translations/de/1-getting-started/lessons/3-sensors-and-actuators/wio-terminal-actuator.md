<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "db44083b4dc6fb06eac83c4f16448940",
  "translation_date": "2025-08-25T22:07:11+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-actuator.md",
  "language_code": "de"
}
-->
# Baue ein Nachtlicht - Wio Terminal

In diesem Teil der Lektion fügst du deinem Wio Terminal eine LED hinzu und nutzt sie, um ein Nachtlicht zu erstellen.

## Hardware

Das Nachtlicht benötigt jetzt einen Aktor.

Der Aktor ist eine **LED**, eine [lichtemittierende Diode](https://wikipedia.org/wiki/Light-emitting_diode), die Licht abgibt, wenn Strom durch sie fließt. Dies ist ein digitaler Aktor mit zwei Zuständen: an und aus. Ein Wert von 1 schaltet die LED ein, und ein Wert von 0 schaltet sie aus. Dies ist ein externer Grove-Aktor, der mit dem Wio Terminal verbunden werden muss.

Die Logik des Nachtlichts in Pseudocode lautet:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Verbinde die LED

Die Grove-LED wird als Modul mit einer Auswahl an LEDs geliefert, sodass du die Farbe wählen kannst.

#### Aufgabe - Verbinde die LED

Verbinde die LED.

![Eine Grove-LED](../../../../../translated_images/de/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. Wähle deine Lieblings-LED aus und stecke die Beine in die beiden Löcher des LED-Moduls.

    LEDs sind lichtemittierende Dioden, und Dioden sind elektronische Bauteile, die Strom nur in eine Richtung leiten können. Das bedeutet, dass die LED richtig herum angeschlossen werden muss, sonst funktioniert sie nicht.

    Eines der Beine der LED ist der positive Pin, das andere der negative Pin. Die LED ist nicht perfekt rund und auf einer Seite leicht abgeflacht. Die leicht abgeflachte Seite ist der negative Pin. Wenn du die LED mit dem Modul verbindest, stelle sicher, dass der Pin auf der abgerundeten Seite mit der Buchse **+** auf der Außenseite des Moduls verbunden ist und die abgeflachte Seite mit der Buchse näher zur Mitte des Moduls.

1. Das LED-Modul hat einen Drehknopf, mit dem du die Helligkeit steuern kannst. Drehe diesen zunächst ganz nach oben, indem du ihn mit einem kleinen Kreuzschlitzschraubendreher so weit wie möglich gegen den Uhrzeigersinn drehst.

1. Stecke ein Ende eines Grove-Kabels in die Buchse des LED-Moduls. Es passt nur in einer Richtung hinein.

1. Während das Wio Terminal nicht mit deinem Computer oder einer anderen Stromquelle verbunden ist, verbinde das andere Ende des Grove-Kabels mit der rechten Grove-Buchse des Wio Terminals, wenn du auf den Bildschirm schaust. Dies ist die Buchse, die am weitesten vom Netzschalter entfernt ist.

    > 💁 Die rechte Grove-Buchse kann mit analogen oder digitalen Sensoren und Aktoren verwendet werden. Die linke Buchse ist nur für I2C- und digitale Sensoren und Aktoren.

![Die Grove-LED, verbunden mit der rechten Buchse](../../../../../translated_images/de/wio-led.265a1897e72d7f21.webp)

## Programmiere das Nachtlicht

Das Nachtlicht kann jetzt mit dem eingebauten Lichtsensor und der Grove-LED programmiert werden.

### Aufgabe - Programmiere das Nachtlicht

Programmiere das Nachtlicht.

1. Öffne das Nachtlicht-Projekt in VS Code, das du im vorherigen Teil dieser Aufgabe erstellt hast.

1. Füge die folgende Zeile am Ende der `setup`-Funktion hinzu:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Diese Zeile konfiguriert den Pin, der zur Kommunikation mit der LED über den Grove-Port verwendet wird.

    Der `D0`-Pin ist der digitale Pin für die rechte Grove-Buchse. Dieser Pin wird auf `OUTPUT` gesetzt, was bedeutet, dass er mit einem Aktor verbunden ist und Daten an den Pin geschrieben werden.

1. Füge den folgenden Code direkt vor der `delay`-Anweisung in der `loop`-Funktion hinzu:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Dieser Code überprüft den `light`-Wert. Wenn dieser kleiner als 300 ist, wird ein `HIGH`-Wert an den digitalen Pin `D0` gesendet. Dieses `HIGH` ist ein Wert von 1, der die LED einschaltet. Wenn der Lichtwert größer oder gleich 300 ist, wird ein `LOW`-Wert von 0 an den Pin gesendet, wodurch die LED ausgeschaltet wird.

    > 💁 Beim Senden digitaler Werte an Aktoren entspricht ein LOW-Wert 0V, und ein HIGH-Wert ist die maximale Spannung für das Gerät. Für das Wio Terminal beträgt die HIGH-Spannung 3,3V.

1. Verbinde das Wio Terminal erneut mit deinem Computer und lade den neuen Code wie zuvor hoch.

1. Öffne den Serial Monitor. Lichtwerte werden im Terminal ausgegeben.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

1. Bedecke und enthülle den Lichtsensor. Beobachte, wie die LED aufleuchtet, wenn der Lichtwert 300 oder weniger beträgt, und sich ausschaltet, wenn der Lichtwert größer als 300 ist.

![Die LED, die sich am WIO ein- und ausschaltet, wenn sich der Lichtwert ändert](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Du findest diesen Code im Ordner [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal).

😀 Dein Nachtlicht-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.