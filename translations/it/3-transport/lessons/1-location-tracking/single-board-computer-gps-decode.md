<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-25T18:06:25+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "it"
}
-->
# Decodifica dei dati GPS - Hardware IoT Virtuale e Raspberry Pi

In questa parte della lezione, decodificherai i messaggi NMEA letti dal sensore GPS tramite il Raspberry Pi o il Dispositivo IoT Virtuale, ed estrarrai latitudine e longitudine.

## Decodifica dei dati GPS

Una volta letti i dati NMEA grezzi dalla porta seriale, possono essere decodificati utilizzando una libreria NMEA open source.

### Attività - decodifica dei dati GPS

Programma il dispositivo per decodificare i dati GPS.

1. Apri il progetto dell'app `gps-sensor` se non è già aperto.

1. Installa il pacchetto Pip `pynmea2`. Questo pacchetto contiene il codice per decodificare i messaggi NMEA.

    ```sh
    pip3 install pynmea2
    ```

1. Aggiungi il seguente codice alle importazioni nel file `app.py` per importare il modulo `pynmea2`:

    ```python
    import pynmea2
    ```

1. Sostituisci il contenuto della funzione `print_gps_data` con il seguente:

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    Questo codice utilizzerà la libreria `pynmea2` per analizzare la riga letta dalla porta seriale UART.

    Se il tipo di frase del messaggio è `GGA`, allora si tratta di un messaggio di fissaggio della posizione, che viene elaborato. I valori di latitudine e longitudine vengono letti dal messaggio e convertiti in gradi decimali dal formato NMEA `(d)ddmm.mmmm`. La funzione `dm_to_sd` esegue questa conversione.

    Viene quindi controllata la direzione della latitudine e, se la latitudine è a sud, il valore viene convertito in un numero negativo. Lo stesso vale per la longitudine: se è a ovest, viene convertita in un numero negativo.

    Infine, le coordinate vengono stampate sulla console, insieme al numero di satelliti utilizzati per ottenere la posizione.

1. Esegui il codice. Se stai utilizzando un dispositivo IoT virtuale, assicurati che l'app CounterFit sia in esecuzione e che i dati GPS vengano inviati.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Puoi trovare questo codice nella cartella [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) o nella cartella [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 Il tuo programma per il sensore GPS con decodifica dei dati è stato un successo!

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.