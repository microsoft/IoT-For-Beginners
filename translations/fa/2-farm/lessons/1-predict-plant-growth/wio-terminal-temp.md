<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-25T21:19:59+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "fa"
}
-->
# اندازه‌گیری دما - Wio Terminal

در این بخش از درس، شما یک حسگر دما به Wio Terminal خود اضافه می‌کنید و مقادیر دما را از آن می‌خوانید.

## سخت‌افزار

Wio Terminal به یک حسگر دما نیاز دارد.

حسگری که استفاده می‌کنید، [حسگر رطوبت و دمای DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html) است که دو حسگر را در یک بسته ترکیب می‌کند. این حسگر نسبتاً محبوب است و تعداد زیادی حسگر تجاری موجود هستند که دما، رطوبت و گاهی فشار جوی را ترکیب می‌کنند. بخش حسگر دما یک ترمیستور با ضریب دمای منفی (NTC) است، یعنی ترمیستوری که مقاومت آن با افزایش دما کاهش می‌یابد.

این یک حسگر دیجیتال است، بنابراین دارای یک ADC داخلی است که سیگنال دیجیتالی حاوی داده‌های دما و رطوبت را تولید می‌کند که میکروکنترلر می‌تواند آن را بخواند.

### اتصال حسگر دما

حسگر دمای Grove می‌تواند به پورت دیجیتال Wio Terminal متصل شود.

#### وظیفه - اتصال حسگر دما

حسگر دما را متصل کنید.

![یک حسگر دمای Grove](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.fa.png)

1. یک سر کابل Grove را به سوکت روی حسگر رطوبت و دما وارد کنید. این کابل فقط از یک جهت وارد می‌شود.

1. با قطع اتصال Wio Terminal از کامپیوتر یا منبع تغذیه دیگر، سر دیگر کابل Grove را به سوکت سمت راست Grove روی Wio Terminal متصل کنید (وقتی به صفحه نمایش نگاه می‌کنید). این سوکت دورترین سوکت از دکمه پاور است.

![حسگر دمای Grove متصل به سوکت سمت راست](../../../../../translated_images/wio-temperature-sensor.2934928f38c7f79a68d24879d2c8986c78244696f931e2e33c293f426ecdc0ad.fa.png)

## برنامه‌نویسی حسگر دما

اکنون می‌توانید Wio Terminal را برای استفاده از حسگر دمای متصل برنامه‌نویسی کنید.

### وظیفه - برنامه‌نویسی حسگر دما

دستگاه را برنامه‌نویسی کنید.

1. یک پروژه جدید Wio Terminal با استفاده از PlatformIO ایجاد کنید. این پروژه را `temperature-sensor` بنامید. کدی را در تابع `setup` اضافه کنید تا پورت سریال را پیکربندی کند.

    > ⚠️ می‌توانید به [دستورالعمل‌های ایجاد پروژه PlatformIO در پروژه 1، درس 1 در صورت نیاز مراجعه کنید](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. یک وابستگی کتابخانه برای کتابخانه حسگر رطوبت و دمای Seeed Grove به فایل `platformio.ini` پروژه اضافه کنید:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ می‌توانید به [دستورالعمل‌های افزودن کتابخانه‌ها به پروژه PlatformIO در پروژه 1، درس 4 در صورت نیاز مراجعه کنید](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. دستورات `#include` زیر را به بالای فایل، زیر `#include <Arduino.h>` موجود اضافه کنید:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    این دستورات فایل‌های مورد نیاز برای تعامل با حسگر را وارد می‌کنند. فایل هدر `DHT.h` کد مربوط به خود حسگر را شامل می‌شود و افزودن هدر `SPI.h` تضمین می‌کند که کد مورد نیاز برای ارتباط با حسگر هنگام کامپایل برنامه لینک شود.

1. قبل از تابع `setup`، حسگر DHT را اعلام کنید:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    این یک نمونه از کلاس `DHT` را اعلام می‌کند که حسگر **دیجیتال رطوبت و دما** را مدیریت می‌کند. این حسگر به پورت `D0`، یعنی سوکت سمت راست Grove روی Wio Terminal متصل است. پارامتر دوم به کد می‌گوید که حسگر مورد استفاده *DHT11* است - کتابخانه‌ای که استفاده می‌کنید از انواع دیگر این حسگر نیز پشتیبانی می‌کند.

1. در تابع `setup`، کدی برای تنظیم اتصال سریال اضافه کنید:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. در انتهای تابع `setup`، بعد از آخرین `delay`، یک فراخوانی برای شروع حسگر DHT اضافه کنید:

    ```cpp
    dht.begin();
    ```

1. در تابع `loop`، کدی اضافه کنید که حسگر را فراخوانی کرده و دما را به پورت سریال چاپ کند:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    این کد یک آرایه خالی از 2 عدد اعشاری اعلام می‌کند و آن را به فراخوانی `readTempAndHumidity` روی نمونه `DHT` ارسال می‌کند. این فراخوانی آرایه را با 2 مقدار پر می‌کند - رطوبت در آیتم 0ام آرایه قرار می‌گیرد (به یاد داشته باشید که در C++ آرایه‌ها از 0 شروع می‌شوند، بنابراین آیتم 0ام اولین آیتم آرایه است) و دما در آیتم 1ام قرار می‌گیرد.

    دما از آیتم 1ام آرایه خوانده شده و به پورت سریال چاپ می‌شود.

    > 🇺🇸 دما به صورت سلسیوس خوانده می‌شود. برای آمریکایی‌ها، برای تبدیل این مقدار به فارنهایت، مقدار سلسیوس خوانده شده را بر 5 تقسیم کنید، سپس در 9 ضرب کنید و در نهایت 32 اضافه کنید. برای مثال، یک مقدار دمای 20°C به این صورت تبدیل می‌شود: ((20/5)*9) + 32 = 68°F.

1. کد را بسازید و به Wio Terminal آپلود کنید.

    > ⚠️ می‌توانید به [دستورالعمل‌های ایجاد پروژه PlatformIO در پروژه 1، درس 1 در صورت نیاز مراجعه کنید](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. پس از آپلود، می‌توانید دما را با استفاده از مانیتور سریال مشاهده کنید:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 می‌توانید این کد را در پوشه [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal) پیدا کنید.

😀 برنامه حسگر دمای شما با موفقیت اجرا شد!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه انسانی حرفه‌ای استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.