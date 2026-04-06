# ਇੱਕ ਚਿੱਤਰ ਨੂੰ ਵਰਗਬੱਧ ਕਰੋ - Wio Terminal

ਇਸ ਪਾਠ ਦੇ ਇਸ ਭਾਗ ਵਿੱਚ, ਤੁਸੀਂ ਕੈਮਰੇ ਦੁਆਰਾ ਕੈਪਚਰ ਕੀਤੇ ਚਿੱਤਰ ਨੂੰ Custom Vision ਸੇਵਾ ਨੂੰ ਭੇਜੋਗੇ ਤਾਂ ਜੋ ਇਸਨੂੰ ਵਰਗਬੱਧ ਕੀਤਾ ਜਾ ਸਕੇ।

## ਇੱਕ ਚਿੱਤਰ ਨੂੰ ਵਰਗਬੱਧ ਕਰੋ

Custom Vision ਸੇਵਾ ਵਿੱਚ REST API ਹੈ ਜਿਸਨੂੰ ਤੁਸੀਂ Wio Terminal ਤੋਂ ਚਿੱਤਰਾਂ ਨੂੰ ਵਰਗਬੱਧ ਕਰਨ ਲਈ ਕਾਲ ਕਰ ਸਕਦੇ ਹੋ। ਇਹ REST API HTTPS ਕਨੈਕਸ਼ਨ - ਇੱਕ ਸੁਰੱਖਿਅਤ HTTP ਕਨੈਕਸ਼ਨ ਰਾਹੀਂ ਪਹੁੰਚਯੋਗ ਹੈ।

HTTPS ਐਂਡਪੌਇੰਟਸ ਨਾਲ ਸੰਚਾਰ ਕਰਦੇ ਸਮੇਂ, ਕਲਾਇੰਟ ਕੋਡ ਨੂੰ ਉਸ ਸਰਵਰ ਤੋਂ ਪਬਲਿਕ ਕੀ ਸਰਟੀਫਿਕੇਟ ਦੀ ਬੇਨਤੀ ਕਰਨ ਦੀ ਜ਼ਰੂਰਤ ਹੁੰਦੀ ਹੈ ਜਿਸਨੂੰ ਪਹੁੰਚਿਆ ਜਾ ਰਿਹਾ ਹੈ, ਅਤੇ ਇਸਨੂੰ ਭੇਜੀ ਗਈ ਟ੍ਰੈਫਿਕ ਨੂੰ ਇਨਕ੍ਰਿਪਟ ਕਰਨ ਲਈ ਵਰਤਿਆ ਜਾਂਦਾ ਹੈ। ਤੁਹਾਡਾ ਵੈਬ ਬ੍ਰਾਊਜ਼ਰ ਇਹ ਆਪਣੇ ਆਪ ਕਰਦਾ ਹੈ, ਪਰ ਮਾਈਕਰੋਕੰਟਰੋਲਰ ਨਹੀਂ ਕਰਦੇ। ਤੁਹਾਨੂੰ ਇਹ ਸਰਟੀਫਿਕੇਟ ਮੈਨੁਅਲੀ ਤੌਰ 'ਤੇ ਲੈਣਾ ਪਵੇਗਾ ਅਤੇ ਇਸਨੂੰ REST API ਨਾਲ ਸੁਰੱਖਿਅਤ ਕਨੈਕਸ਼ਨ ਬਣਾਉਣ ਲਈ ਵਰਤਣਾ ਪਵੇਗਾ। ਇਹ ਸਰਟੀਫਿਕੇਟ ਬਦਲਦੇ ਨਹੀਂ ਹਨ, ਇਸ ਲਈ ਜਦੋਂ ਤੁਹਾਡੇ ਕੋਲ ਇੱਕ ਸਰਟੀਫਿਕੇਟ ਹੁੰਦਾ ਹੈ, ਇਸਨੂੰ ਤੁਹਾਡੇ ਐਪਲੀਕੇਸ਼ਨ ਵਿੱਚ ਹਾਰਡ ਕੋਡ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ।

ਇਹ ਸਰਟੀਫਿਕੇਟ ਪਬਲਿਕ ਕੀਜ਼ ਸ਼ਾਮਲ ਕਰਦੇ ਹਨ ਅਤੇ ਸੁਰੱਖਿਅਤ ਰੱਖਣ ਦੀ ਲੋੜ ਨਹੀਂ ਹੁੰਦੀ। ਤੁਸੀਂ ਇਹਨਾਂ ਨੂੰ ਆਪਣੇ ਸੋਰਸ ਕੋਡ ਵਿੱਚ ਵਰਤ ਸਕਦੇ ਹੋ ਅਤੇ GitHub ਵਰਗੇ ਜਨਤਕ ਸਥਾਨਾਂ 'ਤੇ ਸਾਂਝਾ ਕਰ ਸਕਦੇ ਹੋ।

### ਟਾਸਕ - SSL ਕਲਾਇੰਟ ਸੈਟਅਪ ਕਰੋ

1. `fruit-quality-detector` ਐਪ ਪ੍ਰੋਜੈਕਟ ਖੋਲ੍ਹੋ ਜੇਕਰ ਇਹ ਪਹਿਲਾਂ ਹੀ ਖੁੱਲ੍ਹਾ ਨਹੀਂ ਹੈ।

1. `config.h` ਹੈਡਰ ਫਾਈਲ ਖੋਲ੍ਹੋ ਅਤੇ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ *Microsoft Azure DigiCert Global Root G2 ਸਰਟੀਫਿਕੇਟ* ਹੈ - ਇਹ ਉਹਨਾਂ ਸਰਟੀਫਿਕੇਟਸ ਵਿੱਚੋਂ ਇੱਕ ਹੈ ਜੋ ਬਹੁਤ ਸਾਰੇ Azure ਸੇਵਾਵਾਂ ਦੁਆਰਾ ਗਲੋਬਲ ਤੌਰ 'ਤੇ ਵਰਤੇ ਜਾਂਦੇ ਹਨ।

    > 💁 ਇਹ ਦੇਖਣ ਲਈ ਕਿ ਇਹ ਵਰਤਣ ਲਈ ਸਰਟੀਫਿਕੇਟ ਹੈ, macOS ਜਾਂ Linux 'ਤੇ ਹੇਠਾਂ ਦਿੱਤਾ ਕਮਾਂਡ ਚਲਾਓ। ਜੇਕਰ ਤੁਸੀਂ Windows ਵਰਤ ਰਹੇ ਹੋ, ਤਾਂ ਤੁਸੀਂ ਇਹ ਕਮਾਂਡ [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਚਲਾ ਸਕਦੇ ਹੋ:
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > ਆਉਟਪੁੱਟ DigiCert Global Root G2 ਸਰਟੀਫਿਕੇਟ ਦੀ ਸੂਚੀ ਦਿਖਾਏਗੀ।

1. `main.cpp` ਖੋਲ੍ਹੋ ਅਤੇ ਹੇਠਾਂ ਦਿੱਤਾ ਸ਼ਾਮਲ ਕਰਨ ਵਾਲਾ ਨਿਰਦੇਸ਼ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. ਸ਼ਾਮਲ ਕਰਨ ਵਾਲੇ ਨਿਰਦੇਸ਼ਾਂ ਦੇ ਹੇਠਾਂ, `WifiClientSecure` ਦਾ ਇੱਕ ਇੰਸਟੈਂਸ ਘੋਸ਼ਿਤ ਕਰੋ:

    ```cpp
    WiFiClientSecure client;
    ```

    ਇਹ ਕਲਾਸ HTTPS ਰਾਹੀਂ ਵੈਬ ਐਂਡਪੌਇੰਟਸ ਨਾਲ ਸੰਚਾਰ ਕਰਨ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰਦੀ ਹੈ।

1. `connectWiFi` ਵਿਧੀ ਵਿੱਚ, WiFiClientSecure ਨੂੰ DigiCert Global Root G2 ਸਰਟੀਫਿਕੇਟ ਵਰਤਣ ਲਈ ਸੈਟ ਕਰੋ:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### ਟਾਸਕ - ਇੱਕ ਚਿੱਤਰ ਨੂੰ ਵਰਗਬੱਧ ਕਰੋ

1. `platformio.ini` ਫਾਈਲ ਵਿੱਚ `lib_deps` ਸੂਚੀ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਇੱਕ ਵਾਧੂ ਲਾਈਨ ਸ਼ਾਮਲ ਕਰੋ:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    ਇਹ [ArduinoJson](https://arduinojson.org), ਇੱਕ Arduino JSON ਲਾਇਬ੍ਰੇਰੀ ਨੂੰ ਇੰਪੋਰਟ ਕਰਦਾ ਹੈ, ਅਤੇ REST API ਤੋਂ JSON ਜਵਾਬ ਨੂੰ ਡਿਕੋਡ ਕਰਨ ਲਈ ਵਰਤਿਆ ਜਾਵੇਗਾ।

1. `config.h` ਵਿੱਚ Custom Vision ਸੇਵਾ ਤੋਂ ਪ੍ਰਡਿਕਸ਼ਨ URL ਅਤੇ Key ਲਈ constants ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    `<PREDICTION_URL>` ਨੂੰ Custom Vision ਤੋਂ ਪ੍ਰਡਿਕਸ਼ਨ URL ਨਾਲ ਬਦਲੋ। `<PREDICTION_KEY>` ਨੂੰ ਪ੍ਰਡਿਕਸ਼ਨ ਕੀ ਨਾਲ ਬਦਲੋ।

1. `main.cpp` ਵਿੱਚ ArduinoJson ਲਾਇਬ੍ਰੇਰੀ ਲਈ ਇੱਕ ਸ਼ਾਮਲ ਕਰਨ ਵਾਲਾ ਨਿਰਦੇਸ਼ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `main.cpp` ਵਿੱਚ `buttonPressed` ਫੰਕਸ਼ਨ ਤੋਂ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤਾ ਫੰਕਸ਼ਨ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਕੋਡ ਇੱਕ `HTTPClient` ਘੋਸ਼ਿਤ ਕਰਕੇ ਸ਼ੁਰੂ ਹੁੰਦਾ ਹੈ - ਇੱਕ ਕਲਾਸ ਜਿਸ ਵਿੱਚ REST APIs ਨਾਲ ਸੰਚਾਰ ਕਰਨ ਲਈ ਵਿਧੀਆਂ ਸ਼ਾਮਲ ਹਨ। ਫਿਰ ਇਹ ਕਲਾਇੰਟ ਨੂੰ Azure ਪਬਲਿਕ ਕੀ ਨਾਲ ਸੈਟਅਪ ਕੀਤੇ WiFiClientSecure ਇੰਸਟੈਂਸ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਪ੍ਰਡਿਕਸ਼ਨ URL ਨਾਲ ਕਨੈਕਟ ਕਰਦਾ ਹੈ।

    ਕਨੈਕਟ ਹੋਣ ਤੋਂ ਬਾਅਦ, ਇਹ ਹੈਡਰ ਭੇਜਦਾ ਹੈ - REST API ਦੇ ਖਿਲਾਫ ਕੀਤੇ ਜਾਣ ਵਾਲੇ ਅਗਲੇ ਬੇਨਤੀ ਬਾਰੇ ਜਾਣਕਾਰੀ। `Content-Type` ਹੈਡਰ ਦਰਸਾਉਂਦਾ ਹੈ ਕਿ API ਕਾਲ ਕੱਚਾ ਬਾਈਨਰੀ ਡਾਟਾ ਭੇਜੇਗੀ, `Prediction-Key` ਹੈਡਰ Custom Vision ਪ੍ਰਡਿਕਸ਼ਨ ਕੀ ਪਾਸ ਕਰਦਾ ਹੈ।

    ਅਗਲੇ ਕਦਮ ਵਿੱਚ, HTTP ਕਲਾਇੰਟ ਨੂੰ ਇੱਕ POST ਬੇਨਤੀ ਕੀਤੀ ਜਾਂਦੀ ਹੈ, ਜਿਸ ਵਿੱਚ ਇੱਕ ਬਾਈਟ ਐਰੇ ਅਪਲੋਡ ਕੀਤਾ ਜਾਂਦਾ ਹੈ। ਇਹ JPEG ਚਿੱਤਰ ਸ਼ਾਮਲ ਕਰੇਗਾ ਜੋ ਕੈਮਰੇ ਤੋਂ ਕੈਪਚਰ ਕੀਤਾ ਗਿਆ ਸੀ ਜਦੋਂ ਇਹ ਫੰਕਸ਼ਨ ਕਾਲ ਕੀਤਾ ਗਿਆ।

    > 💁 POST ਬੇਨਤੀਆਂ ਡਾਟਾ ਭੇਜਣ ਅਤੇ ਜਵਾਬ ਪ੍ਰਾਪਤ ਕਰਨ ਲਈ ਹੁੰਦੀਆਂ ਹਨ। ਹੋਰ ਬੇਨਤੀ ਕਿਸਮਾਂ ਹਨ ਜਿਵੇਂ ਕਿ GET ਬੇਨਤੀਆਂ ਜੋ ਡਾਟਾ ਪ੍ਰਾਪਤ ਕਰਦੀਆਂ ਹਨ। GET ਬੇਨਤੀਆਂ ਤੁਹਾਡੇ ਵੈਬ ਬ੍ਰਾਊਜ਼ਰ ਦੁਆਰਾ ਵੈਬ ਪੇਜ ਲੋਡ ਕਰਨ ਲਈ ਵਰਤੀਆਂ ਜਾਂਦੀਆਂ ਹਨ।

    POST ਬੇਨਤੀ ਇੱਕ ਜਵਾਬ ਸਥਿਤੀ ਕੋਡ ਵਾਪਸ ਕਰਦੀ ਹੈ। ਇਹ ਚੰਗੀ ਤਰ੍ਹਾਂ ਪਰਿਭਾਸ਼ਿਤ ਮੁੱਲ ਹਨ, ਜਿਨ੍ਹਾਂ ਵਿੱਚ 200 ਦਾ ਮਤਲਬ **OK** ਹੈ - POST ਬੇਨਤੀ ਸਫਲ ਰਹੀ।

    > 💁 ਤੁਸੀਂ ਸਾਰੇ ਜਵਾਬ ਸਥਿਤੀ ਕੋਡ [HTTP ਸਥਿਤੀ ਕੋਡਾਂ ਦੀ ਸੂਚੀ ਵਾਲੇ ਪੰਨੇ 'ਤੇ Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes) 'ਤੇ ਦੇਖ ਸਕਦੇ ਹੋ।

    ਜੇਕਰ 200 ਵਾਪਸ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਤਾਂ ਨਤੀਜਾ HTTP ਕਲਾਇੰਟ ਤੋਂ ਪੜ੍ਹਿਆ ਜਾਂਦਾ ਹੈ। ਇਹ REST API ਤੋਂ ਪ੍ਰਡਿਕਸ਼ਨ ਦੇ ਨਤੀਜਿਆਂ ਨਾਲ ਇੱਕ JSON ਦਸਤਾਵੇਜ਼ ਦੇ ਰੂਪ ਵਿੱਚ ਇੱਕ ਟੈਕਸਟ ਜਵਾਬ ਹੈ। JSON ਹੇਠਾਂ ਦਿੱਤੇ ਫਾਰਮੈਟ ਵਿੱਚ ਹੈ:

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

    ਇੱਥੇ ਮਹੱਤਵਪੂਰਨ ਹਿੱਸਾ `predictions` ਐਰੇ ਹੈ। ਇਹ ਪ੍ਰਡਿਕਸ਼ਨ ਸ਼ਾਮਲ ਕਰਦਾ ਹੈ, ਹਰ ਟੈਗ ਲਈ ਇੱਕ ਐਂਟਰੀ ਜਿਸ ਵਿੱਚ ਟੈਗ ਦਾ ਨਾਮ ਅਤੇ ਸੰਭਾਵਨਾ ਸ਼ਾਮਲ ਹੈ। ਵਾਪਸ ਕੀਤੀਆਂ ਸੰਭਾਵਨਾਵਾਂ 0-1 ਤੋਂ ਫਲੋਟਿੰਗ ਪੌਇੰਟ ਨੰਬਰ ਹੁੰਦੀਆਂ ਹਨ, ਜਿਨ੍ਹਾਂ ਵਿੱਚ 0 ਟੈਗ ਨਾਲ ਮੇਲ ਖਾਣ ਦੀ 0% ਸੰਭਾਵਨਾ ਹੈ, ਅਤੇ 1 100% ਸੰਭਾਵਨਾ ਹੈ।

    > 💁 ਚਿੱਤਰ ਵਰਗਬੱਧ ਕਰਨ ਵਾਲੇ ਸਾਰੇ ਟੈਗਾਂ ਲਈ ਪ੍ਰਤੀਸ਼ਤ ਵਾਪਸ ਕਰਦੇ ਹਨ ਜੋ ਵਰਤੇ ਗਏ ਹਨ। ਹਰ ਟੈਗ ਵਿੱਚ ਇਹ ਸੰਭਾਵਨਾ ਹੋਵੇਗੀ ਕਿ ਚਿੱਤਰ ਉਸ ਟੈਗ ਨਾਲ ਮੇਲ ਖਾਂਦਾ ਹੈ।

    ਇਹ JSON ਡਿਕੋਡ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਅਤੇ ਹਰ ਟੈਗ ਲਈ ਸੰਭਾਵਨਾਵਾਂ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਨੂੰ ਭੇਜੀਆਂ ਜਾਂਦੀਆਂ ਹਨ।

1. `buttonPressed` ਫੰਕਸ਼ਨ ਵਿੱਚ, SD ਕਾਰਡ 'ਤੇ ਸੇਵ ਕਰਨ ਵਾਲੇ ਕੋਡ ਨੂੰ `classifyImage` ਕਾਲ ਨਾਲ ਬਦਲੋ, ਜਾਂ ਚਿੱਤਰ ਲਿਖੇ ਜਾਣ ਤੋਂ ਬਾਅਦ ਸ਼ਾਮਲ ਕਰੋ, ਪਰ **ਬਫਰ ਨੂੰ ਮਿਟਾਉਣ ਤੋਂ ਪਹਿਲਾਂ**:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 ਜੇਕਰ ਤੁਸੀਂ SD ਕਾਰਡ 'ਤੇ ਸੇਵ ਕਰਨ ਵਾਲੇ ਕੋਡ ਨੂੰ ਬਦਲਦੇ ਹੋ, ਤਾਂ ਤੁਸੀਂ ਆਪਣਾ ਕੋਡ ਸਾਫ ਕਰ ਸਕਦੇ ਹੋ `setupSDCard` ਅਤੇ `saveToSDCard` ਫੰਕਸ਼ਨ ਨੂੰ ਹਟਾ ਕੇ।

1. ਆਪਣਾ ਕੋਡ ਅਪਲੋਡ ਕਰੋ ਅਤੇ ਚਲਾਓ। ਕੈਮਰੇ ਨੂੰ ਕੁਝ ਫਲਾਂ ਵੱਲ ਇਸ਼ਾਰਾ ਕਰੋ ਅਤੇ C ਬਟਨ ਦਬਾਓ। ਤੁਸੀਂ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਵਿੱਚ ਆਉਟਪੁੱਟ ਦੇਖੋਗੇ:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    ਤੁਸੀਂ Custom Vision ਵਿੱਚ **Predictions** ਟੈਬ ਵਿੱਚ ਲਿਆ ਗਿਆ ਚਿੱਤਰ ਅਤੇ ਇਹ ਮੁੱਲ ਦੇਖ ਸਕਦੇ ਹੋ।

    ![Custom Vision ਵਿੱਚ ਇੱਕ ਕੇਲਾ, 56.8% ਪੱਕਾ ਅਤੇ 43.1% ਕੱਚਾ](../../../../../translated_images/pa/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਫਲ ਗੁਣਵੱਤਾ ਵਰਗਬੱਧ ਕਰਨ ਵਾਲਾ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਰਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁੱਤੀਆਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।