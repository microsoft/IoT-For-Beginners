<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-28T17:39:29+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "my"
}
-->
# သင့် IoT စက်ပစ္စည်းမှ Object Detector ကို ခေါ်သုံးခြင်း - အတု IoT Hardware နှင့် Raspberry Pi

သင့် object detector ကို ထုတ်ဝေပြီးပါက၊ သင့် IoT စက်ပစ္စည်းမှ အသုံးပြုနိုင်ပါသည်။

## Image Classifier Project ကို မိတ္တူကူးခြင်း

သင့် stock detector ၏ အများစုသည် ယခင်သင်ခန်းစာတွင် ဖန်တီးခဲ့သော image classifier နှင့် တူညီသည်။

### လုပ်ငန်းစဉ် - Image Classifier Project ကို မိတ္တူကူးခြင်း

1. `stock-counter` ဟုခေါ်သော ဖိုလ်ဒါတစ်ခုကို သင့်ကွန်ပျူတာ (သို့) Raspberry Pi တွင် ဖန်တီးပါ။ သင့်အနေဖြင့် အတု IoT စက်ပစ္စည်းကို အသုံးပြုနေပါက virtual environment ကို ပြင်ဆင်ထားရန် သေချာပါစေ။

1. ကင်မရာ hardware ကို ပြင်ဆင်ပါ။

   * Raspberry Pi ကို အသုံးပြုနေပါက PiCamera ကို တပ်ဆင်ရန် လိုအပ်ပါမည်။ ကင်မရာကို တစ်နေရာတည်းတွင် တပ်ဆင်ထားလိုပါက၊ ဥပမာအားဖြင့် ကြိုးကို သေတ္တာ (သို့) သံဗူးပေါ်တွင် ချိတ်ထားခြင်း၊ သို့မဟုတ် ကင်မရာကို သေတ္တာပေါ်တွင် double-sided tape ဖြင့် တပ်ဆင်ထားနိုင်ပါသည်။
   * အတု IoT စက်ပစ္စည်းကို အသုံးပြုနေပါက CounterFit နှင့် CounterFit PyCamera shim ကို ထည့်သွင်းရန် လိုအပ်ပါမည်။ သင့်အနေဖြင့် ရုပ်ပုံများကို အသုံးပြုမည်ဆိုပါက၊ သင့် object detector မမြင်ဖူးသေးသော ရုပ်ပုံများကို ဖမ်းယူထားပါ။ သင့် webcam ကို အသုံးပြုမည်ဆိုပါက၊ သင့် stock ကို မြင်နိုင်သောနေရာတွင် တပ်ဆင်ထားရန် သေချာပါစေ။

1. ကင်မရာမှ ရုပ်ပုံများကို ဖမ်းယူရန် [manufacturing project ၏ lesson 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) တွင် ဖော်ပြထားသော လုပ်ငန်းစဉ်များကို ထပ်မံလုပ်ဆောင်ပါ။

1. Image classifier ကို ခေါ်သုံးရန် [manufacturing project ၏ lesson 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) တွင် ဖော်ပြထားသော လုပ်ငန်းစဉ်များကို ထပ်မံလုပ်ဆောင်ပါ။ ဤ code ၏ အများစုကို object detection အတွက် ပြန်လည်အသုံးပြုမည်ဖြစ်သည်။

## Classifier Code ကို Image Detector Code သို့ ပြောင်းလဲခြင်း

Image classification အတွက် အသုံးပြုခဲ့သော code သည် object detection အတွက် အသုံးပြုမည့် code နှင့် အလွန်ဆင်တူသည်။ အဓိကကွာခြားချက်မှာ Custom Vision SDK တွင် ခေါ်သုံးမည့် method နှင့် call ၏ ရလဒ်များဖြစ်သည်။

### လုပ်ငန်းစဉ် - Classifier Code ကို Image Detector Code သို့ ပြောင်းလဲခြင်း

1. ရုပ်ပုံကို classify လုပ်ပြီး prediction များကို process လုပ်သည့် code သုံးကြောင်းကို ဖျက်ပါ။

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    ဤသုံးကြောင်းကို ဖျက်ပါ။

1. ရုပ်ပုံအတွင်း object များကို detect လုပ်ရန် အောက်ပါ code ကို ထည့်ပါ။

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    ဤ code သည် predictor တွင် `detect_image` method ကို ခေါ်သုံးပြီး object detector ကို run လုပ်ပါသည်။ ထို့နောက် threshold ထက် မြင့်မားသော probability ရှိသည့် prediction များကို စုဆောင်းပြီး console တွင် print လုပ်ပါသည်။

    Image classifier သည် tag တစ်ခုစီအတွက် ရလဒ်တစ်ခုသာ ပြန်ပေးသော်လည်း၊ object detector သည် ရလဒ်များစွာကို ပြန်ပေးနိုင်ပါသည်။ ထို့ကြောင့် probability နိမ့်သော prediction များကို ဖယ်ရှားရန် လိုအပ်ပါသည်။

1. ဤ code ကို run လုပ်ပါ၊ ရုပ်ပုံကို ဖမ်းယူပြီး object detector သို့ ပို့ပါ၊ ပြီးလျှင် detect လုပ်ထားသော object များကို print လုပ်ပါမည်။ အတု IoT စက်ပစ္စည်းကို အသုံးပြုနေပါက CounterFit တွင် သင့် image ကို သင့်တော်စွာ ပြင်ဆင်ထားရန် သို့မဟုတ် webcam ကို ရွေးထားရန် သေချာပါစေ။ Raspberry Pi ကို အသုံးပြုနေပါက သင့်ကင်မရာကို စင်္ကြံပေါ်ရှိ object များကို ညွှန်းထားရန် သေချာပါစေ။

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 `threshold` ကို သင့်ရုပ်ပုံများအတွက် သင့်တော်သောတန်ဖိုးသို့ ပြင်ဆင်ရန် လိုအပ်နိုင်ပါသည်။

    ဖမ်းယူထားသော ရုပ်ပုံနှင့် Prediction tab တွင် ရလဒ်များကို Custom Vision တွင် ကြည့်ရှုနိုင်ပါမည်။

    ![စင်္ကြံပေါ်ရှိ ခရမ်းချဉ်ပေါင်း ၄ ကန်နှင့် ၃၅.၈%, ၃၃.၅%, ၂၅.၇% နှင့် ၁၆.၆% ရှိသော prediction များ](../../../../../translated_images/my/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 ဤ code ကို [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) သို့မဟုတ် [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device) ဖိုလ်ဒါတွင် ရှာနိုင်ပါသည်။

😀 သင့် stock counter program အောင်မြင်ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားယူမှုမှားများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။