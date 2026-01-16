<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-27T21:34:23+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "sw"
}
-->
# Tafsiri Hotuba - Kifaa Pepe cha IoT

Katika sehemu hii ya somo, utaandika msimbo wa kutafsiri hotuba wakati wa kuibadilisha kuwa maandishi kwa kutumia huduma ya hotuba, kisha kutafsiri maandishi kwa kutumia huduma ya Translator kabla ya kutoa majibu kwa sauti.

## Tumia huduma ya hotuba kutafsiri hotuba

Huduma ya hotuba inaweza kuchukua hotuba na sio tu kuibadilisha kuwa maandishi kwa lugha ile ile, bali pia kutafsiri matokeo hayo kwa lugha nyingine.

### Kazi - tumia huduma ya hotuba kutafsiri hotuba

1. Fungua mradi wa `smart-timer` kwenye VS Code, na hakikisha mazingira pepe yamewashwa kwenye terminal.

1. Ongeza kauli zifuatazo za uingizaji chini ya uingizaji uliopo:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Hii inaingiza madarasa yanayotumika kutafsiri hotuba, na maktaba ya `requests` ambayo itatumika kufanya simu kwa huduma ya Translator baadaye katika somo hili.

1. Kipima muda chako cha smart kitakuwa na lugha 2 zilizowekwa - lugha ya seva iliyotumika kufundisha LUIS (lugha hiyo hiyo pia hutumika kujenga ujumbe wa kuzungumza na mtumiaji), na lugha inayozungumzwa na mtumiaji. Sasisha kigezo cha `language` kuwa lugha itakayozungumzwa na mtumiaji, na ongeza kigezo kipya kinachoitwa `server_language` kwa lugha iliyotumika kufundisha LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Badilisha `<user language>` na jina la eneo la lugha utakayozungumza, kwa mfano `fr-FR` kwa Kifaransa, au `zn-HK` kwa Kantonese.

    Badilisha `<server language>` na jina la eneo la lugha iliyotumika kufundisha LUIS.

    Unaweza kupata orodha ya lugha zinazoungwa mkono na majina yao ya eneo katika [Nyaraka za msaada wa lugha na sauti kwenye Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ikiwa huzungumzi lugha nyingi, unaweza kutumia huduma kama [Bing Translate](https://www.bing.com/translator) au [Google Translate](https://translate.google.com) kutafsiri kutoka lugha unayopendelea kwenda lugha unayochagua. Huduma hizi zinaweza pia kucheza sauti ya maandishi yaliyotafsiriwa. Kumbuka kuwa kitambuzi cha hotuba kitaepuza baadhi ya sauti zinazotoka kwenye kifaa chako, kwa hivyo unaweza kuhitaji kutumia kifaa kingine kucheza maandishi yaliyotafsiriwa.
    >
    > Kwa mfano, ikiwa umefundisha LUIS kwa Kiingereza, lakini unataka kutumia Kifaransa kama lugha ya mtumiaji, unaweza kutafsiri sentensi kama "set a 2 minute and 27 second timer" kutoka Kiingereza kwenda Kifaransa kwa kutumia Bing Translate, kisha tumia kitufe cha **Listen translation** kuzungumza tafsiri hiyo kwenye kipaza sauti chako.
    >
    > ![Kitufe cha kusikiliza tafsiri kwenye Bing Translate](../../../../../translated_images/sw/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Badilisha matamko ya `recognizer_config` na `recognizer` na yafuatayo:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Hii inaunda usanidi wa tafsiri kutambua hotuba kwa lugha ya mtumiaji, na kuunda tafsiri kwa lugha ya mtumiaji na lugha ya seva. Kisha inatumia usanidi huu kuunda kitambuzi cha tafsiri - kitambuzi cha hotuba kinachoweza kutafsiri matokeo ya utambuzi wa hotuba kwa lugha nyingi.

    > 💁 Lugha ya asili inahitaji kuelezwa katika `target_languages`, vinginevyo hutapata tafsiri yoyote.

1. Sasisha kazi ya `recognized`, ukibadilisha yaliyomo yote ya kazi hiyo na yafuatayo:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Msimbo huu unakagua kuona kama tukio lililotambuliwa lilizinduliwa kwa sababu hotuba ilitafsiriwa (tukio hili linaweza kuzinduliwa nyakati nyingine, kama wakati hotuba inapotambuliwa lakini haikutafsiriwa). Ikiwa hotuba ilitafsiriwa, inapata tafsiri katika kamusi ya `args.result.translations` inayolingana na lugha ya seva.

    Kamusi ya `args.result.translations` inatumia sehemu ya lugha ya mpangilio wa eneo, si mpangilio mzima. Kwa mfano, ikiwa unaomba tafsiri kwa `fr-FR` kwa Kifaransa, kamusi itakuwa na kipengele kwa `fr`, si `fr-FR`.

    Maandishi yaliyotafsiriwa kisha yanatumwa kwa IoT Hub.

1. Endesha msimbo huu kujaribu tafsiri. Hakikisha programu yako ya kazi inafanya kazi, na omba kipima muda kwa lugha ya mtumiaji, ama kwa kuzungumza lugha hiyo mwenyewe, au kwa kutumia programu ya tafsiri.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Tafsiri maandishi kwa kutumia huduma ya Translator

Huduma ya hotuba haiungi mkono tafsiri ya maandishi kurudi kuwa hotuba, badala yake unaweza kutumia huduma ya Translator kutafsiri maandishi. Huduma hii ina REST API unayoweza kutumia kutafsiri maandishi.

### Kazi - tumia rasilimali ya Translator kutafsiri maandishi

1. Ongeza ufunguo wa API wa Translator chini ya `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Badilisha `<key>` na ufunguo wa API wa rasilimali yako ya huduma ya Translator.

1. Juu ya kazi ya `say`, fafanua kazi ya `translate_text` ambayo itatafsiri maandishi kutoka lugha ya seva kwenda lugha ya mtumiaji:

    ```python
    def translate_text(text):
    ```

1. Ndani ya kazi hii, fafanua URL na vichwa vya REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL ya API hii si maalum kwa eneo, badala yake eneo linapitiwa kama kichwa. Ufunguo wa API unatumika moja kwa moja, kwa hivyo tofauti na huduma ya hotuba, hakuna haja ya kupata tokeni ya ufikiaji kutoka kwa API ya mtoaji wa tokeni.

1. Chini ya hii fafanua vigezo na mwili wa simu:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` inafafanua vigezo vya kupitisha kwa simu ya API, ikipitia lugha ya kutoka na ya kwenda. Simu hii itatafsiri maandishi katika lugha ya `from` kwenda lugha ya `to`.

    `body` ina maandishi ya kutafsiri. Hii ni safu, kwani vitalu vingi vya maandishi vinaweza kutafsiriwa katika simu moja.

1. Fanya simu kwa REST API, na upate majibu:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Jibu linalorudi ni safu ya JSON, na kipengele kimoja kinachobeba tafsiri. Kipengele hiki kina safu ya tafsiri za vitu vyote vilivyopitishwa kwenye mwili.

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

1. Rudisha mali ya `text` kutoka tafsiri ya kwanza kutoka kipengele cha kwanza kwenye safu:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Sasisha kazi ya `say` kutafsiri maandishi ya kusema kabla ya SSML kuzalishwa:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Msimbo huu pia unachapisha matoleo ya asili na yaliyotafsiriwa ya maandishi kwenye console.

1. Endesha msimbo wako. Hakikisha programu yako ya kazi inafanya kazi, na omba kipima muda kwa lugha ya mtumiaji, ama kwa kuzungumza lugha hiyo mwenyewe, au kwa kutumia programu ya tafsiri.

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

    > 💁 Kutokana na njia tofauti za kusema kitu katika lugha tofauti, unaweza kupata tafsiri ambazo ni tofauti kidogo na mifano uliyotoa kwa LUIS. Ikiwa ni hivyo, ongeza mifano zaidi kwa LUIS, fundisha tena kisha chapisha tena mfano huo.

> 💁 Unaweza kupata msimbo huu katika folda ya [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Programu yako ya kipima muda cha lugha nyingi imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.