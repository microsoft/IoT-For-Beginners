# ចាត់ថ្នាក់រូបភាព - Wio Terminal

នៅក្នុងផ្នែកនេះនៃមេរៀន អ្នកនឹងផ្ញើរូបភាពដែលបានថតដោយកាមេរ៉ាទៅកាន់សេវាកម្ម Custom Vision ដើម្បីចាត់ថ្នាក់វា។

## ចាត់ថ្នាក់រូបភាព

សេវាកម្ម Custom Vision មាន REST API ដែលអ្នកអាចហៅពី Wio Terminal ដើម្បីចាត់ថ្នាក់រូបភាពបាន។ REST API នេះអាចចូលដំណើរការបានតាមការតភ្ជាប់ HTTPS - ការតភ្ជាប់ HTTP ដែលមានសុវត្ថិភាព។

នៅពេលធ្វើប្រតិបត្តិការជាមួយចំណុចបញ្ចប់ HTTPS កូដអ្នកប្រើត្រូវតែស្នើសុំវិញ្ញាបនបត្រការបួនកូនសាធារណៈពីម៉ាស៊ីនមេដែលត្រូវបានចូលដំណើរការ ហើយប្រើវា ដើម្បីស៊ែរការចរាចរណ៍ដែលវាផ្ញើ។ អ្នកប្រេហ្ស័ររបស់អ្នកធ្វើរឿងនេះដោយស្វ័យប្រវត្តិ ប៉ុន្តែមីក្រូកុងត្រូឡឺមិនធ្វើដូចនេះទេ។ អ្នកត្រូវតែស្នើសុំវិញ្ញាបនបត្រនេះដោយដៃ ហើយប្រើវាដើម្បីបង្កើតការតភ្ជាប់ដែលមានសុវត្ថិភាពទៅកាន់ REST API។ វីញ្ញាបនបត្រទាំងនេះមិនប្ដូរទេ ដូចនេះពេលអ្នកបានវិញ្ញាបនបត្រមួយហើយ វាអាចត្រូវបានកូដរឹតបន្តិចនៅក្នុងកម្មវិធីរបស់អ្នក។

វិញ្ញាបនបត្រទាំងនេះរួមមានកូនសោសាធារណៈ ហើយមិនចាំបាច់ត្រូវរក្សាទុកយ៉ាងរឹងមាំទេ។ អ្នកអាចប្រើពួកវានៅក្នុងកូដប្រភពរបស់អ្នក និងចែករំលែកសាធារណៈនៅកន្លែងដូចជា GitHub។

### ភារកិច្ច - រៀបចំម៉ាស៊ីនអតិថិជន SSL

1. បើកគម្រោងកម្មវិធី `fruit-quality-detector` ប្រសិនបើវាមិនបានបើករួចទេ។

1. បើកឯកសារ header `config.h` ហើយបន្ថែមសម្គាល់ដូចខាងក្រោម៖

    ```cpp
    const char *CERTIFICATE =
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

    វា​*Microsoft Azure DigiCert Global Root G2 certificate* - វាជាវិញ្ញាបនបត្រមួយក្នុងចំណោមវិញ្ញាបនបត្រដែលបានប្រើដោយសេវាកម្ម Azure ជាច្រើនជាសកល។

    > 💁 ដើម្បីមើលថាវា​ជា​វិញ្ញាបនបត្រដែលត្រូវប្រើ ចូររត់ពាក្យបញ្ជាខាងក្រោមលើ macOS ឬ Linux។ ប្រសិនបើអ្នកប្រើ Windows អ្នកអាចដំណើរការប្រតិបត្តិនេះតាម [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > លទ្ធផលនឹងបង្ហាញចំណងជើងវិញ្ញាបនបត្រ DigiCert Global Root G2។

1. បើក `main.cpp` ហើយបន្ថែមបញ្ជាផ្ដល់ការរួមបញ្ចូលខាងក្រោម៖

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. នៅខាងក្រោមបញ្ជាផ្ដល់ការរួមបញ្ចូល បញ្ចាក់ឧបករណ៍ `WifiClientSecure` មួយ៖

    ```cpp
    WiFiClientSecure client;
    ```

    ថ្នាក់នេះមានកូដសម្រាប់ធ្វើការទំនាក់ទំនងជាមួយចំណុចបញ្ចប់វែបតាម HTTPS។

1. នៅក្នុងវិធី `connectWiFi` កំណត់ WiFiClientSecure ដើម្បីប្រើវិញ្ញាបនបត្រ DigiCert Global Root G2៖

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### ភារកិច្ច - ចាត់ថ្នាក់រូបភាព

1. បន្ថែមបន្ទាត់នេះជាបន្ទាត់បន្ថែមទៅបញ្ជី `lib_deps` នៅក្នុងឯកសារ `platformio.ini`៖

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    វានាំចូល [ArduinoJson](https://arduinojson.org), បណ្ណាល័យ JSON សម្រាប់ Arduino ហើយនឹងត្រូវប្រើសម្រាប់បកប្រែចម្លើយ JSON ពី REST API។

1. នៅក្នុង `config.h` បន្ថែមថេរប្រភេទសម្រាប់ URL ការព្យាករណ៍ និង Key ពីសេវាកម្ម Custom Vision៖

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    ជំនួស `<PREDICTION_URL>` ជាមួយ URL ការព្យាករណ៍ពី Custom Vision។ ជំនួស `<PREDICTION_KEY>` ជាមួយ key ការព្យាករណ៍។

1. នៅក្នុង `main.cpp` បន្ថែមបញ្ជាផ្ដល់ការរួមបញ្ចូលសម្រាប់បណ្ណាល័យ ArduinoJson៖

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. បន្ថែមមុខងារខាងក្រោមទៅ `main.cpp` ខាងលើមុខងារ `buttonPressed`។

    ```cpp
    void classifyImage(byte *buffer, uint32_t length)
    {
        HTTPClient httpClient;
        httpClient.begin(client, PREDICTION_URL);
        httpClient.addHeader("Content-Type", "application/octet-stream");
        httpClient.addHeader("Prediction-Key", PREDICTION_KEY);
    
        int httpResponseCode = httpClient.POST(buffer, length);
    
        if (httpResponseCode == 200)
        {
            String result = httpClient.getString();
    
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, result.c_str());
    
            JsonObject obj = doc.as<JsonObject>();
            JsonArray predictions = obj["predictions"].as<JsonArray>();
    
            for(JsonVariant prediction : predictions) 
            {
                String tag = prediction["tagName"].as<String>();
                float probability = prediction["probability"].as<float>();
    
                char buff[32];
                sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
                Serial.println(buff);
            }
        }
    
        httpClient.end();
    }
    ```

    កូដនេះចាប់ផ្តើមដោយសេចក្តីប្រកាស `HTTPClient` - ថ្នាក់ដែលមានវិធីសាស្ត្រសម្រាប់ធ្វើប្រតិបត្តិការជាមួយ REST API។ បន្ទាប់មកវាភ្ជាប់ទៅកាន់ URL ការព្យាករណ៍ដោយប្រកបដោយ WiFiClientSecure ដែលបានរៀបចំជាមួយកូនសោសាធារណៈ Azure។

    បន្ទាប់ពីភ្ជាប់ វានឹងផ្ញើក្បាល - ព័ត៌មានអំពីសំណើដែលនឹងធ្វើ ទៅប្រឆាំង REST API។ ក្បាល `Content-Type` បង្ហាញថាការហៅ API នឹងផ្ញើទិន្នន័យរំពឹងទុកជាកំប៉ុងទិន្នន័យដើម, ក្បាល `Prediction-Key` ផ្ញើ key ការព្យាករណ៍ Custom Vision។

    បន្ទាប់មកសំណើ POST ត្រូវបានធ្វើទៅ HTTP client ដើម្បីផ្ទុកអារេ byte។ នេះនឹងមានរូបភាព JPEG ដែលបានថតពីកាមេរ៉ាពេលមុខងារនេះត្រូវបានហៅ។

    > 💁 សំណើ POST មានគោលបំណងផ្ញើទិន្នន័យ និងទទួលបានចម្លើយ។ មានប្រភេទសំណើផ្សេងទៀតដូចជា GET ដែលយកទិន្នន័យ។ សំណើ GET ត្រូវបានប្រើដោយកម្មវិធីរុករករបស់អ្នកដើម្បីផ្ទុកទំព័រវែប។

    សំណើ POST នាំមកនូវកូដស្ថានភាពចម្លើយ។ វាត្រូវបានកំណត់យ៉ាងច្បាស់ដោយមានលេខ 200 មានន័យថា **OK** - សំណើ POST បានជោគជ័យ។

    > 💁 អ្នកអាចមើលកូដស្ថានភាពចម្លើយទាំងអស់នៅលើ [List of HTTP status codes page on Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    ប្រសិនបើពិភាក្សា 200 វានឹងអានលទ្ធផលពី HTTP client។ នេះជាចម្លើយអក្សរមកពី REST API ដោយមានលទ្ធផលនៃការព្យាករណ៍ជាឯកសារ JSON។ JSON មានរូបមន្តដូចខាងក្រោម៖

    ```jSON
    {
        "id":"45d614d3-7d6f-47e9-8fa2-04f237366a16",
        "project":"135607e5-efac-4855-8afb-c93af3380531",
        "iteration":"04f1c1fa-11ec-4e59-bb23-4c7aca353665",
        "created":"2021-06-10T17:58:58.959Z",
        "predictions":[
            {
                "probability":0.5582016,
                "tagId":"05a432ea-9718-4098-b14f-5f0688149d64",
                "tagName":"ripe"
            },
            {
                "probability":0.44179836,
                "tagId":"bb091037-16e5-418e-a9ea-31c6a2920f17",
                "tagName":"unripe"
            }
        ]
    }
    ```

    ផ្នែកសំខាន់នៅទីនេះគឺអារេ `predictions`។ វាមានការព្យាករណ៍ជាមួយចំណុចនីមួយៗសម្រាប់ក្តារទីមួយ ដែលមានឈ្មោះស្លាក និងប្រហែល។ ប្រហែលដែលបានបញ្ចូនត្រូវជាចំនួនទសភាគចាប់ពី 0-1 ដែល 0 មានន័យថាអាចជាប់ស្លាកបាន 0% ហើយ 1 មានន័យថាអាចជាប់ស្លាកបាន 100%។

    > 💁 កម្មវិធីចាត់ថ្នាក់រូបភាពនឹងបង្ហាញភាគរយសម្រាប់ស្លាកទាំងអស់ដែលបានប្រើ។ ស្លាកនីមួយៗនឹងមានប្រហែលថារូបភាពនោះផ្គូរផ្គងនឹងស្លាកនោះយ៉ាងណា។

    JSON នេះត្រូវបានបកប្រែ ហើយប្រហែលសម្រាប់ស្លាកនីមួយៗត្រូវបានផ្ញើទៅម៉ូនីទ័រស៊េរី។

1. នៅក្នុងមុខងារ `buttonPressed` ចូរជំនួសកូដដែលសន្សំព័ត៌មានទៅកាត SD ជាមួយការហៅមុខងារ `classifyImage` ឬបន្ថែមវាបន្ទាប់ពីរូបភាពត្រូវបានរក្សាទុក តែមុនពេលបង្ហាញបន្ទុកត្រូវបានលុប៖

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 ប្រសិនបើអ្នកជំនួសកូដដែលសន្សំព័ត៌មានទៅកាត SD អ្នកអាចសំអាតកូដរបស់អ្នកដកមុខងារ `setupSDCard` និង `saveToSDCard` ចេញ។

1. ផ្ទុកឡើងហើយរត់កូដរបស់អ្នក។ ធ្វើការបង្ហាញកាមេរ៉ាទៅផ្លែឈើមួយហើយចុចប៊ូតុង C។ អ្នកនឹងឃើញលទ្ធផលនៅម៉ូនីទ័រស៊េរី៖

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    អ្នកនឹងអាចមើលឃើញរូបភាពដែលបានថត និងតម្លៃទាំងនេះនៅផ្ទាំង **Predictions** នៅក្នុង Custom Vision។

    ![A banana in custom vision predicted ripe at 56.8% and unripe at 43.1%](../../../../../translated_images/km/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 អ្នកអាចស្វែងរកកូដនេះនៅក្នុងថត [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal)។

😀 កម្មវិធីចាត់ថ្នាក់គុណភាពផ្លែឈើរបស់អ្នកបានជោគជ័យ!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ការបដិសេធ**៖  
ឯកសារនេះត្រូវបានបកប្រែដោយប្រើសេវាកម្មបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ ខណៈពេលដែលយើងខិតខំប្រឹងប្រែងឱ្យមានភាពត្រឹមត្រូវ សូមយល់ថាការបកប្រែដោយស្វ័យប្រវត្តិអាចមានកំហុស ឬភាពមិនត្រឹមត្រូវ។ ឯកសារដើមក្នុងភាសាម៉ាក់មួយគួរត្រូវបានយកទៅពិចារណាថាជាតំណរភាពបញ្ជាក់។ សម្រាប់ព័ត៌មានសំខាន់ៗ ការបកប្រែដោយមនុស្សអ្នកជំនាញត្រូវបានណែនាំ។ យើងមិនទទួលខុសត្រូវចំពោះការយល់ច្រឡំ ឬការបកប្រែខុសទេ ដែលមកពីការប្រើប្រាស់ការបកប្រែនេះឡើយ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->