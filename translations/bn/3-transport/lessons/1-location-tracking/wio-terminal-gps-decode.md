<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T14:49:58+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "bn"
}
-->
# জিপিএস ডেটা ডিকোড করুন - Wio Terminal

এই পাঠের এই অংশে, আপনি Wio Terminal দ্বারা জিপিএস সেন্সর থেকে পড়া NMEA বার্তাগুলি ডিকোড করবেন এবং অক্ষাংশ ও দ্রাঘিমাংশ বের করবেন।

## জিপিএস ডেটা ডিকোড করুন

যখন সিরিয়াল পোর্ট থেকে কাঁচা NMEA ডেটা পড়া হয়, তখন এটি একটি ওপেন সোর্স NMEA লাইব্রেরি ব্যবহার করে ডিকোড করা যেতে পারে।

### কাজ - জিপিএস ডেটা ডিকোড করুন

ডিভাইসটি প্রোগ্রাম করুন যাতে এটি জিপিএস ডেটা ডিকোড করতে পারে।

1. যদি `gps-sensor` অ্যাপ প্রকল্পটি ইতিমধ্যে খোলা না থাকে, তাহলে এটি খুলুন।

1. প্রকল্পের `platformio.ini` ফাইলে [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) লাইব্রেরির জন্য একটি লাইব্রেরি নির্ভরতা যোগ করুন। এই লাইব্রেরিতে NMEA ডেটা ডিকোড করার কোড রয়েছে।

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. `main.cpp` ফাইলে, TinyGPSPlus লাইব্রেরির জন্য একটি ইনক্লুড নির্দেশ যোগ করুন:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. `Serial3` ঘোষণার নিচে, NMEA বাক্য প্রক্রিয়াকরণের জন্য একটি TinyGPSPlus অবজেক্ট ঘোষণা করুন:

    ```cpp
    TinyGPSPlus gps;
    ```

1. `printGPSData` ফাংশনের বিষয়বস্তু পরিবর্তন করে নিচের কোডটি যোগ করুন:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    এই কোডটি UART সিরিয়াল পোর্ট থেকে পরবর্তী ক্যারেক্টারটি `gps` NMEA ডিকোডারে পড়ে। প্রতিটি ক্যারেক্টারের পরে, এটি পরীক্ষা করে যে ডিকোডারটি একটি বৈধ বাক্য পড়েছে কিনা, তারপর পরীক্ষা করে যে এটি একটি বৈধ অবস্থান পড়েছে কিনা। যদি অবস্থানটি বৈধ হয়, এটি সিরিয়াল মনিটরে পাঠায়, সেইসাথে এই ফিক্সে অবদান রাখা স্যাটেলাইটের সংখ্যা।

1. কোডটি Wio Terminal-এ বিল্ড এবং আপলোড করুন।

1. আপলোড করার পরে, আপনি সিরিয়াল মনিটর ব্যবহার করে জিপিএস অবস্থান ডেটা পর্যবেক্ষণ করতে পারবেন।

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 আপনি এই কোডটি [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার জিপিএস সেন্সর প্রোগ্রাম ডেটা ডিকোডিং সহ সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিক অনুবাদের চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। নথিটির মূল ভাষায় লেখা সংস্করণটিকেই প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ ব্যবহার করার পরামর্শ দেওয়া হয়। এই অনুবাদ ব্যবহারের ফলে সৃষ্ট কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যার জন্য আমরা দায়ী নই।