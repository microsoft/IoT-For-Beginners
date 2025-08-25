<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-25T16:38:15+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "it"
}
-->
# Classificare un'immagine utilizzando un classificatore di immagini basato su IoT Edge - Wio Terminal

In questa parte della lezione, utilizzerai il classificatore di immagini in esecuzione sul dispositivo IoT Edge.

## Utilizzare il classificatore IoT Edge

Il dispositivo IoT può essere reindirizzato per utilizzare il classificatore di immagini IoT Edge. L'URL per il classificatore di immagini è `http://<indirizzo IP o nome>/image`, sostituendo `<indirizzo IP o nome>` con l'indirizzo IP o il nome host del computer su cui è in esecuzione IoT Edge.

### Attività - utilizzare il classificatore IoT Edge

1. Apri il progetto dell'app `fruit-quality-detector` se non è già aperto.

1. Il classificatore di immagini è in esecuzione come API REST utilizzando HTTP, non HTTPS, quindi la chiamata deve utilizzare un client WiFi che funzioni solo con chiamate HTTP. Questo significa che il certificato non è necessario. Elimina il `CERTIFICATE` dal file `config.h`.

1. L'URL di previsione nel file `config.h` deve essere aggiornato al nuovo URL. Puoi anche eliminare il `PREDICTION_KEY`, poiché non è necessario.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Sostituisci `<URL>` con l'URL del tuo classificatore.

1. In `main.cpp`, modifica la direttiva include per il WiFi Client Secure per importare la versione standard HTTP:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Cambia la dichiarazione di `WiFiClient` per utilizzare la versione HTTP:

    ```cpp
    WiFiClient client;
    ```

1. Seleziona la riga che imposta il certificato sul client WiFi. Rimuovi la riga `client.setCACert(CERTIFICATE);` dalla funzione `connectWiFi`.

1. Nella funzione `classifyImage`, rimuovi la riga `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` che imposta la chiave di previsione nell'header.

1. Carica ed esegui il tuo codice. Punta la fotocamera verso un frutto e premi il pulsante C. Vedrai l'output nel monitor seriale:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Puoi trovare questo codice nella cartella [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Il tuo programma per classificare la qualità della frutta è stato un successo!

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.