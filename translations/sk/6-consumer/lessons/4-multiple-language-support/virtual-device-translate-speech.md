# Preložiť reč - Virtuálne IoT zariadenie

V tejto časti lekcie napíšete kód na preklad reči pri jej prevode na text pomocou služby na spracovanie reči, následne preložíte text pomocou služby Translator a nakoniec vygenerujete hovorenú odpoveď.

## Použitie služby na spracovanie reči na preklad reči

Služba na spracovanie reči dokáže nielen previesť reč na text v rovnakom jazyku, ale aj preložiť výstup do iných jazykov.

### Úloha - použitie služby na spracovanie reči na preklad reči

1. Otvorte projekt `smart-timer` vo VS Code a uistite sa, že virtuálne prostredie je načítané v termináli.

1. Pridajte nasledujúce importy pod existujúce importy:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Týmto sa importujú triedy používané na preklad reči a knižnica `requests`, ktorá sa neskôr v tejto lekcii použije na volanie služby Translator.

1. Váš inteligentný časovač bude mať nastavené 2 jazyky - jazyk servera, ktorý bol použitý na trénovanie LUIS (rovnaký jazyk sa používa aj na vytváranie správ pre používateľa), a jazyk, ktorým hovorí používateľ. Aktualizujte premennú `language` na jazyk, ktorým bude hovoriť používateľ, a pridajte novú premennú `server_language` pre jazyk použitý na trénovanie LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Nahraďte `<user language>` názvom lokalizácie jazyka, ktorým budete hovoriť, napríklad `fr-FR` pre francúzštinu alebo `zn-HK` pre kantončinu.

    Nahraďte `<server language>` názvom lokalizácie jazyka použitého na trénovanie LUIS.

    Zoznam podporovaných jazykov a ich názvov lokalizácií nájdete v [dokumentácii o podpore jazykov a hlasov na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ak nehovoríte viacerými jazykmi, môžete použiť službu ako [Bing Translate](https://www.bing.com/translator) alebo [Google Translate](https://translate.google.com) na preklad z vášho preferovaného jazyka do iného jazyka. Tieto služby môžu následne prehrať zvuk preloženého textu. Uvedomte si, že rozpoznávač reči môže ignorovať niektoré zvukové výstupy z vášho zariadenia, takže možno budete potrebovať ďalšie zariadenie na prehrávanie preloženého textu.
    >
    > Napríklad, ak trénujete LUIS v angličtine, ale chcete používať francúzštinu ako jazyk používateľa, môžete preložiť vety ako „nastav časovač na 2 minúty a 27 sekúnd“ z angličtiny do francúzštiny pomocou Bing Translate, a potom použiť tlačidlo **Listen translation** na prehranie prekladu do vášho mikrofónu.
    >
    > ![Tlačidlo Listen translation na Bing Translate](../../../../../translated_images/sk/bing-translate.348aa796d6efe2a9.webp)

1. Nahraďte deklarácie `recognizer_config` a `recognizer` nasledujúcim:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Týmto sa vytvorí konfiguračný súbor na rozpoznávanie reči v jazyku používateľa a na vytváranie prekladov v jazyku používateľa a servera. Následne sa tento konfiguračný súbor použije na vytvorenie prekladového rozpoznávača - rozpoznávača reči, ktorý dokáže preložiť výstup rozpoznávania reči do viacerých jazykov.

    > 💁 Pôvodný jazyk musí byť špecifikovaný v `target_languages`, inak nedostanete žiadne preklady.

1. Aktualizujte funkciu `recognized`, pričom nahraďte celý obsah funkcie nasledujúcim:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Tento kód kontroluje, či bola udalosť rozpoznania spustená kvôli prekladu reči (táto udalosť môže byť spustená aj v iných prípadoch, napríklad keď je reč rozpoznaná, ale nie preložená). Ak bola reč preložená, nájde preklad v slovníku `args.result.translations`, ktorý zodpovedá jazyku servera.

    Slovník `args.result.translations` je kľúčovaný podľa jazykovej časti nastavenia lokalizácie, nie celého nastavenia. Napríklad, ak požiadate o preklad do `fr-FR` pre francúzštinu, slovník bude obsahovať položku pre `fr`, nie `fr-FR`.

    Preložený text sa potom odošle do IoT Hub.

1. Spustite tento kód na otestovanie prekladov. Uistite sa, že vaša funkcia aplikácie beží, a požiadajte o časovač v jazyku používateľa, buď hovorením týmto jazykom, alebo použitím prekladovej aplikácie.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Preklad textu pomocou služby Translator

Služba na spracovanie reči nepodporuje preklad textu späť na reč, namiesto toho môžete použiť službu Translator na preklad textu. Táto služba má REST API, ktoré môžete použiť na preklad textu.

### Úloha - použitie zdroja Translator na preklad textu

1. Pridajte API kľúč pre Translator pod `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Nahraďte `<key>` API kľúčom pre váš zdroj služby Translator.

1. Nad funkciou `say` definujte funkciu `translate_text`, ktorá bude prekladať text z jazyka servera do jazyka používateľa:

    ```python
    def translate_text(text):
    ```

1. V tejto funkcii definujte URL a hlavičky pre volanie REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL pre toto API nie je špecifické pre lokalitu, namiesto toho sa lokalita odovzdáva ako hlavička. API kľúč sa používa priamo, takže na rozdiel od služby na spracovanie reči nie je potrebné získavať prístupový token z API na vydávanie tokenov.

1. Pod týmto definujte parametre a telo pre volanie:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` definuje parametre, ktoré sa odovzdávajú volaniu API, pričom sa odovzdávajú jazyky `from` a `to`. Toto volanie preloží text z jazyka `from` do jazyka `to`.

    `body` obsahuje text na preklad. Toto je pole, pretože v jednom volaní je možné preložiť viacero blokov textu.

1. Vykonajte volanie REST API a získajte odpoveď:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Odpoveď, ktorá sa vráti, je JSON pole, ktoré obsahuje jednu položku s prekladmi. Táto položka má pole pre preklady všetkých položiek odovzdaných v tele.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. Vráťte vlastnosť `text` z prvého prekladu z prvej položky v poli:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Aktualizujte funkciu `say`, aby preložila text na výslovnosť predtým, ako sa vygeneruje SSML:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Tento kód tiež vypíše pôvodnú a preloženú verziu textu do konzoly.

1. Spustite svoj kód. Uistite sa, že vaša funkcia aplikácie beží, a požiadajte o časovač v jazyku používateľa, buď hovorením týmto jazykom, alebo použitím prekladovej aplikácie.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Kvôli rôznym spôsobom vyjadrovania v rôznych jazykoch môžete dostať preklady, ktoré sa mierne líšia od príkladov, ktoré ste poskytli LUIS. Ak je to tak, pridajte viac príkladov do LUIS, znova trénujte a potom znova publikujte model.

> 💁 Tento kód nájdete v priečinku [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Váš viacjazyčný program časovača bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Za autoritatívny zdroj by sa mal považovať pôvodný dokument v jeho pôvodnom jazyku. Pre dôležité informácie odporúčame profesionálny ľudský preklad. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.