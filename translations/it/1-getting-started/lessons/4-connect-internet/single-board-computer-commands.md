<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-25T17:13:19+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "it"
}
-->
# Controlla la tua luce notturna tramite Internet - Hardware IoT virtuale e Raspberry Pi

In questa parte della lezione, ti iscriverai ai comandi inviati da un broker MQTT al tuo Raspberry Pi o dispositivo IoT virtuale.

## Iscriviti ai comandi

Il prossimo passo è iscriversi ai comandi inviati dal broker MQTT e rispondere ad essi.

### Compito

Iscriviti ai comandi.

1. Apri il progetto della luce notturna in VS Code.

1. Se stai utilizzando un dispositivo IoT virtuale, assicurati che il terminale stia eseguendo l'ambiente virtuale. Se stai utilizzando un Raspberry Pi, non utilizzerai un ambiente virtuale.

1. Aggiungi il seguente codice dopo le definizioni di `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    Il `server_command_topic` è l'argomento MQTT a cui il dispositivo si iscriverà per ricevere i comandi LED.

1. Aggiungi il seguente codice appena sopra il ciclo principale, dopo la riga `mqtt_client.loop_start()`:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    Questo codice definisce una funzione, `handle_command`, che legge un messaggio come documento JSON e cerca il valore della proprietà `led_on`. Se è impostato su `True`, il LED viene acceso, altrimenti viene spento.

    Il client MQTT si iscrive all'argomento su cui il server invierà i messaggi e imposta la funzione `handle_command` per essere chiamata quando viene ricevuto un messaggio.

    > 💁 Il gestore `on_message` viene chiamato per tutti gli argomenti a cui ci si iscrive. Se in seguito scrivi codice che ascolta più argomenti, puoi ottenere l'argomento a cui il messaggio è stato inviato dall'oggetto `message` passato alla funzione gestore.

1. Esegui il codice nello stesso modo in cui hai eseguito il codice della parte precedente dell'assegnamento. Se stai utilizzando un dispositivo IoT virtuale, assicurati che l'app CounterFit sia in esecuzione e che il sensore di luce e il LED siano stati creati sui pin corretti.

1. Regola i livelli di luce rilevati dal tuo dispositivo fisico o virtuale. I messaggi ricevuti e i comandi inviati verranno scritti nel terminale. Il LED verrà acceso e spento in base al livello di luce.

> 💁 Puoi trovare questo codice nella cartella [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) o nella cartella [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Hai codificato con successo il tuo dispositivo per rispondere ai comandi di un broker MQTT.

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione AI [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatizzate possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un esperto umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.