<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-25T22:25:36+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "fa"
}
-->
# ترجمه گفتار - Wio Terminal

در این بخش از درس، کدی خواهید نوشت که متن را با استفاده از سرویس مترجم ترجمه کند.

## تبدیل متن به گفتار با استفاده از سرویس مترجم

رابط REST API سرویس گفتار از ترجمه مستقیم پشتیبانی نمی‌کند. در عوض، می‌توانید از سرویس مترجم برای ترجمه متنی که توسط سرویس گفتار به متن تولید شده و همچنین متن پاسخ گفتاری استفاده کنید. این سرویس یک رابط REST API دارد که می‌توانید از آن برای ترجمه متن استفاده کنید، اما برای سهولت استفاده، این قابلیت در یک تریگر HTTP دیگر در برنامه توابع شما قرار می‌گیرد.

### وظیفه - ایجاد یک تابع بدون سرور برای ترجمه متن

1. پروژه `smart-timer-trigger` خود را در VS Code باز کنید و ترمینال را باز کنید و مطمئن شوید که محیط مجازی فعال است. اگر فعال نیست، ترمینال را بسته و دوباره ایجاد کنید.

1. فایل `local.settings.json` را باز کنید و تنظیمات مربوط به کلید API مترجم و مکان آن را اضافه کنید:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    `<key>` را با کلید API مربوط به منبع سرویس مترجم خود جایگزین کنید. `<location>` را با مکانی که هنگام ایجاد منبع سرویس مترجم استفاده کرده‌اید جایگزین کنید.

1. یک تریگر HTTP جدید به این برنامه اضافه کنید به نام `translate-text` با استفاده از دستور زیر از داخل ترمینال VS Code در پوشه ریشه پروژه برنامه توابع:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    این دستور یک تریگر HTTP به نام `translate-text` ایجاد می‌کند.

1. محتوای فایل `__init__.py` در پوشه `translate-text` را با موارد زیر جایگزین کنید:

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

    این کد متن و زبان‌ها را از درخواست HTTP استخراج می‌کند. سپس یک درخواست به REST API مترجم ارسال می‌کند و زبان‌ها را به‌عنوان پارامترهای URL و متن برای ترجمه به‌عنوان بدنه ارسال می‌کند. در نهایت، ترجمه بازگردانده می‌شود.

1. برنامه توابع خود را به صورت محلی اجرا کنید. سپس می‌توانید با استفاده از ابزاری مانند curl این برنامه را فراخوانی کنید، همان‌طور که تریگر HTTP `text-to-timer` را آزمایش کردید. مطمئن شوید که متن برای ترجمه و زبان‌ها را به‌عنوان یک بدنه JSON ارسال می‌کنید:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    این مثال عبارت *Définir une minuterie de 30 secondes* را از زبان فرانسوی به انگلیسی آمریکایی ترجمه می‌کند. نتیجه *Set a 30-second timer* خواهد بود.

> 💁 می‌توانید این کد را در پوشه [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) پیدا کنید.

### وظیفه - استفاده از تابع مترجم برای ترجمه متن

1. پروژه `smart-timer` را در VS Code باز کنید، اگر هنوز باز نیست.

1. تایمر هوشمند شما دو زبان خواهد داشت - زبان سروری که برای آموزش LUIS استفاده شده (همان زبانی که برای ساخت پیام‌هایی که به کاربر گفته می‌شود استفاده می‌شود) و زبان صحبت شده توسط کاربر. مقدار ثابت `LANGUAGE` را در فایل هدر `config.h` به زبانی که کاربر صحبت خواهد کرد تغییر دهید و یک ثابت جدید به نام `SERVER_LANGUAGE` برای زبان استفاده شده برای آموزش LUIS اضافه کنید:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    `<user language>` را با نام محلی زبان مورد نظر خود جایگزین کنید، برای مثال `fr-FR` برای فرانسوی یا `zn-HK` برای کانتونی.

    `<server language>` را با نام محلی زبان استفاده شده برای آموزش LUIS جایگزین کنید.

    می‌توانید لیستی از زبان‌های پشتیبانی شده و نام‌های محلی آن‌ها را در [مستندات پشتیبانی زبان و صدا در Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) پیدا کنید.

    > 💁 اگر به چند زبان صحبت نمی‌کنید، می‌توانید از خدماتی مانند [Bing Translate](https://www.bing.com/translator) یا [Google Translate](https://translate.google.com) برای ترجمه از زبان مورد نظر خود به زبان دیگر استفاده کنید. این خدمات می‌توانند صدای متن ترجمه شده را نیز پخش کنند.
    >
    > برای مثال، اگر LUIS را به زبان انگلیسی آموزش داده‌اید اما می‌خواهید از زبان فرانسوی به‌عنوان زبان کاربر استفاده کنید، می‌توانید جملاتی مانند "set a 2 minute and 27 second timer" را از انگلیسی به فرانسوی با استفاده از Bing Translate ترجمه کنید، سپس از دکمه **Listen translation** برای گفتن ترجمه به میکروفون خود استفاده کنید.
    >
    > ![دکمه Listen translation در Bing Translate](../../../../../translated_images/fa/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. کلید API مترجم و مکان آن را زیر `SPEECH_LOCATION` اضافه کنید:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    `<KEY>` را با کلید API مربوط به منبع سرویس مترجم خود جایگزین کنید. `<LOCATION>` را با مکانی که هنگام ایجاد منبع سرویس مترجم استفاده کرده‌اید جایگزین کنید.

1. URL تریگر مترجم را زیر `VOICE_URL` اضافه کنید:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    `<URL>` را با URL مربوط به تریگر HTTP `translate-text` در برنامه توابع خود جایگزین کنید. این مقدار مشابه مقدار `TEXT_TO_TIMER_FUNCTION_URL` خواهد بود، به جز اینکه نام تابع `translate-text` به جای `text-to-timer` خواهد بود.

1. یک فایل جدید به پوشه `src` اضافه کنید به نام `text_translator.h`.

1. این فایل هدر جدید `text_translator.h` شامل یک کلاس برای ترجمه متن خواهد بود. موارد زیر را به این فایل اضافه کنید تا این کلاس تعریف شود:

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

    این کد کلاس `TextTranslator` را تعریف می‌کند، همراه با یک نمونه از این کلاس. این کلاس یک فیلد برای WiFi client دارد.

1. به بخش `public` این کلاس، یک متد برای ترجمه متن اضافه کنید:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    این متد زبان مبدأ و زبان مقصد را می‌گیرد. هنگام پردازش گفتار، گفتار از زبان کاربر به زبان سرور LUIS ترجمه می‌شود و هنگام ارائه پاسخ‌ها از زبان سرور LUIS به زبان کاربر ترجمه می‌شود.

1. در این متد، کدی برای ساخت یک بدنه JSON که شامل متن برای ترجمه و زبان‌ها است اضافه کنید:

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

1. در زیر این کد، کدی برای ارسال بدنه به برنامه توابع بدون سرور اضافه کنید:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. سپس، کدی برای دریافت پاسخ اضافه کنید:

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

1. در نهایت، کدی برای بستن اتصال و بازگرداندن متن ترجمه شده اضافه کنید:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### وظیفه - ترجمه گفتار شناسایی شده و پاسخ‌ها

1. فایل `main.cpp` را باز کنید.

1. یک دستور include در بالای فایل برای فایل هدر کلاس `TextTranslator` اضافه کنید:

    ```cpp
    #include "text_translator.h"
    ```

1. متنی که هنگام تنظیم یا پایان تایمر گفته می‌شود باید ترجمه شود. برای این کار، خط زیر را به‌عنوان اولین خط در تابع `say` اضافه کنید:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    این متن را به زبان کاربر ترجمه می‌کند.

1. در تابع `processAudio`، متن از صدای ضبط شده با فراخوانی `String text = speechToText.convertSpeechToText();` بازیابی می‌شود. پس از این فراخوانی، متن را ترجمه کنید:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    این متن را از زبان کاربر به زبان استفاده شده در سرور ترجمه می‌کند.

1. این کد را بسازید، آن را به Wio Terminal خود آپلود کنید و از طریق مانیتور سریال آن را آزمایش کنید. هنگامی که عبارت `Ready` را در مانیتور سریال مشاهده کردید، دکمه C (دکمه سمت چپ، نزدیک به کلید روشن/خاموش) را فشار دهید و صحبت کنید. مطمئن شوید که برنامه توابع شما در حال اجرا است و یک تایمر را به زبان کاربر درخواست کنید، یا با صحبت کردن به آن زبان یا با استفاده از یک برنامه ترجمه.

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

> 💁 می‌توانید این کد را در پوشه [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) پیدا کنید.

😀 برنامه تایمر چندزبانه شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه انسانی حرفه‌ای استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.