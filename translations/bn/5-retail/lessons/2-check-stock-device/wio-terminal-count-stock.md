<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T09:55:09+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "bn"
}
-->
# আপনার IoT ডিভাইস থেকে স্টক গণনা করুন - Wio Terminal

একটি চিত্রে স্টক গণনার জন্য ভবিষ্যদ্বাণী এবং তাদের বাউন্ডিং বক্সগুলির সংমিশ্রণ ব্যবহার করা যেতে পারে।

## স্টক গণনা করুন

![প্রতিটি ক্যানের চারপাশে বাউন্ডিং বক্স সহ ৪টি টমেটো পেস্টের ক্যান](../../../../../translated_images/bn/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

উপরে প্রদর্শিত চিত্রে, বাউন্ডিং বক্সগুলির মধ্যে সামান্য ওভারল্যাপ রয়েছে। যদি এই ওভারল্যাপ অনেক বেশি বড় হয়, তাহলে বাউন্ডিং বক্সগুলি একই বস্তু নির্দেশ করতে পারে। বস্তুগুলি সঠিকভাবে গণনা করতে, আপনাকে উল্লেখযোগ্য ওভারল্যাপ সহ বক্সগুলি উপেক্ষা করতে হবে।

### কাজ - ওভারল্যাপ উপেক্ষা করে স্টক গণনা করুন

1. আপনার `stock-counter` প্রকল্পটি খুলুন যদি এটি ইতিমধ্যে খোলা না থাকে।

1. `processPredictions` ফাংশনের উপরে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    এটি বাউন্ডিং বক্সগুলিকে একই বস্তু হিসাবে বিবেচনা করার আগে অনুমোদিত শতাংশ ওভারল্যাপ সংজ্ঞায়িত করে। 0.20 একটি ২০% ওভারল্যাপ নির্দেশ করে।

1. এর নিচে, এবং `processPredictions` ফাংশনের উপরে, দুটি আয়তক্ষেত্রের মধ্যে ওভারল্যাপ গণনা করার জন্য নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    এই কোডটি একটি `Point` স্ট্রাক্ট সংজ্ঞায়িত করে যা চিত্রের পয়েন্টগুলি সংরক্ষণ করে এবং একটি `Rect` স্ট্রাক্ট সংজ্ঞায়িত করে যা একটি আয়তক্ষেত্রকে উপরের বাম এবং নিচের ডান কোঅর্ডিনেট ব্যবহার করে সংজ্ঞায়িত করে। এটি একটি `area` ফাংশন সংজ্ঞায়িত করে যা একটি আয়তক্ষেত্রের এলাকা উপরের বাম এবং নিচের ডান কোঅর্ডিনেট থেকে গণনা করে।

    এরপর এটি একটি `overlappingArea` ফাংশন সংজ্ঞায়িত করে যা দুটি আয়তক্ষেত্রের ওভারল্যাপিং এলাকা গণনা করে। যদি তারা ওভারল্যাপ না করে, এটি 0 ফেরত দেয়।

1. `overlappingArea` ফাংশনের নিচে, একটি বাউন্ডিং বক্সকে `Rect` এ রূপান্তর করার জন্য একটি ফাংশন ঘোষণা করুন:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    এটি অবজেক্ট ডিটেক্টর থেকে একটি ভবিষ্যদ্বাণী গ্রহণ করে, বাউন্ডিং বক্সটি বের করে এবং বাউন্ডিং বক্সের মানগুলি ব্যবহার করে একটি আয়তক্ষেত্র সংজ্ঞায়িত করে। ডান পাশটি বাম প্লাস প্রস্থ থেকে গণনা করা হয়। নিচের অংশটি উপরের প্লাস উচ্চতা হিসাবে গণনা করা হয়।

1. ভবিষ্যদ্বাণীগুলিকে একে অপরের সাথে তুলনা করতে হবে, এবং যদি দুটি ভবিষ্যদ্বাণীর ওভারল্যাপ থ্রেশহোল্ডের চেয়ে বেশি হয়, তাহলে তাদের মধ্যে একটি মুছে ফেলতে হবে। ওভারল্যাপ থ্রেশহোল্ড একটি শতাংশ, তাই এটি ছোটতম বাউন্ডিং বক্সের আকারের সাথে গুণিত হতে হবে যাতে নিশ্চিত করা যায় যে ওভারল্যাপটি পুরো চিত্রের প্রদত্ত শতাংশ নয়, বরং বাউন্ডিং বক্সের প্রদত্ত শতাংশ ছাড়িয়ে গেছে। `processPredictions` ফাংশনের বিষয়বস্তু মুছে ফেলার মাধ্যমে শুরু করুন।

1. খালি `processPredictions` ফাংশনে নিম্নলিখিত যোগ করুন:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    এই কোডটি এমন ভবিষ্যদ্বাণীগুলির জন্য একটি ভেক্টর ঘোষণা করে যা ওভারল্যাপ করে না। এটি সমস্ত ভবিষ্যদ্বাণীগুলির মধ্য দিয়ে লুপ করে, বাউন্ডিং বক্স থেকে একটি `Rect` তৈরি করে।

    এরপর এই কোডটি বাকি ভবিষ্যদ্বাণীগুলির মধ্য দিয়ে লুপ করে, বর্তমান ভবিষ্যদ্বাণীর পরেরটি থেকে শুরু করে। এটি ভবিষ্যদ্বাণীগুলিকে একাধিকবার তুলনা করা থেকে বিরত রাখে - একবার ১ এবং ২ তুলনা করা হলে, ২ কে ১ এর সাথে তুলনা করার প্রয়োজন নেই, শুধুমাত্র ৩, ৪ ইত্যাদির সাথে।

    প্রতিটি জোড়া ভবিষ্যদ্বাণীর জন্য ওভারল্যাপিং এলাকা গণনা করা হয়। এটি তারপর ছোটতম বাউন্ডিং বক্সের এলাকাটির সাথে তুলনা করা হয় - যদি ওভারল্যাপটি ছোটতম বাউন্ডিং বক্সের প্রদত্ত শতাংশ ছাড়িয়ে যায়, তাহলে ভবিষ্যদ্বাণীটি পাস না হওয়া হিসাবে চিহ্নিত করা হয়। সমস্ত ওভারল্যাপ তুলনা করার পরে, যদি ভবিষ্যদ্বাণীটি চেকগুলি পাস করে, এটি `passed_predictions` সংগ্রহে যোগ করা হয়।

    > 💁 এটি ওভারল্যাপগুলি সরানোর একটি খুব সাধারণ উপায়, শুধুমাত্র একটি ওভারল্যাপিং জোড়ায় প্রথমটি সরিয়ে ফেলা। প্রোডাকশন কোডের জন্য, আপনি এখানে আরও যুক্তি যোগ করতে চাইবেন, যেমন একাধিক বস্তুর মধ্যে ওভারল্যাপগুলি বিবেচনা করা, বা যদি একটি বাউন্ডিং বক্স অন্যটির মধ্যে থাকে।

1. এর পরে, পাস করা ভবিষ্যদ্বাণীগুলির বিবরণ সিরিয়াল মনিটরে পাঠানোর জন্য নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    এই কোডটি পাস করা ভবিষ্যদ্বাণীগুলির মধ্য দিয়ে লুপ করে এবং তাদের বিবরণ সিরিয়াল মনিটরে প্রিন্ট করে।

1. এর নিচে, গণনা করা আইটেমগুলির সংখ্যা সিরিয়াল মনিটরে প্রিন্ট করার জন্য কোড যোগ করুন:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    এটি তারপর একটি IoT সার্ভিসে পাঠানো যেতে পারে যাতে স্টক স্তর কম হলে সতর্ক করা যায়।

1. আপনার কোড আপলোড এবং চালান। শেলফে থাকা বস্তুগুলির দিকে ক্যামেরা নির্দেশ করুন এবং C বোতাম চাপুন। `overlap_threshold` মানটি সামঞ্জস্য করার চেষ্টা করুন যাতে ভবিষ্যদ্বাণীগুলি উপেক্ষা করা যায়।

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 আপনি এই কোডটি [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার স্টক কাউন্টার প্রোগ্রাম সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিক অনুবাদের চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। নথিটির মূল ভাষায় লেখা সংস্করণটিকেই প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ ব্যবহার করার পরামর্শ দেওয়া হচ্ছে। এই অনুবাদ ব্যবহারের ফলে সৃষ্ট কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যার জন্য আমরা দায়ী নই।