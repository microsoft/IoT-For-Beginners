<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-28T16:10:24+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "my"
}
-->
# ပုံတစ်ပုံကို အမျိုးအစားခွဲခြားခြင်း - Wio Terminal

ဒီသင်ခန်းစာအပိုင်းမှာ ကင်မရာက ရိုက်ယူထားတဲ့ပုံကို Custom Vision ဝန်ဆောင်မှုဆီပို့ပြီး အမျိုးအစားခွဲခြားပေးမှာဖြစ်ပါတယ်။

## ပုံတစ်ပုံကို အမျိုးအစားခွဲခြားခြင်း

Custom Vision ဝန်ဆောင်မှုမှာ REST API တစ်ခုရှိပြီး Wio Terminal ကနေ အမျိုးအစားခွဲခြားဖို့ ခေါ်ယူနိုင်ပါတယ်။ ဒီ REST API ကို HTTPS ချိတ်ဆက်မှု - လုံခြုံသော HTTP ချိတ်ဆက်မှုမှတစ်ဆင့် အသုံးပြုနိုင်ပါတယ်။

HTTPS endpoint တွေနဲ့ အပြန်အလှန်ဆက်သွယ်တဲ့အခါ client code က ချိတ်ဆက်မယ့် server က public key certificate ကို တောင်းယူပြီး traffic ကို encrypt လုပ်ဖို့ အသုံးပြုရပါမယ်။ သင့် web browser က အလိုအလျောက်လုပ်ပေးနိုင်ပေမယ့် microcontroller တွေကတော့ မလုပ်နိုင်ပါဘူး။ သင့် application မှာ certificate ကို hard code လုပ်ဖို့အတွက် ဒီ certificate ကို manually တောင်းယူရပါမယ်။

ဒီ certificate တွေမှာ public key တွေပါဝင်ပြီး လုံခြုံစွာထားရမယ့်အရာမဟုတ်ပါဘူး။ သင့် source code မှာ အသုံးပြုနိုင်ပြီး GitHub ကဲ့သို့သော public နေရာတွေမှာ share လုပ်နိုင်ပါတယ်။

### Task - SSL client ကို set up လုပ်ပါ

1. `fruit-quality-detector` app project ကို မဖွင့်ထားရင် ဖွင့်ပါ။

1. `config.h` header file ကို ဖွင့်ပြီး အောက်ပါ code ကို ထည့်ပါ။

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

    ဒီဟာက *Microsoft Azure DigiCert Global Root G2 certificate* ဖြစ်ပြီး Azure ဝန်ဆောင်မှုများအတွက် အများအားဖြင့် အသုံးပြုတဲ့ certificate တစ်ခုဖြစ်ပါတယ်။

    > 💁 ဒီ certificate ကို အသုံးပြုဖို့အတွက် macOS သို့မဟုတ် Linux မှာ အောက်ပါ command ကို run လုပ်ပါ။ Windows အသုံးပြုနေပါက [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn) ကို အသုံးပြုပြီး run လုပ်နိုင်ပါတယ်။
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > output မှာ DigiCert Global Root G2 certificate ကို ပြပါလိမ့်မယ်။

1. `main.cpp` ကို ဖွင့်ပြီး အောက်ပါ include directive ကို ထည့်ပါ။

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. include directive တွေ့အောက်မှာ `WifiClientSecure` instance တစ်ခုကို ကြေညာပါ။

    ```cpp
    WiFiClientSecure client;
    ```

    ဒီ class မှာ HTTPS မှတစ်ဆင့် web endpoint တွေနဲ့ ဆက်သွယ်ဖို့ code ပါဝင်ပါတယ်။

1. `connectWiFi` method မှာ WiFiClientSecure ကို DigiCert Global Root G2 certificate ကို အသုံးပြုဖို့ set လုပ်ပါ။

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Task - ပုံတစ်ပုံကို အမျိုးအစားခွဲခြားပါ

1. `platformio.ini` file ရဲ့ `lib_deps` list မှာ အောက်ပါ additional line ကို ထည့်ပါ။

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    ဒီဟာ [ArduinoJson](https://arduinojson.org) ကို import လုပ်ပြီး REST API response ကို decode လုပ်ဖို့ အသုံးပြုမယ်။

1. `config.h` မှာ Custom Vision ဝန်ဆောင်မှုရဲ့ prediction URL နဲ့ Key အတွက် constants တွေကို ထည့်ပါ။

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    `<PREDICTION_URL>` ကို Custom Vision ရဲ့ prediction URL နဲ့ အစားထိုးပါ။ `<PREDICTION_KEY>` ကို prediction key နဲ့ အစားထိုးပါ။

1. `main.cpp` မှာ ArduinoJson library အတွက် include directive ကို ထည့်ပါ။

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `main.cpp` မှာ `buttonPressed` function ရဲ့ အပေါ်မှာ အောက်ပါ function ကို ထည့်ပါ။

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

    ဒီ code က `HTTPClient` ကို ကြေညာပြီး REST API တွေနဲ့ ဆက်သွယ်ဖို့ method တွေပါဝင်ပါတယ်။ client ကို Azure public key နဲ့ setup လုပ်ထားတဲ့ prediction URL ကို ချိတ်ဆက်ပေးပါတယ်။

    ချိတ်ဆက်ပြီးရင် headers တွေကို ပို့ပါတယ် - REST API ကို request လုပ်မယ့်အကြောင်းအရာကို ဖော်ပြတဲ့ header တွေပါ။ `Content-Type` header က raw binary data ပို့မယ်ဆိုတာကို ဖော်ပြပြီး `Prediction-Key` header က Custom Vision prediction key ကို ပို့ပါတယ်။

    နောက်ဆုံးမှာ HTTP client ကို POST request တစ်ခုလုပ်ပြီး byte array တစ်ခုကို upload လုပ်ပါတယ်။ ဒီ byte array မှာ ကင်မရာက ရိုက်ယူထားတဲ့ JPEG ပုံပါဝင်မှာဖြစ်ပါတယ်။

    > 💁 POST request တွေက data ပို့ပြီး response ရယူဖို့အတွက် ဖြစ်ပါတယ်။ GET request တွေက data ရယူဖို့အတွက် ဖြစ်ပါတယ်။ သင့် web browser က web page တွေ load လုပ်ဖို့ GET request ကို အသုံးပြုပါတယ်။

    POST request က response status code ကို ပြန်ပေးပါတယ်။ 200 ဆိုတာ **OK** - POST request အောင်မြင်ခဲ့တယ်ဆိုတာကို ဆိုလိုပါတယ်။

    > 💁 response status code တွေကို [Wikipedia ရဲ့ List of HTTP status codes page](https://wikipedia.org/wiki/List_of_HTTP_status_codes) မှာ ကြည့်ရှုနိုင်ပါတယ်။

    200 ကို ပြန်ပေးရင် REST API ရဲ့ prediction ရလဒ်ကို JSON document အနေနဲ့ HTTP client မှာ ဖတ်ယူနိုင်ပါတယ်။ JSON format က အောက်ပါအတိုင်းဖြစ်ပါတယ်။

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

    အရေးကြီးတဲ့အပိုင်းက `predictions` array ဖြစ်ပါတယ်။ ဒီမှာ tag တစ်ခုစီအတွက် tag name နဲ့ probability ပါဝင်ပါတယ်။ probability တွေက 0-1 အတွင်း floating point number တွေဖြစ်ပြီး 0 က 0% chance, 1 က 100% chance ကို ဆိုလိုပါတယ်။

    > 💁 ပုံခွဲခြားစက်တွေက အသုံးပြုထားတဲ့ tag အားလုံးအတွက် percentage တွေကို ပြန်ပေးပါမယ်။ tag တစ်ခုစီမှာ ပုံဟာ tag နဲ့ ကိုက်ညီနိုင်တဲ့ probability ပါဝင်ပါတယ်။

    ဒီ JSON ကို decode လုပ်ပြီး tag တစ်ခုစီရဲ့ probability တွေကို serial monitor မှာ ပို့ပါတယ်။

1. `buttonPressed` function မှာ SD card ကို save လုပ်တဲ့ code ကို `classifyImage` ကို ခေါ်ယူဖို့ အစားထိုးပါ၊ ဒါမှမဟုတ် ပုံကို ရေးပြီး buffer ကို delete လုပ်မယ့်အခါ **မတိုင်မီ** ထည့်ပါ။

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 SD card ကို save လုပ်တဲ့ code ကို အစားထိုးလိုက်ရင် `setupSDCard` နဲ့ `saveToSDCard` function တွေကို ဖယ်ရှားပြီး code ကို သန့်စင်နိုင်ပါတယ်။

1. သင့် code ကို upload လုပ်ပြီး run လုပ်ပါ။ ကင်မရာကို သစ်သီးတစ်ခုဆီကို ဦးတည်ပြီး C button ကို နှိပ်ပါ။ serial monitor မှာ output ကို ကြည့်နိုင်ပါမယ်။

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    ရိုက်ယူထားတဲ့ပုံနဲ့ prediction value တွေကို Custom Vision ရဲ့ **Predictions** tab မှာ ကြည့်နိုင်ပါမယ်။

    ![Custom Vision မှာ prediction ပြထားတဲ့ သစ်သီးပုံ](../../../../../translated_images/my/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 ဒီ code ကို [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal) folder မှာ ရှာနိုင်ပါတယ်။

😀 သင့်ရဲ့ သစ်သီးအရည်အသွေးခွဲခြားစက်က အောင်မြင်ခဲ့ပါတယ်!

---

**ဝက်ဘ်ဆိုက်မှတ်ချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှန်ကန်မှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက်ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါဝင်နိုင်ကြောင်း သတိပြုပါ။ မူလဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတည်သော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော နားလည်မှုမှားများ သို့မဟုတ် အဓိပ္ပါယ်မှားများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။