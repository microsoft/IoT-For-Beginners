<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T14:18:54+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "pa"
}
-->
# ਸਪੀਚ ਤੋਂ ਟੈਕਸਟ - Wio ਟਰਮੀਨਲ

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਕੋਡ ਲਿਖੋਗੇ ਜੋ ਕੈਪਚਰ ਕੀਤੇ ਗਏ ਆਡੀਓ ਵਿੱਚ ਸਪੀਚ ਨੂੰ ਟੈਕਸਟ ਵਿੱਚ ਬਦਲਣ ਲਈ ਸਪੀਚ ਸਰਵਿਸ ਦੀ ਵਰਤੋਂ ਕਰੇਗਾ।

## ਆਡੀਓ ਨੂੰ ਸਪੀਚ ਸਰਵਿਸ ਨੂੰ ਭੇਜੋ

ਆਡੀਓ ਨੂੰ ਸਪੀਚ ਸਰਵਿਸ ਨੂੰ REST API ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਭੇਜਿਆ ਜਾ ਸਕਦਾ ਹੈ। ਸਪੀਚ ਸਰਵਿਸ ਦੀ ਵਰਤੋਂ ਕਰਨ ਲਈ, ਸਭ ਤੋਂ ਪਹਿਲਾਂ ਤੁਹਾਨੂੰ ਇੱਕ ਐਕਸੈਸ ਟੋਕਨ ਦੀ ਬੇਨਤੀ ਕਰਨੀ ਪਵੇਗੀ, ਫਿਰ ਉਸ ਟੋਕਨ ਦੀ ਵਰਤੋਂ ਕਰਕੇ REST API ਤੱਕ ਪਹੁੰਚ ਕਰੋ। ਇਹ ਐਕਸੈਸ ਟੋਕਨ 10 ਮਿੰਟਾਂ ਬਾਅਦ ਮਿਆਦ ਪੂਰੀ ਕਰ ਜਾਂਦੇ ਹਨ, ਇਸ ਲਈ ਤੁਹਾਡੇ ਕੋਡ ਨੂੰ ਇਹ ਯਕੀਨੀ ਬਣਾਉਣ ਲਈ ਨਿਯਮਿਤ ਤੌਰ 'ਤੇ ਟੋਕਨ ਦੀ ਬੇਨਤੀ ਕਰਨੀ ਚਾਹੀਦੀ ਹੈ ਕਿ ਇਹ ਹਮੇਸ਼ਾਂ ਅਪ-ਟੂ-ਡੇਟ ਹਨ।

### ਕੰਮ - ਐਕਸੈਸ ਟੋਕਨ ਪ੍ਰਾਪਤ ਕਰੋ

1. ਜੇਕਰ `smart-timer` ਪ੍ਰੋਜੈਕਟ ਖੁੱਲ੍ਹਾ ਨਹੀਂ ਹੈ, ਤਾਂ ਇਸਨੂੰ ਖੋਲ੍ਹੋ।

1. WiFi ਤੱਕ ਪਹੁੰਚ ਕਰਨ ਅਤੇ JSON ਨੂੰ ਹੈਂਡਲ ਕਰਨ ਲਈ `platformio.ini` ਫਾਈਲ ਵਿੱਚ ਹੇਠ ਲਿਖੀਆਂ ਲਾਇਬ੍ਰੇਰੀਆਂ ਦੀ ਲੋੜ ਸ਼ਾਮਲ ਕਰੋ:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. ਹੇਠ ਲਿਖਿਆ ਕੋਡ `config.h` ਹੈਡਰ ਫਾਈਲ ਵਿੱਚ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    `<SSID>` ਅਤੇ `<PASSWORD>` ਨੂੰ ਆਪਣੇ WiFi ਲਈ ਸਬੰਧਤ ਮੁੱਲਾਂ ਨਾਲ ਬਦਲੋ।

    `<API_KEY>` ਨੂੰ ਆਪਣੇ ਸਪੀਚ ਸਰਵਿਸ ਸਰੋਤ ਲਈ API ਕੁੰਜੀ ਨਾਲ ਬਦਲੋ। `<LOCATION>` ਨੂੰ ਉਸ ਸਥਾਨ ਨਾਲ ਬਦਲੋ ਜੋ ਤੁਸੀਂ ਸਪੀਚ ਸਰਵਿਸ ਸਰੋਤ ਬਣਾਉਣ ਵੇਲੇ ਵਰਤਿਆ ਸੀ।

    `<LANGUAGE>` ਨੂੰ ਉਸ ਭਾਸ਼ਾ ਦੇ ਲੋਕੇਲ ਨਾਮ ਨਾਲ ਬਦਲੋ ਜਿਸ ਵਿੱਚ ਤੁਸੀਂ ਬੋਲ ਰਹੇ ਹੋ, ਉਦਾਹਰਣ ਲਈ `en-GB` ਅੰਗਰੇਜ਼ੀ ਲਈ, ਜਾਂ `zn-HK` ਕੈਂਟੋਨੀਜ਼ ਲਈ। ਤੁਸੀਂ ਸਹਾਇਕ ਭਾਸ਼ਾਵਾਂ ਅਤੇ ਉਨ੍ਹਾਂ ਦੇ ਲੋਕੇਲ ਨਾਮਾਂ ਦੀ ਸੂਚੀ [ਮਾਈਕਰੋਸਾਫਟ ਡੌਕਸ 'ਤੇ ਭਾਸ਼ਾ ਅਤੇ ਆਵਾਜ਼ ਸਹਾਇਤਾ ਦਸਤਾਵੇਜ਼](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

    `TOKEN_URL` ਕਾਂਸਟੈਂਟ ਟੋਕਨ ਜਾਰੀ ਕਰਨ ਵਾਲੇ ਦਾ URL ਹੈ ਬਿਨਾਂ ਸਥਾਨ ਦੇ। ਇਸਨੂੰ ਪੂਰੇ URL ਪ੍ਰਾਪਤ ਕਰਨ ਲਈ ਬਾਅਦ ਵਿੱਚ ਸਥਾਨ ਨਾਲ ਜੋੜਿਆ ਜਾਵੇਗਾ।

1. ਬਿਲਕੁਲ Custom Vision ਨਾਲ ਜੁੜਨ ਦੀ ਤਰ੍ਹਾਂ, ਤੁਹਾਨੂੰ ਟੋਕਨ ਜਾਰੀ ਕਰਨ ਵਾਲੀ ਸਰਵਿਸ ਨਾਲ ਜੁੜਨ ਲਈ HTTPS ਕਨੈਕਸ਼ਨ ਦੀ ਵਰਤੋਂ ਕਰਨੀ ਪਵੇਗੀ। `config.h` ਦੇ ਅੰਤ ਵਿੱਚ ਹੇਠ ਲਿਖਿਆ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਉਹੀ ਸਰਟੀਫਿਕੇਟ ਹੈ ਜੋ ਤੁਸੀਂ Custom Vision ਨਾਲ ਜੁੜਨ ਵੇਲੇ ਵਰਤਿਆ ਸੀ।

1. `main.cpp` ਫਾਈਲ ਦੇ ਉੱਪਰ WiFi ਹੈਡਰ ਫਾਈਲ ਅਤੇ config ਹੈਡਰ ਫਾਈਲ ਲਈ ਇੱਕ ਸ਼ਾਮਲ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. `main.cpp` ਵਿੱਚ `setup` ਫੰਕਸ਼ਨ ਤੋਂ ਉੱਪਰ WiFi ਨਾਲ ਜੁੜਨ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

1. ਇਸ ਫੰਕਸ਼ਨ ਨੂੰ `setup` ਫੰਕਸ਼ਨ ਵਿੱਚ ਕਾਲ ਕਰੋ ਜਦੋਂ ਸੀਰੀਅਲ ਕਨੈਕਸ਼ਨ ਸਥਾਪਿਤ ਹੋ ਜਾਵੇ:

    ```cpp
    connectWiFi();
    ```

1. `src` ਫੋਲਡਰ ਵਿੱਚ ਇੱਕ ਨਵੀਂ ਹੈਡਰ ਫਾਈਲ ਬਣਾਓ ਜਿਸਦਾ ਨਾਮ `speech_to_text.h` ਹੋਵੇ। ਇਸ ਹੈਡਰ ਫਾਈਲ ਵਿੱਚ ਹੇਠ ਲਿਖਿਆ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ HTTP ਕਨੈਕਸ਼ਨ, ਕਨਫਿਗਰੇਸ਼ਨ ਅਤੇ `mic.h` ਹੈਡਰ ਫਾਈਲ ਲਈ ਕੁਝ ਜ਼ਰੂਰੀ ਹੈਡਰ ਫਾਈਲਾਂ ਸ਼ਾਮਲ ਕਰਦਾ ਹੈ, ਅਤੇ `SpeechToText` ਨਾਮਕ ਇੱਕ ਕਲਾਸ ਨੂੰ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦਾ ਹੈ, ਇਸ ਤੋਂ ਪਹਿਲਾਂ ਕਿ ਇਸ ਕਲਾਸ ਦਾ ਇੱਕ ਉਦਾਹਰਣ ਘੋਸ਼ਿਤ ਕੀਤਾ ਜਾਵੇ ਜੋ ਬਾਅਦ ਵਿੱਚ ਵਰਤਿਆ ਜਾ ਸਕੇ।

1. ਇਸ ਕਲਾਸ ਦੇ `private` ਸੈਕਸ਼ਨ ਵਿੱਚ ਹੇਠ ਲਿਖੇ 2 ਫੀਲਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` ਇੱਕ WiFi ਕਲਾਇੰਟ ਹੈ ਜੋ HTTPS ਦੀ ਵਰਤੋਂ ਕਰਦਾ ਹੈ ਅਤੇ ਐਕਸੈਸ ਟੋਕਨ ਪ੍ਰਾਪਤ ਕਰਨ ਲਈ ਵਰਤਿਆ ਜਾਵੇਗਾ। ਇਹ ਟੋਕਨ ਫਿਰ `_access_token` ਵਿੱਚ ਸਟੋਰ ਕੀਤਾ ਜਾਵੇਗਾ।

1. ਹੇਠ ਲਿਖਿਆ ਮੈਥਡ `private` ਸੈਕਸ਼ਨ ਵਿੱਚ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਕੋਡ ਸਪੀਚ ਸਰੋਤ ਦੇ ਸਥਾਨ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਟੋਕਨ ਜਾਰੀ ਕਰਨ ਵਾਲੇ API ਲਈ URL ਬਣਾਉਂਦਾ ਹੈ। 

1. `public` ਸੈਕਸ਼ਨ ਵਿੱਚ, ਐਕਸੈਸ ਟੋਕਨ ਪ੍ਰਾਪਤ ਕਰਨ ਲਈ ਇੱਕ ਮੈਥਡ ਸ਼ਾਮਲ ਕਰੋ। 

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. `public` ਸੈਕਸ਼ਨ ਵਿੱਚ, ਇੱਕ `init` ਮੈਥਡ ਸ਼ਾਮਲ ਕਰੋ ਜੋ ਟੋਕਨ ਕਲਾਇੰਟ ਨੂੰ ਸੈਟਅੱਪ ਕਰਦਾ ਹੈ:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    ...

(ਅਗਲੇ ਹਿੱਸੇ ਵਿੱਚ ਜਾਰੀ...)

---

**ਅਸਵੀਕਾਰਨਾ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚੱਜੇਪਣ ਹੋ ਸਕਦੇ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼, ਜੋ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਹੈ, ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।