<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-28T10:14:03+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "sk"
}
-->
# Ovládajte svoje nočné svetlo cez internet - Wio Terminal

V tejto časti lekcie budete posielať telemetriu s úrovňami svetla z vášho Wio Terminal na MQTT broker.

## Nainštalujte knižnice JSON pre Arduino

Populárnym spôsobom posielania správ cez MQTT je použitie JSON. Existuje knižnica pre Arduino, ktorá uľahčuje čítanie a zapisovanie JSON dokumentov.

### Úloha

Nainštalujte knižnicu Arduino JSON.

1. Otvorte projekt nočného svetla vo VS Code.

1. Pridajte nasledujúci riadok do zoznamu `lib_deps` v súbore `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Týmto sa importuje [ArduinoJson](https://arduinojson.org), knižnica JSON pre Arduino.

## Publikovanie telemetrie

Ďalším krokom je vytvorenie JSON dokumentu s telemetriou a jeho odoslanie na MQTT broker.

### Úloha - publikovanie telemetrie

Publikujte telemetriu na MQTT broker.

1. Pridajte nasledujúci kód na koniec súboru `config.h`, aby ste definovali názov témy telemetrie pre MQTT broker:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` je téma, na ktorú zariadenie bude publikovať úrovne svetla.

1. Otvorte súbor `main.cpp`.

1. Pridajte nasledujúci príkaz `#include` na začiatok súboru:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Pridajte nasledujúci kód do funkcie `loop`, tesne pred `delay`:

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

    Tento kód načíta úroveň svetla a vytvorí JSON dokument pomocou ArduinoJson, ktorý obsahuje túto úroveň. Následne sa tento dokument serializuje na reťazec a publikuje na telemetrickú MQTT tému pomocou MQTT klienta.

1. Nahrajte kód do vášho Wio Terminal a použite Serial Monitor na sledovanie úrovní svetla, ktoré sa odosielajú na MQTT broker.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Tento kód nájdete v priečinku [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Úspešne ste odoslali telemetriu zo svojho zariadenia.

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.