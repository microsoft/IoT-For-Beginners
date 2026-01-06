<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-25T18:02:45+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "it"
}
-->
# Leggere i dati GPS - Wio Terminal

In questa parte della lezione, aggiungerai un sensore GPS al tuo Wio Terminal e leggerai i valori da esso.

## Hardware

Il Wio Terminal necessita di un sensore GPS.

Il sensore che utilizzerai è un [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Questo sensore può connettersi a più sistemi GPS per ottenere una posizione rapida e precisa. Il sensore è composto da 2 parti: l'elettronica principale del sensore e un'antenna esterna collegata tramite un filo sottile per captare le onde radio dai satelliti.

Questo è un sensore UART, quindi invia i dati GPS tramite UART.

### Collegare il sensore GPS

Il sensore Grove GPS può essere collegato al Wio Terminal.

#### Attività - collegare il sensore GPS

Collega il sensore GPS.

![Un sensore Grove GPS](../../../../../translated_images/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.it.png)

1. Inserisci un'estremità di un cavo Grove nella presa del sensore GPS. Può essere inserito solo in un verso.

1. Con il Wio Terminal scollegato dal computer o da altre fonti di alimentazione, collega l'altra estremità del cavo Grove alla presa Grove sul lato sinistro del Wio Terminal, guardando lo schermo. Questa è la presa più vicina al pulsante di accensione.

    ![Il sensore Grove GPS collegato alla presa sinistra](../../../../../translated_images/wio-gps-sensor.19fd52b81ce58095.it.png)

1. Posiziona il sensore GPS in modo che l'antenna collegata abbia visibilità verso il cielo - idealmente vicino a una finestra aperta o all'esterno. È più facile ottenere un segnale chiaro senza ostacoli davanti all'antenna.

1. Ora puoi collegare il Wio Terminal al tuo computer.

1. Il sensore GPS ha 2 LED: un LED blu che lampeggia quando vengono trasmessi dati e un LED verde che lampeggia ogni secondo quando riceve dati dai satelliti. Assicurati che il LED blu lampeggi quando accendi il Wio Terminal. Dopo alcuni minuti, il LED verde inizierà a lampeggiare - se non lo fa, potrebbe essere necessario riposizionare l'antenna.

## Programmare il sensore GPS

Ora il Wio Terminal può essere programmato per utilizzare il sensore GPS collegato.

### Attività - programmare il sensore GPS

Programma il dispositivo.

1. Crea un nuovo progetto per il Wio Terminal utilizzando PlatformIO. Chiama questo progetto `gps-sensor`. Aggiungi del codice nella funzione `setup` per configurare la porta seriale.

1. Aggiungi la seguente direttiva `include` all'inizio del file `main.cpp`. Questo include un file di intestazione con funzioni per configurare la porta Grove sinistra per UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Sotto questa direttiva, aggiungi la seguente riga di codice per dichiarare una connessione alla porta seriale UART:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. È necessario aggiungere del codice per reindirizzare alcuni gestori di segnali interni a questa porta seriale. Aggiungi il seguente codice sotto la dichiarazione di `Serial3`:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. Nella funzione `setup`, sotto la configurazione della porta `Serial`, configura la porta seriale UART con il seguente codice:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Sotto questo codice nella funzione `setup`, aggiungi il seguente codice per collegare il pin Grove alla porta seriale:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Aggiungi la seguente funzione prima della funzione `loop` per inviare i dati GPS al monitor seriale:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. Nella funzione `loop`, aggiungi il seguente codice per leggere dalla porta seriale UART e stampare l'output sul monitor seriale:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Questo codice legge dalla porta seriale UART. La funzione `readStringUntil` legge fino a un carattere terminatore, in questo caso un carattere di nuova linea. Questo permette di leggere un'intera frase NMEA (le frasi NMEA terminano con un carattere di nuova linea). Finché è possibile leggere dati dalla porta seriale UART, questi vengono letti e inviati al monitor seriale tramite la funzione `printGPSData`. Una volta che non è più possibile leggere dati, la funzione `loop` attende per 1 secondo (1.000ms).

1. Compila e carica il codice sul Wio Terminal.

1. Una volta caricato, puoi monitorare i dati GPS utilizzando il monitor seriale.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 Puoi trovare questo codice nella cartella [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 Il tuo programma per il sensore GPS è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.