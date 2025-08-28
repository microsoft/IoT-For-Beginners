<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-28T16:30:00+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "uk"
}
-->
# Перетворення мови в текст - Raspberry Pi

У цій частині уроку ви напишете код для перетворення мови із записаного аудіо в текст за допомогою мовного сервісу.

## Надсилання аудіо до мовного сервісу

Аудіо можна надіслати до мовного сервісу за допомогою REST API. Щоб використовувати мовний сервіс, спочатку потрібно отримати токен доступу, а потім використовувати цей токен для доступу до REST API. Ці токени доступу мають термін дії 10 хвилин, тому ваш код повинен регулярно запитувати їх, щоб забезпечити їхню актуальність.

### Завдання - отримання токена доступу

1. Відкрийте проєкт `smart-timer` на вашому Raspberry Pi.

1. Видаліть функцію `play_audio`. Вона більше не потрібна, оскільки ви не хочете, щоб розумний таймер повторював те, що ви сказали.

1. Додайте наступний імпорт на початок файлу `app.py`:

    ```python
    import requests
    ```

1. Додайте наступний код перед циклом `while True`, щоб оголосити деякі налаштування для мовного сервісу:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Замініть `<key>` на API-ключ вашого ресурсу мовного сервісу. Замініть `<location>` на розташування, яке ви використовували під час створення ресурсу мовного сервісу.

    Замініть `<language>` на назву локалі мови, якою ви будете говорити, наприклад, `en-GB` для англійської або `zn-HK` для кантонської. Ви можете знайти список підтримуваних мов і їхніх назв локалей у [документації про підтримку мов і голосів на Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Нижче цього додайте наступну функцію для отримання токена доступу:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Ця функція викликає кінцеву точку видачі токенів, передаючи API-ключ у заголовку. Виклик повертає токен доступу, який можна використовувати для виклику мовних сервісів.

1. Нижче цього оголосіть функцію для перетворення мови із записаного аудіо в текст за допомогою REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. У цій функції налаштуйте URL REST API та заголовки:

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

    Цей код створює URL, використовуючи розташування ресурсу мовного сервісу. Потім він заповнює заголовки токеном доступу з функції `get_access_token`, а також частотою дискретизації, яка використовується для запису аудіо. Нарешті, він визначає деякі параметри, які передаються разом із URL і містять мову аудіо.

1. Нижче цього додайте наступний код для виклику REST API та отримання тексту:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Цей код викликає URL і декодує значення JSON, яке приходить у відповіді. Значення `RecognitionStatus` у відповіді вказує, чи вдалося виклику успішно перетворити мову в текст, і якщо це `Success`, то текст повертається з функції, інакше повертається порожній рядок.

1. Перед циклом `while True:` визначте функцію для обробки тексту, отриманого від сервісу перетворення мови в текст. Ця функція поки що просто виводитиме текст у консоль.

    ```python
    def process_text(text):
        print(text)
    ```

1. Нарешті, замініть виклик `play_audio` у циклі `while True` на виклик функції `convert_speech_to_text`, передаючи текст у функцію `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Запустіть код. Натисніть кнопку і говоріть у мікрофон. Відпустіть кнопку, коли закінчите, і аудіо буде перетворено в текст і виведено в консоль.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Спробуйте різні типи речень, а також речення, де слова звучать однаково, але мають різні значення. Наприклад, якщо ви говорите англійською, скажіть "I want to buy two bananas and an apple too" і зверніть увагу, як сервіс правильно використовує "to", "two" і "too" залежно від контексту слова, а не лише його звучання.

> 💁 Ви можете знайти цей код у папці [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Ваше програмне забезпечення для перетворення мови в текст працює успішно!

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматизовані переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.