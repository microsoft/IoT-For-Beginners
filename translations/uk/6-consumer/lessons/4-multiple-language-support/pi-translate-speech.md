<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-28T16:38:17+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "uk"
}
-->
# Переклад мови - Raspberry Pi

У цій частині уроку ви напишете код для перекладу тексту за допомогою сервісу перекладу.

## Перетворення тексту в мову за допомогою сервісу перекладу

REST API сервісу мовлення не підтримує прямий переклад, але ви можете використовувати сервіс Translator для перекладу тексту, згенерованого сервісом перетворення мови в текст, а також тексту для озвучення відповіді. Цей сервіс має REST API, який можна використовувати для перекладу тексту.

### Завдання - використання ресурсу перекладача для перекладу тексту

1. Ваш розумний таймер матиме встановлені 2 мови — мову сервера, який використовувався для навчання LUIS (ця ж мова використовується для створення повідомлень для спілкування з користувачем), і мову, якою говорить користувач. Оновіть змінну `language`, щоб вона відповідала мові, якою говоритиме користувач, і додайте нову змінну під назвою `server_language` для мови, яка використовувалася для навчання LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Замініть `<user language>` на назву локалі мови, якою ви будете говорити, наприклад, `fr-FR` для французької або `zn-HK` для кантонської.

    Замініть `<server language>` на назву локалі мови, яка використовувалася для навчання LUIS.

    Ви можете знайти список підтримуваних мов і їхніх назв локалей у [документації про підтримку мов і голосів на Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Якщо ви не володієте кількома мовами, ви можете скористатися сервісами, такими як [Bing Translate](https://www.bing.com/translator) або [Google Translate](https://translate.google.com), щоб перекласти з вашої улюбленої мови на обрану мову. Ці сервіси також можуть відтворювати аудіо перекладеного тексту.
    >
    > Наприклад, якщо ви навчаєте LUIS англійською, але хочете використовувати французьку як мову користувача, ви можете перекласти речення, такі як "set a 2 minute and 27 second timer", з англійської на французьку за допомогою Bing Translate, а потім скористатися кнопкою **Listen translation**, щоб озвучити переклад у ваш мікрофон.
    >
    > ![Кнопка прослуховування перекладу на Bing Translate](../../../../../translated_images/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.uk.png)

1. Додайте ключ API перекладача під змінною `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Замініть `<key>` на ключ API для вашого ресурсу сервісу перекладача.

1. Над функцією `say` визначте функцію `translate_text`, яка буде перекладати текст з мови сервера на мову користувача:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Мови `from` і `to` передаються в цю функцію — ваш додаток повинен конвертувати з мови користувача на мову сервера під час розпізнавання мови і з мови сервера на мову користувача під час надання озвученого зворотного зв’язку.

1. У цій функції визначте URL і заголовки для виклику REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL для цього API не залежить від розташування, натомість розташування передається як заголовок. Ключ API використовується безпосередньо, тому, на відміну від сервісу мовлення, немає потреби отримувати токен доступу через API видачі токенів.

1. Нижче визначте параметри та тіло для виклику:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` визначає параметри, які передаються у виклик API, передаючи мови `from` і `to`. Цей виклик перекладатиме текст з мови `from` на мову `to`.

    `body` містить текст для перекладу. Це масив, оскільки кілька блоків тексту можуть бути перекладені в одному виклику.

1. Виконайте виклик REST API і отримайте відповідь:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Відповідь, що повертається, є JSON-масивом, який містить один елемент із перекладами. Цей елемент має масив із перекладами всіх елементів, переданих у тілі запиту.

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

1. Поверніть властивість `test` з першого перекладу з першого елемента масиву:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Оновіть цикл `while True`, щоб перекладати текст із виклику `convert_speech_to_text` з мови користувача на мову сервера:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Цей код також виводить оригінальну та перекладену версії тексту в консоль.

1. Оновіть функцію `say`, щоб перекладати текст для озвучення з мови сервера на мову користувача:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Цей код також виводить оригінальну та перекладену версії тексту в консоль.

1. Запустіть ваш код. Переконайтеся, що ваш функціональний додаток працює, і запросіть таймер мовою користувача, або говорячи цією мовою самостійно, або використовуючи додаток для перекладу.

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

    > 💁 Через різні способи висловлювання в різних мовах ви можете отримати переклади, які трохи відрізняються від прикладів, які ви надали LUIS. У такому випадку додайте більше прикладів у LUIS, повторно навчіть і знову опублікуйте модель.

> 💁 Ви можете знайти цей код у папці [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 Ваш багатомовний таймер працює успішно!

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.