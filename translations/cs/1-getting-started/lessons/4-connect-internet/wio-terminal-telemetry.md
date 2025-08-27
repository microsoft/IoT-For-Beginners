<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-27T22:14:12+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "cs"
}
-->
# Ovládejte svůj noční světelný zdroj přes internet - Wio Terminal

V této části lekce budete odesílat telemetrii s úrovněmi světla z vašeho Wio Terminalu na MQTT broker.

## Instalace knihoven JSON pro Arduino

Oblíbeným způsobem odesílání zpráv přes MQTT je použití JSON. Existuje knihovna pro Arduino, která usnadňuje čtení a zápis JSON dokumentů.

### Úkol

Nainstalujte knihovnu Arduino JSON.

1. Otevřete projekt nočního světla ve VS Code.

1. Přidejte následující jako další řádek do seznamu `lib_deps` v souboru `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Tímto importujete [ArduinoJson](https://arduinojson.org), knihovnu JSON pro Arduino.

## Publikování telemetrie

Dalším krokem je vytvoření JSON dokumentu s telemetrií a jeho odeslání na MQTT broker.

### Úkol - publikování telemetrie

Publikujte telemetrii na MQTT broker.

1. Přidejte následující kód na konec souboru `config.h`, abyste definovali název tématu telemetrie pro MQTT broker:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` je téma, na které zařízení bude publikovat úrovně světla.

1. Otevřete soubor `main.cpp`.

1. Přidejte následující direktivu `#include` na začátek souboru:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Přidejte následující kód do funkce `loop`, těsně před `delay`:

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

    Tento kód čte úroveň světla, vytvoří JSON dokument pomocí ArduinoJson obsahující tuto úroveň. Poté je serializován do řetězce a publikován na telemetrické MQTT téma pomocí MQTT klienta.

1. Nahrajte kód do svého Wio Terminalu a použijte Serial Monitor k zobrazení úrovní světla odesílaných na MQTT broker.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Tento kód najdete ve složce [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Úspěšně jste odeslali telemetrii ze svého zařízení.

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.