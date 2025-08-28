<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-28T08:37:56+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "ro"
}
-->
# Clasifică o imagine folosind un clasificator de imagini bazat pe IoT Edge - Wio Terminal

În această parte a lecției, vei folosi clasificatorul de imagini care rulează pe dispozitivul IoT Edge.

## Folosește clasificatorul IoT Edge

Dispozitivul IoT poate fi redirecționat pentru a utiliza clasificatorul de imagini IoT Edge. URL-ul pentru clasificatorul de imagini este `http://<IP address or name>/image`, înlocuind `<IP address or name>` cu adresa IP sau numele gazdei computerului care rulează IoT Edge.

### Sarcină - folosește clasificatorul IoT Edge

1. Deschide proiectul aplicației `fruit-quality-detector` dacă nu este deja deschis.

1. Clasificatorul de imagini rulează ca o API REST folosind HTTP, nu HTTPS, așa că apelul trebuie să utilizeze un client WiFi care funcționează doar cu apeluri HTTP. Asta înseamnă că certificatul nu este necesar. Șterge `CERTIFICATE` din fișierul `config.h`.

1. URL-ul pentru predicție din fișierul `config.h` trebuie actualizat la noul URL. De asemenea, poți șterge `PREDICTION_KEY`, deoarece nu este necesar.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Înlocuiește `<URL>` cu URL-ul clasificatorului tău.

1. În `main.cpp`, schimbă directiva include pentru WiFi Client Secure pentru a importa versiunea standard HTTP:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Schimbă declarația `WiFiClient` pentru a folosi versiunea HTTP:

    ```cpp
    WiFiClient client;
    ```

1. Selectează linia care setează certificatul pe clientul WiFi. Elimină linia `client.setCACert(CERTIFICATE);` din funcția `connectWiFi`.

1. În funcția `classifyImage`, elimină linia `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` care setează cheia de predicție în antet.

1. Încarcă și rulează codul tău. Îndreaptă camera spre un fruct și apasă butonul C. Vei vedea rezultatul în monitorul serial:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Poți găsi acest cod în folderul [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Programul tău de clasificare a calității fructelor a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.