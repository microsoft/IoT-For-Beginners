# Išversti kalbą – Virtualus IoT įrenginys

Šioje pamokos dalyje rašysite kodą, kuris išvers kalbą konvertuojant ją į tekstą naudojant kalbos paslaugą, o tada išvers tekstą naudodami Translator paslaugą prieš sugeneruodami garsinį atsakymą.

## Naudokite kalbos paslaugą kalbos vertimui

Kalbos paslauga gali ne tik konvertuoti kalbą į tekstą ta pačia kalba, bet ir išversti rezultatą į kitas kalbas.

### Užduotis – naudokite kalbos paslaugą kalbos vertimui

1. Atidarykite `smart-timer` projektą VS Code ir įsitikinkite, kad terminale įjungta virtuali aplinka.

1. Pridėkite šiuos importo sakinius po esamais importais:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Tai importuoja klases, naudojamas kalbos vertimui, ir `requests` biblioteką, kuri bus naudojama vėliau šioje pamokoje skambinant į Translator paslaugą.

1. Jūsų išmanusis laikmatis turės nustatytas 2 kalbas – serverio kalbą, kuri buvo naudojama LUIS mokymui (ta pati kalba taip pat naudojama pranešimams, skirtiems vartotojui), ir vartotojo kalbą. Atnaujinkite `language` kintamąjį, kad jis atitiktų vartotojo kalbą, ir pridėkite naują kintamąjį `server_language`, kuris nurodys kalbą, naudotą LUIS mokymui:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Pakeiskite `<user language>` į kalbos lokalės pavadinimą, kuria kalbėsite, pavyzdžiui, `fr-FR` prancūzų kalbai arba `zn-HK` kantoniečių kalbai.

    Pakeiskite `<server language>` į lokalės pavadinimą, naudotą LUIS mokymui.

    Palaikomų kalbų ir jų lokalės pavadinimų sąrašą galite rasti [Microsoft dokumentacijoje apie kalbų ir balsų palaikymą](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Jei nekalbate keliomis kalbomis, galite naudoti tokias paslaugas kaip [Bing Translate](https://www.bing.com/translator) arba [Google Translate](https://translate.google.com), kad išverstų iš jūsų pageidaujamos kalbos į pasirinktą kalbą. Šios paslaugos taip pat gali atkurti išversto teksto garsą. Atkreipkite dėmesį, kad kalbos atpažinimo įrankis gali ignoruoti kai kuriuos jūsų įrenginio garso išvesties signalus, todėl gali prireikti papildomo įrenginio išverstam tekstui atkurti.
    >
    > Pavyzdžiui, jei LUIS mokote anglų kalba, bet norite naudoti prancūzų kalbą kaip vartotojo kalbą, galite išversti sakinius, tokius kaip „set a 2 minute and 27 second timer“, iš anglų į prancūzų kalbą naudodami Bing Translate, tada naudoti **Listen translation** mygtuką, kad ištartumėte vertimą į mikrofoną.
    >
    > ![Bing Translate klausymo vertimo mygtukas](../../../../../translated_images/lt/bing-translate.348aa796d6efe2a9.webp)

1. Pakeiskite `recognizer_config` ir `recognizer` deklaracijas į šias:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Tai sukuria vertimo konfigūraciją, kad būtų atpažįstama kalba vartotojo kalba ir sukuriami vertimai vartotojo ir serverio kalbomis. Tada ši konfigūracija naudojama vertimo atpažinimo įrankiui sukurti – kalbos atpažinimo įrankiui, kuris gali išversti kalbos atpažinimo rezultatą į kelias kalbas.

    > 💁 Pradinė kalba turi būti nurodyta `target_languages`, kitaip negausite jokių vertimų.

1. Atnaujinkite `recognized` funkciją, pakeisdami visą funkcijos turinį šiuo:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Šis kodas patikrina, ar atpažinimo įvykis buvo suaktyvintas dėl to, kad kalba buvo išversta (šis įvykis gali būti suaktyvintas ir kitais atvejais, pavyzdžiui, kai kalba atpažįstama, bet neišverčiama). Jei kalba buvo išversta, ji suranda vertimą `args.result.translations` žodyne, kuris atitinka serverio kalbą.

    `args.result.translations` žodynas yra pagrįstas kalbos dalimi iš lokalės nustatymo, o ne visu nustatymu. Pavyzdžiui, jei prašote vertimo į `fr-FR` prancūzų kalbai, žodyne bus įrašas `fr`, o ne `fr-FR`.

    Išverstas tekstas tada siunčiamas į IoT Hub.

1. Paleiskite šį kodą, kad išbandytumėte vertimus. Įsitikinkite, kad jūsų funkcijų programa veikia, ir paprašykite laikmačio vartotojo kalba, kalbėdami ta kalba patys arba naudodami vertimo programėlę.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Išverskite tekstą naudodami Translator paslaugą

Kalbos paslauga nepalaiko teksto vertimo atgal į kalbą, todėl galite naudoti Translator paslaugą tekstui išversti. Ši paslauga turi REST API, kurią galite naudoti tekstui išversti.

### Užduotis – naudokite Translator resursą tekstui išversti

1. Pridėkite Translator API raktą po `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Pakeiskite `<key>` į jūsų Translator paslaugos resurso API raktą.

1. Virš `say` funkcijos apibrėžkite `translate_text` funkciją, kuri išvers tekstą iš serverio kalbos į vartotojo kalbą:

    ```python
    def translate_text(text):
    ```

1. Šioje funkcijoje apibrėžkite URL ir antraštes REST API skambučiui:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    Šios API URL nėra specifinis vietovei, vietovė perduodama kaip antraštė. API raktas naudojamas tiesiogiai, todėl, skirtingai nei kalbos paslaugoje, nereikia gauti prieigos rakto iš rakto išdavėjo API.

1. Po to apibrėžkite parametrus ir užklausos turinį:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` apibrėžia parametrus, perduodamus API skambučiui, nurodant iš ir į kalbas. Šis skambutis išvers tekstą iš `from` kalbos į `to` kalbą.

    `body` nurodo tekstą, kurį reikia išversti. Tai yra masyvas, nes vienu skambučiu galima išversti kelis teksto blokus.

1. Atlikite REST API skambutį ir gaukite atsakymą:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Atsakymas, kuris grįžta, yra JSON masyvas, kuriame yra vienas elementas su vertimais. Šis elementas turi masyvą su visų `body` perduotų elementų vertimais.

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

1. Grąžinkite `text` savybę iš pirmojo vertimo pirmame masyvo elemente:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Atnaujinkite `say` funkciją, kad išverstų tekstą prieš sugeneruojant SSML:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Šis kodas taip pat išspausdina originalią ir išverstą teksto versijas konsolėje.

1. Paleiskite savo kodą. Įsitikinkite, kad jūsų funkcijų programa veikia, ir paprašykite laikmačio vartotojo kalba, kalbėdami ta kalba patys arba naudodami vertimo programėlę.

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

    > 💁 Dėl skirtingų būdų, kaip galima pasakyti tą patį skirtingomis kalbomis, galite gauti vertimus, kurie šiek tiek skiriasi nuo pavyzdžių, kuriuos pateikėte LUIS. Jei taip nutinka, pridėkite daugiau pavyzdžių į LUIS, pertreniruokite ir vėl paskelbkite modelį.

> 💁 Šį kodą galite rasti [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) aplanke.

😀 Jūsų daugiakalbis laikmačio programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.