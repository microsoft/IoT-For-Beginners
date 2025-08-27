<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T13:50:49+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "bn"
}
-->
# টাইমার সেট করুন - Wio Terminal

এই পাঠের এই অংশে, আপনি আপনার সার্ভারলেস কোড কল করবেন বক্তৃতা বুঝতে এবং ফলাফলের উপর ভিত্তি করে আপনার Wio Terminal-এ একটি টাইমার সেট করবেন।

## টাইমার সেট করুন

বক্তৃতা থেকে টেক্সটে রূপান্তরিত হওয়া টেক্সটটি আপনার সার্ভারলেস কোডে পাঠাতে হবে যাতে এটি LUIS দ্বারা প্রক্রিয়াকৃত হয় এবং টাইমারের জন্য সেকেন্ডের সংখ্যা ফেরত পাওয়া যায়। এই সেকেন্ডের সংখ্যা টাইমার সেট করতে ব্যবহার করা যেতে পারে।

মাইক্রোকন্ট্রোলারগুলোতে সাধারণত Arduino-তে মাল্টিপল থ্রেডের জন্য নেটিভ সাপোর্ট থাকে না, তাই Python বা অন্যান্য উচ্চ-স্তরের ভাষায় কোডিং করার সময় যেমন স্ট্যান্ডার্ড টাইমার ক্লাস পাওয়া যায়, তেমনটি এখানে নেই। এর পরিবর্তে, আপনি টাইমার লাইব্রেরি ব্যবহার করতে পারেন যা `loop` ফাংশনে অতিবাহিত সময় পরিমাপ করে কাজ করে এবং সময় শেষ হলে ফাংশন কল করে।

### কাজ - টেক্সটটি সার্ভারলেস ফাংশনে পাঠান

1. যদি এটি ইতিমধ্যে খোলা না থাকে, তাহলে VS Code-এ `smart-timer` প্রজেক্টটি খুলুন।

1. `config.h` হেডার ফাইলটি খুলুন এবং আপনার ফাংশন অ্যাপের URL যোগ করুন:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    `<URL>`-এর জায়গায় আপনার ফাংশন অ্যাপের URL বসান, যা আপনি আগের পাঠের শেষ ধাপে পেয়েছিলেন, যা আপনার লোকাল মেশিনের IP ঠিকানার দিকে নির্দেশ করে যেখানে ফাংশন অ্যাপটি চলছে।

1. `src` ফোল্ডারে একটি নতুন ফাইল তৈরি করুন যার নাম হবে `language_understanding.h`। এটি একটি ক্লাস সংজ্ঞায়িত করতে ব্যবহৃত হবে যা স্বীকৃত বক্তৃতাকে আপনার ফাংশন অ্যাপে পাঠাবে এবং LUIS ব্যবহার করে সেকেন্ডে রূপান্তর করবে।

1. এই ফাইলের শীর্ষে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    এটি প্রয়োজনীয় কিছু হেডার ফাইল অন্তর্ভুক্ত করে।

1. `LanguageUnderstanding` নামে একটি ক্লাস সংজ্ঞায়িত করুন এবং এই ক্লাসের একটি ইনস্ট্যান্স ঘোষণা করুন:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. আপনার ফাংশন অ্যাপ কল করতে, একটি WiFi ক্লায়েন্ট ঘোষণা করতে হবে। ক্লাসের `private` সেকশনে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    WiFiClient _client;
    ```

1. `public` সেকশনে, `GetTimerDuration` নামে একটি মেথড ঘোষণা করুন যা ফাংশন অ্যাপ কল করবে:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. `GetTimerDuration` মেথডে, ফাংশন অ্যাপে পাঠানোর জন্য JSON তৈরি করতে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    এটি `GetTimerDuration` মেথডে পাঠানো টেক্সটকে নিম্নলিখিত JSON-এ রূপান্তর করে:

    ```json
    {
        "text" : "<text>"
    }
    ```

    যেখানে `<text>` হলো ফাংশনে পাঠানো টেক্সট।

1. এর নিচে, ফাংশন অ্যাপ কল করার জন্য নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    এটি একটি POST রিকোয়েস্ট তৈরি করে, JSON বডি পাঠায় এবং রেসপন্স কোড পায়।

1. এর নিচে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    এই কোডটি রেসপন্স কোড চেক করে। যদি এটি 200 (সফল) হয়, তাহলে টাইমারের জন্য সেকেন্ডের সংখ্যা রেসপন্স বডি থেকে পাওয়া যায়। অন্যথায় একটি ত্রুটি সিরিয়াল মনিটরে পাঠানো হয় এবং সেকেন্ডের সংখ্যা 0 সেট করা হয়।

1. এই মেথডের শেষে নিম্নলিখিত কোড যোগ করুন যা HTTP সংযোগ বন্ধ করে এবং সেকেন্ডের সংখ্যা রিটার্ন করে:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. `main.cpp` ফাইলে এই নতুন হেডারটি অন্তর্ভুক্ত করুন:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `processAudio` ফাংশনের শেষে, `GetTimerDuration` মেথড কল করুন টাইমারের সময়কাল পেতে:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    এটি `SpeechToText` ক্লাস থেকে প্রাপ্ত টেক্সটকে টাইমারের সেকেন্ডের সংখ্যায় রূপান্তর করে।

### কাজ - টাইমার সেট করুন

সেকেন্ডের সংখ্যা টাইমার সেট করতে ব্যবহার করা যেতে পারে।

1. `platformio.ini` ফাইলে নিম্নলিখিত লাইব্রেরি ডিপেনডেন্সি যোগ করুন একটি টাইমার সেট করার জন্য:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. `main.cpp` ফাইলে এই লাইব্রেরির জন্য একটি ইনক্লুড ডিরেক্টিভ যোগ করুন:

    ```cpp
    #include <arduino-timer.h>
    ```

1. `processAudio` ফাংশনের উপরে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    auto timer = timer_create_default();
    ```

    এই কোডটি একটি `timer` নামে টাইমার ঘোষণা করে।

1. এর নিচে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    এই `say` ফাংশনটি ভবিষ্যতে টেক্সটকে বক্তৃতায় রূপান্তর করবে, তবে আপাতত এটি সিরিয়াল মনিটরে পাঠানো টেক্সট লিখবে।

1. `say` ফাংশনের নিচে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    এটি একটি কলব্যাক ফাংশন যা টাইমার শেষ হলে কল করা হবে। এটি একটি বার্তা পাস করে যা টাইমার শেষ হলে বলা হবে। টাইমার পুনরাবৃত্তি করতে পারে, এবং এই কলব্যাকের রিটার্ন ভ্যালু দ্বারা এটি নিয়ন্ত্রণ করা যায় - এটি `false` রিটার্ন করে, যা টাইমারকে পুনরায় চালাতে না বলে।

1. `processAudio` ফাংশনের শেষে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    এই কোডটি মোট সেকেন্ডের সংখ্যা চেক করে, এবং যদি এটি 0 হয়, তাহলে ফাংশন কল থেকে রিটার্ন করে যাতে কোনো টাইমার সেট না হয়। এটি মোট সেকেন্ডের সংখ্যাকে মিনিট এবং সেকেন্ডে রূপান্তর করে।

1. এর নিচে, টাইমার শুরু হলে বলার জন্য একটি বার্তা তৈরি করতে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. এর নিচে, টাইমার শেষ হলে বলার জন্য অনুরূপ কোড যোগ করুন:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. এর পরে, টাইমার শুরু হওয়ার বার্তা বলুন:

    ```cpp
    say(begin_message);
    ```

1. এই ফাংশনের শেষে, টাইমার শুরু করুন:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    এটি টাইমার ট্রিগার করে। টাইমারটি মিলিসেকেন্ড ব্যবহার করে সেট করা হয়, তাই মোট সেকেন্ডের সংখ্যা 1,000 দ্বারা গুণ করা হয় মিলিসেকেন্ডে রূপান্তর করতে। `timerExpired` ফাংশনটি কলব্যাক হিসাবে পাস করা হয়, এবং `end_message` কলব্যাকের কাছে পাস করার জন্য একটি আর্গুমেন্ট হিসাবে পাস করা হয়। এই কলব্যাক শুধুমাত্র `void *` আর্গুমেন্ট গ্রহণ করে, তাই স্ট্রিংটি উপযুক্তভাবে রূপান্তরিত হয়।

1. অবশেষে, টাইমারকে *টিক* করতে হবে, এবং এটি `loop` ফাংশনের শেষে নিম্নলিখিত কোড যোগ করে করা হয়:

    ```cpp
    timer.tick();
    ```

1. এই কোডটি বিল্ড করুন, এটি আপনার Wio Terminal-এ আপলোড করুন এবং সিরিয়াল মনিটরের মাধ্যমে এটি পরীক্ষা করুন। একবার আপনি সিরিয়াল মনিটরে `Ready` দেখতে পেলে, C বোতামটি চাপুন (বাম দিকে, পাওয়ার সুইচের সবচেয়ে কাছের বোতাম), এবং কথা বলুন। 4 সেকেন্ডের অডিও ধারণ করা হবে, টেক্সটে রূপান্তরিত হবে, তারপর আপনার ফাংশন অ্যাপে পাঠানো হবে, এবং একটি টাইমার সেট করা হবে। নিশ্চিত করুন যে আপনার ফাংশন অ্যাপ লোকালভাবে চলছে।

    আপনি দেখতে পাবেন কখন টাইমার শুরু হয় এবং কখন শেষ হয়।

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 আপনি এই কোডটি [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার টাইমার প্রোগ্রাম সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিক অনুবাদের চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। নথিটির মূল ভাষায় থাকা সংস্করণটিকেই প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ ব্যবহার করার পরামর্শ দেওয়া হচ্ছে। এই অনুবাদ ব্যবহারের ফলে সৃষ্ট কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যার জন্য আমরা দায়ী নই।