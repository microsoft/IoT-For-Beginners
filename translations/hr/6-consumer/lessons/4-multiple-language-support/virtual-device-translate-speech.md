<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-28T13:09:11+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "hr"
}
-->
# Prevedi govor - Virtualni IoT uređaj

U ovom dijelu lekcije napisat ćete kod za prevođenje govora prilikom pretvaranja u tekst koristeći uslugu za govor, a zatim prevesti tekst koristeći uslugu Translator prije nego što generirate izgovoreni odgovor.

## Koristite uslugu za govor za prevođenje govora

Usluga za govor može uzeti govor i ne samo pretvoriti ga u tekst na istom jeziku, već i prevesti rezultat na druge jezike.

### Zadatak - koristite uslugu za govor za prevođenje govora

1. Otvorite projekt `smart-timer` u VS Code-u i provjerite je li virtualno okruženje učitano u terminalu.

1. Dodajte sljedeće naredbe za uvoz ispod postojećih uvoza:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Ovo uvozi klase koje se koriste za prevođenje govora i biblioteku `requests` koja će se koristiti za pozivanje usluge Translator kasnije u ovoj lekciji.

1. Vaš pametni timer imat će postavljena 2 jezika - jezik servera koji je korišten za treniranje LUIS-a (isti jezik se također koristi za izgradnju poruka koje se govore korisniku) i jezik koji govori korisnik. Ažurirajte varijablu `language` tako da bude jezik koji će korisnik govoriti i dodajte novu varijablu nazvanu `server_language` za jezik korišten za treniranje LUIS-a:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Zamijenite `<user language>` nazivom lokaliteta jezika kojim ćete govoriti, na primjer `fr-FR` za francuski ili `zn-HK` za kantonski.

    Zamijenite `<server language>` nazivom lokaliteta jezika korištenog za treniranje LUIS-a.

    Popis podržanih jezika i njihovih naziva lokaliteta možete pronaći u [dokumentaciji o podršci za jezik i glas na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ako ne govorite više jezika, možete koristiti uslugu poput [Bing Translate](https://www.bing.com/translator) ili [Google Translate](https://translate.google.com) za prevođenje s vašeg preferiranog jezika na jezik po izboru. Ove usluge tada mogu reproducirati audio prevedenog teksta. Imajte na umu da će prepoznavač govora ignorirati dio audio izlaza s vašeg uređaja, pa ćete možda trebati koristiti dodatni uređaj za reprodukciju prevedenog teksta.
    >
    > Na primjer, ako trenirate LUIS na engleskom, ali želite koristiti francuski kao jezik korisnika, možete prevesti rečenice poput "set a 2 minute and 27 second timer" s engleskog na francuski koristeći Bing Translate, a zatim koristiti gumb **Listen translation** za izgovaranje prijevoda u mikrofon.
    >
    > ![Gumb za slušanje prijevoda na Bing Translate](../../../../../translated_images/hr/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Zamijenite deklaracije `recognizer_config` i `recognizer` sljedećim:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Ovo stvara konfiguraciju za prevođenje kako bi prepoznalo govor na jeziku korisnika i stvorilo prijevode na jeziku korisnika i servera. Zatim koristi ovu konfiguraciju za stvaranje prepoznavača prijevoda - prepoznavača govora koji može prevesti rezultat prepoznavanja govora na više jezika.

    > 💁 Izvorni jezik mora biti naveden u `target_languages`, inače nećete dobiti nikakve prijevode.

1. Ažurirajte funkciju `recognized`, zamjenjujući cijeli sadržaj funkcije sljedećim:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Ovaj kod provjerava je li događaj prepoznavanja pokrenut jer je govor preveden (ovaj događaj može se pokrenuti i u drugim situacijama, poput prepoznavanja govora bez prijevoda). Ako je govor preveden, pronalazi prijevod u rječniku `args.result.translations` koji odgovara jeziku servera.

    Rječnik `args.result.translations` koristi ključ koji odgovara jezičnom dijelu postavke lokaliteta, a ne cijeloj postavci. Na primjer, ako zatražite prijevod na `fr-FR` za francuski, rječnik će sadržavati unos za `fr`, a ne `fr-FR`.

    Prevedeni tekst se zatim šalje na IoT Hub.

1. Pokrenite ovaj kod kako biste testirali prijevode. Provjerite radi li vaša funkcija aplikacije i zatražite timer na jeziku korisnika, bilo govoreći taj jezik sami ili koristeći aplikaciju za prevođenje.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Prevedite tekst koristeći uslugu Translator

Usluga za govor ne podržava prevođenje teksta natrag u govor, umjesto toga možete koristiti uslugu Translator za prevođenje teksta. Ova usluga ima REST API koji možete koristiti za prevođenje teksta.

### Zadatak - koristite resurs Translator za prevođenje teksta

1. Dodajte API ključ za Translator ispod `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Zamijenite `<key>` API ključem za vaš resurs usluge Translator.

1. Iznad funkcije `say`, definirajte funkciju `translate_text` koja će prevoditi tekst s jezika servera na jezik korisnika:

    ```python
    def translate_text(text):
    ```

1. Unutar ove funkcije definirajte URL i zaglavlja za REST API poziv:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL za ovaj API nije specifičan za lokaciju, umjesto toga lokacija se prosljeđuje kao zaglavlje. API ključ se koristi izravno, tako da za razliku od usluge za govor nema potrebe za dobivanjem pristupnog tokena iz API-ja za izdavanje tokena.

1. Ispod ovoga definirajte parametre i tijelo za poziv:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` definira parametre koji se prosljeđuju API pozivu, prosljeđujući jezike `from` i `to`. Ovaj poziv će prevesti tekst s jezika `from` na jezik `to`.

    `body` sadrži tekst za prevođenje. Ovo je niz, jer se više blokova teksta može prevesti u istom pozivu.

1. Napravite poziv REST API-ju i dobijte odgovor:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Odgovor koji se vraća je JSON niz, s jednim stavkom koji sadrži prijevode. Ovaj stavak ima niz za prijevode svih stavki proslijeđenih u tijelu.

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

1. Vratite svojstvo `text` iz prvog prijevoda iz prvog stavka u nizu:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Ažurirajte funkciju `say` kako biste preveli tekst prije nego što se generira SSML:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Ovaj kod također ispisuje originalnu i prevedenu verziju teksta u konzolu.

1. Pokrenite svoj kod. Provjerite radi li vaša funkcija aplikacije i zatražite timer na jeziku korisnika, bilo govoreći taj jezik sami ili koristeći aplikaciju za prevođenje.

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

    > 💁 Zbog različitih načina izražavanja na različitim jezicima, možete dobiti prijevode koji se malo razlikuju od primjera koje ste dali LUIS-u. Ako je to slučaj, dodajte više primjera u LUIS, ponovno trenirajte i ponovno objavite model.

> 💁 Ovaj kod možete pronaći u mapi [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Vaš program za višejezični timer bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.