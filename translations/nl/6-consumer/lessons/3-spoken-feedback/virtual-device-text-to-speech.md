<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T22:31:42+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "nl"
}
-->
# Tekst naar spraak - Virtueel IoT-apparaat

In dit deel van de les schrijf je code om tekst om te zetten in spraak met behulp van de spraakservice.

## Tekst omzetten naar spraak

De spraakservices SDK die je in de vorige les hebt gebruikt om spraak om te zetten naar tekst, kan ook worden gebruikt om tekst weer om te zetten naar spraak. Bij het aanvragen van spraak moet je de stem opgeven die gebruikt moet worden, aangezien spraak kan worden gegenereerd met verschillende stemmen.

Elke taal ondersteunt een reeks verschillende stemmen, en je kunt de lijst met ondersteunde stemmen voor elke taal ophalen via de spraakservices SDK.

### Taak - tekst omzetten naar spraak

1. Open het `smart-timer`-project in VS Code en zorg ervoor dat de virtuele omgeving is geladen in de terminal.

1. Importeer de `SpeechSynthesizer` uit het `azure.cognitiveservices.speech`-pakket door deze toe te voegen aan de bestaande imports:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Maak boven de `say`-functie een spraakconfiguratie aan om te gebruiken met de spraaksynthesizer:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Dit gebruikt dezelfde API-sleutel, locatie en taal die door de herkenner werd gebruikt.

1. Voeg hieronder de volgende code toe om een stem op te halen en deze in te stellen in de spraakconfiguratie:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Dit haalt een lijst op van alle beschikbare stemmen en vindt vervolgens de eerste stem die overeenkomt met de gebruikte taal.

    > 💁 Je kunt de volledige lijst met ondersteunde stemmen vinden in de [documentatie over taal- en stemondersteuning op Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Als je een specifieke stem wilt gebruiken, kun je deze functie verwijderen en de stemnaam uit deze documentatie hardcoderen. Bijvoorbeeld:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Werk de inhoud van de `say`-functie bij om SSML te genereren voor de reactie:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Stop hieronder de spraakherkenning, spreek de SSML uit en start vervolgens de herkenning opnieuw:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    De herkenning wordt gestopt terwijl de tekst wordt uitgesproken om te voorkomen dat de aankondiging van het starten van de timer wordt gedetecteerd, naar LUIS wordt gestuurd en mogelijk wordt geïnterpreteerd als een verzoek om een nieuwe timer in te stellen.

    > 💁 Je kunt dit testen door de regels om de herkenning te stoppen en opnieuw te starten uit te commentariëren. Stel een timer in, en je zult merken dat de aankondiging een nieuwe timer instelt, wat weer een nieuwe aankondiging veroorzaakt, wat leidt tot een nieuwe timer, en zo verder, eindeloos!

1. Voer de app uit en zorg ervoor dat de function app ook draait. Stel een paar timers in, en je hoort een gesproken reactie die zegt dat je timer is ingesteld, gevolgd door een andere gesproken reactie wanneer de timer is voltooid.

> 💁 Je kunt deze code vinden in de map [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Je timerprogramma was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.