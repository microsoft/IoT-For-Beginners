<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-25T17:13:46+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "it"
}
-->
# Controlla la tua luce notturna tramite Internet - Hardware IoT virtuale e Raspberry Pi

In questa parte della lezione, invierai telemetria con i livelli di luce dal tuo Raspberry Pi o dispositivo IoT virtuale a un broker MQTT.

## Pubblica telemetria

Il prossimo passo è creare un documento JSON con la telemetria e inviarlo al broker MQTT.

### Attività

Pubblica telemetria al broker MQTT.

1. Apri il progetto della luce notturna in VS Code.

1. Se stai utilizzando un dispositivo IoT virtuale, assicurati che il terminale stia eseguendo l'ambiente virtuale. Se stai utilizzando un Raspberry Pi, non utilizzerai un ambiente virtuale.

1. Aggiungi il seguente import all'inizio del file `app.py`:

    ```python
    import json
    ```

    La libreria `json` viene utilizzata per codificare la telemetria come documento JSON.

1. Aggiungi il seguente codice dopo la dichiarazione di `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    Il `client_telemetry_topic` è l'argomento MQTT a cui il dispositivo pubblicherà i livelli di luce.

1. Sostituisci il contenuto del ciclo `while True:` alla fine del file con il seguente:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Questo codice impacchetta il livello di luce in un documento JSON e lo pubblica al broker MQTT. Successivamente, il programma si mette in pausa per ridurre la frequenza con cui i messaggi vengono inviati.

1. Esegui il codice nello stesso modo in cui hai eseguito il codice nella parte precedente dell'assegnamento. Se stai utilizzando un dispositivo IoT virtuale, assicurati che l'app CounterFit sia in esecuzione e che il sensore di luce e il LED siano stati creati sui pin corretti.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Puoi trovare questo codice nella cartella [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) o nella cartella [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Hai inviato con successo la telemetria dal tuo dispositivo.

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.