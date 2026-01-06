<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-25T16:22:28+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "it"
}
-->
# Conta il magazzino dal tuo dispositivo IoT - Wio Terminal

Una combinazione di previsioni e dei loro riquadri di delimitazione può essere utilizzata per contare gli oggetti in un'immagine.

## Conta il magazzino

![4 barattoli di concentrato di pomodoro con riquadri di delimitazione attorno a ciascun barattolo](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.it.jpg)

Nell'immagine mostrata sopra, i riquadri di delimitazione hanno un piccolo sovrapposizione. Se questa sovrapposizione fosse molto più grande, i riquadri di delimitazione potrebbero indicare lo stesso oggetto. Per contare correttamente gli oggetti, è necessario ignorare i riquadri con una sovrapposizione significativa.

### Attività - conta il magazzino ignorando la sovrapposizione

1. Apri il tuo progetto `stock-counter` se non è già aperto.

1. Sopra la funzione `processPredictions`, aggiungi il seguente codice:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Questo definisce la percentuale di sovrapposizione consentita prima che i riquadri di delimitazione vengano considerati lo stesso oggetto. 0.20 definisce una sovrapposizione del 20%.

1. Sotto questo, e sopra la funzione `processPredictions`, aggiungi il seguente codice per calcolare la sovrapposizione tra due rettangoli:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    Questo codice definisce una struttura `Point` per memorizzare i punti sull'immagine e una struttura `Rect` per definire un rettangolo utilizzando una coordinata in alto a sinistra e una in basso a destra. Successivamente, definisce una funzione `area` che calcola l'area di un rettangolo a partire da una coordinata in alto a sinistra e una in basso a destra.

    Poi definisce una funzione `overlappingArea` che calcola l'area di sovrapposizione di 2 rettangoli. Se non si sovrappongono, restituisce 0.

1. Sotto la funzione `overlappingArea`, dichiara una funzione per convertire un riquadro di delimitazione in un `Rect`:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    Questo prende una previsione dal rilevatore di oggetti, estrae il riquadro di delimitazione e utilizza i valori del riquadro di delimitazione per definire un rettangolo. Il lato destro viene calcolato dalla somma del lato sinistro e della larghezza. Il lato inferiore viene calcolato dalla somma del lato superiore e dell'altezza.

1. Le previsioni devono essere confrontate tra loro e, se 2 previsioni hanno una sovrapposizione superiore alla soglia, una di esse deve essere eliminata. La soglia di sovrapposizione è una percentuale, quindi deve essere moltiplicata per la dimensione del riquadro di delimitazione più piccolo per verificare che la sovrapposizione superi la percentuale data del riquadro di delimitazione, non la percentuale data dell'intera immagine. Inizia eliminando il contenuto della funzione `processPredictions`.

1. Aggiungi il seguente codice alla funzione `processPredictions` vuota:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    Questo codice dichiara un vettore per memorizzare le previsioni che non si sovrappongono. Poi esegue un ciclo su tutte le previsioni, creando un `Rect` dal riquadro di delimitazione.

    Successivamente, questo codice esegue un ciclo sulle previsioni rimanenti, iniziando da quella successiva alla previsione corrente. Questo evita che le previsioni vengano confrontate più di una volta - una volta che 1 e 2 sono state confrontate, non c'è bisogno di confrontare 2 con 1, solo con 3, 4, ecc.

    Per ogni coppia di previsioni viene calcolata l'area di sovrapposizione. Questa viene poi confrontata con l'area del riquadro di delimitazione più piccolo - se la sovrapposizione supera la percentuale di soglia del riquadro di delimitazione più piccolo, la previsione viene contrassegnata come non valida. Se dopo aver confrontato tutte le sovrapposizioni la previsione supera i controlli, viene aggiunta alla collezione `passed_predictions`.

    > 💁 Questo è un modo molto semplice per rimuovere le sovrapposizioni, eliminando semplicemente la prima in una coppia sovrapposta. Per il codice di produzione, sarebbe opportuno aggiungere più logica, come considerare le sovrapposizioni tra più oggetti o se un riquadro di delimitazione è contenuto da un altro.

1. Dopo questo, aggiungi il seguente codice per inviare i dettagli delle previsioni valide al monitor seriale:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    Questo codice esegue un ciclo sulle previsioni valide e stampa i loro dettagli sul monitor seriale.

1. Sotto questo, aggiungi il codice per stampare il numero di oggetti contati sul monitor seriale:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Questo potrebbe poi essere inviato a un servizio IoT per avvisare se i livelli di magazzino sono bassi.

1. Carica ed esegui il tuo codice. Punta la fotocamera verso gli oggetti su uno scaffale e premi il pulsante C. Prova a regolare il valore `overlap_threshold` per vedere le previsioni ignorate.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 Puoi trovare questo codice nella cartella [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Il tuo programma per contare il magazzino è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.