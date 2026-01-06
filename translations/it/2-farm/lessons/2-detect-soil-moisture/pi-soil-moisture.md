<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-25T17:03:02+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "it"
}
-->
# Misurare l'umidità del suolo - Raspberry Pi

In questa parte della lezione, aggiungerai un sensore capacitivo di umidità del suolo al tuo Raspberry Pi e leggerai i valori da esso.

## Hardware

Il Raspberry Pi necessita di un sensore capacitivo di umidità del suolo.

Il sensore che utilizzerai è un [Sensore Capacitivo di Umidità del Suolo](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), che misura l'umidità del suolo rilevando la capacità del terreno, una proprietà che cambia con il variare dell'umidità. All'aumentare dell'umidità del suolo, la tensione diminuisce.

Questo è un sensore analogico, quindi utilizza un pin analogico e il convertitore ADC a 10 bit presente nel Grove Base Hat sul Raspberry Pi per convertire la tensione in un segnale digitale compreso tra 1 e 1.023. Questo segnale viene poi inviato tramite I²C attraverso i pin GPIO del Raspberry Pi.

### Collegare il sensore di umidità del suolo

Il sensore Grove di umidità del suolo può essere collegato al Raspberry Pi.

#### Attività - collegare il sensore di umidità del suolo

Collega il sensore di umidità del suolo.

![Un sensore Grove di umidità del suolo](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.it.png)

1. Inserisci un'estremità di un cavo Grove nella presa del sensore di umidità del suolo. Il cavo può essere inserito solo in un verso.

1. Con il Raspberry Pi spento, collega l'altra estremità del cavo Grove alla presa analogica contrassegnata come **A0** sul Grove Base Hat collegato al Raspberry Pi. Questa presa è la seconda da destra, nella fila di prese accanto ai pin GPIO.

![Il sensore Grove di umidità del suolo collegato alla presa A0](../../../../../translated_images/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.it.png)

1. Inserisci il sensore di umidità del suolo nel terreno. Il sensore ha una "linea di posizione massima" - una linea bianca che attraversa il sensore. Inserisci il sensore fino a questa linea, ma non oltre.

![Il sensore Grove di umidità del suolo nel terreno](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.it.png)

## Programmare il sensore di umidità del suolo

Ora il Raspberry Pi può essere programmato per utilizzare il sensore di umidità del suolo collegato.

### Attività - programmare il sensore di umidità del suolo

Programma il dispositivo.

1. Accendi il Raspberry Pi e attendi che si avvii.

1. Avvia VS Code, direttamente sul Raspberry Pi o connettendoti tramite l'estensione Remote SSH.

    > ⚠️ Puoi fare riferimento [alle istruzioni per configurare e avviare VS Code in nightlight - lezione 1, se necessario](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Dal terminale, crea una nuova cartella nella directory home dell'utente `pi` chiamata `soil-moisture-sensor`. Crea un file in questa cartella chiamato `app.py`.

1. Apri questa cartella in VS Code.

1. Aggiungi il seguente codice al file `app.py` per importare alcune librerie necessarie:

    ```python
    import time
    from grove.adc import ADC
    ```

    L'istruzione `import time` importa il modulo `time`, che verrà utilizzato più avanti in questa attività.

    L'istruzione `from grove.adc import ADC` importa l'`ADC` dalle librerie Python di Grove. Questa libreria contiene il codice per interagire con il convertitore analogico-digitale sul Grove Base Hat e leggere le tensioni dai sensori analogici.

1. Aggiungi il seguente codice sotto per creare un'istanza della classe `ADC`:

    ```python
    adc = ADC()
    ```

1. Aggiungi un ciclo infinito che legge dall'ADC sul pin A0 e scrive il risultato nella console. Questo ciclo può poi attendere 10 secondi tra una lettura e l'altra.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Esegui l'app Python. Vedrai le misurazioni dell'umidità del suolo scritte nella console. Aggiungi dell'acqua al terreno o rimuovi il sensore dal terreno e osserva il cambiamento del valore.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    Nell'esempio di output sopra, puoi vedere la tensione diminuire quando viene aggiunta acqua.

> 💁 Puoi trovare questo codice nella cartella [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi).

😀 Il tuo programma per il sensore di umidità del suolo è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.