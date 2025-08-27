<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-26T23:56:45+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "ru"
}
-->
# Перевод речи - Raspberry Pi

В этой части урока вы напишете код для перевода текста с использованием сервиса перевода.

## Преобразование текста в речь с помощью сервиса перевода

REST API сервиса речи не поддерживает прямой перевод, но вы можете использовать сервис перевода для перевода текста, сгенерированного сервисом преобразования речи в текст, а также текста, который будет озвучен. Этот сервис предоставляет REST API, который можно использовать для перевода текста.

### Задание - использование ресурса перевода для перевода текста

1. Ваш умный таймер будет настроен на два языка: язык сервера, который использовался для обучения LUIS (этот же язык используется для создания сообщений для общения с пользователем), и язык, на котором говорит пользователь. Обновите переменную `language`, чтобы указать язык, на котором будет говорить пользователь, и добавьте новую переменную `server_language` для языка, использованного для обучения LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Замените `<user language>` на название локали языка, на котором вы будете говорить, например, `fr-FR` для французского или `zn-HK` для кантонского.

    Замените `<server language>` на название локали языка, использованного для обучения LUIS.

    Вы можете найти список поддерживаемых языков и их локалей в [документации о поддержке языков и голосов на сайте Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Если вы не говорите на нескольких языках, вы можете использовать такие сервисы, как [Bing Translate](https://www.bing.com/translator) или [Google Translate](https://translate.google.com), чтобы перевести текст с вашего предпочтительного языка на выбранный язык. Эти сервисы также могут воспроизводить аудио переведенного текста.
    >
    > Например, если вы обучили LUIS на английском, но хотите использовать французский как язык пользователя, вы можете перевести фразы, такие как "set a 2 minute and 27 second timer", с английского на французский с помощью Bing Translate, а затем использовать кнопку **Listen translation**, чтобы произнести перевод в микрофон.
    >
    > ![Кнопка прослушивания перевода в Bing Translate](../../../../../translated_images/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.ru.png)

1. Добавьте ключ API переводчика ниже переменной `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Замените `<key>` на ключ API для вашего ресурса сервиса перевода.

1. Над функцией `say` определите функцию `translate_text`, которая будет переводить текст с языка сервера на язык пользователя:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    В эту функцию передаются исходный и целевой языки. Ваше приложение должно переводить с языка пользователя на язык сервера при распознавании речи и с языка сервера на язык пользователя при предоставлении озвученного ответа.

1. Внутри этой функции задайте URL и заголовки для вызова REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL для этого API не зависит от местоположения, вместо этого местоположение передается в заголовке. Ключ API используется напрямую, поэтому, в отличие от сервиса речи, нет необходимости получать токен доступа через API выдачи токенов.

1. Далее задайте параметры и тело запроса:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` определяет параметры, передаваемые в вызов API, включая исходный и целевой языки. Этот вызов переводит текст с языка `from` на язык `to`.

    `body` содержит текст для перевода. Это массив, так как за один вызов можно перевести несколько блоков текста.

1. Выполните вызов REST API и получите ответ:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Ответ возвращается в виде JSON-массива, содержащего один элемент с переводами. Этот элемент включает массив переводов для всех элементов, переданных в теле запроса.

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

1. Верните свойство `text` из первого перевода первого элемента массива:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Обновите цикл `while True`, чтобы переводить текст, полученный из вызова `convert_speech_to_text`, с языка пользователя на язык сервера:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Этот код также выводит оригинальную и переведенную версии текста в консоль.

1. Обновите функцию `say`, чтобы переводить текст для озвучивания с языка сервера на язык пользователя:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Этот код также выводит оригинальную и переведенную версии текста в консоль.

1. Запустите ваш код. Убедитесь, что ваше приложение работает, и запросите таймер на языке пользователя, либо говоря на этом языке самостоятельно, либо используя приложение для перевода.

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

    > 💁 Из-за различных способов выражения одной и той же мысли на разных языках вы можете получить переводы, которые немного отличаются от примеров, предоставленных LUIS. Если это так, добавьте больше примеров в LUIS, переобучите и заново опубликуйте модель.

> 💁 Вы можете найти этот код в папке [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 Ваше многоязычное приложение-таймер успешно работает!

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Хотя мы стремимся к точности, пожалуйста, учитывайте, что автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его исходном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникшие в результате использования данного перевода.