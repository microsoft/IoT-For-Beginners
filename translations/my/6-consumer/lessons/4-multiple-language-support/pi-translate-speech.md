<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-28T16:38:39+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "my"
}
-->
# စကားပြောကို ဘာသာပြန်ခြင်း - Raspberry Pi

ဒီသင်ခန်းစာရဲ့ အပိုင်းမှာ သင်ဘာသာပြန်ဝန်ဆောင်မှုကို အသုံးပြုပြီး စာသားကို ဘာသာပြန်ဖို့ ကုဒ်ရေးပါမည်။

## ဘာသာပြန်ဝန်ဆောင်မှုကို အသုံးပြု၍ စကားပြောကို စာသားအဖြစ် ပြောင်းခြင်း

Speech service REST API သည် တိုက်ရိုက်ဘာသာပြန်ခြင်းကို မပံ့ပိုးပါ၊ ဒါကြောင့် Speech to Text service မှ ထုတ်လုပ်ထားသော စာသားနှင့် ပြန်ပြောသော စကားပြောစာသားကို ဘာသာပြန်ရန် Translator service ကို အသုံးပြုနိုင်ပါသည်။ ဒီဝန်ဆောင်မှုတွင် စာသားကို ဘာသာပြန်ရန် အသုံးပြုနိုင်သော REST API ရှိပါသည်။

### လုပ်ငန်း - Translator resource ကို အသုံးပြု၍ စာသားကို ဘာသာပြန်ခြင်း

1. သင့် smart timer တွင် ဘာသာစကား ၂ မျိုး သတ်မှတ်ထားမည် - LUIS ကို သင်ကြားရန် အသုံးပြုသော server ဘာသာစကား (user ကို ပြောရန် message များကို ဖန်တီးရန်လည်း အဲဒီဘာသာစကားကို အသုံးပြုသည်) နှင့် user ပြောသော ဘာသာစကား။ `language` variable ကို user ပြောမည့် ဘာသာစကားအဖြစ် update လုပ်ပြီး `server_language` variable အသစ်တစ်ခုကို LUIS ကို သင်ကြားရန် အသုံးပြုသော ဘာသာစကားအဖြစ် ထည့်ပါ။

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` ကို သင့်ပြောမည့် ဘာသာစကား၏ locale name ဖြင့် အစားထိုးပါ၊ ဥပမာ `fr-FR` သည် French အတွက်၊ `zn-HK` သည် Cantonese အတွက်။

    `<server language>` ကို LUIS ကို သင်ကြားရန် အသုံးပြုသော ဘာသာစကား၏ locale name ဖြင့် အစားထိုးပါ။

    Microsoft docs တွင် [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) တွင် ပံ့ပိုးထားသော ဘာသာစကားများနှင့် ၎င်းတို့၏ locale name များကို ရှာဖွေနိုင်ပါသည်။

    > 💁 သင်သည် ဘာသာစကားများစွာ မပြောနိုင်ပါက [Bing Translate](https://www.bing.com/translator) သို့မဟုတ် [Google Translate](https://translate.google.com) ကဲ့သို့သော ဝန်ဆောင်မှုကို အသုံးပြု၍ သင့်နှစ်သက်သော ဘာသာစကားမှ သင့်ရွေးချယ်သော ဘာသာစကားသို့ ဘာသာပြန်နိုင်ပါသည်။ ဒီဝန်ဆောင်မှုများသည် ဘာသာပြန်ထားသော စာသားကို အသံထွက်ပေးနိုင်ပါသည်။
    >
    > ဥပမာအားဖြင့် သင်သည် LUIS ကို English ဖြင့် သင်ကြားပြီး French ကို user ဘာသာစကားအဖြစ် အသုံးပြုလိုပါက "set a 2 minute and 27 second timer" ကဲ့သို့သော စာကြောင်းများကို Bing Translate ကို အသုံးပြု၍ English မှ French သို့ ဘာသာပြန်နိုင်ပြီး **Listen translation** ခလုတ်ကို အသုံးပြု၍ ဘာသာပြန်ထားသော စာသားကို မိုက်ခရိုဖုန်းထဲသို့ ပြောနိုင်ပါသည်။
    >
    > ![Bing Translate တွင် Listen translation ခလုတ်](../../../../../translated_images/my/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. `speech_api_key` အောက်တွင် translator API key ကို ထည့်ပါ:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` ကို သင့် translator service resource အတွက် API key ဖြင့် အစားထိုးပါ။

1. `say` function အထက်တွင် `translate_text` function ကို သတ်မှတ်ပါ၊ ၎င်းသည် server ဘာသာစကားမှ user ဘာသာစကားသို့ စာသားကို ဘာသာပြန်မည်:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    from နှင့် to ဘာသာစကားများကို ဒီ function သို့ ပေးပို့ပါမည် - သင့် app သည် user ဘာသာစကားမှ server ဘာသာစကားသို့ ပြောင်းရန်နှင့် server ဘာသာစကားမှ user ဘာသာစကားသို့ ပြန်ပြောရန် လိုအပ်ပါသည်။

1. ဒီ function အတွင်း REST API call အတွက် URL နှင့် headers ကို သတ်မှတ်ပါ:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    ဒီ API အတွက် URL သည် တည်နေရာအထူးသတ်မှတ်ထားခြင်းမရှိပါ၊ တည်နေရာကို header အဖြစ် ပေးပို့ပါသည်။ API key ကို တိုက်ရိုက်အသုံးပြုပါသည်၊ ဒါကြောင့် speech service ကဲ့သို့ token issuer API မှ access token ရယူရန် မလိုအပ်ပါ။

1. ဒီအောက်တွင် call အတွက် parameters နှင့် body ကို သတ်မှတ်ပါ:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` သည် API call သို့ ပေးပို့ရန် parameters ကို သတ်မှတ်ပါသည်၊ from နှင့် to ဘာသာစကားများကို ပေးပို့ပါသည်။ ဒီ call သည် `from` ဘာသာစကားရှိ စာသားကို `to` ဘာသာစကားသို့ ဘာသာပြန်မည်။

    `body` သည် ဘာသာပြန်ရန် စာသားကို ပါဝင်သည်။ ၎င်းသည် array ဖြစ်ပြီး call တစ်ခုတွင် စာသားအပိုင်းများစွာကို ဘာသာပြန်နိုင်ပါသည်။

1. REST API ကို call လုပ်ပြီး response ကို ရယူပါ:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    ပြန်လာသော response သည် JSON array ဖြစ်ပြီး ဘာသာပြန်ထားသော အချက်အလက်များပါဝင်သည်။ ဒီ item တွင် body တွင် ပေးပို့ထားသော အချက်အလက်များအားလုံး၏ ဘာသာပြန် array ပါဝင်သည်။

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. array တွင် item ပထမဆုံး item မှ ပထမဆုံး ဘာသာပြန်၏ `test` property ကို ပြန်ပေးပါ:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `while True` loop ကို update လုပ်ပြီး user ဘာသာစကားမှ server ဘာသာစကားသို့ `convert_speech_to_text` call မှ စာသားကို ဘာသာပြန်ပါ:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    ဒီကုဒ်သည် console တွင် စာသား၏ original နှင့် translated version များကိုလည်း print လုပ်ပါသည်။

1. `say` function ကို update လုပ်ပြီး server ဘာသာစကားမှ user ဘာသာစကားသို့ ပြောရန် စာသားကို ဘာသာပြန်ပါ:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    ဒီကုဒ်သည် console တွင် စာသား၏ original နှင့် translated version များကိုလည်း print လုပ်ပါသည်။

1. သင့်ကုဒ်ကို run လုပ်ပါ။ သင့် function app ကို run လုပ်ထားပြီး user ဘာသာစကားဖြင့် timer တစ်ခုကို တောင်းဆိုပါ၊ သင်ဘာသာစကားကို ကိုယ်တိုင်ပြောခြင်းဖြင့် သို့မဟုတ် ဘာသာပြန် app ကို အသုံးပြုခြင်းဖြင့်။

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 ဘာသာစကားများတွင် တစ်ခုနှင့်တစ်ခု မတူညီသော စကားပြောနည်းများကြောင့် သင် LUIS ကို ပေးထားသော ဥပမာများနှင့် အနည်းငယ်ကွဲလွဲသော ဘာသာပြန်များရနိုင်ပါသည်။ ဒီလိုဖြစ်ပါက LUIS တွင် ဥပမာများကို ပိုမိုထည့်ပါ၊ ပြန်လေ့ကျင့်ပြီး model ကို ပြန်လည်ပုံနှိပ်ပါ။

> 💁 ဒီကုဒ်ကို [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) folder တွင် ရှာနိုင်ပါသည်။

😀 သင့် multilingual timer program အောင်မြင်ခဲ့ပါသည်!

---

**ဝက်ဘ်ဆိုက်မှတ်ချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှန်ကန်မှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက်ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါဝင်နိုင်ကြောင်း သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူလဘာသာစကားဖြင့် အာဏာတည်သောရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသောအချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော နားလည်မှုမှားများ သို့မဟုတ် အဓိပ္ပါယ်မှားများအတွက် ကျွန်ုပ်တို့ တာဝန်မယူပါ။