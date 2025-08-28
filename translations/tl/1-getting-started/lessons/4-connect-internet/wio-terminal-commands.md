<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-28T00:23:36+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "tl"
}
-->
# Kontrolin ang iyong nightlight gamit ang Internet - Wio Terminal

Sa bahaging ito ng aralin, mag-subscribe ka sa mga utos na ipinapadala mula sa isang MQTT broker papunta sa iyong Wio Terminal.

## Mag-subscribe sa mga utos

Ang susunod na hakbang ay mag-subscribe sa mga utos na ipinapadala mula sa MQTT broker, at tumugon sa mga ito.

### Gawain

Mag-subscribe sa mga utos.

1. Buksan ang nightlight project sa VS Code.

1. Idagdag ang sumusunod na code sa ibaba ng file na `config.h` upang tukuyin ang pangalan ng topic para sa mga utos:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    Ang `SERVER_COMMAND_TOPIC` ay ang topic na susubaybayan ng device upang makatanggap ng mga utos para sa LED.

1. Idagdag ang sumusunod na linya sa dulo ng function na `reconnectMQTTClient` upang mag-subscribe sa command topic kapag muling nakakonekta ang MQTT client:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Idagdag ang sumusunod na code sa ibaba ng function na `reconnectMQTTClient`.

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    Ang function na ito ang magiging callback na tatawagin ng MQTT client kapag nakatanggap ito ng mensahe mula sa server.

    Ang mensahe ay natatanggap bilang isang array ng unsigned 8-bit integers, kaya kailangang i-convert ito sa isang character array upang ma-trato bilang teksto.

    Ang mensahe ay naglalaman ng isang JSON document, at ito ay dine-decode gamit ang ArduinoJson library. Ang `led_on` na property ng JSON document ay binabasa, at depende sa halaga nito, ang LED ay binubuksan o pinapatay.

1. Idagdag ang sumusunod na code sa function na `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Ang code na ito ay nagse-set ng `clientCallback` bilang callback na tatawagin kapag may natanggap na mensahe mula sa MQTT broker.

    > 💁 Ang `clientCallback` handler ay tinatawag para sa lahat ng topics na naka-subscribe. Kung magsusulat ka ng code na nakikinig sa maraming topics sa hinaharap, maaari mong makuha ang topic kung saan ipinadala ang mensahe mula sa `topic` parameter na ipinapasa sa callback function.

1. I-upload ang code sa iyong Wio Terminal, at gamitin ang Serial Monitor upang makita ang mga light level na ipinapadala sa MQTT broker.

1. I-adjust ang light levels na nadedetect ng iyong pisikal o virtual na device. Makikita mo ang mga mensaheng natatanggap at mga utos na ipinapadala sa terminal. Makikita mo rin ang LED na binubuksan at pinapatay depende sa light level.

> 💁 Maaari mong makita ang code na ito sa [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal) na folder.

😀 Matagumpay mong na-program ang iyong device upang tumugon sa mga utos mula sa isang MQTT broker.

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.