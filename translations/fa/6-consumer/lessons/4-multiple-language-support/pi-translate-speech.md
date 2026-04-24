# ترجمه گفتار - رزبری پای

در این بخش از درس، شما کدی خواهید نوشت که متن را با استفاده از سرویس مترجم ترجمه کند.

## تبدیل متن به گفتار با استفاده از سرویس مترجم

رابط برنامه‌نویسی REST سرویس گفتار از ترجمه مستقیم پشتیبانی نمی‌کند. در عوض، می‌توانید از سرویس مترجم برای ترجمه متنی که توسط سرویس گفتار به متن تولید شده و همچنین متن پاسخ گفتاری استفاده کنید. این سرویس یک رابط REST API دارد که می‌توانید از آن برای ترجمه متن استفاده کنید.

### وظیفه - استفاده از منبع مترجم برای ترجمه متن

1. تایمر هوشمند شما دو زبان تنظیم‌شده خواهد داشت - زبان سروری که برای آموزش LUIS استفاده شده (همین زبان برای ساخت پیام‌هایی که به کاربر گفته می‌شود نیز استفاده می‌شود) و زبان صحبت‌شده توسط کاربر. متغیر `language` را به زبانی که کاربر صحبت خواهد کرد به‌روزرسانی کنید و یک متغیر جدید به نام `server_language` برای زبانی که برای آموزش LUIS استفاده شده اضافه کنید:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` را با نام محلی زبانی که در آن صحبت خواهید کرد جایگزین کنید، برای مثال `fr-FR` برای فرانسوی یا `zn-HK` برای کانتونی.

    `<server language>` را با نام محلی زبانی که برای آموزش LUIS استفاده شده جایگزین کنید.

    می‌توانید فهرستی از زبان‌های پشتیبانی‌شده و نام‌های محلی آن‌ها را در [مستندات پشتیبانی زبان و صدا در Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) پیدا کنید.

    > 💁 اگر به چند زبان صحبت نمی‌کنید، می‌توانید از خدماتی مانند [Bing Translate](https://www.bing.com/translator) یا [Google Translate](https://translate.google.com) برای ترجمه از زبان دلخواه خود به زبانی دیگر استفاده کنید. این خدمات می‌توانند صدای متن ترجمه‌شده را نیز پخش کنند.
    >
    > برای مثال، اگر LUIS را به زبان انگلیسی آموزش داده‌اید اما می‌خواهید از زبان فرانسوی به‌عنوان زبان کاربر استفاده کنید، می‌توانید جملاتی مانند "set a 2 minute and 27 second timer" را از انگلیسی به فرانسوی با استفاده از Bing Translate ترجمه کنید، سپس از دکمه **Listen translation** برای گفتن ترجمه به میکروفون خود استفاده کنید.
    >
    > ![دکمه Listen translation در Bing Translate](../../../../../translated_images/fa/bing-translate.348aa796d6efe2a9.webp)

1. کلید API مترجم را زیر `speech_api_key` اضافه کنید:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` را با کلید API منبع سرویس مترجم خود جایگزین کنید.

1. بالای تابع `say`، یک تابع به نام `translate_text` تعریف کنید که متن را از زبان سرور به زبان کاربر ترجمه کند:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    زبان‌های مبدا و مقصد به این تابع ارسال می‌شوند - برنامه شما باید هنگام شناسایی گفتار، از زبان کاربر به زبان سرور تبدیل کند و هنگام ارائه بازخورد گفتاری، از زبان سرور به زبان کاربر.

1. داخل این تابع، URL و هدرهای مربوط به فراخوانی REST API را تعریف کنید:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL این API به مکان خاصی وابسته نیست، بلکه مکان به‌عنوان یک هدر ارسال می‌شود. کلید API مستقیماً استفاده می‌شود، بنابراین برخلاف سرویس گفتار، نیازی به دریافت توکن دسترسی از API صادرکننده توکن نیست.

1. زیر این بخش، پارامترها و بدنه فراخوانی را تعریف کنید:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` پارامترهایی را که باید به فراخوانی API ارسال شوند تعریف می‌کند، و زبان‌های مبدا و مقصد را ارسال می‌کند. این فراخوانی متن را از زبان `from` به زبان `to` ترجمه می‌کند.

    `body` شامل متنی است که باید ترجمه شود. این یک آرایه است، زیرا چندین بلوک متن می‌توانند در یک فراخوانی ترجمه شوند.

1. فراخوانی REST API را انجام دهید و پاسخ را دریافت کنید:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    پاسخی که برمی‌گردد یک آرایه JSON است که یک آیتم دارد که شامل ترجمه‌ها است. این آیتم یک آرایه برای ترجمه‌های تمام آیتم‌های ارسال‌شده در بدنه دارد.

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

1. ویژگی `text` از اولین ترجمه از اولین آیتم در آرایه را بازگردانید:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. حلقه `while True` را به‌روزرسانی کنید تا متن فراخوانی `convert_speech_to_text` را از زبان کاربر به زبان سرور ترجمه کند:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    این کد همچنین نسخه اصلی و ترجمه‌شده متن را در کنسول چاپ می‌کند.

1. تابع `say` را به‌روزرسانی کنید تا متن گفتاری را از زبان سرور به زبان کاربر ترجمه کند:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    این کد همچنین نسخه اصلی و ترجمه‌شده متن را در کنسول چاپ می‌کند.

1. کد خود را اجرا کنید. اطمینان حاصل کنید که برنامه تابع شما در حال اجرا است و یک تایمر را به زبان کاربر درخواست کنید، یا با صحبت کردن به آن زبان یا با استفاده از یک برنامه ترجمه.

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

    > 💁 به دلیل روش‌های مختلف بیان یک موضوع در زبان‌های مختلف، ممکن است ترجمه‌هایی دریافت کنید که کمی با مثال‌هایی که به LUIS داده‌اید متفاوت باشند. اگر این اتفاق افتاد، مثال‌های بیشتری به LUIS اضافه کنید، مدل را دوباره آموزش دهید و سپس دوباره منتشر کنید.

> 💁 می‌توانید این کد را در پوشه [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) پیدا کنید.

😀 برنامه تایمر چندزبانه شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه انسانی حرفه‌ای استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.