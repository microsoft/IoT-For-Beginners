<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-25T22:09:35+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "fa"
}
-->
# افزودن یک حسگر - Wio Terminal

در این بخش از درس، از حسگر نور موجود در Wio Terminal استفاده خواهید کرد.

## سخت‌افزار

حسگر این درس یک **حسگر نور** است که از یک [فوتودیود](https://wikipedia.org/wiki/Photodiode) برای تبدیل نور به سیگنال الکتریکی استفاده می‌کند. این حسگر آنالوگ است و مقدار عددی بین ۰ تا ۱۰۲۳ ارسال می‌کند که نشان‌دهنده میزان نسبی نور است و به هیچ واحد استانداردی مانند [لوکس](https://wikipedia.org/wiki/Lux) تبدیل نمی‌شود.

حسگر نور در Wio Terminal تعبیه شده و از طریق پنجره شفاف پلاستیکی در پشت دستگاه قابل مشاهده است.

![حسگر نور در پشت Wio Terminal](../../../../../translated_images/fa/wio-light-sensor.b1f529f3c95f5165.png)

## برنامه‌نویسی حسگر نور

اکنون می‌توانید دستگاه را برای استفاده از حسگر نور داخلی برنامه‌نویسی کنید.

### وظیفه

دستگاه را برنامه‌نویسی کنید.

1. پروژه چراغ شبانه را که در بخش قبلی این تمرین در VS Code ایجاد کرده‌اید، باز کنید.

1. خط زیر را به انتهای تابع `setup` اضافه کنید:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    این خط پین‌هایی را که برای ارتباط با سخت‌افزار حسگر استفاده می‌شوند، پیکربندی می‌کند.

    پین `WIO_LIGHT` شماره پین GPIO متصل به حسگر نور داخلی است. این پین به حالت `INPUT` تنظیم شده است، به این معنی که به یک حسگر متصل است و داده‌ها از این پین خوانده می‌شوند.

1. محتوای تابع `loop` را حذف کنید.

1. کد زیر را به تابع `loop` که اکنون خالی است، اضافه کنید.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    این کد یک مقدار آنالوگ از پین `WIO_LIGHT` می‌خواند. این مقدار عددی بین ۰ تا ۱۰۲۳ از حسگر نور داخلی می‌خواند. سپس این مقدار به پورت سریال ارسال می‌شود تا بتوانید آن را در Serial Monitor هنگام اجرای این کد مشاهده کنید. `Serial.print` متن را بدون خط جدید در انتها می‌نویسد، بنابراین هر خط با `Light value:` شروع می‌شود و با مقدار واقعی نور پایان می‌یابد.

1. یک تأخیر کوچک یک ثانیه‌ای (۱۰۰۰ میلی‌ثانیه) در انتهای `loop` اضافه کنید، زیرا نیازی به بررسی مداوم سطح نور نیست. تأخیر باعث کاهش مصرف انرژی دستگاه می‌شود.

    ```cpp
    delay(1000);
    ```

1. Wio Terminal را دوباره به کامپیوتر خود متصل کنید و کد جدید را همان‌طور که قبلاً انجام دادید، آپلود کنید.

1. Serial Monitor را متصل کنید. مقادیر نور به ترمینال خروجی داده می‌شوند. حسگر نور در پشت Wio Terminal را بپوشانید و باز کنید، و مقادیر تغییر خواهند کرد.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 می‌توانید این کد را در پوشه [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal) پیدا کنید.

😀 افزودن یک حسگر به برنامه چراغ شبانه شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حیاتی، توصیه می‌شود از ترجمه انسانی حرفه‌ای استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.