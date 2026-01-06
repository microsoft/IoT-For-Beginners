<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-25T17:18:42+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "it"
}
-->
# Controlla la tua luce notturna tramite Internet - Wio Terminal

Il dispositivo IoT deve essere programmato per comunicare con *test.mosquitto.org* utilizzando MQTT, al fine di inviare valori di telemetria con la lettura del sensore di luce e ricevere comandi per controllare il LED.

In questa parte della lezione, collegherai il tuo Wio Terminal a un broker MQTT.

## Installa le librerie Arduino per WiFi e MQTT

Per comunicare con il broker MQTT, è necessario installare alcune librerie Arduino per utilizzare il chip WiFi del Wio Terminal e comunicare con MQTT. Quando si sviluppano dispositivi Arduino, è possibile utilizzare una vasta gamma di librerie che contengono codice open-source e implementano numerose funzionalità. Seeed pubblica librerie per il Wio Terminal che consentono la comunicazione tramite WiFi. Altri sviluppatori hanno pubblicato librerie per comunicare con broker MQTT, e utilizzerai queste librerie con il tuo dispositivo.

Queste librerie sono fornite come codice sorgente che può essere importato automaticamente in PlatformIO e compilato per il tuo dispositivo. In questo modo, le librerie Arduino funzioneranno su qualsiasi dispositivo che supporta il framework Arduino, a condizione che il dispositivo disponga dell'hardware specifico richiesto da quella libreria. Alcune librerie, come le librerie WiFi di Seeed, sono specifiche per determinati hardware.

Le librerie possono essere installate globalmente e compilate se necessario, oppure in un progetto specifico. Per questo compito, le librerie saranno installate nel progetto.

✅ Puoi saperne di più sulla gestione delle librerie e su come trovarle e installarle nella [documentazione delle librerie di PlatformIO](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Attività - installa le librerie Arduino per WiFi e MQTT

Installa le librerie Arduino.

1. Apri il progetto della luce notturna in VS Code.

1. Aggiungi quanto segue alla fine del file `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Questo importa le librerie WiFi di Seeed. La sintassi `@ <numero>` si riferisce a una versione specifica della libreria.

    > 💁 Puoi rimuovere `@ <numero>` per utilizzare sempre l'ultima versione delle librerie, ma non ci sono garanzie che le versioni successive funzionino con il codice sottostante. Il codice qui è stato testato con questa versione delle librerie.

    Questo è tutto ciò che devi fare per aggiungere le librerie. La prossima volta che PlatformIO compila il progetto, scaricherà il codice sorgente di queste librerie e lo compilerà nel tuo progetto.

1. Aggiungi quanto segue a `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Questo importa [PubSubClient](https://github.com/knolleary/pubsubclient), un client MQTT per Arduino.

## Connettersi al WiFi

Ora il Wio Terminal può essere connesso al WiFi.

### Attività - connettersi al WiFi

Connetti il Wio Terminal al WiFi.

1. Crea un nuovo file nella cartella `src` chiamato `config.h`. Puoi farlo selezionando la cartella `src`, o il file `main.cpp` al suo interno, e selezionando il pulsante **Nuovo file** dall'esploratore. Questo pulsante appare solo quando il cursore è sull'esploratore.

    ![Il pulsante nuovo file](../../../../../translated_images/vscode-new-file-button.182702340fe6723c.it.png)

1. Aggiungi il seguente codice a questo file per definire le costanti per le credenziali WiFi:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Sostituisci `<SSID>` con l'SSID del tuo WiFi. Sostituisci `<PASSWORD>` con la password del tuo WiFi.

1. Apri il file `main.cpp`.

1. Aggiungi le seguenti direttive `#include` all'inizio del file:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Questo include i file header per le librerie aggiunte in precedenza, oltre al file header di configurazione. Questi file header sono necessari per indicare a PlatformIO di includere il codice delle librerie. Senza includere esplicitamente questi file header, parte del codice non verrà compilato e otterrai errori di compilazione.

1. Aggiungi il seguente codice sopra la funzione `setup`:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    Questo codice esegue un ciclo finché il dispositivo non è connesso al WiFi e tenta di connettersi utilizzando l'SSID e la password dal file header di configurazione.

1. Aggiungi una chiamata a questa funzione in fondo alla funzione `setup`, dopo che i pin sono stati configurati.

    ```cpp
    connectWiFi();
    ```

1. Carica questo codice sul tuo dispositivo per verificare che la connessione WiFi funzioni. Dovresti vedere questo nel monitor seriale.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Connettersi a MQTT

Una volta che il Wio Terminal è connesso al WiFi, può connettersi al broker MQTT.

### Attività - connettersi a MQTT

Connetti al broker MQTT.

1. Aggiungi il seguente codice in fondo al file `config.h` per definire i dettagli di connessione per il broker MQTT:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Sostituisci `<ID>` con un ID univoco che sarà utilizzato come nome di questo client dispositivo e successivamente per i topic che questo dispositivo pubblica e sottoscrive. Il broker *test.mosquitto.org* è pubblico e utilizzato da molte persone, inclusi altri studenti che lavorano su questo compito. Avere un nome client MQTT univoco e nomi di topic univoci garantisce che il tuo codice non entri in conflitto con quello di altri. Avrai anche bisogno di questo ID quando creerai il codice del server più avanti in questo compito.

    > 💁 Puoi utilizzare un sito web come [GUIDGen](https://www.guidgen.com) per generare un ID univoco.

    Il `BROKER` è l'URL del broker MQTT.

    Il `CLIENT_NAME` è un nome univoco per questo client MQTT sul broker.

1. Apri il file `main.cpp` e aggiungi il seguente codice sotto la funzione `connectWiFi` e sopra la funzione `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Questo codice crea un client WiFi utilizzando le librerie WiFi del Wio Terminal e lo utilizza per creare un client MQTT.

1. Sotto questo codice, aggiungi il seguente:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    Questa funzione testa la connessione al broker MQTT e si riconnette se non è connessa. Esegue un ciclo finché non è connessa e tenta di connettersi utilizzando il nome client univoco definito nel file header di configurazione.

    Se la connessione fallisce, riprova dopo 5 secondi.

1. Aggiungi il seguente codice sotto la funzione `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Questo codice imposta il broker MQTT per il client, oltre a configurare il callback quando viene ricevuto un messaggio. Tenta quindi di connettersi al broker.

1. Chiama la funzione `createMQTTClient` nella funzione `setup` dopo che il WiFi è connesso.

1. Sostituisci l'intera funzione `loop` con il seguente codice:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Questo codice inizia riconnettendosi al broker MQTT. Queste connessioni possono essere interrotte facilmente, quindi vale la pena controllare regolarmente e riconnettersi se necessario. Chiama quindi il metodo `loop` sul client MQTT per elaborare eventuali messaggi in arrivo sul topic sottoscritto. Questa applicazione è single-threaded, quindi i messaggi non possono essere ricevuti su un thread in background; pertanto, è necessario allocare tempo sul thread principale per elaborare eventuali messaggi in attesa sulla connessione di rete.

    Infine, un ritardo di 2 secondi garantisce che i livelli di luce non vengano inviati troppo frequentemente e riduce il consumo energetico del dispositivo.

1. Carica il codice sul tuo Wio Terminal e utilizza il Monitor Serial per vedere il dispositivo connettersi al WiFi e a MQTT.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 Puoi trovare questo codice nella cartella [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Hai connesso con successo il tuo dispositivo a un broker MQTT.

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.