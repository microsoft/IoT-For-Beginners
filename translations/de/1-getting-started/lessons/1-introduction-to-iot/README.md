<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9bae08314d8487cb76ddf3d8797e1544",
  "translation_date": "2025-08-25T22:10:51+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/README.md",
  "language_code": "de"
}
-->
# Einführung in IoT

![Eine Sketchnote-Übersicht dieser Lektion](../../../../../translated_images/de/lesson-1.2606670fa61ee904687da5d6fa4e726639d524d064c895117da1b95b9ff6251d.jpg)

> Sketchnote von [Nitya Narasimhan](https://github.com/nitya). Klicken Sie auf das Bild für eine größere Version.

Diese Lektion wurde im Rahmen der [Hello IoT-Serie](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) des [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) unterrichtet. Die Lektion wurde in zwei Videos unterteilt – eine einstündige Lektion und eine einstündige Sprechstunde, in der tiefer auf Teile der Lektion eingegangen und Fragen beantwortet wurden.

[![Lektion 1: Einführung in IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Lektion 1: Einführung in IoT - Sprechstunde](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Klicken Sie auf die Bilder oben, um die Videos anzusehen.

## Quiz vor der Lektion

[Quiz vor der Lektion](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Einführung

Diese Lektion behandelt einige grundlegende Themen rund um das Internet der Dinge und hilft Ihnen, Ihre Hardware einzurichten.

In dieser Lektion behandeln wir:

* [Was ist das 'Internet der Dinge'?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT-Geräte](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Richten Sie Ihr Gerät ein](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Anwendungen des IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Beispiele für IoT-Geräte in Ihrer Umgebung](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Was ist das 'Internet der Dinge'?

Der Begriff 'Internet der Dinge' wurde 1999 von [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) geprägt, um die Verbindung des Internets mit der physischen Welt über Sensoren zu beschreiben. Seitdem wird der Begriff verwendet, um jedes Gerät zu beschreiben, das mit der physischen Welt interagiert, entweder durch das Sammeln von Daten über Sensoren oder durch reale Interaktionen über Aktoren (Geräte, die etwas tun, wie z. B. einen Schalter umlegen oder eine LED einschalten), die in der Regel mit anderen Geräten oder dem Internet verbunden sind.

> **Sensoren** sammeln Informationen aus der Welt, wie z. B. die Messung von Geschwindigkeit, Temperatur oder Standort.
>
> **Aktoren** wandeln elektrische Signale in reale Interaktionen um, wie z. B. das Auslösen eines Schalters, das Einschalten von Lichtern, das Erzeugen von Geräuschen oder das Senden von Steuersignalen an andere Hardware, z. B. zum Einschalten einer Steckdose.

IoT als Technologiebereich umfasst mehr als nur Geräte – es beinhaltet cloudbasierte Dienste, die Sensordaten verarbeiten oder Anfragen an Aktoren senden können, die mit IoT-Geräten verbunden sind. Es umfasst auch Geräte, die keine oder keine Internetverbindung benötigen, oft als Edge-Geräte bezeichnet. Diese Geräte können Sensordaten selbst verarbeiten und darauf reagieren, meist mithilfe von KI-Modellen, die in der Cloud trainiert wurden.

IoT ist ein schnell wachsendes Technologiefeld. Es wird geschätzt, dass bis Ende 2020 30 Milliarden IoT-Geräte eingesetzt und mit dem Internet verbunden waren. Für die Zukunft wird geschätzt, dass bis 2025 IoT-Geräte fast 80 Zettabyte oder 80 Billionen Gigabyte an Daten sammeln werden. Das ist eine enorme Menge an Daten!

![Ein Diagramm, das aktive IoT-Geräte im Laufe der Zeit zeigt, mit einem Aufwärtstrend von unter 5 Milliarden im Jahr 2015 auf über 30 Milliarden im Jahr 2025](../../../../../images/connected-iot-devices.svg)

✅ Machen Sie ein wenig Recherche: Wie viel der von IoT-Geräten generierten Daten wird tatsächlich genutzt und wie viel wird verschwendet? Warum werden so viele Daten ignoriert?

Diese Daten sind der Schlüssel zum Erfolg des IoT. Um ein erfolgreicher IoT-Entwickler zu sein, müssen Sie verstehen, welche Daten Sie sammeln müssen, wie Sie sie sammeln, wie Sie Entscheidungen auf Basis dieser Daten treffen und wie Sie diese Entscheidungen nutzen können, um bei Bedarf mit der physischen Welt zu interagieren.

## IoT-Geräte

Das **T** in IoT steht für **Things** – Geräte, die mit der physischen Welt um sie herum interagieren, entweder durch das Sammeln von Daten über Sensoren oder durch reale Interaktionen über Aktoren.

Geräte für die Produktion oder kommerzielle Nutzung, wie z. B. Fitness-Tracker für Verbraucher oder industrielle Maschinensteuerungen, sind in der Regel maßgeschneidert. Sie verwenden kundenspezifische Leiterplatten, möglicherweise sogar kundenspezifische Prozessoren, die speziell für eine bestimmte Aufgabe entwickelt wurden, sei es, dass sie klein genug sind, um am Handgelenk getragen zu werden, oder robust genug, um in einer Umgebung mit hohen Temperaturen, hoher Belastung oder starken Vibrationen zu arbeiten.

Als Entwickler, der entweder etwas über IoT lernt oder ein Geräteprototyp erstellt, müssen Sie mit einem Entwicklerkit beginnen. Dies sind universelle IoT-Geräte, die für Entwickler konzipiert sind und oft Funktionen bieten, die auf einem Produktionsgerät nicht vorhanden wären, wie z. B. eine Reihe externer Pins zum Anschließen von Sensoren oder Aktoren, Hardware zur Unterstützung des Debuggings oder zusätzliche Ressourcen, die bei einer großen Produktionsserie unnötige Kosten verursachen würden.

Diese Entwicklerkits fallen normalerweise in zwei Kategorien – Mikrocontroller und Einplatinencomputer. Diese werden hier eingeführt, und wir gehen in der nächsten Lektion detaillierter darauf ein.

> 💁 Ihr Telefon kann auch als universelles IoT-Gerät betrachtet werden, mit eingebauten Sensoren und Aktoren, wobei verschiedene Apps die Sensoren und Aktoren auf unterschiedliche Weise mit verschiedenen Cloud-Diensten nutzen. Es gibt sogar einige IoT-Tutorials, die eine Telefon-App als IoT-Gerät verwenden.

### Mikrocontroller

Ein Mikrocontroller (auch als MCU, kurz für Microcontroller Unit, bezeichnet) ist ein kleiner Computer, der aus folgenden Komponenten besteht:

🧠 Einer oder mehreren zentralen Verarbeitungseinheiten (CPUs) – dem 'Gehirn' des Mikrocontrollers, das Ihr Programm ausführt

💾 Speicher (RAM und Programmspeicher) – wo Ihr Programm, Ihre Daten und Variablen gespeichert werden

🔌 Programmierbare Ein-/Ausgabe (I/O)-Anschlüsse – zur Kommunikation mit externen Peripheriegeräten (angeschlossenen Geräten) wie Sensoren und Aktoren

Mikrocontroller sind typischerweise kostengünstige Rechengeräte, wobei die Durchschnittspreise für die in kundenspezifischer Hardware verwendeten Geräte auf etwa 0,50 US-Dollar sinken und einige Geräte nur 0,03 US-Dollar kosten. Entwicklerkits können bereits ab 4 US-Dollar beginnen, wobei die Kosten steigen, wenn mehr Funktionen hinzugefügt werden. Das [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), ein Mikrocontroller-Entwicklerkit von [Seeed Studios](https://www.seeedstudio.com), das Sensoren, Aktoren, WLAN und einen Bildschirm enthält, kostet etwa 30 US-Dollar.

![Ein Wio Terminal](../../../../../translated_images/de/wio-terminal.b8299ee16587db9a.webp)

> 💁 Seien Sie vorsichtig, wenn Sie im Internet nach Mikrocontrollern suchen, da die Suche nach dem Begriff **MCU** viele Ergebnisse für das Marvel Cinematic Universe und nicht für Mikrocontroller zurückbringen kann.

Mikrocontroller sind darauf ausgelegt, für eine begrenzte Anzahl sehr spezifischer Aufgaben programmiert zu werden, anstatt allgemeine Computer wie PCs oder Macs zu sein. Mit Ausnahme sehr spezifischer Szenarien können Sie keinen Monitor, keine Tastatur und keine Maus anschließen und sie für allgemeine Aufgaben verwenden.

Mikrocontroller-Entwicklerkits werden normalerweise mit zusätzlichen Sensoren und Aktoren geliefert. Die meisten Boards haben eine oder mehrere programmierbare LEDs sowie andere Geräte wie Standardanschlüsse zum Hinzufügen weiterer Sensoren oder Aktoren aus verschiedenen Hersteller-Ökosystemen oder integrierte Sensoren (normalerweise die beliebtesten wie Temperatursensoren). Einige Mikrocontroller verfügen über integrierte drahtlose Konnektivität wie Bluetooth oder WLAN oder haben zusätzliche Mikrocontroller auf dem Board, um diese Konnektivität hinzuzufügen.

> 💁 Mikrocontroller werden normalerweise in C/C++ programmiert.

### Einplatinencomputer

Ein Einplatinencomputer ist ein kleines Rechengerät, das alle Elemente eines vollständigen Computers auf einer einzigen kleinen Platine enthält. Diese Geräte haben Spezifikationen, die denen eines Desktop- oder Laptop-PCs oder Macs nahekommen, führen ein vollständiges Betriebssystem aus, sind jedoch klein, verbrauchen weniger Energie und sind erheblich günstiger.

![Ein Raspberry Pi 4](../../../../../translated_images/de/raspberry-pi-4.fd4590d308c3d456.webp)

Der Raspberry Pi ist einer der beliebtesten Einplatinencomputer.

Wie ein Mikrocontroller verfügt ein Einplatinencomputer über eine CPU, Speicher und Ein-/Ausgabe-Pins, hat jedoch zusätzliche Funktionen wie einen Grafikchip, der es ermöglicht, Monitore anzuschließen, Audioausgänge und USB-Anschlüsse für Tastaturen, Mäuse und andere Standard-USB-Geräte wie Webcams oder externen Speicher. Programme werden auf SD-Karten oder Festplatten zusammen mit einem Betriebssystem gespeichert, anstatt auf einem Speicherchip, der in die Platine eingebaut ist.

> 🎓 Sie können sich einen Einplatinencomputer als eine kleinere, günstigere Version des PCs oder Macs vorstellen, auf dem Sie dies gerade lesen, mit der zusätzlichen Funktion von GPIO (General Purpose Input/Output)-Pins zur Interaktion mit Sensoren und Aktoren.

Einplatinencomputer sind vollwertige Computer und können daher in jeder Sprache programmiert werden. IoT-Geräte werden typischerweise in Python programmiert.

### Hardwareauswahl für die weiteren Lektionen

Alle nachfolgenden Lektionen enthalten Aufgaben, bei denen ein IoT-Gerät verwendet wird, um mit der physischen Welt zu interagieren und mit der Cloud zu kommunizieren. Jede Lektion unterstützt drei Geräteoptionen – Arduino (mit einem Seeed Studios Wio Terminal) oder einen Einplatinencomputer, entweder ein physisches Gerät (einen Raspberry Pi 4) oder einen virtuellen Einplatinencomputer, der auf Ihrem PC oder Mac läuft.

Sie können die benötigte Hardware für alle Aufgaben im [Hardware-Leitfaden](../../../hardware.md) nachlesen.

> 💁 Sie müssen keine IoT-Hardware kaufen, um die Aufgaben zu erledigen. Sie können alles mit einem virtuellen Einplatinencomputer durchführen.

Welche Hardware Sie wählen, hängt davon ab, was Ihnen entweder zu Hause oder in Ihrer Schule zur Verfügung steht und welche Programmiersprache Sie kennen oder lernen möchten. Beide Hardwarevarianten verwenden dasselbe Sensor-Ökosystem, sodass Sie den Weg wechseln können, ohne die meisten Teile des Kits ersetzen zu müssen. Der virtuelle Einplatinencomputer entspricht dem Lernen auf einem Raspberry Pi, wobei der Großteil des Codes auf den Pi übertragbar ist, falls Sie später ein Gerät und Sensoren erwerben.

### Arduino-Entwicklerkit

Wenn Sie daran interessiert sind, die Entwicklung von Mikrocontrollern zu lernen, können Sie die Aufgaben mit einem Arduino-Gerät abschließen. Sie benötigen grundlegende Kenntnisse in C/C++-Programmierung, da die Lektionen nur Code lehren, der für das Arduino-Framework, die verwendeten Sensoren und Aktoren sowie die Bibliotheken, die mit der Cloud interagieren, relevant ist.

Die Aufgaben verwenden [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) mit der [PlatformIO-Erweiterung für Mikrocontroller-Entwicklung](https://platformio.org). Sie können auch die Arduino IDE verwenden, wenn Sie mit diesem Tool vertraut sind, da keine Anleitungen bereitgestellt werden.

### Einplatinencomputer-Entwicklerkit

Wenn Sie daran interessiert sind, IoT-Entwicklung mit Einplatinencomputern zu lernen, können Sie die Aufgaben mit einem Raspberry Pi oder einem virtuellen Gerät, das auf Ihrem PC oder Mac läuft, abschließen.

Sie benötigen grundlegende Kenntnisse in Python-Programmierung, da die Lektionen nur Code lehren, der für die verwendeten Sensoren und Aktoren sowie die Bibliotheken, die mit der Cloud interagieren, relevant ist.

> 💁 Wenn Sie Python programmieren lernen möchten, sehen Sie sich die folgenden zwei Videoserien an:
>
> * [Python für Anfänger](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Mehr Python für Anfänger](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Die Aufgaben verwenden [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Wenn Sie einen Raspberry Pi verwenden, können Sie entweder Ihren Pi mit der vollständigen Desktop-Version von Raspberry Pi OS betreiben und den gesamten Code direkt auf dem Pi mit [der Raspberry Pi OS-Version von VS Code](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn) schreiben oder Ihren Pi als Headless-Gerät betreiben und von Ihrem PC oder Mac aus mit VS Code und der [Remote SSH-Erweiterung](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) programmieren, die es Ihnen ermöglicht, sich mit Ihrem Pi zu verbinden und Code zu bearbeiten, zu debuggen und auszuführen, als ob Sie direkt darauf programmieren würden.

Wenn Sie die virtuelle Geräteoption verwenden, programmieren Sie direkt auf Ihrem Computer. Anstatt Sensoren und Aktoren zu verwenden, nutzen Sie ein Tool, um diese Hardware zu simulieren, indem Sie Sensorwerte definieren und die Ergebnisse von Aktoren auf dem Bildschirm anzeigen.

## Richten Sie Ihr Gerät ein

Bevor Sie mit der Programmierung Ihres IoT-Geräts beginnen können, müssen Sie eine kleine Einrichtung vornehmen. Folgen Sie den entsprechenden Anweisungen unten, je nachdem, welches Gerät Sie verwenden werden.
💁 Wenn du noch kein Gerät hast, sieh dir den [Hardware-Leitfaden](../../../hardware.md) an, um zu entscheiden, welches Gerät du verwenden möchtest und welche zusätzliche Hardware du kaufen musst. Es ist nicht notwendig, Hardware zu kaufen, da alle Projekte auf virtueller Hardware ausgeführt werden können.
Diese Anweisungen enthalten Links zu Websites von Drittanbietern, die von den Herstellern der Hardware oder Tools bereitgestellt werden, die Sie verwenden werden. Dies soll sicherstellen, dass Sie stets die aktuellsten Anweisungen für die verschiedenen Tools und Hardware verwenden.

Arbeiten Sie die entsprechende Anleitung durch, um Ihr Gerät einzurichten und ein "Hello World"-Projekt abzuschließen. Dies wird der erste Schritt sein, um über die vier Lektionen in diesem Einführungsteil ein IoT-Nachtlicht zu erstellen.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Einplatinencomputer - Raspberry Pi](pi.md)
* [Einplatinencomputer - Virtuelles Gerät](virtual-device.md)

✅ Sie werden VS Code sowohl für Arduino als auch für Einplatinencomputer verwenden. Falls Sie dies noch nicht genutzt haben, lesen Sie mehr darüber auf der [VS Code Website](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

## Anwendungen des IoT

IoT deckt eine Vielzahl von Anwendungsfällen ab, die sich in einige breite Kategorien unterteilen lassen:

* Verbraucher-IoT
* Kommerzielles IoT
* Industrielles IoT
* Infrastruktur-IoT

✅ Machen Sie ein wenig Recherche: Finden Sie für jeden der unten beschriebenen Bereiche ein konkretes Beispiel, das nicht im Text genannt wird.

### Verbraucher-IoT

Verbraucher-IoT bezieht sich auf IoT-Geräte, die Verbraucher kaufen und zu Hause nutzen. Einige dieser Geräte sind unglaublich nützlich, wie intelligente Lautsprecher, smarte Heizsysteme und Roboterstaubsauger. Andere sind fragwürdig in ihrer Nützlichkeit, wie sprachgesteuerte Wasserhähne, die dann nicht mehr abgeschaltet werden können, weil die Sprachsteuerung Sie über das Geräusch des fließenden Wassers nicht hört.

Verbraucher-IoT-Geräte befähigen Menschen, in ihrer Umgebung mehr zu erreichen, insbesondere die 1 Milliarde Menschen mit einer Behinderung. Roboterstaubsauger können Menschen mit Mobilitätseinschränkungen saubere Böden bieten, die sie selbst nicht staubsaugen können. Sprachgesteuerte Öfen ermöglichen es Menschen mit eingeschränkter Sicht oder Motorik, ihre Öfen nur mit ihrer Stimme zu bedienen. Gesundheitsmonitore erlauben Patienten, chronische Erkrankungen selbst zu überwachen und regelmäßigere sowie detailliertere Updates zu erhalten. Diese Geräte sind mittlerweile so verbreitet, dass selbst kleine Kinder sie in ihrem Alltag nutzen, beispielsweise Schüler, die während der COVID-Pandemie virtuellen Unterricht hatten und Timer auf Smart-Home-Geräten einstellten, um ihre Schulaufgaben zu verfolgen oder Alarme für bevorstehende Klassenmeetings zu setzen.

✅ Welche Verbraucher-IoT-Geräte haben Sie bei sich oder in Ihrem Zuhause?

### Kommerzielles IoT

Kommerzielles IoT umfasst die Nutzung von IoT im Arbeitsumfeld. In einem Büro können beispielsweise Belegungssensoren und Bewegungsmelder verwendet werden, um Beleuchtung und Heizung zu steuern, sodass Licht und Wärme nur dann eingeschaltet werden, wenn sie benötigt werden. Dies reduziert Kosten und CO₂-Emissionen. In einer Fabrik können IoT-Geräte Sicherheitsrisiken überwachen, wie etwa Arbeiter, die keine Schutzhelme tragen, oder Lärm, der gefährliche Pegel erreicht hat. Im Einzelhandel können IoT-Geräte die Temperatur von Kühlräumen messen und den Ladenbesitzer alarmieren, wenn ein Kühlschrank oder Gefrierschrank außerhalb des erforderlichen Temperaturbereichs liegt. Sie können auch Artikel auf Regalen überwachen, um Mitarbeiter darauf hinzuweisen, dass Produkte nachgefüllt werden müssen. Die Transportbranche verlässt sich zunehmend auf IoT, um Fahrzeugstandorte zu überwachen, gefahrene Kilometer für Straßenbenutzungsgebühren zu erfassen, Fahrerzeiten und Pauseneinhaltung zu verfolgen oder Mitarbeiter zu benachrichtigen, wenn ein Fahrzeug sich einem Depot nähert, um sich auf das Be- oder Entladen vorzubereiten.

✅ Welche kommerziellen IoT-Geräte gibt es in Ihrer Schule oder Ihrem Arbeitsplatz?

### Industrielles IoT (IIoT)

Industrielles IoT, oder IIoT, bezeichnet die Nutzung von IoT-Geräten zur Steuerung und Verwaltung von Maschinen im großen Maßstab. Dies umfasst eine Vielzahl von Anwendungsfällen, von Fabriken bis hin zur digitalen Landwirtschaft.

Fabriken nutzen IoT-Geräte auf viele verschiedene Arten. Maschinen können mit mehreren Sensoren überwacht werden, um Dinge wie Temperatur, Vibration und Drehgeschwindigkeit zu erfassen. Diese Daten können überwacht werden, um die Maschine zu stoppen, wenn sie außerhalb bestimmter Toleranzen arbeitet – beispielsweise wird sie zu heiß und wird abgeschaltet. Diese Daten können auch über Zeit gesammelt und analysiert werden, um vorausschauende Wartung durchzuführen, bei der KI-Modelle die Daten vor einem Ausfall analysieren und diese nutzen, um andere Ausfälle vorherzusagen, bevor sie eintreten.

Digitale Landwirtschaft ist wichtig, um die wachsende Bevölkerung des Planeten zu ernähren, insbesondere die 2 Milliarden Menschen in 500 Millionen Haushalten, die von der [Subsistenzlandwirtschaft](https://wikipedia.org/wiki/Subsistence_agriculture) leben. Digitale Landwirtschaft kann von wenigen Sensoren im einstelligen Dollarbereich bis hin zu großen kommerziellen Anlagen reichen. Ein Landwirt kann damit beginnen, Temperaturen zu überwachen und [Wachstumsgradtage](https://wikipedia.org/wiki/Growing_degree-day) zu nutzen, um vorherzusagen, wann eine Ernte bereit für die Ernte ist. Sie können Bodenfeuchtigkeitsüberwachung mit automatisierten Bewässerungssystemen verbinden, um ihren Pflanzen genau so viel Wasser zu geben, wie sie benötigen, aber nicht mehr, um sicherzustellen, dass ihre Pflanzen nicht austrocknen, ohne Wasser zu verschwenden. Landwirte gehen sogar noch weiter und nutzen Drohnen, Satellitendaten und KI, um das Wachstum von Pflanzen, Krankheiten und die Bodenqualität über große landwirtschaftliche Flächen zu überwachen.

✅ Welche anderen IoT-Geräte könnten Landwirten helfen?

### Infrastruktur-IoT

Infrastruktur-IoT überwacht und steuert die lokale und globale Infrastruktur, die Menschen täglich nutzen.

[Smart Cities](https://wikipedia.org/wiki/Smart_city) sind urbane Gebiete, die IoT-Geräte nutzen, um Daten über die Stadt zu sammeln und diese zu verwenden, um die Funktionsweise der Stadt zu verbessern. Diese Städte werden normalerweise durch Kooperationen zwischen lokalen Regierungen, Hochschulen und lokalen Unternehmen betrieben und überwachen und verwalten Dinge wie Transport, Parken und Umweltverschmutzung. Zum Beispiel wird in Kopenhagen, Dänemark, die Luftverschmutzung, die für die Einwohner wichtig ist, gemessen, und die Daten werden genutzt, um Informationen über die saubersten Rad- und Joggingstrecken bereitzustellen.

[Smart Power Grids](https://wikipedia.org/wiki/Smart_grid) ermöglichen bessere Analysen des Strombedarfs, indem sie Nutzungsdaten auf der Ebene einzelner Haushalte sammeln. Diese Daten können Entscheidungen auf Landesebene leiten, wie etwa wo neue Kraftwerke gebaut werden sollen, und auf persönlicher Ebene, indem sie Nutzern Einblicke geben, wie viel Strom sie verbrauchen, wann sie ihn verbrauchen und sogar Vorschläge machen, wie sie Kosten senken können, beispielsweise durch das nächtliche Laden von Elektroautos.

✅ Wenn Sie IoT-Geräte hinzufügen könnten, um etwas in Ihrer Umgebung zu messen, was wäre das?

## Beispiele für IoT-Geräte, die Sie möglicherweise um sich herum haben

Sie wären überrascht, wie viele IoT-Geräte Sie um sich herum haben. Ich schreibe dies von zu Hause aus und habe die folgenden Geräte mit dem Internet verbunden, die intelligente Funktionen wie App-Steuerung, Sprachsteuerung oder die Möglichkeit, Daten an mein Telefon zu senden, bieten:

* Mehrere intelligente Lautsprecher
* Kühlschrank, Geschirrspüler, Ofen und Mikrowelle
* Strommonitor für Solarpanels
* Smarte Steckdosen
* Video-Türklingel und Sicherheitskameras
* Intelligentes Thermostat mit mehreren smarten Raum-Sensoren
* Garagentoröffner
* Heimunterhaltungssysteme und sprachgesteuerte Fernseher
* Beleuchtung
* Fitness- und Gesundheits-Tracker

All diese Arten von Geräten haben Sensoren und/oder Aktoren und kommunizieren mit dem Internet. Ich kann von meinem Telefon aus sehen, ob mein Garagentor offen ist, und meinen intelligenten Lautsprecher bitten, es für mich zu schließen. Ich kann es sogar auf einen Timer einstellen, sodass es sich automatisch schließt, wenn es nachts noch offen ist. Wenn meine Türklingel läutet, kann ich von meinem Telefon aus sehen, wer dort ist, egal wo ich mich auf der Welt befinde, und über einen Lautsprecher und ein Mikrofon, das in die Türklingel eingebaut ist, mit ihnen sprechen. Ich kann meinen Blutzucker, meine Herzfrequenz und meine Schlafmuster überwachen und nach Mustern in den Daten suchen, um meine Gesundheit zu verbessern. Ich kann meine Beleuchtung über die Cloud steuern und im Dunkeln sitzen, wenn meine Internetverbindung ausfällt.

---

## 🚀 Herausforderung

Listen Sie so viele IoT-Geräte wie möglich auf, die sich in Ihrem Zuhause, Ihrer Schule oder Ihrem Arbeitsplatz befinden – es könnten mehr sein, als Sie denken!

## Quiz nach der Vorlesung

[Quiz nach der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Überprüfung & Selbststudium

Lesen Sie über die Vorteile und Misserfolge von Verbraucher-IoT-Projekten. Suchen Sie auf Nachrichtenseiten nach Artikeln darüber, wann es schiefgegangen ist, wie etwa Datenschutzprobleme, Hardwareprobleme oder Probleme durch fehlende Konnektivität.

Einige Beispiele:

* Schauen Sie sich den Twitter-Account **[Internet of Sh*t](https://twitter.com/internetofshit)** *(Warnung vor vulgärer Sprache)* für einige gute Beispiele von Misserfolgen bei Verbraucher-IoT an.
* [c|net - Meine Apple Watch hat mein Leben gerettet: 5 Menschen teilen ihre Geschichten](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - ADT-Techniker gesteht, jahrelang Kundenkameras ausspioniert zu haben](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(Trigger-Warnung – nicht einvernehmliche Überwachung)*

## Aufgabe

[Untersuchen Sie ein IoT-Projekt](assignment.md)

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.