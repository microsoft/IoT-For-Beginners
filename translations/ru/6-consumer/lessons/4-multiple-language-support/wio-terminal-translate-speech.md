# Перевод речи - Wio Terminal

В этой части урока вы напишете код для перевода текста с использованием сервиса перевода.

## Преобразование текста в речь с использованием сервиса перевода

REST API сервиса речи не поддерживает прямой перевод, но вы можете использовать сервис перевода для перевода текста, сгенерированного сервисом преобразования речи в текст, а также текста, который будет произнесен в ответ. У этого сервиса есть REST API, который можно использовать для перевода текста, но для упрощения работы он будет обернут в другой HTTP-триггер в вашем приложении функций.

### Задача - создание серверлесс-функции для перевода текста

1. Откройте ваш проект `smart-timer-trigger` в VS Code и откройте терминал, убедившись, что виртуальная среда активирована. Если нет, завершите и заново создайте терминал.

1. Откройте файл `local.settings.json` и добавьте настройки для ключа API и местоположения сервиса перевода:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Замените `<key>` на ключ API вашего ресурса сервиса перевода. Замените `<location>` на местоположение, которое вы указали при создании ресурса сервиса перевода.

1. Добавьте новый HTTP-триггер в это приложение под названием `translate-text`, используя следующую команду в терминале VS Code в корневой папке проекта приложения функций:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Это создаст HTTP-триггер с именем `translate-text`.

1. Замените содержимое файла `__init__.py` в папке `translate-text` следующим:

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

    Этот код извлекает текст и языки из HTTP-запроса. Затем он отправляет запрос к REST API сервиса перевода, передавая языки в качестве параметров URL и текст для перевода в теле запроса. Наконец, возвращается перевод.

1. Запустите ваше приложение функций локально. Затем вы можете вызвать его с помощью инструмента, такого как curl, так же, как вы тестировали HTTP-триггер `text-to-timer`. Убедитесь, что вы передаете текст для перевода и языки в формате JSON:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Этот пример переводит *Définir une minuterie de 30 secondes* с французского на американский английский. Результат будет *Set a 30-second timer*.

> 💁 Этот код можно найти в папке [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Задача - использование функции перевода для перевода текста

1. Откройте проект `smart-timer` в VS Code, если он еще не открыт.

1. Ваш умный таймер будет настроен на 2 языка - язык сервера, который использовался для обучения LUIS (этот же язык используется для создания сообщений, которые будут произноситься пользователю), и язык, на котором говорит пользователь. Обновите константу `LANGUAGE` в заголовочном файле `config.h`, чтобы она соответствовала языку, на котором будет говорить пользователь, и добавьте новую константу под названием `SERVER_LANGUAGE` для языка, использованного для обучения LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Замените `<user language>` на имя локали языка, на котором вы будете говорить, например, `fr-FR` для французского или `zn-HK` для кантонского.

    Замените `<server language>` на имя локали языка, использованного для обучения LUIS.

    Вы можете найти список поддерживаемых языков и их имен локалей в [документации о поддержке языков и голосов на сайте Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Если вы не говорите на нескольких языках, вы можете использовать сервисы, такие как [Bing Translate](https://www.bing.com/translator) или [Google Translate](https://translate.google.com), чтобы перевести текст с вашего предпочтительного языка на выбранный язык. Эти сервисы также могут воспроизводить аудио переведенного текста.
    >
    > Например, если вы обучили LUIS на английском, но хотите использовать французский как язык пользователя, вы можете перевести фразы, такие как "set a 2 minute and 27 second timer", с английского на французский с помощью Bing Translate, а затем использовать кнопку **Listen translation**, чтобы произнести перевод в ваш микрофон.
    >
    > ![Кнопка прослушивания перевода в Bing Translate](../../../../../translated_images/ru/bing-translate.348aa796d6efe2a9.webp)

1. Добавьте ключ API и местоположение сервиса перевода ниже `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Замените `<KEY>` на ключ API вашего ресурса сервиса перевода. Замените `<LOCATION>` на местоположение, которое вы указали при создании ресурса сервиса перевода.

1. Добавьте URL триггера перевода ниже `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Замените `<URL>` на URL для HTTP-триггера `translate-text` в вашем приложении функций. Это будет то же значение, что и для `TEXT_TO_TIMER_FUNCTION_URL`, за исключением того, что имя функции будет `translate-text` вместо `text-to-timer`.

1. Добавьте новый файл в папку `src` с именем `text_translator.h`.

1. Этот новый заголовочный файл `text_translator.h` будет содержать класс для перевода текста. Добавьте следующее в этот файл, чтобы объявить этот класс:

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

    Это объявляет класс `TextTranslator`, а также экземпляр этого класса. Класс имеет одно поле для WiFi-клиента.

1. В секцию `public` этого класса добавьте метод для перевода текста:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Этот метод принимает язык, с которого нужно перевести, и язык, на который нужно перевести. При обработке речи текст будет переводиться с языка пользователя на язык сервера LUIS, а при предоставлении ответов - с языка сервера LUIS на язык пользователя.

1. В этом методе добавьте код для создания JSON-тела, содержащего текст для перевода и языки:

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

1. Ниже добавьте следующий код для отправки тела в серверлесс-приложение функций:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Далее добавьте код для получения ответа:

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

1. Наконец, добавьте код для закрытия соединения и возврата переведенного текста:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Задача - перевод распознанной речи и ответов

1. Откройте файл `main.cpp`.

1. Добавьте директиву include в начале файла для заголовочного файла класса `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Текст, который произносится при установке или завершении таймера, нужно перевести. Для этого добавьте следующую строку в начало функции `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Это переведет текст на язык пользователя.

1. В функции `processAudio` текст извлекается из записанного аудио с помощью вызова `String text = speechToText.convertSpeechToText();`. После этого вызова переведите текст:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Это переведет текст с языка пользователя на язык, используемый на сервере.

1. Соберите этот код, загрузите его на ваш Wio Terminal и протестируйте через последовательный монитор. Как только вы увидите `Ready` в последовательном мониторе, нажмите кнопку C (левую кнопку, ближайшую к переключателю питания) и говорите. Убедитесь, что ваше приложение функций запущено, и запросите таймер на языке пользователя, либо говоря на этом языке самостоятельно, либо используя приложение для перевода.

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

> 💁 Этот код можно найти в папке [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Ваш многоязычный таймер успешно работает!

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Хотя мы стремимся к точности, пожалуйста, учитывайте, что автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его исходном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникшие в результате использования данного перевода.