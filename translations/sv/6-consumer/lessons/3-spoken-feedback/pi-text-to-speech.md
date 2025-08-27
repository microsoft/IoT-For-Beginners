<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T20:56:59+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "sv"
}
-->
# Text till tal - Raspberry Pi

I den här delen av lektionen kommer du att skriva kod för att konvertera text till tal med hjälp av tal-tjänsten.

## Konvertera text till tal med hjälp av tal-tjänsten

Texten kan skickas till tal-tjänsten via REST API för att få tal som en ljudfil som kan spelas upp på din IoT-enhet. När du begär tal måste du ange vilken röst som ska användas, eftersom tal kan genereras med en mängd olika röster.

Varje språk stöder ett antal olika röster, och du kan göra en REST-förfrågan till tal-tjänsten för att få en lista över de röster som stöds för varje språk.

### Uppgift - hämta en röst

1. Öppna projektet `smart-timer` i VS Code.

1. Lägg till följande kod ovanför funktionen `say` för att begära en lista över röster för ett språk:

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

    Den här koden definierar en funktion som heter `get_voice` som använder tal-tjänsten för att hämta en lista över röster. Den hittar sedan den första rösten som matchar det språk som används.

    Den här funktionen anropas sedan för att lagra den första rösten, och röstnamnet skrivs ut i konsolen. Den här rösten kan begäras en gång och värdet kan användas för varje anrop för att konvertera text till tal.

    > 💁 Du kan få hela listan över stödda röster från [dokumentationen om språk- och röststöd på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Om du vill använda en specifik röst kan du ta bort den här funktionen och hårdkoda rösten till röstnamnet från denna dokumentation. Till exempel:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Uppgift - konvertera text till tal

1. Nedanför detta, definiera en konstant för ljudformatet som ska hämtas från tal-tjänsten. När du begär ljud kan du göra det i olika format.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Formatet du kan använda beror på din hårdvara. Om du får felmeddelandet `Invalid sample rate` när du spelar upp ljudet, ändra detta till ett annat värde. Du kan hitta listan över stödda värden i [REST API-dokumentationen för text till tal på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Du måste använda ljud i `riff`-format, och värdena att testa är `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` och `riff-48khz-16bit-mono-pcm`.

1. Nedanför detta, deklarera en funktion som heter `get_speech` som kommer att konvertera text till tal med hjälp av tal-tjänstens REST API:

    ```python
    def get_speech(text):
    ```

1. I funktionen `get_speech`, definiera URL:en som ska anropas och headers som ska skickas:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Detta ställer in headers för att använda en genererad åtkomsttoken, anger innehållet som SSML och definierar det ljudformat som behövs.

1. Nedanför detta, definiera SSML som ska skickas till REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Denna SSML anger språket och rösten som ska användas, tillsammans med texten som ska konverteras.

1. Slutligen, lägg till kod i denna funktion för att göra REST-förfrågan och returnera den binära ljuddatan:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Uppgift - spela upp ljudet

1. Nedanför funktionen `get_speech`, definiera en ny funktion för att spela upp ljudet som returneras av REST API-anropet:

    ```python
    def play_speech(speech):
    ```

1. `speech` som skickas till denna funktion kommer att vara den binära ljuddatan som returneras från REST API. Använd följande kod för att öppna detta som en wave-fil och skicka det till PyAudio för att spela upp ljudet:

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

    Den här koden använder en PyAudio-ström, precis som vid inspelning av ljud. Skillnaden här är att strömmen är inställd som en utström, och data läses från ljuddatan och skickas till strömmen.

    Istället för att hårdkoda strömdetaljer som samplingsfrekvens, läses detta från ljuddatan.

1. Ersätt innehållet i funktionen `say` med följande:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Den här koden konverterar text till tal som binär ljuddata och spelar upp ljudet.

1. Kör appen och se till att funktionsappen också körs. Ställ in några timers, och du kommer att höra ett talat svar som säger att din timer har ställts in, och sedan ett annat talat svar när timern är klar.

    Om du får felmeddelandet `Invalid sample rate`, ändra `playback_format` enligt beskrivningen ovan.

> 💁 Du kan hitta denna kod i mappen [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Ditt timerprogram blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.