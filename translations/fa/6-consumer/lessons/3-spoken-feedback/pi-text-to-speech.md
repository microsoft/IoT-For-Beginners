<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-25T22:38:03+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "fa"
}
-->
# تبدیل متن به گفتار - رزبری پای

در این بخش از درس، شما کدی خواهید نوشت که متن را با استفاده از سرویس گفتار به گفتار تبدیل کند.

## تبدیل متن به گفتار با استفاده از سرویس گفتار

متن می‌تواند با استفاده از API REST به سرویس گفتار ارسال شود تا به صورت یک فایل صوتی دریافت شود که می‌توان آن را روی دستگاه IoT شما پخش کرد. هنگام درخواست گفتار، باید صدایی که می‌خواهید استفاده کنید را مشخص کنید، زیرا گفتار می‌تواند با استفاده از انواع مختلف صداها تولید شود.

هر زبان از مجموعه‌ای از صداهای مختلف پشتیبانی می‌کند و شما می‌توانید یک درخواست REST به سرویس گفتار ارسال کنید تا لیست صداهای پشتیبانی‌شده برای هر زبان را دریافت کنید.

### وظیفه - دریافت یک صدا

1. پروژه `smart-timer` را در VS Code باز کنید.

1. کد زیر را بالای تابع `say` اضافه کنید تا لیست صداها برای یک زبان درخواست شود:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    این کد یک تابع به نام `get_voice` تعریف می‌کند که از سرویس گفتار برای دریافت لیست صداها استفاده می‌کند. سپس اولین صدایی که با زبان مورد استفاده مطابقت دارد را پیدا می‌کند.

    این تابع سپس فراخوانی می‌شود تا اولین صدا ذخیره شود و نام صدا در کنسول چاپ شود. این صدا می‌تواند یک بار درخواست شود و مقدار آن برای هر فراخوانی به منظور تبدیل متن به گفتار استفاده شود.

    > 💁 شما می‌توانید لیست کامل صداهای پشتیبانی‌شده را از [مستندات پشتیبانی زبان و صدا در Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) دریافت کنید. اگر می‌خواهید از یک صدای خاص استفاده کنید، می‌توانید این تابع را حذف کرده و نام صدا را از این مستندات به صورت ثابت وارد کنید. برای مثال:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### وظیفه - تبدیل متن به گفتار

1. در زیر این بخش، یک ثابت برای فرمت صوتی که از سرویس گفتار دریافت می‌شود تعریف کنید. هنگام درخواست صوت، می‌توانید آن را در قالب‌های مختلف دریافت کنید.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    فرمت مورد استفاده شما به سخت‌افزار شما بستگی دارد. اگر هنگام پخش صوت خطاهایی مانند `Invalid sample rate` دریافت کردید، این مقدار را به مقدار دیگری تغییر دهید. لیست مقادیر پشتیبانی‌شده را می‌توانید در [مستندات API REST تبدیل متن به گفتار در Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs) پیدا کنید. شما باید از فرمت صوتی `riff` استفاده کنید و مقادیر قابل امتحان عبارتند از `riff-16khz-16bit-mono-pcm`، `riff-24khz-16bit-mono-pcm` و `riff-48khz-16bit-mono-pcm`.

1. در زیر این بخش، یک تابع به نام `get_speech` تعریف کنید که متن را با استفاده از API REST سرویس گفتار به گفتار تبدیل کند:

    ```python
    def get_speech(text):
    ```

1. در تابع `get_speech`، URL فراخوانی و هدرهایی که باید ارسال شوند را تعریف کنید:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    این بخش هدرها را تنظیم می‌کند تا از یک توکن دسترسی تولید‌شده استفاده کند، محتوا را به SSML تنظیم کند و فرمت صوتی مورد نیاز را تعریف کند.

1. در زیر این بخش، SSML را که باید به API REST ارسال شود تعریف کنید:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    این SSML زبان و صدای مورد استفاده را تنظیم می‌کند، همراه با متنی که باید تبدیل شود.

1. در نهایت، کدی در این تابع اضافه کنید تا درخواست REST انجام شود و داده‌های صوتی باینری بازگردانده شود:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### وظیفه - پخش صوت

1. در زیر تابع `get_speech`، یک تابع جدید برای پخش صوت بازگردانده‌شده توسط فراخوانی API REST تعریف کنید:

    ```python
    def play_speech(speech):
    ```

1. صوتی که به این تابع ارسال می‌شود داده‌های صوتی باینری بازگردانده‌شده از API REST خواهد بود. از کد زیر استفاده کنید تا این داده‌ها را به عنوان یک فایل wave باز کنید و آن را به PyAudio ارسال کنید تا صوت پخش شود:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    این کد از یک جریان PyAudio استفاده می‌کند، مشابه ضبط صوت. تفاوت اینجا این است که جریان به عنوان یک جریان خروجی تنظیم شده است و داده‌ها از داده‌های صوتی خوانده شده و به جریان ارسال می‌شوند.

    به جای تنظیم جزئیات جریان مانند نرخ نمونه‌برداری به صورت ثابت، این جزئیات از داده‌های صوتی خوانده می‌شود.

1. محتوای تابع `say` را با کد زیر جایگزین کنید:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    این کد متن را به گفتار به صورت داده‌های صوتی باینری تبدیل می‌کند و صوت را پخش می‌کند.

1. برنامه را اجرا کنید و مطمئن شوید که برنامه تابع نیز در حال اجرا است. چند تایمر تنظیم کنید و خواهید شنید که یک پاسخ صوتی می‌گوید تایمر شما تنظیم شده است، سپس یک پاسخ صوتی دیگر زمانی که تایمر کامل شد.

    اگر خطاهایی مانند `Invalid sample rate` دریافت کردید، `playback_format` را همانطور که در بالا توضیح داده شد تغییر دهید.

> 💁 شما می‌توانید این کد را در پوشه [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) پیدا کنید.

😀 برنامه تایمر شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه حرفه‌ای انسانی استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.