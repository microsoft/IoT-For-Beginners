<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-25T18:07:36+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "it"
}
-->
# Decodifica dei dati GPS - Wio Terminal

In questa parte della lezione, decodificherai i messaggi NMEA letti dal sensore GPS tramite il Wio Terminal e estrarrai la latitudine e la longitudine.

## Decodifica dei dati GPS

Una volta letti i dati NMEA grezzi dalla porta seriale, possono essere decodificati utilizzando una libreria NMEA open source.

### Compito - decodifica dei dati GPS

Programma il dispositivo per decodificare i dati GPS.

1. Apri il progetto dell'app `gps-sensor` se non è già aperto.

1. Aggiungi una dipendenza di libreria per la libreria [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) al file `platformio.ini` del progetto. Questa libreria contiene il codice per decodificare i dati NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. In `main.cpp`, aggiungi una direttiva di inclusione per la libreria TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Sotto la dichiarazione di `Serial3`, dichiara un oggetto TinyGPSPlus per elaborare le frasi NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Modifica il contenuto della funzione `printGPSData` con il seguente:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    Questo codice legge il prossimo carattere dalla porta seriale UART nel decoder NMEA `gps`. Dopo ogni carattere, verifica se il decoder ha letto una frase valida, quindi controlla se ha letto una posizione valida. Se la posizione è valida, la invia al monitor seriale, insieme al numero di satelliti che hanno contribuito a questa determinazione.

1. Compila e carica il codice sul Wio Terminal.

1. Una volta caricato, puoi monitorare i dati della posizione GPS utilizzando il monitor seriale.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Puoi trovare questo codice nella cartella [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Il tuo programma per il sensore GPS con decodifica dei dati è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.