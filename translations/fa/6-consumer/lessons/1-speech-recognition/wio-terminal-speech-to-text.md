<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-25T22:48:52+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "fa"
}
-->
# تبدیل گفتار به متن - Wio Terminal

در این بخش از درس، شما کدی خواهید نوشت که گفتار ضبط‌شده در فایل صوتی را به متن تبدیل کند، با استفاده از سرویس گفتار.

## ارسال فایل صوتی به سرویس گفتار

فایل صوتی می‌تواند با استفاده از REST API به سرویس گفتار ارسال شود. برای استفاده از سرویس گفتار، ابتدا باید یک توکن دسترسی درخواست کنید و سپس از آن توکن برای دسترسی به REST API استفاده کنید. این توکن‌ها پس از ۱۰ دقیقه منقضی می‌شوند، بنابراین کد شما باید به طور منظم توکن جدید درخواست کند تا همیشه به‌روز باشد.

### وظیفه - دریافت توکن دسترسی

1. پروژه `smart-timer` را باز کنید، اگر هنوز باز نشده است.

1. وابستگی‌های کتابخانه زیر را به فایل `platformio.ini` اضافه کنید تا به WiFi دسترسی داشته باشید و JSON را مدیریت کنید:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. کد زیر را به فایل هدر `config.h` اضافه کنید:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    `<SSID>` و `<PASSWORD>` را با مقادیر مربوط به شبکه WiFi خود جایگزین کنید.

    `<API_KEY>` را با کلید API مربوط به منبع سرویس گفتار خود جایگزین کنید. `<LOCATION>` را با مکانی که هنگام ایجاد منبع سرویس گفتار استفاده کرده‌اید جایگزین کنید.

    `<LANGUAGE>` را با نام محلی زبانی که در آن صحبت خواهید کرد جایگزین کنید، برای مثال `en-GB` برای انگلیسی یا `zn-HK` برای کانتونی. لیست زبان‌های پشتیبانی‌شده و نام‌های محلی آن‌ها را می‌توانید در [مستندات پشتیبانی زبان و صدا در Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) پیدا کنید.

    ثابت `TOKEN_URL` آدرس URL صادرکننده توکن بدون مکان است. این آدرس بعداً با مکان ترکیب می‌شود تا URL کامل به دست آید.

1. درست مانند اتصال به Custom Vision، شما باید از اتصال HTTPS برای اتصال به سرویس صادرکننده توکن استفاده کنید. کد زیر را به انتهای `config.h` اضافه کنید:

    ```cpp
    const char *TOKEN_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQAueRcfuAIek/4tmDg0xQwDANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwNjCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBALVGARl56bx3KBUSGuPc4H5uoNFkFH4e7pvTCxRi4j/+z+Xb\r\n"
        "wjEz+5CipDOqjx9/jWjskL5dk7PaQkzItidsAAnDCW1leZBOIi68Lff1bjTeZgMY\r\n"
        "iwdRd3Y39b/lcGpiuP2d23W95YHkMMT8IlWosYIX0f4kYb62rphyfnAjYb/4Od99\r\n"
        "ThnhlAxGtfvSbXcBVIKCYfZgqRvV+5lReUnd1aNjRYVzPOoifgSx2fRyy1+pO1Uz\r\n"
        "aMMNnIOE71bVYW0A1hr19w7kOb0KkJXoALTDDj1ukUEDqQuBfBxReL5mXiu1O7WG\r\n"
        "0vltg0VZ/SZzctBsdBlx1BkmWYBW261KZgBivrql5ELTKKd8qgtHcLQA5fl6JB0Q\r\n"
        "gs5XDaWehN86Gps5JW8ArjGtjcWAIP+X8CQaWfaCnuRm6Bk/03PQWhgdi84qwA0s\r\n"
        "sRfFJwHUPTNSnE8EiGVk2frt0u8PG1pwSQsFuNJfcYIHEv1vOzP7uEOuDydsmCjh\r\n"
        "lxuoK2n5/2aVR3BMTu+p4+gl8alXoBycyLmj3J/PUgqD8SL5fTCUegGsdia/Sa60\r\n"
        "N2oV7vQ17wjMN+LXa2rjj/b4ZlZgXVojDmAjDwIRdDUujQu0RVsJqFLMzSIHpp2C\r\n"
        "Zp7mIoLrySay2YYBu7SiNwL95X6He2kS8eefBBHjzwW/9FxGqry57i71c2cDAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQU1cFnOsKjnfR3UltZEjgp5lVou6UwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQB2oWc93fB8esci/8esixj++N22meiGDjgF\r\n"
        "+rA2LUK5IOQOgcUSTGKSqF9lYfAxPjrqPjDCUPHCURv+26ad5P/BYtXtbmtxJWu+\r\n"
        "cS5BhMDPPeG3oPZwXRHBJFAkY4O4AF7RIAAUW6EzDflUoDHKv83zOiPfYGcpHc9s\r\n"
        "kxAInCedk7QSgXvMARjjOqdakor21DTmNIUotxo8kHv5hwRlGhBJwps6fEVi1Bt0\r\n"
        "trpM/3wYxlr473WSPUFZPgP1j519kLpWOJ8z09wxay+Br29irPcBYv0GMXlHqThy\r\n"
        "8y4m/HyTQeI2IMvMrQnwqPpY+rLIXyviI2vLoI+4xKE4Rn38ZZ8m\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

    این همان گواهی است که هنگام اتصال به Custom Vision استفاده کردید.

1. یک دستور include برای فایل هدر WiFi و فایل هدر config به بالای فایل `main.cpp` اضافه کنید:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. کدی برای اتصال به WiFi در `main.cpp` بالای تابع `setup` اضافه کنید:

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

1. این تابع را از تابع `setup` پس از برقراری اتصال سریال فراخوانی کنید:

    ```cpp
    connectWiFi();
    ```

1. یک فایل هدر جدید در پوشه `src` با نام `speech_to_text.h` ایجاد کنید. در این فایل هدر، کد زیر را اضافه کنید:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "mic.h"
    
    class SpeechToText
    {
    public:

    private:

    };

    SpeechToText speechToText;
    ```

    این شامل برخی فایل‌های هدر ضروری برای اتصال HTTP، پیکربندی و فایل هدر `mic.h` است و یک کلاس به نام `SpeechToText` تعریف می‌کند، سپس یک نمونه از این کلاس را که بعداً می‌توان استفاده کرد اعلام می‌کند.

1. دو فیلد زیر را به بخش `private` این کلاس اضافه کنید:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` یک WiFi Client است که از HTTPS استفاده می‌کند و برای دریافت توکن دسترسی استفاده خواهد شد. این توکن سپس در `_access_token` ذخیره می‌شود.

1. متد زیر را به بخش `private` اضافه کنید:

    ```cpp
    String getAccessToken()
    {
        char url[128];
        sprintf(url, TOKEN_URL, SPEECH_LOCATION);
    
        HTTPClient httpClient;
        httpClient.begin(_token_client, url);
    
        httpClient.addHeader("Ocp-Apim-Subscription-Key", SPEECH_API_KEY);
        int httpResultCode = httpClient.POST("{}");
    
        if (httpResultCode != 200)
        {
            Serial.println("Error getting access token, trying again...");
            delay(10000);
            return getAccessToken();
        }
    
        Serial.println("Got access token.");
        String result = httpClient.getString();
    
        httpClient.end();
    
        return result;
    }
    ```

    این کد URL مربوط به API صادرکننده توکن را با استفاده از مکان منبع گفتار ایجاد می‌کند. سپس یک `HTTPClient` برای انجام درخواست وب ایجاد می‌کند و آن را برای استفاده از WiFi Client پیکربندی‌شده با گواهی نقاط پایانی توکن تنظیم می‌کند. کلید API به عنوان یک هدر برای درخواست تنظیم می‌شود. سپس یک درخواست POST برای دریافت گواهی انجام می‌دهد و در صورت دریافت خطا دوباره تلاش می‌کند. در نهایت توکن دسترسی بازگردانده می‌شود.

1. به بخش `public` یک متد برای دریافت توکن دسترسی اضافه کنید. این متد در درس‌های بعدی برای تبدیل متن به گفتار مورد نیاز خواهد بود.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. به بخش `public` یک متد `init` اضافه کنید که کلاینت توکن را تنظیم می‌کند:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    این گواهی را روی WiFi Client تنظیم می‌کند و سپس توکن دسترسی را دریافت می‌کند.

1. این فایل هدر جدید را به دستورات include در `main.cpp` اضافه کنید:

    ```cpp
    #include "speech_to_text.h"
    ```

1. کلاس `SpeechToText` را در انتهای تابع `setup` مقداردهی اولیه کنید، پس از فراخوانی `mic.init` اما قبل از اینکه `Ready` در مانیتور سریال نوشته شود:

    ```cpp
    speechToText.init();
    ```

### وظیفه - خواندن فایل صوتی از حافظه فلش

1. در بخش قبلی این درس، فایل صوتی در حافظه فلش ضبط شد. این فایل صوتی باید به REST API سرویس گفتار ارسال شود، بنابراین باید از حافظه فلش خوانده شود. نمی‌توان آن را به یک بافر در حافظه بارگذاری کرد زیرا بسیار بزرگ خواهد بود. کلاس `HTTPClient` که درخواست‌های REST را انجام می‌دهد می‌تواند داده‌ها را با استفاده از یک Arduino Stream ارسال کند - کلاسی که می‌تواند داده‌ها را در قطعات کوچک بارگذاری کند و هر قطعه را به صورت جداگانه به عنوان بخشی از درخواست ارسال کند. هر بار که `read` را روی یک استریم فراخوانی می‌کنید، بلوک بعدی داده‌ها را بازمی‌گرداند. یک Arduino Stream می‌تواند ایجاد شود که بتواند از حافظه فلش بخواند. یک فایل جدید به نام `flash_stream.h` در پوشه `src` ایجاد کنید و کد زیر را به آن اضافه کنید:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <HTTPClient.h>
    #include <sfud.h>

    #include "config.h"
    
    class FlashStream : public Stream
    {
    public:
        virtual size_t write(uint8_t val)
        {    
        }
    
        virtual int available()
        {
        }
    
        virtual int read()
        {
        }
    
        virtual int peek()
        {
        }
    private:
    
    };
    ```

    این کلاس `FlashStream` را اعلام می‌کند که از کلاس `Stream` Arduino مشتق شده است. این یک کلاس انتزاعی است - کلاس‌های مشتق‌شده باید چند متد را قبل از اینکه کلاس قابل مقداردهی اولیه باشد پیاده‌سازی کنند، و این متدها در این کلاس تعریف شده‌اند.

    ✅ اطلاعات بیشتر درباره Arduino Streams را در [مستندات Arduino Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/) بخوانید.

1. فیلدهای زیر را به بخش `private` اضافه کنید:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    این یک بافر موقت برای ذخیره داده‌های خوانده‌شده از حافظه فلش تعریف می‌کند، همراه با فیلدهایی برای ذخیره موقعیت فعلی هنگام خواندن از بافر، آدرس فعلی برای خواندن از حافظه فلش، و دستگاه حافظه فلش.

1. متد زیر را به بخش `private` اضافه کنید:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    این کد از حافظه فلش در آدرس فعلی می‌خواند و داده‌ها را در یک بافر ذخیره می‌کند. سپس آدرس را افزایش می‌دهد، بنابراین فراخوانی بعدی بلوک بعدی حافظه را می‌خواند. اندازه بافر بر اساس بزرگ‌ترین قطعه‌ای که `HTTPClient` در یک زمان به REST API ارسال خواهد کرد تنظیم شده است.

    > 💁 پاک کردن حافظه فلش باید با اندازه دانه انجام شود، اما خواندن نیازی به این کار ندارد.

1. یک سازنده به بخش `public` این کلاس اضافه کنید:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    این سازنده تمام فیلدها را برای شروع خواندن از ابتدای بلوک حافظه فلش تنظیم می‌کند و اولین قطعه داده‌ها را در بافر بارگذاری می‌کند.

1. متد `write` را پیاده‌سازی کنید. این استریم فقط داده‌ها را می‌خواند، بنابراین این متد می‌تواند هیچ کاری انجام ندهد و مقدار ۰ را بازگرداند:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. متد `peek` را پیاده‌سازی کنید. این داده‌ها را در موقعیت فعلی بدون حرکت دادن استریم بازمی‌گرداند. فراخوانی چندباره `peek` همیشه همان داده‌ها را بازمی‌گرداند تا زمانی که داده‌ای از استریم خوانده نشود.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. تابع `available` را پیاده‌سازی کنید. این تعداد بایت‌هایی که می‌توان از استریم خواند را بازمی‌گرداند، یا -1 اگر استریم کامل شده باشد. برای این کلاس، حداکثر مقدار موجود هرگز بیشتر از اندازه قطعه HTTPClient نخواهد بود. وقتی این استریم در HTTPClient استفاده می‌شود، تابع `available` را فراخوانی می‌کند تا ببیند چه مقدار داده موجود است، سپس همان مقدار داده را برای ارسال به REST API درخواست می‌کند. نمی‌خواهیم هر قطعه بیشتر از اندازه قطعه HTTPClient باشد، بنابراین اگر بیشتر از آن موجود باشد، اندازه قطعه بازگردانده می‌شود. اگر کمتر باشد، مقدار موجود بازگردانده می‌شود. وقتی تمام داده‌ها استریم شدند، مقدار -1 بازگردانده می‌شود.

    ```cpp
    virtual int available()
    {
        int remaining = BUFFER_SIZE - ((_flash_address - HTTP_TCP_BUFFER_SIZE) + _pos);
        int bytes_available = min(HTTP_TCP_BUFFER_SIZE, remaining);

        if (bytes_available == 0)
        {
            bytes_available = -1;
        }

        return bytes_available;
    }
    ```

1. متد `read` را پیاده‌سازی کنید تا بایت بعدی از بافر بازگردانده شود و موقعیت افزایش یابد. اگر موقعیت از اندازه بافر فراتر رود، بافر با بلوک بعدی از حافظه فلش پر می‌شود و موقعیت بازنشانی می‌شود.

    ```cpp
    virtual int read()
    {
        int retVal = _buffer[_pos++];

        if (_pos == HTTP_TCP_BUFFER_SIZE)
        {
            populateBuffer();
        }

        return retVal;
    }
    ```

1. در فایل هدر `speech_to_text.h` یک دستور include برای این فایل هدر جدید اضافه کنید:

    ```cpp
    #include "flash_stream.h"
    ```

### وظیفه - تبدیل گفتار به متن

1. گفتار می‌تواند با ارسال فایل صوتی به سرویس گفتار از طریق REST API به متن تبدیل شود. این REST API گواهی متفاوتی نسبت به صادرکننده توکن دارد، بنابراین کد زیر را به فایل هدر `config.h` اضافه کنید تا این گواهی تعریف شود:

    ```cpp
    const char *SPEECH_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQCq+mxcpjxFFB6jvh98dTFzANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwMTCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBAMedcDrkXufP7pxVm1FHLDNA9IjwHaMoaY8arqqZ4Gff4xyr\r\n"
        "RygnavXL7g12MPAx8Q6Dd9hfBzrfWxkF0Br2wIvlvkzW01naNVSkHp+OS3hL3W6n\r\n"
        "l/jYvZnVeJXjtsKYcXIf/6WtspcF5awlQ9LZJcjwaH7KoZuK+THpXCMtzD8XNVdm\r\n"
        "GW/JI0C/7U/E7evXn9XDio8SYkGSM63aLO5BtLCv092+1d4GGBSQYolRq+7Pd1kR\r\n"
        "EkWBPm0ywZ2Vb8GIS5DLrjelEkBnKCyy3B0yQud9dpVsiUeE7F5sY8Me96WVxQcb\r\n"
        "OyYdEY/j/9UpDlOG+vA+YgOvBhkKEjiqygVpP8EZoMMijephzg43b5Qi9r5UrvYo\r\n"
        "o19oR/8pf4HJNDPF0/FJwFVMW8PmCBLGstin3NE1+NeWTkGt0TzpHjgKyfaDP2tO\r\n"
        "4bCk1G7pP2kDFT7SYfc8xbgCkFQ2UCEXsaH/f5YmpLn4YPiNFCeeIida7xnfTvc4\r\n"
        "7IxyVccHHq1FzGygOqemrxEETKh8hvDR6eBdrBwmCHVgZrnAqnn93JtGyPLi6+cj\r\n"
        "WGVGtMZHwzVvX1HvSFG771sskcEjJxiQNQDQRWHEh3NxvNb7kFlAXnVdRkkvhjpR\r\n"
        "GchFhTAzqmwltdWhWDEyCMKC2x/mSZvZtlZGY+g37Y72qHzidwtyW7rBetZJAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQUDyBd16FXlduSzyvQx8J3BM5ygHYwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQAlFvNh7QgXVLAZSsNR2XRmIn9iS8OHFCBA\r\n"
        "WxKJoi8YYQafpMTkMqeuzoL3HWb1pYEipsDkhiMnrpfeYZEA7Lz7yqEEtfgHcEBs\r\n"
        "K9KcStQGGZRfmWU07hPXHnFz+5gTXqzCE2PBMlRgVUYJiA25mJPXfB00gDvGhtYa\r\n"
        "+mENwM9Bq1B9YYLyLjRtUz8cyGsdyTIG/bBM/Q9jcV8JGqMU/UjAdh1pFyTnnHEl\r\n"
        "Y59Npi7F87ZqYYJEHJM2LGD+le8VsHjgeWX2CJQko7klXvcizuZvUEDTjHaQcs2J\r\n"
        "+kPgfyMIOY1DMJ21NxOJ2xPRC/wAh/hzSBRVtoAnyuxtkZ4VjIOh\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. یک ثابت برای URL گفتار بدون مکان به این فایل اضافه کنید. این URL بعداً با مکان و زبان ترکیب خواهد شد تا URL کامل به دست آید.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. در فایل هدر `speech_to_text.h`، در بخش `private` کلاس `SpeechToText`، یک فیلد برای WiFi Client با استفاده از گواهی گفتار تعریف کنید:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. در متد `init` گواهی را روی این WiFi Client تنظیم کنید:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. کد زیر را به بخش `public` کلاس `SpeechToText` اضافه کنید تا یک متد برای تبدیل گفتار به متن تعریف شود:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. کد زیر را به این متد اضافه کنید تا یک HTTPClient با استفاده از WiFi Client پیکربندی‌شده با گواهی گفتار ایجاد شود و از URL گفتار تنظیم‌شده با مکان و زبان استفاده کند:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. برخی هدرها باید روی اتصال تنظیم شوند:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    این هدرها برای احراز هویت با استفاده از توکن دسترسی، فرمت فایل صوتی با استفاده از نرخ نمونه‌برداری، و تنظیم اینکه کلاینت انتظار دارد نتیجه به صورت JSON باشد تنظیم می‌شوند.

1. پس از این، کد زیر را برای انجام درخواست REST API اضافه کنید:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    این یک `FlashStream` ایجاد می‌کند و از آن برای ارسال داده‌ها به REST API استفاده می‌کند.

1. کد زیر را به این متد اضافه کنید:

    ```cpp
    String text = "";

    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        text = obj["DisplayText"].as<String>();
    }
    else if (httpResponseCode == 401)
    {
        Serial.println("Access token expired, trying again with a new token");
        _access_token = getAccessToken();
        return convertSpeechToText();
    }
    else
    {
        Serial.print("Failed to convert text to speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    این کد کد پاسخ را بررسی می‌کند.

    اگر کد 200 باشد، که کد موفقیت است، نتیجه دریافت می‌شود، از JSON رمزگشایی می‌شود، و ویژگی `DisplayText` در متغیر `text` تنظیم می‌شود. این ویژگی متن گفتار به صورت متن بازگردانده می‌شود.

    اگر کد پاسخ 401 باشد، توکن دسترسی منقضی شده است (این توکن‌ها فقط ۱۰ دقیقه اعتبار دارند). یک توکن دسترسی جدید درخواست می‌شود و درخواست دوباره انجام می‌شود.

    در غیر این صورت، یک خطا به مانیتور سریال ارسال می‌شود و `text` خالی باقی می‌ماند.

1. کد زیر را به انتهای این متد اضافه کنید تا HTTPClient بسته شود و متن بازگردانده شود:

    ```cpp
    httpClient.end();

    return text;
    ```

1. در `main.cpp` این متد جدید `convertSpeechToText` را در تابع `processAudio` فراخوانی کنید، سپس گفتار را در مانیتور سریال ثبت کنید:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. این کد را بسازید، آن را به Wio Terminal خود آپلود کنید و از طریق مانیتور سریال آن را آزمایش کنید. هنگامی که `Ready` را در مانیتور سریال مشاهده کردید، دکمه C (دکمه سمت چپ، نزدیک به کلید پاور) را فشار دهید و صحبت کنید. ۴ ثانیه فایل صوتی ضبط می‌شود و سپس به متن تبدیل می‌شود.

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
    ```

> 💁 می‌توانید این کد را در پوشه [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) پیدا کنید.

😀 برنامه تبدیل گفتار به متن شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه حرفه‌ای انسانی استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.