<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3b2448c7ab4e9673e77e35a50c5e350d",
  "translation_date": "2025-08-25T18:07:03+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/pi-gps-sensor.md",
  "language_code": "it"
}
-->
# Leggere i dati GPS - Raspberry Pi

In questa parte della lezione, aggiungerai un sensore GPS al tuo Raspberry Pi e leggerai i valori da esso.

## Hardware

Il Raspberry Pi necessita di un sensore GPS.

Il sensore che utilizzerai è un [sensore Grove GPS Air530](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Questo sensore può connettersi a più sistemi GPS per ottenere una posizione rapida e precisa. Il sensore è composto da 2 parti: l'elettronica principale del sensore e un'antenna esterna collegata tramite un filo sottile per captare le onde radio dai satelliti.

Si tratta di un sensore UART, quindi invia i dati GPS tramite UART.

## Collegare il sensore GPS

Il sensore GPS Grove può essere collegato al Raspberry Pi.

### Attività - collegare il sensore GPS

Collega il sensore GPS.

![Un sensore GPS Grove](../../../../../translated_images/it/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Inserisci un'estremità di un cavo Grove nella presa del sensore GPS. Il cavo entrerà solo in un verso.

1. Con il Raspberry Pi spento, collega l'altra estremità del cavo Grove alla presa UART contrassegnata **UART** sul Grove Base Hat collegato al Pi. Questa presa si trova nella fila centrale, sul lato più vicino allo slot della scheda SD, opposto alle porte USB e alla presa Ethernet.

    ![Il sensore GPS Grove collegato alla presa UART](../../../../../translated_images/it/pi-gps-sensor.1f99ee2b2f6528915047ec78967bd362e0e4ee0ed594368a3837b9cf9cdaca64.png)

1. Posiziona il sensore GPS in modo che l'antenna collegata abbia visibilità verso il cielo - idealmente vicino a una finestra aperta o all'esterno. È più facile ottenere un segnale chiaro senza ostacoli davanti all'antenna.

## Programmare il sensore GPS

Ora il Raspberry Pi può essere programmato per utilizzare il sensore GPS collegato.

### Attività - programmare il sensore GPS

Programma il dispositivo.

1. Accendi il Pi e attendi che si avvii.

1. Il sensore GPS ha 2 LED: un LED blu che lampeggia quando vengono trasmessi dati e un LED verde che lampeggia ogni secondo quando riceve dati dai satelliti. Assicurati che il LED blu lampeggi quando accendi il Pi. Dopo alcuni minuti, il LED verde inizierà a lampeggiare; se non lo fa, potrebbe essere necessario riposizionare l'antenna.

1. Avvia VS Code, direttamente sul Pi o connettendoti tramite l'estensione Remote SSH.

    > ⚠️ Puoi fare riferimento [alle istruzioni per configurare e avviare VS Code nella lezione 1, se necessario](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Con le versioni più recenti del Raspberry Pi che supportano il Bluetooth, c'è un conflitto tra la porta seriale utilizzata per il Bluetooth e quella utilizzata dalla porta UART del Grove. Per risolvere questo problema, segui i passaggi seguenti:

    1. Dal terminale di VS Code, modifica il file `/boot/config.txt` utilizzando `nano`, un editor di testo integrato nel terminale, con il seguente comando:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Questo file non può essere modificato direttamente da VS Code poiché richiede permessi `sudo`, ovvero permessi elevati. VS Code non utilizza questi permessi.

    1. Usa i tasti del cursore per navigare fino alla fine del file, quindi copia il codice seguente e incollalo alla fine del file:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Puoi incollare utilizzando le scorciatoie da tastiera normali per il tuo dispositivo (`Ctrl+v` su Windows, Linux o Raspberry Pi OS, `Cmd+v` su macOS).

    1. Salva il file ed esci da nano premendo `Ctrl+x`. Premi `y` quando ti viene chiesto se vuoi salvare il buffer modificato, quindi premi `invio` per confermare che vuoi sovrascrivere `/boot/config.txt`.

        > Se commetti un errore, puoi uscire senza salvare e ripetere questi passaggi.

    1. Modifica il file `/boot/cmdline.txt` in nano con il seguente comando:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Questo file contiene una serie di coppie chiave/valore separate da spazi. Rimuovi tutte le coppie chiave/valore per la chiave `console`. Probabilmente avranno un aspetto simile a questo:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Puoi navigare fino a queste voci utilizzando i tasti del cursore, quindi eliminarle utilizzando i tasti `del` o `backspace`.

        Ad esempio, se il tuo file originale appare così:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        La nuova versione sarà:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Segui i passaggi sopra per salvare il file ed uscire da nano.

    1. Riavvia il Pi, quindi riconnettiti a VS Code una volta che il Pi si è riavviato.

1. Dal terminale, crea una nuova cartella nella directory home dell'utente `pi` chiamata `gps-sensor`. Crea un file in questa cartella chiamato `app.py`.

1. Apri questa cartella in VS Code.

1. Il modulo GPS invia dati UART tramite una porta seriale. Installa il pacchetto Pip `pyserial` per comunicare con la porta seriale dal tuo codice Python:

    ```sh
    pip3 install pyserial
    ```

1. Aggiungi il seguente codice al tuo file `app.py`:

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Questo codice importa il modulo `serial` dal pacchetto Pip `pyserial`. Quindi si connette alla porta seriale `/dev/ttyAMA0` - questo è l'indirizzo della porta seriale che il Grove Pi Base Hat utilizza per la sua porta UART. Successivamente, cancella eventuali dati esistenti da questa connessione seriale.

    Successivamente, viene definita una funzione chiamata `print_gps_data` che stampa sulla console la linea passata ad essa.

    Infine, il codice esegue un ciclo infinito, leggendo quante più linee di testo possibile dalla porta seriale in ogni ciclo. Chiama la funzione `print_gps_data` per ogni linea.

    Dopo che tutti i dati sono stati letti, il ciclo dorme per 1 secondo, quindi riprova.

1. Esegui questo codice. Vedrai l'output grezzo del sensore GPS, qualcosa di simile al seguente:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Se ricevi uno dei seguenti errori quando interrompi e riavvii il codice, aggiungi un blocco `try - except` al tuo ciclo while.

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 Puoi trovare questo codice nella cartella [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 Il tuo programma per il sensore GPS è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.