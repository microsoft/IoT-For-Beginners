# क्यामेराबाट लिइएको तस्बिर वर्गीकरण गर्नुहोस् - Wio Terminal

यस पाठको यस भागमा, तपाईं क्यामेराले लिएको तस्बिरलाई Custom Vision सेवामा पठाएर वर्गीकरण गर्नुहुनेछ।

## तस्बिर वर्गीकरण गर्नुहोस्

Custom Vision सेवामा REST API छ, जसलाई Wio Terminal बाट तस्बिर वर्गीकरण गर्न कल गर्न सकिन्छ। यो REST API HTTPS कनेक्शनमार्फत पहुँच गरिन्छ - सुरक्षित HTTP कनेक्शन।

HTTPS अन्तर्क्रियामा, क्लाइन्ट कोडले पहुँच गरिरहेको सर्भरबाट सार्वजनिक किज सर्टिफिकेट अनुरोध गर्नुपर्छ, र त्यसलाई प्रयोग गरेर पठाइएको ट्राफिकलाई इन्क्रिप्ट गर्नुपर्छ। तपाईंको वेब ब्राउजरले यो स्वचालित रूपमा गर्छ, तर माइक्रोकन्ट्रोलरले गर्दैन। तपाईंले यो सर्टिफिकेट म्यानुअली अनुरोध गर्नुपर्छ र यसलाई REST API सँग सुरक्षित कनेक्शन बनाउन प्रयोग गर्नुपर्छ। यी सर्टिफिकेटहरू परिवर्तन हुँदैनन्, त्यसैले एकपटक तपाईंले सर्टिफिकेट प्राप्त गरेपछि, यसलाई तपाईंको एप्लिकेसनमा हार्ड कोड गर्न सकिन्छ।

यी सर्टिफिकेटहरूमा सार्वजनिक किजहरू हुन्छन्, र सुरक्षित राख्न आवश्यक छैन। तपाईंले यसलाई आफ्नो सोर्स कोडमा प्रयोग गर्न सक्नुहुन्छ र GitHub जस्ता सार्वजनिक स्थानहरूमा साझा गर्न सक्नुहुन्छ।

### कार्य - SSL क्लाइन्ट सेटअप गर्नुहोस्

1. यदि `fruit-quality-detector` एप प्रोजेक्ट खुला छैन भने यसलाई खोल्नुहोस्।

1. `config.h` हेडर फाइल खोल्नुहोस्, र निम्न थप्नुहोस्:

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

    यो *Microsoft Azure DigiCert Global Root G2 certificate* हो - यो धेरै Azure सेवाहरूले विश्वव्यापी रूपमा प्रयोग गर्ने सर्टिफिकेट हो।

    > 💁 यो सर्टिफिकेट प्रयोग गर्नुपर्ने हो भनेर हेर्नका लागि, macOS वा Linux मा निम्न कमाण्ड चलाउनुहोस्। यदि तपाईं Windows प्रयोग गर्दै हुनुहुन्छ भने, तपाईं यो कमाण्ड [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn) प्रयोग गरेर चलाउन सक्नुहुन्छ:
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > आउटपुटले DigiCert Global Root G2 सर्टिफिकेट सूचीबद्ध गर्नेछ।

1. `main.cpp` खोल्नुहोस् र निम्न इनक्लुड डाइरेक्टिभ थप्नुहोस्:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. इनक्लुड डाइरेक्टिभहरू तल, `WifiClientSecure` को एक इन्स्ट्यान्स घोषणा गर्नुहोस्:

    ```cpp
    WiFiClientSecure client;
    ```

    यो क्लासमा HTTPS मार्फत वेब अन्तर्क्रियासँग संवाद गर्न कोड हुन्छ।

1. `connectWiFi` मेथडमा, WiFiClientSecure लाई DigiCert Global Root G2 सर्टिफिकेट प्रयोग गर्न सेट गर्नुहोस्:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### कार्य - तस्बिर वर्गीकरण गर्नुहोस्

1. `platformio.ini` फाइलको `lib_deps` सूचीमा निम्न थप्नुहोस्:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    यसले [ArduinoJson](https://arduinojson.org), एक Arduino JSON लाइब्रेरी आयात गर्छ, र REST API बाट JSON प्रतिक्रिया डिकोड गर्न प्रयोग गरिनेछ।

1. `config.h` मा, Custom Vision सेवाबाट प्रिडिक्शन URL र Key का लागि कन्स्ट्यान्टहरू थप्नुहोस्:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    `<PREDICTION_URL>` लाई Custom Vision बाट प्रिडिक्शन URL ले प्रतिस्थापन गर्नुहोस्। `<PREDICTION_KEY>` लाई प्रिडिक्शन कीले प्रतिस्थापन गर्नुहोस्।

1. `main.cpp` मा ArduinoJson लाइब्रेरीको लागि इनक्लुड डाइरेक्टिभ थप्नुहोस्:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `main.cpp` मा, `buttonPressed` फंक्शनभन्दा माथि निम्न फंक्शन थप्नुहोस्:

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

    यो कोडले `HTTPClient` घोषणा गरेर सुरु गर्छ - यो क्लासमा REST API सँग अन्तर्क्रिया गर्न मेथडहरू हुन्छन्। त्यसपछि क्लाइन्टलाई Azure सार्वजनिक किजको साथ सेटअप गरिएको `WiFiClientSecure` इन्स्ट्यान्स प्रयोग गरेर प्रिडिक्शन URL सँग जडान गर्छ।

    जडान भएपछि, यो हेडरहरू पठाउँछ - REST API विरुद्ध गरिने अनुरोधको बारेमा जानकारी। `Content-Type` हेडरले API कलले कच्चा बाइनरी डाटा पठाउने संकेत गर्छ, `Prediction-Key` हेडरले Custom Vision प्रिडिक्शन की पास गर्छ।

    त्यसपछि HTTP क्लाइन्टमा POST अनुरोध गरिन्छ, जसले बाइट एरे अपलोड गर्छ। यो क्यामेराबाट लिइएको JPEG तस्बिर समावेश गर्नेछ जब यो फंक्शन कल गरिन्छ।

    > 💁 POST अनुरोध डाटा पठाउन र प्रतिक्रिया प्राप्त गर्नका लागि हो। अन्य अनुरोध प्रकारहरू जस्तै GET अनुरोधहरू डाटा प्राप्त गर्नका लागि प्रयोग गरिन्छ। GET अनुरोधहरू तपाईंको वेब ब्राउजरले वेब पेज लोड गर्न प्रयोग गर्छ।

    POST अनुरोधले प्रतिक्रिया स्टाटस कोड फर्काउँछ। यी राम्रोसँग परिभाषित मानहरू हुन्, जहाँ 200 को अर्थ **OK** हो - POST अनुरोध सफल भयो।

    > 💁 तपाईं सबै प्रतिक्रिया स्टाटस कोडहरू [List of HTTP status codes page on Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes) मा हेर्न सक्नुहुन्छ।

    यदि 200 फर्काइन्छ भने, परिणाम HTTP क्लाइन्टबाट पढिन्छ। यो REST API बाट JSON डकुमेन्टको रूपमा प्रिडिक्शनको साथ टेक्स्ट प्रतिक्रिया हो। JSON निम्न स्वरूपमा हुन्छ:

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

    यहाँ महत्त्वपूर्ण भाग `predictions` एरे हो। यसमा प्रिडिक्शनहरू समावेश छन्, प्रत्येक ट्यागको लागि एक प्रविष्टि ट्याग नाम र सम्भाव्यता सहित। फर्काइएका सम्भाव्यता 0-1 बीचका फ्लोटिङ पोइन्ट नम्बरहरू हुन्, जहाँ 0 को अर्थ 0% सम्भाव्यता र 1 को अर्थ 100% सम्भाव्यता हो।

    > 💁 इमेज क्लासिफायरहरूले प्रयोग गरिएका सबै ट्यागहरूको प्रतिशत फर्काउँछन्। प्रत्येक ट्यागसँग तस्बिरले उक्त ट्यागसँग मेल खाने सम्भाव्यता हुन्छ।

    यो JSON डिकोड गरिन्छ, र प्रत्येक ट्यागको सम्भाव्यता सिरियल मोनिटरमा पठाइन्छ।

1. `buttonPressed` फंक्शनमा, SD कार्डमा बचत गर्ने कोडलाई `classifyImage` कलले प्रतिस्थापन गर्नुहोस्, वा तस्बिर लेखिएको भए पनि **बफर मेटाउनु अघि** यसलाई थप्नुहोस्:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 यदि तपाईं SD कार्डमा बचत गर्ने कोड प्रतिस्थापन गर्नुहुन्छ भने, तपाईं आफ्नो कोड सफा गर्न `setupSDCard` र `saveToSDCard` फंक्शनहरू हटाउन सक्नुहुन्छ।

1. आफ्नो कोड अपलोड र चलाउनुहोस्। क्यामेरालाई केही फलफूलतर्फ सोझ्याउनुहोस् र C बटन थिच्नुहोस्। तपाईं सिरियल मोनिटरमा आउटपुट देख्नुहुनेछ:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    तपाईंले लिएको तस्बिर र यी मानहरू Custom Vision को **Predictions** ट्याबमा देख्न सक्नुहुन्छ।

    ![Custom Vision मा एउटा केरा, 56.8% मा पाको र 43.1% मा अपाको भनेर प्रिडिक्ट गरिएको](../../../../../translated_images/ne/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 तपाईं यो कोड [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal) फोल्डरमा पाउन सक्नुहुन्छ।

😀 तपाईंको फलफूल गुणस्तर वर्गीकरण कार्यक्रम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादहरूमा त्रुटि वा अशुद्धता हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।