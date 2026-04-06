# វាស់សំឡេងទៅអក្សរ - Wio Terminal

នៅក្នុងផ្នែកនេះនៃមេរៀន អ្នកនឹងសរសេរកូដដើម្បីបំលែងសំឡេងនៅក្នុងសំឡេងដែលបានចាប់យកទៅជាអក្សរដោយប្រើសេវាកម្មសំឡេង។

## ផ្ញើសំឡេងទៅសេវាកម្មសំឡេង

សំឡេងអាចត្រូវបានផ្ញើទៅសេវាកម្មសំឡេងដោយប្រើ REST API។ ដើម្បីប្រើសេវាកម្មសំឡេង អ្នកត្រូវតែស្នើសុំ access token ជាមុនសិន បន្ទាប់មកប្រើ token នោះដើម្បីចូលប្រើ REST API។ Access token គឺផុតកំណត់បន្ទាប់ពី ១០ នាទី ដូច្នេះកូដរបស់អ្នកគួរតែស្នើសុំពួកវាបានជារឿយៗ ដើម្បីធ្វើឱ្យពួកវានៅតែទាន់សម័យ។

### ការងារ - ទទួលបាន access token

1. បើកគម្រោង `smart-timer` ប្រសិនបើវាមិនបានបើករួចមក។

1. បន្ថែមការទំនួលខុសត្រូវបណ្ណាល័យដូចខាងក្រោមទៅឯកសារ `platformio.ini` ដើម្បីចូលប្រើ WiFi និងដោះស្រាយ JSON៖

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. បន្ថែមកូដដូចខាងលើទៅឯកសារ `config.h`៖

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    ជំនួស `<SSID>` និង `<PASSWORD>` ជាមួយតម្លៃដែលពាក់ព័ន្ធសម្រាប់ WiFi របស់អ្នក។

    ជំនួស `<API_KEY>` ជាមួយកូនសោ API សម្រាប់ធនធានសេវាកម្មសំឡេងរបស់អ្នក។ ជំនួស `<LOCATION>` ជាមួយទីតាំងដែលអ្នកបានប្រើនៅពេលបង្កើតធនធានសេវាកម្មសំឡេង។

    ជំនួស `<LANGUAGE>` ជាមួយឈ្មោះភាសាសម្រាប់ភាសាដែលអ្នកនឹងនិយាយ, ឧទាហរណ៍ `en-GB` សម្រាប់ភាសាអង់គ្លេស, ឬ `zn-HK` សម្រាប់ភាសា Cantonese។ អ្នកអាចរកមើលបញ្ជីភាសាដែលគាំទ្រនិងឈ្មោះភាសានៅក្នុងឯកសារជំនួយ [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)។

    `TOKEN_URL` គឺជាគេហទំព័រនៃអ្នកចេញអាជ្ញាបណ្ណ token ដោយគ្មានទីតាំង។ វានឹងត្រូវបានភ្ជាប់ជាមួយទីតាំងបន្ទាប់មកដើម្បីទទួលបាន URL ពេញលេញ។

1. ដូចដដែលនៅពេលចូល Custom Vision អ្នកគួរតែរៀបចំការតភ្ជាប់ HTTPS ដើម្បីភ្ជាប់ទៅសេវាកម្មចេញ token។ នៅចុងឯកសារ `config.h` បន្ថែមកូដដូចខាងក្រោម៖

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

    វាគឺជាសញ្ញាបត្រដូចដែលអ្នកបានប្រើនៅពេលតភ្ជាប់ទៅ Custom Vision។

1. បន្ថែម include សម្រាប់ឯកសារ WiFi និងឯកសារ config នៅលើឯកសារ `main.cpp`៖

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. បន្ថែមកូដភ្ជាប់ WiFi នៅក្នុង `main.cpp` ខាងលើមុខមុខងារ `setup`៖

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

1. ហៅមុខងារនេះពីមុខងារ `setup` បន្ទាប់ពីភ្ជាប់ស៊េរីបានចាប់ផ្ដើមរួច៖

    ```cpp
    connectWiFi();
    ```

1. បង្កើតឯកសារគោលថ្មីមួយក្នុងថត `src` មានឈ្មោះ `speech_to_text.h`។ ក្នុងឯកសារគោលនេះ បន្ថែមកូដដូចខាងក្រោម៖

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

    វារួមបញ្ចូលឯកសារគោលខ្លះៗសម្រាប់ការតភ្ជាប់ HTTP ការកំណត់ និងឯកសារ `mic.h` ហើយកំណត់ថ្នាក់ដែលមានឈ្មោះ `SpeechToText` មុននឹងប្រកាសអ实例មួយនៃថ្នាក់នោះដែលអាចប្រើបានបន្ទាប់។

1. បន្ថែមវាល ២ ខាងក្រោមទៅផ្នែក `private` នៃថ្នាក់នេះ៖

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` គឺជាគ្លាយ WiFi មួយដែលប្រើ HTTPS ហើយនឹងត្រូវបានប្រើដើម្បីទទួល access token។ token នេះបន្ទាប់មកនឹងត្រូវបានរក្សាទុកនៅក្នុង `_access_token`។

1. បន្ថែមមុខងារ ខាងក្រោមទៅផ្នែក `private`៖

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

    កូដនេះកសាង URL សម្រាប់ token issuer API ដោយប្រើទីតាំងធនធានសំឡេង។ បន្ទាប់មកបង្កើត `HTTPClient` ដើម្បីធ្វើសំណើបណ្ដាញ, កំណត់វាដើម្បីប្រើ client WiFi ដែលបានកំណត់ជាមួយសញ្ញាបត្រនៃ token endpoint។ វាចាត់ទុកកូនសោ API ជា header សម្រាប់ការហៅ។ បន្ទាប់មកធ្វើ POST សំណើសុំសញ្ញាប័ត្រហើយ retry ប្រសិនបើមានកំហុសណាមួយ។ ចុងក្រោយ access token ត្រូវបានត្រឡប់។

1. ទៅផ្នែក `public`, បន្ថែមមុខងារដើម្បីទទួលបាន access token។ វាត្រូវការនៅក្នុងមេរៀនបន្ទាប់ដើម្បីបំលែងអក្សរទៅសំឡេង។

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. ទៅផ្នែក `public`, បន្ថែមមុខងារ `init` ដែលកំណត់ client token៖

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    វាកំណត់សញ្ញាបត្រ នៅលើ WiFi client បន្ទាប់មកទទួលបាន access token។

1. នៅក្នុង `main.cpp`, បន្ថែមឯកសារគោលថ្មីនេះទៅក្នុងកំណត់បញ្ជា include៖

    ```cpp
    #include "speech_to_text.h"
    ```

1. ចាប់ផ្ដើមថ្នាក់ `SpeechToText` នៅចុងមុខងារ `setup`, បន្ទាប់ពីហៅ `mic.init` ប៉ុន្តែមុនពេលសរសេរ `Ready` ទៅម៉ូនីទ័រស៊េរី៖

    ```cpp
    speechToText.init();
    ```

### ការងារ - អានសំឡេងពីមេម៉ូរី flash

1. នៅក្នុងផ្នែកមុននៃមេរៀននេះ សំឡេងត្រូវបានបញ្ចូលទៅក្នុងមេម៉ូរី flash។ សំឡេងនេះត្រូវបានផ្ញើទៅ Speech Services REST API ដូច្នេះវាត្រូវបានអានពីមេម៉ូរី flash។ វាមិនអាចបញ្ជូនទៅក្នុងប៊ុហ្វរមួយដែលនៅក្នុងមេម៉ូរីបានទេ ព្រោះវាធំពេក។ ថ្នាក់ `HTTPClient` ដែលធ្វើ REST calls អាចស្ទ្រីមទិន្នន័យដោយប្រើ Arduino Stream - ថ្នាក់មួយដែលអាចផ្ទុកទិន្នន័យជាផ្នែកតូចៗ ផ្ញើផ្នែកៗនោះនៅពេលពីរៀងក្នុងសំណើ។ គ្រប់ពេលអ្នកហៅ `read` លើ stream វាត្រឡប់ផ្នែកទិន្នន័យបន្ទាប់។ អាចបង្កើត Arduino stream ដែលអាចអានពីមេម៉ូរី flash។ បង្កើតឯកសារថ្មីមួយដែលមានឈ្មោះ `flash_stream.h` ក្នុងថត `src` ហើយបន្ថែមកូដដូចខាងក្រោម៖

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

    នេះប្រកាសថ្នាក់ `FlashStream`, អាចប្រើពីថ្នាក់ Arduino `Stream`។ វាជាថ្នាក់ប抽象 - ថ្នាក់បន្តមានការនៅតែត្រូវអនុវត្តមុខងារមួយចំនួនមុនថ្នាក់អាចត្រូវបានបង្កើត និងមុខងារទាំងនេះកំណត់នៅក្នុងថ្នាក់នេះ។

    ✅ អានបន្ថែមអំពី Arduino Streams នៅក្នុង [Arduino Stream documentation](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. បន្ថែមវាលខាងក្រោមទៅផ្នែក `private`៖

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    នេះកំណត់ប៊ុហ្វរជាបណ្ដោះអាសន្នសម្រាប់ផ្ទុកទិន្នន័យអានពី flash memory ជាមួយនឹងវាលសម្រាប់រក្សាទីតាំងបច្ចុប្បន្ននៅពេលអានពីប៊ុហ្វរ ទីតាំងបច្ចុប្បន្នសម្រាប់អានពី flash memory និងឧបករណ៍ flash memory។

1. នៅក្នុងផ្នែក `private`, បន្ថែមមុខងារខាងក្រោម៖

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    កូដនេះអានពី flash memory នៅទីតាំងបច្ចុប្បន្ន ហើយផ្ទុកទិន្នន័យក្នុងប៊ុហ្វរ។ បន្ទាប់មកបន្ថែមទីតាំងទាំងនោះ ដើម្បីឲ្យហៅក្រោយអានប្លុកបន្ទាប់។ ប៊ុហ្វរត្រូវបានរៀបចំផ្អែកលើអតិបរមានៃទំហំនៃ chunk ដែល `HTTPClient` នឹងផ្ញើទៅ REST API ម្តង។

    > 💁 ការលុបចោល flash memory ត្រូវការធ្វើដោយប្រើទំហំ grain។ អានវិញវិញមិនប៉ះពាល់ចំពោះនេះទេ។

1. នៅក្នុងផ្នែក `public` នៃថ្នាក់នេះ បន្ថែមអាគុយម៉ង់ថ័រមួយ៖

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    អាគុយម៉ង់ថ័រនេះរៀបចំវាលទាំងអស់ដើម្បីចាប់ផ្ដើមអានពីដើមប្លុក flash memory ហើយផ្ទុក chunk ទីមួយទៅក្នុងប៊ុហ្វរ។

1. អនុវត្តមុខងារ `write`។ Stream នេះអានតែមិនសរសេរទេ ដូច្នេះវាអាចមិនធ្វើអ្វីឡើយ ហើយត្រឡប់ 0៖

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. អនុវត្តមុខងារ `peek`។ វាត្រឡប់ទិន្នន័យនៅទីតាំងបច្ចុប្បន្នដោយមិនផ្លាស់ទី stream។ ការហៅ `peek` ជាច្រើនដងនឹងទទួលបានទិន្នន័យដូចគ្នា បើគ្មានការអានទិន្នន័យពី stream។

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. អនុវត្តមុខងារ `available`។ វាត្រឡប់ចំនួនបៃដែលអាចអានពី stream ឬ -1 ប្រសិនបើ stream បានបញ្ចប់។ សម្រាប់ថ្នាក់នេះ អតិបរមា available នឹងមិនលើសទំហំ chunk នៃ HTTPClient ទេ។ ពេល stream នេះត្រូវបានប្រើនៅក្នុង HTTP client វាហៅមុខងារនេះដើម្បីមើលចំនួនទិន្នន័យដែលមាន ហើយស្នើសុំទិន្នន័យប៉ុន្មាននឹងផ្ញើទៅ REST API។ យើងមិនចង់ឲ្យ chunk មួយមានទំហំធំជាង chunk size នៃ HTTP client ទេ ប្រសិនបើច្រើនជាង នឹងត្រឡប់ chunk size។ ប្រសិនបើតិចជាង នោះត្រឡប់លទ្ធផលដែលមាន។ បន្ទាប់ពីទិន្នន័យទាំងអស់បានស្ទ្រីម, វាត្រឡប់ -1។

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

1. អនុវត្តមុខងារ `read` ដើម្បីត្រឡប់បៃបន្ទាប់ពីប៊ុហ្វរ បន្ថែមទីតាំង។ ប្រសិនបើទីតាំងលើសទំហំប៊ុហ្វរ វានឹងបំពេញប៊ុហ្វរជាមួយប្លុកបន្ទាប់ពី memory flash ហើយកំណត់ទីតាំងឡើងវិញ។

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

1. នៅក្នុងឯកសារ `speech_to_text.h` បន្ថែម include សម្រាប់ឯកសារថ្មីនេះ៖

    ```cpp
    #include "flash_stream.h"
    ```

### ការងារ - បំលែងសំឡេងទៅអក្សរ

1. សំឡេងអាចបំលែងទៅអក្សរដោយផ្ញើសំឡេងទៅ Speech Service តាម REST API។ REST API នេះមានសញ្ញាបត្រផ្សេងពី token issuer ដូច្នេះបន្ថែមកូដនេះទៅឯកសារ `config.h` ដើម្បីកំណត់សញ្ញាបត្រ៖

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

1. បន្ថែមអថេរមួយសម្រាប់ speech URL ដោយគ្មានទីតាំង។ វានឹងភ្ជាប់ជាមួយទីតាំងនិងភាសាបន្ទាប់មកដើម្បីទទួលបាន URL ពេញលេញ។

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. នៅក្នុងឯកសារ `speech_to_text.h` ផ្នែក `private` នៃថ្នាក់ `SpeechToText`, កំណត់វាលសម្រាប់ WiFi Client ប្រើសញ្ញាបត្រ speech៖

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. នៅក្នុងមុខងារ `init`, កំណត់សញ្ញាបត្រលើ WiFi Client នេះ៖

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. បន្ថែមកូដខាងក្រោមទៅផ្នែក `public` នៃថ្នាក់ `SpeechToText` ដើម្បីកំណត់មុខងារបំលែងសំឡេងទៅអក្សរ៖

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. បន្ថែមកូដខាងក្រោមទៅមុខងារនេះ ដើម្បីបង្កើត HTTP client ប្រើ WiFi client ដែលបានកំណត់ជាមួយសញ្ញាបត្រ speech និងប្រើ speech URL ដែលបានកំណត់ដោយទីតាំង និងភាសា៖

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. ដែល headers មួយចំនួនត្រូវបានកំណត់លើការតភ្ជាប់៖

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    វាកំណត់ headers សម្រាប់ការអោយសិទ្ធិ (authorization) ប្រើ access token, រចនាប័ទ្មសំឡេង ប្រើអត្រាទម្លាប់សំឡេង, និងកំណត់ថា client រំពឹងលទ្ធផលជា JSON។

1. បន្ទាប់ពីនេះ, បន្ថែមកូដនេះសម្រាប់ធ្វើសំណើ REST API៖

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    នេះបង្កើត `FlashStream` ហើយប្រើវាសម្រាប់ស្ទ្រីមទិន្នន័យទៅ REST API។

1. ក្រោមនេះ, បន្ថែមកូដខាងក្រោម៖

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

    កូដនេះពិនិត្យកូដទទួលការឆ្លើយតប។

    ប្រសិនបើវាជា ២០០ ដែលជាកូដជោគជ័យ, លទ្ធផលត្រូវបានយក, ដកកូដពី JSON, ហើយគុណលក្ខណៈ `DisplayText` ត្រូវបានបញ្ចូលទៅក្នុងអថេរ `text`។ នេះជាគុណលក្ខណៈដែលមានអក្សរបំលែងសំឡេងត្រូវបានត្រឡប់មក។

    ប្រសិនបើកូដឆ្លើយតបគឺ 401 នោះ access token បានផុតកំណត់ (token ទាំងនេះមានអាយុកាល ១០ នាទីប៉ុណ្ណោះ)។ ត្រូវស្នើសុំ access token ថ្មី ហើយហៅម្តងទៀត។

    ផ្សេងពីនេះ បញ្ចូនកំហុសទៅម៉ូនីទ័រស៊េរី ហើយអោយអថេរ `text` ទទេ។

1. បន្ថែមកូដខាងក្រោមចុងបញ្ចប់មុខងារនេះ ដើម្បីបិទ HTTP client និងត្រឡប់អក្សរ៖

    ```cpp
    httpClient.end();

    return text;
    ```

1. នៅក្នុង `main.cpp` ហៅមុខងារ `convertSpeechToText` ថ្មីនេះក្នុងមុខងារ `processAudio`, បន្ទាប់មកកត់ត្រាសំឡេងទៅម៉ូនីទ័រស៊េរី៖

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. បង្កើតកូដនេះ, អាប់ឡូតទៅ Wio Terminal របស់អ្នក ហើយសាកល្បងតាមម៉ូនីទ័រស៊េរី។ ពេលអ្នកឃើញ `Ready` នៅក្នុងម៉ូនីទ័រស៊េរី ចុចប៊ូតុង C (ដែលនៅផ្នែកឆ្វេង នៅជិតស៊ីធីចរន្ត), ហើយនិយាយ។ សំឡេងរយៈពេល ៤ វិនាទីនឹងត្រូវបានចាប់យក បន្ទាប់មកបំលែងទៅជាអក្សរ។

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

> 💁 អ្នកអាចរកឃើញកូដនេះនៅក្នុងថត [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal)។

😀 ឯកម្មកម្មការបំលែងសំឡេងទៅអក្សររបស់អ្នកបានជោគជ័យ!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ការព្រមាន**៖  
ឯកសារនេះបានបកប្រែដោយប្រើសេវាកម្មបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ ក្នុងការខិតខំប្រឹងប្រែងសម្រាប់ភាពត្រឹមត្រូវ សូមចំណាំថាការបកប្រែដោយស្វ័យប្រវត្តិនេះអាចមានកំហុស ឬភាពមិនត្រឹមត្រូវខ្លះៗ។ ឯកសារដើមក្នុងភាសាទីតាំងរបស់វាគួរត្រូវបានគេដាក់ចិត្តថាជាអ្នកផ្ដល់ព័ត៌មានដែលមានអំណាច។ សម្រាប់ព័ត៌មានសំខាន់ៗ សូមប្រើការបកប្រែដោយអ្នកជំនាញមនុស្សដែលមានជំនាញ។ យើងមិនមានភារកិច្ចខណៈពេលកើតមានការយល់ច្រឡំ ឬការបកប្រែខុសប្លែកណាមួយ ដែលបណ្តាលមកពីការប្រើប្រាស់ការបកប្រែនេះទេ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->