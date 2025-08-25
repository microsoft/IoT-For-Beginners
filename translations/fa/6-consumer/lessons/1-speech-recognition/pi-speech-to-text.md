<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-25T22:51:24+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "fa"
}
-->
# تبدیل گفتار به متن - رزبری پای

در این بخش از درس، شما کدی خواهید نوشت که گفتار ضبط‌شده در فایل صوتی را به متن تبدیل کند، با استفاده از سرویس گفتار.

## ارسال فایل صوتی به سرویس گفتار

فایل صوتی می‌تواند با استفاده از REST API به سرویس گفتار ارسال شود. برای استفاده از سرویس گفتار، ابتدا باید یک توکن دسترسی درخواست کنید و سپس از آن توکن برای دسترسی به REST API استفاده کنید. این توکن‌های دسترسی پس از ۱۰ دقیقه منقضی می‌شوند، بنابراین کد شما باید به طور منظم توکن جدید درخواست کند تا همیشه به‌روز باشد.

### وظیفه - دریافت توکن دسترسی

1. پروژه `smart-timer` را روی رزبری پای خود باز کنید.

1. تابع `play_audio` را حذف کنید. دیگر نیازی به این تابع نیست، زیرا نمی‌خواهید تایمر هوشمند آنچه را که گفتید به شما بازگو کند.

1. وارد زیر را به بالای فایل `app.py` اضافه کنید:

    ```python
    import requests
    ```

1. کد زیر را بالای حلقه `while True` اضافه کنید تا برخی تنظیمات برای سرویس گفتار تعریف شود:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    `<key>` را با کلید API برای منبع سرویس گفتار خود جایگزین کنید. `<location>` را با مکانی که هنگام ایجاد منبع سرویس گفتار استفاده کردید جایگزین کنید.

    `<language>` را با نام محلی زبان مورد نظر خود جایگزین کنید، برای مثال `en-GB` برای انگلیسی یا `zn-HK` برای کانتونی. می‌توانید لیستی از زبان‌های پشتیبانی‌شده و نام‌های محلی آن‌ها را در [مستندات پشتیبانی زبان و صدا در Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) پیدا کنید.

1. زیر این بخش، تابع زیر را برای دریافت توکن دسترسی اضافه کنید:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    این تابع یک نقطه پایانی صدور توکن را فراخوانی می‌کند و کلید API را به عنوان هدر ارسال می‌کند. این فراخوانی یک توکن دسترسی بازمی‌گرداند که می‌توان از آن برای فراخوانی سرویس‌های گفتار استفاده کرد.

1. زیر این بخش، یک تابع برای تبدیل گفتار ضبط‌شده در فایل صوتی به متن با استفاده از REST API تعریف کنید:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. داخل این تابع، URL و هدرهای REST API را تنظیم کنید:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    این کد یک URL با استفاده از مکان منبع سرویس گفتار ایجاد می‌کند. سپس هدرها را با توکن دسترسی از تابع `get_access_token`، به همراه نرخ نمونه‌برداری استفاده‌شده برای ضبط فایل صوتی، پر می‌کند. در نهایت، برخی پارامترها را برای ارسال همراه با URL تعریف می‌کند که شامل زبان فایل صوتی است.

1. زیر این بخش، کد زیر را برای فراخوانی REST API و دریافت متن اضافه کنید:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    این کد URL را فراخوانی می‌کند و مقدار JSON که در پاسخ دریافت می‌شود را رمزگشایی می‌کند. مقدار `RecognitionStatus` در پاسخ نشان می‌دهد که آیا فراخوانی توانسته است گفتار را با موفقیت به متن تبدیل کند یا خیر، و اگر این مقدار `Success` باشد، متن از تابع بازگردانده می‌شود، در غیر این صورت یک رشته خالی بازگردانده می‌شود.

1. بالای حلقه `while True:`، یک تابع برای پردازش متن بازگردانده‌شده از سرویس تبدیل گفتار به متن تعریف کنید. این تابع فعلاً فقط متن را در کنسول چاپ می‌کند.

    ```python
    def process_text(text):
        print(text)
    ```

1. در نهایت، فراخوانی `play_audio` در حلقه `while True` را با فراخوانی تابع `convert_speech_to_text` جایگزین کنید و متن را به تابع `process_text` ارسال کنید:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. کد را اجرا کنید. دکمه را فشار دهید و در میکروفون صحبت کنید. وقتی صحبتتان تمام شد، دکمه را رها کنید و فایل صوتی به متن تبدیل شده و در کنسول چاپ خواهد شد.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    جملات مختلف را امتحان کنید، همراه با جملاتی که کلمات مشابهی دارند اما معانی متفاوتی دارند. برای مثال، اگر به زبان انگلیسی صحبت می‌کنید، بگویید "I want to buy two bananas and an apple too"، و توجه کنید که چگونه از کلمات صحیح "to"، "two" و "too" بر اساس زمینه کلمه استفاده می‌کند، نه فقط صدای آن.

> 💁 شما می‌توانید این کد را در پوشه [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) پیدا کنید.

😀 برنامه تبدیل گفتار به متن شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه انسانی حرفه‌ای استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.