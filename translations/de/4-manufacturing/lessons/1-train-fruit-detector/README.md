<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f5e63c916d2dd97d58be12aaf76bd9f1",
  "translation_date": "2025-08-25T20:53:30+00:00",
  "source_file": "4-manufacturing/lessons/1-train-fruit-detector/README.md",
  "language_code": "de"
}
-->
# Trainiere einen Obstqualitätsdetektor

![Eine Sketchnote-Übersicht dieser Lektion](../../../../../translated_images/de/lesson-15.843d21afdc6fb2bba70cd9db7b7d2f91598859fafda2078b0bdc44954194b6c0.jpg)

> Sketchnote von [Nitya Narasimhan](https://github.com/nitya). Klicken Sie auf das Bild für eine größere Version.

Dieses Video gibt einen Überblick über den Azure Custom Vision-Dienst, der in dieser Lektion behandelt wird.

[![Custom Vision – Machine Learning Made Easy | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 Klicken Sie auf das obige Bild, um das Video anzusehen.

## Quiz vor der Lektion

[Quiz vor der Lektion](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## Einführung

Der jüngste Aufschwung in Künstlicher Intelligenz (KI) und Maschinellem Lernen (ML) bietet heutigen Entwicklern eine Vielzahl von Möglichkeiten. ML-Modelle können trainiert werden, um verschiedene Dinge in Bildern zu erkennen, einschließlich unreifer Früchte. Dies kann in IoT-Geräten genutzt werden, um Produkte entweder während der Ernte oder bei der Verarbeitung in Fabriken oder Lagern zu sortieren.

In dieser Lektion lernen Sie die Bildklassifikation kennen – die Verwendung von ML-Modellen, um zwischen Bildern verschiedener Objekte zu unterscheiden. Sie lernen, wie Sie einen Bildklassifikator trainieren, um zwischen guten und schlechten Früchten zu unterscheiden, sei es unreif, überreif, beschädigt oder verdorben.

In dieser Lektion behandeln wir:

* [Verwendung von KI und ML zur Lebensmittelsortierung](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Bildklassifikation durch Maschinelles Lernen](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Einen Bildklassifikator trainieren](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Ihren Bildklassifikator testen](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Ihren Bildklassifikator neu trainieren](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## Verwendung von KI und ML zur Lebensmittelsortierung

Die weltweite Bevölkerung zu ernähren ist eine Herausforderung, insbesondere zu einem Preis, der für alle erschwinglich ist. Einer der größten Kostenfaktoren ist die Arbeitskraft, weshalb Landwirte zunehmend auf Automatisierung und Werkzeuge wie IoT setzen, um ihre Arbeitskosten zu senken. Die manuelle Ernte ist arbeitsintensiv (und oft körperlich anstrengend) und wird zunehmend durch Maschinen ersetzt, insbesondere in wohlhabenderen Ländern. Trotz der Kosteneinsparungen durch den Einsatz von Maschinen bei der Ernte gibt es einen Nachteil – die Fähigkeit, Lebensmittel während der Ernte zu sortieren.

Nicht alle Ernten reifen gleichmäßig. Tomaten beispielsweise können noch grüne Früchte an der Pflanze haben, wenn der Großteil reif ist. Obwohl es Verschwendung ist, diese früh zu ernten, ist es für den Landwirt günstiger und einfacher, alles mit Maschinen zu ernten und die unreifen Produkte später zu entsorgen.

✅ Schauen Sie sich verschiedene Früchte oder Gemüse an, die entweder in Ihrer Nähe auf Feldern oder in Ihrem Garten wachsen oder in Geschäften erhältlich sind. Sind sie alle gleich reif, oder sehen Sie Unterschiede?

Der Aufstieg der automatisierten Ernte hat die Sortierung der Produkte von der Ernte in die Fabrik verlagert. Lebensmittel wurden auf langen Förderbändern transportiert, wobei Teams von Menschen die Produkte durchsuchten und alles entfernten, was nicht den Qualitätsstandards entsprach. Die Ernte wurde durch Maschinen günstiger, aber es gab immer noch Kosten für die manuelle Sortierung der Lebensmittel.

![Wenn eine rote Tomate erkannt wird, setzt sie ihre Reise ungehindert fort. Wenn eine grüne Tomate erkannt wird, wird sie durch einen Hebel in einen Abfallbehälter geschleudert.](../../../../../translated_images/de/optical-tomato-sorting.61aa134bdda4e5b1bfb16a212c1e35a6ef0c426cbb8b1c975f79d7bfbf48d068.png)

Die nächste Entwicklung war der Einsatz von Maschinen zur Sortierung, entweder in die Erntemaschinen integriert oder in den Verarbeitungsanlagen. Die erste Generation dieser Maschinen verwendete optische Sensoren, um Farben zu erkennen, und steuerte Aktuatoren, um grüne Tomaten mit Hebeln oder Luftstößen in einen Abfallbehälter zu befördern, während rote Tomaten auf einem Netzwerk von Förderbändern weitergeleitet wurden.

In diesem Video werden grüne Tomaten erkannt und mit Hebeln in einen Behälter geschleudert, während sie von einem Förderband auf ein anderes fallen.

✅ Welche Bedingungen wären in einer Fabrik oder auf einem Feld erforderlich, damit diese optischen Sensoren korrekt funktionieren?

Die neuesten Entwicklungen dieser Sortiermaschinen nutzen KI und ML, indem sie Modelle verwenden, die darauf trainiert sind, gutes von schlechtem Obst zu unterscheiden – nicht nur durch offensichtliche Farbunterschiede wie grüne Tomaten vs. rote, sondern auch durch subtilere Unterschiede im Aussehen, die auf Krankheiten oder Quetschungen hinweisen können.

## Bildklassifikation durch Maschinelles Lernen

Traditionelle Programmierung bedeutet, dass Sie Daten nehmen, einen Algorithmus darauf anwenden und ein Ergebnis erhalten. Im letzten Projekt haben Sie beispielsweise GPS-Koordinaten und einen Geofence verwendet, einen von Azure Maps bereitgestellten Algorithmus angewendet und ein Ergebnis erhalten, ob der Punkt innerhalb oder außerhalb des Geofence liegt. Sie geben mehr Daten ein, und Sie erhalten mehr Ergebnisse.

![Traditionelle Entwicklung nimmt Eingaben und einen Algorithmus und gibt Ergebnisse aus. Maschinelles Lernen verwendet Eingabe- und Ausgabedaten, um ein Modell zu trainieren, und dieses Modell kann neue Eingabedaten verwenden, um neue Ergebnisse zu generieren.](../../../../../translated_images/de/traditional-vs-ml.5c20c169621fa539.webp)

Maschinelles Lernen dreht diesen Prozess um – Sie beginnen mit Daten und bekannten Ergebnissen, und der maschinelle Lernalgorithmus lernt aus den Daten. Sie können dann diesen trainierten Algorithmus, ein sogenanntes *Maschinelles Lernmodell* oder *Modell*, verwenden, um neue Daten einzugeben und neue Ergebnisse zu erhalten.

> 🎓 Der Prozess, bei dem ein maschineller Lernalgorithmus aus den Daten lernt, wird als *Training* bezeichnet. Die Eingaben und bekannten Ergebnisse werden als *Trainingsdaten* bezeichnet.

Beispielsweise könnten Sie einem Modell Millionen von Bildern unreifer Bananen als Eingabetrainingsdaten geben, wobei die Trainingsergebnisse auf `unreif` gesetzt sind, und Millionen von Bildern reifer Bananen mit den Trainingsergebnissen `reif`. Der ML-Algorithmus erstellt dann ein Modell basierend auf diesen Daten. Sie geben diesem Modell ein neues Bild einer Banane, und es wird vorhersagen, ob das neue Bild eine reife oder unreife Banane zeigt.

> 🎓 Die Ergebnisse von ML-Modellen werden als *Vorhersagen* bezeichnet.

![2 Bananen, eine reife mit einer Vorhersage von 99,7% reif, 0,3% unreif, und eine unreife mit einer Vorhersage von 1,4% reif, 98,6% unreif.](../../../../../translated_images/de/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50ece4e4589e724b142da0681f35470fe3db3f7d51240f69c85.png)

ML-Modelle geben keine binären Antworten, sondern Wahrscheinlichkeiten. Beispielsweise könnte ein Modell ein Bild einer Banane erhalten und `reif` mit 99,7% und `unreif` mit 0,3% vorhersagen. Ihr Code würde dann die beste Vorhersage auswählen und entscheiden, dass die Banane reif ist.

Das ML-Modell, das verwendet wird, um Bilder wie diese zu erkennen, wird als *Bildklassifikator* bezeichnet – es erhält beschriftete Bilder und klassifiziert neue Bilder basierend auf diesen Beschriftungen.

> 💁 Dies ist eine Vereinfachung, und es gibt viele andere Möglichkeiten, Modelle zu trainieren, die nicht immer beschriftete Ergebnisse benötigen, wie z. B. unüberwachtes Lernen. Wenn Sie mehr über ML erfahren möchten, schauen Sie sich [ML für Anfänger, ein 24-Lektionen-Curriculum über Maschinelles Lernen](https://aka.ms/ML-beginners) an.

## Einen Bildklassifikator trainieren

Um einen Bildklassifikator erfolgreich zu trainieren, benötigen Sie Millionen von Bildern. Es stellt sich jedoch heraus, dass Sie, sobald Sie einen Bildklassifikator haben, der auf Millionen oder Milliarden verschiedener Bilder trainiert wurde, diesen wiederverwenden und mit einer kleinen Menge an Bildern neu trainieren können, um großartige Ergebnisse zu erzielen – ein Prozess, der als *Transferlernen* bezeichnet wird.

> 🎓 Transferlernen bedeutet, dass Sie das Gelernte aus einem bestehenden ML-Modell auf ein neues Modell basierend auf neuen Daten übertragen.

Sobald ein Bildklassifikator für eine Vielzahl von Bildern trainiert wurde, ist er intern hervorragend darin, Formen, Farben und Muster zu erkennen. Transferlernen ermöglicht es dem Modell, das, was es bereits über die Erkennung von Bildteilen gelernt hat, zu nutzen, um neue Bilder zu erkennen.

![Sobald Sie Formen erkennen können, können sie in verschiedenen Konfigurationen zu einem Boot oder einer Katze zusammengesetzt werden.](../../../../../translated_images/de/shapes-to-images.1a309f0ea88dd66f.webp)

Das können Sie sich wie Kinderbücher über Formen vorstellen, bei denen Sie, sobald Sie einen Halbkreis, ein Rechteck und ein Dreieck erkennen können, ein Segelboot oder eine Katze je nach Konfiguration dieser Formen erkennen können. Der Bildklassifikator kann die Formen erkennen, und das Transferlernen lehrt ihn, welche Kombination ein Boot oder eine Katze – oder eine reife Banane – ergibt.

Es gibt eine Vielzahl von Tools, die Ihnen dabei helfen können, darunter cloudbasierte Dienste, die Ihnen helfen, Ihr Modell zu trainieren und es dann über Web-APIs zu nutzen.

> 💁 Das Training dieser Modelle erfordert viel Rechenleistung, normalerweise über Grafikprozessoren (GPUs). Dieselbe spezialisierte Hardware, die Spiele auf Ihrer Xbox großartig aussehen lässt, kann auch verwendet werden, um maschinelle Lernmodelle zu trainieren. Durch die Nutzung der Cloud können Sie Zeit auf leistungsstarken Computern mit GPUs mieten, um diese Modelle zu trainieren, und so die benötigte Rechenleistung nur für die Zeit nutzen, die Sie benötigen.

## Custom Vision

Custom Vision ist ein cloudbasiertes Tool zum Trainieren von Bildklassifikatoren. Es ermöglicht Ihnen, einen Klassifikator mit nur einer kleinen Anzahl von Bildern zu trainieren. Sie können Bilder über ein Webportal, eine Web-API oder ein SDK hochladen und jedem Bild ein *Tag* zuweisen, das die Klassifikation dieses Bildes angibt. Anschließend trainieren Sie das Modell und testen es, um zu sehen, wie gut es funktioniert. Sobald Sie mit dem Modell zufrieden sind, können Sie Versionen davon veröffentlichen, die über eine Web-API oder ein SDK zugänglich sind.

![Das Azure Custom Vision-Logo](../../../../../translated_images/de/custom-vision-logo.d3d4e7c8a87ec9daf825e72e210576c3cbf60312577be7a139e22dd97ab7f1e6.png)

> 💁 Sie können ein Custom Vision-Modell mit nur 5 Bildern pro Klassifikation trainieren, aber mehr ist besser. Mit mindestens 30 Bildern erzielen Sie bessere Ergebnisse.

Custom Vision ist Teil einer Reihe von KI-Tools von Microsoft, die als Cognitive Services bezeichnet werden. Diese KI-Tools können entweder ohne Training oder mit einer kleinen Menge an Training verwendet werden. Sie umfassen Spracherkennung und -übersetzung, Sprachverständnis und Bildanalyse. Diese Dienste sind mit einer kostenlosen Stufe in Azure verfügbar.

> 💁 Die kostenlose Stufe reicht aus, um ein Modell zu erstellen, es zu trainieren und es dann für Entwicklungsarbeiten zu verwenden. Sie können die Grenzen der kostenlosen Stufe auf der [Seite zu Custom Vision-Limits und -Quoten in der Microsoft-Dokumentation](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn) nachlesen.

### Aufgabe – Erstellen einer Cognitive Services-Ressource

Um Custom Vision zu verwenden, müssen Sie zunächst zwei Cognitive Services-Ressourcen in Azure mit der Azure CLI erstellen, eine für das Custom Vision-Training und eine für die Custom Vision-Vorhersage.

1. Erstellen Sie eine Ressourcengruppe für dieses Projekt mit dem Namen `fruit-quality-detector`.

1. Verwenden Sie den folgenden Befehl, um eine kostenlose Custom Vision-Trainingsressource zu erstellen:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Ersetzen Sie `<location>` durch den Standort, den Sie beim Erstellen der Ressourcengruppe verwendet haben.

    Dadurch wird eine Custom Vision-Trainingsressource in Ihrer Ressourcengruppe erstellt. Sie wird `fruit-quality-detector-training` heißen und die `F0` SKU verwenden, die die kostenlose Stufe ist. Die Option `--yes` bedeutet, dass Sie den Bedingungen der Cognitive Services zustimmen.

> 💁 Verwenden Sie die `S0` SKU, wenn Sie bereits ein kostenloses Konto mit einem der Cognitive Services nutzen.

1. Verwenden Sie den folgenden Befehl, um eine kostenlose Custom Vision-Vorhersageressource zu erstellen:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Ersetzen Sie `<location>` durch den Standort, den Sie beim Erstellen der Ressourcengruppe verwendet haben.

    Dadurch wird eine Custom Vision-Vorhersageressource in Ihrer Ressourcengruppe erstellt. Sie wird `fruit-quality-detector-prediction` heißen und die `F0` SKU verwenden, die die kostenlose Stufe ist. Die Option `--yes` bedeutet, dass Sie den Bedingungen der Cognitive Services zustimmen.

### Aufgabe – Erstellen eines Bildklassifikatorprojekts

1. Starten Sie das Custom Vision-Portal unter [CustomVision.ai](https://customvision.ai) und melden Sie sich mit dem Microsoft-Konto an, das Sie für Ihr Azure-Konto verwendet haben.

1. Folgen Sie dem Abschnitt [Erstellen eines neuen Projekts im Quickstart zur Erstellung eines Klassifikators in der Microsoft-Dokumentation](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project), um ein neues Custom Vision-Projekt zu erstellen. Die Benutzeroberfläche kann sich ändern, und diese Dokumentation ist immer die aktuellste Referenz.

    Nennen Sie Ihr Projekt `fruit-quality-detector`.

    Stellen Sie beim Erstellen Ihres Projekts sicher, dass Sie die zuvor erstellte Ressource `fruit-quality-detector-training` verwenden. Verwenden Sie den Projekttyp *Klassifikation*, den Klassifikationstyp *Multiklassen* und die Domäne *Lebensmittel*.

    ![Die Einstellungen für das Custom Vision-Projekt mit dem Namen fruit-quality-detector, keiner Beschreibung, der Ressource fruit-quality-detector-training, dem Projekttyp Klassifikation, dem Klassifikationstyp Multiklassen und der Domäne Lebensmittel.](../../../../../translated_images/de/custom-vision-create-project.cf46325b92d8b131089f6647cf5e07b664cb77850e106d66e3c057b6b69756c6.png)

✅ Nehmen Sie sich etwas Zeit, um die Benutzeroberfläche von Custom Vision für Ihren Bildklassifikator zu erkunden.

### Aufgabe – Trainieren Ihres Bildklassifikatorprojekts

Um einen Bildklassifikator zu trainieren, benötigen Sie mehrere Bilder von Obst, sowohl in guter als auch in schlechter Qualität, die Sie als gut und schlecht markieren können, wie z. B. eine reife und eine überreife Banane.
💁 Diese Klassifikatoren können Bilder von allem klassifizieren. Wenn du also keine Früchte unterschiedlicher Qualität zur Hand hast, kannst du stattdessen zwei verschiedene Obstsorten oder Katzen und Hunde verwenden!
Idealerweise sollte jedes Bild nur die Frucht zeigen, entweder mit einem einheitlichen Hintergrund oder einer großen Vielfalt an Hintergründen. Achten Sie darauf, dass im Hintergrund nichts zu sehen ist, was spezifisch für reife oder unreife Früchte ist.

> 💁 Es ist wichtig, keine spezifischen Hintergründe oder Gegenstände zu haben, die nicht mit dem zu klassifizierenden Objekt zusammenhängen. Andernfalls könnte der Klassifikator nur auf Basis des Hintergrunds klassifizieren. Es gab einmal einen Klassifikator für Hautkrebs, der auf Muttermale trainiert wurde, sowohl normale als auch krebsartige. Die krebsartigen Muttermale hatten alle Lineale daneben, um die Größe zu messen. Es stellte sich heraus, dass der Klassifikator fast 100 % genau war, wenn es darum ging, Lineale in Bildern zu erkennen, nicht aber krebsartige Muttermale.

Bildklassifikatoren arbeiten mit sehr niedriger Auflösung. Zum Beispiel kann Custom Vision Trainings- und Vorhersagebilder bis zu 10240x10240 verarbeiten, trainiert und führt das Modell jedoch mit Bildern in 227x227 aus. Größere Bilder werden auf diese Größe verkleinert, daher sollte das zu klassifizierende Objekt einen großen Teil des Bildes einnehmen, da es sonst in der kleineren Bildgröße, die der Klassifikator verwendet, zu klein sein könnte.

1. Sammeln Sie Bilder für Ihren Klassifikator. Sie benötigen mindestens 5 Bilder für jedes Label, um den Klassifikator zu trainieren, aber je mehr, desto besser. Sie benötigen auch einige zusätzliche Bilder, um den Klassifikator zu testen. Diese Bilder sollten alle unterschiedliche Aufnahmen desselben Objekts sein. Zum Beispiel:

    * Verwenden Sie 2 reife Bananen und machen Sie einige Bilder von jeder aus verschiedenen Blickwinkeln. Machen Sie mindestens 7 Bilder (5 zum Trainieren, 2 zum Testen), idealerweise mehr.

        ![Fotos von 2 verschiedenen Bananen](../../../../../translated_images/de/banana-training-images.530eb203346d73bc23b8b990fb4609470bf4ff7c942ccc13d4cfffeed9be1ad4.png)

    * Wiederholen Sie denselben Vorgang mit 2 unreifen Bananen.

    Sie sollten mindestens 10 Trainingsbilder haben, mit mindestens 5 reifen und 5 unreifen, sowie 4 Testbilder, 2 reife und 2 unreife. Ihre Bilder sollten im PNG- oder JPEG-Format vorliegen und kleiner als 6 MB sein. Wenn Sie sie beispielsweise mit einem iPhone erstellen, könnten es hochauflösende HEIC-Bilder sein, die konvertiert und möglicherweise verkleinert werden müssen. Je mehr Bilder, desto besser, und Sie sollten eine ähnliche Anzahl von reifen und unreifen Bildern haben.

    Wenn Sie keine reifen und unreifen Früchte haben, können Sie verschiedene Früchte oder beliebige zwei Objekte verwenden, die Sie zur Verfügung haben. Sie können auch einige Beispielbilder im [images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images)-Ordner von reifen und unreifen Bananen finden, die Sie verwenden können.

1. Folgen Sie dem Abschnitt [Bilder hochladen und taggen im Quickstart zum Erstellen eines Klassifikators in der Microsoft-Dokumentation](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images), um Ihre Trainingsbilder hochzuladen. Taggen Sie die reifen Früchte als `ripe` und die unreifen Früchte als `unripe`.

    ![Die Upload-Dialoge zeigen den Upload von Bildern reifer und unreifer Bananen](../../../../../translated_images/de/image-upload-bananas.0751639f3815e0ec42bdbc6254d1e4357a185834d1ae10c9948a0e7d6d336695.png)

1. Folgen Sie dem Abschnitt [Klassifikator trainieren im Quickstart zum Erstellen eines Klassifikators in der Microsoft-Dokumentation](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier), um den Bildklassifikator mit Ihren hochgeladenen Bildern zu trainieren.

    Sie haben die Wahl zwischen verschiedenen Trainingsarten. Wählen Sie **Schnelles Training**.

Der Klassifikator wird dann trainiert. Es dauert ein paar Minuten, bis das Training abgeschlossen ist.

> 🍌 Wenn Sie sich entscheiden, Ihre Früchte zu essen, während der Klassifikator trainiert, stellen Sie sicher, dass Sie vorher genügend Bilder zum Testen haben!

## Testen Sie Ihren Bildklassifikator

Sobald Ihr Klassifikator trainiert ist, können Sie ihn testen, indem Sie ihm ein neues Bild zur Klassifikation geben.

### Aufgabe - Testen Sie Ihren Bildklassifikator

1. Folgen Sie der [Dokumentation zum Testen Ihres Modells in der Microsoft-Dokumentation](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model), um Ihren Bildklassifikator zu testen. Verwenden Sie die Testbilder, die Sie zuvor erstellt haben, und nicht die Bilder, die Sie für das Training verwendet haben.

    ![Eine unreife Banane wird mit 98,9 % Wahrscheinlichkeit als unreif und mit 1,1 % Wahrscheinlichkeit als reif vorhergesagt](../../../../../translated_images/de/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64886422438850ea14f0be6ac918c217ea3b255c685abfabe7.png)

1. Testen Sie alle Testbilder, die Ihnen zur Verfügung stehen, und beobachten Sie die Wahrscheinlichkeiten.

## Trainieren Sie Ihren Bildklassifikator erneut

Wenn Sie Ihren Klassifikator testen, liefert er möglicherweise nicht die erwarteten Ergebnisse. Bildklassifikatoren verwenden maschinelles Lernen, um Vorhersagen darüber zu treffen, was auf einem Bild zu sehen ist, basierend auf Wahrscheinlichkeiten, dass bestimmte Merkmale eines Bildes zu einem bestimmten Label passen. Er versteht nicht, was auf dem Bild ist – er weiß nicht, was eine Banane ist oder was eine Banane von einem Boot unterscheidet. Sie können Ihren Klassifikator verbessern, indem Sie ihn mit Bildern, bei denen er Fehler macht, erneut trainieren.

Jedes Mal, wenn Sie eine Vorhersage mit der Schnelltest-Option machen, werden das Bild und die Ergebnisse gespeichert. Sie können diese Bilder verwenden, um Ihr Modell erneut zu trainieren.

### Aufgabe - Trainieren Sie Ihren Bildklassifikator erneut

1. Folgen Sie der [Dokumentation zur Verwendung vorhergesagter Bilder für das Training in der Microsoft-Dokumentation](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training), um Ihr Modell erneut zu trainieren, indem Sie das richtige Tag für jedes Bild verwenden.

1. Testen Sie Ihr Modell nach dem erneuten Training mit neuen Bildern.

---

## 🚀 Herausforderung

Was glauben Sie, würde passieren, wenn Sie ein Bild einer Erdbeere mit einem Modell testen, das auf Bananen trainiert wurde, oder ein Bild einer aufblasbaren Banane, einer Person im Bananenkostüm oder sogar einer gelben Cartoonfigur wie jemandem aus den Simpsons?

Probieren Sie es aus und sehen Sie, welche Vorhersagen gemacht werden. Sie können Bilder zum Testen mit der [Bing-Bildersuche](https://www.bing.com/images/trending) finden.

## Quiz nach der Vorlesung

[Quiz nach der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## Rückblick & Selbststudium

* Beim Training Ihres Klassifikators haben Sie Werte für *Precision*, *Recall* und *AP* gesehen, die das erstellte Modell bewerten. Lesen Sie nach, was diese Werte bedeuten, im Abschnitt [Klassifikator bewerten im Quickstart zum Erstellen eines Klassifikators in der Microsoft-Dokumentation](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier).
* Lesen Sie nach, wie Sie Ihren Klassifikator verbessern können, in der [Anleitung zur Verbesserung Ihres Custom Vision-Modells in der Microsoft-Dokumentation](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn).

## Aufgabe

[Trainieren Sie Ihren Klassifikator für mehrere Früchte und Gemüse](assignment.md)

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.