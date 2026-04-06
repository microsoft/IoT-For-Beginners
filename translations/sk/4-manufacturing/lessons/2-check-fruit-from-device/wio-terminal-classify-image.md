# Klasifikácia obrázku - Wio Terminal

V tejto časti lekcie pošlete obrázok zachytený kamerou do služby Custom Vision, aby ste ho klasifikovali.

## Klasifikácia obrázku

Služba Custom Vision má REST API, ktoré môžete volať z Wio Terminal na klasifikáciu obrázkov. Toto REST API je prístupné cez HTTPS pripojenie - zabezpečené HTTP pripojenie.

Pri interakcii s HTTPS koncovými bodmi musí klientský kód požiadať o verejný certifikát od servera, ku ktorému sa pripája, a použiť ho na šifrovanie odosielanej komunikácie. Váš webový prehliadač to robí automaticky, ale mikrokontroléry nie. Certifikát budete musieť požiadať manuálne a použiť ho na vytvorenie zabezpečeného pripojenia k REST API. Tieto certifikáty sa nemenia, takže akonáhle máte certifikát, môžete ho pevne zakódovať vo svojej aplikácii.

Tieto certifikáty obsahujú verejné kľúče a nemusia byť uchovávané v bezpečí. Môžete ich použiť vo svojom zdrojovom kóde a zdieľať ich verejne na miestach ako GitHub.

### Úloha - nastavenie SSL klienta

1. Otvorte projekt aplikácie `fruit-quality-detector`, ak už nie je otvorený.

1. Otvorte hlavičkový súbor `config.h` a pridajte nasledujúce:

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

    Toto je *Microsoft Azure DigiCert Global Root G2 certifikát* - jeden z certifikátov používaných mnohými Azure službami globálne.

    > 💁 Aby ste videli, že toto je certifikát, ktorý treba použiť, spustite nasledujúci príkaz na macOS alebo Linuxe. Ak používate Windows, môžete tento príkaz spustiť pomocou [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Výstup zobrazí certifikát DigiCert Global Root G2.

1. Otvorte `main.cpp` a pridajte nasledujúci direktív pre zahrnutie:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Pod direktívami pre zahrnutie deklarujte inštanciu `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Táto trieda obsahuje kód na komunikáciu s webovými koncovými bodmi cez HTTPS.

1. V metóde `connectWiFi` nastavte WiFiClientSecure na použitie certifikátu DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Úloha - klasifikácia obrázku

1. Pridajte nasledujúci riadok do zoznamu `lib_deps` v súbore `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Týmto importujete [ArduinoJson](https://arduinojson.org), knižnicu JSON pre Arduino, ktorá sa použije na dekódovanie JSON odpovede z REST API.

1. V `config.h` pridajte konštanty pre URL predikcie a kľúč zo služby Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Nahraďte `<PREDICTION_URL>` URL predikcie zo služby Custom Vision. Nahraďte `<PREDICTION_KEY>` kľúč predikcie.

1. V `main.cpp` pridajte direktív pre zahrnutie knižnice ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Pridajte nasledujúcu funkciu do `main.cpp`, nad funkciu `buttonPressed`.

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

    Tento kód začína deklaráciou `HTTPClient` - triedy, ktorá obsahuje metódy na interakciu s REST API. Potom pripojí klienta k URL predikcie pomocou inštancie `WiFiClientSecure`, ktorá bola nastavená s verejným kľúčom Azure.

    Po pripojení odošle hlavičky - informácie o nadchádzajúcej požiadavke, ktorá bude urobená voči REST API. Hlavička `Content-Type` indikuje, že API volanie odošle surové binárne dáta, hlavička `Prediction-Key` odovzdáva kľúč predikcie zo služby Custom Vision.

    Následne sa vykoná POST požiadavka na HTTP klienta, ktorá nahrá bajtové pole. Toto pole bude obsahovať JPEG obrázok zachytený kamerou, keď sa táto funkcia zavolá.

    > 💁 POST požiadavky sú určené na odosielanie dát a získanie odpovede. Existujú aj iné typy požiadaviek, ako napríklad GET požiadavky, ktoré získavajú dáta. GET požiadavky používa váš webový prehliadač na načítanie webových stránok.

    POST požiadavka vráti stavový kód odpovede. Tieto hodnoty sú dobre definované, pričom 200 znamená **OK** - POST požiadavka bola úspešná.

    > 💁 Všetky stavové kódy odpovedí si môžete pozrieť na stránke [List of HTTP status codes na Wikipédii](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Ak sa vráti 200, výsledok sa prečíta z HTTP klienta. Toto je textová odpoveď z REST API s výsledkami predikcie vo forme JSON dokumentu. JSON má nasledujúci formát:

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

    Dôležitou časťou je pole `predictions`. Obsahuje predikcie, pričom každá položka obsahuje názov značky a pravdepodobnosť. Pravdepodobnosti sú vrátené ako desatinné čísla od 0 do 1, pričom 0 znamená 0% šancu na zhodu so značkou a 1 znamená 100% šancu.

    > 💁 Klasifikátory obrázkov vrátia percentá pre všetky značky, ktoré boli použité. Každá značka bude mať pravdepodobnosť, že obrázok zodpovedá tejto značke.

    Tento JSON je dekódovaný a pravdepodobnosti pre každú značku sú odoslané do sériového monitora.

1. Vo funkcii `buttonPressed` buď nahraďte kód, ktorý ukladá na SD kartu, volaním `classifyImage`, alebo ho pridajte po tom, ako je obrázok zapísaný, ale **predtým**, ako je buffer vymazaný:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Ak nahradíte kód, ktorý ukladá na SD kartu, môžete vyčistiť svoj kód odstránením funkcií `setupSDCard` a `saveToSDCard`.

1. Nahrajte a spustite svoj kód. Namierte kameru na nejaké ovocie a stlačte tlačidlo C. Výstup uvidíte v sériovom monitore:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Budete môcť vidieť obrázok, ktorý bol zachytený, a tieto hodnoty na karte **Predictions** v službe Custom Vision.

    ![Banán v službe Custom Vision predikovaný ako zrelý na 56.8% a nezrelý na 43.1%](../../../../../translated_images/sk/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Tento kód nájdete v priečinku [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Váš program na klasifikáciu kvality ovocia bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.