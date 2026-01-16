<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-27T21:01:28+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "cs"
}
-->
# Klasifikace obrázku - Wio Terminal

V této části lekce pošlete obrázek zachycený kamerou do služby Custom Vision, aby byl klasifikován.

## Klasifikace obrázku

Služba Custom Vision má REST API, které můžete volat z Wio Terminalu pro klasifikaci obrázků. Toto REST API je přístupné přes HTTPS připojení - zabezpečené HTTP připojení.

Při komunikaci s HTTPS endpointy musí klientský kód požádat server, ke kterému se připojuje, o veřejný certifikát a použít jej k šifrování odesílaného provozu. Váš webový prohlížeč to dělá automaticky, ale mikrokontroléry ne. Certifikát budete muset získat ručně a použít jej k vytvoření zabezpečeného připojení k REST API. Tyto certifikáty se nemění, takže jakmile máte certifikát, můžete jej pevně zakódovat do své aplikace.

Certifikáty obsahují veřejné klíče a není nutné je uchovávat v tajnosti. Můžete je použít ve svém zdrojovém kódu a sdílet je veřejně na místech, jako je GitHub.

### Úkol - nastavení SSL klienta

1. Otevřete projekt aplikace `fruit-quality-detector`, pokud již není otevřený.

1. Otevřete hlavičkový soubor `config.h` a přidejte následující:

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

    Toto je *Microsoft Azure DigiCert Global Root G2 certifikát* - jeden z certifikátů používaných mnoha službami Azure po celém světě.

    > 💁 Abyste viděli, že toto je certifikát, který je třeba použít, spusťte následující příkaz na macOS nebo Linuxu. Pokud používáte Windows, můžete tento příkaz spustit pomocí [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Výstup zobrazí certifikát DigiCert Global Root G2.

1. Otevřete `main.cpp` a přidejte následující direktivu pro zahrnutí:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Pod direktivami pro zahrnutí deklarujte instanci `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Tato třída obsahuje kód pro komunikaci s webovými endpointy přes HTTPS.

1. V metodě `connectWiFi` nastavte `WifiClientSecure`, aby používal certifikát DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Úkol - klasifikace obrázku

1. Přidejte následující jako další řádek do seznamu `lib_deps` v souboru `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Tím se importuje [ArduinoJson](https://arduinojson.org), knihovna JSON pro Arduino, která bude použita k dekódování JSON odpovědi z REST API.

1. V `config.h` přidejte konstanty pro URL predikce a klíč ze služby Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Nahraďte `<PREDICTION_URL>` URL predikce ze služby Custom Vision. Nahraďte `<PREDICTION_KEY>` klíčem predikce.

1. V `main.cpp` přidejte direktivu pro zahrnutí knihovny ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Přidejte následující funkci do `main.cpp`, nad funkci `buttonPressed`.

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

    Tento kód začíná deklarací `HTTPClient` - třídy, která obsahuje metody pro interakci s REST API. Poté připojí klienta k URL predikce pomocí instance `WiFiClientSecure`, která byla nastavena s veřejným klíčem Azure.

    Jakmile je připojen, odešle hlavičky - informace o nadcházejícím požadavku, který bude proveden proti REST API. Hlavička `Content-Type` označuje, že API volání odešle surová binární data, hlavička `Prediction-Key` předává klíč predikce ze služby Custom Vision.

    Poté je na HTTP klienta odeslán požadavek POST, který nahrává pole bajtů. Toto pole bude obsahovat JPEG obrázek zachycený kamerou, když je tato funkce volána.

    > 💁 Požadavky POST jsou určeny pro odesílání dat a získání odpovědi. Existují i jiné typy požadavků, jako například GET požadavky, které získávají data. GET požadavky používá váš webový prohlížeč k načítání webových stránek.

    Požadavek POST vrátí stavový kód odpovědi. Tyto kódy jsou dobře definované hodnoty, přičemž 200 znamená **OK** - požadavek POST byl úspěšný.

    > 💁 Všechny stavové kódy odpovědí najdete na [stránce seznamu HTTP stavových kódů na Wikipedii](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Pokud je vrácena hodnota 200, výsledek je přečten z HTTP klienta. Jedná se o textovou odpověď z REST API s výsledky predikce jako JSON dokument. JSON má následující formát:

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

    Důležitou částí je pole `predictions`. Obsahuje predikce, přičemž každý záznam obsahuje název tagu a pravděpodobnost. Pravděpodobnosti jsou vráceny jako desetinná čísla od 0 do 1, přičemž 0 znamená 0% šanci na shodu s tagem a 1 znamená 100% šanci.

    > 💁 Klasifikátory obrázků vrátí procenta pro všechny tagy, které byly použity. Každý tag bude mít pravděpodobnost, že obrázek odpovídá danému tagu.

    Tento JSON je dekódován a pravděpodobnosti pro každý tag jsou odeslány do sériového monitoru.

1. Ve funkci `buttonPressed` buď nahraďte kód, který ukládá na SD kartu, voláním `classifyImage`, nebo jej přidejte po zápisu obrázku, ale **před** odstraněním bufferu:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Pokud nahradíte kód, který ukládá na SD kartu, můžete svůj kód vyčistit odstraněním funkcí `setupSDCard` a `saveToSDCard`.

1. Nahrajte a spusťte svůj kód. Namířte kameru na nějaké ovoce a stiskněte tlačítko C. Výstup uvidíte v sériovém monitoru:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Budete schopni vidět obrázek, který byl pořízen, a tyto hodnoty na záložce **Predictions** ve službě Custom Vision.

    ![Banán v Custom Vision předpovězený jako zralý na 56.8% a nezralý na 43.1%](../../../../../translated_images/cs/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Tento kód najdete ve složce [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Váš program pro klasifikaci kvality ovoce byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.