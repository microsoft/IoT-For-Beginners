<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-28T17:47:12+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "my"
}
-->
# မြေစိုထိုင်းဆ - Wio Terminal

ဒီသင်ခန်းစာအပိုင်းမှာ Wio Terminal ကို capacitive မြေစိုထိုင်းဆာန့်ဆာတစ်ခု ထည့်သွင်းပြီး၊ အဲဒီဆာန့်ဆာမှ တန်ဖိုးများကို ဖတ်ယူပါမည်။

## ဟာ့ဒ်ဝဲ

Wio Terminal အတွက် capacitive မြေစိုထိုင်းဆာန့်ဆာတစ်ခု လိုအပ်ပါသည်။

သင်အသုံးပြုမည့်ဆာန့်ဆာမှာ [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html) ဖြစ်ပြီး၊ မြေစိုထိုင်းဆကို မြေ၏ capacitance ကို တိုင်းတာခြင်းဖြင့် တိုင်းတာပါသည်။ မြေစိုထိုင်းဆ တိုးလာသည့်အခါ voltage က လျော့ကျသွားပါသည်။

ဒီဆာန့်ဆာက analog ဆာန့်ဆာဖြစ်ပြီး၊ Wio Terminal ရဲ့ analog pin တွေကို ချိတ်ဆက်ကာ onboard ADC ကို အသုံးပြု၍ 0-1,023 အတွင်း တန်ဖိုးတစ်ခု ဖန်တီးပါသည်။

### မြေစိုထိုင်းဆာန့်ဆာကို ချိတ်ဆက်ပါ

Grove မြေစိုထိုင်းဆာန့်ဆာကို Wio Terminal ရဲ့ analog/digital port တွေထဲမှာ ချိတ်ဆက်နိုင်ပါသည်။

#### လုပ်ငန်းစဉ် - မြေစိုထိုင်းဆာန့်ဆာကို ချိတ်ဆက်ပါ

မြေစိုထိုင်းဆာန့်ဆာကို ချိတ်ဆက်ပါ။

![A grove soil moisture sensor](../../../../../translated_images/my/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. Grove ကေဘယ်တစ်ခုကို မြေစိုထိုင်းဆာန့်ဆာရဲ့ socket ထဲထည့်ပါ။ ဒါဟာ တစ်ဖက်ဘက်သာ ထည့်နိုင်ပါသည်။

1. Wio Terminal ကို သင့်ကွန်ပျူတာ သို့မဟုတ် အခြားပါဝါထောက်ပံ့မှုမှ ချိတ်ဆက်ထားခြင်းမရှိဘဲ၊ Grove ကေဘယ်ရဲ့ အခြားဖက်ကို Wio Terminal ရဲ့ ညာဘက် Grove socket (power button မှ အဝေးဆုံး) ထဲထည့်ပါ။

![The grove soil moisture sensor connected to the right hand socket](../../../../../translated_images/my/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. မြေစိုထိုင်းဆာန့်ဆာကို မြေထဲထည့်ပါ။ အမြင့်ဆုံးအနေအထားလိုင်း (sensor ပေါ်ရှိ အဖြူရောင်လိုင်း) ရှိပြီး၊ အဲဒီလိုင်းအထိသာ ထည့်ပါ၊ အဲဒီလိုင်းကို ကျော်မထည့်ပါနှင့်။

![The grove soil moisture sensor in soil](../../../../../translated_images/my/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. ယခု Wio Terminal ကို သင့်ကွန်ပျူတာနှင့် ချိတ်ဆက်နိုင်ပါပြီ။

## မြေစိုထိုင်းဆာန့်ဆာကို အစီအစဉ်ရေးပါ

Wio Terminal ကို ယခုချိတ်ဆက်ထားသော မြေစိုထိုင်းဆာန့်ဆာကို အသုံးပြုရန် အစီအစဉ်ရေးနိုင်ပါပြီ။

### လုပ်ငန်းစဉ် - မြေစိုထိုင်းဆာန့်ဆာကို အစီအစဉ်ရေးပါ

စက်ကို အစီအစဉ်ရေးပါ။

1. PlatformIO ကို အသုံးပြု၍ Wio Terminal project အသစ်တစ်ခု ဖန်တီးပါ။ ဒီ project ကို `soil-moisture-sensor` ဟု အမည်ပေးပါ။ `setup` function ထဲတွင် serial port ကို configure လုပ်ရန် code ထည့်ပါ။

    > ⚠️ [Project 1, Lesson 1 မှ PlatformIO project ဖန်တီးနည်းအညွှန်းကို လိုအပ်ပါက ကြည့်ရှုနိုင်ပါသည်](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project)။

1. ဒီဆာန့်ဆာအတွက် library မရှိသည့်အတွက်၊ Arduino ရဲ့ [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) function ကို အသုံးပြု၍ analog pin မှ ဖတ်ယူနိုင်ပါသည်။ analog pin ကို input အဖြစ် configure လုပ်ရန် `setup` function ထဲတွင် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    pinMode(A0, INPUT);
    ```

    ဒီ code က `A0` pin ကို input pin အဖြစ် သတ်မှတ်ပြီး၊ voltage ကို ဖတ်ယူနိုင်စေပါသည်။

1. `loop` function ထဲတွင် အောက်ပါ code ကို ထည့်၍ pin မှ voltage ကို ဖတ်ပါ။

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. အထက်ပါ code အောက်တွင် serial port သို့ တန်ဖိုးကို print လုပ်ရန် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. နောက်ဆုံးတွင် 10 စက္ကန့်အနားယူရန် delay ထည့်ပါ။

    ```cpp
    delay(10000);
    ```

1. Code ကို build လုပ်ပြီး Wio Terminal သို့ upload လုပ်ပါ။

    > ⚠️ [Project 1, Lesson 1 မှ PlatformIO project ဖန်တီးနည်းအညွှန်းကို လိုအပ်ပါက ကြည့်ရှုနိုင်ပါသည်](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app)။

1. Upload ပြီးလျှင် serial monitor ကို အသုံးပြု၍ မြေစိုထိုင်းဆကို စောင့်ကြည့်နိုင်ပါသည်။ မြေထဲတွင် ရေထည့်ပါ၊ သို့မဟုတ် sensor ကို မြေထဲမှ ထုတ်ပါ၊ တန်ဖိုးပြောင်းလဲမှုကို ကြည့်ပါ။

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    အထက်ပါ output ဥပမာတွင် ရေထည့်သည့်အခါ voltage လျော့ကျမှုကို တွေ့နိုင်ပါသည်။

> 💁 ဒီ code ကို [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) folder တွင် ရှာနိုင်ပါသည်။

😀 သင့်မြေစိုထိုင်းဆာန့်ဆာအစီအစဉ် အောင်မြင်ခဲ့ပါပြီ!

---

**ဝက်ဘ်ဆိုက်မှတ်ချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှန်ကန်မှုအတွက် ကြိုးစားနေပါသော်လည်း၊ အလိုအလျောက်ဘာသာပြန်ဆိုမှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို ကျေးဇူးပြု၍ သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူလဘာသာစကားဖြင့် အာဏာတည်သောရင်းမြစ်အဖြစ် သတ်မှတ်ရန် လိုအပ်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ အတည်ပြုထားသော ဘာသာပြန်ဆိုမှုကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်ဆိုမှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော နားလည်မှုမှားများ သို့မဟုတ် အဓိပ္ပာယ်မှားများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။