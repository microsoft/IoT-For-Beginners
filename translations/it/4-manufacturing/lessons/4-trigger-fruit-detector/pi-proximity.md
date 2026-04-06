# Rileva la prossimità - Raspberry Pi

In questa parte della lezione, aggiungerai un sensore di prossimità al tuo Raspberry Pi e leggerai la distanza da esso.

## Hardware

Il Raspberry Pi necessita di un sensore di prossimità.

Il sensore che utilizzerai è un [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Questo sensore utilizza un modulo di misurazione laser per rilevare la distanza. Ha un intervallo di rilevamento da 10mm a 2000mm (1cm - 2m) e riporta valori in questo intervallo con buona precisione. Le distanze superiori a 1000mm vengono riportate come 8109mm.

Il telemetro laser si trova sul retro del sensore, sul lato opposto rispetto al connettore Grove.

Questo è un sensore I²C.

### Collega il sensore Time of Flight

Il sensore Grove Time of Flight può essere collegato al Raspberry Pi.

#### Attività - collega il sensore Time of Flight

Collega il sensore Time of Flight.

![Un sensore Grove Time of Flight](../../../../../translated_images/it/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Inserisci un'estremità di un cavo Grove nel connettore del sensore Time of Flight. Può essere inserito solo in un modo.

1. Con il Raspberry Pi spento, collega l'altra estremità del cavo Grove a uno dei connettori I²C contrassegnati **I²C** sul Grove Base Hat collegato al Pi. Questi connettori si trovano nella fila inferiore, all'estremità opposta rispetto ai pin GPIO e accanto alla porta del cavo della fotocamera.

![Il sensore Grove Time of Flight collegato al connettore I²C](../../../../../translated_images/it/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Programma il sensore Time of Flight

Ora il Raspberry Pi può essere programmato per utilizzare il sensore Time of Flight collegato.

### Attività - programma il sensore Time of Flight

Programma il dispositivo.

1. Accendi il Raspberry Pi e attendi che si avvii.

1. Apri il codice `fruit-quality-detector` in VS Code, direttamente sul Pi o tramite l'estensione Remote SSH.

1. Installa il pacchetto Pip rpi-vl53l0x, un pacchetto Python che interagisce con un sensore di distanza VL53L0X Time of Flight. Installalo utilizzando questo comando pip:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Crea un nuovo file in questo progetto chiamato `distance-sensor.py`.

    > 💁 Un modo semplice per simulare più dispositivi IoT è creare ciascuno in un file Python separato e poi eseguirli contemporaneamente.

1. Aggiungi il seguente codice a questo file:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Questo importa la libreria Grove I²C bus e una libreria per l'hardware principale del sensore integrato nel sensore Grove Time of Flight.

1. Sotto questo, aggiungi il seguente codice per accedere al sensore:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Questo codice dichiara un sensore di distanza utilizzando il bus Grove I²C e avvia il sensore.

1. Infine, aggiungi un ciclo infinito per leggere le distanze:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Questo codice attende che un valore sia pronto per essere letto dal sensore e poi lo stampa sulla console.

1. Esegui questo codice.

    > 💁 Ricorda che questo file si chiama `distance-sensor.py`! Assicurati di eseguirlo con Python, non con `app.py`.

1. Vedrai apparire le misurazioni della distanza nella console. Posiziona oggetti vicino al sensore e vedrai la misurazione della distanza:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Il telemetro si trova sul retro del sensore, quindi assicurati di utilizzare il lato corretto quando misuri la distanza.

    ![Il telemetro sul retro del sensore Time of Flight puntato verso una banana](../../../../../translated_images/it/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Puoi trovare questo codice nella cartella [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 Il tuo programma per il sensore di prossimità è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.