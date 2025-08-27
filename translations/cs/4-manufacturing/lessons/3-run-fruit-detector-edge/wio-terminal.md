<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T20:52:24+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "cs"
}
-->
# Klasifikace obrázku pomocí klasifikátoru obrázků na bázi IoT Edge - Wio Terminal

V této části lekce použijete klasifikátor obrázků běžící na zařízení IoT Edge.

## Použití klasifikátoru IoT Edge

Zařízení IoT může být přesměrováno k použití klasifikátoru obrázků IoT Edge. URL pro klasifikátor obrázků je `http://<IP adresa nebo název>/image`, kde `<IP adresa nebo název>` nahradíte IP adresou nebo názvem hostitele počítače, na kterém běží IoT Edge.

### Úkol - použití klasifikátoru IoT Edge

1. Otevřete projekt aplikace `fruit-quality-detector`, pokud již není otevřený.

1. Klasifikátor obrázků běží jako REST API pomocí HTTP, nikoli HTTPS, takže volání musí používat WiFi klienta, který podporuje pouze HTTP volání. To znamená, že certifikát není potřeba. Odstraňte `CERTIFICATE` ze souboru `config.h`.

1. URL pro predikci v souboru `config.h` je třeba aktualizovat na novou URL. Můžete také odstranit `PREDICTION_KEY`, protože není potřeba.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Nahraďte `<URL>` URL adresou vašeho klasifikátoru.

1. V souboru `main.cpp` změňte direktivu pro zahrnutí WiFi Client Secure tak, aby importovala standardní HTTP verzi:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Změňte deklaraci `WiFiClient` na HTTP verzi:

    ```cpp
    WiFiClient client;
    ```

1. Najděte řádek, který nastavuje certifikát na WiFi klientovi. Odstraňte řádek `client.setCACert(CERTIFICATE);` z funkce `connectWiFi`.

1. Ve funkci `classifyImage` odstraňte řádek `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);`, který nastavuje predikční klíč v hlavičce.

1. Nahrajte a spusťte svůj kód. Namiřte kameru na nějaké ovoce a stiskněte tlačítko C. Výstup uvidíte v sériovém monitoru:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Tento kód najdete ve složce [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Váš program pro klasifikaci kvality ovoce byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.