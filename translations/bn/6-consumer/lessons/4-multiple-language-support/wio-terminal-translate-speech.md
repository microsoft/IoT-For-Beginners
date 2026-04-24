# বক্তৃতা অনুবাদ করুন - Wio Terminal

এই পাঠের এই অংশে, আপনি অনুবাদক পরিষেবা ব্যবহার করে টেক্সট অনুবাদ করার কোড লিখবেন।

## অনুবাদক পরিষেবা ব্যবহার করে টেক্সটকে বক্তৃতায় রূপান্তর করুন

বক্তৃতা পরিষেবার REST API সরাসরি অনুবাদ সমর্থন করে না। পরিবর্তে, আপনি বক্তৃতা থেকে টেক্সটে পরিষেবা দ্বারা তৈরি টেক্সট এবং কথোপকথনের প্রতিক্রিয়ার টেক্সট অনুবাদ করতে অনুবাদক পরিষেবা ব্যবহার করতে পারেন। এই পরিষেবার একটি REST API রয়েছে যা আপনি টেক্সট অনুবাদ করতে ব্যবহার করতে পারেন, তবে এটি সহজে ব্যবহার করার জন্য আপনার ফাংশন অ্যাপে একটি HTTP ট্রিগারে মোড়ানো হবে।

### কাজ - টেক্সট অনুবাদ করার জন্য একটি সার্ভারলেস ফাংশন তৈরি করুন

1. আপনার `smart-timer-trigger` প্রকল্পটি VS Code-এ খুলুন এবং নিশ্চিত করুন যে ভার্চুয়াল পরিবেশটি সক্রিয় করা হয়েছে। যদি না হয়, টার্মিনাল বন্ধ করুন এবং পুনরায় তৈরি করুন।

1. `local.settings.json` ফাইলটি খুলুন এবং অনুবাদক API কী এবং অবস্থানের জন্য সেটিংস যোগ করুন:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    `<key>`-এর জায়গায় আপনার অনুবাদক পরিষেবা রিসোর্সের API কীটি প্রতিস্থাপন করুন। `<location>`-এর জায়গায় আপনি যখন অনুবাদক পরিষেবা রিসোর্স তৈরি করেছিলেন তখন ব্যবহৃত অবস্থানটি প্রতিস্থাপন করুন।

1. এই অ্যাপে একটি নতুন HTTP ট্রিগার যোগ করুন, যা `translate-text` নামে হবে। এটি করতে, VS Code টার্মিনালে প্রকল্পের মূল ফোল্ডারে নিম্নলিখিত কমান্ডটি চালান:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    এটি একটি HTTP ট্রিগার তৈরি করবে, যার নাম হবে `translate-text`।

1. `translate-text` ফোল্ডারের `__init__.py` ফাইলের বিষয়বস্তু নিম্নলিখিত কোড দিয়ে প্রতিস্থাপন করুন:

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

    এই কোডটি HTTP অনুরোধ থেকে টেক্সট এবং ভাষাগুলি বের করে। এটি অনুবাদক REST API-তে একটি অনুরোধ করে, URL-এর প্যারামিটার হিসাবে ভাষাগুলি এবং অনুবাদ করার টেক্সটটি বডি হিসাবে পাঠায়। শেষে, অনুবাদটি ফেরত দেয়।

1. আপনার ফাংশন অ্যাপটি লোকালভাবে চালান। এরপর আপনি এটি `text-to-timer` HTTP ট্রিগার পরীক্ষা করার মতো একটি টুল ব্যবহার করে কল করতে পারেন। নিশ্চিত করুন যে JSON বডি হিসাবে অনুবাদ করার টেক্সট এবং ভাষাগুলি পাস করেছেন:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    এই উদাহরণটি *Définir une minuterie de 30 secondes* ফরাসি থেকে US ইংরেজিতে অনুবাদ করে। এটি *Set a 30-second timer* ফেরত দেবে।

> 💁 আপনি এই কোডটি [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) ফোল্ডারে খুঁজে পেতে পারেন।

### কাজ - অনুবাদক ফাংশন ব্যবহার করে টেক্সট অনুবাদ করুন

1. যদি `smart-timer` প্রকল্পটি ইতিমধ্যে খোলা না থাকে, তাহলে এটি VS Code-এ খুলুন।

1. আপনার স্মার্ট টাইমারে 2টি ভাষা সেট করা থাকবে - LUIS প্রশিক্ষণের জন্য ব্যবহৃত সার্ভারের ভাষা (একই ভাষা ব্যবহারকারীকে কথা বলার জন্য বার্তা তৈরি করতে ব্যবহৃত হয়), এবং ব্যবহারকারীর কথোপকথনের ভাষা। `config.h` হেডার ফাইলের `LANGUAGE` কনস্ট্যান্টটি ব্যবহারকারীর কথোপকথনের ভাষা হিসাবে আপডেট করুন এবং `SERVER_LANGUAGE` নামে একটি নতুন কনস্ট্যান্ট যোগ করুন, যা LUIS প্রশিক্ষণের জন্য ব্যবহৃত ভাষা:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    `<user language>`-এর জায়গায় আপনি যে ভাষায় কথা বলবেন তার লোকাল নাম প্রতিস্থাপন করুন, যেমন `fr-FR` ফরাসির জন্য বা `zn-HK` ক্যান্টোনিজের জন্য।

    `<server language>`-এর জায়গায় LUIS প্রশিক্ষণের জন্য ব্যবহৃত ভাষার লোকাল নাম প্রতিস্থাপন করুন।

    Microsoft ডকসের [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)-এ সমর্থিত ভাষা এবং তাদের লোকাল নামের তালিকা খুঁজে পেতে পারেন।

    > 💁 যদি আপনি একাধিক ভাষায় কথা বলতে না পারেন, তাহলে [Bing Translate](https://www.bing.com/translator) বা [Google Translate](https://translate.google.com)-এর মতো একটি পরিষেবা ব্যবহার করতে পারেন আপনার পছন্দের ভাষা থেকে অন্য ভাষায় অনুবাদ করতে। এই পরিষেবাগুলি অনুবাদিত টেক্সটের অডিও প্লে করতে পারে।
    >
    > উদাহরণস্বরূপ, যদি আপনি LUIS-কে ইংরেজিতে প্রশিক্ষণ দেন, কিন্তু ব্যবহারকারীর ভাষা হিসেবে ফরাসি ব্যবহার করতে চান, তাহলে Bing Translate ব্যবহার করে "set a 2 minute and 27 second timer" ইংরেজি থেকে ফরাসিতে অনুবাদ করতে পারেন। এরপর **Listen translation** বোতামটি ব্যবহার করে অনুবাদটি আপনার মাইক্রোফোনে বলতে পারেন।
    >
    > ![Bing Translate-এ Listen translation বোতাম](../../../../../translated_images/bn/bing-translate.348aa796d6efe2a9.webp)

1. `SPEECH_LOCATION`-এর নিচে অনুবাদক API কী এবং অবস্থান যোগ করুন:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    `<KEY>`-এর জায়গায় আপনার অনুবাদক পরিষেবা রিসোর্সের API কীটি প্রতিস্থাপন করুন। `<LOCATION>`-এর জায়গায় আপনি যখন অনুবাদক পরিষেবা রিসোর্স তৈরি করেছিলেন তখন ব্যবহৃত অবস্থানটি প্রতিস্থাপন করুন।

1. `VOICE_URL`-এর নিচে অনুবাদক ট্রিগার URL যোগ করুন:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    `<URL>`-এর জায়গায় আপনার ফাংশন অ্যাপের `translate-text` HTTP ট্রিগারের URLটি প্রতিস্থাপন করুন। এটি `TEXT_TO_TIMER_FUNCTION_URL`-এর মতোই হবে, তবে ফাংশনের নাম `text-to-timer` এর পরিবর্তে `translate-text` হবে।

1. `src` ফোল্ডারে একটি নতুন ফাইল যোগ করুন, যার নাম হবে `text_translator.h`।

1. এই নতুন `text_translator.h` হেডার ফাইলটি একটি ক্লাস ধারণ করবে, যা টেক্সট অনুবাদ করবে। এই ফাইলটিতে নিম্নলিখিত কোড যোগ করুন, যা এই ক্লাসটি ঘোষণা করবে:

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

    এটি `TextTranslator` ক্লাসটি ঘোষণা করে, এবং এই ক্লাসের একটি ইনস্ট্যান্স তৈরি করে। ক্লাসটির একটি ফিল্ড রয়েছে, যা WiFi ক্লায়েন্টের জন্য।

1. এই ক্লাসের `public` সেকশনে একটি মেথড যোগ করুন, যা টেক্সট অনুবাদ করবে:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    এই মেথডটি অনুবাদ করার ভাষা এবং অনুবাদ করার ভাষা গ্রহণ করে। বক্তৃতা পরিচালনা করার সময়, বক্তৃতাটি ব্যবহারকারীর ভাষা থেকে LUIS সার্ভারের ভাষায় অনুবাদ করা হবে, এবং প্রতিক্রিয়া দেওয়ার সময় এটি LUIS সার্ভারের ভাষা থেকে ব্যবহারকারীর ভাষায় অনুবাদ করবে।

1. এই মেথডে কোড যোগ করুন, যা অনুবাদ করার টেক্সট এবং ভাষাগুলি ধারণকারী একটি JSON বডি তৈরি করবে:

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

1. এর নিচে, সার্ভারলেস ফাংশন অ্যাপে বডি পাঠানোর জন্য নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. এরপর, প্রতিক্রিয়া পাওয়ার জন্য কোড যোগ করুন:

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

1. শেষে, সংযোগ বন্ধ করার এবং অনুবাদিত টেক্সট ফেরত দেওয়ার জন্য কোড যোগ করুন:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### কাজ - স্বীকৃত বক্তৃতা এবং প্রতিক্রিয়াগুলি অনুবাদ করুন

1. `main.cpp` ফাইলটি খুলুন।

1. ফাইলের শীর্ষে `TextTranslator` ক্লাস হেডার ফাইলের জন্য একটি ইনক্লুড ডিরেক্টিভ যোগ করুন:

    ```cpp
    #include "text_translator.h"
    ```

1. যখন একটি টাইমার সেট করা হয় বা শেষ হয়, তখন বলা টেক্সটটি অনুবাদ করতে হবে। এটি করতে, `say` ফাংশনের প্রথম লাইনে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    এটি টেক্সটটি ব্যবহারকারীর ভাষায় অনুবাদ করবে।

1. `processAudio` ফাংশনে, `String text = speechToText.convertSpeechToText();` কলের মাধ্যমে ক্যাপচার করা অডিও থেকে টেক্সট পুনরুদ্ধার করা হয়। এই কলের পরে, টেক্সটটি অনুবাদ করুন:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    এটি ব্যবহারকারীর ভাষা থেকে সার্ভারে ব্যবহৃত ভাষায় টেক্সটটি অনুবাদ করবে।

1. এই কোডটি তৈরি করুন, এটি আপনার Wio Terminal-এ আপলোড করুন এবং সিরিয়াল মনিটরের মাধ্যমে এটি পরীক্ষা করুন। একবার আপনি সিরিয়াল মনিটরে `Ready` দেখতে পেলে, C বোতামটি চাপুন (বাম দিকে, পাওয়ার সুইচের সবচেয়ে কাছাকাছি), এবং কথা বলুন। নিশ্চিত করুন যে আপনার ফাংশন অ্যাপটি চালু রয়েছে এবং ব্যবহারকারীর ভাষায় একটি টাইমার অনুরোধ করুন, হয় নিজে সেই ভাষায় কথা বলে, অথবা একটি অনুবাদ অ্যাপ ব্যবহার করে।

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

> 💁 আপনি এই কোডটি [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার বহুভাষিক টাইমার প্রোগ্রাম সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিকতার জন্য চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা তার জন্য দায়ী থাকব না।