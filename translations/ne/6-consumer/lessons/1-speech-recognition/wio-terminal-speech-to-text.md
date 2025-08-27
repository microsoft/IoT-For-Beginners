<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T14:17:33+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "ne"
}
-->
# आवाजलाई पाठमा रूपान्तरण - Wio Terminal

यस पाठको यस भागमा, तपाईंले क्याप्चर गरिएको अडियोमा रहेको आवाजलाई पाठमा रूपान्तरण गर्न कोड लेख्नुहुनेछ, जसमा आवाज सेवा प्रयोग गरिन्छ।

## अडियोलाई आवाज सेवामा पठाउनुहोस्

अडियोलाई आवाज सेवामा REST API प्रयोग गरेर पठाउन सकिन्छ। आवाज सेवा प्रयोग गर्नका लागि, पहिलो चरणमा तपाईंले पहुँच टोकन अनुरोध गर्नुपर्छ, त्यसपछि उक्त टोकन प्रयोग गरेर REST API पहुँच गर्न सकिन्छ। यी पहुँच टोकनहरू १० मिनेटपछि समाप्त हुन्छन्, त्यसैले तपाईंको कोडले नियमित रूपमा टोकन अनुरोध गर्नुपर्छ ताकि टोकन सधैं अद्यावधिक रहोस्।

### कार्य - पहुँच टोकन प्राप्त गर्नुहोस्

1. यदि `smart-timer` प्रोजेक्ट खुला छैन भने यसलाई खोल्नुहोस्।

1. WiFi पहुँच गर्न र JSON ह्यान्डल गर्न `platformio.ini` फाइलमा निम्न पुस्तकालय निर्भरताहरू थप्नुहोस्:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. `config.h` हेडर फाइलमा निम्न कोड थप्नुहोस्:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    `<SSID>` र `<PASSWORD>` लाई तपाईंको WiFi का सम्बन्धित मानहरूमा प्रतिस्थापन गर्नुहोस्।

    `<API_KEY>` लाई तपाईंको आवाज सेवा स्रोतको API कुञ्जीमा प्रतिस्थापन गर्नुहोस्। `<LOCATION>` लाई तपाईंले आवाज सेवा स्रोत सिर्जना गर्दा प्रयोग गरेको स्थानमा प्रतिस्थापन गर्नुहोस्।

    `<LANGUAGE>` लाई तपाईं बोल्ने भाषाको स्थानीय नाममा प्रतिस्थापन गर्नुहोस्, जस्तै अंग्रेजीका लागि `en-GB`, वा क्यान्टोनिजका लागि `zn-HK`। समर्थित भाषाहरू र तिनका स्थानीय नामहरूको सूची [Microsoft Docs मा भाषा र आवाज समर्थन दस्तावेज](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) मा पाउन सकिन्छ।

    `TOKEN_URL` स्थिरांक टोकन जारीकर्ता URL हो, स्थानबिना। यो पछि स्थानसँग मिलाएर पूर्ण URL प्राप्त गरिनेछ।

1. Custom Vision मा जस्तै, टोकन जारी गर्ने सेवासँग जडान गर्न HTTPS जडान प्रयोग गर्न आवश्यक छ। `config.h` को अन्त्यमा निम्न कोड थप्नुहोस्:

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

    यो त्यही प्रमाणपत्र हो जुन तपाईंले Custom Vision मा जडान गर्दा प्रयोग गर्नुभएको थियो।

1. `main.cpp` फाइलको शीर्षमा WiFi हेडर फाइल र config हेडर फाइलको समावेश थप्नुहोस्:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. `setup` कार्यभन्दा माथि `main.cpp` मा WiFi जडान गर्न कोड थप्नुहोस्:

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

1. यो कार्यलाई `setup` कार्यबाट कल गर्नुहोस्, सीरियल जडान स्थापना भएपछि:

    ```cpp
    connectWiFi();
    ```

1. `src` फोल्डरमा नयाँ हेडर फाइल `speech_to_text.h` सिर्जना गर्नुहोस्। यस हेडर फाइलमा निम्न कोड थप्नुहोस्:

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

    यसले HTTP जडान, कन्फिगरेसन, र `mic.h` हेडर फाइलका लागि आवश्यक हेडर फाइलहरू समावेश गर्दछ, र `SpeechToText` नामक कक्षा परिभाषित गर्दछ, जसको उदाहरण पछि प्रयोग गर्न सकिन्छ।

1. यस कक्षाको `private` खण्डमा निम्न दुई क्षेत्रहरू थप्नुहोस्:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` एक WiFi Client हो जसले HTTPS प्रयोग गर्दछ र पहुँच टोकन प्राप्त गर्न प्रयोग गरिनेछ। यो टोकन `_access_token` मा भण्डारण गरिनेछ।

1. `private` खण्डमा निम्न विधि थप्नुहोस्:

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

    यो कोडले आवाज स्रोतको स्थान प्रयोग गरेर टोकन जारीकर्ता API को URL निर्माण गर्दछ। त्यसपछि यो वेब अनुरोध गर्न `HTTPClient` सिर्जना गर्दछ, टोकन अन्तबिन्दुको प्रमाणपत्रको साथ WiFi क्लाइन्ट सेटअप गर्दछ। यो API कुञ्जीलाई कलको हेडरको रूपमा सेट गर्दछ। त्यसपछि यो प्रमाणपत्र प्राप्त गर्न POST अनुरोध गर्दछ, यदि कुनै त्रुटि आएमा पुन: प्रयास गर्दछ। अन्ततः पहुँच टोकन फर्काइन्छ।

1. `public` खण्डमा पहुँच टोकन प्राप्त गर्न विधि थप्नुहोस्। यो विधि पछि पाठलाई आवाजमा रूपान्तरण गर्न आवश्यक हुनेछ।

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. `public` खण्डमा `init` विधि थप्नुहोस् जसले टोकन क्लाइन्ट सेटअप गर्दछ:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    यसले WiFi क्लाइन्टमा प्रमाणपत्र सेट गर्दछ, त्यसपछि पहुँच टोकन प्राप्त गर्दछ।

1. `main.cpp` मा यस नयाँ हेडर फाइललाई समावेश निर्देशनहरूमा थप्नुहोस्:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `setup` कार्यको अन्त्यमा `SpeechToText` कक्षा आरम्भ गर्नुहोस्, `mic.init` कलपछि तर सीरियल मोनिटरमा `Ready` लेख्नुअघि:

    ```cpp
    speechToText.init();
    ```

### कार्य - फ्ल्यास मेमोरीबाट अडियो पढ्नुहोस्

1. पाठको अघिल्लो भागमा, अडियो फ्ल्यास मेमोरीमा रेकर्ड गरिएको थियो। यो अडियोलाई Speech Services REST API मा पठाउन आवश्यक छ, त्यसैले यसलाई फ्ल्यास मेमोरीबाट पढ्नुपर्छ। यो इन-मेमोरी बफरमा लोड गर्न सकिँदैन किनभने यो धेरै ठूलो हुनेछ। `HTTPClient` कक्षाले REST कलहरूमा डेटा स्ट्रिम गर्न सक्छ, जसले सानो टुक्राहरूमा डेटा लोड गर्न सक्छ र एक पटकमा टुक्रा पठाउन सक्छ। प्रत्येक पटक तपाईं स्ट्रिममा `read` कल गर्नुहुन्छ, यसले अर्को डेटा ब्लक फर्काउँछ। Arduino स्ट्रिम सिर्जना गर्न सकिन्छ जसले फ्ल्यास मेमोरीबाट पढ्न सक्छ। `src` फोल्डरमा नयाँ फाइल `flash_stream.h` सिर्जना गर्नुहोस्, र यसमा निम्न कोड थप्नुहोस्:

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

    यसले `FlashStream` कक्षा घोषणा गर्दछ, Arduino `Stream` कक्षबाट व्युत्पन्न। यो एक अमूर्त कक्षा हो - व्युत्पन्न कक्षाहरूले केही विधिहरू कार्यान्वयन गर्नुपर्छ कक्षा उदाहरणित हुनुअघि, र यी विधिहरू यस कक्षामा परिभाषित छन्।

    ✅ Arduino Streams मा थप पढ्नुहोस् [Arduino Stream दस्तावेज](https://www.arduino.cc/reference/en/language/functions/communication/stream/) मा।

1. `private` खण्डमा निम्न क्षेत्रहरू थप्नुहोस्:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    यसले फ्ल्यास मेमोरीबाट पढिएको डेटा भण्डारण गर्न अस्थायी बफर परिभाषित गर्दछ, बफरबाट पढ्दा हालको स्थिति भण्डारण गर्न क्षेत्रहरू, हालको ठेगाना फ्ल्यास मेमोरीबाट पढ्न, र फ्ल्यास मेमोरी उपकरण।

1. `private` खण्डमा निम्न विधि थप्नुहोस्:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    यो कोडले फ्ल्यास मेमोरीको हालको ठेगानाबाट पढ्छ र डेटा बफरमा भण्डारण गर्दछ। त्यसपछि यो ठेगाना बढाउँछ, त्यसैले अर्को कलले मेमोरीको अर्को ब्लक पढ्छ। बफरको आकार REST API मा एक पटकमा `HTTPClient` द्वारा पठाइने सबैभन्दा ठूलो टुक्राको आधारमा सेट गरिएको छ।

    > 💁 फ्ल्यास मेमोरी मेट्न अनाज आकार प्रयोग गर्नुपर्छ, तर पढ्न भने आवश्यक छैन।

1. कक्षाको `public` खण्डमा कन्स्ट्रक्टर थप्नुहोस्:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    यो कन्स्ट्रक्टरले फ्ल्यास मेमोरी ब्लकको सुरुवातबाट पढ्न सुरु गर्न सबै क्षेत्रहरू सेट गर्दछ, र बफरमा पहिलो डेटा टुक्रा लोड गर्दछ।

1. `write` विधि कार्यान्वयन गर्नुहोस्। यो स्ट्रिमले केवल डेटा पढ्नेछ, त्यसैले यसले केही नगर्ने र 0 फर्काउने गर्न सक्छ:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. `peek` विधि कार्यान्वयन गर्नुहोस्। यसले स्ट्रिमलाई अगाडि बढाउँदा बिना हालको स्थितिमा डेटा फर्काउँछ। `peek` बारम्बार कल गर्दा, स्ट्रिमबाट कुनै डेटा नपढिएसम्म सधैं उही डेटा फर्काउँछ।

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. `available` कार्यान्वयन गर्नुहोस्। यसले स्ट्रिमबाट कति बाइटहरू पढ्न सकिन्छ भन्ने फर्काउँछ, वा यदि स्ट्रिम पूरा भयो भने -1 फर्काउँछ। यस कक्षाको लागि, अधिकतम उपलब्धता `HTTPClient` को टुक्रा आकारभन्दा बढी हुनेछैन। जब यो स्ट्रिम `HTTPClient` मा प्रयोग गरिन्छ, यसले यो कार्यलाई कति डेटा उपलब्ध छ हेर्न कल गर्दछ, त्यसपछि REST API मा पठाउन त्यति डेटा अनुरोध गर्दछ। हामी चाहन्न कि प्रत्येक टुक्रा `HTTPClient` को टुक्रा आकारभन्दा बढी होस्, त्यसैले यदि उपलब्धता बढी छ भने, टुक्रा आकार फर्काइन्छ। यदि कम छ भने, उपलब्धता फर्काइन्छ। सबै डेटा स्ट्रिम गरिसकेपछि, -1 फर्काइन्छ।

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

1. `read` विधि कार्यान्वयन गर्नुहोस् ताकि बफरबाट अर्को बाइट फर्काउँछ, स्थिति बढाउँदै। यदि स्थिति बफरको आकारभन्दा बढी छ भने, यो फ्ल्यास मेमोरीबाट अर्को ब्लकले बफर भर्छ र स्थिति रिसेट गर्दछ।

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

1. `speech_to_text.h` हेडर फाइलमा यस नयाँ हेडर फाइलको समावेश निर्देशन थप्नुहोस्:

    ```cpp
    #include "flash_stream.h"
    ```

### कार्य - आवाजलाई पाठमा रूपान्तरण गर्नुहोस्

1. आवाजलाई पाठमा रूपान्तरण गर्न अडियोलाई REST API मार्फत Speech Service मा पठाउन सकिन्छ। यस REST API को टोकन जारीकर्तासँग फरक प्रमाणपत्र छ, त्यसैले `config.h` हेडर फाइलमा निम्न कोड थप्नुहोस् ताकि यो प्रमाणपत्र परिभाषित होस्:

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

1. यस फाइलमा स्थानबिना आवाज URL को लागि स्थिरांक थप्नुहोस्। यो पछि स्थान र भाषासँग मिलाएर पूर्ण URL प्राप्त गरिनेछ।

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. `speech_to_text.h` हेडर फाइलमा, `SpeechToText` कक्षाको `private` खण्डमा, आवाज प्रमाणपत्र प्रयोग गर्ने WiFi Client को लागि क्षेत्र परिभाषित गर्नुहोस्:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. `init` विधिमा, यस WiFi Client मा प्रमाणपत्र सेट गर्नुहोस्:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. `SpeechToText` कक्षाको `public` खण्डमा आवाजलाई पाठमा रूपान्तरण गर्न विधि परिभाषित गर्न निम्न कोड थप्नुहोस्:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. यस विधिमा निम्न कोड थप्नुहोस् ताकि आवाज प्रमाणपत्रको साथ कन्फिगर गरिएको WiFi Client प्रयोग गरेर HTTP क्लाइन्ट सिर्जना गरियोस्, र स्थान र भाषासँग सेट गरिएको आवाज URL प्रयोग गरियोस्:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. जडानमा केही हेडरहरू सेट गर्न आवश्यक छ:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    यसले पहुँच टोकन प्रयोग गरेर प्राधिकरणका लागि हेडर सेट गर्दछ, अडियो ढाँचा नमूना दर प्रयोग गरेर सेट गर्दछ, र क्लाइन्टले JSON को रूपमा परिणाम अपेक्षा गर्दछ।

1. यसपछि, REST API कल गर्न निम्न कोड थप्नुहोस्:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    यसले `FlashStream` सिर्जना गर्दछ र यसलाई REST API मा डेटा स्ट्रिम गर्न प्रयोग गर्दछ।

1. यसको तल निम्न कोड थप्नुहोस्:

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

    यो कोडले प्रतिक्रिया कोड जाँच गर्दछ।

    यदि यो 200 हो, सफलताको कोड, त्यसपछि परिणाम प्राप्त गरिन्छ, JSON बाट डिकोड गरिन्छ, र `DisplayText` गुणलाई `text` चरमा सेट गरिन्छ। यो गुणमा आवाजको पाठ संस्करण फर्काइन्छ।

    यदि प्रतिक्रिया कोड 401 हो भने, पहुँच टोकन समाप्त भएको छ (यी टोकनहरू केवल १० मिनेटसम्म टिक्छन्)। नयाँ पहुँच टोकन अनुरोध गरिन्छ, र कल फेरि गरिन्छ।

    अन्यथा, सीरियल मोनिटरमा त्रुटि पठाइन्छ, र `text` खाली छोडिन्छ।

1. यस विधिको अन्त्यमा निम्न कोड थप्नुहोस् ताकि HTTP क्लाइन्ट बन्द गरियोस् र पाठ फर्काइयोस्:

    ```cpp
    httpClient.end();

    return text;
    ```

1. `main.cpp` मा नयाँ `convertSpeechToText` विधि `processAudio` कार्यमा कल गर्नुहोस्, त्यसपछि सीरियल मोनिटरमा आवाजलाई लग गर्नुहोस्:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. यो कोड निर्माण गर्नुहोस्, यसलाई तपाईंको Wio Terminal मा अपलोड गर्नुहोस्, र सीरियल मोनिटर मार्फत परीक्षण गर्नुहोस्। जब तपाईं सीरियल मोनिटरमा `Ready` देख्नुहुन्छ, C बटन (बायाँतर्फको, पावर स्विचको नजिक) थिच्नुहोस्, र बोल्नुहोस्। ४ सेकेन्डको अडियो क्याप्चर गरिनेछ, त्यसपछि पाठमा रूपान्तरण गरिनेछ।

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

> 💁 तपाईं यो कोड [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) फोल्डरमा पाउन सक्नुहुन्छ।

😀 तपाईंको आवाजलाई पाठमा रूपान्तरण गर्ने कार्यक्रम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादमा त्रुटिहरू वा अशुद्धताहरू हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।