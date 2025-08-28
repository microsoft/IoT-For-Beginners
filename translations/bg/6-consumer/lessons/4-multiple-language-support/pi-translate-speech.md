<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-28T09:28:49+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "bg"
}
-->
# Превод на реч - Raspberry Pi

В тази част от урока ще напишете код за превод на текст, използвайки услугата за превод.

## Преобразуване на текст в реч с помощта на услугата за превод

REST API на услугата за реч не поддържа директни преводи. Вместо това можете да използвате услугата Translator, за да преведете текста, генериран от услугата за преобразуване на реч в текст, както и текста на отговора, който ще бъде изговорен. Тази услуга разполага с REST API, който можете да използвате за превод на текст.

### Задача - използване на ресурса за превод за превод на текст

1. Вашият умен таймер ще има зададени 2 езика - езикът на сървъра, който е използван за обучение на LUIS (същият език се използва и за създаване на съобщенията, които ще се изговарят на потребителя), и езикът, който говори потребителят. Актуализирайте променливата `language`, за да бъде езикът, на който ще говори потребителят, и добавете нова променлива, наречена `server_language`, за езика, използван за обучение на LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Заменете `<user language>` с името на локала за езика, на който ще говорите, например `fr-FR` за френски или `zn-HK` за кантонски.

    Заменете `<server language>` с името на локала за езика, използван за обучение на LUIS.

    Можете да намерите списък с поддържаните езици и техните имена на локали в [документацията за поддръжка на езици и гласове в Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ако не говорите няколко езика, можете да използвате услуга като [Bing Translate](https://www.bing.com/translator) или [Google Translate](https://translate.google.com), за да преведете от предпочитания от вас език на избран от вас език. Тези услуги могат също да възпроизвеждат аудио на преведения текст.
    >
    > Например, ако обучите LUIS на английски, но искате да използвате френски като език на потребителя, можете да преведете изречения като "set a 2 minute and 27 second timer" от английски на френски с помощта на Bing Translate, след което да използвате бутона **Listen translation**, за да изговорите превода в микрофона си.
    >
    > ![Бутонът за слушане на превод в Bing Translate](../../../../../translated_images/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.bg.png)

1. Добавете API ключа за преводача под `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Заменете `<key>` с API ключа за вашия ресурс на услугата за превод.

1. Над функцията `say` дефинирайте функция `translate_text`, която ще превежда текст от езика на сървъра на езика на потребителя:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Езиците за превод се предават на тази функция - вашето приложение трябва да преобразува от езика на потребителя към езика на сървъра при разпознаване на реч и от езика на сървъра към езика на потребителя при предоставяне на изговорена обратна връзка.

1. Вътре в тази функция дефинирайте URL адреса и заглавията за REST API заявката:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL адресът за този API не е специфичен за местоположението, вместо това местоположението се предава като заглавие. API ключът се използва директно, така че, за разлика от услугата за реч, няма нужда да се получава токен за достъп от API за издаване на токени.

1. Под това дефинирайте параметрите и тялото на заявката:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` дефинира параметрите, които ще се предадат на API заявката, като се посочват езиците за превод. Тази заявка ще преведе текста от езика `from` на езика `to`.

    `body` съдържа текста за превод. Това е масив, тъй като множество блокове текст могат да бъдат преведени в една и съща заявка.

1. Извършете заявката към REST API и получете отговора:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Отговорът, който се връща, е JSON масив с един елемент, който съдържа преводите. Този елемент има масив с преводи на всички елементи, предадени в тялото.

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

1. Върнете свойството `test` от първия превод от първия елемент в масива:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Актуализирайте цикъла `while True`, за да превежда текста от извикването на `convert_speech_to_text` от езика на потребителя към езика на сървъра:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Този код също така отпечатва оригиналната и преведената версия на текста в конзолата.

1. Актуализирайте функцията `say`, за да превежда текста за изговаряне от езика на сървъра към езика на потребителя:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Този код също така отпечатва оригиналната и преведената версия на текста в конзолата.

1. Стартирайте кода си. Уверете се, че вашето приложение функционира, и поискайте таймер на езика на потребителя, като говорите на този език или използвате приложение за превод.

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

    > 💁 Поради различните начини на изразяване на различни езици, може да получите преводи, които са малко по-различни от примерите, които сте дали на LUIS. Ако това е така, добавете повече примери към LUIS, обучете отново и публикувайте модела.

> 💁 Можете да намерите този код в папката [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 Вашата програма за многоезичен таймер беше успешна!

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматичните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия изходен език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален човешки превод. Ние не носим отговорност за каквито и да е недоразумения или погрешни интерпретации, произтичащи от използването на този превод.