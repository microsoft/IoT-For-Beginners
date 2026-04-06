# प्रतिमा वर्गीकृत करा - Wio Terminal

या धड्याच्या भागात, तुम्ही कॅमेऱ्याने घेतलेली प्रतिमा Custom Vision सेवेकडे पाठवून ती वर्गीकृत कराल.

## प्रतिमा वर्गीकृत करा

Custom Vision सेवेमध्ये REST API आहे ज्याचा उपयोग Wio Terminal वरून प्रतिमा वर्गीकृत करण्यासाठी करता येतो. हा REST API HTTPS कनेक्शनद्वारे प्रवेश केला जातो - एक सुरक्षित HTTP कनेक्शन.

HTTPS endpoints शी संवाद साधताना, क्लायंट कोडला प्रवेश केलेल्या सर्व्हरकडून सार्वजनिक की प्रमाणपत्राची विनंती करावी लागते आणि त्याचा उपयोग करून पाठवलेला डेटा एन्क्रिप्ट करावा लागतो. तुमचा वेब ब्राउझर हे स्वयंचलितपणे करतो, परंतु मायक्रोकंट्रोलर्स तसे करत नाहीत. तुम्हाला हे प्रमाणपत्र हाताने मिळवावे लागेल आणि REST API शी सुरक्षित कनेक्शन तयार करण्यासाठी त्याचा उपयोग करावा लागेल. ही प्रमाणपत्रे बदलत नाहीत, त्यामुळे एकदा प्रमाणपत्र मिळाल्यावर ते तुमच्या अॅप्लिकेशनमध्ये हार्ड कोड केले जाऊ शकते.

ही प्रमाणपत्रे सार्वजनिक की समाविष्ट करतात आणि सुरक्षित ठेवण्याची गरज नाही. तुम्ही ती तुमच्या सोर्स कोडमध्ये वापरू शकता आणि GitHub सारख्या सार्वजनिक ठिकाणी शेअर करू शकता.

### कार्य - SSL क्लायंट सेट करा

1. `fruit-quality-detector` अॅप प्रकल्प उघडा, जर तो आधीच उघडलेला नसेल.

1. `config.h` हेडर फाइल उघडा आणि खालील कोड जोडा:

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

    हे *Microsoft Azure DigiCert Global Root G2 प्रमाणपत्र* आहे - हे अनेक Azure सेवांद्वारे जागतिक स्तरावर वापरले जाणारे प्रमाणपत्र आहे.

    > 💁 हे प्रमाणपत्र वापरण्यासाठी आहे हे पाहण्यासाठी, macOS किंवा Linux वर खालील कमांड चालवा. जर तुम्ही Windows वापरत असाल, तर तुम्ही [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn) वापरून ही कमांड चालवू शकता:
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > आउटपुटमध्ये DigiCert Global Root G2 प्रमाणपत्र सूचीबद्ध असेल.

1. `main.cpp` उघडा आणि खालील include directive जोडा:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. include directives च्या खाली, `WifiClientSecure` चे instance घोषित करा:

    ```cpp
    WiFiClientSecure client;
    ```

    ही class HTTPS द्वारे वेब endpoints शी संवाद साधण्यासाठी कोड समाविष्ट करते.

1. `connectWiFi` पद्धतीमध्ये, WiFiClientSecure ला DigiCert Global Root G2 प्रमाणपत्र वापरण्यास सेट करा:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### कार्य - प्रतिमा वर्गीकृत करा

1. `platformio.ini` फाइलमधील `lib_deps` यादीमध्ये खालील अतिरिक्त ओळ जोडा:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    हे [ArduinoJson](https://arduinojson.org), एक Arduino JSON लायब्ररी आयात करते, आणि REST API कडून JSON प्रतिसाद डिकोड करण्यासाठी वापरले जाईल.

1. `config.h` मध्ये, Custom Vision सेवेमधून prediction URL आणि Key साठी constants जोडा:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    `<PREDICTION_URL>` ला Custom Vision मधील prediction URL ने बदला. `<PREDICTION_KEY>` ला prediction key ने बदला.

1. `main.cpp` मध्ये, ArduinoJson लायब्ररीसाठी include directive जोडा:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `main.cpp` मध्ये, `buttonPressed` फंक्शनच्या वर खालील फंक्शन जोडा:

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

    हा कोड `HTTPClient` घोषित करून सुरू होतो - एक class ज्यामध्ये REST APIs शी संवाद साधण्यासाठी पद्धती असतात. त्यानंतर क्लायंटला Azure सार्वजनिक कीसह सेट केलेल्या `WiFiClientSecure` instance वापरून prediction URL शी कनेक्ट केले जाते.

    एकदा कनेक्ट झाल्यावर, headers पाठवले जातात - REST API विरुद्ध केलेल्या विनंतीबद्दल माहिती. `Content-Type` header सूचित करते की API कॉल कच्चा बायनरी डेटा पाठवेल, `Prediction-Key` header Custom Vision prediction key पास करतो.

    नंतर HTTP क्लायंटवर POST विनंती केली जाते, ज्यामध्ये बाइट array अपलोड केले जाते. हे बाइट array कॅमेऱ्याने घेतलेली JPEG प्रतिमा समाविष्ट करेल.

    > 💁 POST विनंत्या डेटा पाठवण्यासाठी आणि प्रतिसाद मिळवण्यासाठी असतात. GET विनंत्या डेटा मिळवण्यासाठी वापरल्या जातात. GET विनंत्या तुमचा वेब ब्राउझर वेब पृष्ठे लोड करण्यासाठी वापरतो.

    POST विनंती प्रतिसाद स्थिती कोड परत करते. हे चांगल्या प्रकारे परिभाषित केलेले मूल्ये असतात, ज्यामध्ये 200 म्हणजे **OK** - POST विनंती यशस्वी झाली.

    > 💁 तुम्ही [List of HTTP status codes page on Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes) वर सर्व प्रतिसाद स्थिती कोड पाहू शकता.

    जर 200 परत आले, तर परिणाम HTTP क्लायंटकडून वाचला जातो. हा REST API कडून prediction च्या परिणामांसह JSON दस्तऐवज म्हणून पाठवलेला मजकूर प्रतिसाद आहे. JSON खालील स्वरूपात आहे:

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

    येथे महत्त्वाचा भाग म्हणजे `predictions` array. यात predictions असतात, प्रत्येक टॅगसाठी एक entry ज्यामध्ये टॅगचे नाव आणि probability असते. परत आलेल्या probabilities 0-1 दरम्यान असतात, 0 म्हणजे टॅगशी जुळण्याची 0% शक्यता, आणि 1 म्हणजे 100% शक्यता.

    > 💁 प्रतिमा वर्गीकर्ते वापरलेल्या सर्व टॅगसाठी टक्केवारी परत करतात. प्रत्येक टॅगसाठी प्रतिमेने त्या टॅगशी जुळण्याची probability असते.

    हा JSON डिकोड केला जातो, आणि प्रत्येक टॅगसाठी probabilities serial monitor वर पाठवले जातात.

1. `buttonPressed` फंक्शनमध्ये, SD कार्डवर सेव्ह करण्यासाठी असलेला कोड `classifyImage` कॉलने बदला, किंवा तो कोड लिहिल्यानंतर जोडा, पण **buffer delete करण्याच्या आधी**:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 जर तुम्ही SD कार्डवर सेव्ह करण्यासाठी असलेला कोड बदलला, तर तुम्ही तुमचा कोड साफ करून `setupSDCard` आणि `saveToSDCard` फंक्शन्स काढून टाकू शकता.

1. तुमचा कोड अपलोड करा आणि चालवा. कॅमेरा फळांकडे निर्देशित करा आणि C बटण दाबा. तुम्हाला serial monitor मध्ये आउटपुट दिसेल:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    तुम्ही घेतलेली प्रतिमा आणि Custom Vision मधील **Predictions** टॅबमध्ये ही मूल्ये पाहू शकता.

    ![Custom Vision मध्ये एक केळी, 56.8% पक्की आणि 43.1% कच्ची म्हणून वर्गीकृत](../../../../../translated_images/mr/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 तुम्ही हा कोड [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal) फोल्डरमध्ये शोधू शकता.

😀 तुमचा फळ गुणवत्ता वर्गीकर्ता प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून निर्माण होणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.