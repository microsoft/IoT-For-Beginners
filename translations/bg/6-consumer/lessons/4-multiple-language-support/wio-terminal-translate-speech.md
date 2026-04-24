# Превод на реч - Wio Terminal

В тази част от урока ще напишете код за превод на текст, използвайки услугата за превод.

## Преобразуване на текст в реч с помощта на услугата за превод

REST API на услугата за реч не поддържа директни преводи. Вместо това можете да използвате услугата Translator, за да преведете текста, генериран от услугата за преобразуване на реч в текст, както и текста на отговора, който ще бъде произнесен. Тази услуга разполага с REST API, който можете да използвате за превод на текст, но за по-лесно използване ще я обвием в друг HTTP тригер във вашето приложение с функции.

### Задача - създаване на безсървърна функция за превод на текст

1. Отворете вашия проект `smart-timer-trigger` във VS Code и отворете терминала, като се уверите, че виртуалната среда е активирана. Ако не е, затворете и създайте отново терминала.

1. Отворете файла `local.settings.json` и добавете настройки за API ключа и местоположението на услугата за превод:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Заменете `<key>` с API ключа за вашия ресурс на услугата за превод. Заменете `<location>` с местоположението, което сте използвали при създаването на ресурса на услугата за превод.

1. Добавете нов HTTP тригер към това приложение, наречен `translate-text`, като използвате следната команда от терминала на VS Code в основната папка на проекта с функции:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Това ще създаде HTTP тригер, наречен `translate-text`.

1. Заменете съдържанието на файла `__init__.py` в папката `translate-text` със следното:

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

    Този код извлича текста и езиците от HTTP заявката. След това прави заявка към REST API на услугата за превод, като предава езиците като параметри за URL и текста за превод като тяло. Накрая връща превода.

1. Стартирайте локално вашето приложение с функции. След това можете да го извикате, използвайки инструмент като curl, по същия начин, по който тествахте HTTP тригера `text-to-timer`. Уверете се, че предавате текста за превод и езиците като JSON тяло:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Този пример превежда *Définir une minuterie de 30 secondes* от френски на американски английски. Ще върне *Set a 30-second timer*.

> 💁 Можете да намерите този код в папката [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Задача - използване на функцията за превод за превод на текст

1. Отворете проекта `smart-timer` във VS Code, ако вече не е отворен.

1. Вашият умен таймер ще има зададени 2 езика - езикът на сървъра, който е използван за обучение на LUIS (същият език се използва и за създаване на съобщенията за говорене към потребителя), и езикът, на който говори потребителят. Актуализирайте константата `LANGUAGE` във файла `config.h`, за да бъде езикът, на който ще говори потребителят, и добавете нова константа, наречена `SERVER_LANGUAGE`, за езика, използван за обучение на LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Заменете `<user language>` с името на локала за езика, на който ще говорите, например `fr-FR` за френски или `zn-HK` за кантонски.

    Заменете `<server language>` с името на локала за езика, използван за обучение на LUIS.

    Можете да намерите списък с поддържаните езици и техните имена на локали в [документацията за поддръжка на езици и гласове на Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ако не говорите няколко езика, можете да използвате услуга като [Bing Translate](https://www.bing.com/translator) или [Google Translate](https://translate.google.com), за да преведете от предпочитания от вас език на избран от вас език. Тези услуги могат също да възпроизвеждат аудио на преведения текст.
    >
    > Например, ако обучите LUIS на английски, но искате да използвате френски като език на потребителя, можете да преведете изречения като "set a 2 minute and 27 second timer" от английски на френски, използвайки Bing Translate, след което да използвате бутона **Listen translation**, за да произнесете превода в микрофона си.
    >
    > ![Бутонът за слушане на превод в Bing Translate](../../../../../translated_images/bg/bing-translate.348aa796d6efe2a9.webp)

1. Добавете API ключа и местоположението на услугата за превод под `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Заменете `<KEY>` с API ключа за вашия ресурс на услугата за превод. Заменете `<LOCATION>` с местоположението, което сте използвали при създаването на ресурса на услугата за превод.

1. Добавете URL адреса на тригера за превод под `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Заменете `<URL>` с URL адреса за HTTP тригера `translate-text` във вашето приложение с функции. Това ще бъде същото като стойността за `TEXT_TO_TIMER_FUNCTION_URL`, но с име на функция `translate-text` вместо `text-to-timer`.

1. Добавете нов файл в папката `src`, наречен `text_translator.h`.

1. Този нов заглавен файл `text_translator.h` ще съдържа клас за превод на текст. Добавете следното към този файл, за да декларирате този клас:

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

    Това декларира класа `TextTranslator`, заедно с инстанция на този клас. Класът има едно поле за WiFi клиента.

1. В секцията `public` на този клас добавете метод за превод на текст:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Този метод приема езика, от който да се превежда, и езика, на който да се превежда. При обработка на реч, речта ще се превежда от езика на потребителя към езика на сървъра на LUIS, а при даване на отговори ще се превежда от езика на сървъра на LUIS към езика на потребителя.

1. В този метод добавете код за създаване на JSON тяло, съдържащо текста за превод и езиците:

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

1. Под това добавете следния код за изпращане на тялото към приложението с функции:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. След това добавете код за получаване на отговора:

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

1. Накрая добавете код за затваряне на връзката и връщане на преведения текст:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Задача - превод на разпознатата реч и отговорите

1. Отворете файла `main.cpp`.

1. Добавете директива за включване в началото на файла за заглавния файл на класа `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Текстът, който се произнася, когато таймерът е зададен или изтече, трябва да бъде преведен. За да направите това, добавете следното като първи ред на функцията `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Това ще преведе текста на езика на потребителя.

1. Във функцията `processAudio` текстът се извлича от записаното аудио с извикването `String text = speechToText.convertSpeechToText();`. След това извикване преведете текста:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Това ще преведе текста от езика на потребителя на езика, използван на сървъра.

1. Компилирайте този код, качете го на вашия Wio Terminal и го тествайте през серийния монитор. След като видите `Ready` в серийния монитор, натиснете бутон C (този от лявата страна, най-близо до превключвателя за захранване) и говорете. Уверете се, че вашето приложение с функции работи, и поискайте таймер на езика на потребителя, като говорите на този език или използвате приложение за превод.

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

> 💁 Можете да намерите този код в папката [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Вашата многоезична програма за таймер беше успешна!

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматизираните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия роден език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален човешки превод. Ние не носим отговорност за недоразумения или погрешни интерпретации, произтичащи от използването на този превод.