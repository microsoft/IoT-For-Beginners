<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-26T21:36:13+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "ur"
}
-->
# اپنے IoT ڈیوائس سے آبجیکٹ ڈیٹیکٹر کو کال کریں - Wio Terminal

جب آپ کا آبجیکٹ ڈیٹیکٹر پبلش ہو جائے، تو اسے آپ کے IoT ڈیوائس سے استعمال کیا جا سکتا ہے۔

## امیج کلاسیفائر پروجیکٹ کو کاپی کریں

آپ کے اسٹاک ڈیٹیکٹر کا زیادہ تر حصہ وہی ہے جو آپ نے پچھلے سبق میں امیج کلاسیفائر کے لیے بنایا تھا۔

### کام - امیج کلاسیفائر پروجیکٹ کو کاپی کریں

1. اپنے ArduCam کو Wio Terminal سے کنیکٹ کریں، [مینوفیکچرنگ پروجیکٹ کے سبق نمبر 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera) کے مراحل کو فالو کرتے ہوئے۔

    آپ کیمرے کو ایک جگہ پر فکس کرنے کا سوچ سکتے ہیں، جیسے کہ کیبل کو کسی باکس یا کین کے اوپر لٹکا کر، یا ڈبل سائیڈ ٹیپ کے ذریعے کیمرے کو باکس پر فکس کر کے۔

1. PlatformIO کا استعمال کرتے ہوئے ایک نیا Wio Terminal پروجیکٹ بنائیں۔ اس پروجیکٹ کا نام `stock-counter` رکھیں۔

1. [مینوفیکچرنگ پروجیکٹ کے سبق نمبر 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) کے مراحل کو دہرائیں تاکہ کیمرے سے تصاویر حاصل کی جا سکیں۔

1. [مینوفیکچرنگ پروجیکٹ کے سبق نمبر 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) کے مراحل کو دہرائیں تاکہ امیج کلاسیفائر کو کال کیا جا سکے۔ اس کوڈ کا زیادہ تر حصہ آبجیکٹ ڈیٹیکشن کے لیے دوبارہ استعمال ہوگا۔

## کوڈ کو کلاسیفائر سے امیج ڈیٹیکٹر میں تبدیل کریں

امیجز کو کلاسیفائی کرنے کے لیے استعمال ہونے والا کوڈ آبجیکٹس کو ڈیٹیکٹ کرنے کے کوڈ سے بہت ملتا جلتا ہے۔ بنیادی فرق وہ URL ہے جو آپ نے Custom Vision سے حاصل کیا، اور کال کے نتائج ہیں۔

### کام - کوڈ کو کلاسیفائر سے امیج ڈیٹیکٹر میں تبدیل کریں

1. `main.cpp` فائل کے اوپر درج ذیل include directive شامل کریں:

    ```cpp
    #include <vector>
    ```

1. `classifyImage` فنکشن کا نام تبدیل کر کے `detectStock` رکھیں، فنکشن کے نام اور `buttonPressed` فنکشن میں کال دونوں جگہ۔

1. `detectStock` فنکشن کے اوپر ایک تھریش ہولڈ ڈکلیئر کریں تاکہ کم پروبیبلیٹی والے ڈیٹیکشنز کو فلٹر کیا جا سکے:

    ```cpp
    const float threshold = 0.3f;
    ```

    امیج کلاسیفائر کے برعکس جو ہر ٹیگ کے لیے صرف ایک نتیجہ دیتا ہے، آبجیکٹ ڈیٹیکٹر متعدد نتائج دیتا ہے، لہذا کم پروبیبلیٹی والے نتائج کو فلٹر کرنا ضروری ہے۔

1. `detectStock` فنکشن کے اوپر ایک فنکشن ڈکلیئر کریں جو پیشگوئیوں کو پراسیس کرے:

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

    یہ پیشگوئیوں کی فہرست لیتا ہے اور انہیں سیریل مانیٹر پر پرنٹ کرتا ہے۔

1. `detectStock` فنکشن میں، پیشگوئیوں کے لیے لوپ کے مواد کو درج ذیل سے تبدیل کریں:

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

    یہ پیشگوئیوں کے ذریعے لوپ کرتا ہے، پروبیبلیٹی کو تھریش ہولڈ سے موازنہ کرتا ہے۔ تمام پیشگوئیاں جن کی پروبیبلیٹی تھریش ہولڈ سے زیادہ ہوتی ہے، ایک `list` میں شامل کی جاتی ہیں اور `processPredictions` فنکشن کو پاس کی جاتی ہیں۔

1. اپنا کوڈ اپلوڈ کریں اور چلائیں۔ کیمرے کو شیلف پر موجود اشیاء کی طرف پوائنٹ کریں اور C بٹن دبائیں۔ آپ سیریل مانیٹر میں آؤٹ پٹ دیکھ سکیں گے:

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

    > 💁 آپ کو اپنی تصاویر کے لیے مناسب تھریش ہولڈ ایڈجسٹ کرنے کی ضرورت ہو سکتی ہے۔

    آپ وہ تصویر دیکھ سکیں گے جو لی گئی تھی، اور یہ ویلیوز **Predictions** ٹیب میں Custom Vision میں نظر آئیں گی۔

    ![شیلف پر رکھے ٹماٹر پیسٹ کے 4 کینز کے ساتھ 4 ڈیٹیکشنز کی پیشگوئیاں: 35.8%, 33.5%, 25.7% اور 16.6%](../../../../../translated_images/ur/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 آپ یہ کوڈ [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا اسٹاک کاؤنٹر پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔