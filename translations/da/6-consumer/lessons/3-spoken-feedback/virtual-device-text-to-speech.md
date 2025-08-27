<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T20:52:47+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "da"
}
-->
# Tekst til tale - Virtuel IoT-enhed

I denne del af lektionen vil du skrive kode for at konvertere tekst til tale ved hjælp af tale-tjenesten.

## Konverter tekst til tale

SDK'en for tale-tjenester, som du brugte i den sidste lektion til at konvertere tale til tekst, kan også bruges til at konvertere tekst tilbage til tale. Når du anmoder om tale, skal du angive den stemme, der skal bruges, da tale kan genereres med en række forskellige stemmer.

Hvert sprog understøtter en række forskellige stemmer, og du kan få listen over understøttede stemmer for hvert sprog fra tale-tjenestens SDK.

### Opgave - konverter tekst til tale

1. Åbn `smart-timer`-projektet i VS Code, og sørg for, at det virtuelle miljø er indlæst i terminalen.

1. Importér `SpeechSynthesizer` fra pakken `azure.cognitiveservices.speech` ved at tilføje det til de eksisterende imports:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Over funktionen `say`, opret en tale-konfiguration til brug med tale-synthesizeren:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Dette bruger den samme API-nøgle, placering og sprog, som blev brugt af genkendelsesværktøjet.

1. Tilføj derefter følgende kode for at få en stemme og indstille den på tale-konfigurationen:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Dette henter en liste over alle tilgængelige stemmer og finder derefter den første stemme, der matcher det sprog, der bruges.

    > 💁 Du kan få den fulde liste over understøttede stemmer fra [Dokumentationen om sprog- og stemmeunderstøttelse på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Hvis du vil bruge en specifik stemme, kan du fjerne denne funktion og hardkode stemmen til stemmens navn fra denne dokumentation. For eksempel:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Opdater indholdet af funktionen `say` for at generere SSML til svaret:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Tilføj derefter kode til at stoppe talegenkendelsen, afspille SSML og derefter starte genkendelsen igen:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Genkendelsen stoppes, mens teksten afspilles, for at undgå, at meddelelsen om, at timeren starter, bliver opfanget, sendt til LUIS og muligvis fortolket som en anmodning om at indstille en ny timer.

    > 💁 Du kan teste dette ved at kommentere linjerne, der stopper og genstarter genkendelsen. Indstil én timer, og du vil måske opdage, at meddelelsen indstiller en ny timer, hvilket forårsager en ny meddelelse, der igen indstiller en ny timer, og så videre i det uendelige!

1. Kør appen, og sørg for, at funktionsappen også kører. Indstil nogle timere, og du vil høre en talt meddelelse, der siger, at din timer er blevet indstillet, og derefter en anden talt meddelelse, når timeren er færdig.

> 💁 Du kan finde denne kode i mappen [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Dit timer-program var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.