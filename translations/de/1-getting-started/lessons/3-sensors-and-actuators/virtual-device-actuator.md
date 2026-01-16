<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-25T22:07:57+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "de"
}
-->
# Baue ein Nachtlicht - Virtuelle IoT-Hardware

In diesem Teil der Lektion fügst du deinem virtuellen IoT-Gerät eine LED hinzu und nutzt sie, um ein Nachtlicht zu erstellen.

## Virtuelle Hardware

Das Nachtlicht benötigt einen Aktor, der in der CounterFit-App erstellt wird.

Der Aktor ist eine **LED**. In einem physischen IoT-Gerät wäre dies eine [Leuchtdiode](https://wikipedia.org/wiki/Leuchtdiode), die Licht abgibt, wenn Strom durch sie fließt. Dies ist ein digitaler Aktor mit zwei Zuständen: an und aus. Ein Wert von 1 schaltet die LED ein, ein Wert von 0 schaltet sie aus.

Die Logik des Nachtlichts in Pseudocode lautet:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Füge den Aktor zu CounterFit hinzu

Um eine virtuelle LED zu verwenden, musst du sie in der CounterFit-App hinzufügen.

#### Aufgabe - Füge den Aktor zu CounterFit hinzu

Füge die LED zur CounterFit-App hinzu.

1. Stelle sicher, dass die CounterFit-Web-App aus dem vorherigen Teil dieser Aufgabe läuft. Falls nicht, starte sie und füge den Lichtsensor erneut hinzu.

1. Erstelle eine LED:

    1. Wähle im Feld *Create actuator* im Bereich *Actuator* im Dropdown-Menü *Actuator type* den Eintrag *LED* aus.

    1. Setze den *Pin* auf *5*.

    1. Wähle die Schaltfläche **Add**, um die LED auf Pin 5 zu erstellen.

    ![Die LED-Einstellungen](../../../../../translated_images/de/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    Die LED wird erstellt und erscheint in der Liste der Aktoren.

    ![Die erstellte LED](../../../../../translated_images/de/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    Sobald die LED erstellt wurde, kannst du die Farbe mit dem *Color*-Picker ändern. Wähle die Schaltfläche **Set**, um die Farbe zu ändern, nachdem du sie ausgewählt hast.

### Programmiere das Nachtlicht

Das Nachtlicht kann nun mit dem CounterFit-Lichtsensor und der LED programmiert werden.

#### Aufgabe - Programmiere das Nachtlicht

Programmiere das Nachtlicht.

1. Öffne das Nachtlicht-Projekt in VS Code, das du im vorherigen Teil dieser Aufgabe erstellt hast. Beende und erstelle das Terminal neu, um sicherzustellen, dass es mit der virtuellen Umgebung läuft, falls erforderlich.

1. Öffne die Datei `app.py`.

1. Füge den folgenden Code in die Datei `app.py` ein, um eine benötigte Bibliothek zu importieren. Dieser Code sollte oben, unter den anderen `import`-Zeilen, hinzugefügt werden.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    Die Anweisung `from counterfit_shims_grove.grove_led import GroveLed` importiert die `GroveLed`-Klasse aus den CounterFit Grove Shim Python-Bibliotheken. Diese Bibliothek enthält Code, um mit einer in der CounterFit-App erstellten LED zu interagieren.

1. Füge den folgenden Code nach der `light_sensor`-Deklaration hinzu, um eine Instanz der Klasse zu erstellen, die die LED verwaltet:

    ```python
    led = GroveLed(5)
    ```

    Die Zeile `led = GroveLed(5)` erstellt eine Instanz der `GroveLed`-Klasse, die mit Pin **5** verbunden ist – dem CounterFit Grove-Pin, an dem die LED angeschlossen ist.

1. Füge eine Überprüfung innerhalb der `while`-Schleife und vor dem `time.sleep` hinzu, um die Lichtwerte zu überprüfen und die LED ein- oder auszuschalten:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Dieser Code überprüft den `light`-Wert. Wenn dieser kleiner als 300 ist, wird die `on`-Methode der `GroveLed`-Klasse aufgerufen, die einen digitalen Wert von 1 an die LED sendet und sie einschaltet. Wenn der Lichtwert größer oder gleich 300 ist, wird die `off`-Methode aufgerufen, die einen digitalen Wert von 0 an die LED sendet und sie ausschaltet.

    > 💁 Dieser Code sollte auf die gleiche Ebene eingerückt sein wie die Zeile `print('Light level:', light)`, um innerhalb der while-Schleife zu sein!

1. Führe im VS Code-Terminal den folgenden Befehl aus, um deine Python-App auszuführen:

    ```sh
    python3 app.py
    ```

    Lichtwerte werden in der Konsole ausgegeben.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Ändere die *Value*- oder *Random*-Einstellungen, um den Lichtwert über und unter 300 zu variieren. Die LED wird ein- und ausgeschaltet.

![Die LED in der CounterFit-App schaltet sich ein und aus, wenn sich der Lichtwert ändert](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Du findest diesen Code im Ordner [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device).

😀 Dein Nachtlicht-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.