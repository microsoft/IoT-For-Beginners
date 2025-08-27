<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T10:43:18+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "bn"
}
-->
# IoT Edge ভিত্তিক ইমেজ ক্লাসিফায়ার ব্যবহার করে একটি ছবি শ্রেণীবদ্ধ করুন - Wio Terminal

এই পাঠের এই অংশে, আপনি IoT Edge ডিভাইসে চলমান ইমেজ ক্লাসিফায়ার ব্যবহার করবেন।

## IoT Edge ক্লাসিফায়ার ব্যবহার করুন

IoT ডিভাইসটিকে IoT Edge ইমেজ ক্লাসিফায়ার ব্যবহার করার জন্য পুনঃনির্দেশিত করা যেতে পারে। ইমেজ ক্লাসিফায়ারের URL হলো `http://<IP address or name>/image`, যেখানে `<IP address or name>`-এর জায়গায় IoT Edge চালানো কম্পিউটারের IP ঠিকানা বা হোস্ট নাম বসাতে হবে।

### কাজ - IoT Edge ক্লাসিফায়ার ব্যবহার করুন

1. যদি এটি ইতিমধ্যে খোলা না থাকে, তাহলে `fruit-quality-detector` অ্যাপ প্রকল্পটি খুলুন।

1. ইমেজ ক্লাসিফায়ারটি HTTP ব্যবহার করে একটি REST API হিসেবে চলছে, HTTPS নয়, তাই কলটি এমন একটি WiFi ক্লায়েন্ট ব্যবহার করতে হবে যা শুধুমাত্র HTTP কলের সাথে কাজ করে। এর মানে হলো সার্টিফিকেট প্রয়োজন নেই। `config.h` ফাইল থেকে `CERTIFICATE` মুছে ফেলুন।

1. `config.h` ফাইলে প্রেডিকশন URL-টি নতুন URL-এ আপডেট করতে হবে। এছাড়াও, `PREDICTION_KEY` মুছে ফেলতে পারেন কারণ এটি প্রয়োজন নেই।

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    `<URL>`-এর জায়গায় আপনার ক্লাসিফায়ারের URL বসান।

1. `main.cpp`-এ, WiFi Client Secure-এর জন্য ইনক্লুড ডিরেক্টিভটি পরিবর্তন করে স্ট্যান্ডার্ড HTTP সংস্করণ আমদানি করুন:

    ```cpp
    #include <WiFiClient.h>
    ```

1. `WiFiClient`-এর ডিক্লারেশনটি HTTP সংস্করণে পরিবর্তন করুন:

    ```cpp
    WiFiClient client;
    ```

1. WiFi ক্লায়েন্টে সার্টিফিকেট সেট করার লাইনটি নির্বাচন করুন। `connectWiFi` ফাংশন থেকে `client.setCACert(CERTIFICATE);` লাইনটি মুছে ফেলুন।

1. `classifyImage` ফাংশনে, হেডারে প্রেডিকশন কী সেট করার জন্য ব্যবহৃত `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` লাইনটি মুছে ফেলুন।

1. আপনার কোড আপলোড করুন এবং চালান। ক্যামেরাটি কিছু ফলের দিকে নির্দেশ করুন এবং C বোতামটি চাপুন। আপনি সিরিয়াল মনিটরে আউটপুট দেখতে পাবেন:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 আপনি এই কোডটি [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার ফলের গুণমান নির্ধারণকারী প্রোগ্রামটি সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিক অনুবাদ প্রদানের চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা তার জন্য দায়ী থাকব না।