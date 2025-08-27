<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-27T21:48:28+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "nl"
}
-->
# Beheer je nachtlampje via het internet - Wio Terminal

In dit deel van de les leer je hoe je commando's die vanaf een MQTT-broker naar je Wio Terminal worden gestuurd, kunt ontvangen.

## Abonneren op commando's

De volgende stap is om je te abonneren op de commando's die door de MQTT-broker worden verzonden en hierop te reageren.

### Taak

Abonneer je op commando's.

1. Open het nachtlampjesproject in VS Code.

1. Voeg de volgende code toe aan de onderkant van het bestand `config.h` om de naam van het onderwerp voor de commando's te definiëren:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    Het `SERVER_COMMAND_TOPIC` is het onderwerp waarop het apparaat zich abonneert om LED-commando's te ontvangen.

1. Voeg de volgende regel toe aan het einde van de functie `reconnectMQTTClient` om je te abonneren op het commando-onderwerp wanneer de MQTT-client opnieuw verbinding maakt:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Voeg de volgende code toe onder de functie `reconnectMQTTClient`.

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

    Deze functie wordt de callback die de MQTT-client aanroept wanneer er een bericht van de server wordt ontvangen.

    Het bericht wordt ontvangen als een array van ongetekende 8-bits gehele getallen en moet worden omgezet naar een karakterarray om als tekst te worden behandeld.

    Het bericht bevat een JSON-document en wordt gedecodeerd met behulp van de ArduinoJson-bibliotheek. De eigenschap `led_on` van het JSON-document wordt gelezen, en afhankelijk van de waarde wordt de LED in- of uitgeschakeld.

1. Voeg de volgende code toe aan de functie `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Deze code stelt de `clientCallback` in als de callback die wordt aangeroepen wanneer er een bericht van de MQTT-broker wordt ontvangen.

    > 💁 De `clientCallback`-handler wordt aangeroepen voor alle onderwerpen waarop je bent geabonneerd. Als je later code schrijft die naar meerdere onderwerpen luistert, kun je het onderwerp waarnaar het bericht is verzonden ophalen via de parameter `topic` die aan de callbackfunctie wordt doorgegeven.

1. Upload de code naar je Wio Terminal en gebruik de Seriële Monitor om de lichtniveaus te zien die naar de MQTT-broker worden verzonden.

1. Pas de lichtniveaus aan die door je fysieke of virtuele apparaat worden gedetecteerd. Je zult berichten zien die worden ontvangen en commando's die in de terminal worden verzonden. Je zult ook zien dat de LED wordt in- of uitgeschakeld afhankelijk van het lichtniveau.

> 💁 Je kunt deze code vinden in de map [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Je hebt je apparaat succesvol geprogrammeerd om te reageren op commando's van een MQTT-broker.

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, willen we u erop wijzen dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor kritieke informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.