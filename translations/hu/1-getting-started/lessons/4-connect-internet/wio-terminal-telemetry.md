<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-27T22:13:59+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "hu"
}
-->
# Vezéreld az éjszakai fényedet az interneten keresztül - Wio Terminal

Ebben a leckében a Wio Terminal fényerősségi adatait fogod elküldeni az MQTT brokerhez.

## Telepítsd a JSON Arduino könyvtárakat

Az MQTT-n keresztüli üzenetküldés egyik népszerű módja a JSON használata. Van egy Arduino könyvtár a JSON-hoz, amely megkönnyíti a JSON dokumentumok olvasását és írását.

### Feladat

Telepítsd az Arduino JSON könyvtárat.

1. Nyisd meg a nightlight projektet a VS Code-ban.

1. Add hozzá a következő sort a `lib_deps` listához a `platformio.ini` fájlban:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Ez importálja az [ArduinoJson](https://arduinojson.org) könyvtárat, amely egy Arduino JSON könyvtár.

## Telemetria küldése

A következő lépés egy JSON dokumentum létrehozása a telemetria adatokkal, majd ezek elküldése az MQTT brokerhez.

### Feladat - telemetria küldése

Küldj telemetria adatokat az MQTT brokerhez.

1. Add hozzá a következő kódot a `config.h` fájl aljára, hogy meghatározd a telemetria témájának nevét az MQTT broker számára:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    A `CLIENT_TELEMETRY_TOPIC` az a téma, amelyre az eszköz a fényerősségi adatokat fogja küldeni.

1. Nyisd meg a `main.cpp` fájlt.

1. Add hozzá a következő `#include` direktívát a fájl tetejére:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Add hozzá a következő kódot a `loop` függvénybe, közvetlenül a `delay` előtt:

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

    Ez a kód beolvassa a fényerősséget, és létrehoz egy JSON dokumentumot az ArduinoJson segítségével, amely tartalmazza ezt az értéket. Ezután a dokumentumot sztringgé alakítja, és elküldi az MQTT kliens által a telemetria MQTT témára.

1. Töltsd fel a kódot a Wio Terminal eszközödre, és használd a Serial Monitor-t, hogy lásd, hogyan küldi el az eszköz a fényerősségi adatokat az MQTT brokerhez.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Ezt a kódot megtalálod a [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) mappában.

😀 Sikeresen elküldted a telemetria adatokat az eszközödről.

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.