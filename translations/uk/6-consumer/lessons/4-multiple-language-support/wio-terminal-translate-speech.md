# Переклад мовлення - Wio Terminal

У цій частині уроку ви напишете код для перекладу тексту за допомогою сервісу перекладача.

## Перетворення тексту в мовлення за допомогою сервісу перекладача

REST API сервісу мовлення не підтримує прямі переклади, але ви можете використовувати сервіс Translator для перекладу тексту, створеного сервісом перетворення мовлення в текст, а також тексту відповіді, що озвучена. Цей сервіс має REST API, який можна використовувати для перекладу тексту, але для зручності використання він буде обгорнутий у ще один HTTP-тригер у вашому додатку функцій.

### Завдання - створити безсерверну функцію для перекладу тексту

1. Відкрийте ваш проект `smart-timer-trigger` у VS Code і відкрийте термінал, переконавшись, що віртуальне середовище активоване. Якщо ні, закрийте і створіть термінал заново.

1. Відкрийте файл `local.settings.json` і додайте налаштування для ключа API перекладача та його розташування:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Замініть `<key>` на ключ API для вашого ресурсу сервісу перекладача. Замініть `<location>` на розташування, яке ви використовували при створенні ресурсу сервісу перекладача.

1. Додайте новий HTTP-тригер до цього додатку під назвою `translate-text`, використовуючи наступну команду з терміналу VS Code у кореневій папці проекту функцій:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Це створить HTTP-тригер під назвою `translate-text`.

1. Замініть вміст файлу `__init__.py` у папці `translate-text` наступним:

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    Цей код витягує текст і мови з HTTP-запиту. Потім він робить запит до REST API перекладача, передаючи мови як параметри для URL і текст для перекладу як тіло запиту. Нарешті, переклад повертається.

1. Запустіть ваш додаток функцій локально. Ви можете викликати його за допомогою інструменту, такого як curl, так само як ви тестували ваш HTTP-тригер `text-to-timer`. Переконайтеся, що передаєте текст для перекладу та мови у вигляді JSON-тела:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Цей приклад перекладає *Définir une minuterie de 30 secondes* з французької на американську англійську. Він поверне *Set a 30-second timer*.

> 💁 Ви можете знайти цей код у папці [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Завдання - використати функцію перекладача для перекладу тексту

1. Відкрийте проект `smart-timer` у VS Code, якщо він ще не відкритий.

1. Ваш розумний таймер матиме 2 встановлені мови - мову сервера, яка використовувалася для навчання LUIS (та ж мова також використовується для створення повідомлень для спілкування з користувачем), і мову, якою говорить користувач. Оновіть константу `LANGUAGE` у заголовковому файлі `config.h`, щоб вона відповідала мові, якою буде говорити користувач, і додайте нову константу під назвою `SERVER_LANGUAGE` для мови, яка використовувалася для навчання LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Замініть `<user language>` на назву локалі для мови, якою ви будете говорити, наприклад `fr-FR` для французької або `zn-HK` для кантонської.

    Замініть `<server language>` на назву локалі для мови, яка використовувалася для навчання LUIS.

    Ви можете знайти список підтримуваних мов і їх локалі у [документації про підтримку мов і голосів на Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Якщо ви не говорите кількома мовами, ви можете використовувати сервіс, такий як [Bing Translate](https://www.bing.com/translator) або [Google Translate](https://translate.google.com), щоб перекладати з вашої улюбленої мови на мову за вашим вибором. Ці сервіси також можуть відтворювати аудіо перекладеного тексту.
    >
    > Наприклад, якщо ви навчаєте LUIS англійською, але хочете використовувати французьку як мову користувача, ви можете перекладати речення, такі як "set a 2 minute and 27 second timer", з англійської на французьку за допомогою Bing Translate, а потім використовувати кнопку **Listen translation**, щоб озвучити переклад у ваш мікрофон.
    >
    > ![Кнопка прослуховування перекладу на Bing Translate](../../../../../translated_images/uk/bing-translate.348aa796d6efe2a9.webp)

1. Додайте ключ API перекладача та його розташування нижче `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Замініть `<KEY>` на ключ API для вашого ресурсу сервісу перекладача. Замініть `<LOCATION>` на розташування, яке ви використовували при створенні ресурсу сервісу перекладача.

1. Додайте URL тригера перекладача нижче `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Замініть `<URL>` на URL для HTTP-тригера `translate-text` у вашому додатку функцій. Це буде те ж саме значення, що і для `TEXT_TO_TIMER_FUNCTION_URL`, за винятком назви функції `translate-text` замість `text-to-timer`.

1. Додайте новий файл до папки `src` під назвою `text_translator.h`.

1. Цей новий заголовковий файл `text_translator.h` міститиме клас для перекладу тексту. Додайте наступне до цього файлу, щоб оголосити цей клас:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    Це оголошує клас `TextTranslator`, а також екземпляр цього класу. Клас має одне поле для клієнта WiFi.

1. У секцію `public` цього класу додайте метод для перекладу тексту:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Цей метод приймає мову, з якої потрібно перекладати, і мову, на яку потрібно перекладати. При обробці мовлення текст буде перекладатися з мови користувача на мову сервера LUIS, а при наданні відповідей він буде перекладатися з мови сервера LUIS на мову користувача.

1. У цьому методі додайте код для створення JSON-тела, що містить текст для перекладу та мови:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. Нижче цього додайте наступний код для надсилання тіла до додатку функцій:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Далі додайте код для отримання відповіді:

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Нарешті, додайте код для закриття з'єднання та повернення перекладеного тексту:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Завдання - переклад розпізнаного мовлення та відповідей

1. Відкрийте файл `main.cpp`.

1. Додайте директиву включення на початку файлу для заголовкового файлу класу `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Текст, який озвучується при встановленні таймера або його завершенні, потрібно перекласти. Для цього додайте наступне як перший рядок функції `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Це перекладе текст на мову користувача.

1. У функції `processAudio` текст отримується з захопленого аудіо за допомогою виклику `String text = speechToText.convertSpeechToText();`. Після цього виклику перекладіть текст:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Це перекладе текст з мови користувача на мову, яка використовується на сервері.

1. Зберіть цей код, завантажте його на ваш Wio Terminal і протестуйте через серійний монітор. Як тільки ви побачите `Ready` у серійному моніторі, натисніть кнопку C (ту, що зліва, найближче до перемикача живлення) і говоріть. Переконайтеся, що ваш додаток функцій працює, і запросіть таймер мовою користувача, або говорячи цією мовою самостійно, або використовуючи додаток для перекладу.

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 Ви можете знайти цей код у папці [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Ваш багатомовний таймер успішно працює!

---

**Відмова від відповідальності**:  
Цей документ було перекладено за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, зверніть увагу, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають у результаті використання цього перекладу.