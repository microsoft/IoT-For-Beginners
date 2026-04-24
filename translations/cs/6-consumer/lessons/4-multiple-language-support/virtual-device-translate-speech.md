# Překlad řeči - Virtuální IoT zařízení

V této části lekce napíšete kód pro překlad řeči při převodu na text pomocí služby pro rozpoznávání řeči, poté přeložíte text pomocí služby Translator a nakonec vygenerujete mluvenou odpověď.

## Použití služby pro rozpoznávání řeči k překladu řeči

Služba pro rozpoznávání řeči dokáže nejen převést řeč na text ve stejném jazyce, ale také přeložit výstup do jiných jazyků.

### Úkol - použití služby pro rozpoznávání řeči k překladu řeči

1. Otevřete projekt `smart-timer` ve VS Code a ujistěte se, že je v terminálu načten virtuální prostředí.

1. Přidejte následující příkazy pro import pod stávající importy:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Tímto se importují třídy používané pro překlad řeči a knihovna `requests`, která bude později v této lekci použita pro volání služby Translator.

1. Váš chytrý časovač bude mít nastaveny 2 jazyky - jazyk serveru, který byl použit pro trénování LUIS (stejný jazyk se také používá pro vytváření zpráv určených k mluvení s uživatelem), a jazyk, kterým mluví uživatel. Aktualizujte proměnnou `language` na jazyk, kterým bude uživatel mluvit, a přidejte novou proměnnou `server_language` pro jazyk použitý k trénování LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Nahraďte `<user language>` názvem místního nastavení jazyka, kterým budete mluvit, například `fr-FR` pro francouzštinu nebo `zn-HK` pro kantonštinu.

    Nahraďte `<server language>` názvem místního nastavení jazyka použitého k trénování LUIS.

    Seznam podporovaných jazyků a jejich názvů místních nastavení najdete v [dokumentaci o podpoře jazyků a hlasů na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Pokud nemluvíte více jazyky, můžete použít službu jako [Bing Translate](https://www.bing.com/translator) nebo [Google Translate](https://translate.google.com) k překladu z vašeho preferovaného jazyka do jiného jazyka. Tyto služby pak mohou přehrát audio přeloženého textu. Uvědomte si, že rozpoznávač řeči může ignorovat některý zvukový výstup z vašeho zařízení, takže možná budete potřebovat další zařízení pro přehrání přeloženého textu.
    >
    > Například pokud trénujete LUIS v angličtině, ale chcete použít francouzštinu jako uživatelský jazyk, můžete věty jako „nastav časovač na 2 minuty a 27 sekund“ přeložit z angličtiny do francouzštiny pomocí Bing Translate, a poté použít tlačítko **Poslechnout překlad** k vyslovení překladu do mikrofonu.
    >
    > ![Tlačítko Poslechnout překlad na Bing Translate](../../../../../translated_images/cs/bing-translate.348aa796d6efe2a9.webp)

1. Nahraďte deklarace `recognizer_config` a `recognizer` následujícím:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Tímto se vytvoří konfigurační nastavení pro překlad, které rozpozná řeč v uživatelském jazyce a vytvoří překlady v uživatelském a serverovém jazyce. Poté se použije tento konfigurátor k vytvoření překladového rozpoznávače - rozpoznávače řeči, který dokáže přeložit výstup rozpoznávání řeči do více jazyků.

    > 💁 Původní jazyk musí být uveden v `target_languages`, jinak nebudete mít žádné překlady.

1. Aktualizujte funkci `recognized`, nahraďte celý obsah funkce následujícím:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Tento kód kontroluje, zda byla událost rozpoznání spuštěna kvůli překladu řeči (tato událost může být spuštěna i v jiných případech, například když je řeč rozpoznána, ale není přeložena). Pokud byla řeč přeložena, najde překlad ve slovníku `args.result.translations`, který odpovídá serverovému jazyku.

    Slovník `args.result.translations` je klíčován podle jazykové části nastavení místního jazyka, nikoli podle celého nastavení. Například pokud požádáte o překlad do `fr-FR` pro francouzštinu, slovník bude obsahovat položku pro `fr`, nikoli `fr-FR`.

    Přeložený text je poté odeslán do IoT Hubu.

1. Spusťte tento kód pro testování překladů. Ujistěte se, že vaše funkční aplikace běží, a požádejte o časovač v uživatelském jazyce, buď mluvením tímto jazykem, nebo použitím překladové aplikace.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Překlad textu pomocí služby Translator

Služba pro rozpoznávání řeči nepodporuje překlad textu zpět na řeč, místo toho můžete použít službu Translator k překladu textu. Tato služba má REST API, které můžete použít k překladu textu.

### Úkol - použití zdroje Translator k překladu textu

1. Přidejte klíč API pro Translator pod `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Nahraďte `<key>` klíčem API pro váš zdroj služby Translator.

1. Nad funkcí `say` definujte funkci `translate_text`, která přeloží text ze serverového jazyka do uživatelského jazyka:

    ```python
    def translate_text(text):
    ```

1. Uvnitř této funkce definujte URL a hlavičky pro volání REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL pro toto API není specifické pro lokalitu, místo toho je lokalita předána jako hlavička. Klíč API je použit přímo, takže na rozdíl od služby pro rozpoznávání řeči není potřeba získat přístupový token z API pro vydávání tokenů.

1. Pod tímto definujte parametry a tělo pro volání:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` definuje parametry, které se předají volání API, a předává jazyky `from` a `to`. Toto volání přeloží text z jazyka `from` do jazyka `to`.

    `body` obsahuje text k překladu. Jedná se o pole, protože v jednom volání lze přeložit více bloků textu.

1. Proveďte volání REST API a získejte odpověď:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Odpověď, která se vrátí, je JSON pole s jednou položkou, která obsahuje překlady. Tato položka má pole pro překlady všech položek předaných v těle.

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

1. Vraťte vlastnost `text` z prvního překladu z první položky v poli:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Aktualizujte funkci `say`, aby přeložila text k vyslovení před generováním SSML:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Tento kód také vypíše původní a přeložené verze textu do konzole.

1. Spusťte svůj kód. Ujistěte se, že vaše funkční aplikace běží, a požádejte o časovač v uživatelském jazyce, buď mluvením tímto jazykem, nebo použitím překladové aplikace.

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

    > 💁 Kvůli různým způsobům vyjadřování v různých jazycích můžete získat překlady, které se mírně liší od příkladů, které jste poskytli LUIS. Pokud je to tento případ, přidejte více příkladů do LUIS, znovu trénujte a poté model znovu publikujte.

> 💁 Tento kód najdete ve složce [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Váš vícejazyčný program časovače byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.