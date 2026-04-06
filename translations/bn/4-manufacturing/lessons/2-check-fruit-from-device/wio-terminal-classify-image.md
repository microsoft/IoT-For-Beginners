# একটি ছবি শ্রেণীবদ্ধ করুন - Wio Terminal

এই পাঠের এই অংশে, আপনি ক্যামেরা দ্বারা ধারণ করা ছবিটি শ্রেণীবদ্ধ করার জন্য Custom Vision সার্ভিসে পাঠাবেন।

## একটি ছবি শ্রেণীবদ্ধ করুন

Custom Vision সার্ভিসে একটি REST API রয়েছে যা Wio Terminal থেকে ছবি শ্রেণীবদ্ধ করার জন্য ব্যবহার করা যায়। এই REST API একটি HTTPS সংযোগের মাধ্যমে অ্যাক্সেস করা হয় - এটি একটি সুরক্ষিত HTTP সংযোগ।

HTTPS এন্ডপয়েন্টের সাথে যোগাযোগ করার সময়, ক্লায়েন্ট কোডটি অ্যাক্সেস করা সার্ভার থেকে পাবলিক কী সার্টিফিকেট অনুরোধ করে এবং এটি ব্যবহার করে প্রেরিত ডেটা এনক্রিপ্ট করে। আপনার ওয়েব ব্রাউজার এটি স্বয়ংক্রিয়ভাবে করে, কিন্তু মাইক্রোকন্ট্রোলারগুলো তা করে না। আপনাকে এই সার্টিফিকেটটি ম্যানুয়ালি অনুরোধ করতে হবে এবং এটি ব্যবহার করে REST API এর সাথে একটি সুরক্ষিত সংযোগ তৈরি করতে হবে। এই সার্টিফিকেটগুলো পরিবর্তন হয় না, তাই একবার সার্টিফিকেট পেলে, এটি আপনার অ্যাপ্লিকেশনে হার্ড কোড করা যেতে পারে।

এই সার্টিফিকেটগুলোতে পাবলিক কী থাকে এবং এগুলো সুরক্ষিত রাখার প্রয়োজন নেই। আপনি এগুলো আপনার সোর্স কোডে ব্যবহার করতে পারেন এবং GitHub-এর মতো পাবলিক জায়গায় শেয়ার করতে পারেন।

### কাজ - একটি SSL ক্লায়েন্ট সেটআপ করুন

1. যদি এটি ইতিমধ্যে খোলা না থাকে, তাহলে `fruit-quality-detector` অ্যাপ প্রকল্পটি খুলুন।

1. `config.h` হেডার ফাইলটি খুলুন এবং নিচের কোডটি যোগ করুন:

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

    এটি *Microsoft Azure DigiCert Global Root G2 সার্টিফিকেট* - এটি বিশ্বব্যাপী অনেক Azure সার্ভিসে ব্যবহৃত একটি সার্টিফিকেট।

    > 💁 এটি যে সঠিক সার্টিফিকেট তা নিশ্চিত করতে, macOS বা Linux-এ নিচের কমান্ডটি চালান। যদি আপনি Windows ব্যবহার করেন, তাহলে [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn) ব্যবহার করে এই কমান্ডটি চালাতে পারেন:
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > আউটপুটে DigiCert Global Root G2 সার্টিফিকেট তালিকাভুক্ত থাকবে।

1. `main.cpp` খুলুন এবং নিচের include নির্দেশনা যোগ করুন:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. include নির্দেশনার নিচে, `WifiClientSecure` এর একটি ইনস্ট্যান্স ঘোষণা করুন:

    ```cpp
    WiFiClientSecure client;
    ```

    এই ক্লাসটি HTTPS এর মাধ্যমে ওয়েব এন্ডপয়েন্টের সাথে যোগাযোগ করার কোড ধারণ করে।

1. `connectWiFi` মেথডে, WiFiClientSecure-কে DigiCert Global Root G2 সার্টিফিকেট ব্যবহার করতে সেট করুন:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### কাজ - একটি ছবি শ্রেণীবদ্ধ করুন

1. `platformio.ini` ফাইলের `lib_deps` তালিকায় একটি অতিরিক্ত লাইন যোগ করুন:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    এটি [ArduinoJson](https://arduinojson.org), একটি Arduino JSON লাইব্রেরি, ইমপোর্ট করে এবং REST API থেকে JSON রেসপন্স ডিকোড করতে ব্যবহৃত হবে।

1. `config.h`-এ, Custom Vision সার্ভিস থেকে প্রেডিকশন URL এবং Key এর জন্য কনস্ট্যান্ট যোগ করুন:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    `<PREDICTION_URL>` এর জায়গায় Custom Vision থেকে প্রাপ্ত প্রেডিকশন URL দিন। `<PREDICTION_KEY>` এর জায়গায় প্রেডিকশন কী দিন।

1. `main.cpp`-এ ArduinoJson লাইব্রেরির জন্য একটি include নির্দেশনা যোগ করুন:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `main.cpp`-এ, `buttonPressed` ফাংশনের উপরে নিচের ফাংশনটি যোগ করুন:

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

    এই কোডটি একটি `HTTPClient` ঘোষণা করে - এটি REST API এর সাথে যোগাযোগ করার জন্য মেথড ধারণ করে। এরপর এটি Azure পাবলিক কী সহ সেটআপ করা WiFiClientSecure ইনস্ট্যান্স ব্যবহার করে প্রেডিকশন URL-এ ক্লায়েন্টটি সংযুক্ত করে।

    সংযোগ স্থাপনের পর, এটি হেডার পাঠায় - REST API এর বিরুদ্ধে করা অনুরোধের তথ্য। `Content-Type` হেডারটি নির্দেশ করে যে API কলটি কাঁচা বাইনারি ডেটা পাঠাবে, এবং `Prediction-Key` হেডারটি Custom Vision প্রেডিকশন কী পাঠায়।

    এরপর একটি POST অনুরোধ HTTP ক্লায়েন্টে করা হয়, যেখানে একটি বাইট অ্যারে আপলোড করা হয়। এটি JPEG ছবি ধারণ করে যা ক্যামেরা থেকে ধারণ করা হয় যখন এই ফাংশনটি ডাকা হয়।

    > 💁 POST অনুরোধ ডেটা পাঠানোর এবং রেসপন্স পাওয়ার জন্য ব্যবহৃত হয়। অন্য অনুরোধের ধরন যেমন GET অনুরোধ ডেটা পুনরুদ্ধার করতে ব্যবহৃত হয়। আপনার ওয়েব ব্রাউজার ওয়েব পেজ লোড করতে GET অনুরোধ ব্যবহার করে।

    POST অনুরোধ একটি রেসপন্স স্ট্যাটাস কোড ফেরত দেয়। এগুলো সুসংজ্ঞায়িত মান, যেখানে 200 মানে **OK** - POST অনুরোধ সফল হয়েছে।

    > 💁 আপনি সমস্ত রেসপন্স স্ট্যাটাস কোড [Wikipedia-র HTTP স্ট্যাটাস কোড পৃষ্ঠায়](https://wikipedia.org/wiki/List_of_HTTP_status_codes) দেখতে পারেন।

    যদি 200 ফেরত আসে, তাহলে HTTP ক্লায়েন্ট থেকে রেজাল্টটি পড়া হয়। এটি REST API থেকে প্রেডিকশনের ফলাফল সহ একটি JSON ডকুমেন্টের টেক্সট রেসপন্স। JSON এর ফরম্যাট নিম্নরূপ:

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

    এখানে গুরুত্বপূর্ণ অংশটি হলো `predictions` অ্যারে। এটি প্রেডিকশনগুলো ধারণ করে, যেখানে প্রতিটি ট্যাগের জন্য ট্যাগের নাম এবং সম্ভাবনা থাকে। ফেরত দেওয়া সম্ভাবনাগুলো 0-1 এর মধ্যে ফ্লোটিং পয়েন্ট সংখ্যা, যেখানে 0 মানে 0% সম্ভাবনা এবং 1 মানে 100% সম্ভাবনা।

    > 💁 ইমেজ ক্লাসিফায়ারগুলো সমস্ত ব্যবহৃত ট্যাগের জন্য শতাংশ ফেরত দেয়। প্রতিটি ট্যাগের জন্য সম্ভাবনা থাকে যে ছবিটি সেই ট্যাগের সাথে মেলে।

    এই JSON ডিকোড করা হয় এবং প্রতিটি ট্যাগের সম্ভাবনা সিরিয়াল মনিটরে পাঠানো হয়।

1. `buttonPressed` ফাংশনে, SD কার্ডে সংরক্ষণ করার কোডটি `classifyImage` ফাংশনের একটি কল দিয়ে প্রতিস্থাপন করুন, অথবা এটি যোগ করুন কিন্তু **বাফার মুছে ফেলার আগে**:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 যদি আপনি SD কার্ডে সংরক্ষণ করার কোডটি প্রতিস্থাপন করেন, তাহলে আপনার কোডটি পরিষ্কার করতে `setupSDCard` এবং `saveToSDCard` ফাংশনগুলো সরিয়ে ফেলতে পারেন।

1. আপনার কোড আপলোড করুন এবং চালান। ক্যামেরাটি কিছু ফলের দিকে নির্দেশ করুন এবং C বোতামটি চাপুন। আপনি সিরিয়াল মনিটরে আউটপুট দেখতে পাবেন:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    আপনি যে ছবি তুলেছেন তা এবং এই মানগুলো Custom Vision-এর **Predictions** ট্যাবে দেখতে পারবেন।

    ![Custom Vision-এ একটি কলা, যা 56.8% পাকা এবং 43.1% কাঁচা হিসেবে প্রেডিক্ট করা হয়েছে](../../../../../translated_images/bn/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 আপনি এই কোডটি [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার ফলের গুণমান শ্রেণীবদ্ধকরণ প্রোগ্রামটি সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিকতার জন্য চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা তার জন্য দায়ী থাকব না।