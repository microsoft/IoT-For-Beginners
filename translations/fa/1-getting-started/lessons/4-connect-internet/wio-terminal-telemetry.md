<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-25T21:59:07+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "fa"
}
-->
# کنترل چراغ خواب خود از طریق اینترنت - Wio Terminal

در این بخش از درس، شما داده‌های تلومتری مربوط به سطح نور را از Wio Terminal خود به MQTT broker ارسال خواهید کرد.

## نصب کتابخانه‌های JSON برای Arduino

یک روش محبوب برای ارسال پیام‌ها از طریق MQTT استفاده از JSON است. یک کتابخانه برای Arduino وجود دارد که خواندن و نوشتن اسناد JSON را آسان‌تر می‌کند.

### وظیفه

کتابخانه JSON برای Arduino را نصب کنید.

1. پروژه چراغ خواب را در VS Code باز کنید.

1. خط زیر را به عنوان یک خط اضافی به لیست `lib_deps` در فایل `platformio.ini` اضافه کنید:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    این کتابخانه [ArduinoJson](https://arduinojson.org)، یک کتابخانه JSON برای Arduino را وارد می‌کند.

## ارسال تلومتری

مرحله بعدی ایجاد یک سند JSON با داده‌های تلومتری و ارسال آن به MQTT broker است.

### وظیفه - ارسال تلومتری

داده‌های تلومتری را به MQTT broker ارسال کنید.

1. کد زیر را به انتهای فایل `config.h` اضافه کنید تا نام موضوع تلومتری برای MQTT broker تعریف شود:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` موضوعی است که دستگاه سطح نور را به آن ارسال خواهد کرد.

1. فایل `main.cpp` را باز کنید.

1. دستور `#include` زیر را به بالای فایل اضافه کنید:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. کد زیر را داخل تابع `loop`، درست قبل از `delay` اضافه کنید:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    این کد سطح نور را می‌خواند و یک سند JSON با استفاده از ArduinoJson ایجاد می‌کند که این سطح را شامل می‌شود. سپس این سند به یک رشته تبدیل شده و توسط کلاینت MQTT در موضوع تلومتری MQTT منتشر می‌شود.

1. کد را به Wio Terminal خود آپلود کنید و از Serial Monitor برای مشاهده سطح نور ارسال شده به MQTT broker استفاده کنید.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 شما می‌توانید این کد را در پوشه [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) پیدا کنید.

😀 شما با موفقیت داده‌های تلومتری را از دستگاه خود ارسال کردید.

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه انسانی حرفه‌ای استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.