<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-26T06:43:11+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "pl"
}
-->
# Publikowanie temperatury - Wio Terminal

W tej części lekcji opublikujesz wartości temperatury wykryte przez Wio Terminal za pomocą MQTT, aby mogły być później wykorzystane do obliczenia GDD.

## Publikowanie temperatury

Po odczytaniu temperatury można ją opublikować za pomocą MQTT do kodu 'serwera', który odczyta wartości i zapisze je, aby mogły być użyte do obliczeń GDD. Mikrokontrolery nie odczytują czasu z Internetu ani nie śledzą czasu za pomocą zegara czasu rzeczywistego w standardzie, urządzenie musi być zaprogramowane, aby to robić, zakładając, że posiada odpowiedni sprzęt.

Aby uprościć sprawy w tej lekcji, czas nie będzie wysyłany razem z danymi z czujnika, zamiast tego może zostać dodany przez kod serwera później, gdy odbierze wiadomości.

### Zadanie

Zaprogramuj urządzenie, aby publikowało dane o temperaturze.

1. Otwórz projekt `temperature-sensor` dla Wio Terminal.

1. Powtórz kroki, które wykonałeś w lekcji 4, aby połączyć się z MQTT i wysłać dane telemetryczne. Będziesz używać tego samego publicznego brokera Mosquitto.

    Kroki te obejmują:

    - Dodanie bibliotek Seeed WiFi i MQTT do pliku `.ini`
    - Dodanie pliku konfiguracyjnego i kodu do połączenia z WiFi
    - Dodanie kodu do połączenia z brokerem MQTT
    - Dodanie kodu do publikowania danych telemetrycznych

    > ⚠️ Zapoznaj się z [instrukcjami dotyczącymi połączenia z MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) oraz [instrukcjami dotyczącymi wysyłania danych telemetrycznych](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) z lekcji 4, jeśli zajdzie taka potrzeba.

1. Upewnij się, że `CLIENT_NAME` w pliku nagłówkowym `config.h` odzwierciedla ten projekt:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. W przypadku danych telemetrycznych, zamiast wysyłać wartość światła, wyślij wartość temperatury odczytaną z czujnika DHT jako właściwość w dokumencie JSON o nazwie `temperature`, zmieniając funkcję `loop` w `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Wartość temperatury nie musi być odczytywana zbyt często - nie zmienia się znacząco w krótkim czasie, więc ustaw `delay` w funkcji `loop` na 10 minut:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 Funkcja `delay` przyjmuje czas w milisekundach, więc dla ułatwienia odczytu wartość jest przekazywana jako wynik obliczenia. 1,000ms w sekundzie, 60s w minucie, więc 10 x (60s w minucie) x (1000ms w sekundzie) daje opóźnienie 10 minut.

1. Wgraj to na swój Wio Terminal i użyj monitora szeregowego, aby zobaczyć, jak temperatura jest wysyłana do brokera MQTT.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Ten kod znajdziesz w folderze [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Udało Ci się pomyślnie opublikować temperaturę jako dane telemetryczne z Twojego urządzenia.

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia wykonanego przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.