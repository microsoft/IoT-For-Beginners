<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-26T07:00:19+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "pl"
}
-->
# Steruj swoją lampką nocną przez Internet - Wio Terminal

W tej części lekcji wyślesz dane telemetryczne dotyczące poziomu światła z Wio Terminal do brokera MQTT.

## Zainstaluj biblioteki JSON dla Arduino

Popularnym sposobem przesyłania wiadomości przez MQTT jest użycie JSON. Istnieje biblioteka Arduino dla JSON, która ułatwia odczytywanie i zapisywanie dokumentów JSON.

### Zadanie

Zainstaluj bibliotekę Arduino JSON.

1. Otwórz projekt lampki nocnej w VS Code.

1. Dodaj następującą linię do listy `lib_deps` w pliku `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    To importuje [ArduinoJson](https://arduinojson.org), bibliotekę JSON dla Arduino.

## Publikowanie danych telemetrycznych

Kolejnym krokiem jest utworzenie dokumentu JSON z danymi telemetrycznymi i wysłanie go do brokera MQTT.

### Zadanie - publikowanie danych telemetrycznych

Publikuj dane telemetryczne do brokera MQTT.

1. Dodaj poniższy kod na końcu pliku `config.h`, aby zdefiniować nazwę tematu telemetrycznego dla brokera MQTT:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` to temat, na który urządzenie będzie publikować poziomy światła.

1. Otwórz plik `main.cpp`.

1. Dodaj następującą dyrektywę `#include` na początku pliku:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Dodaj poniższy kod wewnątrz funkcji `loop`, tuż przed `delay`:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    Ten kod odczytuje poziom światła i tworzy dokument JSON za pomocą ArduinoJson, który zawiera ten poziom. Następnie jest on serializowany do ciągu znaków i publikowany na temacie telemetrycznym MQTT przez klienta MQTT.

1. Wgraj kod na swój Wio Terminal i użyj Monitora Szeregowego, aby zobaczyć poziomy światła wysyłane do brokera MQTT.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Ten kod znajdziesz w folderze [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Udało Ci się pomyślnie wysłać dane telemetryczne z urządzenia.

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia wykonanego przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.