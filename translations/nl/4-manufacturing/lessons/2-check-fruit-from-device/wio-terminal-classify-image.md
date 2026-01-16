<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-27T20:43:04+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "nl"
}
-->
# Classificeer een afbeelding - Wio Terminal

In dit deel van de les stuur je de afbeelding die door de camera is vastgelegd naar de Custom Vision-service om deze te classificeren.

## Classificeer een afbeelding

De Custom Vision-service heeft een REST API die je kunt aanroepen vanaf de Wio Terminal om afbeeldingen te classificeren. Deze REST API wordt benaderd via een HTTPS-verbinding - een beveiligde HTTP-verbinding.

Bij interactie met HTTPS-eindpunten moet de clientcode het openbare sleutelcertificaat opvragen van de server die wordt benaderd en dit gebruiken om het verkeer dat wordt verzonden te versleutelen. Je webbrowser doet dit automatisch, maar microcontrollers niet. Je moet dit certificaat handmatig opvragen en gebruiken om een beveiligde verbinding met de REST API te maken. Deze certificaten veranderen niet, dus zodra je een certificaat hebt, kan het hard gecodeerd worden in je applicatie.

Deze certificaten bevatten openbare sleutels en hoeven niet beveiligd te worden. Je kunt ze in je broncode gebruiken en openbaar delen op plaatsen zoals GitHub.

### Taak - stel een SSL-client in

1. Open het project van de app `fruit-quality-detector` als het nog niet geopend is.

1. Open het headerbestand `config.h` en voeg het volgende toe:

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

    Dit is het *Microsoft Azure DigiCert Global Root G2-certificaat* - een van de certificaten die wereldwijd door veel Azure-services worden gebruikt.

    > 💁 Om te zien dat dit het certificaat is dat je moet gebruiken, voer je de volgende opdracht uit op macOS of Linux. Als je Windows gebruikt, kun je deze opdracht uitvoeren met de [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > De uitvoer zal het DigiCert Global Root G2-certificaat vermelden.

1. Open `main.cpp` en voeg de volgende include-richtlijn toe:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Verklaar onder de include-richtlijnen een instantie van `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Deze klasse bevat code om te communiceren met web-eindpunten via HTTPS.

1. Stel in de methode `connectWiFi` de WifiClientSecure in om het DigiCert Global Root G2-certificaat te gebruiken:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Taak - classificeer een afbeelding

1. Voeg het volgende toe als een extra regel aan de `lib_deps`-lijst in het bestand `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Dit importeert [ArduinoJson](https://arduinojson.org), een Arduino JSON-bibliotheek, en zal worden gebruikt om de JSON-reactie van de REST API te decoderen.

1. Voeg in `config.h` constanten toe voor de voorspellings-URL en sleutel van de Custom Vision-service:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Vervang `<PREDICTION_URL>` door de voorspellings-URL van Custom Vision. Vervang `<PREDICTION_KEY>` door de voorspellingssleutel.

1. Voeg in `main.cpp` een include-richtlijn toe voor de ArduinoJson-bibliotheek:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Voeg de volgende functie toe aan `main.cpp`, boven de functie `buttonPressed`.

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

    Deze code begint met het declareren van een `HTTPClient` - een klasse die methoden bevat om te communiceren met REST API's. Vervolgens verbindt het de client met de voorspellings-URL met behulp van de `WiFiClientSecure`-instantie die is ingesteld met de openbare sleutel van Azure.

    Zodra de verbinding tot stand is gebracht, worden headers verzonden - informatie over het verzoek dat zal worden gedaan tegen de REST API. De header `Content-Type` geeft aan dat de API-aanroep ruwe binaire gegevens zal verzenden, de header `Prediction-Key` geeft de Custom Vision-voorspellingssleutel door.

    Vervolgens wordt een POST-verzoek gedaan aan de HTTP-client, waarbij een byte-array wordt geüpload. Dit bevat de JPEG-afbeelding die door de camera is vastgelegd wanneer deze functie wordt aangeroepen.

    > 💁 POST-verzoeken zijn bedoeld om gegevens te verzenden en een reactie te ontvangen. Er zijn andere soorten verzoeken, zoals GET-verzoeken, die gegevens ophalen. GET-verzoeken worden door je webbrowser gebruikt om webpagina's te laden.

    Het POST-verzoek retourneert een statuscode van de reactie. Dit zijn goed gedefinieerde waarden, waarbij 200 betekent **OK** - het POST-verzoek was succesvol.

    > 💁 Je kunt alle statuscodes van reacties bekijken op de [Lijst van HTTP-statuscodes-pagina op Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Als een 200 wordt geretourneerd, wordt het resultaat gelezen van de HTTP-client. Dit is een tekstreactie van de REST API met de resultaten van de voorspelling als een JSON-document. De JSON heeft het volgende formaat:

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

    Het belangrijkste deel hier is de array `predictions`. Deze bevat de voorspellingen, met één item voor elke tag met de tagnaam en de waarschijnlijkheid. De geretourneerde waarschijnlijkheden zijn drijvende getallen van 0-1, waarbij 0 een kans van 0% betekent dat de tag overeenkomt, en 1 een kans van 100%.

    > 💁 Afbeeldingsclassificeerders retourneren de percentages voor alle tags die zijn gebruikt. Elke tag heeft een waarschijnlijkheid dat de afbeelding overeenkomt met die tag.

    Deze JSON wordt gedecodeerd en de waarschijnlijkheden voor elke tag worden naar de seriële monitor gestuurd.

1. Vervang in de functie `buttonPressed` de code die opslaat op de SD-kaart door een aanroep naar `classifyImage`, of voeg deze toe na het schrijven van de afbeelding, maar **voordat** de buffer wordt verwijderd:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Als je de code vervangt die opslaat op de SD-kaart, kun je je code opschonen door de functies `setupSDCard` en `saveToSDCard` te verwijderen.

1. Upload en voer je code uit. Richt de camera op wat fruit en druk op de C-knop. Je ziet de uitvoer in de seriële monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Je kunt de afbeelding die is gemaakt zien, en deze waarden in het tabblad **Predictions** in Custom Vision.

    ![Een banaan in Custom Vision voorspeld als rijp met 56,8% en onrijp met 43,1%](../../../../../translated_images/nl/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Je kunt deze code vinden in de map [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Je programma voor het classificeren van fruitkwaliteit was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.