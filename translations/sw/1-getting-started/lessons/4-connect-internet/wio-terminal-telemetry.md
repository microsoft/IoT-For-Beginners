<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-27T22:13:50+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "sw"
}
-->
# Dhibiti taa yako ya usiku kupitia Mtandao - Wio Terminal

Katika sehemu hii ya somo, utatuma data ya telemetry yenye viwango vya mwanga kutoka kwa Wio Terminal yako kwenda kwa MQTT broker.

## Sakinisha maktaba za JSON za Arduino

Njia maarufu ya kutuma ujumbe kupitia MQTT ni kutumia JSON. Kuna maktaba ya Arduino kwa JSON ambayo inarahisisha kusoma na kuandika hati za JSON.

### Kazi

Sakinisha maktaba ya Arduino JSON.

1. Fungua mradi wa nightlight katika VS Code.

1. Ongeza mstari ufuatao kama mstari wa ziada kwenye orodha ya `lib_deps` katika faili ya `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Hii inaingiza [ArduinoJson](https://arduinojson.org), maktaba ya JSON ya Arduino.

## Tuma telemetry

Hatua inayofuata ni kuunda hati ya JSON yenye telemetry na kuituma kwa MQTT broker.

### Kazi - tuma telemetry

Tuma telemetry kwa MQTT broker.

1. Ongeza msimbo ufuatao chini ya faili ya `config.h` ili kufafanua jina la mada ya telemetry kwa MQTT broker:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` ni mada ambayo kifaa kitachapisha viwango vya mwanga.

1. Fungua faili ya `main.cpp`

1. Ongeza agizo la `#include` lifuatalo juu ya faili:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Ongeza msimbo ufuatao ndani ya kazi ya `loop`, kabla tu ya `delay`:

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

    Msimbo huu unasoma kiwango cha mwanga, na kuunda hati ya JSON kwa kutumia ArduinoJson inayojumuisha kiwango hiki. Hati hii kisha inabadilishwa kuwa kamba na kuchapishwa kwenye mada ya telemetry ya MQTT na mteja wa MQTT.

1. Pakia msimbo kwenye Wio Terminal yako, na tumia Serial Monitor kuona viwango vya mwanga vinavyotumwa kwa MQTT broker.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Unaweza kupata msimbo huu katika folda ya [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Umefanikiwa kutuma telemetry kutoka kwa kifaa chako.

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.