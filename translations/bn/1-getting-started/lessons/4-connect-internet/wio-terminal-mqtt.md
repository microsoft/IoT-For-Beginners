<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T12:32:37+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "bn"
}
-->
# ইন্টারনেটের মাধ্যমে আপনার নাইটলাইট নিয়ন্ত্রণ করুন - Wio Terminal

IoT ডিভাইসটি *test.mosquitto.org* এর সাথে MQTT ব্যবহার করে যোগাযোগ করার জন্য কোড করা প্রয়োজন, যাতে এটি লাইট সেন্সরের রিডিং সহ টেলিমেট্রি মান পাঠাতে পারে এবং LED নিয়ন্ত্রণের জন্য কমান্ড গ্রহণ করতে পারে।

এই পাঠের অংশে, আপনি আপনার Wio Terminal-কে একটি MQTT ব্রোকারের সাথে সংযুক্ত করবেন।

## WiFi এবং MQTT Arduino লাইব্রেরি ইনস্টল করুন

MQTT ব্রোকারের সাথে যোগাযোগ করতে, আপনাকে কিছু Arduino লাইব্রেরি ইনস্টল করতে হবে যা Wio Terminal-এর WiFi চিপ ব্যবহার করে এবং MQTT এর সাথে যোগাযোগ করে। Arduino ডিভাইসের জন্য ডেভেলপ করার সময়, আপনি বিভিন্ন লাইব্রেরি ব্যবহার করতে পারেন যা ওপেন-সোর্স কোড ধারণ করে এবং অনেক ক্ষমতা বাস্তবায়ন করে। Seeed Wio Terminal-এর জন্য লাইব্রেরি প্রকাশ করে যা এটি WiFi এর মাধ্যমে যোগাযোগ করতে সক্ষম করে। অন্যান্য ডেভেলপাররা MQTT ব্রোকারের সাথে যোগাযোগ করার জন্য লাইব্রেরি প্রকাশ করেছেন, এবং আপনি এগুলি আপনার ডিভাইসের সাথে ব্যবহার করবেন।

এই লাইব্রেরিগুলি সোর্স কোড হিসাবে সরবরাহ করা হয় যা PlatformIO-তে স্বয়ংক্রিয়ভাবে আমদানি করা যায় এবং আপনার ডিভাইসের জন্য কম্পাইল করা যায়। এইভাবে Arduino লাইব্রেরিগুলি যে কোনও ডিভাইসে কাজ করবে যা Arduino ফ্রেমওয়ার্ক সমর্থন করে, যদি ডিভাইসটির সেই লাইব্রেরির জন্য প্রয়োজনীয় নির্দিষ্ট হার্ডওয়্যার থাকে। কিছু লাইব্রেরি, যেমন Seeed WiFi লাইব্রেরি, নির্দিষ্ট হার্ডওয়্যারের জন্য বিশেষভাবে তৈরি।

লাইব্রেরিগুলি গ্লোবালি ইনস্টল করা এবং প্রয়োজনে কম্পাইল করা যেতে পারে, অথবা একটি নির্দিষ্ট প্রজেক্টে। এই অ্যাসাইনমেন্টের জন্য, লাইব্রেরিগুলি প্রজেক্টে ইনস্টল করা হবে।

✅ লাইব্রেরি ম্যানেজমেন্ট এবং কীভাবে লাইব্রেরি খুঁজে এবং ইনস্টল করতে হয় সে সম্পর্কে আরও জানতে পারেন [PlatformIO লাইব্রেরি ডকুমেন্টেশন](https://docs.platformio.org/en/latest/librarymanager/index.html) থেকে।

### টাস্ক - WiFi এবং MQTT Arduino লাইব্রেরি ইনস্টল করুন

Arduino লাইব্রেরি ইনস্টল করুন।

1. VS Code-এ নাইটলাইট প্রজেক্ট খুলুন।

1. `platformio.ini` ফাইলের শেষে নিম্নলিখিত যোগ করুন:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    এটি Seeed WiFi লাইব্রেরি আমদানি করে। `@ <number>` সিনট্যাক্সটি লাইব্রেরির একটি নির্দিষ্ট সংস্করণ নম্বরকে নির্দেশ করে।

    > 💁 আপনি সর্বদা লাইব্রেরির সর্বশেষ সংস্করণ ব্যবহার করতে `@ <number>` সরিয়ে ফেলতে পারেন, তবে পরবর্তী সংস্করণগুলি নীচের কোডের সাথে কাজ করবে তার কোনও গ্যারান্টি নেই। এখানে কোডটি এই লাইব্রেরির সংস্করণের সাথে পরীক্ষা করা হয়েছে।

    লাইব্রেরি যোগ করার জন্য এটুকুই যথেষ্ট। পরবর্তীবার PlatformIO প্রজেক্টটি তৈরি করলে এটি এই লাইব্রেরিগুলির সোর্স কোড ডাউনলোড করবে এবং আপনার প্রজেক্টে কম্পাইল করবে।

1. `lib_deps`-এ নিম্নলিখিত যোগ করুন:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    এটি [PubSubClient](https://github.com/knolleary/pubsubclient), একটি Arduino MQTT ক্লায়েন্ট আমদানি করে।

## WiFi-তে সংযুক্ত করুন

এখন Wio Terminal-কে WiFi-তে সংযুক্ত করা যাবে।

### টাস্ক - WiFi-তে সংযুক্ত করুন

Wio Terminal-কে WiFi-তে সংযুক্ত করুন।

1. `src` ফোল্ডারে একটি নতুন ফাইল তৈরি করুন যার নাম `config.h`। এটি করতে, `src` ফোল্ডার বা তার ভিতরে থাকা `main.cpp` ফাইলটি নির্বাচন করুন এবং এক্সপ্লোরারে **New file** বোতামটি নির্বাচন করুন। এই বোতামটি শুধুমাত্র তখনই প্রদর্শিত হয় যখন আপনার কার্সর এক্সপ্লোরারের উপর থাকে।

    ![নতুন ফাইল বোতাম](../../../../../translated_images/bn/vscode-new-file-button.182702340fe6723c.png)

1. এই ফাইলে নিম্নলিখিত কোড যোগ করুন যা আপনার WiFi ক্রেডেনশিয়ালের জন্য কনস্ট্যান্ট সংজ্ঞায়িত করে:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    `<SSID>`-এর জায়গায় আপনার WiFi-এর SSID লিখুন। `<PASSWORD>`-এর জায়গায় আপনার WiFi পাসওয়ার্ড লিখুন।

1. `main.cpp` ফাইলটি খুলুন।

1. ফাইলের শীর্ষে নিম্নলিখিত `#include` নির্দেশগুলি যোগ করুন:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    এটি পূর্বে যোগ করা লাইব্রেরিগুলির জন্য হেডার ফাইলগুলি অন্তর্ভুক্ত করে, পাশাপাশি কনফিগ হেডার ফাইল। এই হেডার ফাইলগুলি PlatformIO-কে লাইব্রেরিগুলির কোড আনতে বলে। এই হেডার ফাইলগুলি স্পষ্টভাবে অন্তর্ভুক্ত না করলে, কিছু কোড কম্পাইল করা হবে না এবং আপনি কম্পাইলার ত্রুটি পাবেন।

1. `setup` ফাংশনের উপরে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    এই কোডটি ডিভাইসটি WiFi-তে সংযুক্ত না থাকা পর্যন্ত লুপ করে এবং কনফিগ হেডার ফাইল থেকে SSID এবং পাসওয়ার্ড ব্যবহার করে সংযোগ করার চেষ্টা করে।

1. পিনগুলি কনফিগার করার পরে `setup` ফাংশনের শেষে এই ফাংশনটি কল করুন।

    ```cpp
    connectWiFi();
    ```

1. আপনার ডিভাইসে এই কোড আপলোড করুন এবং দেখুন WiFi সংযোগ কাজ করছে কিনা। আপনি এটি সিরিয়াল মনিটরে দেখতে পাবেন।

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## MQTT-তে সংযুক্ত করুন

Wio Terminal WiFi-তে সংযুক্ত হওয়ার পরে, এটি MQTT ব্রোকারের সাথে সংযুক্ত হতে পারে।

### টাস্ক - MQTT-তে সংযুক্ত করুন

MQTT ব্রোকারের সাথে সংযুক্ত করুন।

1. MQTT ব্রোকারের সংযোগের বিবরণ সংজ্ঞায়িত করতে `config.h` ফাইলের শেষে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    `<ID>`-এর জায়গায় একটি ইউনিক আইডি লিখুন যা এই ডিভাইস ক্লায়েন্টের নাম হিসেবে ব্যবহৃত হবে এবং পরে এই ডিভাইসটি যে টপিকগুলি প্রকাশ এবং সাবস্ক্রাইব করবে তার জন্য। *test.mosquitto.org* ব্রোকারটি পাবলিক এবং অনেক লোক ব্যবহার করে, যার মধ্যে এই অ্যাসাইনমেন্টে কাজ করা অন্যান্য শিক্ষার্থীরাও রয়েছে। একটি ইউনিক MQTT ক্লায়েন্ট নাম এবং টপিক নাম থাকা নিশ্চিত করে যে আপনার কোড অন্য কারও সাথে সংঘর্ষ করবে না। আপনি এই অ্যাসাইনমেন্টে পরে সার্ভার কোড তৈরি করার সময়ও এই আইডি প্রয়োজন হবে।

    > 💁 আপনি একটি ওয়েবসাইট যেমন [GUIDGen](https://www.guidgen.com) ব্যবহার করে একটি ইউনিক আইডি তৈরি করতে পারেন।

    `BROKER` হল MQTT ব্রোকারের URL।

    `CLIENT_NAME` হল এই MQTT ক্লায়েন্টের জন্য ব্রোকারে একটি ইউনিক নাম।

1. `main.cpp` ফাইলটি খুলুন এবং `connectWiFi` ফাংশনের নিচে এবং `setup` ফাংশনের উপরে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    এই কোডটি Wio Terminal WiFi লাইব্রেরি ব্যবহার করে একটি WiFi ক্লায়েন্ট তৈরি করে এবং এটি ব্যবহার করে একটি MQTT ক্লায়েন্ট তৈরি করে।

1. এই কোডের নিচে নিম্নলিখিত যোগ করুন:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    এই ফাংশনটি MQTT ব্রোকারের সাথে সংযোগ পরীক্ষা করে এবং সংযুক্ত না থাকলে পুনরায় সংযোগ করে। এটি লুপ করে যতক্ষণ না এটি সংযুক্ত হয় এবং কনফিগ হেডার ফাইলের ইউনিক ক্লায়েন্ট নাম ব্যবহার করে সংযোগ করার চেষ্টা করে।

    যদি সংযোগ ব্যর্থ হয়, এটি ৫ সেকেন্ড পরে পুনরায় চেষ্টা করে।

1. `reconnectMQTTClient` ফাংশনের নিচে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    এই কোডটি ক্লায়েন্টের জন্য MQTT ব্রোকার সেট করে, পাশাপাশি একটি কলব্যাক সেট করে যখন একটি বার্তা গ্রহণ করা হয়। এটি ব্রোকারের সাথে সংযোগ করার চেষ্টা করে।

1. WiFi সংযুক্ত হওয়ার পরে `setup` ফাংশনে `createMQTTClient` ফাংশনটি কল করুন।

1. পুরো `loop` ফাংশনটি নিম্নলিখিত দিয়ে প্রতিস্থাপন করুন:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    এই কোডটি MQTT ব্রোকারের সাথে পুনরায় সংযোগ দিয়ে শুরু করে। এই সংযোগগুলি সহজেই ভেঙে যেতে পারে, তাই নিয়মিতভাবে পরীক্ষা করা এবং প্রয়োজন হলে পুনরায় সংযোগ করা গুরুত্বপূর্ণ। এটি তারপরে MQTT ক্লায়েন্টের `loop` মেথড কল করে যে কোনও বার্তা প্রক্রিয়া করতে যা সাবস্ক্রাইব করা টপিকে আসছে। এই অ্যাপটি সিঙ্গেল-থ্রেডেড, তাই বার্তাগুলি ব্যাকগ্রাউন্ড থ্রেডে গ্রহণ করা যাবে না, তাই প্রধান থ্রেডে নেটওয়ার্ক সংযোগে অপেক্ষমাণ বার্তাগুলি প্রক্রিয়া করার জন্য সময় বরাদ্দ করতে হবে।

    অবশেষে, ২ সেকেন্ডের একটি বিলম্ব নিশ্চিত করে যে লাইট লেভেলগুলি খুব ঘন ঘন পাঠানো হচ্ছে না এবং ডিভাইসের পাওয়ার কনজাম্পশন কমায়।

1. আপনার Wio Terminal-এ কোড আপলোড করুন এবং সিরিয়াল মনিটর ব্যবহার করে ডিভাইসটি WiFi এবং MQTT-তে সংযুক্ত হচ্ছে কিনা দেখুন।

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 আপনি এই কোডটি [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনি সফলভাবে আপনার ডিভাইসকে একটি MQTT ব্রোকারের সাথে সংযুক্ত করেছেন।

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিক অনুবাদের চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। নথিটির মূল ভাষায় থাকা সংস্করণটিকেই প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ ব্যবহার করার পরামর্শ দেওয়া হয়। এই অনুবাদ ব্যবহারের ফলে সৃষ্ট কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যার জন্য আমরা দায়ী নই।