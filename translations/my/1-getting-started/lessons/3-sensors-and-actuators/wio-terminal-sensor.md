<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-28T17:30:51+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "my"
}
-->
# Wio Terminal - အာရုံခံကိရိယာ ထည့်သွင်းခြင်း

ဒီသင်ခန်းစာအပိုင်းမှာ Wio Terminal ရဲ့ အလင်းအာရုံခံကိရိယာကို အသုံးပြုသွားမှာ ဖြစ်ပါတယ်။

## ဟာ့ဒ်ဝဲ

ဒီသင်ခန်းစာအတွက် အသုံးပြုမည့် အာရုံခံကိရိယာက **အလင်းအာရုံခံကိရိယာ** ဖြစ်ပြီး၊ [photodiode](https://wikipedia.org/wiki/Photodiode) ကို အသုံးပြုကာ အလင်းကို လျှပ်စစ်သို့ ပြောင်းလဲပေးပါတယ်။ ဒီကိရိယာက analog အာရုံခံကိရိယာဖြစ်ပြီး၊ 0 မှ 1,023 အတွင်းရှိ ကိန်းတန်ဖိုးတစ်ခုကို ပေးပို့ကာ အလင်းရဲ့ အချိုးချင်းပမာဏကို ဖော်ပြပေးပါတယ်။ ဒါဟာ [lux](https://wikipedia.org/wiki/Lux) လိုသော တိုင်းတာမှုယူနစ်တစ်ခုနဲ့ မဆက်စပ်ပါဘူး။

အလင်းအာရုံခံကိရိယာကို Wio Terminal ထဲမှာ တပ်ဆင်ထားပြီး၊ အနောက်ဘက်ရှိ ပလပ်စတစ်ပြတင်းပေါက်မှ မြင်နိုင်ပါတယ်။

![Wio Terminal အနောက်ဘက်ရှိ အလင်းအာရုံခံကိရိယာ](../../../../../translated_images/wio-light-sensor.b1f529f3c95f5165.my.png)

## အလင်းအာရုံခံကိရိယာကို ပရိုဂရမ်ရေးခြင်း

ဒီစက်ကို အလင်းအာရုံခံကိရိယာကို အသုံးပြုနိုင်ရန် ပရိုဂရမ်ရေးနိုင်ပါပြီ။

### လုပ်ငန်းစဉ်

စက်ကို ပရိုဂရမ်ရေးပါ။

1. ယခင်အပိုင်းမှာ ဖန်တီးထားသော nightlight project ကို VS Code မှာ ဖွင့်ပါ။

1. `setup` function ရဲ့ အောက်ဆုံးမှာ အောက်ပါလိုင်းကို ထည့်ပါ။

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    ဒီလိုင်းက အာရုံခံကိရိယာ hardware နဲ့ ဆက်သွယ်ရန် အသုံးပြုမည့် pin များကို ပြင်ဆင်ပေးပါတယ်။

    `WIO_LIGHT` pin က on-board အလင်းအာရုံခံကိရိယာနဲ့ ဆက်စပ်ထားသော GPIO pin နံပါတ်ဖြစ်ပါတယ်။ ဒီ pin ကို `INPUT` အဖြစ် သတ်မှတ်ထားပြီး၊ အာရုံခံကိရိယာမှ ဒေတာကို ဖတ်ယူရန် အသုံးပြုပါမည်။

1. `loop` function ရဲ့ အကြောင်းအရာအားလုံးကို ဖျက်ပါ။

1. အောက်ပါကုဒ်ကို ယခုအလွတ်ဖြစ်နေသော `loop` function ထဲ ထည့်ပါ။

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    ဒီကုဒ်က `WIO_LIGHT` pin မှ analog တန်ဖိုးတစ်ခုကို ဖတ်ယူပါမည်။ ဒီတန်ဖိုးက on-board အလင်းအာရုံခံကိရိယာမှ 0-1,023 အတွင်းရှိ တန်ဖိုးတစ်ခုကို ဖော်ပြပါမည်။ ဒီတန်ဖိုးကို Serial Monitor မှာ ဖတ်ရှုနိုင်ရန် serial port သို့ ပေးပို့ပါမည်။ `Serial.print` က နောက်ဆုံးမှာ အတန်းသစ်မထည့်ပေးပါဘူး၊ ဒါကြောင့် တိုင်းတန်းတစ်ခုစီမှာ `Light value:` နဲ့ အလင်းတန်ဖိုးကို ဖော်ပြပါမည်။

1. `loop` function ရဲ့ အဆုံးမှာ တစ်စက္ကန့် (1,000ms) အနည်းငယ် နားစေပါ။ အလင်းအဆင့်များကို အဆက်မပြတ် စစ်ဆေးရန် မလိုအပ်ပါဘူး။ နားစေခြင်းက စက်ရဲ့ လျှပ်စစ်စွမ်းအင် သုံးစွဲမှုကို လျှော့ချပေးပါမည်။

    ```cpp
    delay(1000);
    ```

1. Wio Terminal ကို သင့်ကွန်ပျူတာနှင့် ပြန်လည်ချိတ်ဆက်ပြီး၊ ယခင်ကဲ့သို့ ကုဒ်အသစ်ကို upload လုပ်ပါ။

1. Serial Monitor ကို ချိတ်ဆက်ပါ။ အလင်းတန်ဖိုးများကို terminal မှာ output အဖြစ် မြင်ရပါမည်။ Wio Terminal ရဲ့ အနောက်ဘက်ရှိ အလင်းအာရုံခံကိရိယာကို ဖုံးထားခြင်းနှင့် ဖွင့်ထားခြင်းအားဖြင့် တန်ဖိုးများ ပြောင်းလဲမှုကို ကြည့်ရှုနိုင်ပါမည်။

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 ဒီကုဒ်ကို [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal) folder မှာ ရှာနိုင်ပါတယ်။

😀 သင့် nightlight ပရိုဂရမ်မှာ အာရုံခံကိရိယာ ထည့်သွင်းခြင်း အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါရှိနိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်ခြင်းကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအမှားများ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။