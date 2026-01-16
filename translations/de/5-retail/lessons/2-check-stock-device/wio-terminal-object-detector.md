<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-25T20:48:43+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "de"
}
-->
# Rufen Sie Ihren Objektdetektor von Ihrem IoT-Gerät aus - Wio Terminal

Sobald Ihr Objektdetektor veröffentlicht wurde, kann er von Ihrem IoT-Gerät aus verwendet werden.

## Kopieren Sie das Bildklassifizierungsprojekt

Der Großteil Ihres Lagerdetektors ist identisch mit dem Bildklassifizierer, den Sie in einer vorherigen Lektion erstellt haben.

### Aufgabe - Kopieren Sie das Bildklassifizierungsprojekt

1. Verbinden Sie Ihre ArduCam mit Ihrem Wio Terminal, indem Sie die Schritte aus [Lektion 2 des Fertigungsprojekts](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera) befolgen.

    Sie könnten die Kamera auch in einer festen Position befestigen, zum Beispiel, indem Sie das Kabel über eine Schachtel oder Dose hängen oder die Kamera mit doppelseitigem Klebeband an einer Schachtel befestigen.

1. Erstellen Sie ein brandneues Wio Terminal-Projekt mit PlatformIO. Nennen Sie dieses Projekt `stock-counter`.

1. Wiederholen Sie die Schritte aus [Lektion 2 des Fertigungsprojekts](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device), um Bilder mit der Kamera aufzunehmen.

1. Wiederholen Sie die Schritte aus [Lektion 2 des Fertigungsprojekts](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device), um den Bildklassifizierer aufzurufen. Der Großteil dieses Codes wird wiederverwendet, um Objekte zu erkennen.

## Ändern Sie den Code von einem Klassifizierer zu einem Objektdetektor

Der Code, den Sie verwendet haben, um Bilder zu klassifizieren, ist sehr ähnlich zu dem Code, der Objekte erkennt. Der Hauptunterschied ist die URL, die Sie von Custom Vision erhalten haben, und die Ergebnisse des Aufrufs.

### Aufgabe - Ändern Sie den Code von einem Klassifizierer zu einem Objektdetektor

1. Fügen Sie die folgende Include-Direktive oben in die Datei `main.cpp` ein:

    ```cpp
    #include <vector>
    ```

1. Benennen Sie die Funktion `classifyImage` in `detectStock` um, sowohl den Namen der Funktion als auch den Aufruf in der Funktion `buttonPressed`.

1. Deklarieren Sie oberhalb der Funktion `detectStock` eine Schwelle, um alle Erkennungen mit einer niedrigen Wahrscheinlichkeit herauszufiltern:

    ```cpp
    const float threshold = 0.3f;
    ```

    Im Gegensatz zu einem Bildklassifizierer, der nur ein Ergebnis pro Tag zurückgibt, liefert der Objektdetektor mehrere Ergebnisse. Daher müssen alle mit einer niedrigen Wahrscheinlichkeit herausgefiltert werden.

1. Deklarieren Sie oberhalb der Funktion `detectStock` eine Funktion, um die Vorhersagen zu verarbeiten:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    Diese Funktion nimmt eine Liste von Vorhersagen und gibt sie im seriellen Monitor aus.

1. Ersetzen Sie in der Funktion `detectStock` den Inhalt der `for`-Schleife, die durch die Vorhersagen iteriert, mit folgendem:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    Diese Schleife durchläuft die Vorhersagen und vergleicht die Wahrscheinlichkeit mit der Schwelle. Alle Vorhersagen, die eine höhere Wahrscheinlichkeit als die Schwelle haben, werden zu einer `list` hinzugefügt und an die Funktion `processPredictions` übergeben.

1. Laden Sie Ihren Code hoch und führen Sie ihn aus. Richten Sie die Kamera auf Objekte in einem Regal und drücken Sie die C-Taste. Sie werden die Ausgabe im seriellen Monitor sehen:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 Möglicherweise müssen Sie die `threshold` auf einen geeigneten Wert für Ihre Bilder anpassen.

    Sie können das aufgenommene Bild und diese Werte im **Predictions**-Tab in Custom Vision sehen.

    ![4 Dosen Tomatenmark auf einem Regal mit Vorhersagen für die 4 Erkennungen von 35,8 %, 33,5 %, 25,7 % und 16,6 %](../../../../../translated_images/de/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Sie finden diesen Code im Ordner [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Ihr Lagerzählprogramm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.