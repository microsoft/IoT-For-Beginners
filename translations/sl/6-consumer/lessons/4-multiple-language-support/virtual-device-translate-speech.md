# Prevedi govor - Virtualna IoT naprava

V tem delu lekcije boste napisali kodo za prevajanje govora pri pretvorbi v besedilo z uporabo storitve za govor, nato pa prevedli besedilo z uporabo storitve Translator, preden ustvarite govorjeni odgovor.

## Uporaba storitve za govor za prevajanje govora

Storitve za govor lahko sprejmejo govor in ga ne le pretvorijo v besedilo v istem jeziku, temveč tudi prevedejo izhod v druge jezike.

### Naloga - uporaba storitve za govor za prevajanje govora

1. Odprite projekt `smart-timer` v VS Code in se prepričajte, da je virtualno okolje naloženo v terminalu.

1. Dodajte naslednje uvozne izjave pod obstoječe uvoze:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    To uvozi razrede, ki se uporabljajo za prevajanje govora, in knjižnico `requests`, ki bo uporabljena za klic storitve Translator kasneje v tej lekciji.

1. Vaša pametna ura bo imela nastavljena 2 jezika - jezik strežnika, ki je bil uporabljen za treniranje LUIS (isti jezik se uporablja tudi za ustvarjanje sporočil za uporabnika), in jezik, ki ga govori uporabnik. Posodobite spremenljivko `language`, da bo to jezik, ki ga bo govoril uporabnik, in dodajte novo spremenljivko `server_language` za jezik, uporabljen za treniranje LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Zamenjajte `<user language>` z imenom lokalnega jezika, v katerem boste govorili, na primer `fr-FR` za francoščino ali `zn-HK` za kantonščino.

    Zamenjajte `<server language>` z imenom lokalnega jezika, uporabljenega za treniranje LUIS.

    Seznam podprtih jezikov in njihovih lokalnih imen najdete v [dokumentaciji o podpori za jezike in glasove na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Če ne govorite več jezikov, lahko uporabite storitev, kot je [Bing Translate](https://www.bing.com/translator) ali [Google Translate](https://translate.google.com), za prevajanje iz vašega želenega jezika v izbrani jezik. Te storitve lahko nato predvajajo zvok prevedenega besedila. Upoštevajte, da bo prepoznavalnik govora ignoriral nekatere zvočne izhode iz vaše naprave, zato boste morda morali uporabiti dodatno napravo za predvajanje prevedenega besedila.
    >
    > Na primer, če trenirate LUIS v angleščini, vendar želite uporabiti francoščino kot uporabniški jezik, lahko prevedete stavke, kot je "nastavi 2 minuti in 27 sekundni časovnik", iz angleščine v francoščino z uporabo Bing Translate, nato pa uporabite gumb **Listen translation**, da govorite prevod v mikrofon.
    >
    > ![Gumb za poslušanje prevoda na Bing Translate](../../../../../translated_images/sl/bing-translate.348aa796d6efe2a9.webp)

1. Zamenjajte deklaracije `recognizer_config` in `recognizer` z naslednjimi:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    To ustvari konfiguracijo za prevajanje, ki prepozna govor v uporabniškem jeziku in ustvari prevode v uporabniškem in strežniškem jeziku. Nato uporabi to konfiguracijo za ustvarjanje prepoznavalnika prevodov - prepoznavalnika govora, ki lahko prevede izhod prepoznave govora v več jezikov.

    > 💁 Izvirni jezik mora biti naveden v `target_languages`, sicer ne boste dobili nobenih prevodov.

1. Posodobite funkcijo `recognized`, tako da zamenjate celotno vsebino funkcije z naslednjo:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Ta koda preveri, ali je bil dogodek prepoznan sprožen zaradi prevoda govora (ta dogodek se lahko sproži tudi v drugih primerih, na primer, ko je govor prepoznan, vendar ne preveden). Če je bil govor preveden, najde prevod v slovarju `args.result.translations`, ki ustreza strežniškemu jeziku.

    Slovar `args.result.translations` je ključan glede na jezikovni del nastavitve lokalnega jezika, ne celotne nastavitve. Na primer, če zahtevate prevod v `fr-FR` za francoščino, bo slovar vseboval vnos za `fr`, ne za `fr-FR`.

    Prevedeno besedilo se nato pošlje v IoT Hub.

1. Zaženite to kodo za testiranje prevodov. Prepričajte se, da vaša funkcija deluje, in zahtevajte časovnik v uporabniškem jeziku, bodisi tako, da sami govorite ta jezik, bodisi z uporabo aplikacije za prevajanje.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Prevajanje besedila z uporabo storitve Translator

Storitve za govor ne podpirajo prevajanja besedila nazaj v govor, namesto tega lahko uporabite storitev Translator za prevajanje besedila. Ta storitev ima REST API, ki ga lahko uporabite za prevajanje besedila.

### Naloga - uporaba vira Translator za prevajanje besedila

1. Dodajte ključ API za Translator pod `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Zamenjajte `<key>` s ključem API za vaš vir storitve Translator.

1. Nad funkcijo `say` definirajte funkcijo `translate_text`, ki bo prevedla besedilo iz strežniškega jezika v uporabniški jezik:

    ```python
    def translate_text(text):
    ```

1. Znotraj te funkcije definirajte URL in glave za klic REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL za ta API ni specifičen za lokacijo, namesto tega se lokacija posreduje kot glava. Ključ API se uporablja neposredno, zato za razliko od storitve za govor ni treba pridobiti dostopnega žetona iz API za izdajanje žetonov.

1. Pod tem definirajte parametre in telo za klic:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` določa parametre za posredovanje klicu API, pri čemer posreduje jezike `from` in `to`. Ta klic bo prevedel besedilo iz jezika `from` v jezik `to`.

    `body` vsebuje besedilo za prevajanje. To je polje, saj je mogoče v istem klicu prevesti več blokov besedila.

1. Izvedite klic REST API in pridobite odgovor:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Odgovor, ki se vrne, je JSON polje z enim elementom, ki vsebuje prevode. Ta element ima polje za prevode vseh elementov, posredovanih v telesu.

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

1. Vrni lastnost `text` iz prvega prevoda iz prvega elementa v polju:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Posodobite funkcijo `say`, da prevede besedilo, preden se ustvari SSML:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Ta koda prav tako izpiše izvirno in prevedeno različico besedila v konzolo.

1. Zaženite svojo kodo. Prepričajte se, da vaša funkcija deluje, in zahtevajte časovnik v uporabniškem jeziku, bodisi tako, da sami govorite ta jezik, bodisi z uporabo aplikacije za prevajanje.

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

    > 💁 Zaradi različnih načinov izražanja v različnih jezikih lahko dobite prevode, ki se nekoliko razlikujejo od primerov, ki ste jih dali LUIS. Če je temu tako, dodajte več primerov v LUIS, ponovno trenirajte in nato ponovno objavite model.

> 💁 To kodo najdete v mapi [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Vaš večjezični program za časovnik je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitne nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.