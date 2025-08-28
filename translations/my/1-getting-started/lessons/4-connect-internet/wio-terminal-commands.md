<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-28T17:10:59+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "my"
}
-->
# အင်တာနက်မှ သင့်ညဉ့်မီးအိမ်ကို ထိန်းချုပ်ပါ - Wio Terminal

ဒီသင်ခန်းစာအပိုင်းမှာ သင်သည် MQTT broker မှ ပေးပို့သော အမိန့်များကို သင့် Wio Terminal မှ စာရင်းသွင်းပါမည်။

## အမိန့်များကို စာရင်းသွင်းပါ

နောက်တစ်ဆင့်မှာ MQTT broker မှ ပေးပို့သော အမိန့်များကို စာရင်းသွင်းပြီး အမိန့်များကို တုံ့ပြန်ပါမည်။

### လုပ်ဆောင်ရန်

အမိန့်များကို စာရင်းသွင်းပါ။

1. VS Code မှာ nightlight project ကို ဖွင့်ပါ။

1. `config.h` ဖိုင်၏ အောက်ဆုံးတွင် အမိန့်များအတွက် topic name ကို သတ်မှတ်ရန် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` သည် LED အမိန့်များကို လက်ခံရန် စာရင်းသွင်းမည့် topic ဖြစ်သည်။

1. MQTT client ကို ပြန်လည်ချိတ်ဆက်သောအခါ အမိန့် topic ကို စာရင်းသွင်းရန် `reconnectMQTTClient` function ၏ အဆုံးတွင် အောက်ပါလိုင်းကို ထည့်ပါ။

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. `reconnectMQTTClient` function အောက်တွင် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    ဒီ function သည် MQTT client မှ server မှ message လက်ခံသောအခါ ခေါ်သည့် callback ဖြစ်ပါသည်။

    Message ကို unsigned 8-bit integer array အဖြစ် လက်ခံရရှိပြီး၊ text အဖြစ် ဆက်လက်အသုံးပြုရန် character array အဖြစ် ပြောင်းလဲရန် လိုအပ်ပါသည်။

    Message တွင် JSON document ပါဝင်ပြီး၊ ArduinoJson library ကို အသုံးပြု၍ decode လုပ်ပါသည်။ JSON document ၏ `led_on` property ကို ဖတ်ပြီး၊ အတန်းတန်ဖိုးပေါ်မူတည်၍ LED ကို ဖွင့်ခြင်း သို့မဟုတ် ပိတ်ခြင်းကို ဆောင်ရွက်ပါသည်။

1. `createMQTTClient` function တွင် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    client.setCallback(clientCallback);
    ```

    ဒီ code သည် MQTT broker မှ message လက်ခံသောအခါ ခေါ်သည့် callback အဖြစ် `clientCallback` ကို သတ်မှတ်ပါသည်။

    > 💁 `clientCallback` handler သည် စာရင်းသွင်းထားသော topic အားလုံးအတွက် ခေါ်ပါသည်။ နောက်ပိုင်းတွင် မတူညီသော topic များကို နားထောင်ရန် code ရေးသားပါက callback function သို့ ပေးပို့သော `topic` parameter မှ message ပေးပို့ထားသော topic ကို ရယူနိုင်ပါသည်။

1. Code ကို သင့် Wio Terminal သို့ upload လုပ်ပြီး Serial Monitor ကို အသုံးပြု၍ MQTT broker သို့ ပေးပို့သော အလင်းအဆင့်များကို ကြည့်ပါ။

1. သင့်ရုပ်ပိုင်းဆိုင်ရာ device သို့မဟုတ် အိမ်မက် device မှ အလင်းအဆင့်များကို ချိန်ညှိပါ။ Terminal တွင် message လက်ခံခြင်းနှင့် အမိန့်ပေးပို့ခြင်းကို တွေ့ရပါမည်။ အလင်းအဆင့်ပေါ်မူတည်၍ LED ကို ဖွင့်ခြင်းနှင့် ပိတ်ခြင်းကိုလည်း တွေ့ရပါမည်။

> 💁 ဒီ code ကို [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal) folder တွင် ရှာဖွေနိုင်ပါသည်။

😀 သင်သည် MQTT broker မှ အမိန့်များကို တုံ့ပြန်ရန် သင့် device ကို အောင်မြင်စွာ code ရေးသားပြီးဖြစ်ပါသည်။

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေပါသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူလဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။