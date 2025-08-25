<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-25T22:39:32+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "fa"
}
-->
# تبدیل متن به گفتار - Wio Terminal

در این بخش از درس، متن را به گفتار تبدیل خواهید کرد تا بازخورد صوتی ارائه دهید.

## تبدیل متن به گفتار

SDK خدمات گفتار که در درس قبلی برای تبدیل گفتار به متن استفاده کردید، می‌تواند برای تبدیل متن به گفتار نیز استفاده شود.

## دریافت لیست صداها

هنگام درخواست گفتار، باید صدایی که می‌خواهید استفاده کنید را مشخص کنید، زیرا گفتار می‌تواند با استفاده از انواع مختلف صداها تولید شود. هر زبان از مجموعه‌ای از صداهای مختلف پشتیبانی می‌کند و می‌توانید لیست صداهای پشتیبانی‌شده برای هر زبان را از SDK خدمات گفتار دریافت کنید. محدودیت‌های میکروکنترلرها در اینجا وارد عمل می‌شوند - درخواست لیست صداهای پشتیبانی‌شده توسط خدمات تبدیل متن به گفتار یک سند JSON با حجم بیش از 77 کیلوبایت است که برای پردازش توسط Wio Terminal بسیار بزرگ است. در زمان نگارش این متن، لیست کامل شامل 215 صدا است که هر کدام توسط یک سند JSON مانند زیر تعریف شده‌اند:

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

این JSON مربوط به صدای **Aria** است که دارای سبک‌های مختلف صدا است. تنها چیزی که برای تبدیل متن به گفتار لازم است، نام کوتاه، `en-US-AriaNeural` است.

به جای دانلود و رمزگشایی این لیست کامل در میکروکنترلر خود، باید کدی بدون سرور بنویسید تا لیست صداهای زبان مورد استفاده خود را بازیابی کنید و این کد را از Wio Terminal خود فراخوانی کنید. سپس کد شما می‌تواند یک صدای مناسب از لیست انتخاب کند، مانند اولین صدایی که پیدا می‌کند.

### وظیفه - ایجاد یک تابع بدون سرور برای دریافت لیست صداها

1. پروژه `smart-timer-trigger` خود را در VS Code باز کنید و ترمینال را باز کنید و مطمئن شوید که محیط مجازی فعال شده است. اگر فعال نیست، ترمینال را ببندید و دوباره ایجاد کنید.

1. فایل `local.settings.json` را باز کنید و تنظیمات مربوط به کلید API گفتار و مکان را اضافه کنید:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    `<key>` را با کلید API برای منبع خدمات گفتار خود جایگزین کنید. `<location>` را با مکانی که هنگام ایجاد منبع خدمات گفتار استفاده کردید جایگزین کنید.

1. یک HTTP trigger جدید به این برنامه اضافه کنید به نام `get-voices` با استفاده از دستور زیر از داخل ترمینال VS Code در پوشه اصلی پروژه برنامه توابع:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    این یک HTTP trigger به نام `get-voices` ایجاد خواهد کرد.

1. محتوای فایل `__init__.py` در پوشه `get-voices` را با موارد زیر جایگزین کنید:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    این کد یک درخواست HTTP به نقطه پایانی برای دریافت صداها ایجاد می‌کند. این لیست صداها یک بلوک بزرگ JSON با صداهای همه زبان‌ها است، بنابراین صداهای زبان ارسال‌شده در بدنه درخواست فیلتر می‌شوند، سپس نام کوتاه استخراج شده و به صورت یک لیست JSON بازگردانده می‌شود. نام کوتاه همان مقداری است که برای تبدیل متن به گفتار لازم است، بنابراین فقط این مقدار بازگردانده می‌شود.

    > 💁 می‌توانید فیلتر را به دلخواه تغییر دهید تا فقط صداهایی که می‌خواهید انتخاب شوند.

    این حجم داده را از 77 کیلوبایت (در زمان نگارش) به یک سند JSON بسیار کوچک‌تر کاهش می‌دهد. به عنوان مثال، برای صداهای ایالات متحده این حجم 408 بایت است.

1. برنامه توابع خود را به صورت محلی اجرا کنید. سپس می‌توانید با استفاده از ابزاری مانند curl این را فراخوانی کنید، همانطور که HTTP trigger `text-to-timer` خود را آزمایش کردید. مطمئن شوید که زبان خود را به عنوان یک بدنه JSON ارسال کنید:

    ```json
    {
        "language":"<language>"
    }
    ```

    `<language>` را با زبان خود جایگزین کنید، مانند `en-GB` یا `zh-CN`.

> 💁 می‌توانید این کد را در پوشه [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) پیدا کنید.

### وظیفه - بازیابی صدا از Wio Terminal خود

1. پروژه `smart-timer` خود را در VS Code باز کنید اگر هنوز باز نشده است.

1. فایل هدر `config.h` را باز کنید و URL برنامه توابع خود را اضافه کنید:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    `<URL>` را با URL برای HTTP trigger `get-voices` در برنامه توابع خود جایگزین کنید. این مقدار همان مقدار `TEXT_TO_TIMER_FUNCTION_URL` خواهد بود، به جز با نام تابع `get-voices` به جای `text-to-timer`.

1. یک فایل جدید در پوشه `src` ایجاد کنید به نام `text_to_speech.h`. این فایل برای تعریف یک کلاس برای تبدیل متن به گفتار استفاده خواهد شد.

1. دستورات include زیر را به بالای فایل جدید `text_to_speech.h` اضافه کنید:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. کد زیر را در زیر این دستورات اضافه کنید تا کلاس `TextToSpeech` را اعلام کنید، همراه با یک نمونه که می‌تواند در بقیه برنامه استفاده شود:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. برای فراخوانی برنامه توابع خود، باید یک WiFi client اعلام کنید. موارد زیر را به بخش `private` کلاس اضافه کنید:

    ```cpp
    WiFiClient _client;
    ```

1. در بخش `private`، یک فیلد برای صدای انتخاب‌شده اضافه کنید:

    ```cpp
    String _voice;
    ```

1. به بخش `public`، یک تابع `init` اضافه کنید که اولین صدا را دریافت کند:

    ```cpp
    void init()
    {
    }
    ```

1. برای دریافت صداها، یک سند JSON باید به برنامه توابع ارسال شود که زبان را مشخص کند. کد زیر را به تابع `init` اضافه کنید تا این سند JSON ایجاد شود:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. سپس یک `HTTPClient` ایجاد کنید و از آن برای فراخوانی برنامه توابع برای دریافت صداها استفاده کنید، سند JSON را ارسال کنید:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. زیر این کد، کدی اضافه کنید تا کد پاسخ را بررسی کند، و اگر 200 (موفقیت) بود، لیست صداها استخراج شود و اولین صدا از لیست بازیابی شود:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. پس از این، اتصال HTTP client را پایان دهید:

    ```cpp
    httpClient.end();
    ```

1. فایل `main.cpp` را باز کنید و دستور include زیر را به بالای فایل اضافه کنید تا این فایل هدر جدید را شامل شود:

    ```cpp
    #include "text_to_speech.h"
    ```

1. در تابع `setup`، زیر فراخوانی `speechToText.init();`، موارد زیر را اضافه کنید تا کلاس `TextToSpeech` را مقداردهی اولیه کنید:

    ```cpp
    textToSpeech.init();
    ```

1. کد را بسازید، آن را به Wio Terminal خود آپلود کنید و از طریق مانیتور سریال آن را آزمایش کنید. مطمئن شوید که برنامه توابع شما در حال اجرا است.

    لیست صداهای موجود که از برنامه توابع بازگردانده شده‌اند، همراه با صدای انتخاب‌شده را مشاهده خواهید کرد.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## تبدیل متن به گفتار

پس از داشتن یک صدا برای استفاده، می‌توان از آن برای تبدیل متن به گفتار استفاده کرد. محدودیت‌های حافظه مشابه با صداها هنگام تبدیل گفتار به متن نیز اعمال می‌شوند، بنابراین باید گفتار را روی یک کارت SD ذخیره کنید تا بتوان آن را از طریق ReSpeaker پخش کرد.

> 💁 در درس‌های قبلی این پروژه از حافظه فلش برای ذخیره گفتار ضبط‌شده از میکروفون استفاده کردید. این درس از کارت SD استفاده می‌کند زیرا پخش صدا از آن با استفاده از کتابخانه‌های صوتی Seeed آسان‌تر است.

همچنین محدودیت دیگری وجود دارد که باید در نظر گرفته شود، داده‌های صوتی موجود از خدمات گفتار و فرمت‌هایی که Wio Terminal پشتیبانی می‌کند. برخلاف کامپیوترهای کامل، کتابخانه‌های صوتی برای میکروکنترلرها ممکن است بسیار محدود باشند. به عنوان مثال، کتابخانه صوتی Seeed Arduino که می‌تواند صدا را از طریق ReSpeaker پخش کند، فقط از صدا با نرخ نمونه‌برداری 44.1KHz پشتیبانی می‌کند. خدمات گفتار Azure می‌توانند صدا را در چندین فرمت ارائه دهند، اما هیچ‌کدام از آن‌ها از این نرخ نمونه‌برداری استفاده نمی‌کنند، آن‌ها فقط 8KHz، 16KHz، 24KHz و 48KHz ارائه می‌دهند. این بدان معناست که صدا باید به 44.1KHz بازنمونه‌برداری شود، چیزی که به منابع بیشتری نسبت به Wio Terminal نیاز دارد، به ویژه حافظه.

هنگام نیاز به دستکاری داده‌هایی مانند این، اغلب بهتر است از کد بدون سرور استفاده کنید، به ویژه اگر داده‌ها از طریق یک فراخوانی وب دریافت شوند. Wio Terminal می‌تواند یک تابع بدون سرور را فراخوانی کند، متن را برای تبدیل ارسال کند، و تابع بدون سرور می‌تواند هم خدمات گفتار را برای تبدیل متن به گفتار فراخوانی کند و هم صدا را به نرخ نمونه‌برداری مورد نیاز بازنمونه‌برداری کند. سپس می‌تواند صدا را به شکلی که Wio Terminal نیاز دارد بازگرداند تا روی کارت SD ذخیره شود و از طریق ReSpeaker پخش شود.

### وظیفه - ایجاد یک تابع بدون سرور برای تبدیل متن به گفتار

1. پروژه `smart-timer-trigger` خود را در VS Code باز کنید و ترمینال را باز کنید و مطمئن شوید که محیط مجازی فعال شده است. اگر فعال نیست، ترمینال را ببندید و دوباره ایجاد کنید.

1. یک HTTP trigger جدید به این برنامه اضافه کنید به نام `text-to-speech` با استفاده از دستور زیر از داخل ترمینال VS Code در پوشه اصلی پروژه برنامه توابع:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    این یک HTTP trigger به نام `text-to-speech` ایجاد خواهد کرد.

1. بسته Pip [librosa](https://librosa.org) دارای توابعی برای بازنمونه‌برداری صدا است، بنابراین آن را به فایل `requirements.txt` اضافه کنید:

    ```sh
    librosa
    ```

    پس از اضافه کردن این مورد، بسته‌های Pip را با استفاده از دستور زیر از ترمینال VS Code نصب کنید:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ اگر از لینوکس، از جمله Raspberry Pi OS استفاده می‌کنید، ممکن است نیاز به نصب `libsndfile` با دستور زیر داشته باشید:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. برای تبدیل متن به گفتار، نمی‌توانید مستقیماً از کلید API گفتار استفاده کنید، بلکه باید یک توکن دسترسی درخواست کنید، با استفاده از کلید API برای احراز هویت درخواست توکن دسترسی. فایل `__init__.py` را از پوشه `text-to-speech` باز کنید و تمام کد موجود در آن را با موارد زیر جایگزین کنید:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    این ثابت‌هایی برای مکان و کلید گفتار تعریف می‌کند که از تنظیمات خوانده می‌شوند. سپس تابع `get_access_token` را تعریف می‌کند که یک توکن دسترسی برای خدمات گفتار بازیابی می‌کند.

1. زیر این کد، موارد زیر را اضافه کنید:

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    این HTTP trigger را تعریف می‌کند که متن را به گفتار تبدیل می‌کند. متن برای تبدیل، زبان و صدا از بدنه JSON ارسال‌شده به درخواست استخراج می‌شود، مقداری SSML برای درخواست گفتار ایجاد می‌کند، سپس REST API مربوطه را با احراز هویت با استفاده از توکن دسترسی فراخوانی می‌کند. این فراخوانی REST API صدا را به صورت فایل WAV مونو 16 بیتی، 48KHz رمزگذاری‌شده بازمی‌گرداند، که توسط مقدار `playback_format` تعریف شده است که به فراخوانی REST API ارسال می‌شود.

    سپس این صدا توسط `librosa` از نرخ نمونه‌برداری 48KHz به نرخ نمونه‌برداری 44.1KHz بازنمونه‌برداری می‌شود، سپس این صدا در یک بافر باینری ذخیره می‌شود که سپس بازگردانده می‌شود.

1. برنامه توابع خود را به صورت محلی اجرا کنید یا آن را در فضای ابری مستقر کنید. سپس می‌توانید با استفاده از ابزاری مانند curl این را فراخوانی کنید، همانطور که HTTP trigger `text-to-timer` خود را آزمایش کردید. مطمئن شوید که زبان، صدا و متن را به عنوان بدنه JSON ارسال کنید:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    `<language>` را با زبان خود جایگزین کنید، مانند `en-GB` یا `zh-CN`. `<voice>` را با صدایی که می‌خواهید استفاده کنید جایگزین کنید. `<text>` را با متنی که می‌خواهید به گفتار تبدیل کنید جایگزین کنید. می‌توانید خروجی را در یک فایل ذخیره کنید و آن را با هر پخش‌کننده صوتی که می‌تواند فایل‌های WAV را پخش کند، پخش کنید.

    به عنوان مثال، برای تبدیل "Hello" به گفتار با استفاده از انگلیسی آمریکایی با صدای Jenny Neural، با برنامه توابع در حال اجرا به صورت محلی، می‌توانید از دستور curl زیر استفاده کنید:

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    این صدا را در فایل `hello.wav` در دایرکتوری فعلی ذخیره خواهد کرد.

> 💁 می‌توانید این کد را در پوشه [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) پیدا کنید.

### وظیفه - بازیابی گفتار از Wio Terminal خود

1. پروژه `smart-timer` خود را در VS Code باز کنید اگر هنوز باز نشده است.

1. فایل هدر `config.h` را باز کنید و URL برنامه توابع خود را اضافه کنید:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    `<URL>` را با URL برای HTTP trigger `text-to-speech` در برنامه توابع خود جایگزین کنید. این مقدار همان مقدار `TEXT_TO_TIMER_FUNCTION_URL` خواهد بود، به جز با نام تابع `text-to-speech` به جای `text-to-timer`.

1. فایل هدر `text_to_speech.h` را باز کنید و روش زیر را به بخش `public` کلاس `TextToSpeech` اضافه کنید:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. به روش `convertTextToSpeech`، کد زیر را اضافه کنید تا JSON برای ارسال به برنامه توابع ایجاد شود:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    این زبان، صدا و متن را به سند JSON می‌نویسد، سپس آن را به یک رشته سریال‌سازی می‌کند.

1. زیر این، کد زیر را اضافه کنید تا برنامه توابع را فراخوانی کند:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    این یک HTTPClient ایجاد می‌کند، سپس یک درخواست POST با استفاده از سند JSON به HTTP trigger تبدیل متن به گفتار ارسال می‌کند.

1. اگر فراخوانی موفقیت‌آمیز باشد، داده‌های باینری خام بازگردانده‌شده از فراخوانی برنامه توابع می‌تواند به یک فایل روی کارت SD جریان داده شود. کد زیر را اضافه کنید تا این کار انجام شود:

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    این کد پاسخ را بررسی می‌کند و اگر 200 (موفقیت) بود، داده‌های باینری به یک فایل در ریشه کارت SD به نام `SPEECH.WAV` جریان داده می‌شود.

1. در انتهای این روش، اتصال HTTP را ببندید:

    ```cpp
    httpClient.end();
    ```

1. اکنون متن برای گفتن می‌تواند به صدا تبدیل شود. در فایل `main.cpp`، خط زیر را به انتهای تابع `say` اضافه کنید تا متن برای گفتن به صدا تبدیل شود:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### وظیفه - پخش صدا از Wio Terminal

**به زودی**

## استقرار برنامه توابع در فضای ابری

دلیل اجرای برنامه توابع به صورت محلی این است که بسته `librosa` در لینوکس به کتابخانه‌ای وابسته است که به صورت پیش‌فرض نصب نشده و باید قبل از اجرای برنامه توابع نصب شود. برنامه‌های توابع بدون سرور هستند - یعنی سروری وجود ندارد که بتوانید خودتان مدیریت کنید، بنابراین راهی برای نصب این کتابخانه از قبل وجود ندارد.

راه‌حل این است که برنامه توابع خود را با استفاده از یک کانتینر Docker مستقر کنید. این کانتینر توسط فضای ابری هر زمان که نیاز به ایجاد یک نمونه جدید از برنامه توابع شما باشد (مانند زمانی که تقاضا از منابع موجود بیشتر شود، یا اگر برنامه توابع برای مدتی استفاده نشده و بسته شده باشد) مستقر می‌شود.

می‌توانید دستورالعمل‌های ایجاد یک برنامه توابع و استقرار آن از طریق Docker را در [مستندات ایجاد یک تابع در لینوکس با استفاده از یک کانتینر سفارشی در Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python) پیدا کنید.

پس از استقرار، می‌توانید کد Wio Terminal خود را برای دسترسی به این تابع منتقل کنید:

1. گواهی Azure Functions را به `config.h` اضافه کنید:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. تمام موارد شامل `<WiFiClient.h>` را به `<WiFiClientSecure.h>` تغییر دهید.

1. تمام فیلدهای `WiFiClient` را به `WiFiClientSecure` تغییر دهید.

1. در هر کلاسی که یک فیلد `WiFiClientSecure` دارد، یک سازنده اضافه کنید و گواهی را در آن سازنده تنظیم کنید:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه حرفه‌ای انسانی استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.