<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-27T22:10:53+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "sw"
}
-->
# Dhibiti taa yako ya usiku kupitia Mtandao - Wio Terminal

Katika sehemu hii ya somo, utajiunga na amri zinazotumwa kutoka kwa MQTT broker hadi kwenye Wio Terminal yako.

## Jiunge na amri

Hatua inayofuata ni kujiunga na amri zinazotumwa kutoka kwa MQTT broker, na kujibu amri hizo.

### Kazi

Jiunge na amri.

1. Fungua mradi wa taa ya usiku kwenye VS Code.

1. Ongeza msimbo ufuatao chini ya faili ya `config.h` ili kufafanua jina la mada kwa amri:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` ni mada ambayo kifaa kitaunganishwa nayo ili kupokea amri za LED.

1. Ongeza mstari ufuatao mwishoni mwa kazi ya `reconnectMQTTClient` ili kujiunga na mada ya amri wakati mteja wa MQTT anapounganishwa tena:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Ongeza msimbo ufuatao chini ya kazi ya `reconnectMQTTClient`.

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

    Kazi hii itakuwa callback ambayo mteja wa MQTT ataita wakati unapokea ujumbe kutoka kwa seva.

    Ujumbe unapokelewa kama safu ya namba za 8-bit zisizo na ishara, kwa hivyo unahitaji kubadilishwa kuwa safu ya herufi ili kutibiwa kama maandishi.

    Ujumbe unajumuisha hati ya JSON, na inatambuliwa kwa kutumia maktaba ya ArduinoJson. Sifa ya `led_on` ya hati ya JSON inasomwa, na kulingana na thamani yake, LED inawashwa au kuzimwa.

1. Ongeza msimbo ufuatao kwenye kazi ya `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Msimbo huu unaweka `clientCallback` kama callback itakayoitwa wakati ujumbe unapokelewa kutoka kwa MQTT broker.

    > 💁 Mshughulikiaji wa `clientCallback` unaitwa kwa mada zote zilizojiunga. Ikiwa baadaye utaandika msimbo unaosikiliza mada nyingi, unaweza kupata mada ambayo ujumbe ulitumwa kupitia parameter ya `topic` inayopitishwa kwa kazi ya callback.

1. Pakia msimbo kwenye Wio Terminal yako, na tumia Serial Monitor kuona viwango vya mwanga vinavyotumwa kwa MQTT broker.

1. Rekebisha viwango vya mwanga vinavyogunduliwa na kifaa chako halisi au cha kawaida. Utaona ujumbe ukipokelewa na amri zikitumwa kwenye terminal. Pia utaona LED ikiwashwa na kuzimwa kulingana na kiwango cha mwanga.

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Umefanikiwa kuandika msimbo wa kifaa chako ili kujibu amri kutoka kwa MQTT broker.

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.