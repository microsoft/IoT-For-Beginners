<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-25T17:19:21+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "it"
}
-->
# Controlla la tua luce notturna tramite Internet - Wio Terminal

In questa parte della lezione, ti iscriverai ai comandi inviati da un broker MQTT al tuo Wio Terminal.

## Iscriviti ai comandi

Il passo successivo è iscriversi ai comandi inviati dal broker MQTT e rispondere ad essi.

### Attività

Iscriviti ai comandi.

1. Apri il progetto della luce notturna in VS Code.

1. Aggiungi il seguente codice alla fine del file `config.h` per definire il nome del topic per i comandi:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    Il `SERVER_COMMAND_TOPIC` è il topic a cui il dispositivo si iscriverà per ricevere i comandi per il LED.

1. Aggiungi la seguente riga alla fine della funzione `reconnectMQTTClient` per iscriverti al topic dei comandi quando il client MQTT viene riconnesso:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Aggiungi il seguente codice sotto la funzione `reconnectMQTTClient`.

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

    Questa funzione sarà il callback che il client MQTT chiamerà quando riceverà un messaggio dal server.

    Il messaggio viene ricevuto come un array di interi non firmati a 8 bit, quindi deve essere convertito in un array di caratteri per essere trattato come testo.

    Il messaggio contiene un documento JSON, che viene decodificato utilizzando la libreria ArduinoJson. La proprietà `led_on` del documento JSON viene letta e, a seconda del valore, il LED viene acceso o spento.

1. Aggiungi il seguente codice alla funzione `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Questo codice imposta il `clientCallback` come callback da chiamare quando un messaggio viene ricevuto dal broker MQTT.

    > 💁 Il gestore `clientCallback` viene chiamato per tutti i topic a cui ci si è iscritti. Se in seguito scriverai codice che ascolta più topic, puoi ottenere il topic a cui il messaggio è stato inviato dal parametro `topic` passato alla funzione di callback.

1. Carica il codice sul tuo Wio Terminal e utilizza il Serial Monitor per vedere i livelli di luce inviati al broker MQTT.

1. Regola i livelli di luce rilevati dal tuo dispositivo fisico o virtuale. Vedrai i messaggi ricevuti e i comandi inviati nel terminale. Vedrai anche il LED accendersi e spegnersi a seconda del livello di luce.

> 💁 Puoi trovare questo codice nella cartella [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Hai codificato con successo il tuo dispositivo per rispondere ai comandi di un broker MQTT.

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.