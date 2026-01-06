<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-25T17:01:27+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "it"
}
-->
# Misurare l'umidità del suolo - Wio Terminal

In questa parte della lezione, aggiungerai un sensore capacitivo di umidità del suolo al tuo Wio Terminal e leggerai i valori da esso.

## Hardware

Il Wio Terminal necessita di un sensore capacitivo di umidità del suolo.

Il sensore che utilizzerai è un [Sensore Capacitivo di Umidità del Suolo](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), che misura l'umidità del suolo rilevando la capacità del terreno, una proprietà che cambia con il variare dell'umidità. All'aumentare dell'umidità del suolo, la tensione diminuisce.

Questo è un sensore analogico, quindi si collega ai pin analogici del Wio Terminal, utilizzando un ADC integrato per creare un valore da 0 a 1.023.

### Collegare il sensore di umidità del suolo

Il sensore Grove di umidità del suolo può essere collegato alla porta analogica/digitale configurabile del Wio Terminal.

#### Attività - collegare il sensore di umidità del suolo

Collega il sensore di umidità del suolo.

![Un sensore Grove di umidità del suolo](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.it.png)

1. Inserisci un'estremità di un cavo Grove nella presa del sensore di umidità del suolo. Può essere inserito solo in un verso.

1. Con il Wio Terminal scollegato dal computer o da altre fonti di alimentazione, collega l'altra estremità del cavo Grove alla presa Grove sul lato destro del Wio Terminal, guardando lo schermo. Questa è la presa più lontana dal pulsante di accensione.

![Il sensore Grove di umidità del suolo collegato alla presa destra](../../../../../translated_images/wio-soil-moisture-sensor.46919b61c3f6cb74.it.png)

1. Inserisci il sensore di umidità del suolo nel terreno. Ha una "linea di posizione massima" - una linea bianca sul sensore. Inserisci il sensore fino a questa linea, ma non oltre.

![Il sensore Grove di umidità del suolo nel terreno](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.it.png)

1. Ora puoi collegare il Wio Terminal al tuo computer.

## Programmare il sensore di umidità del suolo

Ora il Wio Terminal può essere programmato per utilizzare il sensore di umidità del suolo collegato.

### Attività - programmare il sensore di umidità del suolo

Programma il dispositivo.

1. Crea un nuovo progetto Wio Terminal utilizzando PlatformIO. Chiama questo progetto `soil-moisture-sensor`. Aggiungi del codice nella funzione `setup` per configurare la porta seriale.

    > ⚠️ Puoi fare riferimento a [le istruzioni per creare un progetto PlatformIO nel progetto 1, lezione 1, se necessario](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Non esiste una libreria per questo sensore, ma puoi leggere dal pin analogico utilizzando la funzione [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) integrata di Arduino. Inizia configurando il pin analogico come input in modo che i valori possano essere letti da esso, aggiungendo il seguente codice alla funzione `setup`.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Questo imposta il pin `A0`, il pin combinato analogico/digitale, come un pin di input da cui può essere letta la tensione.

1. Aggiungi il seguente codice alla funzione `loop` per leggere la tensione da questo pin:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Sotto questo codice, aggiungi il seguente codice per stampare il valore sulla porta seriale:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Infine, aggiungi un ritardo di 10 secondi alla fine:

    ```cpp
    delay(10000);
    ```

1. Compila e carica il codice sul Wio Terminal.

    > ⚠️ Puoi fare riferimento a [le istruzioni per creare un progetto PlatformIO nel progetto 1, lezione 1, se necessario](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Una volta caricato, puoi monitorare l'umidità del suolo utilizzando il monitor seriale. Aggiungi dell'acqua al terreno o rimuovi il sensore dal terreno e osserva il cambiamento del valore.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    Nell'esempio di output sopra, puoi vedere la tensione diminuire man mano che viene aggiunta acqua.

> 💁 Puoi trovare questo codice nella cartella [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal).

😀 Il tuo programma per il sensore di umidità del suolo è stato un successo!

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.