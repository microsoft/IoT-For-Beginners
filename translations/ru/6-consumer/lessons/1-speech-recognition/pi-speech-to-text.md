<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T00:32:19+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "ru"
}
-->
# Распознавание речи - Raspberry Pi

В этой части урока вы напишете код для преобразования речи из записанного аудио в текст с использованием службы распознавания речи.

## Отправка аудио в службу распознавания речи

Аудио можно отправить в службу распознавания речи с помощью REST API. Чтобы использовать службу распознавания речи, сначала необходимо запросить токен доступа, а затем использовать этот токен для доступа к REST API. Эти токены доступа истекают через 10 минут, поэтому ваш код должен регулярно запрашивать их, чтобы они всегда были актуальными.

### Задача - получение токена доступа

1. Откройте проект `smart-timer` на вашем Raspberry Pi.

1. Удалите функцию `play_audio`. Она больше не нужна, так как умный таймер не должен повторять то, что вы сказали.

1. Добавьте следующий импорт в начало файла `app.py`:

    ```python
    import requests
    ```

1. Добавьте следующий код выше цикла `while True`, чтобы задать настройки для службы распознавания речи:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Замените `<key>` на ключ API для вашего ресурса службы распознавания речи. Замените `<location>` на местоположение, которое вы указали при создании ресурса службы распознавания речи.

    Замените `<language>` на имя локали языка, на котором вы будете говорить, например, `en-GB` для английского или `zn-HK` для кантонского. Список поддерживаемых языков и их локалей можно найти в [документации о поддержке языков и голосов на сайте Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Ниже этого добавьте следующую функцию для получения токена доступа:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Эта функция вызывает конечную точку выдачи токенов, передавая ключ API в заголовке. В ответе возвращается токен доступа, который можно использовать для вызова служб распознавания речи.

1. Ниже этого объявите функцию для преобразования речи из записанного аудио в текст с использованием REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Внутри этой функции настройте URL REST API и заголовки:

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

    Этот код формирует URL, используя местоположение ресурса службы распознавания речи. Затем он заполняет заголовки токеном доступа из функции `get_access_token`, а также частотой дискретизации, используемой для записи аудио. Наконец, он определяет параметры, которые будут переданы с URL, содержащим язык аудио.

1. Ниже этого добавьте следующий код для вызова REST API и получения текста:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Этот код вызывает URL и декодирует значение JSON, которое приходит в ответе. Значение `RecognitionStatus` в ответе указывает, удалось ли успешно преобразовать речь в текст, и если это `Success`, то текст возвращается из функции, в противном случае возвращается пустая строка.

1. Выше цикла `while True:` определите функцию для обработки текста, возвращенного службой распознавания речи. Эта функция пока будет просто выводить текст в консоль.

    ```python
    def process_text(text):
        print(text)
    ```

1. Наконец, замените вызов `play_audio` в цикле `while True` на вызов функции `convert_speech_to_text`, передавая текст в функцию `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Запустите код. Нажмите кнопку и говорите в микрофон. Отпустите кнопку, когда закончите, и аудио будет преобразовано в текст и выведено в консоль.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Попробуйте разные типы предложений, а также предложения, где слова звучат одинаково, но имеют разные значения. Например, если вы говорите на английском, скажите: "I want to buy two bananas and an apple too" и обратите внимание, как программа правильно использует "to", "two" и "too" в зависимости от контекста слова, а не только его звучания.

> 💁 Этот код можно найти в папке [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Ваше приложение для преобразования речи в текст успешно работает!

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Хотя мы стремимся к точности, пожалуйста, учитывайте, что автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его исходном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникшие в результате использования данного перевода.