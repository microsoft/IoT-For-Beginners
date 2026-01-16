<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-28T19:13:32+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "lt"
}
-->
# Klasifikuokite vaizdą - Wio Terminal

Šioje pamokos dalyje jūs siųsite kamerą užfiksuotą vaizdą į „Custom Vision“ paslaugą, kad jis būtų klasifikuotas.

## Klasifikuokite vaizdą

„Custom Vision“ paslauga turi REST API, kurį galite iškviesti iš Wio Terminal, kad klasifikuotumėte vaizdus. Šis REST API pasiekiamas per HTTPS ryšį - saugų HTTP ryšį.

Naudojantis HTTPS galiniais taškais, kliento kodas turi paprašyti viešojo rakto sertifikato iš serverio, su kuriuo jungiamasi, ir naudoti jį siunčiamam srautui užšifruoti. Jūsų interneto naršyklė tai daro automatiškai, tačiau mikrovaldikliai to nedaro. Jums reikės rankiniu būdu paprašyti šio sertifikato ir naudoti jį kuriant saugų ryšį su REST API. Šie sertifikatai nesikeičia, todėl, kai turite sertifikatą, jį galima įrašyti tiesiogiai į jūsų programą.

Šie sertifikatai turi viešuosius raktus ir jų nereikia laikyti saugiai. Juos galite naudoti savo šaltinio kode ir viešai dalintis tokiose vietose kaip „GitHub“.

### Užduotis - nustatyti SSL klientą

1. Atidarykite `fruit-quality-detector` programos projektą, jei jis dar neatidarytas.

1. Atidarykite `config.h` antraštės failą ir pridėkite šiuos duomenis:

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

    Tai yra *Microsoft Azure DigiCert Global Root G2 sertifikatas* - vienas iš sertifikatų, naudojamų daugelyje „Azure“ paslaugų visame pasaulyje.

    > 💁 Norėdami pamatyti, kad tai yra sertifikatas, kurį reikia naudoti, vykdykite šią komandą macOS arba Linux sistemoje. Jei naudojate „Windows“, galite vykdyti šią komandą naudodami [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Rezultatas parodys DigiCert Global Root G2 sertifikatą.

1. Atidarykite `main.cpp` ir pridėkite šią įtraukimo direktyvą:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Žemiau įtraukimo direktyvų deklaruokite `WifiClientSecure` egzempliorių:

    ```cpp
    WiFiClientSecure client;
    ```

    Ši klasė turi kodą, skirtą bendrauti su interneto galiniais taškais per HTTPS.

1. `connectWiFi` metode nustatykite, kad `WiFiClientSecure` naudotų DigiCert Global Root G2 sertifikatą:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Užduotis - klasifikuoti vaizdą

1. Pridėkite šią eilutę prie `lib_deps` sąrašo `platformio.ini` faile:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Tai importuoja [ArduinoJson](https://arduinojson.org), „Arduino“ JSON biblioteką, kuri bus naudojama REST API atsakymui dekoduoti.

1. `config.h` faile pridėkite konstantas, skirtas „Custom Vision“ paslaugos prognozės URL ir raktui:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Pakeiskite `<PREDICTION_URL>` į prognozės URL iš „Custom Vision“. Pakeiskite `<PREDICTION_KEY>` į prognozės raktą.

1. `main.cpp` faile pridėkite įtraukimo direktyvą „ArduinoJson“ bibliotekai:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Pridėkite šią funkciją į `main.cpp`, virš `buttonPressed` funkcijos:

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

    Šis kodas pradeda deklaruodamas `HTTPClient` - klasę, turinčią metodus, skirtus bendrauti su REST API. Tada jis prijungia klientą prie prognozės URL naudodamas `WiFiClientSecure` egzempliorių, kuris buvo nustatytas su „Azure“ viešuoju raktu.

    Kai prisijungta, jis siunčia antraštes - informaciją apie būsimą užklausą, kuri bus pateikta REST API. Antraštė `Content-Type` nurodo, kad API užklausa siųs neapdorotus dvejetainius duomenis, o antraštė `Prediction-Key` perduoda „Custom Vision“ prognozės raktą.

    Toliau atliekama POST užklausa HTTP klientui, įkeliant baitų masyvą. Tai bus JPEG vaizdas, užfiksuotas kamera, kai ši funkcija bus iškviesta.

    > 💁 POST užklausos skirtos duomenų siuntimui ir atsakymo gavimui. Yra ir kitų užklausų tipų, tokių kaip GET užklausos, kurios gauna duomenis. GET užklausos naudojamos jūsų interneto naršyklėje, kad būtų įkeltos interneto svetainės.

    POST užklausa grąžina atsakymo būsenos kodą. Tai yra gerai apibrėžtos reikšmės, kur 200 reiškia **OK** - POST užklausa buvo sėkminga.

    > 💁 Visus atsakymo būsenos kodus galite pamatyti [HTTP būsenos kodų sąrašo puslapyje „Wikipedia“](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Jei grąžinamas 200, rezultatas nuskaitomas iš HTTP kliento. Tai yra tekstinis atsakymas iš REST API su prognozės rezultatais JSON dokumento formatu. JSON yra tokio formato:

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

    Svarbiausia dalis čia yra `predictions` masyvas. Jame yra prognozės, kur kiekvienas įrašas turi žymos pavadinimą ir tikimybę. Grąžinamos tikimybės yra slankiojo kablelio skaičiai nuo 0 iki 1, kur 0 reiškia 0% tikimybę atitikti žymą, o 1 reiškia 100% tikimybę.

    > 💁 Vaizdų klasifikatoriai grąžins procentus visoms naudotoms žymoms. Kiekviena žyma turės tikimybę, kad vaizdas atitinka tą žymą.

    Šis JSON yra dekoduojamas, o tikimybės kiekvienai žymai siunčiamos į serijinį monitorių.

1. `buttonPressed` funkcijoje pakeiskite kodą, kuris išsaugo į SD kortelę, į `classifyImage` iškvietimą, arba pridėkite jį po vaizdo įrašymo, bet **prieš** buferio ištrynimą:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Jei pakeisite kodą, kuris išsaugo į SD kortelę, galite išvalyti savo kodą pašalindami `setupSDCard` ir `saveToSDCard` funkcijas.

1. Įkelkite ir paleiskite savo kodą. Nukreipkite kamerą į vaisius ir paspauskite C mygtuką. Rezultatus pamatysite serijiniame monitoriuje:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Galėsite matyti užfiksuotą vaizdą ir šias reikšmes **Predictions** skiltyje „Custom Vision“.

    ![Bananas „Custom Vision“ prognozuotas kaip prinokęs 56.8% ir neprinokęs 43.1%](../../../../../translated_images/lt/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Šį kodą galite rasti [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal) aplanke.

😀 Jūsų vaisių kokybės klasifikavimo programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.