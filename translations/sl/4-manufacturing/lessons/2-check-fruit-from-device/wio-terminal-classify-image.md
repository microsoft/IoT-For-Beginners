<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-28T12:32:59+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "sl"
}
-->
# Razvrščanje slike - Wio Terminal

V tem delu lekcije boste poslali sliko, zajeto s kamero, storitvi Custom Vision za njeno razvrščanje.

## Razvrščanje slike

Storitev Custom Vision ima REST API, ki ga lahko pokličete iz Wio Terminala za razvrščanje slik. Ta REST API je dostopen prek povezave HTTPS - varne povezave HTTP.

Pri interakciji s končnimi točkami HTTPS mora odjemalska koda zahtevati javni ključni certifikat od strežnika, do katerega dostopa, in ga uporabiti za šifriranje prometa, ki ga pošilja. Vaš spletni brskalnik to naredi samodejno, mikrokrmilniki pa ne. Ta certifikat boste morali zahtevati ročno in ga uporabiti za vzpostavitev varne povezave z REST API-jem. Ti certifikati se ne spreminjajo, zato jih lahko, ko jih pridobite, trdo kodirate v svojo aplikacijo.

Ti certifikati vsebujejo javne ključe in jih ni treba hraniti na varnem. Lahko jih uporabite v svoji izvorni kodi in jih delite javno na mestih, kot je GitHub.

### Naloga - nastavitev SSL odjemalca

1. Odprite projekt aplikacije `fruit-quality-detector`, če še ni odprt.

1. Odprite glavno datoteko `config.h` in dodajte naslednje:

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

    To je *Microsoft Azure DigiCert Global Root G2 certifikat* - eden od certifikatov, ki jih uporabljajo številne Azure storitve po vsem svetu.

    > 💁 Da preverite, da je to pravi certifikat, zaženite naslednji ukaz na macOS ali Linuxu. Če uporabljate Windows, lahko ta ukaz zaženete z uporabo [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Izhod bo prikazal certifikat DigiCert Global Root G2.

1. Odprite `main.cpp` in dodajte naslednjo direktivo za vključitev:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Pod direktivami za vključitev deklarirajte instanco `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Ta razred vsebuje kodo za komunikacijo s spletnimi končnimi točkami prek HTTPS.

1. V metodi `connectWiFi` nastavite, da `WiFiClientSecure` uporablja certifikat DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Naloga - razvrščanje slike

1. Dodajte naslednjo vrstico na seznam `lib_deps` v datoteki `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    To uvozi [ArduinoJson](https://arduinojson.org), knjižnico JSON za Arduino, ki bo uporabljena za dekodiranje JSON odgovora iz REST API-ja.

1. V `config.h` dodajte konstanti za URL in ključ napovedi iz storitve Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Zamenjajte `<PREDICTION_URL>` z URL-jem napovedi iz Custom Vision. Zamenjajte `<PREDICTION_KEY>` s ključem napovedi.

1. V `main.cpp` dodajte direktivo za vključitev knjižnice ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Dodajte naslednjo funkcijo v `main.cpp`, nad funkcijo `buttonPressed`.

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

    Ta koda začne z deklaracijo `HTTPClient` - razreda, ki vsebuje metode za interakcijo z REST API-ji. Nato poveže odjemalca z URL-jem napovedi z uporabo instance `WiFiClientSecure`, ki je bila nastavljena z javnim ključem Azure.

    Ko je povezava vzpostavljena, pošlje glave - informacije o prihajajoči zahtevi, ki bo izvedena proti REST API-ju. Glava `Content-Type` označuje, da bo API zahteva poslala surove binarne podatke, glava `Prediction-Key` pa posreduje ključ napovedi Custom Vision.

    Nato se izvede POST zahteva na HTTP odjemalca, ki naloži bajtno polje. To bo vsebovalo JPEG sliko, zajeto s kamero, ko je funkcija poklicana.

    > 💁 POST zahteve so namenjene pošiljanju podatkov in pridobivanju odgovora. Obstajajo tudi druge vrste zahtev, kot so GET zahteve, ki pridobivajo podatke. GET zahteve uporablja vaš spletni brskalnik za nalaganje spletnih strani.

    POST zahteva vrne statusno kodo odgovora. To so dobro definirane vrednosti, pri čemer 200 pomeni **OK** - POST zahteva je bila uspešna.

    > 💁 Vse statusne kode odgovorov si lahko ogledate na [strani s seznamom HTTP statusnih kod na Wikipediji](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Če je vrnjena koda 200, se rezultat prebere iz HTTP odjemalca. To je besedilni odgovor iz REST API-ja z rezultati napovedi kot JSON dokument. JSON je v naslednji obliki:

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

    Pomemben del tukaj je polje `predictions`. To vsebuje napovedi, pri čemer vsak vnos za oznako vsebuje ime oznake in verjetnost. Vrnjene verjetnosti so števila s plavajočo vejico od 0-1, kjer 0 pomeni 0% možnosti ujemanja z oznako, 1 pa 100% možnosti.

    > 💁 Razvrščevalniki slik bodo vrnili odstotke za vse uporabljene oznake. Vsaka oznaka bo imela verjetnost, da se slika ujema z njo.

    Ta JSON se dekodira, verjetnosti za vsako oznako pa se pošljejo v serijski monitor.

1. V funkciji `buttonPressed` bodisi zamenjajte kodo, ki shranjuje na SD kartico, z klicem `classifyImage`, ali pa jo dodajte po tem, ko je slika zapisana, vendar **preden** je medpomnilnik izbrisan:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Če zamenjate kodo, ki shranjuje na SD kartico, lahko očistite svojo kodo tako, da odstranite funkciji `setupSDCard` in `saveToSDCard`.

1. Naložite in zaženite svojo kodo. Usmerite kamero proti sadju in pritisnite gumb C. Izhod boste videli v serijskem monitorju:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Videli boste sliko, ki je bila posneta, in te vrednosti v zavihku **Predictions** v Custom Vision.

    ![Banana v Custom Vision napovedana kot zrela s 56,8% in nezrela s 43,1%](../../../../../translated_images/sl/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 To kodo najdete v mapi [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Vaš program za razvrščanje kakovosti sadja je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.