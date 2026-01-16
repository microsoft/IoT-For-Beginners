<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2026-01-07T06:37:21+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "kn"
}
-->
# ಚಿತ್ರ ವರ್ಗೀಕರಿಸು - Wio ಟರ್ಮಿನಲ್

ಪಾಠದ ಈ ಭಾಗದಲ್ಲಿ, ನೀವು ಕ್ಯಾಮೆರಾದ ಮೂಲಕ ಹಿಡಿದ ಚಿತ್ರವನ್ನು ಕಸ್ಟಮ್ ವಿಷನ್ ಸೇವೆಗೆ ಕಳುಹಿಸಿ ಅದನ್ನು ವರ್ಗೀಕರಿಸುವಿರಿ.

## ಚಿತ್ರವನ್ನು ವರ್ಗೀಕರಿಸು

ಕಸ್ಟಮ್ ವಿಷನ್ ಸೇವೆಯು REST API ಹೊಂದಿದೆ, ನೀವು ಅದನ್ನು Wio ಟರ್ಮಿನಲ್ ಬಳಸಿ ಚಿತ್ರಗಳನ್ನು ವರ್ಗೀಕರಿಸಲು ಕರೆ ಮಾಡಲು ಸಾಧ್ಯ. ಈ REST API HTTPS ಸಂಪರ್ಕಮೂಲಕ ಪ್ರವೇಶಿಸಲಾಗುತ್ತದೆ - ಇದು ಸುರक्षित HTTP ಸಂಪರ್ಕ.

HTTPS ಎಂಡ್‌ಪಾಯಿಂಟ್‌ಗಳೊಂದಿಗೆ ಕಾರ್ಯನಿರ್ವಹಿಸುವಾಗ, ಕ್ಲೈಂಟ್ ಕೋಡ್ ಪ್ರವೇಶಿಸುತ್ತಿರುವ ಸರ್ವರ್‌ನಿಂದ ಸಾರ್ವಜನಿಕ ಕೀ ಪ್ರಮಾಣಪತ್ರವನ್ನು ವಿನಂತಿಸಬೇಕಾಗಿ ಬರುತ್ತದೆ ಮತ್ತು ಅದನ್ನು ಬಳಸಿ ಟ್ರಾಫಿಕ್ ಅನ್ನು ಎನ್‌ಕ್ರಿಪ್ಟ್ ಮಾಡಬೇಕು. ನಿಮ್ಮ ವೆಬ್ ಬ್ರೌಸರ್ ಇದನ್ನು ಸ್ವಯಂಚಾಲಿತವಾಗಿ ಮಾಡುತ್ತದೆ, ಆದರೆ ಮೈಕ್ರ್ವಕಂಟ್ರೋಲ್ಲರ್‌ಗಳು ಅದು ಮಾಡೋದಿಲ್ಲ. ನೀವು ಈ ಪ್ರಮಾಣಪತ್ರವನ್ನು ಕೈಗಾರಿಕವಾಗಿ ವಿನಂತಿಸಿ REST API ಗೆ ಸುರಕ್ಷಿತ ಸಂಪರ್ಕ ನಿರ್ಮಿಸಲು ಅದನ್ನು ಬಳಸಬೇಕಾಗುತ್ತದೆ. ಈ ಪ್ರಮಾಣಪತ್ರಗಳು ಬದಲಾಗಿಸುವುದಿಲ್ಲ, ಆದ್ದರಿಂದ ಒಮ್ಮೆ ಪ್ರಮಾಣಪತ್ರವನ್ನು ಹೊಂದಿದರೆ, ಅದು ನಿಮ್ಮ ಅನ್ವಯಿಕೆಯಲ್ಲಿ ಹಾರ್ಡ್ ಕೋಡ್ ಆಗಿರಬಹುದು.

ಈ ಪ್ರಮಾಣಿ ಪತ್ರಗಳಲ್ಲಿ ಸಾರ್ವಜನಿಕ ಕೀಲಿಗಳು ಇರುತ್ತವೆ ಮತ್ತು ಅವುಗಳನ್ನು ಸುರಕ್ಷಿತವಾಗಿ ಇರಿಸಬೇಕಾಗಿಲ್ಲ. ನೀವು ಅವರನ್ನು ನಿಮ್ಮ ಮೂಲ ಕೋಡ್‌ನಲ್ಲಿ ಬಳಸಬಹುದು ಮತ್ತು GitHub ಮುಂತಾದ ಸಾರ್ವಜನಿಕ ಸ್ಥಳಗಳಲ್ಲಿ ಹಂಚಿಕೊಳ್ಳಬಹುದು.

### ಕಾರ್ಯ - SSL ಕ್ಲೈಂಟ್ ಸೆಟ್‌ಅಪ್‌ಮಾಡಿ

1. `fruit-quality-detector` ಅಪ್ಲಿಕೇಶನ್ ಪ್ರಾಜೆಕ್ಟ್ ತೆರೆ, ಅದು ಈಗಾಗಲೇ ತೆರೆಯದಿದ್ದರೆ.

1. `config.h` ಹೆಡರ್ ಫೈಲ್ ತೆರೆಯಿರಿ, ಮತ್ತು ಕೆಳಕಂಡವುಗಳನ್ನು ಸೇರಿಸಿ:

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

    ಇದು *Microsoft Azure DigiCert Global Root G2 ಪ್ರಮಾಣಪತ್ರ* - ಇದು ಆಜುರ್ ಸೇವೆಗಳ ಮೂಲಕ ಪ್ರಪಂಚದಾದ್ಯಾಂತ ಬಳಸಲಾಗುವ ಪ್ರಮಾಣಪತ್ರಗಳಲ್ಲಿ ಒಂದಾಗಿದೆ.

    > 💁 ಇದು ಬಳಸಬೇಕಾದ ಪ್ರಮಾಣಪತ್ರ ಇದಾಗಿದೆ ಎಂದು ನೋಡಲು, macOS ಅಥವಾ Linux ನಲ್ಲಿ ಕೆಳಗಿನ ಆಜ್ಞೆಯನ್ನು ಚಲಾಯಿಸಿ. ನೀವು Windows ಬಳಸಿ ಇದ್ದರೆ, ನೀವು ಈ ಆಜ್ಞೆಯನ್ನು [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn) ಬಳಸಿ ಮುಂದುವರಿಸಬಹುದು:
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > ಔಟ್‌ಪುಟ್ DigiCert Global Root G2 ಪ್ರಮಾಣಪತ್ರವನ್ನು ಪಟ್ಟಿ ಮಾಡುತ್ತದೆ.

1. `main.cpp` ತೆರೆಯಿರಿ ಮತ್ತು ಕೆಳಗಿನ ಇನ್ಕ್ಲೂಡ್ ನಿರ್ದೇಶನವನ್ನು ಸೇರಿಸಿ:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. ಇನ್ಕ್ಲೂಡ್ ನಿರ್ದೇಶನಗಳ ಕೆಳಗೆ, `WifiClientSecure` ನ ಒಂದು ಉದಾಹರಣೆಯನ್ನು ಘೋಷಿಸಿ:

    ```cpp
    WiFiClientSecure client;
    ```

    ಈ ವರ್ಗವು HTTPS ಮೂಲಕ ವೆಬ್ ಎಂಡ್‌ಪಾಯಿಂಟ್‌ಗಳೊಂದಿಗೆ ಸಂವಹನ ನಡೆಸಲು ಸಂರಚಿಸಲಾಗಿದೆ.

1. `connectWiFi` ವಿಧಾನದಲ್ಲಿ, WiFiClientSecure ಅನ್ನು DigiCert Global Root G2 ಪ್ರಮಾಣಪತ್ರವನ್ನು ಬಳಸಲು ಸೆಟ್ ಮಾಡಿ:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### ಕಾರ್ಯ - ಚಿತ್ರವನ್ನು ವರ್ಗೀಕರಿಸು

1. `platformio.ini` ಫೈಲ್‌ನ `lib_deps` ಪಟ್ಟಿಗೆ ಕೆಳಗಿನ ಸಾಲನ್ನು ಸೇರಿಸಿ:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    ಇದು [ArduinoJson](https://arduinojson.org) ಅನ್ನು ಆಮದು ಮಾಡುತ್ತದೆ, ಒಂದು ಅರುಡಿನೋ JSON ಗ್ರಂಥಾಲಯ ಮತ್ತು REST API ನಿಂದ JSON ಪ್ರತಿಕ್ರಿಯೆಯನ್ನು ಡಿಕೋಡ್ ಮಾಡಲು ಬಳಸಲಾಗುವುದು.

1. `config.h` ನಲ್ಲಿ, ಕಸ್ಟಮ್ ವಿಷನ್ ಸೇವೆಯಿಂದ ಪೂರ್ವಾನುಮಾನದ URL ಮತ್ತು ಕೀವನ್ನು ಪ್ರತ್ಯೇಕವಾಗಿ ಸ್ಥಿರಾಂಕಗಳಾಗಿ ಸೇರಿಸಿ:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    `<PREDICTION_URL>` ಅನ್ನು ಕಸ್ಟಮ್ ವಿಷನ್‌ನ ಪೂರ್ವಾನುಮಾನದ URL ನಿಂದ ಬದಲಿಸಿ. `<PREDICTION_KEY>` ಅನ್ನು ಪೂರ್ವಾನುಮಾನದ ಕೀಲಿಯನ್ನು ಬದಲಿಸಿ.

1. `main.cpp` ನಲ್ಲಿ, ArduinoJson ಗ್ರಂಥಾಲಯದ ಇನ್ಕ್ಲೂಡ್ ನಿರ್ದೇಶನವನ್ನು ಸೇರಿಸಿ:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `buttonPressed` ಫังก್ಷನ್ ಗೆ ಮೇಲ್ಪಟ್ಟಿದ್ದು, `main.cpp` ಗೆ ಕೆಳಗಿನ ಫังก್ಷನ್ ಅನ್ನು ಸೇರಿಸಿ.

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

    ಈ ಕೋಡ್ ಆರಂಭದಲ್ಲಿ `HTTPClient` ಘೋಷಿಸುತ್ತದೆ - REST API ಗಳೊಂದಿಗೆ ಸಂವಹನ ಮಾಡುವ ವಿಧಾನಗಳನ್ನು ಹೊಂದಿರುವ ವರ್ಗ. ನಂತರ `WiFiClientSecure` ಉದಾಹರಣೆಯನ್ನು ಬಳಸಿ ಆಜುರ್ ಸಾರ್ವಜನಿಕ ಕೀಲಿಯಿಂದ ಸೆಟ್ ಮಾಡಲಾದ ಪೂರ್ವಾನುಮಾನದ URL ಗೆ ಸಂಪರ್ಕ ಹೊಂದುತ್ತದೆ.

    ಸಂಪರ್ಕಗೊಂಡ ಮೇಲೂ, ವಿಷಯದ ಶುಲ್ಕವನ್ನು ಸೂಚಿಸುವವನ್ನು ಒಳಗೊಂಡಂತೆ REST API ಗೆ ಮಾಡುವ ದಾವೆಯ ಕುರಿತು ಮಾಹಿತಿಯನ್ನು ಕಳುಹಿಸಲಾಗುತ್ತದೆ. `Content-Type` ಹೆಡರ್ ಕಚ್ಚಾ ಬೈನರಿ ಡೇಟಾ ಕಳುಹಿಸಲು ಸೂಚಿಸುತ್ತದೆ, ಮತ್ತು `Prediction-Key` ಹೆಡರ್ ಕಸ್ಟಮ್ ವಿಷನ್ ಪೂರ್ವಾನುಮಾನದ ಕೀಲಿಯನ್ನು ಪಾಸ್ ಮಾಡುತ್ತದೆ.

    ನಂತರ, HTTP ಕ್ಲೈಂಟ್ ಗೆ ಬಿಟ್ ಅರೆ ಅನ್ನು ಅಪ್‌ಲೋಡ್ ಮಾಡುವ POST ವಿನಂತಿ ಇಡಲಾಗುತ್ತದೆ. ಇದು ಈ ಫังก್ಷನ್ ಕರೆ ಮಾಡಿದಾಗ ಕ್ಯಾಮೆರಾ ಹಿಡಿದ JPEG ಚಿತ್ರವನ್ನು ಒಳKubmetsAG0D.

    > 💁 POST ವಿನಂತಿಗಳು ಡೇಟಾ ಕಳುಹಿಸುವುದಕ್ಕೆ ಮತ್ತು ಪ್ರತಿಕ್ರಿಯೆ ಪಡೆಯುವುದಕ್ಕೆ ಉದ್ದೇಶಿತ. GET ವಿನಂತಿಗಳು ಡೇಟಾ ತರಲು ಬಳಸಲಾಗುತ್ತವೆ. ನಿಮ್ಮ ವೆಬ್ ಬ್ರೌಸರ್ ವೆಬ್ ಪುಟಗಳನ್ನು ಲೋಡ್ ಮಾಡಲು GET ವಿನಂತಿಗಳನ್ನು ಬಳಸುತ್ತದೆ.

    POST ವಿನಂತಿ ಪ್ರತಿಕ್ರಿಯೆ ಸ್ಥಿತಿ ಕೋಡ್ ಅನ್ನು ಹಿಂತಿರುಗಿಸುತ್ತದೆ. ಇವು ಚೆನ್ನಾಗಿ ವ್ಯಾಖ್ಯಾನಿಸಲ್ಪಟ್ಟ ಮೌಲ್ಯಗಳು, 200 ಅಂದರೆ **OK** - POST ವಿನಂತಿ ಯಶಸ್ವಿಯಾದದ್ದು.

    > 💁 Wikipedia ನ [List of HTTP status codes](https://wikipedia.org/wiki/List_of_HTTP_status_codes) ಪುಟದಲ್ಲಿ ಎಲ್ಲಾ ಪ್ರತಿಕ್ರಿಯೆ ಸ್ಥಿತಿ ಕೋಡ್ ನೋಡಬಹುದು.

    200 ಮರಳಿದರೆ, ಫಲಿತಾಂಶ HTTP ಕ್ಲೈಂಟ್ ನಿಂದ ಓದಲಾಗುತ್ತದೆ. ಇದು REST API ನಿಂದ ಬಂದ ಪಠ್ಯ ಪ್ರತಿಕ್ರಿಯೆ, ಪೂರ್ವಾನುಮಾನದ ಫಲಿತಾಂಶವನ್ನು JSON ದಾಖಲೆ ರೂಪದಲ್ಲಿ ಒಳಗೊಂಡಿದೆ. JSON ಕೆಳಕಂಡ ಹೀಗೆ ಲಭ್ಯವಿದೆ:

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

    ಇಲ್ಲಿ ಪ್ರಮುಖ ಭಾಗ `predictions` ಆರೆ ಇದೆ. ಇದು ಪೂರ್ವಾನುಮಾನದ ಫಲಿತಾಂಶಗಳನ್ನು ಹೊಂದಿದೆ, ಪ್ರತಿಯೊಂದು ಟ್ಯಾಗ್‌ಗೆ ಟ್ಯಾಗ್ ಹೆಸರು ಮತ್ತು ಸಮಭಾವನೆಯೊಂದಿಗೆ ಒಂದು ಎಂಟ್ರಿ ಇದೆ. ಮರಳಿದ ಸಮಭಾವನೆಗಳು ತೇಲುವ ಬಿಂದು ನಂಬಿಕೆಗಳಾಗಿದ್ದು 0-1 ರ ಮಧ್ಯೆ ಇರುತ್ತವೆ, 0 ಅಂದರೆ ಟ್ಯಾಗ್‌ಗೆ ಹೊಂದಿಕೊಳ್ಳಲು 0% ಅವಕಾಶ, ಮತ್ತು 1 ಅಂದರೆ 100% ಅವಕಾಶ.

    > 💁 ಚಿತ್ರ ವರ್ಗೀಕರಣಕಾರರು ಬಳಕೆಯಾದ ಪ್ರತಿಯೊಂದು ಟ್ಯಾಗ್ಗೆ ಶೇಕಡಾವಾರಿಯ ಫಲಿತಾಂಶ ನೀಡುತ್ತಾರೆ. ಪ್ರತಿಯೊಂದು ಟ್ಯಾಗ್‌ಗೆ ಚಿತ್ರ ಹೊಂದಿಕೊಳ್ಳುವ ಸಾಧ್ಯತೆ ಇರುತ್ತದೆ.

    ಈ JSONತ್ಯಾಜ್ಯವಾಗುತ್ತದೆ, ಹಾಗೂ ಪ್ರತಿಯೊಂದು ಟ್ಯಾಗಿನ ಸಮಭಾವನೆಗಳನ್ನು ಸೀರಿಯಲ್ ಮಾನಿಟರ್‌ಗೆ ಕಳುಹಿಸಲಾಗುತ್ತದೆ.

1. `buttonPressed` ಫังก್ಷನ್‌ನಲ್ಲಿ, SD ಕಾರ್ಡ್‌ಗೆ ಸಂಗ್ರಹಿಸುವ ಕೋಡ್ ಅನ್ನು `classifyImage` ಕರೆದಿಂದ ಬದಲಾಯಿಸಬಹುದು ಅಥವಾ ಚಿತ್ರ ಬರೆಯಲಾದ ಬಳಿಕ, ಆದ್ರೆ ಬ್ಯುಫರ್ ಅಳಿಸುವ ಮೊದಲು ಅದನ್ನು ಸೇರಿಸಬಹುದು:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 SD ಕಾರ್ಡ್‌ಗೆ ಸಂಗ್ರಹಿಸುವ ಕೋಡ್ ಅನ್ನು ಬದಲಿಸಿದರೆ, ನೀವು `setupSDCard` ಮತ್ತು `saveToSDCard` ಫังก್ಷನ್ಗಳನ್ನು ತೆಗೆದುಹಾಕಿ ಕೋಡ್ ಕ್ಲೀನ್ ಮಾಡಬಹುದು.

1. ನಿಮ್ಮ ಕೋಡ್ ಅಪ්ಲೋಡ್ ಮಾಡಿ ಮತ್ತು ಚಾಲನೆ ಮಾಡಿ. ಕ್ಯಾಮೆರಾವನ್ನು ಕೆಲವು ಹಣ್ಣಿನತ್ತ ಕೇಂದ್ರೀಕರಿಸಿ C ಬಟನ್ ಒತ್ತಿ. ನೀವು ಅನ್ಯದಲ್ಲಿ ಸರಿಯಾದ ಔಟ್‌ಪುಟ್ ನೋಡಬಹುದು:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    ತೆಗೆದುಕೊಂಡ ಚಿತ್ರವನ್ನು ಮತ್ತು ಈ ಮೌಲ್ಯಗಳನ್ನು ಕಸ್ಟಮ್ ವಿಷನ್‌ನ **Predictions** ಟ್ಯಾಬ್‌ನಲ್ಲಿ ನೋಡಬಹುದು.

    ![ಕಸ್ಟಮ್ ವಿಷನ್‌ನಲ್ಲಿ ಬ Nonetheless ಬಾಳೆಗೆ 56.8% ಮತ್ತು ಬಾಳೆಪುಷ್ಪ ತಳಿ 43.1% ಎಂದು ಭವಿಷ್ಯದ ಸೂಚನೆ](../../../../../translated_images/kn/custom-vision-banana-prediction.30cdff4e1d72db5d.png)

> 💁 ಈ ಕೋಡ್ ಅನ್ನು [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal) ಫೋಲ್ಡರ್‌ನಲ್ಲಿ ಕಾಣಬಹುದು.

😀 ನಿಮ್ಮ ಹಣ್ಣಿನ ಗುಣಮಟ್ಟ ವರ್ಗೀಕರಣಗಾರ ಕಾರ್ಯಕ್ರಮ ಯಶಸ್ವಿಯಾದದ್ದು!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ನಿರಾಕರಣೆ**:  
ಈ ಡಾಕ್ಯುಮೆಂಟ್ ಅನ್ನು AI ಭಾಷಾಂತರ ಸೇವೆ [Co-op Translator](https://github.com/Azure/co-op-translator) ಬಳಸಿ ಭಾಷಾಂತರಿಸಲಾಗಿದೆ. ನಾವು ಶುದ್ಧತೆಗಾಗಿ ಪ್ರಯತ್ನಿಸುತ್ತಿದ್ದರೂ, ಸ್ವಯಂಚಾಲಿತ ಭಾಷಾಂತರಗಳಲ್ಲಿ ತಪ್ಪುಗಳು ಅಥವಾ ಅಸಮಾರಂಭತೆಗಳು ಇರುವ ಸಾಧ್ಯತೆ ಇದೆ ಎಂದು ದಯವಿಟ್ಟು ಗಮನಿಸಿ. ಮೂಲ ಭಾಷೆಯಲ್ಲಿ ಇರುವ ಮೂಲ ಡಾಕ್ಯುಮೆಂಟ್ ಅನ್ನು ಅಧಿಕೃತ מקורವಾಗಿ ಪರಿಗಣಿಸಬೇಕು. ಮಹತ್ವপূর্ণ ಮಾಹಿತಿಗಾಗಿ, ವೃತ್ತಿಪರ ಮಾನವ ಭಾಷಾಂತರವನ್ನು ಶಿಫಾರಸು ಮಾಡಲಾಗುತ್ತದೆ. ಈ ಭಾಷಾಂತರವನ್ನು ಬಳಸಿಕೊಳ್ಳುವಾಗ ಉಂಟಾಗಬಂದಿರುವ ಯಾವುದಾದರೂ ತಪ್ಪು ಅರ್ಥಗಳಿಗಾಗಿ ನಾವು ಹೊಣೆಗಾರರಾಗಿರುವುದಿಲ್ಲ.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->