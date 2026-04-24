# আপনার IoT ডিভাইস থেকে আপনার অবজেক্ট ডিটেক্টর কল করুন - Wio Terminal

আপনার অবজেক্ট ডিটেক্টর প্রকাশিত হওয়ার পর, এটি আপনার IoT ডিভাইস থেকে ব্যবহার করা যেতে পারে।

## ইমেজ ক্লাসিফায়ার প্রকল্প কপি করুন

আপনার স্টক ডিটেক্টর প্রকল্পের বেশিরভাগ অংশই পূর্ববর্তী পাঠে তৈরি করা ইমেজ ক্লাসিফায়ারের মতো।

### কাজ - ইমেজ ক্লাসিফায়ার প্রকল্প কপি করুন

1. আপনার ArduCam-কে Wio Terminal-এর সাথে সংযুক্ত করুন, [ম্যানুফ্যাকচারিং প্রকল্পের পাঠ ২](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera)-এর ধাপগুলি অনুসরণ করে।

    আপনি ক্যামেরাটিকে একটি নির্দিষ্ট অবস্থানে স্থির করতে চাইতে পারেন, যেমন একটি বাক্স বা ক্যানের উপর তার ঝুলিয়ে রাখা, অথবা ডাবল-সাইডেড টেপ ব্যবহার করে ক্যামেরাটিকে একটি বাক্সে স্থির করা।

1. PlatformIO ব্যবহার করে একটি নতুন Wio Terminal প্রকল্প তৈরি করুন। এই প্রকল্পটির নাম দিন `stock-counter`।

1. [ম্যানুফ্যাকচারিং প্রকল্পের পাঠ ২](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device)-এর ধাপগুলি পুনরায় অনুসরণ করে ক্যামেরা থেকে ছবি তুলুন।

1. [ম্যানুফ্যাকচারিং প্রকল্পের পাঠ ২](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device)-এর ধাপগুলি পুনরায় অনুসরণ করে ইমেজ ক্লাসিফায়ার কল করুন। এই কোডের বেশিরভাগ অংশ অবজেক্ট ডিটেক্ট করতে পুনরায় ব্যবহার করা হবে।

## কোডটি ক্লাসিফায়ার থেকে ইমেজ ডিটেক্টরে পরিবর্তন করুন

আপনি যে কোডটি ইমেজ ক্লাসিফাই করতে ব্যবহার করেছেন, সেটি অবজেক্ট ডিটেক্ট করার কোডের সাথে খুবই মিল। প্রধান পার্থক্য হলো Custom Vision থেকে প্রাপ্ত URL এবং কলের ফলাফল।

### কাজ - কোডটি ক্লাসিফায়ার থেকে ইমেজ ডিটেক্টরে পরিবর্তন করুন

1. `main.cpp` ফাইলের শীর্ষে নিম্নলিখিত ইনক্লুড ডিরেক্টিভ যোগ করুন:

    ```cpp
    #include <vector>
    ```

1. `classifyImage` ফাংশনের নাম পরিবর্তন করে `detectStock` করুন, ফাংশনের নাম এবং `buttonPressed` ফাংশনে কল উভয় ক্ষেত্রেই।

1. `detectStock` ফাংশনের উপরে একটি থ্রেশহোল্ড ঘোষণা করুন, যা কম সম্ভাবনার ডিটেকশনগুলোকে ফিল্টার করবে:

    ```cpp
    const float threshold = 0.3f;
    ```

    ইমেজ ক্লাসিফায়ার শুধুমাত্র প্রতি ট্যাগে একটি ফলাফল ফেরত দেয়, কিন্তু অবজেক্ট ডিটেক্টর একাধিক ফলাফল ফেরত দেয়, তাই কম সম্ভাবনার ডিটেকশনগুলো ফিল্টার করা প্রয়োজন।

1. `detectStock` ফাংশনের উপরে একটি ফাংশন ঘোষণা করুন যা প্রেডিকশনগুলো প্রক্রিয়া করবে:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    এটি প্রেডিকশনগুলোর একটি তালিকা গ্রহণ করে এবং সেগুলো সিরিয়াল মনিটরে প্রিন্ট করে।

1. `detectStock` ফাংশনের মধ্যে, প্রেডিকশনগুলোর উপর লুপ করা `for` লুপের বিষয়বস্তু নিম্নলিখিত কোড দিয়ে প্রতিস্থাপন করুন:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    এটি প্রেডিকশনগুলোর উপর লুপ করে, সম্ভাবনাকে থ্রেশহোল্ডের সাথে তুলনা করে। সমস্ত প্রেডিকশন যেগুলোর সম্ভাবনা থ্রেশহোল্ডের চেয়ে বেশি, সেগুলো একটি `list`-এ যোগ করা হয় এবং `processPredictions` ফাংশনে পাঠানো হয়।

1. আপনার কোড আপলোড এবং চালান। ক্যামেরাটি শেলফে থাকা অবজেক্টগুলোর দিকে নির্দেশ করুন এবং C বোতাম চাপুন। আপনি সিরিয়াল মনিটরে আউটপুট দেখতে পাবেন:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 আপনার ছবির জন্য একটি উপযুক্ত মানে থ্রেশহোল্ড সামঞ্জস্য করতে হতে পারে।

    আপনি তোলা ছবিটি এবং এই মানগুলো **Predictions** ট্যাবে Custom Vision-এ দেখতে পারবেন।

    ![শেলফে ৪টি টমেটো পেস্টের ক্যান এবং ৪টি ডিটেকশনের সম্ভাবনা ৩৫.৮%, ৩৩.৫%, ২৫.৭% এবং ১৬.৬%](../../../../../translated_images/bn/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 আপনি এই কোডটি [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার স্টক কাউন্টার প্রোগ্রাম সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিক অনুবাদ প্রদানের চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা দায়বদ্ধ থাকব না।