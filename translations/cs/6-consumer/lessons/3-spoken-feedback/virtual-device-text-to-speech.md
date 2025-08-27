<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T21:08:21+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "cs"
}
-->
# Text na řeč - Virtuální IoT zařízení

V této části lekce napíšete kód pro převod textu na řeč pomocí služby pro rozpoznávání řeči.

## Převod textu na řeč

SDK služby pro rozpoznávání řeči, kterou jste použili v předchozí lekci k převodu řeči na text, lze použít i k převodu textu zpět na řeč. Při požadavku na řeč je potřeba zadat hlas, který se má použít, protože řeč může být generována pomocí různých hlasů.

Každý jazyk podporuje řadu různých hlasů a seznam podporovaných hlasů pro každý jazyk můžete získat ze SDK služby pro rozpoznávání řeči.

### Úkol - převod textu na řeč

1. Otevřete projekt `smart-timer` ve VS Code a ujistěte se, že je v terminálu načten virtuální prostředí.

1. Importujte `SpeechSynthesizer` z balíčku `azure.cognitiveservices.speech` přidáním do stávajících importů:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Nad funkcí `say` vytvořte konfiguraci řeči, kterou použijete s nástrojem pro syntézu řeči:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Tato konfigurace používá stejný API klíč, umístění a jazyk, které byly použity rozpoznávačem.

1. Pod tímto kódem přidejte následující kód pro získání hlasu a jeho nastavení v konfiguraci řeči:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Tento kód získá seznam všech dostupných hlasů a poté najde první hlas, který odpovídá používanému jazyku.

    > 💁 Kompletní seznam podporovaných hlasů můžete získat z [dokumentace o podpoře jazyků a hlasů na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Pokud chcete použít konkrétní hlas, můžete tuto funkci odstranit a pevně nastavit hlas na název hlasu z této dokumentace. Například:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Aktualizujte obsah funkce `say` tak, aby generovala SSML pro odpověď:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Pod tímto kódem zastavte rozpoznávání řeči, přehrajte SSML a poté znovu spusťte rozpoznávání:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Rozpoznávání je zastaveno během přehrávání textu, aby se zabránilo tomu, že oznámení o spuštění časovače bude detekováno, odesláno do LUIS a možná interpretováno jako požadavek na nastavení nového časovače.

    > 💁 Můžete to otestovat tak, že zakomentujete řádky pro zastavení a restartování rozpoznávání. Nastavte jeden časovač a možná zjistíte, že oznámení nastaví nový časovač, což způsobí nové oznámení, které nastaví další časovač, a tak dále donekonečna!

1. Spusťte aplikaci a ujistěte se, že funkční aplikace také běží. Nastavte několik časovačů a uslyšíte mluvenou odpověď, která říká, že váš časovač byl nastaven, a poté další mluvenou odpověď, když časovač skončí.

> 💁 Tento kód najdete ve složce [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Váš program pro časovač byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby AI pro překlady [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatizované překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.