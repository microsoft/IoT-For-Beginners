<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-27T21:33:15+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "sw"
}
-->
# Tafsiri hotuba - Raspberry Pi

Katika sehemu hii ya somo, utaandika msimbo wa kutafsiri maandishi ukitumia huduma ya mtafsiri.

## Badilisha maandishi kuwa hotuba ukitumia huduma ya mtafsiri

API ya REST ya huduma ya hotuba haiungi mkono tafsiri za moja kwa moja, badala yake unaweza kutumia huduma ya Translator kutafsiri maandishi yanayotokana na huduma ya hotuba hadi maandishi, na maandishi ya majibu yanayozungumzwa. Huduma hii ina API ya REST unayoweza kutumia kutafsiri maandishi.

### Kazi - tumia rasilimali ya mtafsiri kutafsiri maandishi

1. Kipima muda chako mahiri kitakuwa na lugha 2 zilizowekwa - lugha ya seva iliyotumika kufundisha LUIS (lugha hiyo hiyo pia hutumika kuunda ujumbe wa kuzungumza na mtumiaji), na lugha inayozungumzwa na mtumiaji. Sasisha kigezo cha `language` kuwa lugha itakayozungumzwa na mtumiaji, na ongeza kigezo kipya kinachoitwa `server_language` kwa lugha iliyotumika kufundisha LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Badilisha `<user language>` na jina la eneo kwa lugha utakayozungumza, kwa mfano `fr-FR` kwa Kifaransa, au `zn-HK` kwa Kantonese.

    Badilisha `<server language>` na jina la eneo kwa lugha iliyotumika kufundisha LUIS.

    Unaweza kupata orodha ya lugha zinazoungwa mkono na majina yao ya eneo katika [Nyaraka za msaada wa lugha na sauti kwenye Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ikiwa huzungumzi lugha nyingi, unaweza kutumia huduma kama [Bing Translate](https://www.bing.com/translator) au [Google Translate](https://translate.google.com) kutafsiri kutoka lugha unayopendelea hadi lugha unayochagua. Huduma hizi zinaweza pia kucheza sauti ya maandishi yaliyotafsiriwa.
    >
    > Kwa mfano, ikiwa umefundisha LUIS kwa Kiingereza, lakini unataka kutumia Kifaransa kama lugha ya mtumiaji, unaweza kutafsiri sentensi kama "set a 2 minute and 27 second timer" kutoka Kiingereza hadi Kifaransa ukitumia Bing Translate, kisha tumia kitufe cha **Listen translation** kuzungumza tafsiri hiyo kwenye kipaza sauti chako.
    >
    > ![Kitufe cha kusikiliza tafsiri kwenye Bing Translate](../../../../../translated_images/sw/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Ongeza ufunguo wa API wa mtafsiri chini ya `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Badilisha `<key>` na ufunguo wa API wa rasilimali yako ya huduma ya mtafsiri.

1. Juu ya kazi ya `say`, fafanua kazi ya `translate_text` ambayo itatafsiri maandishi kutoka lugha ya seva hadi lugha ya mtumiaji:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Lugha za kutoka na kwenda zinapokelewa na kazi hii - programu yako inahitaji kubadilisha kutoka lugha ya mtumiaji hadi lugha ya seva wakati wa kutambua hotuba, na kutoka lugha ya seva hadi lugha ya mtumiaji wakati wa kutoa maoni ya hotuba.

1. Ndani ya kazi hii, fafanua URL na vichwa vya API ya REST:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL ya API hii si maalum kwa eneo, badala yake eneo linapokelewa kama kichwa. Ufunguo wa API unatumika moja kwa moja, kwa hivyo tofauti na huduma ya hotuba, hakuna haja ya kupata tokeni ya ufikiaji kutoka kwa API ya mtoaji wa tokeni.

1. Chini ya hii, fafanua vigezo na mwili wa simu:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` hufafanua vigezo vya kupitisha kwa simu ya API, ikipitia lugha za kutoka na kwenda. Simu hii itatafsiri maandishi katika lugha ya `from` hadi lugha ya `to`.

    `body` inajumuisha maandishi ya kutafsiri. Hii ni safu, kwani vitalu vingi vya maandishi vinaweza kutafsiriwa katika simu moja.

1. Fanya simu ya API ya REST, na upate majibu:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Jibu linalorudi ni safu ya JSON, na kipengele kimoja kinachojumuisha tafsiri. Kipengele hiki kina safu ya tafsiri za vitu vyote vilivyopitishwa kwenye mwili.

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

1. Rudisha mali ya `test` kutoka kwa tafsiri ya kwanza kutoka kipengele cha kwanza kwenye safu:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Sasisha kitanzi cha `while True` kutafsiri maandishi kutoka kwa simu ya `convert_speech_to_text` kutoka lugha ya mtumiaji hadi lugha ya seva:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Msimbo huu pia unachapisha matoleo ya awali na yaliyotafsiriwa ya maandishi kwenye koni.

1. Sasisha kazi ya `say` kutafsiri maandishi ya kusema kutoka lugha ya seva hadi lugha ya mtumiaji:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Msimbo huu pia unachapisha matoleo ya awali na yaliyotafsiriwa ya maandishi kwenye koni.

1. Endesha msimbo wako. Hakikisha programu yako ya kazi inafanya kazi, na omba kipima muda kwa lugha ya mtumiaji, ama kwa kuzungumza lugha hiyo mwenyewe, au kwa kutumia programu ya tafsiri.

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

    > 💁 Kutokana na njia tofauti za kusema kitu katika lugha tofauti, unaweza kupata tafsiri ambazo ni tofauti kidogo na mifano uliyotoa kwa LUIS. Ikiwa ni hivyo, ongeza mifano zaidi kwa LUIS, fundisha tena kisha chapisha tena mfano huo.

> 💁 Unaweza kupata msimbo huu katika [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) folda.

😀 Programu yako ya kipima muda cha lugha nyingi imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.