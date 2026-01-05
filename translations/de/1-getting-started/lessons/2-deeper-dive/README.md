<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9dd7f645ad1c6f20b72fee512987f772",
  "translation_date": "2025-08-25T22:20:46+00:00",
  "source_file": "1-getting-started/lessons/2-deeper-dive/README.md",
  "language_code": "de"
}
-->
# Ein tieferer Einblick in IoT

![Eine Sketchnote-Übersicht dieser Lektion](../../../../../translated_images/lesson-2.324b0580d620c25e0a24fb7fddfc0b29a846dd4b82c08e7a9466d580ee78ce51.de.jpg)

> Sketchnote von [Nitya Narasimhan](https://github.com/nitya). Klicken Sie auf das Bild für eine größere Version.

Diese Lektion wurde als Teil der [Hello IoT-Serie](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) vom [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) unterrichtet. Die Lektion wurde in zwei Videos unterrichtet - eine einstündige Lektion und eine einstündige Sprechstunde, in der tiefer auf Teile der Lektion eingegangen und Fragen beantwortet wurden.

[![Lektion 2: Ein tieferer Einblick in IoT](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![Lektion 2: Ein tieferer Einblick in IoT - Sprechstunde](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Klicken Sie auf die Bilder oben, um die Videos anzusehen

## Quiz vor der Lektion

[Quiz vor der Lektion](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Einführung

Diese Lektion geht tiefer auf einige der Konzepte ein, die in der letzten Lektion behandelt wurden.

In dieser Lektion behandeln wir:

* [Komponenten einer IoT-Anwendung](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Tieferer Einblick in Mikrocontroller](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Tieferer Einblick in Einplatinencomputer](../../../../../1-getting-started/lessons/2-deeper-dive)

## Komponenten einer IoT-Anwendung

Die zwei Hauptkomponenten einer IoT-Anwendung sind das *Internet* und das *Ding*. Schauen wir uns diese beiden Komponenten genauer an.

### Das Ding

![Ein Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.de.jpg)

Der **Ding**-Teil von IoT bezieht sich auf ein Gerät, das mit der physischen Welt interagieren kann. Diese Geräte sind normalerweise kleine, kostengünstige Computer, die mit niedrigen Geschwindigkeiten und geringem Stromverbrauch arbeiten – zum Beispiel einfache Mikrocontroller mit Kilobyte RAM (im Gegensatz zu Gigabyte bei einem PC), die nur mit wenigen hundert Megahertz laufen (im Gegensatz zu Gigahertz bei einem PC), aber manchmal so wenig Strom verbrauchen, dass sie wochen-, monate- oder sogar jahrelang mit Batterien betrieben werden können.

Diese Geräte interagieren mit der physischen Welt, entweder durch Sensoren, die Daten aus ihrer Umgebung sammeln, oder durch Steuerung von Ausgängen oder Aktoren, um physische Änderungen vorzunehmen. Ein typisches Beispiel hierfür ist ein intelligenter Thermostat – ein Gerät, das über einen Temperatursensor, eine Möglichkeit zur Einstellung einer gewünschten Temperatur wie ein Drehregler oder Touchscreen und eine Verbindung zu einem Heiz- oder Kühlsystem verfügt, das eingeschaltet wird, wenn die gemessene Temperatur außerhalb des gewünschten Bereichs liegt. Der Temperatursensor erkennt, dass der Raum zu kalt ist, und ein Aktor schaltet die Heizung ein.

![Ein Diagramm, das Temperatur und einen Drehregler als Eingaben für ein IoT-Gerät sowie die Steuerung einer Heizung als Ausgabe zeigt](../../../../../translated_images/basic-thermostat.a923217fd1f37e5a6f3390396a65c22a387419ea2dd17e518ec24315ba6ae9a8.de.png)

Es gibt eine riesige Bandbreite an verschiedenen Dingen, die als IoT-Geräte fungieren können, von spezieller Hardware, die eine Sache erfasst, bis hin zu universellen Geräten, sogar Ihrem Smartphone! Ein Smartphone kann Sensoren verwenden, um die Welt um sich herum zu erkennen, und Aktoren, um mit der Welt zu interagieren – zum Beispiel mit einem GPS-Sensor, um Ihren Standort zu bestimmen, und einem Lautsprecher, um Ihnen Navigationsanweisungen zu einem Ziel zu geben.

✅ Denken Sie an andere Systeme um Sie herum, die Daten von einem Sensor lesen und diese nutzen, um Entscheidungen zu treffen. Ein Beispiel wäre der Thermostat eines Backofens. Können Sie weitere finden?

### Das Internet

Die **Internet**-Seite einer IoT-Anwendung besteht aus Anwendungen, mit denen das IoT-Gerät Daten senden und empfangen kann, sowie anderen Anwendungen, die die Daten des IoT-Geräts verarbeiten und Entscheidungen darüber treffen können, welche Anforderungen an die Aktoren des IoT-Geräts gesendet werden sollen.

Ein typisches Setup wäre ein Cloud-Dienst, mit dem das IoT-Gerät verbunden ist. Dieser Cloud-Dienst übernimmt Aufgaben wie Sicherheit, empfängt Nachrichten vom IoT-Gerät und sendet Nachrichten zurück an das Gerät. Dieser Cloud-Dienst würde dann mit anderen Anwendungen verbunden sein, die Sensordaten verarbeiten oder speichern können oder die Sensordaten mit Daten aus anderen Systemen kombinieren, um Entscheidungen zu treffen.

Geräte verbinden sich auch nicht immer direkt über WLAN oder kabelgebundene Verbindungen mit dem Internet. Einige Geräte verwenden Mesh-Netzwerke, um über Technologien wie Bluetooth miteinander zu kommunizieren, und verbinden sich über ein Hub-Gerät, das über eine Internetverbindung verfügt.

Im Beispiel eines intelligenten Thermostats würde sich der Thermostat über das Heim-WLAN mit einem Cloud-Dienst verbinden. Er würde die Temperaturdaten an diesen Cloud-Dienst senden, und von dort aus würden sie in einer Art Datenbank gespeichert, sodass der Hausbesitzer die aktuellen und vergangenen Temperaturen über eine Telefon-App überprüfen kann. Ein anderer Dienst in der Cloud würde wissen, welche Temperatur der Hausbesitzer wünscht, und Nachrichten über den Cloud-Dienst zurück an das IoT-Gerät senden, um dem Heizsystem mitzuteilen, ob es ein- oder ausgeschaltet werden soll.

![Ein Diagramm, das Temperatur und einen Drehregler als Eingaben für ein IoT-Gerät zeigt, das IoT-Gerät mit bidirektionaler Kommunikation zur Cloud, die wiederum bidirektionale Kommunikation zu einem Telefon hat, und die Steuerung einer Heizung als Ausgabe des IoT-Geräts](../../../../../translated_images/mobile-controlled-thermostat.4a994010473d8d6a52ba68c67e5f02dc8928c717e93ca4b9bc55525aa75bbb60.de.png)

Eine noch intelligentere Version könnte KI in der Cloud verwenden, die Daten von anderen Sensoren, die mit anderen IoT-Geräten verbunden sind, wie Belegungssensoren, die erkennen, welche Räume genutzt werden, sowie Daten wie Wetter und sogar Ihren Kalender, um Entscheidungen darüber zu treffen, wie die Temperatur intelligent eingestellt werden kann. Zum Beispiel könnte sie Ihre Heizung ausschalten, wenn sie aus Ihrem Kalender liest, dass Sie im Urlaub sind, oder die Heizung raumweise ausschalten, je nachdem, welche Räume Sie nutzen, und aus den Daten lernen, um mit der Zeit immer genauer zu werden.

![Ein Diagramm, das mehrere Temperatursensoren und einen Drehregler als Eingaben für ein IoT-Gerät zeigt, das IoT-Gerät mit bidirektionaler Kommunikation zur Cloud, die wiederum bidirektionale Kommunikation zu einem Telefon, einem Kalender und einem Wetterdienst hat, und die Steuerung einer Heizung als Ausgabe des IoT-Geräts](../../../../../translated_images/smarter-thermostat.a75855f15d2d9e63.de.png)

✅ Welche anderen Daten könnten helfen, einen mit dem Internet verbundenen Thermostat intelligenter zu machen?

### IoT am Edge

Obwohl das I in IoT für Internet steht, müssen diese Geräte nicht mit dem Internet verbunden sein. In einigen Fällen können Geräte sich mit 'Edge'-Geräten verbinden – Gateway-Geräten, die in Ihrem lokalen Netzwerk laufen, sodass Sie Daten verarbeiten können, ohne eine Verbindung über das Internet herzustellen. Dies kann schneller sein, wenn Sie viele Daten haben oder eine langsame Internetverbindung, es ermöglicht Ihnen, offline zu arbeiten, wo keine Internetverbindung möglich ist, wie auf einem Schiff oder in einem Katastrophengebiet bei der Reaktion auf eine humanitäre Krise, und es ermöglicht Ihnen, Daten privat zu halten. Einige Geräte enthalten Verarbeitungsprogramme, die mit Cloud-Tools erstellt wurden, und führen diese lokal aus, um Daten zu sammeln und darauf zu reagieren, ohne eine Internetverbindung zu nutzen, um eine Entscheidung zu treffen.

Ein Beispiel hierfür ist ein intelligentes Heimgerät wie ein Apple HomePod, Amazon Alexa oder Google Home, das Ihre Stimme mit KI-Modellen verarbeitet, die in der Cloud trainiert wurden, aber lokal auf dem Gerät laufen. Diese Geräte 'wachen auf', wenn ein bestimmtes Wort oder eine bestimmte Phrase gesprochen wird, und senden Ihre Sprache erst dann über das Internet zur Verarbeitung. Das Gerät hört auf, Sprache zu senden, wenn es eine Pause in Ihrer Rede erkennt. Alles, was Sie sagen, bevor Sie das Gerät mit dem Weckwort aktivieren, und alles, was Sie sagen, nachdem das Gerät aufgehört hat zuzuhören, wird nicht über das Internet an den Geräteanbieter gesendet und bleibt daher privat.

✅ Denken Sie an andere Szenarien, in denen Privatsphäre wichtig ist, sodass die Verarbeitung von Daten besser am Edge als in der Cloud erfolgen würde. Ein Hinweis: Denken Sie an IoT-Geräte mit Kameras oder anderen Bildgebungsgeräten.

### IoT-Sicherheit

Bei jeder Internetverbindung ist Sicherheit ein wichtiger Aspekt. Es gibt einen alten Witz, dass 'das S in IoT für Sicherheit steht' – es gibt kein 'S' in IoT, was impliziert, dass es nicht sicher ist.

IoT-Geräte verbinden sich mit einem Cloud-Dienst und sind daher nur so sicher wie dieser Cloud-Dienst – wenn Ihr Cloud-Dienst jedem Gerät erlaubt, sich zu verbinden, können bösartige Daten gesendet oder Virenangriffe durchgeführt werden. Dies kann sehr reale Konsequenzen haben, da IoT-Geräte mit anderen Geräten interagieren und diese steuern. Zum Beispiel manipulierte der [Stuxnet-Wurm](https://wikipedia.org/wiki/Stuxnet) Ventile in Zentrifugen, um sie zu beschädigen. Hacker haben auch [schlechte Sicherheitsvorkehrungen ausgenutzt, um auf Babyüberwachungsgeräte](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) und andere Heimüberwachungsgeräte zuzugreifen.

> 💁 Manchmal laufen IoT-Geräte und Edge-Geräte in einem Netzwerk, das vollständig vom Internet isoliert ist, um die Daten privat und sicher zu halten. Dies wird als [Air-Gapping](https://wikipedia.org/wiki/Air_gap_(networking)) bezeichnet.

## Tieferer Einblick in Mikrocontroller

In der letzten Lektion haben wir Mikrocontroller eingeführt. Schauen wir uns diese nun genauer an.

### CPU

Die CPU ist das 'Gehirn' des Mikrocontrollers. Sie ist der Prozessor, der Ihren Code ausführt und Daten an angeschlossene Geräte senden und von diesen empfangen kann. CPUs können einen oder mehrere Kerne enthalten – im Wesentlichen eine oder mehrere CPUs, die zusammenarbeiten, um Ihren Code auszuführen.

CPUs sind auf eine Uhr angewiesen, die viele Millionen oder Milliarden Mal pro Sekunde tickt. Jeder Tick oder Zyklus synchronisiert die Aktionen, die die CPU ausführen kann. Mit jedem Tick kann die CPU eine Anweisung aus einem Programm ausführen, wie z. B. Daten von einem externen Gerät abrufen oder eine mathematische Berechnung durchführen. Dieser regelmäßige Zyklus ermöglicht es, alle Aktionen abzuschließen, bevor die nächste Anweisung verarbeitet wird.

Je schneller der Taktzyklus, desto mehr Anweisungen können pro Sekunde verarbeitet werden und desto schneller ist die CPU. CPU-Geschwindigkeiten werden in [Hertz (Hz)](https://wikipedia.org/wiki/Hertz) gemessen, einer Standardeinheit, bei der 1 Hz einen Zyklus oder Takt pro Sekunde bedeutet.

> 🎓 CPU-Geschwindigkeiten werden oft in MHz oder GHz angegeben. 1MHz sind 1 Million Hz, 1GHz sind 1 Milliarde Hz.

> 💁 CPUs führen Programme mit dem [Fetch-Decode-Execute-Zyklus](https://wikipedia.org/wiki/Instruction_cycle) aus. Bei jedem Taktzyklus holt die CPU die nächste Anweisung aus dem Speicher, dekodiert sie und führt sie aus, z. B. mit einer arithmetisch-logischen Einheit (ALU), um zwei Zahlen zu addieren. Einige Ausführungen benötigen mehrere Ticks, sodass der nächste Zyklus beim nächsten Tick nach Abschluss der Anweisung ausgeführt wird.

![Der Fetch-Decode-Execute-Zyklus zeigt, wie die Anweisung aus dem Programm im RAM abgerufen, dekodiert und auf einer CPU ausgeführt wird](../../../../../translated_images/fetch-decode-execute.2fd6f150f6280392807f4475382319abd0cee0b90058e1735444d6baa6f2078c.de.png)

Mikrocontroller haben viel niedrigere Taktgeschwindigkeiten als Desktop- oder Laptop-Computer oder sogar die meisten Smartphones. Das Wio Terminal hat beispielsweise eine CPU, die mit 120MHz oder 120.000.000 Zyklen pro Sekunde läuft.

✅ Ein durchschnittlicher PC oder Mac hat eine CPU mit mehreren Kernen, die mit mehreren Gigahertz laufen, was bedeutet, dass der Takt Milliarden Mal pro Sekunde tickt. Recherchieren Sie die Taktgeschwindigkeit Ihres Computers und vergleichen Sie, wie viel schneller er ist als das Wio Terminal.

Jeder Taktzyklus verbraucht Energie und erzeugt Wärme. Je schneller die Ticks, desto mehr Energie wird verbraucht und desto mehr Wärme wird erzeugt. PCs haben Kühlkörper und Lüfter, um Wärme abzuleiten, ohne die sie innerhalb von Sekunden überhitzen und herunterfahren würden. Mikrocontroller haben oft weder das eine noch das andere, da sie viel kühler und daher viel langsamer laufen. PCs laufen mit Netzstrom oder großen Batterien für einige Stunden, Mikrocontroller können Tage, Monate oder sogar Jahre mit kleinen Batterien laufen. Mikrocontroller können auch Kerne haben, die mit unterschiedlichen Geschwindigkeiten laufen, und auf langsamere, energieeffiziente Kerne umschalten, wenn die CPU-Belastung gering ist, um den Energieverbrauch zu reduzieren.

> 💁 Einige PCs und Macs übernehmen die gleiche Mischung aus schnellen Hochleistungskernen und langsameren energieeffizienten Kernen, um Batterien zu sparen. Zum Beispiel kann der M1-Chip in den neuesten Apple-Laptops zwischen 4 Leistungskernen und 4 Effizienzkerne wechseln, um je nach ausgeführter Aufgabe die Batterielaufzeit oder Geschwindigkeit zu optimieren.

✅ Machen Sie eine kleine Recherche: Lesen Sie über CPUs im [Wikipedia-Artikel über CPUs](https://wikipedia.org/wiki/Central_processing_unit).

#### Aufgabe

Untersuchen Sie das Wio Terminal.

Wenn Sie ein Wio Terminal für diese Lektionen verwenden, versuchen Sie, die CPU zu finden. Suchen Sie den Abschnitt *Hardware Overview* auf der [Produktseite des Wio Terminals](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) für ein Bild der internen Komponenten und versuchen Sie, die CPU durch das klare Plastikfenster auf der Rückseite zu finden.

### Speicher

Mikrocontroller haben normalerweise zwei Arten von Speicher – Programmspeicher und Arbeitsspeicher (RAM).

Der Programmspeicher ist nichtflüchtig, was bedeutet, dass alles, was darauf geschrieben wird, erhalten bleibt, wenn das Gerät keinen Strom hat. Dies ist der Speicher, der Ihren Programmcode speichert.

RAM ist der Speicher, der vom Programm verwendet wird, um zu laufen, und enthält Variablen, die von Ihrem Programm zugewiesen wurden, sowie Daten, die von Peripheriegeräten gesammelt wurden. RAM ist flüchtig, wenn der Strom ausfällt, gehen die Inhalte verloren, was effektiv Ihr Programm zurücksetzt.
🎓 Der Programmspeicher speichert deinen Code und bleibt erhalten, auch wenn keine Stromversorgung vorhanden ist.
🎓 RAM wird verwendet, um Ihr Programm auszuführen, und wird zurückgesetzt, wenn keine Stromversorgung vorhanden ist.

Wie bei der CPU ist der Speicher eines Mikrocontrollers um Größenordnungen kleiner als der eines PCs oder Macs. Ein typischer PC hat möglicherweise 8 Gigabyte (GB) RAM, also 8.000.000.000 Bytes, wobei jedes Byte genug Platz bietet, um einen einzelnen Buchstaben oder eine Zahl von 0 bis 255 zu speichern. Ein Mikrocontroller hingegen verfügt oft nur über Kilobytes (KB) RAM, wobei ein Kilobyte 1.000 Bytes entspricht. Das oben erwähnte Wio Terminal hat 192KB RAM, also 192.000 Bytes – mehr als 40.000-mal weniger als ein durchschnittlicher PC!

Das folgende Diagramm zeigt den relativen Größenunterschied zwischen 192KB und 8GB – der kleine Punkt in der Mitte repräsentiert 192KB.

![Ein Vergleich zwischen 192KB und 8GB – mehr als 40.000-mal größer](../../../../../translated_images/ram-comparison.6beb73541b42ac6f.de.png)

Auch der Programmspeicher ist kleiner als bei einem PC. Ein typischer PC hat möglicherweise eine 500GB-Festplatte für Programmspeicher, während ein Mikrocontroller oft nur Kilobytes oder vielleicht ein paar Megabytes (MB) Speicherplatz hat (1MB entspricht 1.000KB oder 1.000.000 Bytes). Das Wio Terminal verfügt über 4MB Programmspeicher.

✅ Recherchieren Sie ein wenig: Wie viel RAM und Speicherplatz hat der Computer, den Sie gerade verwenden? Wie schneidet das im Vergleich zu einem Mikrocontroller ab?

### Eingabe/Ausgabe

Mikrocontroller benötigen Ein- und Ausgabeverbindungen (I/O), um Daten von Sensoren zu lesen und Steuersignale an Aktoren zu senden. Sie verfügen in der Regel über eine Reihe von universellen Ein-/Ausgabe-Pins (GPIO). Diese Pins können in der Software so konfiguriert werden, dass sie entweder Eingaben empfangen (also ein Signal empfangen) oder Ausgaben senden (also ein Signal senden).

🧠⬅️ Eingabepins werden verwendet, um Werte von Sensoren zu lesen.

🧠➡️ Ausgabepins senden Anweisungen an Aktoren.

✅ Sie werden mehr darüber in einer späteren Lektion lernen.

#### Aufgabe

Untersuchen Sie das Wio Terminal.

Wenn Sie das Wio Terminal für diese Lektionen verwenden, suchen Sie die GPIO-Pins. Finden Sie den Abschnitt *Pinout-Diagramm* auf der [Produktseite des Wio Terminals](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), um herauszufinden, welche Pins welche Funktionen haben. Das Wio Terminal wird mit einem Aufkleber geliefert, den Sie auf der Rückseite anbringen können und der die Pinnummern zeigt. Bringen Sie diesen jetzt an, falls Sie es noch nicht getan haben.

### Physische Größe

Mikrocontroller sind in der Regel klein, wobei der kleinste, ein [Freescale Kinetis KL03 MCU, klein genug ist, um in die Delle eines Golfballs zu passen](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/). Allein die CPU eines PCs kann 40mm x 40mm messen, und das ohne die Kühlkörper und Lüfter, die notwendig sind, damit die CPU länger als ein paar Sekunden ohne Überhitzung läuft – deutlich größer als ein kompletter Mikrocontroller. Das Wio Terminal Entwicklerkit mit Mikrocontroller, Gehäuse, Bildschirm und einer Reihe von Anschlüssen und Komponenten ist kaum größer als eine nackte Intel i9 CPU und deutlich kleiner als die CPU mit Kühlkörper und Lüfter!

| Gerät                           | Größe                 |
| ------------------------------- | --------------------- |
| Freescale Kinetis KL03          | 1,6mm x 2mm x 1mm     |
| Wio Terminal                    | 72mm x 57mm x 12mm    |
| Intel i9 CPU, Kühlkörper und Lüfter | 136mm x 145mm x 103mm |

### Frameworks und Betriebssysteme

Aufgrund ihrer niedrigen Geschwindigkeit und Speichergröße führen Mikrocontroller kein Betriebssystem (OS) im herkömmlichen Sinne aus. Das Betriebssystem, das Ihren Computer betreibt (Windows, Linux oder macOS), benötigt viel Speicher und Rechenleistung, um Aufgaben auszuführen, die für einen Mikrocontroller völlig unnötig sind. Denken Sie daran, dass Mikrocontroller in der Regel programmiert werden, um eine oder mehrere sehr spezifische Aufgaben auszuführen, im Gegensatz zu einem allgemeinen Computer wie einem PC oder Mac, der eine Benutzeroberfläche, Musik- oder Filmwiedergabe, Werkzeuge zum Schreiben von Dokumenten oder Code, Spiele oder das Surfen im Internet unterstützen muss.

Um einen Mikrocontroller ohne Betriebssystem zu programmieren, benötigen Sie einige Tools, die es Ihnen ermöglichen, Ihren Code so zu erstellen, dass der Mikrocontroller ihn ausführen kann, und APIs, die mit den Peripheriegeräten kommunizieren können. Jeder Mikrocontroller ist anders, daher unterstützen Hersteller normalerweise Standard-Frameworks, die es Ihnen ermöglichen, einem standardisierten „Rezept“ zu folgen, um Ihren Code zu erstellen und auf jedem Mikrocontroller auszuführen, der dieses Framework unterstützt.

Sie können Mikrocontroller auch mit einem Betriebssystem programmieren – oft als Echtzeitbetriebssystem (RTOS) bezeichnet, da diese so konzipiert sind, dass sie Daten in Echtzeit an Peripheriegeräte senden und von diesen empfangen können. Diese Betriebssysteme sind sehr leichtgewichtig und bieten Funktionen wie:

* Multithreading, das es Ihrem Code ermöglicht, mehr als einen Codeblock gleichzeitig auszuführen, entweder auf mehreren Kernen oder abwechselnd auf einem Kern.
* Netzwerkanbindung, um sicher über das Internet zu kommunizieren.
* Komponenten für grafische Benutzeroberflächen (GUI) zum Erstellen von Benutzeroberflächen (UI) auf Geräten mit Bildschirmen.

✅ Lesen Sie über verschiedene RTOS: [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org).

#### Arduino

![Das Arduino-Logo](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) ist wahrscheinlich das beliebteste Mikrocontroller-Framework, insbesondere bei Schülern, Hobbyisten und Bastlern. Arduino ist eine Open-Source-Elektronikplattform, die Software und Hardware kombiniert. Sie können Arduino-kompatible Boards direkt von Arduino oder von anderen Herstellern kaufen und dann mit dem Arduino-Framework programmieren.

Arduino-Boards werden in C oder C++ programmiert. Die Verwendung von C/C++ ermöglicht es, dass Ihr Code sehr klein kompiliert wird und schnell läuft – etwas, das auf einem eingeschränkten Gerät wie einem Mikrocontroller erforderlich ist. Der Kern einer Arduino-Anwendung wird als Sketch bezeichnet und ist C/C++-Code mit zwei Funktionen – `setup` und `loop`. Wenn das Board startet, führt der Arduino-Framework-Code die `setup`-Funktion einmal aus und dann die `loop`-Funktion immer wieder, bis die Stromversorgung abgeschaltet wird.

In der `setup`-Funktion schreiben Sie Ihren Initialisierungscode, wie z. B. die Verbindung mit WiFi und Cloud-Diensten oder die Initialisierung von Pins für Eingabe und Ausgabe. Ihr Code in der `loop`-Funktion enthält dann die Verarbeitung, wie das Lesen von Sensorwerten und das Senden dieser Werte in die Cloud. Normalerweise fügen Sie am Ende jeder Schleife eine Verzögerung ein, z. B. wenn Sie Sensordaten nur alle 10 Sekunden senden möchten. Dadurch kann der Mikrocontroller Energie sparen, indem er schläft, und die Schleife wird erst nach 10 Sekunden erneut ausgeführt.

![Ein Arduino-Sketch, der zuerst setup ausführt und dann loop wiederholt](../../../../../translated_images/arduino-sketch.79590cb837ff7a7c6a68d1afda6cab83fd53d3bb1bd9a8bf2eaf8d693a4d3ea6.de.png)

✅ Diese Programmarchitektur wird als *Ereignisschleife* oder *Nachrichtenschleife* bezeichnet. Viele Anwendungen verwenden dies im Hintergrund, und es ist der Standard für die meisten Desktop-Anwendungen, die auf Betriebssystemen wie Windows, macOS oder Linux laufen. Die `loop`-Funktion lauscht auf Nachrichten von Benutzeroberflächenkomponenten wie Tasten oder Geräten wie der Tastatur und reagiert darauf. Mehr dazu können Sie in diesem [Artikel über die Ereignisschleife](https://wikipedia.org/wiki/Event_loop) lesen.

Arduino bietet Standardbibliotheken für die Interaktion mit Mikrocontrollern und den I/O-Pins, mit unterschiedlichen Implementierungen im Hintergrund, um auf verschiedenen Mikrocontrollern zu laufen. Zum Beispiel pausiert die [`delay`-Funktion](https://www.arduino.cc/reference/en/language/functions/time/delay/) das Programm für eine bestimmte Zeit, und die [`digitalRead`-Funktion](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) liest einen Wert von `HIGH` oder `LOW` von einem bestimmten Pin, unabhängig davon, auf welchem Board der Code ausgeführt wird. Diese Standardbibliotheken ermöglichen es, dass Arduino-Code, der für ein Board geschrieben wurde, für jedes andere Arduino-Board neu kompiliert werden kann und läuft, vorausgesetzt, die Pins sind gleich und die Boards unterstützen dieselben Funktionen.

Es gibt ein großes Ökosystem von Drittanbieter-Arduino-Bibliotheken, die es Ihnen ermöglichen, zusätzliche Funktionen zu Ihren Arduino-Projekten hinzuzufügen, wie z. B. die Verwendung von Sensoren und Aktoren oder die Verbindung zu Cloud-IoT-Diensten.

##### Aufgabe

Untersuchen Sie das Wio Terminal.

Wenn Sie das Wio Terminal für diese Lektionen verwenden, lesen Sie den Code, den Sie in der letzten Lektion geschrieben haben, erneut. Finden Sie die `setup`- und `loop`-Funktion. Überwachen Sie die serielle Ausgabe, um zu sehen, dass die `loop`-Funktion wiederholt aufgerufen wird. Fügen Sie Code zur `setup`-Funktion hinzu, um auf den seriellen Port zu schreiben, und beobachten Sie, dass dieser Code nur einmal bei jedem Neustart aufgerufen wird. Versuchen Sie, Ihr Gerät mit dem Netzschalter an der Seite neu zu starten, um zu zeigen, dass dies bei jedem Neustart des Geräts aufgerufen wird.

## Ein tieferer Einblick in Einplatinencomputer

In der letzten Lektion haben wir Einplatinencomputer eingeführt. Schauen wir uns diese nun genauer an.

### Raspberry Pi

![Das Raspberry Pi-Logo](../../../../../translated_images/raspberry-pi-logo.4efaa16605cee054.de.png)

Die [Raspberry Pi Foundation](https://www.raspberrypi.org) ist eine Wohltätigkeitsorganisation aus Großbritannien, die 2009 gegründet wurde, um das Studium der Informatik, insbesondere auf Schulebene, zu fördern. Im Rahmen dieser Mission entwickelten sie einen Einplatinencomputer, den Raspberry Pi. Raspberry Pis sind derzeit in drei Varianten erhältlich – einer Vollversion, der kleineren Pi Zero und einem Compute-Modul, das in Ihr finales IoT-Gerät eingebaut werden kann.

![Ein Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.de.jpg)

Die neueste Version des vollwertigen Raspberry Pi ist der Raspberry Pi 4B. Dieser verfügt über eine Quad-Core-CPU (4 Kerne) mit 1,5GHz, 2, 4 oder 8GB RAM, Gigabit-Ethernet, WiFi, 2 HDMI-Ports mit Unterstützung für 4k-Bildschirme, einen Audio- und Composite-Videoausgang, USB-Ports (2 USB 2.0, 2 USB 3.0), 40 GPIO-Pins, einen Kamerasteckplatz für ein Raspberry Pi Kameramodul und einen SD-Kartensteckplatz. All das auf einer Platine, die 88mm x 58mm x 19,5mm misst und mit einem 3A USB-C-Netzteil betrieben wird. Diese beginnen bei 35 US-Dollar, deutlich günstiger als ein PC oder Mac.

> 💁 Es gibt auch einen Pi400, einen All-in-One-Computer mit einem Pi4, der in eine Tastatur integriert ist.

![Ein Raspberry Pi Zero](../../../../../translated_images/raspberry-pi-zero.f7a4133e1e7d54bb.de.jpg)

Der Pi Zero ist viel kleiner und energieeffizienter. Er hat eine Single-Core-CPU mit 1GHz, 512MB RAM, WiFi (im Zero W-Modell), einen einzigen HDMI-Port, einen Micro-USB-Port, 40 GPIO-Pins, einen Kamerasteckplatz für ein Raspberry Pi Kameramodul und einen SD-Kartensteckplatz. Er misst 65mm x 30mm x 5mm und verbraucht sehr wenig Energie. Der Zero kostet 5 US-Dollar, die W-Version mit WiFi 10 US-Dollar.

> 🎓 Die CPUs in beiden Geräten sind ARM-Prozessoren, im Gegensatz zu den Intel/AMD x86- oder x64-Prozessoren, die in den meisten PCs und Macs zu finden sind. Diese ähneln den CPUs, die in einigen Mikrocontrollern sowie in fast allen Mobiltelefonen, dem Microsoft Surface X und den neuen Apple Silicon-basierten Apple Macs verwendet werden.

Alle Varianten des Raspberry Pi führen eine Version von Debian Linux aus, die als Raspberry Pi OS bezeichnet wird. Diese ist als Lite-Version ohne Desktop verfügbar, was perfekt für „headless“-Projekte ist, bei denen kein Bildschirm benötigt wird, oder als Vollversion mit einer vollständigen Desktop-Umgebung, einschließlich Webbrowser, Office-Anwendungen, Programmierwerkzeugen und Spielen. Da das Betriebssystem eine Version von Debian Linux ist, können Sie jede Anwendung oder jedes Tool installieren, das auf Debian läuft und für den ARM-Prozessor im Pi entwickelt wurde.

#### Aufgabe

Untersuchen Sie den Raspberry Pi.

Wenn Sie einen Raspberry Pi für diese Lektionen verwenden, lesen Sie über die verschiedenen Hardwarekomponenten auf der Platine nach.

* Sie finden Details zu den Prozessoren auf der [Raspberry Pi Hardware-Dokumentationsseite](https://www.raspberrypi.org/documentation/hardware/raspberrypi/). Lesen Sie über den Prozessor, der in dem von Ihnen verwendeten Pi steckt.
* Lokalisieren Sie die GPIO-Pins. Lesen Sie mehr darüber in der [Raspberry Pi GPIO-Dokumentation](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Verwenden Sie den [GPIO-Pin-Nutzungsleitfaden](https://www.raspberrypi.org/documentation/usage/gpio/README.md), um die verschiedenen Pins auf Ihrem Pi zu identifizieren.

### Programmierung von Einplatinencomputern

Einplatinencomputer sind vollständige Computer, die ein vollständiges Betriebssystem ausführen. Das bedeutet, dass es eine breite Palette von Programmiersprachen, Frameworks und Tools gibt, die Sie verwenden können, um sie zu programmieren, im Gegensatz zu Mikrocontrollern, die auf die Unterstützung des Boards in Frameworks wie Arduino angewiesen sind. Die meisten Programmiersprachen verfügen über Bibliotheken, die auf die GPIO-Pins zugreifen können, um Daten von Sensoren und Aktoren zu senden und zu empfangen.

✅ Welche Programmiersprachen kennen Sie? Werden diese unter Linux unterstützt?

Die am häufigsten verwendete Programmiersprache für den Bau von IoT-Anwendungen auf einem Raspberry Pi ist Python. Es gibt ein riesiges Ökosystem von Hardware, die für den Pi entwickelt wurde, und fast alle davon enthalten den relevanten Code, der benötigt wird, um sie als Python-Bibliotheken zu verwenden. Einige dieser Ökosysteme basieren auf sogenannten „Hats“ – so genannt, weil sie wie ein Hut auf dem Pi sitzen und über einen großen Anschluss mit den 40 GPIO-Pins verbunden werden. Diese Hats bieten zusätzliche Funktionen, wie Bildschirme, Sensoren, ferngesteuerte Autos oder Adapter, die es ermöglichen, Sensoren mit standardisierten Kabeln anzuschließen.
### Einsatz von Einplatinencomputern in professionellen IoT-Implementierungen

Einplatinencomputer werden nicht nur als Entwicklerkits, sondern auch für professionelle IoT-Implementierungen eingesetzt. Sie bieten eine leistungsstarke Möglichkeit, Hardware zu steuern und komplexe Aufgaben wie das Ausführen von Machine-Learning-Modellen zu bewältigen. Zum Beispiel gibt es das [Raspberry Pi 4 Compute Module](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/), das die gesamte Leistung eines Raspberry Pi 4 bietet, jedoch in einer kompakteren und günstigeren Form ohne die meisten Anschlüsse, speziell entwickelt für die Integration in kundenspezifische Hardware.

---

## 🚀 Herausforderung

Die Herausforderung in der letzten Lektion bestand darin, so viele IoT-Geräte wie möglich aufzulisten, die sich in deinem Zuhause, deiner Schule oder deinem Arbeitsplatz befinden. Für jedes Gerät in dieser Liste: Glaubst du, dass sie auf Mikrocontrollern oder Einplatinencomputern basieren, oder vielleicht auf einer Mischung aus beidem?

## Quiz nach der Vorlesung

[Quiz nach der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Rückblick & Selbststudium

* Lies den [Arduino-Einstiegsleitfaden](https://www.arduino.cc/en/Guide/Introduction), um mehr über die Arduino-Plattform zu erfahren.
* Lies die [Einführung zum Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/), um mehr über Raspberry Pis zu lernen.
* Erfahre mehr über einige der Konzepte und Akronyme im Artikel [Was sind CPUs, MPUs, MCUs und GPUs?](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/) im Electrical Engineering Journal.

✅ Nutze diese Leitfäden zusammen mit den Kosten, die du über die Links im [Hardware-Leitfaden](../../../hardware.md) findest, um zu entscheiden, welche Hardware-Plattform du verwenden möchtest, oder ob du lieber ein virtuelles Gerät nutzen möchtest.

## Aufgabe

[Vergleiche und kontrastiere Mikrocontroller und Einplatinencomputer](assignment.md)

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.