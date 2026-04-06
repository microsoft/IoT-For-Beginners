# Rufen Sie Ihren Objektdetektor von Ihrem IoT-Gerät auf - Virtuelle IoT-Hardware und Raspberry Pi

Sobald Ihr Objektdetektor veröffentlicht wurde, kann er von Ihrem IoT-Gerät aus verwendet werden.

## Kopieren Sie das Bildklassifizierungsprojekt

Der Großteil Ihres Lagerdetektors ist identisch mit dem Bildklassifizierer, den Sie in einer vorherigen Lektion erstellt haben.

### Aufgabe - Kopieren Sie das Bildklassifizierungsprojekt

1. Erstellen Sie einen Ordner namens `stock-counter` entweder auf Ihrem Computer, wenn Sie ein virtuelles IoT-Gerät verwenden, oder auf Ihrem Raspberry Pi. Wenn Sie ein virtuelles IoT-Gerät verwenden, stellen Sie sicher, dass Sie eine virtuelle Umgebung einrichten.

1. Richten Sie die Kamerahardware ein.

    * Wenn Sie einen Raspberry Pi verwenden, müssen Sie die PiCamera anbringen. Sie könnten die Kamera auch in einer festen Position fixieren, z. B. indem Sie das Kabel über eine Box oder Dose hängen oder die Kamera mit doppelseitigem Klebeband an einer Box befestigen.
    * Wenn Sie ein virtuelles IoT-Gerät verwenden, müssen Sie CounterFit und das CounterFit PyCamera-Shim installieren. Wenn Sie Standbilder verwenden möchten, erfassen Sie einige Bilder, die Ihr Objektdetektor noch nicht gesehen hat. Wenn Sie Ihre Webcam verwenden möchten, stellen Sie sicher, dass sie so positioniert ist, dass sie die zu erkennenden Lagerbestände sehen kann.

1. Wiederholen Sie die Schritte aus [Lektion 2 des Fertigungsprojekts](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device), um Bilder von der Kamera aufzunehmen.

1. Wiederholen Sie die Schritte aus [Lektion 2 des Fertigungsprojekts](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device), um den Bildklassifizierer aufzurufen. Der Großteil dieses Codes wird wiederverwendet, um Objekte zu erkennen.

## Ändern Sie den Code von einem Klassifizierer zu einem Objektdetektor

Der Code, den Sie zur Klassifizierung von Bildern verwendet haben, ist dem Code zur Objekterkennung sehr ähnlich. Der Hauptunterschied liegt in der Methode, die im Custom Vision SDK aufgerufen wird, und den Ergebnissen des Aufrufs.

### Aufgabe - Ändern Sie den Code von einem Klassifizierer zu einem Objektdetektor

1. Löschen Sie die drei Codezeilen, die das Bild klassifizieren und die Vorhersagen verarbeiten:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Entfernen Sie diese drei Zeilen.

1. Fügen Sie den folgenden Code hinzu, um Objekte im Bild zu erkennen:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Dieser Code ruft die Methode `detect_image` auf dem Prädiktor auf, um den Objektdetektor auszuführen. Anschließend werden alle Vorhersagen mit einer Wahrscheinlichkeit über einem Schwellenwert gesammelt und in der Konsole ausgegeben.

    Im Gegensatz zu einem Bildklassifizierer, der nur ein Ergebnis pro Tag zurückgibt, liefert der Objektdetektor mehrere Ergebnisse. Daher müssen alle mit einer niedrigen Wahrscheinlichkeit herausgefiltert werden.

1. Führen Sie diesen Code aus. Er wird ein Bild aufnehmen, es an den Objektdetektor senden und die erkannten Objekte ausgeben. Wenn Sie ein virtuelles IoT-Gerät verwenden, stellen Sie sicher, dass Sie ein geeignetes Bild in CounterFit eingestellt haben oder Ihre Webcam ausgewählt ist. Wenn Sie einen Raspberry Pi verwenden, stellen Sie sicher, dass Ihre Kamera auf Objekte in einem Regal zeigt.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Möglicherweise müssen Sie den `threshold` an einen geeigneten Wert für Ihre Bilder anpassen.

    Sie können das aufgenommene Bild und diese Werte im **Predictions**-Tab in Custom Vision sehen.

    ![4 Dosen Tomatenmark auf einem Regal mit Vorhersagen für die 4 Erkennungen von 35,8 %, 33,5 %, 25,7 % und 16,6 %](../../../../../translated_images/de/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Sie finden diesen Code im Ordner [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) oder [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 Ihr Lagerzähler-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.