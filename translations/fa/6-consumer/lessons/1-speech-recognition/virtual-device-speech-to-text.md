<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-25T22:45:30+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "fa"
}
-->
# تبدیل گفتار به متن - دستگاه مجازی اینترنت اشیا

در این بخش از درس، شما کدی خواهید نوشت که گفتاری که از میکروفون شما ضبط شده است را با استفاده از سرویس گفتار به متن تبدیل می‌کند.

## تبدیل گفتار به متن

در سیستم‌عامل‌های ویندوز، لینوکس و macOS، می‌توانید از Python SDK سرویس‌های گفتار استفاده کنید تا به میکروفون گوش دهید و هر گفتاری که شناسایی می‌شود را به متن تبدیل کنید. این ابزار به صورت مداوم گوش می‌دهد، سطح صدا را تشخیص می‌دهد و زمانی که سطح صدا کاهش می‌یابد (مانند پایان یک بلوک گفتار)، گفتار را برای تبدیل به متن ارسال می‌کند.

### وظیفه - تبدیل گفتار به متن

1. یک اپلیکیشن جدید پایتون در کامپیوتر خود ایجاد کنید. این اپلیکیشن را در پوشه‌ای به نام `smart-timer` با یک فایل به نام `app.py` و یک محیط مجازی پایتون ایجاد کنید.

1. بسته Pip مربوط به سرویس‌های گفتار را نصب کنید. مطمئن شوید که این کار را از یک ترمینال با محیط مجازی فعال انجام می‌دهید.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ اگر با خطای زیر مواجه شدید:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > باید Pip را به‌روزرسانی کنید. این کار را با دستور زیر انجام دهید و سپس دوباره تلاش کنید بسته را نصب کنید:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. واردات زیر را به فایل `app.py` اضافه کنید:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    این کد برخی از کلاس‌هایی که برای شناسایی گفتار استفاده می‌شوند را وارد می‌کند.

1. کد زیر را برای تعریف برخی تنظیمات اضافه کنید:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    `<key>` را با کلید API سرویس گفتار خود جایگزین کنید. `<location>` را با موقعیتی که هنگام ایجاد منبع سرویس گفتار استفاده کرده‌اید جایگزین کنید.

    `<language>` را با نام محلی زبانی که در آن صحبت می‌کنید جایگزین کنید، برای مثال `en-GB` برای انگلیسی یا `zn-HK` برای کانتونی. می‌توانید لیست زبان‌های پشتیبانی‌شده و نام‌های محلی آن‌ها را در [مستندات پشتیبانی زبان و صدا در Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) پیدا کنید.

    این تنظیمات برای ایجاد یک شیء `SpeechConfig` استفاده می‌شود که سرویس‌های گفتار را پیکربندی می‌کند.

1. کد زیر را برای ایجاد یک تشخیص‌دهنده گفتار اضافه کنید:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. تشخیص‌دهنده گفتار روی یک رشته پس‌زمینه اجرا می‌شود، به صدا گوش می‌دهد و هر گفتاری که در آن شناسایی شود را به متن تبدیل می‌کند. شما می‌توانید متن را با استفاده از یک تابع callback دریافت کنید - تابعی که تعریف می‌کنید و به تشخیص‌دهنده ارسال می‌کنید. هر بار که گفتار شناسایی می‌شود، این تابع فراخوانی می‌شود. کد زیر را برای تعریف یک callback اضافه کنید و این callback را به تشخیص‌دهنده ارسال کنید. همچنین یک تابع برای پردازش متن تعریف کنید که متن را در کنسول بنویسد:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. تشخیص‌دهنده فقط زمانی شروع به گوش دادن می‌کند که به صورت صریح آن را شروع کنید. کد زیر را برای شروع تشخیص اضافه کنید. این کد در پس‌زمینه اجرا می‌شود، بنابراین برنامه شما به یک حلقه بی‌نهایت نیاز دارد که بخوابد تا برنامه در حال اجرا باقی بماند.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. این اپلیکیشن را اجرا کنید. در میکروفون خود صحبت کنید و صدای تبدیل‌شده به متن در کنسول نمایش داده خواهد شد.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    جملات مختلف را امتحان کنید، همراه با جملاتی که کلمات مشابهی دارند اما معانی متفاوتی دارند. برای مثال، اگر به زبان انگلیسی صحبت می‌کنید، بگویید "I want to buy two bananas and an apple too" و توجه کنید که چگونه از "to"، "two" و "too" به درستی بر اساس زمینه کلمه استفاده می‌کند، نه فقط صدای آن.

> 💁 می‌توانید این کد را در پوشه [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) پیدا کنید.

😀 برنامه تبدیل گفتار به متن شما با موفقیت اجرا شد!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حیاتی، ترجمه حرفه‌ای انسانی توصیه می‌شود. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.