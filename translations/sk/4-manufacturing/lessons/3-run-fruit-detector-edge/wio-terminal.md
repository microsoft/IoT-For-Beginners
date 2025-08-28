<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-28T08:37:40+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "sk"
}
-->
# Klasifikácia obrázku pomocou IoT Edge založeného klasifikátora obrázkov - Wio Terminal

V tejto časti lekcie použijete klasifikátor obrázkov bežiaci na zariadení IoT Edge.

## Použitie klasifikátora IoT Edge

IoT zariadenie môže byť presmerované na použitie klasifikátora obrázkov IoT Edge. URL pre klasifikátor obrázkov je `http://<IP adresa alebo názov>/image`, kde `<IP adresa alebo názov>` nahradíte IP adresou alebo názvom hostiteľa počítača, na ktorom beží IoT Edge.

### Úloha - použitie klasifikátora IoT Edge

1. Otvorte projekt aplikácie `fruit-quality-detector`, ak ešte nie je otvorený.

1. Klasifikátor obrázkov beží ako REST API pomocou HTTP, nie HTTPS, takže volanie musí používať WiFi klienta, ktorý pracuje iba s HTTP volaniami. To znamená, že certifikát nie je potrebný. Odstráňte `CERTIFICATE` zo súboru `config.h`.

1. URL predikcie v súbore `config.h` je potrebné aktualizovať na novú URL. Môžete tiež odstrániť `PREDICTION_KEY`, pretože nie je potrebný.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Nahraďte `<URL>` URL adresou vášho klasifikátora.

1. V súbore `main.cpp` zmeňte direktívu pre import WiFi Client Secure na import štandardnej HTTP verzie:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Zmeňte deklaráciu `WiFiClient` na HTTP verziu:

    ```cpp
    WiFiClient client;
    ```

1. Vyberte riadok, ktorý nastavuje certifikát na WiFi klientovi. Odstráňte riadok `client.setCACert(CERTIFICATE);` z funkcie `connectWiFi`.

1. Vo funkcii `classifyImage` odstráňte riadok `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);`, ktorý nastavuje predikčný kľúč v hlavičke.

1. Nahrajte a spustite svoj kód. Namierte kameru na nejaké ovocie a stlačte tlačidlo C. Výstup uvidíte v sériovom monitore:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Tento kód nájdete v priečinku [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Program na klasifikáciu kvality ovocia bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.