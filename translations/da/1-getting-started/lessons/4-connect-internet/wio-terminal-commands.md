<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-27T21:50:03+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "da"
}
-->
# Styr din natlampe over internettet - Wio Terminal

I denne del af lektionen vil du abonnere på kommandoer sendt fra en MQTT-broker til din Wio Terminal.

## Abonner på kommandoer

Næste trin er at abonnere på de kommandoer, der sendes fra MQTT-brokeren, og reagere på dem.

### Opgave

Abonner på kommandoer.

1. Åbn natlampeprojektet i VS Code.

1. Tilføj følgende kode nederst i `config.h`-filen for at definere emnenavnet for kommandoerne:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` er det emne, som enheden vil abonnere på for at modtage LED-kommandoer.

1. Tilføj følgende linje til slutningen af funktionen `reconnectMQTTClient` for at abonnere på kommandoemnet, når MQTT-klienten genopretter forbindelsen:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Tilføj følgende kode under funktionen `reconnectMQTTClient`.

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

    Denne funktion vil være den callback, som MQTT-klienten kalder, når den modtager en besked fra serveren.

    Beskeden modtages som et array af usignerede 8-bit heltal og skal konverteres til et karakterarray for at blive behandlet som tekst.

    Beskeden indeholder et JSON-dokument, som dekodes ved hjælp af ArduinoJson-biblioteket. `led_on`-egenskaben i JSON-dokumentet læses, og afhængigt af værdien tændes eller slukkes LED'en.

1. Tilføj følgende kode til funktionen `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Denne kode sætter `clientCallback` som den callback, der skal kaldes, når en besked modtages fra MQTT-brokeren.

    > 💁 `clientCallback`-handleren kaldes for alle emner, der er abonneret på. Hvis du senere skriver kode, der lytter til flere emner, kan du få det emne, som beskeden blev sendt til, fra parameteren `topic`, der sendes til callback-funktionen.

1. Upload koden til din Wio Terminal, og brug Serial Monitor til at se lysniveauerne, der sendes til MQTT-brokeren.

1. Juster lysniveauerne, der registreres af din fysiske eller virtuelle enhed. Du vil se beskeder blive modtaget og kommandoer blive sendt i terminalen. Du vil også se LED'en blive tændt og slukket afhængigt af lysniveauet.

> 💁 Du kan finde denne kode i mappen [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Du har med succes kodet din enhed til at reagere på kommandoer fra en MQTT-broker.

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.