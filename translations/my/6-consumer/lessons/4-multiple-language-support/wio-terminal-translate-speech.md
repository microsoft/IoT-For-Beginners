<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-28T16:37:30+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "my"
}
-->
# စကားပြောကို ဘာသာပြန်ခြင်း - Wio Terminal

ဒီသင်ခန်းစာပိုင်းမှာ သင်သည် ဘာသာပြန်ဝန်ဆောင်မှုကို အသုံးပြု၍ စာသားကို ဘာသာပြန်ရန် ကုဒ်ရေးသားပါမည်။

## ဘာသာပြန်ဝန်ဆောင်မှုကို အသုံးပြု၍ စာသားကို စကားပြောအဖြစ် ပြောင်းခြင်း

Speech service REST API သည် တိုက်ရိုက် ဘာသာပြန်ခြင်းကို မပံ့ပိုးပါ၊ သို့သော် Speech-to-text service မှ ထွက်လာသော စာသားနှင့် ပြန်ပြောသော စကား၏ စာသားကို ဘာသာပြန်ရန် Translator service ကို အသုံးပြုနိုင်ပါသည်။ ဒီဝန်ဆောင်မှုတွင် REST API ရှိပြီး စာသားကို ဘာသာပြန်ရန် အသုံးပြုနိုင်သော်လည်း၊ အသုံးပြုရလွယ်ကူစေရန်အတွက် functions app ထဲတွင် HTTP trigger တစ်ခုအဖြစ် ထပ်မံထုပ်ပိုးထားသည်။

### လုပ်ငန်း - စာသားကို ဘာသာပြန်ရန် serverless function တစ်ခု ဖန်တီးခြင်း

1. သင်၏ `smart-timer-trigger` project ကို VS Code တွင် ဖွင့်ပြီး virtual environment ကို အလုပ်လုပ်နေကြောင်း သေချာစေပါ။ မဟုတ်ပါက terminal ကို ပိတ်ပြီး ပြန်ဖန်တီးပါ။

1. `local.settings.json` ဖိုင်ကို ဖွင့်ပြီး translator API key နှင့် location အတွက် settings များ ထည့်ပါ။

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    `<key>` ကို သင့် translator service resource အတွက် API key ဖြင့် အစားထိုးပါ။ `<location>` ကို သင် translator service resource ကို ဖန်တီးစဉ် အသုံးပြုခဲ့သော location ဖြင့် အစားထိုးပါ။

1. functions app project ၏ root folder အတွင်း VS Code terminal မှာ အောက်ပါ command ကို အသုံးပြု၍ `translate-text` ဟုခေါ်သော HTTP trigger အသစ်တစ်ခု ထည့်ပါ။

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    ဒီဟာက `translate-text` ဟုခေါ်သော HTTP trigger တစ်ခုကို ဖန်တီးပါမည်။

1. `translate-text` folder ထဲရှိ `__init__.py` ဖိုင်၏ အကြောင်းအရာများကို အောက်ပါအတိုင်း အစားထိုးပါ။

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    ဒီကုဒ်က HTTP request မှ စာသားနှင့် ဘာသာစကားများကို ထုတ်ယူပါသည်။ ထို့နောက် ဘာသာပြန်ရန် languages ကို URL parameters အဖြစ်၊ စာသားကို body အဖြစ် translator REST API သို့ တောင်းဆိုမှုတစ်ခု ပြုလုပ်ပါသည်။ နောက်ဆုံးတွင် ဘာသာပြန်ထားသော စာသားကို ပြန်ပေးပါသည်။

1. သင့် function app ကို ဒေသတွင်းတွင် အလုပ်လုပ်စေပါ။ ထို့နောက် curl ကဲ့သို့သော tool တစ်ခုကို အသုံးပြု၍ သင်၏ `text-to-timer` HTTP trigger ကို စမ်းသပ်ခဲ့သည့် နည်းလမ်းတူတူ သုံးနိုင်ပါသည်။ ဘာသာပြန်ရန် စာသားနှင့် ဘာသာစကားများကို JSON body အဖြစ် ပေးပို့ရန် သေချာစေပါ။

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    ဤဥပမာသည် *Définir une minuterie de 30 secondes* ကို ပြင်သစ်ဘာသာမှ အမေရိကန်အင်္ဂလိပ်ဘာသာသို့ ဘာသာပြန်သည်။ ၎င်းသည် *Set a 30-second timer* ဟု ပြန်ပေးပါမည်။

> 💁 ဒီကုဒ်ကို [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) folder တွင် ရှာနိုင်ပါသည်။

### လုပ်ငန်း - ဘာသာပြန် function ကို အသုံးပြု၍ စာသားကို ဘာသာပြန်ခြင်း

1. `smart-timer` project ကို VS Code တွင် ဖွင့်ထားမရှိပါက ဖွင့်ပါ။

1. သင့် smart timer တွင် ဘာသာစကား ၂ မျိုး သတ်မှတ်ထားမည် - LUIS ကို သင်ကြားရန် အသုံးပြုသော server ၏ ဘာသာစကား (user နှင့် ပြောဆိုရန် message များကို ဖန်တီးရန်လည်း အတူတူ အသုံးပြုသည်) နှင့် အသုံးပြုသူ ပြောသော ဘာသာစကား။ `config.h` header ဖိုင်တွင် `LANGUAGE` constant ကို အသုံးပြုသူ ပြောမည့် ဘာသာစကားအဖြစ် update ပြုလုပ်ပြီး `SERVER_LANGUAGE` ဟုခေါ်သော constant အသစ်တစ်ခု ထည့်ပါ။

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    `<user language>` ကို သင်ပြောမည့် ဘာသာစကား၏ locale name ဖြင့် အစားထိုးပါ၊ ဥပမာ `fr-FR` သည် ပြင်သစ်ဘာသာ၊ `zn-HK` သည် Cantonese ဖြစ်သည်။

    `<server language>` ကို LUIS ကို သင်ကြားရန် အသုံးပြုသော ဘာသာစကား၏ locale name ဖြင့် အစားထိုးပါ။

    Microsoft docs တွင် [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) တွင် ပံ့ပိုးထားသော ဘာသာစကားများနှင့် ၎င်းတို့၏ locale names များကို ရှာနိုင်ပါသည်။

    > 💁 သင်သည် ဘာသာစကားများစွာ မပြောနိုင်ပါက [Bing Translate](https://www.bing.com/translator) သို့မဟုတ် [Google Translate](https://translate.google.com) ကဲ့သို့သော ဝန်ဆောင်မှုများကို အသုံးပြု၍ သင့်နှစ်သက်သော ဘာသာစကားမှ သင်ရွေးချယ်သော ဘာသာစကားသို့ ဘာသာပြန်နိုင်ပါသည်။ ၎င်းဝန်ဆောင်မှုများသည် ဘာသာပြန်ထားသော စာသား၏ အသံကို ဖော်ပြနိုင်ပါသည်။
    >
    > ဥပမာအားဖြင့် LUIS ကို အင်္ဂလိပ်ဘာသာဖြင့် သင်ကြားပြီး အသုံးပြုသူ ဘာသာစကားအဖြစ် ပြင်သစ်ကို အသုံးပြုလိုပါက Bing Translate ကို အသုံးပြု၍ "set a 2 minute and 27 second timer" ကဲ့သို့သော စာကြောင်းများကို အင်္ဂလိပ်မှ ပြင်သစ်သို့ ဘာသာပြန်နိုင်ပါသည်။ ထို့နောက် **Listen translation** ခလုတ်ကို အသုံးပြု၍ ဘာသာပြန်ထားသော စာသားကို သင့်မိုက်ခရိုဖုန်းထဲသို့ ပြောနိုင်ပါသည်။
    >
    > ![Bing Translate တွင် Listen translation ခလုတ်](../../../../../translated_images/my/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. `SPEECH_LOCATION` အောက်တွင် translator API key နှင့် location ကို ထည့်ပါ။

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    `<KEY>` ကို သင့် translator service resource အတွက် API key ဖြင့် အစားထိုးပါ။ `<LOCATION>` ကို သင် translator service resource ကို ဖန်တီးစဉ် အသုံးပြုခဲ့သော location ဖြင့် အစားထိုးပါ။

1. `VOICE_URL` အောက်တွင် translator trigger URL ကို ထည့်ပါ။

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    `<URL>` ကို သင့် function app တွင် `translate-text` HTTP trigger အတွက် URL ဖြင့် အစားထိုးပါ။ ၎င်းသည် `TEXT_TO_TIMER_FUNCTION_URL` ၏ တန်ဖိုးနှင့် တူသည်၊ function name ကို `text-to-timer` အစား `translate-text` ဖြင့် အစားထိုးထားသည်။

1. `src` folder တွင် `text_translator.h` ဟုခေါ်သော ဖိုင်အသစ်တစ်ခု ထည့်ပါ။

1. ဒီအသစ်သော `text_translator.h` header ဖိုင်တွင် စာသားကို ဘာသာပြန်ရန် class တစ်ခု ပါဝင်မည်။ ဒီ class ကို ကြေညာရန် အောက်ပါအတိုင်း ထည့်ပါ။

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    ၎င်းသည် `TextTranslator` class ကို ကြေညာပြီး ၎င်း class ၏ instance တစ်ခုပါဝင်သည်။ class တွင် WiFi client အတွက် field တစ်ခုသာ ပါဝင်သည်။

1. ဒီ class ၏ `public` အပိုင်းတွင် စာသားကို ဘာသာပြန်ရန် method တစ်ခု ထည့်ပါ။

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    ဒီ method သည် ဘာသာပြန်ရန် ဘာသာစကားနှင့် ဘာသာပြန်ပြီးသော ဘာသာစကားကို လက်ခံသည်။ Speech ကို ကိုင်တွယ်စဉ် Speech ကို အသုံးပြုသူ ဘာသာစကားမှ LUIS server ဘာသာစကားသို့ ဘာသာပြန်ပြီး၊ ပြန်ပြောသောအခါ LUIS server ဘာသာစကားမှ အသုံးပြုသူ ဘာသာစကားသို့ ဘာသာပြန်ပါမည်။

1. ဒီ method တွင် ဘာသာပြန်ရန် စာသားနှင့် ဘာသာစကားများပါဝင်သော JSON body တစ်ခု ဖန်တီးရန် ကုဒ်ထည့်ပါ။

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. ဒီအောက်တွင် serverless function app သို့ body ကို ပေးပို့ရန် အောက်ပါကုဒ်ထည့်ပါ။

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. နောက်တစ်ဆင့်မှာ response ကို ရယူရန် ကုဒ်ထည့်ပါ။

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. နောက်ဆုံးတွင် connection ကို ပိတ်ပြီး ဘာသာပြန်ထားသော စာသားကို ပြန်ပေးရန် ကုဒ်ထည့်ပါ။

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### လုပ်ငန်း - အသိအမှတ်ပြုထားသော စကားနှင့် ပြန်ပြောသော စကားကို ဘာသာပြန်ခြင်း

1. `main.cpp` ဖိုင်ကို ဖွင့်ပါ။

1. ဖိုင်၏ အပေါ်ဆုံးတွင် `TextTranslator` class header ဖိုင်အတွက် include directive တစ်ခု ထည့်ပါ။

    ```cpp
    #include "text_translator.h"
    ```

1. Timer သတ်မှတ်ခြင်း သို့မဟုတ် သက်တမ်းကုန်ဆုံးခြင်းအခါ ပြောသော စကားကို ဘာသာပြန်ရန် လိုအပ်သည်။ ၎င်းအတွက် `say` function ၏ ပထမဆုံးလိုင်းအဖြစ် အောက်ပါအတိုင်း ထည့်ပါ။

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    ၎င်းသည် စာသားကို အသုံးပြုသူ ဘာသာစကားသို့ ဘာသာပြန်ပါမည်။

1. `processAudio` function တွင် `String text = speechToText.convertSpeechToText();` ခေါ်ဆိုမှုဖြင့် audio မှ text ကို ရယူသည်။ ဒီခေါ်ဆိုမှုအပြီးတွင် စာသားကို ဘာသာပြန်ပါ။

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    ၎င်းသည် အသုံးပြုသူ ဘာသာစကားမှ server တွင် အသုံးပြုသော ဘာသာစကားသို့ စာသားကို ဘာသာပြန်ပါမည်။

1. ဒီကုဒ်ကို build လုပ်ပြီး Wio Terminal သို့ upload လုပ်ပါ။ Serial monitor မှတစ်ဆင့် စမ်းသပ်ပါ။ Serial monitor တွင် `Ready` ဟု မြင်လျှင် C ခလုတ် (power switch အနီးရှိ ဘယ်ဘက်ဖက် ခလုတ်) ကို နှိပ်ပြီး စကားပြောပါ။ သင့် function app အလုပ်လုပ်နေကြောင်း သေချာစေပြီး အသုံးပြုသူ ဘာသာစကားဖြင့် timer တစ်ခု တောင်းဆိုပါ၊ သင်ဘာသာစကားကို ကိုယ်တိုင် ပြောခြင်းဖြင့် သို့မဟုတ် ဘာသာပြန် app ကို အသုံးပြုခြင်းဖြင့် ပြုလုပ်နိုင်ပါသည်။

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 ဒီကုဒ်ကို [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) folder တွင် ရှာနိုင်ပါသည်။

😀 သင့် multilingual timer program အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူက ဘာသာပြန်မှု ဝန်ဆောင်မှုကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားယူမှားမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။