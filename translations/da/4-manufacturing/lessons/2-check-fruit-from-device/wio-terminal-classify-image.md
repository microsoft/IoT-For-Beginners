<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-27T20:47:10+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "da"
}
-->
# Klassificér et billede - Wio Terminal

I denne del af lektionen vil du sende det billede, der er taget af kameraet, til Custom Vision-tjenesten for at klassificere det.

## Klassificér et billede

Custom Vision-tjenesten har en REST API, som du kan kalde fra Wio Terminal for at klassificere billeder. Denne REST API tilgås via en HTTPS-forbindelse - en sikker HTTP-forbindelse.

Når du interagerer med HTTPS-endpoints, skal klientkoden anmode om den offentlige nøglecertifikat fra den server, der tilgås, og bruge det til at kryptere den trafik, den sender. Din webbrowser gør dette automatisk, men mikrocontrollere gør ikke. Du skal manuelt anmode om dette certifikat og bruge det til at oprette en sikker forbindelse til REST API'en. Disse certifikater ændrer sig ikke, så når du har et certifikat, kan det hardkodes i din applikation.

Disse certifikater indeholder offentlige nøgler og behøver ikke at blive holdt sikre. Du kan bruge dem i din kildekode og dele dem offentligt på steder som GitHub.

### Opgave - opsæt en SSL-klient

1. Åbn projektet `fruit-quality-detector`, hvis det ikke allerede er åbent.

1. Åbn header-filen `config.h`, og tilføj følgende:

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

    Dette er *Microsoft Azure DigiCert Global Root G2-certifikatet* - det er et af de certifikater, der bruges af mange Azure-tjenester globalt.

    > 💁 For at se, at dette er det certifikat, der skal bruges, kan du køre følgende kommando på macOS eller Linux. Hvis du bruger Windows, kan du køre denne kommando ved hjælp af [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Outputtet vil liste DigiCert Global Root G2-certifikatet.

1. Åbn `main.cpp` og tilføj følgende include-direktiv:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Under include-direktiverne, deklarér en instans af `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Denne klasse indeholder kode til at kommunikere med web-endpoints via HTTPS.

1. I metoden `connectWiFi`, indstil WiFiClientSecure til at bruge DigiCert Global Root G2-certifikatet:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Opgave - klassificér et billede

1. Tilføj følgende som en ekstra linje til listen `lib_deps` i filen `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Dette importerer [ArduinoJson](https://arduinojson.org), et Arduino JSON-bibliotek, som vil blive brugt til at dekode JSON-responsen fra REST API'en.

1. I `config.h`, tilføj konstanter for forudsigelses-URL'en og nøgle fra Custom Vision-tjenesten:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Erstat `<PREDICTION_URL>` med forudsigelses-URL'en fra Custom Vision. Erstat `<PREDICTION_KEY>` med forudsigelsesnøglen.

1. I `main.cpp`, tilføj et include-direktiv for ArduinoJson-biblioteket:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Tilføj følgende funktion til `main.cpp`, over funktionen `buttonPressed`.

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

    Denne kode starter med at deklarere en `HTTPClient` - en klasse, der indeholder metoder til at interagere med REST API'er. Den forbinder derefter klienten til forudsigelses-URL'en ved hjælp af den `WiFiClientSecure`-instans, der blev opsat med Azure's offentlige nøgle.

    Når forbindelsen er oprettet, sender den headers - information om den kommende anmodning, der vil blive lavet mod REST API'en. Headeren `Content-Type` angiver, at API-kaldet vil sende rå binære data, og headeren `Prediction-Key` sender Custom Vision-forudsigelsesnøglen.

    Derefter laves en POST-anmodning til HTTP-klienten, hvor en byte-array uploades. Denne vil indeholde JPEG-billedet, der er taget med kameraet, når denne funktion kaldes.

    > 💁 POST-anmodninger bruges til at sende data og få en respons. Der findes andre anmodningstyper, såsom GET-anmodninger, der henter data. GET-anmodninger bruges af din webbrowser til at indlæse websider.

    POST-anmodningen returnerer en responsstatuskode. Disse er veldefinerede værdier, hvor 200 betyder **OK** - POST-anmodningen var vellykket.

    > 💁 Du kan se alle responsstatuskoderne på [Liste over HTTP-statuskoder på Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Hvis en 200 returneres, læses resultatet fra HTTP-klienten. Dette er en tekstrespons fra REST API'en med resultaterne af forudsigelsen som et JSON-dokument. JSON'en har følgende format:

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

    Den vigtige del her er arrayet `predictions`. Dette indeholder forudsigelserne, med en post for hver tag, der indeholder tag-navnet og sandsynligheden. Sandsynlighederne, der returneres, er flydende tal fra 0-1, hvor 0 er 0% chance for at matche tagget, og 1 er 100% chance.

    > 💁 Billedklassifikatorer returnerer procentdelene for alle tags, der er blevet brugt. Hvert tag vil have en sandsynlighed for, at billedet matcher det tag.

    Denne JSON dekodes, og sandsynlighederne for hvert tag sendes til den serielle monitor.

1. I funktionen `buttonPressed`, enten erstat koden, der gemmer til SD-kortet, med et kald til `classifyImage`, eller tilføj det efter billedet er skrevet, men **før** bufferen slettes:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Hvis du erstatter koden, der gemmer til SD-kortet, kan du rydde op i din kode ved at fjerne funktionerne `setupSDCard` og `saveToSDCard`.

1. Upload og kør din kode. Peg kameraet mod noget frugt og tryk på C-knappen. Du vil se outputtet i den serielle monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Du vil kunne se det billede, der blev taget, og disse værdier i **Predictions**-fanen i Custom Vision.

    ![En banan i Custom Vision forudsagt moden med 56.8% og umoden med 43.1%](../../../../../translated_images/da/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Du kan finde denne kode i mappen [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Dit program til klassificering af frugtkvalitet var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.