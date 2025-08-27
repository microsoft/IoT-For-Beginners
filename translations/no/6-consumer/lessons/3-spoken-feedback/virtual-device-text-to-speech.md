<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T20:52:58+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "no"
}
-->
# Tekst til tale - Virtuell IoT-enhet

I denne delen av leksjonen skal du skrive kode for å konvertere tekst til tale ved hjelp av tale-tjenesten.

## Konverter tekst til tale

SDK-en for tale-tjenester som du brukte i forrige leksjon for å konvertere tale til tekst, kan også brukes til å konvertere tekst tilbake til tale. Når du ber om tale, må du spesifisere stemmen som skal brukes, ettersom tale kan genereres med en rekke forskjellige stemmer.

Hvert språk støtter et utvalg av ulike stemmer, og du kan få en liste over støttede stemmer for hvert språk fra tale-tjenestens SDK.

### Oppgave - konverter tekst til tale

1. Åpne `smart-timer`-prosjektet i VS Code, og sørg for at det virtuelle miljøet er lastet inn i terminalen.

1. Importer `SpeechSynthesizer` fra pakken `azure.cognitiveservices.speech` ved å legge det til de eksisterende importene:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Over `say`-funksjonen, opprett en tale-konfigurasjon som skal brukes med tale-syntetisatoren:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Dette bruker samme API-nøkkel, lokasjon og språk som ble brukt av gjenkjenneren.

1. Under dette, legg til følgende kode for å hente en stemme og sette den på tale-konfigurasjonen:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Dette henter en liste over alle tilgjengelige stemmer, og finner deretter den første stemmen som samsvarer med språket som brukes.

    > 💁 Du kan få den fullstendige listen over støttede stemmer fra [dokumentasjonen for språk- og stemmestøtte på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Hvis du ønsker å bruke en spesifikk stemme, kan du fjerne denne funksjonen og hardkode stemmen til stemmens navn fra denne dokumentasjonen. For eksempel:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Oppdater innholdet i `say`-funksjonen for å generere SSML for responsen:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Under dette, stopp talegjenkjenningen, les opp SSML, og start deretter gjenkjenningen igjen:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Gjenkjenningen stoppes mens teksten leses opp for å unngå at kunngjøringen om at timeren starter blir oppfattet, sendt til LUIS og muligens tolket som en forespørsel om å sette en ny timer.

    > 💁 Du kan teste dette ved å kommentere ut linjene som stopper og starter gjenkjenningen. Sett én timer, og du kan oppleve at kunngjøringen setter en ny timer, som fører til en ny kunngjøring, som igjen setter en ny timer, og så videre i det uendelige!

1. Kjør appen, og sørg for at funksjonsappen også kjører. Sett noen timere, og du vil høre en muntlig respons som sier at timeren din er satt, og deretter en ny muntlig respons når timeren er ferdig.

> 💁 Du finner denne koden i [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device)-mappen.

😀 Timer-programmet ditt var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.