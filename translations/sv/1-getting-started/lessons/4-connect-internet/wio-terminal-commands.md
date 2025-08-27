<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-27T21:49:51+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "sv"
}
-->
# Styr din nattlampa över Internet - Wio Terminal

I den här delen av lektionen kommer du att prenumerera på kommandon som skickas från en MQTT-broker till din Wio Terminal.

## Prenumerera på kommandon

Nästa steg är att prenumerera på kommandon som skickas från MQTT-brokern och svara på dem.

### Uppgift

Prenumerera på kommandon.

1. Öppna nattlampa-projektet i VS Code.

1. Lägg till följande kod längst ner i filen `config.h` för att definiera ämnesnamnet för kommandona:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` är ämnet som enheten kommer att prenumerera på för att ta emot LED-kommandon.

1. Lägg till följande rad i slutet av funktionen `reconnectMQTTClient` för att prenumerera på kommandotemat när MQTT-klienten återansluts:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Lägg till följande kod under funktionen `reconnectMQTTClient`.

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

    Den här funktionen kommer att vara callback-funktionen som MQTT-klienten anropar när den tar emot ett meddelande från servern.

    Meddelandet tas emot som en array av osignerade 8-bitars heltal och måste konverteras till en teckenarray för att behandlas som text.

    Meddelandet innehåller ett JSON-dokument och avkodas med hjälp av ArduinoJson-biblioteket. Egenskapen `led_on` i JSON-dokumentet läses, och beroende på värdet tänds eller släcks LED-lampan.

1. Lägg till följande kod i funktionen `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Den här koden sätter `clientCallback` som callback-funktion som anropas när ett meddelande tas emot från MQTT-brokern.

    > 💁 Callback-funktionen `clientCallback` anropas för alla ämnen som prenumereras på. Om du senare skriver kod som lyssnar på flera ämnen kan du få ämnet som meddelandet skickades till från parametern `topic` som skickas till callback-funktionen.

1. Ladda upp koden till din Wio Terminal och använd Serial Monitor för att se ljusnivåerna som skickas till MQTT-brokern.

1. Justera ljusnivåerna som detekteras av din fysiska eller virtuella enhet. Du kommer att se meddelanden tas emot och kommandon skickas i terminalen. Du kommer också att se att LED-lampan tänds och släcks beroende på ljusnivån.

> 💁 Du kan hitta den här koden i mappen [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Du har framgångsrikt programmerat din enhet att svara på kommandon från en MQTT-broker.

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.