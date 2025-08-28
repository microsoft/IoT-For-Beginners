<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-28T19:08:23+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "lt"
}
-->
# Klasifikuokite vaizdą naudodami IoT Edge pagrįstą vaizdų klasifikatorių - Wio Terminal

Šioje pamokos dalyje naudosite vaizdų klasifikatorių, veikiantį IoT Edge įrenginyje.

## Naudokite IoT Edge klasifikatorių

IoT įrenginys gali būti nukreiptas naudoti IoT Edge vaizdų klasifikatorių. Vaizdų klasifikatoriaus URL yra `http://<IP adresas arba pavadinimas>/image`, kur `<IP adresas arba pavadinimas>` pakeičiamas į kompiuterio, kuriame veikia IoT Edge, IP adresą arba pavadinimą.

### Užduotis - naudokite IoT Edge klasifikatorių

1. Atidarykite `fruit-quality-detector` programos projektą, jei jis dar neatidarytas.

1. Vaizdų klasifikatorius veikia kaip REST API, naudojantis HTTP, o ne HTTPS, todėl užklausa turi naudoti WiFi klientą, kuris veikia tik su HTTP užklausomis. Tai reiškia, kad sertifikatas nereikalingas. Ištrinkite `CERTIFICATE` iš `config.h` failo.

1. `config.h` faile esantis prognozės URL turi būti atnaujintas į naują URL. Taip pat galite ištrinti `PREDICTION_KEY`, nes jis nereikalingas.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Pakeiskite `<URL>` į savo klasifikatoriaus URL.

1. `main.cpp` faile pakeiskite WiFi Client Secure įtraukimo direktyvą, kad būtų importuota standartinė HTTP versija:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Pakeiskite `WiFiClient` deklaraciją į HTTP versiją:

    ```cpp
    WiFiClient client;
    ```

1. Suraskite eilutę, kuri nustato sertifikatą WiFi klientui. Ištrinkite eilutę `client.setCACert(CERTIFICATE);` iš `connectWiFi` funkcijos.

1. `classifyImage` funkcijoje pašalinkite eilutę `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);`, kuri nustato prognozės raktą antraštėje.

1. Įkelkite ir paleiskite savo kodą. Nukreipkite kamerą į vaisių ir paspauskite C mygtuką. Rezultatus pamatysite serijiniame monitoriuje:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Šį kodą galite rasti [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) aplanke.

😀 Jūsų vaisių kokybės klasifikatoriaus programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.