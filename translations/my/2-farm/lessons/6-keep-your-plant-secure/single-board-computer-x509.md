<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-28T17:58:58+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "my"
}
-->
# X.509 လက်မှတ်ကို သင့်စက်ကိရိယာကုဒ်တွင် အသုံးပြုခြင်း - အတု IoT Hardware နှင့် Raspberry Pi

ဒီသင်ခန်းပိုင်းမှာ သင့်အတု IoT စက်ကိရိယာ သို့မဟုတ် Raspberry Pi ကို X.509 လက်မှတ်ကို အသုံးပြုပြီး IoT Hub နှင့် ချိတ်ဆက်ပါမည်။

## သင့်စက်ကိရိယာကို IoT Hub နှင့် ချိတ်ဆက်ပါ

နောက်တစ်ဆင့်မှာ X.509 လက်မှတ်များကို အသုံးပြုပြီး သင့်စက်ကိရိယာကို IoT Hub နှင့် ချိတ်ဆက်ရမည်ဖြစ်သည်။

### အလုပ်ပေးချက် - IoT Hub နှင့် ချိတ်ဆက်ပါ

1. သင့် IoT စက်ကိရိယာကုဒ်ရှိ ဖိုလ်ဒါထဲသို့ key နှင့် လက်မှတ်ဖိုင်များကို ကူးထည့်ပါ။ သင်သည် Raspberry Pi ကို VS Code Remote SSH မှတဆင့် အသုံးပြုပြီး သင့် PC သို့မဟုတ် Mac တွင် key များကို ဖန်တီးထားပါက ဖိုင်များကို VS Code ရှိ explorer ထဲသို့ ဆွဲချပြီး ကူးထည့်နိုင်ပါသည်။

1. `app.py` ဖိုင်ကို ဖွင့်ပါ။

1. X.509 လက်မှတ်ကို အသုံးပြုပြီး ချိတ်ဆက်ရန် IoT Hub ၏ host name နှင့် X.509 လက်မှတ်လိုအပ်ပါမည်။ စက်ကိရိယာ client ကို ဖန်တီးမည့်အခါ မတိုင်မီ host name ကို ထည့်သွင်းထားသော variable ကို ဖန်တီးရန် အောက်ပါကုဒ်ကို ထည့်ပါ:

    ```python
    host_name = "<host_name>"
    ```

    `<host_name>` ကို သင့် IoT Hub ၏ host name ဖြင့် အစားထိုးပါ။ သင်သည် `connection_string` ရှိ `HostName` အပိုင်းမှ ယူနိုင်ပါသည်။ ၎င်းသည် `.azure-devices.net` ဖြင့် အဆုံးသတ်သော သင့် IoT Hub ၏ နာမည်ဖြစ်ပါမည်။

1. အထက်ပါကုဒ်အောက်တွင် device ID ကို ထည့်သွင်းထားသော variable ကို ဖန်တီးပါ:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. X.509 ဖိုင်များပါဝင်သော `X509` class ၏ instance တစ်ခုလိုအပ်ပါမည်။ `azure.iot.device` module မှ imported classes များစာရင်းထဲသို့ `X509` ကို ထည့်ပါ:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. သင့်လက်မှတ်နှင့် key ဖိုင်များကို အသုံးပြု၍ `X509` class instance ကို ဖန်တီးရန် `host_name` ထည့်သွင်းထားသောနေရာအောက်တွင် အောက်ပါကုဒ်ကို ထည့်ပါ:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    ၎င်းသည် `soil-moisture-sensor-x509-cert.pem` နှင့် `soil-moisture-sensor-x509-key.pem` ဖိုင်များကို အသုံးပြု၍ `X509` class ကို ဖန်တီးပါမည်။

1. connection string ကို အသုံးပြု၍ `device_client` ကို ဖန်တီးထားသော ကုဒ်လိုင်းကို အောက်ပါကုဒ်ဖြင့် အစားထိုးပါ:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    ၎င်းသည် connection string အစား X.509 လက်မှတ်ကို အသုံးပြု၍ ချိတ်ဆက်ပါမည်။

1. `connection_string` variable ပါသော ကုဒ်လိုင်းကို ဖျက်ပါ။

1. သင့်ကုဒ်ကို run လုပ်ပါ။ IoT Hub သို့ ပို့သော message များကို ကြည့်ရှုပြီး အရင်ကလို direct method requests များကို ပို့ပါ။ စက်ကိရိယာသည် ချိတ်ဆက်ပြီး မြေစိုထိုင်းမှု reading များကို ပို့ခြင်းနှင့် direct method requests များကို လက်ခံခြင်းကို တွေ့ရပါမည်။

> 💁 သင်ဤကုဒ်ကို [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) သို့မဟုတ် [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device) ဖိုလ်ဒါတွင် ရှာနိုင်ပါသည်။

😀 သင့်မြေစိုထိုင်းမှု sensor အစီအစဉ်သည် X.509 လက်မှတ်ကို အသုံးပြုပြီး IoT Hub နှင့် ချိတ်ဆက်ပြီးပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူရင်းဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။