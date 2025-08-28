<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-28T18:10:18+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "my"
}
-->
# အပူချိန်ကို ထုတ်ဝေခြင်း - Virtual IoT Hardware နှင့် Raspberry Pi

ဒီသင်ခန်းစာရဲ့ အပိုင်းမှာတော့ Raspberry Pi သို့မဟုတ် Virtual IoT Device က ရှာဖွေတွေ့ရှိထားတဲ့ အပူချိန်တန်ဖိုးတွေကို MQTT ကနေ ထုတ်ဝေပြီးနောက်ပိုင်း GDD တွက်ချက်ဖို့ အသုံးပြုနိုင်အောင် ပြုလုပ်ပါမယ်။

## အပူချိန်ကို ထုတ်ဝေပါ

အပူချိန်ကို ဖတ်ပြီးတာနဲ့ MQTT ကနေ 'server' code တစ်ခုဆီကို ထုတ်ဝေနိုင်ပါတယ်။ ဒီ code က အပူချိန်တန်ဖိုးတွေကို ဖတ်ပြီး GDD တွက်ချက်ဖို့ အသင့်ထားပေးပါမယ်။

### တာဝန် - အပူချိန်ကို ထုတ်ဝေပါ

အပူချိန်ဒေတာကို ထုတ်ဝေဖို့အတွက် device ကို အစီအစဉ်ရေးပါ။

1. `temperature-sensor` app project ကို ဖွင့်ထားမဟုတ်ရင် ဖွင့်ပါ။

1. Lesson 4 မှာ လုပ်ခဲ့တဲ့အတိုင်း MQTT ကို ချိတ်ဆက်ပြီး telemetry ပို့ဖို့ လုပ်ဆောင်ပါ။ ဒီအတွက် public Mosquitto broker ကို အသုံးပြုပါမယ်။

    ဒီအဆင့်တွေကို လိုက်နာပါ-

    - MQTT pip package ကို ထည့်ပါ။
    - MQTT broker ကို ချိတ်ဆက်ဖို့ code ထည့်ပါ။
    - Telemetry ကို ထုတ်ဝေဖို့ code ထည့်ပါ။

    > ⚠️ [MQTT ချိတ်ဆက်ရန် လမ်းညွှန်ချက်များ](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) နှင့် [telemetry ပို့ရန် လမ်းညွှန်ချက်များ](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) ကို လိုအပ်ပါက Lesson 4 မှာ ပြန်ကြည့်ပါ။

1. `client_name` က ဒီ project ရဲ့ နာမည်ကို ပြသနိုင်အောင် သေချာစေပါ-

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Telemetry အတွက်တော့ light value ပို့မယ့်အစား DHT sensor က ဖတ်ထားတဲ့ အပူချိန်တန်ဖိုးကို JSON document ရဲ့ `temperature` ဆိုတဲ့ property အနေနဲ့ ပို့ပါ-

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. အပူချိန်တန်ဖိုးကို မကြာခဏ ဖတ်စရာမလိုပါဘူး - အချိန်အတိုအတွင်းမှာ များစွာပြောင်းလဲမှာ မဟုတ်လို့ `time.sleep` ကို ၁၀ မိနစ်အထိ သတ်မှတ်ပါ-

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 `sleep` function က အချိန်ကို စက္ကန့်အနေနဲ့ ယူပါတယ်။ အလွယ်တကူ ဖတ်နိုင်အောင် ၁ မိနစ်မှာ ၆၀ စက္ကန့်ဆိုတာကို အသုံးပြုပြီး ၁၀ x (၁ မိနစ်မှာ ၆၀ စက္ကန့်) ဆိုတဲ့ တွက်ချက်မှုရလဒ်ကို ပေးထားပါတယ်။

1. အစီအစဉ်ကို အရင်အပိုင်းမှာ လုပ်ခဲ့သလိုပဲ run လိုက်ပါ။ Virtual IoT device ကို အသုံးပြုနေတယ်ဆိုရင် CounterFit app ကို run ထားပြီး humidity နဲ့ temperature sensors ကို မှန်ကန်တဲ့ pins တွေမှာ ဖန်တီးထားတာ သေချာပါစေ။

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 ဒီ code ကို [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) folder သို့မဟုတ် [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi) folder မှာ ရှာနိုင်ပါတယ်။

😀 သင့် device ကနေ telemetry အနေနဲ့ အပူချိန်ကို အောင်မြင်စွာ ထုတ်ဝေပြီးပါပြီ။

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားယူမှားမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။