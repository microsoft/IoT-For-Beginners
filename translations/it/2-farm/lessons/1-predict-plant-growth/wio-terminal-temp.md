<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-25T16:46:53+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "it"
}
-->
# Misurare la temperatura - Wio Terminal

In questa parte della lezione, aggiungerai un sensore di temperatura al tuo Wio Terminal e leggerai i valori di temperatura da esso.

## Hardware

Il Wio Terminal necessita di un sensore di temperatura.

Il sensore che utilizzerai è un [sensore di umidità e temperatura DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), che combina 2 sensori in un unico dispositivo. Questo sensore è abbastanza popolare e molti sensori disponibili in commercio combinano temperatura, umidità e talvolta pressione atmosferica. Il componente del sensore di temperatura è un termistore a coefficiente di temperatura negativo (NTC), un termistore in cui la resistenza diminuisce con l'aumentare della temperatura.

Si tratta di un sensore digitale, quindi dispone di un ADC integrato per creare un segnale digitale contenente i dati di temperatura e umidità che il microcontrollore può leggere.

### Collegare il sensore di temperatura

Il sensore di temperatura Grove può essere collegato alla porta digitale del Wio Terminal.

#### Attività - collegare il sensore di temperatura

Collega il sensore di temperatura.

![Un sensore di temperatura Grove](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.it.png)

1. Inserisci un'estremità di un cavo Grove nella presa del sensore di umidità e temperatura. Può essere inserito solo in un verso.

1. Con il Wio Terminal scollegato dal computer o da altre fonti di alimentazione, collega l'altra estremità del cavo Grove alla presa Grove sul lato destro del Wio Terminal, guardando lo schermo. Questa è la presa più lontana dal pulsante di accensione.

![Il sensore di temperatura Grove collegato alla presa destra](../../../../../translated_images/wio-temperature-sensor.2934928f38c7f79a.it.png)

## Programmare il sensore di temperatura

Ora il Wio Terminal può essere programmato per utilizzare il sensore di temperatura collegato.

### Attività - programmare il sensore di temperatura

Programma il dispositivo.

1. Crea un nuovo progetto Wio Terminal utilizzando PlatformIO. Chiama questo progetto `temperature-sensor`. Aggiungi il codice nella funzione `setup` per configurare la porta seriale.

    > ⚠️ Puoi fare riferimento [alle istruzioni per creare un progetto PlatformIO nel progetto 1, lezione 1, se necessario](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Aggiungi una dipendenza della libreria per la libreria Seeed Grove Humidity and Temperature sensor al file `platformio.ini` del progetto:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Puoi fare riferimento [alle istruzioni per aggiungere librerie a un progetto PlatformIO nel progetto 1, lezione 4, se necessario](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Aggiungi le seguenti direttive `#include` all'inizio del file, sotto l'esistente `#include <Arduino.h>`:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Questo importa i file necessari per interagire con il sensore. Il file di intestazione `DHT.h` contiene il codice per il sensore stesso, e aggiungere l'intestazione `SPI.h` garantisce che il codice necessario per comunicare con il sensore venga collegato durante la compilazione dell'app.

1. Prima della funzione `setup`, dichiara il sensore DHT:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Questo dichiara un'istanza della classe `DHT` che gestisce il sensore digitale di umidità e temperatura. Questo è collegato alla porta `D0`, la presa Grove sul lato destro del Wio Terminal. Il secondo parametro indica al codice che il sensore utilizzato è il sensore *DHT11* - la libreria che stai utilizzando supporta altre varianti di questo sensore.

1. Nella funzione `setup`, aggiungi il codice per configurare la connessione seriale:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. Alla fine della funzione `setup`, dopo l'ultimo `delay`, aggiungi una chiamata per avviare il sensore DHT:

    ```cpp
    dht.begin();
    ```

1. Nella funzione `loop`, aggiungi il codice per chiamare il sensore e stampare la temperatura sulla porta seriale:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Questo codice dichiara un array vuoto di 2 float e lo passa alla chiamata `readTempAndHumidity` sull'istanza `DHT`. Questa chiamata popola l'array con 2 valori: l'umidità va nel primo elemento dell'array (indice 0, poiché in C++ gli array sono basati su zero), e la temperatura va nel secondo elemento (indice 1).

    La temperatura viene letta dal secondo elemento dell'array e stampata sulla porta seriale.

    > 🇺🇸 La temperatura viene letta in gradi Celsius. Per gli americani, per convertirla in Fahrenheit, dividi il valore in Celsius per 5, poi moltiplica per 9 e aggiungi 32. Ad esempio, una lettura di temperatura di 20°C diventa ((20/5)*9) + 32 = 68°F.

1. Compila e carica il codice sul Wio Terminal.

    > ⚠️ Puoi fare riferimento [alle istruzioni per creare un progetto PlatformIO nel progetto 1, lezione 1, se necessario](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Una volta caricato, puoi monitorare la temperatura utilizzando il monitor seriale:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Puoi trovare questo codice nella cartella [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 Il tuo programma per il sensore di temperatura è stato un successo!

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.