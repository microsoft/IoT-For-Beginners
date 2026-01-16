<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-28T15:56:59+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "my"
}
-->
# အနီးကပ်မှုကို ရှာဖွေပါ - အတု IoT စက်ပစ္စည်း

ဒီသင်ခန်းစာအပိုင်းမှာ သင်၏ အတု IoT စက်ပစ္စည်းတွင် အနီးကပ်မှုအာရုံခံကိရိယာတစ်ခု ထည့်သွင်းပြီး အကွာအဝေးကို ဖတ်ရှုမည်ဖြစ်သည်။

## စက်ပစ္စည်း

အတု IoT စက်ပစ္စည်းသည် အတုအကွာအဝေးအာရုံခံကိရိယာကို အသုံးပြုမည်။

အမှန်တကယ် IoT စက်ပစ္စည်းတွင် အကွာအဝေးကို ရှာဖွေဖို့ လေဆာအကွာအဝေးမော်ဂျူးပါရှိသော အာရုံခံကိရိယာကို အသုံးပြုမည်။

### CounterFit တွင် အကွာအဝေးအာရုံခံကိရိယာကို ထည့်သွင်းပါ

အတုအကွာအဝေးအာရုံခံကိရိယာကို အသုံးပြုရန် CounterFit app တွင် ထည့်သွင်းရန်လိုအပ်သည်။

#### လုပ်ငန်းစဉ် - CounterFit တွင် အကွာအဝေးအာရုံခံကိရိယာကို ထည့်သွင်းပါ

CounterFit app တွင် အကွာအဝေးအာရုံခံကိရိယာကို ထည့်သွင်းပါ။

1. VS Code တွင် `fruit-quality-detector` ကုဒ်ကို ဖွင့်ပြီး အတုပတ်ဝန်းကျင်ကို အတက်ထားပါ။

1. အပို Pip package တစ်ခုကို ထည့်သွင်းပါ။ ဒါဟာ CounterFit shim ကို ထည့်သွင်းပြီး [rpi-vl53l0x Pip package](https://pypi.org/project/rpi-vl53l0x/) ကို အတုဖြင့် အသုံးပြုနိုင်စေမည်။ ဒီ Python package သည် [VL53L0X time-of-flight distance sensor](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/) နှင့် ဆက်သွယ်သည်။ အတုပတ်ဝန်းကျင်ကို အတက်ထားသော terminal မှာ ထည့်သွင်းပါ။

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. CounterFit web app ကို အလုပ်လုပ်နေကြောင်း သေချာစေပါ။

1. အကွာအဝေးအာရုံခံကိရိယာကို ဖန်တီးပါ:

    1. *Sensors* panel ရဲ့ *Create sensor* box မှာ *Sensor type* box ကို drop down လုပ်ပြီး *Distance* ကို ရွေးပါ။

    1. *Units* ကို `Millimeter` အဖြစ်ထားပါ။

    1. ဒီအာရုံခံကိရိယာသည် I²C sensor ဖြစ်သောကြောင့် address ကို `0x29` အဖြစ်ထားပါ။ အမှန်တကယ် VL53L0X sensor ကို အသုံးပြုပါက address ကို hardcoded လုပ်ထားမည်ဖြစ်သည်။

    1. **Add** ခလုတ်ကို ရွေးပြီး အကွာအဝေးအာရုံခံကိရိယာကို ဖန်တီးပါ။

    ![အကွာအဝေးအာရုံခံကိရိယာ၏ ဆက်တင်များ](../../../../../translated_images/my/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.png)

    အကွာအဝေးအာရုံခံကိရိယာကို ဖန်တီးပြီး အာရုံခံကိရိယာစာရင်းတွင် ပေါ်လာမည်။

    ![ဖန်တီးပြီးသော အကွာအဝေးအာရုံခံကိရိယာ](../../../../../translated_images/my/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.png)

## အကွာအဝေးအာရုံခံကိရိယာကို အစီအစဉ်ရေးပါ

အတု IoT စက်ပစ္စည်းသည် အတုအကွာအဝေးအာရုံခံကိရိယာကို အသုံးပြုရန် အစီအစဉ်ရေးနိုင်ပါပြီ။

### လုပ်ငန်းစဉ် - time of flight sensor ကို အစီအစဉ်ရေးပါ

1. `fruit-quality-detector` project တွင် `distance-sensor.py` ဟုခေါ်သော ဖိုင်အသစ်တစ်ခု ဖန်တီးပါ။

    > 💁 IoT စက်ပစ္စည်းများစွာကို အတုဖြင့် simulation လုပ်ရန် အလွယ်ဆုံးနည်းလမ်းမှာ Python ဖိုင်တစ်ခုစီတွင် အစီအစဉ်ရေးပြီး တစ်ချိန်တည်းတွင် run လုပ်ခြင်းဖြစ်သည်။

1. အောက်ပါကုဒ်ဖြင့် CounterFit နှင့် ချိတ်ဆက်မှုကို စတင်ပါ:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. အောက်ပါကုဒ်ကို ထည့်သွင်းပါ:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    ဒီကုဒ်သည် VL53L0X time of flight sensor အတွက် sensor library shim ကို import လုပ်သည်။

1. အောက်တွင် အာရုံခံကိရိယာကို access လုပ်ရန် အောက်ပါကုဒ်ကို ထည့်သွင်းပါ:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    ဒီကုဒ်သည် အကွာအဝေးအာရုံခံကိရိယာကို ကြေညာပြီး sensor ကို စတင်သည်။

1. နောက်ဆုံးတွင် အကွာအဝေးကို ဖတ်ရန် အဆုံးမရှိသော loop ကို ထည့်သွင်းပါ:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    ဒီကုဒ်သည် sensor မှ ဖတ်ရှုရန် value ရရှိသည်ကို စောင့်ပြီး console တွင် print လုပ်သည်။

1. ဒီကုဒ်ကို run လုပ်ပါ။

    > 💁 ဒီဖိုင်ကို `distance-sensor.py` ဟုခေါ်သည်ကို မမေ့ပါနှင့်! Python ဖြင့် run လုပ်ပါ၊ `app.py` မဟုတ်ပါ။

1. သင် console တွင် အကွာအဝေးတိုင်းတာမှုများကို မြင်ရမည်။ CounterFit တွင် value ကို ပြောင်းလဲပါ၊ သို့မဟုတ် အတု random value များကို အသုံးပြုပါ။

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 ဒီကုဒ်ကို [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device) folder တွင် ရှာဖွေနိုင်သည်။

😀 သင်၏ proximity sensor အစီအစဉ်အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူရင်းဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအမှားများ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။