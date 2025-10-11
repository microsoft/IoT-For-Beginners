<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-10-11T11:19:10+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "et"
}
-->
# Juhi oma öölampi Interneti kaudu - Wio Terminal

Selles õppetunni osas tellid käske, mis saadetakse MQTT brokerilt sinu Wio Terminalile.

## Käskude tellimine

Järgmine samm on tellida käske, mis saadetakse MQTT brokerilt, ja neile vastata.

### Ülesanne

Tellida käske.

1. Ava öölambi projekt VS Code'is.

1. Lisa järgmine kood `config.h` faili lõppu, et määratleda käskude teema nimi:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

   `SERVER_COMMAND_TOPIC` on teema, millele seade tellib LED-käskude vastuvõtmiseks.

1. Lisa järgmine rida `reconnectMQTTClient` funktsiooni lõppu, et tellida käskude teema, kui MQTT klient uuesti ühendatakse:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Lisa järgmine kood `reconnectMQTTClient` funktsiooni alla.

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

   See funktsioon on tagasihelistus, mida MQTT klient kutsub, kui serverilt sõnum saadakse.

   Sõnum saadakse unsigned 8-bitiste täisarvude massiivina, seega tuleb see teisendada tähemärkide massiiviks, et seda tekstina käsitleda.

   Sõnum sisaldab JSON-dokumenti, mis dekodeeritakse ArduinoJson teegi abil. JSON-dokumendi `led_on` omadus loetakse ja sõltuvalt väärtusest lülitatakse LED sisse või välja.

1. Lisa järgmine kood `createMQTTClient` funktsiooni:

    ```cpp
    client.setCallback(clientCallback);
    ```

   See kood määrab `clientCallback` tagasihelistuse, mida kutsutakse, kui MQTT brokerilt sõnum saadakse.

   > 💁 `clientCallback` käsitleja kutsutakse kõigi tellitud teemade jaoks. Kui hiljem kirjutad koodi, mis kuulab mitut teemat, saad teema, millele sõnum saadeti, `topic` parameetrist, mis edastatakse tagasihelistusfunktsioonile.

1. Laadi kood oma Wio Terminalile ja kasuta Serial Monitori, et näha valguse tasemeid, mis saadetakse MQTT brokerile.

1. Kohanda füüsilise või virtuaalse seadme tuvastatud valguse tasemeid. Näed terminalis sõnumeid, mis saadakse ja käske, mis saadetakse. Näed ka, kuidas LED lülitatakse sisse ja välja sõltuvalt valguse tasemest.

> 💁 Selle koodi leiad [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal) kaustast.

😀 Oled edukalt kodeerinud oma seadme vastama käskudele, mis saadetakse MQTT brokerilt.

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.