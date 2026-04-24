# Clasificarea unei imagini - Wio Terminal

În această parte a lecției, vei trimite imaginea capturată de cameră către serviciul Custom Vision pentru a o clasifica.

## Clasificarea unei imagini

Serviciul Custom Vision are o API REST pe care o poți apela de pe Wio Terminal pentru a clasifica imagini. Această API REST este accesată printr-o conexiune HTTPS - o conexiune HTTP securizată.

Când interacționezi cu puncte de acces HTTPS, codul client trebuie să solicite certificatul cheii publice de la serverul accesat și să îl folosească pentru a cripta traficul pe care îl trimite. Browserul tău web face acest lucru automat, dar microcontrolerele nu. Va trebui să soliciți acest certificat manual și să îl folosești pentru a crea o conexiune securizată cu API-ul REST. Aceste certificate nu se schimbă, așa că, odată ce ai un certificat, acesta poate fi codificat direct în aplicația ta.

Aceste certificate conțin chei publice și nu trebuie păstrate în siguranță. Le poți folosi în codul sursă și le poți distribui public pe platforme precum GitHub.

### Sarcină - configurarea unui client SSL

1. Deschide proiectul aplicației `fruit-quality-detector` dacă nu este deja deschis.

1. Deschide fișierul header `config.h` și adaugă următorul cod:

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

    Acesta este *certificatul Microsoft Azure DigiCert Global Root G2* - unul dintre certificatele utilizate de multe servicii Azure la nivel global.

    > 💁 Pentru a verifica că acesta este certificatul corect, rulează următoarea comandă pe macOS sau Linux. Dacă folosești Windows, poți rula această comandă utilizând [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Rezultatul va lista certificatul DigiCert Global Root G2.

1. Deschide `main.cpp` și adaugă următoarea directivă include:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Sub directivele include, declară o instanță a `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Această clasă conține cod pentru a comunica cu puncte de acces web prin HTTPS.

1. În metoda `connectWiFi`, configurează `WiFiClientSecure` să utilizeze certificatul DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Sarcină - clasificarea unei imagini

1. Adaugă următoarea linie suplimentară în lista `lib_deps` din fișierul `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Aceasta importă [ArduinoJson](https://arduinojson.org), o bibliotecă JSON pentru Arduino, care va fi utilizată pentru a decoda răspunsul JSON de la API-ul REST.

1. În `config.h`, adaugă constante pentru URL-ul de predicție și cheia de la serviciul Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Înlocuiește `<PREDICTION_URL>` cu URL-ul de predicție de la Custom Vision. Înlocuiește `<PREDICTION_KEY>` cu cheia de predicție.

1. În `main.cpp`, adaugă o directivă include pentru biblioteca ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Adaugă următoarea funcție în `main.cpp`, deasupra funcției `buttonPressed`.

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

    Codul începe prin declararea unui `HTTPClient` - o clasă care conține metode pentru a interacționa cu API-uri REST. Apoi conectează clientul la URL-ul de predicție utilizând instanța `WiFiClientSecure` configurată cu cheia publică Azure.

    Odată conectat, trimite anteturi - informații despre cererea care urmează să fie făcută către API-ul REST. Antetul `Content-Type` indică faptul că apelul API va trimite date binare brute, iar antetul `Prediction-Key` transmite cheia de predicție Custom Vision.

    Urmează o cerere POST către clientul HTTP, încărcând un array de octeți. Acesta va conține imaginea JPEG capturată de cameră atunci când funcția este apelată.

    > 💁 Cererile POST sunt destinate trimiterii de date și obținerii unui răspuns. Există și alte tipuri de cereri, cum ar fi cererile GET, care recuperează date. Cererile GET sunt utilizate de browserul tău web pentru a încărca pagini web.

    Cererea POST returnează un cod de stare al răspunsului. Acestea sunt valori bine definite, iar 200 înseamnă **OK** - cererea POST a fost realizată cu succes.

    > 💁 Poți vedea toate codurile de stare ale răspunsului pe [pagina List of HTTP status codes de pe Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Dacă se returnează un 200, rezultatul este citit de la clientul HTTP. Acesta este un răspuns text de la API-ul REST cu rezultatele predicției sub formă de document JSON. JSON-ul are următorul format:

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

    Partea importantă aici este array-ul `predictions`. Acesta conține predicțiile, cu o intrare pentru fiecare etichetă, incluzând numele etichetei și probabilitatea. Probabilitățile returnate sunt numere în virgulă mobilă între 0-1, unde 0 reprezintă o șansă de 0% de a se potrivi cu eticheta, iar 1 reprezintă o șansă de 100%.

    > 💁 Clasificatorii de imagini vor returna procentele pentru toate etichetele utilizate. Fiecare etichetă va avea o probabilitate ca imaginea să se potrivească cu acea etichetă.

    Acest JSON este decodat, iar probabilitățile pentru fiecare etichetă sunt trimise către monitorul serial.

1. În funcția `buttonPressed`, înlocuiește codul care salvează pe cardul SD cu un apel către `classifyImage`, sau adaugă-l după ce imaginea este scrisă, dar **înainte** ca bufferul să fie șters:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Dacă înlocuiești codul care salvează pe cardul SD, poți curăța codul eliminând funcțiile `setupSDCard` și `saveToSDCard`.

1. Încarcă și rulează codul. Îndreaptă camera către un fruct și apasă butonul C. Vei vedea rezultatul în monitorul serial:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Vei putea vedea imaginea capturată și aceste valori în fila **Predictions** din Custom Vision.

    ![O banană în Custom Vision prezisă ca fiind coaptă cu 56.8% și necoaptă cu 43.1%](../../../../../translated_images/ro/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Poți găsi acest cod în folderul [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Programul tău de clasificare a calității fructelor a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.