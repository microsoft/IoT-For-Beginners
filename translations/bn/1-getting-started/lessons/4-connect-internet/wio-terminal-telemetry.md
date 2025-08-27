<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-27T12:30:09+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "bn"
}
-->
# ইন্টারনেটের মাধ্যমে আপনার নাইটলাইট নিয়ন্ত্রণ করুন - Wio Terminal

এই পাঠের এই অংশে, আপনি আপনার Wio Terminal থেকে MQTT ব্রোকারে লাইট লেভেলের টেলিমেট্রি পাঠাবেন।

## JSON Arduino লাইব্রেরি ইনস্টল করুন

MQTT এর মাধ্যমে বার্তা পাঠানোর একটি জনপ্রিয় উপায় হল JSON ব্যবহার করা। JSON ডকুমেন্ট পড়া এবং লেখা সহজ করার জন্য একটি Arduino লাইব্রেরি রয়েছে।

### কাজ

Arduino JSON লাইব্রেরি ইনস্টল করুন।

1. VS Code-এ নাইটলাইট প্রকল্পটি খুলুন।

1. `platformio.ini` ফাইলের `lib_deps` তালিকায় একটি অতিরিক্ত লাইন হিসেবে নিম্নলিখিতটি যোগ করুন:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    এটি [ArduinoJson](https://arduinojson.org) আমদানি করে, যা একটি Arduino JSON লাইব্রেরি।

## টেলিমেট্রি প্রকাশ করুন

পরবর্তী ধাপ হল টেলিমেট্রির জন্য একটি JSON ডকুমেন্ট তৈরি করা এবং এটি MQTT ব্রোকারে পাঠানো।

### কাজ - টেলিমেট্রি প্রকাশ করুন

MQTT ব্রোকারে টেলিমেট্রি প্রকাশ করুন।

1. MQTT ব্রোকারের জন্য টেলিমেট্রি টপিক নাম সংজ্ঞায়িত করতে `config.h` ফাইলের নিচে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` হল সেই টপিক যেখানে ডিভাইসটি লাইট লেভেল প্রকাশ করবে।

1. `main.cpp` ফাইলটি খুলুন।

1. ফাইলের শীর্ষে নিম্নলিখিত `#include` নির্দেশনা যোগ করুন:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `loop` ফাংশনের ভিতরে, `delay` এর ঠিক আগে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    এই কোডটি লাইট লেভেল পড়ে এবং ArduinoJson ব্যবহার করে একটি JSON ডকুমেন্ট তৈরি করে যা এই লেভেল ধারণ করে। এটি একটি স্ট্রিংয়ে সিরিয়ালাইজ করা হয় এবং MQTT ক্লায়েন্টের মাধ্যমে টেলিমেট্রি MQTT টপিকে প্রকাশ করা হয়।

1. আপনার Wio Terminal-এ কোড আপলোড করুন এবং Serial Monitor ব্যবহার করে দেখুন কিভাবে লাইট লেভেলগুলি MQTT ব্রোকারে পাঠানো হচ্ছে।

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 আপনি এই কোডটি [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনি সফলভাবে আপনার ডিভাইস থেকে টেলিমেট্রি পাঠিয়েছেন।

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিক অনুবাদ প্রদানের চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা দায়বদ্ধ থাকব না।