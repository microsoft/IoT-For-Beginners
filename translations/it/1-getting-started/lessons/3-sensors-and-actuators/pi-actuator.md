<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-25T17:22:48+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "it"
}
-->
# Costruire una luce notturna - Raspberry Pi

In questa parte della lezione, aggiungerai un LED al tuo Raspberry Pi e lo utilizzerai per creare una luce notturna.

## Hardware

La luce notturna ora necessita di un attuatore.

L'attuatore è un **LED**, un [diodo a emissione luminosa](https://wikipedia.org/wiki/Light-emitting_diode) che emette luce quando la corrente lo attraversa. Questo è un attuatore digitale che ha 2 stati, acceso e spento. Inviare un valore di 1 accende il LED, mentre inviare un valore di 0 lo spegne. Il LED è un attuatore esterno Grove e deve essere collegato al Grove Base hat sul Raspberry Pi.

La logica della luce notturna in pseudo-codice è:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Collegare il LED

Il Grove LED viene fornito come modulo con una selezione di LED, permettendoti di scegliere il colore.

#### Attività - collegare il LED

Collega il LED.

![Un LED Grove](../../../../../translated_images/it/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. Scegli il tuo LED preferito e inserisci i piedini nei due fori sul modulo LED.

    I LED sono diodi a emissione luminosa, e i diodi sono dispositivi elettronici che possono trasportare corrente solo in una direzione. Questo significa che il LED deve essere collegato nel verso corretto, altrimenti non funzionerà.

    Uno dei piedini del LED è il pin positivo, l'altro è il pin negativo. Il LED non è perfettamente rotondo ed è leggermente più piatto su un lato. Il lato leggermente più piatto è il pin negativo. Quando colleghi il LED al modulo, assicurati che il pin dal lato arrotondato sia collegato alla presa contrassegnata **+** all'esterno del modulo, e il lato più piatto sia collegato alla presa più vicina al centro del modulo.

1. Il modulo LED ha un pulsante rotante che ti permette di controllare la luminosità. Ruotalo completamente in senso antiorario per iniziare, utilizzando un piccolo cacciavite a croce.

1. Inserisci un'estremità di un cavo Grove nella presa del modulo LED. Il cavo entrerà solo in un verso.

1. Con il Raspberry Pi spento, collega l'altra estremità del cavo Grove alla presa digitale contrassegnata **D5** sul Grove Base hat collegato al Pi. Questa presa è la seconda da sinistra, nella fila di prese accanto ai pin GPIO.

![Il LED Grove collegato alla presa D5](../../../../../translated_images/it/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## Programmare la luce notturna

Ora è possibile programmare la luce notturna utilizzando il sensore di luce Grove e il LED Grove.

### Attività - programmare la luce notturna

Programma la luce notturna.

1. Accendi il Pi e attendi che si avvii.

1. Apri il progetto della luce notturna in VS Code che hai creato nella parte precedente di questo compito, eseguendolo direttamente sul Pi o collegandoti utilizzando l'estensione Remote SSH.

1. Aggiungi il seguente codice al file `app.py` per importare una libreria necessaria. Questo codice dovrebbe essere aggiunto in alto, sotto le altre righe di `import`.

    ```python
    from grove.grove_led import GroveLed
    ```

    L'istruzione `from grove.grove_led import GroveLed` importa il `GroveLed` dalle librerie Python Grove. Questa libreria contiene il codice per interagire con un LED Grove.

1. Aggiungi il seguente codice dopo la dichiarazione di `light_sensor` per creare un'istanza della classe che gestisce il LED:

    ```python
    led = GroveLed(5)
    ```

    La riga `led = GroveLed(5)` crea un'istanza della classe `GroveLed` collegandosi al pin **D5** - il pin digitale Grove a cui è collegato il LED.

    > 💁 Tutte le prese hanno numeri di pin univoci. I pin 0, 2, 4 e 6 sono pin analogici, mentre i pin 5, 16, 18, 22, 24 e 26 sono pin digitali.

1. Aggiungi un controllo all'interno del ciclo `while`, e prima di `time.sleep`, per verificare i livelli di luce e accendere o spegnere il LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Questo codice verifica il valore di `light`. Se è inferiore a 300, chiama il metodo `on` della classe `GroveLed`, che invia un valore digitale di 1 al LED, accendendolo. Se il valore della luce è maggiore o uguale a 300, chiama il metodo `off`, inviando un valore digitale di 0 al LED, spegnendolo.

    > 💁 Questo codice dovrebbe essere indentato allo stesso livello della riga `print('Light level:', light)` per essere all'interno del ciclo while!

    > 💁 Quando si inviano valori digitali agli attuatori, un valore di 0 corrisponde a 0V, mentre un valore di 1 corrisponde alla tensione massima per il dispositivo. Per il Raspberry Pi con sensori e attuatori Grove, la tensione di 1 è 3.3V.

1. Dal terminale di VS Code, esegui il seguente comando per avviare la tua app Python:

    ```sh
    python3 app.py
    ```

    I valori di luce verranno visualizzati nella console.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Copri e scopri il sensore di luce. Nota come il LED si accende se il livello di luce è 300 o inferiore, e si spegne quando il livello di luce è maggiore di 300.

    > 💁 Se il LED non si accende, assicurati che sia collegato nel verso corretto e che il pulsante rotante sia impostato al massimo.

![Il LED collegato al Pi si accende e si spegne al variare del livello di luce](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Puoi trovare questo codice nella cartella [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 Il tuo programma per la luce notturna è stato un successo!

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.