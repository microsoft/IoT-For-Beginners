<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-25T22:57:07+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "fa"
}
-->
# خواندن داده‌های GPS - Wio Terminal

در این بخش از درس، شما یک حسگر GPS به Wio Terminal اضافه می‌کنید و مقادیر آن را می‌خوانید.

## سخت‌افزار

Wio Terminal به یک حسگر GPS نیاز دارد.

حسگری که استفاده خواهید کرد [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html) است. این حسگر می‌تواند به سیستم‌های مختلف GPS متصل شود تا موقعیت‌یابی سریع و دقیق انجام دهد. این حسگر از دو بخش تشکیل شده است - بخش الکترونیکی اصلی حسگر و یک آنتن خارجی که با یک سیم نازک به حسگر متصل شده تا امواج رادیویی ماهواره‌ها را دریافت کند.

این حسگر از نوع UART است و داده‌های GPS را از طریق UART ارسال می‌کند.

### اتصال حسگر GPS

حسگر Grove GPS می‌تواند به Wio Terminal متصل شود.

#### وظیفه - اتصال حسگر GPS

حسگر GPS را متصل کنید.

![یک حسگر Grove GPS](../../../../../translated_images/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.fa.png)

1. یک سر کابل Grove را به سوکت روی حسگر GPS وارد کنید. کابل فقط از یک جهت وارد سوکت می‌شود.

1. با قطع اتصال Wio Terminal از کامپیوتر یا منبع تغذیه دیگر، سر دیگر کابل Grove را به سوکت سمت چپ Wio Terminal متصل کنید. این سوکت نزدیک‌ترین سوکت به دکمه پاور است.

    ![حسگر Grove GPS متصل به سوکت سمت چپ](../../../../../translated_images/wio-gps-sensor.19fd52b81ce58095d5deb3d4e5a1fdd88818d76569b00b1f0d740c92dc986525.fa.png)

1. حسگر GPS را در موقعیتی قرار دهید که آنتن متصل به آن دید به آسمان داشته باشد - ترجیحاً کنار یک پنجره باز یا در فضای باز. دریافت سیگنال واضح‌تر زمانی آسان‌تر است که چیزی مانع آنتن نباشد.

1. اکنون می‌توانید Wio Terminal را به کامپیوتر خود متصل کنید.

1. حسگر GPS دارای دو LED است - یک LED آبی که هنگام ارسال داده چشمک می‌زند و یک LED سبز که هر ثانیه هنگام دریافت داده از ماهواره‌ها چشمک می‌زند. مطمئن شوید که LED آبی هنگام روشن کردن Wio Terminal چشمک می‌زند. پس از چند دقیقه، LED سبز شروع به چشمک زدن می‌کند - اگر این اتفاق نیفتاد، ممکن است نیاز باشد آنتن را جابجا کنید.

## برنامه‌نویسی حسگر GPS

اکنون می‌توانید Wio Terminal را برای استفاده از حسگر GPS متصل شده برنامه‌نویسی کنید.

### وظیفه - برنامه‌نویسی حسگر GPS

دستگاه را برنامه‌نویسی کنید.

1. یک پروژه جدید Wio Terminal با استفاده از PlatformIO ایجاد کنید. نام این پروژه را `gps-sensor` بگذارید. کدی در تابع `setup` اضافه کنید تا پورت سریال تنظیم شود.

1. دستور زیر را در بالای فایل `main.cpp` اضافه کنید. این دستور یک فایل هدر شامل توابعی برای تنظیم پورت Grove سمت چپ برای UART را وارد می‌کند.

    ```cpp
    #include <wiring_private.h>
    ```

1. در زیر این دستور، خط کد زیر را اضافه کنید تا یک اتصال پورت سریال به پورت UART اعلام شود:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. باید کدی اضافه کنید تا برخی از هندلرهای سیگنال داخلی به این پورت سریال هدایت شوند. کد زیر را در زیر اعلامیه `Serial3` اضافه کنید:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. در تابع `setup`، در زیر جایی که پورت `Serial` تنظیم شده است، پورت سریال UART را با کد زیر تنظیم کنید:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. در زیر این کد در تابع `setup`، کد زیر را اضافه کنید تا پین Grove به پورت سریال متصل شود:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. تابع زیر را قبل از تابع `loop` اضافه کنید تا داده‌های GPS را به مانیتور سریال ارسال کند:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. در تابع `loop`، کد زیر را اضافه کنید تا داده‌ها را از پورت سریال UART بخواند و خروجی را به مانیتور سریال چاپ کند:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    این کد داده‌ها را از پورت سریال UART می‌خواند. تابع `readStringUntil` تا یک کاراکتر پایانی، در اینجا یک خط جدید، می‌خواند. این کار یک جمله کامل NMEA را می‌خواند (جملات NMEA با یک کاراکتر خط جدید خاتمه می‌یابند). تا زمانی که داده‌ها از پورت سریال UART قابل خواندن باشند، خوانده شده و از طریق تابع `printGPSData` به مانیتور سریال ارسال می‌شوند. زمانی که دیگر داده‌ای قابل خواندن نباشد، `loop` برای 1 ثانیه (1000 میلی‌ثانیه) تأخیر می‌اندازد.

1. کد را بسازید و به Wio Terminal آپلود کنید.

1. پس از آپلود، می‌توانید داده‌های GPS را با استفاده از مانیتور سریال مشاهده کنید.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 شما می‌توانید این کد را در پوشه [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal) پیدا کنید.

😀 برنامه حسگر GPS شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه حرفه‌ای انسانی استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.