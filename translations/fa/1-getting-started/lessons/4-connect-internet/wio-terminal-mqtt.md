<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-25T22:01:02+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "fa"
}
-->
# کنترل چراغ خواب از طریق اینترنت - Wio Terminal

دستگاه IoT باید به گونه‌ای برنامه‌ریزی شود که با استفاده از MQTT به *test.mosquitto.org* متصل شود تا مقادیر تله‌متری را با خواندن حسگر نور ارسال کرده و دستورات را برای کنترل LED دریافت کند.

در این بخش از درس، شما Wio Terminal خود را به یک MQTT broker متصل خواهید کرد.

## نصب کتابخانه‌های WiFi و MQTT برای Arduino

برای ارتباط با MQTT broker، باید چند کتابخانه Arduino نصب کنید تا بتوانید از چیپ WiFi در Wio Terminal استفاده کرده و با MQTT ارتباط برقرار کنید. هنگام توسعه برای دستگاه‌های Arduino، می‌توانید از طیف گسترده‌ای از کتابخانه‌ها که شامل کدهای متن‌باز هستند و قابلیت‌های متنوعی را پیاده‌سازی می‌کنند، استفاده کنید. شرکت Seeed کتابخانه‌هایی برای Wio Terminal منتشر کرده است که امکان ارتباط از طریق WiFi را فراهم می‌کند. توسعه‌دهندگان دیگر نیز کتابخانه‌هایی برای ارتباط با MQTT brokerها منتشر کرده‌اند که شما از این کتابخانه‌ها در دستگاه خود استفاده خواهید کرد.

این کتابخانه‌ها به صورت کد منبع ارائه می‌شوند که می‌توانند به صورت خودکار به PlatformIO وارد شده و برای دستگاه شما کامپایل شوند. به این ترتیب، کتابخانه‌های Arduino روی هر دستگاهی که از چارچوب Arduino پشتیبانی می‌کند کار خواهند کرد، به شرطی که دستگاه سخت‌افزار خاص مورد نیاز آن کتابخانه را داشته باشد. برخی کتابخانه‌ها، مانند کتابخانه‌های WiFi شرکت Seeed، مختص سخت‌افزار خاصی هستند.

کتابخانه‌ها می‌توانند به صورت کلی نصب شده و در صورت نیاز کامپایل شوند، یا به یک پروژه خاص اضافه شوند. برای این تمرین، کتابخانه‌ها به پروژه اضافه خواهند شد.

✅ می‌توانید اطلاعات بیشتری درباره مدیریت کتابخانه‌ها و نحوه یافتن و نصب آن‌ها در [مستندات کتابخانه PlatformIO](https://docs.platformio.org/en/latest/librarymanager/index.html) بیابید.

### وظیفه - نصب کتابخانه‌های WiFi و MQTT برای Arduino

کتابخانه‌های Arduino را نصب کنید.

1. پروژه چراغ خواب را در VS Code باز کنید.

1. موارد زیر را به انتهای فایل `platformio.ini` اضافه کنید:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    این کد کتابخانه‌های WiFi شرکت Seeed را وارد می‌کند. نحوۀ `@ <number>` به یک نسخه خاص از کتابخانه اشاره دارد.

    > 💁 می‌توانید `@ <number>` را حذف کنید تا همیشه از آخرین نسخه کتابخانه‌ها استفاده شود، اما تضمینی وجود ندارد که نسخه‌های بعدی با کد زیر کار کنند. کد اینجا با این نسخه از کتابخانه‌ها تست شده است.

    این تمام کاری است که برای اضافه کردن کتابخانه‌ها باید انجام دهید. دفعه بعد که PlatformIO پروژه را کامپایل کند، کد منبع این کتابخانه‌ها را دانلود کرده و به پروژه شما اضافه می‌کند.

1. موارد زیر را به `lib_deps` اضافه کنید:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    این کد [PubSubClient](https://github.com/knolleary/pubsubclient)، یک کلاینت MQTT برای Arduino را وارد می‌کند.

## اتصال به WiFi

اکنون Wio Terminal می‌تواند به WiFi متصل شود.

### وظیفه - اتصال به WiFi

Wio Terminal را به WiFi متصل کنید.

1. یک فایل جدید در پوشه `src` به نام `config.h` ایجاد کنید. می‌توانید این کار را با انتخاب پوشه `src` یا فایل `main.cpp` داخل آن و کلیک روی دکمه **New file** از اکسپلورر انجام دهید. این دکمه فقط زمانی ظاهر می‌شود که نشانگر شما روی اکسپلورر باشد.

    ![دکمه فایل جدید](../../../../../translated_images/fa/vscode-new-file-button.182702340fe6723c.png)

1. کد زیر را به این فایل اضافه کنید تا مقادیر ثابت برای اطلاعات WiFi شما تعریف شود:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    `<SSID>` را با SSID شبکه WiFi خود جایگزین کنید. `<PASSWORD>` را با رمز عبور WiFi خود جایگزین کنید.

1. فایل `main.cpp` را باز کنید.

1. دستورات `#include` زیر را به بالای فایل اضافه کنید:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    این دستورات فایل‌های هدر کتابخانه‌هایی که قبلاً اضافه کردید و همچنین فایل هدر تنظیمات را وارد می‌کنند. این فایل‌های هدر برای اطلاع دادن به PlatformIO برای وارد کردن کد از کتابخانه‌ها لازم هستند. بدون وارد کردن صریح این فایل‌های هدر، برخی کدها کامپایل نمی‌شوند و خطاهای کامپایلر دریافت خواهید کرد.

1. کد زیر را بالای تابع `setup` اضافه کنید:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    این کد در حالی که دستگاه به WiFi متصل نیست، حلقه می‌زند و تلاش می‌کند با استفاده از SSID و رمز عبور از فایل تنظیمات متصل شود.

1. یک فراخوانی به این تابع در انتهای تابع `setup`، پس از پیکربندی پین‌ها اضافه کنید.

    ```cpp
    connectWiFi();
    ```

1. این کد را به دستگاه خود آپلود کنید تا بررسی کنید اتصال WiFi کار می‌کند. باید این موارد را در مانیتور سریال ببینید.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## اتصال به MQTT

پس از اتصال Wio Terminal به WiFi، می‌تواند به MQTT broker متصل شود.

### وظیفه - اتصال به MQTT

به MQTT broker متصل شوید.

1. کد زیر را به انتهای فایل `config.h` اضافه کنید تا جزئیات اتصال به MQTT broker تعریف شود:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    `<ID>` را با یک شناسه منحصربه‌فرد جایگزین کنید که به عنوان نام این کلاینت دستگاه استفاده خواهد شد و بعداً برای موضوعاتی که این دستگاه منتشر و مشترک می‌شود استفاده خواهد شد. *test.mosquitto.org* یک broker عمومی است که توسط افراد زیادی، از جمله دانشجویان دیگر که این تمرین را انجام می‌دهند، استفاده می‌شود. داشتن یک نام کلاینت MQTT و نام موضوعات منحصربه‌فرد تضمین می‌کند که کد شما با کد دیگران تداخل نداشته باشد. شما همچنین به این شناسه هنگام ایجاد کد سرور در ادامه این تمرین نیاز خواهید داشت.

    > 💁 می‌توانید از وب‌سایتی مانند [GUIDGen](https://www.guidgen.com) برای تولید یک شناسه منحصربه‌فرد استفاده کنید.

    `BROKER` آدرس URL MQTT broker است.

    `CLIENT_NAME` یک نام منحصربه‌فرد برای این کلاینت MQTT در broker است.

1. فایل `main.cpp` را باز کنید و کد زیر را زیر تابع `connectWiFi` و بالای تابع `setup` اضافه کنید:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    این کد یک کلاینت WiFi با استفاده از کتابخانه‌های WiFi Wio Terminal ایجاد کرده و از آن برای ایجاد یک کلاینت MQTT استفاده می‌کند.

1. کد زیر را در زیر این کد اضافه کنید:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    این تابع اتصال به MQTT broker را تست کرده و در صورت عدم اتصال، دوباره متصل می‌شود. این تابع در حالی که متصل نیست حلقه می‌زند و تلاش می‌کند با استفاده از نام کلاینت منحصربه‌فرد تعریف‌شده در فایل تنظیمات متصل شود.

    اگر اتصال ناموفق باشد، پس از 5 ثانیه دوباره تلاش می‌کند.

1. کد زیر را زیر تابع `reconnectMQTTClient` اضافه کنید:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    این کد MQTT broker را برای کلاینت تنظیم کرده و همچنین callback را برای زمانی که پیامی دریافت می‌شود تنظیم می‌کند. سپس تلاش می‌کند به broker متصل شود.

1. تابع `createMQTTClient` را در تابع `setup` پس از اتصال WiFi فراخوانی کنید.

1. کل تابع `loop` را با کد زیر جایگزین کنید:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    این کد با اتصال مجدد به MQTT broker شروع می‌شود. این اتصالات به راحتی می‌توانند قطع شوند، بنابراین ارزش دارد که به طور منظم بررسی و در صورت لزوم دوباره متصل شوید. سپس متد `loop` را روی کلاینت MQTT فراخوانی می‌کند تا هر پیامی که در موضوع مشترک‌شده دریافت شده پردازش شود. این برنامه تک‌ریسمانی است، بنابراین پیام‌ها نمی‌توانند در یک ریسمان پس‌زمینه دریافت شوند، بنابراین باید زمانی در ریسمان اصلی برای پردازش پیام‌های منتظر در اتصال شبکه تخصیص داده شود.

    در نهایت، یک تأخیر 2 ثانیه‌ای تضمین می‌کند که سطح نور بیش از حد ارسال نشود و مصرف انرژی دستگاه کاهش یابد.

1. کد را به Wio Terminal خود آپلود کنید و از مانیتور سریال برای مشاهده اتصال دستگاه به WiFi و MQTT استفاده کنید.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 می‌توانید این کد را در پوشه [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) پیدا کنید.

😀 شما با موفقیت دستگاه خود را به یک MQTT broker متصل کردید.

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه انسانی حرفه‌ای استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.