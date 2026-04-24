# ترجمه گفتار - دستگاه مجازی IoT

در این بخش از درس، شما کدی خواهید نوشت که گفتار را هنگام تبدیل به متن با استفاده از سرویس گفتار ترجمه کند، سپس متن را با استفاده از سرویس Translator ترجمه کرده و در نهایت یک پاسخ گفتاری تولید کند.

## استفاده از سرویس گفتار برای ترجمه گفتار

سرویس گفتار می‌تواند گفتار را نه تنها به متن در همان زبان تبدیل کند، بلکه خروجی را به زبان‌های دیگر نیز ترجمه کند.

### وظیفه - استفاده از سرویس گفتار برای ترجمه گفتار

1. پروژه `smart-timer` را در VS Code باز کنید و مطمئن شوید که محیط مجازی در ترمینال بارگذاری شده است.

1. دستورات import زیر را به کد خود اضافه کنید:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    این دستورات کلاس‌هایی را که برای ترجمه گفتار استفاده می‌شوند و همچنین کتابخانه `requests` که برای فراخوانی سرویس Translator در ادامه این درس استفاده خواهد شد، وارد می‌کند.

1. تایمر هوشمند شما دو زبان تنظیم خواهد داشت - زبان سروری که برای آموزش LUIS استفاده شده است (همان زبانی که برای ساخت پیام‌هایی که به کاربر گفته می‌شود استفاده می‌شود) و زبان گفتاری کاربر. متغیر `language` را به زبانی که کاربر صحبت خواهد کرد به‌روزرسانی کنید و یک متغیر جدید به نام `server_language` برای زبان استفاده‌شده در آموزش LUIS اضافه کنید:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` را با نام محلی زبانی که در آن صحبت خواهید کرد جایگزین کنید، برای مثال `fr-FR` برای فرانسوی یا `zn-HK` برای کانتونی.

    `<server language>` را با نام محلی زبانی که برای آموزش LUIS استفاده شده است جایگزین کنید.

    می‌توانید لیستی از زبان‌های پشتیبانی‌شده و نام‌های محلی آن‌ها را در [مستندات پشتیبانی زبان و صدا در Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) پیدا کنید.

    > 💁 اگر به چند زبان صحبت نمی‌کنید، می‌توانید از خدماتی مانند [Bing Translate](https://www.bing.com/translator) یا [Google Translate](https://translate.google.com) برای ترجمه از زبان مورد نظر خود به زبانی دیگر استفاده کنید. این خدمات می‌توانند صدای متن ترجمه‌شده را نیز پخش کنند. توجه داشته باشید که تشخیص‌دهنده گفتار ممکن است برخی از خروجی‌های صوتی دستگاه شما را نادیده بگیرد، بنابراین ممکن است نیاز به استفاده از یک دستگاه اضافی برای پخش متن ترجمه‌شده داشته باشید.
    >
    > برای مثال، اگر LUIS را به زبان انگلیسی آموزش داده‌اید اما می‌خواهید از زبان فرانسوی به‌عنوان زبان کاربر استفاده کنید، می‌توانید جملاتی مانند "set a 2 minute and 27 second timer" را از انگلیسی به فرانسوی با استفاده از Bing Translate ترجمه کنید، سپس از دکمه **Listen translation** برای گفتن ترجمه به میکروفون خود استفاده کنید.
    >
    > ![دکمه Listen translation در Bing Translate](../../../../../translated_images/fa/bing-translate.348aa796d6efe2a9.webp)

1. اعلان‌های `recognizer_config` و `recognizer` را با موارد زیر جایگزین کنید:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    این کد یک پیکربندی ترجمه ایجاد می‌کند تا گفتار را در زبان کاربر تشخیص دهد و ترجمه‌هایی در زبان کاربر و زبان سرور ایجاد کند. سپس از این پیکربندی برای ایجاد یک تشخیص‌دهنده ترجمه استفاده می‌شود - یک تشخیص‌دهنده گفتار که می‌تواند خروجی تشخیص گفتار را به چندین زبان ترجمه کند.

    > 💁 زبان اصلی باید در `target_languages` مشخص شود، در غیر این صورت هیچ ترجمه‌ای دریافت نخواهید کرد.

1. تابع `recognized` را به‌روزرسانی کنید و کل محتوای تابع را با موارد زیر جایگزین کنید:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    این کد بررسی می‌کند که آیا رویداد تشخیص به دلیل ترجمه گفتار فعال شده است (این رویداد ممکن است در مواقع دیگر نیز فعال شود، مانند زمانی که گفتار تشخیص داده شده اما ترجمه نشده است). اگر گفتار ترجمه شده باشد، ترجمه‌ای را که در دیکشنری `args.result.translations` با زبان سرور مطابقت دارد پیدا می‌کند.

    دیکشنری `args.result.translations` بر اساس بخش زبان تنظیم محلی کلیدگذاری شده است، نه کل تنظیم. برای مثال، اگر ترجمه‌ای به `fr-FR` برای فرانسوی درخواست کنید، دیکشنری شامل یک ورودی برای `fr` خواهد بود، نه `fr-FR`.

    متن ترجمه‌شده سپس به IoT Hub ارسال می‌شود.

1. این کد را اجرا کنید تا ترجمه‌ها را آزمایش کنید. مطمئن شوید که برنامه تابع شما در حال اجرا است و یک تایمر را به زبان کاربر درخواست کنید، یا با صحبت کردن به آن زبان یا با استفاده از یک برنامه ترجمه.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## ترجمه متن با استفاده از سرویس Translator

سرویس گفتار از ترجمه متن به گفتار پشتیبانی نمی‌کند، در عوض می‌توانید از سرویس Translator برای ترجمه متن استفاده کنید. این سرویس یک API REST دارد که می‌توانید از آن برای ترجمه متن استفاده کنید.

### وظیفه - استفاده از منبع Translator برای ترجمه متن

1. کلید API سرویس Translator را زیر `speech_api_key` اضافه کنید:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` را با کلید API منبع سرویس Translator خود جایگزین کنید.

1. بالای تابع `say`، یک تابع به نام `translate_text` تعریف کنید که متن را از زبان سرور به زبان کاربر ترجمه کند:

    ```python
    def translate_text(text):
    ```

1. در داخل این تابع، URL و هدرها را برای فراخوانی API REST تعریف کنید:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL این API به مکان خاصی وابسته نیست، بلکه مکان به‌عنوان یک هدر ارسال می‌شود. کلید API مستقیماً استفاده می‌شود، بنابراین برخلاف سرویس گفتار نیازی به دریافت توکن دسترسی از API صادرکننده توکن نیست.

1. زیر این بخش، پارامترها و بدنه فراخوانی را تعریف کنید:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` پارامترهایی را که باید به فراخوانی API ارسال شوند تعریف می‌کند، و زبان‌های مبدأ و مقصد را مشخص می‌کند. این فراخوانی متن را از زبان `from` به زبان `to` ترجمه می‌کند.

    `body` شامل متنی است که باید ترجمه شود. این یک آرایه است، زیرا چندین بلوک متن می‌توانند در یک فراخوانی ترجمه شوند.

1. فراخوانی API REST را انجام دهید و پاسخ را دریافت کنید:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    پاسخی که بازمی‌گردد یک آرایه JSON است که یک آیتم دارد که شامل ترجمه‌ها است. این آیتم یک آرایه برای ترجمه‌های تمام آیتم‌هایی که در بدنه ارسال شده‌اند دارد.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. ویژگی `text` را از اولین ترجمه از اولین آیتم در آرایه بازگردانید:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. تابع `say` را به‌روزرسانی کنید تا متن را قبل از تولید SSML ترجمه کند:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    این کد همچنین نسخه اصلی و ترجمه‌شده متن را در کنسول چاپ می‌کند.

1. کد خود را اجرا کنید. مطمئن شوید که برنامه تابع شما در حال اجرا است و یک تایمر را به زبان کاربر درخواست کنید، یا با صحبت کردن به آن زبان یا با استفاده از یک برنامه ترجمه.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 به دلیل روش‌های مختلف بیان یک موضوع در زبان‌های مختلف، ممکن است ترجمه‌هایی دریافت کنید که کمی با مثال‌هایی که به LUIS داده‌اید متفاوت باشند. اگر این اتفاق افتاد، مثال‌های بیشتری به LUIS اضافه کنید، دوباره آموزش دهید و سپس مدل را دوباره منتشر کنید.

> 💁 می‌توانید این کد را در پوشه [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) پیدا کنید.

😀 برنامه تایمر چندزبانه شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه انسانی حرفه‌ای استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.