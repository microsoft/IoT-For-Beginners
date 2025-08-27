<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T00:15:37+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "ur"
}
-->
# وائیو ٹرمینل - متن کو آواز میں تبدیل کریں

اس سبق کے اس حصے میں، آپ متن کو آواز میں تبدیل کریں گے تاکہ بولی جانے والی رائے فراہم کی جا سکے۔

## متن کو آواز میں تبدیل کریں

پچھلے سبق میں استعمال کردہ اسپیک سروسز SDK، جو آواز کو متن میں تبدیل کرتا ہے، متن کو دوبارہ آواز میں تبدیل کرنے کے لیے بھی استعمال کیا جا سکتا ہے۔

## آوازوں کی فہرست حاصل کریں

جب آواز کی درخواست کی جاتی ہے، تو آپ کو استعمال کرنے کے لیے آواز فراہم کرنی ہوگی کیونکہ مختلف آوازوں کے ذریعے آواز پیدا کی جا سکتی ہے۔ ہر زبان مختلف آوازوں کی ایک رینج کو سپورٹ کرتی ہے، اور آپ اسپیک سروسز SDK سے ہر زبان کے لیے سپورٹ شدہ آوازوں کی فہرست حاصل کر سکتے ہیں۔ یہاں مائیکرو کنٹرولرز کی حدود سامنے آتی ہیں - متن کو آواز میں تبدیل کرنے کی خدمات کے ذریعے سپورٹ شدہ آوازوں کی فہرست حاصل کرنے کے لیے کال ایک JSON دستاویز ہے جو 77KB سے زیادہ ہے، جو وائیو ٹرمینل کے ذریعے پروسیس کرنے کے لیے بہت بڑی ہے۔ اس وقت، مکمل فہرست میں 215 آوازیں شامل ہیں، ہر ایک کو ایک JSON دستاویز کے ذریعے بیان کیا گیا ہے جیسے کہ درج ذیل:

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

یہ JSON **Aria** آواز کے لیے ہے، جس کے پاس متعدد آواز کے انداز ہیں۔ متن کو آواز میں تبدیل کرتے وقت صرف `en-US-AriaNeural` جیسے shortname کی ضرورت ہوتی ہے۔

پورے فہرست کو مائیکرو کنٹرولر پر ڈاؤن لوڈ اور ڈی کوڈ کرنے کے بجائے، آپ کو کچھ مزید سرور لیس کوڈ لکھنے کی ضرورت ہوگی تاکہ آپ کی زبان کے لیے آوازوں کی فہرست حاصل کی جا سکے، اور اسے وائیو ٹرمینل سے کال کریں۔ آپ کا کوڈ پھر فہرست سے مناسب آواز منتخب کر سکتا ہے، جیسے کہ پہلی آواز جو اسے ملتی ہے۔

### کام - آوازوں کی فہرست حاصل کرنے کے لیے سرور لیس فنکشن بنائیں

1. اپنے `smart-timer-trigger` پروجیکٹ کو VS کوڈ میں کھولیں، اور ٹرمینل کھولیں، یہ یقینی بناتے ہوئے کہ ورچوئل ماحول فعال ہے۔ اگر نہیں، تو ٹرمینل کو ختم کریں اور دوبارہ بنائیں۔

1. `local.settings.json` فائل کھولیں اور اسپیک API کلید اور مقام کے لیے سیٹنگز شامل کریں:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    `<key>` کو اپنے اسپیک سروس ریسورس کے API کلید سے تبدیل کریں۔ `<location>` کو اس مقام سے تبدیل کریں جو آپ نے اسپیک سروس ریسورس بناتے وقت استعمال کیا تھا۔

1. اس ایپ میں ایک نیا HTTP ٹرگر شامل کریں جسے `get-voices` کہا جاتا ہے، درج ذیل کمانڈ کو VS کوڈ ٹرمینل میں فنکشنز ایپ پروجیکٹ کے روٹ فولڈر کے اندر استعمال کریں:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    یہ ایک HTTP ٹرگر بنائے گا جسے `get-voices` کہا جاتا ہے۔

1. `get-voices` فولڈر میں `__init__.py` فائل کے مواد کو درج ذیل سے تبدیل کریں:

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

    یہ کوڈ اسپیک سروسز کے اینڈ پوائنٹ پر آوازوں کی فہرست حاصل کرنے کے لیے HTTP درخواست کرتا ہے۔ یہ آوازوں کی فہرست تمام زبانوں کے لیے ایک بڑا JSON بلاک ہے، لہذا درخواست کے جسم میں دی گئی زبان کے لیے آوازوں کو فلٹر کیا جاتا ہے، پھر shortname نکالا جاتا ہے اور JSON فہرست کے طور پر واپس کیا جاتا ہے۔ shortname وہ قدر ہے جو متن کو آواز میں تبدیل کرنے کے لیے ضروری ہے، لہذا صرف یہی قدر واپس کی جاتی ہے۔

    > 💁 آپ فلٹر کو اپنی ضرورت کے مطابق تبدیل کر سکتے ہیں تاکہ صرف وہ آوازیں منتخب کریں جو آپ چاہتے ہیں۔

    یہ ڈیٹا کے سائز کو 77KB (لکھنے کے وقت) سے ایک چھوٹے JSON دستاویز میں کم کر دیتا ہے۔ مثال کے طور پر، امریکی آوازوں کے لیے یہ 408 بائٹس ہے۔

1. اپنی فنکشن ایپ کو مقامی طور پر چلائیں۔ آپ اسے curl جیسے ٹول کا استعمال کرتے ہوئے اسی طرح کال کر سکتے ہیں جیسے آپ نے اپنے `text-to-timer` HTTP ٹرگر کو ٹیسٹ کیا تھا۔ اپنی زبان کو JSON جسم کے طور پر پاس کرنا یقینی بنائیں:

    ```json
    {
        "language":"<language>"
    }
    ```

    `<language>` کو اپنی زبان سے تبدیل کریں، جیسے `en-GB` یا `zh-CN`۔

> 💁 آپ اس کوڈ کو [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) فولڈر میں تلاش کر سکتے ہیں۔

### کام - وائیو ٹرمینل سے آواز حاصل کریں

1. اگر `smart-timer` پروجیکٹ پہلے سے کھلا نہیں ہے تو اسے VS کوڈ میں کھولیں۔

1. `config.h` ہیڈر فائل کھولیں اور اپنی فنکشن ایپ کے لیے URL شامل کریں:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    `<URL>` کو اپنی فنکشن ایپ کے `get-voices` HTTP ٹرگر کے URL سے تبدیل کریں۔ یہ `TEXT_TO_TIMER_FUNCTION_URL` کی قدر جیسا ہی ہوگا، سوائے فنکشن کے نام `get-voices` کے بجائے `text-to-timer`۔

1. `src` فولڈر میں ایک نئی فائل بنائیں جسے `text_to_speech.h` کہا جاتا ہے۔ یہ متن کو آواز میں تبدیل کرنے کے لیے ایک کلاس کو ڈیفائن کرنے کے لیے استعمال کی جائے گی۔

1. نئی `text_to_speech.h` فائل کے اوپر درج ذیل شامل کریں:

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

1. اس کے نیچے درج ذیل کوڈ شامل کریں تاکہ `TextToSpeech` کلاس کو ڈیفائن کیا جا سکے، ساتھ ہی ایک انسٹینس جو ایپلیکیشن کے باقی حصے میں استعمال کیا جا سکتا ہے:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. اپنی فنکشن ایپ کو کال کرنے کے لیے، آپ کو ایک WiFi کلائنٹ ڈیفائن کرنا ہوگا۔ کلاس کے `private` سیکشن میں درج ذیل شامل کریں:

    ```cpp
    WiFiClient _client;
    ```

1. `private` سیکشن میں، منتخب کردہ آواز کے لیے ایک فیلڈ شامل کریں:

    ```cpp
    String _voice;
    ```

1. `public` سیکشن میں ایک `init` فنکشن شامل کریں جو پہلی آواز حاصل کرے گا:

    ```cpp
    void init()
    {
    }
    ```

1. آوازوں کو حاصل کرنے کے لیے، ایک JSON دستاویز کو زبان کے ساتھ فنکشن ایپ پر بھیجنے کی ضرورت ہے۔ `init` فنکشن میں درج ذیل کوڈ شامل کریں تاکہ یہ JSON دستاویز بنائی جا سکے:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. اس کے بعد ایک `HTTPClient` بنائیں، پھر اسے آوازوں کو حاصل کرنے کے لیے فنکشن ایپ کو کال کرنے کے لیے استعمال کریں، JSON دستاویز کو پوسٹ کرتے ہوئے:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. اس کے نیچے کوڈ شامل کریں تاکہ رسپانس کو چیک کیا جا سکے، اور اگر یہ 200 (کامیابی) ہے، تو آوازوں کی فہرست نکالیں، فہرست سے پہلی آواز حاصل کریں:

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

1. اس کے بعد، HTTP کلائنٹ کنکشن ختم کریں:

    ```cpp
    httpClient.end();
    ```

1. `main.cpp` فائل کھولیں، اور اس نئی ہیڈر فائل کو شامل کرنے کے لیے اوپر درج ذیل شامل کریں:

    ```cpp
    #include "text_to_speech.h"
    ```

1. `setup` فنکشن میں، `speechToText.init();` کال کے نیچے درج ذیل شامل کریں تاکہ `TextToSpeech` کلاس کو انیشیلائز کیا جا سکے:

    ```cpp
    textToSpeech.init();
    ```

1. اس کوڈ کو بنائیں، اسے اپنے وائیو ٹرمینل پر اپ لوڈ کریں اور سیریل مانیٹر کے ذریعے ٹیسٹ کریں۔ یقینی بنائیں کہ آپ کی فنکشن ایپ چل رہی ہے۔

    آپ کو فنکشن ایپ سے دستیاب آوازوں کی فہرست واپس آتی ہوئی نظر آئے گی، ساتھ ہی منتخب کردہ آواز۔

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

## متن کو آواز میں تبدیل کریں

ایک بار جب آپ کے پاس استعمال کرنے کے لیے آواز ہو، تو اسے متن کو آواز میں تبدیل کرنے کے لیے استعمال کیا جا سکتا ہے۔ آواز کو متن میں تبدیل کرنے کے ساتھ وہی میموری کی حدود آواز کو متن میں تبدیل کرنے پر بھی لاگو ہوتی ہیں، لہذا آپ کو آواز کو SD کارڈ پر محفوظ کرنے کی ضرورت ہوگی تاکہ اسے ReSpeaker پر چلایا جا سکے۔

> 💁 اس پروجیکٹ کے پہلے اسباق میں آپ نے مائیکروفون سے حاصل کردہ آواز کو محفوظ کرنے کے لیے فلیش میموری کا استعمال کیا۔ یہ سبق SD کارڈ استعمال کرتا ہے کیونکہ Seeed آڈیو لائبریریوں کا استعمال کرتے ہوئے اس سے آڈیو چلانا آسان ہے۔

یہاں ایک اور حد پر غور کرنا ضروری ہے، اسپیک سروس سے دستیاب آڈیو ڈیٹا، اور وہ فارمیٹس جو وائیو ٹرمینل سپورٹ کرتا ہے۔ مکمل کمپیوٹرز کے برعکس، مائیکرو کنٹرولرز کے لیے آڈیو لائبریریاں ان فارمیٹس میں محدود ہو سکتی ہیں جنہیں وہ سپورٹ کرتی ہیں۔ مثال کے طور پر، Seeed Arduino Audio لائبریری جو ReSpeaker پر آواز چلا سکتی ہے، صرف 44.1KHz سیمپل ریٹ پر آڈیو کو سپورٹ کرتی ہے۔ Azure اسپیک سروسز کئی فارمیٹس میں آڈیو فراہم کر سکتی ہیں، لیکن ان میں سے کوئی بھی اس سیمپل ریٹ کا استعمال نہیں کرتا، وہ صرف 8KHz، 16KHz، 24KHz اور 48KHz فراہم کرتے ہیں۔ اس کا مطلب ہے کہ آڈیو کو 44.1KHz پر دوبارہ سیمپل کرنے کی ضرورت ہے، جو وائیو ٹرمینل کے پاس زیادہ وسائل، خاص طور پر میموری کی ضرورت ہوگی۔

جب اس طرح کے ڈیٹا کو جوڑنے کی ضرورت ہو، تو اکثر بہتر ہوتا ہے کہ سرور لیس کوڈ استعمال کریں، خاص طور پر اگر ڈیٹا ویب کال کے ذریعے حاصل کیا گیا ہو۔ وائیو ٹرمینل سرور لیس فنکشن کو کال کر سکتا ہے، متن کو تبدیل کرنے کے لیے پاس کرتے ہوئے، اور سرور لیس فنکشن اسپیک سروس کو متن کو آواز میں تبدیل کرنے کے لیے کال کر سکتا ہے، ساتھ ہی آڈیو کو مطلوبہ سیمپل ریٹ پر دوبارہ سیمپل کر سکتا ہے۔ پھر یہ آڈیو کو اس شکل میں واپس کر سکتا ہے جسے وائیو ٹرمینل SD کارڈ پر محفوظ کر سکتا ہے اور ReSpeaker پر چلا سکتا ہے۔

### کام - متن کو آواز میں تبدیل کرنے کے لیے سرور لیس فنکشن بنائیں

1. اپنے `smart-timer-trigger` پروجیکٹ کو VS کوڈ میں کھولیں، اور ٹرمینل کھولیں، یہ یقینی بناتے ہوئے کہ ورچوئل ماحول فعال ہے۔ اگر نہیں، تو ٹرمینل کو ختم کریں اور دوبارہ بنائیں۔

1. اس ایپ میں ایک نیا HTTP ٹرگر شامل کریں جسے `text-to-speech` کہا جاتا ہے، درج ذیل کمانڈ کو VS کوڈ ٹرمینل میں فنکشنز ایپ پروجیکٹ کے روٹ فولڈر کے اندر استعمال کریں:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    یہ ایک HTTP ٹرگر بنائے گا جسے `text-to-speech` کہا جاتا ہے۔

1. [librosa](https://librosa.org) Pip پیکج میں آڈیو کو دوبارہ سیمپل کرنے کے فنکشنز ہیں، لہذا اسے `requirements.txt` فائل میں شامل کریں:

    ```sh
    librosa
    ```

    ایک بار جب یہ شامل ہو جائے، درج ذیل کمانڈ کو VS کوڈ ٹرمینل سے استعمال کرتے ہوئے Pip پیکجز انسٹال کریں:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ اگر آپ لینکس استعمال کر رہے ہیں، بشمول Raspberry Pi OS، تو آپ کو `libsndfile` درج ذیل کمانڈ کے ساتھ انسٹال کرنے کی ضرورت ہو سکتی ہے:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. متن کو آواز میں تبدیل کرنے کے لیے، آپ اسپیک API کلید کو براہ راست استعمال نہیں کر سکتے، بلکہ آپ کو ایک ایکسیس ٹوکن کی درخواست کرنی ہوگی، API کلید کو ایکسیس ٹوکن درخواست کی تصدیق کے لیے استعمال کرتے ہوئے۔ `text-to-speech` فولڈر سے `__init__.py` فائل کھولیں اور اس میں موجود تمام کوڈ کو درج ذیل سے تبدیل کریں:

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

    یہ سیٹنگز سے پڑھی جانے والی مقام اور اسپیک کلید کے لیے کانسٹنٹس ڈیفائن کرتا ہے۔ پھر یہ `get_access_token` فنکشن ڈیفائن کرتا ہے جو اسپیک سروس کے لیے ایکسیس ٹوکن حاصل کرے گا۔

1. اس کوڈ کے نیچے درج ذیل شامل کریں:

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

    یہ HTTP ٹرگر ڈیفائن کرتا ہے جو متن کو آواز میں تبدیل کرتا ہے۔ یہ JSON جسم سے متن کو تبدیل کرنے، زبان اور آواز کو نکالتا ہے، اسپیک کی درخواست کرنے کے لیے کچھ SSML بناتا ہے، پھر متعلقہ REST API کو ایکسیس ٹوکن کے ذریعے تصدیق کرتے ہوئے کال کرتا ہے۔ یہ REST API کال آڈیو کو 16-bit، 48KHz مونو WAV فائل کے طور پر انکوڈ کر کے واپس کرتا ہے، جو `playback_format` کی قدر سے ڈیفائن کیا گیا ہے، جو REST API کال کو بھیجا جاتا ہے۔

    پھر یہ `librosa` کے ذریعے 48KHz کے سیمپل ریٹ سے 44.1KHz کے سیمپل ریٹ پر دوبارہ سیمپل کیا جاتا ہے، پھر یہ آڈیو ایک بائنری بفر میں محفوظ کیا جاتا ہے جو پھر واپس کیا جاتا ہے۔

1. اپنی فنکشن ایپ کو مقامی طور پر چلائیں، یا اسے کلاؤڈ پر ڈیپلائی کریں۔ آپ اسے curl جیسے ٹول کا استعمال کرتے ہوئے اسی طرح کال کر سکتے ہیں جیسے آپ نے اپنے `text-to-timer` HTTP ٹرگر کو ٹیسٹ کیا تھا۔ زبان، آواز اور متن کو JSON جسم کے طور پر پاس کرنا یقینی بنائیں:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    `<language>` کو اپنی زبان سے تبدیل کریں، جیسے `en-GB` یا `zh-CN`۔ `<voice>` کو اپنی مطلوبہ آواز سے تبدیل کریں۔ `<text>` کو اس متن سے تبدیل کریں جسے آپ آواز میں تبدیل کرنا چاہتے ہیں۔ آپ آؤٹ پٹ کو فائل میں محفوظ کر سکتے ہیں اور اسے کسی بھی آڈیو پلیئر کے ساتھ چلا سکتے ہیں جو WAV فائلز چلا سکتا ہے۔

    مثال کے طور پر، "Hello" کو امریکی انگریزی میں Jenny Neural آواز کے ساتھ آواز میں تبدیل کرنے کے لیے، فنکشن ایپ کو مقامی طور پر چلانے کے ساتھ، آپ درج ذیل curl کمانڈ استعمال کر سکتے ہیں:

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

    یہ آڈیو کو موجودہ ڈائریکٹری میں `hello.wav` کے طور پر محفوظ کرے گا۔

> 💁 آپ اس کوڈ کو [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) فولڈر میں تلاش کر سکتے ہیں۔

### کام - وائیو ٹرمینل سے آواز حاصل کریں

1. اگر `smart-timer` پروجیکٹ پہلے سے کھلا نہیں ہے تو اسے VS کوڈ میں کھولیں۔

1. `config.h` ہیڈر فائل کھولیں اور اپنی فنکشن ایپ کے لیے URL شامل کریں:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    `<URL>` کو اپنی فنکشن ایپ کے `text-to-speech` HTTP ٹرگر کے URL سے تبدیل کریں۔ یہ `TEXT_TO_TIMER_FUNCTION_URL` کی قدر جیسا ہی ہوگا، سوائے فنکشن کے نام `text-to-speech` کے بجائے `text-to-timer`۔

1. `text_to_speech.h` ہیڈر فائل کھولیں، اور `TextToSpeech` کلاس کے `public` سیکشن میں درج ذیل میتھڈ شامل کریں:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. `convertTextToSpeech` میتھڈ میں، فنکشن ایپ کو بھیجنے کے لیے JSON بنانے کے لیے درج ذیل کوڈ شامل کریں:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    یہ زبان، آواز اور متن کو JSON دستاویز میں لکھتا ہے، پھر اسے ایک سٹرنگ میں سیریلائز کرتا ہے۔

1. اس کے نیچے، فنکشن ایپ کو کال کرنے کے لیے درج ذیل کوڈ شامل کریں:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    یہ ایک HTTPClient بناتا ہے، پھر JSON دستاویز کا استعمال کرتے ہوئے متن کو آواز میں تبدیل کرنے کے HTTP ٹرگر پر POST درخواست کرتا ہے۔

1. اگر کال کام کرتی ہے، تو فنکشن ایپ کال سے واپس کیے گئے خام بائنری ڈیٹا کو SD کارڈ پر فائل میں اسٹریم کیا جا سکتا ہے۔ ایسا کرنے کے لیے درج ذیل کوڈ شامل کریں:

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

    یہ کوڈ رسپانس کو چیک کرتا ہے، اور اگر یہ 200 (کامیابی) ہے، تو بائنری ڈیٹا SD کارڈ کی روٹ میں `SPEECH.WAV` نامی فائل میں اسٹریم کیا جاتا ہے۔

1. اس میتھڈ کے آخر میں، HTTP کنکشن بند کریں:

    ```cpp
    httpClient.end();
    ```

1. اب بولے جانے والے متن کو آڈیو میں تبدیل کیا جا سکتا ہے۔ `main.cpp` فائل میں، `say` فنکشن کے آخر میں درج ذیل لائن شامل کریں تاکہ بولے جانے والے متن کو آڈیو میں تبدیل کیا جا سکے:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### کام - اپنے Wio Terminal سے آڈیو چلائیں

**جلد آرہا ہے**

## اپنی فنکشنز ایپ کو کلاؤڈ پر ڈیپلائے کریں

فنکشنز ایپ کو مقامی طور پر چلانے کی وجہ یہ ہے کہ لینکس پر `librosa` پائپ پیکیج ایک ایسی لائبریری پر منحصر ہے جو ڈیفالٹ طور پر انسٹال نہیں ہوتی، اور فنکشن ایپ کو چلانے سے پہلے اسے انسٹال کرنا ضروری ہوگا۔ فنکشنز ایپس سرور لیس ہوتی ہیں - آپ کے پاس کوئی سرور نہیں ہوتا جسے آپ خود مینیج کر سکیں، اس لیے اس لائبریری کو پہلے سے انسٹال کرنے کا کوئی طریقہ نہیں ہوتا۔

اس کا حل یہ ہے کہ اپنی فنکشنز ایپ کو ایک Docker کنٹینر کے ذریعے ڈیپلائے کریں۔ یہ کنٹینر کلاؤڈ کے ذریعے اس وقت ڈیپلائے کیا جاتا ہے جب اسے آپ کی فنکشن ایپ کا نیا انسٹینس شروع کرنے کی ضرورت ہو (جیسے جب ڈیمانڈ دستیاب وسائل سے زیادہ ہو جائے، یا اگر فنکشن ایپ کچھ وقت سے استعمال نہیں ہوئی ہو اور بند ہو گئی ہو)۔

آپ فنکشن ایپ کو سیٹ اپ کرنے اور Docker کے ذریعے ڈیپلائے کرنے کی ہدایات [Microsoft Docs پر لینکس پر کسٹم کنٹینر استعمال کرتے ہوئے فنکشن بنانے کی دستاویزات](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python) میں دیکھ سکتے ہیں۔

جب یہ ڈیپلائے ہو جائے، تو آپ اپنی Wio Terminal کوڈ کو اس فنکشن تک رسائی کے لیے پورٹ کر سکتے ہیں:

1. Azure Functions کا سرٹیفکیٹ `config.h` میں شامل کریں:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. تمام `<WiFiClient.h>` شاملات کو `<WiFiClientSecure.h>` میں تبدیل کریں۔

1. تمام `WiFiClient` فیلڈز کو `WiFiClientSecure` میں تبدیل کریں۔

1. ہر کلاس میں جس میں `WiFiClientSecure` فیلڈ ہو، ایک کنسٹرکٹر شامل کریں اور اس کنسٹرکٹر میں سرٹیفکیٹ سیٹ کریں:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔