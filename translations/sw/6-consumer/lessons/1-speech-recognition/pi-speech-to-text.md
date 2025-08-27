<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T21:23:54+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "sw"
}
-->
# Hotuba kwa maandishi - Raspberry Pi

Katika sehemu hii ya somo, utaandika msimbo wa kubadilisha hotuba katika sauti iliyorekodiwa kuwa maandishi kwa kutumia huduma ya hotuba.

## Tuma sauti kwa huduma ya hotuba

Sauti inaweza kutumwa kwa huduma ya hotuba kwa kutumia REST API. Ili kutumia huduma ya hotuba, kwanza unahitaji kuomba tokeni ya ufikiaji, kisha utumie tokeni hiyo kufikia REST API. Tokeni hizi za ufikiaji huisha baada ya dakika 10, kwa hivyo msimbo wako unapaswa kuziomba mara kwa mara ili kuhakikisha zinabaki kuwa za kisasa.

### Kazi - pata tokeni ya ufikiaji

1. Fungua mradi wa `smart-timer` kwenye Pi yako.

1. Ondoa kazi ya `play_audio`. Hii haitahitajika tena kwa sababu hutaki kipima muda chako cha kisasa kurudia kile ulichosema.

1. Ongeza uingizaji ufuatao juu ya faili ya `app.py`:

    ```python
    import requests
    ```

1. Ongeza msimbo ufuatao juu ya kitanzi cha `while True` ili kutangaza mipangilio fulani ya huduma ya hotuba:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Badilisha `<key>` na ufunguo wa API wa rasilimali yako ya huduma ya hotuba. Badilisha `<location>` na eneo ulilotumia ulipounda rasilimali ya huduma ya hotuba.

    Badilisha `<language>` na jina la eneo la lugha utakayozungumza, kwa mfano `en-GB` kwa Kiingereza, au `zn-HK` kwa Kantonese. Unaweza kupata orodha ya lugha zinazoungwa mkono na majina yao ya eneo katika [Nyaraka za msaada wa lugha na sauti kwenye Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Chini ya hii, ongeza kazi ifuatayo ili kupata tokeni ya ufikiaji:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Hii inaita sehemu ya kutoa tokeni, ikipitisha ufunguo wa API kama kichwa. Simu hii inarudisha tokeni ya ufikiaji ambayo inaweza kutumika kuita huduma za hotuba.

1. Chini ya hii, tangaza kazi ya kubadilisha hotuba katika sauti iliyorekodiwa kuwa maandishi kwa kutumia REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Ndani ya kazi hii, weka URL ya REST API na vichwa:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Hii inajenga URL kwa kutumia eneo la rasilimali ya huduma za hotuba. Kisha inajaza vichwa na tokeni ya ufikiaji kutoka kwa kazi ya `get_access_token`, pamoja na kiwango cha sampuli kilichotumika kurekodi sauti. Hatimaye inafafanua vigezo fulani vya kupitishwa na URL vinavyohusiana na lugha katika sauti.

1. Chini ya hii, ongeza msimbo ufuatao wa kuita REST API na kurudisha maandishi:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Hii inaita URL na kufafanua thamani ya JSON inayokuja katika majibu. Thamani ya `RecognitionStatus` katika majibu inaonyesha ikiwa simu iliweza kubadilisha hotuba kuwa maandishi kwa mafanikio, na ikiwa ni `Success` basi maandishi yanarudishwa kutoka kwa kazi, vinginevyo maandishi tupu yanarudishwa.

1. Juu ya kitanzi cha `while True:`, fafanua kazi ya kushughulikia maandishi yaliyorejeshwa kutoka huduma ya hotuba hadi maandishi. Kazi hii kwa sasa itachapisha tu maandishi kwenye koni.

    ```python
    def process_text(text):
        print(text)
    ```

1. Hatimaye badilisha simu ya `play_audio` katika kitanzi cha `while True` na simu ya kazi ya `convert_speech_to_text`, ukipitisha maandishi kwa kazi ya `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Endesha msimbo. Bonyeza kitufe na zungumza kwenye kipaza sauti. Achilia kitufe unapomaliza, na sauti itabadilishwa kuwa maandishi na kuchapishwa kwenye koni.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Jaribu aina tofauti za sentensi, pamoja na sentensi ambapo maneno yana sauti sawa lakini yana maana tofauti. Kwa mfano, ikiwa unazungumza kwa Kiingereza, sema 'I want to buy two bananas and an apple too', na angalia jinsi itakavyotumia to, two na too kwa usahihi kulingana na muktadha wa neno, si sauti yake tu.

> 💁 Unaweza kupata msimbo huu katika folda ya [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Programu yako ya kubadilisha hotuba kuwa maandishi imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.