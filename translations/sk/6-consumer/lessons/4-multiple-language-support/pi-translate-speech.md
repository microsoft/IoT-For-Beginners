<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-28T09:28:09+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "sk"
}
-->
# Preložiť reč - Raspberry Pi

V tejto časti lekcie napíšete kód na preklad textu pomocou prekladateľskej služby.

## Prevod textu na reč pomocou prekladateľskej služby

REST API služby reči nepodporuje priame preklady, namiesto toho môžete použiť službu Translator na preklad textu generovaného službou prevodu reči na text a textu hovorených odpovedí. Táto služba má REST API, ktoré môžete použiť na preklad textu.

### Úloha - použite prekladateľský zdroj na preklad textu

1. Váš inteligentný časovač bude mať nastavené 2 jazyky - jazyk servera, ktorý bol použitý na trénovanie LUIS (ten istý jazyk sa používa aj na vytváranie správ pre používateľa), a jazyk, ktorým hovorí používateľ. Aktualizujte premennú `language` na jazyk, ktorým bude hovoriť používateľ, a pridajte novú premennú `server_language` pre jazyk použitý na trénovanie LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Nahraďte `<user language>` názvom lokalizácie jazyka, ktorým budete hovoriť, napríklad `fr-FR` pre francúzštinu alebo `zn-HK` pre kantončinu.

    Nahraďte `<server language>` názvom lokalizácie jazyka použitého na trénovanie LUIS.

    Zoznam podporovaných jazykov a ich názvov lokalizácií nájdete v [dokumentácii o podpore jazykov a hlasov na Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ak nehovoríte viacerými jazykmi, môžete použiť službu ako [Bing Translate](https://www.bing.com/translator) alebo [Google Translate](https://translate.google.com) na preklad z vášho preferovaného jazyka do iného jazyka podľa vášho výberu. Tieto služby môžu následne prehrávať zvuk preloženého textu.
    >
    > Napríklad, ak trénujete LUIS v angličtine, ale chcete používať francúzštinu ako jazyk používateľa, môžete preložiť vety ako „nastav časovač na 2 minúty a 27 sekúnd“ z angličtiny do francúzštiny pomocou Bing Translate, a potom použiť tlačidlo **Listen translation** na vyslovenie prekladu do vášho mikrofónu.
    >
    > ![Tlačidlo Listen translation na Bing Translate](../../../../../translated_images/sk/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Pridajte API kľúč pre prekladateľa pod `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Nahraďte `<key>` API kľúčom pre váš prekladateľský zdroj.

1. Nad funkciou `say` definujte funkciu `translate_text`, ktorá bude prekladať text z jazyka servera do jazyka používateľa:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Do tejto funkcie sa odovzdávajú jazyky „from“ a „to“ - vaša aplikácia musí prevádzať z jazyka používateľa na jazyk servera pri rozpoznávaní reči a z jazyka servera na jazyk používateľa pri poskytovaní hovorených odpovedí.

1. Vo vnútri tejto funkcie definujte URL a hlavičky pre REST API volanie:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL pre toto API nie je špecifické pre lokalitu, namiesto toho sa lokalita odovzdáva ako hlavička. API kľúč sa používa priamo, takže na rozdiel od služby reči nie je potrebné získavať prístupový token z API vydavateľa tokenov.

1. Nižšie definujte parametre a telo pre volanie:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` definuje parametre, ktoré sa odovzdávajú API volaniu, pričom sa odovzdávajú jazyky „from“ a „to“. Toto volanie preloží text z jazyka „from“ do jazyka „to“.

    `body` obsahuje text na preklad. Ide o pole, pretože v jednom volaní je možné preložiť viacero blokov textu.

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
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. Vráťte vlastnosť `text` z prvého prekladu z prvej položky v poli:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Aktualizujte cyklus `while True`, aby prekladal text z volania `convert_speech_to_text` z jazyka používateľa do jazyka servera:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Tento kód tiež vypíše pôvodnú a preloženú verziu textu do konzoly.

1. Aktualizujte funkciu `say`, aby prekladala text na vyslovenie z jazyka servera do jazyka používateľa:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Tento kód tiež vypíše pôvodnú a preloženú verziu textu do konzoly.

1. Spustite svoj kód. Uistite sa, že vaša funkčná aplikácia beží, a požiadajte o časovač v jazyku používateľa, buď tým, že budete hovoriť týmto jazykom sami, alebo pomocou prekladateľskej aplikácie.

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

    > 💁 Kvôli rôznym spôsobom vyjadrovania v rôznych jazykoch môžete dostať preklady, ktoré sa mierne líšia od príkladov, ktoré ste poskytli LUIS. Ak je to tak, pridajte viac príkladov do LUIS, znova natrénujte a potom znova publikujte model.

> 💁 Tento kód nájdete v priečinku [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 Váš viacjazyčný program časovača bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.