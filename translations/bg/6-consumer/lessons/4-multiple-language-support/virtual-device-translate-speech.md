# Превод на реч - Виртуално IoT устройство

В тази част от урока ще напишете код за превод на реч при преобразуване в текст с помощта на услугата за реч, след това ще преведете текста с услугата Translator, преди да генерирате говорен отговор.

## Използване на услугата за реч за превод на реч

Услугата за реч може да преобразува реч не само в текст на същия език, но и да преведе резултата на други езици.

### Задача - използване на услугата за реч за превод на реч

1. Отворете проекта `smart-timer` в VS Code и се уверете, че виртуалната среда е заредена в терминала.

1. Добавете следните изявления за импортиране под съществуващите импорти:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Това импортира класове, използвани за превод на реч, и библиотеката `requests`, която ще се използва за извикване на услугата Translator по-късно в този урок.

1. Вашият смарт таймер ще има зададени 2 езика - езикът на сървъра, който е използван за обучение на LUIS (същият език се използва и за създаване на съобщенията за потребителя), и езикът, на който говори потребителят. Актуализирайте променливата `language`, за да бъде езикът, на който ще говори потребителят, и добавете нова променлива, наречена `server_language`, за езика, използван за обучение на LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Заменете `<user language>` с името на локала за езика, на който ще говорите, например `fr-FR` за френски или `zn-HK` за кантонски.

    Заменете `<server language>` с името на локала за езика, използван за обучение на LUIS.

    Можете да намерите списък с поддържаните езици и техните имена на локали в [документацията за поддръжка на език и глас в Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ако не говорите няколко езика, можете да използвате услуга като [Bing Translate](https://www.bing.com/translator) или [Google Translate](https://translate.google.com), за да преведете от предпочитания от вас език на избран от вас език. Тези услуги могат да възпроизвеждат аудио на преведения текст. Имайте предвид, че разпознавачът на реч ще игнорира някои аудио изходи от вашето устройство, така че може да се наложи да използвате допълнително устройство, за да възпроизведете преведения текст.
    >
    > Например, ако обучите LUIS на английски, но искате да използвате френски като език на потребителя, можете да преведете изречения като "set a 2 minute and 27 second timer" от английски на френски с Bing Translate, след това използвайте бутона **Listen translation**, за да говорите превода в микрофона си.
    >
    > ![Бутонът Listen translation в Bing Translate](../../../../../translated_images/bg/bing-translate.348aa796d6efe2a9.webp)

1. Заменете декларациите `recognizer_config` и `recognizer` със следното:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Това създава конфигурация за превод, за да разпознае речта на езика на потребителя и да създаде преводи на езика на потребителя и сървъра. След това използва тази конфигурация, за да създаде разпознавател за превод - разпознавател на реч, който може да преведе резултата от разпознаването на реч на няколко езика.

    > 💁 Оригиналният език трябва да бъде посочен в `target_languages`, в противен случай няма да получите никакви преводи.

1. Актуализирайте функцията `recognized`, като замените цялото съдържание на функцията със следното:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Този код проверява дали събитието за разпознаване е било задействано, защото речта е била преведена (това събитие може да се задейства и в други случаи, като например когато речта е разпозната, но не е преведена). Ако речта е била преведена, тя намира превода в речника `args.result.translations`, който съответства на езика на сървъра.

    Речникът `args.result.translations` е ключиран според езиковата част на настройката за локал, а не цялата настройка. Например, ако поискате превод на `fr-FR` за френски, речникът ще съдържа запис за `fr`, а не за `fr-FR`.

    Преведеният текст след това се изпраща към IoT Hub.

1. Стартирайте този код, за да тествате преводите. Уверете се, че вашето приложение функционира, и поискайте таймер на езика на потребителя, като говорите на този език сами или използвате приложение за превод.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Превод на текст с услугата Translator

Услугата за реч не поддържа превод на текст обратно в реч, вместо това можете да използвате услугата Translator, за да преведете текста. Тази услуга има REST API, който можете да използвате за превод на текста.

### Задача - използване на ресурса Translator за превод на текст

1. Добавете API ключа на Translator под `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Заменете `<key>` с API ключа за вашия ресурс на услугата Translator.

1. Над функцията `say` дефинирайте функция `translate_text`, която ще превежда текст от езика на сървъра към езика на потребителя:

    ```python
    def translate_text(text):
    ```

1. Вътре в тази функция дефинирайте URL и заглавията за REST API извикването:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL за този API не е специфичен за местоположение, вместо това местоположението се предава като заглавие. API ключът се използва директно, така че за разлика от услугата за реч няма нужда да се получава токен за достъп от API за издаване на токени.

1. Под това дефинирайте параметрите и тялото за извикването:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` дефинира параметрите, които да се предадат на API извикването, като се предават езиците `from` и `to`. Това извикване ще преведе текст от езика `from` на езика `to`.

    `body` съдържа текста за превод. Това е масив, тъй като множество блокове текст могат да бъдат преведени в едно извикване.

1. Направете извикването към REST API и вземете отговора:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Отговорът, който се връща, е JSON масив, с един елемент, който съдържа преводите. Този елемент има масив за преводите на всички елементи, предадени в тялото.

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

1. Върнете свойството `text` от първия превод от първия елемент в масива:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Актуализирайте функцията `say`, за да преведе текста, който трябва да бъде казан, преди да се генерира SSML:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Този код също така отпечатва оригиналната и преведената версия на текста в конзолата.

1. Стартирайте вашия код. Уверете се, че вашето приложение функционира, и поискайте таймер на езика на потребителя, като говорите на този език сами или използвате приложение за превод.

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

    > 💁 Поради различните начини за изразяване на нещо на различни езици, може да получите преводи, които са малко различни от примерите, които сте дали на LUIS. Ако това е така, добавете повече примери към LUIS, обучете отново и публикувайте модела.

> 💁 Можете да намерите този код в папката [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Вашата многоезична програма за таймер беше успешна!

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматизираните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия изходен език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален човешки превод. Ние не носим отговорност за каквито и да е недоразумения или погрешни интерпретации, произтичащи от използването на този превод.