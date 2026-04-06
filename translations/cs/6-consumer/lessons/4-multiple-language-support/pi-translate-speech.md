# Překlad řeči - Raspberry Pi

V této části lekce napíšete kód pro překlad textu pomocí překladatelské služby.

## Převod textu na řeč pomocí překladatelské služby

REST API služby pro řeč nepodporuje přímé překlady, místo toho můžete použít službu Translator k překladu textu vytvořeného službou převodu řeči na text a textu mluvené odpovědi. Tato služba má REST API, které můžete použít k překladu textu.

### Úkol - použití zdroje Translator k překladu textu

1. Váš chytrý časovač bude mít nastaveny 2 jazyky - jazyk serveru, který byl použit k trénování LUIS (stejný jazyk se také používá k vytváření zpráv pro komunikaci s uživatelem), a jazyk, kterým mluví uživatel. Aktualizujte proměnnou `language` na jazyk, kterým bude mluvit uživatel, a přidejte novou proměnnou `server_language` pro jazyk použitý k trénování LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Nahraďte `<user language>` názvem místního nastavení jazyka, kterým budete mluvit, například `fr-FR` pro francouzštinu nebo `zn-HK` pro kantonštinu.

    Nahraďte `<server language>` názvem místního nastavení jazyka použitého k trénování LUIS.

    Seznam podporovaných jazyků a jejich názvů místních nastavení najdete v [dokumentaci o podpoře jazyků a hlasů na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Pokud nemluvíte více jazyky, můžete použít službu jako [Bing Translate](https://www.bing.com/translator) nebo [Google Translate](https://translate.google.com) k překladu z vašeho preferovaného jazyka do jiného jazyka dle vašeho výběru. Tyto služby pak mohou přehrát zvuk přeloženého textu.
    >
    > Například pokud trénujete LUIS v angličtině, ale chcete použít francouzštinu jako uživatelský jazyk, můžete věty jako "nastav časovač na 2 minuty a 27 sekund" přeložit z angličtiny do francouzštiny pomocí Bing Translate, a poté použít tlačítko **Poslechnout překlad** k vyslovení překladu do mikrofonu.
    >
    > ![Tlačítko Poslechnout překlad na Bing Translate](../../../../../translated_images/cs/bing-translate.348aa796d6efe2a9.webp)

1. Přidejte klíč API překladatelské služby pod `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Nahraďte `<key>` klíčem API pro váš zdroj překladatelské služby.

1. Nad funkcí `say` definujte funkci `translate_text`, která bude překládat text z jazyka serveru do uživatelského jazyka:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Do této funkce se předávají zdrojový a cílový jazyk - vaše aplikace musí převádět z uživatelského jazyka do jazyka serveru při rozpoznávání řeči a z jazyka serveru do uživatelského jazyka při poskytování mluvené zpětné vazby.

1. Uvnitř této funkce definujte URL a hlavičky pro volání REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL pro toto API není specifické pro lokalitu, místo toho se lokalita předává jako hlavička. Klíč API se používá přímo, takže na rozdíl od služby pro řeč není potřeba získat přístupový token z API vydavatele tokenů.

1. Pod tímto definujte parametry a tělo pro volání:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` definuje parametry, které se předávají volání API, přičemž se předávají zdrojový a cílový jazyk. Toto volání přeloží text ze zdrojového jazyka do cílového jazyka.

    `body` obsahuje text k překladu. Jedná se o pole, protože v jednom volání lze přeložit více bloků textu.

1. Proveďte volání REST API a získejte odpověď:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Odpověď, která se vrátí, je JSON pole, které obsahuje jednu položku s překlady. Tato položka má pole pro překlady všech položek předaných v těle.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. Vraťte vlastnost `text` z prvního překladu z první položky v poli:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Aktualizujte smyčku `while True`, aby překládala text z volání `convert_speech_to_text` z uživatelského jazyka do jazyka serveru:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Tento kód také vypisuje původní a přeložené verze textu do konzole.

1. Aktualizujte funkci `say`, aby překládala text k vyslovení z jazyka serveru do uživatelského jazyka:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Tento kód také vypisuje původní a přeložené verze textu do konzole.

1. Spusťte svůj kód. Ujistěte se, že vaše funkční aplikace běží, a požádejte o časovač v uživatelském jazyce, buď tím, že budete mluvit tímto jazykem sami, nebo pomocí překladatelské aplikace.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Kvůli různým způsobům vyjadřování v různých jazycích můžete získat překlady, které se mírně liší od příkladů, které jste poskytli LUIS. Pokud k tomu dojde, přidejte do LUIS více příkladů, znovu natrénujte a poté znovu publikujte model.

> 💁 Tento kód najdete ve složce [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 Váš vícejazyčný program časovače byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Přestože se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.