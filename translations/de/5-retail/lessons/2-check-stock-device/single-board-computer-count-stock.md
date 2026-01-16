<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-25T20:47:32+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "de"
}
-->
# Zähle Lagerbestände mit deinem IoT-Gerät – Virtuelle IoT-Hardware und Raspberry Pi

Eine Kombination aus den Vorhersagen und ihren Begrenzungsrahmen kann verwendet werden, um Lagerbestände in einem Bild zu zählen.

## Begrenzungsrahmen anzeigen

Als hilfreicher Debugging-Schritt kannst du nicht nur die Begrenzungsrahmen ausgeben, sondern sie auch auf das Bild zeichnen, das auf der Festplatte gespeichert wurde, als ein Bild aufgenommen wurde.

### Aufgabe – Begrenzungsrahmen ausgeben

1. Stelle sicher, dass das Projekt `stock-counter` in VS Code geöffnet ist und die virtuelle Umgebung aktiviert ist, falls du ein virtuelles IoT-Gerät verwendest.

1. Ändere die `print`-Anweisung in der `for`-Schleife wie folgt, um die Begrenzungsrahmen in der Konsole auszugeben:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Führe die App aus, während die Kamera auf einige Lagerbestände in einem Regal zeigt. Die Begrenzungsrahmen werden in der Konsole ausgegeben, mit Werten für links, oben, Breite und Höhe von 0-1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Aufgabe – Begrenzungsrahmen auf das Bild zeichnen

1. Das Pip-Paket [Pillow](https://pypi.org/project/Pillow/) kann verwendet werden, um auf Bildern zu zeichnen. Installiere es mit folgendem Befehl:

    ```sh
    pip3 install pillow
    ```

    Falls du ein virtuelles IoT-Gerät verwendest, stelle sicher, dass du dies innerhalb der aktivierten virtuellen Umgebung ausführst.

1. Füge die folgende Import-Anweisung am Anfang der Datei `app.py` hinzu:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Dies importiert den Code, der benötigt wird, um das Bild zu bearbeiten.

1. Füge den folgenden Code am Ende der Datei `app.py` hinzu:

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    Dieser Code öffnet das zuvor gespeicherte Bild zur Bearbeitung. Anschließend durchläuft er die Vorhersagen, um die Begrenzungsrahmen zu erhalten, und berechnet die Koordinaten der unteren rechten Ecke mithilfe der Begrenzungsrahmenwerte von 0-1. Diese werden dann in Bildkoordinaten umgerechnet, indem sie mit der entsprechenden Dimension des Bildes multipliziert werden. Zum Beispiel würde ein linker Wert von 0,5 bei einem Bild mit 600 Pixeln Breite in 300 umgerechnet werden (0,5 x 600 = 300).

    Jeder Begrenzungsrahmen wird mit einer roten Linie auf das Bild gezeichnet. Schließlich wird das bearbeitete Bild gespeichert und das ursprüngliche Bild überschrieben.

1. Führe die App aus, während die Kamera auf einige Lagerbestände in einem Regal zeigt. Du wirst die Datei `image.jpg` im VS Code Explorer sehen und kannst sie auswählen, um die Begrenzungsrahmen zu betrachten.

    ![4 Dosen Tomatenmark mit Begrenzungsrahmen um jede Dose](../../../../../translated_images/de/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

## Lagerbestände zählen

Im oben gezeigten Bild haben die Begrenzungsrahmen eine kleine Überlappung. Wenn diese Überlappung jedoch viel größer wäre, könnten die Begrenzungsrahmen dasselbe Objekt anzeigen. Um die Objekte korrekt zu zählen, musst du Rahmen mit einer signifikanten Überlappung ignorieren.

### Aufgabe – Lagerbestände zählen und Überlappungen ignorieren

1. Das Pip-Paket [Shapely](https://pypi.org/project/Shapely/) kann verwendet werden, um die Schnittmenge zu berechnen. Falls du einen Raspberry Pi verwendest, musst du zuerst eine Bibliotheksabhängigkeit installieren:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Installiere das Shapely-Pip-Paket:

    ```sh
    pip3 install shapely
    ```

    Falls du ein virtuelles IoT-Gerät verwendest, stelle sicher, dass du dies innerhalb der aktivierten virtuellen Umgebung ausführst.

1. Füge die folgende Import-Anweisung am Anfang der Datei `app.py` hinzu:

    ```python
    from shapely.geometry import Polygon
    ```

    Dies importiert den Code, der benötigt wird, um Polygone zu erstellen und Überlappungen zu berechnen.

1. Füge oberhalb des Codes, der die Begrenzungsrahmen zeichnet, den folgenden Code hinzu:

    ```python
    overlap_threshold = 0.20
    ```

    Dies definiert den Prozentsatz der Überlappung, der erlaubt ist, bevor die Begrenzungsrahmen als dasselbe Objekt betrachtet werden. 0,20 definiert eine 20%ige Überlappung.

1. Um die Überlappung mit Shapely zu berechnen, müssen die Begrenzungsrahmen in Shapely-Polygone umgewandelt werden. Füge die folgende Funktion hinzu, um dies zu tun:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Diese Funktion erstellt ein Polygon mithilfe des Begrenzungsrahmens einer Vorhersage.

1. Die Logik zum Entfernen überlappender Objekte beinhaltet den Vergleich aller Begrenzungsrahmen. Wenn ein Paar von Vorhersagen Begrenzungsrahmen hat, die die Schwelle der Überlappung überschreiten, wird eine der Vorhersagen gelöscht. Um alle Vorhersagen zu vergleichen, wird Vorhersage 1 mit 2, 3, 4 usw. verglichen, dann 2 mit 3, 4 usw. Der folgende Code führt dies aus:

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    Die Überlappung wird mit der Shapely-Methode `Polygon.intersection` berechnet, die ein Polygon zurückgibt, das die Überlappung darstellt. Die Fläche wird dann aus diesem Polygon berechnet. Diese Überlappungsschwelle ist kein absoluter Wert, sondern muss ein Prozentsatz des Begrenzungsrahmens sein. Daher wird der kleinste Begrenzungsrahmen gefunden, und die Überlappungsschwelle wird verwendet, um zu berechnen, welche Fläche die Überlappung haben kann, ohne den Prozentsatz der Überlappungsschwelle des kleinsten Begrenzungsrahmens zu überschreiten. Wenn die Überlappung diese überschreitet, wird die Vorhersage zum Löschen markiert.

    Sobald eine Vorhersage zum Löschen markiert wurde, muss sie nicht erneut überprüft werden, sodass die innere Schleife abbricht, um die nächste Vorhersage zu überprüfen. Du kannst keine Elemente aus einer Liste löschen, während du sie durchläufst. Daher werden die Begrenzungsrahmen, die die Schwelle der Überlappung überschreiten, zur Liste `to_delete` hinzugefügt und am Ende gelöscht.

    Schließlich wird die Anzahl der Lagerbestände in der Konsole ausgegeben. Diese könnte dann an einen IoT-Dienst gesendet werden, um zu alarmieren, wenn die Lagerbestände niedrig sind. All dieser Code befindet sich vor dem Zeichnen der Begrenzungsrahmen, sodass du die Lagerbestandsvorhersagen ohne Überlappungen auf den generierten Bildern sehen wirst.

    > 💁 Dies ist eine sehr einfache Methode, um Überlappungen zu entfernen, indem einfach das erste Element in einem überlappenden Paar entfernt wird. Für Produktionscode solltest du hier mehr Logik einfügen, z. B. die Überlappungen zwischen mehreren Objekten berücksichtigen oder prüfen, ob ein Begrenzungsrahmen in einem anderen enthalten ist.

1. Führe die App aus, während die Kamera auf einige Lagerbestände in einem Regal zeigt. Die Ausgabe zeigt die Anzahl der Begrenzungsrahmen ohne Überlappungen, die die Schwelle überschreiten. Versuche, den Wert von `overlap_threshold` anzupassen, um zu sehen, wie Vorhersagen ignoriert werden.

> 💁 Du findest diesen Code im Ordner [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) oder [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Dein Lagerzähler-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.