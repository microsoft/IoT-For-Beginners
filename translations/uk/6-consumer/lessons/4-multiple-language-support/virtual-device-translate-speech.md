# Переклад мовлення - Віртуальний IoT-пристрій

У цій частині уроку ви напишете код для перекладу мовлення при конвертації в текст за допомогою служби мовлення, а потім перекладете текст за допомогою служби Translator перед створенням озвученої відповіді.

## Використання служби мовлення для перекладу мовлення

Служба мовлення може не лише конвертувати мовлення в текст тією ж мовою, але й перекладати результат на інші мови.

### Завдання - використання служби мовлення для перекладу мовлення

1. Відкрийте проект `smart-timer` у VS Code і переконайтеся, що віртуальне середовище завантажено в терміналі.

1. Додайте наступні оператори імпорту нижче існуючих імпортів:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Це імпортує класи, які використовуються для перекладу мовлення, а також бібліотеку `requests`, яка буде використана для виклику служби Translator пізніше в цьому уроці.

1. Ваш розумний таймер матиме 2 встановлені мови - мову сервера, яка використовувалася для навчання LUIS (та ж мова також використовується для створення повідомлень для спілкування з користувачем), і мову, якою говорить користувач. Оновіть змінну `language`, щоб вона відповідала мові, якою буде говорити користувач, і додайте нову змінну `server_language` для мови, яка використовувалася для навчання LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Замініть `<user language>` на назву локалі мови, якою ви будете говорити, наприклад `fr-FR` для французької або `zn-HK` для кантонської.

    Замініть `<server language>` на назву локалі мови, яка використовувалася для навчання LUIS.

    Ви можете знайти список підтримуваних мов і їх локалі в [документації про підтримку мов і голосів на Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Якщо ви не володієте кількома мовами, ви можете використовувати такі сервіси, як [Bing Translate](https://www.bing.com/translator) або [Google Translate](https://translate.google.com), щоб перекладати з вашої улюбленої мови на обрану вами мову. Ці сервіси можуть також відтворювати аудіо перекладеного тексту. Зверніть увагу, що розпізнавач мовлення може ігнорувати деякий аудіовихід вашого пристрою, тому вам може знадобитися додатковий пристрій для відтворення перекладеного тексту.
    >
    > Наприклад, якщо ви навчаєте LUIS англійською, але хочете використовувати французьку як мову користувача, ви можете перекладати речення, такі як "set a 2 minute and 27 second timer", з англійської на французьку за допомогою Bing Translate, а потім використовувати кнопку **Listen translation**, щоб озвучити переклад у ваш мікрофон.
    >
    > ![Кнопка прослуховування перекладу на Bing Translate](../../../../../translated_images/uk/bing-translate.348aa796d6efe2a9.webp)

1. Замініть декларації `recognizer_config` і `recognizer` наступним:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Це створює конфігурацію перекладу для розпізнавання мовлення мовою користувача і створення перекладів мовою користувача та мовою сервера. Потім ця конфігурація використовується для створення перекладача мовлення - розпізнавача мовлення, який може перекладати результат розпізнавання мовлення на кілька мов.

    > 💁 Оригінальна мова повинна бути вказана в `target_languages`, інакше ви не отримаєте жодних перекладів.

1. Оновіть функцію `recognized`, замінивши весь її вміст наступним:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Цей код перевіряє, чи подія розпізнавання була викликана через переклад мовлення (ця подія може викликатися в інших випадках, наприклад, коли мовлення розпізнано, але не перекладено). Якщо мовлення було перекладено, він знаходить переклад у словнику `args.result.translations`, який відповідає мові сервера.

    Словник `args.result.translations` використовує ключі, які відповідають мовній частині налаштування локалі, а не всьому налаштуванню. Наприклад, якщо ви запитуєте переклад на `fr-FR` для французької, словник міститиме запис для `fr`, а не `fr-FR`.

    Перекладений текст потім надсилається до IoT Hub.

1. Запустіть цей код, щоб протестувати переклади. Переконайтеся, що ваш функціональний додаток працює, і запросіть таймер мовою користувача, або говорячи цією мовою самостійно, або використовуючи додаток для перекладу.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Переклад тексту за допомогою служби Translator

Служба мовлення не підтримує переклад тексту назад у мовлення, натомість ви можете використовувати службу Translator для перекладу тексту. Ця служба має REST API, який ви можете використовувати для перекладу тексту.

### Завдання - використання ресурсу Translator для перекладу тексту

1. Додайте ключ API Translator нижче `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Замініть `<key>` на ключ API для вашого ресурсу служби Translator.

1. Над функцією `say` визначте функцію `translate_text`, яка буде перекладати текст з мови сервера на мову користувача:

    ```python
    def translate_text(text):
    ```

1. У цій функції визначте URL і заголовки для виклику REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL для цього API не залежить від місця розташування, натомість місце розташування передається як заголовок. Ключ API використовується безпосередньо, тому, на відміну від служби мовлення, немає необхідності отримувати токен доступу з API видачі токенів.

1. Нижче визначте параметри і тіло для виклику:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` визначає параметри для передачі у виклик API, передаючи мови `from` і `to`. Цей виклик перекладатиме текст з мови `from` на мову `to`.

    `body` містить текст для перекладу. Це масив, оскільки кілька блоків тексту можуть бути перекладені в одному виклику.

1. Здійсніть виклик REST API і отримайте відповідь:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Відповідь, яка повертається, є JSON-масивом, з одним елементом, який містить переклади. Цей елемент має масив для перекладів усіх елементів, переданих у тілі.

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

1. Поверніть властивість `text` з першого перекладу першого елемента масиву:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Оновіть функцію `say`, щоб перекладати текст перед створенням SSML:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Цей код також друкує оригінальну та перекладену версії тексту в консоль.

1. Запустіть ваш код. Переконайтеся, що ваш функціональний додаток працює, і запросіть таймер мовою користувача, або говорячи цією мовою самостійно, або використовуючи додаток для перекладу.

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

    > 💁 Через різні способи висловлювання в різних мовах ви можете отримати переклади, які трохи відрізняються від прикладів, які ви надали LUIS. Якщо це так, додайте більше прикладів до LUIS, перевчіть і повторно опублікуйте модель.

> 💁 Ви можете знайти цей код у папці [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Ваш багатомовний таймер успішно працює!

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.