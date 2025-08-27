<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T20:57:30+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "no"
}
-->
# Tekst til tale - Raspberry Pi

I denne delen av leksjonen skal du skrive kode for å konvertere tekst til tale ved hjelp av tale-tjenesten.

## Konverter tekst til tale ved hjelp av tale-tjenesten

Teksten kan sendes til tale-tjenesten via REST API for å få tale som en lydfil som kan spilles av på din IoT-enhet. Når du ber om tale, må du spesifisere stemmen som skal brukes, da tale kan genereres med en rekke forskjellige stemmer.

Hvert språk støtter et utvalg av ulike stemmer, og du kan gjøre en REST-forespørsel mot tale-tjenesten for å få en liste over støttede stemmer for hvert språk.

### Oppgave - få en stemme

1. Åpne `smart-timer`-prosjektet i VS Code.

1. Legg til følgende kode over `say`-funksjonen for å be om en liste over stemmer for et språk:

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

    Denne koden definerer en funksjon kalt `get_voice` som bruker tale-tjenesten for å hente en liste over stemmer. Den finner deretter den første stemmen som samsvarer med språket som brukes.

    Denne funksjonen kalles deretter for å lagre den første stemmen, og stemmens navn skrives ut til konsollen. Denne stemmen kan forespørres én gang, og verdien kan brukes for hver kall for å konvertere tekst til tale.

    > 💁 Du kan få den fullstendige listen over støttede stemmer fra [Language and voice support-dokumentasjonen på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Hvis du ønsker å bruke en spesifikk stemme, kan du fjerne denne funksjonen og hardkode stemmen til stemmens navn fra denne dokumentasjonen. For eksempel:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Oppgave - konverter tekst til tale

1. Under dette, definer en konstant for lydformatet som skal hentes fra tale-tjenesten. Når du ber om lyd, kan du gjøre det i en rekke forskjellige formater.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Formatet du kan bruke avhenger av maskinvaren din. Hvis du får feilmeldinger som `Invalid sample rate` når du spiller av lyden, endre dette til en annen verdi. Du kan finne listen over støttede verdier i [Text to speech REST API-dokumentasjonen på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Du må bruke lyd i `riff`-format, og verdiene du kan prøve er `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` og `riff-48khz-16bit-mono-pcm`.

1. Under dette, deklarer en funksjon kalt `get_speech` som vil konvertere tekst til tale ved hjelp av tale-tjenestens REST API:

    ```python
    def get_speech(text):
    ```

1. I `get_speech`-funksjonen, definer URL-en som skal kalles og headerne som skal sendes:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Dette setter headerne til å bruke en generert tilgangstoken, definerer innholdet som SSML og spesifiserer det nødvendige lydformatet.

1. Under dette, definer SSML som skal sendes til REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Denne SSML-en setter språket og stemmen som skal brukes, sammen med teksten som skal konverteres.

1. Til slutt, legg til kode i denne funksjonen for å gjøre REST-forespørselen og returnere den binære lyddataen:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Oppgave - spille av lyden

1. Under `get_speech`-funksjonen, definer en ny funksjon for å spille av lyden som returneres fra REST API-kallet:

    ```python
    def play_speech(speech):
    ```

1. `speech` som sendes til denne funksjonen vil være de binære lyddataene som returneres fra REST API. Bruk følgende kode for å åpne dette som en wave-fil og sende det til PyAudio for å spille av lyden:

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

    Denne koden bruker en PyAudio-strøm, på samme måte som ved opptak av lyd. Forskjellen her er at strømmen er satt som en utgangsstrøm, og data leses fra lyddataene og sendes til strømmen.

    I stedet for å hardkode strøm-detaljer som samplingsfrekvens, leses dette fra lyddataene.

1. Erstatt innholdet i `say`-funksjonen med følgende:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Denne koden konverterer tekst til tale som binære lyddata og spiller av lyden.

1. Kjør appen, og sørg for at funksjonsappen også kjører. Sett noen timere, og du vil høre en muntlig respons som sier at timeren din er satt, og deretter en annen muntlig respons når timeren er ferdig.

    Hvis du får feilmeldinger som `Invalid sample rate`, endre `playback_format` som beskrevet ovenfor.

> 💁 Du finner denne koden i [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi)-mappen.

😀 Timer-programmet ditt var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.