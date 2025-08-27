<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-27T21:52:46+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "sv"
}
-->
# Styr din nattlampa över Internet - Wio Terminal

I denna del av lektionen kommer du att skicka telemetri med ljusnivåer från din Wio Terminal till MQTT-brokern.

## Installera JSON Arduino-bibliotek

Ett populärt sätt att skicka meddelanden över MQTT är att använda JSON. Det finns ett Arduino-bibliotek för JSON som gör det enklare att läsa och skriva JSON-dokument.

### Uppgift

Installera Arduino JSON-biblioteket.

1. Öppna nattlampa-projektet i VS Code.

1. Lägg till följande som en extra rad i listan `lib_deps` i filen `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Detta importerar [ArduinoJson](https://arduinojson.org), ett Arduino JSON-bibliotek.

## Publicera telemetri

Nästa steg är att skapa ett JSON-dokument med telemetri och skicka det till MQTT-brokern.

### Uppgift - publicera telemetri

Publicera telemetri till MQTT-brokern.

1. Lägg till följande kod längst ner i filen `config.h` för att definiera telemetriämnets namn för MQTT-brokern:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` är ämnet som enheten kommer att publicera ljusnivåer till.

1. Öppna filen `main.cpp`

1. Lägg till följande `#include`-direktiv högst upp i filen:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Lägg till följande kod inuti funktionen `loop`, precis före `delay`:

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

    Denna kod läser ljusnivån och skapar ett JSON-dokument med ArduinoJson som innehåller denna nivå. Detta serialiseras sedan till en sträng och publiceras på telemetri-MQTT-ämnet av MQTT-klienten.

1. Ladda upp koden till din Wio Terminal och använd Serial Monitor för att se ljusnivåerna som skickas till MQTT-brokern.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Du kan hitta denna kod i mappen [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Du har framgångsrikt skickat telemetri från din enhet.

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiska översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.