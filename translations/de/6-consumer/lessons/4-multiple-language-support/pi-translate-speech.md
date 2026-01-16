<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-25T22:28:20+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "de"
}
-->
# Sprache übersetzen - Raspberry Pi

In diesem Teil der Lektion schreiben Sie Code, um Text mithilfe des Übersetzungsdienstes zu übersetzen.

## Text in Sprache umwandeln mit dem Übersetzungsdienst

Die REST-API des Sprachdienstes unterstützt keine direkten Übersetzungen. Stattdessen können Sie den Übersetzungsdienst nutzen, um den Text zu übersetzen, der vom Sprach-zu-Text-Dienst generiert wurde, sowie den Text der gesprochenen Antwort. Dieser Dienst bietet eine REST-API, mit der Sie den Text übersetzen können.

### Aufgabe - Den Übersetzungsdienst nutzen, um Text zu übersetzen

1. Ihr intelligenter Timer wird auf zwei Sprachen eingestellt sein – die Sprache des Servers, der für das Training von LUIS verwendet wurde (diese Sprache wird auch verwendet, um die Nachrichten zu erstellen, die dem Benutzer vorgelesen werden), und die Sprache, die vom Benutzer gesprochen wird. Aktualisieren Sie die Variable `language`, sodass sie die Sprache enthält, die vom Benutzer gesprochen wird, und fügen Sie eine neue Variable namens `server_language` für die Sprache hinzu, die für das Training von LUIS verwendet wurde:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Ersetzen Sie `<user language>` durch den Lokalisierungsnamen der Sprache, die Sie sprechen werden, z. B. `fr-FR` für Französisch oder `zn-HK` für Kantonesisch.

    Ersetzen Sie `<server language>` durch den Lokalisierungsnamen der Sprache, die für das Training von LUIS verwendet wurde.

    Eine Liste der unterstützten Sprachen und ihrer Lokalisierungsnamen finden Sie in der [Dokumentation zu Sprach- und Sprachunterstützung auf Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Wenn Sie keine mehreren Sprachen sprechen, können Sie einen Dienst wie [Bing Translate](https://www.bing.com/translator) oder [Google Translate](https://translate.google.com) verwenden, um von Ihrer bevorzugten Sprache in eine andere Sprache zu übersetzen. Diese Dienste können dann Audio des übersetzten Textes abspielen.
    >
    > Zum Beispiel, wenn Sie LUIS auf Englisch trainieren, aber Französisch als Benutzersprache verwenden möchten, können Sie Sätze wie "set a 2 minute and 27 second timer" mit Bing Translate von Englisch ins Französische übersetzen und dann die Schaltfläche **Listen translation** verwenden, um die Übersetzung in Ihr Mikrofon zu sprechen.
    >
    > ![Die Schaltfläche "Listen translation" auf Bing Translate](../../../../../translated_images/de/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Fügen Sie den API-Schlüssel des Übersetzungsdienstes unterhalb des `speech_api_key` hinzu:

    ```python
    translator_api_key = '<key>'
    ```

    Ersetzen Sie `<key>` durch den API-Schlüssel für Ihre Übersetzungsdienst-Ressource.

1. Definieren Sie oberhalb der Funktion `say` eine Funktion `translate_text`, die Text von der Serversprache in die Benutzersprache übersetzt:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Die Quell- und Zielsprache werden an diese Funktion übergeben – Ihre App muss von der Benutzersprache in die Serversprache übersetzen, wenn Sprache erkannt wird, und von der Serversprache in die Benutzersprache, wenn gesprochene Rückmeldungen gegeben werden.

1. Definieren Sie innerhalb dieser Funktion die URL und die Header für den REST-API-Aufruf:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    Die URL für diese API ist nicht standortspezifisch, stattdessen wird der Standort als Header übergeben. Der API-Schlüssel wird direkt verwendet, sodass im Gegensatz zum Sprachdienst kein Zugriffstoken von der Token-Aussteller-API abgerufen werden muss.

1. Definieren Sie darunter die Parameter und den Body für den Aufruf:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    Die `params` definieren die Parameter, die an den API-Aufruf übergeben werden, und geben die Quell- und Zielsprache an. Dieser Aufruf übersetzt Text in der Quellsprache in die Zielsprache.

    Der `body` enthält den zu übersetzenden Text. Dies ist ein Array, da mehrere Textblöcke in einem einzigen Aufruf übersetzt werden können.

1. Führen Sie den REST-API-Aufruf aus und holen Sie die Antwort:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Die Antwort, die zurückkommt, ist ein JSON-Array mit einem Element, das die Übersetzungen enthält. Dieses Element hat ein Array für die Übersetzungen aller im Body übergebenen Elemente.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. Geben Sie die Eigenschaft `text` der ersten Übersetzung aus dem ersten Element des Arrays zurück:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Aktualisieren Sie die Schleife `while True`, um den Text aus dem Aufruf von `convert_speech_to_text` von der Benutzersprache in die Serversprache zu übersetzen:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Dieser Code gibt auch die ursprüngliche und die übersetzte Version des Textes in der Konsole aus.

1. Aktualisieren Sie die Funktion `say`, um den Text, der gesprochen werden soll, von der Serversprache in die Benutzersprache zu übersetzen:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Dieser Code gibt auch die ursprüngliche und die übersetzte Version des Textes in der Konsole aus.

1. Führen Sie Ihren Code aus. Stellen Sie sicher, dass Ihre Funktions-App läuft, und fordern Sie einen Timer in der Benutzersprache an, entweder indem Sie selbst in dieser Sprache sprechen oder eine Übersetzungs-App verwenden.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Aufgrund der unterschiedlichen Ausdrucksweisen in verschiedenen Sprachen können die Übersetzungen leicht von den Beispielen abweichen, die Sie LUIS gegeben haben. In diesem Fall fügen Sie LUIS weitere Beispiele hinzu, trainieren Sie das Modell erneut und veröffentlichen Sie es erneut.

> 💁 Sie finden diesen Code im Ordner [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 Ihr mehrsprachiges Timer-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.