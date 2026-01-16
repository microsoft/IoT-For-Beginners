<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-28T16:39:29+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "my"
}
-->
# စကားပြောဘာသာပြန်ခြင်း - အွန်လိုင်း IoT စက်ပစ္စည်း

ဒီသင်ခန်းစာအပိုင်းမှာ သင် speech service ကို အသုံးပြုပြီး စကားပြောကို စာသားအဖြစ်ပြောင်းလဲပြီးနောက် ဘာသာပြန်ခြင်းလုပ်ဆောင်ရန် ကုဒ်ရေးသားပါမည်။ ထို့နောက် Translator service ကို အသုံးပြုပြီး စာသားကို ဘာသာပြန်ပြီး အသံဖြင့် ပြန်လည်ထုတ်ပေးပါမည်။

## Speech Service ကို အသုံးပြုပြီး စကားပြောကို ဘာသာပြန်ခြင်း

Speech service သည် စကားပြောကို မူလဘာသာစကားအတိုင်း စာသားအဖြစ်ပြောင်းလဲနိုင်သလို၊ အခြားဘာသာစကားများသို့လည်း ဘာသာပြန်နိုင်သည်။

### လုပ်ဆောင်ရန် - Speech Service ကို အသုံးပြုပြီး စကားပြောကို ဘာသာပြန်ခြင်း

1. `smart-timer` project ကို VS Code မှာ ဖွင့်ပြီး terminal မှာ virtual environment ကို load လုပ်ထားပါ။

1. ရှိပြီးသား import statements အောက်တွင် အောက်ပါ import statements ကို ထည့်ပါ။

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    ဒီမှာ speech ဘာသာပြန်ခြင်းနှင့် ပတ်သက်သော classes များနှင့် `requests` library ကို import လုပ်ထားသည်။ ဒီ library ကို သင်ခန်းစာနောက်ပိုင်းတွင် Translator service ကို ခေါ်ရန် အသုံးပြုမည်။

1. သင့် smart timer တွင် ဘာသာစကား ၂ မျိုး သတ်မှတ်ထားမည် - LUIS ကို သင်ကြားရန် အသုံးပြုသော server ဘာသာစကား (user နှင့် ဆက်သွယ်ရန် အသုံးပြုသော စာသားများကို ဖန်တီးရန်လည်း အသုံးပြုသည်) နှင့် user ပြောသော ဘာသာစကား။ `language` variable ကို user ပြောမည့် ဘာသာစကားအဖြစ် update လုပ်ပြီး `server_language` variable ကို LUIS ကို သင်ကြားရန် အသုံးပြုသော ဘာသာစကားအဖြစ် ထည့်ပါ။

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` ကို သင့်ပြောမည့် ဘာသာစကား၏ locale name ဖြင့် အစားထိုးပါ။ ဥပမာ `fr-FR` သည် ပြင်သစ်ဘာသာစကား၊ `zn-HK` သည် Cantonese ဖြစ်သည်။

    `<server language>` ကို LUIS ကို သင်ကြားရန် အသုံးပြုသော ဘာသာစကား၏ locale name ဖြင့် အစားထိုးပါ။

    Microsoft docs တွင် [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) တွင် locale names များကို ရှာနိုင်ပါသည်။

    > 💁 သင် ဘာသာစကားများ မပြောတတ်ပါက [Bing Translate](https://www.bing.com/translator) သို့မဟုတ် [Google Translate](https://translate.google.com) ကဲ့သို့သော ဝန်ဆောင်မှုများကို အသုံးပြုနိုင်ပါသည်။ ဒီဝန်ဆောင်မှုများသည် ဘာသာပြန်ထားသော စာသားကို အသံဖြင့် ထုတ်ပေးနိုင်ပါသည်။ သို့သော် speech recognizer သည် သင့်စက်၏ အသံ output အချို့ကို မသိရှိနိုင်ပါက အပိုစက်တစ်လုံးကို အသုံးပြုရန် လိုအပ်နိုင်ပါသည်။
    >
    > ဥပမာအားဖြင့် LUIS ကို အင်္ဂလိပ်ဘာသာစကားဖြင့် သင်ကြားပြီး user ဘာသာစကားအဖြစ် ပြင်သစ်ကို အသုံးပြုလိုပါက "set a 2 minute and 27 second timer" ကဲ့သို့သော စာကြောင်းများကို Bing Translate ဖြင့် ပြင်သစ်ဘာသာစကားသို့ ဘာသာပြန်ပြီး **Listen translation** ခလုတ်ကို အသုံးပြု၍ သင့်မိုက်ခရိုဖုန်းထဲသို့ ပြောနိုင်ပါသည်။
    >
    > ![Bing Translate တွင် Listen translation ခလုတ်](../../../../../translated_images/my/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. `recognizer_config` နှင့် `recognizer` ကို အောက်ပါအတိုင်း အစားထိုးပါ။

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    ဒီမှာ user ဘာသာစကားကို အသိအမှတ်ပြုရန် translation config တစ်ခု ဖန်တီးပြီး user နှင့် server ဘာသာစကားများသို့ ဘာသာပြန်ရန် ဖန်တီးထားသည်။ ထို့နောက် ဒီ config ကို အသုံးပြုပြီး translation recognizer တစ်ခု ဖန်တီးထားသည်။

    > 💁 `target_languages` တွင် မူလဘာသာစကားကို သတ်မှတ်ရန် လိုအပ်သည်။ မဟုတ်ပါက ဘာသာပြန်မှု မရနိုင်ပါ။

1. `recognized` function ကို အောက်ပါအတိုင်း အစားထိုးပါ။

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    ဒီကုဒ်သည် recognized event သည် speech ဘာသာပြန်မှုကြောင့် ဖြစ်ပေါ်ခဲ့သည်ကို စစ်ဆေးသည်။ speech ဘာသာပြန်မှုဖြစ်ပါက `args.result.translations` dictionary ထဲမှ server ဘာသာစကားနှင့် ကိုက်ညီသော ဘာသာပြန်မှုကို ရှာဖွေသည်။

    `args.result.translations` dictionary သည် locale setting ၏ language အပိုင်းကိုသာ key အဖြစ် အသုံးပြုသည်။ ဥပမာအားဖြင့် `fr-FR` ကို ပြင်သစ်ဘာသာစကားအဖြစ် သတ်မှတ်ပါက dictionary တွင် `fr` entry ကိုသာ ပါမည်။

    ဘာသာပြန်ထားသော စာသားကို IoT Hub သို့ ပို့သည်။

1. ဒီကုဒ်ကို run လုပ်ပြီး ဘာသာပြန်မှုကို စမ်းသပ်ပါ။ သင့် function app ကို run လုပ်ထားပြီး user ဘာသာစကားဖြင့် timer တစ်ခုကို တောင်းဆိုပါ။ သင်ကိုယ်တိုင် ပြောခြင်းဖြစ်စေ၊ translation app ကို အသုံးပြုခြင်းဖြစ်စေ။

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Translator Service ကို အသုံးပြုပြီး စာသားကို ဘာသာပြန်ခြင်း

Speech service သည် စာသားကို ပြန်လည် အသံထုတ်ပေးရန် မပံ့ပိုးပါ။ ထို့အစား Translator service ကို အသုံးပြုနိုင်သည်။ ဒီ service တွင် REST API တစ်ခု ပါရှိသည်။

### လုပ်ဆောင်ရန် - Translator Resource ကို အသုံးပြုပြီး စာသားကို ဘာသာပြန်ခြင်း

1. `speech_api_key` အောက်တွင် translator API key ကို ထည့်ပါ။

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` ကို သင့် translator service resource ၏ API key ဖြင့် အစားထိုးပါ။

1. `say` function အထက်တွင် `translate_text` function ကို သတ်မှတ်ပါ။ ဒီ function သည် server ဘာသာစကားမှ user ဘာသာစကားသို့ စာသားကို ဘာသာပြန်မည်။

    ```python
    def translate_text(text):
    ```

1. ဒီ function အတွင်း REST API call အတွက် URL နှင့် headers ကို သတ်မှတ်ပါ။

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    ဒီ API ၏ URL သည် တည်နေရာပေါ်မူတည်ခြင်းမရှိပါ။ တည်နေရာကို header အဖြစ် ပေးပို့သည်။ API key ကို တိုက်ရိုက် အသုံးပြုသည်။

1. အောက်တွင် call အတွက် parameters နှင့် body ကို သတ်မှတ်ပါ။

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` သည် API call အတွက် parameters များကို သတ်မှတ်သည်။ `from` ဘာသာစကားမှ `to` ဘာသာစကားသို့ ဘာသာပြန်မည်။

    `body` သည် ဘာသာပြန်ရန် စာသားကို ပါဝင်သည်။ ဒါသည် array ဖြစ်ပြီး စာသားအပိုင်းများစွာကို တစ်ခါတည်း ဘာသာပြန်နိုင်သည်။

1. REST API ကို call လုပ်ပြီး response ကို ရယူပါ။

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    ပြန်လာသော response သည် JSON array ဖြစ်ပြီး ဘာသာပြန်မှုများပါဝင်သည်။

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. array ၏ ပထမ item မှ ပထမ ဘာသာပြန်မှု၏ `text` property ကို return ပြန်ပါ။

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `say` function ကို update လုပ်ပြီး SSML ဖန်တီးမီ ပြောရန် စာသားကို ဘာသာပြန်ပါ။

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    ဒီကုဒ်သည် မူလစာသားနှင့် ဘာသာပြန်ထားသော စာသားကို console တွင် print ပြပါမည်။

1. သင့်ကုဒ်ကို run လုပ်ပါ။ သင့် function app ကို run လုပ်ထားပြီး user ဘာသာစကားဖြင့် timer တစ်ခုကို တောင်းဆိုပါ။ သင်ကိုယ်တိုင် ပြောခြင်းဖြစ်စေ၊ translation app ကို အသုံးပြုခြင်းဖြစ်စေ။

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 ဘာသာစကားအလိုက် ပြောဆိုပုံကွဲခြားမှုများကြောင့် LUIS သို့ ပေးထားသော ဥပမာများနှင့် မတူညီသော ဘာသာပြန်မှုများ ရနိုင်ပါသည်။ ဒီလိုဖြစ်ပါက LUIS တွင် ဥပမာများ ထပ်ထည့်ပြီး ပြန်လည်သင်ကြားပြီး model ကို ပြန်လည်ထုတ်ဝေပါ။

> 💁 ဒီကုဒ်ကို [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) folder တွင် ရှာနိုင်ပါသည်။

😀 သင့် multilingual timer program အောင်မြင်ခဲ့ပါပြီ!

---

**ဝက်ဘ်ဆိုက်မှတ်ချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှန်ကန်မှုအတွက် ကြိုးစားနေပါသော်လည်း၊ အလိုအလျောက်ဘာသာပြန်ဆိုမှုများတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါဝင်နိုင်သည်ကို ကျေးဇူးပြု၍ သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူလဘာသာစကားဖြင့် အာဏာတည်သောရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူက ဘာသာပြန်ဆိုမှုကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်ဆိုမှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော နားလည်မှုမှားမှုများ သို့မဟုတ် အဓိပ္ပါယ်မှားမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။