<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T20:57:15+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "da"
}
-->
# Tekst til tale - Raspberry Pi

I denne del af lektionen vil du skrive kode for at konvertere tekst til tale ved hjælp af tale-tjenesten.

## Konverter tekst til tale ved hjælp af tale-tjenesten

Teksten kan sendes til tale-tjenesten via REST API for at få tale som en lydfil, der kan afspilles på din IoT-enhed. Når du anmoder om tale, skal du angive den stemme, der skal bruges, da tale kan genereres med en række forskellige stemmer.

Hvert sprog understøtter en række forskellige stemmer, og du kan lave en REST-anmodning til tale-tjenesten for at få en liste over understøttede stemmer for hvert sprog.

### Opgave - få en stemme

1. Åbn `smart-timer`-projektet i VS Code.

1. Tilføj følgende kode over `say`-funktionen for at anmode om listen over stemmer for et sprog:

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

    Denne kode definerer en funktion kaldet `get_voice`, der bruger tale-tjenesten til at få en liste over stemmer. Den finder derefter den første stemme, der matcher det sprog, der bruges.

    Denne funktion kaldes derefter for at gemme den første stemme, og stemmens navn udskrives til konsollen. Denne stemme kan anmodes én gang, og værdien kan bruges til hver anmodning om at konvertere tekst til tale.

    > 💁 Du kan få den fulde liste over understøttede stemmer fra [Language and voice support documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Hvis du vil bruge en specifik stemme, kan du fjerne denne funktion og hardkode stemmen til stemmens navn fra denne dokumentation. For eksempel:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Opgave - konverter tekst til tale

1. Definér nedenfor en konstant for det lydformat, der skal hentes fra tale-tjenesterne. Når du anmoder om lyd, kan du gøre det i en række forskellige formater.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Det format, du kan bruge, afhænger af din hardware. Hvis du får fejl som `Invalid sample rate`, når du afspiller lyden, skal du ændre dette til en anden værdi. Du kan finde listen over understøttede værdier i [Text to speech REST API documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Du skal bruge lyd i `riff`-format, og de værdier, du kan prøve, er `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` og `riff-48khz-16bit-mono-pcm`.

1. Definér nedenfor en funktion kaldet `get_speech`, der vil konvertere tekst til tale ved hjælp af tale-tjenestens REST API:

    ```python
    def get_speech(text):
    ```

1. I `get_speech`-funktionen skal du definere URL'en, der skal kaldes, og de headers, der skal sendes:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Dette sætter headers til at bruge en genereret adgangstoken, angiver indholdet som SSML og definerer det nødvendige lydformat.

1. Definér nedenfor SSML, der skal sendes til REST API'et:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Denne SSML angiver sproget og stemmen, der skal bruges, sammen med teksten, der skal konverteres.

1. Til sidst skal du tilføje kode i denne funktion for at lave REST-anmodningen og returnere de binære lyddata:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Opgave - afspil lyden

1. Definér nedenfor `get_speech`-funktionen en ny funktion for at afspille lyden, der returneres fra REST API-anmodningen:

    ```python
    def play_speech(speech):
    ```

1. Den `speech`, der sendes til denne funktion, vil være de binære lyddata, der returneres fra REST API'et. Brug følgende kode til at åbne dette som en wave-fil og sende det til PyAudio for at afspille lyden:

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

    Denne kode bruger en PyAudio-stream, ligesom ved optagelse af lyd. Forskellen her er, at streamen er sat som en output-stream, og data læses fra lyddataene og sendes til streamen.

    I stedet for at hardkode stream-detaljer som sample rate, læses det fra lyddataene.

1. Erstat indholdet af `say`-funktionen med følgende:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Denne kode konverterer teksten til tale som binære lyddata og afspiller lyden.

1. Kør appen, og sørg for, at funktion-appen også kører. Sæt nogle timere, og du vil høre en talt besked, der siger, at din timer er sat, og derefter en anden talt besked, når timeren er færdig.

    Hvis du får fejl som `Invalid sample rate`, skal du ændre `playback_format` som beskrevet ovenfor.

> 💁 Du kan finde denne kode i [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi)-mappen.

😀 Dit timer-program var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.