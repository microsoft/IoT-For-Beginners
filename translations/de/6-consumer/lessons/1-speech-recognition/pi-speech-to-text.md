<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-25T22:51:09+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "de"
}
-->
# Sprache zu Text - Raspberry Pi

In diesem Teil der Lektion schreiben Sie Code, um Sprache aus dem aufgenommenen Audio in Text umzuwandeln, indem Sie den Sprachdienst verwenden.

## Senden Sie das Audio an den Sprachdienst

Das Audio kann über die REST-API an den Sprachdienst gesendet werden. Um den Sprachdienst zu nutzen, müssen Sie zunächst ein Zugriffstoken anfordern und dieses dann verwenden, um auf die REST-API zuzugreifen. Diese Zugriffstoken laufen nach 10 Minuten ab, daher sollte Ihr Code sie regelmäßig anfordern, um sicherzustellen, dass sie immer aktuell sind.

### Aufgabe - Zugriffstoken abrufen

1. Öffnen Sie das Projekt `smart-timer` auf Ihrem Raspberry Pi.

1. Entfernen Sie die Funktion `play_audio`. Diese wird nicht mehr benötigt, da Sie nicht möchten, dass der Smart Timer Ihnen das Gesagte wiederholt.

1. Fügen Sie die folgende Import-Anweisung oben in die Datei `app.py` ein:

    ```python
    import requests
    ```

1. Fügen Sie den folgenden Code oberhalb der Schleife `while True` ein, um einige Einstellungen für den Sprachdienst zu deklarieren:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Ersetzen Sie `<key>` durch den API-Schlüssel für Ihre Sprachdienst-Ressource. Ersetzen Sie `<location>` durch den Standort, den Sie bei der Erstellung der Sprachdienst-Ressource verwendet haben.

    Ersetzen Sie `<language>` durch den Gebietsschema-Namen der Sprache, in der Sie sprechen werden, z. B. `en-GB` für Englisch oder `zn-HK` für Kantonesisch. Eine Liste der unterstützten Sprachen und ihrer Gebietsschema-Namen finden Sie in der [Dokumentation zur Sprach- und Stimmenunterstützung auf Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Fügen Sie darunter die folgende Funktion ein, um ein Zugriffstoken zu erhalten:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Diese Funktion ruft einen Token-Ausgabe-Endpunkt auf und übergibt den API-Schlüssel als Header. Der Endpunkt gibt ein Zugriffstoken zurück, das verwendet werden kann, um die Sprachdienste aufzurufen.

1. Deklarieren Sie darunter eine Funktion, um Sprache aus dem aufgenommenen Audio mithilfe der REST-API in Text umzuwandeln:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Richten Sie innerhalb dieser Funktion die REST-API-URL und die Header ein:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Diese Funktion erstellt eine URL basierend auf dem Standort der Sprachdienst-Ressource. Anschließend werden die Header mit dem Zugriffstoken aus der Funktion `get_access_token` sowie der Abtastrate des aufgenommenen Audios gefüllt. Schließlich werden einige Parameter definiert, die mit der URL übergeben werden und die Sprache des Audios enthalten.

1. Fügen Sie darunter den folgenden Code ein, um die REST-API aufzurufen und den Text zurückzubekommen:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Diese Funktion ruft die URL auf und dekodiert den JSON-Wert, der in der Antwort enthalten ist. Der Wert `RecognitionStatus` in der Antwort zeigt an, ob die Umwandlung von Sprache in Text erfolgreich war. Wenn dieser Wert `Success` ist, wird der Text aus der Funktion zurückgegeben, andernfalls wird ein leerer String zurückgegeben.

1. Definieren Sie oberhalb der Schleife `while True:` eine Funktion, um den Text zu verarbeiten, der vom Sprachdienst zurückgegeben wird. Diese Funktion wird den Text vorerst nur in der Konsole ausgeben.

    ```python
    def process_text(text):
        print(text)
    ```

1. Ersetzen Sie schließlich den Aufruf von `play_audio` in der Schleife `while True` durch einen Aufruf der Funktion `convert_speech_to_text`, wobei der Text an die Funktion `process_text` übergeben wird:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Führen Sie den Code aus. Drücken Sie die Taste und sprechen Sie ins Mikrofon. Lassen Sie die Taste los, wenn Sie fertig sind, und das Audio wird in Text umgewandelt und in der Konsole ausgegeben.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Probieren Sie verschiedene Arten von Sätzen aus, einschließlich Sätzen, bei denen Wörter gleich klingen, aber unterschiedliche Bedeutungen haben. Wenn Sie beispielsweise auf Englisch sprechen, sagen Sie: „I want to buy two bananas and an apple too“ und bemerken Sie, wie der Dienst das korrekte „to“, „two“ und „too“ basierend auf dem Kontext des Wortes verwendet, nicht nur basierend auf seinem Klang.

> 💁 Sie finden diesen Code im Ordner [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Ihr Sprache-zu-Text-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.