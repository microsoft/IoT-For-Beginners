<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64f18a8f8aaa1fef5e7320e0992d8b3a",
  "translation_date": "2025-08-25T18:03:26+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/virtual-device-gps-sensor.md",
  "language_code": "it"
}
-->
# Leggere dati GPS - Hardware IoT Virtuale

In questa parte della lezione, aggiungerai un sensore GPS al tuo dispositivo IoT virtuale e leggerai i valori da esso.

## Hardware Virtuale

Il dispositivo IoT virtuale utilizzerà un sensore GPS simulato accessibile tramite UART attraverso una porta seriale.

Un sensore GPS fisico avrà un'antenna per captare le onde radio dai satelliti GPS e convertire i segnali GPS in dati GPS. La versione virtuale simula questo permettendoti di impostare una latitudine e una longitudine, inviare frasi NMEA grezze o caricare un file GPX con più posizioni che possono essere restituite in sequenza.

> 🎓 Le frasi NMEA saranno trattate più avanti in questa lezione.

### Aggiungere il sensore a CounterFit

Per utilizzare un sensore GPS virtuale, devi aggiungerne uno all'app CounterFit.

#### Attività - aggiungere il sensore a CounterFit

Aggiungi il sensore GPS all'app CounterFit.

1. Crea una nuova app Python sul tuo computer in una cartella chiamata `gps-sensor` con un singolo file chiamato `app.py` e un ambiente virtuale Python, e aggiungi i pacchetti pip di CounterFit.

    > ⚠️ Puoi fare riferimento [alle istruzioni per creare e configurare un progetto Python CounterFit nella lezione 1, se necessario](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Installa un pacchetto Pip aggiuntivo per installare uno shim di CounterFit che può comunicare con sensori basati su UART tramite una connessione seriale. Assicurati di installarlo da un terminale con l'ambiente virtuale attivato.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Assicurati che l'app web di CounterFit sia in esecuzione.

1. Crea un sensore GPS:

    1. Nella casella *Create sensor* nel pannello *Sensors*, apri il menu a tendina *Sensor type* e seleziona *UART GPS*.

    1. Lascia il *Port* impostato su */dev/ttyAMA0*.

    1. Seleziona il pulsante **Add** per creare il sensore GPS sulla porta `/dev/ttyAMA0`.

    ![Le impostazioni del sensore GPS](../../../../../translated_images/it/counterfit-create-gps-sensor.6385dc9357d85ad1d47b4abb2525e7651fd498917d25eefc5a72feab09eedc70.png)

    Il sensore GPS sarà creato e apparirà nella lista dei sensori.

    ![Il sensore GPS creato](../../../../../translated_images/it/counterfit-gps-sensor.3fbb15af0a5367566f2f11324ef5a6f30861cdf2b497071a5e002b7aa473550e.png)

## Programmare il sensore GPS

Ora il dispositivo IoT virtuale può essere programmato per utilizzare il sensore GPS virtuale.

### Attività - programmare il sensore GPS

Programma l'app del sensore GPS.

1. Assicurati che l'app `gps-sensor` sia aperta in VS Code.

1. Apri il file `app.py`.

1. Aggiungi il seguente codice all'inizio di `app.py` per connettere l'app a CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Aggiungi il seguente codice sotto questo per importare alcune librerie necessarie, inclusa la libreria per la porta seriale di CounterFit:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Questo codice importa il modulo `serial` dal pacchetto Pip `counterfit_shims_serial`. Successivamente si connette alla porta seriale `/dev/ttyAMA0`, che è l'indirizzo della porta seriale utilizzata dal sensore GPS virtuale per la sua porta UART.

1. Aggiungi il seguente codice sotto questo per leggere dalla porta seriale e stampare i valori sulla console:

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Viene definita una funzione chiamata `print_gps_data` che stampa sulla console la linea passata come parametro.

    Successivamente, il codice esegue un ciclo infinito, leggendo quante più linee di testo possibile dalla porta seriale in ogni ciclo. Chiama la funzione `print_gps_data` per ogni linea.

    Dopo che tutti i dati sono stati letti, il ciclo si interrompe per 1 secondo, quindi riprende.

1. Esegui questo codice, assicurandoti di utilizzare un terminale diverso da quello in cui l'app CounterFit è in esecuzione, in modo che l'app CounterFit rimanga attiva.

1. Dall'app CounterFit, modifica il valore del sensore GPS. Puoi farlo in uno dei seguenti modi:

    * Imposta la **Source** su `Lat/Lon` e specifica una latitudine, una longitudine e il numero di satelliti utilizzati per ottenere il fix GPS. Questo valore verrà inviato solo una volta, quindi seleziona la casella **Repeat** per far sì che i dati si ripetano ogni secondo.

      ![Il sensore GPS con lat lon selezionato](../../../../../translated_images/it/counterfit-gps-sensor-latlon.008c867d75464fbe7f84107cc57040df565ac07cb57d2f21db37d087d470197d.png)

    * Imposta la **Source** su `NMEA` e aggiungi alcune frasi NMEA nella casella di testo. Tutti questi valori verranno inviati, con un intervallo di 1 secondo prima che ogni nuova frase GGA (fix di posizione) possa essere letta.

      ![Il sensore GPS con frasi NMEA impostate](../../../../../translated_images/it/counterfit-gps-sensor-nmea.c62eea442171e17e19528b051b104cfcecdc9cd18db7bc72920f29821ae63f73.png)

      Puoi utilizzare uno strumento come [nmeagen.org](https://www.nmeagen.org) per generare queste frasi disegnando su una mappa. Questi valori verranno inviati solo una volta, quindi seleziona la casella **Repeat** per far sì che i dati si ripetano un secondo dopo che tutti sono stati inviati.

    * Imposta la **Source** su GPX file e carica un file GPX con posizioni di tracciamento. Puoi scaricare file GPX da numerosi siti di mappe e escursionismo popolari, come [AllTrails](https://www.alltrails.com/). Questi file contengono più posizioni GPS come un percorso, e il sensore GPS restituirà ogni nuova posizione a intervalli di 1 secondo.

      ![Il sensore GPS con un file GPX impostato](../../../../../translated_images/it/counterfit-gps-sensor-gpxfile.8310b063ce8a425ccc8ebeec8306aeac5e8e55207f007d52c6e1194432a70cd9.png)

      Questi valori verranno inviati solo una volta, quindi seleziona la casella **Repeat** per far sì che i dati si ripetano un secondo dopo che tutti sono stati inviati.

    Una volta configurate le impostazioni GPS, seleziona il pulsante **Set** per confermare questi valori nel sensore.

1. Vedrai l'output grezzo del sensore GPS, qualcosa di simile al seguente:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Puoi trovare questo codice nella cartella [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device).

😀 Il tuo programma per il sensore GPS è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche potrebbero contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.