# Prevedi govor - Raspberry Pi

V tem delu lekcije boste napisali kodo za prevajanje besedila z uporabo storitve za prevajanje.

## Pretvorba besedila v govor z uporabo storitve za prevajanje

REST API storitve za govor ne podpira neposrednih prevodov, namesto tega lahko uporabite storitev Translator za prevajanje besedila, ki ga ustvari storitev za pretvorbo govora v besedilo, in besedila izgovorjenega odziva. Ta storitev ima REST API, ki ga lahko uporabite za prevajanje besedila.

### Naloga - uporaba vira Translator za prevajanje besedila

1. Vaša pametna ura bo imela nastavljena dva jezika - jezik strežnika, ki je bil uporabljen za treniranje LUIS (isti jezik se uporablja tudi za sestavljanje sporočil za uporabnika), in jezik, ki ga govori uporabnik. Posodobite spremenljivko `language`, da bo to jezik, ki ga bo govoril uporabnik, in dodajte novo spremenljivko `server_language` za jezik, ki je bil uporabljen za treniranje LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Zamenjajte `<user language>` z imenom lokalizacije jezika, v katerem boste govorili, na primer `fr-FR` za francoščino ali `zn-HK` za kantonščino.

    Zamenjajte `<server language>` z imenom lokalizacije jezika, ki je bil uporabljen za treniranje LUIS.

    Seznam podprtih jezikov in njihovih lokalizacijskih imen najdete v [dokumentaciji o podpori za jezike in glasove na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Če ne govorite več jezikov, lahko uporabite storitev, kot sta [Bing Translate](https://www.bing.com/translator) ali [Google Translate](https://translate.google.com), za prevajanje iz vašega želenega jezika v izbran jezik. Te storitve lahko nato predvajajo zvok prevedenega besedila.
    >
    > Na primer, če trenirate LUIS v angleščini, vendar želite uporabiti francoščino kot uporabniški jezik, lahko prevedete stavke, kot je "nastavi 2 minuti in 27 sekundni časovnik", iz angleščine v francoščino z Bing Translate, nato pa uporabite gumb **Poslušaj prevod**, da izgovorite prevod v mikrofon.
    >
    > ![Gumb poslušaj prevod na Bing Translate](../../../../../translated_images/sl/bing-translate.348aa796d6efe2a9.webp)

1. Dodajte ključ API storitve Translator pod `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Zamenjajte `<key>` s ključem API za vaš vir storitve Translator.

1. Nad funkcijo `say` definirajte funkcijo `translate_text`, ki bo prevedla besedilo iz jezika strežnika v uporabniški jezik:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Jezika "from" in "to" sta posredovana tej funkciji - vaša aplikacija mora pretvoriti iz uporabniškega jezika v jezik strežnika pri prepoznavanju govora in iz jezika strežnika v uporabniški jezik pri podajanju izgovorjenega odziva.

1. Znotraj te funkcije definirajte URL in glave za klic REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL za ta API ni specifičen za lokacijo, namesto tega je lokacija posredovana kot glava. Ključ API se uporablja neposredno, zato za razliko od storitve za govor ni treba pridobiti dostopnega žetona iz API za izdajo žetonov.

1. Spodaj definirajte parametre in telo za klic:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` definira parametre za posredovanje klicu API, pri čemer posreduje jezika "from" in "to". Ta klic bo prevedel besedilo iz jezika "from" v jezik "to".

    `body` vsebuje besedilo za prevajanje. To je polje, saj je mogoče v istem klicu prevesti več blokov besedila.

1. Izvedite klic REST API in pridobite odziv:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Odziv, ki se vrne, je JSON polje z enim elementom, ki vsebuje prevode. Ta element ima polje za prevode vseh elementov, posredovanih v telesu.

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

1. Vrni lastnost `text` iz prvega prevoda prvega elementa v polju:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Posodobite zanko `while True`, da prevedete besedilo iz klica `convert_speech_to_text` iz uporabniškega jezika v jezik strežnika:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Ta koda tudi natisne izvirno in prevedeno različico besedila v konzolo.

1. Posodobite funkcijo `say`, da prevedete besedilo za izgovor iz jezika strežnika v uporabniški jezik:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Ta koda tudi natisne izvirno in prevedeno različico besedila v konzolo.

1. Zaženite svojo kodo. Prepričajte se, da vaša funkcijska aplikacija deluje, in zahtevajte časovnik v uporabniškem jeziku, bodisi tako, da sami govorite ta jezik, bodisi z uporabo aplikacije za prevajanje.

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

    > 💁 Zaradi različnih načinov izražanja v različnih jezikih lahko dobite prevode, ki se nekoliko razlikujejo od primerov, ki ste jih dali LUIS. Če je temu tako, dodajte več primerov v LUIS, ponovno trenirajte in nato ponovno objavite model.

> 💁 To kodo najdete v mapi [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 Vaš večjezični program za časovnik je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.