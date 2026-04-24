# Klassificera en bild - Wio Terminal

I den här delen av lektionen kommer du att skicka bilden som kameran fångat till Custom Vision-tjänsten för att klassificera den.

## Klassificera en bild

Custom Vision-tjänsten har ett REST API som du kan anropa från Wio Terminal för att klassificera bilder. Detta REST API nås via en HTTPS-anslutning - en säker HTTP-anslutning.

När du interagerar med HTTPS-slutpunkter behöver klientkoden begära det offentliga nyckelcertifikatet från servern som nås och använda det för att kryptera trafiken som skickas. Din webbläsare gör detta automatiskt, men mikrokontroller gör det inte. Du måste begära detta certifikat manuellt och använda det för att skapa en säker anslutning till REST API:t. Dessa certifikat ändras inte, så när du väl har ett certifikat kan det hårdkodas i din applikation.

Dessa certifikat innehåller offentliga nycklar och behöver inte hållas säkra. Du kan använda dem i din källkod och dela dem offentligt på platser som GitHub.

### Uppgift - ställ in en SSL-klient

1. Öppna projektet `fruit-quality-detector` om det inte redan är öppet.

1. Öppna header-filen `config.h` och lägg till följande:

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

    Detta är *Microsoft Azure DigiCert Global Root G2-certifikatet* - det är ett av de certifikat som används av många Azure-tjänster globalt.

    > 💁 För att se att detta är certifikatet som ska användas, kör följande kommando på macOS eller Linux. Om du använder Windows kan du köra detta kommando med [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Utdata kommer att lista DigiCert Global Root G2-certifikatet.

1. Öppna `main.cpp` och lägg till följande include-direktiv:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Under include-direktiven, deklarera en instans av `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Denna klass innehåller kod för att kommunicera med webbsidor via HTTPS.

1. I metoden `connectWiFi`, ställ in WiFiClientSecure att använda DigiCert Global Root G2-certifikatet:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Uppgift - klassificera en bild

1. Lägg till följande som en extra rad i listan `lib_deps` i filen `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Detta importerar [ArduinoJson](https://arduinojson.org), ett Arduino JSON-bibliotek, som kommer att användas för att avkoda JSON-svaret från REST API:t.

1. I `config.h`, lägg till konstanter för prediktions-URL och nyckel från Custom Vision-tjänsten:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Ersätt `<PREDICTION_URL>` med prediktions-URL:en från Custom Vision. Ersätt `<PREDICTION_KEY>` med prediktionsnyckeln.

1. I `main.cpp`, lägg till ett include-direktiv för ArduinoJson-biblioteket:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Lägg till följande funktion i `main.cpp`, ovanför funktionen `buttonPressed`.

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

    Denna kod börjar med att deklarera en `HTTPClient` - en klass som innehåller metoder för att interagera med REST API:er. Den ansluter sedan klienten till prediktions-URL:en med hjälp av instansen `WiFiClientSecure` som ställdes in med Azures offentliga nyckel.

    När anslutningen är upprättad skickas headers - information om den kommande begäran som kommer att göras mot REST API:t. Headern `Content-Type` indikerar att API-anropet kommer att skicka rå binär data, och headern `Prediction-Key` skickar Custom Vision-prediktionsnyckeln.

    Därefter görs en POST-begäran till HTTP-klienten, där en byte-array laddas upp. Denna kommer att innehålla JPEG-bilden som fångats av kameran när denna funktion anropas.

    > 💁 POST-begäran används för att skicka data och få ett svar. Det finns andra typer av begäran, som GET-begäran, som hämtar data. GET-begäran används av din webbläsare för att ladda webbsidor.

    POST-begäran returnerar en svarskod. Dessa är väldefinierade värden, där 200 betyder **OK** - POST-begäran lyckades.

    > 💁 Du kan se alla svarskoder på sidan [List of HTTP status codes på Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Om en 200 returneras läses resultatet från HTTP-klienten. Detta är ett textbaserat svar från REST API:t med resultaten av prediktionen som ett JSON-dokument. JSON ser ut så här:

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

    Den viktiga delen här är arrayen `predictions`. Den innehåller prediktionerna, med en post för varje tagg som innehåller taggnamnet och sannolikheten. Sannolikheterna som returneras är flyttal mellan 0-1, där 0 är 0% chans att matcha taggen och 1 är 100% chans.

    > 💁 Bildklassificerare returnerar procentandelar för alla taggar som har använts. Varje tagg kommer att ha en sannolikhet att bilden matchar den taggen.

    Denna JSON avkodas, och sannolikheterna för varje tagg skickas till seriemonitorn.

1. I funktionen `buttonPressed`, ersätt antingen koden som sparar till SD-kortet med ett anrop till `classifyImage`, eller lägg till det efter att bilden har skrivits, men **innan** bufferten raderas:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Om du ersätter koden som sparar till SD-kortet kan du städa upp din kod genom att ta bort funktionerna `setupSDCard` och `saveToSDCard`.

1. Ladda upp och kör din kod. Rikta kameran mot någon frukt och tryck på C-knappen. Du kommer att se utdata i seriemonitorn:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Du kommer att kunna se bilden som togs och dessa värden i fliken **Predictions** i Custom Vision.

    ![En banan i Custom Vision förutspådd som mogen med 56,8% och omogen med 43,1%](../../../../../translated_images/sv/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Du kan hitta denna kod i mappen [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Ditt program för att klassificera fruktkvalitet blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.