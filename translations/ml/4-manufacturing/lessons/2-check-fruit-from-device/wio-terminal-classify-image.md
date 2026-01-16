<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2026-01-07T06:36:32+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "ml"
}
-->
# ഒരു ചിത്രം വർഗീകരിക്കുക - Wio ടെർമിനൽ

പാഠത്തിന്റെ ഈ ഭാഗത്തിൽ, ക്യാമറ പിടിച്ച ചിത്രాన్ని Custom Vision സേവനത്തിലേക്ക് അയച്ച് അത് വർഗീകരിക്കും.

## ഒരു ചിത്രം വർഗീകരിക്കുക

Custom Vision സേവനത്തിന് REST API ഉണ്ട് എന്ന് നിങ്ങൾക്ക് Wio ടെർമിനൽ ഉപയോഗിച്ച് വിളിച്ച് ചിത്രങ്ങൾ വർഗീകരിക്കാൻ കഴിയും. ഈ REST API HTTPS കണക്ഷൻ വഴിയാണ് ആക്സസ് ചെയ്യുന്നത് - സുരക്ഷിത HTTP കണക്ഷൻ.

HTTPS എൻഡ്‌പോയിന്റുകളുമായി ഇടപഴകുമ്പോൾ, ക്ലയൻറ് കോഡ് ആക്സസ് ചെയ്യുന്നതിനുള്ള സർവറിൽ നിന്നുള്ള പൊതു കി സർട്ടിഫിക്കറ്റ് അഭ്യർത്ഥിക്കേണ്ടതുണ്ട്, അതുപയോഗിച്ച് അയക്കുന്ന ട്രാഫിക് എൻക്രിപ്റ്റ് ചെയ്യണം. നിങ്ങളുടെ വെബ് ബ്രൗസർ ഇത് സ്വയം ചെയ്യുന്നു, പക്ഷേ മൈക്രോകൺട്രോളറുകൾ അത്രമാത്രം റോബസ്റ്റ് അല്ല. നിങ്ങൾക്ക് ഈ സർട്ടിഫിക്കറ്റ് മാനുൽ ആയി അഭ്യർത്ഥിച്ച് REST API-യുമായി സുരക്ഷിത കണക്ഷൻ സൃഷ്ടിക്കാൻ ഇത് ഉപയോഗിക്കണം. ഈ സർട്ടിഫിക്കറ്റുകൾ മാറാറില്ല, അതിനാൽ ഒരു സർട്ടിഫിക്കറ്റ് ലഭിച്ചാൽ, നിങ്ങളുടെ ആപ്ലിക്കേഷനിൽ ഹാർഡ് കോഡ് ചെയ്യാവുന്നതാണ്.

ഈ സർട്ടിഫിക്കറ്റുകൾ പൊതു കീകൾ ഉൾക്കൊള്ളുന്നു, അതിനാൽ അവ സുരക്ഷിതമായി സൂക്ഷിക്കേണ്ടതില്ല. നിങ്ങൾക്ക് അവ നിങ്ങളുടെ സോഴ്‌സ് കോഡിൽ ഉപയോഗിക്കാം, ഗിറ്റ്ഹബിന് പോലുള്ള പൊതുവേദികളിൽ പങ്കിടാനും കഴിയും.

### ടാസ്‌ക് - SSL ക്ലയർന്റ് സെറ്റപ്പ് ചെയ്യുക

1. `fruit-quality-detector` ആപ്പ് പ്രോജക്ട് തുറക്കപ്പെട്ടിട്ടില്ലെങ്കിൽ തുറക്കുക.

1. `config.h` ഹെഡർ ഫയൽ തുറന്ന് താഴെ കാണിക്കുന്നതു ചേർക്കുക:

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

    ഇത് *Microsoft Azure DigiCert Global Root G2 സർട്ടിഫിക്കറ്റ്* ആണ് - ഇത് ആഗോളമായി പല Azure സേവനങ്ങളാൽ ഉപയോഗിച്ചുകൊണ്ടിരിക്കുന്ന സർട്ടിഫിക്കറ്റുകളിൽ ഒന്ന്.

    > 💁 ഇത് ഉപയോഗിക്കേണ്ട സർട്ടിഫിക്കറ്റാണെന്ന് ഉറപ്പാക്കാൻ, macOS അല്ലെങ്കിൽ Linux-ൽ താഴെ കാണിച്ച കമാൻഡ് ഓടിക്കുക. Windows ഉപയോഗിച്ചാൽ [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn) ഉപയോഗിച്ച് കമാൻഡ് ഓടിക്കാം:
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > ഔട്ട്‌പുട്ടിൽ DigiCert Global Root G2 സർട്ടിഫിക്കറ്റ് കാണും.

1. `main.cpp` തുറന്ന് താഴെ കാണിക്കുന്ന ഇൻക്ലൂഡ് നിർദ്ദേശം ചേർക്കുക:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. ഇൻക്ലൂഡ് നിർദ്ദേശങ്ങളുടെ താഴെ, `WifiClientSecure` എന്ന ഇൻസ്റ്റൻസ് പ്രഖ്യാപിക്കുക:

    ```cpp
    WiFiClientSecure client;
    ```

    ഈ ക്ലാസ് HTTPS വഴി വെബ് എൻഡ്‌പോയിന്റുകളുമായി ആശയവിനിമയം നടത്താൻ വേണ്ടിയുള്ള കോഡ് ഉൾക്കൊള്ളുന്നു.

1. `connectWiFi` മെതഡിൽ, DigiCert Global Root G2 സർട്ടിഫിക്കറ്റ് ഉപയോഗിക്കുന്നതിന് WiFiClientSecure സെറ്റ് ചെയ്യുക:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### ടാസ്‌ക് - ഒരു ചിത്രം വർഗീകരിക്കുക

1. `platformio.ini` ഫയലിലെ `lib_deps` ലിസ്റ്റിലേക്ക് താഴെ കാണിച്ച വരി ചേർക്കുക:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    ഇത് [ArduinoJson](https://arduinojson.org) എന്ന Arduino JSON ലൈബ്രറിയെ ഇറക്കുമതി ചെയ്യുന്നു, REST API-യിൽ നിന്നുള്ള JSON പ്രതികരണം ഡീകോഡ് ചെയ്യാനായി ഇത് ഉപയോഗിക്കും.

1. `config.h` ൽ Custom Vision സേവനത്തിന്റെ പ്രെഡിക്ഷൻ URLനും കീയും ആയി സെറ്റിംഗ് കോൺസ്റ്റന്റ്സ് ചേർക്കുക:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    `<PREDICTION_URL>` എന്നത് Custom Vision-ൽ നിന്നുള്ള പ്രെഡിക്ഷൻ URL-ഓപായി മാറ്റുക. `<PREDICTION_KEY>` എന്നത് പ്രെഡിക്ഷൻ കീയോട് മാറ്റുക.

1. `main.cpp` ൽ ArduinoJson ലൈബ്രറിയുടെ ഇൻക്ലൂഡ് നിർദ്ദേശം ചേർക്കുക:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `main.cpp`ൽ, `buttonPressed` ഫംഗ്ഷനിനു മുകളിൽ താഴെ കാണുന്ന ഫംഗ്ഷൻ ചേർക്കുക:

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

    ഈ കോഡ് ആദ്യം `HTTPClient` പ്രഖ്യാപിച്ച് REST API-കളുമായി ഇടപഴകാനുള്ള മെതഡുകൾ ഉള്ള ക്ലാസ്സാണ്. ശേഷം ഈ ക്ലയന്റിനെ Azure പൊതു കീ ഉപയോഗിച്ച് സെറ്റ് ചെയ്ത `WiFiClientSecure` ഇൻസ്റ്റൻസ് ഉപയോഗിച്ച് പ്രെഡിക്ഷൻ URL-തോട് കണക്റ്റുചെയ്യുന്നു.

    കണക്റ്റ് ചെയ്തശേഷം, REST API-യുടെ അടുത്തുള്ള അഭ്യർത്ഥനയിൽ പ്രധാനപ്പെട്ട ഹെഡറുകൾ അയക്കുന്നു. `Content-Type` ഹെഡർ അപ്ലോഡ് ചെയ്യാനിരിക്കുന്ന ഡാറ്റ റോയി ബൈനറി ഡാറ്റയാണ് എന്നാണ് സൂചന നൽകുന്നു, `Prediction-Key` ഹെഡർ Custom Vision പ്രെഡിക്ഷൻ കീ നൽകുന്നു.

    പിന്നീട് HTTP ക്ലയന്റിലേക്ക് POST അഭ്യർത്ഥനയുമായി ഒരു ബൈറ്റു അരെ അപ്‌ലോഡു ചെയ്യുന്നു. ഈ ബൈറ്റു അരെ ക്യാമറ പിടിച്ച JPEG ഇമേജ് ആണ്, ഈ ഫംഗ്ഷൻ വിളിക്കുമ്പോൾ.

    > 💁 POST അഭ്യർത്ഥനകൾ ഡാറ്റ അയയ്ക്കാനും അതിന്റെ മറുപടി ലഭിക്കാനുമാണ്. GET പോലുള്ള മറ്റ് അഭ്യർത്ഥന തരങ്ങളും ഉണ്ട്, അവ ഡാറ്റ വീതിപ്പ് ചെയ്യാനാണ് ഉപയോഗിക്കുന്നത്. വെബ് പേജുകൾ ലോഡ് ചെയ്യാനായി നിങ്ങളുടെ വെബ് ബ്രൗസർ GET അഭ്യർത്ഥനകൾ ഉപയോഗിക്കുന്നു.

    POST അഭ്യർത്ഥന ഒരു സ്റ്റാറ്റസ് കോഡ് തിരികെ നൽകും. ഇവ വ്യക്തമായി നിർവചിക്കപ്പെട്ട മൂല്യങ്ങളാണ്, 200 എന്നത് **ശരി** എന്നാണ് സൂചിപ്പിക്കുന്നത് - POST അഭ്യർത്ഥന വിജയകരമായി പൂർത്തിയായതെന്ന്.

    > 💁 എല്ലാ പ്രതികരണ സ്റ്റാറ്റസ് കോഡുകളും [List of HTTP status codes page on Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)-ൽ കാണാം

    200 ലഭിച്ചാൽ, ഫലം HTTP client-ൽ നിന്ന് വായിക്കുന്നു. ഇത് REST API-യിൽ നിന്നുള്ള JSON പ്രമാണം ആകുന്ന ടെക്സ്റ്റ് മറുപടിയാണ്. JSON താഴെ കൂടെ这样 ഉണ്ട്:

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

    പ്രധാനഭാഗം ഇതാണ്: `predictions` അറേ. ഇതിൽ ഓരോ ടാഗിനും ഒന്ന് ഓരോ എൻട്രി ഉണ്ട്, ടാഗിന്റെ പേര്, സാധ്യതയുടെ സാന്ദ്രതയോടെ. സാധ്യതകൾ 0 മുതൽ 1 വരെയുള്ള ഫ്ലോട്ടിംഗ് പോയിന്റ് സംഖ്യകൾ ആണ്, 0 അർത്ഥം 0% സാധ്യത ടാഗ് പൊരുമെന്നാണ്, 1 അർത്ഥം 100% സാധ്യത.

    > 💁 ഇമേജ് ക്ലാസിഫയറുകൾ ഉപയോ‌ഗിച്ച എല്ലാ ടാഗുകൾക്കും സാന്ദ്രത ശതമാനങ്ങൾ നൽകും. ഓരോ ടാഗിനും ചിത്രം ആ ടാഗിനോട് പൊരുക്കമുണ്ടെന്ന സാധ്യത ഉണ്ട്.

    JSON ഡീകോഡ് ചെയ്യപ്പെടുന്നു, ടാഗുകളുടെ സാധ്യതകൾ സീരിയൽ മോണിറ്ററിലേക്ക് അയക്കുന്നു.

1. `buttonPressed` ഫംഗ്ഷനിൽ, SD കാർഡിൽ സേവ് ചെയ്യുന്ന കോഡ് പകരം `classifyImage` ഫംഗ്ഷൻ വിളിക്കുക അല്ലെങ്കിൽ ചിത്രം എഴുതിയതിനുശേഷം, പക്ഷേ ബഫർ ഡിലീറ്റ് ചെയ്യുന്നതിനു **മുമ്പ്** ചേർക്കുക:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 SD കാർഡിൽ സേവ് ചെയ്യുന്ന കോഡ് മാറ്റിയാൽ `setupSDCard` ആയും `saveToSDCard` ഫംഗ്ഷനുകളും കോഡിൽ നിന്നും ഒഴിവാക്കിയാൽ ഇടപാടുക്കുന്നു.

1. നിങ്ങളുടെ കോഡ് അപ്‌ലോഡ് ചെയ്ത് റൺ ചെയ്യുക. ക്യാമറ ഒരു പഴം തിരിച്ചറിയാൻ നിങ്ങളെ സഹായിക്കും, C ബട്ടൺ അമർത്തുക. സീരിയൽ മോണിറ്ററിൽ ഔട്ട്‌പുട്ട് കാണാം:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    എടുത്ത ചിത്രം കാണാനും, Custom Vision-ൽ **Predictions** ടാബിൽ ഈ മൂല്യങ്ങളും കാണാനാകും.

    ![A banana in custom vision predicted ripe at 56.8% and unripe at 43.1%](../../../../../translated_images/ml/custom-vision-banana-prediction.30cdff4e1d72db5d.png)

> 💁 ഈ കോഡ് [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal) ഫോളഡറിൽ കണ്ടെത്താവുന്നതാണ്.

😀 നിങ്ങളുടെ പഴം ഗുണനിലവാര ക്ലാസിഫയർ പ്രോഗ്രാം വിജയകരമായി പൂർത്തിയായി!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**അസാധാരണ രേഖ**:
ഈ രേഖ AI വിവർത്തന സേവനം [കോ-ഓപ് ട്രാൻസ്ലേറ്റർ](https://github.com/Azure/co-op-translator) ഉപയോഗിച്ച് വിവർത്തനം ചെയ്തതാണ്. നാം കൃത്യത ലക്ഷ്യമിടുമ്പോഴും, കോഡും വിവർത്തനങ്ങളിലും പിഴവുകൾ അല്ലെങ്കിൽ തെറ്റുകൾ ഉണ്ടാകാവുന്നതാണ്. ഇതിന്റെ ചട്ടപ്രകാരം യഥാർത്ഥ ഭാഷയിലുള്ള പ്രസ്താവനയാണ് സത്യവാങ്മൂലം. പ്രധാന വിവരങ്ങൾക്കായി പ്രൊഫഷണൽ മാനവ വിവർത്തനം ഉപദേശിക്കുന്നു. ഈ വിവർത്തനം ഉപയോഗിക്കുന്നതിൽ നിന്നുള്ള തെറ്റിദ്ധാരണകൾക്കോ തെറ്റായ വ്യാഖ്യാനങ്ങൾക്കോ ഞങ്ങൾ ഉത്തരവാദിത്വം വഹിക്കുന്നില്ല.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->