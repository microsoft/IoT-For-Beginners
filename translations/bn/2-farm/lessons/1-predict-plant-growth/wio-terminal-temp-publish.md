<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T11:07:12+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "bn"
}
-->
# তাপমাত্রা প্রকাশ করুন - Wio Terminal

এই পাঠের এই অংশে, আপনি Wio Terminal দ্বারা সনাক্ত করা তাপমাত্রার মানগুলি MQTT এর মাধ্যমে প্রকাশ করবেন যাতে পরে GDD গণনার জন্য ব্যবহার করা যেতে পারে।

## তাপমাত্রা প্রকাশ করুন

একবার তাপমাত্রা পড়া হয়ে গেলে, এটি MQTT এর মাধ্যমে কিছু 'server' কোডে প্রকাশ করা যেতে পারে যা মানগুলি পড়বে এবং GDD গণনার জন্য প্রস্তুত রাখতে সংরক্ষণ করবে। মাইক্রোকন্ট্রোলারগুলি ইন্টারনেট থেকে সময় পড়ে না এবং ডিফল্টভাবে একটি রিয়েল-টাইম ক্লক দিয়ে সময় ট্র্যাক করে না, ডিভাইসটি এটি করার জন্য প্রোগ্রাম করতে হবে, যদি প্রয়োজনীয় হার্ডওয়্যার থাকে।

এই পাঠের জন্য বিষয়গুলো সহজ করার জন্য, সেন্সর ডেটার সাথে সময় পাঠানো হবে না, পরিবর্তে যখন সার্ভার কোড বার্তাগুলি গ্রহণ করবে তখন এটি যোগ করা যেতে পারে।

### কাজ

ডিভাইসটি তাপমাত্রার ডেটা প্রকাশ করার জন্য প্রোগ্রাম করুন।

1. `temperature-sensor` Wio Terminal প্রকল্পটি খুলুন

1. MQTT-তে সংযোগ স্থাপন এবং টেলিমেট্রি পাঠানোর জন্য আপনি পাঠ ৪-এ যা করেছিলেন তা পুনরাবৃত্তি করুন। আপনি একই পাবলিক Mosquitto ব্রোকার ব্যবহার করবেন।

    এই ধাপগুলো হল:

    - `.ini` ফাইলে Seeed WiFi এবং MQTT লাইব্রেরি যোগ করুন
    - WiFi-তে সংযোগ করার জন্য কনফিগ ফাইল এবং কোড যোগ করুন
    - MQTT ব্রোকারে সংযোগ করার জন্য কোড যোগ করুন
    - টেলিমেট্রি প্রকাশ করার জন্য কোড যোগ করুন

    > ⚠️ MQTT-তে সংযোগ করার [নির্দেশাবলী](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) এবং টেলিমেট্রি পাঠানোর [নির্দেশাবলী](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) পাঠ ৪ থেকে প্রয়োজন হলে দেখুন।

1. নিশ্চিত করুন যে `config.h` হেডার ফাইলে `CLIENT_NAME` এই প্রকল্পটি প্রতিফলিত করে:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. টেলিমেট্রির জন্য, একটি light value পাঠানোর পরিবর্তে, DHT সেন্সর থেকে পড়া তাপমাত্রার মানটি JSON ডকুমেন্টে `temperature` নামে একটি প্রপার্টিতে পাঠান `main.cpp`-এর `loop` ফাংশন পরিবর্তন করে:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. তাপমাত্রার মান খুব ঘন ঘন পড়ার প্রয়োজন নেই - এটি স্বল্প সময়ে খুব বেশি পরিবর্তন হবে না, তাই `loop` ফাংশনে `delay` ১০ মিনিটে সেট করুন:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 `delay` ফাংশন সময়কে মিলিসেকেন্ডে নেয়, তাই এটি পড়া সহজ করার জন্য মানটি একটি গণনার ফলাফল হিসাবে পাস করা হয়। ১,০০০ms একটি সেকেন্ডে, ৬০s একটি মিনিটে, তাই ১০ x (৬০s একটি মিনিটে) x (১০০০ms একটি সেকেন্ডে) ১০ মিনিটের বিলম্ব দেয়।

1. এটি আপনার Wio Terminal-এ আপলোড করুন এবং MQTT ব্রোকারে তাপমাত্রা পাঠানো হচ্ছে কিনা তা দেখতে সিরিয়াল মনিটর ব্যবহার করুন।

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 আপনি এই কোডটি [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনি সফলভাবে আপনার ডিভাইস থেকে টেলিমেট্রি হিসাবে তাপমাত্রা প্রকাশ করেছেন।

---

**দাবিত্যাগ**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসাধ্য সঠিকতা নিশ্চিত করার চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা দায়বদ্ধ থাকব না।