<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-25T21:47:57+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "fa"
}
-->
# اتصال دستگاه IoT شما به ابر - Wio Terminal

در این بخش از درس، شما Wio Terminal خود را به IoT Hub متصل می‌کنید تا داده‌های تله‌متری ارسال کرده و دستورات دریافت کنید.

## اتصال دستگاه به IoT Hub

گام بعدی اتصال دستگاه شما به IoT Hub است.

### وظیفه - اتصال به IoT Hub

1. پروژه `soil-moisture-sensor` را در VS Code باز کنید.

1. فایل `platformio.ini` را باز کنید. وابستگی کتابخانه `knolleary/PubSubClient` را حذف کنید. این کتابخانه برای اتصال به بروکر عمومی MQTT استفاده می‌شد و برای اتصال به IoT Hub نیازی به آن نیست.

1. وابستگی‌های کتابخانه زیر را اضافه کنید:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    کتابخانه `Seeed Arduino RTC` کدی برای تعامل با ساعت واقعی در Wio Terminal فراهم می‌کند که برای ردیابی زمان استفاده می‌شود. سایر کتابخانه‌ها به دستگاه IoT شما اجازه می‌دهند به IoT Hub متصل شود.

1. مورد زیر را به انتهای فایل `platformio.ini` اضافه کنید:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    این یک فلگ کامپایلر تنظیم می‌کند که هنگام کامپایل کد Arduino IoT Hub مورد نیاز است.

1. فایل هدر `config.h` را باز کنید. تمام تنظیمات MQTT را حذف کرده و ثابت زیر را برای رشته اتصال دستگاه اضافه کنید:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    `<connection string>` را با رشته اتصال دستگاه خود که قبلاً کپی کرده‌اید جایگزین کنید.

1. اتصال به IoT Hub از یک توکن مبتنی بر زمان استفاده می‌کند. این بدان معناست که دستگاه IoT باید زمان فعلی را بداند. برخلاف سیستم‌عامل‌هایی مانند ویندوز، macOS یا لینوکس، میکروکنترلرها به‌طور خودکار زمان فعلی را از طریق اینترنت همگام‌سازی نمی‌کنند. بنابراین باید کدی اضافه کنید تا زمان فعلی را از یک [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) سرور دریافت کند. پس از دریافت زمان، می‌توان آن را در یک ساعت واقعی در Wio Terminal ذخیره کرد، به‌طوری که زمان صحیح در تاریخ بعدی درخواست شود، به شرطی که دستگاه برق خود را از دست ندهد. یک فایل جدید به نام `ntp.h` با کد زیر اضافه کنید:

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    جزئیات این کد خارج از محدوده این درس است. این کدی را تعریف می‌کند که تابعی به نام `initTime` دارد که زمان فعلی را از یک سرور NTP دریافت کرده و از آن برای تنظیم ساعت در Wio Terminal استفاده می‌کند.

1. فایل `main.cpp` را باز کنید و تمام کدهای MQTT، از جمله فایل هدر `PubSubClient.h`، اعلان متغیر `PubSubClient`، متدهای `reconnectMQTTClient` و `createMQTTClient` و هرگونه فراخوانی به این متغیرها و متدها را حذف کنید. این فایل باید فقط شامل کدی برای اتصال به WiFi، دریافت رطوبت خاک و ایجاد یک سند JSON با آن باشد.

1. دستورات `#include` زیر را به بالای فایل `main.cpp` اضافه کنید تا فایل‌های هدر برای کتابخانه‌های IoT Hub و تنظیم زمان را شامل شود:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. فراخوانی زیر را به انتهای تابع `setup` اضافه کنید تا زمان فعلی تنظیم شود:

    ```cpp
    initTime();
    ```

1. اعلان متغیر زیر را به بالای فایل، درست زیر دستورات include اضافه کنید:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    این یک `IOTHUB_DEVICE_CLIENT_LL_HANDLE` را اعلام می‌کند، که یک هندل برای اتصال به IoT Hub است.

1. کد زیر را در زیر این اعلان اضافه کنید:

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    این یک تابع callback اعلام می‌کند که وقتی اتصال به IoT Hub وضعیت خود را تغییر می‌دهد، مانند اتصال یا قطع اتصال، فراخوانی می‌شود. وضعیت به پورت سریال ارسال می‌شود.

1. در زیر این، یک تابع برای اتصال به IoT Hub اضافه کنید:

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    این کد کتابخانه IoT Hub را مقداردهی اولیه می‌کند، سپس با استفاده از رشته اتصال در فایل هدر `config.h` یک اتصال ایجاد می‌کند. این اتصال بر اساس MQTT است. اگر اتصال شکست بخورد، این موضوع به پورت سریال ارسال می‌شود - اگر این را در خروجی مشاهده کردید، رشته اتصال را بررسی کنید. در نهایت، callback وضعیت اتصال تنظیم می‌شود.

1. این تابع را در تابع `setup` زیر فراخوانی `initTime` فراخوانی کنید:

    ```cpp
    connectIoTHub();
    ```

1. درست مانند کلاینت MQTT، این کد روی یک رشته واحد اجرا می‌شود، بنابراین برای پردازش پیام‌هایی که توسط هاب ارسال و دریافت می‌شوند، به زمان نیاز دارد. مورد زیر را به بالای تابع `loop` اضافه کنید تا این کار انجام شود:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. این کد را بسازید و آپلود کنید. اتصال را در مانیتور سریال مشاهده خواهید کرد:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    در خروجی می‌توانید مشاهده کنید که زمان NTP دریافت می‌شود، سپس کلاینت دستگاه متصل می‌شود. ممکن است چند ثانیه طول بکشد تا اتصال برقرار شود، بنابراین ممکن است رطوبت خاک را در خروجی مشاهده کنید در حالی که دستگاه در حال اتصال است.

    > 💁 می‌توانید زمان یونیکس NTP را به نسخه‌ای خواناتر با استفاده از وب‌سایتی مانند [unixtimestamp.com](https://www.unixtimestamp.com) تبدیل کنید.

## ارسال تله‌متری

اکنون که دستگاه شما متصل است، می‌توانید تله‌متری را به IoT Hub ارسال کنید، به جای بروکر MQTT.

### وظیفه - ارسال تله‌متری

1. تابع زیر را بالای تابع `setup` اضافه کنید:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    این کد یک پیام IoT Hub از یک رشته که به‌عنوان پارامتر ارسال شده ایجاد می‌کند، آن را به هاب ارسال می‌کند، سپس شیء پیام را پاک می‌کند.

1. این کد را در تابع `loop`، درست بعد از خطی که تله‌متری به پورت سریال ارسال می‌شود، فراخوانی کنید:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## مدیریت دستورات

دستگاه شما باید دستوری از کد سرور برای کنترل رله دریافت کند. این دستور به‌عنوان یک درخواست متد مستقیم ارسال می‌شود.

### وظیفه - مدیریت یک درخواست متد مستقیم

1. کد زیر را قبل از تابع `connectIoTHub` اضافه کنید:

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    این کد یک متد callback تعریف می‌کند که کتابخانه IoT Hub می‌تواند هنگام دریافت یک درخواست متد مستقیم آن را فراخوانی کند. متدی که درخواست شده در پارامتر `method_name` ارسال می‌شود. این تابع متد فراخوانی شده را به پورت سریال چاپ می‌کند، سپس بسته به نام متد، رله را روشن یا خاموش می‌کند.

    > 💁 این می‌توانست در یک درخواست متد مستقیم واحد نیز پیاده‌سازی شود، با ارسال وضعیت مورد نظر رله در یک payload که می‌تواند با درخواست متد ارسال شود و از پارامتر `payload` در دسترس باشد.

1. کد زیر را به انتهای تابع `directMethodCallback` اضافه کنید:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    درخواست‌های متد مستقیم به یک پاسخ نیاز دارند، و پاسخ در دو بخش است - یک پاسخ به‌صورت متن و یک کد بازگشتی. این کد یک نتیجه به‌صورت سند JSON زیر ایجاد می‌کند:

    ```JSON
    {
        "Result": ""
    }
    ```

    سپس این نتیجه در پارامتر `response` کپی می‌شود و اندازه این پاسخ در پارامتر `response_size` تنظیم می‌شود. این کد سپس `IOTHUB_CLIENT_OK` را بازمی‌گرداند تا نشان دهد متد به‌درستی مدیریت شده است.

1. callback را با اضافه کردن مورد زیر به انتهای تابع `connectIoTHub` متصل کنید:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. تابع `loop` تابع `IoTHubDeviceClient_LL_DoWork` را برای پردازش رویدادهای ارسال شده توسط IoT Hub فراخوانی می‌کند. این تابع فقط هر 10 ثانیه به دلیل `delay` فراخوانی می‌شود، به این معنی که متدهای مستقیم فقط هر 10 ثانیه پردازش می‌شوند. برای کارآمدتر کردن این فرآیند، می‌توان تأخیر 10 ثانیه‌ای را به تأخیرهای کوتاه‌تر تقسیم کرد و هر بار `IoTHubDeviceClient_LL_DoWork` را فراخوانی کرد. برای انجام این کار، کد زیر را بالای تابع `loop` اضافه کنید:

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    این کد به‌طور مکرر حلقه می‌زند، `IoTHubDeviceClient_LL_DoWork` را فراخوانی کرده و هر بار 100 میلی‌ثانیه تأخیر می‌اندازد. این کار را به تعداد دفعات لازم برای تأخیر به مدت زمان داده شده در پارامتر `delay_time` انجام می‌دهد. این بدان معناست که دستگاه حداکثر 100 میلی‌ثانیه برای پردازش درخواست‌های متد مستقیم منتظر می‌ماند.

1. در تابع `loop`، فراخوانی به `IoTHubDeviceClient_LL_DoWork` را حذف کرده و فراخوانی `delay(10000)` را با مورد زیر جایگزین کنید تا این تابع جدید فراخوانی شود:

    ```cpp
    work_delay(10000);
    ```

> 💁 می‌توانید این کد را در پوشه [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) پیدا کنید.

😀 برنامه حسگر رطوبت خاک شما به IoT Hub متصل شد!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حیاتی، ترجمه حرفه‌ای انسانی توصیه می‌شود. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.