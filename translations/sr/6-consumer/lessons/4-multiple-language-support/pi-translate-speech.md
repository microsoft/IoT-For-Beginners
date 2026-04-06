# Превод говора - Raspberry Pi

У овом делу лекције, написаћете код за превођење текста користећи услугу преводиоца.

## Претварање текста у говор помоћу услуге преводиоца

REST API услуге говора не подржава директне преводе, али можете користити услугу Преводиоца да преведете текст који је генерисан помоћу услуге претварања говора у текст, као и текст одговора који се изговара. Ова услуга има REST API који можете користити за превођење текста.

### Задатак - користите ресурс преводиоца за превођење текста

1. Ваш паметни тајмер ће имати подешена два језика - језик сервера који је коришћен за тренирање LUIS-а (тај исти језик се користи и за креирање порука које се изговарају кориснику) и језик који говори корисник. Ажурирајте променљиву `language` тако да буде језик који ће корисник говорити, и додајте нову променљиву под називом `server_language` за језик који је коришћен за тренирање LUIS-а:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Замените `<user language>` са именом локала за језик на коме ћете говорити, на пример `fr-FR` за француски или `zn-HK` за кантонски.

    Замените `<server language>` са именом локала за језик који је коришћен за тренирање LUIS-а.

    Листу подржаних језика и њихових имена локала можете пронаћи у [документацији о подршци за језике и гласове на Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ако не говорите више језика, можете користити услугу као што је [Bing Translate](https://www.bing.com/translator) или [Google Translate](https://translate.google.com) за превођење са вашег омиљеног језика на језик по вашем избору. Ове услуге могу репродуковати аудио преведеног текста.
    >
    > На пример, ако сте тренирали LUIS на енглеском, али желите да користите француски као језик корисника, можете превести реченице попут "set a 2 minute and 27 second timer" са енглеског на француски користећи Bing Translate, а затим користити дугме **Listen translation** да изговорите превод у ваш микрофон.
    >
    > ![Дугме за слушање превода на Bing Translate](../../../../../translated_images/sr/bing-translate.348aa796d6efe2a9.webp)

1. Додајте API кључ преводиоца испод `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Замените `<key>` са API кључем за ваш ресурс услуге преводиоца.

1. Изнад функције `say`, дефинишите функцију `translate_text` која ће преводити текст са језика сервера на језик корисника:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Језици "from" и "to" се прослеђују овој функцији - ваша апликација треба да конвертује са језика корисника на језик сервера када препознаје говор, и са језика сервера на језик корисника када пружа изговорени одговор.

1. Унутар ове функције, дефинишите URL и заглавља за REST API позив:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL за овај API није специфичан за локацију, већ се локација прослеђује као заглавље. API кључ се користи директно, тако да за разлику од услуге говора, није потребно добити приступни токен од API-ја за издавање токена.

1. Испод овога дефинишите параметре и тело за позив:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` дефинише параметре који се прослеђују API позиву, укључујући језике "from" и "to". Овај позив ће превести текст са језика "from" на језик "to".

    `body` садржи текст који треба превести. Ово је низ, јер се више блокова текста може превести у истом позиву.

1. Направите позив REST API-ју и добијте одговор:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Одговор који се враћа је JSON низ, са једним елементом који садржи преводе. Овај елемент има низ за преводе свих ставки прослеђених у телу.

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

1. Вратите својство `test` из првог превода из првог елемента у низу:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Ажурирајте `while True` петљу да преведе текст из позива `convert_speech_to_text` са језика корисника на језик сервера:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Овај код такође штампа оригиналну и преведену верзију текста у конзоли.

1. Ажурирајте функцију `say` да преведе текст који треба изговорити са језика сервера на језик корисника:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Овај код такође штампа оригиналну и преведену верзију текста у конзоли.

1. Покрените свој код. Уверите се да ваша функцијска апликација ради и затражите тајмер на језику корисника, било тако што ћете сами говорити тај језик или користећи апликацију за превођење.

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

    > 💁 Због различитих начина изражавања на различитим језицима, можете добити преводе који се мало разликују од примера које сте дали LUIS-у. Ако је то случај, додајте више примера у LUIS, поново обучите и поново објавите модел.

> 💁 Овај код можете пронаћи у [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) фасцикли.

😀 Ваш програм за мултијезички тајмер је био успешан!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати ауторитативним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.