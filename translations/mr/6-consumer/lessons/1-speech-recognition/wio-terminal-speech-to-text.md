<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T14:16:46+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "mr"
}
-->
# भाषण ते मजकूर - Wio Terminal

या धड्याच्या या भागात, तुम्ही कॅप्चर केलेल्या ऑडिओमधील भाषण मजकूरात रूपांतरित करण्यासाठी भाषण सेवेसाठी कोड लिहाल.

## ऑडिओ भाषण सेवेला पाठवा

ऑडिओ REST API चा वापर करून भाषण सेवेला पाठवता येतो. भाषण सेवा वापरण्यासाठी, प्रथम तुम्हाला प्रवेश टोकनची विनंती करावी लागेल, नंतर त्या टोकनचा वापर करून REST API ला प्रवेश मिळवा. हे प्रवेश टोकन 10 मिनिटांनंतर कालबाह्य होतात, त्यामुळे तुमच्या कोडने नियमितपणे त्यांची विनंती केली पाहिजे जेणेकरून ते नेहमी अद्ययावत राहतील.

### कार्य - प्रवेश टोकन मिळवा

1. `smart-timer` प्रकल्प उघडा, जर तो आधीच उघडलेला नसेल.

1. WiFi आणि JSON हाताळण्यासाठी `platformio.ini` फाइलमध्ये खालील लायब्ररी अवलंबित्वे जोडा:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. `config.h` हेडर फाइलमध्ये खालील कोड जोडा:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    `<SSID>` आणि `<PASSWORD>` तुमच्या WiFi साठी संबंधित मूल्यांनी बदला.

    `<API_KEY>` ला तुमच्या भाषण सेवा स्त्रोतासाठी API कीने बदला. `<LOCATION>` ला तुम्ही भाषण सेवा स्त्रोत तयार करताना वापरलेल्या स्थानाने बदला.

    `<LANGUAGE>` ला तुम्ही बोलत असलेल्या भाषेसाठी स्थानिक नावाने बदला, उदाहरणार्थ इंग्रजीसाठी `en-GB`, किंवा कॅन्टोनीजसाठी `zn-HK`. समर्थित भाषा आणि त्यांची स्थानिक नावे [Microsoft Docs वरील भाषा आणि आवाज समर्थन दस्तऐवज](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) मध्ये सापडतील.

    `TOKEN_URL` स्थिरांक हा स्थानाशिवाय टोकन जारीकर्त्याचा URL आहे. हे नंतर स्थानासह एकत्रित केले जाईल जेणेकरून पूर्ण URL मिळेल.

1. Custom Vision शी कनेक्ट करण्याप्रमाणेच, तुम्हाला टोकन जारी करणाऱ्या सेवेशी कनेक्ट करण्यासाठी HTTPS कनेक्शन वापरावे लागेल. `config.h` च्या शेवटी खालील कोड जोडा:

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

    हा तोच प्रमाणपत्र आहे जो तुम्ही Custom Vision शी कनेक्ट करताना वापरला होता.

1. `main.cpp` फाइलच्या शीर्षस्थानी WiFi हेडर फाइल आणि config हेडर फाइलसाठी समाविष्ट जोडा:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. `setup` फंक्शनच्या वर `main.cpp` मध्ये WiFi शी कनेक्ट होण्यासाठी कोड जोडा:

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

1. `setup` फंक्शनमधून, सिरीयल कनेक्शन स्थापन झाल्यानंतर या फंक्शनला कॉल करा:

    ```cpp
    connectWiFi();
    ```

1. `src` फोल्डरमध्ये `speech_to_text.h` नावाची नवीन हेडर फाइल तयार करा. या हेडर फाइलमध्ये खालील कोड जोडा:

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

    यात HTTP कनेक्शन, कॉन्फिगरेशन आणि `mic.h` हेडर फाइलसाठी आवश्यक हेडर फाइल्स समाविष्ट आहेत, आणि `SpeechToText` नावाचा वर्ग परिभाषित केला आहे, नंतर नंतर वापरता येणाऱ्या त्या वर्गाची एक उदाहरणे घोषित केली आहे.

1. या वर्गाच्या `private` विभागात खालील 2 फील्ड जोडा:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` हा HTTPS वापरणारा WiFi क्लायंट आहे आणि तो प्रवेश टोकन मिळवण्यासाठी वापरला जाईल. हे टोकन नंतर `_access_token` मध्ये संग्रहित केले जाईल.

1. `private` विभागात खालील पद्धत जोडा:

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

    हा कोड भाषण स्त्रोताच्या स्थानाचा वापर करून टोकन जारीकर्ता API साठी URL तयार करतो. त्यानंतर वेब विनंती करण्यासाठी `HTTPClient` तयार करतो, टोकन एंडपॉइंट्स प्रमाणपत्रासह WiFi क्लायंट वापरण्यासाठी सेट करतो. कॉलसाठी API की हेडर म्हणून सेट करतो. नंतर प्रमाणपत्र मिळवण्यासाठी POST विनंती करतो, जर काही त्रुटी आल्या तर पुन्हा प्रयत्न करतो. शेवटी प्रवेश टोकन परत केले जाते.

1. `public` विभागात, प्रवेश टोकन मिळवण्यासाठी पद्धत जोडा. हे नंतरच्या धड्यांमध्ये मजकूर भाषणात रूपांतरित करण्यासाठी आवश्यक असेल.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. `public` विभागात, टोकन क्लायंट सेट करण्यासाठी `init` पद्धत जोडा:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    हे WiFi क्लायंटवर प्रमाणपत्र सेट करते, नंतर प्रवेश टोकन मिळवते.

1. `main.cpp` मध्ये, या नवीन हेडर फाइलला समाविष्ट निर्देशांमध्ये जोडा:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `setup` फंक्शनच्या शेवटी, `mic.init` कॉलनंतर पण `Ready` सिरीयल मॉनिटरवर लिहिण्यापूर्वी `SpeechToText` वर्ग प्रारंभ करा:

    ```cpp
    speechToText.init();
    ```

### कार्य - फ्लॅश मेमरीमधून ऑडिओ वाचा

1. या धड्याच्या आधीच्या भागात, ऑडिओ फ्लॅश मेमरीमध्ये रेकॉर्ड केला गेला होता. हा ऑडिओ भाषण सेवांच्या REST API ला पाठवला जाईल, त्यामुळे तो फ्लॅश मेमरीमधून वाचला पाहिजे. तो इन-मेमरी बफरमध्ये लोड केला जाऊ शकत नाही कारण तो खूप मोठा असेल. `HTTPClient` वर्ग जो REST कॉल करतो तो Arduino Stream वापरून डेटा प्रवाहित करू शकतो - एक वर्ग जो डेटा लहान तुकड्यांमध्ये लोड करू शकतो, विनंतीचा भाग म्हणून एकावेळी एक तुकडा पाठवतो. तुम्ही स्ट्रीमवर `read` कॉल केल्यावर प्रत्येक वेळी तो पुढील डेटा ब्लॉक परत करतो. Arduino स्ट्रीम तयार केला जाऊ शकतो जो फ्लॅश मेमरीमधून वाचू शकतो. `src` फोल्डरमध्ये `flash_stream.h` नावाची नवीन फाइल तयार करा आणि त्यात खालील कोड जोडा:

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

    हे `FlashStream` वर्ग घोषित करते, जो Arduino `Stream` वर्गावरून व्युत्पन्न केला जातो. हा एक अमूर्त वर्ग आहे - व्युत्पन्न वर्गांनी काही पद्धती लागू कराव्या लागतात, त्यानंतरच वर्ग उदाहरण तयार केला जाऊ शकतो.

    ✅ Arduino Streams बद्दल अधिक वाचा [Arduino Stream दस्तऐवज](https://www.arduino.cc/reference/en/language/functions/communication/stream/) मध्ये.

1. `private` विभागात खालील फील्ड जोडा:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    हे फ्लॅश मेमरीमधून वाचलेल्या डेटा साठवण्यासाठी तात्पुरता बफर परिभाषित करते, बफरमधून वाचताना चालू स्थिती साठवण्यासाठी फील्ड, फ्लॅश मेमरीमधून वाचण्यासाठी चालू पत्ता, आणि फ्लॅश मेमरी डिव्हाइस.

1. `private` विभागात खालील पद्धत जोडा:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    हा कोड फ्लॅश मेमरीमधून चालू पत्त्यावरून वाचतो आणि डेटा बफरमध्ये साठवतो. नंतर पत्ता वाढवतो, त्यामुळे पुढील कॉल पुढील मेमरी ब्लॉक वाचतो. बफर HTTPClient एकावेळी REST API ला पाठवेल अशा सर्वात मोठ्या तुकड्याच्या आकारावर आधारित आहे.

    > 💁 फ्लॅश मेमरी मिटवणे धान्याच्या आकाराने करावे लागते, वाचन मात्र तसे नाही.

1. या वर्गाच्या `public` विभागात एक कन्स्ट्रक्टर जोडा:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    हा कन्स्ट्रक्टर सर्व फील्ड्स फ्लॅश मेमरी ब्लॉकच्या सुरुवातीपासून वाचण्यास सेट करतो, आणि पहिला डेटा ब्लॉक बफरमध्ये लोड करतो.

1. `write` पद्धत लागू करा. हा स्ट्रीम फक्त डेटा वाचेल, त्यामुळे हे काहीही करू शकत नाही आणि 0 परत करू शकते:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. `peek` पद्धत लागू करा. हे स्ट्रीम पुढे न हलवता चालू स्थितीवरील डेटा परत करते. जर डेटा वाचला गेला नाही तर `peek` अनेक वेळा कॉल केल्यावर नेहमी समान डेटा परत करेल.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. `available` फंक्शन लागू करा. हे स्ट्रीममधून किती बाइट्स वाचले जाऊ शकतात ते परत करते, किंवा स्ट्रीम पूर्ण झाल्यास -1 परत करते. या वर्गासाठी, जास्तीत जास्त उपलब्धता HTTPClient च्या तुकड्याच्या आकारापेक्षा जास्त नसावी. जेव्हा हा स्ट्रीम HTTP क्लायंटमध्ये वापरला जातो तेव्हा तो किती डेटा उपलब्ध आहे ते पाहण्यासाठी हे फंक्शन कॉल करतो, नंतर REST API ला पाठवण्यासाठी त्या प्रमाणात डेटा विनंती करतो. आम्हाला प्रत्येक तुकडा HTTP क्लायंटच्या तुकड्याच्या आकारापेक्षा जास्त नको आहे, त्यामुळे जर जास्त उपलब्ध असेल तर तुकड्याचा आकार परत केला जातो. जर कमी असेल, तर जे उपलब्ध आहे ते परत केले जाते. सर्व डेटा प्रवाहित झाल्यावर, -1 परत केले जाते.

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

1. `read` पद्धत लागू करा जी बफरमधून पुढील बाइट परत करते, स्थिती वाढवते. जर स्थिती बफरच्या आकारापेक्षा जास्त असेल, तर ती फ्लॅश मेमरीमधून पुढील ब्लॉकने बफर भरते आणि स्थिती रीसेट करते.

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

1. `speech_to_text.h` हेडर फाइलमध्ये, या नवीन हेडर फाइलसाठी समाविष्ट निर्देश जोडा:

    ```cpp
    #include "flash_stream.h"
    ```

### कार्य - भाषण मजकूरात रूपांतरित करा

1. भाषण मजकूरात रूपांतरित करण्यासाठी ऑडिओ भाषण सेवेला REST API च्या माध्यमातून पाठवला जाऊ शकतो. या REST API ला टोकन जारीकर्त्यापेक्षा वेगळे प्रमाणपत्र आहे, त्यामुळे `config.h` हेडर फाइलमध्ये खालील कोड जोडा:

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

1. या फाइलमध्ये स्थानाशिवाय भाषण URL साठी एक स्थिरांक जोडा. हे नंतर स्थान आणि भाषेसह एकत्रित केले जाईल जेणेकरून पूर्ण URL मिळेल.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. `speech_to_text.h` हेडर फाइलमध्ये, `SpeechToText` वर्गाच्या `private` विभागात, भाषण प्रमाणपत्र वापरणाऱ्या WiFi क्लायंटसाठी फील्ड परिभाषित करा:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. `init` पद्धतीमध्ये, या WiFi क्लायंटवर प्रमाणपत्र सेट करा:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. `SpeechToText` वर्गाच्या `public` विभागात भाषण मजकूरात रूपांतरित करण्यासाठी पद्धत परिभाषित करण्यासाठी खालील कोड जोडा:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. या पद्धतीमध्ये खालील कोड जोडा जे भाषण प्रमाणपत्रासह कॉन्फिगर केलेल्या WiFi क्लायंटचा वापर करून HTTP क्लायंट तयार करते, आणि भाषण URL स्थान आणि भाषेसह सेट करते:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. कनेक्शनवर काही हेडर सेट करणे आवश्यक आहे:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    हे अधिकृततेसाठी प्रवेश टोकन, ऑडिओ स्वरूपासाठी नमुना दर, आणि क्लायंटला JSON स्वरूपात परिणाम अपेक्षित असल्याचे सेट करते.

1. यानंतर, REST API कॉल करण्यासाठी खालील कोड जोडा:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    हे `FlashStream` तयार करते आणि REST API ला डेटा प्रवाहित करण्यासाठी त्याचा वापर करते.

1. याखाली, खालील कोड जोडा:

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

    हा कोड प्रतिसाद कोड तपासतो.

    जर तो 200 असेल, यशासाठी कोड, तर परिणाम प्राप्त केला जातो, JSON मधून डिकोड केला जातो, आणि `DisplayText` प्रॉपर्टी `text` व्हेरिएबलमध्ये सेट केली जाते. भाषणाचा मजकूर परत करण्यासाठी ही प्रॉपर्टी वापरली जाते.

    जर प्रतिसाद कोड 401 असेल, तर प्रवेश टोकन कालबाह्य झाले आहे (ही टोकन फक्त 10 मिनिटे टिकतात). नवीन प्रवेश टोकनची विनंती केली जाते, आणि कॉल पुन्हा केला जातो.

    अन्यथा, सिरीयल मॉनिटरवर त्रुटी पाठवली जाते, आणि `text` रिकामे ठेवले जाते.

1. या पद्धतीच्या शेवटी खालील कोड जोडा जे HTTP क्लायंट बंद करते आणि मजकूर परत करते:

    ```cpp
    httpClient.end();

    return text;
    ```

1. `main.cpp` मध्ये, `processAudio` फंक्शनमध्ये या नवीन `convertSpeechToText` पद्धतीला कॉल करा, नंतर भाषण सिरीयल मॉनिटरवर लॉग करा:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. हा कोड तयार करा, Wio Terminal वर अपलोड करा आणि सिरीयल मॉनिटरद्वारे तपासा. एकदा तुम्हाला सिरीयल मॉनिटरमध्ये `Ready` दिसल्यावर, C बटण दाबा (डाव्या बाजूला, पॉवर स्विचजवळील), आणि बोला. 4 सेकंदांचा ऑडिओ कॅप्चर केला जाईल, नंतर मजकूरात रूपांतरित केला जाईल.

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

> 💁 तुम्हाला हा कोड [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) फोल्डरमध्ये सापडेल.

😀 तुमचा भाषण ते मजकूर प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) चा वापर करून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरे त्रुटी किंवा अचूकतेच्या अभावाने ग्रस्त असू शकतात. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून निर्माण होणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.