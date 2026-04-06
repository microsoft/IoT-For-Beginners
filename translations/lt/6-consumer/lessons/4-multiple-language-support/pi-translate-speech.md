# Išversti kalbą - Raspberry Pi

Šioje pamokos dalyje rašysite kodą, skirtą tekstui versti naudojant vertimo paslaugą.

## Konvertuokite tekstą į kalbą naudodami vertimo paslaugą

Kalbos paslaugos REST API nepalaiko tiesioginių vertimų, tačiau galite naudoti Vertėjo paslaugą, kad išverstumėte tekstą, sugeneruotą kalbos į tekstą paslaugos, ir atsakymo tekstą. Ši paslauga turi REST API, kurią galite naudoti tekstui versti.

### Užduotis - naudokite vertėjo išteklius tekstui versti

1. Jūsų išmanusis laikmatis turės nustatytas 2 kalbas - serverio kalbą, kuri buvo naudojama LUIS mokymui (ta pati kalba taip pat naudojama pranešimams vartotojui kurti), ir vartotojo kalbą. Atnaujinkite `language` kintamąjį, kad jis atitiktų kalbą, kuria kalbės vartotojas, ir pridėkite naują kintamąjį, pavadintą `server_language`, kuris nurodys kalbą, naudotą LUIS mokymui:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Pakeiskite `<user language>` į kalbos lokalės pavadinimą, kuria kalbėsite, pavyzdžiui, `fr-FR` prancūzų kalbai arba `zn-HK` kantoniečių kalbai.

    Pakeiskite `<server language>` į lokalės pavadinimą, naudotą LUIS mokymui.

    Palaikomų kalbų ir jų lokalės pavadinimų sąrašą galite rasti [Microsoft dokumentacijoje apie kalbų ir balsų palaikymą](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Jei nekalbate keliomis kalbomis, galite naudoti tokias paslaugas kaip [Bing Translate](https://www.bing.com/translator) arba [Google Translate](https://translate.google.com), kad išverstumėte iš savo pageidaujamos kalbos į pasirinktą kalbą. Šios paslaugos taip pat gali atkurti išverstą tekstą kaip garsą.
    >
    > Pavyzdžiui, jei LUIS mokote anglų kalba, bet norite naudoti prancūzų kalbą kaip vartotojo kalbą, galite išversti sakinius, tokius kaip „nustatykite 2 minučių ir 27 sekundžių laikmatį“, iš anglų į prancūzų kalbą naudodami Bing Translate, tada naudokite mygtuką **Klausyti vertimo**, kad įrašytumėte vertimą į mikrofoną.
    >
    > ![Mygtukas „Klausyti vertimo“ Bing Translate](../../../../../translated_images/lt/bing-translate.348aa796d6efe2a9.webp)

1. Pridėkite vertėjo API raktą po `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Pakeiskite `<key>` į savo vertėjo paslaugos ištekliaus API raktą.

1. Virš `say` funkcijos apibrėžkite `translate_text` funkciją, kuri išvers tekstą iš serverio kalbos į vartotojo kalbą:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Šiai funkcijai perduodamos pradinė ir tikslinė kalbos - jūsų programa turi konvertuoti iš vartotojo kalbos į serverio kalbą, kai atpažįstama kalba, ir iš serverio kalbos į vartotojo kalbą, kai pateikiamas atsakymas.

1. Šios funkcijos viduje apibrėžkite URL ir antraštes REST API užklausai:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    Šios API URL nėra specifinis vietovei, vietovė perduodama kaip antraštė. API raktas naudojamas tiesiogiai, todėl, skirtingai nei kalbos paslaugoje, nereikia gauti prieigos žetono iš žetonų išdavimo API.

1. Po to apibrėžkite parametrus ir užklausos turinį:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` apibrėžia parametrus, perduodamus API užklausai, nurodant pradinę ir tikslinę kalbas. Ši užklausa išvers tekstą iš pradinės kalbos į tikslinę kalbą.

    `body` nurodo tekstą, kurį reikia išversti. Tai yra masyvas, nes vienoje užklausoje galima išversti kelis teksto blokus.

1. Atlikite REST API užklausą ir gaukite atsakymą:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Atsakymas yra JSON masyvas, kuriame yra vienas elementas su vertimais. Šis elementas turi masyvą su visų `body` perduotų elementų vertimais.

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

1. Grąžinkite pirmojo masyvo elemento pirmojo vertimo `test` savybę:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Atnaujinkite `while True` ciklą, kad išverstų tekstą iš `convert_speech_to_text` funkcijos iš vartotojo kalbos į serverio kalbą:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Šis kodas taip pat išspausdina pradinę ir išverstą teksto versijas konsolėje.

1. Atnaujinkite `say` funkciją, kad išverstų tekstą iš serverio kalbos į vartotojo kalbą:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Šis kodas taip pat išspausdina pradinę ir išverstą teksto versijas konsolėje.

1. Paleiskite savo kodą. Įsitikinkite, kad jūsų funkcijų programa veikia, ir paprašykite laikmačio vartotojo kalba, kalbėdami ta kalba patys arba naudodami vertimo programėlę.

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

    > 💁 Dėl skirtingų sakinių formuluočių skirtingomis kalbomis galite gauti vertimus, kurie šiek tiek skiriasi nuo pavyzdžių, kuriuos pateikėte LUIS. Jei taip nutinka, pridėkite daugiau pavyzdžių į LUIS, pertreniruokite ir vėl paskelbkite modelį.

> 💁 Šį kodą galite rasti [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) aplanke.

😀 Jūsų daugiakalbis laikmatis buvo sėkmingas!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.