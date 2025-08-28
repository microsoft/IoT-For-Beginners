<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-28T17:12:57+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "my"
}
-->
# အင်တာနက်မှ သင့်ညဉ့်မီးကို ထိန်းချုပ်ပါ - အတု IoT ဟာ့ဒ်ဝဲနှင့် Raspberry Pi

ဒီသင်ခန်းစာပိုင်းမှာ သင်သည် MQTT broker မှ သင့် Raspberry Pi သို့မဟုတ် အတု IoT စက်ပစ္စည်းသို့ ပေးပို့သော အမိန့်များကို စာရင်းသွင်းပါမည်။

## အမိန့်များကို စာရင်းသွင်းပါ

နောက်တစ်ဆင့်မှာ MQTT broker မှ ပေးပို့သော အမိန့်များကို စာရင်းသွင်းပြီး အဲဒီအမိန့်များကို တုံ့ပြန်ပါမည်။

### တာဝန်

အမိန့်များကို စာရင်းသွင်းပါ။

1. VS Code တွင် nightlight project ကို ဖွင့်ပါ။

1. သင်အတု IoT စက်ပစ္စည်းကို အသုံးပြုနေပါက terminal သည် virtual environment ကို run လုပ်နေကြောင်း သေချာစေပါ။ သင် Raspberry Pi ကို အသုံးပြုနေပါက virtual environment ကို အသုံးမပြုရပါ။

1. `client_telemetry_topic` ကို သတ်မှတ်ထားသော နောက်တွင် အောက်ပါကုဒ်ကို ထည့်ပါ-

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` သည် စက်ပစ္စည်းသည် LED အမိန့်များကို လက်ခံရန် စာရင်းသွင်းမည့် MQTT topic ဖြစ်သည်။

1. `mqtt_client.loop_start()` လိုင်း၏ အပေါ်တွင်၊ main loop မစတင်မီ အောက်ပါကုဒ်ကို ထည့်ပါ-

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    ဒီကုဒ်သည် `handle_command` ဟုခေါ်သော function တစ်ခုကို သတ်မှတ်ပြီး၊ JSON စာရွက်စာတမ်းအဖြစ် message ကို ဖတ်ပြီး `led_on` property ၏ တန်ဖိုးကို ရှာဖွေပါသည်။ အကယ်၍ `True` သတ်မှတ်ထားပါက LED ကို ဖွင့်မည်ဖြစ်ပြီး၊ မဟုတ်ပါက LED ကို ပိတ်မည်ဖြစ်သည်။

    MQTT client သည် server မှ message ပေးပို့မည့် topic ကို စာရင်းသွင်းပြီး၊ message လက်ခံသောအခါ `handle_command` function ကို ခေါ်ရန် သတ်မှတ်ထားသည်။

    > 💁 `on_message` handler သည် စာရင်းသွင်းထားသော topic အားလုံးအတွက် ခေါ်ခံရသည်။ နောက်ပိုင်းတွင် သင်သည် topics များစွာကို နားထောင်ရန် ကုဒ်ရေးပါက၊ message object မှ message ပေးပို့ထားသော topic ကို ရယူနိုင်သည်။

1. ယခင်အလုပ်အပိုင်းမှ ကုဒ်ကို run လုပ်သည့် နည်းလမ်းအတိုင်း ကုဒ်ကို run လုပ်ပါ။ သင်အတု IoT စက်ပစ္စည်းကို အသုံးပြုနေပါက CounterFit app သည် run လုပ်နေပြီး၊ light sensor နှင့် LED ကို မှန်ကန်သော pin များတွင် ဖန်တီးထားကြောင်း သေချာစေပါ။

1. သင့်ရဲ့ ရုပ်ပိုင်းဆိုင်ရာ သို့မဟုတ် အတုစက်ပစ္စည်းမှ သိရှိသော အလင်းအဆင့်များကို ချိန်ညှိပါ။ လက်ခံနေသော message များနှင့် ပေးပို့နေသော အမိန့်များကို terminal တွင် ရေးသားထားမည်ဖြစ်သည်။ အလင်းအဆင့်ပေါ်မူတည်၍ LED ကိုလည်း ဖွင့်/ပိတ် လုပ်မည်ဖြစ်သည်။

> 💁 ဒီကုဒ်ကို [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) folder သို့မဟုတ် [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi) folder တွင် ရှာဖွေနိုင်ပါသည်။

😀 သင်၏စက်ပစ္စည်းကို MQTT broker မှ အမိန့်များကို တုံ့ပြန်စေရန် အောင်မြင်စွာ ကုဒ်ရေးပြီးဖြစ်ပါသည်။

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါရှိနိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် ရှုလေ့လာသင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်ခြင်းကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။