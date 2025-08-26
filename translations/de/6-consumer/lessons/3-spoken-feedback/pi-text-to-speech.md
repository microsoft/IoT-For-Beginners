<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-25T22:37:46+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "de"
}
-->
# Text-to-Speech - Raspberry Pi

In diesem Teil der Lektion schreiben Sie Code, um Text mithilfe des Sprachdienstes in Sprache umzuwandeln.

## Text in Sprache umwandeln mit dem Sprachdienst

Der Text kann über die REST-API an den Sprachdienst gesendet werden, um eine Audiodatei zu erhalten, die auf Ihrem IoT-Gerät abgespielt werden kann. Beim Anfordern von Sprache müssen Sie die Stimme angeben, da Sprache mit einer Vielzahl unterschiedlicher Stimmen generiert werden kann.

Jede Sprache unterstützt eine Reihe verschiedener Stimmen, und Sie können eine REST-Anfrage an den Sprachdienst stellen, um die Liste der unterstützten Stimmen für jede Sprache zu erhalten.

### Aufgabe - Eine Stimme auswählen

1. Öffnen Sie das Projekt `smart-timer` in VS Code.

1. Fügen Sie den folgenden Code oberhalb der Funktion `say` ein, um die Liste der Stimmen für eine Sprache anzufordern:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    Dieser Code definiert eine Funktion namens `get_voice`, die den Sprachdienst verwendet, um eine Liste von Stimmen zu erhalten. Anschließend wird die erste Stimme gefunden, die der verwendeten Sprache entspricht.

    Diese Funktion wird dann aufgerufen, um die erste Stimme zu speichern, und der Name der Stimme wird in der Konsole ausgegeben. Diese Stimme kann einmal angefordert und der Wert für jeden Aufruf zur Umwandlung von Text in Sprache verwendet werden.

    > 💁 Sie können die vollständige Liste der unterstützten Stimmen in der [Dokumentation zur Sprach- und Stimmenunterstützung auf Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) einsehen. Wenn Sie eine bestimmte Stimme verwenden möchten, können Sie diese Funktion entfernen und die Stimme direkt mit dem Namen aus dieser Dokumentation festlegen. Zum Beispiel:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Aufgabe - Text in Sprache umwandeln

1. Definieren Sie darunter eine Konstante für das Audioformat, das vom Sprachdienst abgerufen werden soll. Wenn Sie Audio anfordern, können Sie dies in verschiedenen Formaten tun.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Das Format, das Sie verwenden können, hängt von Ihrer Hardware ab. Wenn Sie Fehler wie `Invalid sample rate` beim Abspielen des Audios erhalten, ändern Sie diesen Wert. Eine Liste der unterstützten Werte finden Sie in der [REST-API-Dokumentation für Text-to-Speech auf Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Sie müssen Audio im `riff`-Format verwenden, und die Werte, die Sie ausprobieren können, sind `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` und `riff-48khz-16bit-mono-pcm`.

1. Definieren Sie darunter eine Funktion namens `get_speech`, die den Text mithilfe der REST-API des Sprachdienstes in Sprache umwandelt:

    ```python
    def get_speech(text):
    ```

1. Definieren Sie in der Funktion `get_speech` die URL, die aufgerufen werden soll, und die Header, die übergeben werden müssen:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Hier werden die Header festgelegt, um ein generiertes Zugriffstoken zu verwenden, den Inhalt auf SSML zu setzen und das benötigte Audioformat zu definieren.

1. Definieren Sie darunter das SSML, das an die REST-API gesendet werden soll:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Dieses SSML legt die Sprache und die zu verwendende Stimme fest sowie den Text, der umgewandelt werden soll.

1. Fügen Sie schließlich in dieser Funktion Code hinzu, um die REST-Anfrage zu stellen und die binären Audiodaten zurückzugeben:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Aufgabe - Das Audio abspielen

1. Definieren Sie unterhalb der Funktion `get_speech` eine neue Funktion, um das von der REST-API zurückgegebene Audio abzuspielen:

    ```python
    def play_speech(speech):
    ```

1. Das an diese Funktion übergebene `speech` ist die von der REST-API zurückgegebene binäre Audiodatei. Verwenden Sie den folgenden Code, um diese als Wave-Datei zu öffnen und an PyAudio zu übergeben, um das Audio abzuspielen:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    Dieser Code verwendet einen PyAudio-Stream, ähnlich wie beim Aufnehmen von Audio. Der Unterschied besteht darin, dass der Stream hier als Ausgabestream festgelegt ist und Daten aus den Audiodaten gelesen und an den Stream übergeben werden.

    Anstatt die Stream-Details wie die Abtastrate fest zu codieren, werden diese aus den Audiodaten ausgelesen.

1. Ersetzen Sie den Inhalt der Funktion `say` durch Folgendes:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Dieser Code wandelt den Text in Sprache als binäre Audiodaten um und spielt das Audio ab.

1. Führen Sie die App aus und stellen Sie sicher, dass die Funktions-App ebenfalls läuft. Stellen Sie einige Timer ein, und Sie werden eine gesprochene Antwort hören, die sagt, dass Ihr Timer eingestellt wurde, und eine weitere gesprochene Antwort, wenn der Timer abgelaufen ist.

    Wenn Sie Fehler wie `Invalid sample rate` erhalten, ändern Sie das `playback_format` wie oben beschrieben.

> 💁 Sie finden diesen Code im Ordner [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Ihr Timer-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.