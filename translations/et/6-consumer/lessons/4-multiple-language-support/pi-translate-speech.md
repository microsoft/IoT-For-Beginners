<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-10-11T12:17:07+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "et"
}
-->
# Tõlgi kõne - Raspberry Pi

Selles õppetunni osas kirjutad koodi, et tõlkida teksti kasutades tõlketeenust.

## Teksti muutmine kõneks tõlketeenuse abil

Kõneteenuse REST API ei toeta otseseid tõlkeid, selle asemel saad kasutada Translator teenust, et tõlkida teksti, mis on loodud kõne-tekstiks teenuse abil, ja ka räägitud vastuse teksti. Sellel teenusel on REST API, mida saad kasutada teksti tõlkimiseks.

### Ülesanne - kasuta tõlketeenust teksti tõlkimiseks

1. Sinu nutikas taimeril on määratud kaks keelt - serveri keel, mida kasutati LUIS-i treenimiseks (sama keelt kasutatakse ka kasutajale sõnumite edastamiseks), ja kasutaja räägitav keel. Uuenda `language` muutujat, et see vastaks keelele, mida kasutaja räägib, ning lisa uus muutuja nimega `server_language` LUIS-i treenimiseks kasutatud keele jaoks:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Asenda `<user language>` keele lokaadi nimega, milles sa räägid, näiteks `fr-FR` prantsuse keele jaoks või `zn-HK` kantoni keele jaoks.

    Asenda `<server language>` keele lokaadi nimega, mida kasutati LUIS-i treenimiseks.

    Saad leida toetatud keelte ja nende lokaadi nimede loendi [Microsofti dokumentatsioonist keele ja hääle toe kohta](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Kui sa ei räägi mitut keelt, saad kasutada teenuseid nagu [Bing Translate](https://www.bing.com/translator) või [Google Translate](https://translate.google.com), et tõlkida oma eelistatud keelest mõnda teise keelde. Need teenused võivad ka mängida tõlgitud teksti heli.
    >
    > Näiteks, kui treenid LUIS-i inglise keeles, kuid soovid kasutada prantsuse keelt kasutaja keelena, saad tõlkida lauseid nagu "set a 2 minute and 27 second timer" inglise keelest prantsuse keelde Bing Translate'i abil, seejärel kasutada **Kuula tõlget** nuppu, et rääkida tõlge oma mikrofonisse.
    >
    > ![Kuula tõlget nupp Bing Translate'is](../../../../../translated_images/et/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Lisa tõlketeenuse API võti `speech_api_key` alla:

    ```python
    translator_api_key = '<key>'
    ```

    Asenda `<key>` tõlketeenuse ressursi API võtmega.

1. Defineeri `say` funktsiooni kohal `translate_text` funktsioon, mis tõlgib teksti serveri keelest kasutaja keelde:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Funktsioonile edastatakse lähte- ja sihtkeeled - sinu rakendus peab konverteerima kasutaja keele serveri keelde kõne tuvastamisel ja serveri keele kasutaja keelde räägitud tagasiside andmisel.

1. Selle funktsiooni sees defineeri URL ja päised REST API päringu jaoks:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    Selle API URL ei ole asukohaspetsiifiline, selle asemel edastatakse asukoht päises. API võtit kasutatakse otse, seega erinevalt kõneteenusest ei ole vaja hankida juurdepääsuluba tokeni väljastaja API-st.

1. Defineeri selle all päringu parameetrid ja keha:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` määratleb parameetrid, mida API päringule edastada, edastades lähte- ja sihtkeeled. See päring tõlgib teksti `from` keeles `to` keelde.

    `body` sisaldab tõlgitavat teksti. See on massiiv, kuna sama päringuga saab tõlkida mitu tekstilõiku.

1. Tee REST API päring ja saa vastus:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Tagastatud vastus on JSON massiiv, kus üks element sisaldab tõlkeid. See element sisaldab massiivi kõigi kehas edastatud elementide tõlgetega.

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

1. Tagasta esimese tõlke `test` omadus massiivi esimesest elemendist:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Uuenda `while True` tsüklit, et tõlkida teksti, mis on saadud `convert_speech_to_text` funktsioonist, kasutaja keelest serveri keelde:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    See kood prindib ka algse ja tõlgitud teksti versioonid konsooli.

1. Uuenda `say` funktsiooni, et tõlkida räägitav tekst serveri keelest kasutaja keelde:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    See kood prindib ka algse ja tõlgitud teksti versioonid konsooli.

1. Käivita oma kood. Veendu, et sinu funktsioonirakendus töötab, ja küsi taimerit kasutaja keeles, kas ise seda keelt rääkides või tõlketeenuse rakendust kasutades.

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

    > 💁 Erinevate keelte erinevate väljendusviiside tõttu võid saada tõlkeid, mis erinevad veidi näidetest, mida LUIS-ile andsid. Kui see juhtub, lisa LUIS-ile rohkem näiteid, treeni mudel uuesti ja avalda see uuesti.

> 💁 Selle koodi leiad [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) kaustast.

😀 Sinu mitmekeelne taimeriprogramm oli edukas!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.