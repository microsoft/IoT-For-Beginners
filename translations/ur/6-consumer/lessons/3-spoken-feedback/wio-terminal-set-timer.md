<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T00:11:37+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "ur"
}
-->
# وائیو ٹرمینل پر ٹائمر سیٹ کریں

اس سبق کے اس حصے میں، آپ اپنی سرور لیس کوڈ کو کال کریں گے تاکہ تقریر کو سمجھا جا سکے، اور نتائج کی بنیاد پر اپنے وائیو ٹرمینل پر ایک ٹائمر سیٹ کریں۔

## ٹائمر سیٹ کریں

تقریر کو متن میں تبدیل کرنے کے بعد جو متن واپس آتا ہے، اسے آپ کے سرور لیس کوڈ کو بھیجا جانا چاہیے تاکہ LUIS کے ذریعے پروسیس کیا جا سکے، اور ٹائمر کے لیے سیکنڈز کی تعداد واپس حاصل کی جا سکے۔ ان سیکنڈز کی تعداد کو ٹائمر سیٹ کرنے کے لیے استعمال کیا جا سکتا ہے۔

مائیکرو کنٹرولرز میں Arduino میں متعدد تھریڈز کے لیے مقامی طور پر سپورٹ نہیں ہوتی، اس لیے یہاں معیاری ٹائمر کلاسز موجود نہیں ہیں جیسا کہ Python یا دیگر اعلیٰ سطحی زبانوں میں ہوتا ہے۔ اس کے بجائے، آپ ٹائمر لائبریریاں استعمال کر سکتے ہیں جو `loop` فنکشن میں گزرے ہوئے وقت کو ماپ کر کام کرتی ہیں اور وقت ختم ہونے پر فنکشنز کو کال کرتی ہیں۔

### کام - متن کو سرور لیس فنکشن کو بھیجیں

1. اگر `smart-timer` پروجیکٹ پہلے سے کھلا نہیں ہے تو اسے VS Code میں کھولیں۔

1. `config.h` ہیڈر فائل کھولیں اور اپنی فنکشن ایپ کے لیے URL شامل کریں:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    `<URL>` کو اپنی فنکشن ایپ کے URL سے تبدیل کریں جو آپ نے پچھلے سبق کے آخری مرحلے میں حاصل کیا تھا، جو آپ کے مقامی مشین کے IP ایڈریس کی طرف اشارہ کرتا ہے جہاں فنکشن ایپ چل رہی ہے۔

1. `src` فولڈر میں ایک نئی فائل بنائیں جس کا نام `language_understanding.h` ہو۔ یہ فائل اس کلاس کو ڈیفائن کرنے کے لیے استعمال ہوگی جو پہچانی گئی تقریر کو آپ کی فنکشن ایپ کو بھیجے گی تاکہ LUIS کے ذریعے سیکنڈز میں تبدیل کیا جا سکے۔

1. اس فائل کے اوپر درج ذیل شامل کریں:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    یہ کچھ ضروری ہیڈر فائلز شامل کرتا ہے۔

1. ایک کلاس `LanguageUnderstanding` کے نام سے ڈیفائن کریں، اور اس کلاس کا ایک انسٹینس ڈکلیئر کریں:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. اپنی فنکشن ایپ کو کال کرنے کے لیے، ایک WiFi کلائنٹ ڈکلیئر کریں۔ کلاس کے `private` سیکشن میں درج ذیل شامل کریں:

    ```cpp
    WiFiClient _client;
    ```

1. `public` سیکشن میں، ایک میتھڈ `GetTimerDuration` ڈکلیئر کریں تاکہ فنکشن ایپ کو کال کیا جا سکے:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. `GetTimerDuration` میتھڈ میں، فنکشن ایپ کو بھیجے جانے والے JSON کو بنانے کے لیے درج ذیل کوڈ شامل کریں:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    یہ کوڈ `GetTimerDuration` میتھڈ کو پاس کیے گئے متن کو درج ذیل JSON میں تبدیل کرتا ہے:

    ```json
    {
        "text" : "<text>"
    }
    ```

    جہاں `<text>` وہ متن ہے جو فنکشن کو پاس کیا گیا ہے۔

1. اس کے نیچے، فنکشن ایپ کال کرنے کے لیے درج ذیل کوڈ شامل کریں:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    یہ ایک POST درخواست فنکشن ایپ کو بھیجتا ہے، JSON باڈی پاس کرتا ہے اور رسپانس کوڈ حاصل کرتا ہے۔

1. اس کے نیچے درج ذیل کوڈ شامل کریں:

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

    یہ کوڈ رسپانس کوڈ کو چیک کرتا ہے۔ اگر یہ 200 (کامیابی) ہے، تو ٹائمر کے لیے سیکنڈز کی تعداد رسپانس باڈی سے حاصل کی جاتی ہے۔ ورنہ، ایک ایرر سیریل مانیٹر پر بھیجا جاتا ہے اور سیکنڈز کی تعداد 0 پر سیٹ کی جاتی ہے۔

1. اس میتھڈ کے آخر میں درج ذیل کوڈ شامل کریں تاکہ HTTP کنکشن بند کیا جا سکے اور سیکنڈز کی تعداد واپس کی جا سکے:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. `main.cpp` فائل میں، اس نئے ہیڈر کو شامل کریں:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `processAudio` فنکشن کے آخر میں، `GetTimerDuration` میتھڈ کو کال کریں تاکہ ٹائمر کی مدت حاصل کی جا سکے:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    یہ `SpeechToText` کلاس کی کال سے حاصل شدہ متن کو ٹائمر کے لیے سیکنڈز کی تعداد میں تبدیل کرتا ہے۔

### کام - ٹائمر سیٹ کریں

سیکنڈز کی تعداد کو ٹائمر سیٹ کرنے کے لیے استعمال کیا جا سکتا ہے۔

1. `platformio.ini` فائل میں درج ذیل لائبریری ڈپینڈنسی شامل کریں تاکہ ٹائمر سیٹ کرنے کے لیے ایک لائبریری شامل کی جا سکے:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. `main.cpp` فائل میں اس لائبریری کے لیے ایک انکلوڈ ڈائریکٹو شامل کریں:

    ```cpp
    #include <arduino-timer.h>
    ```

1. `processAudio` فنکشن کے اوپر درج ذیل کوڈ شامل کریں:

    ```cpp
    auto timer = timer_create_default();
    ```

    یہ کوڈ ایک ٹائمر `timer` ڈکلیئر کرتا ہے۔

1. اس کے نیچے درج ذیل کوڈ شامل کریں:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    یہ `say` فنکشن آخر کار متن کو تقریر میں تبدیل کرے گا، لیکن فی الحال یہ صرف پاس کیے گئے متن کو سیریل مانیٹر پر لکھے گا۔

1. `say` فنکشن کے نیچے درج ذیل کوڈ شامل کریں:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    یہ ایک کال بیک فنکشن ہے جو ٹائمر ختم ہونے پر کال کیا جائے گا۔ یہ ایک پیغام پاس کرتا ہے جو ٹائمر ختم ہونے پر کہا جائے گا۔ ٹائمرز کو دہرایا جا سکتا ہے، اور یہ کال بیک کے ریٹرن ویلیو سے کنٹرول کیا جا سکتا ہے - یہ `false` ریٹرن کرتا ہے تاکہ ٹائمر دوبارہ نہ چلے۔

1. `processAudio` فنکشن کے آخر میں درج ذیل کوڈ شامل کریں:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    یہ کوڈ کل سیکنڈز کو چیک کرتا ہے، اور اگر یہ 0 ہے، تو فنکشن کال سے واپس آ جاتا ہے تاکہ کوئی ٹائمر سیٹ نہ ہو۔ پھر یہ کل سیکنڈز کو منٹ اور سیکنڈز میں تبدیل کرتا ہے۔

1. اس کوڈ کے نیچے، ٹائمر شروع ہونے پر کہنے کے لیے ایک پیغام بنانے کے لیے درج ذیل شامل کریں:

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

1. اس کے نیچے، ٹائمر ختم ہونے پر کہنے کے لیے ایک پیغام بنانے کے لیے اسی طرح کا کوڈ شامل کریں:

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

1. اس کے بعد، ٹائمر شروع ہونے کا پیغام کہیں:

    ```cpp
    say(begin_message);
    ```

1. اس فنکشن کے آخر میں، ٹائمر شروع کریں:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    یہ ٹائمر کو ٹرگر کرتا ہے۔ ٹائمر ملی سیکنڈز میں سیٹ کیا جاتا ہے، اس لیے کل سیکنڈز کو 1,000 سے ضرب دے کر ملی سیکنڈز میں تبدیل کیا جاتا ہے۔ `timerExpired` فنکشن کو کال بیک کے طور پر پاس کیا جاتا ہے، اور `end_message` کو کال بیک کو پاس کرنے کے لیے ایک آرگومنٹ کے طور پر پاس کیا جاتا ہے۔ یہ کال بیک صرف `void *` آرگومنٹس لیتا ہے، اس لیے اسٹرنگ کو مناسب طریقے سے تبدیل کیا جاتا ہے۔

1. آخر میں، ٹائمر کو *ٹِک* کرنے کی ضرورت ہے، اور یہ `loop` فنکشن میں کیا جاتا ہے۔ `loop` فنکشن کے آخر میں درج ذیل کوڈ شامل کریں:

    ```cpp
    timer.tick();
    ```

1. اس کوڈ کو بنائیں، اسے اپنے وائیو ٹرمینل پر اپ لوڈ کریں اور سیریل مانیٹر کے ذریعے اسے ٹیسٹ کریں۔ جب آپ سیریل مانیٹر میں `Ready` دیکھیں، تو C بٹن دبائیں (جو بائیں جانب ہے، پاور سوئچ کے قریب)، اور بولیں۔ 4 سیکنڈز کی آڈیو کیپچر کی جائے گی، متن میں تبدیل کی جائے گی، پھر آپ کی فنکشن ایپ کو بھیجی جائے گی، اور ایک ٹائمر سیٹ کیا جائے گا۔ یقینی بنائیں کہ آپ کی فنکشن ایپ مقامی طور پر چل رہی ہے۔

    آپ دیکھیں گے کہ ٹائمر کب شروع ہوتا ہے، اور کب ختم ہوتا ہے۔

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

> 💁 آپ اس کوڈ کو [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا ٹائمر پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔