<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-25T22:37:13+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "fa"
}
-->
# تنظیم تایمر - Wio Terminal

در این بخش از درس، کد سرورلس خود را فراخوانی می‌کنید تا گفتار را تشخیص دهد و بر اساس نتایج، یک تایمر روی Wio Terminal تنظیم کنید.

## تنظیم تایمر

متنی که از فراخوانی تبدیل گفتار به متن بازمی‌گردد باید به کد سرورلس شما ارسال شود تا توسط LUIS پردازش شود و تعداد ثانیه‌های تایمر را بازگرداند. این تعداد ثانیه‌ها می‌تواند برای تنظیم تایمر استفاده شود.

میکروکنترلرها به طور پیش‌فرض از چندین رشته (threads) در Arduino پشتیبانی نمی‌کنند، بنابراین کلاس‌های تایمر استانداردی مانند آنچه در زبان‌هایی مثل Python یا دیگر زبان‌های سطح بالا وجود دارد، ندارند. در عوض، می‌توانید از کتابخانه‌های تایمر استفاده کنید که با اندازه‌گیری زمان سپری‌شده در تابع `loop` کار می‌کنند و پس از اتمام زمان، توابع را فراخوانی می‌کنند.

### وظیفه - ارسال متن به تابع سرورلس

1. اگر پروژه `smart-timer` در VS Code باز نیست، آن را باز کنید.

1. فایل هدر `config.h` را باز کنید و URL مربوط به برنامه تابع خود را اضافه کنید:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    `<URL>` را با URL برنامه تابع خود که در مرحله آخر درس قبلی به دست آوردید جایگزین کنید، به گونه‌ای که به آدرس IP دستگاه محلی شما که برنامه تابع را اجرا می‌کند اشاره کند.

1. یک فایل جدید در پوشه `src` با نام `language_understanding.h` ایجاد کنید. این فایل برای تعریف کلاسی استفاده می‌شود که گفتار تشخیص داده‌شده را به برنامه تابع شما ارسال کند تا توسط LUIS به ثانیه تبدیل شود.

1. موارد زیر را به بالای این فایل اضافه کنید:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    این کد شامل برخی فایل‌های هدر موردنیاز است.

1. کلاسی به نام `LanguageUnderstanding` تعریف کنید و یک نمونه از این کلاس اعلام کنید:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. برای فراخوانی برنامه تابع خود، باید یک WiFi client اعلام کنید. موارد زیر را به بخش `private` کلاس اضافه کنید:

    ```cpp
    WiFiClient _client;
    ```

1. در بخش `public`، یک متد به نام `GetTimerDuration` برای فراخوانی برنامه تابع اعلام کنید:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. در متد `GetTimerDuration`، کد زیر را برای ساخت JSON که به برنامه تابع ارسال می‌شود اضافه کنید:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    این کد متن ارسال‌شده به متد `GetTimerDuration` را به JSON زیر تبدیل می‌کند:

    ```json
    {
        "text" : "<text>"
    }
    ```

    که در آن `<text>` متنی است که به تابع ارسال شده است.

1. در زیر این کد، کد زیر را برای فراخوانی برنامه تابع اضافه کنید:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    این کد یک درخواست POST به برنامه تابع ارسال می‌کند، بدنه JSON را ارسال کرده و کد پاسخ را دریافت می‌کند.

1. کد زیر را در زیر این بخش اضافه کنید:

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

    این کد کد پاسخ را بررسی می‌کند. اگر کد 200 (موفقیت) باشد، تعداد ثانیه‌های تایمر از بدنه پاسخ دریافت می‌شود. در غیر این صورت، یک خطا به مانیتور سریال ارسال شده و تعداد ثانیه‌ها به 0 تنظیم می‌شود.

1. کد زیر را به انتهای این متد اضافه کنید تا اتصال HTTP بسته شود و تعداد ثانیه‌ها بازگردانده شود:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. در فایل `main.cpp`، این هدر جدید را اضافه کنید:

    ```cpp
    #include "speech_to_text.h"
    ```

1. در انتهای تابع `processAudio`، متد `GetTimerDuration` را برای دریافت مدت زمان تایمر فراخوانی کنید:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    این کد متن حاصل از فراخوانی کلاس `SpeechToText` را به تعداد ثانیه‌های تایمر تبدیل می‌کند.

### وظیفه - تنظیم تایمر

تعداد ثانیه‌ها می‌تواند برای تنظیم تایمر استفاده شود.

1. وابستگی کتابخانه زیر را به فایل `platformio.ini` اضافه کنید تا یک کتابخانه برای تنظیم تایمر اضافه شود:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. یک دستور include برای این کتابخانه به فایل `main.cpp` اضافه کنید:

    ```cpp
    #include <arduino-timer.h>
    ```

1. بالای تابع `processAudio`، کد زیر را اضافه کنید:

    ```cpp
    auto timer = timer_create_default();
    ```

    این کد یک تایمر به نام `timer` اعلام می‌کند.

1. کد زیر را در زیر این بخش اضافه کنید:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    این تابع `say` در نهایت متن را به گفتار تبدیل می‌کند، اما در حال حاضر فقط متن ارسال‌شده را به مانیتور سریال می‌نویسد.

1. کد زیر را در زیر تابع `say` اضافه کنید:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    این یک تابع callback است که وقتی تایمر منقضی می‌شود فراخوانی می‌شود. این تابع پیامی را که باید هنگام انقضای تایمر گفته شود دریافت می‌کند. تایمرها می‌توانند تکرار شوند و این موضوع با مقدار بازگشتی این callback کنترل می‌شود - این مقدار `false` بازمی‌گرداند تا به تایمر بگوید دوباره اجرا نشود.

1. کد زیر را به انتهای تابع `processAudio` اضافه کنید:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    این کد تعداد کل ثانیه‌ها را بررسی می‌کند و اگر 0 باشد، از فراخوانی تابع بازمی‌گردد تا هیچ تایمری تنظیم نشود. سپس تعداد کل ثانیه‌ها را به دقیقه و ثانیه تبدیل می‌کند.

1. کد زیر را در زیر این بخش اضافه کنید تا پیامی برای اعلام شروع تایمر ایجاد شود:

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

1. کد مشابهی را در زیر این بخش اضافه کنید تا پیامی برای اعلام انقضای تایمر ایجاد شود:

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

1. پس از این، پیام شروع تایمر را اعلام کنید:

    ```cpp
    say(begin_message);
    ```

1. در انتهای این تابع، تایمر را شروع کنید:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    این کد تایمر را فعال می‌کند. تایمر با استفاده از میلی‌ثانیه تنظیم می‌شود، بنابراین تعداد کل ثانیه‌ها در 1,000 ضرب می‌شود تا به میلی‌ثانیه تبدیل شود. تابع `timerExpired` به عنوان callback ارسال می‌شود و `end_message` به عنوان آرگومان برای ارسال به callback ارسال می‌شود. این callback فقط آرگومان‌های `void *` می‌گیرد، بنابراین رشته به طور مناسب تبدیل می‌شود.

1. در نهایت، تایمر باید *تیک* بزند و این کار در تابع `loop` انجام می‌شود. کد زیر را به انتهای تابع `loop` اضافه کنید:

    ```cpp
    timer.tick();
    ```

1. این کد را بسازید، آن را روی Wio Terminal خود آپلود کنید و از طریق مانیتور سریال آن را آزمایش کنید. وقتی `Ready` را در مانیتور سریال مشاهده کردید، دکمه C (دکمه سمت چپ، نزدیک به کلید پاور) را فشار دهید و صحبت کنید. 4 ثانیه صدا ضبط می‌شود، به متن تبدیل می‌شود، سپس به برنامه تابع شما ارسال می‌شود و یک تایمر تنظیم می‌شود. مطمئن شوید که برنامه تابع شما به صورت محلی در حال اجرا است.

    شما خواهید دید که تایمر چه زمانی شروع می‌شود و چه زمانی پایان می‌یابد.

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

> 💁 می‌توانید این کد را در پوشه [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) پیدا کنید.

😀 برنامه تایمر شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه انسانی حرفه‌ای استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.