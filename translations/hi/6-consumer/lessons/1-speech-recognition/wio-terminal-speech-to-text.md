<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-25T17:55:19+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "hi"
}
-->
# वाक से पाठ - Wio Terminal

इस पाठ के इस भाग में, आप कोड लिखेंगे जो कैप्चर किए गए ऑडियो में वाक को पाठ में बदलने के लिए स्पीच सर्विस का उपयोग करेगा।

## ऑडियो को स्पीच सर्विस पर भेजें

ऑडियो को REST API का उपयोग करके स्पीच सर्विस पर भेजा जा सकता है। स्पीच सर्विस का उपयोग करने के लिए, पहले आपको एक एक्सेस टोकन का अनुरोध करना होगा, फिर उस टोकन का उपयोग REST API तक पहुंचने के लिए करना होगा। ये एक्सेस टोकन 10 मिनट के बाद समाप्त हो जाते हैं, इसलिए आपके कोड को नियमित रूप से इन्हें अनुरोध करना चाहिए ताकि वे हमेशा अद्यतन रहें।

### कार्य - एक्सेस टोकन प्राप्त करें

1. `smart-timer` प्रोजेक्ट खोलें यदि यह पहले से खुला नहीं है।

1. `platformio.ini` फाइल में निम्नलिखित लाइब्रेरी डिपेंडेंसी जोड़ें ताकि WiFi तक पहुंचा जा सके और JSON को हैंडल किया जा सके:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. `config.h` हेडर फाइल में निम्नलिखित कोड जोड़ें:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    `<SSID>` और `<PASSWORD>` को अपने WiFi के संबंधित मानों से बदलें।

    `<API_KEY>` को अपनी स्पीच सर्विस रिसोर्स की API कुंजी से बदलें। `<LOCATION>` को उस स्थान से बदलें जिसे आपने स्पीच सर्विस रिसोर्स बनाते समय उपयोग किया था।

    `<LANGUAGE>` को उस भाषा के लोकल नाम से बदलें जिसमें आप बोलेंगे, जैसे `en-GB` अंग्रेजी के लिए, या `zn-HK` कैंटोनीज़ के लिए। समर्थित भाषाओं और उनके लोकल नामों की सूची [Microsoft Docs पर भाषा और आवाज़ समर्थन दस्तावेज़](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) में पाई जा सकती है।

    `TOKEN_URL` कॉन्स्टेंट टोकन जारीकर्ता का URL है जिसमें स्थान शामिल नहीं है। इसे बाद में स्थान के साथ जोड़ा जाएगा ताकि पूरा URL प्राप्त हो सके।

1. Custom Vision से कनेक्ट करने की तरह, आपको टोकन जारी करने वाली सर्विस से कनेक्ट करने के लिए HTTPS कनेक्शन का उपयोग करना होगा। `config.h` के अंत में निम्नलिखित कोड जोड़ें:

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

    यह वही प्रमाणपत्र है जिसे आपने Custom Vision से कनेक्ट करते समय उपयोग किया था।

1. `main.cpp` फाइल के शीर्ष पर WiFi हेडर फाइल और config हेडर फाइल के लिए एक इनक्लूड जोड़ें:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. `setup` फंक्शन के ऊपर `main.cpp` में WiFi से कनेक्ट करने के लिए कोड जोड़ें:

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

1. इस फंक्शन को `setup` फंक्शन से कॉल करें, सीरियल कनेक्शन स्थापित होने के बाद:

    ```cpp
    connectWiFi();
    ```

1. `src` फोल्डर में एक नई हेडर फाइल बनाएं जिसका नाम `speech_to_text.h` हो। इस हेडर फाइल में निम्नलिखित कोड जोड़ें:

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

    इसमें HTTP कनेक्शन, कॉन्फ़िगरेशन और `mic.h` हेडर फाइल के लिए कुछ आवश्यक हेडर फाइलें शामिल हैं, और `SpeechToText` नामक एक क्लास को परिभाषित किया गया है, फिर उस क्लास का एक इंस्टेंस घोषित किया गया है जिसे बाद में उपयोग किया जा सकता है।

1. इस क्लास के `private` सेक्शन में निम्नलिखित 2 फील्ड जोड़ें:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` एक WiFi क्लाइंट है जो HTTPS का उपयोग करता है और इसे एक्सेस टोकन प्राप्त करने के लिए उपयोग किया जाएगा। यह टोकन फिर `_access_token` में संग्रहीत किया जाएगा।

1. `private` सेक्शन में निम्नलिखित मेथड जोड़ें:

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

    यह कोड स्पीच रिसोर्स के स्थान का उपयोग करके टोकन जारीकर्ता API के लिए URL बनाता है। फिर यह एक `HTTPClient` बनाता है जो वेब अनुरोध करता है, इसे टोकन एंडपॉइंट्स प्रमाणपत्र के साथ कॉन्फ़िगर किए गए WiFi क्लाइंट का उपयोग करने के लिए सेट करता है। यह API कुंजी को कॉल के लिए एक हेडर के रूप में सेट करता है। फिर यह प्रमाणपत्र प्राप्त करने के लिए एक POST अनुरोध करता है, और यदि कोई त्रुटि होती है तो पुनः प्रयास करता है। अंत में एक्सेस टोकन लौटाया जाता है।

1. `public` सेक्शन में, एक्सेस टोकन प्राप्त करने के लिए एक मेथड जोड़ें। यह बाद के पाठों में टेक्स्ट को वाक में बदलने के लिए आवश्यक होगा।

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. `public` सेक्शन में, एक `init` मेथड जोड़ें जो टोकन क्लाइंट को सेट करता है:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    यह WiFi क्लाइंट पर प्रमाणपत्र सेट करता है, फिर एक्सेस टोकन प्राप्त करता है।

1. `main.cpp` में, इस नई हेडर फाइल को इनक्लूड डायरेक्टिव्स में जोड़ें:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `setup` फंक्शन के अंत में, `mic.init` कॉल के बाद लेकिन सीरियल मॉनिटर में `Ready` लिखने से पहले `SpeechToText` क्लास को इनिशियलाइज़ करें:

    ```cpp
    speechToText.init();
    ```

### कार्य - फ्लैश मेमोरी से ऑडियो पढ़ें

1. इस पाठ के पहले भाग में, ऑडियो को फ्लैश मेमोरी में रिकॉर्ड किया गया था। इस ऑडियो को स्पीच सर्विस REST API पर भेजने की आवश्यकता होगी, इसलिए इसे फ्लैश मेमोरी से पढ़ा जाना चाहिए। इसे इन-मेमोरी बफर में लोड नहीं किया जा सकता क्योंकि यह बहुत बड़ा होगा। `HTTPClient` क्लास जो REST कॉल करता है, वह Arduino स्ट्रीम का उपयोग करके डेटा को स्ट्रीम कर सकता है - एक क्लास जो छोटे टुकड़ों में डेटा लोड कर सकता है, और एक समय में एक टुकड़ा अनुरोध के हिस्से के रूप में भेज सकता है। जब भी आप स्ट्रीम पर `read` कॉल करते हैं, यह डेटा का अगला ब्लॉक लौटाता है। एक Arduino स्ट्रीम बनाई जा सकती है जो फ्लैश मेमोरी से पढ़ सकती है। `src` फोल्डर में एक नई फाइल बनाएं जिसका नाम `flash_stream.h` हो, और इसमें निम्नलिखित कोड जोड़ें:

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

    यह `FlashStream` क्लास को घोषित करता है, जो Arduino `Stream` क्लास से व्युत्पन्न है। यह एक अमूर्त क्लास है - व्युत्पन्न क्लास को कुछ मेथड्स को लागू करना होगा इससे पहले कि क्लास को इंस्टेंटिएट किया जा सके, और ये मेथड्स इस क्लास में परिभाषित हैं।

    ✅ Arduino स्ट्रीम पर अधिक पढ़ें [Arduino Stream दस्तावेज़](https://www.arduino.cc/reference/en/language/functions/communication/stream/) में।

1. `private` सेक्शन में निम्नलिखित फील्ड जोड़ें:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    यह फ्लैश मेमोरी से पढ़े गए डेटा को संग्रहीत करने के लिए एक अस्थायी बफर को परिभाषित करता है, साथ ही बफर से पढ़ने के समय वर्तमान स्थिति, फ्लैश मेमोरी से पढ़ने के लिए वर्तमान पता, और फ्लैश मेमोरी डिवाइस को संग्रहीत करता है।

1. `private` सेक्शन में निम्नलिखित मेथड जोड़ें:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    यह कोड फ्लैश मेमोरी से वर्तमान पते पर पढ़ता है और डेटा को बफर में संग्रहीत करता है। फिर यह पता बढ़ाता है, ताकि अगली कॉल मेमोरी के अगले ब्लॉक को पढ़े। बफर का आकार HTTPClient द्वारा REST API पर एक समय में भेजे जाने वाले सबसे बड़े टुकड़े के आधार पर होता है।

    > 💁 फ्लैश मेमोरी को मिटाना ग्रेन साइज का उपयोग करके किया जाना चाहिए, जबकि पढ़ना इसके विपरीत नहीं है।

1. इस क्लास के `public` सेक्शन में एक कंस्ट्रक्टर जोड़ें:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    यह कंस्ट्रक्टर सभी फील्ड्स को फ्लैश मेमोरी ब्लॉक की शुरुआत से पढ़ना शुरू करने के लिए सेट करता है, और बफर में डेटा के पहले टुकड़े को लोड करता है।

1. `write` मेथड को लागू करें। यह स्ट्रीम केवल डेटा पढ़ेगा, इसलिए यह कुछ नहीं करेगा और 0 लौटाएगा:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. `peek` मेथड को लागू करें। यह वर्तमान स्थिति पर डेटा लौटाता है बिना स्ट्रीम को आगे बढ़ाए। `peek` को कई बार कॉल करने से हमेशा वही डेटा लौटेगा जब तक कि स्ट्रीम से कोई डेटा नहीं पढ़ा जाता।

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. `available` फंक्शन को लागू करें। यह स्ट्रीम से पढ़े जा सकने वाले बाइट्स की संख्या लौटाता है, या -1 यदि स्ट्रीम पूरी हो चुकी है। इस क्लास के लिए, अधिकतम उपलब्धता HTTPClient के चंक साइज से अधिक नहीं होगी। जब यह स्ट्रीम HTTP क्लाइंट में उपयोग की जाती है, तो यह फंक्शन यह देखने के लिए कॉल करता है कि कितना डेटा उपलब्ध है, फिर REST API पर भेजने के लिए उतना डेटा अनुरोध करता है। हम नहीं चाहते कि प्रत्येक चंक HTTP क्लाइंट के चंक साइज से अधिक हो, इसलिए यदि उससे अधिक उपलब्ध है, तो चंक साइज लौटाया जाता है। यदि कम है, तो जितना उपलब्ध है वह लौटाया जाता है। एक बार जब सभी डेटा स्ट्रीम हो जाता है, तो -1 लौटाया जाता है।

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

1. `read` मेथड को लागू करें ताकि बफर से अगला बाइट लौटाया जा सके, स्थिति को बढ़ाते हुए। यदि स्थिति बफर के आकार से अधिक हो जाती है, तो यह फ्लैश मेमोरी से अगले ब्लॉक के साथ बफर को पॉप्युलेट करता है और स्थिति को रीसेट करता है।

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

1. `speech_to_text.h` हेडर फाइल में, इस नई हेडर फाइल के लिए एक इनक्लूड डायरेक्टिव जोड़ें:

    ```cpp
    #include "flash_stream.h"
    ```

### कार्य - वाक को पाठ में बदलें

1. वाक को पाठ में बदलने के लिए ऑडियो को REST API के माध्यम से स्पीच सर्विस पर भेजा जा सकता है। इस REST API का प्रमाणपत्र टोकन जारीकर्ता से अलग है, इसलिए `config.h` हेडर फाइल में इस प्रमाणपत्र को परिभाषित करने के लिए निम्नलिखित कोड जोड़ें:

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

1. इस फाइल में एक कॉन्स्टेंट जोड़ें जो स्थान के बिना स्पीच URL को परिभाषित करता है। इसे बाद में स्थान और भाषा के साथ जोड़ा जाएगा ताकि पूरा URL प्राप्त हो सके।

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. `speech_to_text.h` हेडर फाइल में, `SpeechToText` क्लास के `private` सेक्शन में, स्पीच प्रमाणपत्र का उपयोग करने वाले WiFi क्लाइंट के लिए एक फील्ड परिभाषित करें:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. `init` मेथड में, इस WiFi क्लाइंट पर प्रमाणपत्र सेट करें:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. `SpeechToText` क्लास के `public` सेक्शन में, वाक को पाठ में बदलने के लिए एक मेथड परिभाषित करें:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. इस मेथड में, स्पीच प्रमाणपत्र के साथ कॉन्फ़िगर किए गए WiFi क्लाइंट का उपयोग करके एक HTTP क्लाइंट बनाने और स्थान और भाषा के साथ सेट किए गए स्पीच URL का उपयोग करने के लिए निम्नलिखित कोड जोड़ें:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. कनेक्शन पर कुछ हेडर सेट करने की आवश्यकता है:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    यह हेडर को एक्सेस टोकन का उपयोग करके प्राधिकरण के लिए सेट करता है, ऑडियो प्रारूप को सैंपल रेट का उपयोग करके सेट करता है, और यह सेट करता है कि क्लाइंट परिणाम को JSON के रूप में अपेक्षित करता है।

1. इसके बाद, REST API कॉल करने के लिए निम्नलिखित कोड जोड़ें:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    यह एक `FlashStream` बनाता है और REST API पर डेटा स्ट्रीम करने के लिए इसका उपयोग करता है।

1. इसके नीचे, निम्नलिखित कोड जोड़ें:

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

    यह कोड प्रतिक्रिया कोड की जांच करता है।

    यदि यह 200 है, जो सफलता का कोड है, तो परिणाम प्राप्त किया जाता है, JSON से डिकोड किया जाता है, और `DisplayText` प्रॉपर्टी को `text` वेरिएबल में सेट किया जाता है। यह वह प्रॉपर्टी है जिसमें वाक का टेक्स्ट संस्करण लौटाया जाता है।

    यदि प्रतिक्रिया कोड 401 है, तो एक्सेस टोकन समाप्त हो गया है (ये टोकन केवल 10 मिनट तक चलते हैं)। एक नया एक्सेस टोकन अनुरोध किया जाता है, और कॉल को फिर से किया जाता है।

    अन्यथा, एक त्रुटि सीरियल मॉनिटर पर भेजी जाती है, और `text` खाली छोड़ दिया जाता है।

1. इस मेथड के अंत में निम्नलिखित कोड जोड़ें ताकि HTTP क्लाइंट को बंद किया जा सके और टेक्स्ट लौटाया जा सके:

    ```cpp
    httpClient.end();

    return text;
    ```

1. `main.cpp` में, इस नए `convertSpeechToText` मेथड को `processAudio` फंक्शन में कॉल करें, फिर वाक को सीरियल मॉनिटर पर लॉग करें:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. इस कोड को बनाएं, इसे अपने Wio Terminal पर अपलोड करें और इसे सीरियल मॉनिटर के माध्यम से टेस्ट करें। एक बार जब आप सीरियल मॉनिटर में `Ready` देखें, तो C बटन दबाएं (जो बाईं ओर है, पावर स्विच के सबसे करीब), और बोलें। 4 सेकंड का ऑडियो कैप्चर किया जाएगा, फिर इसे टेक्स्ट में बदल दिया जाएगा।

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

> 💁 आप इस कोड को [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) फोल्डर में पा सकते हैं।

😀 आपका वाक से पाठ प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।