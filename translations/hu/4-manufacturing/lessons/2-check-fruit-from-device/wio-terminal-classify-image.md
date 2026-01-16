<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-27T21:00:50+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "hu"
}
-->
# Kép osztályozása - Wio Terminal

Ebben a leckében a kamerával rögzített képet elküldöd a Custom Vision szolgáltatásnak, hogy osztályozza azt.

## Kép osztályozása

A Custom Vision szolgáltatás rendelkezik egy REST API-val, amelyet a Wio Terminal segítségével hívhatsz meg képek osztályozására. Ez a REST API HTTPS kapcsolaton keresztül érhető el - egy biztonságos HTTP kapcsolat.

Amikor HTTPS végpontokkal kommunikálsz, a kliens kódnak kérnie kell a nyilvános kulcs tanúsítványt az elérni kívánt szervertől, és ezt használva titkosítja a küldött adatokat. A webböngésződ ezt automatikusan elvégzi, de a mikrokontrollerek nem. Neked manuálisan kell kérned ezt a tanúsítványt, és használni azt a REST API-val való biztonságos kapcsolat létrehozásához. Ezek a tanúsítványok nem változnak, így ha egyszer megszerezted, beépítheted az alkalmazásodba.

Ezek a tanúsítványok nyilvános kulcsokat tartalmaznak, és nem szükséges őket titokban tartani. Használhatod őket a forráskódodban, és nyilvánosan megoszthatod például GitHubon.

### Feladat - SSL kliens beállítása

1. Nyisd meg a `fruit-quality-detector` alkalmazás projektet, ha még nem tetted meg.

1. Nyisd meg a `config.h` fejlécfájlt, és add hozzá a következőt:

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

    Ez a *Microsoft Azure DigiCert Global Root G2 tanúsítvány* - ez az egyik tanúsítvány, amelyet számos Azure szolgáltatás használ világszerte.

    > 💁 Annak ellenőrzéséhez, hogy ez a megfelelő tanúsítvány, futtasd a következő parancsot macOS-en vagy Linuxon. Ha Windows-t használsz, a parancsot a [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn) segítségével futtathatod:
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > A kimenet listázni fogja a DigiCert Global Root G2 tanúsítványt.

1. Nyisd meg a `main.cpp` fájlt, és add hozzá a következő include direktívát:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Az include direktívák alatt deklarálj egy `WifiClientSecure` példányt:

    ```cpp
    WiFiClientSecure client;
    ```

    Ez az osztály tartalmazza a kódot, amely lehetővé teszi a HTTPS végpontokkal való kommunikációt.

1. A `connectWiFi` metódusban állítsd be, hogy a WiFiClientSecure használja a DigiCert Global Root G2 tanúsítványt:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Feladat - kép osztályozása

1. Add hozzá a következőt a `lib_deps` listához a `platformio.ini` fájlban:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Ez importálja az [ArduinoJson](https://arduinojson.org) könyvtárat, amely egy Arduino JSON könyvtár, és a REST API válaszának dekódolására lesz használva.

1. A `config.h` fájlban adj hozzá konstansokat a Custom Vision szolgáltatás előrejelzési URL-jéhez és kulcsához:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Cseréld ki `<PREDICTION_URL>`-t a Custom Vision előrejelzési URL-jére. Cseréld ki `<PREDICTION_KEY>`-t az előrejelzési kulcsra.

1. A `main.cpp` fájlban adj hozzá egy include direktívát az ArduinoJson könyvtárhoz:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Add hozzá a következő függvényt a `main.cpp` fájlhoz, a `buttonPressed` függvény fölé:

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

    Ez a kód egy `HTTPClient`-et deklarál - egy osztályt, amely REST API-kal való interakcióhoz szükséges metódusokat tartalmaz. Ezután a kliens csatlakozik az előrejelzési URL-hez a korábban beállított `WiFiClientSecure` példány segítségével.

    Miután csatlakozott, fejlécet küld - információt a közelgő REST API kérésről. A `Content-Type` fejléc jelzi, hogy a kérés nyers bináris adatokat fog küldeni, a `Prediction-Key` fejléc pedig átadja a Custom Vision előrejelzési kulcsot.

    Ezután egy POST kérés kerül elküldésre az HTTP kliensnek, amely feltölt egy bájttömböt. Ez tartalmazza a kamerával rögzített JPEG képet, amikor a függvényt meghívják.

    > 💁 A POST kérés adatküldésre és válasz fogadására szolgál. Vannak más kérés típusok, például GET kérés, amely adatokat kér le. A GET kéréseket a webböngésződ használja weboldalak betöltésére.

    A POST kérés egy válasz státuszkódot ad vissza. Ezek jól definiált értékek, ahol a 200 azt jelenti, hogy **OK** - a POST kérés sikeres volt.

    > 💁 Az összes válasz státuszkódot megtalálhatod a [HTTP státuszkódok listája Wikipedia oldalon](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Ha 200-as kódot kapunk, az eredményt kiolvassuk az HTTP kliensből. Ez egy szöveges válasz a REST API-tól, amely tartalmazza az előrejelzés eredményeit JSON dokumentum formájában. A JSON a következő formátumú:

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

    A fontos rész itt a `predictions` tömb. Ez tartalmazza az előrejelzéseket, minden címkéhez egy bejegyzést a címke nevével és a valószínűséggel. A visszaadott valószínűségek lebegőpontos számok 0-1 között, ahol 0 azt jelenti, hogy 0% az esélye a címkének, és 1 azt jelenti, hogy 100% az esélye.

    > 💁 A képosztályozók visszaadják az összes címke százalékos értékét, amelyet használtak. Minden címkéhez tartozik egy valószínűség, hogy a kép megfelel-e annak.

    Ez a JSON dekódolásra kerül, és a címkék valószínűségei a soros monitorra kerülnek.

1. A `buttonPressed` függvényben cseréld ki az SD kártyára mentést végző kódot egy `classifyImage` hívásra, vagy add hozzá az SD kártyára írás után, de **mielőtt** a puffer törlésre kerül:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Ha lecseréled az SD kártyára mentést végző kódot, akkor megtisztíthatod a kódodat, eltávolítva a `setupSDCard` és `saveToSDCard` függvényeket.

1. Töltsd fel és futtasd a kódot. Irányítsd a kamerát néhány gyümölcsre, és nyomd meg a C gombot. Az eredményt látni fogod a soros monitoron:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Látni fogod a készített képet, és ezeket az értékeket a Custom Vision **Predictions** fülén.

    ![Egy banán a Custom Vision-ben, érettként 56.8%-os, éretlenként 43.1%-os előrejelzéssel](../../../../../translated_images/hu/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Ezt a kódot megtalálhatod a [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal) mappában.

😀 A gyümölcsminőség osztályozó programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.