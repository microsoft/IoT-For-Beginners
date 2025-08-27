<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T20:52:33+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "sv"
}
-->
# Text till tal - Virtuell IoT-enhet

I den här delen av lektionen kommer du att skriva kod för att omvandla text till tal med hjälp av tal-tjänsten.

## Omvandla text till tal

SDK:n för tal-tjänster som du använde i förra lektionen för att omvandla tal till text kan också användas för att omvandla text tillbaka till tal. När du begär tal måste du ange vilken röst som ska användas, eftersom tal kan genereras med en mängd olika röster.

Varje språk stöder ett antal olika röster, och du kan få en lista över de röster som stöds för varje språk från SDK:n för tal-tjänster.

### Uppgift - omvandla text till tal

1. Öppna projektet `smart-timer` i VS Code och se till att den virtuella miljön är laddad i terminalen.

1. Importera `SpeechSynthesizer` från paketet `azure.cognitiveservices.speech` genom att lägga till det i de befintliga importerna:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Ovanför funktionen `say`, skapa en tal-konfiguration att använda med tal-syntetisatorn:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Detta använder samma API-nyckel, plats och språk som användes av igenkännaren.

1. Lägg till följande kod nedanför detta för att hämta en röst och ställa in den i tal-konfigurationen:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Detta hämtar en lista över alla tillgängliga röster och hittar sedan den första rösten som matchar det språk som används.

    > 💁 Du kan få hela listan över stödda röster från [dokumentationen om språk- och röststöd på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Om du vill använda en specifik röst kan du ta bort den här funktionen och hårdkoda rösten till röstnamnet från denna dokumentation. Till exempel:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Uppdatera innehållet i funktionen `say` för att generera SSML för svaret:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Nedanför detta, stoppa taligenkänningen, spela upp SSML, och starta sedan igenkänningen igen:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Igenkänningen stoppas medan texten läses upp för att undvika att meddelandet om att timern startar upptäcks, skickas till LUIS och eventuellt tolkas som en begäran om att ställa in en ny timer.

    > 💁 Du kan testa detta genom att kommentera bort raderna som stoppar och startar igenkänningen. Ställ in en timer, och du kan märka att meddelandet ställer in en ny timer, vilket orsakar ett nytt meddelande, som leder till en ny timer, och så vidare i all oändlighet!

1. Kör appen och se till att funktionsappen också körs. Ställ in några timers, och du kommer att höra ett talat svar som säger att din timer har ställts in, följt av ett annat talat svar när timern är klar.

> 💁 Du kan hitta denna kod i mappen [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Ditt timerprogram blev en succé!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.