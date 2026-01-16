<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-25T20:46:38+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "de"
}
-->
# Zähle Lagerbestand mit deinem IoT-Gerät - Wio Terminal

Eine Kombination aus den Vorhersagen und ihren Begrenzungsrahmen kann verwendet werden, um den Lagerbestand in einem Bild zu zählen.

## Lagerbestand zählen

![4 Dosen Tomatenmark mit Begrenzungsrahmen um jede Dose](../../../../../translated_images/de/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

Im oben gezeigten Bild haben die Begrenzungsrahmen eine kleine Überlappung. Wenn diese Überlappung viel größer wäre, könnten die Begrenzungsrahmen dasselbe Objekt anzeigen. Um die Objekte korrekt zu zählen, müssen Sie Rahmen mit einer signifikanten Überlappung ignorieren.

### Aufgabe - Lagerbestand zählen und Überlappung ignorieren

1. Öffnen Sie Ihr `stock-counter`-Projekt, falls es nicht bereits geöffnet ist.

1. Fügen Sie oberhalb der Funktion `processPredictions` den folgenden Code hinzu:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Dies definiert den Prozentsatz der erlaubten Überlappung, bevor die Begrenzungsrahmen als dasselbe Objekt betrachtet werden. 0.20 definiert eine Überlappung von 20%.

1. Fügen Sie darunter, und oberhalb der Funktion `processPredictions`, den folgenden Code hinzu, um die Überlappung zwischen zwei Rechtecken zu berechnen:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    Dieser Code definiert eine `Point`-Struktur, um Punkte im Bild zu speichern, und eine `Rect`-Struktur, um ein Rechteck mit einer oberen linken und unteren rechten Koordinate zu definieren. Anschließend wird eine `area`-Funktion definiert, die die Fläche eines Rechtecks aus einer oberen linken und unteren rechten Koordinate berechnet.

    Danach wird eine `overlappingArea`-Funktion definiert, die die überlappende Fläche von zwei Rechtecken berechnet. Wenn sie sich nicht überlappen, wird 0 zurückgegeben.

1. Deklarieren Sie unterhalb der Funktion `overlappingArea` eine Funktion, um einen Begrenzungsrahmen in ein `Rect` umzuwandeln:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    Diese Funktion nimmt eine Vorhersage des Objekterkennungsmodells, extrahiert den Begrenzungsrahmen und verwendet die Werte des Begrenzungsrahmens, um ein Rechteck zu definieren. Die rechte Seite wird aus der linken Seite plus der Breite berechnet. Der untere Bereich wird als die obere Seite plus die Höhe berechnet.

1. Die Vorhersagen müssen miteinander verglichen werden, und wenn zwei Vorhersagen eine Überlappung haben, die den Schwellenwert überschreitet, muss eine von ihnen gelöscht werden. Der Überlappungsschwellenwert ist ein Prozentsatz, der mit der Größe des kleinsten Begrenzungsrahmens multipliziert werden muss, um zu überprüfen, ob die Überlappung den angegebenen Prozentsatz des Begrenzungsrahmens überschreitet, nicht den Prozentsatz des gesamten Bildes. Löschen Sie zunächst den Inhalt der Funktion `processPredictions`.

1. Fügen Sie der leeren Funktion `processPredictions` Folgendes hinzu:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    Dieser Code deklariert einen Vektor, um die Vorhersagen zu speichern, die sich nicht überlappen. Anschließend wird durch alle Vorhersagen geschleift, wobei ein `Rect` aus dem Begrenzungsrahmen erstellt wird.

    Danach wird durch die verbleibenden Vorhersagen geschleift, beginnend mit derjenigen nach der aktuellen Vorhersage. Dies verhindert, dass Vorhersagen mehr als einmal verglichen werden - sobald 1 und 2 verglichen wurden, besteht keine Notwendigkeit, 2 mit 1 zu vergleichen, sondern nur mit 3, 4 usw.

    Für jedes Paar von Vorhersagen wird die überlappende Fläche berechnet. Diese wird dann mit der Fläche des kleinsten Begrenzungsrahmens verglichen - wenn die Überlappung den Schwellenwertprozentsatz des kleinsten Begrenzungsrahmens überschreitet, wird die Vorhersage als nicht bestanden markiert. Wenn die Vorhersage nach dem Vergleich aller Überlappungen die Prüfungen besteht, wird sie der Sammlung `passed_predictions` hinzugefügt.

    > 💁 Dies ist eine sehr einfache Methode, um Überlappungen zu entfernen, indem einfach die erste in einem überlappenden Paar entfernt wird. Für Produktionscode sollten Sie hier mehr Logik einfügen, z. B. die Überlappungen zwischen mehreren Objekten berücksichtigen oder prüfen, ob ein Begrenzungsrahmen vollständig in einem anderen enthalten ist.

1. Fügen Sie danach den folgenden Code hinzu, um Details der bestandenen Vorhersagen an den seriellen Monitor zu senden:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    Dieser Code schleift durch die bestandenen Vorhersagen und druckt deren Details auf den seriellen Monitor.

1. Fügen Sie darunter Code hinzu, um die Anzahl der gezählten Objekte auf den seriellen Monitor zu drucken:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Dies könnte dann an einen IoT-Dienst gesendet werden, um zu alarmieren, wenn die Lagerbestände niedrig sind.

1. Laden Sie Ihren Code hoch und führen Sie ihn aus. Richten Sie die Kamera auf Objekte in einem Regal und drücken Sie die C-Taste. Versuchen Sie, den Wert von `overlap_threshold` anzupassen, um zu sehen, wie Vorhersagen ignoriert werden.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 Sie finden diesen Code im Ordner [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Ihr Lagerzähler-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.