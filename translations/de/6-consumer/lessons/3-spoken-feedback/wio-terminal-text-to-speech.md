<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-25T22:38:53+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "de"
}
-->
# Text-zu-Sprache - Wio Terminal

In diesem Teil der Lektion werden Sie Text in Sprache umwandeln, um gesprochene Rückmeldungen zu geben.

## Text-zu-Sprache

Das Speech Services SDK, das Sie in der letzten Lektion verwendet haben, um Sprache in Text umzuwandeln, kann auch verwendet werden, um Text wieder in Sprache umzuwandeln.

## Liste der Stimmen abrufen

Beim Anfordern von Sprache müssen Sie die Stimme angeben, die verwendet werden soll, da Sprache mit einer Vielzahl unterschiedlicher Stimmen generiert werden kann. Jede Sprache unterstützt eine Reihe verschiedener Stimmen, und Sie können die Liste der unterstützten Stimmen für jede Sprache aus dem Speech Services SDK abrufen. Hier kommen die Einschränkungen von Mikrocontrollern ins Spiel – der Aufruf, um die Liste der von den Text-zu-Sprache-Diensten unterstützten Stimmen zu erhalten, ist ein JSON-Dokument von über 77 KB Größe, viel zu groß, um vom Wio Terminal verarbeitet zu werden. Zum Zeitpunkt des Schreibens enthält die vollständige Liste 215 Stimmen, die jeweils durch ein JSON-Dokument wie das folgende definiert sind:

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

Dieses JSON ist für die **Aria**-Stimme, die mehrere Sprachstile hat. Alles, was benötigt wird, um Text in Sprache umzuwandeln, ist der Kurzname, `en-US-AriaNeural`.

Anstatt diese gesamte Liste auf Ihrem Mikrocontroller herunterzuladen und zu dekodieren, müssen Sie etwas mehr serverlose Code schreiben, um die Liste der Stimmen für die Sprache, die Sie verwenden, abzurufen und diese von Ihrem Wio Terminal aus aufzurufen. Ihr Code kann dann eine geeignete Stimme aus der Liste auswählen, z. B. die erste, die er findet.

### Aufgabe - Erstellen Sie eine serverlose Funktion, um eine Liste von Stimmen abzurufen

1. Öffnen Sie Ihr `smart-timer-trigger`-Projekt in VS Code und öffnen Sie das Terminal, wobei Sie sicherstellen, dass die virtuelle Umgebung aktiviert ist. Falls nicht, beenden und erstellen Sie das Terminal neu.

1. Öffnen Sie die Datei `local.settings.json` und fügen Sie Einstellungen für den Speech API-Schlüssel und den Standort hinzu:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Ersetzen Sie `<key>` durch den API-Schlüssel für Ihre Speech Service-Ressource. Ersetzen Sie `<location>` durch den Standort, den Sie bei der Erstellung der Speech Service-Ressource verwendet haben.

1. Fügen Sie diesem App-Projekt einen neuen HTTP-Trigger namens `get-voices` hinzu, indem Sie den folgenden Befehl im VS Code-Terminal im Stammordner des Functions-App-Projekts ausführen:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Dadurch wird ein HTTP-Trigger namens `get-voices` erstellt.

1. Ersetzen Sie den Inhalt der Datei `__init__.py` im Ordner `get-voices` durch Folgendes:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    Dieser Code führt eine HTTP-Anfrage an den Endpunkt aus, um die Stimmen abzurufen. Diese Stimmenliste ist ein großer Block von JSON mit Stimmen für alle Sprachen, sodass die Stimmen für die Sprache, die im Anfragekörper übergeben wird, herausgefiltert werden, dann wird der Kurzname extrahiert und als JSON-Liste zurückgegeben. Der Kurzname ist der Wert, der benötigt wird, um Text in Sprache umzuwandeln, daher wird nur dieser Wert zurückgegeben.

    > 💁 Sie können den Filter nach Bedarf ändern, um nur die Stimmen auszuwählen, die Sie möchten.

    Dies reduziert die Größe der Daten von 77 KB (zum Zeitpunkt des Schreibens) auf ein viel kleineres JSON-Dokument. Zum Beispiel beträgt dies für US-Stimmen 408 Bytes.

1. Führen Sie Ihre Functions-App lokal aus. Sie können dies dann mit einem Tool wie curl auf die gleiche Weise testen, wie Sie Ihren `text-to-timer`-HTTP-Trigger getestet haben. Stellen Sie sicher, dass Sie Ihre Sprache als JSON-Körper übergeben:

    ```json
    {
        "language":"<language>"
    }
    ```

    Ersetzen Sie `<language>` durch Ihre Sprache, z. B. `en-GB` oder `zh-CN`.

> 💁 Sie finden diesen Code im Ordner [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Aufgabe - Abrufen der Stimme von Ihrem Wio Terminal

1. Öffnen Sie das `smart-timer`-Projekt in VS Code, falls es noch nicht geöffnet ist.

1. Öffnen Sie die Header-Datei `config.h` und fügen Sie die URL für Ihre Functions-App hinzu:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Ersetzen Sie `<URL>` durch die URL für den `get-voices`-HTTP-Trigger Ihrer Functions-App. Dies wird derselbe Wert wie `TEXT_TO_TIMER_FUNCTION_URL` sein, außer mit einem Funktionsnamen von `get-voices` anstelle von `text-to-timer`.

1. Erstellen Sie eine neue Datei im Ordner `src` namens `text_to_speech.h`. Diese wird verwendet, um eine Klasse zu definieren, die von Text zu Sprache konvertiert.

1. Fügen Sie die folgenden Include-Direktiven oben in die neue Datei `text_to_speech.h` ein:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. Fügen Sie den folgenden Code darunter ein, um die `TextToSpeech`-Klasse zu deklarieren, zusammen mit einer Instanz, die im Rest der Anwendung verwendet werden kann:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Um Ihre Functions-App aufzurufen, müssen Sie einen WiFi-Client deklarieren. Fügen Sie Folgendes zum Abschnitt `private` der Klasse hinzu:

    ```cpp
    WiFiClient _client;
    ```

1. Fügen Sie im Abschnitt `private` ein Feld für die ausgewählte Stimme hinzu:

    ```cpp
    String _voice;
    ```

1. Fügen Sie dem Abschnitt `public` eine `init`-Funktion hinzu, die die erste Stimme abruft:

    ```cpp
    void init()
    {
    }
    ```

1. Um die Stimmen abzurufen, muss ein JSON-Dokument an die Functions-App mit der Sprache gesendet werden. Fügen Sie den folgenden Code zur `init`-Funktion hinzu, um dieses JSON-Dokument zu erstellen:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Erstellen Sie anschließend einen `HTTPClient` und verwenden Sie ihn, um die Functions-App aufzurufen, um die Stimmen abzurufen, indem Sie das JSON-Dokument posten:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Fügen Sie darunter Code hinzu, um den Antwortcode zu überprüfen, und wenn er 200 (Erfolg) ist, dann die Liste der Stimmen zu extrahieren und die erste aus der Liste abzurufen:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Beenden Sie danach die HTTP-Client-Verbindung:

    ```cpp
    httpClient.end();
    ```

1. Öffnen Sie die Datei `main.cpp` und fügen Sie die folgende Include-Direktive oben ein, um diese neue Header-Datei einzubinden:

    ```cpp
    #include "text_to_speech.h"
    ```

1. Fügen Sie in der `setup`-Funktion unterhalb des Aufrufs von `speechToText.init();` Folgendes hinzu, um die `TextToSpeech`-Klasse zu initialisieren:

    ```cpp
    textToSpeech.init();
    ```

1. Bauen Sie diesen Code, laden Sie ihn auf Ihr Wio Terminal hoch und testen Sie ihn über den seriellen Monitor. Stellen Sie sicher, dass Ihre Functions-App läuft.

    Sie werden die Liste der verfügbaren Stimmen sehen, die von der Functions-App zurückgegeben wird, zusammen mit der ausgewählten Stimme.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## Text in Sprache umwandeln

Sobald Sie eine Stimme haben, die verwendet werden kann, kann sie verwendet werden, um Text in Sprache umzuwandeln. Die gleichen Speicherbeschränkungen bei Stimmen gelten auch beim Umwandeln von Sprache in Text, daher müssen Sie die Sprache auf einer SD-Karte speichern, um sie über den ReSpeaker abzuspielen.

> 💁 In früheren Lektionen in diesem Projekt haben Sie Flash-Speicher verwendet, um Sprache zu speichern, die vom Mikrofon aufgenommen wurde. Diese Lektion verwendet eine SD-Karte, da es einfacher ist, Audio von ihr mit den Seeed-Audio-Bibliotheken abzuspielen.

Es gibt auch eine weitere Einschränkung zu beachten: die verfügbaren Audiodaten vom Speech Service und die Formate, die das Wio Terminal unterstützt. Im Gegensatz zu vollständigen Computern können Audiobibliotheken für Mikrocontroller sehr begrenzt sein, was die unterstützten Audioformate betrifft. Beispielsweise unterstützt die Seeed Arduino Audio-Bibliothek, die Sound über den ReSpeaker abspielen kann, nur Audio mit einer Abtastrate von 44,1 kHz. Die Azure Speech Services können Audio in einer Reihe von Formaten bereitstellen, aber keines davon verwendet diese Abtastrate, sie bieten nur 8 kHz, 16 kHz, 24 kHz und 48 kHz. Das bedeutet, dass das Audio auf 44,1 kHz umgesampelt werden muss, was mehr Ressourcen erfordern würde, als das Wio Terminal hat, insbesondere Speicher.

Wenn Daten wie diese manipuliert werden müssen, ist es oft besser, serverlosen Code zu verwenden, insbesondere wenn die Daten über einen Webaufruf bezogen werden. Das Wio Terminal kann eine serverlose Funktion aufrufen, den zu konvertierenden Text übergeben, und die serverlose Funktion kann sowohl den Speech Service aufrufen, um Text in Sprache umzuwandeln, als auch das Audio auf die erforderliche Abtastrate umsamplen. Es kann dann das Audio in der Form zurückgeben, die das Wio Terminal benötigt, um auf der SD-Karte gespeichert und über den ReSpeaker abgespielt zu werden.

### Aufgabe - Erstellen Sie eine serverlose Funktion, um Text in Sprache umzuwandeln

1. Öffnen Sie Ihr `smart-timer-trigger`-Projekt in VS Code und öffnen Sie das Terminal, wobei Sie sicherstellen, dass die virtuelle Umgebung aktiviert ist. Falls nicht, beenden und erstellen Sie das Terminal neu.

1. Fügen Sie diesem App-Projekt einen neuen HTTP-Trigger namens `text-to-speech` hinzu, indem Sie den folgenden Befehl im VS Code-Terminal im Stammordner des Functions-App-Projekts ausführen:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Dadurch wird ein HTTP-Trigger namens `text-to-speech` erstellt.

1. Das [librosa](https://librosa.org)-Pip-Paket hat Funktionen zum Umsampeln von Audio, daher fügen Sie dies der Datei `requirements.txt` hinzu:

    ```sh
    librosa
    ```

    Sobald dies hinzugefügt wurde, installieren Sie die Pip-Pakete mit dem folgenden Befehl aus dem VS Code-Terminal:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Wenn Sie Linux verwenden, einschließlich Raspberry Pi OS, müssen Sie möglicherweise `libsndfile` mit dem folgenden Befehl installieren:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Um Text in Sprache umzuwandeln, können Sie den Speech API-Schlüssel nicht direkt verwenden, sondern müssen stattdessen ein Zugriffstoken anfordern, wobei der API-Schlüssel zur Authentifizierung der Zugriffstoken-Anfrage verwendet wird. Öffnen Sie die Datei `__init__.py` aus dem Ordner `text-to-speech` und ersetzen Sie den gesamten Code darin durch Folgendes:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Dies definiert Konstanten für den Standort und den Speech-Schlüssel, die aus den Einstellungen gelesen werden. Es definiert dann die Funktion `get_access_token`, die ein Zugriffstoken für den Speech Service abruft.

1. Fügen Sie unter diesem Code Folgendes hinzu:

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    Dies definiert den HTTP-Trigger, der den Text in Sprache umwandelt. Es extrahiert den zu konvertierenden Text, die Sprache und die Stimme aus dem JSON-Körper, der an die Anfrage gesendet wird, erstellt etwas SSML, um die Sprache anzufordern, und ruft dann die entsprechende REST-API auf, wobei das Zugriffstoken zur Authentifizierung verwendet wird. Dieser REST-API-Aufruf gibt das Audio als 16-Bit, 48 kHz Mono-WAV-Datei zurück, definiert durch den Wert von `playback_format`, der an den REST-API-Aufruf gesendet wird.

    Dies wird dann von `librosa` von einer Abtastrate von 48 kHz auf eine Abtastrate von 44,1 kHz umgesampelt, dann wird dieses Audio in einem binären Puffer gespeichert, der dann zurückgegeben wird.

1. Führen Sie Ihre Functions-App lokal aus oder stellen Sie sie in der Cloud bereit. Sie können dies dann mit einem Tool wie curl auf die gleiche Weise testen, wie Sie Ihren `text-to-timer`-HTTP-Trigger getestet haben. Stellen Sie sicher, dass Sie die Sprache, Stimme und den Text als JSON-Körper übergeben:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Ersetzen Sie `<language>` durch Ihre Sprache, z. B. `en-GB` oder `zh-CN`. Ersetzen Sie `<voice>` durch die Stimme, die Sie verwenden möchten. Ersetzen Sie `<text>` durch den Text, den Sie in Sprache umwandeln möchten. Sie können die Ausgabe in einer Datei speichern und mit jedem Audioplayer abspielen, der WAV-Dateien abspielen kann.

    Zum Beispiel, um "Hello" in Sprache umzuwandeln, mit US-Englisch und der Jenny Neural-Stimme, während die Functions-App lokal läuft, können Sie den folgenden curl-Befehl verwenden:

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    Dies speichert das Audio in `hello.wav` im aktuellen Verzeichnis.

> 💁 Sie finden diesen Code im Ordner [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Aufgabe - Abrufen der Sprache von Ihrem Wio Terminal

1. Öffnen Sie das `smart-timer`-Projekt in VS Code, falls es noch nicht geöffnet ist.

1. Öffnen Sie die Header-Datei `config.h` und fügen Sie die URL für Ihre Functions-App hinzu:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Ersetzen Sie `<URL>` durch die URL für den `text-to-speech`-HTTP-Trigger Ihrer Functions-App. Dies wird derselbe Wert wie `TEXT_TO_TIMER_FUNCTION_URL` sein, außer mit einem Funktionsnamen von `text-to-speech` anstelle von `text-to-timer`.

1. Öffnen Sie die Header-Datei `text_to_speech.h` und fügen Sie die folgende Methode zum Abschnitt `public` der `TextToSpeech`-Klasse hinzu:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Fügen Sie der Methode `convertTextToSpeech` den folgenden Code hinzu, um das JSON zu erstellen, das an die Functions-App gesendet werden soll:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Dies schreibt die Sprache, Stimme und den Text in das JSON-Dokument und serialisiert es dann zu einem String.

1. Fügen Sie darunter den folgenden Code hinzu, um die Functions-App aufzurufen:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Dies erstellt einen HTTPClient und führt eine POST-Anfrage mit dem JSON-Dokument an den Text-zu-Sprache-HTTP-Trigger aus.

1. Wenn der Aufruf funktioniert, können die rohen Binärdaten, die von der Functions-App zurückgegeben werden, in eine Datei auf der SD-Karte gestreamt werden. Fügen Sie den folgenden Code hinzu, um dies zu tun:

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Dieser Code überprüft die Antwort, und wenn sie 200 (Erfolg) ist, werden die Binärdaten in eine Datei im Stammverzeichnis der SD-Karte namens `SPEECH.WAV` gestreamt.

1. Schließen Sie am Ende dieser Methode die HTTP-Verbindung:

    ```cpp
    httpClient.end();
    ```

1. Der zu sprechende Text kann jetzt in Audio umgewandelt werden. Fügen Sie in der Datei `main.cpp` die folgende Zeile am Ende der Funktion `say` hinzu, um den zu sprechenden Text in Audio umzuwandeln:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Aufgabe - Audio von deinem Wio Terminal abspielen

**Demnächst verfügbar**

## Deine Functions-App in die Cloud bereitstellen

Der Grund, warum die Functions-App lokal ausgeführt wird, liegt darin, dass das `librosa`-Pip-Paket unter Linux von einer Bibliothek abhängt, die standardmäßig nicht installiert ist und vor dem Ausführen der Functions-App installiert werden muss. Functions-Apps sind serverlos – es gibt keine Server, die du selbst verwalten kannst, und somit keine Möglichkeit, diese Bibliothek im Voraus zu installieren.

Stattdessen wird die Functions-App mithilfe eines Docker-Containers bereitgestellt. Dieser Container wird von der Cloud bereitgestellt, wann immer eine neue Instanz deiner Functions-App gestartet werden muss (zum Beispiel, wenn die Nachfrage die verfügbaren Ressourcen übersteigt oder wenn die Functions-App längere Zeit nicht genutzt wurde und heruntergefahren wurde).

Die Anweisungen zum Einrichten einer Functions-App und zur Bereitstellung über Docker findest du in der [Dokumentation zum Erstellen einer Funktion auf Linux mit einem benutzerdefinierten Container auf Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Sobald dies bereitgestellt wurde, kannst du deinen Wio Terminal-Code anpassen, um auf diese Funktion zuzugreifen:

1. Füge das Azure Functions-Zertifikat zu `config.h` hinzu:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Ändere alle Includes von `<WiFiClient.h>` zu `<WiFiClientSecure.h>`.

1. Ändere alle `WiFiClient`-Felder zu `WiFiClientSecure`.

1. Füge in jeder Klasse, die ein `WiFiClientSecure`-Feld hat, einen Konstruktor hinzu und setze das Zertifikat in diesem Konstruktor:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.