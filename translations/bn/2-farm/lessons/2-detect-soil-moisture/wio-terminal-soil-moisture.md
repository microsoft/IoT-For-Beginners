# মাটি আর্দ্রতা পরিমাপ করুন - Wio Terminal

এই পাঠের এই অংশে, আপনি আপনার Wio Terminal-এ একটি capacitive মাটি আর্দ্রতা সেন্সর যোগ করবেন এবং এর থেকে মান পড়বেন।

## হার্ডওয়্যার

Wio Terminal-এর জন্য একটি capacitive মাটি আর্দ্রতা সেন্সর প্রয়োজন।

আপনি যে সেন্সরটি ব্যবহার করবেন তা হলো [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), যা মাটির আর্দ্রতা পরিমাপ করে মাটির capacitance সনাক্ত করার মাধ্যমে। মাটির আর্দ্রতা পরিবর্তনের সাথে সাথে এই বৈশিষ্ট্য পরিবর্তিত হয়। মাটির আর্দ্রতা বাড়ার সাথে সাথে ভোল্টেজ কমে যায়।

এটি একটি অ্যানালগ সেন্সর, যা Wio Terminal-এর অ্যানালগ পিনে সংযুক্ত হয় এবং একটি অনবোর্ড ADC ব্যবহার করে ০-১,০২৩ এর মধ্যে একটি মান তৈরি করে।

### মাটি আর্দ্রতা সেন্সর সংযুক্ত করুন

Grove মাটি আর্দ্রতা সেন্সরটি Wio Terminal-এর কনফিগারযোগ্য অ্যানালগ/ডিজিটাল পোর্টে সংযুক্ত করা যেতে পারে।

#### কাজ - মাটি আর্দ্রতা সেন্সর সংযুক্ত করুন

মাটি আর্দ্রতা সেন্সর সংযুক্ত করুন।

![একটি Grove মাটি আর্দ্রতা সেন্সর](../../../../../translated_images/bn/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Grove কেবলের এক প্রান্ত মাটি আর্দ্রতা সেন্সরের সকেটে প্রবেশ করান। এটি শুধুমাত্র একটি নির্দিষ্ট দিকেই প্রবেশ করবে।

1. Wio Terminal আপনার কম্পিউটার বা অন্য পাওয়ার সাপ্লাই থেকে সংযোগ বিচ্ছিন্ন অবস্থায়, Grove কেবলের অন্য প্রান্তটি Wio Terminal-এর ডান পাশের Grove সকেটে সংযুক্ত করুন, যখন আপনি স্ক্রিনের দিকে তাকাচ্ছেন। এটি পাওয়ার বোতামের থেকে সবচেয়ে দূরের সকেট।

![ডান পাশের সকেটে সংযুক্ত Grove মাটি আর্দ্রতা সেন্সর](../../../../../translated_images/bn/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. মাটি আর্দ্রতা সেন্সরটি মাটিতে প্রবেশ করান। এতে একটি 'সর্বোচ্চ অবস্থান রেখা' রয়েছে - সেন্সরের উপর একটি সাদা রেখা। সেন্সরটি এই রেখা পর্যন্ত প্রবেশ করান, কিন্তু এর বেশি নয়।

![মাটিতে Grove মাটি আর্দ্রতা সেন্সর](../../../../../translated_images/bn/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. এখন আপনি Wio Terminal-কে আপনার কম্পিউটারে সংযুক্ত করতে পারেন।

## মাটি আর্দ্রতা সেন্সর প্রোগ্রাম করুন

এখন Wio Terminal-কে সংযুক্ত মাটি আর্দ্রতা সেন্সর ব্যবহার করার জন্য প্রোগ্রাম করা যেতে পারে।

### কাজ - মাটি আর্দ্রতা সেন্সর প্রোগ্রাম করুন

ডিভাইসটি প্রোগ্রাম করুন।

1. PlatformIO ব্যবহার করে একটি নতুন Wio Terminal প্রকল্প তৈরি করুন। এই প্রকল্পটির নাম দিন `soil-moisture-sensor`। `setup` ফাংশনে সিরিয়াল পোর্ট কনফিগার করার জন্য কোড যোগ করুন।

    > ⚠️ [প্রকল্প ১, পাঠ ১-এ PlatformIO প্রকল্প তৈরি করার নির্দেশনা প্রয়োজন হলে এখানে দেখুন](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project)।

1. এই সেন্সরের জন্য কোনো লাইব্রেরি নেই, তবে আপনি Arduino-এর বিল্ট-ইন [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) ফাংশন ব্যবহার করে অ্যানালগ পিন থেকে পড়তে পারেন। প্রথমে অ্যানালগ পিনটি ইনপুটের জন্য কনফিগার করুন যাতে এটি থেকে মান পড়া যায়। `setup` ফাংশনে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    pinMode(A0, INPUT);
    ```

    এটি `A0` পিন, যা অ্যানালগ/ডিজিটাল পিনের সংমিশ্রণ, ইনপুট পিন হিসেবে সেট করে যাতে ভোল্টেজ পড়া যায়।

1. `loop` ফাংশনে নিম্নলিখিত কোড যোগ করুন যাতে এই পিন থেকে ভোল্টেজ পড়া যায়:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. এই কোডের নিচে, সিরিয়াল পোর্টে মান প্রিন্ট করার জন্য নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. শেষে ১০ সেকেন্ডের একটি বিলম্ব যোগ করুন:

    ```cpp
    delay(10000);
    ```

1. কোডটি Wio Terminal-এ বিল্ড এবং আপলোড করুন।

    > ⚠️ [প্রকল্প ১, পাঠ ১-এ PlatformIO প্রকল্প তৈরি করার নির্দেশনা প্রয়োজন হলে এখানে দেখুন](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app)।

1. আপলোড করার পর, আপনি সিরিয়াল মনিটর ব্যবহার করে মাটি আর্দ্রতা পর্যবেক্ষণ করতে পারেন। মাটিতে কিছু পানি যোগ করুন, অথবা সেন্সরটি মাটি থেকে সরান এবং মান পরিবর্তন দেখুন।

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    উপরের উদাহরণ আউটপুটে, আপনি দেখতে পারেন পানি যোগ করার সাথে সাথে ভোল্টেজ কমে যাচ্ছে।

> 💁 আপনি এই কোডটি [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার মাটি আর্দ্রতা সেন্সর প্রোগ্রাম সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসাধ্য সঠিকতা নিশ্চিত করার চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা দায়বদ্ধ থাকব না।