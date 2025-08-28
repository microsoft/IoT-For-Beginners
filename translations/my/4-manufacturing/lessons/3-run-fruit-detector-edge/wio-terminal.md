<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-28T16:04:28+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "my"
}
-->
# IoT Edge အခြေခံ Image Classifier - Wio Terminal ကို အသုံးပြု၍ ပုံတစ်ပုံကို ခွဲခြားခြင်း

ဒီသင်ခန်းစာအပိုင်းမှာ၊ သင်သည် IoT Edge စက်ပစ္စည်းပေါ်တွင် လည်ပတ်နေသော Image Classifier ကို အသုံးပြုမည်ဖြစ်သည်။

## IoT Edge Classifier ကို အသုံးပြုပါ

IoT စက်ပစ္စည်းကို IoT Edge Image Classifier ကို အသုံးပြုရန် ပြောင်းလဲနိုင်သည်။ Image Classifier အတွက် URL သည် `http://<IP address or name>/image` ဖြစ်ပြီး `<IP address or name>` ကို IoT Edge လည်ပတ်နေသော ကွန်ပျူတာ၏ IP လိပ်စာ သို့မဟုတ် host name ဖြင့် အစားထိုးပါ။

### အလုပ် - IoT Edge Classifier ကို အသုံးပြုပါ

1. `fruit-quality-detector` app project ကို ဖွင့်ထားမရှိသေးပါက ဖွင့်ပါ။

1. Image Classifier သည် HTTP ကို အသုံးပြုသော REST API အနေဖြင့် လည်ပတ်နေပြီး HTTPS မဟုတ်ပါ။ ထို့ကြောင့် WiFi client သည် HTTP calls တွင်သာ အလုပ်လုပ်နိုင်ရမည်ဖြစ်သည်။ အဆိုပါ client အတွက် certificate မလိုအပ်ပါ။ `config.h` ဖိုင်မှ `CERTIFICATE` ကို ဖျက်ပါ။

1. `config.h` ဖိုင်ရှိ prediction URL ကို အသစ်သော URL သို့ ပြောင်းလဲရန် လိုအပ်ပါသည်။ `PREDICTION_KEY` ကိုလည်း ဖျက်ပစ်နိုင်သည်၊ အဲဒါမလိုအပ်ပါ။

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    `<URL>` ကို သင့် classifier အတွက် URL ဖြင့် အစားထိုးပါ။

1. `main.cpp` တွင် WiFi Client Secure အတွက် include directive ကို standard HTTP version ကို import ပြောင်းပါ:

    ```cpp
    #include <WiFiClient.h>
    ```

1. `WiFiClient` ကို standard HTTP version အဖြစ် ပြောင်းလဲကြေညာပါ:

    ```cpp
    WiFiClient client;
    ```

1. WiFi client တွင် certificate ကို သတ်မှတ်ထားသော line ကို ရွေးပါ။ `connectWiFi` function မှ `client.setCACert(CERTIFICATE);` line ကို ဖျက်ပါ။

1. `classifyImage` function တွင် header ထဲတွင် prediction key ကို သတ်မှတ်ထားသော `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` line ကို ဖျက်ပါ။

1. သင့် code ကို upload လုပ်ပြီး run လုပ်ပါ။ ကင်မရာကို သစ်သီးတစ်ခုခုဆီသို့ ဦးတည်ပြီး C ခလုတ်ကို နှိပ်ပါ။ Serial monitor တွင် output ကို မြင်ရပါမည်:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 ဒီ code ကို [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) folder တွင် ရှာနိုင်ပါသည်။

😀 သင့် fruit quality classifier program အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူရင်းဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် ရှုလေ့လာသင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူက ဘာသာပြန်မှုကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားယူမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။