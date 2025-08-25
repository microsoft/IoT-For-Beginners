<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-25T17:18:01+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "it"
}
-->
# Controlla la tua luce notturna su Internet - Hardware IoT virtuale e Raspberry Pi

Il dispositivo IoT deve essere programmato per comunicare con *test.mosquitto.org* utilizzando MQTT, al fine di inviare valori di telemetria con la lettura del sensore di luce e ricevere comandi per controllare il LED.

In questa parte della lezione, collegherai il tuo Raspberry Pi o dispositivo IoT virtuale a un broker MQTT.

## Installa il pacchetto client MQTT

Per comunicare con il broker MQTT, è necessario installare una libreria MQTT tramite pip, sia sul tuo Raspberry Pi che nel tuo ambiente virtuale, se stai utilizzando un dispositivo virtuale.

### Attività

Installa il pacchetto pip

1. Apri il progetto della luce notturna in VS Code.

1. Se stai utilizzando un dispositivo IoT virtuale, assicurati che il terminale stia eseguendo l'ambiente virtuale. Se stai utilizzando un Raspberry Pi, non utilizzerai un ambiente virtuale.

1. Esegui il seguente comando per installare il pacchetto pip MQTT:

    ```sh
    pip3 install paho-mqtt
    ```

## Programma il dispositivo

Il dispositivo è pronto per essere programmato.

### Attività

Scrivi il codice del dispositivo.

1. Aggiungi il seguente import all'inizio del file `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    La libreria `paho.mqtt.client` consente alla tua app di comunicare tramite MQTT.

1. Aggiungi il seguente codice dopo le definizioni del sensore di luce e del LED:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Sostituisci `<ID>` con un ID univoco che verrà utilizzato come nome di questo client del dispositivo e successivamente per i topic che questo dispositivo pubblica e sottoscrive. Il broker *test.mosquitto.org* è pubblico e utilizzato da molte persone, inclusi altri studenti che stanno lavorando a questo compito. Avere un nome client MQTT e nomi di topic univoci garantisce che il tuo codice non entri in conflitto con quello di altri. Avrai bisogno di questo ID anche quando creerai il codice del server più avanti in questo compito.

    > 💁 Puoi utilizzare un sito web come [GUIDGen](https://www.guidgen.com) per generare un ID univoco.

    Il `client_name` è un nome univoco per questo client MQTT sul broker.

1. Aggiungi il seguente codice sotto questo nuovo codice per creare un oggetto client MQTT e connetterti al broker MQTT:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Questo codice crea l'oggetto client, si connette al broker MQTT pubblico e avvia un ciclo di elaborazione che viene eseguito in un thread in background, ascoltando i messaggi su qualsiasi topic sottoscritto.

1. Esegui il codice nello stesso modo in cui hai eseguito il codice nella parte precedente del compito. Se stai utilizzando un dispositivo IoT virtuale, assicurati che l'app CounterFit sia in esecuzione e che il sensore di luce e il LED siano stati creati sui pin corretti.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Puoi trovare questo codice nella cartella [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) o nella cartella [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Hai collegato con successo il tuo dispositivo a un broker MQTT.

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.