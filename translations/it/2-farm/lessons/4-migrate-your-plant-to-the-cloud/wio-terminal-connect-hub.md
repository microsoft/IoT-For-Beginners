<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-25T17:08:23+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "it"
}
-->
# Collega il tuo dispositivo IoT al cloud - Wio Terminal

In questa parte della lezione, collegherai il tuo Wio Terminal al tuo IoT Hub per inviare telemetria e ricevere comandi.

## Collega il tuo dispositivo a IoT Hub

Il prossimo passo è collegare il tuo dispositivo a IoT Hub.

### Attività - collegamento a IoT Hub

1. Apri il progetto `soil-moisture-sensor` in VS Code.

1. Apri il file `platformio.ini`. Rimuovi la dipendenza della libreria `knolleary/PubSubClient`. Questa veniva utilizzata per connettersi al broker MQTT pubblico e non è necessaria per connettersi a IoT Hub.

1. Aggiungi le seguenti dipendenze di libreria:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    La libreria `Seeed Arduino RTC` fornisce il codice per interagire con un orologio in tempo reale nel Wio Terminal, utilizzato per tenere traccia del tempo. Le altre librerie consentono al tuo dispositivo IoT di connettersi a IoT Hub.

1. Aggiungi quanto segue alla fine del file `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Questo imposta un flag del compilatore necessario per compilare il codice di Arduino IoT Hub.

1. Apri il file header `config.h`. Rimuovi tutte le impostazioni MQTT e aggiungi la seguente costante per la stringa di connessione del dispositivo:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Sostituisci `<connection string>` con la stringa di connessione del tuo dispositivo che hai copiato in precedenza.

1. La connessione a IoT Hub utilizza un token basato sul tempo. Questo significa che il dispositivo IoT deve conoscere l'ora corrente. A differenza dei sistemi operativi come Windows, macOS o Linux, i microcontrollori non sincronizzano automaticamente l'ora corrente tramite Internet. Questo significa che dovrai aggiungere del codice per ottenere l'ora corrente da un [server NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Una volta ottenuta l'ora, può essere memorizzata in un orologio in tempo reale nel Wio Terminal, consentendo di richiedere l'ora corretta in un secondo momento, a meno che il dispositivo non perda alimentazione. Aggiungi un nuovo file chiamato `ntp.h` con il seguente codice:

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    I dettagli di questo codice sono al di fuori dello scopo di questa lezione. Definisce una funzione chiamata `initTime` che ottiene l'ora corrente da un server NTP e la utilizza per impostare l'orologio sul Wio Terminal.

1. Apri il file `main.cpp` e rimuovi tutto il codice MQTT, inclusi il file header `PubSubClient.h`, la dichiarazione della variabile `PubSubClient`, i metodi `reconnectMQTTClient` e `createMQTTClient`, e qualsiasi chiamata a queste variabili e metodi. Questo file dovrebbe contenere solo il codice per connettersi al WiFi, ottenere l'umidità del suolo e creare un documento JSON con questi dati.

1. Aggiungi le seguenti direttive `#include` all'inizio del file `main.cpp` per includere i file header delle librerie IoT Hub e per impostare l'ora:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Aggiungi la seguente chiamata alla fine della funzione `setup` per impostare l'ora corrente:

    ```cpp
    initTime();
    ```

1. Aggiungi la seguente dichiarazione di variabile all'inizio del file, appena sotto le direttive include:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Questo dichiara un `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, un handle per una connessione a IoT Hub.

1. Sotto questa, aggiungi il seguente codice:

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    Questo dichiara una funzione di callback che verrà chiamata quando la connessione a IoT Hub cambia stato, ad esempio durante la connessione o la disconnessione. Lo stato viene inviato alla porta seriale.

1. Sotto questa, aggiungi una funzione per connettersi a IoT Hub:

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    Questo codice inizializza il codice della libreria IoT Hub, quindi crea una connessione utilizzando la stringa di connessione nel file header `config.h`. Questa connessione si basa su MQTT. Se la connessione fallisce, questo viene inviato alla porta seriale - se vedi questo nell'output, controlla la stringa di connessione. Infine, viene configurato il callback dello stato della connessione.

1. Chiama questa funzione nella funzione `setup` sotto la chiamata a `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Come per il client MQTT, questo codice viene eseguito su un singolo thread e necessita di tempo per elaborare i messaggi inviati dall'hub e all'hub. Aggiungi quanto segue all'inizio della funzione `loop` per fare ciò:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Compila e carica questo codice. Vedrai la connessione nel monitor seriale:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    Nell'output puoi vedere l'ora NTP che viene recuperata, seguita dalla connessione del client del dispositivo. Potrebbero essere necessari alcuni secondi per connettersi, quindi potresti vedere l'umidità del suolo nell'output mentre il dispositivo si sta connettendo.

    > 💁 Puoi convertire l'ora UNIX dell'NTP in una versione più leggibile utilizzando un sito web come [unixtimestamp.com](https://www.unixtimestamp.com)

## Invia telemetria

Ora che il tuo dispositivo è connesso, puoi inviare telemetria a IoT Hub invece che al broker MQTT.

### Attività - invia telemetria

1. Aggiungi la seguente funzione sopra la funzione `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Questo codice crea un messaggio IoT Hub da una stringa passata come parametro, lo invia all'hub, quindi pulisce l'oggetto del messaggio.

1. Chiama questo codice nella funzione `loop`, subito dopo la riga in cui la telemetria viene inviata alla porta seriale:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Gestisci i comandi

Il tuo dispositivo deve gestire un comando dal codice server per controllare il relè. Questo viene inviato come una richiesta di metodo diretto.

## Attività - gestisci una richiesta di metodo diretto

1. Aggiungi il seguente codice prima della funzione `connectIoTHub`:

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    Questo codice definisce un metodo di callback che la libreria IoT Hub può chiamare quando riceve una richiesta di metodo diretto. Il metodo richiesto viene inviato nel parametro `method_name`. Questa funzione stampa il metodo chiamato sulla porta seriale, quindi accende o spegne il relè a seconda del nome del metodo.

    > 💁 Questo potrebbe anche essere implementato in un singolo metodo diretto, passando lo stato desiderato del relè in un payload che può essere passato con la richiesta del metodo e disponibile dal parametro `payload`.

1. Aggiungi il seguente codice alla fine della funzione `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Le richieste di metodo diretto necessitano di una risposta, e la risposta è composta da due parti: una risposta come testo e un codice di ritorno. Questo codice creerà un risultato come il seguente documento JSON:

    ```JSON
    {
        "Result": ""
    }
    ```

    Questo viene quindi copiato nel parametro `response`, e la dimensione di questa risposta viene impostata nel parametro `response_size`. Questo codice quindi restituisce `IOTHUB_CLIENT_OK` per indicare che il metodo è stato gestito correttamente.

1. Collega il callback aggiungendo quanto segue alla fine della funzione `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. La funzione `loop` chiamerà la funzione `IoTHubDeviceClient_LL_DoWork` per elaborare gli eventi inviati da IoT Hub. Questo viene chiamato solo ogni 10 secondi a causa del `delay`, il che significa che i metodi diretti vengono elaborati solo ogni 10 secondi. Per rendere questo più efficiente, il ritardo di 10 secondi può essere implementato come molti ritardi più brevi, chiamando `IoTHubDeviceClient_LL_DoWork` ogni volta. Per fare ciò, aggiungi il seguente codice sopra la funzione `loop`:

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    Questo codice eseguirà un ciclo ripetutamente, chiamando `IoTHubDeviceClient_LL_DoWork` e ritardando di 100ms ogni volta. Lo farà tante volte quanto necessario per ritardare per il tempo specificato nel parametro `delay_time`. Questo significa che il dispositivo aspetta al massimo 100ms per elaborare le richieste di metodo diretto.

1. Nella funzione `loop`, rimuovi la chiamata a `IoTHubDeviceClient_LL_DoWork` e sostituisci la chiamata `delay(10000)` con il seguente codice per chiamare questa nuova funzione:

    ```cpp
    work_delay(10000);
    ```

> 💁 Puoi trovare questo codice nella cartella [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Il tuo programma per il sensore di umidità del suolo è connesso al tuo IoT Hub!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.