# Vorhersage des Pflanzenwachstums mit IoT

![Eine Sketchnote-Übersicht dieser Lektion](../../../../../translated_images/de/lesson-5.42b234299279d263.webp)

> Sketchnote von [Nitya Narasimhan](https://github.com/nitya). Klicken Sie auf das Bild für eine größere Version.

## Quiz vor der Vorlesung

[Quiz vor der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Einführung

Pflanzen benötigen bestimmte Dinge, um zu wachsen – Wasser, Kohlendioxid, Nährstoffe, Licht und Wärme. In dieser Lektion lernen Sie, wie Sie das Wachstum und die Reife von Pflanzen berechnen können, indem Sie die Lufttemperatur messen.

In dieser Lektion behandeln wir:

* [Digitale Landwirtschaft](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Warum ist Temperatur beim Anbau wichtig?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Umgebungstemperatur messen](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Wachstumsgradtage (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [GDD mit Daten eines Temperatursensors berechnen](../../../../../2-farm/lessons/1-predict-plant-growth)

## Digitale Landwirtschaft

Die digitale Landwirtschaft revolutioniert die Art und Weise, wie wir Landwirtschaft betreiben, indem sie Werkzeuge zur Sammlung, Speicherung und Analyse von Daten aus der Landwirtschaft nutzt. Wir befinden uns derzeit in einer Phase, die vom Weltwirtschaftsforum als „Vierte Industrielle Revolution“ bezeichnet wird, und der Aufstieg der digitalen Landwirtschaft wird als „Vierte Agrarrevolution“ oder „Landwirtschaft 4.0“ bezeichnet.

> 🎓 Der Begriff „Digitale Landwirtschaft“ umfasst auch die gesamte „Wertschöpfungskette der Landwirtschaft“, also die gesamte Reise vom Bauernhof bis zum Tisch. Dazu gehört die Überwachung der Qualität von Produkten, während diese transportiert und verarbeitet werden, Lager- und E-Commerce-Systeme, sogar Apps zur Vermietung von Traktoren!

Diese Veränderungen ermöglichen es Landwirten, Erträge zu steigern, weniger Dünger und Pestizide zu verwenden und Wasser effizienter zu nutzen. Obwohl sie hauptsächlich in wohlhabenderen Ländern eingesetzt werden, sinken die Preise für Sensoren und andere Geräte langsam, wodurch sie auch in Entwicklungsländern zugänglicher werden.

Einige durch digitale Landwirtschaft ermöglichte Techniken sind:

* Temperaturmessung – Die Messung der Temperatur ermöglicht es Landwirten, das Wachstum und die Reife von Pflanzen vorherzusagen.
* Automatische Bewässerung – Die Messung der Bodenfeuchtigkeit und das Einschalten von Bewässerungssystemen, wenn der Boden zu trocken ist, anstatt zeitgesteuerter Bewässerung. Zeitgesteuerte Bewässerung kann dazu führen, dass Pflanzen während einer heißen, trockenen Periode zu wenig Wasser erhalten oder bei Regen überbewässert werden. Durch Bewässerung nur bei Bedarf können Landwirte ihren Wasserverbrauch optimieren.
* Schädlingsbekämpfung – Landwirte können Kameras auf automatisierten Robotern oder Drohnen verwenden, um nach Schädlingen zu suchen, und dann Pestizide nur dort anwenden, wo sie benötigt werden, wodurch die Menge an Pestiziden reduziert und das Abfließen von Pestiziden in lokale Wasserquellen minimiert wird.

✅ Machen Sie etwas Recherche. Welche anderen Techniken werden verwendet, um die Erträge in der Landwirtschaft zu verbessern?

> 🎓 Der Begriff „Präzisionslandwirtschaft“ beschreibt das Beobachten, Messen und Reagieren auf Pflanzen auf einer Feldbasis oder sogar auf Teilen eines Feldes. Dazu gehört das Messen von Wasser-, Nährstoff- und Schädlingsniveaus und das genaue Reagieren, wie z. B. das Bewässern nur eines kleinen Teils eines Feldes.

## Warum ist Temperatur beim Anbau wichtig?

Beim Lernen über Pflanzen wird den meisten Schülern beigebracht, dass Wasser, Licht, Kohlendioxid und Nährstoffe notwendig sind. Pflanzen benötigen jedoch auch Wärme, um zu wachsen – deshalb blühen Pflanzen im Frühling, wenn die Temperatur steigt, Schneeglöckchen oder Narzissen können aufgrund einer kurzen Wärmeperiode früh sprießen, und Gewächshäuser und Treibhäuser sind so effektiv beim Pflanzenwachstum.

> 🎓 Treibhäuser und Gewächshäuser erfüllen ähnliche Aufgaben, jedoch mit einem wichtigen Unterschied. Treibhäuser werden künstlich beheizt und ermöglichen es Landwirten, die Temperaturen genauer zu kontrollieren, während Gewächshäuser auf die Sonne angewiesen sind und die einzige Kontrolle normalerweise Fenster oder andere Öffnungen sind, um Wärme abzulassen.

Pflanzen haben eine Basis- oder Mindesttemperatur, eine optimale Temperatur und eine maximale Temperatur, die alle auf den täglichen Durchschnittstemperaturen basieren.

* Basistemperatur – Dies ist die minimale tägliche Durchschnittstemperatur, die eine Pflanze benötigt, um zu wachsen.
* Optimale Temperatur – Dies ist die beste tägliche Durchschnittstemperatur, um das maximale Wachstum zu erzielen.
* Maximale Temperatur – Dies ist die maximale Temperatur, die eine Pflanze aushalten kann. Darüber hinaus stellt die Pflanze ihr Wachstum ein, um Wasser zu sparen und zu überleben.

> 💁 Dies sind Durchschnittstemperaturen, die über die Tages- und Nachttemperaturen gemittelt werden. Pflanzen benötigen auch unterschiedliche Temperaturen tagsüber und nachts, um effizienter zu photosynthetisieren und nachts Energie zu sparen.

Jede Pflanzenart hat unterschiedliche Werte für ihre Basis-, optimale und maximale Temperatur. Deshalb gedeihen einige Pflanzen in heißen Ländern und andere in kälteren Ländern.

✅ Machen Sie etwas Recherche. Für Pflanzen in Ihrem Garten, Ihrer Schule oder Ihrem lokalen Park – können Sie die Basistemperatur herausfinden?

![Ein Diagramm, das zeigt, wie die Wachstumsrate mit steigender Temperatur zunimmt und dann abnimmt, wenn die Temperatur zu hoch wird](../../../../../translated_images/de/plant-growth-temp-graph.c6d69c9478e6ca83.webp)

Das obige Diagramm zeigt ein Beispiel für ein Wachstumsraten-Temperatur-Diagramm. Bis zur Basistemperatur gibt es kein Wachstum. Die Wachstumsrate steigt bis zur optimalen Temperatur und fällt dann nach Erreichen dieses Höhepunkts ab. Bei der maximalen Temperatur stoppt das Wachstum.

Die Form dieses Diagramms variiert je nach Pflanzenart. Einige haben steilere Abfälle über der optimalen Temperatur, andere haben langsamere Anstiege von der Basis- zur optimalen Temperatur.

> 💁 Damit ein Landwirt das beste Wachstum erzielen kann, muss er die drei Temperaturwerte kennen und die Form der Diagramme für die Pflanzen verstehen, die er anbaut.

Wenn ein Landwirt die Temperatur kontrollieren kann, beispielsweise in einem kommerziellen Treibhaus, kann er die Bedingungen für seine Pflanzen optimieren. Ein kommerzielles Treibhaus, das Tomaten anbaut, wird beispielsweise tagsüber auf etwa 25°C und nachts auf 20°C eingestellt, um das schnellste Wachstum zu erzielen.

> 🍅 Durch die Kombination dieser Temperaturen mit künstlichem Licht, Düngemitteln und kontrollierten CO
Dieser Code öffnet die CSV-Datei und fügt am Ende eine neue Zeile hinzu. Die Zeile enthält das aktuelle Datum und die Uhrzeit in einem menschenlesbaren Format, gefolgt von der Temperatur, die vom IoT-Gerät empfangen wurde. Die Daten werden im [ISO 8601-Format](https://wikipedia.org/wiki/ISO_8601) mit Zeitzone, aber ohne Mikrosekunden gespeichert.

1. Führen Sie diesen Code wie zuvor aus und stellen Sie sicher, dass Ihr IoT-Gerät Daten sendet. Eine CSV-Datei namens `temperature.csv` wird im gleichen Ordner erstellt. Wenn Sie diese öffnen, sehen Sie Datums-/Zeitangaben und Temperaturmessungen:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Lassen Sie diesen Code eine Weile laufen, um Daten zu erfassen. Idealerweise sollten Sie ihn einen ganzen Tag lang ausführen, um genügend Daten für die GDD-Berechnungen zu sammeln.

    
> 💁 Wenn Sie ein virtuelles IoT-Gerät verwenden, aktivieren Sie das Kontrollkästchen "Zufällig" und legen Sie einen Bereich fest, um zu vermeiden, dass bei jeder Rückgabe des Temperaturwerts immer die gleiche Temperatur angezeigt wird.
    ![Aktivieren Sie das Kontrollkästchen "Zufällig" und legen Sie einen Bereich fest](../../../../../translated_images/de/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.webp) 

    > 💁 Wenn Sie dies einen ganzen Tag lang ausführen möchten, müssen Sie sicherstellen, dass der Computer, auf dem Ihr Servercode läuft, nicht in den Energiesparmodus wechselt. Ändern Sie dazu entweder Ihre Energieeinstellungen oder führen Sie etwas wie [dieses Python-Skript zum Aktivhalten des Systems](https://github.com/jaqsparow/keep-system-active) aus.
    
> 💁 Sie finden diesen Code im Ordner [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server).

### Aufgabe - GDD mit den gespeicherten Daten berechnen

Sobald der Server Temperaturdaten erfasst hat, kann die GDD für eine Pflanze berechnet werden.

Die Schritte, um dies manuell zu tun, sind:

1. Finden Sie die Basistemperatur für die Pflanze. Zum Beispiel beträgt die Basistemperatur für Erdbeeren 10°C.

1. Finden Sie in der `temperature.csv` die höchsten und niedrigsten Temperaturen des Tages.

1. Verwenden Sie die zuvor gegebene GDD-Berechnung, um die GDD zu berechnen.

Zum Beispiel, wenn die höchste Temperatur des Tages 25°C und die niedrigste 12°C beträgt:

![GDD = 25 + 12 geteilt durch 2, dann 10 vom Ergebnis abziehen, ergibt 8.5](../../../../../translated_images/de/gdd-calculation-strawberries.59f57db94b22adb8.webp)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Daher haben die Erdbeeren **8.5** GDD erhalten. Erdbeeren benötigen etwa 250 GDD, um Früchte zu tragen, also dauert es noch eine Weile.

---

## 🚀 Herausforderung

Pflanzen brauchen mehr als nur Wärme, um zu wachsen. Was wird noch benötigt?

Finden Sie heraus, ob es Sensoren gibt, die diese messen können. Was ist mit Aktoren, um diese Werte zu steuern? Wie würden Sie ein oder mehrere IoT-Geräte zusammenstellen, um das Pflanzenwachstum zu optimieren?

## Quiz nach der Vorlesung

[Quiz nach der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Rückblick & Selbststudium

* Lesen Sie mehr über digitale Landwirtschaft auf der [Wikipedia-Seite zur digitalen Landwirtschaft](https://wikipedia.org/wiki/Digital_agriculture). Lesen Sie auch mehr über Präzisionslandwirtschaft auf der [Wikipedia-Seite zur Präzisionslandwirtschaft](https://wikipedia.org/wiki/Precision_agriculture).
* Die vollständige Berechnung der Wachstumsgradtage ist komplizierter als die hier gegebene vereinfachte Version. Lesen Sie mehr über die komplexere Gleichung und wie man mit Temperaturen unterhalb der Basislinie umgeht auf der [Wikipedia-Seite zu Wachstumsgradtagen](https://wikipedia.org/wiki/Growing_degree-day).
* Lebensmittel könnten in Zukunft knapp werden, wenn wir weiterhin die gleichen Methoden in der Landwirtschaft verwenden. Erfahren Sie mehr über High-Tech-Landwirtschaftstechniken in diesem [Hi-Tech Farms of Future Video auf YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Aufgabe

[Visualisieren Sie GDD-Daten mit einem Jupyter Notebook](assignment.md)

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.