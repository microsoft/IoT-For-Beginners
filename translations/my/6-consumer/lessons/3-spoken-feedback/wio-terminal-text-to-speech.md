<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-28T16:19:51+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "my"
}
-->
# စာသားကို အသံအဖြစ်ပြောင်းခြင်း - Wio Terminal

ဒီသင်ခန်းစာရဲ့ အပိုင်းမှာ စာသားကို အသံအဖြစ်ပြောင်းပြီး ပြောဆို feedback ပေးပါမယ်။

## စာသားကို အသံအဖြစ်ပြောင်းခြင်း

နောက်ဆုံးသင်ခန်းစာမှာ အသံကို စာသားအဖြစ်ပြောင်းဖို့ သုံးခဲ့တဲ့ speech services SDK ကို အသုံးပြုပြီး စာသားကို ပြန်လည်အသံအဖြစ်ပြောင်းနိုင်ပါတယ်။

## အသံများရရှိရန်

အသံတောင်းဆိုတဲ့အခါ အသံကို သတ်မှတ်ပေးရပါမယ်၊ အကြောင်းကတော့ အသံကို အမျိုးမျိုးသော အသံများကို အသုံးပြုပြီး ဖန်တီးနိုင်ပါတယ်။ ဘာသာစကားတစ်ခုစီမှာ အမျိုးမျိုးသော အသံများကို ပံ့ပိုးပေးထားပြီး speech services SDK မှာ ဘာသာစကားတစ်ခုစီအတွက် ပံ့ပိုးပေးထားတဲ့ အသံများစာရင်းကို ရနိုင်ပါတယ်။ 

Microcontroller တွေရဲ့ အကန့်အသတ်တွေ ဒီမှာ ပါဝင်လာပါတယ် - စာသားကို အသံအဖြစ်ပြောင်းတဲ့ services မှာ ပံ့ပိုးပေးထားတဲ့ အသံများစာရင်းကို ရယူဖို့ JSON စာရွက်တစ်ခုကို တောင်းဆိုရမှာဖြစ်ပြီး၊ အရွယ်အစား 77KB ကျော်ရှိပါတယ်၊ ဒါဟာ Wio Terminal အတွက် အလွန်ကြီးမားလွန်းပါတယ်။ ဒီစာရင်းမှာ အသံ 215 ခုပါဝင်ပြီး၊ JSON စာရွက်တစ်ခုက အောက်ပါအတိုင်း သတ်မှတ်ထားပါတယ်။

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

ဒီ JSON က **Aria** အသံအတွက်ဖြစ်ပြီး၊ အသံစတိုင်အမျိုးမျိုးပါဝင်ပါတယ်။ စာသားကို အသံအဖြစ်ပြောင်းတဲ့အခါ `en-US-AriaNeural` ဆိုတဲ့ shortname လိုအပ်ပါတယ်။

Microcontroller မှာ ဒီစာရင်းကို အပြည့်အဝ ဒေါင်းလုပ်လုပ်ပြီး decode လုပ်မယ့်အစား၊ သင်အသုံးပြုမယ့် ဘာသာစကားအတွက် အသံများစာရင်းကို ရယူဖို့ serverless code ရေးဖို့လိုအပ်ပါတယ်၊ ပြီးတော့ Wio Terminal မှာ ဒီ code ကို ခေါ်ပါ။ သင့် code က စာရင်းထဲက သင့်တော်တဲ့ အသံကို ရွေးချယ်နိုင်ပါတယ်၊ ဥပမာ အရင်ဆုံးတွေ့တဲ့ အသံကို ရွေးချယ်နိုင်ပါတယ်။

### အလုပ် - အသံများရယူဖို့ serverless function တစ်ခုဖန်တီးပါ

1. သင့် `smart-timer-trigger` project ကို VS Code မှာ ဖွင့်ပြီး terminal ကို ဖွင့်ပါ၊ virtual environment ကို activate လုပ်ထားတာ သေချာပါစေ။ မဟုတ်ရင် terminal ကို ပိတ်ပြီး ပြန်ဖန်တီးပါ။

1. `local.settings.json` ဖိုင်ကို ဖွင့်ပြီး speech API key နဲ့ location အတွက် settings တွေ ထည့်ပါ:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    `<key>` ကို သင့် speech service resource အတွက် API key နဲ့ အစားထိုးပါ။ `<location>` ကို speech service resource ဖန်တီးတဲ့အခါ သုံးခဲ့တဲ့ location နဲ့ အစားထိုးပါ။

1. ဒီ app မှာ `get-voices` ဆိုတဲ့ HTTP trigger အသစ်တစ်ခုကို အောက်ပါ command ကို VS Code terminal ရဲ့ functions app project root folder မှာ အသုံးပြုပြီး ဖန်တီးပါ:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    ဒါဟာ `get-voices` ဆိုတဲ့ HTTP trigger ကို ဖန်တီးပါလိမ့်မယ်။

1. `get-voices` folder ရဲ့ `__init__.py` ဖိုင်ထဲမှာ အောက်ပါ code နဲ့ အစားထိုးပါ:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    ဒီ code က endpoint ကို အသံများရယူဖို့ HTTP request လုပ်ပါတယ်။ အသံများစာရင်းက ဘာသာစကားအားလုံးအတွက် JSON အကြီးတစ်ခုဖြစ်ပြီး၊ request body မှာ ပေးထားတဲ့ ဘာသာစကားအတွက် အသံများကို filter လုပ်ပြီး၊ shortname ကို extract လုပ်ပြီး JSON စာရင်းအဖြစ် ပြန်ပေးပါတယ်။ shortname က စာသားကို အသံအဖြစ်ပြောင်းဖို့ လိုအပ်တဲ့ တန်ဖိုးဖြစ်ပြီး၊ ဒီတန်ဖိုးကိုသာ ပြန်ပေးပါတယ်။

    > 💁 သင်လိုအပ်တဲ့ အသံများကို ရွေးချယ်ဖို့ filter ကို ပြောင်းနိုင်ပါတယ်။

    ဒါဟာ 77KB (ရေးသားချိန်မှာ) အရွယ်ရှိတဲ့ data ကို အလွန်သေးငယ်တဲ့ JSON စာရွက်အဖြစ် လျှော့ချပေးပါတယ်။ ဥပမာ အမေရိကန်အသံများအတွက် 408 bytes ဖြစ်ပါတယ်။

1. သင့် function app ကို locally run လုပ်ပါ။ ပြီးတော့ curl လို tool ကို အသုံးပြုပြီး သင့် `text-to-timer` HTTP trigger ကို စမ်းသပ်ခဲ့သလို စမ်းသပ်နိုင်ပါတယ်။ သင့်ဘာသာစကားကို JSON body အနေနဲ့ ပေးပါ:

    ```json
    {
        "language":"<language>"
    }
    ```

    `<language>` ကို သင့်ဘာသာစကားနဲ့ အစားထိုးပါ၊ ဥပမာ `en-GB` သို့မဟုတ် `zh-CN`။

> 💁 ဒီ code ကို [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) folder မှာ ရှာနိုင်ပါတယ်။

### အလုပ် - Wio Terminal မှာ အသံကို ရယူပါ

1. `smart-timer` project ကို VS Code မှာ ဖွင့်ထားမယ်။

1. `config.h` header ဖိုင်ကို ဖွင့်ပြီး သင့် function app အတွက် URL ကို ထည့်ပါ:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    `<URL>` ကို `get-voices` HTTP trigger အတွက် URL နဲ့ အစားထိုးပါ။ ဒါဟာ `TEXT_TO_TIMER_FUNCTION_URL` အတွက် တန်ဖိုးနဲ့ တူပါမယ်၊ function name ကို `text-to-timer` အစား `get-voices` ဖြစ်ပါတယ်။

1. `src` folder မှာ `text_to_speech.h` ဆိုတဲ့ ဖိုင်အသစ်တစ်ခု ဖန်တီးပါ။ ဒီဖိုင်ကို စာသားကို အသံအဖြစ်ပြောင်းဖို့ class တစ်ခု သတ်မှတ်ဖို့ အသုံးပြုပါမယ်။

1. `text_to_speech.h` ဖိုင်ရဲ့ အပေါ်မှာ အောက်ပါ include directives တွေ ထည့်ပါ:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. အောက်မှာ `TextToSpeech` class ကို ကြေညာပြီး၊ application ရဲ့ အခြားနေရာမှာ အသုံးပြုနိုင်တဲ့ instance တစ်ခုကို ထည့်ပါ:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. function app ကို ခေါ်ဖို့ WiFi client ကို ကြေညာပါ။ class ရဲ့ `private` section မှာ အောက်ပါ code ကို ထည့်ပါ:

    ```cpp
    WiFiClient _client;
    ```

1. `private` section မှာ ရွေးချယ်ထားတဲ့ အသံအတွက် field တစ်ခု ထည့်ပါ:

    ```cpp
    String _voice;
    ```

1. `public` section မှာ `init` function ကို ထည့်ပြီး ပထမဆုံးအသံကို ရယူပါ:

    ```cpp
    void init()
    {
    }
    ```

1. အသံများရယူဖို့ JSON စာရွက်ကို function app ကို ပို့ဖို့ `init` function မှာ အောက်ပါ code ကို ထည့်ပါ:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. `HTTPClient` တစ်ခု ဖန်တီးပြီး၊ function app ကို ခေါ်ဖို့ အသုံးပြုပါ:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. response code ကို စစ်ဆေးပြီး၊ 200 (success) ဖြစ်ရင် အသံများစာရင်းကို extract လုပ်ပြီး၊ စာရင်းထဲက ပထမဆုံးအသံကို ရယူပါ:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. HTTP client connection ကို ပိတ်ပါ:

    ```cpp
    httpClient.end();
    ```

1. `main.cpp` ဖိုင်ကို ဖွင့်ပြီး၊ အပေါ်မှာ ဒီ header ဖိုင်ကို include လုပ်ဖို့ directive ကို ထည့်ပါ:

    ```cpp
    #include "text_to_speech.h"
    ```

1. `setup` function မှာ `speechToText.init();` ကို ခေါ်တဲ့နေရာအောက်မှာ `TextToSpeech` class ကို initialize လုပ်ဖို့ အောက်ပါ code ကို ထည့်ပါ:

    ```cpp
    textToSpeech.init();
    ```

1. ဒီ code ကို build လုပ်ပြီး၊ Wio Terminal မှာ upload လုပ်ပြီး serial monitor မှာ စမ်းသပ်ပါ။ သင့် function app ကို run လုပ်ထားတာ သေချာပါစေ။

    function app မှာ ပြန်ပေးတဲ့ အသံများစာရင်းနဲ့ ရွေးချယ်ထားတဲ့ အသံကို တွေ့ရပါမယ်။

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## စာသားကို အသံအဖြစ်ပြောင်းခြင်း

အသံကို အသုံးပြုနိုင်တဲ့အခါ၊ စာသားကို အသံအဖြစ်ပြောင်းနိုင်ပါတယ်။ အသံများအတွက် memory အကန့်အသတ်တွေက စာသားကို အသံအဖြစ်ပြောင်းတဲ့အခါမှာလည်း သက်ဆိုင်ပါတယ်၊ ဒါကြောင့် အသံကို SD card မှာ သိမ်းပြီး ReSpeaker မှာ play လုပ်ဖို့ လိုအပ်ပါတယ်။

> 💁 ဒီ project ရဲ့ အရင် lessons တွေမှာ microphone မှာ record လုပ်ထားတဲ့ အသံကို flash memory မှာ သိမ်းခဲ့ပါတယ်။ ဒီ lesson မှာ Seeed audio libraries ကို အသုံးပြုပြီး SD card မှာ audio ကို play လုပ်ရတာ ပိုလွယ်ပါတယ်။

အခြားအကန့်အသတ်တစ်ခုကိုလည်း စဉ်းစားရပါမယ်၊ speech service မှာ ရရှိနိုင်တဲ့ audio data နဲ့ Wio Terminal ပံ့ပိုးပေးတဲ့ formats တွေပါ။ microcontroller တွေအတွက် audio libraries တွေက audio formats ပံ့ပိုးမှု အလွန်ကန့်သတ်ထားနိုင်ပါတယ်။ ဥပမာ Seeed Arduino Audio library က ReSpeaker မှာ အသံ play လုပ်ဖို့ 44.1KHz sample rate ကိုသာ ပံ့ပိုးပါတယ်။ Azure speech services က audio ကို formats အမျိုးမျိုးပေးနိုင်ပေမယ့်၊ 44.1KHz sample rate ကို မပံ့ပိုးပါဘူး၊ 8KHz, 16KHz, 24KHz နဲ့ 48KHz ကိုသာ ပံ့ပိုးပါတယ်။ ဒါကြောင့် audio ကို 44.1KHz sample rate ကို ပြန်လည်ပြောင်းဖို့ လိုအပ်ပါတယ်၊ ဒါဟာ Wio Terminal ရဲ့ resources, အထူးသဖြင့် memory ကိုပိုလိုအပ်ပါတယ်။

ဒီလို data ကို manipulate လုပ်ဖို့လိုတဲ့အခါ၊ web call မှာ sourced ဖြစ်တဲ့ data တွေကို serverless code ကို အသုံးပြုတာ ပိုကောင်းပါတယ်။ Wio Terminal က serverless function ကို ခေါ်ပြီး၊ ပြောင်းဖို့စာသားကို ပေးနိုင်ပါတယ်၊ serverless function က speech service ကို ခေါ်ပြီး စာသားကို အသံအဖြစ်ပြောင်းနိုင်ပါတယ်၊ audio ကို လိုအပ်တဲ့ sample rate ကို ပြန်လည်ပြောင်းနိုင်ပါတယ်။ ပြီးတော့ audio ကို Wio Terminal မှာ SD card မှာ သိမ်းပြီး ReSpeaker မှာ play လုပ်ဖို့ လိုအပ်တဲ့ format အနေနဲ့ ပြန်ပေးနိုင်ပါတယ်။

### အလုပ် - စာသားကို အသံအဖြစ်ပြောင်းဖို့ serverless function တစ်ခုဖန်တီးပါ

1. `smart-timer-trigger` project ကို VS Code မှာ ဖွင့်ပြီး terminal ကို ဖွင့်ပါ၊ virtual environment ကို activate လုပ်ထားတာ သေချာပါစေ။ မဟုတ်ရင် terminal ကို ပိတ်ပြီး ပြန်ဖန်တီးပါ။

1. ဒီ app မှာ `text-to-speech` ဆိုတဲ့ HTTP trigger အသစ်တစ်ခုကို အောက်ပါ command ကို VS Code terminal ရဲ့ functions app project root folder မှာ အသုံးပြုပြီး ဖန်တီးပါ:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    ဒါဟာ `text-to-speech` ဆိုတဲ့ HTTP trigger ကို ဖန်တီးပါလိမ့်မယ်။

1. [librosa](https://librosa.org) Pip package မှာ audio ကို re-sample လုပ်ဖို့ functions တွေ ပါဝင်ပါတယ်၊ ဒါကို `requirements.txt` ဖိုင်မှာ ထည့်ပါ:

    ```sh
    librosa
    ```

    ထည့်ပြီးရင် VS Code terminal မှာ အောက်ပါ command ကို အသုံးပြုပြီး Pip packages တွေ install လုပ်ပါ:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Linux, Raspberry Pi OS အပါအဝင် သုံးနေပါက `libsndfile` ကို အောက်ပါ command နဲ့ install လုပ်ဖို့လိုအပ်နိုင်ပါတယ်:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. စာသားကို အသံအဖြစ်ပြောင်းဖို့ speech API key ကို တိုက်ရိုက်အသုံးမပြုနိုင်ပါဘူး၊ API key ကို အသုံးပြုပြီး access token တောင်းဆိုဖို့ authentication လုပ်ရပါမယ်။ `text-to-speech` folder ရဲ့ `__init__.py` ဖိုင်ကို ဖွင့်ပြီး အောက်ပါ code နဲ့ အစားထိုးပါ:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    ဒါဟာ settings မှာ ဖတ်မယ့် location နဲ့ speech key အတွက် constants တွေကို သတ်မှတ်ပါတယ်။ ပြီးတော့ speech service အတွက် access token ရယူဖို့ `get_access_token` function ကို သတ်မှတ်ပါတယ်။

1. ဒီ code အောက်မှာ အောက်ပါ code ကို ထည့်ပါ:

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    ဒါဟာ စာသားကို အသံအဖြစ်ပြောင်းတဲ့ HTTP trigger ကို သတ်မှတ်ပါတယ်။ JSON body မှာ request လုပ်တဲ့ စာသား၊ ဘာသာစကားနဲ့ အသံကို extract လုပ်ပြီး၊ speech တောင်းဆိုဖို့ SSML တစ်ခုကို ဖန်တီးပါတယ်၊ ပြီးတော့ access token ကို အသုံးပြုပြီး REST API ကို ခေါ်ပါတယ်။ REST API call က 16-bit, 48KHz mono WAV file အဖြစ် encode လုပ်ထားတဲ့ audio ကို ပြန်ပေးပါတယ်၊ `playback_format` တန်ဖိုးက REST API call ကို ပေးထားတဲ့ format ကို သတ်မှတ်ပါတယ်။

    ဒီ audio ကို `librosa` က 48KHz sample rate မှ 44.1KHz sample rate ကို ပြန်လည်ပြောင်းပါတယ်၊ ပြီးတော့ audio ကို binary buffer အဖြစ် သိမ်းပြီး ပြန်ပေးပါတယ်။

1. သင့် function app ကို locally run လုပ်ပါ၊ သို့မဟုတ် cloud မှာ deploy လုပ်ပါ။ curl လို tool ကို အသုံးပြုပြီး သင့် `text-to-timer` HTTP trigger ကို စမ်းသပ်ခဲ့သလို စမ်းသပ်နိုင်ပါတယ်။ ဘာသာစကား၊ အသံနဲ့ စာသားကို JSON body အနေနဲ့ ပေးပါ:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    `<language>` ကို သင့်ဘာသာစကားနဲ့ အစားထိုးပါ၊ ဥပမာ `en-GB` သို့မဟုတ် `zh-CN`။ `<voice>` ကို သင်အသုံးပြုချင်တဲ့ အသံနဲ့ အစားထိုးပါ။ `<text>` ကို အသံအဖြစ်ပြောင်းချင်တဲ့ စာသားနဲ့ အစားထိုးပါ။ output ကို ဖိုင်အဖြစ် save လုပ်ပြီး WAV files play လုပ်နိုင်တဲ့ audio player တစ်ခုနဲ့ play လုပ်နိုင်ပါတယ်။

    ဥပမာ "Hello" ကို US English Jenny Neural အသံနဲ့ အသံအဖြစ်ပြောင်းဖို့၊ function app ကို locally run လုပ်ထားတဲ့အခါ၊ အောက်ပါ curl command ကို အသုံးပြုနိုင်ပါတယ်:

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    ဒါဟာ audio ကို `hello.wav` အဖြစ် current directory မှာ save လုပ်ပါလိမ့်မယ်။

> 💁 ဒီ code ကို [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) folder မှာ ရှာနိုင်ပါတယ်။

### အလုပ် - Wio Terminal မှာ အသံကို ရယူပါ

1. `smart-timer` project ကို VS Code မှာ ဖွင့်ထားမယ်။

1. `config.h` header ဖိုင်ကို ဖွင့်ပြီး သင့် function app အတွက် URL ကို ထည့်ပါ:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    `<URL>` ကို `text-to-speech` HTTP trigger အတွက် URL နဲ့ အစားထိုးပါ။ ဒါဟာ `TEXT_TO_TIMER_FUNCTION_URL` အတွက် တန်ဖိုးနဲ့ တူပါမယ်၊ function name ကို `text-to-timer` အစား `text-to-speech` ဖြစ်ပါတယ်။

1. `text_to_speech.h` header ဖိုင်ကို ဖွင့်ပြီး `TextToSpeech` class ရဲ့ `public` section မှာ အောက်ပါ method ကို ထည့်ပါ:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. `convertTextToSpeech` method မှာ function app ကို ပို့ဖို့ JSON ဖန်တီးဖို့ အောက်ပါ code ကို ထည့်ပါ:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    ဒါဟာ ဘာသာစကား၊ အသံနဲ့ စာသားကို JSON document မှာ ရေးပြီး၊ string အဖြစ် serialize လုပ်ပါတယ်။

1. အောက်မှာ function app ကို ခေါ်ဖို့ အောက်ပါ code ကို ထည့်ပါ:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    ဒါဟာ HTTPClient တစ်ခု ဖန်တီးပြီး၊ JSON document ကို POST request အနေနဲ့ text to speech HTTP trigger ကို ပို့ပါတယ်။

1. call အောင်မြင်ရင်၊ function app call မှာ ပြန်ပေးတဲ့ raw binary data ကို SD card ရဲ့ ဖိုင်တစ်ခုကို stream လုပ်နိုင်ပါတယ်။ အောက်ပါ code ကို ထည့်ပါ:

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    ဒီ code က response ကို စစ်ဆေးပြီး၊ 200 (success) ဖြစ်ရင် binary data ကို SD card ရဲ့ root မှာ `SPEECH.WAV` ဆိုတဲ့ ဖိုင်အဖြစ် stream လုပ်ပါတယ်။

1. method ရဲ့ အဆုံးမှာ HTTP connection ကို ပိတ်ပါ:

    @@CODE
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### တာဝန် - Wio Terminal မှ အသံဖွင့်ပါ

**မကြာမီ**

## သင့် functions app ကို cloud သို့ တင်ပို့ခြင်း

Functions app ကို ဒေသတွင်းတွင် run လုပ်ရန်အကြောင်းရင်းမှာ `librosa` Pip package သည် Linux ပေါ်တွင် dependency library တစ်ခုရှိပြီး၊ အဲဒီ library ကို ပုံမှန်အားဖြင့် မထည့်သွင်းထားသောကြောင့် function app ကို run လုပ်နိုင်ရန်အတွက် ထည့်သွင်းရန်လိုအပ်သည်။ Function apps သည် serverless ဖြစ်ပြီး - သင့်ကိုယ်တိုင် စီမံခန့်ခွဲနိုင်သော servers မရှိပါ၊ ထို့ကြောင့် library ကို ကြိုတင်ထည့်သွင်းရန် နည်းလမ်းမရှိပါ။

ဒီအရာကို ပြုလုပ်ရန် နည်းလမ်းမှာ functions app ကို Docker container အသုံးပြု၍ တင်ပို့ခြင်းဖြစ်သည်။ ဒီ container ကို cloud မှ function app အသစ်တစ်ခုကို run လုပ်ရန် (ဥပမာ - demand က ရရှိနိုင်သော resources များထက် များလာသောအခါ၊ သို့မဟုတ် function app ကို အချိန်ကြာကြာ မသုံးသောအခါ ပိတ်ထားသောအခြေအနေ) အလိုအလျောက် deploy လုပ်ပေးသည်။

Linux ပေါ်တွင် custom container အသုံးပြု၍ function app တစ်ခုကို setup လုပ်ပြီး Docker မှတစ်ဆင့် deploy လုပ်ရန် လမ်းညွှန်ချက်များကို [Microsoft Docs တွင် create a function on Linux using a custom container documentation](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python) တွင် ရှာဖွေနိုင်ပါသည်။

ဒီအရာကို deploy လုပ်ပြီးလျှင် သင့် Wio Terminal code ကို function ကို access လုပ်ရန် port ပြောင်းနိုင်ပါသည်-

1. Azure Functions certificate ကို `config.h` ထဲသို့ ထည့်ပါ-

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. `<WiFiClient.h>` ကို `<WiFiClientSecure.h>` သို့ include ပြောင်းပါ။

1. `WiFiClient` fields အားလုံးကို `WiFiClientSecure` သို့ ပြောင်းပါ။

1. `WiFiClientSecure` field ပါရှိသော class အားလုံးတွင် constructor တစ်ခုထည့်ပြီး၊ အဲဒီ constructor တွင် certificate ကို set လုပ်ပါ-

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**ဝက်ဘ်ဆိုက်မှတ်ချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှန်ကန်မှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက်ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါဝင်နိုင်ကြောင်း သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူလဘာသာစကားဖြင့် အာဏာတည်သောရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသောအချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ဘာသာပြန်ခြင်းကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော နားလည်မှုမှားများ သို့မဟုတ် အဓိပ္ပါယ်မှားများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။