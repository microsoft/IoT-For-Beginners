<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-25T22:25:15+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "de"
}
-->
# Übersetze Sprache - Wio Terminal

In diesem Teil der Lektion schreiben Sie Code, um Text mithilfe des Übersetzungsdienstes zu übersetzen.

## Text in Sprache umwandeln mit dem Übersetzungsdienst

Die REST-API des Sprachdienstes unterstützt keine direkten Übersetzungen. Stattdessen können Sie den Übersetzungsdienst nutzen, um den Text zu übersetzen, der vom Sprach-zu-Text-Dienst generiert wurde, sowie den Text der gesprochenen Antwort. Dieser Dienst verfügt über eine REST-API, die Sie zur Übersetzung des Textes verwenden können. Um die Nutzung zu erleichtern, wird dies in einem weiteren HTTP-Trigger in Ihrer Functions-App eingebettet.

### Aufgabe - Erstellen Sie eine serverlose Funktion zur Textübersetzung

1. Öffnen Sie Ihr `smart-timer-trigger`-Projekt in VS Code und öffnen Sie das Terminal, wobei Sie sicherstellen, dass die virtuelle Umgebung aktiviert ist. Falls nicht, beenden und erstellen Sie das Terminal neu.

1. Öffnen Sie die Datei `local.settings.json` und fügen Sie Einstellungen für den API-Schlüssel und den Standort des Übersetzungsdienstes hinzu:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Ersetzen Sie `<key>` durch den API-Schlüssel Ihrer Übersetzungsdienst-Ressource. Ersetzen Sie `<location>` durch den Standort, den Sie bei der Erstellung der Übersetzungsdienst-Ressource verwendet haben.

1. Fügen Sie einen neuen HTTP-Trigger zu dieser App hinzu, der `translate-text` heißt, und verwenden Sie dazu den folgenden Befehl im VS Code-Terminal im Stammordner des Functions-App-Projekts:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Dadurch wird ein HTTP-Trigger namens `translate-text` erstellt.

1. Ersetzen Sie den Inhalt der Datei `__init__.py` im Ordner `translate-text` durch Folgendes:

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    Dieser Code extrahiert den Text und die Sprachen aus der HTTP-Anfrage. Anschließend wird eine Anfrage an die REST-API des Übersetzungsdienstes gestellt, wobei die Sprachen als Parameter für die URL und der zu übersetzende Text als Body übergeben werden. Schließlich wird die Übersetzung zurückgegeben.

1. Führen Sie Ihre Functions-App lokal aus. Sie können diese dann mit einem Tool wie curl auf die gleiche Weise testen, wie Sie Ihren `text-to-timer`-HTTP-Trigger getestet haben. Stellen Sie sicher, dass Sie den zu übersetzenden Text und die Sprachen als JSON-Body übergeben:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Dieses Beispiel übersetzt *Définir une minuterie de 30 secondes* von Französisch ins US-Englisch. Es wird *Set a 30-second timer* zurückgeben.

> 💁 Sie finden diesen Code im Ordner [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Aufgabe - Verwenden Sie die Übersetzungsfunktion zur Textübersetzung

1. Öffnen Sie das `smart-timer`-Projekt in VS Code, falls es noch nicht geöffnet ist.

1. Ihr Smart-Timer wird zwei Sprachen verwenden - die Sprache des Servers, die zum Trainieren von LUIS verwendet wurde (diese Sprache wird auch verwendet, um die Nachrichten zu erstellen, die dem Benutzer gesprochen werden), und die Sprache, die vom Benutzer gesprochen wird. Aktualisieren Sie die Konstante `LANGUAGE` in der Header-Datei `config.h`, sodass sie die Sprache darstellt, die vom Benutzer gesprochen wird, und fügen Sie eine neue Konstante namens `SERVER_LANGUAGE` für die Sprache hinzu, die zum Trainieren von LUIS verwendet wurde:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Ersetzen Sie `<user language>` durch den Gebietsschemanamen der Sprache, in der Sie sprechen werden, z. B. `fr-FR` für Französisch oder `zn-HK` für Kantonesisch.

    Ersetzen Sie `<server language>` durch den Gebietsschemanamen der Sprache, die zum Trainieren von LUIS verwendet wurde.

    Eine Liste der unterstützten Sprachen und ihrer Gebietsschemanamen finden Sie in der [Dokumentation zur Sprach- und Stimmenunterstützung auf Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Wenn Sie nicht mehrere Sprachen sprechen, können Sie einen Dienst wie [Bing Translate](https://www.bing.com/translator) oder [Google Translate](https://translate.google.com) verwenden, um von Ihrer bevorzugten Sprache in eine andere Sprache zu übersetzen. Diese Dienste können dann Audio des übersetzten Textes abspielen.
    >
    > Wenn Sie beispielsweise LUIS auf Englisch trainieren, aber Französisch als Benutzersprache verwenden möchten, können Sie Sätze wie "set a 2 minute and 27 second timer" von Englisch ins Französische mit Bing Translate übersetzen und dann die **Listen translation**-Schaltfläche verwenden, um die Übersetzung in Ihr Mikrofon zu sprechen.
    >
    > ![Die Listen translation-Schaltfläche auf Bing Translate](../../../../../translated_images/de/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Fügen Sie den API-Schlüssel und den Standort des Übersetzungsdienstes unterhalb von `SPEECH_LOCATION` hinzu:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Ersetzen Sie `<KEY>` durch den API-Schlüssel Ihrer Übersetzungsdienst-Ressource. Ersetzen Sie `<LOCATION>` durch den Standort, den Sie bei der Erstellung der Übersetzungsdienst-Ressource verwendet haben.

1. Fügen Sie die URL des Übersetzungs-Triggers unterhalb von `VOICE_URL` hinzu:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Ersetzen Sie `<URL>` durch die URL des `translate-text`-HTTP-Triggers Ihrer Functions-App. Diese wird denselben Wert wie `TEXT_TO_TIMER_FUNCTION_URL` haben, außer dass der Funktionsname `translate-text` anstelle von `text-to-timer` lautet.

1. Fügen Sie dem Ordner `src` eine neue Datei namens `text_translator.h` hinzu.

1. Diese neue Header-Datei `text_translator.h` wird eine Klasse zur Textübersetzung enthalten. Fügen Sie Folgendes zu dieser Datei hinzu, um diese Klasse zu deklarieren:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    Dies deklariert die Klasse `TextTranslator` sowie eine Instanz dieser Klasse. Die Klasse hat ein einziges Feld für den WiFi-Client.

1. Fügen Sie dem `public`-Abschnitt dieser Klasse eine Methode zur Textübersetzung hinzu:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Diese Methode nimmt die Sprache, aus der übersetzt werden soll, und die Sprache, in die übersetzt werden soll. Beim Umgang mit Sprache wird die Sprache des Benutzers in die LUIS-Server-Sprache übersetzt, und bei Antworten wird die LUIS-Server-Sprache in die Benutzersprache übersetzt.

1. Fügen Sie in dieser Methode Code hinzu, um einen JSON-Body zu erstellen, der den zu übersetzenden Text und die Sprachen enthält:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. Fügen Sie darunter den folgenden Code hinzu, um den Body an die serverlose Functions-App zu senden:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Fügen Sie anschließend Code hinzu, um die Antwort zu erhalten:

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Fügen Sie schließlich Code hinzu, um die Verbindung zu schließen und den übersetzten Text zurückzugeben:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Aufgabe - Übersetzen Sie die erkannte Sprache und die Antworten

1. Öffnen Sie die Datei `main.cpp`.

1. Fügen Sie am Anfang der Datei eine Include-Direktive für die Header-Datei der Klasse `TextTranslator` hinzu:

    ```cpp
    #include "text_translator.h"
    ```

1. Der Text, der gesagt wird, wenn ein Timer gesetzt oder abläuft, muss übersetzt werden. Fügen Sie dazu Folgendes als erste Zeile der Funktion `say` hinzu:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Dies wird den Text in die Benutzersprache übersetzen.

1. In der Funktion `processAudio` wird Text aus dem aufgenommenen Audio mit dem Aufruf `String text = speechToText.convertSpeechToText();` abgerufen. Übersetzen Sie den Text nach diesem Aufruf:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Dies wird den Text von der Benutzersprache in die Sprache übersetzen, die auf dem Server verwendet wird.

1. Bauen Sie diesen Code, laden Sie ihn auf Ihren Wio Terminal hoch und testen Sie ihn über den seriellen Monitor. Sobald Sie `Ready` im seriellen Monitor sehen, drücken Sie die C-Taste (die auf der linken Seite, am nächsten zum Netzschalter) und sprechen Sie. Stellen Sie sicher, dass Ihre Functions-App läuft, und fordern Sie einen Timer in der Benutzersprache an, entweder indem Sie selbst in dieser Sprache sprechen oder eine Übersetzungs-App verwenden.

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 Sie finden diesen Code im Ordner [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Ihr mehrsprachiges Timer-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.