<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-25T17:02:30+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "it"
}
-->
# Misurare l'umidità del suolo - Hardware IoT Virtuale

In questa parte della lezione, aggiungerai un sensore capacitivo di umidità del suolo al tuo dispositivo IoT virtuale e leggerai i valori da esso.

## Hardware Virtuale

Il dispositivo IoT virtuale utilizzerà un sensore capacitivo di umidità del suolo simulato Grove. Questo mantiene il laboratorio identico all'utilizzo di un Raspberry Pi con un sensore capacitivo di umidità del suolo fisico.

In un dispositivo IoT fisico, il sensore di umidità del suolo sarebbe un sensore capacitivo che misura l'umidità del suolo rilevando la capacità del terreno, una proprietà che cambia con il variare dell'umidità del suolo. Quando l'umidità del suolo aumenta, la tensione diminuisce.

Questo è un sensore analogico, quindi utilizza un ADC simulato a 10 bit per riportare un valore da 1 a 1.023.

### Aggiungere il sensore di umidità del suolo a CounterFit

Per utilizzare un sensore di umidità del suolo virtuale, è necessario aggiungerlo all'app CounterFit.

#### Attività - Aggiungere il sensore di umidità del suolo a CounterFit

Aggiungi il sensore di umidità del suolo all'app CounterFit.

1. Crea una nuova app Python sul tuo computer in una cartella chiamata `soil-moisture-sensor` con un unico file chiamato `app.py`, un ambiente virtuale Python e aggiungi i pacchetti pip di CounterFit.

    > ⚠️ Puoi fare riferimento [alle istruzioni per creare e configurare un progetto Python CounterFit nella lezione 1, se necessario](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Assicurati che l'app web CounterFit sia in esecuzione.

1. Crea un sensore di umidità del suolo:

    1. Nella casella *Create sensor* nel pannello *Sensors*, apri il menu a tendina *Sensor type* e seleziona *Soil Moisture*.

    1. Lascia le *Units* impostate su *NoUnits*.

    1. Assicurati che il *Pin* sia impostato su *0*.

    1. Seleziona il pulsante **Add** per creare il sensore *Soil Moisture* sul Pin 0.

    ![Le impostazioni del sensore di umidità del suolo](../../../../../translated_images/it/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    Il sensore di umidità del suolo verrà creato e apparirà nella lista dei sensori.

    ![Il sensore di umidità del suolo creato](../../../../../translated_images/it/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## Programmare l'app del sensore di umidità del suolo

Ora è possibile programmare l'app del sensore di umidità del suolo utilizzando i sensori di CounterFit.

### Attività - Programmare l'app del sensore di umidità del suolo

Programma l'app del sensore di umidità del suolo.

1. Assicurati che l'app `soil-moisture-sensor` sia aperta in VS Code.

1. Apri il file `app.py`.

1. Aggiungi il seguente codice all'inizio di `app.py` per connettere l'app a CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Aggiungi il seguente codice al file `app.py` per importare alcune librerie necessarie:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    L'istruzione `import time` importa il modulo `time`, che verrà utilizzato più avanti in questa attività.

    L'istruzione `from counterfit_shims_grove.adc import ADC` importa la classe `ADC` per interagire con un convertitore analogico-digitale virtuale che può connettersi a un sensore CounterFit.

1. Aggiungi il seguente codice sotto questo per creare un'istanza della classe `ADC`:

    ```python
    adc = ADC()
    ```

1. Aggiungi un ciclo infinito che legge da questo ADC sul pin 0 e scrive il risultato sulla console. Questo ciclo può poi dormire per 10 secondi tra una lettura e l'altra.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. Dall'app CounterFit, modifica il valore del sensore di umidità del suolo che verrà letto dall'app. Puoi farlo in due modi:

    * Inserisci un numero nella casella *Value* del sensore di umidità del suolo, quindi seleziona il pulsante **Set**. Il numero inserito sarà il valore restituito dal sensore.

    * Seleziona la casella *Random* e inserisci un valore *Min* e *Max*, quindi seleziona il pulsante **Set**. Ogni volta che il sensore legge un valore, leggerà un numero casuale tra *Min* e *Max*.

1. Esegui l'app Python. Vedrai le misurazioni dell'umidità del suolo scritte sulla console. Modifica il *Value* o le impostazioni *Random* per vedere il valore cambiare.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Puoi trovare questo codice nella cartella [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device).

😀 Il tuo programma per il sensore di umidità del suolo è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.