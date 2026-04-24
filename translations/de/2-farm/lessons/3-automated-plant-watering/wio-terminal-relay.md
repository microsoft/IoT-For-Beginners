# Steuerung eines Relais - Wio Terminal

In diesem Teil der Lektion fügen Sie Ihrem Wio Terminal ein Relais zusätzlich zum Bodenfeuchtigkeitssensor hinzu und steuern es basierend auf dem Bodenfeuchtigkeitsniveau.

## Hardware

Das Wio Terminal benötigt ein Relais.

Das Relais, das Sie verwenden, ist ein [Grove-Relais](https://www.seeedstudio.com/Grove-Relay.html), ein normalerweise offenes Relais (das bedeutet, dass der Ausgangskreis offen oder getrennt ist, wenn kein Signal an das Relais gesendet wird), das Ausgangskreise bis zu 250V und 10A handhaben kann.

Dies ist ein digitaler Aktuator, der an die digitalen Pins des Wio Terminals angeschlossen wird. Der kombinierte Analog-/Digital-Port ist bereits mit dem Bodenfeuchtigkeitssensor belegt, daher wird das Relais an den anderen Port angeschlossen, der ein kombinierter I²C- und Digital-Port ist.

### Relais anschließen

Das Grove-Relais kann an den digitalen Port des Wio Terminals angeschlossen werden.

#### Aufgabe

Schließen Sie das Relais an.

![Ein Grove-Relais](../../../../../translated_images/de/grove-relay.d426958ca210fbd0.webp)

1. Stecken Sie ein Ende eines Grove-Kabels in die Buchse des Relais. Es passt nur in einer Richtung hinein.

1. Verbinden Sie, während das Wio Terminal von Ihrem Computer oder einer anderen Stromquelle getrennt ist, das andere Ende des Grove-Kabels mit der linken Grove-Buchse des Wio Terminals, wenn Sie auf den Bildschirm schauen. Lassen Sie den Bodenfeuchtigkeitssensor mit der rechten Buchse verbunden.

![Das Grove-Relais ist mit der linken Buchse verbunden, und der Bodenfeuchtigkeitssensor ist mit der rechten Buchse verbunden](../../../../../translated_images/de/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.webp)

1. Stecken Sie den Bodenfeuchtigkeitssensor in die Erde, falls er nicht bereits aus der vorherigen Lektion dort steckt.

## Relais programmieren

Das Wio Terminal kann jetzt so programmiert werden, dass es das angeschlossene Relais verwendet.

### Aufgabe

Programmieren Sie das Gerät.

1. Öffnen Sie das Projekt `soil-moisture-sensor` aus der letzten Lektion in VS Code, falls es nicht bereits geöffnet ist. Sie werden dieses Projekt erweitern.

2. Es gibt keine Bibliothek für diesen Aktuator - es handelt sich um einen digitalen Aktuator, der durch ein hohes oder niedriges Signal gesteuert wird. Um ihn einzuschalten, senden Sie ein hohes Signal an den Pin (3,3V), um ihn auszuschalten, senden Sie ein niedriges Signal (0V). Sie können dies mit der eingebauten Arduino-Funktion [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/) tun. Fügen Sie zunächst Folgendes am Ende der `setup`-Funktion hinzu, um den kombinierten I²C-/Digital-Port als Ausgangspin einzurichten, der eine Spannung an das Relais sendet:

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` ist die Portnummer für den kombinierten I²C-/Digital-Port.

1. Um zu testen, ob das Relais funktioniert, fügen Sie Folgendes in die `loop`-Funktion unterhalb des letzten `delay` hinzu:

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    Der Code sendet ein hohes Signal an den Pin, an den das Relais angeschlossen ist, um es einzuschalten, wartet 500ms (eine halbe Sekunde) und sendet dann ein niedriges Signal, um das Relais auszuschalten.

1. Bauen und laden Sie den Code auf das Wio Terminal hoch.

1. Nach dem Hochladen schaltet sich das Relais alle 10 Sekunden ein und aus, mit einer halben Sekunde Verzögerung zwischen Ein- und Ausschalten. Sie werden hören, wie das Relais klickt, wenn es sich ein- und ausschaltet. Eine LED auf der Grove-Platine leuchtet, wenn das Relais eingeschaltet ist, und erlischt, wenn es ausgeschaltet ist.

    ![Das Relais schaltet sich ein und aus](../../../../../images/relay-turn-on-off.gif)

## Relais basierend auf Bodenfeuchtigkeit steuern

Jetzt, da das Relais funktioniert, kann es basierend auf den Bodenfeuchtigkeitswerten gesteuert werden.

### Aufgabe

Steuern Sie das Relais.

1. Löschen Sie die 3 Codezeilen, die Sie hinzugefügt haben, um das Relais zu testen. Ersetzen Sie sie durch den folgenden Code:

    ```cpp
    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }
    ```

    Dieser Code überprüft den Bodenfeuchtigkeitswert vom Bodenfeuchtigkeitssensor. Wenn er über 450 liegt, wird das Relais eingeschaltet, und wenn er unter 450 fällt, wird es ausgeschaltet.

    > 💁 Denken Sie daran, dass der kapazitive Bodenfeuchtigkeitssensor niedrigere Werte liest, je feuchter der Boden ist, und umgekehrt.

1. Bauen und laden Sie den Code auf das Wio Terminal hoch.

1. Überwachen Sie das Gerät über den seriellen Monitor. Sie werden sehen, wie das Relais je nach Bodenfeuchtigkeitswert ein- oder ausgeschaltet wird. Testen Sie es in trockener Erde und fügen Sie dann Wasser hinzu.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Sie finden diesen Code im Ordner [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal).

😀 Ihr Programm zur Steuerung eines Relais basierend auf einem Bodenfeuchtigkeitssensor war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.