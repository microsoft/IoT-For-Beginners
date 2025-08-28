<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-28T12:57:32+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "sr"
}
-->
# Претварање говора у текст - Raspberry Pi

У овом делу лекције, написаћете код за претварање говора из снимљеног аудио записа у текст користећи услугу за говор.

## Слање аудио записа услузи за говор

Аудио запис се може послати услузи за говор користећи REST API. Да бисте користили услугу за говор, прво морате затражити приступни токен, а затим користити тај токен за приступ REST API-ју. Ови приступни токени истичу након 10 минута, па ваш код треба редовно да их захтева како би увек били ажурни.

### Задатак - добијање приступног токена

1. Отворите пројекат `smart-timer` на вашем Raspberry Pi-ју.

1. Уклоните функцију `play_audio`. Ова функција више није потребна јер не желите да паметни тајмер понавља оно што сте рекли.

1. Додајте следећи импорт на врх датотеке `app.py`:

    ```python
    import requests
    ```

1. Додајте следећи код изнад `while True` петље да бисте дефинисали нека подешавања за услугу за говор:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Замените `<key>` са API кључем за ваш ресурс услуге за говор. Замените `<location>` са локацијом коју сте користили приликом креирања ресурса услуге за говор.

    Замените `<language>` са именом локала за језик на којем ћете говорити, на пример `en-GB` за енглески или `zn-HK` за кантонски. Листу подржаних језика и њихових локала можете пронаћи у [документацији о подршци за језик и глас на Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Испод овога, додајте следећу функцију за добијање приступног токена:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Ова функција позива крајњу тачку за издавање токена, прослеђујући API кључ као хедер. Овај позив враћа приступни токен који се може користити за позивање услуга за говор.

1. Испод овога, дефинишите функцију за претварање говора из снимљеног аудио записа у текст користећи REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Унутар ове функције, подесите URL и хедере за REST API:

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

    Ово гради URL користећи локацију ресурса услуге за говор. Затим попуњава хедере са приступним токеном из функције `get_access_token`, као и са sample rate-ом који је коришћен за снимање аудио записа. На крају дефинише неке параметре који се прослеђују са URL-ом, а који садрже језик у аудио запису.

1. Испод овога, додајте следећи код за позивање REST API-ја и добијање текста:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Овај код позива URL и декодира JSON вредност која долази у одговору. Вредност `RecognitionStatus` у одговору указује да ли је позив успешно претворио говор у текст, и ако је ова вредност `Success`, текст се враћа из функције, у супротном се враћа празан стринг.

1. Изнад `while True:` петље, дефинишите функцију за обраду текста који је враћен из услуге за претварање говора у текст. Ова функција ће за сада само исписивати текст на конзолу.

    ```python
    def process_text(text):
        print(text)
    ```

1. На крају замените позив функције `play_audio` у `while True` петљи са позивом функције `convert_speech_to_text`, прослеђујући текст функцији `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Покрените код. Притисните дугме и говорите у микрофон. Отпустите дугме када завршите, и аудио запис ће бити претворен у текст и исписан на конзолу.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Испробајте различите типове реченица, као и реченице где речи звуче исто, али имају различита значења. На пример, ако говорите на енглеском, реците 'I want to buy two bananas and an apple too', и приметите како ће користити исправне to, two и too на основу контекста речи, а не само њиховог звука.

> 💁 Овај код можете пронаћи у [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) фолдеру.

😀 Ваш програм за претварање говора у текст је успешно завршен!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати меродавним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.