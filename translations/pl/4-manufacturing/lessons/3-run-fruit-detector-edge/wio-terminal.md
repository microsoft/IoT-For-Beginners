<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-26T06:37:41+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "pl"
}
-->
# Klasyfikacja obrazu za pomocą klasyfikatora obrazów opartego na IoT Edge - Wio Terminal

W tej części lekcji użyjesz klasyfikatora obrazów działającego na urządzeniu IoT Edge.

## Użyj klasyfikatora IoT Edge

Urządzenie IoT może zostać przekierowane do użycia klasyfikatora obrazów IoT Edge. URL dla klasyfikatora obrazów to `http://<adres IP lub nazwa>/image`, gdzie `<adres IP lub nazwa>` należy zastąpić adresem IP lub nazwą hosta komputera, na którym działa IoT Edge.

### Zadanie - użycie klasyfikatora IoT Edge

1. Otwórz projekt aplikacji `fruit-quality-detector`, jeśli nie jest już otwarty.

1. Klasyfikator obrazów działa jako REST API używając HTTP, a nie HTTPS, więc wywołanie musi korzystać z klienta WiFi, który obsługuje tylko połączenia HTTP. Oznacza to, że certyfikat nie jest potrzebny. Usuń `CERTIFICATE` z pliku `config.h`.

1. URL predykcji w pliku `config.h` musi zostać zaktualizowany do nowego URL. Możesz również usunąć `PREDICTION_KEY`, ponieważ nie jest potrzebny.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Zamień `<URL>` na URL swojego klasyfikatora.

1. W pliku `main.cpp` zmień dyrektywę include dla WiFi Client Secure, aby zaimportować standardową wersję HTTP:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Zmień deklarację `WiFiClient` na wersję HTTP:

    ```cpp
    WiFiClient client;
    ```

1. Znajdź linię, która ustawia certyfikat na kliencie WiFi. Usuń linię `client.setCACert(CERTIFICATE);` z funkcji `connectWiFi`.

1. W funkcji `classifyImage` usuń linię `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);`, która ustawia klucz predykcji w nagłówku.

1. Wgraj i uruchom swój kod. Skieruj kamerę na jakiś owoc i naciśnij przycisk C. Zobaczysz wynik w monitorze szeregowym:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Kod znajdziesz w folderze [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Twój program klasyfikatora jakości owoców zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.