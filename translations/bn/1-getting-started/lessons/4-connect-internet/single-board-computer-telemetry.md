<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-27T12:18:53+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "bn"
}
-->
# ইন্টারনেটের মাধ্যমে আপনার নাইটলাইট নিয়ন্ত্রণ করুন - ভার্চুয়াল IoT হার্ডওয়্যার এবং রাস্পবেরি পাই

এই পাঠের এই অংশে, আপনি আপনার রাস্পবেরি পাই বা ভার্চুয়াল IoT ডিভাইস থেকে আলো স্তরের টেলিমেট্রি একটি MQTT ব্রোকারে পাঠাবেন।

## টেলিমেট্রি প্রকাশ করুন

পরবর্তী ধাপটি হলো টেলিমেট্রির জন্য একটি JSON ডকুমেন্ট তৈরি করা এবং এটি MQTT ব্রোকারে পাঠানো।

### কাজ

MQTT ব্রোকারে টেলিমেট্রি প্রকাশ করুন।

1. VS Code-এ নাইটলাইট প্রকল্পটি খুলুন।

1. যদি আপনি একটি ভার্চুয়াল IoT ডিভাইস ব্যবহার করেন, তাহলে নিশ্চিত করুন যে টার্মিনাল ভার্চুয়াল পরিবেশ চালাচ্ছে। যদি আপনি রাস্পবেরি পাই ব্যবহার করেন, তাহলে ভার্চুয়াল পরিবেশ ব্যবহার করা হবে না।

1. `app.py` ফাইলের শীর্ষে নিম্নলিখিত ইমপোর্ট যোগ করুন:

    ```python
    import json
    ```

    `json` লাইব্রেরি টেলিমেট্রিকে একটি JSON ডকুমেন্ট হিসেবে এনকোড করতে ব্যবহৃত হয়।

1. `client_name` ঘোষণার পরে নিম্নলিখিত কোড যোগ করুন:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` হলো MQTT টপিক যেখানে ডিভাইস আলো স্তর প্রকাশ করবে।

1. ফাইলের শেষে `while True:` লুপের বিষয়বস্তু নিম্নলিখিত কোড দিয়ে প্রতিস্থাপন করুন:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    এই কোড আলো স্তরকে একটি JSON ডকুমেন্টে প্যাকেজ করে এবং এটি MQTT ব্রোকারে প্রকাশ করে। তারপর এটি বার্তা পাঠানোর ফ্রিকোয়েন্সি কমানোর জন্য কিছুক্ষণ অপেক্ষা করে।

1. আগের অংশের কোড চালানোর মতো একইভাবে কোড চালান। যদি আপনি একটি ভার্চুয়াল IoT ডিভাইস ব্যবহার করেন, তাহলে নিশ্চিত করুন যে CounterFit অ্যাপটি চালু আছে এবং আলো সেন্সর এবং LED সঠিক পিনে তৈরি করা হয়েছে।

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 আপনি এই কোডটি [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) ফোল্ডারে বা [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনি সফলভাবে আপনার ডিভাইস থেকে টেলিমেট্রি পাঠিয়েছেন।

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিক অনুবাদ প্রদানের চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা তার জন্য দায়ী থাকব না।