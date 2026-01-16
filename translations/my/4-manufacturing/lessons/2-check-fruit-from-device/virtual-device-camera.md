<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-28T16:07:27+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "my"
}
-->
# ပုံတစ်ပုံကိုဖမ်းယူခြင်း - အိမ်တွင်း IoT စက်ပစ္စည်း

ဒီသင်ခန်းစာအပိုင်းမှာ သင့်ရဲ့ အိမ်တွင်း IoT စက်ပစ္စည်းမှာ ကင်မရာအာရုံခံကိရိယာတစ်ခု ထည့်သွင်းပြီး ပုံများကို ဖတ်ရှုမည်ဖြစ်သည်။

## စက်ပစ္စည်း

အိမ်တွင်း IoT စက်ပစ္စည်းသည် ဖိုင်များမှပုံများ သို့မဟုတ် သင့်ရဲ့ webcam မှပုံများကို ပေးပို့သော ကင်မရာကို အတုအယောင်အသုံးပြုမည်ဖြစ်သည်။

### CounterFit တွင် ကင်မရာထည့်သွင်းခြင်း

အတုအယောင်ကင်မရာကို အသုံးပြုရန် CounterFit app တွင် ထည့်သွင်းရန်လိုအပ်သည်။

#### လုပ်ဆောင်ရန် - CounterFit တွင် ကင်မရာထည့်သွင်းခြင်း

CounterFit app တွင် ကင်မရာထည့်သွင်းပါ။

1. သင့်ကွန်ပျူတာတွင် `fruit-quality-detector` ဟုခေါ်သော ဖိုလ်ဒါတစ်ခုတွင် `app.py` ဟုခေါ်သော ဖိုင်တစ်ခုနှင့် Python virtual environment တစ်ခုပါရှိသော Python app အသစ်တစ်ခု ဖန်တီးပြီး CounterFit pip packages ကို ထည့်သွင်းပါ။

    > ⚠️ [သင်ခန်းစာ ၁ တွင် CounterFit Python project ဖန်တီးခြင်းနှင့် အဆင်ပြေစွာတပ်ဆင်ခြင်းအတွက် လမ်းညွှန်ချက်များကို လိုအပ်ပါက ပြန်လည်ကြည့်ရှုနိုင်သည်](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md)။

1. Camera sensors နှင့် ဆက်သွယ်နိုင်ရန် CounterFit shim ကို ထည့်သွင်းရန်အတွက် [Picamera Pip package](https://pypi.org/project/picamera/) အချို့ကို အတုအယောင်ပြုလုပ်သော Pip package ထပ်တစ်ခုကို ထည့်သွင်းပါ။ Virtual environment ကို active လုပ်ထားသော terminal မှာ ထည့်သွင်းရမည်ဖြစ်သည်။

    ```sh
    pip install counterfit-shims-picamera
    ```

1. CounterFit web app ကို run လုပ်ထားပါ။

1. ကင်မရာတစ်ခု ဖန်တီးပါ:

    1. *Sensors* pane ရဲ့ *Create sensor* box မှာ *Sensor type* box ကို drop down လုပ်ပြီး *Camera* ကို ရွေးချယ်ပါ။

    1. *Name* ကို `Picamera` ဟု သတ်မှတ်ပါ။

    1. **Add** ခလုတ်ကို ရွေးချယ်ပြီး ကင်မရာကို ဖန်တီးပါ။

    ![ကင်မရာ settings](../../../../../translated_images/my/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    ကင်မရာကို ဖန်တီးပြီး sensors list မှာ ပေါ်လာမည်။

    ![ဖန်တီးပြီးသော ကင်မရာ](../../../../../translated_images/my/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## ကင်မရာကို အစီအစဉ်ရေးခြင်း

အိမ်တွင်း IoT စက်ပစ္စည်းသည် အတုအယောင်ကင်မရာကို အသုံးပြုရန် အစီအစဉ်ရေးနိုင်ပြီဖြစ်သည်။

### လုပ်ဆောင်ရန် - ကင်မရာကို အစီအစဉ်ရေးခြင်း

စက်ပစ္စည်းကို အစီအစဉ်ရေးပါ။

1. `fruit-quality-detector` app ကို VS Code တွင် ဖွင့်ထားပါ။

1. `app.py` ဖိုင်ကို ဖွင့်ပါ။

1. CounterFit နှင့် app ကို ချိတ်ဆက်ရန် `app.py` ရဲ့ အပေါ်ပိုင်းတွင် အောက်ပါ code ကို ထည့်သွင်းပါ:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. `app.py` ဖိုင်တွင် အောက်ပါ code ကို ထည့်သွင်းပါ:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    ဒီ code ကလိုအပ်သော library များကို import လုပ်ပြီး counterfit_shims_picamera library မှ `PiCamera` class ကိုပါ ထည့်သွင်းသည်။

1. ကင်မရာကို initialize လုပ်ရန် အောက်ပါ code ကို ထည့်သွင်းပါ:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    ဒီ code က PiCamera object တစ်ခု ဖန်တီးပြီး resolution ကို 640x480 သတ်မှတ်သည်။ Resolution ပိုမြင့်သောပုံများကို support လုပ်နိုင်သော်လည်း image classifier သည် ပိုသေးသောပုံများ (227x227) တွင်သာ အလုပ်လုပ်သဖြင့် ပိုကြီးသောပုံများကို ဖမ်းယူရန် မလိုအပ်ပါ။

    `camera.rotation = 0` ဆိုသော line သည် ပုံ၏ rotation ကို degree ဖြင့် သတ်မှတ်သည်။ Webcam သို့မဟုတ် ဖိုင်မှ ပုံကို လိုအပ်သလို rotate လုပ်ရန် ဒီ value ကို ပြောင်းလဲနိုင်သည်။ ဥပမာအားဖြင့် landscape mode မှ webcam ပေါ်ရှိ ငှက်ပုံကို portrait mode သို့ ပြောင်းလဲလိုပါက `camera.rotation = 90` ဟု သတ်မှတ်ပါ။

1. ပုံကို binary data အဖြစ် ဖမ်းယူရန် အောက်ပါ code ကို ထည့်သွင်းပါ:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    ဒီ code က binary data ကို သိမ်းဆည်းရန် `BytesIO` object တစ်ခု ဖန်တီးသည်။ ကင်မရာမှ JPEG ဖိုင်အဖြစ် ဖတ်ယူပြီး ဒီ object တွင် သိမ်းဆည်းသည်။ ဒီ object တွင် data ရေးသားနေသောနေရာကို သိရှိရန် position indicator ရှိပြီး `image.seek(0)` line သည် position ကို data ရှိသောအစပိုင်းသို့ ပြန်လည်ရွှေ့သည်။

1. ပုံကို ဖိုင်အဖြစ် သိမ်းဆည်းရန် အောက်ပါ code ကို ထည့်သွင်းပါ:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    ဒီ code က `image.jpg` ဟုခေါ်သော ဖိုင်ကို ဖွင့်ပြီး `BytesIO` object မှ data အားလုံးကို ဖတ်ယူကာ ဖိုင်ထဲသို့ ရေးသားသည်။

    > 💁 ပုံကို `BytesIO` object မသုံးဘဲ ဖိုင်ထဲသို့ တိုက်ရိုက် သိမ်းဆည်းနိုင်သည်။ သို့သော် ဒီသင်ခန်းစာတွင် image classifier သို့ ပုံကို ပေးပို့ရန် `BytesIO` object ကို အသုံးပြုထားသည်။

1. CounterFit တွင် ကင်မရာဖမ်းယူမည့်ပုံကို configure လုပ်ပါ။ *Source* ကို *File* သို့မဟုတ် *WebCam* သတ်မှတ်ပြီး ပုံဖိုင်တစ်ခု upload လုပ်ပါ၊ သို့မဟုတ် webcam မှပုံများကို ဖမ်းယူပါ။ ပုံတစ်ခုကိုရွေးချယ်ပြီး သို့မဟုတ် webcam ကိုရွေးချယ်ပြီးနောက် **Set** ခလုတ်ကို ရွေးချယ်ပါ။

    ![CounterFit တွင် ဖိုင်ကို image source အဖြစ် သတ်မှတ်ထားခြင်းနှင့် webcam preview](../../../../../translated_images/my/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. ပုံတစ်ပုံကို ဖမ်းယူပြီး `image.jpg` ဟုခေါ်သော ဖိုင်အဖြစ် လက်ရှိဖိုလ်ဒါတွင် သိမ်းဆည်းမည်။ ဒီဖိုင်ကို VS Code explorer တွင် တွေ့မြင်နိုင်မည်။ ဖိုင်ကို ရွေးချယ်ပြီး ပုံကို ကြည့်ရှုပါ။ Rotate လုပ်ရန်လိုအပ်ပါက `camera.rotation = 0` line ကို update လုပ်ပြီး ပုံကို ထပ်မံဖမ်းယူပါ။

> 💁 ဒီ code ကို [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device) ဖိုလ်ဒါတွင် ရှာနိုင်သည်။

😀 သင့်ရဲ့ ကင်မရာအစီအစဉ်ရေးခြင်းအောင်မြင်ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။