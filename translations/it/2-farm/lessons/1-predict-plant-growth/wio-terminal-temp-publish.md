<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-25T16:47:22+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "it"
}
-->
# Pubblicare la temperatura - Wio Terminal

In questa parte della lezione, pubblicherai i valori di temperatura rilevati dal Wio Terminal tramite MQTT, in modo che possano essere utilizzati successivamente per calcolare il GDD.

## Pubblicare la temperatura

Una volta letta la temperatura, questa può essere pubblicata tramite MQTT a un codice 'server' che leggerà i valori e li memorizzerà pronti per essere utilizzati nel calcolo del GDD. I microcontrollori non leggono l'ora da Internet né tengono traccia del tempo con un orologio in tempo reale di default; il dispositivo deve essere programmato per farlo, supponendo che disponga dell'hardware necessario.

Per semplificare le cose in questa lezione, l'ora non verrà inviata insieme ai dati del sensore; invece, potrà essere aggiunta dal codice server quando riceve i messaggi.

### Attività

Programma il dispositivo per pubblicare i dati della temperatura.

1. Apri il progetto `temperature-sensor` per il Wio Terminal.

1. Ripeti i passaggi che hai eseguito nella lezione 4 per connetterti a MQTT e inviare telemetria. Utilizzerai lo stesso broker pubblico Mosquitto.

    I passaggi sono i seguenti:

    - Aggiungi le librerie Seeed WiFi e MQTT al file `.ini`
    - Aggiungi il file di configurazione e il codice per connetterti al WiFi
    - Aggiungi il codice per connetterti al broker MQTT
    - Aggiungi il codice per pubblicare la telemetria

    > ⚠️ Consulta le [istruzioni per connettersi a MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) e le [istruzioni per inviare telemetria](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) dalla lezione 4, se necessario.

1. Assicurati che il `CLIENT_NAME` nel file header `config.h` rifletta questo progetto:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Per la telemetria, invece di inviare un valore di luce, invia il valore della temperatura letto dal sensore DHT in una proprietà del documento JSON chiamata `temperature`, modificando la funzione `loop` in `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Non è necessario leggere il valore della temperatura molto spesso, poiché non cambierà molto in un breve intervallo di tempo. Imposta quindi il `delay` nella funzione `loop` a 10 minuti:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 La funzione `delay` prende il tempo in millisecondi, quindi per renderlo più leggibile il valore viene passato come risultato di un calcolo. 1.000 ms in un secondo, 60 secondi in un minuto, quindi 10 x (60 secondi in un minuto) x (1.000 ms in un secondo) dà un ritardo di 10 minuti.

1. Carica il codice sul tuo Wio Terminal e utilizza il monitor seriale per vedere la temperatura inviata al broker MQTT.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Puoi trovare questo codice nella cartella [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Hai pubblicato con successo la temperatura come telemetria dal tuo dispositivo.

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.