# Превод говора - Wio Terminal

У овом делу лекције, написаћете код за превођење текста користећи услугу преводиоца.

## Претварање текста у говор помоћу услуге преводиоца

REST API услуге говора не подржава директне преводе, али можете користити услугу Преводиоца за превођење текста који је генерисан помоћу услуге претварања говора у текст, као и текста одговора који се изговара. Ова услуга има REST API који можете користити за превођење текста, али да би употреба била једноставнија, овај API ће бити обухваћен другим HTTP тригером у вашој апликацији функција.

### Задатак - креирање серверлес функције за превођење текста

1. Отворите свој пројекат `smart-timer-trigger` у VS Code-у и отворите терминал, водећи рачуна да је виртуелно окружење активирано. Ако није, затворите и поново креирајте терминал.

1. Отворите датотеку `local.settings.json` и додајте подешавања за API кључ и локацију услуге преводиоца:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Замените `<key>` API кључем за ваш ресурс услуге преводиоца. Замените `<location>` локацијом коју сте користили приликом креирања ресурса услуге преводиоца.

1. Додајте нови HTTP тригер у ову апликацију под називом `translate-text` користећи следећу команду из VS Code терминала у основном фолдеру пројекта апликације функција:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Ово ће креирати HTTP тригер под називом `translate-text`.

1. Замените садржај датотеке `__init__.py` у фолдеру `translate-text` следећим:

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

    Овај код извлачи текст и језике из HTTP захтева. Затим шаље захтев REST API-ју услуге преводиоца, прослеђујући језике као параметре за URL и текст за превођење као тело. На крају, превод се враћа.

1. Покрените своју апликацију функција локално. Затим је можете позвати користећи алат као што је curl на исти начин као што сте тестирали `text-to-timer` HTTP тригер. Обавезно проследите текст за превођење и језике као JSON тело:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Овај пример преводи *Définir une minuterie de 30 secondes* са француског на амерички енглески. Вратиће *Set a 30-second timer*.

> 💁 Овај код можете пронаћи у фолдеру [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Задатак - коришћење функције преводиоца за превођење текста

1. Отворите пројекат `smart-timer` у VS Code-у ако већ није отворен.

1. Ваш паметни тајмер ће имати подешена 2 језика - језик сервера који је коришћен за тренирање LUIS-а (тај исти језик се користи и за креирање порука које се изговарају кориснику) и језик који говори корисник. Ажурирајте константу `LANGUAGE` у хедер датотеци `config.h` тако да буде језик који ће корисник говорити, и додајте нову константу под називом `SERVER_LANGUAGE` за језик који је коришћен за тренирање LUIS-а:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Замените `<user language>` именом локала за језик којим ћете говорити, на пример `fr-FR` за француски или `zn-HK` за кантонски.

    Замените `<server language>` именом локала за језик који је коришћен за тренирање LUIS-а.

    Листу подржаних језика и њихових имена локала можете пронаћи у [документацији о подршци за језике и гласове на Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ако не говорите више језика, можете користити услугу као што је [Bing Translate](https://www.bing.com/translator) или [Google Translate](https://translate.google.com) за превођење са вашег омиљеног језика на језик по вашем избору. Ове услуге могу репродуковати аудио преведеног текста.
    >
    > На пример, ако тренирате LUIS на енглеском, али желите да користите француски као језик корисника, можете превести реченице попут "set a 2 minute and 27 second timer" са енглеског на француски користећи Bing Translate, а затим користити дугме **Listen translation** да изговорите превод у свој микрофон.
    >
    > ![Дугме за слушање превода на Bing Translate](../../../../../translated_images/sr/bing-translate.348aa796d6efe2a9.webp)

1. Додајте API кључ и локацију услуге преводиоца испод `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Замените `<KEY>` API кључем за ваш ресурс услуге преводиоца. Замените `<LOCATION>` локацијом коју сте користили приликом креирања ресурса услуге преводиоца.

1. Додајте URL тригера преводиоца испод `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Замените `<URL>` URL-ом за HTTP тригер `translate-text` у вашој апликацији функција. Ово ће бити исто као вредност за `TEXT_TO_TIMER_FUNCTION_URL`, осим што ће име функције бити `translate-text` уместо `text-to-timer`.

1. Додајте нову датотеку у фолдер `src` под називом `text_translator.h`.

1. Ова нова хедер датотека `text_translator.h` ће садржати класу за превођење текста. Додајте следеће у ову датотеку да бисте декларисали ову класу:

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

    Овим се декларише класа `TextTranslator`, заједно са њеним примерком. Класа има једно поље за WiFi клијент.

1. У `public` секцију ове класе додајте метод за превођење текста:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Овај метод узима језик са којег се преводи и језик на који се преводи. Приликом обраде говора, говор ће се преводити са језика корисника на језик сервера LUIS-а, а приликом давања одговора преводиће се са језика сервера LUIS-а на језик корисника.

1. У овом методу додајте код за конструисање JSON тела које садржи текст за превођење и језике:

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

1. Испод овога додајте следећи код за слање тела серверлес апликацији функција:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Затим додајте код за добијање одговора:

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

1. На крају, додајте код за затварање везе и враћање преведеног текста:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Задатак - превођење препознатог говора и одговора

1. Отворите датотеку `main.cpp`.

1. Додајте директиву за укључивање на врху датотеке за хедер датотеку класе `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Текст који се изговара када се тајмер подеси или истекне треба да се преведе. Да бисте то урадили, додајте следеће као прву линију функције `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Ово ће превести текст на језик корисника.

1. У функцији `processAudio`, текст се добија из снимљеног аудио записа позивом `String text = speechToText.convertSpeechToText();`. Након овог позива, преведите текст:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Ово ће превести текст са језика корисника на језик који се користи на серверу.

1. Компилирајте овај код, отпремите га на свој Wio Terminal и тестирајте га преко серијског монитора. Када видите `Ready` у серијском монитору, притисните дугме C (оно са леве стране, најближе прекидачу за напајање) и говорите. Уверите се да ваша апликација функција ради и затражите тајмер на језику корисника, било да сами говорите тај језик или користите апликацију за превођење.

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

> 💁 Овај код можете пронаћи у фолдеру [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Ваш програм за мултијезички тајмер је био успешан!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати меродавним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.