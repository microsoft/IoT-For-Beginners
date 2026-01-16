<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-25T16:48:38+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "it"
}
-->
# Misurare la temperatura - Raspberry Pi

In questa parte della lezione, aggiungerai un sensore di temperatura al tuo Raspberry Pi.

## Hardware

Il sensore che utilizzerai è un [sensore di umidità e temperatura DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), che combina 2 sensori in un unico dispositivo. Questo sensore è abbastanza popolare e molti sensori disponibili in commercio combinano temperatura, umidità e talvolta pressione atmosferica. Il componente del sensore di temperatura è un termistore a coefficiente di temperatura negativo (NTC), un termistore in cui la resistenza diminuisce con l'aumentare della temperatura.

Si tratta di un sensore digitale, quindi dispone di un ADC integrato per creare un segnale digitale contenente i dati di temperatura e umidità che il microcontrollore può leggere.

### Collegare il sensore di temperatura

Il sensore di temperatura Grove può essere collegato al Raspberry Pi.

#### Attività

Collega il sensore di temperatura

![Un sensore di temperatura Grove](../../../../../translated_images/it/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Inserisci un'estremità di un cavo Grove nella presa del sensore di umidità e temperatura. Il cavo può essere inserito solo in un verso.

1. Con il Raspberry Pi spento, collega l'altra estremità del cavo Grove alla presa digitale contrassegnata **D5** sul Grove Base Hat collegato al Pi. Questa presa è la seconda da sinistra, nella fila di prese accanto ai pin GPIO.

![Il sensore di temperatura Grove collegato alla presa A0](../../../../../translated_images/it/pi-temperature-sensor.3ff82fff672c8e565ef25a39d26d111de006b825a7e0867227ef4e7fbff8553c.png)

## Programmare il sensore di temperatura

Ora il dispositivo può essere programmato per utilizzare il sensore di temperatura collegato.

### Attività

Programma il dispositivo.

1. Accendi il Pi e attendi che si avvii.

1. Avvia VS Code, direttamente sul Pi o connettendoti tramite l'estensione Remote SSH.

    > ⚠️ Puoi fare riferimento [alle istruzioni per configurare e avviare VS Code nella lezione 1, se necessario](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Dal terminale, crea una nuova cartella nella directory home dell'utente `pi` chiamata `temperature-sensor`. Crea un file in questa cartella chiamato `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Apri questa cartella in VS Code.

1. Per utilizzare il sensore di temperatura e umidità, è necessario installare un pacchetto Pip aggiuntivo. Dal terminale in VS Code, esegui il seguente comando per installare questo pacchetto Pip sul Pi:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Aggiungi il seguente codice al file `app.py` per importare le librerie necessarie:

    ```python
    import time
    from seeed_dht import DHT
    ```

    L'istruzione `from seeed_dht import DHT` importa la classe `DHT` per interagire con un sensore di temperatura Grove dal modulo `seeed_dht`.

1. Aggiungi il seguente codice dopo il codice sopra per creare un'istanza della classe che gestisce il sensore di temperatura:

    ```python
    sensor = DHT("11", 5)
    ```

    Questo dichiara un'istanza della classe `DHT` che gestisce il sensore digitale di umidità e temperatura (**D**igital **H**umidity and **T**emperature sensor). Il primo parametro indica al codice che il sensore utilizzato è il sensore *DHT11* - la libreria che stai utilizzando supporta altre varianti di questo sensore. Il secondo parametro indica al codice che il sensore è collegato alla porta digitale `D5` sul Grove Base Hat.

    > ✅ Ricorda, tutte le prese hanno numeri di pin univoci. I pin 0, 2, 4 e 6 sono pin analogici, mentre i pin 5, 16, 18, 22, 24 e 26 sono pin digitali.

1. Aggiungi un ciclo infinito dopo il codice sopra per interrogare il valore del sensore di temperatura e stamparlo sulla console:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    La chiamata a `sensor.read()` restituisce una tupla contenente umidità e temperatura. Hai bisogno solo del valore della temperatura, quindi l'umidità viene ignorata. Il valore della temperatura viene poi stampato sulla console.

1. Aggiungi una breve pausa di dieci secondi alla fine del `loop`, poiché i livelli di temperatura non devono essere controllati continuamente. Una pausa riduce il consumo energetico del dispositivo.

    ```python
    time.sleep(10)
    ```

1. Dal terminale di VS Code, esegui il seguente comando per avviare la tua app Python:

    ```sh
    python3 app.py
    ```

    Dovresti vedere i valori di temperatura stampati sulla console. Usa qualcosa per riscaldare il sensore, come premere il pollice su di esso o utilizzare un ventilatore per vedere i valori cambiare:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Puoi trovare questo codice nella cartella [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi).

😀 Il tuo programma per il sensore di temperatura è stato un successo!

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.