<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-28T17:14:02+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "my"
}
-->
# အင်တာနက်မှ သင့်ညဉ့်မီးအိမ်ကို ထိန်းချုပ်ပါ - အိမ်စီး IoT ဟာ့ဒ်ဝဲနှင့် Raspberry Pi

IoT စက်ပစ္စည်းကို *test.mosquitto.org* နှင့် MQTT ကို အသုံးပြု၍ အလင်းအာရုံခံကိရိယာ၏ ဖတ်ရှုမှုများကို telemetry အချက်အလက်များအဖြစ် ပို့ပေးရန်နှင့် LED ကို ထိန်းချုပ်ရန် အမိန့်များကို လက်ခံရန်အတွက် ကုဒ်ရေးရန် လိုအပ်ပါသည်။

ဒီသင်ခန်းစာ၏ အပိုင်းတွင် သင့် Raspberry Pi သို့မဟုတ် အိမ်စီး IoT စက်ပစ္စည်းကို MQTT broker နှင့် ချိတ်ဆက်ပါမည်။

## MQTT client package ကို ထည့်သွင်းပါ

MQTT broker နှင့် ဆက်သွယ်ရန် MQTT library pip package ကို သင့် Pi သို့မဟုတ် အိမ်စီးပတ်ဝန်းကျင်တွင် (virtual environment) ထည့်သွင်းရန် လိုအပ်ပါသည်။

### လုပ်ဆောင်ရန်

pip package ကို ထည့်သွင်းပါ

1. VS Code တွင် nightlight project ကို ဖွင့်ပါ။

1. အိမ်စီး IoT စက်ပစ္စည်းကို အသုံးပြုနေပါက terminal သည် အိမ်စီးပတ်ဝန်းကျင်ကို run လုပ်နေကြောင်း သေချာပါ။ Raspberry Pi ကို အသုံးပြုနေပါက အိမ်စီးပတ်ဝန်းကျင်ကို အသုံးမပြုပါ။

1. MQTT pip package ကို ထည့်သွင်းရန် အောက်ပါ command ကို run လုပ်ပါ-

    ```sh
    pip3 install paho-mqtt
    ```

## စက်ပစ္စည်းကို ကုဒ်ရေးပါ

စက်ပစ္စည်းကို ကုဒ်ရေးရန် အဆင်သင့်ဖြစ်ပါပြီ။

### လုပ်ဆောင်ရန်

စက်ပစ္စည်းကုဒ်ကို ရေးပါ။

1. `app.py` ဖိုင်၏ အပေါ်ပိုင်းတွင် အောက်ပါ import ကို ထည့်ပါ-

    ```python
    import paho.mqtt.client as mqtt
    ```

    `paho.mqtt.client` library သည် သင့် app ကို MQTT ဖြင့် ဆက်သွယ်နိုင်စေပါသည်။

1. အလင်းအာရုံခံကိရိယာနှင့် LED ကို သတ်မှတ်ထားသော ကုဒ်များ၏ အောက်တွင် အောက်ပါကုဒ်ကို ထည့်ပါ-

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    `<ID>` ကို ဒီစက်ပစ္စည်း client ၏ အမည်အဖြစ် အသုံးပြုမည့် ထူးခြားသော ID ဖြင့် အစားထိုးပါ။ ထို့အပြင် ဒီစက်ပစ္စည်းက ပို့ပေးသောနှင့် subscribe လုပ်သော topics များအတွက်လည်း အသုံးပြုမည်ဖြစ်သည်။ *test.mosquitto.org* broker သည် public ဖြစ်ပြီး ဒီအလုပ်ကို လေ့လာနေသော ကျောင်းသားများအပါအဝင် လူများစွာ အသုံးပြုနေပါသည်။ ထူးခြားသော MQTT client အမည်နှင့် topic အမည်များရှိခြင်းသည် သင့်ကုဒ်သည် အခြားသူများ၏ကုဒ်နှင့် မတူညီစေရန် အရေးကြီးပါသည်။ ဒီ ID ကို သင်ဒီအလုပ်၏ နောက်ပိုင်းတွင် server code ကို ဖန်တီးသောအခါလည်း လိုအပ်ပါမည်။

    > 💁 [GUIDGen](https://www.guidgen.com) ကဲ့သို့သော website ကို အသုံးပြု၍ ထူးခြားသော ID ကို ဖန်တီးနိုင်ပါသည်။

    `client_name` သည် broker တွင် ဒီ MQTT client အတွက် ထူးခြားသောအမည်ဖြစ်သည်။

1. MQTT client object ကို ဖန်တီးပြီး MQTT broker နှင့် ချိတ်ဆက်ရန် အောက်ပါကုဒ်ကို ဒီကုဒ်အသစ်၏ အောက်တွင် ထည့်ပါ-

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    ဒီကုဒ်သည် client object ကို ဖန်တီးပြီး public MQTT broker နှင့် ချိတ်ဆက်ကာ subscribed topics များတွင် messages များကို နားထောင်နေသော background thread တွင် processing loop ကို စတင်ပါသည်။

1. အလုပ်၏ ယခင်အပိုင်းမှ ကုဒ်ကို run လုပ်သည့် နည်းလမ်းတူ run လုပ်ပါ။ အိမ်စီး IoT စက်ပစ္စည်းကို အသုံးပြုနေပါက CounterFit app ကို run လုပ်ထားပြီး အလင်းအာရုံခံကိရိယာနှင့် LED ကို မှန်ကန်သော pins တွင် ဖန်တီးထားကြောင်း သေချာပါ။

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 ဒီကုဒ်ကို [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) folder သို့မဟုတ် [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi) folder တွင် ရှာနိုင်ပါသည်။

😀 သင်၏စက်ပစ္စည်းကို MQTT broker နှင့် အောင်မြင်စွာ ချိတ်ဆက်ပြီးပါပြီ။

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါရှိနိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်ခြင်းကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွဲအချော်များ သို့မဟုတ် အနားယူမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။