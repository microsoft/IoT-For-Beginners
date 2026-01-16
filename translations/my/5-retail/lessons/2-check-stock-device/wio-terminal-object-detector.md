<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-28T17:36:51+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "my"
}
-->
# သင့် IoT စက်ပစ္စည်းမှ Object Detector ကို ခေါ်သုံးခြင်း - Wio Terminal

Object detector ကို ထုတ်ဝေပြီးပါက သင့် IoT စက်ပစ္စည်းမှ အသုံးပြုနိုင်ပါသည်။

## Image Classifier Project ကို မိတ္တူကူးခြင်း

သင့် stock detector ၏ အများစုသည် ယခင်သင်ခန်းစာတွင် ဖန်တီးခဲ့သော image classifier နှင့် တူညီပါသည်။

### လုပ်ငန်းစဉ် - Image Classifier Project ကို မိတ္တူကူးခြင်း

1. သင့် Wio Terminal နှင့် ArduCam ကို [ထုတ်လုပ်မှုစီမံကိန်း၏ သင်ခန်းစာ ၂](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera) တွင် ဖော်ပြထားသည့် အဆင့်များအတိုင်း ချိတ်ဆက်ပါ။

    ကင်မရာကို တစ်နေရာတည်းတွင် တည်ငြိမ်စေလိုပါက၊ ဥပမာ၊ ကြောင့်ကြိုးကို သေတ္တာ သို့မဟုတ် သံဗူးပေါ်တွင် ချိတ်ထားခြင်း၊ သို့မဟုတ် ကင်မရာကို သေတ္တာပေါ်တွင် နှစ်ဖက်ကပ်ကပ်တိပ်ဖြင့် ကပ်ထားခြင်းတို့ကို စဉ်းစားနိုင်ပါသည်။

1. PlatformIO ကို အသုံးပြု၍ Wio Terminal Project အသစ်တစ်ခု ဖန်တီးပါ။ Project ကို `stock-counter` ဟု အမည်ပေးပါ။

1. [ထုတ်လုပ်မှုစီမံကိန်း၏ သင်ခန်းစာ ၂](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) တွင် ဖော်ပြထားသည့် အဆင့်များကို ထပ်မံလုပ်ဆောင်ပြီး ကင်မရာမှ ပုံရိပ်များကို ဖမ်းယူပါ။

1. [ထုတ်လုပ်မှုစီမံကိန်း၏ သင်ခန်းစာ ၂](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) တွင် ဖော်ပြထားသည့် အဆင့်များကို ထပ်မံလုပ်ဆောင်ပြီး image classifier ကို ခေါ်သုံးပါ။ ဤ code ၏ အများစုကို object detection အတွက် ပြန်လည်အသုံးပြုမည်ဖြစ်သည်။

## Code ကို Classifier မှ Image Detector သို့ ပြောင်းလဲခြင်း

Image classification အတွက် အသုံးပြုခဲ့သော code သည် object detection အတွက် အသုံးပြုရမည့် code နှင့် အလွန်ဆင်တူပါသည်။ အဓိကကွာခြားချက်မှာ Custom Vision မှ ရရှိသော URL နှင့် call ၏ ရလဒ်များဖြစ်သည်။

### လုပ်ငန်းစဉ် - Code ကို Classifier မှ Image Detector သို့ ပြောင်းလဲခြင်း

1. `main.cpp` ဖိုင်၏ အပေါ်ပိုင်းတွင် အောက်ပါ include directive ကို ထည့်ပါ။

    ```cpp
    #include <vector>
    ```

1. `classifyImage` function ကို `detectStock` ဟု ပြောင်းလဲပါ၊ function အမည်နှင့် `buttonPressed` function အတွင်းရှိ call ကိုလည်း ပြောင်းပါ။

1. `detectStock` function အထက်တွင် အောက်ပါ threshold ကို ကြေညာပါ၊ ဤ threshold သည် အနိမ့်ဆုံး probability ရှိသော detection များကို ဖယ်ထုတ်ရန် အသုံးပြုမည်ဖြစ်သည်။

    ```cpp
    const float threshold = 0.3f;
    ```

    Image classifier သည် tag တစ်ခုစီအတွက် ရလဒ်တစ်ခုသာ ပြန်ပေးသော်လည်း၊ object detector သည် ရလဒ်များစွာ ပြန်ပေးမည်ဖြစ်သည်။ ထို့ကြောင့် အနိမ့်ဆုံး probability ရှိသော detection များကို ဖယ်ထုတ်ရန် လိုအပ်ပါသည်။

1. `detectStock` function အထက်တွင် prediction များကို process ပြုလုပ်ရန် function တစ်ခု ကြေညာပါ။

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

    ဤ function သည် prediction များ၏ စာရင်းကို ယူပြီး serial monitor တွင် ပြသပါမည်။

1. `detectStock` function အတွင်းရှိ `for` loop ၏ အကြောင်းအရာကို အောက်ပါ code ဖြင့် အစားထိုးပါ။

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

    ဤ loop သည် prediction များကို threshold နှင့် နှိုင်းယှဉ်ပြီး၊ threshold ထက် မြင့်မားသော probability ရှိသော prediction များကို `list` ထဲသို့ ထည့်ပြီး `processPredictions` function သို့ ပေးပို့ပါမည်။

1. သင့် code ကို upload ပြုလုပ်ပြီး run လုပ်ပါ။ ကင်မရာကို စင်ထဲရှိ ပစ္စည်းများကို ညွှန်းပြီး C ခလုတ်ကို နှိပ်ပါ။ Serial monitor တွင် output ကို ကြည့်ရှုနိုင်ပါမည်။

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

    > 💁 သင့်ပုံရိပ်များအတွက် သင့်တော်သော `threshold` တန်ဖိုးကို ချိန်ညှိရန် လိုအပ်နိုင်ပါသည်။

    ဖမ်းယူထားသော ပုံရိပ်ကို ကြည့်ရှုနိုင်ပြီး၊ ဤတန်ဖိုးများကို Custom Vision ၏ **Predictions** tab တွင် တွေ့နိုင်ပါမည်။

    ![စင်ပေါ်ရှိ ခရမ်းချဉ်သီးပူစီ ၄ ကန်နှင့် ၄ ခု၏ detection တန်ဖိုးများ - 35.8%, 33.5%, 25.7% နှင့် 16.6%](../../../../../translated_images/my/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 ဤ code ကို [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) ဖိုလ်ဒါတွင် ရှာနိုင်ပါသည်။

😀 သင့် stock counter program အောင်မြင်ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားယူမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။