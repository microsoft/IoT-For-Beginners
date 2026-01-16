<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-26T23:52:24+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "ur"
}
-->
# تقریر کا ترجمہ - Wio Terminal

اس سبق کے اس حصے میں، آپ کوڈ لکھیں گے تاکہ مترجم سروس کا استعمال کرتے ہوئے متن کا ترجمہ کیا جا سکے۔

## مترجم سروس کا استعمال کرتے ہوئے متن کو تقریر میں تبدیل کریں

تقریر سروس REST API براہ راست ترجمے کی حمایت نہیں کرتا، لیکن آپ تقریر سے متن سروس کے ذریعے پیدا کردہ متن اور بولے گئے جواب کے متن کو ترجمہ کرنے کے لیے مترجم سروس استعمال کر سکتے ہیں۔ اس سروس میں ایک REST API ہے جسے آپ متن کا ترجمہ کرنے کے لیے استعمال کر سکتے ہیں، لیکن اسے استعمال کرنے میں آسان بنانے کے لیے اسے آپ کے فنکشنز ایپ میں ایک اور HTTP ٹرگر میں لپیٹ دیا جائے گا۔

### کام - متن کا ترجمہ کرنے کے لیے ایک سرور لیس فنکشن بنائیں

1. اپنے `smart-timer-trigger` پروجیکٹ کو VS Code میں کھولیں، اور ٹرمینل کھولیں، یہ یقینی بناتے ہوئے کہ ورچوئل ماحول فعال ہے۔ اگر نہیں، تو ٹرمینل کو ختم کریں اور دوبارہ بنائیں۔

1. `local.settings.json` فائل کھولیں اور مترجم API کلید اور مقام کے لیے ترتیبات شامل کریں:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    `<key>` کو اپنے مترجم سروس ریسورس کے API کلید سے تبدیل کریں۔ `<location>` کو اس مقام سے تبدیل کریں جو آپ نے مترجم سروس ریسورس بناتے وقت استعمال کیا تھا۔

1. اس ایپ میں ایک نیا HTTP ٹرگر شامل کریں جسے `translate-text` کہا جاتا ہے، درج ذیل کمانڈ کا استعمال کرتے ہوئے، جو فنکشنز ایپ پروجیکٹ کے روٹ فولڈر کے اندر VS Code ٹرمینل میں چلائی جائے:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    یہ ایک HTTP ٹرگر بنائے گا جسے `translate-text` کہا جاتا ہے۔

1. `translate-text` فولڈر میں موجود `__init__.py` فائل کے مواد کو درج ذیل سے تبدیل کریں:

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

    یہ کوڈ HTTP درخواست سے متن اور زبانیں نکالتا ہے۔ پھر یہ مترجم REST API کو ایک درخواست بھیجتا ہے، URL کے پیرامیٹرز کے طور پر زبانیں اور ترجمہ کرنے کے لیے متن کو باڈی کے طور پر پاس کرتا ہے۔ آخر میں، ترجمہ واپس کیا جاتا ہے۔

1. اپنی فنکشن ایپ کو مقامی طور پر چلائیں۔ آپ اسے curl جیسے ٹول کا استعمال کرتے ہوئے اسی طرح کال کر سکتے ہیں جیسے آپ نے اپنے `text-to-timer` HTTP ٹرگر کو آزمایا تھا۔ ترجمہ کرنے کے لیے متن اور زبانیں JSON باڈی کے طور پر پاس کرنا یقینی بنائیں:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    یہ مثال *Définir une minuterie de 30 secondes* کو فرانسیسی سے امریکی انگریزی میں ترجمہ کرتی ہے۔ یہ *Set a 30-second timer* واپس کرے گا۔

> 💁 آپ اس کوڈ کو [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) فولڈر میں تلاش کر سکتے ہیں۔

### کام - مترجم فنکشن کا استعمال کرتے ہوئے متن کا ترجمہ کریں

1. اگر `smart-timer` پروجیکٹ پہلے سے کھلا نہیں ہے تو اسے VS Code میں کھولیں۔

1. آپ کے اسمارٹ ٹائمر میں 2 زبانیں سیٹ ہوں گی - وہ زبان جو LUIS کو تربیت دینے کے لیے استعمال کی گئی تھی (یہی زبان صارف سے بات کرنے کے پیغامات بنانے کے لیے بھی استعمال ہوتی ہے)، اور وہ زبان جو صارف بولتا ہے۔ `config.h` ہیڈر فائل میں `LANGUAGE` مستقل کو اپ ڈیٹ کریں تاکہ وہ زبان ہو جو صارف بولے گا، اور ایک نیا مستقل شامل کریں جسے `SERVER_LANGUAGE` کہا جاتا ہے، جو LUIS کو تربیت دینے کے لیے استعمال ہونے والی زبان کے لیے ہے:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    `<user language>` کو اس زبان کے لوکیل نام سے تبدیل کریں جس میں آپ بولیں گے، مثال کے طور پر فرانسیسی کے لیے `fr-FR`، یا کینٹونیز کے لیے `zn-HK`۔

    `<server language>` کو اس زبان کے لوکیل نام سے تبدیل کریں جو LUIS کو تربیت دینے کے لیے استعمال کی گئی تھی۔

    آپ Microsoft Docs پر [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) میں معاون زبانوں اور ان کے لوکیل ناموں کی فہرست تلاش کر سکتے ہیں۔

    > 💁 اگر آپ کئی زبانیں نہیں بولتے تو آپ [Bing Translate](https://www.bing.com/translator) یا [Google Translate](https://translate.google.com) جیسی سروس کا استعمال کر سکتے ہیں تاکہ اپنی پسندیدہ زبان سے کسی اور زبان میں ترجمہ کریں۔ یہ سروسز پھر ترجمہ شدہ متن کا آڈیو چلا سکتی ہیں۔
    >
    > مثال کے طور پر، اگر آپ LUIS کو انگریزی میں تربیت دیتے ہیں، لیکن صارف کی زبان کے طور پر فرانسیسی استعمال کرنا چاہتے ہیں، تو آپ جملے جیسے "set a 2 minute and 27 second timer" کو Bing Translate کا استعمال کرتے ہوئے انگریزی سے فرانسیسی میں ترجمہ کر سکتے ہیں، پھر **Listen translation** بٹن کا استعمال کرتے ہوئے ترجمہ کو اپنے مائیکروفون میں بول سکتے ہیں۔
    >
    > ![Bing Translate پر Listen translation بٹن](../../../../../translated_images/ur/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. `SPEECH_LOCATION` کے نیچے مترجم API کلید اور مقام شامل کریں:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    `<KEY>` کو اپنے مترجم سروس ریسورس کے API کلید سے تبدیل کریں۔ `<LOCATION>` کو اس مقام سے تبدیل کریں جو آپ نے مترجم سروس ریسورس بناتے وقت استعمال کیا تھا۔

1. `VOICE_URL` کے نیچے مترجم ٹرگر URL شامل کریں:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    `<URL>` کو `translate-text` HTTP ٹرگر کے URL سے تبدیل کریں جو آپ کی فنکشن ایپ پر ہے۔ یہ `TEXT_TO_TIMER_FUNCTION_URL` کی قدر جیسا ہی ہوگا، سوائے اس کے کہ فنکشن کا نام `translate-text` ہوگا، `text-to-timer` کے بجائے۔

1. `src` فولڈر میں ایک نئی فائل شامل کریں جسے `text_translator.h` کہا جاتا ہے۔

1. یہ نیا `text_translator.h` ہیڈر فائل ایک کلاس پر مشتمل ہوگی جو متن کا ترجمہ کرے گی۔ اس کلاس کو اعلان کرنے کے لیے درج ذیل کو اس فائل میں شامل کریں:

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

    یہ `TextTranslator` کلاس کا اعلان کرتا ہے، ساتھ ہی اس کلاس کا ایک انسٹینس بھی۔ کلاس میں WiFi کلائنٹ کے لیے ایک واحد فیلڈ ہے۔

1. اس کلاس کے `public` سیکشن میں، متن کا ترجمہ کرنے کے لیے ایک طریقہ شامل کریں:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    یہ طریقہ اس زبان کو لیتا ہے جس سے ترجمہ کرنا ہے، اور اس زبان کو جس میں ترجمہ کرنا ہے۔ تقریر کو ہینڈل کرتے وقت، تقریر صارف کی زبان سے LUIS سرور زبان میں ترجمہ کی جائے گی، اور جوابات دیتے وقت یہ LUIS سرور زبان سے صارف کی زبان میں ترجمہ کرے گی۔

1. اس طریقہ میں، ایک JSON باڈی بنانے کے لیے کوڈ شامل کریں جس میں ترجمہ کرنے کے لیے متن اور زبانیں ہوں:

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

1. اس کے نیچے، درج ذیل کوڈ شامل کریں تاکہ باڈی کو سرور لیس فنکشن ایپ پر بھیجا جا سکے:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. اگلا، جواب حاصل کرنے کے لیے کوڈ شامل کریں:

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

1. آخر میں، کنکشن بند کرنے اور ترجمہ شدہ متن واپس کرنے کے لیے کوڈ شامل کریں:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### کام - پہچانی گئی تقریر اور جوابات کا ترجمہ کریں

1. `main.cpp` فائل کھولیں۔

1. فائل کے اوپر `TextTranslator` کلاس ہیڈر فائل کے لیے ایک شامل ہدایت شامل کریں:

    ```cpp
    #include "text_translator.h"
    ```

1. جب ٹائمر سیٹ ہوتا ہے یا ختم ہوتا ہے تو کہا جانے والا متن ترجمہ کرنے کی ضرورت ہوتی ہے۔ ایسا کرنے کے لیے، `say` فنکشن کی پہلی لائن کے طور پر درج ذیل شامل کریں:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    یہ متن کو صارف کی زبان میں ترجمہ کرے گا۔

1. `processAudio` فنکشن میں، متن کو `String text = speechToText.convertSpeechToText();` کال کے ساتھ کیپچر شدہ آڈیو سے حاصل کیا جاتا ہے۔ اس کال کے بعد، متن کا ترجمہ کریں:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    یہ متن کو صارف کی زبان سے سرور پر استعمال ہونے والی زبان میں ترجمہ کرے گا۔

1. اس کوڈ کو بنائیں، اسے اپنے Wio Terminal پر اپ لوڈ کریں اور سیریل مانیٹر کے ذریعے اسے آزمائیں۔ ایک بار جب آپ سیریل مانیٹر میں `Ready` دیکھیں، تو C بٹن دبائیں (جو بائیں جانب ہے، پاور سوئچ کے قریب)، اور بولیں۔ یقینی بنائیں کہ آپ کی فنکشن ایپ چل رہی ہے، اور صارف کی زبان میں ٹائمر کی درخواست کریں، یا تو خود اس زبان میں بول کر، یا ترجمہ ایپ کا استعمال کرتے ہوئے۔

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

> 💁 آپ اس کوڈ کو [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا کثیر لسانی ٹائمر پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔