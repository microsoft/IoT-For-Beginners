<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T22:27:45+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "nl"
}
-->
# Tekst naar spraak - Raspberry Pi

In dit deel van de les schrijf je code om tekst om te zetten naar spraak met behulp van de spraakservice.

## Tekst omzetten naar spraak met behulp van de spraakservice

De tekst kan naar de spraakservice worden gestuurd via de REST API om spraak te verkrijgen als een audiobestand dat kan worden afgespeeld op je IoT-apparaat. Bij het aanvragen van spraak moet je de stem opgeven die gebruikt moet worden, aangezien spraak kan worden gegenereerd met verschillende stemmen.

Elke taal ondersteunt een reeks verschillende stemmen, en je kunt een REST-verzoek sturen naar de spraakservice om de lijst met ondersteunde stemmen voor elke taal op te halen.

### Taak - een stem ophalen

1. Open het `smart-timer`-project in VS Code.

1. Voeg de volgende code toe boven de `say`-functie om de lijst met stemmen voor een taal op te vragen:

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

    Deze code definieert een functie genaamd `get_voice` die de spraakservice gebruikt om een lijst met stemmen op te halen. Vervolgens wordt de eerste stem gevonden die overeenkomt met de gebruikte taal.

    Deze functie wordt vervolgens aangeroepen om de eerste stem op te slaan, en de naam van de stem wordt afgedrukt in de console. Deze stem kan één keer worden opgevraagd en de waarde kan worden gebruikt voor elke oproep om tekst om te zetten naar spraak.

    > 💁 Je kunt de volledige lijst met ondersteunde stemmen vinden in de [documentatie over taal- en stemondersteuning op Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Als je een specifieke stem wilt gebruiken, kun je deze functie verwijderen en de stemnaam hard coderen op basis van de documentatie. Bijvoorbeeld:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Taak - tekst omzetten naar spraak

1. Definieer hieronder een constante voor het audioformaat dat moet worden opgehaald van de spraakservice. Wanneer je audio aanvraagt, kun je dit doen in verschillende formaten.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Het formaat dat je kunt gebruiken, hangt af van je hardware. Als je fouten krijgt zoals `Invalid sample rate` bij het afspelen van de audio, wijzig dit dan naar een andere waarde. Je kunt de lijst met ondersteunde waarden vinden in de [REST API-documentatie voor tekst naar spraak op Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Je moet gebruik maken van audio in het `riff`-formaat, en de waarden die je kunt proberen zijn `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` en `riff-48khz-16bit-mono-pcm`.

1. Declareer hieronder een functie genaamd `get_speech` die tekst omzet naar spraak met behulp van de REST API van de spraakservice:

    ```python
    def get_speech(text):
    ```

1. Definieer in de `get_speech`-functie de URL die moet worden aangeroepen en de headers die moeten worden meegegeven:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Hiermee worden de headers ingesteld om een gegenereerde toegangstoken te gebruiken, de inhoud in SSML te zetten en het benodigde audioformaat te definiëren.

1. Definieer hieronder de SSML die naar de REST API moet worden gestuurd:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Deze SSML stelt de taal en de stem in die moet worden gebruikt, samen met de tekst die moet worden omgezet.

1. Voeg tot slot code toe in deze functie om het REST-verzoek uit te voeren en de binaire audiodata terug te geven:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Taak - de audio afspelen

1. Definieer onder de `get_speech`-functie een nieuwe functie om de audio af te spelen die is geretourneerd door de REST API-aanroep:

    ```python
    def play_speech(speech):
    ```

1. De `speech` die aan deze functie wordt doorgegeven, is de binaire audiodata die is geretourneerd door de REST API. Gebruik de volgende code om dit te openen als een wave-bestand en door te geven aan PyAudio om de audio af te spelen:

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

    Deze code gebruikt een PyAudio-stream, net zoals bij het opnemen van audio. Het verschil hier is dat de stream is ingesteld als een uitvoerstream, en data wordt gelezen uit de audiodata en naar de stream gestuurd.

    In plaats van de streamdetails zoals de samplefrequentie hard te coderen, worden deze gelezen uit de audiodata.

1. Vervang de inhoud van de `say`-functie door het volgende:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Deze code zet de tekst om naar spraak als binaire audiodata en speelt de audio af.

1. Voer de app uit en zorg ervoor dat de functie-app ook draait. Stel enkele timers in, en je hoort een gesproken reactie die zegt dat je timer is ingesteld, gevolgd door een andere gesproken reactie wanneer de timer voltooid is.

    Als je fouten krijgt zoals `Invalid sample rate`, wijzig dan de `playback_format` zoals hierboven beschreven.

> 💁 Je kunt deze code vinden in de map [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Je timerprogramma is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.