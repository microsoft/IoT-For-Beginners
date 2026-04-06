# اندازه‌گیری رطوبت خاک - Wio Terminal

در این بخش از درس، یک حسگر رطوبت خاک خازنی به Wio Terminal خود اضافه می‌کنید و مقادیر آن را می‌خوانید.

## سخت‌افزار

برای Wio Terminal به یک حسگر رطوبت خاک خازنی نیاز دارید.

حسگری که استفاده می‌کنید [حسگر رطوبت خاک خازنی](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html) است که رطوبت خاک را با تشخیص ظرفیت خازنی خاک اندازه‌گیری می‌کند، خاصیتی که با تغییر رطوبت خاک تغییر می‌کند. با افزایش رطوبت خاک، ولتاژ کاهش می‌یابد.

این حسگر آنالوگ است، بنابراین به پین‌های آنالوگ Wio Terminal متصل می‌شود و از مبدل آنالوگ به دیجیتال (ADC) داخلی برای تولید مقداری بین ۰ تا ۱۰۲۳ استفاده می‌کند.

### اتصال حسگر رطوبت خاک

حسگر رطوبت خاک Grove می‌تواند به پورت آنالوگ/دیجیتال قابل تنظیم Wio Terminal متصل شود.

#### وظیفه - اتصال حسگر رطوبت خاک

حسگر رطوبت خاک را متصل کنید.

![یک حسگر رطوبت خاک Grove](../../../../../translated_images/fa/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. یک سر کابل Grove را به سوکت روی حسگر رطوبت خاک وارد کنید. کابل فقط از یک جهت وارد می‌شود.

1. با Wio Terminal که از کامپیوتر یا منبع تغذیه دیگر جدا شده است، سر دیگر کابل Grove را به سوکت سمت راست Wio Terminal متصل کنید (وقتی به صفحه نمایش نگاه می‌کنید). این سوکت دورترین سوکت از دکمه پاور است.

![حسگر رطوبت خاک Grove متصل به سوکت سمت راست](../../../../../translated_images/fa/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. حسگر رطوبت خاک را در خاک قرار دهید. این حسگر یک "خط بالاترین موقعیت" دارد - یک خط سفید روی حسگر. حسگر را تا این خط وارد کنید اما از آن عبور نکنید.

![حسگر رطوبت خاک Grove در خاک](../../../../../translated_images/fa/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. اکنون می‌توانید Wio Terminal را به کامپیوتر خود متصل کنید.

## برنامه‌نویسی حسگر رطوبت خاک

اکنون می‌توانید Wio Terminal را برای استفاده از حسگر رطوبت خاک متصل شده برنامه‌نویسی کنید.

### وظیفه - برنامه‌نویسی حسگر رطوبت خاک

دستگاه را برنامه‌نویسی کنید.

1. یک پروژه جدید Wio Terminal با استفاده از PlatformIO ایجاد کنید. این پروژه را `soil-moisture-sensor` بنامید. کدی را در تابع `setup` اضافه کنید تا پورت سریال را پیکربندی کند.

    > ⚠️ می‌توانید به [دستورالعمل‌های ایجاد پروژه PlatformIO در پروژه ۱، درس ۱ در صورت نیاز مراجعه کنید](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. برای این حسگر کتابخانه‌ای وجود ندارد، بنابراین می‌توانید از پین آنالوگ با استفاده از تابع داخلی Arduino [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) بخوانید. ابتدا پین آنالوگ را برای ورودی پیکربندی کنید تا بتوان مقادیر را از آن خواند. کد زیر را به تابع `setup` اضافه کنید.

    ```cpp
    pinMode(A0, INPUT);
    ```

    این کد پین `A0`، پین ترکیبی آنالوگ/دیجیتال، را به عنوان یک پین ورودی تنظیم می‌کند که می‌توان ولتاژ را از آن خواند.

1. کد زیر را به تابع `loop` اضافه کنید تا ولتاژ را از این پین بخوانید:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. در زیر این کد، کد زیر را اضافه کنید تا مقدار را به پورت سریال چاپ کند:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. در نهایت، یک تأخیر ۱۰ ثانیه‌ای در انتها اضافه کنید:

    ```cpp
    delay(10000);
    ```

1. کد را بسازید و به Wio Terminal آپلود کنید.

    > ⚠️ می‌توانید به [دستورالعمل‌های ایجاد پروژه PlatformIO در پروژه ۱، درس ۱ در صورت نیاز مراجعه کنید](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. پس از آپلود، می‌توانید رطوبت خاک را با استفاده از مانیتور سریال مشاهده کنید. مقداری آب به خاک اضافه کنید یا حسگر را از خاک خارج کنید و تغییر مقدار را مشاهده کنید.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    در خروجی نمونه بالا، می‌توانید کاهش ولتاژ را با اضافه کردن آب مشاهده کنید.

> 💁 می‌توانید این کد را در پوشه [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) پیدا کنید.

😀 برنامه حسگر رطوبت خاک شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه انسانی حرفه‌ای استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.