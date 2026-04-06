# एक छवि को वर्गीकृत करें - Wio Terminal

इस पाठ के इस भाग में, आप कैमरे द्वारा कैप्चर की गई छवि को Custom Vision सेवा पर भेजेंगे ताकि इसे वर्गीकृत किया जा सके।

## एक छवि को वर्गीकृत करें

Custom Vision सेवा में एक REST API है जिसे आप Wio Terminal से छवियों को वर्गीकृत करने के लिए कॉल कर सकते हैं। यह REST API एक HTTPS कनेक्शन के माध्यम से एक्सेस की जाती है - जो एक सुरक्षित HTTP कनेक्शन है।

जब HTTPS एंडपॉइंट्स के साथ इंटरैक्ट करते हैं, तो क्लाइंट कोड को उस सर्वर से सार्वजनिक कुंजी प्रमाणपत्र (public key certificate) का अनुरोध करना होता है, जिसे एक्सेस किया जा रहा है, और इसका उपयोग ट्रैफिक को एन्क्रिप्ट करने के लिए करना होता है। आपका वेब ब्राउज़र यह स्वचालित रूप से करता है, लेकिन माइक्रोकंट्रोलर्स ऐसा नहीं करते। आपको यह प्रमाणपत्र मैन्युअल रूप से प्राप्त करना होगा और इसे REST API के साथ एक सुरक्षित कनेक्शन बनाने के लिए उपयोग करना होगा। ये प्रमाणपत्र बदलते नहीं हैं, इसलिए एक बार जब आपके पास प्रमाणपत्र हो, तो इसे आपके एप्लिकेशन में हार्ड कोड किया जा सकता है।

ये प्रमाणपत्र सार्वजनिक कुंजियों को रखते हैं और इन्हें सुरक्षित रखने की आवश्यकता नहीं होती। आप इन्हें अपने सोर्स कोड में उपयोग कर सकते हैं और GitHub जैसे सार्वजनिक स्थानों पर साझा कर सकते हैं।

### कार्य - एक SSL क्लाइंट सेट करें

1. यदि `fruit-quality-detector` ऐप प्रोजेक्ट पहले से खुला नहीं है, तो इसे खोलें।

1. `config.h` हेडर फाइल खोलें, और निम्नलिखित जोड़ें:

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

    यह *Microsoft Azure DigiCert Global Root G2 प्रमाणपत्र* है - यह उन प्रमाणपत्रों में से एक है जो कई Azure सेवाओं द्वारा वैश्विक स्तर पर उपयोग किए जाते हैं।

    > 💁 यह देखने के लिए कि यह उपयोग करने के लिए सही प्रमाणपत्र है, macOS या Linux पर निम्नलिखित कमांड चलाएं। यदि आप Windows का उपयोग कर रहे हैं, तो आप इस कमांड को [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn) का उपयोग करके चला सकते हैं:
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > आउटपुट DigiCert Global Root G2 प्रमाणपत्र को सूचीबद्ध करेगा।

1. `main.cpp` खोलें और निम्नलिखित include निर्देश जोड़ें:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. include निर्देशों के नीचे, `WifiClientSecure` का एक उदाहरण घोषित करें:

    ```cpp
    WiFiClientSecure client;
    ```

    यह क्लास HTTPS के माध्यम से वेब एंडपॉइंट्स के साथ संवाद करने के लिए कोड रखती है।

1. `connectWiFi` मेथड में, WiFiClientSecure को DigiCert Global Root G2 प्रमाणपत्र का उपयोग करने के लिए सेट करें:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### कार्य - एक छवि को वर्गीकृत करें

1. `platformio.ini` फाइल में `lib_deps` सूची में निम्नलिखित को एक अतिरिक्त लाइन के रूप में जोड़ें:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    यह [ArduinoJson](https://arduinojson.org), एक Arduino JSON लाइब्रेरी को आयात करता है, और इसे REST API से JSON प्रतिक्रिया को डिकोड करने के लिए उपयोग किया जाएगा।

1. `config.h` में, Custom Vision सेवा से prediction URL और Key के लिए constants जोड़ें:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    `<PREDICTION_URL>` को Custom Vision से प्राप्त prediction URL से बदलें। `<PREDICTION_KEY>` को prediction key से बदलें।

1. `main.cpp` में, ArduinoJson लाइब्रेरी के लिए एक include निर्देश जोड़ें:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `main.cpp` में, `buttonPressed` फंक्शन के ऊपर निम्नलिखित फंक्शन जोड़ें:

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

    यह कोड `HTTPClient` को डिक्लेयर करके शुरू होता है - एक क्लास जिसमें REST APIs के साथ इंटरैक्ट करने के लिए मेथड्स होते हैं। फिर यह क्लाइंट को Azure सार्वजनिक कुंजी के साथ सेट किए गए `WiFiClientSecure` उदाहरण का उपयोग करके prediction URL से कनेक्ट करता है।

    कनेक्ट होने के बाद, यह हेडर्स भेजता है - REST API के खिलाफ किए जाने वाले आगामी अनुरोध के बारे में जानकारी। `Content-Type` हेडर इंगित करता है कि API कॉल कच्चे बाइनरी डेटा भेजेगा, और `Prediction-Key` हेडर Custom Vision prediction key को पास करता है।

    इसके बाद, HTTP क्लाइंट पर एक POST अनुरोध किया जाता है, जिसमें एक बाइट ऐरे अपलोड किया जाता है। इसमें कैमरे से कैप्चर की गई JPEG छवि होगी जब इस फंक्शन को कॉल किया जाएगा।

    > 💁 POST अनुरोध डेटा भेजने और प्रतिक्रिया प्राप्त करने के लिए होते हैं। अन्य अनुरोध प्रकार जैसे GET अनुरोध डेटा प्राप्त करने के लिए उपयोग किए जाते हैं। आपका वेब ब्राउज़र वेब पेज लोड करने के लिए GET अनुरोधों का उपयोग करता है।

    POST अनुरोध एक प्रतिक्रिया स्थिति कोड लौटाता है। ये पूर्व-परिभाषित मान होते हैं, जिसमें 200 का अर्थ है **OK** - POST अनुरोध सफल रहा।

    > 💁 आप सभी प्रतिक्रिया स्थिति कोड [विकिपीडिया पर HTTP स्थिति कोड की सूची](https://wikipedia.org/wiki/List_of_HTTP_status_codes) पेज पर देख सकते हैं।

    यदि 200 लौटाया जाता है, तो परिणाम HTTP क्लाइंट से पढ़ा जाता है। यह REST API से एक JSON दस्तावेज़ के रूप में भविष्यवाणी के परिणामों के साथ एक टेक्स्ट प्रतिक्रिया है। JSON निम्नलिखित प्रारूप में है:

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

    यहां महत्वपूर्ण हिस्सा `predictions` ऐरे है। इसमें भविष्यवाणियां होती हैं, प्रत्येक टैग के लिए एक प्रविष्टि होती है जिसमें टैग का नाम और संभावना होती है। लौटाई गई संभावनाएं 0-1 के फ्लोटिंग पॉइंट नंबर होती हैं, जहां 0 का अर्थ है 0% संभावना और 1 का अर्थ है 100% संभावना।

    > 💁 छवि वर्गीकरणकर्ता उन सभी टैग्स के लिए प्रतिशत लौटाएंगे जिनका उपयोग किया गया है। प्रत्येक टैग में यह संभावना होगी कि छवि उस टैग से मेल खाती है।

    इस JSON को डिकोड किया जाता है, और प्रत्येक टैग के लिए संभावनाओं को सीरियल मॉनिटर पर भेजा जाता है।

1. `buttonPressed` फंक्शन में, या तो SD कार्ड पर सेव करने वाले कोड को `classifyImage` कॉल से बदलें, या इसे छवि लिखने के बाद जोड़ें, लेकिन **बफर को हटाने से पहले**:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 यदि आप SD कार्ड पर सेव करने वाले कोड को बदलते हैं, तो आप अपने कोड को साफ कर सकते हैं और `setupSDCard` और `saveToSDCard` फंक्शन्स को हटा सकते हैं।

1. अपना कोड अपलोड करें और चलाएं। कैमरे को किसी फल की ओर इंगित करें और C बटन दबाएं। आप सीरियल मॉनिटर में आउटपुट देखेंगे:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    आप वह छवि देख पाएंगे जो ली गई थी, और ये मान Custom Vision के **Predictions** टैब में देख पाएंगे।

    ![Custom Vision में एक केला, 56.8% पर पका हुआ और 43.1% पर कच्चा भविष्यवाणी की गई](../../../../../translated_images/hi/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 आप इस कोड को [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal) फोल्डर में पा सकते हैं।

😀 आपका फल गुणवत्ता वर्गीकरण प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता के लिए प्रयासरत हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को आधिकारिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।