<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-26T21:33:44+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "ur"
}
-->
# اپنے IoT ڈیوائس سے اسٹاک گنیں - Wio Terminal

پیشگوئیوں اور ان کے باؤنڈنگ باکسز کے امتزاج کو تصویر میں اسٹاک گننے کے لیے استعمال کیا جا سکتا ہے۔

## اسٹاک گننا

![ٹماٹر کے پیسٹ کے 4 ڈبے، ہر ڈبے کے گرد باؤنڈنگ باکسز کے ساتھ](../../../../../translated_images/ur/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

اوپر دکھائی گئی تصویر میں، باؤنڈنگ باکسز میں تھوڑا سا اوورلیپ ہے۔ اگر یہ اوورلیپ بہت زیادہ ہوتا، تو باؤنڈنگ باکسز ایک ہی چیز کی نشاندہی کر سکتے تھے۔ اشیاء کو درست طریقے سے گننے کے لیے، آپ کو ان باکسز کو نظرانداز کرنا ہوگا جن میں نمایاں اوورلیپ ہو۔

### کام - اوورلیپ کو نظرانداز کرتے ہوئے اسٹاک گنیں

1. اگر آپ کا `stock-counter` پروجیکٹ پہلے سے کھلا نہیں ہے تو اسے کھولیں۔

1. `processPredictions` فنکشن کے اوپر، درج ذیل کوڈ شامل کریں:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    یہ اس اوورلیپ کی فیصد کی وضاحت کرتا ہے جو باؤنڈنگ باکسز کو ایک ہی چیز سمجھنے سے پہلے اجازت دی جاتی ہے۔ 0.20 کا مطلب ہے 20% اوورلیپ۔

1. اس کے نیچے، اور `processPredictions` فنکشن کے اوپر، دو مستطیلوں کے درمیان اوورلیپ کا حساب لگانے کے لیے درج ذیل کوڈ شامل کریں:

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

    یہ کوڈ ایک `Point` اسٹرکچر کی وضاحت کرتا ہے جو تصویر پر پوائنٹس کو اسٹور کرتا ہے، اور ایک `Rect` اسٹرکچر جو اوپر بائیں اور نیچے دائیں کوآرڈینیٹ کا استعمال کرتے ہوئے ایک مستطیل کی وضاحت کرتا ہے۔ پھر یہ ایک `area` فنکشن کی وضاحت کرتا ہے جو اوپر بائیں اور نیچے دائیں کوآرڈینیٹ سے مستطیل کا رقبہ نکالتا ہے۔

    اس کے بعد یہ ایک `overlappingArea` فنکشن کی وضاحت کرتا ہے جو 2 مستطیلوں کے اوورلیپنگ رقبے کا حساب لگاتا ہے۔ اگر وہ اوورلیپ نہ کریں، تو یہ 0 واپس کرتا ہے۔

1. `overlappingArea` فنکشن کے نیچے، ایک فنکشن کا اعلان کریں جو باؤنڈنگ باکس کو `Rect` میں تبدیل کرے:

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

    یہ آبجیکٹ ڈیٹیکٹر سے ایک پیشگوئی لیتا ہے، باؤنڈنگ باکس نکالتا ہے اور باؤنڈنگ باکس کی قدروں کو استعمال کرتے ہوئے ایک مستطیل کی وضاحت کرتا ہے۔ دائیں طرف بائیں طرف سے چوڑائی شامل کر کے نکالی جاتی ہے۔ نیچے کی طرف اوپر سے اونچائی شامل کر کے نکالی جاتی ہے۔

1. پیشگوئیوں کو ایک دوسرے سے موازنہ کرنے کی ضرورت ہے، اور اگر 2 پیشگوئیوں میں اوورلیپ تھریشولڈ سے زیادہ ہو، تو ان میں سے ایک کو حذف کرنا ہوگا۔ اوورلیپ تھریشولڈ ایک فیصد ہے، اس لیے اسے سب سے چھوٹے باؤنڈنگ باکس کے سائز سے ضرب دینا ہوگا تاکہ یہ چیک کیا جا سکے کہ اوورلیپ باؤنڈنگ باکس کے دیے گئے فیصد سے زیادہ ہے، نہ کہ پوری تصویر کے دیے گئے فیصد سے۔ `processPredictions` فنکشن کے مواد کو حذف کر کے شروع کریں۔

1. خالی `processPredictions` فنکشن میں درج ذیل شامل کریں:

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

    یہ کوڈ ان پیشگوئیوں کو اسٹور کرنے کے لیے ایک ویکٹر کا اعلان کرتا ہے جو اوورلیپ نہیں کرتی ہیں۔ پھر یہ تمام پیشگوئیوں کے ذریعے لوپ کرتا ہے، باؤنڈنگ باکس سے ایک `Rect` بناتا ہے۔

    اس کے بعد یہ باقی پیشگوئیوں کے ذریعے لوپ کرتا ہے، موجودہ پیشگوئی کے بعد سے شروع کرتے ہوئے۔ یہ پیشگوئیوں کو ایک سے زیادہ بار موازنہ کرنے سے روکتا ہے - ایک بار جب 1 اور 2 کا موازنہ ہو جائے، تو 2 کا 1 کے ساتھ موازنہ کرنے کی ضرورت نہیں، صرف 3، 4، وغیرہ کے ساتھ۔

    ہر پیشگوئی کے جوڑے کے لیے اوورلیپنگ ایریا کا حساب لگایا جاتا ہے۔ پھر اس کا موازنہ سب سے چھوٹے باؤنڈنگ باکس کے رقبے سے کیا جاتا ہے - اگر اوورلیپ باؤنڈنگ باکس کے تھریشولڈ فیصد سے زیادہ ہو، تو پیشگوئی کو پاس نہ کرنے کے طور پر نشان زد کیا جاتا ہے۔ اگر تمام اوورلیپ کا موازنہ کرنے کے بعد، پیشگوئی چیک پاس کرتی ہے تو اسے `passed_predictions` کلیکشن میں شامل کر دیا جاتا ہے۔

    > 💁 یہ اوورلیپ کو ہٹانے کا ایک بہت ہی سادہ طریقہ ہے، صرف اوورلیپنگ جوڑے میں سے پہلے کو ہٹانا۔ پروڈکشن کوڈ کے لیے، آپ کو یہاں مزید منطق شامل کرنے کی ضرورت ہوگی، جیسے کہ متعدد اشیاء کے درمیان اوورلیپ پر غور کرنا، یا اگر ایک باؤنڈنگ باکس دوسرے کے اندر ہو۔

1. اس کے بعد، پاس شدہ پیشگوئیوں کی تفصیلات سیریل مانیٹر پر بھیجنے کے لیے درج ذیل کوڈ شامل کریں:

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

    یہ کوڈ پاس شدہ پیشگوئیوں کے ذریعے لوپ کرتا ہے اور ان کی تفصیلات سیریل مانیٹر پر پرنٹ کرتا ہے۔

1. اس کے نیچے، سیریل مانیٹر پر گنی گئی اشیاء کی تعداد پرنٹ کرنے کے لیے کوڈ شامل کریں:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    یہ پھر IoT سروس کو بھیجا جا سکتا ہے تاکہ اگر اسٹاک کی سطح کم ہو تو الرٹ کیا جا سکے۔

1. اپنا کوڈ اپلوڈ کریں اور چلائیں۔ کیمرہ کو شیلف پر موجود اشیاء کی طرف کریں اور C بٹن دبائیں۔ `overlap_threshold` ویلیو کو ایڈجسٹ کرنے کی کوشش کریں تاکہ پیشگوئیوں کو نظرانداز ہوتے ہوئے دیکھ سکیں۔

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

> 💁 آپ اس کوڈ کو [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا اسٹاک کاؤنٹر پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔