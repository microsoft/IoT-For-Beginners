<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T13:54:33+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "bn"
}
-->
# টেক্সট থেকে স্পিচ - Wio Terminal

এই পাঠের এই অংশে, আপনি টেক্সটকে স্পিচে রূপান্তর করবেন যাতে কথিত প্রতিক্রিয়া প্রদান করা যায়।

## টেক্সট থেকে স্পিচ

স্পিচ সার্ভিসেস SDK, যা আপনি আগের পাঠে টেক্সট থেকে স্পিচে রূপান্তর করতে ব্যবহার করেছিলেন, তা টেক্সটকে আবার স্পিচে রূপান্তর করতেও ব্যবহার করা যেতে পারে।

## ভয়েসের তালিকা পান

স্পিচ অনুরোধ করার সময়, আপনাকে ব্যবহারের জন্য একটি ভয়েস সরবরাহ করতে হবে কারণ বিভিন্ন ভয়েস ব্যবহার করে স্পিচ তৈরি করা যেতে পারে। প্রতিটি ভাষা বিভিন্ন ভয়েস সমর্থন করে এবং প্রতিটি ভাষার জন্য সমর্থিত ভয়েসের তালিকা স্পিচ সার্ভিসেস SDK থেকে পাওয়া যায়। এখানে মাইক্রোকন্ট্রোলারের সীমাবদ্ধতাগুলি প্রাসঙ্গিক হয়ে ওঠে - টেক্সট থেকে স্পিচ সার্ভিস দ্বারা সমর্থিত ভয়েসের তালিকা পাওয়ার জন্য কলটি একটি JSON ডকুমেন্ট যা ৭৭KB এর বেশি আকারের, যা Wio Terminal দ্বারা প্রক্রিয়া করার জন্য অনেক বড়। লেখার সময়, সম্পূর্ণ তালিকায় ২১৫টি ভয়েস রয়েছে, প্রতিটি একটি JSON ডকুমেন্ট দ্বারা সংজ্ঞায়িত, যেমন নিম্নলিখিত:

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

এই JSON **Aria** ভয়েসের জন্য, যার একাধিক ভয়েস স্টাইল রয়েছে। টেক্সট থেকে স্পিচে রূপান্তর করার সময় যা প্রয়োজন তা হল সংক্ষিপ্ত নাম, `en-US-AriaNeural`।

আপনার মাইক্রোকন্ট্রোলারে এই সম্পূর্ণ তালিকা ডাউনলোড এবং ডিকোড করার পরিবর্তে, আপনাকে এমন কিছু সার্ভারলেস কোড লিখতে হবে যা আপনি যে ভাষা ব্যবহার করছেন তার জন্য ভয়েসের তালিকা পুনরুদ্ধার করবে এবং এটি আপনার Wio Terminal থেকে কল করবে। এরপর আপনার কোড তালিকা থেকে একটি উপযুক্ত ভয়েস বেছে নিতে পারে, যেমন প্রথমটি যা এটি খুঁজে পায়।

### কাজ - ভয়েসের তালিকা পেতে একটি সার্ভারলেস ফাংশন তৈরি করুন

1. আপনার `smart-timer-trigger` প্রকল্পটি VS Code-এ খুলুন এবং টার্মিনালটি খুলুন, নিশ্চিত করুন যে ভার্চুয়াল এনভায়রনমেন্ট সক্রিয় রয়েছে। যদি না থাকে, টার্মিনালটি বন্ধ করে পুনরায় তৈরি করুন।

1. `local.settings.json` ফাইলটি খুলুন এবং স্পিচ API কী এবং অবস্থানের জন্য সেটিংস যোগ করুন:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    `<key>`-এর জায়গায় আপনার স্পিচ সার্ভিস রিসোর্সের API কী বসান। `<location>`-এর জায়গায় আপনি যখন স্পিচ সার্ভিস রিসোর্স তৈরি করেছিলেন তখন ব্যবহৃত অবস্থানটি বসান।

1. এই অ্যাপে `get-voices` নামে একটি নতুন HTTP ট্রিগার যোগ করুন, যা VS Code টার্মিনালে ফাংশন অ্যাপ প্রকল্পের রুট ফোল্ডার থেকে নিম্নলিখিত কমান্ড ব্যবহার করে তৈরি করা যেতে পারে:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    এটি `get-voices` নামে একটি HTTP ট্রিগার তৈরি করবে।

1. `get-voices` ফোল্ডারের `__init__.py` ফাইলের বিষয়বস্তু নিম্নলিখিত কোড দিয়ে প্রতিস্থাপন করুন:

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

    এই কোডটি ভয়েসগুলি পেতে এন্ডপয়েন্টে একটি HTTP অনুরোধ করে। এই ভয়েস তালিকাটি সমস্ত ভাষার জন্য একটি বড় JSON ব্লক, তাই অনুরোধ বডিতে পাস করা ভাষার জন্য ভয়েসগুলি ফিল্টার করা হয়, তারপর সংক্ষিপ্ত নামটি বের করে একটি JSON তালিকা হিসাবে ফেরত দেওয়া হয়। টেক্সট থেকে স্পিচে রূপান্তর করার জন্য সংক্ষিপ্ত নামটি প্রয়োজন, তাই শুধুমাত্র এই মানটি ফেরত দেওয়া হয়।

    > 💁 আপনি প্রয়োজন অনুযায়ী ফিল্টারটি পরিবর্তন করতে পারেন শুধুমাত্র আপনার পছন্দের ভয়েসগুলি নির্বাচন করতে।

    এটি ডেটার আকার ৭৭KB (লেখার সময়) থেকে একটি ছোট JSON ডকুমেন্টে কমিয়ে দেয়। উদাহরণস্বরূপ, US ভয়েসের জন্য এটি ৪০৮ বাইট।

1. আপনার ফাংশন অ্যাপটি লোকালভাবে চালান। এরপর আপনি এটি `text-to-timer` HTTP ট্রিগার পরীক্ষা করার মতো করে curl-এর মতো একটি টুল ব্যবহার করে কল করতে পারেন। নিশ্চিত করুন যে আপনার ভাষাটি একটি JSON বডি হিসাবে পাস করা হয়েছে:

    ```json
    {
        "language":"<language>"
    }
    ```

    `<language>`-এর জায়গায় আপনার ভাষা বসান, যেমন `en-GB` বা `zh-CN`।

> 💁 আপনি এই কোডটি [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) ফোল্ডারে খুঁজে পেতে পারেন।

### কাজ - আপনার Wio Terminal থেকে ভয়েস পুনরুদ্ধার করুন

1. যদি এটি ইতিমধ্যে খোলা না থাকে তবে VS Code-এ `smart-timer` প্রকল্পটি খুলুন।

1. `config.h` হেডার ফাইলটি খুলুন এবং আপনার ফাংশন অ্যাপের URL যোগ করুন:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    `<URL>`-এর জায়গায় আপনার ফাংশন অ্যাপের `get-voices` HTTP ট্রিগারের URL বসান। এটি `TEXT_TO_TIMER_FUNCTION_URL`-এর মানের মতোই হবে, তবে ফাংশনের নাম `text-to-timer` এর পরিবর্তে `get-voices` হবে।

1. `src` ফোল্ডারে একটি নতুন ফাইল তৈরি করুন যার নাম `text_to_speech.h`। এটি টেক্সট থেকে স্পিচে রূপান্তর করার জন্য একটি ক্লাস সংজ্ঞায়িত করতে ব্যবহৃত হবে।

1. নতুন `text_to_speech.h` ফাইলের উপরে নিম্নলিখিত ইনক্লুড ডিরেক্টিভগুলি যোগ করুন:

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

1. এর নিচে `TextToSpeech` ক্লাসটি ডিক্লেয়ার করার জন্য এবং অ্যাপ্লিকেশনের বাকি অংশে ব্যবহারের জন্য একটি ইনস্ট্যান্স ডিক্লেয়ার করার জন্য নিম্নলিখিত কোডটি যোগ করুন:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. আপনার ফাংশন অ্যাপ কল করার জন্য একটি WiFi ক্লায়েন্ট ডিক্লেয়ার করুন। ক্লাসের `private` সেকশনে নিম্নলিখিতটি যোগ করুন:

    ```cpp
    WiFiClient _client;
    ```

1. `private` সেকশনে একটি ফিল্ড যোগ করুন নির্বাচিত ভয়েসের জন্য:

    ```cpp
    String _voice;
    ```

1. `public` সেকশনে একটি `init` ফাংশন যোগ করুন যা প্রথম ভয়েসটি পাবে:

    ```cpp
    void init()
    {
    }
    ```

1. ভয়েসগুলি পেতে, একটি JSON ডকুমেন্ট তৈরি করতে হবে যা ভাষার সাথে ফাংশন অ্যাপে পাঠানো হবে। `init` ফাংশনে নিম্নলিখিত কোডটি যোগ করুন:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. এরপর একটি `HTTPClient` তৈরি করুন এবং এটি ব্যবহার করে ফাংশন অ্যাপ কল করুন ভয়েসগুলি পেতে, JSON ডকুমেন্ট পোস্ট করে:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. এর নিচে কোড যোগ করুন যা রেসপন্স কোড চেক করবে, এবং যদি এটি ২০০ (সফল) হয়, তাহলে ভয়েসগুলির তালিকা বের করবে এবং তালিকা থেকে প্রথমটি পুনরুদ্ধার করবে:

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

1. এর পরে, HTTP ক্লায়েন্ট সংযোগটি বন্ধ করুন:

    ```cpp
    httpClient.end();
    ```

1. `main.cpp` ফাইলটি খুলুন এবং এই নতুন হেডার ফাইলটি অন্তর্ভুক্ত করতে উপরে নিম্নলিখিত ইনক্লুড ডিরেক্টিভটি যোগ করুন:

    ```cpp
    #include "text_to_speech.h"
    ```

1. `setup` ফাংশনে, `speechToText.init();` কলের নিচে, `TextToSpeech` ক্লাসটি ইনিশিয়ালাইজ করার জন্য নিম্নলিখিতটি যোগ করুন:

    ```cpp
    textToSpeech.init();
    ```

1. এই কোডটি বিল্ড করুন, এটি আপনার Wio Terminal-এ আপলোড করুন এবং সিরিয়াল মনিটরের মাধ্যমে এটি পরীক্ষা করুন। নিশ্চিত করুন যে আপনার ফাংশন অ্যাপটি চালু রয়েছে।

    আপনি ফাংশন অ্যাপ থেকে ফেরত আসা উপলব্ধ ভয়েসগুলির তালিকা এবং নির্বাচিত ভয়েসটি দেখতে পাবেন।

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

## টেক্সট থেকে স্পিচে রূপান্তর করুন

একবার আপনার ব্যবহারের জন্য একটি ভয়েস থাকলে, এটি টেক্সটকে স্পিচে রূপান্তর করতে ব্যবহার করা যেতে পারে। ভয়েসগুলির ক্ষেত্রে যে মেমরি সীমাবদ্ধতা রয়েছে তা স্পিচে রূপান্তরের ক্ষেত্রেও প্রযোজ্য, তাই আপনাকে স্পিচটি SD কার্ডে লিখতে হবে যাতে এটি ReSpeaker-এর মাধ্যমে প্লে করা যায়।

> 💁 এই প্রকল্পের আগের পাঠে আপনি মাইক্রোফোন থেকে ক্যাপচার করা স্পিচ ফ্ল্যাশ মেমরিতে সংরক্ষণ করতে ব্যবহার করেছিলেন। এই পাঠে SD কার্ড ব্যবহার করা হয়েছে কারণ Seeed অডিও লাইব্রেরি ব্যবহার করে এটি থেকে অডিও প্লে করা সহজ।

আরেকটি সীমাবদ্ধতাও বিবেচনা করতে হবে, স্পিচ সার্ভিস থেকে উপলব্ধ অডিও ডেটা এবং Wio Terminal যে ফরম্যাটগুলি সমর্থন করে। সম্পূর্ণ কম্পিউটারের মতো নয়, মাইক্রোকন্ট্রোলারের জন্য অডিও লাইব্রেরিগুলি সমর্থিত অডিও ফরম্যাটে খুব সীমিত হতে পারে। উদাহরণস্বরূপ, Seeed Arduino Audio লাইব্রেরি যা ReSpeaker-এর মাধ্যমে সাউন্ড প্লে করতে পারে শুধুমাত্র ৪৪.১KHz স্যাম্পল রেটের অডিও সমর্থন করে। Azure স্পিচ সার্ভিসগুলি বেশ কয়েকটি ফরম্যাটে অডিও প্রদান করতে পারে, তবে এর কোনোটিই এই স্যাম্পল রেট ব্যবহার করে না, তারা শুধুমাত্র ৮KHz, ১৬KHz, ২৪KHz এবং ৪৮KHz প্রদান করে। এর মানে অডিওটি ৪৪.১KHz-এ পুনরায় স্যাম্পল করতে হবে, যা Wio Terminal-এর কাছে থাকা বেশি রিসোর্স প্রয়োজন, বিশেষ করে মেমরি।

যখন এই ধরনের ডেটা ম্যানিপুলেট করার প্রয়োজন হয়, তখন এটি প্রায়শই সার্ভারলেস কোড ব্যবহার করা ভাল, বিশেষ করে যদি ডেটা ওয়েব কলের মাধ্যমে উৎস হয়। Wio Terminal একটি সার্ভারলেস ফাংশন কল করতে পারে, রূপান্তর করার জন্য টেক্সট পাস করতে পারে, এবং সার্ভারলেস ফাংশনটি টেক্সট থেকে স্পিচে রূপান্তর করার পাশাপাশি প্রয়োজনীয় স্যাম্পল রেটে অডিও পুনরায় স্যাম্পল করতে পারে। এটি তখন অডিওটি Wio Terminal-এর প্রয়োজনীয় ফর্মে ফেরত দিতে পারে যা SD কার্ডে সংরক্ষণ করা হবে এবং ReSpeaker-এর মাধ্যমে প্লে করা হবে।

### কাজ - টেক্সট থেকে স্পিচে রূপান্তর করতে একটি সার্ভারলেস ফাংশন তৈরি করুন

1. আপনার `smart-timer-trigger` প্রকল্পটি VS Code-এ খুলুন এবং টার্মিনালটি খুলুন, নিশ্চিত করুন যে ভার্চুয়াল এনভায়রনমেন্ট সক্রিয় রয়েছে। যদি না থাকে, টার্মিনালটি বন্ধ করে পুনরায় তৈরি করুন।

1. এই অ্যাপে `text-to-speech` নামে একটি নতুন HTTP ট্রিগার যোগ করুন, যা VS Code টার্মিনালে ফাংশন অ্যাপ প্রকল্পের রুট ফোল্ডার থেকে নিম্নলিখিত কমান্ড ব্যবহার করে তৈরি করা যেতে পারে:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    এটি `text-to-speech` নামে একটি HTTP ট্রিগার তৈরি করবে।

1. [librosa](https://librosa.org) Pip প্যাকেজে অডিও পুনরায় স্যাম্পল করার ফাংশন রয়েছে, তাই এটি `requirements.txt` ফাইলে যোগ করুন:

    ```sh
    librosa
    ```

    একবার এটি যোগ করা হলে, VS Code টার্মিনাল থেকে নিম্নলিখিত কমান্ড ব্যবহার করে Pip প্যাকেজগুলি ইনস্টল করুন:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ আপনি যদি Linux ব্যবহার করেন, যার মধ্যে Raspberry Pi OS অন্তর্ভুক্ত, তবে আপনাকে নিম্নলিখিত কমান্ড দিয়ে `libsndfile` ইনস্টল করতে হতে পারে:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. টেক্সট থেকে স্পিচে রূপান্তর করতে, আপনি সরাসরি স্পিচ API কী ব্যবহার করতে পারবেন না, পরিবর্তে আপনাকে একটি অ্যাক্সেস টোকেন অনুরোধ করতে হবে, অ্যাক্সেস টোকেন অনুরোধ প্রমাণীকরণের জন্য API কী ব্যবহার করে। `text-to-speech` ফোল্ডারের `__init__.py` ফাইলটি খুলুন এবং এতে থাকা সমস্ত কোড নিম্নলিখিত কোড দিয়ে প্রতিস্থাপন করুন:

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

    এটি সেটিংস থেকে পড়া অবস্থান এবং স্পিচ কী-এর জন্য কনস্ট্যান্ট সংজ্ঞায়িত করে। এরপর এটি `get_access_token` ফাংশন সংজ্ঞায়িত করে যা স্পিচ সার্ভিসের জন্য একটি অ্যাক্সেস টোকেন পুনরুদ্ধার করবে।

1. এই কোডের নিচে নিম্নলিখিতটি যোগ করুন:

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

    এটি টেক্সট থেকে স্পিচে রূপান্তর করার জন্য HTTP ট্রিগার সংজ্ঞায়িত করে। এটি রূপান্তর করার জন্য টেক্সট, ভাষা এবং ভয়েস JSON বডি থেকে বের করে, স্পিচ অনুরোধ করার জন্য কিছু SSML তৈরি করে, তারপর প্রাসঙ্গিক REST API কল করে অ্যাক্সেস টোকেন ব্যবহার করে প্রমাণীকরণ করে। এই REST API কলটি ১৬-বিট, ৪৮KHz মনো WAV ফাইল হিসাবে এনকোড করা অডিও ফেরত দেয়, যা `playback_format` এর মান দ্বারা সংজ্ঞায়িত, যা REST API কলে পাঠানো হয়।

    এরপর এটি `librosa` দ্বারা ৪৮KHz স্যাম্পল রেট থেকে ৪৪.১KHz স্যাম্পল রেটে পুনরায় স্যাম্পল করা হয়, তারপর এই অডিওটি একটি বাইনারি বাফারে সংরক্ষণ করা হয় যা পরে ফেরত দেওয়া হয়।

1. আপনার ফাংশন অ্যাপটি লোকালভাবে চালান, অথবা এটি ক্লাউডে ডিপ্লয় করুন। এরপর আপনি এটি `text-to-timer` HTTP ট্রিগার পরীক্ষা করার মতো করে curl-এর মতো একটি টুল ব্যবহার করে কল করতে পারেন। নিশ্চিত করুন যে ভাষা, ভয়েস এবং টেক্সট JSON বডি হিসাবে পাস করা হয়েছে:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    `<language>`-এর জায়গায় আপনার ভাষা বসান, যেমন `en-GB` বা `zh-CN`। `<voice>`-এর জায়গায় আপনি যে ভয়েসটি ব্যবহার করতে চান তা বসান। `<text>`-এর জায়গায় আপনি যে টেক্সটটি স্পিচে রূপান্তর করতে চান তা বসান। আপনি আউটপুটটি একটি ফাইলে সংরক্ষণ করতে পারেন এবং যেকোনো অডিও প্লেয়ার দিয়ে এটি প্লে করতে পারেন যা WAV ফাইল প্লে করতে পারে।

    উদাহরণস্বরূপ, "Hello" শব্দটিকে US English-এ Jenny Neural ভয়েস ব্যবহার করে স্পিচে রূপান্তর করতে, ফাংশন অ্যাপটি লোকালভাবে চালানোর সময়, আপনি নিম্নলিখিত curl কমান্ডটি ব্যবহার করতে পারেন:

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

    এটি বর্তমান ডিরেক্টরিতে `hello.wav` নামে অডিওটি সংরক্ষণ করবে।

> 💁 আপনি এই কোডটি [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) ফোল্ডারে খুঁজে পেতে পারেন।

### কাজ - আপনার Wio Terminal থেকে স্পিচ পুনরুদ্ধার করুন

1. যদি এটি ইতিমধ্যে খোলা না থাকে তবে VS Code-এ `smart-timer` প্রকল্পটি খুলুন।

1. `config.h` হেডার ফাইলটি খুলুন এবং আপনার ফাংশন অ্যাপের URL যোগ করুন:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    `<URL>`-এর জায়গায় আপনার ফাংশন অ্যাপের `text-to-speech` HTTP ট্রিগারের URL বসান। এটি `TEXT_TO_TIMER_FUNCTION_URL`-এর মানের মতোই হবে, তবে ফাংশনের নাম `text-to-timer` এর পরিবর্তে `text-to-speech` হবে।

1. `text_to_speech.h` হেডার ফাইলটি খুলুন এবং `TextToSpeech` ক্লাসের `public` সেকশনে নিম্নলিখিত মেথডটি যোগ করুন:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. `convertTextToSpeech` মেথডে, ফাংশন অ্যাপে পাঠানোর জন্য JSON তৈরি করতে নিম্নলিখিত কোডটি যোগ করুন:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    এটি ভাষা, ভয়েস এবং টেক্সট JSON ডকুমেন্টে লিখে, তারপর এটি একটি স্ট্রিংয়ে সিরিয়ালাইজ করে।

1. এর নিচে, ফাংশন অ্যাপ কল করার জন্য নিম্নলিখিত কোডটি যোগ করুন:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    এটি একটি HTTPClient তৈরি করে, তারপর JSON ডকুমেন্ট ব্যবহার করে `text-to-speech` HTTP ট্রিগারে একটি POST অনুরোধ করে।

1. যদি কলটি সফল হয়, ফাংশন অ্যাপ কল থেকে ফেরত আসা কাঁচা বাইনারি ডেটা SD কার্ডে একটি ফাইলে স্ট্রিম করা যেতে পারে। এটি করতে নিম্নলিখিত কোডটি যোগ করুন:

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

    এই কোডটি রেসপন্স চেক করে, এবং যদি এটি ২০০ (সফল) হয়, তাহলে বাইনারি ডেটা SD কার্ডের রুটে `SPEECH.WAV` নামে একটি ফাইলে স্ট্রিম করে।

1. এই মেথডের শেষে, HTTP সংযোগটি বন্ধ করুন:

    ```cpp
    httpClient.end();
    ```

1. এখন বলা টেক্সটটি অডিওতে রূপান্তর করা যেতে পারে। `main.cpp` ফাইলে, `say
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### টাস্ক - আপনার Wio Terminal থেকে অডিও চালান

**শীঘ্রই আসছে**

## আপনার ফাংশন অ্যাপ ক্লাউডে ডিপ্লয় করা

ফাংশন অ্যাপ লোকালভাবে চালানোর কারণ হলো `librosa` Pip প্যাকেজের লিনাক্সে একটি ডিপেনডেন্সি রয়েছে যা ডিফল্টভাবে ইনস্টল করা থাকে না এবং এটি ইনস্টল করতে হবে ফাংশন অ্যাপ চালানোর আগে। ফাংশন অ্যাপগুলো সার্ভারলেস - এখানে এমন কোনো সার্ভার নেই যা আপনি নিজে পরিচালনা করতে পারেন, তাই এই লাইব্রেরি আগে থেকে ইনস্টল করার কোনো উপায় নেই।

এর পরিবর্তে, আপনার ফাংশন অ্যাপকে একটি Docker কন্টেইনার ব্যবহার করে ডিপ্লয় করা হয়। এই কন্টেইনারটি ক্লাউড দ্বারা ডিপ্লয় করা হয় যখনই এটি আপনার ফাংশন অ্যাপের একটি নতুন ইনস্ট্যান্স চালু করার প্রয়োজন হয় (যেমন যখন চাহিদা উপলব্ধ রিসোর্সের চেয়ে বেশি হয়, অথবা যদি ফাংশন অ্যাপ দীর্ঘ সময় ধরে ব্যবহার না করা হয় এবং বন্ধ হয়ে যায়)।

Linux-এ একটি কাস্টম কন্টেইনার ব্যবহার করে ফাংশন তৈরি এবং Docker এর মাধ্যমে ডিপ্লয় করার নির্দেশনা আপনি [Microsoft Docs-এ Linux ব্যবহার করে কাস্টম কন্টেইনারে ফাংশন তৈরি করার ডকুমেন্টেশনে](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python) খুঁজে পেতে পারেন।

একবার এটি ডিপ্লয় হয়ে গেলে, আপনি আপনার Wio Terminal কোডকে এই ফাংশন অ্যাক্সেস করার জন্য পোর্ট করতে পারেন:

1. Azure Functions সার্টিফিকেটটি `config.h`-এ যোগ করুন:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. সমস্ত `<WiFiClient.h>` অন্তর্ভুক্তিকে `<WiFiClientSecure.h>`-এ পরিবর্তন করুন।

1. সমস্ত `WiFiClient` ফিল্ডকে `WiFiClientSecure`-এ পরিবর্তন করুন।

1. প্রতিটি ক্লাসে যেখানে একটি `WiFiClientSecure` ফিল্ড রয়েছে, একটি কনস্ট্রাক্টর যোগ করুন এবং সেই কনস্ট্রাক্টরে সার্টিফিকেট সেট করুন:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিকতার জন্য চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা দায়বদ্ধ থাকব না।