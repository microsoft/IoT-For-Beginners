<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-27T20:42:44+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "fi"
}
-->
# Luokittele kuva - Wio Terminal

Tässä osassa oppituntia lähetät kameran ottaman kuvan Custom Vision -palveluun luokiteltavaksi.

## Kuva luokittelu

Custom Vision -palvelussa on REST API, jota voit kutsua Wio Terminalista kuvien luokittelua varten. Tämä REST API on käytettävissä HTTPS-yhteyden kautta - turvallisen HTTP-yhteyden avulla.

Kun käytetään HTTPS-päätepisteitä, asiakaskoodin täytyy pyytää julkisen avaimen varmenne palvelimelta, johon ollaan yhteydessä, ja käyttää sitä liikenteen salaamiseen. Verkkoselaimesi tekee tämän automaattisesti, mutta mikro-ohjaimet eivät. Sinun täytyy pyytää tämä varmenne manuaalisesti ja käyttää sitä turvallisen yhteyden luomiseen REST API:iin. Nämä varmenteet eivät muutu, joten kun sinulla on varmenne, sen voi kovakoodata sovellukseesi.

Varmenteet sisältävät julkisia avaimia, eikä niitä tarvitse pitää salassa. Voit käyttää niitä lähdekoodissasi ja jakaa niitä julkisesti esimerkiksi GitHubissa.

### Tehtävä - SSL-asiakkaan asettaminen

1. Avaa `fruit-quality-detector`-sovellusprojekti, jos se ei ole jo auki.

1. Avaa `config.h`-otsikkotiedosto ja lisää seuraava:

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

    Tämä on *Microsoft Azure DigiCert Global Root G2 -varmenne* - yksi varmenteista, joita monet Azure-palvelut käyttävät maailmanlaajuisesti.

    > 💁 Näet, että tämä on oikea varmenne käyttämällä seuraavaa komentoa macOS- tai Linux-käyttöjärjestelmässä. Jos käytät Windowsia, voit suorittaa tämän komennon [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn) -ympäristössä:
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Tulosteessa näkyy DigiCert Global Root G2 -varmenne.

1. Avaa `main.cpp` ja lisää seuraava include-direktiivi:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Include-direktiivien alapuolella määritä `WifiClientSecure`-instanssi:

    ```cpp
    WiFiClientSecure client;
    ```

    Tämä luokka sisältää koodin verkkopäätepisteiden kanssa kommunikointiin HTTPS:n kautta.

1. `connectWiFi`-metodissa aseta WiFiClientSecure käyttämään DigiCert Global Root G2 -varmennetta:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Tehtävä - kuvan luokittelu

1. Lisää seuraava rivi `lib_deps`-listaan `platformio.ini`-tiedostossa:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Tämä tuo [ArduinoJson](https://arduinojson.org)-kirjaston, joka on Arduino JSON -kirjasto, ja sitä käytetään REST API:n JSON-vastauksen purkamiseen.

1. Lisää `config.h`-tiedostoon vakioita Custom Vision -palvelun ennusteen URL-osoitteelle ja avaimelle:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Korvaa `<PREDICTION_URL>` Custom Visionin ennusteen URL-osoitteella. Korvaa `<PREDICTION_KEY>` ennusteen avaimella.

1. Lisää `main.cpp`-tiedostoon include-direktiivi ArduinoJson-kirjastolle:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Lisää seuraava funktio `main.cpp`-tiedostoon, `buttonPressed`-funktion yläpuolelle:

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

    Tämä koodi aloittaa määrittämällä `HTTPClient`-luokan, joka sisältää metodeja REST API:iden kanssa vuorovaikuttamiseen. Se yhdistää asiakkaan ennusteen URL-osoitteeseen käyttäen aiemmin asetettua `WiFiClientSecure`-instanssia, joka sisältää Azure-julkisen avaimen.

    Kun yhteys on muodostettu, se lähettää otsakkeita - tietoa tulevasta pyynnöstä REST API:lle. `Content-Type`-otsake osoittaa, että API-pyyntö lähettää raakaa binääridataa, ja `Prediction-Key`-otsake välittää Custom Vision -ennusteen avaimen.

    Seuraavaksi tehdään POST-pyyntö HTTP-asiakkaalle, ja lähetetään tavutaulukko. Tämä sisältää kameran ottaman JPEG-kuvan, kun funktiota kutsutaan.

    > 💁 POST-pyynnöt on tarkoitettu datan lähettämiseen ja vastauksen saamiseen. On olemassa myös muita pyyntötyyppejä, kuten GET-pyynnöt, jotka hakevat dataa. GET-pyyntöjä käytetään verkkoselaimessasi verkkosivujen lataamiseen.

    POST-pyyntö palauttaa vastauskoodin. Nämä ovat hyvin määriteltyjä arvoja, joista 200 tarkoittaa **OK** - POST-pyyntö onnistui.

    > 💁 Voit nähdä kaikki vastauskoodit [HTTP-vastauskoodien luettelossa Wikipediassa](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Jos 200 palautetaan, tulos luetaan HTTP-asiakkaalta. Tämä on tekstivastaus REST API:lta, joka sisältää ennusteen tulokset JSON-dokumenttina. JSON on seuraavassa muodossa:

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

    Tärkeä osa tässä on `predictions`-taulukko. Tämä sisältää ennusteet, joissa jokaisessa merkinnässä on tunnisteen nimi ja todennäköisyys. Palautetut todennäköisyydet ovat liukulukuja välillä 0-1, missä 0 tarkoittaa 0 % mahdollisuutta vastata tunnistetta ja 1 tarkoittaa 100 % mahdollisuutta.

    > 💁 Kuvanluokittelijat palauttavat prosentit kaikille käytetyille tunnisteille. Jokaisella tunnisteella on todennäköisyys, että kuva vastaa kyseistä tunnistetta.

    JSON dekoodataan, ja todennäköisyydet jokaiselle tunnisteelle lähetetään sarjamonitoriin.

1. `buttonPressed`-funktiossa korvaa SD-kortille tallentava koodi kutsulla `classifyImage`-funktioon, tai lisää se kuvan tallentamisen jälkeen, mutta **ennen** puskurin poistamista:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Jos korvaat SD-kortille tallentavan koodin, voit siivota koodiasi poistamalla `setupSDCard`- ja `saveToSDCard`-funktiot.

1. Lataa ja suorita koodisi. Suuntaa kamera hedelmään ja paina C-painiketta. Näet tuloksen sarjamonitorissa:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Näet otetun kuvan ja nämä arvot **Predictions**-välilehdellä Custom Visionissa.

    ![Banaani Custom Visionissa ennustettu kypsäksi 56.8 % ja raaksi 43.1 %](../../../../../translated_images/fi/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Löydät tämän koodin [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal)-kansiosta.

😀 Hedelmien laadun luokittelusovelluksesi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.