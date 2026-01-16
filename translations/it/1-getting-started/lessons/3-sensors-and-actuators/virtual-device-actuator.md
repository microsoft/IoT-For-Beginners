<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-25T17:23:56+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "it"
}
-->
# Costruire una luce notturna - Hardware IoT Virtuale

In questa parte della lezione, aggiungerai un LED al tuo dispositivo IoT virtuale e lo utilizzerai per creare una luce notturna.

## Hardware Virtuale

La luce notturna necessita di un attuatore, creato nell'app CounterFit.

L'attuatore è un **LED**. In un dispositivo IoT fisico, sarebbe un [diodo a emissione luminosa](https://wikipedia.org/wiki/Diodo_a_emissione_luminosa) che emette luce quando una corrente lo attraversa. Questo è un attuatore digitale che ha 2 stati, acceso e spento. Inviare un valore di 1 accende il LED, mentre un valore di 0 lo spegne.

La logica della luce notturna in pseudo-codice è:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Aggiungere l'attuatore a CounterFit

Per utilizzare un LED virtuale, è necessario aggiungerlo all'app CounterFit.

#### Attività - aggiungere l'attuatore a CounterFit

Aggiungi il LED all'app CounterFit.

1. Assicurati che l'app web CounterFit sia in esecuzione dalla parte precedente di questo compito. In caso contrario, avviala e riaggiungi il sensore di luce.

1. Crea un LED:

    1. Nella casella *Create actuator* nel pannello *Actuator*, apri il menu a tendina *Actuator type* e seleziona *LED*.

    1. Imposta il *Pin* su *5*.

    1. Seleziona il pulsante **Add** per creare il LED sul Pin 5.

    ![Le impostazioni del LED](../../../../../translated_images/it/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    Il LED verrà creato e apparirà nell'elenco degli attuatori.

    ![Il LED creato](../../../../../translated_images/it/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    Una volta creato il LED, puoi cambiarne il colore utilizzando il selettore *Color*. Seleziona il pulsante **Set** per cambiare il colore dopo averlo scelto.

### Programmare la luce notturna

Ora è possibile programmare la luce notturna utilizzando il sensore di luce e il LED di CounterFit.

#### Attività - programmare la luce notturna

Programma la luce notturna.

1. Apri il progetto della luce notturna in VS Code che hai creato nella parte precedente di questo compito. Termina e ricrea il terminale per assicurarti che stia utilizzando l'ambiente virtuale, se necessario.

1. Apri il file `app.py`.

1. Aggiungi il seguente codice al file `app.py` per importare una libreria necessaria. Questo dovrebbe essere aggiunto in alto, sotto le altre righe di `import`.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    L'istruzione `from counterfit_shims_grove.grove_led import GroveLed` importa il `GroveLed` dalle librerie Python CounterFit Grove shim. Questa libreria contiene il codice per interagire con un LED creato nell'app CounterFit.

1. Aggiungi il seguente codice dopo la dichiarazione di `light_sensor` per creare un'istanza della classe che gestisce il LED:

    ```python
    led = GroveLed(5)
    ```

    La riga `led = GroveLed(5)` crea un'istanza della classe `GroveLed` collegandola al pin **5** - il pin Grove di CounterFit a cui è collegato il LED.

1. Aggiungi un controllo all'interno del ciclo `while`, e prima di `time.sleep`, per verificare i livelli di luce e accendere o spegnere il LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Questo codice controlla il valore di `light`. Se è inferiore a 300, chiama il metodo `on` della classe `GroveLed`, che invia un valore digitale di 1 al LED, accendendolo. Se il valore della luce è maggiore o uguale a 300, chiama il metodo `off`, inviando un valore digitale di 0 al LED, spegnendolo.

    > 💁 Questo codice dovrebbe essere indentato allo stesso livello della riga `print('Light level:', light)` per essere all'interno del ciclo while!

1. Dal Terminale di VS Code, esegui il seguente comando per avviare la tua app Python:

    ```sh
    python3 app.py
    ```

    I valori della luce verranno visualizzati nella console.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Modifica le impostazioni *Value* o *Random* per variare il livello di luce sopra e sotto 300. Il LED si accenderà e spegnerà.

![Il LED nell'app CounterFit che si accende e spegne al variare del livello di luce](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Puoi trovare questo codice nella cartella [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device).

😀 Il tuo programma per la luce notturna è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.