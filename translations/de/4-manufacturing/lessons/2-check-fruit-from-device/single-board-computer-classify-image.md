<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-25T20:59:20+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "de"
}
-->
# Klassifizieren eines Bildes - Virtuelle IoT-Hardware und Raspberry Pi

In diesem Teil der Lektion senden Sie das vom Kamera erfasste Bild an den Custom Vision-Dienst, um es zu klassifizieren.

## Bilder an Custom Vision senden

Der Custom Vision-Dienst verfügt über ein Python-SDK, das Sie zur Klassifizierung von Bildern verwenden können.

### Aufgabe - Bilder an Custom Vision senden

1. Öffnen Sie den Ordner `fruit-quality-detector` in VS Code. Wenn Sie ein virtuelles IoT-Gerät verwenden, stellen Sie sicher, dass die virtuelle Umgebung im Terminal läuft.

1. Das Python-SDK zum Senden von Bildern an Custom Vision ist als Pip-Paket verfügbar. Installieren Sie es mit folgendem Befehl:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Fügen Sie die folgenden Import-Anweisungen am Anfang der Datei `app.py` hinzu:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Damit werden einige Module aus den Custom Vision-Bibliotheken eingebunden, eines zur Authentifizierung mit dem Prediction Key und eines, um eine Prediction-Client-Klasse bereitzustellen, die Custom Vision aufrufen kann.

1. Fügen Sie den folgenden Code am Ende der Datei hinzu:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Ersetzen Sie `<prediction_url>` durch die URL, die Sie zuvor im Dialogfeld *Prediction URL* kopiert haben. Ersetzen Sie `<prediction key>` durch den Prediction Key, den Sie aus demselben Dialogfeld kopiert haben.

1. Die Prediction-URL, die im Dialogfeld *Prediction URL* bereitgestellt wurde, ist so konzipiert, dass sie direkt beim Aufruf des REST-Endpunkts verwendet wird. Das Python-SDK verwendet Teile der URL an verschiedenen Stellen. Fügen Sie den folgenden Code hinzu, um diese URL in die benötigten Teile aufzuteilen:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Dies teilt die URL auf und extrahiert den Endpunkt `https://<location>.api.cognitive.microsoft.com`, die Projekt-ID und den Namen der veröffentlichten Iteration.

1. Erstellen Sie ein Predictor-Objekt, um die Vorhersage mit folgendem Code durchzuführen:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    Die `prediction_credentials` umschließen den Prediction Key. Diese werden dann verwendet, um ein Prediction-Client-Objekt zu erstellen, das auf den Endpunkt zeigt.

1. Senden Sie das Bild mit folgendem Code an Custom Vision:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Dies spult das Bild zurück zum Anfang und sendet es dann an den Prediction-Client.

1. Zeigen Sie schließlich die Ergebnisse mit folgendem Code an:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Dies durchläuft alle zurückgegebenen Vorhersagen und zeigt sie im Terminal an. Die zurückgegebenen Wahrscheinlichkeiten sind Gleitkommazahlen von 0 bis 1, wobei 0 einer 0%igen Übereinstimmung mit dem Tag entspricht und 1 einer 100%igen Übereinstimmung.

    > 💁 Bildklassifizierer geben die Prozentsätze für alle verwendeten Tags zurück. Jedes Tag hat eine Wahrscheinlichkeit, dass das Bild diesem Tag entspricht.

1. Führen Sie Ihren Code aus, während Ihre Kamera auf ein Stück Obst, ein geeignetes Bildset oder Obst, das auf Ihrer Webcam sichtbar ist (bei Verwendung virtueller IoT-Hardware), gerichtet ist. Sie sehen die Ausgabe in der Konsole:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Sie können das aufgenommene Bild sehen und diese Werte im **Predictions**-Tab in Custom Vision einsehen.

    ![Eine Banane in Custom Vision, vorhergesagt als reif mit 56,8% und unreif mit 43,1%](../../../../../translated_images/de/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Sie finden diesen Code im Ordner [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) oder [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Ihr Programm zur Klassifizierung der Obstqualität war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.