<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-25T22:40:36+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "fa"
}
-->
# تبدیل متن به گفتار - دستگاه مجازی IoT

در این بخش از درس، شما کدی خواهید نوشت که متن را به گفتار تبدیل کند با استفاده از سرویس گفتار.

## تبدیل متن به گفتار

SDK سرویس‌های گفتار که در درس قبلی برای تبدیل گفتار به متن استفاده کردید، می‌تواند برای تبدیل متن به گفتار نیز استفاده شود. هنگام درخواست گفتار، باید صدایی که می‌خواهید استفاده کنید را مشخص کنید، زیرا گفتار می‌تواند با استفاده از انواع مختلف صداها تولید شود.

هر زبان از مجموعه‌ای از صداهای مختلف پشتیبانی می‌کند، و شما می‌توانید لیست صداهای پشتیبانی‌شده برای هر زبان را از SDK سرویس‌های گفتار دریافت کنید.

### وظیفه - تبدیل متن به گفتار

1. پروژه `smart-timer` را در VS Code باز کنید و مطمئن شوید که محیط مجازی در ترمینال بارگذاری شده است.

1. `SpeechSynthesizer` را از بسته `azure.cognitiveservices.speech` وارد کنید و آن را به واردات موجود اضافه کنید:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. بالای تابع `say`، یک پیکربندی گفتار برای استفاده با گفتارساز ایجاد کنید:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    این از همان کلید API، مکان و زبان استفاده می‌کند که توسط تشخیص‌دهنده استفاده شده بود.

1. در زیر این بخش، کد زیر را اضافه کنید تا یک صدا دریافت کرده و آن را روی پیکربندی گفتار تنظیم کنید:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    این لیستی از تمام صداهای موجود را دریافت می‌کند، سپس اولین صدایی که با زبان مورد استفاده مطابقت دارد را پیدا می‌کند.

    > 💁 شما می‌توانید لیست کامل صداهای پشتیبانی‌شده را از [مستندات پشتیبانی زبان و صدا در Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) دریافت کنید. اگر می‌خواهید از یک صدای خاص استفاده کنید، می‌توانید این تابع را حذف کرده و صدای مورد نظر را به صورت دستی از نام صدا در این مستندات تنظیم کنید. برای مثال:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. محتوای تابع `say` را به‌روزرسانی کنید تا SSML برای پاسخ تولید شود:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. در زیر این بخش، تشخیص گفتار را متوقف کنید، SSML را بخوانید، سپس تشخیص را دوباره شروع کنید:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    تشخیص در حالی که متن خوانده می‌شود متوقف می‌شود تا از تشخیص اعلام شروع تایمر جلوگیری شود، که ممکن است به LUIS ارسال شده و به اشتباه به عنوان درخواست تنظیم تایمر جدید تفسیر شود.

    > 💁 شما می‌توانید این را با کامنت‌گذاری خطوط توقف و شروع مجدد تشخیص آزمایش کنید. یک تایمر تنظیم کنید، و ممکن است متوجه شوید که اعلامیه تایمر جدیدی تنظیم می‌کند، که باعث اعلامیه جدیدی می‌شود، و این روند به طور بی‌پایان ادامه پیدا می‌کند!

1. برنامه را اجرا کنید و مطمئن شوید که برنامه تابع نیز در حال اجرا است. چند تایمر تنظیم کنید، و خواهید شنید که یک پاسخ گفتاری اعلام می‌کند که تایمر شما تنظیم شده است، سپس یک پاسخ گفتاری دیگر زمانی که تایمر کامل می‌شود.

> 💁 شما می‌توانید این کد را در پوشه [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) پیدا کنید.

😀 برنامه تایمر شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه انسانی حرفه‌ای استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.