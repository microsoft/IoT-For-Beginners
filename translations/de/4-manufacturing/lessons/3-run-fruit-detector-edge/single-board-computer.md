<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-25T21:09:36+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "de"
}
-->
# Klassifizieren eines Bildes mit einem IoT-Edge-basierten Bildklassifikator - Virtuelle IoT-Hardware und Raspberry Pi

In diesem Teil der Lektion verwenden Sie den Bildklassifikator, der auf dem IoT-Edge-Gerät läuft.

## Verwenden des IoT-Edge-Klassifikators

Das IoT-Gerät kann so umgeleitet werden, dass es den IoT-Edge-Bildklassifikator verwendet. Die URL für den Bildklassifikator lautet `http://<IP-Adresse oder Name>/image`, wobei `<IP-Adresse oder Name>` durch die IP-Adresse oder den Hostnamen des Computers ersetzt wird, auf dem IoT Edge läuft.

Die Python-Bibliothek für Custom Vision funktioniert nur mit cloud-gehosteten Modellen, nicht mit Modellen, die auf IoT Edge gehostet werden. Das bedeutet, dass Sie die REST-API verwenden müssen, um den Klassifikator aufzurufen.

### Aufgabe - Verwenden des IoT-Edge-Klassifikators

1. Öffnen Sie das Projekt `fruit-quality-detector` in VS Code, falls es noch nicht geöffnet ist. Wenn Sie ein virtuelles IoT-Gerät verwenden, stellen Sie sicher, dass die virtuelle Umgebung aktiviert ist.

1. Öffnen Sie die Datei `app.py` und entfernen Sie die Import-Anweisungen von `azure.cognitiveservices.vision.customvision.prediction` und `msrest.authentication`.

1. Fügen Sie die folgende Import-Anweisung am Anfang der Datei hinzu:

    ```python
    import requests
    ```

1. Löschen Sie den gesamten Code nach dem Speichern des Bildes in einer Datei, beginnend mit `image_file.write(image.read())` bis zum Ende der Datei.

1. Fügen Sie den folgenden Code am Ende der Datei hinzu:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Ersetzen Sie `<URL>` durch die URL Ihres Klassifikators.

    Dieser Code führt eine REST-POST-Anfrage an den Klassifikator aus und sendet das Bild als Body der Anfrage. Die Ergebnisse werden als JSON zurückgegeben und dekodiert, um die Wahrscheinlichkeiten auszugeben.

1. Führen Sie Ihren Code aus, während Ihre Kamera auf ein Stück Obst gerichtet ist, ein geeignetes Bildset verwendet wird oder Obst auf Ihrer Webcam sichtbar ist, falls Sie virtuelle IoT-Hardware verwenden. Sie sehen die Ausgabe in der Konsole:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Sie finden diesen Code im Ordner [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) oder [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Ihr Programm zur Klassifizierung der Obstqualität war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.