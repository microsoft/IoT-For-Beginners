<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-25T17:46:52+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "it"
}
-->
# Imposta un timer - Wio Terminal

In questa parte della lezione, chiamerai il tuo codice serverless per comprendere il discorso e imposterai un timer sul tuo Wio Terminal in base ai risultati.

## Imposta un timer

Il testo che ritorna dalla chiamata di riconoscimento vocale deve essere inviato al tuo codice serverless per essere elaborato da LUIS, ottenendo il numero di secondi per il timer. Questo numero di secondi può essere utilizzato per impostare un timer.

I microcontrollori non supportano nativamente i thread multipli in Arduino, quindi non ci sono classi standard per i timer come potresti trovare programmando in Python o in altri linguaggi di alto livello. Invece, puoi utilizzare librerie per timer che funzionano misurando il tempo trascorso nella funzione `loop` e chiamando funzioni quando il tempo è scaduto.

### Attività - invia il testo alla funzione serverless

1. Apri il progetto `smart-timer` in VS Code se non è già aperto.

1. Apri il file header `config.h` e aggiungi l'URL per la tua funzione app:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Sostituisci `<URL>` con l'URL della tua funzione app che hai ottenuto nell'ultimo passaggio della lezione precedente, puntando all'indirizzo IP della tua macchina locale che esegue la funzione app.

1. Crea un nuovo file nella cartella `src` chiamato `language_understanding.h`. Questo sarà utilizzato per definire una classe che invia il discorso riconosciuto alla tua funzione app per essere convertito in secondi utilizzando LUIS.

1. Aggiungi il seguente codice all'inizio di questo file:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Questo include alcuni file header necessari.

1. Definisci una classe chiamata `LanguageUnderstanding` e dichiara un'istanza di questa classe:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Per chiamare la tua funzione app, devi dichiarare un client WiFi. Aggiungi il seguente codice alla sezione `private` della classe:

    ```cpp
    WiFiClient _client;
    ```

1. Nella sezione `public`, dichiara un metodo chiamato `GetTimerDuration` per chiamare la funzione app:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. Nel metodo `GetTimerDuration`, aggiungi il seguente codice per costruire il JSON da inviare alla funzione app:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Questo converte il testo passato al metodo `GetTimerDuration` nel seguente JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    dove `<text>` è il testo passato alla funzione.

1. Sotto questo, aggiungi il seguente codice per effettuare la chiamata alla funzione app:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Questo effettua una richiesta POST alla funzione app, passando il corpo JSON e ottenendo il codice di risposta.

1. Aggiungi il seguente codice sotto questo:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Questo codice controlla il codice di risposta. Se è 200 (successo), allora il numero di secondi per il timer viene recuperato dal corpo della risposta. Altrimenti, un errore viene inviato al monitor seriale e il numero di secondi è impostato a 0.

1. Aggiungi il seguente codice alla fine di questo metodo per chiudere la connessione HTTP e restituire il numero di secondi:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. Nel file `main.cpp`, includi questo nuovo header:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Alla fine della funzione `processAudio`, chiama il metodo `GetTimerDuration` per ottenere la durata del timer:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Questo converte il testo dalla chiamata alla classe `SpeechToText` nel numero di secondi per il timer.

### Attività - imposta un timer

Il numero di secondi può essere utilizzato per impostare un timer.

1. Aggiungi la seguente dipendenza della libreria al file `platformio.ini` per aggiungere una libreria per impostare un timer:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Aggiungi una direttiva include per questa libreria al file `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Sopra la funzione `processAudio`, aggiungi il seguente codice:

    ```cpp
    auto timer = timer_create_default();
    ```

    Questo codice dichiara un timer chiamato `timer`.

1. Sotto questo, aggiungi il seguente codice:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Questa funzione `say` convertirà eventualmente il testo in voce, ma per ora scriverà semplicemente il testo passato al monitor seriale.

1. Sotto la funzione `say`, aggiungi il seguente codice:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Questa è una funzione di callback che verrà chiamata quando un timer scade. Viene passato un messaggio da dire quando il timer scade. I timer possono ripetersi, e questo può essere controllato dal valore di ritorno di questo callback - questo ritorna `false`, per indicare al timer di non eseguire nuovamente.

1. Aggiungi il seguente codice alla fine della funzione `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Questo codice controlla il numero totale di secondi e, se è 0, ritorna dalla chiamata alla funzione in modo che nessun timer venga impostato. Converte quindi il numero totale di secondi in minuti e secondi.

1. Sotto questo codice, aggiungi il seguente per creare un messaggio da dire quando il timer viene avviato:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. Sotto questo, aggiungi un codice simile per creare un messaggio da dire quando il timer è scaduto:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. Dopo questo, pronuncia il messaggio di avvio del timer:

    ```cpp
    say(begin_message);
    ```

1. Alla fine di questa funzione, avvia il timer:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Questo attiva il timer. Il timer è impostato utilizzando millisecondi, quindi il numero totale di secondi viene moltiplicato per 1.000 per convertirlo in millisecondi. La funzione `timerExpired` viene passata come callback, e il `end_message` viene passato come argomento da passare al callback. Questo callback accetta solo argomenti di tipo `void *`, quindi la stringa viene convertita di conseguenza.

1. Infine, il timer deve *ticchettare*, e questo viene fatto nella funzione `loop`. Aggiungi il seguente codice alla fine della funzione `loop`:

    ```cpp
    timer.tick();
    ```

1. Compila questo codice, caricalo sul tuo Wio Terminal e testalo attraverso il monitor seriale. Una volta che vedi `Ready` nel monitor seriale, premi il pulsante C (quello sul lato sinistro, più vicino all'interruttore di accensione) e parla. Verranno catturati 4 secondi di audio, convertiti in testo, inviati alla tua funzione app e verrà impostato un timer. Assicurati che la tua funzione app sia in esecuzione localmente.

    Vedrai quando il timer inizia e quando termina.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Puoi trovare questo codice nella cartella [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Il tuo programma per il timer è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.