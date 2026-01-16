<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-25T20:56:33+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "de"
}
-->
# Überprüfung der Obstqualität mit einem IoT-Gerät

![Eine Sketchnote-Übersicht dieser Lektion](../../../../../translated_images/de/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.jpg)

> Sketchnote von [Nitya Narasimhan](https://github.com/nitya). Klicken Sie auf das Bild für eine größere Version.

## Quiz vor der Vorlesung

[Quiz vor der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Einführung

In der letzten Lektion haben Sie etwas über Bildklassifikatoren gelernt und wie man sie trainiert, um gutes und schlechtes Obst zu erkennen. Um diesen Bildklassifikator in einer IoT-Anwendung zu verwenden, müssen Sie in der Lage sein, ein Bild mit einer Kamera aufzunehmen und dieses Bild in die Cloud zu senden, um es zu klassifizieren.

In dieser Lektion lernen Sie Kamerasensoren kennen und wie Sie diese mit einem IoT-Gerät verwenden, um ein Bild aufzunehmen. Außerdem erfahren Sie, wie Sie den Bildklassifikator von Ihrem IoT-Gerät aus aufrufen können.

In dieser Lektion behandeln wir:

* [Kamerasensoren](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Ein Bild mit einem IoT-Gerät aufnehmen](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Ihren Bildklassifikator veröffentlichen](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Bilder von Ihrem IoT-Gerät klassifizieren](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Das Modell verbessern](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Kamerasensoren

Kamerasensoren sind, wie der Name schon sagt, Kameras, die Sie mit Ihrem IoT-Gerät verbinden können. Sie können Standbilder aufnehmen oder Streaming-Videos erfassen. Einige liefern Rohbilddaten, andere komprimieren die Bilddaten in eine Bilddatei wie JPEG oder PNG. Normalerweise sind die Kameras, die mit IoT-Geräten funktionieren, viel kleiner und haben eine geringere Auflösung als die, die Sie vielleicht gewohnt sind. Es gibt jedoch auch hochauflösende Kameras, die mit den besten Smartphones konkurrieren können. Sie können verschiedene Wechselobjektive, Mehrkamerasysteme, Infrarot-Wärmekameras oder UV-Kameras erhalten.

![Das Licht einer Szene passiert eine Linse und wird auf einen CMOS-Sensor fokussiert](../../../../../translated_images/de/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.png)

Die meisten Kamerasensoren verwenden Bildsensoren, bei denen jedes Pixel eine Fotodiode ist. Eine Linse fokussiert das Bild auf den Bildsensor, und Tausende oder Millionen von Fotodioden erfassen das Licht, das auf jede einzelne fällt, und zeichnen dies als Pixeldaten auf.

> 💁 Linsen drehen Bilder um, der Kamerasensor dreht das Bild dann wieder richtig herum. Das ist auch bei Ihren Augen der Fall – das, was Sie sehen, wird auf der Rückseite Ihres Auges auf den Kopf gestellt erfasst, und Ihr Gehirn korrigiert es.

> 🎓 Der Bildsensor wird als Active-Pixel-Sensor (APS) bezeichnet, und der beliebteste Typ von APS ist ein Complementary Metal-Oxide Semiconductor-Sensor, oder CMOS. Sie haben möglicherweise den Begriff CMOS-Sensor für Kamerasensoren gehört.

Kamerasensoren sind digitale Sensoren, die Bilddaten als digitale Daten senden, normalerweise mit Hilfe einer Bibliothek, die die Kommunikation bereitstellt. Kameras verwenden Protokolle wie SPI, um große Datenmengen zu senden – Bilder sind erheblich größer als einzelne Zahlen von einem Sensor wie einem Temperatursensor.

✅ Welche Einschränkungen gibt es bei der Bildgröße mit IoT-Geräten? Denken Sie insbesondere an die Beschränkungen bei Mikrocontroller-Hardware.

## Ein Bild mit einem IoT-Gerät aufnehmen

Sie können Ihr IoT-Gerät verwenden, um ein Bild aufzunehmen, das klassifiziert werden soll.

### Aufgabe – ein Bild mit einem IoT-Gerät aufnehmen

Arbeiten Sie die entsprechende Anleitung durch, um ein Bild mit Ihrem IoT-Gerät aufzunehmen:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Einplatinencomputer - Raspberry Pi](pi-camera.md)
* [Einplatinencomputer - Virtuelles Gerät](virtual-device-camera.md)

## Ihren Bildklassifikator veröffentlichen

Sie haben Ihren Bildklassifikator in der letzten Lektion trainiert. Bevor Sie ihn von Ihrem IoT-Gerät aus verwenden können, müssen Sie das Modell veröffentlichen.

### Modelliterationen

Während Ihr Modell in der letzten Lektion trainiert wurde, haben Sie möglicherweise bemerkt, dass die Registerkarte **Leistung** Iterationen auf der Seite anzeigt. Als Sie das Modell zum ersten Mal trainiert haben, haben Sie *Iteration 1* im Training gesehen. Als Sie das Modell mit den Vorhersagebildern verbessert haben, haben Sie *Iteration 2* im Training gesehen.

Jedes Mal, wenn Sie das Modell trainieren, erhalten Sie eine neue Iteration. Dies ist eine Möglichkeit, die verschiedenen Versionen Ihres Modells zu verfolgen, die mit unterschiedlichen Datensätzen trainiert wurden. Wenn Sie einen **Schnelltest** durchführen, gibt es ein Dropdown-Menü, mit dem Sie die Iteration auswählen können, sodass Sie die Ergebnisse über mehrere Iterationen hinweg vergleichen können.

Wenn Sie mit einer Iteration zufrieden sind, können Sie sie veröffentlichen, um sie für externe Anwendungen verfügbar zu machen. Auf diese Weise können Sie eine veröffentlichte Version haben, die von Ihren Geräten verwendet wird, dann an einer neuen Version über mehrere Iterationen arbeiten und diese veröffentlichen, sobald Sie damit zufrieden sind.

### Aufgabe – eine Iteration veröffentlichen

Iterationen werden über das Custom Vision-Portal veröffentlicht.

1. Starten Sie das Custom Vision-Portal unter [CustomVision.ai](https://customvision.ai) und melden Sie sich an, falls Sie es noch nicht geöffnet haben. Öffnen Sie dann Ihr Projekt `fruit-quality-detector`.

1. Wählen Sie die Registerkarte **Leistung** aus den Optionen oben aus.

1. Wählen Sie die neueste Iteration aus der Liste *Iterationen* auf der Seite aus.

1. Wählen Sie die Schaltfläche **Veröffentlichen** für die Iteration aus.

    ![Die Schaltfläche Veröffentlichen](../../../../../translated_images/de/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.png)

1. Legen Sie im Dialogfeld *Modell veröffentlichen* die *Vorhersageressource* auf die Ressource `fruit-quality-detector-prediction` fest, die Sie in der letzten Lektion erstellt haben. Lassen Sie den Namen als `Iteration2` und wählen Sie die Schaltfläche **Veröffentlichen** aus.

1. Sobald die Iteration veröffentlicht ist, wählen Sie die Schaltfläche **Vorhersage-URL** aus. Dies zeigt Details der Vorhersage-API, die Sie benötigen, um das Modell von Ihrem IoT-Gerät aus aufzurufen. Der untere Abschnitt ist mit *Wenn Sie eine Bilddatei haben* beschriftet, und dies sind die Details, die Sie benötigen. Kopieren Sie die angezeigte URL, die etwa so aussieht:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Dabei wird `<location>` der Standort sein, den Sie bei der Erstellung Ihrer Custom Vision-Ressource verwendet haben, und `<id>` wird eine lange ID aus Buchstaben und Zahlen sein.

    Kopieren Sie auch den Wert *Vorhersage-Schlüssel*. Dies ist ein sicherer Schlüssel, den Sie übergeben müssen, wenn Sie das Modell aufrufen. Nur Anwendungen, die diesen Schlüssel übergeben, dürfen das Modell verwenden, alle anderen Anwendungen werden abgelehnt.

    ![Das Dialogfeld Vorhersage-API zeigt die URL und den Schlüssel](../../../../../translated_images/de/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ Wenn eine neue Iteration veröffentlicht wird, hat sie einen anderen Namen. Wie würden Sie die Iteration ändern, die ein IoT-Gerät verwendet?

## Bilder von Ihrem IoT-Gerät klassifizieren

Sie können diese Verbindungsdetails jetzt verwenden, um den Bildklassifikator von Ihrem IoT-Gerät aus aufzurufen.

### Aufgabe – Bilder von Ihrem IoT-Gerät klassifizieren

Arbeiten Sie die entsprechende Anleitung durch, um Bilder mit Ihrem IoT-Gerät zu klassifizieren:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Einplatinencomputer - Raspberry Pi/Virtuelles IoT-Gerät](single-board-computer-classify-image.md)

## Das Modell verbessern

Es kann sein, dass die Ergebnisse, die Sie mit der Kamera Ihres IoT-Geräts erhalten, nicht den Erwartungen entsprechen. Die Vorhersagen sind möglicherweise nicht so genau wie bei Bildern, die von Ihrem Computer hochgeladen wurden. Dies liegt daran, dass das Modell mit anderen Daten trainiert wurde als denjenigen, die für Vorhersagen verwendet werden.

Um die besten Ergebnisse für einen Bildklassifikator zu erzielen, sollten Sie das Modell mit Bildern trainieren, die den für Vorhersagen verwendeten Bildern so ähnlich wie möglich sind. Wenn Sie beispielsweise Ihre Handykamera verwendet haben, um Bilder für das Training aufzunehmen, werden die Bildqualität, Schärfe und Farben anders sein als bei einer Kamera, die mit einem IoT-Gerät verbunden ist.

![2 Bananenbilder, eines mit niedriger Auflösung und schlechter Beleuchtung von einem IoT-Gerät, und eines mit hoher Auflösung und guter Beleuchtung von einem Telefon](../../../../../translated_images/de/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.png)

Im obigen Bild wurde das Bananenbild links mit einer Raspberry Pi-Kamera aufgenommen, das rechts mit einem iPhone von derselben Banane am selben Ort. Es gibt einen deutlichen Unterschied in der Qualität – das iPhone-Bild ist schärfer, mit helleren Farben und mehr Kontrast.

✅ Was könnte sonst noch dazu führen, dass die von Ihrem IoT-Gerät aufgenommenen Bilder falsche Vorhersagen haben? Denken Sie an die Umgebung, in der ein IoT-Gerät verwendet werden könnte. Welche Faktoren können das aufgenommene Bild beeinflussen?

Um das Modell zu verbessern, können Sie es mit den Bildern, die vom IoT-Gerät aufgenommen wurden, erneut trainieren.

### Aufgabe – das Modell verbessern

1. Klassifizieren Sie mehrere Bilder von reifen und unreifen Früchten mit Ihrem IoT-Gerät.

1. Trainieren Sie das Modell im Custom Vision-Portal erneut mit den Bildern auf der Registerkarte *Vorhersagen*.

    > ⚠️ Sie können [die Anweisungen zum erneuten Trainieren Ihres Klassifikators in Lektion 1 bei Bedarf](../1-train-fruit-detector/README.md#retrain-your-image-classifier) nachlesen.

1. Wenn Ihre Bilder sehr unterschiedlich zu den ursprünglichen Bildern aussehen, die für das Training verwendet wurden, können Sie alle ursprünglichen Bilder löschen, indem Sie sie auf der Registerkarte *Trainingsbilder* auswählen und die Schaltfläche **Löschen** auswählen. Um ein Bild auszuwählen, bewegen Sie den Cursor darüber, und ein Häkchen erscheint. Wählen Sie dieses Häkchen aus, um das Bild auszuwählen oder die Auswahl aufzuheben.

1. Trainieren Sie eine neue Iteration des Modells und veröffentlichen Sie es mit den oben genannten Schritten.

1. Aktualisieren Sie die Endpunkt-URL in Ihrem Code und führen Sie die App erneut aus.

1. Wiederholen Sie diese Schritte, bis Sie mit den Ergebnissen der Vorhersagen zufrieden sind.

---

## 🚀 Herausforderung

Wie stark beeinflussen die Bildauflösung oder Beleuchtung die Vorhersage?

Versuchen Sie, die Auflösung der Bilder in Ihrem Gerätecode zu ändern, und sehen Sie, ob dies einen Unterschied in der Qualität der Bilder macht. Probieren Sie auch unterschiedliche Beleuchtung aus.

Wenn Sie ein Produktionsgerät entwickeln würden, das an Bauernhöfe oder Fabriken verkauft wird, wie würden Sie sicherstellen, dass es immer konsistente Ergebnisse liefert?

## Quiz nach der Vorlesung

[Quiz nach der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Rückblick & Selbststudium

Sie haben Ihr Custom Vision-Modell mit dem Portal trainiert. Dies setzt voraus, dass Bilder verfügbar sind – und in der realen Welt können Sie möglicherweise keine Trainingsdaten erhalten, die mit den Bildern übereinstimmen, die die Kamera Ihres Geräts aufnimmt. Sie können dies umgehen, indem Sie direkt von Ihrem Gerät aus mit der Trainings-API trainieren, um ein Modell mit Bildern zu trainieren, die von Ihrem IoT-Gerät aufgenommen wurden.

* Lesen Sie mehr über die Trainings-API im [Schnellstart zur Verwendung des Custom Vision SDK](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Aufgabe

[Auf Klassifikationsergebnisse reagieren](assignment.md)

**Haftungsausschluss**:  
Dieses Dokument wurde mithilfe des KI-Übersetzungsdienstes [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.