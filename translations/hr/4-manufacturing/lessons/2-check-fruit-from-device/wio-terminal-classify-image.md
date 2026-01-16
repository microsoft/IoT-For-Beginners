<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-28T12:32:28+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "hr"
}
-->
# Klasificirajte sliku - Wio Terminal

U ovom dijelu lekcije poslat ćete sliku snimljenu kamerom usluzi Custom Vision kako biste je klasificirali.

## Klasificirajte sliku

Usluga Custom Vision ima REST API koji možete pozvati s Wio Terminala za klasifikaciju slika. Ovaj REST API se pristupa putem HTTPS veze - sigurne HTTP veze.

Kada komunicirate s HTTPS krajnjim točkama, klijentski kod mora zatražiti javni ključ certifikata od poslužitelja kojem se pristupa i koristiti ga za šifriranje prometa koji šalje. Vaš web preglednik to radi automatski, ali mikrokontroleri ne. Morat ćete ručno zatražiti ovaj certifikat i koristiti ga za stvaranje sigurne veze s REST API-jem. Ovi certifikati se ne mijenjaju, pa se, nakon što imate certifikat, on može hardkodirati u vašu aplikaciju.

Ovi certifikati sadrže javne ključeve i ne moraju biti čuvani u tajnosti. Možete ih koristiti u svom izvornom kodu i dijeliti ih javno na mjestima poput GitHuba.

### Zadatak - postavite SSL klijent

1. Otvorite projekt aplikacije `fruit-quality-detector` ako već nije otvoren.

1. Otvorite zaglavnu datoteku `config.h` i dodajte sljedeće:

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

    Ovo je *Microsoft Azure DigiCert Global Root G2 certifikat* - jedan od certifikata koje koriste mnoge Azure usluge globalno.

    > 💁 Da biste vidjeli da je ovo certifikat koji treba koristiti, pokrenite sljedeću naredbu na macOS-u ili Linuxu. Ako koristite Windows, ovu naredbu možete pokrenuti pomoću [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Izlaz će prikazati DigiCert Global Root G2 certifikat.

1. Otvorite `main.cpp` i dodajte sljedeću direktivu za uključivanje:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Ispod direktiva za uključivanje, deklarirajte instancu `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Ova klasa sadrži kod za komunikaciju s web krajnjim točkama putem HTTPS-a.

1. U metodi `connectWiFi`, postavite WiFiClientSecure da koristi DigiCert Global Root G2 certifikat:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Zadatak - klasificirajte sliku

1. Dodajte sljedeće kao dodatni redak u popis `lib_deps` u datoteci `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Ovo uvozi [ArduinoJson](https://arduinojson.org), Arduino JSON biblioteku, koja će se koristiti za dekodiranje JSON odgovora iz REST API-ja.

1. U `config.h`, dodajte konstante za URL predikcije i ključ iz usluge Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Zamijenite `<PREDICTION_URL>` s URL-om predikcije iz Custom Vision. Zamijenite `<PREDICTION_KEY>` s ključem predikcije.

1. U `main.cpp`, dodajte direktivu za uključivanje ArduinoJson biblioteke:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Dodajte sljedeću funkciju u `main.cpp`, iznad funkcije `buttonPressed`.

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

    Ovaj kod započinje deklariranjem `HTTPClient` - klase koja sadrži metode za interakciju s REST API-jima. Zatim povezuje klijenta s URL-om predikcije koristeći instancu `WiFiClientSecure` koja je postavljena s javnim ključem Azurea.

    Nakon povezivanja, šalje zaglavlja - informacije o nadolazećem zahtjevu koji će biti poslan REST API-ju. Zaglavlje `Content-Type` označava da će API poziv poslati sirove binarne podatke, dok zaglavlje `Prediction-Key` prosljeđuje ključ predikcije Custom Visiona.

    Zatim se POST zahtjev šalje HTTP klijentu, učitavajući niz bajtova. Ovo će sadržavati JPEG sliku snimljenu kamerom kada se ova funkcija pozove.

    > 💁 POST zahtjevi su namijenjeni slanju podataka i dobivanju odgovora. Postoje i druge vrste zahtjeva, poput GET zahtjeva koji dohvaćaju podatke. GET zahtjeve koristi vaš web preglednik za učitavanje web stranica.

    POST zahtjev vraća statusni kod odgovora. To su dobro definirane vrijednosti, pri čemu 200 znači **OK** - POST zahtjev je bio uspješan.

    > 💁 Sve statusne kodove odgovora možete vidjeti na [stranici s popisom HTTP statusnih kodova na Wikipediji](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Ako se vrati 200, rezultat se čita iz HTTP klijenta. Ovo je tekstualni odgovor iz REST API-ja s rezultatima predikcije kao JSON dokument. JSON ima sljedeći format:

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

    Važan dio ovdje je niz `predictions`. On sadrži predikcije, s jednim unosom za svaku oznaku koji sadrži naziv oznake i vjerojatnost. Vjerojatnosti koje se vraćaju su brojevi s pomičnim zarezom od 0-1, pri čemu 0 znači 0% šanse za podudaranje s oznakom, a 1 znači 100% šanse.

    > 💁 Klasifikatori slika vraćaju postotke za sve oznake koje su korištene. Svaka oznaka će imati vjerojatnost da slika odgovara toj oznaci.

    Ovaj JSON se dekodira, a vjerojatnosti za svaku oznaku šalju se na serijski monitor.

1. U funkciji `buttonPressed`, zamijenite kod koji sprema na SD karticu pozivom funkcije `classifyImage`, ili ga dodajte nakon što je slika zapisana, ali **prije** nego što se međuspremnik izbriše:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Ako zamijenite kod koji sprema na SD karticu, možete očistiti svoj kod uklanjanjem funkcija `setupSDCard` i `saveToSDCard`.

1. Prenesite i pokrenite svoj kod. Usmjerite kameru prema nekom voću i pritisnite tipku C. Vidjet ćete izlaz na serijskom monitoru:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Moći ćete vidjeti sliku koja je snimljena i ove vrijednosti na kartici **Predictions** u Custom Visionu.

    ![Banana u Custom Visionu predviđena kao zrela s 56.8% i nezrela s 43.1%](../../../../../translated_images/hr/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Ovaj kod možete pronaći u mapi [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Vaš program za klasifikaciju kvalitete voća bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.