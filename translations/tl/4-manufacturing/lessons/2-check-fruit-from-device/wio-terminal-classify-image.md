<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-27T21:02:30+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "tl"
}
-->
# Magklasipika ng Imahe - Wio Terminal

Sa bahaging ito ng aralin, ipapadala mo ang imahe na kinunan ng camera sa Custom Vision service upang ma-klasipika ito.

## Magklasipika ng Imahe

Ang Custom Vision service ay may REST API na maaaring tawagan mula sa Wio Terminal upang magklasipika ng mga imahe. Ang REST API na ito ay ina-access gamit ang HTTPS connection - isang secure na HTTP connection.

Kapag nakikipag-ugnayan sa HTTPS endpoints, kailangang humiling ang client code ng pampublikong key certificate mula sa server na ina-access, at gamitin ito upang i-encrypt ang traffic na ipinapadala. Ginagawa ito ng iyong web browser nang awtomatiko, ngunit hindi ito ginagawa ng mga microcontroller. Kailangan mong manu-manong humiling ng certificate at gamitin ito upang lumikha ng secure na koneksyon sa REST API. Ang mga certificate na ito ay hindi nagbabago, kaya kapag mayroon ka na nito, maaari itong i-hard code sa iyong application.

Ang mga certificate na ito ay naglalaman ng mga pampublikong key, at hindi kailangang panatilihing ligtas. Maaari mo itong gamitin sa iyong source code at ibahagi ito sa publiko sa mga lugar tulad ng GitHub.

### Gawain - I-set up ang SSL client

1. Buksan ang proyekto ng `fruit-quality-detector` app kung hindi pa ito bukas.

1. Buksan ang `config.h` header file, at idagdag ang sumusunod:

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

    Ito ang *Microsoft Azure DigiCert Global Root G2 certificate* - isa ito sa mga certificate na ginagamit ng maraming Azure services sa buong mundo.

    > 💁 Upang makita na ito ang certificate na gagamitin, patakbuhin ang sumusunod na command sa macOS o Linux. Kung gumagamit ka ng Windows, maaari mong patakbuhin ang command na ito gamit ang [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Ang output ay magpapakita ng DigiCert Global Root G2 certificate.

1. Buksan ang `main.cpp` at idagdag ang sumusunod na include directive:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Sa ibaba ng mga include directives, ideklara ang isang instance ng `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Ang class na ito ay naglalaman ng code upang makipag-ugnayan sa mga web endpoint gamit ang HTTPS.

1. Sa `connectWiFi` method, i-set ang WiFiClientSecure upang gamitin ang DigiCert Global Root G2 certificate:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Gawain - Magklasipika ng Imahe

1. Idagdag ang sumusunod bilang karagdagang linya sa `lib_deps` list sa `platformio.ini` file:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Ina-import nito ang [ArduinoJson](https://arduinojson.org), isang Arduino JSON library, na gagamitin upang i-decode ang JSON response mula sa REST API.

1. Sa `config.h`, magdagdag ng constants para sa prediction URL at Key mula sa Custom Vision service:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Palitan ang `<PREDICTION_URL>` ng prediction URL mula sa Custom Vision. Palitan ang `<PREDICTION_KEY>` ng prediction key.

1. Sa `main.cpp`, magdagdag ng include directive para sa ArduinoJson library:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Idagdag ang sumusunod na function sa `main.cpp`, sa itaas ng `buttonPressed` function.

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

    Nagsisimula ang code sa pagdeklara ng `HTTPClient` - isang class na naglalaman ng mga method upang makipag-ugnayan sa REST APIs. Pagkatapos, ikinokonekta nito ang client sa prediction URL gamit ang `WiFiClientSecure` instance na na-set up gamit ang Azure public key.

    Kapag nakakonekta na, nagpapadala ito ng headers - impormasyon tungkol sa paparating na request na gagawin laban sa REST API. Ang `Content-Type` header ay nagpapahiwatig na ang API call ay magpapadala ng raw binary data, ang `Prediction-Key` header ay nagpapasa ng Custom Vision prediction key.

    Susunod, isang POST request ang ginagawa sa HTTP client, ina-upload ang byte array. Ito ay maglalaman ng JPEG image na kinunan mula sa camera kapag tinawag ang function na ito.

    > 💁 Ang POST request ay para sa pagpapadala ng data, at pagkuha ng response. May iba pang uri ng request tulad ng GET requests na kumukuha ng data. Ang GET requests ay ginagamit ng iyong web browser upang mag-load ng mga web page.

    Ang POST request ay nagbabalik ng response status code. Ang mga ito ay well-defined values, kung saan ang 200 ay nangangahulugang **OK** - matagumpay ang POST request.

    > 💁 Makikita mo ang lahat ng response status codes sa [List of HTTP status codes page on Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Kung ang 200 ay naibalik, binabasa ang resulta mula sa HTTP client. Ito ay isang text response mula sa REST API na may mga resulta ng prediction bilang isang JSON document. Ang JSON ay nasa sumusunod na format:

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

    Ang mahalagang bahagi dito ay ang `predictions` array. Naglalaman ito ng mga prediction, na may isang entry para sa bawat tag na naglalaman ng tag name at probability. Ang probabilities na ibinabalik ay floating point numbers mula 0-1, kung saan ang 0 ay nangangahulugang 0% chance na tumugma sa tag, at ang 1 ay nangangahulugang 100% chance.

    > 💁 Ang mga image classifier ay magbabalik ng percentages para sa lahat ng tag na ginamit. Ang bawat tag ay magkakaroon ng probability na ang imahe ay tumutugma sa tag na iyon.

    Ang JSON ay na-decode, at ang probabilities para sa bawat tag ay ipinapadala sa serial monitor.

1. Sa `buttonPressed` function, palitan ang code na nagse-save sa SD card ng tawag sa `classifyImage`, o idagdag ito pagkatapos ng imahe ay naisulat, ngunit **bago** ang buffer ay na-delete:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Kung papalitan mo ang code na nagse-save sa SD card, maaari mong linisin ang iyong code sa pamamagitan ng pag-alis ng `setupSDCard` at `saveToSDCard` functions.

1. I-upload at patakbuhin ang iyong code. Itutok ang camera sa ilang prutas at pindutin ang C button. Makikita mo ang output sa serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Makikita mo ang imahe na kinunan, at ang mga values na ito sa **Predictions** tab sa Custom Vision.

    ![Isang saging sa custom vision na na-predict na hinog sa 56.8% at hilaw sa 43.1%](../../../../../translated_images/tl/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Makikita mo ang code na ito sa [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal) folder.

😀 Tagumpay ang iyong fruit quality classifier program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.