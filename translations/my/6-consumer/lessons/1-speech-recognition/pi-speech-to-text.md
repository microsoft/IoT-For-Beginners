<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-28T16:30:20+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "my"
}
-->
# အသံမှ စာသား - Raspberry Pi

ဒီသင်ခန်းစာအပိုင်းမှာ သင်ရဲ့အော်ဒီယိုမှတစ်ဆင့် အသံကို စာသားအဖြစ်ပြောင်းလဲပေးနိုင်ရန် ကုဒ်ရေးသားပါမည်။

## အသံကို အသံဝန်ဆောင်မှုဆီသို့ ပို့ပါ

အသံကို REST API ကို အသုံးပြု၍ အသံဝန်ဆောင်မှုဆီသို့ ပို့နိုင်သည်။ အသံဝန်ဆောင်မှုကို အသုံးပြုရန်အတွက် အရင်ဆုံး access token တစ်ခုကို တောင်းဆိုရမည်၊ ထို့နောက် token ကို အသုံးပြု၍ REST API ကို အသုံးပြုနိုင်သည်။ ဒီ access tokens များသည် ၁၀ မိနစ်အတွင်း သက်တမ်းကုန်သွားနိုင်သောကြောင့် သင့်ရဲ့ကုဒ်သည် အမြဲတမ်း update ဖြစ်နေစေရန် regular interval တွင် token များကို တောင်းဆိုရမည်။

### လုပ်ငန်း - access token ရယူပါ

1. သင့် Pi မှာ `smart-timer` project ကို ဖွင့်ပါ။

1. `play_audio` function ကို ဖယ်ရှားပါ။ ဒီ function ကို မလိုအပ်တော့ပါ၊ အကြောင်းမှာ smart timer သည် သင်ပြောသောအရာကို ပြန်ပြောမည်မဟုတ်ပါ။

1. `app.py` ဖိုင်၏ အပေါ်ဆုံးတွင် အောက်ပါ import ကို ထည့်ပါ။

    ```python
    import requests
    ```

1. `while True` loop အပေါ်တွင် အသံဝန်ဆောင်မှုအတွက် settings များကို ကြေညာရန် အောက်ပါကုဒ်ကို ထည့်ပါ။

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    `<key>` ကို သင့်အသံဝန်ဆောင်မှု resource အတွက် API key ဖြင့် အစားထိုးပါ။ `<location>` ကို သင်အသံဝန်ဆောင်မှု resource ကို ဖန်တီးခဲ့သောနေရာဖြင့် အစားထိုးပါ။

    `<language>` ကို သင်ပြောမည့်ဘာသာစကား၏ locale name ဖြင့် အစားထိုးပါ၊ ဥပမာ `en-GB` သည် အင်္ဂလိပ်ဘာသာစကားအတွက်ဖြစ်သည်၊ `zn-HK` သည် Cantonese အတွက်ဖြစ်သည်။ Microsoft docs တွင် [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) တွင် locale names များနှင့် supported languages များကို ရှာဖွေကြည့်နိုင်သည်။

1. အောက်တွင် access token ရယူရန် function ကို ထည့်ပါ။

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    ဒီ function သည် token issuing endpoint ကို API key ကို header အဖြစ်ပေးပို့ပြီး ခေါ်သုံးသည်။ ဒီ call သည် အသံဝန်ဆောင်မှုများကို ခေါ်ရန် အသုံးပြုနိုင်သော access token ကို ပြန်ပေးသည်။

1. အောက်တွင် REST API ကို အသုံးပြု၍ အသံကို စာသားအဖြစ်ပြောင်းလဲရန် function ကို ကြေညာပါ။

    ```python
    def convert_speech_to_text(buffer):
    ```

1. ဒီ function အတွင်း REST API URL နှင့် headers များကို စီစဉ်ပါ။

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    ဒီ function သည် အသံဝန်ဆောင်မှု resource ၏ location ကို အသုံးပြု၍ URL တစ်ခုကို ဖန်တီးသည်။ ထို့နောက် `get_access_token` function မှ access token ကို headers တွင် ထည့်သွင်းပြီး အသံဖမ်းယူမှု sample rate ကို ထည့်သွင်းသည်။ နောက်ဆုံးတွင် URL နှင့် language parameters များကို သတ်မှတ်သည်။

1. အောက်တွင် REST API ကို ခေါ်သုံးပြီး text ကို ပြန်ရယူရန် အောက်ပါကုဒ်ကို ထည့်ပါ။

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    ဒီ function သည် URL ကို ခေါ်သုံးပြီး ပြန်လာသော JSON response ကို decode လုပ်သည်။ response အတွင်း `RecognitionStatus` value သည် အသံကို စာသားအဖြစ်အောင်မြင်စွာ extract လုပ်နိုင်ခဲ့သည်ကို ပြသသည်။ `Success` ဖြစ်ပါက text ကို function မှ ပြန်ပေးသည်၊ မဟုတ်ပါက အလွတ် string ကို ပြန်ပေးသည်။

1. `while True:` loop အပေါ်တွင် အသံမှ text ပြန်ရလာသောအရာကို process လုပ်ရန် function ကို ကြေညာပါ။ ဒီ function သည် text ကို console တွင် print လုပ်ရန်သာ ဖြစ်ပါမည်။

    ```python
    def process_text(text):
        print(text)
    ```

1. နောက်ဆုံးတွင် `while True` loop အတွင်း `play_audio` ကို ဖယ်ရှားပြီး `convert_speech_to_text` function ကို ခေါ်သုံးပါ၊ text ကို `process_text` function သို့ ပေးပို့ပါ။

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. ကုဒ်ကို run လုပ်ပါ။ ခလုတ်ကို နှိပ်ပြီး မိုက်ခရိုဖုန်းထဲသို့ ပြောပါ။ ပြောပြီးပါက ခလုတ်ကို လွှတ်ပါ၊ အသံကို စာသားအဖြစ်ပြောင်းပြီး console တွင် print လုပ်ပါမည်။

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    အမျိုးမျိုးသော စာကြောင်းများကို စမ်းကြည့်ပါ၊ အသံတူသော စကားလုံးများပါဝင်သော စာကြောင်းများကိုပါ စမ်းကြည့်ပါ။ ဥပမာ အင်္ဂလိပ်ဘာသာစကားဖြင့် ပြောပါက 'I want to buy two bananas and an apple too' ဟု ပြောပါ၊ ထို့နောက် context အပေါ်မူတည်၍ to, two, too ကို မှန်ကန်စွာ အသုံးပြုထားသည်ကို သတိပြုပါ။

> 💁 ဒီကုဒ်ကို [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) folder တွင် ရှာဖွေနိုင်ပါသည်။

😀 သင့်ရဲ့ အသံမှ စာသား ပြောင်းလဲမှု အစီအစဉ်အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါရှိနိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူက ဘာသာပြန်ခြင်းကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွဲအချော်အချော်များအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။