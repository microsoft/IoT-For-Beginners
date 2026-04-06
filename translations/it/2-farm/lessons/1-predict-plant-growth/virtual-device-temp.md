# Misurare la temperatura - Hardware IoT Virtuale

In questa parte della lezione, aggiungerai un sensore di temperatura al tuo dispositivo IoT virtuale.

## Hardware Virtuale

Il dispositivo IoT virtuale utilizzerà un sensore simulato Grove Digital Humidity and Temperature. Questo mantiene il laboratorio simile all'utilizzo di un Raspberry Pi con un sensore fisico Grove DHT11.

Il sensore combina un **sensore di temperatura** con un **sensore di umidità**, ma in questo laboratorio ti interesserà solo la componente del sensore di temperatura. In un dispositivo IoT fisico, il sensore di temperatura sarebbe un [termistore](https://wikipedia.org/wiki/Thermistor) che misura la temperatura rilevando un cambiamento di resistenza al variare della temperatura. I sensori di temperatura sono solitamente sensori digitali che convertono internamente la resistenza misurata in una temperatura in gradi Celsius (o Kelvin, o Fahrenheit).

### Aggiungere i sensori a CounterFit

Per utilizzare un sensore virtuale di umidità e temperatura, devi aggiungere i due sensori all'app CounterFit.

#### Attività - aggiungere i sensori a CounterFit

Aggiungi i sensori di umidità e temperatura all'app CounterFit.

1. Crea una nuova app Python sul tuo computer in una cartella chiamata `temperature-sensor` con un singolo file chiamato `app.py`, un ambiente virtuale Python, e aggiungi i pacchetti pip di CounterFit.

    > ⚠️ Puoi fare riferimento [alle istruzioni per creare e configurare un progetto Python CounterFit nella lezione 1 se necessario](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Installa un pacchetto Pip aggiuntivo per installare uno shim CounterFit per il sensore DHT11. Assicurati di installarlo da un terminale con l'ambiente virtuale attivato.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Assicurati che l'app web CounterFit sia in esecuzione.

1. Crea un sensore di umidità:

    1. Nella casella *Create sensor* nel pannello *Sensors*, apri il menu a tendina *Sensor type* e seleziona *Humidity*.

    1. Lascia le *Units* impostate su *Percentage*.

    1. Assicurati che il *Pin* sia impostato su *5*.

    1. Seleziona il pulsante **Add** per creare il sensore di umidità sul Pin 5.

    ![Impostazioni del sensore di umidità](../../../../../translated_images/it/counterfit-create-humidity-sensor.2750e27b6f30e09c.webp)

    Il sensore di umidità verrà creato e apparirà nella lista dei sensori.

    ![Sensore di umidità creato](../../../../../translated_images/it/counterfit-humidity-sensor.7b12f7f339e430cb.webp)

1. Crea un sensore di temperatura:

    1. Nella casella *Create sensor* nel pannello *Sensors*, apri il menu a tendina *Sensor type* e seleziona *Temperature*.

    1. Lascia le *Units* impostate su *Celsius*.

    1. Assicurati che il *Pin* sia impostato su *6*.

    1. Seleziona il pulsante **Add** per creare il sensore di temperatura sul Pin 6.

    ![Impostazioni del sensore di temperatura](../../../../../translated_images/it/counterfit-create-temperature-sensor.199350ed34f7343d.webp)

    Il sensore di temperatura verrà creato e apparirà nella lista dei sensori.

    ![Sensore di temperatura creato](../../../../../translated_images/it/counterfit-temperature-sensor.f0560236c96a9016.webp)

## Programmare l'app del sensore di temperatura

Ora puoi programmare l'app del sensore di temperatura utilizzando i sensori di CounterFit.

### Attività - programmare l'app del sensore di temperatura

Programma l'app del sensore di temperatura.

1. Assicurati che l'app `temperature-sensor` sia aperta in VS Code.

1. Apri il file `app.py`.

1. Aggiungi il seguente codice all'inizio di `app.py` per connettere l'app a CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Aggiungi il seguente codice al file `app.py` per importare le librerie necessarie:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    L'istruzione `from seeed_dht import DHT` importa la classe `DHT` per interagire con un sensore virtuale Grove di temperatura utilizzando uno shim dal modulo `counterfit_shims_seeed_python_dht`.

1. Aggiungi il seguente codice dopo quello sopra per creare un'istanza della classe che gestisce il sensore virtuale di umidità e temperatura:

    ```python
    sensor = DHT("11", 5)
    ```

    Questo dichiara un'istanza della classe `DHT` che gestisce il sensore virtuale di **U**midità e **T**emperatura **D**igitale. Il primo parametro indica che il sensore utilizzato è un sensore virtuale *DHT11*. Il secondo parametro indica che il sensore è connesso alla porta `5`.

    > 💁 CounterFit simula questo sensore combinato di umidità e temperatura collegandosi a 2 sensori: un sensore di umidità sul pin indicato quando viene creata la classe `DHT`, e un sensore di temperatura che funziona sul pin successivo. Se il sensore di umidità è sul pin 5, lo shim si aspetta che il sensore di temperatura sia sul pin 6.

1. Aggiungi un ciclo infinito dopo il codice sopra per interrogare il valore del sensore di temperatura e stamparlo sulla console:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    La chiamata a `sensor.read()` restituisce una tupla di umidità e temperatura. Ti serve solo il valore della temperatura, quindi l'umidità viene ignorata. Il valore della temperatura viene poi stampato sulla console.

1. Aggiungi una pausa di dieci secondi alla fine del `loop`, poiché i livelli di temperatura non devono essere controllati continuamente. Una pausa riduce il consumo energetico del dispositivo.

    ```python
    time.sleep(10)
    ```

1. Dal terminale di VS Code con un ambiente virtuale attivato, esegui il seguente comando per avviare la tua app Python:

    ```sh
    python app.py
    ```

1. Dall'app CounterFit, modifica il valore del sensore di temperatura che verrà letto dall'app. Puoi farlo in due modi:

    * Inserisci un numero nella casella *Value* del sensore di temperatura, quindi seleziona il pulsante **Set**. Il numero inserito sarà il valore restituito dal sensore.

    * Seleziona la casella *Random*, inserisci un valore *Min* e *Max*, quindi seleziona il pulsante **Set**. Ogni volta che il sensore legge un valore, leggerà un numero casuale tra *Min* e *Max*.

    Dovresti vedere i valori impostati apparire nella console. Modifica il *Value* o le impostazioni *Random* per vedere il valore cambiare.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Puoi trovare questo codice nella cartella [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device).

😀 Il tuo programma del sensore di temperatura è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.