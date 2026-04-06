# Rileva la prossimità - Hardware IoT Virtuale

In questa parte della lezione, aggiungerai un sensore di prossimità al tuo dispositivo IoT virtuale e leggerai la distanza da esso.

## Hardware

Il dispositivo IoT virtuale utilizzerà un sensore di distanza simulato.

In un dispositivo IoT fisico, utilizzeresti un sensore con un modulo di misurazione laser per rilevare la distanza.

### Aggiungi il sensore di distanza a CounterFit

Per utilizzare un sensore di distanza virtuale, devi aggiungerne uno all'app CounterFit.

#### Attività - aggiungi il sensore di distanza a CounterFit

Aggiungi il sensore di distanza all'app CounterFit.

1. Apri il codice `fruit-quality-detector` in VS Code e assicurati che l'ambiente virtuale sia attivato.

1. Installa un pacchetto Pip aggiuntivo per installare uno shim di CounterFit che può comunicare con i sensori di distanza simulando il pacchetto Pip [rpi-vl53l0x](https://pypi.org/project/rpi-vl53l0x/), un pacchetto Python che interagisce con [un sensore di distanza VL53L0X time-of-flight](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Assicurati di installarlo da un terminale con l'ambiente virtuale attivato.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Assicurati che l'app web CounterFit sia in esecuzione.

1. Crea un sensore di distanza:

    1. Nella casella *Create sensor* nel pannello *Sensors*, apri il menu a tendina *Sensor type* e seleziona *Distance*.

    1. Lascia le *Units* come `Millimeter`.

    1. Questo sensore è un sensore I²C, quindi imposta l'indirizzo su `0x29`. Se utilizzassi un sensore VL53L0X fisico, sarebbe codificato a questo indirizzo.

    1. Seleziona il pulsante **Add** per creare il sensore di distanza.

    ![Le impostazioni del sensore di distanza](../../../../../translated_images/it/counterfit-create-distance-sensor.967c9fb98f27888d.webp)

    Il sensore di distanza verrà creato e apparirà nella lista dei sensori.

    ![Il sensore di distanza creato](../../../../../translated_images/it/counterfit-distance-sensor.079eefeeea0b68af.webp)

## Programma il sensore di distanza

Ora il dispositivo IoT virtuale può essere programmato per utilizzare il sensore di distanza simulato.

### Attività - programma il sensore time-of-flight

1. Crea un nuovo file nel progetto `fruit-quality-detector` chiamato `distance-sensor.py`.

    > 💁 Un modo semplice per simulare più dispositivi IoT è farlo in file Python separati, quindi eseguirli contemporaneamente.

1. Avvia una connessione a CounterFit con il seguente codice:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Aggiungi il seguente codice sotto questo:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Questo importa la libreria shim del sensore VL53L0X time-of-flight.

1. Sotto questo, aggiungi il seguente codice per accedere al sensore:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Questo codice dichiara un sensore di distanza, quindi avvia il sensore.

1. Infine, aggiungi un ciclo infinito per leggere le distanze:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Questo codice attende che un valore sia pronto per essere letto dal sensore, quindi lo stampa sulla console.

1. Esegui questo codice.

    > 💁 Non dimenticare che questo file si chiama `distance-sensor.py`! Assicurati di eseguirlo tramite Python, non `app.py`.

1. Vedrai le misurazioni della distanza apparire nella console. Cambia il valore in CounterFit per vedere questo valore cambiare, oppure usa valori casuali.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Puoi trovare questo codice nella cartella [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 Il tuo programma per il sensore di prossimità è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione AI [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatizzate potrebbero contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.