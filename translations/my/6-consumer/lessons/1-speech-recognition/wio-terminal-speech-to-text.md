<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-28T16:34:51+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "my"
}
-->
# အသံမှ စာသား - Wio Terminal

ဒီသင်ခန်းစာရဲ့ အပိုင်းမှာ သင်ရဲ့ ကုဒ်ကို အသံဝန်ဆောင်မှုကို အသုံးပြုပြီး ဖမ်းယူထားသော အသံကို စာသားအဖြစ် ပြောင်းလဲရေးလုပ်ဆောင်ပါမည်။

## အသံကို အသံဝန်ဆောင်မှုဆီသို့ ပို့ပါ

အသံကို REST API ကို အသုံးပြု၍ အသံဝန်ဆောင်မှုဆီသို့ ပို့နိုင်ပါသည်။ အသံဝန်ဆောင်မှုကို အသုံးပြုရန်အတွက် အရင်ဆုံး သင်သည် access token တစ်ခုကို တောင်းဆိုရမည်၊ ထို့နောက် အဆိုပါ token ကို REST API ကို အသုံးပြုရန် အသုံးပြုပါ။ ဒီ access tokens များသည် 10 မိနစ်အတွင်း သက်တမ်းကုန်သွားမည်ဖြစ်သောကြောင့် သင်၏ ကုဒ်သည် အမြဲတမ်း update ဖြစ်နေစေရန် အကြိမ်ကြိမ်တောင်းဆိုရမည်။

### လုပ်ဆောင်ရန် - access token ရယူပါ

1. `smart-timer` project ကို ဖွင့်ပါ၊ project ဖွင့်ထားမရှိလျှင် ဖွင့်ပါ။

1. WiFi ကို access ပြုလုပ်ရန်နှင့် JSON ကို ကိုင်တွယ်ရန် `platformio.ini` ဖိုင်တွင် အောက်ပါ library dependencies များကို ထည့်ပါ။

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. `config.h` header ဖိုင်တွင် အောက်ပါကုဒ်ကို ထည့်ပါ။

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    `<SSID>` နှင့် `<PASSWORD>` ကို သင့် WiFi အတွက် သက်ဆိုင်ရာတန်ဖိုးများဖြင့် အစားထိုးပါ။

    `<API_KEY>` ကို သင့်အသံဝန်ဆောင်မှု resource အတွက် API key ဖြင့် အစားထိုးပါ။ `<LOCATION>` ကို သင့်အသံဝန်ဆောင်မှု resource ကို ဖန်တီးခဲ့သောနေရာဖြင့် အစားထိုးပါ။

    `<LANGUAGE>` ကို သင်ပြောမည့်ဘာသာစကားအတွက် locale name ဖြင့် အစားထိုးပါ၊ ဥပမာ `en-GB` သည် အင်္ဂလိပ်ဘာသာစကား၊ `zn-HK` သည် Cantonese ဖြစ်သည်။ Microsoft docs တွင် [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) တွင် အထောက်အပံ့ပေးသော ဘာသာစကားများနှင့် locale names များကို ရှာဖွေကြည့်နိုင်ပါသည်။

    `TOKEN_URL` constant သည် location မပါသော token issuer URL ဖြစ်သည်။ အပြည့်အစုံ URL ကို later တွင် location နှင့် ပေါင်းစပ်မည်ဖြစ်သည်။

1. Custom Vision ကို ချိတ်ဆက်သည့်အတိုင်း HTTPS connection ကို အသုံးပြု၍ token issuing service ကို ချိတ်ဆက်ရန်လိုအပ်ပါသည်။ `config.h` အဆုံးတွင် အောက်ပါကုဒ်ကို ထည့်ပါ။

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

    ဒီက certificate သည် Custom Vision ကို ချိတ်ဆက်သည့်အခါ အသုံးပြုခဲ့သော certificate တူတူပင်ဖြစ်သည်။

1. WiFi header ဖိုင်နှင့် config header ဖိုင်ကို `main.cpp` ဖိုင်၏ အပေါ်ပိုင်းတွင် include လုပ်ပါ။

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. WiFi ကို ချိတ်ဆက်ရန် ကုဒ်ကို `main.cpp` တွင် `setup` function အထက်တွင် ထည့်ပါ။

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

1. serial connection တည်ဆောက်ပြီးနောက် `setup` function မှာ ဒီ function ကို ခေါ်ပါ။

    ```cpp
    connectWiFi();
    ```

1. `src` folder တွင် `speech_to_text.h` ဟုခေါ်သော header ဖိုင်အသစ်တစ်ခု ဖန်တီးပါ။ ဒီ header ဖိုင်တွင် အောက်ပါကုဒ်ကို ထည့်ပါ။

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

    ဒီမှာ HTTP connection, configuration နှင့် `mic.h` header ဖိုင်များအတွက် လိုအပ်သော header ဖိုင်များကို include လုပ်ပြီး `SpeechToText` ဟုခေါ်သော class ကို သတ်မှတ်ထားပြီး နောက်ပိုင်းတွင် အသုံးပြုနိုင်သော class instance ကို ကြေညာထားသည်။

1. ဒီ class ရဲ့ `private` section တွင် အောက်ပါ 2 fields ကို ထည့်ပါ။

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` သည် HTTPS ကို အသုံးပြုသော WiFi Client ဖြစ်ပြီး access token ကို ရယူရန် အသုံးပြုမည်။ ဒီ token ကို `_access_token` တွင် သိမ်းဆည်းမည်။

1. `private` section တွင် အောက်ပါ method ကို ထည့်ပါ။

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

    ဒီကုဒ်သည် အသံ resource ရဲ့ location ကို အသုံးပြု၍ token issuer API အတွက် URL ကို တည်ဆောက်သည်။ ထို့နောက် web request ကို ပြုလုပ်ရန် `HTTPClient` တစ်ခုကို ဖန်တီးပြီး WiFi client ကို token endpoints certificate ဖြင့် configure လုပ်ထားသည်။ API key ကို call အတွက် header အဖြစ် သတ်မှတ်ထားသည်။ POST request ကို ပြုလုပ်ပြီး certificate ကို ရယူသည်၊ error ရရှိပါက retry လုပ်သည်။ access token ကို နောက်ဆုံး return ပြုလုပ်သည်။

1. `public` section တွင် access token ရယူရန် method တစ်ခုကို ထည့်ပါ။ ဒီ method ကို later lessons တွင် text ကို အသံအဖြစ် ပြောင်းရန် လိုအပ်မည်။

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. `public` section တွင် token client ကို setup လုပ်သည့် `init` method ကို ထည့်ပါ။

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    ဒီ method သည် WiFi client တွင် certificate ကို သတ်မှတ်ပြီး access token ကို ရယူသည်။

1. `main.cpp` တွင် ဒီ header ဖိုင်အသစ်ကို include directives တွင် ထည့်ပါ။

    ```cpp
    #include "speech_to_text.h"
    ```

1. `setup` function ရဲ့ အဆုံးတွင် `SpeechToText` class ကို initialize လုပ်ပါ၊ `mic.init` call အပြီး serial monitor တွင် `Ready` ရေးသားမည့်အချိန်မတိုင်မီ။

    ```cpp
    speechToText.init();
    ```

### လုပ်ဆောင်ရန် - flash memory မှ အသံကို ဖတ်ပါ

1. သင်ခန်းစာရဲ့ အစပိုင်းတွင် အသံကို flash memory တွင် record လုပ်ထားသည်။ ဒီအသံကို Speech Services REST API ကို ပို့ရန်လိုအပ်သည်၊ ထို့ကြောင့် flash memory မှ ဖတ်ရန်လိုအပ်သည်။ memory buffer တွင် load လုပ်၍ မရပါ၊ အကြီးမားလွန်းသည်။ REST calls ပြုလုပ်သည့် `HTTPClient` class သည် Arduino Stream ကို အသုံးပြု၍ data ကို stream လုပ်နိုင်သည် - data ကို အပိုင်းပိုင်းအနည်းငယ်ဖြင့် load လုပ်ပြီး request အတွင်း data ကို တစ်ခါတစ်ခါ ပို့သည်။ Stream ကို call လုပ်တိုင်း next block of data ကို return ပြုလုပ်သည်။ Arduino stream ကို flash memory မှ data ကို ဖတ်နိုင်ရန် ဖန်တီးနိုင်သည်။ `src` folder တွင် `flash_stream.h` ဟုခေါ်သော ဖိုင်အသစ်တစ်ခု ဖန်တီးပြီး အောက်ပါကုဒ်ကို ထည့်ပါ။

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

    ဒီမှာ `FlashStream` class ကို Arduino `Stream` class မှ ဆင်းသက်ထားသည်။ ဒီဟာက abstract class ဖြစ်ပြီး derived classes တွေက အချို့ method များကို implement လုပ်ရမည်၊ ဒီ method များကို ဒီ class တွင် သတ်မှတ်ထားသည်။

    ✅ Arduino Streams အကြောင်းကို [Arduino Stream documentation](https://www.arduino.cc/reference/en/language/functions/communication/stream/) တွင် ပိုမိုဖတ်ရှုနိုင်ပါသည်။

1. `private` section တွင် အောက်ပါ fields များကို ထည့်ပါ။

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    ဒီဟာက flash memory မှ data ကို ဖတ်ရန် temporary buffer ကို သတ်မှတ်ထားပြီး buffer မှ current position, flash memory မှ current address နှင့် flash memory device ကို သိမ်းဆည်းထားသည်။

1. `private` section တွင် အောက်ပါ method ကို ထည့်ပါ။

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    ဒီကုဒ်သည် flash memory မှ current address တွင် data ကို ဖတ်ပြီး buffer တွင် သိမ်းဆည်းသည်။ ထို့နောက် address ကို တိုးမြှင့်ပြီး နောက်တစ်ကြိမ် call လုပ်သောအခါ memory ရဲ့ next block ကို ဖတ်သည်။ buffer size ကို REST API ကို တစ်ခါတစ်ခါ ပို့မည့် HTTPClient ရဲ့ largest chunk အတိုင်း သတ်မှတ်ထားသည်။

    > 💁 flash memory ကို ဖျက်ရန် grain size ကို အသုံးပြုရမည်၊ ဖတ်ရန်အတွက်တော့ မလိုအပ်ပါ။

1. ဒီ class ရဲ့ `public` section တွင် constructor ကို ထည့်ပါ။

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    ဒီ constructor သည် flash memory block ရဲ့ start မှ data ကို ဖတ်ရန် field များကို setup လုပ်ပြီး buffer တွင် ပထမဆုံး chunk ကို load လုပ်သည်။

1. `write` method ကို implement လုပ်ပါ။ ဒီ stream သည် data ကို ဖတ်ရန်သာဖြစ်သောကြောင့် ဘာမှမလုပ်ဘဲ 0 ကို return ပြုလုပ်နိုင်သည်။

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. `peek` method ကို implement လုပ်ပါ။ ဒီဟာက current position မှ data ကို stream ကို မရွှေ့ဘဲ return ပြုလုပ်သည်။ `peek` ကို အကြိမ်ကြိမ် call လုပ်ပါက data ကို မဖတ်မီအချိန်အထိ အတူတူ data ကို return ပြုလုပ်မည်။

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. `available` function ကို implement လုပ်ပါ။ stream မှ data ကို ဘယ်လောက်ဖတ်နိုင်မည်ကို return ပြုလုပ်သည်၊ stream ပြီးဆုံးပါက -1 ကို return ပြုလုပ်သည်။ ဒီ class အတွက် HTTPClient ရဲ့ chunk size ထက် မပိုသော data ကို return ပြုလုပ်မည်။ stream ကို HTTP client တွင် အသုံးပြုသောအခါ available function ကို call လုပ်ပြီး data ကို ဘယ်လောက် request ပြုလုပ်မည်ကို ဆုံးဖြတ်သည်။ chunk size ထက် data မပိုပါက chunk size ကို return ပြုလုပ်သည်။ data မရှိတော့ပါက -1 ကို return ပြုလုပ်သည်။

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

1. `read` method ကို implement လုပ်ပြီး buffer မှ next byte ကို return ပြုလုပ်ပါ၊ position ကို တိုးမြှင့်ပါ။ position သည် buffer size ထက် ကျော်လွန်ပါက flash memory မှ next block ကို buffer တွင် populate လုပ်ပြီး position ကို reset လုပ်ပါ။

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

1. `speech_to_text.h` header ဖိုင်တွင် ဒီ header ဖိုင်အသစ်ကို include directive အဖြစ် ထည့်ပါ။

    ```cpp
    #include "flash_stream.h"
    ```

### လုပ်ဆောင်ရန် - အသံကို စာသားအဖြစ် ပြောင်းပါ

1. အသံကို REST API ကို အသုံးပြု၍ Speech Service ကို ပို့ခြင်းအားဖြင့် စာသားအဖြစ် ပြောင်းနိုင်သည်။ ဒီ REST API သည် token issuer နှင့် certificate မတူသောကြောင့် `config.h` header ဖိုင်တွင် အောက်ပါကုဒ်ကို ထည့်ပါ။

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

1. location မပါသော speech URL အတွက် constant ကို ဒီဖိုင်တွင် ထည့်ပါ။ location နှင့် language ကို later တွင် ပေါင်းစပ်ပြီး full URL ကို ရယူမည်။

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. `speech_to_text.h` header ဖိုင်တွင် `SpeechToText` class ရဲ့ `private` section တွင် speech certificate ကို အသုံးပြုသော WiFi Client အတွက် field ကို သတ်မှတ်ပါ။

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. `init` method တွင် WiFi Client တွင် certificate ကို သတ်မှတ်ပါ။

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. `SpeechToText` class ရဲ့ `public` section တွင် အသံကို စာသားအဖြစ် ပြောင်းရန် method ကို သတ်မှတ်ပါ။

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. ဒီ method တွင် speech certificate ဖြင့် configure လုပ်ထားသော WiFi client ကို အသုံးပြု၍ HTTP client ကို ဖန်တီးပြီး location နှင့် language ဖြင့် speech URL ကို အသုံးပြုပါ။

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. connection အတွက် headers များကို သတ်မှတ်ရန်လိုအပ်သည်။

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    ဒီဟာက authorization ကို access token ဖြင့်၊ audio format ကို sample rate ဖြင့်၊ client သည် result ကို JSON အဖြစ် ရရှိရန် သတ်မှတ်ထားသည်။

1. ဒီအပြီး REST API call ကို ပြုလုပ်ရန် အောက်ပါကုဒ်ကို ထည့်ပါ။

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    ဒီဟာက `FlashStream` ကို ဖန်တီးပြီး REST API ကို data ကို stream လုပ်ရန် အသုံးပြုသည်။

1. ဒီအောက်တွင် အောက်ပါကုဒ်ကို ထည့်ပါ။

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

    response code ကို စစ်ဆေးသည်။

    response code သည် 200 ဖြစ်ပါက (success code) result ကို JSON မှ decode လုပ်ပြီး `DisplayText` property ကို `text` variable တွင် ထည့်သည်။ ဒီ property သည် အသံ၏ စာသား version ကို return ပြုလုပ်သည်။

    response code သည် 401 ဖြစ်ပါက access token သက်တမ်းကုန်သွားသည် (ဒီ tokens များသည် 10 မိနစ်သာ သက်တမ်းရှိသည်)။ အသစ် access token ကို တောင်းဆိုပြီး call ကို ထပ်မံပြုလုပ်သည်။

    အခြား response code ဖြစ်ပါက serial monitor တွင် error ကို ပို့ပြီး `text` ကို blank ထားသည်။

1. ဒီ method ရဲ့ အဆုံးတွင် HTTP client ကို ပိတ်ပြီး text ကို return ပြုလုပ်ရန် အောက်ပါကုဒ်ကို ထည့်ပါ။

    ```cpp
    httpClient.end();

    return text;
    ```

1. `main.cpp` တွင် `processAudio` function တွင် ဒီ `convertSpeechToText` method ကို call လုပ်ပြီး speech ကို serial monitor တွင် log လုပ်ပါ။

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. ဒီကုဒ်ကို build လုပ်ပြီး Wio Terminal သို့ upload လုပ်ပါ၊ serial monitor မှာ စမ်းသပ်ပါ။ `Ready` ကို serial monitor တွင် မြင်တွေ့သောအခါ၊ C button (power switch အနီးဆုံး ဘယ်ဘက်မှာရှိသော button) ကို နှိပ်ပြီး ပြောပါ။ 4 စက္ကန့်အတွင်း အသံကို ဖမ်းယူပြီး စာသားအဖြစ် ပြောင်းလဲမည်။

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

> 💁 ဒီကုဒ်ကို [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) folder တွင် ရှာဖွေကြည့်နိုင်ပါသည်။

😀 သင်၏ အသံမှ စာသား ပြောင်းလဲရေး အစီအစဉ်အောင်မြင်ခဲ့ပါသည်!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါရှိနိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် ရှုလေ့လာသင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွဲအချော်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။