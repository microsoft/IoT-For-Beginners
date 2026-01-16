<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-27T21:00:29+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "sw"
}
-->
# Tambua picha - Wio Terminal

Katika sehemu hii ya somo, utatuma picha iliyokamatwa na kamera kwa huduma ya Custom Vision ili kuitambua.

## Tambua picha

Huduma ya Custom Vision ina API ya REST unayoweza kuitumia kutoka kwa Wio Terminal kutambua picha. API hii ya REST inapatikana kupitia muunganisho wa HTTPS - muunganisho salama wa HTTP.

Unaposhirikiana na sehemu za mwisho za HTTPS, msimbo wa mteja unahitaji kuomba cheti cha ufunguo wa umma kutoka kwa seva inayofikiwa, na kutumia cheti hicho kusimba trafiki inayotumwa. Kivinjari chako cha wavuti hufanya hili kiotomatiki, lakini microcontrollers hazifanyi hivyo. Utahitaji kuomba cheti hiki mwenyewe na kukitumia kuunda muunganisho salama kwa API ya REST. Vyeti hivi havibadiliki, kwa hivyo mara unapokuwa na cheti, kinaweza kuwekwa moja kwa moja kwenye programu yako.

Vyeti hivi vina funguo za umma, na havihitaji kuhifadhiwa kwa usalama. Unaweza kuvitumia katika msimbo wako wa chanzo na kuvishiriki hadharani kwenye maeneo kama GitHub.

### Kazi - weka mteja wa SSL

1. Fungua mradi wa programu ya `fruit-quality-detector` ikiwa haujafunguliwa tayari.

1. Fungua faili ya kichwa `config.h`, na ongeza yafuatayo:

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

    Hii ni *Microsoft Azure DigiCert Global Root G2 certificate* - ni moja ya vyeti vinavyotumiwa na huduma nyingi za Azure duniani.

    > 💁 Ili kuona kwamba hiki ndicho cheti cha kutumia, endesha amri ifuatayo kwenye macOS au Linux. Ikiwa unatumia Windows, unaweza kuendesha amri hii ukitumia [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Matokeo yatataja cheti cha DigiCert Global Root G2.

1. Fungua `main.cpp` na ongeza agizo la kujumuisha:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Chini ya maagizo ya kujumuisha, tangaza mfano wa `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Darasa hili lina msimbo wa kuwasiliana na sehemu za mwisho za wavuti kupitia HTTPS.

1. Katika njia ya `connectWiFi`, weka WiFiClientSecure kutumia cheti cha DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Kazi - tambua picha

1. Ongeza mstari ufuatao kama mstari wa ziada kwenye orodha ya `lib_deps` katika faili ya `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Hii inaingiza [ArduinoJson](https://arduinojson.org), maktaba ya JSON ya Arduino, na itatumika kufafanua majibu ya JSON kutoka kwa API ya REST.

1. Katika `config.h`, ongeza vigezo vya URL ya utabiri na Key kutoka kwa huduma ya Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Badilisha `<PREDICTION_URL>` na URL ya utabiri kutoka Custom Vision. Badilisha `<PREDICTION_KEY>` na ufunguo wa utabiri.

1. Katika `main.cpp`, ongeza agizo la kujumuisha maktaba ya ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Ongeza kazi ifuatayo kwa `main.cpp`, juu ya kazi ya `buttonPressed`.

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

    Msimbo huu huanza kwa kutangaza `HTTPClient` - darasa linalo na mbinu za kushirikiana na API za REST. Kisha linaunganisha mteja na URL ya utabiri ukitumia mfano wa `WiFiClientSecure` uliowekwa na ufunguo wa umma wa Azure.

    Mara baada ya kuunganishwa, hutuma vichwa - taarifa kuhusu ombi linalokuja ambalo litatolewa dhidi ya API ya REST. Kichwa cha `Content-Type` kinaonyesha kwamba ombi la API litatuma data ya binary ghafi, kichwa cha `Prediction-Key` kinapitisha ufunguo wa utabiri wa Custom Vision.

    Kisha ombi la POST linatolewa kwa mteja wa HTTP, likipakia safu ya byte. Hii itakuwa na picha ya JPEG iliyokamatwa kutoka kwa kamera wakati kazi hii inaitwa.

    > 💁 Ombi la POST linakusudiwa kutuma data, na kupata majibu. Kuna aina nyingine za maombi kama maombi ya GET ambayo hupata data. Maombi ya GET hutumiwa na kivinjari chako cha wavuti kupakia kurasa za wavuti.

    Ombi la POST linarejesha msimbo wa hali ya majibu. Hizi ni thamani zilizoainishwa vizuri, na 200 ikimaanisha **OK** - ombi la POST lilifanikiwa.

    > 💁 Unaweza kuona misimbo yote ya hali ya majibu katika [Ukurasa wa Orodha ya Msimbo wa Hali ya HTTP kwenye Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Ikiwa 200 inarejeshwa, matokeo yanasomwa kutoka kwa mteja wa HTTP. Hii ni majibu ya maandishi kutoka kwa API ya REST na matokeo ya utabiri kama hati ya JSON. JSON iko katika muundo ufuatao:

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

    Sehemu muhimu hapa ni safu ya `predictions`. Hii ina utabiri, na ingizo moja kwa kila tagi likiwa na jina la tagi na uwezekano. Uwezekano uliorejeshwa ni nambari za pointi za kuelea kutoka 0-1, na 0 ikiwa na nafasi ya 0% ya kulingana na tagi, na 1 ikiwa na nafasi ya 100%.

    > 💁 Watabiri wa picha watarudisha asilimia kwa tagi zote ambazo zimetumika. Kila tagi itakuwa na uwezekano kwamba picha inalingana na tagi hiyo.

    JSON hii inafafanuliwa, na uwezekano kwa kila tagi unatumwa kwa monitor ya serial.

1. Katika kazi ya `buttonPressed`, badilisha msimbo unaohifadhi kwenye kadi ya SD na wito kwa `classifyImage`, au ongeza baada ya picha kuandikwa, lakini **kabla** ya buffer kufutwa:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Ikiwa unabadilisha msimbo unaohifadhi kwenye kadi ya SD unaweza kusafisha msimbo wako kwa kuondoa kazi za `setupSDCard` na `saveToSDCard`.

1. Pakia na endesha msimbo wako. Elekeza kamera kwenye matunda na bonyeza kitufe cha C. Utaona matokeo kwenye monitor ya serial:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Utaweza kuona picha iliyochukuliwa, na maadili haya katika kichupo cha **Predictions** kwenye Custom Vision.

    ![Ndizi katika Custom Vision iliyotabiriwa kuwa imeiva kwa 56.8% na haijaiva kwa 43.1%](../../../../../translated_images/sw/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Unaweza kupata msimbo huu katika folda ya [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Programu yako ya kutambua ubora wa matunda imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.