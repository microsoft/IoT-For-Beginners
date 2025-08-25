<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-25T17:07:37+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "it"
}
-->
# Collega il tuo dispositivo IoT al cloud - Hardware IoT virtuale e Raspberry Pi

In questa parte della lezione, collegherai il tuo dispositivo IoT virtuale o Raspberry Pi al tuo IoT Hub, per inviare telemetria e ricevere comandi.

## Collega il tuo dispositivo a IoT Hub

Il prossimo passo è collegare il tuo dispositivo a IoT Hub.

### Attività - collegarsi a IoT Hub

1. Apri la cartella `soil-moisture-sensor` in VS Code. Assicurati che l'ambiente virtuale sia in esecuzione nel terminale se stai utilizzando un dispositivo IoT virtuale.

1. Installa alcuni pacchetti aggiuntivi di Pip:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` è una libreria per comunicare con il tuo IoT Hub.

1. Aggiungi i seguenti import all'inizio del file `app.py`, sotto gli import esistenti:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Questo codice importa l'SDK per comunicare con il tuo IoT Hub.

1. Rimuovi la riga `import paho.mqtt.client as mqtt` poiché questa libreria non è più necessaria. Rimuovi tutto il codice MQTT, inclusi i nomi dei topic, tutto il codice che utilizza `mqtt_client` e `handle_command`. Mantieni il ciclo `while True:`, ma elimina la riga `mqtt_client.publish` da questo ciclo.

1. Aggiungi il seguente codice sotto le dichiarazioni di import:

    ```python
    connection_string = "<connection string>"
    ```

    Sostituisci `<connection string>` con la stringa di connessione che hai recuperato per il dispositivo in precedenza in questa lezione.

    > 💁 Questo non è una buona pratica. Le stringhe di connessione non dovrebbero mai essere memorizzate nel codice sorgente, poiché potrebbero essere salvate nel controllo del codice sorgente e trovate da chiunque. Lo stiamo facendo qui per semplicità. Idealmente, dovresti utilizzare qualcosa come una variabile d'ambiente e uno strumento come [`python-dotenv`](https://pypi.org/project/python-dotenv/). Imparerai di più su questo in una lezione futura.

1. Sotto questo codice, aggiungi il seguente per creare un oggetto client del dispositivo che possa comunicare con IoT Hub e connetterlo:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Esegui questo codice. Vedrai il tuo dispositivo connettersi.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Invia telemetria

Ora che il tuo dispositivo è connesso, puoi inviare telemetria a IoT Hub invece che al broker MQTT.

### Attività - invia telemetria

1. Aggiungi il seguente codice all'interno del ciclo `while True`, appena prima del comando sleep:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Questo codice crea un `Message` di IoT Hub contenente la lettura dell'umidità del suolo come stringa JSON, quindi lo invia a IoT Hub come messaggio da dispositivo a cloud.

## Gestisci comandi

Il tuo dispositivo deve gestire un comando dal codice del server per controllare il relè. Questo viene inviato come richiesta di metodo diretto.

## Attività - gestire una richiesta di metodo diretto

1. Aggiungi il seguente codice prima del ciclo `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Questo definisce un metodo, `handle_method_request`, che verrà chiamato quando un metodo diretto viene chiamato da IoT Hub. Ogni metodo diretto ha un nome, e questo codice si aspetta un metodo chiamato `relay_on` per accendere il relè e `relay_off` per spegnerlo.

    > 💁 Questo potrebbe anche essere implementato in un singolo metodo diretto, passando lo stato desiderato del relè in un payload che può essere passato con la richiesta del metodo e disponibile dall'oggetto `request`.

1. I metodi diretti richiedono una risposta per informare il codice chiamante che sono stati gestiti. Aggiungi il seguente codice alla fine della funzione `handle_method_request` per creare una risposta alla richiesta:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Questo codice invia una risposta alla richiesta di metodo diretto con un codice di stato HTTP 200 e lo invia a IoT Hub.

1. Aggiungi il seguente codice sotto questa definizione di funzione:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Questo codice dice al client di IoT Hub di chiamare la funzione `handle_method_request` quando viene chiamato un metodo diretto.

> 💁 Puoi trovare questo codice nella cartella [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) o [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Il tuo programma del sensore di umidità del suolo è connesso al tuo IoT Hub!

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.