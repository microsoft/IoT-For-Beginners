<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-28T13:08:10+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "hr"
}
-->
# Prevedi govor - Raspberry Pi

U ovom dijelu lekcije napisat ćete kod za prevođenje teksta koristeći uslugu prevoditelja.

## Pretvorite tekst u govor koristeći uslugu prevoditelja

REST API za uslugu govora ne podržava direktne prijevode, ali možete koristiti uslugu Prevoditelja za prevođenje teksta generiranog uslugom govora u tekst, kao i teksta izgovorenog odgovora. Ova usluga ima REST API koji možete koristiti za prevođenje teksta.

### Zadatak - koristite resurs prevoditelja za prevođenje teksta

1. Vaš pametni mjerač vremena imat će postavljena 2 jezika - jezik servera koji je korišten za treniranje LUIS-a (isti jezik se također koristi za izgradnju poruka koje se govore korisniku) i jezik koji govori korisnik. Ažurirajte varijablu `language` tako da bude jezik koji će korisnik govoriti, i dodajte novu varijablu nazvanu `server_language` za jezik korišten za treniranje LUIS-a:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Zamijenite `<user language>` nazivom lokaliteta za jezik kojim ćete govoriti, na primjer `fr-FR` za francuski ili `zn-HK` za kantonski.

    Zamijenite `<server language>` nazivom lokaliteta za jezik korišten za treniranje LUIS-a.

    Popis podržanih jezika i njihovih naziva lokaliteta možete pronaći u [dokumentaciji o podršci za jezike i glasove na Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ako ne govorite više jezika, možete koristiti uslugu poput [Bing Translate](https://www.bing.com/translator) ili [Google Translate](https://translate.google.com) za prevođenje s vašeg preferiranog jezika na jezik po izboru. Ove usluge mogu reproducirati audio prevedenog teksta.
    >
    > Na primjer, ako trenirate LUIS na engleskom, ali želite koristiti francuski kao jezik korisnika, možete prevesti rečenice poput "postavi mjerač vremena na 2 minute i 27 sekundi" s engleskog na francuski koristeći Bing Translate, a zatim koristiti gumb **Listen translation** za izgovaranje prijevoda u mikrofon.
    >
    > ![Gumb za slušanje prijevoda na Bing Translate](../../../../../translated_images/hr/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Dodajte API ključ prevoditelja ispod `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Zamijenite `<key>` API ključem za vaš resurs usluge prevoditelja.

1. Iznad funkcije `say`, definirajte funkciju `translate_text` koja će prevoditi tekst s jezika servera na jezik korisnika:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Jezici "from" i "to" prosljeđuju se ovoj funkciji - vaša aplikacija treba pretvoriti s jezika korisnika na jezik servera prilikom prepoznavanja govora, i s jezika servera na jezik korisnika prilikom pružanja izgovorenih povratnih informacija.

1. Unutar ove funkcije definirajte URL i zaglavlja za REST API poziv:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL za ovaj API nije specifičan za lokaciju, već se lokacija prosljeđuje kao zaglavlje. API ključ se koristi direktno, tako da za razliku od usluge govora nije potrebno dobiti pristupni token od API-ja za izdavanje tokena.

1. Ispod ovoga definirajte parametre i tijelo za poziv:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` definira parametre za prosljeđivanje API pozivu, prosljeđujući jezike "from" i "to". Ovaj poziv će prevesti tekst s jezika "from" na jezik "to".

    `body` sadrži tekst za prevođenje. Ovo je niz, jer se više blokova teksta može prevesti u istom pozivu.

1. Napravite REST API poziv i dobijte odgovor:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Odgovor koji se vraća je JSON niz, s jednim stavkom koji sadrži prijevode. Ovaj stavak ima niz za prijevode svih stavki proslijeđenih u tijelu.

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

1. Vratite svojstvo `test` iz prvog prijevoda iz prve stavke u nizu:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Ažurirajte petlju `while True` kako biste preveli tekst iz poziva `convert_speech_to_text` s jezika korisnika na jezik servera:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Ovaj kod također ispisuje originalnu i prevedenu verziju teksta na konzolu.

1. Ažurirajte funkciju `say` kako biste preveli tekst za izgovaranje s jezika servera na jezik korisnika:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Ovaj kod također ispisuje originalnu i prevedenu verziju teksta na konzolu.

1. Pokrenite svoj kod. Osigurajte da vaša funkcijska aplikacija radi i zatražite mjerač vremena na jeziku korisnika, bilo govoreći taj jezik sami ili koristeći aplikaciju za prevođenje.

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

    > 💁 Zbog različitih načina izražavanja u različitim jezicima, možete dobiti prijevode koji se malo razlikuju od primjera koje ste dali LUIS-u. Ako je to slučaj, dodajte više primjera u LUIS, ponovno trenirajte i zatim ponovno objavite model.

> 💁 Ovaj kod možete pronaći u [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) mapi.

😀 Vaš program za višejezični mjerač vremena bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.