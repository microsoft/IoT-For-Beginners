<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-28T17:13:35+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "my"
}
-->
# အင်တာနက်မှ သင့်ညဉ့်မီးကို ထိန်းချုပ်ပါ - Wio Terminal

ဒီသင်ခန်းစာအပိုင်းမှာ သင့် Wio Terminal မှ အလင်းအဆင့်များနှင့် telemetry ကို MQTT broker သို့ ပို့မည်ဖြစ်သည်။

## JSON Arduino libraries ကို ထည့်သွင်းပါ

MQTT မှတဆင့် မက်ဆေ့ချ်များကို ပို့ရန် နည်းလမ်းများထဲမှာ JSON ကို အသုံးပြုခြင်းသည် လူကြိုက်များသော နည်းလမ်းတစ်ခုဖြစ်သည်။ JSON ကို ဖတ်ခြင်းနှင့် ရေးခြင်းကို ပိုမိုလွယ်ကူစေသော Arduino library တစ်ခုလည်း ရှိသည်။

### အလုပ်ပေးချက်

Arduino JSON library ကို ထည့်သွင်းပါ။

1. VS Code မှာ nightlight project ကို ဖွင့်ပါ။

1. `platformio.ini` ဖိုင်ရဲ့ `lib_deps` စာရင်းမှာ အောက်ပါလိုင်းကို ထည့်ပါ။

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    ဒါက [ArduinoJson](https://arduinojson.org) ကို ထည့်သွင်းပေးပြီး Arduino JSON library တစ်ခုဖြစ်သည်။

## Telemetry ကို ပို့ပါ

နောက်တစ်ဆင့်မှာ JSON document တစ်ခုကို telemetry ဖြင့် ဖန်တီးပြီး MQTT broker သို့ ပို့ရမည်ဖြစ်သည်။

### အလုပ်ပေးချက် - telemetry ကို ပို့ပါ

Telemetry ကို MQTT broker သို့ ပို့ပါ။

1. MQTT broker အတွက် telemetry topic name ကို သတ်မှတ်ရန် `config.h` ဖိုင်ရဲ့ အောက်ဆုံးမှာ အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` သည် အလင်းအဆင့်များကို ပို့မည့် topic ဖြစ်သည်။

1. `main.cpp` ဖိုင်ကို ဖွင့်ပါ။

1. ဖိုင်ရဲ့ အပေါ်ဆုံးမှာ အောက်ပါ `#include` directive ကို ထည့်ပါ။

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `loop` function ရဲ့ `delay` မတိုင်မီ အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    ဒီ code က အလင်းအဆင့်ကို ဖတ်ပြီး ArduinoJson ကို အသုံးပြု၍ JSON document တစ်ခုကို ဖန်တီးသည်။ ထို့နောက် string အဖြစ် serialize လုပ်ပြီး telemetry MQTT topic မှတဆင့် MQTT client က publish လုပ်သည်။

1. Code ကို သင့် Wio Terminal သို့ upload လုပ်ပြီး Serial Monitor ကို အသုံးပြု၍ အလင်းအဆင့်များကို MQTT broker သို့ ပို့နေသည်ကို ကြည့်ပါ။

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 ဒီ code ကို [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) folder မှာ ရှာနိုင်ပါတယ်။

😀 သင့် device မှ telemetry ကို အောင်မြင်စွာ ပို့ပြီးပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူရင်းဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူက ဘာသာပြန်မှုကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားယူမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။