<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-28T08:56:28+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "sk"
}
-->
# Text na reč - Virtuálne IoT zariadenie

V tejto časti lekcie napíšete kód na prevod textu na reč pomocou služby na spracovanie reči.

## Prevod textu na reč

SDK služby na spracovanie reči, ktoré ste použili v predchádzajúcej lekcii na prevod reči na text, môžete použiť aj na prevod textu späť na reč. Pri požiadavke na reč musíte zadať hlas, ktorý sa má použiť, pretože reč môže byť generovaná pomocou rôznych hlasov.

Každý jazyk podporuje rôzne hlasy a zoznam podporovaných hlasov pre každý jazyk môžete získať zo SDK služby na spracovanie reči.

### Úloha - prevod textu na reč

1. Otvorte projekt `smart-timer` vo VS Code a uistite sa, že virtuálne prostredie je načítané v termináli.

1. Importujte `SpeechSynthesizer` z balíka `azure.cognitiveservices.speech` pridaním do existujúcich importov:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Nad funkciou `say` vytvorte konfiguráciu reči, ktorá sa použije so syntetizátorom reči:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Táto konfigurácia používa rovnaký API kľúč, lokalitu a jazyk, aké používal rozpoznávač.

1. Pod týmto kódom pridajte nasledujúci kód na získanie hlasu a jeho nastavenie v konfigurácii reči:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Tento kód načíta zoznam všetkých dostupných hlasov a potom nájde prvý hlas, ktorý zodpovedá používanej reči.

    > 💁 Kompletný zoznam podporovaných hlasov môžete nájsť v [dokumentácii o podpore jazykov a hlasov na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Ak chcete použiť konkrétny hlas, môžete túto funkciu odstrániť a pevne nastaviť hlas na názov hlasu z tejto dokumentácie. Napríklad:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Aktualizujte obsah funkcie `say` tak, aby generovala SSML pre odpoveď:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Pod týmto kódom zastavte rozpoznávanie reči, prehrajte SSML a potom opäť spustite rozpoznávanie:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Rozpoznávanie sa zastaví počas prehrávania textu, aby sa zabránilo tomu, že oznámenie o spustení časovača bude detegované, odoslané do LUIS a prípadne interpretované ako požiadavka na nastavenie nového časovača.

    > 💁 Môžete si to vyskúšať tak, že zakomentujete riadky na zastavenie a opätovné spustenie rozpoznávania. Nastavte jeden časovač a možno zistíte, že oznámenie nastaví nový časovač, čo spôsobí nové oznámenie, vedúce k novému časovaču, a tak ďalej donekonečna!

1. Spustite aplikáciu a uistite sa, že funkčná aplikácia tiež beží. Nastavte niekoľko časovačov a budete počuť hovorenú odpoveď, ktorá oznámi, že váš časovač bol nastavený, a ďalšiu hovorenú odpoveď, keď časovač skončí.

> 💁 Tento kód nájdete v priečinku [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Váš program na časovače bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.