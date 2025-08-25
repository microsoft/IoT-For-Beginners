<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-25T23:03:10+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "fa"
}
-->
# رمزگشایی داده‌های GPS - Wio Terminal

در این بخش از درس، پیام‌های NMEA خوانده شده از حسگر GPS توسط Wio Terminal را رمزگشایی کرده و عرض و طول جغرافیایی را استخراج خواهید کرد.

## رمزگشایی داده‌های GPS

پس از خواندن داده‌های خام NMEA از پورت سریال، می‌توان آن‌ها را با استفاده از یک کتابخانه متن‌باز NMEA رمزگشایی کرد.

### وظیفه - رمزگشایی داده‌های GPS

دستگاه را برنامه‌ریزی کنید تا داده‌های GPS را رمزگشایی کند.

1. اگر پروژه اپلیکیشن `gps-sensor` باز نیست، آن را باز کنید.

1. یک وابستگی کتابخانه‌ای برای کتابخانه [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) به فایل `platformio.ini` پروژه اضافه کنید. این کتابخانه کدی برای رمزگشایی داده‌های NMEA دارد.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. در فایل `main.cpp`، یک دستور include برای کتابخانه TinyGPSPlus اضافه کنید:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. زیر اعلان `Serial3`، یک شیء TinyGPSPlus برای پردازش جملات NMEA اعلام کنید:

    ```cpp
    TinyGPSPlus gps;
    ```

1. محتوای تابع `printGPSData` را به موارد زیر تغییر دهید:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    این کد کاراکتر بعدی را از پورت سریال UART به رمزگشای NMEA `gps` می‌خواند. پس از هر کاراکتر، بررسی می‌کند که آیا رمزگشا یک جمله معتبر خوانده است یا خیر، سپس بررسی می‌کند که آیا مکان معتبر خوانده شده است. اگر مکان معتبر باشد، آن را همراه با تعداد ماهواره‌هایی که در این موقعیت نقش داشته‌اند، به مانیتور سریال ارسال می‌کند.

1. کد را بسازید و به Wio Terminal آپلود کنید.

1. پس از آپلود، می‌توانید داده‌های مکان GPS را با استفاده از مانیتور سریال مشاهده کنید.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 می‌توانید این کد را در پوشه [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) پیدا کنید.

😀 برنامه حسگر GPS شما با رمزگشایی داده‌ها موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه حرفه‌ای انسانی استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.