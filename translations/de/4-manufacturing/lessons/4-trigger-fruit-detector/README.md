# Auslösen der Obstqualitätsprüfung durch einen Sensor

![Eine Sketchnote-Übersicht dieser Lektion](../../../../../translated_images/de/lesson-18.92c32ed1d354caa5.webp)

> Sketchnote von [Nitya Narasimhan](https://github.com/nitya). Klicken Sie auf das Bild für eine größere Version.

## Quiz vor der Vorlesung

[Quiz vor der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Einführung

Eine IoT-Anwendung besteht nicht nur aus einem einzelnen Gerät, das Daten erfasst und in die Cloud sendet. Häufig arbeiten mehrere Geräte zusammen, um Daten aus der physischen Welt mit Sensoren zu erfassen, Entscheidungen auf Basis dieser Daten zu treffen und über Aktoren oder Visualisierungen wieder mit der physischen Welt zu interagieren.

In dieser Lektion lernen Sie mehr über die Architektur komplexer IoT-Anwendungen, die Integration mehrerer Sensoren und Cloud-Dienste zur Analyse und Speicherung von Daten sowie die Anzeige einer Reaktion über einen Aktor. Sie erfahren, wie Sie einen Prototyp für ein Obstqualitätskontrollsystem entwerfen, einschließlich der Verwendung von Näherungssensoren zur Auslösung der IoT-Anwendung und der Architektur dieses Prototyps.

In dieser Lektion behandeln wir:

* [Komplexe IoT-Anwendungen entwerfen](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Ein Obstqualitätskontrollsystem entwerfen](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Obstqualitätsprüfung durch einen Sensor auslösen](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Daten für einen Obstqualitätsdetektor verwenden](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Entwicklergeräte zur Simulation mehrerer IoT-Geräte verwenden](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Übergang zur Produktion](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 Dies ist die letzte Lektion in diesem Projekt. Vergessen Sie nach Abschluss dieser Lektion und der Aufgabe nicht, Ihre Cloud-Dienste aufzuräumen. Sie benötigen die Dienste, um die Aufgabe abzuschließen. Stellen Sie daher sicher, dass Sie diese zuerst abschließen.
>
> Falls erforderlich, finden Sie Anweisungen im [Leitfaden zur Projektbereinigung](../../../clean-up.md).

## Komplexe IoT-Anwendungen entwerfen

IoT-Anwendungen bestehen aus vielen Komponenten, darunter eine Vielzahl von Geräten und Internetdiensten.

IoT-Anwendungen können als *Dinge* (Geräte) beschrieben werden, die Daten senden, die *Erkenntnisse* generieren. Diese *Erkenntnisse* führen zu *Aktionen*, die ein Geschäft oder einen Prozess verbessern. Ein Beispiel ist ein Motor (das Ding), der Temperaturdaten sendet. Diese Daten werden verwendet, um zu bewerten, ob der Motor wie erwartet funktioniert (die Erkenntnis). Die Erkenntnis wird genutzt, um den Wartungsplan des Motors proaktiv zu priorisieren (die Aktion).

* Verschiedene Dinge erfassen unterschiedliche Daten.
* IoT-Dienste liefern Erkenntnisse über diese Daten, manchmal ergänzt durch Daten aus zusätzlichen Quellen.
* Diese Erkenntnisse treiben Aktionen an, einschließlich der Steuerung von Aktoren in Geräten oder der Visualisierung von Daten.

### Referenz-IoT-Architektur

![Eine Referenz-IoT-Architektur](../../../../../translated_images/de/iot-reference-architecture.2278b98b55c6d4e8.webp)

Das obige Diagramm zeigt eine Referenz-IoT-Architektur.

> 🎓 Eine *Referenzarchitektur* ist eine Beispielarchitektur, die Sie als Vorlage beim Entwerfen neuer Systeme verwenden können. In diesem Fall können Sie beim Aufbau eines neuen IoT-Systems der Referenzarchitektur folgen und Ihre eigenen Geräte und Dienste entsprechend ersetzen.

* **Dinge** sind Geräte, die Daten von Sensoren erfassen und möglicherweise mit Edge-Diensten interagieren, um diese Daten zu interpretieren, wie z. B. Bildklassifikatoren zur Interpretation von Bilddaten. Die Daten der Geräte werden an einen IoT-Dienst gesendet.
* **Erkenntnisse** stammen aus serverlosen Anwendungen oder aus Analysen gespeicherter Daten.
* **Aktionen** können Befehle sein, die an Geräte gesendet werden, oder die Visualisierung von Daten, die es Menschen ermöglichen, Entscheidungen zu treffen.

![Eine Referenz-IoT-Architektur](../../../../../translated_images/de/iot-reference-architecture-azure.0b8d2161af924cb1.webp)

Das obige Diagramm zeigt einige der bisher behandelten Komponenten und Dienste und wie sie in einer Referenz-IoT-Architektur miteinander verbunden sind.

* **Dinge** - Sie haben Gerätecode geschrieben, um Daten von Sensoren zu erfassen und Bilder mit Custom Vision sowohl in der Cloud als auch auf einem Edge-Gerät zu analysieren. Diese Daten wurden an IoT Hub gesendet.
* **Erkenntnisse** - Sie haben Azure Functions verwendet, um auf Nachrichten zu reagieren, die an einen IoT Hub gesendet wurden, und Daten zur späteren Analyse in Azure Storage gespeichert.
* **Aktionen** - Sie haben Aktoren basierend auf Entscheidungen gesteuert, die in der Cloud getroffen und als Befehle an die Geräte gesendet wurden, und Sie haben Daten mit Azure Maps visualisiert.

✅ Denken Sie an andere IoT-Geräte, die Sie verwendet haben, wie z. B. intelligente Haushaltsgeräte. Was sind die Dinge, Erkenntnisse und Aktionen, die mit diesem Gerät und seiner Software verbunden sind?

Dieses Muster kann je nach Bedarf skaliert werden, indem mehr Geräte und Dienste hinzugefügt werden.

### Daten und Sicherheit

Während Sie die Architektur Ihres Systems definieren, müssen Sie ständig Daten und Sicherheit berücksichtigen.

* Welche Daten sendet und empfängt Ihr Gerät?
* Wie sollten diese Daten gesichert und geschützt werden?
* Wie sollte der Zugriff auf das Gerät und den Cloud-Dienst kontrolliert werden?

✅ Denken Sie an die Datensicherheit von IoT-Geräten, die Sie besitzen. Wie viele dieser Daten sind persönlich und sollten sowohl während der Übertragung als auch bei der Speicherung privat bleiben? Welche Daten sollten nicht gespeichert werden?

## Ein Obstqualitätskontrollsystem entwerfen

Wenden wir nun die Idee von Dingen, Erkenntnissen und Aktionen auf unseren Obstqualitätsdetektor an, um eine größere End-to-End-Anwendung zu entwerfen.

Stellen Sie sich vor, Sie haben die Aufgabe erhalten, einen Obstqualitätsdetektor für eine Verarbeitungsanlage zu entwickeln. Obst wird auf einem Förderbandsystem transportiert, wo derzeit Mitarbeiter Zeit damit verbringen, das Obst von Hand zu überprüfen und unreifes Obst zu entfernen, sobald es ankommt. Um die Kosten zu senken, möchte der Anlagenbesitzer ein automatisiertes System.

✅ Eine der Trends mit dem Aufstieg des IoT (und der Technologie im Allgemeinen) ist, dass manuelle Arbeiten durch Maschinen ersetzt werden. Recherchieren Sie: Wie viele Arbeitsplätze werden voraussichtlich durch IoT verloren gehen? Wie viele neue Arbeitsplätze werden durch die Entwicklung von IoT-Geräten geschaffen?

Sie müssen ein System entwickeln, bei dem Obst erkannt wird, sobald es auf dem Förderband ankommt. Es wird dann fotografiert und mit einem KI-Modell am Edge überprüft. Die Ergebnisse werden in die Cloud gesendet und, falls das Obst unreif ist, wird eine Benachrichtigung ausgegeben, damit das unreife Obst entfernt werden kann.

|   |   |
| - | - |
| **Dinge** | Detektor für Obst, das auf dem Förderband ankommt<br>Kamera zum Fotografieren und Klassifizieren des Obstes<br>Edge-Gerät, das den Klassifikator ausführt<br>Gerät zur Benachrichtigung über unreifes Obst |
| **Erkenntnisse** | Entscheidung, die Reife des Obstes zu überprüfen<br>Speichern der Ergebnisse der Reifeklassifikation<br>Feststellen, ob eine Benachrichtigung über unreifes Obst erforderlich ist |
| **Aktionen** | Senden eines Befehls an ein Gerät, um das Obst zu fotografieren und mit einem Bildklassifikator zu überprüfen<br>Senden eines Befehls an ein Gerät, um zu benachrichtigen, dass das Obst unreif ist |

### Prototyping Ihrer Anwendung

![Eine Referenz-IoT-Architektur für die Obstqualitätsprüfung](../../../../../translated_images/de/iot-reference-architecture-fruit-quality.cc705f121c3b6fa7.webp)

Das obige Diagramm zeigt eine Referenzarchitektur für diese Prototypanwendung.

* Ein IoT-Gerät mit einem Näherungssensor erkennt das Eintreffen von Obst. Es sendet eine Nachricht an die Cloud, dass Obst erkannt wurde.
* Eine serverlose Anwendung in der Cloud sendet einen Befehl an ein anderes Gerät, um ein Foto zu machen und das Bild zu klassifizieren.
* Ein IoT-Gerät mit einer Kamera macht ein Foto und sendet es an einen Bildklassifikator, der am Edge läuft. Die Ergebnisse werden dann an die Cloud gesendet.
* Eine serverlose Anwendung in der Cloud speichert diese Informationen zur späteren Analyse, um zu sehen, welcher Prozentsatz des Obstes unreif ist. Wenn das Obst unreif ist, sendet es einen Befehl an ein anderes IoT-Gerät, um Fabrikarbeiter über unreifes Obst über eine LED zu benachrichtigen.

> 💁 Diese gesamte IoT-Anwendung könnte als einzelnes Gerät implementiert werden, mit der gesamten Logik zum Starten der Bildklassifikation und Steuern der LED integriert. Es könnte einen IoT Hub nur verwenden, um die Anzahl der erkannten unreifen Früchte zu verfolgen und das Gerät zu konfigurieren. In dieser Lektion wird es erweitert, um die Konzepte für groß angelegte IoT-Anwendungen zu demonstrieren.

Für den Prototyp werden Sie all dies auf einem einzigen Gerät implementieren. Wenn Sie einen Mikrocontroller verwenden, verwenden Sie ein separates Edge-Gerät, um den Bildklassifikator auszuführen. Sie haben bereits die meisten Dinge gelernt, die Sie benötigen, um dies zu bauen.

## Obstqualitätsprüfung durch einen Sensor auslösen

Das IoT-Gerät benötigt eine Art Auslöser, um anzuzeigen, wann Obst bereit ist, klassifiziert zu werden. Ein möglicher Auslöser wäre, zu messen, wann das Obst an der richtigen Position auf dem Förderband ist, indem der Abstand zu einem Sensor gemessen wird.

![Näherungssensoren senden Laserstrahlen zu Objekten wie Bananen und messen die Zeit, bis der Strahl zurückgeworfen wird](../../../../../translated_images/de/proximity-sensor.f5cd752c77fb62fe.webp)

Näherungssensoren können verwendet werden, um den Abstand vom Sensor zu einem Objekt zu messen. Sie senden normalerweise einen Strahl elektromagnetischer Strahlung wie einen Laserstrahl oder Infrarotlicht aus und erkennen dann die Strahlung, die von einem Objekt reflektiert wird. Die Zeit zwischen dem Senden des Laserstrahls und dem Zurückkommen des Signals kann verwendet werden, um den Abstand zum Sensor zu berechnen.

> 💁 Sie haben wahrscheinlich Näherungssensoren verwendet, ohne es zu wissen. Die meisten Smartphones schalten den Bildschirm aus, wenn Sie sie an Ihr Ohr halten, um zu verhindern, dass Sie versehentlich einen Anruf mit Ihrem Ohrläppchen beenden. Dies funktioniert mit einem Näherungssensor, der ein Objekt in der Nähe des Bildschirms während eines Anrufs erkennt und die Touch-Funktionen deaktiviert, bis das Telefon einen bestimmten Abstand entfernt ist.

### Aufgabe - Obstqualitätsprüfung durch einen Abstandssensor auslösen

Arbeiten Sie die entsprechende Anleitung durch, um mit Ihrem IoT-Gerät ein Objekt mit einem Näherungssensor zu erkennen:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Einplatinencomputer - Raspberry Pi](pi-proximity.md)
* [Einplatinencomputer - Virtuelles Gerät](virtual-device-proximity.md)

## Daten für einen Obstqualitätsdetektor verwenden

Der Prototyp-Obstdetektor hat mehrere Komponenten, die miteinander kommunizieren.

![Die Komponenten kommunizieren miteinander](../../../../../translated_images/de/fruit-quality-detector-message-flow.adf2a65da8fd8741.webp)

* Ein Näherungssensor misst den Abstand zu einem Stück Obst und sendet dies an IoT Hub
* Der Befehl zur Steuerung der Kamera kommt von IoT Hub zum Kameragerät
* Die Ergebnisse der Bildklassifikation werden an IoT Hub gesendet
* Der Befehl zur Steuerung einer LED zur Benachrichtigung über unreifes Obst wird von IoT Hub an das Gerät mit der LED gesendet

Es ist sinnvoll, die Struktur dieser Nachrichten im Voraus zu definieren, bevor Sie die Anwendung entwickeln.

> 💁 So ziemlich jeder erfahrene Entwickler hat irgendwann in seiner Karriere Stunden, Tage oder sogar Wochen damit verbracht, Fehler zu suchen, die durch Unterschiede in den gesendeten Daten im Vergleich zu den erwarteten Daten verursacht wurden.

Zum Beispiel - wenn Sie Temperaturinformationen senden, wie würden Sie das JSON definieren? Sie könnten ein Feld namens `temperature` haben oder die übliche Abkürzung `temp` verwenden.

```json
{
    "temperature": 20.7
}
```

im Vergleich zu:

```json
{
    "temp": 20.7
}
```

Sie müssen auch Einheiten berücksichtigen - ist die Temperatur in °C oder °F? Wenn Sie die Temperatur mit einem Verbrauchergerät messen und die Anzeigeeinheiten ändern, müssen Sie sicherstellen, dass die Einheiten, die an die Cloud gesendet werden, konsistent bleiben.

✅ Recherchieren Sie: Wie haben Probleme mit Einheiten dazu geführt, dass der $125 Millionen teure Mars Climate Orbiter abgestürzt ist?

Denken Sie über die Daten nach, die für den Obstqualitätsdetektor gesendet werden. Wie würden Sie jede Nachricht definieren? Wo würden Sie die Daten analysieren und Entscheidungen darüber treffen, welche Daten gesendet werden sollen?

Zum Beispiel - das Auslösen der Bildklassifikation mit dem Näherungssensor. Das IoT-Gerät misst den Abstand, aber wo wird die Entscheidung getroffen? Entscheidet das Gerät, dass das Obst nah genug ist, und sendet eine Nachricht, um IoT Hub zu sagen, dass die Klassifikation ausgelöst werden soll? Oder sendet es Näherungsmessungen und lässt IoT Hub entscheiden?

Die Antwort auf solche Fragen lautet: Es kommt darauf an. Jeder Anwendungsfall ist anders, weshalb Sie als IoT-Entwickler das System, das Sie entwickeln, verstehen müssen, wie es verwendet wird und welche Daten erfasst werden.

* Wenn die Entscheidung von IoT Hub getroffen wird, müssen Sie mehrere Abstandsmessungen senden.
* Wenn Sie zu viele Nachrichten senden, erhöht dies die Kosten für IoT Hub und die benötigte Bandbreite Ihrer IoT-Geräte (insbesondere in einer Fabrik mit Millionen von Geräten). Es kann auch Ihr Gerät verlangsamen.
* Wenn Sie die Entscheidung auf dem Gerät treffen, müssen Sie eine Möglichkeit zur Konfiguration des Geräts bereitstellen, um die Maschine fein abzustimmen.

## Entwicklergeräte zur Simulation mehrerer IoT-Geräte verwenden

Um Ihren Prototyp zu erstellen, müssen Sie Ihr IoT-Entwicklungskit so verwenden, dass es wie mehrere Geräte funktioniert, Telemetrie sendet und auf Befehle reagiert.

### Simulation mehrerer IoT-Geräte auf einem Raspberry Pi oder virtueller IoT-Hardware

Wenn Sie einen Einplatinencomputer wie einen Raspberry Pi verwenden, können Sie mehrere Anwendungen gleichzeitig ausführen. Das bedeutet, dass Sie mehrere IoT-Geräte simulieren können, indem Sie mehrere Anwendungen erstellen, eine pro 'IoT-Gerät'. Beispielsweise können Sie jedes Gerät als separate Python-Datei implementieren und sie in verschiedenen Terminal-Sitzungen ausführen.
💁 Beachten Sie, dass einige Hardware nicht funktioniert, wenn sie gleichzeitig von mehreren Anwendungen genutzt wird.
### Simulation mehrerer Geräte auf einem Mikrocontroller

Mikrocontroller sind komplizierter, wenn es darum geht, mehrere Geräte zu simulieren. Im Gegensatz zu Einplatinencomputern können Sie nicht mehrere Anwendungen gleichzeitig ausführen. Stattdessen müssen Sie die gesamte Logik für alle separaten IoT-Geräte in einer einzigen Anwendung integrieren.

Einige Vorschläge, um diesen Prozess zu erleichtern, sind:

* Erstellen Sie eine oder mehrere Klassen pro IoT-Gerät – zum Beispiel Klassen wie `DistanceSensor`, `ClassifierCamera`, `LEDController`. Jede Klasse kann ihre eigenen `setup`- und `loop`-Methoden haben, die von den Hauptfunktionen `setup` und `loop` aufgerufen werden.
* Verarbeiten Sie Befehle an einer zentralen Stelle und leiten Sie sie bei Bedarf an die entsprechende Geräteklasse weiter.
* In der Haupt-`loop`-Funktion müssen Sie das Timing für jedes Gerät berücksichtigen. Wenn Sie beispielsweise eine Geräteklasse haben, die alle 10 Sekunden verarbeitet werden muss, und eine andere, die jede Sekunde verarbeitet werden muss, verwenden Sie in Ihrer Haupt-`loop`-Funktion eine Verzögerung von 1 Sekunde. Jeder `loop`-Aufruf löst den relevanten Code für das Gerät aus, das jede Sekunde verarbeitet werden muss. Verwenden Sie einen Zähler, um jede Schleife zu zählen, und verarbeiten Sie das andere Gerät, wenn der Zähler 10 erreicht (und setzen Sie den Zähler danach zurück).

## Übergang zur Produktion

Der Prototyp bildet die Grundlage für ein endgültiges Produktionssystem. Einige der Unterschiede, wenn Sie in die Produktion übergehen, wären:

* Robuste Komponenten – Verwendung von Hardware, die für die Belastungen in einer Fabrik wie Lärm, Hitze, Vibrationen und Stress ausgelegt ist.
* Interne Kommunikation – Einige Komponenten würden direkt miteinander kommunizieren, um den Umweg über die Cloud zu vermeiden, und nur Daten zur Speicherung in die Cloud senden. Wie dies umgesetzt wird, hängt von der Fabrikstruktur ab, entweder durch direkte Kommunikation oder durch Ausführung eines Teils des IoT-Dienstes am Edge mithilfe eines Gateway-Geräts.
* Konfigurationsoptionen – Jede Fabrik und jeder Anwendungsfall ist unterschiedlich, daher muss die Hardware konfigurierbar sein. Beispielsweise muss der Näherungssensor möglicherweise verschiedene Früchte in unterschiedlichen Entfernungen erkennen. Anstatt die Entfernung, die die Klassifizierung auslöst, fest zu codieren, sollte dies über die Cloud konfigurierbar sein, beispielsweise mithilfe eines Device Twin.
* Automatisierte Fruchtentfernung – Anstelle einer LED, die anzeigt, dass eine Frucht unreif ist, würden automatisierte Geräte diese entfernen.

✅ Recherchieren Sie: In welchen anderen Aspekten würden sich Produktionsgeräte von Entwicklerkits unterscheiden?

---

## 🚀 Herausforderung

In dieser Lektion haben Sie einige der Konzepte gelernt, die Sie benötigen, um ein IoT-System zu entwerfen. Denken Sie an die vorherigen Projekte zurück. Wie passen diese in die oben gezeigte Referenzarchitektur?

Wählen Sie eines der bisherigen Projekte aus und überlegen Sie sich das Design einer komplexeren Lösung, die mehrere Fähigkeiten zusammenführt, die über das hinausgehen, was in den Projekten behandelt wurde. Zeichnen Sie die Architektur und denken Sie an alle Geräte und Dienste, die Sie benötigen würden.

Beispiel: Ein Fahrzeugverfolgungsgerät, das GPS mit Sensoren kombiniert, um Dinge wie Temperaturen in einem Kühltransporter, Motor-Ein- und Ausschaltzeiten und die Identität des Fahrers zu überwachen. Welche Geräte sind beteiligt, welche Dienste werden benötigt, welche Daten werden übertragen und welche Sicherheits- und Datenschutzaspekte müssen berücksichtigt werden?

## Quiz nach der Vorlesung

[Quiz nach der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Überprüfung & Selbststudium

* Lesen Sie mehr über IoT-Architekturen in der [Azure IoT Referenzarchitektur-Dokumentation auf Microsoft Docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Lesen Sie mehr über Device Twins in der [Dokumentation zu Device Twins in IoT Hub auf Microsoft Docs](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Lesen Sie über OPC-UA, ein Kommunikationsprotokoll für Maschinen in der industriellen Automatisierung, auf der [OPC-UA-Seite auf Wikipedia](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Aufgabe

[Erstellen Sie einen Fruchtqualitätsdetektor](assignment.md)

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.