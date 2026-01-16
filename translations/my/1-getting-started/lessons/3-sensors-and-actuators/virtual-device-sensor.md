<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-28T17:29:48+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "my"
}
-->
# ညအလင်းပွိုင့် - အိမ်စီး IoT ဟာ့ဒ်ဝဲ

ဒီသင်ခန်းစာအပိုင်းမှာ သင့်ရဲ့ အိမ်စီး IoT စက်ပစ္စည်းမှာ အလင်းခံစနစ်တစ်ခု ထည့်သွင်းပါမည်။

## အိမ်စီး ဟာ့ဒ်ဝဲ

ညအလင်းပွိုင့်အတွက် CounterFit app မှာ sensor တစ်ခုလိုအပ်ပါတယ်။

ဒီ sensor က **အလင်းခံစနစ်** ဖြစ်ပါတယ်။ အလင်းခံစနစ်ဟာ [photodiode](https://wikipedia.org/wiki/Photodiode) တစ်ခုဖြစ်ပြီး အလင်းကို လျှပ်စစ်သို့ ပြောင်းလဲပေးနိုင်ပါတယ်။ အလင်းခံစနစ်တွေဟာ analog sensor ဖြစ်ပြီး အလင်းပမာဏကို အနည်းအများအတိုင်း အနိမ့်ဆုံးအဆင့်အထိ integer value အနေနဲ့ ပေးပို့ပါတယ်။ ဒါဟာ [lux](https://wikipedia.org/wiki/Lux) စတဲ့ စံချိန်စနစ်နဲ့ မဆက်စပ်ပါ။

### CounterFit မှာ sensor တွေ ထည့်သွင်းပါ

အိမ်စီး အလင်းခံစနစ်ကို အသုံးပြုဖို့ CounterFit app မှာ ထည့်သွင်းဖို့လိုအပ်ပါတယ်။

#### လုပ်ငန်း - CounterFit မှာ sensor တွေ ထည့်သွင်းပါ

CounterFit app မှာ အလင်းခံစနစ်ကို ထည့်သွင်းပါ။

1. အရင်အပိုင်းမှာ အသုံးပြုခဲ့တဲ့ CounterFit web app ကို run လုပ်ထားပါ။ မ run လုပ်ထားရင် ပြန်စတင်ပါ။

1. အလင်းခံစနစ်တစ်ခု ဖန်တီးပါ:

    1. *Sensors* panel ရဲ့ *Create sensor* box မှာ *Sensor type* box ကို drop down လုပ်ပြီး *Light* ကို ရွေးပါ။

    1. *Units* ကို *NoUnits* အတိုင်းထားပါ။

    1. *Pin* ကို *0* အတိုင်းထားပါ။

    1. **Add** button ကို ရွေးပြီး Pin 0 မှာ အလင်း sensor ကို ဖန်တီးပါ။

    ![အလင်း sensor ရဲ့ settings](../../../../../translated_images/my/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    အလင်း sensor ကို ဖန်တီးပြီး sensor list မှာ ပေါ်လာပါမည်။

    ![ဖန်တီးပြီးသော အလင်း sensor](../../../../../translated_images/my/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## အလင်း sensor ကို programming လုပ်ပါ

အခုတော့ စက်ပစ္စည်းကို CounterFit app ရဲ့ အလင်း sensor ကို အသုံးပြုဖို့ programming လုပ်နိုင်ပါပြီ။

### လုပ်ငန်း - အလင်း sensor ကို programming လုပ်ပါ

စက်ပစ္စည်းကို programming လုပ်ပါ။

1. အရင်အပိုင်းမှာ ဖန်တီးထားတဲ့ VS Code ရဲ့ nightlight project ကို ဖွင့်ပါ။ virtual environment ကို အသုံးပြုဖို့ terminal ကို kill လုပ်ပြီး ပြန်ဖန်တီးပါ။

1. `app.py` ဖိုင်ကို ဖွင့်ပါ။

1. `app.py` ဖိုင်ရဲ့ အပေါ်ပိုင်းမှာ `import` statement တွေ နေရာမှာ အောက်ပါ code ကို ထည့်ပါ:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time` statement က Python ရဲ့ `time` module ကို import လုပ်ပြီး ဒီသင်ခန်းစာရဲ့ နောက်ပိုင်းမှာ အသုံးပြုပါမည်။

    `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` statement က CounterFit Grove shim Python libraries မှ `GroveLightSensor` ကို import လုပ်ပါမည်။ ဒီ library မှာ CounterFit app မှာ ဖန်တီးထားတဲ့ အလင်း sensor နဲ့ ဆက်သွယ်ဖို့ code ပါဝင်ပါတယ်။

1. ဖိုင်ရဲ့ အောက်ပိုင်းမှာ အလင်း sensor ကို စီမံခန့်ခွဲဖို့ class instance တွေ ဖန်တီးရန် အောက်ပါ code ကို ထည့်ပါ:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    `light_sensor = GroveLightSensor(0)` line က **0** pin နဲ့ ဆက်သွယ်ထားတဲ့ `GroveLightSensor` class ရဲ့ instance ကို ဖန်တီးပါမည်။

1. အပေါ်က code အပြီးမှာ အလင်း sensor ရဲ့ value ကို poll လုပ်ပြီး console မှာ print လုပ်ဖို့ infinite loop ကို ထည့်ပါ:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    ဒီ code က `GroveLightSensor` class ရဲ့ `light` property ကို အသုံးပြုပြီး အလင်းအဆင့်ကို ဖတ်ပါမည်။ ဒီ property က pin မှ analog value ကို ဖတ်ပြီး console မှာ print လုပ်ပါမည်။

1. `while` loop ရဲ့ အဆုံးမှာ တစ်စက္ကန့်အနည်းငယ် sleep လုပ်ပါ။ အလင်းအဆင့်ကို အမြဲမကြည့်ဖို့ sleep လုပ်ခြင်းက စက်ပစ္စည်းရဲ့ power consumption ကို လျှော့ချနိုင်ပါတယ်။

    ```python
    time.sleep(1)
    ```

1. VS Code Terminal မှာ အောက်ပါ command ကို run လုပ်ပြီး Python app ကို run လုပ်ပါ:

    ```sh
    python3 app.py
    ```

    အလင်း value တွေ console မှာ output ဖြစ်လာပါမည်။ အစမှာ value က 0 ဖြစ်ပါမည်။

1. CounterFit app မှာ sensor ရဲ့ value ကို ပြောင်းလဲပါ။ sensor ဖတ်တဲ့ value ကို အောက်ပါနည်းနှစ်မျိုးနဲ့ ပြောင်းလဲနိုင်ပါတယ်:

    * *Value* box မှာ နံပါတ်တစ်ခု ထည့်ပြီး **Set** button ကို ရွေးပါ။ သင်ထည့်တဲ့ နံပါတ်က sensor က ပြန်ပေးတဲ့ value ဖြစ်ပါမည်။

    * *Random* checkbox ကို ရွေးပြီး *Min* နဲ့ *Max* value တွေ ထည့်ပါ။ **Set** button ကို ရွေးပါ။ sensor ဖတ်တဲ့ value တစ်ခုစီဟာ *Min* နဲ့ *Max* အကြားမှာ random နံပါတ်ဖြစ်ပါမည်။

    သင်ပြောင်းလဲတဲ့ value တွေ console မှာ output ဖြစ်လာပါမည်။ *Value* နဲ့ *Random* settings ကို ပြောင်းပြီး value ကို ပြောင်းလဲပါ။

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 ဒီ code ကို [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device) folder မှာ ရှာနိုင်ပါတယ်။

😀 သင့်ရဲ့ ညအလင်းပွိုင့် program အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါရှိနိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူရင်းဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်ခြင်းကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။