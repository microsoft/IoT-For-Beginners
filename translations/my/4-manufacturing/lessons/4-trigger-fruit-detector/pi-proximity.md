<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-28T15:55:16+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "my"
}
-->
# နီးကပ်မှုကို သိရှိရန် - Raspberry Pi

ဒီသင်ခန်းစာအပိုင်းမှာ Raspberry Pi ကို နီးကပ်မှုအာရုံခံကိရိယာတစ်ခု ထည့်သွင်းပြီး အကွာအဝေးကို ဖတ်ရှုမည်ဖြစ်သည်။

## ဟာ့ဒ်ဝဲ

Raspberry Pi အတွက် နီးကပ်မှုအာရုံခံကိရိယာလိုအပ်သည်။

သင်အသုံးပြုမည့်အာရုံခံကိရိယာမှာ [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html) ဖြစ်သည်။ ဒီအာရုံခံကိရိယာသည် လေဆာအကွာအဝေးတိုင်းတာမှုကို အသုံးပြု၍ အကွာအဝေးကို သိရှိသည်။ ဒီအာရုံခံကိရိယာသည် 10mm မှ 2000mm (1cm - 2m) အကွာအဝေးရှိပြီး၊ 1000mm အထက်ရှိအကွာအဝေးများကို 8109mm အဖြစ်တိကျစွာ ဖော်ပြပေးမည်ဖြစ်သည်။

လေဆာအကွာအဝေးတိုင်းတာကိရိယာသည် အာရုံခံကိရိယာ၏နောက်ဘက်တွင်ရှိပြီး Grove socket ၏ဆန့်ဘက်ဘက်တွင်ရှိသည်။

ဒီအာရုံခံကိရိယာသည် I²C sensor ဖြစ်သည်။

### Time of Flight Sensor ကို ချိတ်ဆက်ပါ

Grove Time of Flight Sensor ကို Raspberry Pi နှင့် ချိတ်ဆက်နိုင်သည်။

#### အလုပ် - Time of Flight Sensor ကို ချိတ်ဆက်ပါ

Time of Flight Sensor ကို ချိတ်ဆက်ပါ။

![Grove Time of Flight Sensor](../../../../../translated_images/my/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Grove cable ၏တစ်ဖက်အဆုံးကို Time of Flight Sensor ၏ socket တွင် ထည့်ပါ။ ၎င်းသည် တစ်ဖက်ဘက်သာ ထည့်နိုင်ပါသည်။

1. Raspberry Pi ကို ပိတ်ထားပြီး Grove cable ၏တစ်ဖက်အဆုံးကို Grove Base hat တွင်ရှိသော **I²C** အဆို့များထဲမှ တစ်ခုတွင် ချိတ်ဆက်ပါ။ ဒီအဆို့များသည် အောက်ခြေတန်းတွင်ရှိပြီး GPI pins ၏ဆန့်ဘက်ဘက်နှင့် ကင်မရာ cable slot အနီးတွင်ရှိသည်။

![Grove Time of Flight Sensor ကို I²C socket တွင် ချိတ်ဆက်ထားသောပုံ](../../../../../translated_images/my/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Time of Flight Sensor ကို အစီအစဉ်ရေးပါ

Raspberry Pi ကို ချိတ်ဆက်ထားသော Time of Flight Sensor ကို အသုံးပြုရန် အစီအစဉ်ရေးနိုင်ပါသည်။

### အလုပ် - Time of Flight Sensor ကို အစီအစဉ်ရေးပါ

ဒီကိရိယာကို အစီအစဉ်ရေးပါ။

1. Pi ကို ဖွင့်ပြီး boot ပြီးစီးရန် စောင့်ပါ။

1. `fruit-quality-detector` code ကို VS Code တွင် ဖွင့်ပါ၊ Pi တွင် တိုက်ရိုက်ဖွင့်ပါ၊ သို့မဟုတ် Remote SSH extension ကို အသုံးပြု၍ ချိတ်ဆက်ပါ။

1. VL53L0X Time-of-Flight Distance Sensor ကို အသုံးပြုရန် Python package ဖြစ်သော rpi-vl53l0x Pip package ကို ထည့်သွင်းပါ။ ဒီ pip command ကို အသုံးပြု၍ ထည့်သွင်းပါ။

    ```sh
    pip install rpi-vl53l0x
    ```

1. ဒီ project တွင် `distance-sensor.py` ဟုခေါ်သော ဖိုင်အသစ်တစ်ခု ဖန်တီးပါ။

    > 💁 IoT ကိရိယာများစွာကို simulation လုပ်ရန် အလွယ်ဆုံးနည်းမှာ Python ဖိုင်တစ်ခုစီတွင် အစီအစဉ်ရေးပြီး၊ အချိန်တစ်ပြိုင်နက်တွင် run လုပ်ခြင်းဖြစ်သည်။

1. ဒီဖိုင်တွင် အောက်ပါ code ကို ထည့်ပါ။

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    ဒီ code သည် Grove I²C bus library နှင့် Grove Time of Flight Sensor ၏ core sensor hardware အတွက် sensor library ကို import လုပ်သည်။

1. ဒီ code အောက်တွင် အာရုံခံကိရိယာကို access လုပ်ရန် အောက်ပါ code ကို ထည့်ပါ။

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    ဒီ code သည် Grove I²C bus ကို အသုံးပြု၍ Distance Sensor ကို ကြေညာပြီး Sensor ကို စတင်သည်။

1. နောက်ဆုံးတွင် အကွာအဝေးကို ဖတ်ရန် အဆုံးမရှိသော loop ကို ထည့်ပါ။

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    ဒီ code သည် Sensor မှ ဖတ်ရန် value ရရှိရန် စောင့်ပြီး၊ console တွင် print လုပ်သည်။

1. ဒီ code ကို run လုပ်ပါ။

    > 💁 ဒီဖိုင်ကို `distance-sensor.py` ဟုခေါ်သည်ကို မမေ့ပါနှင့်! Python မှတစ်ဆင့် run လုပ်ပါ၊ `app.py` မဟုတ်ပါ။

1. Console တွင် အကွာအဝေးတိုင်းတာမှုများကို တွေ့ရမည်။ Sensor အနီးတွင် objects များကိုထားပြီး အကွာအဝေးတိုင်းတာမှုကို တွေ့ရမည်။

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Rangefinder သည် Sensor ၏နောက်ဘက်တွင်ရှိသည်၊ အကွာအဝေးတိုင်းတာရာတွင် မှန်ကန်သောဘက်ကို အသုံးပြုပါ။

    ![Time of Flight Sensor ၏နောက်ဘက် Rangefinder သည် ငှက်ပျောသီးကို ငေးကြည့်နေသောပုံ](../../../../../translated_images/my/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 ဒီ code ကို [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi) folder တွင် ရှာနိုင်ပါသည်။

😀 သင့် proximity sensor အစီအစဉ်အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။