<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-28T00:27:00+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "tl"
}
-->
# Kontrolin ang Iyong Nightlight sa Internet - Wio Terminal

Sa bahaging ito ng aralin, magpapadala ka ng telemetry na may mga antas ng liwanag mula sa iyong Wio Terminal papunta sa MQTT broker.

## I-install ang JSON Arduino Libraries

Isang popular na paraan ng pagpapadala ng mga mensahe gamit ang MQTT ay sa pamamagitan ng JSON. Mayroong Arduino library para sa JSON na nagpapadali sa pagbabasa at pagsusulat ng mga JSON na dokumento.

### Gawain

I-install ang Arduino JSON library.

1. Buksan ang nightlight project sa VS Code.

1. Idagdag ang sumusunod bilang karagdagang linya sa listahan ng `lib_deps` sa file na `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Ina-import nito ang [ArduinoJson](https://arduinojson.org), isang Arduino JSON library.

## Mag-publish ng Telemetry

Ang susunod na hakbang ay gumawa ng JSON na dokumento na may telemetry at ipadala ito sa MQTT broker.

### Gawain - mag-publish ng telemetry

Mag-publish ng telemetry sa MQTT broker.

1. Idagdag ang sumusunod na code sa ibaba ng file na `config.h` upang tukuyin ang pangalan ng telemetry topic para sa MQTT broker:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    Ang `CLIENT_TELEMETRY_TOPIC` ay ang topic kung saan magpapadala ang device ng mga antas ng liwanag.

1. Buksan ang file na `main.cpp`.

1. Idagdag ang sumusunod na `#include` directive sa itaas ng file:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Idagdag ang sumusunod na code sa loob ng `loop` function, bago ang `delay`:

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

    Binabasa ng code na ito ang antas ng liwanag, at gumagawa ng JSON na dokumento gamit ang ArduinoJson na naglalaman ng antas na ito. Pagkatapos, ito ay isine-serialize sa isang string at ipinapadala sa telemetry MQTT topic gamit ang MQTT client.

1. I-upload ang code sa iyong Wio Terminal, at gamitin ang Serial Monitor upang makita ang mga antas ng liwanag na ipinapadala sa MQTT broker.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Makikita mo ang code na ito sa [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) folder.

😀 Matagumpay kang nakapagpadala ng telemetry mula sa iyong device.

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa orihinal nitong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.