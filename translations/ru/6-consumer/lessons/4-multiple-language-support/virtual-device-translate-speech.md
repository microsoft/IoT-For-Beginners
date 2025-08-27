<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-26T23:57:51+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "ru"
}
-->
# Перевод речи - Виртуальное IoT-устройство

В этой части урока вы напишете код для перевода речи при преобразовании в текст с использованием службы распознавания речи, а затем переведете текст с помощью службы Translator перед генерацией голосового ответа.

## Использование службы распознавания речи для перевода речи

Служба распознавания речи может не только преобразовывать речь в текст на том же языке, но и переводить результат на другие языки.

### Задача - использование службы распознавания речи для перевода речи

1. Откройте проект `smart-timer` в VS Code и убедитесь, что виртуальная среда загружена в терминале.

1. Добавьте следующие инструкции импорта ниже существующих импортов:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Это импортирует классы, используемые для перевода речи, и библиотеку `requests`, которая будет использоваться для вызова службы Translator позже в этом уроке.

1. Ваш умный таймер будет настроен на два языка: язык сервера, который использовался для обучения LUIS (тот же язык также используется для создания сообщений для общения с пользователем), и язык, на котором говорит пользователь. Обновите переменную `language`, чтобы указать язык, на котором будет говорить пользователь, и добавьте новую переменную `server_language` для языка, использованного для обучения LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Замените `<user language>` на имя локали языка, на котором вы будете говорить, например, `fr-FR` для французского или `zn-HK` для кантонского.

    Замените `<server language>` на имя локали языка, использованного для обучения LUIS.

    Вы можете найти список поддерживаемых языков и их имена локалей в [документации о поддержке языков и голосов на сайте Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Если вы не говорите на нескольких языках, вы можете использовать такие сервисы, как [Bing Translate](https://www.bing.com/translator) или [Google Translate](https://translate.google.com), чтобы перевести с вашего предпочтительного языка на выбранный вами язык. Эти сервисы могут воспроизводить аудио переведенного текста. Учтите, что распознаватель речи может игнорировать некоторый аудиовывод с вашего устройства, поэтому вам может понадобиться дополнительное устройство для воспроизведения переведенного текста.
    >
    > Например, если вы обучили LUIS на английском языке, но хотите использовать французский как язык пользователя, вы можете перевести такие предложения, как "установить таймер на 2 минуты и 27 секунд" с английского на французский с помощью Bing Translate, а затем использовать кнопку **Listen translation**, чтобы произнести перевод в микрофон.
    >
    > ![Кнопка прослушивания перевода в Bing Translate](../../../../../translated_images/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.ru.png)

1. Замените объявления `recognizer_config` и `recognizer` следующим:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Это создает конфигурацию перевода для распознавания речи на языке пользователя и создания переводов на язык пользователя и сервера. Затем эта конфигурация используется для создания переводчика-распознавателя — распознавателя речи, который может переводить результат распознавания речи на несколько языков.

    > 💁 Оригинальный язык должен быть указан в `target_languages`, иначе вы не получите никаких переводов.

1. Обновите функцию `recognized`, заменив весь ее содержимое следующим:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Этот код проверяет, был ли вызвано событие распознавания из-за перевода речи (это событие может быть вызвано в других случаях, например, когда речь распознана, но не переведена). Если речь была переведена, он находит перевод в словаре `args.result.translations`, который соответствует языку сервера.

    Словарь `args.result.translations` использует ключи, основанные на части языка из настройки локали, а не на всей настройке. Например, если вы запросите перевод на `fr-FR` для французского, словарь будет содержать запись для `fr`, а не `fr-FR`.

    Переведенный текст затем отправляется в IoT Hub.

1. Запустите этот код, чтобы протестировать переводы. Убедитесь, что ваше приложение-функция работает, и запросите таймер на языке пользователя, либо говоря на этом языке самостоятельно, либо используя приложение для перевода.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Перевод текста с использованием службы Translator

Служба распознавания речи не поддерживает перевод текста обратно в речь, вместо этого вы можете использовать службу Translator для перевода текста. У этой службы есть REST API, который вы можете использовать для перевода текста.

### Задача - использование ресурса Translator для перевода текста

1. Добавьте ключ API Translator ниже `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Замените `<key>` на ключ API для вашего ресурса службы Translator.

1. Над функцией `say` определите функцию `translate_text`, которая будет переводить текст с языка сервера на язык пользователя:

    ```python
    def translate_text(text):
    ```

1. Внутри этой функции определите URL и заголовки для вызова REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL для этого API не зависит от местоположения, вместо этого местоположение передается в виде заголовка. Ключ API используется напрямую, поэтому, в отличие от службы распознавания речи, нет необходимости получать токен доступа через API выдачи токенов.

1. Ниже определите параметры и тело для вызова:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` определяет параметры для передачи в вызов API, передавая исходный и целевой языки. Этот вызов будет переводить текст с языка `from` на язык `to`.

    `body` содержит текст для перевода. Это массив, так как несколько блоков текста могут быть переведены в одном вызове.

1. Выполните вызов REST API и получите ответ:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Ответ, который возвращается, представляет собой JSON-массив, содержащий один элемент с переводами. Этот элемент имеет массив для переводов всех элементов, переданных в теле.

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

1. Верните свойство `text` из первого перевода первого элемента массива:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Обновите функцию `say`, чтобы перевести текст перед генерацией SSML:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Этот код также выводит оригинальную и переведенную версии текста в консоль.

1. Запустите ваш код. Убедитесь, что ваше приложение-функция работает, и запросите таймер на языке пользователя, либо говоря на этом языке самостоятельно, либо используя приложение для перевода.

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

    > 💁 Из-за различных способов выражения в разных языках вы можете получить переводы, которые немного отличаются от примеров, которые вы дали LUIS. Если это так, добавьте больше примеров в LUIS, переобучите и снова опубликуйте модель.

> 💁 Вы можете найти этот код в папке [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Ваш многоязычный таймер успешно работает!

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Несмотря на наши усилия по обеспечению точности, пожалуйста, учитывайте, что автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его исходном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникшие в результате использования данного перевода.