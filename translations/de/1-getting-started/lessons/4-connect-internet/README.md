# Verbinden Sie Ihr Gerät mit dem Internet

![Eine Sketchnote-Übersicht dieser Lektion](../../../../../translated_images/de/lesson-4.7344e074ea68fa54.webp)

> Sketchnote von [Nitya Narasimhan](https://github.com/nitya). Klicken Sie auf das Bild für eine größere Version.

Diese Lektion wurde als Teil der [Hello IoT-Serie](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) vom [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) unterrichtet. Die Lektion wurde in zwei Videos unterteilt - eine einstündige Lektion und eine einstündige Sprechstunde, in der tiefer auf Teile der Lektion eingegangen und Fragen beantwortet wurden.

[![Lektion 4: Verbinden Sie Ihr Gerät mit dem Internet](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Lektion 4: Verbinden Sie Ihr Gerät mit dem Internet - Sprechstunde](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Klicken Sie auf die Bilder oben, um die Videos anzusehen

## Quiz vor der Lektion

[Quiz vor der Lektion](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Einführung

Das **I** in IoT steht für **Internet** – die Cloud-Konnektivität und -Dienste, die viele Funktionen von IoT-Geräten ermöglichen, von der Erfassung von Messwerten der mit dem Gerät verbundenen Sensoren bis hin zum Senden von Nachrichten zur Steuerung der Aktoren. IoT-Geräte verbinden sich typischerweise mit einem einzigen Cloud-IoT-Dienst über ein standardisiertes Kommunikationsprotokoll, und dieser Dienst ist mit dem Rest Ihrer IoT-Anwendung verbunden, von KI-Diensten zur intelligenten Entscheidungsfindung über Ihre Daten bis hin zu Webanwendungen für Steuerung oder Berichterstattung.

> 🎓 Daten, die von Sensoren erfasst und an die Cloud gesendet werden, nennt man Telemetrie.

IoT-Geräte können Nachrichten von der Cloud empfangen. Oft enthalten diese Nachrichten Befehle – also Anweisungen, eine Aktion entweder intern (wie Neustart oder Firmware-Update) oder mithilfe eines Aktors (wie das Einschalten einer Lampe) auszuführen.

Diese Lektion führt einige der Kommunikationsprotokolle ein, die IoT-Geräte verwenden können, um sich mit der Cloud zu verbinden, sowie die Arten von Daten, die sie senden oder empfangen könnten. Sie werden auch praktisch mit diesen Protokollen arbeiten, indem Sie die Internetsteuerung zu Ihrem Nachtlicht hinzufügen und die LED-Steuerungslogik in 'Server'-Code verlagern, der lokal ausgeführt wird.

In dieser Lektion behandeln wir:

* [Kommunikationsprotokolle](../../../../../1-getting-started/lessons/4-connect-internet)
* [Message Queueing Telemetry Transport (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetrie](../../../../../1-getting-started/lessons/4-connect-internet)
* [Befehle](../../../../../1-getting-started/lessons/4-connect-internet)

## Kommunikationsprotokolle

Es gibt eine Reihe beliebter Kommunikationsprotokolle, die von IoT-Geräten verwendet werden, um mit dem Internet zu kommunizieren. Die beliebtesten basieren auf Publish/Subscribe-Messaging über eine Art Broker. Die IoT-Geräte verbinden sich mit dem Broker und veröffentlichen Telemetrie und abonnieren Befehle. Die Cloud-Dienste verbinden sich ebenfalls mit dem Broker, abonnieren alle Telemetrie-Nachrichten und veröffentlichen Befehle entweder an bestimmte Geräte oder an Gruppen von Geräten.

![IoT-Geräte verbinden sich mit einem Broker, veröffentlichen Telemetrie und abonnieren Befehle. Cloud-Dienste verbinden sich mit dem Broker, abonnieren alle Telemetrie und senden Befehle an bestimmte Geräte.](../../../../../translated_images/de/pub-sub.7c7ed43fe9fd15d4.webp)

MQTT ist das beliebteste Kommunikationsprotokoll für IoT-Geräte und wird in dieser Lektion behandelt. Andere Protokolle umfassen AMQP und HTTP/HTTPS.

## Message Queueing Telemetry Transport (MQTT)

[MQTT](http://mqtt.org) ist ein leichtgewichtiges, offenes Standard-Messaging-Protokoll, das Nachrichten zwischen Geräten senden kann. Es wurde 1999 entwickelt, um Öl-Pipelines zu überwachen, und 15 Jahre später von IBM als offener Standard veröffentlicht.

MQTT hat einen einzigen Broker und mehrere Clients. Alle Clients verbinden sich mit dem Broker, und der Broker leitet Nachrichten an die relevanten Clients weiter. Nachrichten werden über benannte Themen (Topics) geroutet, anstatt direkt an einen einzelnen Client gesendet zu werden. Ein Client kann ein Thema veröffentlichen, und alle Clients, die dieses Thema abonniert haben, erhalten die Nachricht.

![IoT-Gerät veröffentlicht Telemetrie auf dem /telemetry-Thema, und der Cloud-Dienst abonniert dieses Thema](../../../../../translated_images/de/mqtt.cbf7f21d9adc3e17.webp)

✅ Recherchieren Sie. Wenn Sie viele IoT-Geräte haben, wie können Sie sicherstellen, dass Ihr MQTT-Broker alle Nachrichten verarbeiten kann?

### Verbinden Sie Ihr IoT-Gerät mit MQTT

Der erste Schritt, um die Internetsteuerung zu Ihrem Nachtlicht hinzuzufügen, besteht darin, es mit einem MQTT-Broker zu verbinden.

#### Aufgabe

Verbinden Sie Ihr Gerät mit einem MQTT-Broker.

In diesem Teil der Lektion verbinden Sie Ihr IoT-Nachtlicht mit dem Internet, um es fernzusteuern. Später in dieser Lektion wird Ihr IoT-Gerät eine Telemetrie-Nachricht über MQTT an einen öffentlichen MQTT-Broker mit dem Lichtpegel senden, wo sie von einem Server-Code abgeholt wird, den Sie schreiben werden. Dieser Code überprüft den Lichtpegel und sendet eine Befehlsnachricht zurück an das Gerät, die ihm mitteilt, ob die LED ein- oder ausgeschaltet werden soll.

Ein realer Anwendungsfall für ein solches Setup könnte darin bestehen, Daten von mehreren Lichtsensoren zu sammeln, bevor entschieden wird, ob die Lichter eingeschaltet werden sollen, an einem Ort mit vielen Lichtern, wie einem Stadion. Dies könnte verhindern, dass die Lichter eingeschaltet werden, wenn nur ein Sensor von Wolken oder einem Vogel verdeckt ist, die anderen Sensoren jedoch genügend Licht erkennen.

✅ Welche anderen Situationen erfordern die Auswertung von Daten aus mehreren Sensoren, bevor Befehle gesendet werden?

Anstatt sich mit den Komplexitäten der Einrichtung eines MQTT-Brokers im Rahmen dieser Aufgabe zu befassen, können Sie einen öffentlichen Testserver verwenden, der [Eclipse Mosquitto](https://www.mosquitto.org), einen Open-Source-MQTT-Broker, ausführt. Dieser Test-Broker ist öffentlich verfügbar unter [test.mosquitto.org](https://test.mosquitto.org) und erfordert kein Konto, was ihn zu einem großartigen Werkzeug für das Testen von MQTT-Clients und -Servern macht.

> 💁 Dieser Test-Broker ist öffentlich und nicht sicher. Jeder könnte zuhören, was Sie veröffentlichen, daher sollte er nicht mit Daten verwendet werden, die privat bleiben müssen.

![Ein Flussdiagramm der Aufgabe, das zeigt, wie Lichtpegel gelesen und überprüft werden und die LED gesteuert wird](../../../../../translated_images/de/assignment-1-internet-flow.3256feab5f052fd2.webp)

Folgen Sie dem entsprechenden Schritt unten, um Ihr Gerät mit dem MQTT-Broker zu verbinden:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Einplatinencomputer - Raspberry Pi/virtuelles IoT-Gerät](single-board-computer-mqtt.md)

### Ein tieferer Einblick in MQTT

Themen können eine Hierarchie haben, und Clients können verschiedene Ebenen der Hierarchie mit Platzhaltern abonnieren. Zum Beispiel können Sie Temperatur-Telemetrie-Nachrichten an das Thema `/telemetry/temperature` senden und Feuchtigkeits-Nachrichten an das Thema `/telemetry/humidity`, und dann in Ihrer Cloud-App das Thema `/telemetry/*` abonnieren, um sowohl die Temperatur- als auch die Feuchtigkeits-Telemetrie-Nachrichten zu empfangen.

Nachrichten können mit einer Qualität des Dienstes (QoS) gesendet werden, die die Garantie für den Empfang der Nachricht bestimmt.

* Höchstens einmal – die Nachricht wird nur einmal gesendet, und der Client und Broker unternehmen keine zusätzlichen Schritte, um die Zustellung zu bestätigen (Fire-and-Forget).
* Mindestens einmal – die Nachricht wird vom Sender mehrmals wiederholt, bis eine Bestätigung empfangen wird (bestätigte Zustellung).
* Genau einmal – der Sender und Empfänger führen einen Zwei-Level-Handshake durch, um sicherzustellen, dass nur eine Kopie der Nachricht empfangen wird (gesicherte Zustellung).

✅ Welche Situationen könnten eine gesicherte Zustellung über eine Fire-and-Forget-Nachricht erfordern?

Obwohl der Name Message Queueing (MQTT) lautet, unterstützt es tatsächlich keine Nachrichtenwarteschlangen. Das bedeutet, dass ein Client, der sich trennt und dann wieder verbindet, keine Nachrichten empfängt, die während der Trennung gesendet wurden, außer denen, die er bereits mit dem QoS-Prozess zu verarbeiten begonnen hat. Nachrichten können ein Retained-Flag gesetzt haben. Wenn dies gesetzt ist, speichert der MQTT-Broker die letzte Nachricht, die mit diesem Flag an ein Thema gesendet wurde, und sendet diese an alle Clients, die später das Thema abonnieren. Auf diese Weise erhalten die Clients immer die neueste Nachricht.

MQTT unterstützt auch eine Keep-Alive-Funktion, die überprüft, ob die Verbindung während langer Pausen zwischen Nachrichten noch aktiv ist.

> 🦟 [Mosquitto von der Eclipse Foundation](https://mosquitto.org) bietet einen kostenlosen MQTT-Broker, den Sie selbst ausführen können, um mit MQTT zu experimentieren, sowie einen öffentlichen MQTT-Broker, den Sie zum Testen Ihres Codes verwenden können, gehostet unter [test.mosquitto.org](https://test.mosquitto.org).

MQTT-Verbindungen können öffentlich und offen oder verschlüsselt und gesichert mit Benutzernamen und Passwörtern oder Zertifikaten sein.

> 💁 MQTT kommuniziert über TCP/IP, dasselbe zugrunde liegende Netzwerkprotokoll wie HTTP, jedoch auf einem anderen Port. Sie können MQTT auch über Websockets verwenden, um mit Webanwendungen zu kommunizieren, die in einem Browser ausgeführt werden, oder in Situationen, in denen Firewalls oder andere Netzwerkregeln Standard-MQTT-Verbindungen blockieren.

## Telemetrie

Das Wort Telemetrie stammt aus griechischen Wurzeln und bedeutet "fernmessen". Telemetrie ist der Vorgang, Daten von Sensoren zu erfassen und an die Cloud zu senden.

> 💁 Eines der frühesten Telemetriegeräte wurde 1874 in Frankreich erfunden und sendete Echtzeit-Wetter- und Schneetiefeninformationen von Mont Blanc nach Paris. Es verwendete physische Drähte, da drahtlose Technologien zu dieser Zeit nicht verfügbar waren.

Schauen wir uns das Beispiel des intelligenten Thermostats aus Lektion 1 an.

![Ein internetverbundener Thermostat mit mehreren Raumsensoren](../../../../../translated_images/de/telemetry.21e5d8b97649d2eb.webp)

Der Thermostat verfügt über Temperatursensoren zur Erfassung von Telemetrie. Höchstwahrscheinlich hat er einen eingebauten Temperatursensor und könnte sich mit mehreren externen Temperatursensoren über ein drahtloses Protokoll wie [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE) verbinden.

Ein Beispiel für die Telemetriedaten, die er senden könnte, wäre:

| Name | Wert | Beschreibung |
| ---- | ----- | ----------- |
| `thermostat_temperature` | 18°C | Die Temperatur, die vom eingebauten Temperatursensor des Thermostats gemessen wurde |
| `livingroom_temperature` | 19°C | Die Temperatur, die von einem entfernten Temperatursensor gemessen wurde, der als `livingroom` benannt wurde, um den Raum zu identifizieren, in dem er sich befindet |
| `bedroom_temperature` | 21°C | Die Temperatur, die von einem entfernten Temperatursensor gemessen wurde, der als `bedroom` benannt wurde, um den Raum zu identifizieren, in dem er sich befindet |

Der Cloud-Dienst kann dann diese Telemetriedaten verwenden, um Entscheidungen darüber zu treffen, welche Befehle zur Steuerung der Heizung gesendet werden sollen.

### Senden Sie Telemetrie von Ihrem IoT-Gerät

Der nächste Schritt, um die Internetsteuerung zu Ihrem Nachtlicht hinzuzufügen, besteht darin, die Lichtpegel-Telemetrie an den MQTT-Broker auf einem Telemetrie-Thema zu senden.

#### Aufgabe - Senden Sie Telemetrie von Ihrem IoT-Gerät

Senden Sie Lichtpegel-Telemetrie an den MQTT-Broker.

Daten werden als JSON codiert gesendet – kurz für JavaScript Object Notation, ein Standard zur Codierung von Daten in Textform mit Schlüssel/Wert-Paaren.

✅ Wenn Sie JSON noch nicht kennen, können Sie mehr darüber in der [JSON.org-Dokumentation](https://www.json.org/) erfahren.

Folgen Sie dem entsprechenden Schritt unten, um Telemetrie von Ihrem Gerät an den MQTT-Broker zu senden:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Einplatinencomputer - Raspberry Pi/virtuelles IoT-Gerät](single-board-computer-telemetry.md)

### Empfangen Sie Telemetrie vom MQTT-Broker

Es hat keinen Sinn, Telemetrie zu senden, wenn niemand am anderen Ende zuhört. Die Lichtpegel-Telemetrie benötigt etwas, das sie empfängt und verarbeitet. Dieser 'Server'-Code ist die Art von Code, die Sie als Teil einer größeren IoT-Anwendung auf einen Cloud-Dienst bereitstellen würden, aber hier werden Sie diesen Code lokal auf Ihrem Computer ausführen (oder auf Ihrem Pi, wenn Sie direkt darauf programmieren). Der Server-Code besteht aus einer Python-App, die Telemetrie-Nachrichten über MQTT mit Lichtpegeln empfängt. Später in dieser Lektion werden Sie ihn so konfigurieren, dass er mit einer Befehlsnachricht antwortet, die Anweisungen enthält, die LED ein- oder auszuschalten.

✅ Recherchieren Sie: Was passiert mit MQTT-Nachrichten, wenn es keinen Listener gibt?

#### Installieren Sie Python und VS Code

Wenn Sie Python und VS Code nicht lokal installiert haben, müssen Sie beide installieren, um den Server zu programmieren. Wenn Sie ein virtuelles IoT-Gerät verwenden oder auf Ihrem Raspberry Pi arbeiten, können Sie diesen Schritt überspringen, da Sie dies bereits installiert und konfiguriert haben sollten.

##### Aufgabe - Installieren Sie Python und VS Code

Installieren Sie Python und VS Code.

1. Installieren Sie Python. Besuchen Sie die [Python-Download-Seite](https://www.python.org/downloads/) für Anweisungen zur Installation der neuesten Version von Python.

1. Installieren Sie Visual Studio Code (VS Code). Dies ist der Editor, den Sie verwenden werden, um Ihren virtuellen Gerätecode in Python zu schreiben. Besuchen Sie die [VS Code-Dokumentation](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) für Anweisungen zur Installation von VS Code.
💁 Du kannst gerne jede beliebige Python-IDE oder jeden Editor für diese Lektionen verwenden, falls du ein bevorzugtes Tool hast, aber die Lektionen basieren auf Anweisungen für die Nutzung von VS Code.
1. Installieren Sie die VS Code Pylance-Erweiterung. Dies ist eine Erweiterung für VS Code, die Unterstützung für die Programmiersprache Python bietet. Lesen Sie die [Pylance-Erweiterungsdokumentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance), um Anweisungen zur Installation dieser Erweiterung in VS Code zu erhalten.

#### Konfigurieren einer Python-virtuellen Umgebung

Eine der leistungsstarken Funktionen von Python ist die Möglichkeit, [pip-Pakete](https://pypi.org) zu installieren – das sind Codepakete, die von anderen Personen geschrieben und im Internet veröffentlicht wurden. Sie können ein pip-Paket mit einem einzigen Befehl auf Ihrem Computer installieren und dieses Paket dann in Ihrem Code verwenden. Sie werden pip verwenden, um ein Paket zu installieren, das die Kommunikation über MQTT ermöglicht.

Standardmäßig ist ein installiertes Paket überall auf Ihrem Computer verfügbar, was zu Problemen mit Paketversionen führen kann – beispielsweise wenn eine Anwendung von einer Version eines Pakets abhängt, die nicht mehr funktioniert, nachdem Sie eine neue Version für eine andere Anwendung installiert haben. Um dieses Problem zu umgehen, können Sie eine [Python-virtuelle Umgebung](https://docs.python.org/3/library/venv.html) verwenden, im Wesentlichen eine Kopie von Python in einem dedizierten Ordner. Wenn Sie pip-Pakete installieren, werden diese nur in diesem Ordner installiert.

##### Aufgabe – Konfigurieren einer Python-virtuellen Umgebung

Konfigurieren Sie eine Python-virtuelle Umgebung und installieren Sie die MQTT-pip-Pakete.

1. Führen Sie in Ihrem Terminal oder Ihrer Befehlszeile Folgendes an einem Ort Ihrer Wahl aus, um ein neues Verzeichnis zu erstellen und zu diesem zu navigieren:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Führen Sie nun Folgendes aus, um eine virtuelle Umgebung im Ordner `.venv` zu erstellen:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Sie müssen explizit `python3` aufrufen, um die virtuelle Umgebung zu erstellen, falls Sie Python 2 zusätzlich zu Python 3 (der neuesten Version) installiert haben. Wenn Python 2 installiert ist, wird durch den Aufruf von `python` Python 2 anstelle von Python 3 verwendet.

1. Aktivieren Sie die virtuelle Umgebung:

    * Unter Windows:
        * Wenn Sie die Eingabeaufforderung oder die Eingabeaufforderung über Windows Terminal verwenden, führen Sie Folgendes aus:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Wenn Sie PowerShell verwenden, führen Sie Folgendes aus:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Unter macOS oder Linux führen Sie Folgendes aus:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Diese Befehle sollten von demselben Ort aus ausgeführt werden, an dem Sie den Befehl zum Erstellen der virtuellen Umgebung ausgeführt haben. Sie müssen niemals in den `.venv`-Ordner navigieren, sondern sollten immer den Aktivierungsbefehl und alle Befehle zum Installieren von Paketen oder Ausführen von Code von dem Ordner aus ausführen, in dem Sie die virtuelle Umgebung erstellt haben.

1. Sobald die virtuelle Umgebung aktiviert ist, wird der Standardbefehl `python` die Version von Python ausführen, die zum Erstellen der virtuellen Umgebung verwendet wurde. Führen Sie Folgendes aus, um die Version zu überprüfen:

    ```sh
    python --version
    ```

    Die Ausgabe wird ähnlich wie folgt aussehen:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Ihre Python-Version kann unterschiedlich sein – solange es Version 3.6 oder höher ist, ist alles in Ordnung. Wenn nicht, löschen Sie diesen Ordner, installieren Sie eine neuere Version von Python und versuchen Sie es erneut.

1. Führen Sie die folgenden Befehle aus, um das pip-Paket für [Paho-MQTT](https://pypi.org/project/paho-mqtt/), eine beliebte MQTT-Bibliothek, zu installieren:

    ```sh
    pip install paho-mqtt
    ```

    Dieses pip-Paket wird nur in der virtuellen Umgebung installiert und ist außerhalb dieser nicht verfügbar.

#### Schreiben des Servercodes

Der Servercode kann nun in Python geschrieben werden.

##### Aufgabe – Schreiben des Servercodes

Schreiben Sie den Servercode.

1. Führen Sie in Ihrem Terminal oder Ihrer Befehlszeile Folgendes innerhalb der virtuellen Umgebung aus, um eine Python-Datei namens `app.py` zu erstellen:

    * Unter Windows führen Sie Folgendes aus:

        ```cmd
        type nul > app.py
        ```

    * Unter macOS oder Linux führen Sie Folgendes aus:

        ```cmd
        touch app.py
        ```

1. Öffnen Sie den aktuellen Ordner in VS Code:

    ```sh
    code .
    ```

1. Wenn VS Code startet, wird die Python-virtuelle Umgebung aktiviert. Dies wird in der unteren Statusleiste angezeigt:

    ![VS Code zeigt die ausgewählte virtuelle Umgebung an](../../../../../translated_images/de/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Wenn das VS Code-Terminal bereits läuft, wenn VS Code gestartet wird, wird die virtuelle Umgebung darin nicht aktiviert. Am einfachsten ist es, das Terminal mit der Schaltfläche **Aktives Terminal schließen** zu beenden:

    ![VS Code-Schaltfläche zum Schließen des aktiven Terminals](../../../../../translated_images/de/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

1. Starten Sie ein neues VS Code-Terminal, indem Sie *Terminal -> Neues Terminal* auswählen oder `` CTRL+` `` drücken. Das neue Terminal lädt die virtuelle Umgebung, wobei der Aktivierungsaufruf im Terminal erscheint. Der Name der virtuellen Umgebung (`.venv`) wird ebenfalls in der Eingabeaufforderung angezeigt:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Öffnen Sie die Datei `app.py` aus dem VS Code-Explorer und fügen Sie den folgenden Code hinzu:

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    Ersetzen Sie `<ID>` in Zeile 6 durch die eindeutige ID, die Sie beim Erstellen Ihres Gerätecodes verwendet haben.

    ⚠️ Diese **muss** dieselbe ID sein, die Sie auf Ihrem Gerät verwendet haben, sonst wird der Servercode nicht auf die richtigen Themen abonnieren oder veröffentlichen.

    Dieser Code erstellt einen MQTT-Client mit einem eindeutigen Namen und verbindet sich mit dem Broker *test.mosquitto.org*. Anschließend wird eine Verarbeitungsschleife gestartet, die in einem Hintergrundthread läuft und Nachrichten zu abonnierten Themen empfängt.

    Der Client abonniert dann Nachrichten zum Telemetrie-Thema und definiert eine Funktion, die aufgerufen wird, wenn eine Nachricht empfangen wird. Wenn eine Telemetrie-Nachricht empfangen wird, wird die Funktion `handle_telemetry` aufgerufen, die die empfangene Nachricht in der Konsole ausgibt.

    Schließlich hält eine Endlosschleife die Anwendung am Laufen. Der MQTT-Client hört auf Nachrichten in einem Hintergrundthread und läuft die ganze Zeit, während die Hauptanwendung läuft.

1. Führen Sie im VS Code-Terminal Folgendes aus, um Ihre Python-App auszuführen:

    ```sh
    python app.py
    ```

    Die App beginnt, Nachrichten vom IoT-Gerät zu empfangen.

1. Stellen Sie sicher, dass Ihr Gerät läuft und Telemetrie-Nachrichten sendet. Passen Sie die Lichtstärken an, die von Ihrem physischen oder virtuellen Gerät erkannt werden. Empfangene Nachrichten werden im Terminal ausgegeben.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    Die Datei `app.py` in der virtuellen Umgebung des Nachtlichts muss laufen, damit die Datei `app.py` in der virtuellen Umgebung des Nachtlicht-Servers die gesendeten Nachrichten empfangen kann.

> 💁 Sie finden diesen Code im Ordner [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server).

### Wie oft sollte Telemetrie gesendet werden?

Eine wichtige Überlegung bei Telemetrie ist, wie oft die Daten gemessen und gesendet werden sollten. Die Antwort lautet: Es kommt darauf an. Wenn Sie häufig messen, können Sie schneller auf Änderungen reagieren, aber Sie verbrauchen mehr Energie, mehr Bandbreite, erzeugen mehr Daten und benötigen mehr Cloud-Ressourcen zur Verarbeitung. Sie müssen oft genug messen, aber nicht zu oft.

Für ein Thermostat reicht es wahrscheinlich aus, alle paar Minuten zu messen, da sich Temperaturen nicht so häufig ändern. Wenn Sie nur einmal am Tag messen, könnten Sie Ihr Haus für Nachttemperaturen mitten an einem sonnigen Tag heizen, während Sie bei einer Messung jede Sekunde Tausende unnötig duplizierter Temperaturmessungen erhalten, die die Internetgeschwindigkeit und Bandbreite der Benutzer beeinträchtigen (ein Problem für Menschen mit begrenzten Bandbreitenplänen), mehr Energie verbrauchen, was ein Problem für batteriebetriebene Geräte wie Fernsensoren sein kann, und die Kosten für die Cloud-Computing-Ressourcen des Anbieters erhöhen, die diese verarbeiten und speichern.

Wenn Sie Daten rund um eine Maschine in einer Fabrik überwachen, deren Ausfall katastrophale Schäden und Millionen von Dollar an Einnahmeverlusten verursachen könnte, könnte es notwendig sein, mehrmals pro Sekunde zu messen. Es ist besser, Bandbreite zu verschwenden, als Telemetrie zu verpassen, die darauf hinweist, dass eine Maschine gestoppt und repariert werden muss, bevor sie kaputt geht.

> 💁 In dieser Situation könnten Sie in Betracht ziehen, ein Edge-Gerät zu verwenden, um die Telemetrie zuerst zu verarbeiten und die Abhängigkeit vom Internet zu reduzieren.

### Verlust der Konnektivität

Internetverbindungen können unzuverlässig sein, mit häufigen Ausfällen. Was sollte ein IoT-Gerät unter diesen Umständen tun – sollte es die Daten verlieren oder speichern, bis die Konnektivität wiederhergestellt ist? Auch hier lautet die Antwort: Es kommt darauf an.

Für ein Thermostat können die Daten wahrscheinlich verloren gehen, sobald eine neue Temperaturmessung durchgeführt wurde. Das Heizsystem interessiert sich nicht dafür, dass es vor 20 Minuten 20,5°C war, wenn die Temperatur jetzt 19°C beträgt. Es ist die aktuelle Temperatur, die bestimmt, ob die Heizung ein- oder ausgeschaltet werden sollte.

Für Maschinen möchten Sie möglicherweise die Daten behalten, insbesondere wenn sie verwendet werden, um Trends zu erkennen. Es gibt maschinelle Lernmodelle, die Anomalien in Datenströmen erkennen können, indem sie Daten über einen definierten Zeitraum (z. B. die letzte Stunde) betrachten und anomale Daten erkennen. Dies wird häufig für die vorausschauende Wartung verwendet, um Hinweise darauf zu finden, dass etwas bald kaputt gehen könnte, damit Sie es reparieren oder ersetzen können, bevor das passiert. Sie möchten möglicherweise jede Telemetrie für eine Maschine senden, damit sie zur Anomalieerkennung verarbeitet werden kann. Sobald das IoT-Gerät wieder eine Verbindung herstellen kann, sendet es alle während des Internetausfalls generierten Telemetrie-Daten.

IoT-Geräteentwickler sollten auch berücksichtigen, ob das IoT-Gerät während eines Internetausfalls oder eines Signalverlusts aufgrund des Standorts verwendet werden kann. Ein intelligentes Thermostat sollte in der Lage sein, einige begrenzte Entscheidungen zur Steuerung der Heizung zu treffen, wenn es aufgrund eines Ausfalls keine Telemetrie an die Cloud senden kann.

[![Dieser Ferrari wurde unbrauchbar, weil jemand versucht hat, ihn unterirdisch zu aktualisieren, wo es keinen Mobilfunkempfang gibt](../../../../../translated_images/de/bricked-car.dc38f8efadc6c59d.webp)](https://twitter.com/internetofshit/status/1315736960082808832)

Damit MQTT einen Verlust der Konnektivität bewältigen kann, müssen das Geräte- und der Servercode dafür verantwortlich sein, die Nachrichtenübermittlung sicherzustellen, falls dies erforderlich ist, beispielsweise durch die Anforderung, dass alle gesendeten Nachrichten durch zusätzliche Nachrichten zu einem Antwortthema beantwortet werden, und falls nicht, werden sie manuell in eine Warteschlange gestellt, um später erneut abgespielt zu werden.

## Befehle

Befehle sind Nachrichten, die von der Cloud an ein Gerät gesendet werden, um es anzuweisen, etwas zu tun. Meistens geht es darum, eine Art Ausgabe über einen Aktuator zu geben, aber es kann auch eine Anweisung für das Gerät selbst sein, wie z. B. einen Neustart durchzuführen oder zusätzliche Telemetrie zu sammeln und als Antwort auf den Befehl zurückzugeben.

![Ein internetverbundenes Thermostat, das einen Befehl erhält, die Heizung einzuschalten](../../../../../translated_images/de/commands.d6c06bbbb3a02cce.webp)

Ein Thermostat könnte einen Befehl von der Cloud erhalten, die Heizung einzuschalten. Basierend auf den Telemetriedaten aller Sensoren hat der Cloud-Dienst entschieden, dass die Heizung eingeschaltet werden sollte, und sendet daher den entsprechenden Befehl.

### Befehle an den MQTT-Broker senden

Der nächste Schritt für unser internetgesteuertes Nachtlicht besteht darin, dass der Servercode einen Befehl zurück an das IoT-Gerät sendet, um das Licht basierend auf den erkannten Lichtstärken zu steuern.

1. Öffnen Sie den Servercode in VS Code.

1. Fügen Sie nach der Deklaration des `client_telemetry_topic` die folgende Zeile hinzu, um festzulegen, welches Thema für das Senden von Befehlen verwendet werden soll:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Fügen Sie am Ende der Funktion `handle_telemetry` den folgenden Code hinzu:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Dies sendet eine JSON-Nachricht an das Befehls-Thema mit dem Wert von `led_on`, der auf true oder false gesetzt wird, je nachdem, ob das Licht weniger als 300 beträgt oder nicht. Wenn das Licht weniger als 300 beträgt, wird true gesendet, um das Gerät anzuweisen, die LED einzuschalten.

1. Führen Sie den Code wie zuvor aus.

1. Passen Sie die Lichtstärken an, die von Ihrem physischen oder virtuellen Gerät erkannt werden. Empfangene Nachrichten und gesendete Befehle werden im Terminal ausgegeben:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 Die Telemetrie und Befehle werden jeweils über ein einzelnes Thema gesendet. Das bedeutet, dass Telemetrie von mehreren Geräten im selben Telemetrie-Thema erscheint und Befehle an mehrere Geräte im selben Befehls-Thema erscheinen. Wenn Sie einen Befehl an ein bestimmtes Gerät senden möchten, könnten Sie mehrere Themen verwenden, die mit einer eindeutigen Geräte-ID benannt sind, wie `/commands/device1`, `/commands/device2`. Auf diese Weise kann ein Gerät Nachrichten hören, die nur für dieses eine Gerät bestimmt sind.

> 💁 Sie finden diesen Code im Ordner [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server).

### Befehle auf dem IoT-Gerät verarbeiten

Da nun Befehle vom Server gesendet werden, können Sie jetzt Code zum IoT-Gerät hinzufügen, um diese zu verarbeiten und die LED zu steuern.

Folgen Sie dem entsprechenden Schritt unten, um Befehle vom MQTT-Broker zu empfangen:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Einplatinencomputer - Raspberry Pi/virtuelles IoT-Gerät](single-board-computer-commands.md)

Sobald dieser Code geschrieben und ausgeführt wird, experimentieren Sie mit der Änderung der Lichtstärken. Beobachten Sie die Ausgabe vom Server und Gerät und beobachten Sie die LED, während Sie die Lichtstärken ändern.

### Verlust der Konnektivität

Was sollte ein Cloud-Dienst tun, wenn er einen Befehl an ein IoT-Gerät senden muss, das offline ist? Auch hier lautet die Antwort: Es kommt darauf an.

Wenn der neueste Befehl einen früheren überschreibt, können die früheren wahrscheinlich ignoriert werden. Wenn ein Cloud-Dienst einen Befehl sendet, die Heizung einzuschalten, und dann einen Befehl sendet, sie auszuschalten, kann der Einschaltbefehl ignoriert und nicht erneut gesendet werden.

Wenn die Befehle in einer bestimmten Reihenfolge verarbeitet werden müssen, wie z. B. das Bewegen eines Roboterarms nach oben und dann das Schließen eines Greifers, müssen sie in der richtigen Reihenfolge gesendet werden, sobald die Konnektivität wiederhergestellt ist.

✅ Wie könnte der Geräte- oder Servercode sicherstellen, dass Befehle immer in der richtigen Reihenfolge über MQTT gesendet und verarbeitet werden, falls erforderlich?

---

## 🚀 Herausforderung

Die Herausforderung in den letzten drei Lektionen bestand darin, so viele IoT-Geräte wie möglich zu identifizieren, die sich in Ihrem Zuhause, Ihrer Schule oder Ihrem Arbeitsplatz befinden, und zu entscheiden, ob sie auf Mikrocontrollern oder Einplatinencomputern oder sogar einer Mischung aus beiden basieren, und darüber nachzudenken, welche Sensoren und Aktoren sie verwenden.
Für diese Geräte, überlegen Sie, welche Nachrichten sie möglicherweise senden oder empfangen. Welche Telemetriedaten senden sie? Welche Nachrichten oder Befehle könnten sie empfangen? Denken Sie, dass sie sicher sind?

## Quiz nach der Vorlesung

[Quiz nach der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Überprüfung & Selbststudium

Lesen Sie mehr über MQTT auf der [MQTT Wikipedia-Seite](https://wikipedia.org/wiki/MQTT).

Versuchen Sie, selbst einen MQTT-Broker mit [Mosquitto](https://www.mosquitto.org) auszuführen, und verbinden Sie sich mit Ihrem IoT-Gerät und Server-Code.

> 💁 Tipp - Standardmäßig erlaubt Mosquitto keine anonymen Verbindungen (also Verbindungen ohne Benutzername und Passwort) und keine Verbindungen von außerhalb des Computers, auf dem es läuft.  
> Sie können dies mit einer [`mosquitto.conf` Konfigurationsdatei](https://www.mosquitto.org/man/mosquitto-conf-5.html) wie folgt beheben:
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Aufgabe

[Vergleichen und kontrastieren Sie MQTT mit anderen Kommunikationsprotokollen](assignment.md)

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.