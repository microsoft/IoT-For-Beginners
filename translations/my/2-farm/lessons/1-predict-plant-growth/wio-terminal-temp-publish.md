<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-28T18:09:10+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "my"
}
-->
# အပူချိန်ကို ထုတ်ပြန်ပါ - Wio Terminal

ဒီသင်ခန်းစာအပိုင်းမှာ Wio Terminal က တွေ့ရှိထားတဲ့ အပူချိန်တန်ဖိုးတွေကို MQTT မှတစ်ဆင့် ထုတ်ပြန်မှာဖြစ်ပြီး၊ နောက်ပိုင်းမှာ GDD တွက်ချက်ဖို့ အသုံးပြုနိုင်အောင် ပြင်ဆင်မှာဖြစ်ပါတယ်။

## အပူချိန်ကို ထုတ်ပြန်ပါ

အပူချိန်ကို ဖတ်ပြီးတာနဲ့ MQTT မှတစ်ဆင့် 'server' ကုဒ်တစ်ခုဆီကို ထုတ်ပြန်နိုင်ပါတယ်၊ အဲဒီကုဒ်က အပူချိန်တန်ဖိုးတွေကို ဖတ်ပြီး သိမ်းဆည်းထားပြီး GDD တွက်ချက်ဖို့ အသုံးပြုနိုင်ပါတယ်။ Microcontroller တွေက အင်တာနက်ကနေ အချိန်ကို မဖတ်နိုင်သလို၊ အချိန်ကို အလိုအလျောက် စောင့်ကြည့်ဖို့ real-time clock မပါရှိပါဘူး၊ ဒါကြောင့် ဒီအရာတွေကို လိုအပ်တဲ့ hardware ရှိမရှိပေါ်မူတည်ပြီး device ကို အထူးစီမံရေးသားရပါမယ်။

ဒီသင်ခန်းစာအတွက် အဆင်ပြေစေဖို့ အချိန်ကို sensor data နဲ့အတူ မပို့ပါဘူး၊ အစား server ကုဒ်က message ရရှိတဲ့အချိန်မှာ အချိန်ကို ထည့်ပေးနိုင်ပါတယ်။

### လုပ်ဆောင်ရန်

Device ကို အပူချိန် data ကို ထုတ်ပြန်ဖို့ စီမံရေးသားပါ။

1. `temperature-sensor` Wio Terminal project ကို ဖွင့်ပါ။

1. Lesson 4 မှာ လုပ်ခဲ့သလို MQTT နဲ့ ချိတ်ဆက်ပြီး telemetry ပို့ဖို့ လုပ်ဆောင်ပါ။ အများပြည်သူအသုံးပြုနိုင်တဲ့ Mosquitto broker ကို ပြန်လည်အသုံးပြုမှာဖြစ်ပါတယ်။

    ဒီအဆင့်တွေမှာ ပါဝင်တာက:

    - `.ini` ဖိုင်မှာ Seeed WiFi နဲ့ MQTT library တွေ ထည့်ပါ။
    - WiFi နဲ့ ချိတ်ဆက်ဖို့ config ဖိုင်နဲ့ ကုဒ်ထည့်ပါ။
    - MQTT broker နဲ့ ချိတ်ဆက်ဖို့ ကုဒ်ထည့်ပါ။
    - Telemetry ပို့ဖို့ ကုဒ်ထည့်ပါ။

    > ⚠️ [MQTT နဲ့ ချိတ်ဆက်ရန် လမ်းညွှန်ချက်များ](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) နဲ့ [telemetry ပို့ရန် လမ်းညွှန်ချက်များ](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) ကို လိုအပ်ပါက ပြန်လည်ကြည့်ပါ။

1. `config.h` header ဖိုင်ထဲမှာ `CLIENT_NAME` က ဒီ project ကို ကိုယ်စားပြုနေမှန်း သေချာစေပါ။

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Telemetry အတွက် အလင်းတန်ဖိုး ပို့မယ့်အစား DHT sensor က ဖတ်ထားတဲ့ အပူချိန်တန်ဖိုးကို JSON document ထဲမှာ `temperature` ဆိုတဲ့ property အနေနဲ့ ပို့ပါ။ ဒီအတွက် `main.cpp` ထဲက `loop` function ကို ပြောင်းလဲရေးသားပါ။

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. အပူချိန်တန်ဖိုးကို မကြာခဏ ဖတ်စရာ မလိုပါဘူး - အချိန်အတိုအတွင်းမှာ မပြောင်းလဲလွန်းပါဘူး၊ ဒါကြောင့် `loop` function ထဲမှာ `delay` ကို ၁၀ မိနစ်အထိ သတ်မှတ်ပါ။

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 `delay` function က အချိန်ကို milliseconds နဲ့ယူပါတယ်၊ ဒါကြောင့် calculation ရလဒ်အနေနဲ့ ပေးထားတာကို အသုံးပြုရတာ ပိုမိုလွယ်ကူစေပါတယ်။ ၁,၀၀၀ms = ၁ စက္ကန့်၊ ၆၀ စက္ကန့် = ၁ မိနစ်၊ ဒါကြောင့် ၁၀ x (၆၀ စက္ကန့်) x (၁,၀၀၀ms) က ၁၀ မိနစ် delay ဖြစ်ပါတယ်။

1. ဒီကုဒ်ကို Wio Terminal ထဲကို upload လုပ်ပြီး serial monitor ကို အသုံးပြုကာ MQTT broker ဆီကို အပူချိန် ပို့နေမှုကို ကြည့်ပါ။

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 ဒီကုဒ်ကို [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) folder ထဲမှာ ရှာနိုင်ပါတယ်။

😀 သင့် device မှာ အပူချိန်ကို telemetry အနေနဲ့ အောင်မြင်စွာ ထုတ်ပြန်ပြီးပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူရင်းဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။