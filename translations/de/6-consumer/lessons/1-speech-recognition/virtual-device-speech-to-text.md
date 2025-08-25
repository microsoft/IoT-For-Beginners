<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-25T22:45:17+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "de"
}
-->
# Sprache zu Text - Virtuelles IoT-Gerät

In diesem Teil der Lektion schreiben Sie Code, um Sprache, die über Ihr Mikrofon aufgenommen wird, mithilfe des Sprachdienstes in Text umzuwandeln.

## Sprache in Text umwandeln

Unter Windows, Linux und macOS kann das Python SDK der Sprachdienste verwendet werden, um Ihr Mikrofon abzuhören und erkannte Sprache in Text umzuwandeln. Es hört kontinuierlich zu, erkennt die Audiopegel und sendet die Sprache zur Umwandlung in Text, wenn der Audiopegel abfällt, beispielsweise am Ende eines Sprachblocks.

### Aufgabe - Sprache in Text umwandeln

1. Erstellen Sie eine neue Python-App auf Ihrem Computer in einem Ordner namens `smart-timer` mit einer einzigen Datei namens `app.py` und einer Python-virtuellen Umgebung.

1. Installieren Sie das Pip-Paket für die Sprachdienste. Stellen Sie sicher, dass Sie dies in einem Terminal mit aktivierter virtueller Umgebung ausführen.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Wenn Sie den folgenden Fehler erhalten:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > müssen Sie Pip aktualisieren. Führen Sie dazu den folgenden Befehl aus und versuchen Sie anschließend, das Paket erneut zu installieren:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Fügen Sie die folgenden Importe zur Datei `app.py` hinzu:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Dies importiert einige Klassen, die zur Spracherkennung verwendet werden.

1. Fügen Sie den folgenden Code hinzu, um einige Konfigurationen zu deklarieren:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Ersetzen Sie `<key>` durch den API-Schlüssel für Ihren Sprachdienst. Ersetzen Sie `<location>` durch den Standort, den Sie bei der Erstellung der Ressource für den Sprachdienst verwendet haben.

    Ersetzen Sie `<language>` durch den Gebietsschema-Namen der Sprache, in der Sie sprechen werden, z. B. `en-GB` für Englisch oder `zn-HK` für Kantonesisch. Eine Liste der unterstützten Sprachen und ihrer Gebietsschema-Namen finden Sie in der [Dokumentation zur Sprach- und Sprachunterstützung auf Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Diese Konfiguration wird dann verwendet, um ein `SpeechConfig`-Objekt zu erstellen, das die Sprachdienste konfiguriert.

1. Fügen Sie den folgenden Code hinzu, um einen Sprachrekognizer zu erstellen:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Der Sprachrekognizer läuft in einem Hintergrund-Thread, hört auf Audio und wandelt erkannte Sprache in Text um. Sie können den Text über eine Callback-Funktion abrufen – eine Funktion, die Sie definieren und an den Rekognizer übergeben. Jedes Mal, wenn Sprache erkannt wird, wird der Callback aufgerufen. Fügen Sie den folgenden Code hinzu, um einen Callback zu definieren, diesen an den Rekognizer zu übergeben und eine Funktion zu definieren, die den Text verarbeitet und in die Konsole schreibt:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Der Rekognizer beginnt erst dann mit dem Zuhören, wenn Sie ihn explizit starten. Fügen Sie den folgenden Code hinzu, um die Erkennung zu starten. Dies läuft im Hintergrund, daher benötigt Ihre Anwendung auch eine Endlosschleife, die schläft, um die Anwendung am Laufen zu halten.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Führen Sie diese App aus. Sprechen Sie in Ihr Mikrofon, und die in Text umgewandelte Sprache wird in der Konsole ausgegeben.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Probieren Sie verschiedene Arten von Sätzen aus, einschließlich solcher, bei denen Wörter gleich klingen, aber unterschiedliche Bedeutungen haben. Wenn Sie beispielsweise auf Englisch sprechen, sagen Sie: „I want to buy two bananas and an apple too“ und achten Sie darauf, wie der richtige Kontext für „to“, „two“ und „too“ verwendet wird, basierend auf der Bedeutung des Wortes und nicht nur auf seinem Klang.

> 💁 Sie finden diesen Code im Ordner [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Ihr Sprache-zu-Text-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.