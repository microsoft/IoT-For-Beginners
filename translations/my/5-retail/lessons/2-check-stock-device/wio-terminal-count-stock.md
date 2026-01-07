<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-28T17:38:33+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "my"
}
-->
# Wio Terminal - သင့် IoT စက်ကနေ စတော့အရေအတွက်တွက်ခြင်း

အကြံပြုချက်များနှင့် bounding boxes တွေကိုပေါင်းစပ်ပြီး ပုံထဲမှာရှိတဲ့ စတော့အရေအတွက်ကိုတွက်နိုင်ပါတယ်။

## စတော့အရေအတွက်တွက်ခြင်း

![တစ်ခုချင်းစီကို bounding boxes ဖြင့်ပတ်ထားသော ခရမ်းချဉ်သီးပေါင်း ၄ ကန်](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.my.jpg)

အထက်ပါပုံတွင် bounding boxes တွေမှာ အနည်းငယ်တစ်ခုနှင့်တစ်ခုကျော်လွှားမှုရှိပါတယ်။ ကျော်လွှားမှုက ပိုများလာခဲ့ရင် bounding boxes တွေဟာ တစ်ခုတည်းသောအရာကိုပြသနိုင်ပါတယ်။ အရာဝတ္ထုများကိုမှန်ကန်စွာတွက်ရန် ကျော်လွှားမှုများသော boxes တွေကို မထည့်သွင်းစဉ်းစားရပါမည်။

### လုပ်ငန်း - ကျော်လွှားမှုကို မထည့်သွင်းစဉ်းစားဘဲ စတော့အရေအတွက်တွက်ခြင်း

1. သင့် `stock-counter` project ကို မဖွင့်ထားသေးရင် ဖွင့်ပါ။

1. `processPredictions` function အပေါ်တွင် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    ဒီ code က bounding boxes တွေကို တစ်ခုတည်းသောအရာအဖြစ်စဉ်းစားမည်မဟုတ်သော ကျော်လွှားမှု၏ ရာခိုင်နှုန်းကို သတ်မှတ်ပေးပါတယ်။ 0.20 က 20% ကျော်လွှားမှုကို သတ်မှတ်ပေးပါတယ်။

1. ဒီ code အောက်မှာ၊ `processPredictions` function အပေါ်မှာ အောက်ပါ code ကို ထည့်ပါ။ ဒါက rectangle နှစ်ခုအကြား ကျော်လွှားမှုကိုတွက်ရန်ဖြစ်ပါတယ်။

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

    ဒီ code က `Point` struct ကို သတ်မှတ်ပြီး ပုံထဲမှာရှိတဲ့ point တွေကို သိမ်းဆည်းပေးပါတယ်။ `Rect` struct က rectangle ကို အပေါ်ဘက်-ဘယ်ဘက်နှင့် အောက်ဘက်-ညာဘက် coordinates တွေကို သတ်မှတ်ပေးပါတယ်။ ထို့နောက် `area` function က rectangle ရဲ့ အကျယ်အဝန်းကိုတွက်ပေးပါတယ်။

    နောက်ဆုံးမှာ `overlappingArea` function က rectangle နှစ်ခုရဲ့ ကျော်လွှားမှုအကျယ်အဝန်းကိုတွက်ပေးပါတယ်။ ကျော်လွှားမှုမရှိရင် 0 ကိုပြန်ပေးပါသည်။

1. `overlappingArea` function အောက်မှာ bounding box ကို `Rect` အဖြစ်ပြောင်းရန် function ကို ကြေညာပါ။

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

    ဒီ function က object detector ရဲ့ prediction ကိုယူပြီး bounding box ကိုထုတ်ယူကာ rectangle ကိုသတ်မှတ်ပေးပါတယ်။ ညာဘက်ဘက်ကို ဘယ်ဘက်နှင့် width ကိုပေါင်းပြီးတွက်သည်။ အောက်ဘက်ကို အပေါ်ဘက်နှင့် height ကိုပေါင်းပြီးတွက်သည်။

1. predictions တွေကို တစ်ခုနှင့်တစ်ခုနှိုင်းယှဉ်ရန်လိုအပ်ပြီး၊ prediction နှစ်ခုမှာ threshold ကျော်လွှားမှုရှိရင် တစ်ခုကို ဖျက်ရန်လိုအပ်ပါသည်။ overlap threshold က ရာခိုင်နှုန်းဖြစ်ပြီး၊ အငယ်ဆုံး bounding box ရဲ့အရွယ်အစားကို မျိုးဆက်ပြီး ကျော်လွှားမှုက bounding box ရဲ့ ရာခိုင်နှုန်းကို ကျော်လွန်ကြောင်းစစ်ဆေးရန်လိုအပ်ပါသည်။ `processPredictions` function ရဲ့ အကြောင်းအရာကို ဖျက်ပါ။

1. `processPredictions` function ရဲ့ အလွတ်နေရာတွင် အောက်ပါ code ကို ထည့်ပါ။

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

    ဒီ code က overlap မရှိသော predictions တွေကို သိမ်းဆည်းရန် vector ကို ကြေညာသည်။ ထို့နောက် prediction အားလုံးကို loop ဖြင့် iterate လုပ်ကာ bounding box ကို `Rect` အဖြစ်ပြောင်းသည်။

    ထို့နောက် code က ကျန်ရှိသော predictions တွေကို loop ဖြင့် iterate လုပ်သည်။ ယခုပြုလုပ်နေသော prediction အပြီးမှစတင်သည်။ ဒါက prediction တွေကို တစ်ခါထက်မကြိမ်နှိုင်းယှဉ်ရန်ကာကွယ်ပေးသည် - 1 နှင့် 2 ကိုနှိုင်းယှဉ်ပြီးရင် 2 ကို 1 နှင့်ပြန်နှိုင်းရန်မလိုတော့ပါ၊ 3, 4 စသည်ဖြင့်သာနှိုင်းရန်လိုအပ်ပါသည်။

    prediction နှစ်ခုအကြား ကျော်လွှားမှုအကျယ်အဝန်းကိုတွက်သည်။ ထို့နောက် အငယ်ဆုံး bounding box ရဲ့အကျယ်အဝန်းနှင့်နှိုင်းယှဉ်သည် - ကျော်လွှားမှုက bounding box ရဲ့ threshold ရာခိုင်နှုန်းကို ကျော်လွန်ပါက prediction ကို မဖြတ်မတောက်အဖြစ်သတ်မှတ်သည်။ ကျော်လွှားမှုအားလုံးကိုစစ်ဆေးပြီးနောက် prediction က စစ်ဆေးမှုကိုအောင်မြင်ပါက `passed_predictions` collection ထဲသို့ထည့်သည်။

    > 💁 ဒီဟာက overlap တွေကိုဖယ်ရှားရန် အလွန်ရိုးရှင်းသောနည်းလမ်းဖြစ်ပြီး overlap ဖြစ်နေသော prediction pair တွေထဲက ပထမတစ်ခုကိုဖယ်ရှားပေးသည်။ production code အတွက်တော့ overlap ဖြစ်နေသော objects များစွာကိုစဉ်းစားခြင်း၊ သို့မဟုတ် bounding box တစ်ခုက အခြား bounding box ကိုပါဝင်ထားခြင်းစသည်တို့ကို ထည့်သွင်းစဉ်းစားရန် logic ပိုမိုထည့်သွင်းရန်လိုအပ်ပါသည်။

1. ထို့နောက် passed predictions ရဲ့ အသေးစိတ်ကို serial monitor သို့ပို့ရန် အောက်ပါ code ကိုထည့်ပါ။

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

    ဒီ code က passed predictions တွေကို loop ဖြင့် iterate လုပ်ကာ serial monitor တွင် အသေးစိတ်ကို print လုပ်သည်။

1. ဒီ code အောက်မှာ serial monitor တွင် တွက်ထားသော items အရေအတွက်ကို print လုပ်ရန် code ကိုထည့်ပါ။

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    ဒီအချက်အလက်ကို IoT service သို့ပို့ကာ စတော့အရေအတွက်နည်းပါက အချက်ပေးနိုင်ပါသည်။

1. သင့် code ကို upload လုပ်ပြီး run လုပ်ပါ။ ကင်မရာကို စင်ပေါ်ရှိ objects များကိုညွှန်ပြီး C ခလုတ်ကိုနှိပ်ပါ။ `overlap_threshold` တန်ဖိုးကိုပြောင်းပြီး prediction များကို မထည့်သွင်းစဉ်းစားခြင်းကိုကြည့်ပါ။

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

> 💁 ဒီ code ကို [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) folder မှာတွေ့နိုင်ပါတယ်။

😀 သင့် stock counter program အောင်မြင်ခဲ့ပါပြီ!

---

**ဝက်ဘ်ဆိုက်မှတ်ချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှန်ကန်မှုအတွက် ကြိုးစားနေပါသော်လည်း၊ အလိုအလျောက်ဘာသာပြန်ဆိုမှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်ပါသည်။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူလဘာသာစကားဖြင့် အာဏာတည်သောရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပြန်ဆိုမှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော နားလည်မှုမှားမှုများ သို့မဟုတ် အဓိပ္ပါယ်မှားမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။