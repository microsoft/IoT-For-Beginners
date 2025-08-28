<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-28T17:12:31+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "my"
}
-->
# အင်တာနက်မှတစ်ဆင့် သင့်ညဉ့်မီးကို ထိန်းချုပ်ပါ - အတု IoT ဟာ့ဒ်ဝဲနှင့် Raspberry Pi

ဒီသင်ခန်းစာအပိုင်းမှာ သင့် Raspberry Pi သို့မဟုတ် အတု IoT စက်ကိရိယာမှ မီးအလင်းအဆင့်များကို MQTT broker သို့ ပို့ပေးမည့် telemetry ကို ပေးပို့ပါမည်။

## Telemetry ကို ပို့ပေးပါ

နောက်တစ်ဆင့်မှာ telemetry ပါဝင်တဲ့ JSON စာရွက်စာတမ်းကို ဖန်တီးပြီး MQTT broker သို့ ပို့ပေးရမည်ဖြစ်သည်။

### လုပ်ငန်း

Telemetry ကို MQTT broker သို့ ပို့ပေးပါ။

1. VS Code မှာ nightlight project ကို ဖွင့်ပါ။

1. အတု IoT စက်ကိရိယာကို အသုံးပြုနေပါက terminal ကို virtual environment မှာ လည်ပတ်နေကြောင်း သေချာစေပါ။ Raspberry Pi ကို အသုံးပြုနေပါက virtual environment ကို အသုံးမပြုရပါ။

1. `app.py` ဖိုင်၏ အပေါ်ဆုံးတွင် အောက်ပါ import ကို ထည့်ပါ။

    ```python
    import json
    ```

    `json` library ကို telemetry ကို JSON စာရွက်စာတမ်းအဖြစ် encode လုပ်ရန် အသုံးပြုသည်။

1. `client_name` ကြေညာချက်အောက်တွင် အောက်ပါကို ထည့်ပါ။

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` သည် စက်ကိရိယာမှ မီးအလင်းအဆင့်များကို ပို့ပေးမည့် MQTT topic ဖြစ်သည်။

1. ဖိုင်၏ အဆုံးတွင်ရှိသော `while True:` loop ၏ အကြောင်းအရာကို အောက်ပါအတိုင်း ပြောင်းလဲပါ။

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    ဒီကုဒ်သည် မီးအလင်းအဆင့်ကို JSON စာရွက်စာတမ်းအဖြစ် ထုပ်ပိုးပြီး MQTT broker သို့ ပို့ပေးသည်။ ထို့နောက် မက်ဆေ့ပို့ပေးမှုအကြိမ်ရေကို လျှော့ချရန် အနည်းငယ်ရပ်နားသည်။

1. ယခင်အလုပ်မှာ ကုဒ်ကို လည်ပတ်ခဲ့သည့် နည်းလမ်းအတိုင်း ကုဒ်ကို လည်ပတ်ပါ။ အတု IoT စက်ကိရိယာကို အသုံးပြုနေပါက CounterFit app ကို လည်ပတ်နေကြောင်း၊ မီးအလင်းအာရုံခံကိရိယာနှင့် LED ကို မှန်ကန်သော pin များတွင် ဖန်တီးထားကြောင်း သေချာစေပါ။

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 ဒီကုဒ်ကို [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) folder သို့မဟုတ် [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) folder တွင် ရှာတွေ့နိုင်ပါသည်။

😀 သင့်စက်ကိရိယာမှ telemetry ကို အောင်မြင်စွာ ပို့ပေးနိုင်ပါပြီ။

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားယူမှားမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။