# Klassifiser et bilde - Wio Terminal

I denne delen av leksjonen skal du sende bildet som kameraet har tatt til Custom Vision-tjenesten for å klassifisere det.

## Klassifiser et bilde

Custom Vision-tjenesten har et REST API som du kan bruke fra Wio Terminal for å klassifisere bilder. Dette REST API-et nås via en HTTPS-tilkobling - en sikker HTTP-tilkobling.

Når du kommuniserer med HTTPS-endepunkter, må klientkoden be om det offentlige nøkkelsertifikatet fra serveren som blir brukt, og bruke det til å kryptere trafikken den sender. Nettleseren din gjør dette automatisk, men mikrokontrollere gjør det ikke. Du må be om dette sertifikatet manuelt og bruke det til å opprette en sikker tilkobling til REST API-et. Disse sertifikatene endres ikke, så når du har et sertifikat, kan det hardkodes i applikasjonen din.

Disse sertifikatene inneholder offentlige nøkler og trenger ikke å holdes hemmelige. Du kan bruke dem i kildekoden din og dele dem offentlig på steder som GitHub.

### Oppgave - sett opp en SSL-klient

1. Åpne prosjektet for appen `fruit-quality-detector` hvis det ikke allerede er åpent.

1. Åpne header-filen `config.h` og legg til følgende:

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

    Dette er *Microsoft Azure DigiCert Global Root G2-sertifikatet* - det er et av sertifikatene som brukes av mange Azure-tjenester globalt.

    > 💁 For å se at dette er sertifikatet som skal brukes, kjør følgende kommando på macOS eller Linux. Hvis du bruker Windows, kan du kjøre denne kommandoen ved hjelp av [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Utdataene vil liste opp DigiCert Global Root G2-sertifikatet.

1. Åpne `main.cpp` og legg til følgende include-direktiv:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Under include-direktivene, deklarer en instans av `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Denne klassen inneholder kode for å kommunisere med web-endepunkter via HTTPS.

1. I metoden `connectWiFi`, sett WiFiClientSecure til å bruke DigiCert Global Root G2-sertifikatet:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Oppgave - klassifiser et bilde

1. Legg til følgende som en ekstra linje i listen `lib_deps` i filen `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Dette importerer [ArduinoJson](https://arduinojson.org), et Arduino JSON-bibliotek, som vil bli brukt til å dekode JSON-responsen fra REST API-et.

1. I `config.h`, legg til konstanter for prediksjons-URL og nøkkel fra Custom Vision-tjenesten:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Erstatt `<PREDICTION_URL>` med prediksjons-URL-en fra Custom Vision. Erstatt `<PREDICTION_KEY>` med prediksjonsnøkkelen.

1. I `main.cpp`, legg til et include-direktiv for ArduinoJson-biblioteket:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Legg til følgende funksjon i `main.cpp`, over funksjonen `buttonPressed`.

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

    Denne koden starter med å deklarere en `HTTPClient` - en klasse som inneholder metoder for å kommunisere med REST API-er. Deretter kobler den klienten til prediksjons-URL-en ved hjelp av `WiFiClientSecure`-instansen som ble satt opp med Azure offentlig nøkkel.

    Når den er koblet til, sender den headers - informasjon om den kommende forespørselen som vil bli gjort mot REST API-et. Headeren `Content-Type` indikerer at API-kallet vil sende rå binærdata, og headeren `Prediction-Key` sender Custom Vision-prediksjonsnøkkelen.

    Deretter gjøres en POST-forespørsel til HTTP-klienten, og en byte-array lastes opp. Denne vil inneholde JPEG-bildet som ble tatt av kameraet når denne funksjonen kalles.

    > 💁 POST-forespørsler brukes til å sende data og få en respons. Det finnes andre forespørselstyper, som GET-forespørsler, som henter data. GET-forespørsler brukes av nettleseren din for å laste inn nettsider.

    POST-forespørselen returnerer en responsstatuskode. Disse er veldefinerte verdier, der 200 betyr **OK** - POST-forespørselen var vellykket.

    > 💁 Du kan se alle responsstatuskodene på [Wikipedia-siden for HTTP-statuskoder](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Hvis 200 returneres, leses resultatet fra HTTP-klienten. Dette er en tekstrespons fra REST API-et med resultatene av prediksjonen som et JSON-dokument. JSON-en har følgende format:

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

    Den viktige delen her er arrayet `predictions`. Dette inneholder prediksjonene, med én oppføring for hver tag som inneholder tag-navnet og sannsynligheten. Sannsynlighetene som returneres er flyttall fra 0-1, der 0 er 0 % sjanse for å matche taggen, og 1 er 100 % sjanse.

    > 💁 Bildeklassifiserere vil returnere prosentene for alle tagger som har blitt brukt. Hver tag vil ha en sannsynlighet for at bildet matcher den taggen.

    Denne JSON-en dekodes, og sannsynlighetene for hver tag sendes til seriell monitor.

1. I funksjonen `buttonPressed`, erstatt enten koden som lagrer til SD-kortet med et kall til `classifyImage`, eller legg det til etter at bildet er skrevet, men **før** bufferen slettes:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Hvis du erstatter koden som lagrer til SD-kortet, kan du rydde opp i koden ved å fjerne funksjonene `setupSDCard` og `saveToSDCard`.

1. Last opp og kjør koden din. Rett kameraet mot en frukt og trykk på C-knappen. Du vil se utdataene i seriell monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Du vil kunne se bildet som ble tatt, og disse verdiene i **Predictions**-fanen i Custom Vision.

    ![En banan i Custom Vision, predikert som moden med 56,8 % og umoden med 43,1 %](../../../../../translated_images/no/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Du finner denne koden i mappen [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Programmet ditt for klassifisering av fruktkvalitet var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.