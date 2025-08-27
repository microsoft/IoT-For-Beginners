<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T00:28:19+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "ur"
}
-->
# تقریر کو متن میں تبدیل کرنا - Wio Terminal

اس سبق کے اس حصے میں، آپ کوڈ لکھیں گے تاکہ کیپچر کیے گئے آڈیو میں تقریر کو متن میں تبدیل کیا جا سکے، اس کے لیے اسپیکنگ سروس کا استعمال کیا جائے گا۔

## آڈیو کو اسپیکنگ سروس پر بھیجیں

آڈیو کو اسپیکنگ سروس پر REST API کے ذریعے بھیجا جا سکتا ہے۔ اسپیکنگ سروس استعمال کرنے کے لیے، پہلے آپ کو ایک ایکسیس ٹوکن کی درخواست کرنی ہوگی، پھر اس ٹوکن کو REST API تک رسائی کے لیے استعمال کریں۔ یہ ایکسیس ٹوکن 10 منٹ کے بعد ختم ہو جاتے ہیں، اس لیے آپ کے کوڈ کو باقاعدگی سے ان کی درخواست کرنی چاہیے تاکہ یہ ہمیشہ اپ ٹو ڈیٹ رہیں۔

### کام - ایکسیس ٹوکن حاصل کریں

1. `smart-timer` پروجیکٹ کھولیں اگر یہ پہلے سے کھلا نہیں ہے۔

1. `platformio.ini` فائل میں درج ذیل لائبریری ڈیپینڈنسیز شامل کریں تاکہ WiFi تک رسائی حاصل کی جا سکے اور JSON کو ہینڈل کیا جا سکے:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. `config.h` ہیڈر فائل میں درج ذیل کوڈ شامل کریں:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    `<SSID>` اور `<PASSWORD>` کو اپنے WiFi کے متعلقہ ویلیوز سے تبدیل کریں۔

    `<API_KEY>` کو اپنی اسپیکنگ سروس ریسورس کے API کلید سے تبدیل کریں۔ `<LOCATION>` کو اس مقام سے تبدیل کریں جو آپ نے اسپیکنگ سروس ریسورس بناتے وقت استعمال کیا تھا۔

    `<LANGUAGE>` کو اس زبان کے لوکیل نام سے تبدیل کریں جس میں آپ بات کریں گے، مثلاً `en-GB` انگریزی کے لیے، یا `zn-HK` کینٹونیز کے لیے۔ آپ مائیکروسافٹ ڈاکس پر [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) میں سپورٹ شدہ زبانوں اور ان کے لوکیل ناموں کی فہرست دیکھ سکتے ہیں۔

    `TOKEN_URL` کانسٹنٹ ٹوکن جاری کرنے والے کا URL ہے بغیر مقام کے۔ یہ بعد میں مقام کے ساتھ ملایا جائے گا تاکہ مکمل URL حاصل کیا جا سکے۔

1. بالکل اسی طرح جیسے Custom Vision سے جڑنے کے لیے HTTPS کنکشن استعمال کیا گیا تھا، آپ کو ٹوکن جاری کرنے والی سروس سے جڑنے کے لیے HTTPS کنکشن استعمال کرنا ہوگا۔ `config.h` کے آخر میں درج ذیل کوڈ شامل کریں:

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

    یہ وہی سرٹیفکیٹ ہے جو آپ نے Custom Vision سے جڑنے کے وقت استعمال کیا تھا۔

1. `main.cpp` فائل کے شروع میں WiFi ہیڈر فائل اور config ہیڈر فائل کے لیے انکلوڈ شامل کریں:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. `main.cpp` میں `setup` فنکشن کے اوپر WiFi سے جڑنے کے لیے کوڈ شامل کریں:

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

1. اس فنکشن کو `setup` فنکشن میں سیریل کنکشن قائم ہونے کے بعد کال کریں:

    ```cpp
    connectWiFi();
    ```

1. `src` فولڈر میں ایک نئی ہیڈر فائل بنائیں جس کا نام `speech_to_text.h` ہو۔ اس ہیڈر فائل میں درج ذیل کوڈ شامل کریں:

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

    یہ HTTP کنکشن، کنفیگریشن، اور `mic.h` ہیڈر فائل کے لیے ضروری ہیڈر فائلز شامل کرتا ہے، اور `SpeechToText` نامی ایک کلاس کو ڈیفائن کرتا ہے، پھر اس کلاس کی ایک انسٹینس کو ڈکلیئر کرتا ہے جو بعد میں استعمال کی جا سکتی ہے۔

1. اس کلاس کے `private` سیکشن میں درج ذیل 2 فیلڈز شامل کریں:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` ایک WiFi کلائنٹ ہے جو HTTPS استعمال کرتا ہے اور ایکسیس ٹوکن حاصل کرنے کے لیے استعمال ہوگا۔ یہ ٹوکن پھر `_access_token` میں محفوظ کیا جائے گا۔

1. `private` سیکشن میں درج ذیل میتھڈ شامل کریں:

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

    یہ کوڈ اسپیکنگ ریسورس کے مقام کا استعمال کرتے ہوئے ٹوکن جاری کرنے والے API کے لیے URL بناتا ہے۔ پھر ایک `HTTPClient` بناتا ہے تاکہ ویب درخواست کی جا سکے، اور اسے ٹوکن اینڈ پوائنٹس سرٹیفکیٹ کے ساتھ کنفیگر کردہ WiFi کلائنٹ کے ساتھ سیٹ کرتا ہے۔ یہ API کلید کو کال کے لیے ہیڈر کے طور پر سیٹ کرتا ہے۔ پھر یہ سرٹیفکیٹ حاصل کرنے کے لیے POST درخواست کرتا ہے، اور اگر کوئی ایرر آتا ہے تو دوبارہ کوشش کرتا ہے۔ آخر میں ایکسیس ٹوکن واپس کیا جاتا ہے۔

1. `public` سیکشن میں ایک میتھڈ شامل کریں تاکہ ایکسیس ٹوکن حاصل کیا جا سکے۔ یہ بعد کے اسباق میں متن کو تقریر میں تبدیل کرنے کے لیے ضروری ہوگا۔

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. `public` سیکشن میں ایک `init` میتھڈ شامل کریں جو ٹوکن کلائنٹ کو سیٹ اپ کرے:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    یہ WiFi کلائنٹ پر سرٹیفکیٹ سیٹ کرتا ہے، پھر ایکسیس ٹوکن حاصل کرتا ہے۔

1. `main.cpp` میں اس نئی ہیڈر فائل کو انکلوڈ ڈائریکٹیوز میں شامل کریں:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `setup` فنکشن کے آخر میں `SpeechToText` کلاس کو انیشیالائز کریں، `mic.init` کال کے بعد لیکن `Ready` کو سیریل مانیٹر پر لکھنے سے پہلے:

    ```cpp
    speechToText.init();
    ```

### کام - فلیش میموری سے آڈیو پڑھیں

1. سبق کے ایک پہلے حصے میں، آڈیو کو فلیش میموری میں ریکارڈ کیا گیا تھا۔ اس آڈیو کو اسپیکنگ سروس REST API پر بھیجنے کی ضرورت ہوگی، اس لیے اسے فلیش میموری سے پڑھنے کی ضرورت ہے۔ اسے ان میموری بفر میں لوڈ نہیں کیا جا سکتا کیونکہ یہ بہت بڑا ہوگا۔ `HTTPClient` کلاس جو REST کالز کرتی ہے، Arduino Stream کا استعمال کرتے ہوئے ڈیٹا کو اسٹریم کر سکتی ہے - ایک کلاس جو ڈیٹا کو چھوٹے حصوں میں لوڈ کر سکتی ہے، اور ایک وقت میں ایک حصہ بھیج سکتی ہے۔ ہر بار جب آپ `read` کو اسٹریم پر کال کرتے ہیں تو یہ اگلا ڈیٹا بلاک واپس کرتا ہے۔ ایک Arduino اسٹریم بنایا جا سکتا ہے جو فلیش میموری سے پڑھ سکتا ہے۔ `src` فولڈر میں ایک نئی فائل بنائیں جس کا نام `flash_stream.h` ہو، اور اس میں درج ذیل کوڈ شامل کریں:

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

    یہ `FlashStream` کلاس کو ڈکلیئر کرتا ہے، جو Arduino `Stream` کلاس سے ماخوذ ہے۔ یہ ایک ایبسٹریکٹ کلاس ہے - ماخوذ کلاسز کو چند میتھڈز کو امپلیمنٹ کرنا ہوتا ہے اس سے پہلے کہ کلاس کو انسٹینشیٹ کیا جا سکے، اور یہ میتھڈز اس کلاس میں ڈیفائن کیے گئے ہیں۔

    ✅ Arduino Streams کے بارے میں مزید پڑھیں [Arduino Stream documentation](https://www.arduino.cc/reference/en/language/functions/communication/stream/) میں۔

1. `private` سیکشن میں درج ذیل فیلڈز شامل کریں:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    یہ ایک عارضی بفر ڈیفائن کرتا ہے تاکہ فلیش میموری سے پڑھے گئے ڈیٹا کو اسٹور کیا جا سکے، ساتھ ہی موجودہ پوزیشن کو اسٹور کرنے کے لیے فیلڈز، فلیش میموری سے پڑھنے کے لیے موجودہ ایڈریس، اور فلیش میموری ڈیوائس۔

1. `private` سیکشن میں درج ذیل میتھڈ شامل کریں:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    یہ کوڈ موجودہ ایڈریس پر فلیش میموری سے پڑھتا ہے اور ڈیٹا کو بفر میں اسٹور کرتا ہے۔ پھر ایڈریس کو انکریمنٹ کرتا ہے، تاکہ اگلی کال میموری کے اگلے بلاک کو پڑھے۔ بفر کا سائز REST API پر ایک وقت میں بھیجے جانے والے سب سے بڑے بلاک کے مطابق ہے۔

    > 💁 فلیش میموری کو مٹانا گرین سائز کے ساتھ کرنا ہوتا ہے، لیکن پڑھنا اس طرح نہیں ہوتا۔

1. اس کلاس کے `public` سیکشن میں ایک کنسٹرکٹر شامل کریں:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    یہ کنسٹرکٹر تمام فیلڈز کو سیٹ کرتا ہے تاکہ فلیش میموری بلاک کے آغاز سے پڑھنا شروع کیا جا سکے، اور پہلے ڈیٹا بلاک کو بفر میں لوڈ کرتا ہے۔

1. `write` میتھڈ کو امپلیمنٹ کریں۔ یہ اسٹریم صرف ڈیٹا پڑھے گا، اس لیے یہ کچھ نہیں کرے گا اور 0 واپس کرے گا:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. `peek` میتھڈ کو امپلیمنٹ کریں۔ یہ موجودہ پوزیشن پر ڈیٹا واپس کرتا ہے بغیر اسٹریم کو آگے بڑھائے۔ `peek` کو متعدد بار کال کرنے سے ہمیشہ وہی ڈیٹا واپس آئے گا جب تک کہ اسٹریم سے کوئی ڈیٹا نہ پڑھا جائے۔

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. `available` فنکشن کو امپلیمنٹ کریں۔ یہ بتاتا ہے کہ اسٹریم سے کتنے بائٹس پڑھے جا سکتے ہیں، یا -1 اگر اسٹریم مکمل ہو گیا ہو۔ اس کلاس کے لیے، زیادہ سے زیادہ دستیاب HTTPClient کے بلاک سائز سے زیادہ نہیں ہوگا۔ جب یہ اسٹریم HTTP کلائنٹ میں استعمال ہوتا ہے تو یہ فنکشن دیکھتا ہے کہ کتنا ڈیٹا دستیاب ہے، پھر REST API پر بھیجنے کے لیے اتنا ڈیٹا مانگتا ہے۔ ہم نہیں چاہتے کہ ہر بلاک HTTP کلائنٹ کے بلاک سائز سے زیادہ ہو، اس لیے اگر زیادہ دستیاب ہو تو بلاک سائز واپس کیا جاتا ہے۔ اگر کم ہو، تو جو دستیاب ہے وہ واپس کیا جاتا ہے۔ ایک بار جب تمام ڈیٹا اسٹریم ہو جائے، -1 واپس کیا جاتا ہے۔

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

1. `read` میتھڈ کو امپلیمنٹ کریں تاکہ بفر سے اگلا بائٹ واپس کرے، پوزیشن کو انکریمنٹ کرتے ہوئے۔ اگر پوزیشن بفر کے سائز سے تجاوز کر جائے، تو یہ بفر کو فلیش میموری سے اگلے بلاک کے ساتھ پاپولیٹ کرتا ہے اور پوزیشن کو ری سیٹ کرتا ہے۔

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

1. `speech_to_text.h` ہیڈر فائل میں اس نئی ہیڈر فائل کے لیے انکلوڈ ڈائریکٹیو شامل کریں:

    ```cpp
    #include "flash_stream.h"
    ```

### کام - تقریر کو متن میں تبدیل کریں

1. تقریر کو متن میں تبدیل کرنے کے لیے آڈیو کو REST API کے ذریعے اسپیکنگ سروس پر بھیجا جا سکتا ہے۔ اس REST API کا سرٹیفکیٹ ٹوکن جاری کرنے والے سے مختلف ہے، اس لیے `config.h` ہیڈر فائل میں درج ذیل کوڈ شامل کریں تاکہ اس سرٹیفکیٹ کو ڈیفائن کیا جا سکے:

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

1. اس فائل میں اسپیکنگ URL کے لیے ایک کانسٹنٹ شامل کریں بغیر مقام کے۔ یہ بعد میں مقام اور زبان کے ساتھ ملایا جائے گا تاکہ مکمل URL حاصل کیا جا سکے۔

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. `speech_to_text.h` ہیڈر فائل میں، `SpeechToText` کلاس کے `private` سیکشن میں، اسپیکنگ سرٹیفکیٹ کے ساتھ کنفیگر کردہ WiFi کلائنٹ کے لیے ایک فیلڈ ڈیفائن کریں:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. `init` میتھڈ میں، اس WiFi کلائنٹ پر سرٹیفکیٹ سیٹ کریں:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. `SpeechToText` کلاس کے `public` سیکشن میں تقریر کو متن میں تبدیل کرنے کے لیے ایک میتھڈ ڈیفائن کریں:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. اس میتھڈ میں درج ذیل کوڈ شامل کریں تاکہ اسپیکنگ سرٹیفکیٹ کے ساتھ کنفیگر کردہ WiFi کلائنٹ کا استعمال کرتے ہوئے ایک HTTP کلائنٹ بنایا جا سکے، اور اسپیکنگ URL کو مقام اور زبان کے ساتھ سیٹ کیا جا سکے:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. کنکشن پر کچھ ہیڈرز سیٹ کرنے کی ضرورت ہے:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    یہ ایکسیس ٹوکن کے ذریعے آتھورائزیشن، سیمپل ریٹ کے ذریعے آڈیو فارمیٹ، اور JSON کے طور پر نتیجہ کی توقع سیٹ کرتا ہے۔

1. اس کے بعد، REST API کال کرنے کے لیے درج ذیل کوڈ شامل کریں:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    یہ ایک `FlashStream` بناتا ہے اور اسے REST API پر ڈیٹا اسٹریم کرنے کے لیے استعمال کرتا ہے۔

1. اس کے نیچے درج ذیل کوڈ شامل کریں:

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

    یہ کوڈ ریسپانس کوڈ چیک کرتا ہے۔

    اگر یہ 200 ہے، جو کامیابی کا کوڈ ہے، تو نتیجہ حاصل کیا جاتا ہے، JSON سے ڈیکوڈ کیا جاتا ہے، اور `DisplayText` پراپرٹی کو `text` ویریبل میں سیٹ کیا جاتا ہے۔ یہ وہ پراپرٹی ہے جس میں تقریر کا متن ورژن واپس کیا جاتا ہے۔

    اگر ریسپانس کوڈ 401 ہے، تو ایکسیس ٹوکن ختم ہو چکا ہے (یہ ٹوکن صرف 10 منٹ تک رہتے ہیں)۔ ایک نیا ایکسیس ٹوکن طلب کیا جاتا ہے، اور کال دوبارہ کی جاتی ہے۔

    ورنہ، ایک ایرر سیریل مانیٹر پر بھیجا جاتا ہے، اور `text` خالی چھوڑ دیا جاتا ہے۔

1. اس میتھڈ کے آخر میں درج ذیل کوڈ شامل کریں تاکہ HTTP کلائنٹ کو بند کیا جا سکے اور متن واپس کیا جا سکے:

    ```cpp
    httpClient.end();

    return text;
    ```

1. `main.cpp` میں اس نئے `convertSpeechToText` میتھڈ کو `processAudio` فنکشن میں کال کریں، پھر تقریر کو سیریل مانیٹر پر لاگ کریں:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. اس کوڈ کو بلڈ کریں، اسے اپنے Wio Terminal پر اپلوڈ کریں اور سیریل مانیٹر کے ذریعے اسے ٹیسٹ کریں۔ جب آپ سیریل مانیٹر میں `Ready` دیکھیں، تو C بٹن دبائیں (جو بائیں جانب ہے، پاور سوئچ کے قریب)، اور بولیں۔ 4 سیکنڈ کا آڈیو کیپچر کیا جائے گا، پھر اسے متن میں تبدیل کیا جائے گا۔

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

> 💁 آپ اس کوڈ کو [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا تقریر کو متن میں تبدیل کرنے کا پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔