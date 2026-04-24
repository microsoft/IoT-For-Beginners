# Controllare un relè - Hardware IoT Virtuale

In questa parte della lezione, aggiungerai un relè al tuo dispositivo IoT virtuale, oltre al sensore di umidità del suolo, e lo controllerai in base al livello di umidità del suolo.

## Hardware Virtuale

Il dispositivo IoT virtuale utilizzerà un relè Grove simulato. Questo mantiene il laboratorio simile all'utilizzo di un Raspberry Pi con un relè Grove fisico.

In un dispositivo IoT fisico, il relè sarebbe un relè normalmente aperto (il circuito di uscita è aperto o disconnesso quando non viene inviato alcun segnale al relè). Un relè di questo tipo può gestire circuiti di uscita fino a 250V e 10A.

### Aggiungere il relè a CounterFit

Per utilizzare un relè virtuale, è necessario aggiungerlo all'app CounterFit.

#### Attività

Aggiungi il relè all'app CounterFit.

1. Apri il progetto `soil-moisture-sensor` dalla lezione precedente in VS Code, se non è già aperto. Aggiungerai a questo progetto.

1. Assicurati che l'app web CounterFit sia in esecuzione.

1. Crea un relè:

    1. Nella casella *Create actuator* nel pannello *Actuators*, apri il menu a tendina *Actuator type* e seleziona *Relay*.

    1. Imposta il *Pin* su *5*.

    1. Seleziona il pulsante **Add** per creare il relè sul Pin 5.

    ![Le impostazioni del relè](../../../../../translated_images/it/counterfit-create-relay.fa7c40fd0f2f6afc.webp)

    Il relè verrà creato e apparirà nella lista degli attuatori.

    ![Il relè creato](../../../../../translated_images/it/counterfit-relay.bbf74c1dbdc8b9ac.webp)

## Programmare il relè

L'app del sensore di umidità del suolo può ora essere programmata per utilizzare il relè virtuale.

### Attività

Programma il dispositivo virtuale.

1. Apri il progetto `soil-moisture-sensor` dalla lezione precedente in VS Code, se non è già aperto. Aggiungerai a questo progetto.

1. Aggiungi il seguente codice al file `app.py` sotto gli import esistenti:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Questa istruzione importa il `GroveRelay` dalle librerie shim Python Grove per interagire con il relè Grove virtuale.

1. Aggiungi il seguente codice sotto la dichiarazione della classe `ADC` per creare un'istanza di `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Questo crea un relè utilizzando il pin **5**, il pin a cui hai collegato il relè.

1. Per testare che il relè funzioni, aggiungi il seguente codice al ciclo `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Il codice accende il relè, aspetta 0,5 secondi, quindi spegne il relè.

1. Esegui l'app Python. Il relè si accenderà e spegnerà ogni 10 secondi, con un ritardo di mezzo secondo tra accensione e spegnimento. Vedrai il relè virtuale nell'app CounterFit chiudersi e aprirsi mentre il relè si accende e si spegne.

    ![Il relè virtuale che si accende e spegne](../../../../../images/virtual-relay-turn-on-off.gif)

## Controllare il relè in base all'umidità del suolo

Ora che il relè funziona, può essere controllato in risposta alle letture di umidità del suolo.

### Attività

Controlla il relè.

1. Elimina le 3 righe di codice che hai aggiunto per testare il relè. Sostituiscile con il seguente codice al loro posto:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Questo codice controlla il livello di umidità del suolo dal sensore di umidità del suolo. Se è superiore a 450, accende il relè, spegnendolo se scende sotto 450.

    > 💁 Ricorda che il sensore capacitivo di umidità del suolo legge: più basso è il livello di umidità del suolo, maggiore è l'umidità nel terreno e viceversa.

1. Esegui l'app Python. Vedrai il relè accendersi o spegnersi a seconda dei livelli di umidità del suolo. Modifica le impostazioni *Value* o *Random* per il sensore di umidità del suolo per vedere il valore cambiare.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Puoi trovare questo codice nella cartella [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device).

😀 Il tuo programma per controllare un relè con un sensore di umidità del suolo virtuale è stato un successo!

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.