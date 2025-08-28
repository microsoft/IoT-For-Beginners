<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-28T16:21:07+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "my"
}
-->
# Text to speech - Raspberry Pi

ဒီသင်ခန်းစာပိုင်းမှာ သင်သည် speech service ကို အသုံးပြု၍ စာသားကို အသံသို့ ပြောင်းလဲရန် ကုဒ်ရေးသားပါမည်။

## Speech service ကို အသုံးပြု၍ စာသားကို အသံသို့ ပြောင်းလဲခြင်း

စာသားကို REST API ကို အသုံးပြု၍ speech service သို့ ပို့ပြီး IoT စက်ပစ္စည်းပေါ်တွင် ပြန်ဖွင့်နိုင်သော အသံဖိုင်အဖြစ် ရယူနိုင်သည်။ Speech ကို တောင်းဆိုရာတွင် အသံအမျိုးအစားကို သတ်မှတ်ရန် လိုအပ်သည်။ အမျိုးမျိုးသော အသံများကို အသုံးပြု၍ speech ကို ဖန်တီးနိုင်သည်။

ဘာသာစကားတိုင်းတွင် မတူညီသော အသံအမျိုးအစားများကို ပံ့ပိုးပေးထားပြီး speech service ကို REST request ဖြင့် တောင်းဆိုကာ ဘာသာစကားတစ်ခုစီအတွက် ပံ့ပိုးထားသော အသံစာရင်းကို ရယူနိုင်သည်။

### Task - အသံတစ်ခု ရယူခြင်း

1. `smart-timer` project ကို VS Code တွင် ဖွင့်ပါ။

1. `say` function အထက်တွင် ဘာသာစကားတစ်ခုအတွက် အသံစာရင်းကို တောင်းဆိုရန် အောက်ပါကုဒ်ကို ထည့်ပါ။

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    ဒီကုဒ်သည် `get_voice` ဟုခေါ်သော function တစ်ခုကို သတ်မှတ်ထားပြီး speech service ကို အသုံးပြု၍ အသံစာရင်းကို ရယူသည်။ ထို့နောက် အသုံးပြုမည့် ဘာသာစကားနှင့် ကိုက်ညီသော ပထမဆုံးအသံကို ရှာဖွေသည်။

    ဒီ function ကို ခေါ်ပြီး ပထမဆုံးအသံကို သိမ်းဆည်းကာ အသံအမည်ကို console တွင် ပုံနှိပ်ပြသသည်။ ဒီအသံကို တစ်ကြိမ်တောင်းဆိုပြီး စာသားကို အသံသို့ ပြောင်းလဲရာတွင် အမြဲတမ်း အသုံးပြုနိုင်သည်။

    > 💁 Microsoft Docs တွင် [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) မှာ ပံ့ပိုးထားသော အသံစာရင်းကို အပြည့်အစုံ ရယူနိုင်သည်။ သင်တစ်ခုချင်းစီ အသံကို သတ်မှတ်လိုပါက ဒီ function ကို ဖယ်ရှားပြီး အသံအမည်ကို documentation မှာ ရှိသော အသံအမည်ဖြင့် hard code လုပ်နိုင်သည်။ ဥပမာအားဖြင့်:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Task - စာသားကို အသံသို့ ပြောင်းလဲခြင်း

1. ဒီအောက်တွင် speech service မှ ရယူမည့် အသံဖိုင်အမျိုးအစားအတွက် constant တစ်ခုကို သတ်မှတ်ပါ။ အသံကို တောင်းဆိုရာတွင် အမျိုးမျိုးသော ဖော်မတ်များဖြင့် ပြုလုပ်နိုင်သည်။

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    သင့် hardware အပေါ်မူတည်၍ အသုံးပြုနိုင်သော ဖော်မတ်များ မတူနိုင်သည်။ အသံဖိုင်ကို ဖွင့်ရာတွင် `Invalid sample rate` အမှားများ ရရှိပါက ဒီဖော်မတ်ကို အခြားတစ်ခုသို့ ပြောင်းပါ။ [Text to speech REST API documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs) တွင် ပံ့ပိုးထားသော ဖော်မတ်များကို ရှာနိုင်သည်။ `riff` ဖော်မတ်အသံကို အသုံးပြုရန် လိုအပ်ပြီး `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` နှင့် `riff-48khz-16bit-mono-pcm` တို့ကို စမ်းသပ်ပါ။

1. ဒီအောက်တွင် speech service REST API ကို အသုံးပြု၍ စာသားကို အသံသို့ ပြောင်းလဲရန် `get_speech` ဟုခေါ်သော function တစ်ခုကို သတ်မှတ်ပါ။

    ```python
    def get_speech(text):
    ```

1. `get_speech` function တွင် ခေါ်မည့် URL နှင့် ပေးပို့ရန် headers ကို သတ်မှတ်ပါ။

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    ဒီ headers တွင် ဖန်တီးထားသော access token ကို အသုံးပြုကာ SSML ကို content အဖြစ် သတ်မှတ်ပြီး လိုအပ်သော အသံဖော်မတ်ကို သတ်မှတ်သည်။

1. ဒီအောက်တွင် REST API သို့ ပေးပို့ရန် SSML ကို သတ်မှတ်ပါ။

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    ဒီ SSML တွင် ဘာသာစကားနှင့် အသုံးပြုမည့် အသံကို သတ်မှတ်ပြီး ပြောင်းလဲရန် စာသားကို ထည့်သွင်းသည်။

1. နောက်ဆုံးတွင် ဒီ function တွင် REST request ကို ပြုလုပ်ကာ binary audio data ကို ပြန်ပေးရန် ကုဒ်ထည့်ပါ။

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Task - အသံဖိုင်ကို ဖွင့်ခြင်း

1. `get_speech` function အောက်တွင် REST API call မှ ပြန်လာသော အသံကို ဖွင့်ရန် function တစ်ခုကို သတ်မှတ်ပါ။

    ```python
    def play_speech(speech):
    ```

1. ဒီ function သို့ ပေးပို့မည့် `speech` သည် REST API မှ ပြန်လာသော binary audio data ဖြစ်သည်။ အောက်ပါကုဒ်ကို အသုံးပြု၍ wave ဖိုင်အဖြစ် ဖွင့်ကာ PyAudio ကို အသုံးပြု၍ အသံဖွင့်ပါ။

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    ဒီကုဒ်သည် PyAudio stream ကို အသုံးပြုသည်။ အသံဖမ်းယူခြင်းနှင့် တူသည်။ ကွာခြားချက်မှာ stream ကို output stream အဖြစ် သတ်မှတ်ပြီး audio data မှ data ကို ဖတ်၍ stream သို့ ပို့သည်။

    Stream အသေးစိတ်ကို hard code မလုပ်ဘဲ audio data မှ ဖတ်ယူသည်။

1. `say` function ၏ အကြောင်းအရာကို အောက်ပါအတိုင်း ပြောင်းလဲပါ။

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    ဒီကုဒ်သည် စာသားကို binary audio data အဖြစ် speech သို့ ပြောင်းပြီး အသံဖွင့်သည်။

1. App ကို run လုပ်ပြီး function app ကိုလည်း run လုပ်ပါ။ Timer များကို သတ်မှတ်ပြီး သင့် timer သတ်မှတ်ပြီးကြောင်း ပြောဆိုသည့် အသံကို ကြားရမည်။ Timer ပြီးဆုံးသောအခါတွင်လည်း ပြောဆိုသည့် အသံကို ကြားရမည်။

    `Invalid sample rate` အမှားများ ရရှိပါက အထက်ဖော်ပြထားသည့်အတိုင်း `playback_format` ကို ပြောင်းပါ။

> 💁 ဒီကုဒ်ကို [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) folder တွင် ရှာနိုင်သည်။

😀 သင့် timer အစီအစဉ်အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။