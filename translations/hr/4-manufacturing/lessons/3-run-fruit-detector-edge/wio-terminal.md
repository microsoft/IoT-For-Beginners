<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-28T12:23:02+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "hr"
}
-->
# Klasificirajte sliku pomoću IoT Edge klasifikatora slika - Wio Terminal

U ovom dijelu lekcije koristit ćete klasifikator slika koji radi na IoT Edge uređaju.

## Koristite IoT Edge klasifikator

IoT uređaj može biti preusmjeren na korištenje IoT Edge klasifikatora slika. URL za klasifikator slika je `http://<IP adresa ili ime>/image`, gdje `<IP adresa ili ime>` treba zamijeniti IP adresom ili nazivom računala na kojem radi IoT Edge.

### Zadatak - koristite IoT Edge klasifikator

1. Otvorite projekt aplikacije `fruit-quality-detector` ako već nije otvoren.

1. Klasifikator slika radi kao REST API koristeći HTTP, a ne HTTPS, pa poziv mora koristiti WiFi klijent koji radi samo s HTTP pozivima. To znači da certifikat nije potreban. Izbrišite `CERTIFICATE` iz datoteke `config.h`.

1. URL za predikciju u datoteci `config.h` treba ažurirati na novi URL. Također možete izbrisati `PREDICTION_KEY` jer nije potreban.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Zamijenite `<URL>` s URL-om vašeg klasifikatora.

1. U datoteci `main.cpp`, promijenite direktivu za uključivanje WiFi Client Secure kako biste uvezli standardnu HTTP verziju:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Promijenite deklaraciju `WiFiClient` na HTTP verziju:

    ```cpp
    WiFiClient client;
    ```

1. Odaberite liniju koja postavlja certifikat na WiFi klijentu. Uklonite liniju `client.setCACert(CERTIFICATE);` iz funkcije `connectWiFi`.

1. U funkciji `classifyImage`, uklonite liniju `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` koja postavlja ključ predikcije u zaglavlje.

1. Prenesite i pokrenite svoj kod. Usmjerite kameru prema nekom voću i pritisnite C gumb. Vidjet ćete izlaz u serijskom monitoru:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Ovaj kod možete pronaći u mapi [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Vaš program za klasifikaciju kvalitete voća bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.