<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-28T15:55:53+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "my"
}
-->
# အနီးကပ်မှုကို သိရှိခြင်း - Wio Terminal

ဒီသင်ခန်းစာအပိုင်းမှာ Wio Terminal ကို proximity sensor တစ်ခုထည့်သွင်းပြီး အကွာအဝေးကိုဖတ်ရှုမည်ဖြစ်သည်။

## Hardware

Wio Terminal အတွက် proximity sensor တစ်ခုလိုအပ်ပါသည်။

သင်အသုံးပြုမည့် sensor သည် [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html) ဖြစ်သည်။ ဒီ sensor သည် laser ranging module ကိုအသုံးပြု၍ အကွာအဝေးကို သိရှိသည်။ ဒီ sensor သည် 10mm မှ 2000mm (1cm - 2m) အကွာအဝေးရှိပြီး 1000mm အထက်ရှိအကွာအဝေးများကို 8109mm အဖြစ် report လုပ်ပါမည်။

Laser rangefinder သည် sensor ၏နောက်ဘက်တွင်ရှိပြီး Grove socket ၏ဆန့်ဘက်ဘက်တွင်ရှိသည်။

ဒီ sensor သည် I²C sensor ဖြစ်သည်။

### Time of Flight Sensor ကို ချိတ်ဆက်ခြင်း

Grove Time of Flight Sensor ကို Wio Terminal နှင့် ချိတ်ဆက်နိုင်သည်။

#### Task - Time of Flight Sensor ကို ချိတ်ဆက်ပါ

Time of Flight Sensor ကို ချိတ်ဆက်ပါ။

![A grove time of flight sensor](../../../../../translated_images/my/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Grove cable ၏တစ်ဖက်အဆုံးကို Time of Flight Sensor ၏ socket ထဲသို့ ထည့်ပါ။ ၎င်းသည် တစ်ဖက်ဘက်သာ အဆင်ပြေစွာ ထည့်နိုင်ပါမည်။

1. Wio Terminal ကို သင့်ကွန်ပျူတာ သို့မဟုတ် အခြား power supply မှ ချိတ်ဆက်ထားခြင်းမရှိဘဲ Grove cable ၏တစ်ဖက်အဆုံးကို Wio Terminal ၏ screen ကိုကြည့်နေသောအခါ ဘယ်ဘက် Grove socket (power button အနီးဆုံး socket) ထဲသို့ ချိတ်ဆက်ပါ။ ၎င်းသည် digital နှင့် I²C socket ပေါင်းစပ်ထားသော socket ဖြစ်သည်။

![The grove time of flight sensor connected to the left hand socket](../../../../../translated_images/my/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Wio Terminal ကို သင့်ကွန်ပျူတာနှင့် ချိတ်ဆက်နိုင်ပါပြီ။

## Time of Flight Sensor ကို Program လုပ်ခြင်း

Wio Terminal ကို ချိတ်ဆက်ထားသော Time of Flight Sensor ကို အသုံးပြုရန် Program လုပ်နိုင်ပါပြီ။

### Task - Time of Flight Sensor ကို Program လုပ်ပါ

1. PlatformIO ကို အသုံးပြု၍ Wio Terminal project အသစ်တစ်ခု ဖန်တီးပါ။ ဒီ project ကို `distance-sensor` ဟု အမည်ပေးပါ။ `setup` function တွင် serial port ကို configure လုပ်ရန် code ထည့်ပါ။

1. Project ၏ `platformio.ini` ဖိုင်တွင် Seeed Grove Time of Flight Distance Sensor Library အတွက် library dependency ကို ထည့်ပါ။

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. `main.cpp` တွင် ရှိပြီးသား include directives အောက်တွင် `Seeed_vl53l0x` class ၏ instance တစ်ခုကို ကြေညာပါ။ ၎င်းသည် Time of Flight Sensor နှင့် အပြန်အလှန်လုပ်ဆောင်ရန် အသုံးပြုမည်ဖြစ်သည်။

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. `setup` function ၏ အောက်ဆုံးတွင် sensor ကို initialize လုပ်ရန် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. `loop` function တွင် sensor မှတစ်ဆင့် value တစ်ခုကို ဖတ်ပါ။

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    ဒီ code သည် data structure တစ်ခုကို initialize လုပ်ပြီး `PerformSingleRangingMeasurement` method ထဲသို့ pass လုပ်ပါမည်။ ၎င်းသည် distance measurement ဖြင့် populate လုပ်ပါမည်။

1. ဒီ code အောက်တွင် distance measurement ကို ရေးထုတ်ပြီး 1 စက္ကန့်အတွက် delay လုပ်ပါ။

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. ဒီ code ကို build, upload, run လုပ်ပါ။ Serial monitor တွင် distance measurement များကို ကြည့်နိုင်ပါမည်။ Sensor အနီးတွင် objects များကိုထားပြီး distance measurement ကို ကြည့်ရှုနိုင်ပါမည်။

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Rangefinder သည် sensor ၏နောက်ဘက်တွင်ရှိသောကြောင့် အကွာအဝေးကိုတိုင်းတာသောအခါ မှန်ကန်သောဘက်ကို အသုံးပြုပါ။

    ![The rangefinder on the back of the time of flight sensor pointing at a banana](../../../../../translated_images/my/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 ဒီ code ကို [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal) folder တွင် ရှာနိုင်ပါသည်။

😀 သင့် proximity sensor program အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရားရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူက ဘာသာပြန်ခြင်းကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားယူမှားမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။