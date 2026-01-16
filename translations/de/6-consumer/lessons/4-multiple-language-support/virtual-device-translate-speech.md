<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-25T22:29:18+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "de"
}
-->
# Übersetze Sprache - Virtuelles IoT-Gerät

In diesem Teil der Lektion schreiben Sie Code, um Sprache bei der Umwandlung in Text mit dem Sprachdienst zu übersetzen, anschließend Text mit dem Übersetzungsdienst zu übersetzen und schließlich eine gesprochene Antwort zu generieren.

## Verwenden Sie den Sprachdienst, um Sprache zu übersetzen

Der Sprachdienst kann Sprache nicht nur in Text in derselben Sprache umwandeln, sondern auch die Ausgabe in andere Sprachen übersetzen.

### Aufgabe - Verwenden Sie den Sprachdienst, um Sprache zu übersetzen

1. Öffnen Sie das Projekt `smart-timer` in VS Code und stellen Sie sicher, dass die virtuelle Umgebung im Terminal geladen ist.

1. Fügen Sie die folgenden Importanweisungen unter den bestehenden Imports hinzu:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Dies importiert Klassen, die zur Übersetzung von Sprache verwendet werden, sowie eine `requests`-Bibliothek, die später in dieser Lektion für einen Aufruf des Übersetzungsdienstes verwendet wird.

1. Ihr Smart-Timer wird zwei Sprachen haben - die Sprache des Servers, die für das Training von LUIS verwendet wurde (diese Sprache wird auch verwendet, um Nachrichten zu erstellen, die dem Benutzer gesprochen werden), und die Sprache, die vom Benutzer gesprochen wird. Aktualisieren Sie die Variable `language`, um die Sprache festzulegen, die vom Benutzer gesprochen wird, und fügen Sie eine neue Variable namens `server_language` für die Sprache hinzu, die für das Training von LUIS verwendet wurde:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Ersetzen Sie `<user language>` durch den Gebietsschemanamen der Sprache, in der Sie sprechen werden, z. B. `fr-FR` für Französisch oder `zn-HK` für Kantonesisch.

    Ersetzen Sie `<server language>` durch den Gebietsschemanamen der Sprache, die für das Training von LUIS verwendet wurde.

    Eine Liste der unterstützten Sprachen und ihrer Gebietsschemanamen finden Sie in der [Dokumentation zur Sprach- und Sprachunterstützung auf Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Wenn Sie keine mehreren Sprachen sprechen, können Sie einen Dienst wie [Bing Translate](https://www.bing.com/translator) oder [Google Translate](https://translate.google.com) verwenden, um von Ihrer bevorzugten Sprache in eine Sprache Ihrer Wahl zu übersetzen. Diese Dienste können dann Audio des übersetzten Textes abspielen. Beachten Sie, dass der Spracherkenner einige Audioausgaben von Ihrem Gerät ignorieren kann, sodass Sie möglicherweise ein zusätzliches Gerät benötigen, um den übersetzten Text abzuspielen.
    >
    > Wenn Sie beispielsweise LUIS auf Englisch trainieren, aber Französisch als Benutzersprache verwenden möchten, können Sie Sätze wie "set a 2 minute and 27 second timer" von Englisch ins Französische mit Bing Translate übersetzen und dann die Schaltfläche **Listen translation** verwenden, um die Übersetzung in Ihr Mikrofon zu sprechen.
    >
    > ![Die Schaltfläche "Listen translation" auf Bing Translate](../../../../../translated_images/de/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Ersetzen Sie die Deklarationen `recognizer_config` und `recognizer` durch Folgendes:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Dies erstellt eine Übersetzungskonfiguration, um Sprache in der Benutzersprache zu erkennen und Übersetzungen in der Benutzer- und Serversprache zu erstellen. Anschließend wird diese Konfiguration verwendet, um einen Übersetzungsrekognizer zu erstellen - einen Sprachrekognizer, der die Ausgabe der Spracherkennung in mehrere Sprachen übersetzen kann.

    > 💁 Die ursprüngliche Sprache muss in den `target_languages` angegeben werden, andernfalls erhalten Sie keine Übersetzungen.

1. Aktualisieren Sie die Funktion `recognized`, indem Sie den gesamten Inhalt der Funktion durch Folgendes ersetzen:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Dieser Code überprüft, ob das erkannte Ereignis ausgelöst wurde, weil Sprache übersetzt wurde (dieses Ereignis kann zu anderen Zeiten ausgelöst werden, z. B. wenn die Sprache erkannt, aber nicht übersetzt wurde). Wenn die Sprache übersetzt wurde, findet er die Übersetzung im Wörterbuch `args.result.translations`, die der Serversprache entspricht.

    Das Wörterbuch `args.result.translations` ist nach dem Sprachteil der Gebietsschemaeinstellung und nicht nach der gesamten Einstellung geordnet. Wenn Sie beispielsweise eine Übersetzung in `fr-FR` für Französisch anfordern, enthält das Wörterbuch einen Eintrag für `fr`, nicht für `fr-FR`.

    Der übersetzte Text wird dann an den IoT-Hub gesendet.

1. Führen Sie diesen Code aus, um die Übersetzungen zu testen. Stellen Sie sicher, dass Ihre Funktions-App läuft, und fordern Sie einen Timer in der Benutzersprache an, entweder indem Sie diese Sprache selbst sprechen oder eine Übersetzungs-App verwenden.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Übersetzen Sie Text mit dem Übersetzungsdienst

Der Sprachdienst unterstützt keine Rückübersetzung von Text in Sprache. Stattdessen können Sie den Übersetzungsdienst verwenden, um den Text zu übersetzen. Dieser Dienst verfügt über eine REST-API, die Sie zur Übersetzung des Textes verwenden können.

### Aufgabe - Verwenden Sie die Übersetzungsressource, um Text zu übersetzen

1. Fügen Sie den API-Schlüssel des Übersetzungsdienstes unterhalb des `speech_api_key` hinzu:

    ```python
    translator_api_key = '<key>'
    ```

    Ersetzen Sie `<key>` durch den API-Schlüssel für Ihre Übersetzungsdienstressource.

1. Definieren Sie oberhalb der Funktion `say` eine Funktion `translate_text`, die Text von der Serversprache in die Benutzersprache übersetzt:

    ```python
    def translate_text(text):
    ```

1. Definieren Sie innerhalb dieser Funktion die URL und die Header für den REST-API-Aufruf:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    Die URL für diese API ist nicht ortsspezifisch, stattdessen wird der Standort als Header übergeben. Der API-Schlüssel wird direkt verwendet, sodass im Gegensatz zum Sprachdienst kein Zugriffstoken von der Token-Aussteller-API abgerufen werden muss.

1. Definieren Sie darunter die Parameter und den Body für den Aufruf:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    Die `params` definieren die Parameter, die an den API-Aufruf übergeben werden, und geben die Ausgangs- und Zielsprachen an. Dieser Aufruf übersetzt Text in der `from`-Sprache in die `to`-Sprache.

    Der `body` enthält den zu übersetzenden Text. Dies ist ein Array, da mehrere Textblöcke im selben Aufruf übersetzt werden können.

1. Führen Sie den REST-API-Aufruf aus und holen Sie die Antwort:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Die Antwort, die zurückkommt, ist ein JSON-Array mit einem Element, das die Übersetzungen enthält. Dieses Element hat ein Array für Übersetzungen aller im Body übergebenen Elemente.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. Geben Sie die Eigenschaft `text` der ersten Übersetzung des ersten Elements im Array zurück:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Aktualisieren Sie die Funktion `say`, um den zu sprechenden Text zu übersetzen, bevor das SSML generiert wird:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Dieser Code druckt auch die ursprüngliche und die übersetzte Version des Textes in die Konsole.

1. Führen Sie Ihren Code aus. Stellen Sie sicher, dass Ihre Funktions-App läuft, und fordern Sie einen Timer in der Benutzersprache an, entweder indem Sie diese Sprache selbst sprechen oder eine Übersetzungs-App verwenden.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Aufgrund der unterschiedlichen Ausdrucksweisen in verschiedenen Sprachen können Sie Übersetzungen erhalten, die leicht von den Beispielen abweichen, die Sie LUIS gegeben haben. Wenn dies der Fall ist, fügen Sie LUIS weitere Beispiele hinzu, trainieren Sie das Modell erneut und veröffentlichen Sie es erneut.

> 💁 Sie finden diesen Code im Ordner [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Ihr mehrsprachiges Timer-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.