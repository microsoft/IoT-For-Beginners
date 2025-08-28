<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-28T16:27:40+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "my"
}
-->
# မိုဘိုင်းစက်ပစ္စည်းအတွက် အသံမှ စာသားသို့ - အတု IoT စက်ပစ္စည်း

ဒီသင်ခန်းစာအပိုင်းမှာ သင့်မိုက်ခရိုဖုန်းမှ ဖမ်းယူထားသော အသံကို စာသားအဖြစ် ပြောင်းလဲရန် အသံဝန်ဆောင်မှုကို အသုံးပြု၍ ကုဒ်ရေးသားပါမည်။

## အသံမှ စာသားသို့ ပြောင်းလဲခြင်း

Windows, Linux, နှင့် macOS ပေါ်တွင် အသံဝန်ဆောင်မှု Python SDK ကို အသုံးပြု၍ သင့်မိုက်ခရိုဖုန်းကို နားထောင်ပြီး ဖမ်းမိသော အသံအားလုံးကို စာသားအဖြစ် ပြောင်းလဲနိုင်သည်။ ၎င်းသည် ဆက်တိုက်နားထောင်ပြီး အသံအဆင့်များကို စစ်ဆေးကာ အသံအဆင့်ကျသွားသောအခါ (ဥပမာ - စကားတစ်ပိုင်းအဆုံးတွင်) အသံကို စာသားအဖြစ် ပြောင်းရန် ပို့ပေးပါမည်။

### လုပ်ငန်း - အသံမှ စာသားသို့ ပြောင်းခြင်း

1. သင့်ကွန်ပျူတာတွင် `smart-timer` ဟုခေါ်သော ဖိုလ်ဒါတစ်ခုတွင် `app.py` ဟုခေါ်သော ဖိုင်တစ်ခုနှင့် Python အထူးပတ်ဝန်းကျင်တစ်ခုဖြင့် Python အက်ပ်အသစ်တစ်ခု ဖန်တီးပါ။

1. အသံဝန်ဆောင်မှုများအတွက် Pip package ကို ထည့်သွင်းပါ။ အထူးပတ်ဝန်းကျင်ကို အက်တိဗိတ်လုပ်ထားသော terminal မှ ထည့်သွင်းရမည်ဖြစ်သည်။

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ အောက်ပါအမှားကို ကြုံရပါက:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Pip ကို အပ်ဒိတ်လုပ်ရန် လိုအပ်ပါမည်။ အောက်ပါ command ကို အသုံးပြု၍ ပြုလုပ်ပါ၊ ထို့နောက် package ကို ထပ်မံထည့်သွင်းပါ။
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. `app.py` ဖိုင်တွင် အောက်ပါ imports များကို ထည့်ပါ:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    ၎င်းသည် အသံကို အသိအမှတ်ပြုရန် အသုံးပြုမည့် class များကို import လုပ်ပါသည်။

1. အောက်ပါကုဒ်ကို ထည့်၍ အချို့သော configuration များကို ကြေညာပါ:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    `<key>` ကို သင့်အသံဝန်ဆောင်မှု၏ API key ဖြင့် အစားထိုးပါ။ `<location>` ကို သင်အသံဝန်ဆောင်မှု resource ကို ဖန်တီးခဲ့သောနေရာဖြင့် အစားထိုးပါ။

    `<language>` ကို သင်ပြောမည့်ဘာသာစကား၏ locale name ဖြင့် အစားထိုးပါ၊ ဥပမာ `en-GB` သည် အင်္ဂလိပ်ဘာသာစကား၊ `zn-HK` သည် Cantonese ဖြစ်သည်။ Microsoft docs တွင် [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) တွင် ပံ့ပိုးထားသော ဘာသာစကားများနှင့် ၎င်းတို့၏ locale name များကို ရှာဖွေနိုင်ပါသည်။

    ဤ configuration ကို အသံဝန်ဆောင်မှုများကို configure ပြုလုပ်ရန် အသုံးပြုမည့် `SpeechConfig` object တစ်ခု ဖန်တီးရန် အသုံးပြုပါမည်။

1. အသံအသိအမှတ်ပြုစက်တစ်ခု ဖန်တီးရန် အောက်ပါကုဒ်ကို ထည့်ပါ:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. အသံအသိအမှတ်ပြုစက်သည် နောက်ခံ thread ပေါ်တွင် လည်ပတ်ပြီး အသံကို နားထောင်ကာ ၎င်းတွင်ပါဝင်သော အသံအား စာသားအဖြစ် ပြောင်းလဲပါသည်။ သင့်အနေဖြင့် callback function တစ်ခုကို သတ်မှတ်ပြီး recognizer သို့ ပေးပို့ကာ အသံတွေ့ရှိတိုင်း callback ကို ခေါ်နိုင်သည်။ အောက်ပါကုဒ်ကို ထည့်၍ callback ကို သတ်မှတ်ပြီး recognizer သို့ ပေးပို့ပါ၊ ထို့အပြင် စာသားကို console တွင် ရေးသားရန် function တစ်ခုကို သတ်မှတ်ပါ:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. recognizer သည် သင်တစ်ဦးတည်းစတင်မလုပ်မီ နားထောင်မှုကို စတင်မည်မဟုတ်ပါ။ recognizer ကို စတင်ရန် အောက်ပါကုဒ်ကို ထည့်ပါ။ ၎င်းသည် နောက်ခံတွင် လည်ပတ်မည်ဖြစ်ပြီး သင့်အက်ပ်လိပ်စာကို လည်ပတ်နေစေရန် အဆုံးမဲ့ loop တစ်ခုကို sleep ဖြင့် ထည့်သွင်းရန် လိုအပ်ပါမည်။

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. ဤအက်ပ်ကို လည်ပတ်ပါ။ သင့်မိုက်ခရိုဖုန်းထဲသို့ ပြောဆိုပါ၊ ပြောင်းလဲထားသော အသံကို စာသားအဖြစ် console တွင် output ပြုလုပ်ပါမည်။

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    အမျိုးမျိုးသော စာကြောင်းများကို စမ်းသပ်ပါ၊ ထို့အပြင် အသံတူသော်လည်း အဓိပ္ပါယ်ကွဲသော စကားလုံးများပါဝင်သော စာကြောင်းများကိုလည်း စမ်းသပ်ပါ။ ဥပမာ - သင်အင်္ဂလိပ်ဘာသာစကားဖြင့် ပြောဆိုပါက 'I want to buy two bananas and an apple too' ဟု ပြောပါ၊ ၎င်းသည် စကားလုံး၏ အသံသာမက ၎င်း၏ အကြောင်းအရာအပေါ်မူတည်၍ to, two, too တို့ကို မှန်ကန်စွာ အသုံးပြုမည်ဖြစ်သည်။

> 💁 ဤကုဒ်ကို [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) ဖိုလ်ဒါတွင် ရှာဖွေနိုင်ပါသည်။

😀 သင်၏ အသံမှ စာသားသို့ ပြောင်းလဲသော အစီအစဉ်အောင်မြင်ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေပါသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်ခြင်းကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွဲအချော်အချော်များ သို့မဟုတ် အနားယူမှုမှားများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။