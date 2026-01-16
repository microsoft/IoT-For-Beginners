<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-25T21:28:01+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "de"
}
-->
# Steuere ein Relais - Raspberry Pi

In diesem Teil der Lektion fügst du deinem Raspberry Pi ein Relais hinzu, zusätzlich zum Bodenfeuchtigkeitssensor, und steuerst es basierend auf dem Bodenfeuchtigkeitsniveau.

## Hardware

Der Raspberry Pi benötigt ein Relais.

Das Relais, das du verwenden wirst, ist ein [Grove-Relais](https://www.seeedstudio.com/Grove-Relay.html), ein normalerweise offenes Relais (das bedeutet, dass der Ausgangskreis offen oder getrennt ist, wenn kein Signal an das Relais gesendet wird), das Ausgangskreise bis zu 250V und 10A handhaben kann.

Dies ist ein digitaler Aktor und wird daher an einen digitalen Pin auf dem Grove Base Hat angeschlossen.

### Verbinde das Relais

Das Grove-Relais kann mit dem Raspberry Pi verbunden werden.

#### Aufgabe

Verbinde das Relais.

![Ein Grove-Relais](../../../../../translated_images/de/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Stecke ein Ende eines Grove-Kabels in die Buchse des Relais. Es passt nur in einer Richtung hinein.

1. Schalte den Raspberry Pi aus und verbinde das andere Ende des Grove-Kabels mit der digitalen Buchse, die mit **D5** auf dem Grove Base Hat markiert ist, der am Pi angebracht ist. Diese Buchse ist die zweite von links in der Reihe der Buchsen neben den GPIO-Pins. Lass den Bodenfeuchtigkeitssensor weiterhin mit der **A0**-Buchse verbunden.

![Das Grove-Relais ist mit der D5-Buchse verbunden, und der Bodenfeuchtigkeitssensor ist mit der A0-Buchse verbunden](../../../../../translated_images/de/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. Stecke den Bodenfeuchtigkeitssensor in die Erde, falls er nicht bereits aus der vorherigen Lektion dort steckt.

## Programmiere das Relais

Der Raspberry Pi kann nun programmiert werden, um das angeschlossene Relais zu verwenden.

### Aufgabe

Programmiere das Gerät.

1. Schalte den Pi ein und warte, bis er hochgefahren ist.

1. Öffne das `soil-moisture-sensor`-Projekt aus der letzten Lektion in VS Code, falls es nicht bereits geöffnet ist. Du wirst dieses Projekt erweitern.

1. Füge den folgenden Code in die Datei `app.py` unterhalb der bestehenden Importe ein:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Diese Anweisung importiert das `GroveRelay` aus den Grove-Python-Bibliotheken, um mit dem Grove-Relais zu interagieren.

1. Füge den folgenden Code unterhalb der Deklaration der `ADC`-Klasse hinzu, um eine `GroveRelay`-Instanz zu erstellen:

    ```python
    relay = GroveRelay(5)
    ```

    Dies erstellt ein Relais, das den Pin **D5** verwendet, den digitalen Pin, an den du das Relais angeschlossen hast.

1. Um zu testen, ob das Relais funktioniert, füge Folgendes in die `while True:`-Schleife ein:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Der Code schaltet das Relais ein, wartet 0,5 Sekunden und schaltet es dann wieder aus.

1. Führe die Python-App aus. Das Relais wird alle 10 Sekunden ein- und ausgeschaltet, mit einer halben Sekunde Verzögerung zwischen Ein- und Ausschalten. Du wirst hören, wie das Relais klickt, wenn es ein- und ausgeschaltet wird. Eine LED auf der Grove-Platine leuchtet, wenn das Relais eingeschaltet ist, und erlischt, wenn es ausgeschaltet ist.

    ![Das Relais schaltet sich ein und aus](../../../../../images/relay-turn-on-off.gif)

## Steuere das Relais basierend auf der Bodenfeuchtigkeit

Jetzt, da das Relais funktioniert, kann es in Abhängigkeit von den Bodenfeuchtigkeitswerten gesteuert werden.

### Aufgabe

Steuere das Relais.

1. Lösche die 3 Zeilen Code, die du hinzugefügt hast, um das Relais zu testen. Ersetze sie durch den folgenden Code:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Dieser Code überprüft den Bodenfeuchtigkeitswert vom Bodenfeuchtigkeitssensor. Wenn er über 450 liegt, wird das Relais eingeschaltet, und wenn er unter 450 liegt, wird es ausgeschaltet.

    > 💁 Denke daran, dass der kapazitive Bodenfeuchtigkeitssensor niedrigere Werte liest, je feuchter der Boden ist, und höhere Werte, je trockener der Boden ist.

1. Führe die Python-App aus. Du wirst sehen, wie das Relais je nach Bodenfeuchtigkeitswert ein- oder ausgeschaltet wird. Probiere es in trockener Erde aus und füge dann Wasser hinzu.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Du findest diesen Code im Ordner [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi).

😀 Dein Programm zur Steuerung eines Relais basierend auf einem Bodenfeuchtigkeitssensor war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, weisen wir darauf hin, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.