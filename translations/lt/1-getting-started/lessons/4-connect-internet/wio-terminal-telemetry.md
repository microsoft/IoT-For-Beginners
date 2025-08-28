<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-28T19:58:13+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "lt"
}
-->
# Valdykite savo naktinę lemputę internetu - Wio Terminal

Šioje pamokos dalyje siųsite telemetriją su šviesos lygiais iš savo Wio Terminal į MQTT brokerį.

## Įdiekite JSON Arduino bibliotekas

Populiarus būdas siųsti pranešimus per MQTT yra naudojant JSON. Yra Arduino biblioteka JSON, kuri palengvina JSON dokumentų skaitymą ir rašymą.

### Užduotis

Įdiekite Arduino JSON biblioteką.

1. Atidarykite naktinės lemputės projektą VS Code.

1. Pridėkite šią eilutę kaip papildomą įrašą į `lib_deps` sąrašą `platformio.ini` faile:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Tai importuoja [ArduinoJson](https://arduinojson.org), Arduino JSON biblioteką.

## Telemetrijos publikavimas

Kitas žingsnis yra sukurti JSON dokumentą su telemetrija ir išsiųsti jį MQTT brokeriui.

### Užduotis - telemetrijos publikavimas

Publikuokite telemetriją MQTT brokeriui.

1. Pridėkite šį kodą į `config.h` failo apačią, kad apibrėžtumėte telemetrijos temos pavadinimą MQTT brokeriui:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` yra tema, kurioje įrenginys publikuos šviesos lygius.

1. Atidarykite `main.cpp` failą.

1. Pridėkite šią `#include` direktyvą failo viršuje:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Pridėkite šį kodą į `loop` funkciją, tiesiai prieš `delay`:

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

    Šis kodas nuskaito šviesos lygį, sukuria JSON dokumentą naudojant ArduinoJson, kuriame yra šis lygis. Tada jis serializuojamas į eilutę ir publikuojamas telemetrijos MQTT temoje per MQTT klientą.

1. Įkelkite kodą į savo Wio Terminal ir naudokite Serial Monitor, kad pamatytumėte, kaip šviesos lygiai siunčiami į MQTT brokerį.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Šį kodą galite rasti [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) aplanke.

😀 Jūs sėkmingai išsiuntėte telemetriją iš savo įrenginio.

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.