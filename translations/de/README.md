<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6c354ec3487e4f6cfafbe44557996cd9",
  "translation_date": "2026-01-05T12:26:41+00:00",
  "source_file": "README.md",
  "language_code": "de"
}
-->
### Treten Sie der Azure AI Foundry Community bei

Wenn Sie nicht weiterkommen oder Fragen zum Erstellen von KI-Anwendungen haben. Tauschen Sie sich mit anderen Lernenden und erfahrenen Entwicklern über MCP aus. Es ist eine unterstützende Community, in der Fragen willkommen sind und Wissen frei geteilt wird.

Wenn Sie Produktfeedback haben oder während des Erstellens auf Fehler stoßen, besuchen Sie:

Folgen Sie diesen Schritten, um mit der Nutzung dieser Ressourcen zu beginnen:
1. **Forken Sie das Repository**: Klicken Sie [![GitHub forks](https://img.shields.io/github/forks/microsoft/IoT-For-Beginners.svg?style=social&label=Fork)](https://GitHub.com/microsoft/IoT-For-Beginners/fork)
2. **Klonen Sie das Repository**: `git clone https://github.com/microsoft/IoT-For-Beginners.git`
3. [**Treten Sie dem Microsoft Foundry Discord bei und treffen Sie Experten und andere Entwickler**](https://discord.com/invite/ByRwuEEgH4)


### 🌐 Mehrsprachige Unterstützung

#### Unterstützt über GitHub Action (Automatisiert & Immer Aktuell)

> **Möchten Sie lieber lokal klonen?**

> Dieses Repository enthält über 50 Sprachübersetzungen, was die Download-Größe erheblich erhöht. Um ohne Übersetzungen zu klonen, verwenden Sie Sparse Checkout:
> ```bash
> git clone --filter=blob:none --sparse https://github.com/microsoft/IoT-For-Beginners.git
> cd IoT-For-Beginners
> git sparse-checkout set --no-cone '/*' '!translations' '!translated_images'
> ```
> So erhalten Sie alles, was Sie benötigen, um den Kurs abzuschließen, mit deutlich schnellerem Download.

# IoT für Anfänger - Ein Curriculum

Die Azure Cloud Advocates bei Microsoft freuen sich, ein 12-wöchiges Curriculum mit 24 Lektionen über die Grundlagen von IoT anzubieten. Jede Lektion enthält Vor- und Nachtests, schriftliche Anleitungen zum Abschluss der Lektion, eine Lösung, eine Aufgabe und mehr. Unsere projektbasierte Pädagogik ermöglicht Lernen durch Bauen – eine bewährte Methode, um neue Fähigkeiten nachhaltig zu verankern.

Die Projekte verfolgen die Reise von Lebensmitteln vom Bauernhof bis zum Tisch. Dazu gehören Landwirtschaft, Logistik, Fertigung, Einzelhandel und Verbraucher – alles beliebte Industriebereiche für IoT-Geräte.

> Sketchnote von [Nitya Narasimhan](https://github.com/nitya). Klicken Sie auf das Bild für eine größere Version.

**Herzlichen Dank an unsere Autoren [Jen Fox](https://github.com/jenfoxbot), [Jen Looper](https://github.com/jlooper), [Jim Bennett](https://github.com/jimbobbennett) und unsere Sketchnote-Künstlerin [Nitya Narasimhan](https://github.com/nitya).**

**Vielen Dank auch an unser Team von [Microsoft Learn Student Ambassadors](https://studentambassadors.microsoft.com?WT.mc_id=academic-17441-jabenn), die dieses Curriculum überprüft und übersetzt haben – [Aditya Garg](https://github.com/AdityaGarg00), [Anurag Sharma](https://github.com/Anurag-0-1-A), [Arpita Das](https://github.com/Arpiiitaaa), [Aryan Jain](https://www.linkedin.com/in/aryan-jain-47a4a1145/), [Bhavesh Suneja](https://github.com/EliteWarrior315), [Faith Hunja](https://faithhunja.github.io/), [Lateefah Bello](https://www.linkedin.com/in/lateefah-bello/), [Manvi Jha](https://github.com/Severus-Matthew), [Mireille Tan](https://www.linkedin.com/in/mireille-tan-a4834819a/), [Mohammad Iftekher (Iftu) Ebne Jalal](https://github.com/Iftu119), [Mohammad Zulfikar](https://github.com/mohzulfikar), [Priyanshu Srivastav](https://www.linkedin.com/in/priyanshu-srivastav-b067241ba), [Thanmai Gowducheruvu](https://github.com/innovation-platform), und [Zina Kamel](https://www.linkedin.com/in/zina-kamel/).**

Treffen Sie das Team!

**Gif von** [Mohit Jaisal](https://linkedin.com/in/mohitjaisal)

> 🎥 Klicken Sie auf das obenstehende Bild für ein Video über das Projekt!

> **Lehrkräfte**, wir haben [einige Vorschläge](for-teachers.md) zur Nutzung dieses Curriculums aufgenommen. Wenn Sie eigene Lektionen erstellen möchten, finden Sie auch eine [Lektionsvorlage](lesson-template/README.md).

> **[Schülerinnen und Schüler](https://aka.ms/student-page)**, um dieses Curriculum eigenständig zu nutzen, forken Sie das gesamte Repo und bearbeiten Sie die Übungen eigenständig, beginnend mit einem Vorlesungstest, Lesen der Vorlesung und Abschluss der restlichen Aktivitäten. Versuchen Sie, die Projekte zu erstellen, indem Sie die Lektionen verstehen, statt den Lösungs-Code zu kopieren; dieser Code ist jedoch in den /solutions-Ordnern in jeder projektorientierten Lektion verfügbar. Eine weitere Idee ist die Bildung einer Lerngruppe mit Freunden, um die Inhalte gemeinsam zu erarbeiten. Zur Vertiefung empfehlen wir [Microsoft Learn](https://docs.microsoft.com/users/jimbobbennett/collections/ke2ehd351jopwr?WT.mc_id=academic-17441-jabenn).

Sehen Sie sich für eine Übersicht dieses Kurses dieses Video an:

> 🎥 Klicken Sie auf das obenstehende Bild für ein Video über das Projekt!

## Pädagogik

Wir haben beim Aufbau dieses Curriculums zwei pädagogische Grundsätze gewählt: Es projektbasiert zu gestalten und häufige Tests einzubauen. Am Ende dieser Reihe erstellen die Lernenden ein System zur Pflanzenüberwachung und -bewässerung, eine Fahrzeugverfolgung, eine smarte Fabrikumgebung zur Überwachung und Kontrolle von Lebensmitteln sowie einen sprachgesteuerten Küchentimer. Sie lernen die Grundlagen des Internet of Things, einschließlich der Programmierung von Geräten, Verbindungen zur Cloud, Telemetrieanalyse und KI am Rand.

Indem die Inhalte auf Projekte abgestimmt sind, wird der Lernprozess für die Studierenden ansprechender gestaltet und das Behalten der Konzepte verbessert.

Zudem setzt ein Test vor der Lektion die Lernabsicht, während ein zweiter Test danach das Behalten weiter fördert. Dieses Curriculum ist flexibel und macht Spaß und kann komplett oder teilweise absolviert werden. Die Projekte beginnen klein und werden im Verlauf der 12 Wochen immer komplexer.

Jedes Projekt basiert auf verfügbarer realer Hardware für Lernende und Hobbyisten. Jedes Projekt untersucht den jeweiligen Projektbereich und vermittelt relevantes Hintergrundwissen. Um ein erfolgreicher Entwickler zu sein, hilft es, den Bereich zu verstehen, in dem Probleme gelöst werden. Dieses Wissen ermöglicht es den Studierenden, über ihre IoT-Lösungen nachzudenken und das Gelernte im Kontext realer Problemstellungen einzuschätzen. Die Lernenden erfahren das „Warum“ ihrer Lösungen und bekommen Verständnis für die Anwender.

## Hardware

Für die Projekte stehen uns zwei IoT-Hardware-Optionen zur Verfügung, je nach persönlicher Vorliebe, Sprachkenntnissen, Lernzielen und Verfügbarkeit. Außerdem bieten wir eine „virtuelle Hardware“-Version für diejenigen an, die keinen Zugriff auf Hardware haben oder sich vor einem Kauf genauer informieren möchten. Mehr Infos und eine „Einkaufsliste“ finden Sie auf der [Hardware-Seite](./hardware.md), einschließlich Links zum Kauf kompletter Sets bei unseren Freunden von Seeed Studio.
> 💁 Finden Sie unsere [Verhaltensregeln](CODE_OF_CONDUCT.md), [Beitragsrichtlinien](CONTRIBUTING.md) und [Übersetzungsrichtlinien](TRANSLATIONS.md). Wir freuen uns über Ihr konstruktives Feedback!
>
> 🔧 Haben Sie Probleme? Schauen Sie in unseren [Fehlerbehebungsleitfaden](TROUBLESHOOTING.md) für Lösungen zu häufigen Problemen.

## Jede Lektion beinhaltet:

- Sketchnote
- optional ergänzendes Video
- Aufwärmquiz vor der Lektion
- schriftliche Lektion
- bei projektbasierten Lektionen Schritt-für-Schritt-Anleitungen zum Bau des Projekts
- Wissensüberprüfungen
- eine Herausforderung
- ergänzende Lektüre
- Aufgabe
- [Quiz nach der Lektion](https://ff-quizzes.netlify.app/en/)

> **Eine Anmerkung zu den Quizzen**: Alle Quizze befinden sich im quiz-app-Ordner, insgesamt 48 Quizze mit jeweils drei Fragen. Sie sind aus den Lektionen heraus verlinkt, aber die Quiz-App kann lokal ausgeführt oder auf Azure bereitgestellt werden; folgen Sie den Anweisungen im `quiz-app`-Ordner. Die Quizze werden nach und nach lokalisiert.

## Lektionen

|       |                  Projektname                  |                         Vermittelte Konzepte                         | Lernziele                                                                                                                                                                |                                                      Verknüpfte Lektion                                                       |
| :---: | :------------------------------------------: | :------------------------------------------------------------------: | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- | :--------------------------------------------------------------------------------------------------------------------------: |
|  01   | [Erste Schritte](./1-getting-started/README.md)    |                        Einführung in IoT                            | Erlernen Sie die Grundprinzipien von IoT und die grundlegenden Bausteine von IoT-Lösungen, wie Sensoren und Cloud-Dienste, während Sie Ihr erstes IoT-Gerät einrichten   |                         [Einführung in IoT](./1-getting-started/lessons/1-introduction-to-iot/README.md)                       |
|  02   | [Erste Schritte](./1-getting-started/README.md)    |                       Ein tieferer Einblick in IoT                  | Erfahren Sie mehr über die Komponenten eines IoT-Systems sowie über Mikrocontroller und Einplatinencomputer                                                            |                             [Ein tieferer Einblick in IoT](./1-getting-started/lessons/2-deeper-dive/README.md)               |
|  03   | [Erste Schritte](./1-getting-started/README.md)    | Interaktion mit der physischen Welt mittels Sensoren und Aktoren    | Lernen Sie Sensoren kennen, um Daten aus der physischen Welt zu erfassen, und Aktoren, um Rückmeldungen zu senden, während Sie eine Nachtlicht bauen                      | [Interaktion mit der physischen Welt mittels Sensoren und Aktoren](./1-getting-started/lessons/3-sensors-and-actuators/README.md) |
|  04   | [Erste Schritte](./1-getting-started/README.md)    |                 Verbinden Sie Ihr Gerät mit dem Internet            | Erfahren Sie, wie Sie ein IoT-Gerät mit dem Internet verbinden, um Nachrichten zu senden und zu empfangen, indem Sie Ihr Nachtlicht mit einem MQTT-Broker verbinden     |                      [Verbinden Sie Ihr Gerät mit dem Internet](./1-getting-started/lessons/4-connect-internet/README.md)      |
|  05   |            [Landwirtschaft](./2-farm/README.md)    |                      Pflanzenwachstum vorhersagen                   | Lernen Sie, wie Sie das Pflanzenwachstum anhand von Temperaturdaten, die von einem IoT-Gerät erfasst werden, vorhersagen können                                         |                            [Pflanzenwachstum vorhersagen](./2-farm/lessons/1-predict-plant-growth/README.md)                |
|  06   |            [Landwirtschaft](./2-farm/README.md)    |                      Bodenfeuchtigkeit erkennen                     | Lernen Sie, wie man die Bodenfeuchtigkeit erkennt und einen Bodenfeuchtesensor kalibriert                                                                               |                            [Bodenfeuchtigkeit erkennen](./2-farm/lessons/2-detect-soil-moisture/README.md)                  |
|  07   |            [Landwirtschaft](./2-farm/README.md)    |                     Automatisierte Pflanzenbewässerung              | Lernen Sie, wie Sie die Bewässerung mit einem Relais und MQTT automatisieren und zeitlich steuern                                                                       |                         [Automatisierte Pflanzenbewässerung](./2-farm/lessons/3-automated-plant-watering/README.md)          |
|  08   |            [Landwirtschaft](./2-farm/README.md)    |               Ihre Pflanze in die Cloud migrieren                   | Erfahren Sie mehr über die Cloud und cloud-gehostete IoT-Dienste und wie Sie Ihre Pflanze stattdessen mit einem dieser Dienste anstelle eines öffentlichen MQTT-Brokers verbinden |             [Ihre Pflanze in die Cloud migrieren](./2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md)              |
|  09   |            [Landwirtschaft](./2-farm/README.md)    |           Migrieren Sie Ihre Anwendungslogik in die Cloud           | Lernen Sie, wie Sie Anwendungslogik in der Cloud schreiben können, die auf IoT-Nachrichten reagiert                                                                     |                   [Anwendungslogik in die Cloud migrieren](./2-farm/lessons/5-migrate-application-to-the-cloud/README.md)     |
|  10   |            [Landwirtschaft](./2-farm/README.md)    |                      Halten Sie Ihre Pflanze sicher                 | Erfahren Sie, wie IoT-Sicherheit funktioniert und wie Sie Ihre Pflanze mit Schlüsseln und Zertifikaten schützen                                                        |                               [Halten Sie Ihre Pflanze sicher](./2-farm/lessons/6-keep-your-plant-secure/README.md)           |
|  11   |          [Transport](./3-transport/README.md)       |                        Ortung verfolgen                             | Erfahren Sie mehr über GPS-Standortverfolgung für IoT-Geräte                                                                                                           |                               [Ortung verfolgen](./3-transport/lessons/1-location-tracking/README.md)                         |
|  12   |          [Transport](./3-transport/README.md)       |                      Ortsdaten speichern                            | Lernen Sie, wie IoT-Daten gespeichert werden können, um später visualisiert oder analysiert zu werden                                                                  |                               [Ortsdaten speichern](./3-transport/lessons/2-store-location-data/README.md)                   |
|  13   |          [Transport](./3-transport/README.md)       |                     Ortsdaten visualisieren                         | Lernen Sie, wie Ortsdaten auf einer Karte visualisiert werden und wie Karten die reale 3D-Welt in 2 Dimensionen darstellen                                              |                         [Ortsdaten visualisieren](./3-transport/lessons/3-visualize-location-data/README.md)                 |
|  14   |          [Transport](./3-transport/README.md)       |                            Geofences                                | Erfahren Sie, was Geofences sind und wie sie verwendet werden können, um zu benachrichtigen, wenn Fahrzeuge in der Lieferkette ihrem Ziel nahekommen                      |                                   [Geofences](./3-transport/lessons/4-geofences/README.md)                                   |
|  15   |       [Herstellung](./4-manufacturing/README.md)    |                 Trainieren Sie einen Fruchterkennungsdetektor      | Erfahren Sie, wie man einen Bildklassifikator in der Cloud trainiert, um die Qualität von Früchten zu erkennen                                                         |                        [Fruchterkennungsdetektor trainieren](./4-manufacturing/lessons/1-train-fruit-detector/README.md)       |
|  16   |       [Herstellung](./4-manufacturing/README.md)    |                    Fruchtqualität mit einem IoT-Gerät prüfen       | Erfahren Sie, wie Sie Ihren Fruchterkennungsdetektor von einem IoT-Gerät aus verwenden                                                                                  |                     [Fruchtqualität mit IoT-Gerät prüfen](./4-manufacturing/lessons/2-check-fruit-from-device/README.md)      |
|  17   |       [Herstellung](./4-manufacturing/README.md)    |                      Führen Sie Ihren Fruchterkennungsdetektor am Edge aus  | Erfahren Sie, wie Sie Ihren Fruchterkennungsdetektor auf einem IoT-Gerät am Edge ausführen                                                                              |                         [Fruchterkennungsdetektor am Edge ausführen](./4-manufacturing/lessons/3-run-fruit-detector-edge/README.md) |
|  18   |       [Herstellung](./4-manufacturing/README.md)    |                Auslösen der Früchtequalitätsbestimmung über einen Sensor   | Erfahren Sie, wie man die Früchtequalitätsbestimmung über einen Sensor auslöst                                                                                          |                     [Früchtequalitätsbestimmung über Sensor auslösen](./4-manufacturing/lessons/4-trigger-fruit-detector/README.md) |
|  19   |            [Einzelhandel](./5-retail/README.md)     |                    Trainieren Sie einen Lagererkennungsdetektor    | Erfahren Sie, wie Sie Objekterkennung verwenden können, um einen Lagererkennungsdetektor zu trainieren, der den Lagerbestand in einem Geschäft zählt                    |                       [Lagererkennungsdetektor trainieren](./5-retail/lessons/1-train-stock-detector/README.md)              |
|  20   |            [Einzelhandel](./5-retail/README.md)     |                    Lagerbestand mit IoT-Gerät prüfen               | Erfahren Sie, wie Sie mit einem IoT-Gerät den Lagerbestand unter Verwendung eines Objekterkennungsmodells prüfen können                                                |                         [Lagerbestand mit IoT-Gerät prüfen](./5-retail/lessons/2-check-stock-device/README.md)               |
|  21   |           [Verbraucher](./6-consumer/README.md)     |                     Spracherkennung mit einem IoT-Gerät            | Lernen Sie, wie Sie Sprache von einem IoT-Gerät erkennen, um eine intelligente Zeitschaltuhr zu bauen                                                                  |                      [Spracherkennung mit IoT-Gerät](./6-consumer/lessons/1-speech-recognition/README.md)                    |
|  22   |           [Verbraucher](./6-consumer/README.md)     |                          Sprache verstehen                          | Lernen Sie, wie Sie Sätze, die an ein IoT-Gerät gesprochen werden, verstehen                                                                                            |                              [Sprache verstehen](./6-consumer/lessons/2-language-understanding/README.md)                    |
|  23   |           [Verbraucher](./6-consumer/README.md)     |                 Timer einstellen und mündliches Feedback geben    | Lernen Sie, wie Sie auf einem IoT-Gerät einen Timer einstellen und gesprochenes Feedback geben, wenn der Timer eingestellt ist und endet                            |                  [Timer einstellen und gesprochenes Feedback geben](./6-consumer/lessons/3-spoken-feedback/README.md)       |
|  24   |           [Verbraucher](./6-consumer/README.md)     |                        Mehrsprachigkeit unterstützen              | Lernen Sie, wie Sie mehrere Sprachen unterstützen, sowohl beim Ansprechen als auch bei den Antworten Ihrer intelligenten Zeitschaltuhr                                  |                    [Mehrsprachigkeit unterstützen](./6-consumer/lessons/4-multiple-language-support/README.md)              |

## Offline-Zugriff

Sie können diese Dokumentation offline nutzen, indem Sie [Docsify](https://docsify.js.org/#/) verwenden. Forken Sie dieses Repository, [installieren Sie Docsify](https://docsify.js.org/#/quickstart) auf Ihrem lokalen Rechner und geben Sie dann im Stammordner dieses Repos `docsify serve` ein. Die Webseite wird auf Port 3000 auf Ihrem localhost bereitgestellt: `localhost:3000`.

## Quiz

Danke an die Community für das interaktive Quiz, das Ihr Wissen zu jedem Kapitel testet. Testen Sie Ihr Wissen [hier](https://ff-quizzes.netlify.app/en/) 

### PDF

Sie können bei Bedarf eine PDF dieses Inhalts für den Offline-Zugriff erstellen. Stellen Sie dazu sicher, dass [npm installiert](https://docs.npmjs.com/downloading-and-installing-node-js-and-npm) ist, und führen Sie die folgenden Befehle im Stammordner dieses Repositories aus:

```sh
npm i
npm run convert
```

### Folien

Für einige Lektionen gibt es Foliensätze im Ordner [slides](../../slides).

## Weitere Lehrpläne

Unser Team erstellt weitere Lehrpläne! Schauen Sie sich an:

<!-- CO-OP TRANSLATOR OTHER COURSES START -->
### LangChain
[![LangChain4j für Anfänger](https://img.shields.io/badge/LangChain4j%20for%20Beginners-22C55E?style=for-the-badge&&labelColor=E5E7EB&color=0553D6)](https://aka.ms/langchain4j-for-beginners)
[![LangChain.js für Anfänger](https://img.shields.io/badge/LangChain.js%20for%20Beginners-22C55E?style=for-the-badge&labelColor=E5E7EB&color=0553D6)](https://aka.ms/langchainjs-for-beginners?WT.mc_id=m365-94501-dwahlin)

---

### Azure / Edge / MCP / Agents
[![AZD für Anfänger](https://img.shields.io/badge/AZD%20for%20Beginners-0078D4?style=for-the-badge&labelColor=E5E7EB&color=0078D4)](https://github.com/microsoft/AZD-for-beginners?WT.mc_id=academic-105485-koreyst)
[![Edge AI für Anfänger](https://img.shields.io/badge/Edge%20AI%20for%20Beginners-00B8E4?style=for-the-badge&labelColor=E5E7EB&color=00B8E4)](https://github.com/microsoft/edgeai-for-beginners?WT.mc_id=academic-105485-koreyst)
[![MCP für Anfänger](https://img.shields.io/badge/MCP%20for%20Beginners-009688?style=for-the-badge&labelColor=E5E7EB&color=009688)](https://github.com/microsoft/mcp-for-beginners?WT.mc_id=academic-105485-koreyst)
[![KI-Agenten für Anfänger](https://img.shields.io/badge/AI%20Agents%20for%20Beginners-00C49A?style=for-the-badge&labelColor=E5E7EB&color=00C49A)](https://github.com/microsoft/ai-agents-for-beginners?WT.mc_id=academic-105485-koreyst)

---
 
### Generative KI-Reihe
[![Generative KI für Anfänger](https://img.shields.io/badge/Generative%20AI%20for%20Beginners-8B5CF6?style=for-the-badge&labelColor=E5E7EB&color=8B5CF6)](https://github.com/microsoft/generative-ai-for-beginners?WT.mc_id=academic-105485-koreyst)
[![Generative KI (.NET)](https://img.shields.io/badge/Generative%20AI%20(.NET)-9333EA?style=for-the-badge&labelColor=E5E7EB&color=9333EA)](https://github.com/microsoft/Generative-AI-for-beginners-dotnet?WT.mc_id=academic-105485-koreyst)
[![Generative KI (Java)](https://img.shields.io/badge/Generative%20AI%20(Java)-C084FC?style=for-the-badge&labelColor=E5E7EB&color=C084FC)](https://github.com/microsoft/generative-ai-for-beginners-java?WT.mc_id=academic-105485-koreyst)
[![Generative KI (JavaScript)](https://img.shields.io/badge/Generative%20AI%20(JavaScript)-E879F9?style=for-the-badge&labelColor=E5E7EB&color=E879F9)](https://github.com/microsoft/generative-ai-with-javascript?WT.mc_id=academic-105485-koreyst)

---
 
### Kernwissen
[![ML für Anfänger](https://img.shields.io/badge/ML%20for%20Beginners-22C55E?style=for-the-badge&labelColor=E5E7EB&color=22C55E)](https://aka.ms/ml-beginners?WT.mc_id=academic-105485-koreyst)
[![Datenwissenschaft für Anfänger](https://img.shields.io/badge/Data%20Science%20for%20Beginners-84CC16?style=for-the-badge&labelColor=E5E7EB&color=84CC16)](https://aka.ms/datascience-beginners?WT.mc_id=academic-105485-koreyst)
[![KI für Anfänger](https://img.shields.io/badge/AI%20for%20Beginners-A3E635?style=for-the-badge&labelColor=E5E7EB&color=A3E635)](https://aka.ms/ai-beginners?WT.mc_id=academic-105485-koreyst)
[![Cybersicherheit für Anfänger](https://img.shields.io/badge/Cybersecurity%20for%20Beginners-F97316?style=for-the-badge&labelColor=E5E7EB&color=F97316)](https://github.com/microsoft/Security-101?WT.mc_id=academic-96948-sayoung)
[![Webentwicklung für Anfänger](https://img.shields.io/badge/Web%20Dev%20for%20Beginners-EC4899?style=for-the-badge&labelColor=E5E7EB&color=EC4899)](https://aka.ms/webdev-beginners?WT.mc_id=academic-105485-koreyst)
[![IoT für Anfänger](https://img.shields.io/badge/IoT%20for%20Beginners-14B8A6?style=for-the-badge&labelColor=E5E7EB&color=14B8A6)](https://aka.ms/iot-beginners?WT.mc_id=academic-105485-koreyst)
[![XR-Entwicklung für Anfänger](https://img.shields.io/badge/XR%20Development%20for%20Beginners-38BDF8?style=for-the-badge&labelColor=E5E7EB&color=38BDF8)](https://github.com/microsoft/xr-development-for-beginners?WT.mc_id=academic-105485-koreyst)

---
 
### Copilot-Reihe
[![Copilot für KI-Paarprogrammierung](https://img.shields.io/badge/Copilot%20for%20AI%20Paired%20Programming-FACC15?style=for-the-badge&labelColor=E5E7EB&color=FACC15)](https://aka.ms/GitHubCopilotAI?WT.mc_id=academic-105485-koreyst)
[![Copilot für C#/.NET](https://img.shields.io/badge/Copilot%20for%20C%23/.NET-FBBF24?style=for-the-badge&labelColor=E5E7EB&color=FBBF24)](https://github.com/microsoft/mastering-github-copilot-for-dotnet-csharp-developers?WT.mc_id=academic-105485-koreyst)
[![Copilot-Abenteuer](https://img.shields.io/badge/Copilot%20Adventure-FDE68A?style=for-the-badge&labelColor=E5E7EB&color=FDE68A)](https://github.com/microsoft/CopilotAdventures?WT.mc_id=academic-105485-koreyst)
<!-- CO-OP TRANSLATOR OTHER COURSES END -->

## Bildnachweise

Sie finden alle Bildnachweise, die für diesen Lehrplan erforderlich sind, in der Datei [Attributions](./attributions.md).

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Haftungsausschluss**:  
Dieses Dokument wurde mithilfe des KI-Übersetzungsdienstes [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir auf Genauigkeit achten, können automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten. Das Originaldokument in der jeweiligen Ursprungssprache gilt als maßgebliche Quelle. Für wichtige Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die aus der Nutzung dieser Übersetzung entstehen.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->