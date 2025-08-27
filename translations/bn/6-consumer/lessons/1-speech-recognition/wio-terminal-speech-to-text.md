<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T14:16:06+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "bn"
}
-->
# স্পিচ টু টেক্সট - Wio Terminal

এই পাঠের এই অংশে, আপনি কোড লিখবেন যা ক্যাপচার করা অডিওর স্পিচকে টেক্সটে রূপান্তর করবে স্পিচ সার্ভিস ব্যবহার করে।

## অডিও স্পিচ সার্ভিসে পাঠানো

অডিও স্পিচ সার্ভিসে REST API ব্যবহার করে পাঠানো যেতে পারে। স্পিচ সার্ভিস ব্যবহার করতে হলে প্রথমে একটি অ্যাক্সেস টোকেন অনুরোধ করতে হবে, তারপর সেই টোকেন ব্যবহার করে REST API-তে প্রবেশ করতে হবে। এই অ্যাক্সেস টোকেন ১০ মিনিটের জন্য বৈধ থাকে, তাই আপনার কোডটি নিয়মিতভাবে টোকেন অনুরোধ করবে যাতে এটি সর্বদা আপডেট থাকে।

### টাস্ক - অ্যাক্সেস টোকেন পাওয়া

1. যদি `smart-timer` প্রজেক্টটি এখনও খোলা না থাকে, তাহলে এটি খুলুন।

1. `platformio.ini` ফাইলে নিম্নলিখিত লাইব্রেরি ডিপেনডেন্সি যোগ করুন যাতে WiFi অ্যাক্সেস এবং JSON পরিচালনা করা যায়:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. `config.h` হেডার ফাইলে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    `<SSID>` এবং `<PASSWORD>` আপনার WiFi-এর প্রাসঙ্গিক মান দিয়ে প্রতিস্থাপন করুন।

    `<API_KEY>`-কে আপনার স্পিচ সার্ভিস রিসোর্সের API কী দিয়ে প্রতিস্থাপন করুন। `<LOCATION>`-কে সেই অবস্থান দিয়ে প্রতিস্থাপন করুন যা আপনি স্পিচ সার্ভিস রিসোর্স তৈরি করার সময় ব্যবহার করেছিলেন।

    `<LANGUAGE>`-কে সেই ভাষার লোকাল নাম দিয়ে প্রতিস্থাপন করুন যা আপনি কথা বলবেন, যেমন `en-GB` ইংরেজির জন্য বা `zn-HK` ক্যান্টোনিজের জন্য। Microsoft ডক্সে [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) এ সমর্থিত ভাষা এবং তাদের লোকাল নামের তালিকা খুঁজে পেতে পারেন।

    `TOKEN_URL` কনস্ট্যান্টটি টোকেন ইস্যু করার URL যা অবস্থান ছাড়া। এটি পরে অবস্থানের সাথে মিলিত হয়ে সম্পূর্ণ URL তৈরি করবে।

1. Custom Vision-এ সংযোগ করার মতো, আপনাকে টোকেন ইস্যু করার সার্ভিসে সংযোগ করতে HTTPS সংযোগ ব্যবহার করতে হবে। `config.h`-এর শেষে নিম্নলিখিত কোড যোগ করুন:

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

    এটি সেই একই সার্টিফিকেট যা আপনি Custom Vision-এ সংযোগ করার সময় ব্যবহার করেছিলেন।

1. `main.cpp` ফাইলের শীর্ষে WiFi হেডার ফাইল এবং config হেডার ফাইলের জন্য একটি ইনক্লুড যোগ করুন:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. `setup` ফাংশনের উপরে `main.cpp`-এ WiFi-তে সংযোগ করার কোড যোগ করুন:

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

1. সিরিয়াল সংযোগ স্থাপনের পরে `setup` ফাংশন থেকে এই ফাংশনটি কল করুন:

    ```cpp
    connectWiFi();
    ```

1. `src` ফোল্ডারে একটি নতুন হেডার ফাইল তৈরি করুন যার নাম `speech_to_text.h`। এই হেডার ফাইলে নিম্নলিখিত কোড যোগ করুন:

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

    এটি HTTP সংযোগ, কনফিগারেশন এবং `mic.h` হেডার ফাইলের জন্য কিছু প্রয়োজনীয় হেডার ফাইল অন্তর্ভুক্ত করে এবং `SpeechToText` নামে একটি ক্লাস সংজ্ঞায়িত করে, পরে এই ক্লাসের একটি ইনস্ট্যান্স ঘোষণা করে যা পরে ব্যবহার করা যেতে পারে।

1. এই ক্লাসের `private` সেকশনে নিম্নলিখিত ২টি ফিল্ড যোগ করুন:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` একটি WiFi ক্লায়েন্ট যা HTTPS ব্যবহার করে এবং এটি অ্যাক্সেস টোকেন পেতে ব্যবহৃত হবে। এই টোকেনটি পরে `_access_token`-এ সংরক্ষণ করা হবে।

1. `private` সেকশনে নিম্নলিখিত মেথড যোগ করুন:

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

    এই কোডটি স্পিচ রিসোর্সের অবস্থান ব্যবহার করে টোকেন ইস্যু করার API-এর URL তৈরি করে। তারপর এটি একটি `HTTPClient` তৈরি করে ওয়েব অনুরোধ করার জন্য, এটি টোকেন এন্ডপয়েন্টের সার্টিফিকেট দিয়ে কনফিগার করা WiFi ক্লায়েন্ট ব্যবহার করে সেট আপ করে। এটি API কীকে কলের জন্য একটি হেডার হিসেবে সেট করে। তারপর এটি সার্টিফিকেট পেতে একটি POST অনুরোধ করে, কোনো ত্রুটি পেলে পুনরায় চেষ্টা করে। অবশেষে অ্যাক্সেস টোকেনটি ফেরত দেয়।

1. `public` সেকশনে একটি মেথড যোগ করুন যা অ্যাক্সেস টোকেন পেতে সাহায্য করবে। এটি পরবর্তী পাঠে টেক্সটকে স্পিচে রূপান্তর করতে প্রয়োজন হবে।

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. `public` সেকশনে একটি `init` মেথড যোগ করুন যা টোকেন ক্লায়েন্ট সেট আপ করে:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    এটি WiFi ক্লায়েন্টে সার্টিফিকেট সেট করে, তারপর অ্যাক্সেস টোকেন পায়।

1. `main.cpp`-এ এই নতুন হেডার ফাইলটি ইনক্লুড ডিরেক্টিভে যোগ করুন:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `setup` ফাংশনের শেষে `mic.init` কল করার পরে কিন্তু সিরিয়াল মনিটরে `Ready` লেখার আগে `SpeechToText` ক্লাসটি ইনিশিয়ালাইজ করুন:

    ```cpp
    speechToText.init();
    ```

### টাস্ক - ফ্ল্যাশ মেমরি থেকে অডিও পড়া

1. পাঠের আগের অংশে, অডিওটি ফ্ল্যাশ মেমরিতে রেকর্ড করা হয়েছিল। এই অডিওটি Speech Services REST API-তে পাঠানো হবে, তাই এটি ফ্ল্যাশ মেমরি থেকে পড়তে হবে। এটি ইন-মেমরি বাফারে লোড করা যাবে না কারণ এটি খুব বড় হবে। `HTTPClient` ক্লাসটি REST কল করতে একটি Arduino Stream ব্যবহার করে ডেটা স্ট্রিম করতে পারে - একটি ক্লাস যা ছোট ছোট অংশে ডেটা লোড করতে পারে, একবারে একটি অংশ পাঠাতে পারে। আপনি যখনই একটি স্ট্রিমে `read` কল করবেন এটি পরবর্তী ব্লকটি ফেরত দেয়। একটি Arduino স্ট্রিম তৈরি করা যেতে পারে যা ফ্ল্যাশ মেমরি থেকে পড়তে পারে। `src` ফোল্ডারে একটি নতুন ফাইল তৈরি করুন যার নাম `flash_stream.h`, এবং এতে নিম্নলিখিত কোড যোগ করুন:

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

    এটি `FlashStream` ক্লাস ঘোষণা করে, Arduino `Stream` ক্লাস থেকে ডেরাইভ করে। এটি একটি অ্যাবস্ট্রাক্ট ক্লাস - ডেরাইভ করা ক্লাসগুলিকে কয়েকটি মেথড বাস্তবায়ন করতে হবে ক্লাসটি ইনস্ট্যানশিয়েট করার আগে, এবং এই মেথডগুলি এই ক্লাসে সংজ্ঞায়িত করা হয়েছে।

    ✅ Arduino Streams সম্পর্কে আরও পড়ুন [Arduino Stream documentation](https://www.arduino.cc/reference/en/language/functions/communication/stream/) এ।

1. `private` সেকশনে নিম্নলিখিত ফিল্ড যোগ করুন:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    এটি একটি অস্থায়ী বাফার সংজ্ঞায়িত করে যা ফ্ল্যাশ মেমরি থেকে পড়া ডেটা সংরক্ষণ করে, বর্তমান অবস্থান, বর্তমান ঠিকানা এবং ফ্ল্যাশ মেমরি ডিভাইস সংরক্ষণ করে।

1. `private` সেকশনে নিম্নলিখিত মেথড যোগ করুন:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    এই কোডটি ফ্ল্যাশ মেমরি থেকে বর্তমান ঠিকানায় পড়ে এবং ডেটা একটি বাফারে সংরক্ষণ করে। তারপর এটি ঠিকানাটি বৃদ্ধি করে, যাতে পরবর্তী কল পরবর্তী ব্লকটি পড়ে। বাফারটি HTTPClient-এর সর্বোচ্চ চাঙ্ক সাইজের উপর ভিত্তি করে তৈরি করা হয়েছে যা REST API-তে একবারে পাঠানো হবে।

    > 💁 ফ্ল্যাশ মেমরি মুছতে গ্রেইন সাইজ ব্যবহার করতে হয়, তবে পড়ার ক্ষেত্রে তা প্রয়োজন হয় না।

1. এই ক্লাসের `public` সেকশনে একটি কনস্ট্রাক্টর যোগ করুন:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    এই কনস্ট্রাক্টরটি সমস্ত ফিল্ড সেট আপ করে যাতে ফ্ল্যাশ মেমরি ব্লকের শুরু থেকে পড়া শুরু হয় এবং প্রথম চাঙ্কটি বাফারে লোড করে।

1. `write` মেথডটি বাস্তবায়ন করুন। এই স্ট্রিমটি শুধুমাত্র ডেটা পড়বে, তাই এটি কিছুই করবে না এবং ০ ফেরত দেবে:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. `peek` মেথডটি বাস্তবায়ন করুন। এটি বর্তমান অবস্থানে ডেটা ফেরত দেয় স্ট্রিমটি না সরিয়ে। একাধিকবার `peek` কল করলে একই ডেটা ফেরত দেয় যতক্ষণ না স্ট্রিম থেকে কোনো ডেটা পড়া হয়।

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. `available` ফাংশনটি বাস্তবায়ন করুন। এটি স্ট্রিম থেকে কতগুলো বাইট পড়া যেতে পারে তা ফেরত দেয়, অথবা -১ যদি স্ট্রিম সম্পূর্ণ হয়। এই ক্লাসের জন্য, সর্বাধিক উপলব্ধ HTTPClient-এর চাঙ্ক সাইজের বেশি হবে না। যখন এই স্ট্রিমটি HTTP ক্লায়েন্টে ব্যবহার করা হয় এটি এই ফাংশনটি কল করে দেখতে কতটা ডেটা উপলব্ধ, তারপর REST API-তে পাঠানোর জন্য সেই পরিমাণ ডেটা অনুরোধ করে। আমরা চাই না প্রতিটি চাঙ্ক HTTP ক্লায়েন্টের চাঙ্ক সাইজের বেশি হোক, তাই যদি বেশি উপলব্ধ থাকে তাহলে চাঙ্ক সাইজ ফেরত দেয়। যদি কম থাকে, তাহলে যতটা উপলব্ধ তা ফেরত দেয়। একবার সমস্ত ডেটা স্ট্রিম হয়ে গেলে, -১ ফেরত দেয়।

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

1. `read` মেথডটি বাস্তবায়ন করুন যাতে বাফার থেকে পরবর্তী বাইট ফেরত দেয়, অবস্থান বৃদ্ধি করে। যদি অবস্থান বাফারের সাইজ অতিক্রম করে, এটি ফ্ল্যাশ মেমরি থেকে পরবর্তী ব্লক দিয়ে বাফারটি পূরণ করে এবং অবস্থানটি রিসেট করে।

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

1. `speech_to_text.h` হেডার ফাইলে এই নতুন হেডার ফাইলের জন্য একটি ইনক্লুড ডিরেক্টিভ যোগ করুন:

    ```cpp
    #include "flash_stream.h"
    ```

### টাস্ক - স্পিচকে টেক্সটে রূপান্তর করা

1. স্পিচকে টেক্সটে রূপান্তর করা যেতে পারে অডিওটি Speech Service-এর REST API-তে পাঠিয়ে। এই REST API-এর টোকেন ইস্যু করার সার্টিফিকেটের থেকে আলাদা সার্টিফিকেট রয়েছে, তাই `config.h` হেডার ফাইলে এই সার্টিফিকেট সংজ্ঞায়িত করতে নিম্নলিখিত কোড যোগ করুন:

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

1. এই ফাইলে অবস্থান ছাড়া স্পিচ URL-এর জন্য একটি কনস্ট্যান্ট যোগ করুন। এটি পরে অবস্থান এবং ভাষার সাথে মিলিত হয়ে সম্পূর্ণ URL তৈরি করবে।

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. `speech_to_text.h` হেডার ফাইলে `SpeechToText` ক্লাসের `private` সেকশনে একটি WiFi ক্লায়েন্ট সংজ্ঞায়িত করুন যা স্পিচ সার্টিফিকেট ব্যবহার করে:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. `init` মেথডে এই WiFi ক্লায়েন্টে সার্টিফিকেট সেট করুন:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. `SpeechToText` ক্লাসের `public` সেকশনে স্পিচকে টেক্সটে রূপান্তর করার জন্য একটি মেথড সংজ্ঞায়িত করুন:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. এই মেথডে নিম্নলিখিত কোড যোগ করুন যাতে স্পিচ সার্টিফিকেট দিয়ে কনফিগার করা WiFi ক্লায়েন্ট ব্যবহার করে একটি HTTP ক্লায়েন্ট তৈরি করা যায় এবং অবস্থান এবং ভাষা সেট করা স্পিচ URL ব্যবহার করা যায়:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. সংযোগে কিছু হেডার সেট করতে হবে:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    এটি অ্যাক্সেস টোকেন ব্যবহার করে অথরাইজেশনের জন্য হেডার সেট করে, অডিও ফরম্যাটের জন্য স্যাম্পল রেট ব্যবহার করে এবং ক্লায়েন্ট JSON হিসেবে ফলাফল প্রত্যাশা করে সেট করে।

1. এর পরে, REST API কল করার জন্য নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    এটি একটি `FlashStream` তৈরি করে এবং REST API-তে ডেটা স্ট্রিম করতে এটি ব্যবহার করে।

1. এর নিচে নিম্নলিখিত কোড যোগ করুন:

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

    এই কোডটি রেসপন্স কোড চেক করে।

    যদি এটি ২০০ হয়, সফলতার কোড, তাহলে ফলাফলটি পুনরুদ্ধার করা হয়, JSON থেকে ডিকোড করা হয়, এবং `DisplayText` প্রপার্টি `text` ভেরিয়েবলে সেট করা হয়। এই প্রপার্টি স্পিচের টেক্সট ভার্সনটি ফেরত দেয়।

    যদি রেসপন্স কোড ৪০১ হয়, তাহলে অ্যাক্সেস টোকেনটি মেয়াদোত্তীর্ণ হয়েছে (এই টোকেনগুলি শুধুমাত্র ১০ মিনিটের জন্য বৈধ থাকে)। একটি নতুন অ্যাক্সেস টোকেন অনুরোধ করা হয়, এবং কলটি আবার করা হয়।

    অন্যথায়, একটি ত্রুটি সিরিয়াল মনিটরে পাঠানো হয়, এবং `text` ফাঁকা রাখা হয়।

1. এই মেথডের শেষে HTTP ক্লায়েন্ট বন্ধ করতে এবং টেক্সট ফেরত দিতে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    httpClient.end();

    return text;
    ```

1. `main.cpp`-এ এই নতুন `convertSpeechToText` মেথডটি `processAudio` ফাংশনে কল করুন, তারপর স্পিচটি সিরিয়াল মনিটরে লগ করুন:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. এই কোডটি তৈরি করুন, এটি আপনার Wio Terminal-এ আপলোড করুন এবং সিরিয়াল মনিটরের মাধ্যমে এটি পরীক্ষা করুন। একবার আপনি সিরিয়াল মনিটরে `Ready` দেখতে পান, C বোতামটি চাপুন (বাম দিকে, পাওয়ার সুইচের সবচেয়ে কাছাকাছি), এবং কথা বলুন। ৪ সেকেন্ডের অডিও ক্যাপচার করা হবে, তারপর টেক্সটে রূপান্তরিত হবে।

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

> 💁 আপনি এই কোডটি [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার স্পিচ টু টেক্সট প্রোগ্রাম সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিকতার জন্য চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা দায়বদ্ধ থাকব না।