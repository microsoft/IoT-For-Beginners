<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-25T17:24:58+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "it"
}
-->
# Aggiungere un sensore - Wio Terminal

In questa parte della lezione, utilizzerai il sensore di luce sul tuo Wio Terminal.

## Hardware

Il sensore per questa lezione è un **sensore di luce** che utilizza un [fotodiodo](https://wikipedia.org/wiki/Photodiode) per convertire la luce in un segnale elettrico. Si tratta di un sensore analogico che invia un valore intero da 0 a 1.023, indicando una quantità relativa di luce che non corrisponde a nessuna unità di misura standard come il [lux](https://wikipedia.org/wiki/Lux).

Il sensore di luce è integrato nel Wio Terminal ed è visibile attraverso la finestra di plastica trasparente sul retro.

![Il sensore di luce sul retro del Wio Terminal](../../../../../translated_images/it/wio-light-sensor.b1f529f3c95f5165.webp)

## Programmare il sensore di luce

Ora il dispositivo può essere programmato per utilizzare il sensore di luce integrato.

### Attività

Programma il dispositivo.

1. Apri il progetto della luce notturna in VS Code che hai creato nella parte precedente di questo esercizio.

1. Aggiungi la seguente riga alla fine della funzione `setup`:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Questa riga configura i pin utilizzati per comunicare con l'hardware del sensore.

    Il pin `WIO_LIGHT` è il numero del pin GPIO collegato al sensore di luce integrato. Questo pin è impostato su `INPUT`, il che significa che è collegato a un sensore e i dati verranno letti dal pin.

1. Elimina il contenuto della funzione `loop`.

1. Aggiungi il seguente codice alla funzione `loop`, ora vuota.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Questo codice legge un valore analogico dal pin `WIO_LIGHT`. Legge un valore da 0 a 1.023 dal sensore di luce integrato. Questo valore viene poi inviato alla porta seriale, così potrai leggerlo nel Monitor Seriale quando questo codice è in esecuzione. `Serial.print` scrive il testo senza un ritorno a capo alla fine, quindi ogni riga inizierà con `Light value:` e terminerà con il valore effettivo della luce.

1. Aggiungi un piccolo ritardo di un secondo (1.000ms) alla fine del `loop`, poiché i livelli di luce non devono essere controllati continuamente. Un ritardo riduce il consumo energetico del dispositivo.

    ```cpp
    delay(1000);
    ```

1. Riconnetti il Wio Terminal al tuo computer e carica il nuovo codice come hai fatto in precedenza.

1. Connetti il Monitor Seriale. I valori della luce verranno visualizzati nel terminale. Copri e scopri il sensore di luce sul retro del Wio Terminal, e i valori cambieranno.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 Puoi trovare questo codice nella cartella [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 Aggiungere un sensore al tuo programma di luce notturna è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.