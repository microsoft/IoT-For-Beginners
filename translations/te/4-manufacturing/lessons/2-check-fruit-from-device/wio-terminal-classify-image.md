<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2026-01-07T06:35:46+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "te"
}
-->
# ఒక చిత్రం వర్గీకరించండి - Wio Terminal

పాఠం ఈ భాగంలో, మీరు కెమెరా ద్వారా పొందిన చిత్రాన్ని కస్టమ్ విజన్ సర్వీస్కు పంపించి దాన్ని వర్గీకరిస్తారు.

## ఒక చిత్రం వర్గీకరించండి

కస్టమ్ విజన్ సేవకు REST API ఉంది, ఇది మీరు Wio Terminal నుండి పిలవవచ్చు చిత్రాలను వర్గీకరించేందుకు. ఈ REST API ను HTTPS కనెక్షన్ ద్వారా యాక్సెస్ చేస్తారు - ఇది సురక్షిత HTTP కనెక్షన్.

HTTPS ఎండ్‌పాయింట్లతో అంతర్రియోజనాన్ని నిర్వహించినప్పుడు, క్లయింట్ కోడ్ యాక్సెస్ చేస్తున్న సర్వర్ నుండి పబ్లిక్ కీ సర్టిఫికేట్‌ను కోరాలి, మరియు దానిని ట్రాఫిక్ ఎన్క్రిప్ట్ చేయడానికి ఉపయోగించాలి. మీ వెబ్ బ్రౌజర్ ఇది ఆటోమేటిక్‌గా చేస్తుంది, కానీ మైక్రోకంట్రోలర్లు చేయవు. మీరు ఈ సర్టిఫికేట్‌ను మానువల్‌గా కోరాలి మరియు దానిని ఉపయోగించి REST API కు సురక్షిత కనెక్షన్ సృష్టించాలి. ఈ సర్టిఫికెట్లు మారవు, కాబట్టి ఒకసారి మీకు సర్టిఫికేట్ ఉంటే, దీన్ని మీ అప్లికేషన్‌లో హార్డ్ కోడ్ చేయొచ్చు.

ఈ సర్టిఫికెట్లు పబ్లిక్ కీలు కలిగి ఉంటాయి, మరియు సురక్షితంగా ఉంచాల్సిన అవసరం లేదు. మీరు వాటిని మీ సోర్స్ కోడ్‌లో ఉపయోగించి, GitHub వంటి ప్రదేశాల్లో పబ్లిక్‌గా పంచుకోవచ్చు.

### కార్యం - SSL క్లయింట్ సెటప్ చేయండి

1. మీరు ముందే తెరవకపోతే `fruit-quality-detector` యాప్ ప్రాజెక్టును తెరువండి.

1. `config.h` హెడ్డర్ ఫైల్ ను తెరువు, మరియు క్రింది కోడ్‌ను చేర్చండి:

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

    ఇది *Microsoft Azure DigiCert Global Root G2 సర్టిఫికేట్* - ఇది ప్రపంచవ్యాప్తంగా అనేక Azure సేవల ద్వారా ఉపయోగించబడే సర్టిఫికెట్లలో ఒకటి.

    > 💁 దీన్ని ఉపయోగించాల్సిన సర్టిఫికేట్ అని చూస్తావాలంటే, macOS లేదా Linux లో క్రింది ఆజ్ఞను నడిపి చూడండి. మీరు Windows ఉపయోగిస్తుంటే, ఈ ఆజ్ఞను [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn) ఉపయోగించి నడుపవచ్చు:
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > అవుట్‌పుట్ DigiCert Global Root G2 సర్టిఫికేట్‌ను జాబితా చేస్తుంది.

1. `main.cpp` తెరిచి క్రింది ఇన్‌క్లూడ్ డైరెక్టివ్‌ను జత చేయండి:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. ఇన్‌క్లూడ్ డైరెక్టివ్‌ల క్రింద, `WifiClientSecure` అనే ఉదాహరణను ప్రకటన చేయండి:

    ```cpp
    WiFiClientSecure client;
    ```

    ఈ క్లాస్ HTTPS ద్వారా వెబ్ ఎండ్‌పాయింట్లతో కమ్యూనికేట్ చేయడానికి కోడ్ కలిగి ఉంటుంది.

1. `connectWiFi` పద్ధతిలో, WiFiClientSecureను DigiCert Global Root G2 సర్టిఫికేట్ ఉపయోగించేలా సెట్ చేయండి:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### కార్యం - ఒక చిత్రాన్ని వర్గీకరించండి

1. `platformio.ini` ఫైల్ లో `lib_deps` జాబితాకు క్రింది లైన్‌ను అదనంగా చేర్చండి:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    ఇది [ArduinoJson](https://arduinojson.org) ను దిగుమతి చేస్తుంది, ఇది ఒక Arduino JSON లైబ్రరీ, REST API నుండి JSON స్పందనను డీకోడ్ చేయడానికి ఉపయోగించబడుతుంది.

1. `config.h` లో, కస్టమ్ విజన్ సేవ నుండి ప్రిడిక్షన్ URL మరియు కీకి సంబంధించిన కాంస్టెంట్‌లు జత చేయండి:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    `<PREDICTION_URL>`ని Custom Vision నుండి పొందిన ప్రిడిక్షన్ URLతో మార్చండి. `<PREDICTION_KEY>`ని ప్రిడిక్షన్ కీస్‌తో స్థానాపించండి.

1. `main.cpp` లో, ArduinoJson లైబ్రరీ కోసం ఒక ఇన్‌క్లూడ్ డైరెక్టివ్ జత చేయండి:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `buttonPressed` ఫంక్షన్ ముందు `main.cpp` లో క్రింది ఫంక్షన్‌ను జత చేయండి.

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

    ఈ కోడ్ `HTTPClient`ను డిక్లేర్ చేయడం నుండి ప్రారంభం అవుతుంది - ఇది REST APIలతో ఇంటరాక్ట్ చేసే మెథడ్స్ కలిగివుంటుంది. తర్వాత ఇది Azure పబ్లిక్ కీతో సెటప్ చేసిన `WiFiClientSecure` ఉదాహారణను ఉపయోగించి ప్రిడిక్షన్ URLకి క్లయింట్ కనెక్ట్ చేస్తుంది.

    కనెక్ట్ అయిన తర్వాత, ఇది హెడ్డర్లు పంపుతుంది - REST APIకి చేయవలసిన రిక్వెస్ట్ గురించి సమాచారం. `Content-Type` హెడ్డర్ API కాల్ రా బైనరీ డేటా పంపడం చూపిస్తుంది, `Prediction-Key` హెడ్డర్ Custom Vision ప్రిడిక్షన్ కీని అందజేస్తుంది.

    తరువాత, HTTP క్లయింట్‌కు POST రిక్వెస్ట్ పంపబడుతుంది, ఇది బైట్ అర్రేను అప్‌లోడ్ చేస్తుంది. ఈ బైట్ అర్రే కెమెరా ద్వారా తీసిన JPEG చిత్రాన్ని కలిగి ఉంటుంది, ఈ ఫంక్షన్ పిలవబడినప్పుడు.

    > 💁 POST రిక్వెస్ట్‌లు డేటా పంపించి స్పందన పొందడానికి ఉపయోగిస్తారు. GET రిక్వెస్ట్‌లు వంటి ఇతర రిక్వెస్ట్ రకాలూ ఉన్నాయి, అవి డేటాను పొందుతాయి. మీ వెబ్ బ్రౌజర్ GET రిక్వెస్ట్‌లను ఉపయోగించి వెబ్ పేజీలను లోడ్ చేస్తుంది.

    POST రిక్వెస్ట్ స్పందన స్టేటస్ కోడ్‌ను తిరిగి ఇస్తుంది. ఇవి బాగా నిర్వచించబడిన విలువలు, 200 అంటే **సరే** - POST రిక్వెస్ట్ విజయవంతం అయ్యింది.

    > 💁 మీరు అన్ని స్పందన స్టేటస్ కోడ్‌లను [List of HTTP status codes page on Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes) లో చూడవచ్చు

    200 వస్తే, ఫలితాన్ని HTTP క్లయింట్ నుండి చదవబడుతుంది. ఇది REST API నుండి టెక్స్ట్ స్పందన, ప్రిడిక్షన్ ఫలితాల JSON డాక్యుమెంట్. JSON ఈ విధంగా ఉంటుంది:

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

    ఇక్కడ ముఖ్యమైన భాగం `predictions` అర్రే. ఇది ప్రిడిక్షన్లను కలిగి ఉంటుంది, ప్రతి ట్యాగ్‌కు ఒక ఎంట్రీ ఉంటుంది, అందులో ట్యాగ్ పేరు మరియుProbability ఉంటుంది. Probabilityలు 0 నుండి 1 వరకు ఉన్న తేలియాడే సంఖ్యలుగా వస్తాయి, 0 అంటే ఆ ట్యాగ్‌కు 0% సరిపోయే అవకాశం, 1 అంటే 100% అవకాశం.

    > 💁 ఇమేజ్ క్లాసిఫయर्स ఉపయోగించిన అన్ని ట్యాగ్‌లకు శాతం తిరిగి ఇస్తాయి. ప్రతి ట్యాగ్‌కు చిత్రం సరిపోయే probability ఉంటుంది.

    ఈ JSON డీకోడ్ చేయబడుతుంది, మరియు ప్రతి ట్యాగ్ probabilityలను సీరియల్ మానిటర్‌కు పంపబడుతుంది.

1. `buttonPressed` ఫంక్షన్‌లో, SD కార్డ్‌కు సేవ్ చేసే కోడ్‌ను `classifyImage` ఫంక్షన్ పిలవడంతో మార్చండి లేదా చిత్రం వ్రాయబడిన వెంటనే, కానీ బఫర్ తొలగించక ముందు ఇది జత చేయండి:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 మీరు SD కార్డ్‌లో సేవ్ చేసే కోడ్‌ను మార్చితే, `setupSDCard` మరియు `saveToSDCard` ఫంక్షన్‌లను తీసివేస్తూ మీ కోడ్‌ను శుభ్రం చేసుకోవచ్చు.

1. మీ కోడ్‌ను అప్లోడ్ చేసి నడపండి. కెమెరాను కొన్ని ఫలాలపై తిప్పండి మరియు C బటన్ను నొక్కండి. మీరు సీరియల్ మానిటర్‌లో అవుట్పుట్ చూడవచ్చు:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    మీరు తీసిన చిత్రం మరియు ఈ విలువలను Custom Vision లోని **Predictions** ట్యాబ్‌లో చూడవచ్చు.

    ![Custom Visionలో బ‌నానాను 56.8% రిప్ అయినట్లు, 43.1% అన్‌రిప్‌గా ప్రవచించిన చిత్రం](../../../../../translated_images/te/custom-vision-banana-prediction.30cdff4e1d72db5d.png)

> 💁 మీరు ఈ కోడ్‌ను [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal) ఫోల్డర్‌లో కనుగొనవచ్చు.

😀 మీ ఫలాల నాణ్యత క్లాసిఫయర్ ప్రోగ్రాం విజయం సాధించింది!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**హ్యర్దిక సమాచార సూచన**:
ఈ పత్రాన్ని AI అనువాద సేవ [Co-op Translator](https://github.com/Azure/co-op-translator) ఉపయోగించి అనువదించబడింది. మేము ఖచ్చితత్వానికి ప్రయత్నిస్తున్నప్పటికీ, ఆటోమేటెడ్ అనువాదాల్లో పొరపాట్లు లేదా తప్పులు ఉండవచ్చు అని దయచేసి గమనించండి. మూల పత్రం స్థానిక భాషలో అధికారిక మూలంగా పరిగణించాలి. కీలకమైన సమాచారానికి, ప్రొఫెషనల్ మానవ అనువాదాన్ని సిఫార్సు చేస్తాము. ఈ అనువాదం వాడకంలో జరిగిన ఏవైనా తప్పుదోవలు లేదా ভুল అవగాహనలకు మేము బాధ్యత వహించము.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->