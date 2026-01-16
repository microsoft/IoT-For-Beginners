<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-25T17:24:33+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "it"
}
-->
# Costruire una luce notturna - Hardware IoT Virtuale

In questa parte della lezione, aggiungerai un sensore di luce al tuo dispositivo IoT virtuale.

## Hardware Virtuale

La luce notturna necessita di un sensore, creato nell'app CounterFit.

Il sensore è un **sensore di luce**. In un dispositivo IoT fisico, sarebbe un [fotodiodo](https://wikipedia.org/wiki/Photodiode) che converte la luce in un segnale elettrico. I sensori di luce sono sensori analogici che inviano un valore intero indicando una quantità relativa di luce, che non corrisponde a nessuna unità di misura standard come il [lux](https://wikipedia.org/wiki/Lux).

### Aggiungere i sensori a CounterFit

Per utilizzare un sensore di luce virtuale, devi aggiungerlo all'app CounterFit.

#### Attività - aggiungere i sensori a CounterFit

Aggiungi il sensore di luce all'app CounterFit.

1. Assicurati che l'app web CounterFit sia in esecuzione dalla parte precedente di questo esercizio. Se non lo è, avviala.

1. Crea un sensore di luce:

    1. Nella casella *Create sensor* nel pannello *Sensors*, apri il menu a tendina *Sensor type* e seleziona *Light*.

    1. Lascia l'opzione *Units* impostata su *NoUnits*.

    1. Assicurati che il *Pin* sia impostato su *0*.

    1. Seleziona il pulsante **Add** per creare il sensore di luce sul Pin 0.

    ![Le impostazioni del sensore di luce](../../../../../translated_images/it/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    Il sensore di luce verrà creato e apparirà nella lista dei sensori.

    ![Il sensore di luce creato](../../../../../translated_images/it/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## Programmare il sensore di luce

Ora il dispositivo può essere programmato per utilizzare il sensore di luce integrato.

### Attività - programmare il sensore di luce

Programma il dispositivo.

1. Apri il progetto della luce notturna in VS Code che hai creato nella parte precedente di questo esercizio. Termina e ricrea il terminale per assicurarti che stia utilizzando l'ambiente virtuale, se necessario.

1. Apri il file `app.py`.

1. Aggiungi il seguente codice all'inizio del file `app.py` insieme agli altri `import` per importare alcune librerie necessarie:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    L'istruzione `import time` importa il modulo Python `time` che verrà utilizzato più avanti in questo esercizio.

    L'istruzione `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` importa il `GroveLightSensor` dalle librerie Python CounterFit Grove shim. Questa libreria contiene il codice per interagire con un sensore di luce creato nell'app CounterFit.

1. Aggiungi il seguente codice alla fine del file per creare istanze delle classi che gestiscono il sensore di luce:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    La riga `light_sensor = GroveLightSensor(0)` crea un'istanza della classe `GroveLightSensor` collegata al pin **0** - il pin Grove di CounterFit a cui è collegato il sensore di luce.

1. Aggiungi un ciclo infinito dopo il codice sopra per interrogare il valore del sensore di luce e stamparlo sulla console:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Questo leggerà il livello di luce corrente utilizzando la proprietà `light` della classe `GroveLightSensor`. Questa proprietà legge il valore analogico dal pin. Questo valore viene poi stampato sulla console.

1. Aggiungi una piccola pausa di un secondo alla fine del ciclo `while`, poiché i livelli di luce non devono essere controllati continuamente. Una pausa riduce il consumo energetico del dispositivo.

    ```python
    time.sleep(1)
    ```

1. Dal terminale di VS Code, esegui il seguente comando per avviare la tua app Python:

    ```sh
    python3 app.py
    ```

    I valori della luce verranno visualizzati sulla console. Inizialmente questo valore sarà 0.

1. Dall'app CounterFit, modifica il valore del sensore di luce che verrà letto dall'app. Puoi farlo in due modi:

    * Inserisci un numero nella casella *Value* del sensore di luce, quindi seleziona il pulsante **Set**. Il numero inserito sarà il valore restituito dal sensore.

    * Seleziona la casella *Random* e inserisci un valore *Min* e *Max*, quindi seleziona il pulsante **Set**. Ogni volta che il sensore legge un valore, leggerà un numero casuale tra *Min* e *Max*.

    I valori impostati verranno visualizzati sulla console. Modifica il valore *Value* o le impostazioni *Random* per far cambiare il valore.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Puoi trovare questo codice nella cartella [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 Il tuo programma per la luce notturna è stato un successo!

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche potrebbero contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.