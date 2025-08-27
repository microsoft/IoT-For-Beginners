<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-27T21:50:12+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "no"
}
-->
# Styr nattlampen din over Internett - Wio Terminal

I denne delen av leksjonen vil du abonnere på kommandoer sendt fra en MQTT-broker til din Wio Terminal.

## Abonner på kommandoer

Neste steg er å abonnere på kommandoene som sendes fra MQTT-brokeren, og svare på dem.

### Oppgave

Abonner på kommandoer.

1. Åpne nattlampe-prosjektet i VS Code.

1. Legg til følgende kode nederst i `config.h`-filen for å definere emnenavnet for kommandoene:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` er emnet som enheten vil abonnere på for å motta LED-kommandoer.

1. Legg til følgende linje på slutten av `reconnectMQTTClient`-funksjonen for å abonnere på kommandoemnet når MQTT-klienten kobles til igjen:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Legg til følgende kode under `reconnectMQTTClient`-funksjonen:

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

    Denne funksjonen vil være callback-funksjonen som MQTT-klienten kaller når den mottar en melding fra serveren.

    Meldingen mottas som et array av usignerte 8-bits heltall, og må konverteres til et tegnarray for å behandles som tekst.

    Meldingen inneholder et JSON-dokument, som dekodes ved hjelp av ArduinoJson-biblioteket. `led_on`-egenskapen i JSON-dokumentet leses, og avhengig av verdien slås LED-en av eller på.

1. Legg til følgende kode i `createMQTTClient`-funksjonen:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Denne koden setter `clientCallback` som callback-funksjonen som skal kalles når en melding mottas fra MQTT-brokeren.

    > 💁 `clientCallback`-handleren kalles for alle emner det abonneres på. Hvis du senere skriver kode som lytter til flere emner, kan du hente emnet meldingen ble sendt til fra `topic`-parameteren som sendes til callback-funksjonen.

1. Last opp koden til din Wio Terminal, og bruk Serial Monitor for å se lysnivåene som sendes til MQTT-brokeren.

1. Juster lysnivåene som oppdages av din fysiske eller virtuelle enhet. Du vil se meldinger bli mottatt og kommandoer bli sendt i terminalen. Du vil også se at LED-en slås av og på avhengig av lysnivået.

> 💁 Du finner denne koden i [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal)-mappen.

😀 Du har nå kodet enheten din til å svare på kommandoer fra en MQTT-broker.

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.