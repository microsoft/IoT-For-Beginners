# ਭਾਸ਼ਾ ਅਨੁਵਾਦ - Wio Terminal

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਅਨੁਵਾਦਕ ਸੇਵਾ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਟੈਕਸਟ ਦਾ ਅਨੁਵਾਦ ਕਰਨ ਲਈ ਕੋਡ ਲਿਖੋਗੇ।

## ਅਨੁਵਾਦਕ ਸੇਵਾ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਟੈਕਸਟ ਨੂੰ ਭਾਸ਼ਣ ਵਿੱਚ ਬਦਲੋ

Speech service REST API ਸਿੱਧੇ ਅਨੁਵਾਦਾਂ ਦਾ ਸਮਰਥਨ ਨਹੀਂ ਕਰਦੀ, ਇਸ ਲਈ ਤੁਸੀਂ Speech to Text ਸੇਵਾ ਦੁਆਰਾ ਜਨਰੇਟ ਕੀਤੇ ਟੈਕਸਟ ਅਤੇ ਬੋਲੇ ਗਏ ਜਵਾਬ ਦੇ ਟੈਕਸਟ ਦਾ ਅਨੁਵਾਦ ਕਰਨ ਲਈ Translator ਸੇਵਾ ਦੀ ਵਰਤੋਂ ਕਰ ਸਕਦੇ ਹੋ। ਇਸ ਸੇਵਾ ਵਿੱਚ REST API ਹੈ ਜਿਸਦੀ ਵਰਤੋਂ ਟੈਕਸਟ ਦਾ ਅਨੁਵਾਦ ਕਰਨ ਲਈ ਕੀਤੀ ਜਾ ਸਕਦੀ ਹੈ, ਪਰ ਇਸਨੂੰ ਆਸਾਨ ਬਣਾਉਣ ਲਈ ਇਹ functions app ਵਿੱਚ ਇੱਕ ਹੋਰ HTTP trigger ਵਿੱਚ ਲਪੇਟਿਆ ਜਾਵੇਗਾ।

### ਕੰਮ - ਟੈਕਸਟ ਦਾ ਅਨੁਵਾਦ ਕਰਨ ਲਈ ਇੱਕ serverless function ਬਣਾਓ

1. ਆਪਣੇ `smart-timer-trigger` ਪ੍ਰੋਜੈਕਟ ਨੂੰ VS Code ਵਿੱਚ ਖੋਲ੍ਹੋ ਅਤੇ ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਟਰਮੀਨਲ ਵਿੱਚ virtual environment ਐਕਟੀਵੇਟ ਹੈ। ਜੇ ਨਹੀਂ, ਟਰਮੀਨਲ ਨੂੰ ਬੰਦ ਕਰੋ ਅਤੇ ਮੁੜ ਬਣਾਓ।

1. `local.settings.json` ਫਾਈਲ ਖੋਲ੍ਹੋ ਅਤੇ translator API key ਅਤੇ location ਲਈ settings ਸ਼ਾਮਲ ਕਰੋ:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    `<key>` ਨੂੰ ਆਪਣੇ translator service resource ਲਈ API key ਨਾਲ ਬਦਲੋ। `<location>` ਨੂੰ ਉਸ location ਨਾਲ ਬਦਲੋ ਜੋ ਤੁਸੀਂ translator service resource ਬਣਾਉਣ ਸਮੇਂ ਵਰਤੀ ਸੀ।

1. ਇਸ ਐਪ ਵਿੱਚ ਇੱਕ ਨਵਾਂ HTTP trigger ਸ਼ਾਮਲ ਕਰੋ ਜਿਸਨੂੰ `translate-text` ਕਿਹਾ ਜਾਂਦਾ ਹੈ। ਇਹ ਕੰਮ ਕਰਨ ਲਈ VS Code ਟਰਮੀਨਲ ਵਿੱਚ functions app ਪ੍ਰੋਜੈਕਟ ਦੇ root ਫੋਲਡਰ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਦੀ ਵਰਤੋਂ ਕਰੋ:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    ਇਹ ਇੱਕ HTTP trigger ਬਣਾਏਗਾ ਜਿਸਨੂੰ `translate-text` ਕਿਹਾ ਜਾਂਦਾ ਹੈ।

1. `translate-text` ਫੋਲਡਰ ਵਿੱਚ `__init__.py` ਫਾਈਲ ਦੀ ਸਮੱਗਰੀ ਨੂੰ ਹੇਠਾਂ ਦਿੱਤੇ ਨਾਲ ਬਦਲੋ:

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

    ਇਹ ਕੋਡ HTTP request ਤੋਂ ਟੈਕਸਟ ਅਤੇ ਭਾਸ਼ਾਵਾਂ ਨੂੰ extract ਕਰਦਾ ਹੈ। ਫਿਰ ਇਹ translator REST API ਨੂੰ request ਭੇਜਦਾ ਹੈ, URL ਲਈ ਭਾਸ਼ਾਵਾਂ ਨੂੰ parameters ਵਜੋਂ ਅਤੇ translate ਕਰਨ ਲਈ ਟੈਕਸਟ ਨੂੰ body ਵਜੋਂ ਪਾਸ ਕਰਦਾ ਹੈ। ਆਖਿਰ ਵਿੱਚ, translation ਵਾਪਸ ਕੀਤੀ ਜਾਂਦੀ ਹੈ।

1. ਆਪਣੀ function app ਨੂੰ ਸਥਾਨਕ ਤੌਰ 'ਤੇ ਚਲਾਓ। ਤੁਸੀਂ ਇਸਨੂੰ curl ਵਰਗੇ ਟੂਲ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਕਾਲ ਕਰ ਸਕਦੇ ਹੋ, ਜਿਵੇਂ ਤੁਸੀਂ `text-to-timer` HTTP trigger ਦੀ ਜਾਂਚ ਕੀਤੀ ਸੀ। ਯਕੀਨੀ ਬਣਾਓ ਕਿ translate ਕਰਨ ਲਈ ਟੈਕਸਟ ਅਤੇ ਭਾਸ਼ਾਵਾਂ ਨੂੰ JSON body ਵਜੋਂ ਪਾਸ ਕੀਤਾ ਜਾ ਰਿਹਾ ਹੈ:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    ਇਹ ਉਦਾਹਰਨ *Définir une minuterie de 30 secondes* ਨੂੰ French ਤੋਂ US English ਵਿੱਚ translate ਕਰਦੀ ਹੈ। ਇਹ *Set a 30-second timer* ਵਾਪਸ ਕਰੇਗੀ।

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

### ਕੰਮ - translator function ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਟੈਕਸਟ ਦਾ ਅਨੁਵਾਦ ਕਰੋ

1. `smart-timer` ਪ੍ਰੋਜੈਕਟ ਨੂੰ VS Code ਵਿੱਚ ਖੋਲ੍ਹੋ ਜੇਕਰ ਇਹ ਪਹਿਲਾਂ ਹੀ ਖੁੱਲ੍ਹਾ ਨਹੀਂ ਹੈ।

1. ਤੁਹਾਡੇ smart timer ਵਿੱਚ 2 ਭਾਸ਼ਾਵਾਂ ਸੈਟ ਕੀਤੀਆਂ ਜਾਣਗੀਆਂ - LUIS ਨੂੰ train ਕਰਨ ਲਈ ਵਰਤੀ ਗਈ server ਦੀ ਭਾਸ਼ਾ (ਇਹ ਭਾਸ਼ਾ user ਨਾਲ ਗੱਲ ਕਰਨ ਲਈ messages ਬਣਾਉਣ ਲਈ ਵੀ ਵਰਤੀ ਜਾਂਦੀ ਹੈ), ਅਤੇ user ਦੁਆਰਾ ਬੋਲੀ ਗਈ ਭਾਸ਼ਾ। `config.h` header ਫਾਈਲ ਵਿੱਚ `LANGUAGE` constant ਨੂੰ user ਦੁਆਰਾ ਬੋਲੀ ਜਾਣ ਵਾਲੀ ਭਾਸ਼ਾ ਬਣਾਓ, ਅਤੇ `SERVER_LANGUAGE` ਨਾਮਕ ਇੱਕ ਨਵਾਂ constant ਸ਼ਾਮਲ ਕਰੋ ਜੋ LUIS ਨੂੰ train ਕਰਨ ਲਈ ਵਰਤੀ ਗਈ ਭਾਸ਼ਾ ਹੈ:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    `<user language>` ਨੂੰ ਉਸ locale name ਨਾਲ ਬਦਲੋ ਜਿਸ ਭਾਸ਼ਾ ਵਿੱਚ ਤੁਸੀਂ ਬੋਲ ਰਹੇ ਹੋਵੋਗੇ, ਉਦਾਹਰਨ ਲਈ `fr-FR` French ਲਈ, ਜਾਂ `zn-HK` Cantonese ਲਈ।

    `<server language>` ਨੂੰ LUIS ਨੂੰ train ਕਰਨ ਲਈ ਵਰਤੀ ਗਈ ਭਾਸ਼ਾ ਦੇ locale name ਨਾਲ ਬਦਲੋ।

    ਤੁਸੀਂ Microsoft docs ਵਿੱਚ [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) ਵਿੱਚ supported languages ਅਤੇ ਉਨ੍ਹਾਂ ਦੇ locale names ਦੀ ਸੂਚੀ ਲੱਭ ਸਕਦੇ ਹੋ।

    > 💁 ਜੇਕਰ ਤੁਸੀਂ ਕਈ ਭਾਸ਼ਾਵਾਂ ਨਹੀਂ ਬੋਲਦੇ, ਤਾਂ ਤੁਸੀਂ [Bing Translate](https://www.bing.com/translator) ਜਾਂ [Google Translate](https://translate.google.com) ਵਰਗੇ ਸੇਵਾਵਾਂ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਆਪਣੀ ਪਸੰਦੀਦਾ ਭਾਸ਼ਾ ਤੋਂ ਕਿਸੇ ਹੋਰ ਭਾਸ਼ਾ ਵਿੱਚ translate ਕਰ ਸਕਦੇ ਹੋ। ਇਹ ਸੇਵਾਵਾਂ translate ਕੀਤੇ ਟੈਕਸਟ ਦਾ audio play ਕਰ ਸਕਦੀਆਂ ਹਨ।
    >
    > ਉਦਾਹਰਨ ਲਈ, ਜੇਕਰ ਤੁਸੀਂ LUIS ਨੂੰ English ਵਿੱਚ train ਕਰਦੇ ਹੋ, ਪਰ user language ਵਜੋਂ French ਦੀ ਵਰਤੋਂ ਕਰਨਾ ਚਾਹੁੰਦੇ ਹੋ, ਤਾਂ ਤੁਸੀਂ Bing Translate ਦੀ ਵਰਤੋਂ ਕਰਕੇ "set a 2 minute and 27 second timer" ਵਰਗੇ sentences ਨੂੰ English ਤੋਂ French ਵਿੱਚ translate ਕਰ ਸਕਦੇ ਹੋ, ਫਿਰ **Listen translation** ਬਟਨ ਦੀ ਵਰਤੋਂ ਕਰਕੇ translation ਨੂੰ ਆਪਣੇ microphone ਵਿੱਚ ਬੋਲ ਸਕਦੇ ਹੋ।
    >
    > ![Bing translate ਵਿੱਚ Listen translation ਬਟਨ](../../../../../translated_images/pa/bing-translate.348aa796d6efe2a9.webp)

1. `SPEECH_LOCATION` ਦੇ ਹੇਠਾਂ translator API key ਅਤੇ location ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    `<KEY>` ਨੂੰ ਆਪਣੇ translator service resource ਲਈ API key ਨਾਲ ਬਦਲੋ। `<LOCATION>` ਨੂੰ ਉਸ location ਨਾਲ ਬਦਲੋ ਜੋ ਤੁਸੀਂ translator service resource ਬਣਾਉਣ ਸਮੇਂ ਵਰਤੀ ਸੀ।

1. `VOICE_URL` ਦੇ ਹੇਠਾਂ translator trigger URL ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    `<URL>` ਨੂੰ `translate-text` HTTP trigger ਲਈ URL ਨਾਲ ਬਦਲੋ ਜੋ ਤੁਹਾਡੇ function app ਵਿੱਚ ਹੈ। ਇਹ `TEXT_TO_TIMER_FUNCTION_URL` ਦੇ value ਦੇ ਜੇਹਾ ਹੀ ਹੋਵੇਗਾ, ਸਿਵਾਏ function name `translate-text` ਦੀ ਬਜਾਏ `text-to-timer` ਹੋਵੇਗਾ।

1. `src` ਫੋਲਡਰ ਵਿੱਚ ਇੱਕ ਨਵੀਂ ਫਾਈਲ ਸ਼ਾਮਲ ਕਰੋ ਜਿਸਨੂੰ `text_translator.h` ਕਿਹਾ ਜਾਂਦਾ ਹੈ।

1. ਇਹ ਨਵੀਂ `text_translator.h` header ਫਾਈਲ ਇੱਕ class ਨੂੰ ਟੈਕਸਟ translate ਕਰਨ ਲਈ ਸ਼ਾਮਲ ਕਰੇਗੀ। ਇਸ ਫਾਈਲ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਸ਼ਾਮਲ ਕਰੋ ਤਾਂ ਜੋ ਇਸ class ਨੂੰ declare ਕੀਤਾ ਜਾ ਸਕੇ:

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

    ਇਹ `TextTranslator` class ਨੂੰ declare ਕਰਦਾ ਹੈ, ਨਾਲ ਹੀ ਇਸ class ਦਾ ਇੱਕ instance। ਇਸ class ਵਿੱਚ WiFi client ਲਈ ਇੱਕ field ਹੈ।

1. ਇਸ class ਦੇ `public` section ਵਿੱਚ, ਟੈਕਸਟ translate ਕਰਨ ਲਈ ਇੱਕ method ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    ਇਹ method ਉਸ ਭਾਸ਼ਾ ਨੂੰ ਲੈਂਦੀ ਹੈ ਜਿਸ ਤੋਂ translate ਕਰਨਾ ਹੈ, ਅਤੇ ਉਸ ਭਾਸ਼ਾ ਨੂੰ ਜਿਸ ਵਿੱਚ translate ਕਰਨਾ ਹੈ। ਜਦੋਂ speech ਨੂੰ handle ਕੀਤਾ ਜਾ ਰਿਹਾ ਹੈ, ਤਾਂ speech ਨੂੰ user language ਤੋਂ LUIS server language ਵਿੱਚ translate ਕੀਤਾ ਜਾਵੇਗਾ, ਅਤੇ ਜਦੋਂ responses ਦਿੱਤੇ ਜਾ ਰਹੇ ਹਨ, ਤਾਂ LUIS server language ਤੋਂ user language ਵਿੱਚ translate ਕੀਤਾ ਜਾਵੇਗਾ।

1. ਇਸ method ਵਿੱਚ, JSON body ਬਣਾਉਣ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ ਜਿਸ ਵਿੱਚ translate ਕਰਨ ਲਈ ਟੈਕਸਟ ਅਤੇ ਭਾਸ਼ਾਵਾਂ ਹਨ:

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

1. ਇਸ ਦੇ ਹੇਠਾਂ, serverless function app ਨੂੰ body ਭੇਜਣ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. ਅਗਲੇ ਕਦਮ ਵਿੱਚ, response ਪ੍ਰਾਪਤ ਕਰਨ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

1. ਆਖਿਰ ਵਿੱਚ, connection ਨੂੰ ਬੰਦ ਕਰਨ ਅਤੇ translate ਕੀਤਾ ਟੈਕਸਟ ਵਾਪਸ ਕਰਨ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### ਕੰਮ - ਪਛਾਣ ਕੀਤੇ ਗਏ speech ਅਤੇ responses ਦਾ ਅਨੁਵਾਦ ਕਰੋ

1. `main.cpp` ਫਾਈਲ ਖੋਲ੍ਹੋ।

1. `TextTranslator` class header ਫਾਈਲ ਲਈ ਫਾਈਲ ਦੇ ਉੱਪਰ ਇੱਕ include directive ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    #include "text_translator.h"
    ```

1. ਜਦੋਂ timer ਸੈਟ ਕੀਤਾ ਜਾਂਦਾ ਹੈ ਜਾਂ expire ਹੁੰਦਾ ਹੈ, ਤਾਂ ਕਿਹਾ ਗਿਆ ਟੈਕਸਟ translate ਕੀਤਾ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਇਸ ਲਈ, `say` function ਦੀ ਪਹਿਲੀ ਲਾਈਨ ਵਜੋਂ ਹੇਠਾਂ ਦਿੱਤਾ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    ਇਹ ਟੈਕਸਟ ਨੂੰ user language ਵਿੱਚ translate ਕਰੇਗਾ।

1. `processAudio` function ਵਿੱਚ, captured audio ਤੋਂ ਟੈਕਸਟ `String text = speechToText.convertSpeechToText();` call ਨਾਲ retrieve ਕੀਤਾ ਜਾਂਦਾ ਹੈ। ਇਸ call ਤੋਂ ਬਾਅਦ, ਟੈਕਸਟ translate ਕਰੋ:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    ਇਹ ਟੈਕਸਟ ਨੂੰ user language ਤੋਂ server language ਵਿੱਚ translate ਕਰੇਗਾ।

1. ਇਸ ਕੋਡ ਨੂੰ build ਕਰੋ, ਇਸਨੂੰ ਆਪਣੇ Wio Terminal ਵਿੱਚ upload ਕਰੋ ਅਤੇ serial monitor ਦੁਆਰਾ ਇਸਦੀ ਜਾਂਚ ਕਰੋ। ਜਦੋਂ ਤੁਸੀਂ serial monitor ਵਿੱਚ `Ready` ਦੇਖਦੇ ਹੋ, ਤਾਂ C button (power switch ਦੇ ਸਭ ਤੋਂ ਨੇੜੇ ਵਾਲਾ, ਖੱਬੇ ਪਾਸੇ) ਦਬਾਓ ਅਤੇ ਬੋਲੋ। ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਤੁਹਾਡਾ function app ਚੱਲ ਰਿਹਾ ਹੈ, ਅਤੇ user language ਵਿੱਚ timer ਦੀ demand ਕਰੋ, ਚਾਹੇ ਉਹ ਭਾਸ਼ਾ ਤੁਸੀਂ ਖੁਦ ਬੋਲ ਰਹੇ ਹੋ ਜਾਂ translation app ਦੀ ਵਰਤੋਂ ਕਰ ਰਹੇ ਹੋ।

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

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ multilingual timer ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਰਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਹਾਲਾਂਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦਾ ਯਤਨ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚਨਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।