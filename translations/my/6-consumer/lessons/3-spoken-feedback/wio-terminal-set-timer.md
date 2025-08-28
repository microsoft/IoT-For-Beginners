<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-28T16:21:55+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "my"
}
-->
# Wio Terminal - Timer သတ်မှတ်ခြင်း

ဒီသင်ခန်းစာအပိုင်းမှာ သင့် serverless code ကိုခေါ်ပြီး စကားလုံးများကိုနားလည်စေကာ ရလဒ်အပေါ်မူတည်ပြီး Wio Terminal မှာ timer တစ်ခုကို သတ်မှတ်ပါမည်။

## Timer သတ်မှတ်ခြင်း

Speech-to-text call မှ ပြန်လာသော စာသားကို serverless code သို့ ပို့ရန်လိုအပ်ပြီး LUIS မှ အချိန်(seconds) ကို ပြန်ပေးပါမည်။ ဒီ seconds ကို အသုံးပြု၍ timer တစ်ခုကို သတ်မှတ်နိုင်ပါသည်။

Microcontrollers တွေမှာ Arduino မှာ multiple threads ကို native support မရှိပါသဖြင့် Python သို့မဟုတ် အခြား high-level programming languages တွေမှာတွေ့ရတဲ့ standard timer classes မရှိပါ။ အစား timer libraries တွေကို loop function မှာ အချိန်ကျော်လွန်မှုကိုတိုင်းတာပြီး အချိန်ကုန်သွားသောအခါ function တွေကို ခေါ်ရန် အသုံးပြုနိုင်ပါသည်။

### Task - စာသားကို serverless function သို့ ပို့ပါ

1. `smart-timer` project ကို VS Code မှာ ဖွင့်ပါ (ဖွင့်ထားမရှိသေးပါက)။

1. `config.h` header ဖိုင်ကို ဖွင့်ပြီး function app အတွက် URL ကို ထည့်ပါ။

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    `<URL>` ကို function app အတွက် URL ဖြင့် အစားထိုးပါ။ ဒီ URL ကို နောက်ဆုံးသင်ခန်းစာမှာ local machine ရဲ့ IP address ကို ရယူထားပြီး function app ကို run လုပ်ထားသောနေရာကို ရည်ညွှန်းပါ။

1. `src` folder မှာ `language_understanding.h` ဆိုတဲ့ ဖိုင်အသစ်တစ်ခု ဖန်တီးပါ။ ဒီဖိုင်ကို အသုံးပြု၍ recognized speech ကို function app သို့ ပို့ပြီး LUIS ကို အသုံးပြုကာ seconds အဖြစ် ပြောင်းရန် class ကို သတ်မှတ်ပါမည်။

1. ဒီဖိုင်ရဲ့ အပေါ်ပိုင်းမှာ အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    ဒီမှာလိုအပ်သော header files တွေကို ထည့်သွင်းထားပါသည်။

1. `LanguageUnderstanding` ဆိုတဲ့ class ကို သတ်မှတ်ပြီး ဒီ class ရဲ့ instance ကို ကြေညာပါ။

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Function app ကို ခေါ်ရန် WiFi client ကို ကြေညာရန်လိုအပ်ပါသည်။ Class ရဲ့ `private` section မှာ အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    WiFiClient _client;
    ```

1. `public` section မှာ `GetTimerDuration` ဆိုတဲ့ method ကို ကြေညာပါ။ ဒီ method က function app ကို ခေါ်ရန် အသုံးပြုမည်။

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. `GetTimerDuration` method မှာ function app သို့ ပို့ရန် JSON ကို ဖန်တီးရန် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    ဒီ code က `GetTimerDuration` method သို့ ပို့သော စာသားကို အောက်ပါ JSON အဖြစ် ပြောင်းပါမည်။

    ```json
    {
        "text" : "<text>"
    }
    ```

    `<text>` ဆိုသည်မှာ function သို့ ပို့သော စာသားဖြစ်သည်။

1. ဒီ code အောက်မှာ function app ကို POST request လုပ်ရန် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    ဒီ code က JSON body ကို function app သို့ ပို့ပြီး response code ကို ရယူပါမည်။

1. အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Response code ကို စစ်ဆေးပါ။ 200 (success) ဖြစ်ပါက timer အတွက် seconds ကို response body မှ ရယူပါမည်။ အခြားသော error ဖြစ်ပါက serial monitor မှာ error message ကို ပေးပြီး seconds ကို 0 အဖြစ် သတ်မှတ်ပါမည်။

1. HTTP connection ကို ပိတ်ပြီး seconds ကို ပြန်ပေးရန် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. `main.cpp` ဖိုင်မှာ ဒီ header ကို include လုပ်ပါ။

    ```cpp
    #include "speech_to_text.h"
    ```

1. `processAudio` function ရဲ့ အဆုံးမှာ `GetTimerDuration` method ကို ခေါ်ပြီး timer duration ကို ရယူပါ။

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    SpeechToText class မှ text ကို timer အတွက် seconds အဖြစ် ပြောင်းပါမည်။

### Task - Timer သတ်မှတ်ခြင်း

Seconds ကို timer သတ်မှတ်ရန် အသုံးပြုနိုင်ပါသည်။

1. Timer သတ်မှတ်ရန် library dependency ကို `platformio.ini` ဖိုင်မှာ ထည့်ပါ။

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. ဒီ library ကို `main.cpp` ဖိုင်မှာ include လုပ်ပါ။

    ```cpp
    #include <arduino-timer.h>
    ```

1. `processAudio` function ရဲ့ အပေါ်မှာ အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    auto timer = timer_create_default();
    ```

    Timer ကို `timer` အဖြစ် ကြေညာပါ။

1. အောက်မှာ အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    `say` function က text-to-speech ပြောင်းရန် အသုံးပြုမည်။ ယာယီအားဖြင့် passed-in text ကို serial monitor မှာ ရေးသားပါမည်။

1. `say` function အောက်မှာ အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Timer ကုန်ဆုံးသောအခါ ခေါ်ရန် callback function ဖြစ်သည်။ Timer ကို ပြန်လည် run မလုပ်ရန် `false` ကို return ပြန်ပါမည်။

1. `processAudio` function ရဲ့ အဆုံးမှာ အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Seconds က 0 ဖြစ်ပါက function call မှ ပြန်ထွက်ပါမည်။ Seconds ကို minutes နှင့် seconds အဖြစ် ပြောင်းပါမည်။

1. Timer စတင်သောအခါ ပြောရန် message ဖန်တီးရန် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. Timer ကုန်ဆုံးသောအခါ ပြောရန် message ဖန်တီးရန် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. Timer စတင် message ကို ပြောရန် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    say(begin_message);
    ```

1. Function ရဲ့ အဆုံးမှာ timer ကို စတင်ပါ။

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Timer ကို milliseconds ဖြင့် သတ်မှတ်ပါ။ Seconds ကို milliseconds အဖြစ် ပြောင်းရန် 1,000 ဖြင့် မကြိမ်ပါ။ Callback function အဖြစ် `timerExpired` ကို ပေးပြီး callback သို့ `end_message` ကို argument အဖြစ် ပေးပါ။ Callback function သည် `void *` arguments ကိုသာ လက်ခံနိုင်သဖြင့် string ကို သင့်တော်အောင် ပြောင်းပါ။

1. Timer ကို tick လုပ်ရန် `loop` function ရဲ့ အဆုံးမှာ အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    timer.tick();
    ```

1. Code ကို build လုပ်ပြီး Wio Terminal သို့ upload လုပ်ပါ။ Serial monitor မှာ စမ်းသပ်ပါ။ `Ready` ဆိုတာကို serial monitor မှာ မြင်လျှင် C button ကို နှိပ်ပါ (power switch အနီးမှာရှိသော ဘယ်ဘက် button)။ 4 seconds audio ကို ဖမ်းယူပြီး text အဖြစ် ပြောင်းကာ function app သို့ ပို့ပြီး timer ကို သတ်မှတ်ပါမည်။ Function app ကို locally run လုပ်ထားပါ။

    Timer စတင်သောအချိန်နှင့် ကုန်ဆုံးသောအချိန်ကို မြင်ရပါမည်။

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 ဒီ code ကို [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) folder မှာ ရှာနိုင်ပါသည်။

😀 သင့် timer program အောင်မြင်ခဲ့ပါသည်!

---

**ဝက်ဘ်ဆိုက်မှတ်ချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှန်ကန်မှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက်ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါဝင်နိုင်ကြောင်း သတိပြုပါ။ မူလဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတည်သော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော နားလည်မှုမှားများ သို့မဟုတ် အဓိပ္ပာယ်မှားများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။