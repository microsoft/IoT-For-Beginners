<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-25T21:20:45+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "fa"
}
-->
# انتشار دما - Wio Terminal

در این بخش از درس، دماهایی که توسط Wio Terminal شناسایی شده‌اند را از طریق MQTT منتشر می‌کنید تا بعداً بتوان از آن‌ها برای محاسبه GDD استفاده کرد.

## انتشار دما

پس از خواندن دما، می‌توان آن را از طریق MQTT به کدی که به‌عنوان 'سرور' عمل می‌کند ارسال کرد. این کد مقادیر را می‌خواند و ذخیره می‌کند تا برای محاسبه GDD آماده باشد. میکروکنترلرها به‌طور پیش‌فرض زمان را از اینترنت نمی‌خوانند و زمان را با یک ساعت واقعی ردیابی نمی‌کنند، بنابراین دستگاه باید برای این کار برنامه‌ریزی شود، به شرطی که سخت‌افزار لازم را داشته باشد.

برای ساده‌تر کردن این درس، زمان همراه با داده‌های حسگر ارسال نمی‌شود. در عوض، می‌توان آن را بعداً توسط کد سرور هنگام دریافت پیام‌ها اضافه کرد.

### وظیفه

دستگاه را برای انتشار داده‌های دما برنامه‌ریزی کنید.

1. پروژه `temperature-sensor` Wio Terminal را باز کنید.

1. مراحل انجام‌شده در درس ۴ برای اتصال به MQTT و ارسال تله‌متری را تکرار کنید. شما از همان Mosquitto broker عمومی استفاده خواهید کرد.

    مراحل این کار عبارتند از:

    - افزودن کتابخانه‌های Seeed WiFi و MQTT به فایل `.ini`
    - افزودن فایل پیکربندی و کد برای اتصال به WiFi
    - افزودن کد برای اتصال به MQTT broker
    - افزودن کد برای انتشار تله‌متری

    > ⚠️ به [دستورالعمل‌های اتصال به MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) و [دستورالعمل‌های ارسال تله‌متری](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) از درس ۴ در صورت نیاز مراجعه کنید.

1. مطمئن شوید که `CLIENT_NAME` در فایل هدر `config.h` منعکس‌کننده این پروژه است:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. برای تله‌متری، به‌جای ارسال مقدار نور، مقدار دمای خوانده‌شده از حسگر DHT را در یک ویژگی به نام `temperature` در سند JSON ارسال کنید. این کار را با تغییر تابع `loop` در `main.cpp` انجام دهید:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. نیازی نیست مقدار دما خیلی زود به زود خوانده شود - دما در مدت زمان کوتاه تغییر زیادی نمی‌کند. بنابراین، مقدار `delay` در تابع `loop` را به ۱۰ دقیقه تنظیم کنید:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 تابع `delay` زمان را به میلی‌ثانیه می‌گیرد، بنابراین برای خواندن راحت‌تر، مقدار به‌صورت نتیجه یک محاسبه ارسال می‌شود. ۱۰۰۰ میلی‌ثانیه در یک ثانیه، ۶۰ ثانیه در یک دقیقه، بنابراین ۱۰ x (۶۰ ثانیه در یک دقیقه) x (۱۰۰۰ میلی‌ثانیه در یک ثانیه) یک تأخیر ۱۰ دقیقه‌ای می‌دهد.

1. این کد را به Wio Terminal خود آپلود کنید و از مانیتور سریال برای مشاهده ارسال دما به MQTT broker استفاده کنید.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 می‌توانید این کد را در پوشه [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) پیدا کنید.

😀 شما با موفقیت دما را به‌عنوان تله‌متری از دستگاه خود منتشر کردید.

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه انسانی حرفه‌ای استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.