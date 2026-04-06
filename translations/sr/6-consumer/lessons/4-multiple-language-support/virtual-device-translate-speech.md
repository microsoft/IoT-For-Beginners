# Превод говора - Виртуелни IoT уређај

У овом делу лекције, написаћете код за превођење говора приликом конверзије у текст користећи услугу за говор, а затим ћете превести текст користећи услугу Translator пре него што генеришете одговор у говору.

## Коришћење услуге за говор за превођење говора

Услуга за говор може узети говор и не само да га конвертује у текст на истом језику, већ и да преведе излаз на друге језике.

### Задатак - коришћење услуге за говор за превођење говора

1. Отворите пројекат `smart-timer` у VS Code и уверите се да је виртуелно окружење учитано у терминалу.

1. Додајте следеће изјаве за увоз испод постојећих увоза:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Ово увози класе које се користе за превођење говора и библиотеку `requests` која ће се користити за позив услуге Translator касније у овој лекцији.

1. Ваш паметни тајмер ће имати постављена два језика - језик сервера који је коришћен за тренирање LUIS-а (исти језик се такође користи за креирање порука које се говоре кориснику) и језик који говори корисник. Ажурирајте променљиву `language` да буде језик који ће корисник говорити и додајте нову променљиву `server_language` за језик који је коришћен за тренирање LUIS-а:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Замените `<user language>` именом локала за језик који ћете говорити, на пример `fr-FR` за француски или `zn-HK` за кантонски.

    Замените `<server language>` именом локала за језик који је коришћен за тренирање LUIS-а.

    Листу подржаних језика и њихових имена локала можете пронаћи у [документацији о подршци за језике и гласове на Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ако не говорите више језика, можете користити услугу као што је [Bing Translate](https://www.bing.com/translator) или [Google Translate](https://translate.google.com) за превођење са вашег омиљеног језика на језик по вашем избору. Ове услуге могу репродуковати аудио преведеног текста. Имајте на уму да препознавач говора може игнорисати неке аудио излазе са вашег уређаја, па ће вам можда бити потребан додатни уређај за репродукцију преведеног текста.
    >
    > На пример, ако тренирате LUIS на енглеском, али желите да користите француски као језик корисника, можете превести реченице као што је "подеси тајмер на 2 минута и 27 секунди" са енглеског на француски користећи Bing Translate, а затим користити дугме **Listen translation** да изговорите превод у ваш микрофон.
    >
    > ![Дугме за слушање превода на Bing Translate](../../../../../translated_images/sr/bing-translate.348aa796d6efe2a9.webp)

1. Замените декларације `recognizer_config` и `recognizer` следећим:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Ово креира конфигурацију за превођење која препознаје говор на језику корисника и креира преводе на језику корисника и сервера. Затим користи ову конфигурацију за креирање препознавача превода - препознавача говора који може превести излаз препознавања говора на више језика.

    > 💁 Оригинални језик мора бити наведен у `target_languages`, иначе нећете добити никакве преводе.

1. Ажурирајте функцију `recognized`, заменивши цео садржај функције следећим:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Овај код проверава да ли је догађај препознавања активиран јер је говор преведен (овај догађај може бити активиран у другим случајевима, као што је када је говор препознат али није преведен). Ако је говор преведен, проналази превод у речнику `args.result.translations` који одговара језику сервера.

    Речник `args.result.translations` је кључан на основу језичког дела подешавања локала, а не целог подешавања. На пример, ако затражите превод на `fr-FR` за француски, речник ће садржати унос за `fr`, а не `fr-FR`.

    Преведени текст се затим шаље на IoT Hub.

1. Покрените овај код да тестирате преводе. Уверите се да ваша функција апликације ради и затражите тајмер на језику корисника, било говорећи тај језик сами или користећи апликацију за превођење.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Превод текста користећи услугу Translator

Услуга за говор не подржава превођење текста назад у говор, уместо тога можете користити услугу Translator за превођење текста. Ова услуга има REST API који можете користити за превођење текста.

### Задатак - коришћење ресурса Translator за превођење текста

1. Додајте API кључ за Translator испод `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Замените `<key>` API кључем за ваш ресурс услуге Translator.

1. Изнад функције `say`, дефинишите функцију `translate_text` која ће преводити текст са језика сервера на језик корисника:

    ```python
    def translate_text(text):
    ```

1. Унутар ове функције, дефинишите URL и заглавља за REST API позив:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL за овај API није специфичан за локацију, уместо тога локација се прослеђује као заглавље. API кључ се користи директно, тако да за разлику од услуге за говор нема потребе за добијањем приступног токена из API-а за издавање токена.

1. Испод овога дефинишите параметре и тело за позив:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` дефинише параметре који се прослеђују API позиву, прослеђујући језике `from` и `to`. Овај позив ће превести текст са језика `from` на језик `to`.

    `body` садржи текст за превођење. Ово је низ, јер се више блокова текста може превести у истом позиву.

1. Направите позив REST API-ју и добијте одговор:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Одговор који се враћа је JSON низ, са једним ставком који садржи преводе. Овај ставак има низ за преводе свих ставки прослеђених у телу.

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

1. Вратите својство `text` из првог превода из прве ставке у низу:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Ажурирајте функцију `say` да преведе текст који треба изговорити пре него што се генерише SSML:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Овај код такође штампа оригиналну и преведену верзију текста у конзолу.

1. Покрените свој код. Уверите се да ваша функција апликације ради и затражите тајмер на језику корисника, било говорећи тај језик сами или користећи апликацију за превођење.

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

    > 💁 Због различитих начина изражавања у различитим језицима, можете добити преводе који се мало разликују од примера које сте дали LUIS-у. Ако је то случај, додајте више примера у LUIS, поново обучите и затим поново објавите модел.

> 💁 Овај код можете пронаћи у [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) фасцикли.

😀 Ваш програм за мултијезични тајмер је био успешан!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако настојимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на изворном језику треба сматрати меродавним извором. За критичне информације препоручује се професионални превод од стране људи. Не сносимо одговорност за било каква погрешна тумачења или неспоразуме који могу произаћи из коришћења овог превода.