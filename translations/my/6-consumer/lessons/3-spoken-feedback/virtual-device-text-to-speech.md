<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-28T16:17:09+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "my"
}
-->
# Text to speech - အတု IoT စက်ပစ္စည်း

ဒီသင်ခန်းစာအပိုင်းမှာ သင်သည် စကားကို အသံအဖြစ် ပြောင်းလဲရန် speech service ကို အသုံးပြု၍ ကုဒ်ရေးမည်။

## စကားကို အသံအဖြစ် ပြောင်းလဲခြင်း

မကြာသေးမီ သင်ခန်းစာတွင် စကားကို အသံအဖြစ် ပြောင်းလဲရန် အသုံးပြုခဲ့သော speech services SDK ကို အသံကို ပြန်လည် စကားအဖြစ် ပြောင်းလဲရန် အသုံးပြုနိုင်သည်။ အသံတောင်းဆိုရာတွင် အသံဖန်တီးရန် အသုံးပြုမည့် အသံကို သတ်မှတ်ပေးရန် လိုအပ်သည်။

အသံဖန်တီးနိုင်သော အသံများသည် ဘာသာစကားတစ်ခုစီအတွက် မတူကွဲပြားပြီး speech services SDK မှ ဘာသာစကားတစ်ခုစီအတွက် ထောက်ပံ့ထားသော အသံများစာရင်းကို ရယူနိုင်သည်။

### လုပ်ငန်း - စကားကို အသံအဖြစ် ပြောင်းလဲခြင်း

1. `smart-timer` project ကို VS Code တွင် ဖွင့်ပြီး terminal တွင် virtual environment ကို load လုပ်ထားပါ။

1. `azure.cognitiveservices.speech` package မှ `SpeechSynthesizer` ကို ရှိပြီးသား imports တွင် ထည့်သွင်းပါ။

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. `say` function အပေါ်တွင် speech synthesizer အတွက် အသုံးပြုမည့် speech configuration ကို ဖန်တီးပါ။

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    ဒါဟာ recognizer မှ အသုံးပြုခဲ့သော API key, location နှင့် language တူညီသည်။

1. ဒီအောက်တွင် အသံတစ်ခုကို ရယူပြီး speech config တွင် သတ်မှတ်ရန် အောက်ပါကုဒ်ကို ထည့်ပါ။

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    ဒါဟာ ရရှိနိုင်သော အသံများစာရင်းအားလုံးကို ရယူပြီး အသုံးပြုနေသော ဘာသာစကားနှင့် ကိုက်ညီသော ပထမဆုံးအသံကို ရှာဖွေသည်။

    > 💁 Microsoft Docs တွင် [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) မှ ထောက်ပံ့ထားသော အသံများစာရင်းအားလုံးကို ရယူနိုင်သည်။ သင်တစ်ခုခုကို သတ်မှတ်ထားသော အသံကို အသုံးပြုလိုပါက ဒီ function ကို ဖယ်ရှားပြီး documentation မှ voice name ကို hard code လုပ်နိုင်သည်။ ဥပမာ:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. `say` function ၏ အကြောင်းအရာများကို SSML ဖန်တီးရန် update လုပ်ပါ။

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. ဒီအောက်တွင် speech recognition ကို ရပ်ထားပြီး SSML ကို ပြောဆိုပါ၊ ပြီးလျှင် recognition ကို ပြန်စတင်ပါ။

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    စကားပြောနေစဉ် timer စတင်ခြင်းကို အသံထွက်မပြုရန် recognition ကို ရပ်ထားသည်။ ဒါဟာ LUIS သို့ ပို့ပေးပြီး အသစ်သော timer တစ်ခုကို သတ်မှတ်ရန် တောင်းဆိုမှုအဖြစ် အလွဲသတ်မှတ်ခြင်းကို ရှောင်ရှားရန်ဖြစ်သည်။

    > 💁 recognition ရပ်ထားခြင်းနှင့် ပြန်စတင်ခြင်းကို comment ထည့်ပြီး စမ်းသပ်နိုင်သည်။ timer တစ်ခုကို သတ်မှတ်ပြီး သင်တွေ့ရမည်မှာ timer စတင်ခြင်းကို အသံထွက်ပြောဆိုပြီး အသစ်သော timer တစ်ခုကို သတ်မှတ်ခြင်းဖြစ်သည်။ ဒါဟာ အသံထွက်ပြောဆိုမှုများနှင့် timer အသစ်များကို အဆုံးမရှိအတိုင်း ဆက်လက်လုပ်ဆောင်သွားမည်။

1. app ကို run လုပ်ပြီး function app ကိုလည်း run လုပ်ထားပါ။ timer များကို သတ်မှတ်ပြီး သင်၏ timer သတ်မှတ်ပြီးကြောင်း အသံထွက်ပြောဆိုမှုကို ကြားရမည်။ timer ပြီးဆုံးသောအခါ အသံထွက်ပြောဆိုမှုတစ်ခုကိုလည်း ကြားရမည်။

> 💁 ဒီကုဒ်ကို [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) folder တွင် ရှာနိုင်သည်။

😀 သင်၏ timer program အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် ရှုလေ့လာသင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူက ဘာသာပြန်မှု ဝန်ဆောင်မှုကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားယူမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။