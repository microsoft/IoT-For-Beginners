# Chiama il tuo rilevatore di oggetti dal tuo dispositivo IoT - Wio Terminal

Una volta pubblicato il tuo rilevatore di oggetti, potrà essere utilizzato dal tuo dispositivo IoT.

## Copia il progetto del classificatore di immagini

La maggior parte del tuo rilevatore di oggetti è simile al classificatore di immagini che hai creato in una lezione precedente.

### Attività - copia il progetto del classificatore di immagini

1. Collega la tua ArduCam al Wio Terminal, seguendo i passaggi descritti nella [lezione 2 del progetto di produzione](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Potresti anche voler fissare la fotocamera in una posizione stabile, ad esempio, appendendo il cavo sopra una scatola o una lattina, oppure fissando la fotocamera a una scatola con del nastro biadesivo.

1. Crea un nuovo progetto Wio Terminal utilizzando PlatformIO. Chiama questo progetto `stock-counter`.

1. Ripeti i passaggi descritti nella [lezione 2 del progetto di produzione](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) per catturare immagini dalla fotocamera.

1. Ripeti i passaggi descritti nella [lezione 2 del progetto di produzione](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) per chiamare il classificatore di immagini. La maggior parte di questo codice verrà riutilizzata per rilevare oggetti.

## Modifica il codice da classificatore a rilevatore di immagini

Il codice che hai utilizzato per classificare le immagini è molto simile a quello per rilevare oggetti. La principale differenza è l'URL che viene chiamato, ottenuto da Custom Vision, e i risultati della chiamata.

### Attività - modifica il codice da classificatore a rilevatore di immagini

1. Aggiungi la seguente direttiva `include` all'inizio del file `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Rinomina la funzione `classifyImage` in `detectStock`, sia il nome della funzione che la chiamata nella funzione `buttonPressed`.

1. Sopra la funzione `detectStock`, dichiara una soglia per filtrare eventuali rilevamenti con una bassa probabilità:

    ```cpp
    const float threshold = 0.3f;
    ```

    A differenza di un classificatore di immagini che restituisce un solo risultato per tag, il rilevatore di oggetti restituirà più risultati, quindi quelli con una bassa probabilità devono essere filtrati.

1. Sopra la funzione `detectStock`, dichiara una funzione per elaborare le previsioni:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    Questa funzione prende una lista di previsioni e le stampa sul monitor seriale.

1. Nella funzione `detectStock`, sostituisci il contenuto del ciclo `for` che scorre tra le previsioni con il seguente:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    Questo ciclo scorre tra le previsioni, confrontando la probabilità con la soglia. Tutte le previsioni con una probabilità superiore alla soglia vengono aggiunte a una `list` e passate alla funzione `processPredictions`.

1. Carica ed esegui il tuo codice. Punta la fotocamera verso oggetti su uno scaffale e premi il pulsante C. Vedrai l'output sul monitor seriale:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 Potresti dover regolare la `threshold` a un valore appropriato per le tue immagini.

    Sarai in grado di vedere l'immagine scattata e questi valori nella scheda **Predictions** in Custom Vision.

    ![4 lattine di concentrato di pomodoro su uno scaffale con previsioni per i 4 rilevamenti di 35.8%, 33.5%, 25.7% e 16.6%](../../../../../translated_images/it/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Puoi trovare questo codice nella cartella [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Il tuo programma per il conteggio delle scorte è stato un successo!

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.