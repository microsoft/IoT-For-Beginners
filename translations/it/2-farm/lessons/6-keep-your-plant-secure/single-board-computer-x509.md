<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-25T17:12:06+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "it"
}
-->
# Utilizzare il certificato X.509 nel codice del dispositivo - Hardware IoT Virtuale e Raspberry Pi

In questa parte della lezione, collegherai il tuo dispositivo IoT virtuale o Raspberry Pi al tuo IoT Hub utilizzando il certificato X.509.

## Collegare il dispositivo a IoT Hub

Il prossimo passo è collegare il tuo dispositivo a IoT Hub utilizzando i certificati X.509.

### Attività - collegarsi a IoT Hub

1. Copia i file della chiave e del certificato nella cartella contenente il codice del tuo dispositivo IoT. Se stai utilizzando un Raspberry Pi tramite VS Code Remote SSH e hai creato le chiavi sul tuo PC o Mac, puoi trascinare e rilasciare i file nell'esploratore di VS Code per copiarli.

1. Apri il file `app.py`

1. Per connetterti utilizzando un certificato X.509, avrai bisogno del nome host dell'IoT Hub e del certificato X.509. Inizia creando una variabile contenente il nome host aggiungendo il seguente codice prima che venga creato il client del dispositivo:

    ```python
    host_name = "<host_name>"
    ```

    Sostituisci `<host_name>` con il nome host del tuo IoT Hub. Puoi ottenerlo dalla sezione `HostName` nella `connection_string`. Sarà il nome del tuo IoT Hub, terminando con `.azure-devices.net`.

1. Sotto questo, dichiara una variabile con l'ID del dispositivo:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Avrai bisogno di un'istanza della classe `X509` contenente i file X.509. Aggiungi `X509` alla lista delle classi importate dal modulo `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Crea un'istanza della classe `X509` utilizzando i tuoi file di certificato e chiave aggiungendo questo codice sotto la dichiarazione di `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Questo creerà la classe `X509` utilizzando i file `soil-moisture-sensor-x509-cert.pem` e `soil-moisture-sensor-x509-key.pem` creati in precedenza.

1. Sostituisci la riga di codice che crea il `device_client` da una connection string con il seguente:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Questo si connetterà utilizzando il certificato X.509 invece di una connection string.

1. Elimina la riga con la variabile `connection_string`.

1. Esegui il tuo codice. Monitora i messaggi inviati a IoT Hub e invia richieste di metodo diretto come prima. Vedrai il dispositivo connettersi e inviare letture di umidità del suolo, oltre a ricevere richieste di metodo diretto.

> 💁 Puoi trovare questo codice nella cartella [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) o [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 Il programma del tuo sensore di umidità del suolo è connesso al tuo IoT Hub utilizzando un certificato X.509!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.