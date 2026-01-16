<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-25T16:20:16+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "it"
}
-->
# Chiama il tuo rilevatore di oggetti dal tuo dispositivo IoT - Hardware IoT virtuale e Raspberry Pi

Una volta che il tuo rilevatore di oggetti è stato pubblicato, può essere utilizzato dal tuo dispositivo IoT.

## Copia il progetto del classificatore di immagini

La maggior parte del tuo rilevatore di stock è simile al classificatore di immagini che hai creato in una lezione precedente.

### Attività - copia il progetto del classificatore di immagini

1. Crea una cartella chiamata `stock-counter` sul tuo computer se stai utilizzando un dispositivo IoT virtuale, oppure sul tuo Raspberry Pi. Se stai utilizzando un dispositivo IoT virtuale, assicurati di configurare un ambiente virtuale.

1. Configura l'hardware della fotocamera.

    * Se stai utilizzando un Raspberry Pi, dovrai montare la PiCamera. Potresti anche voler fissare la fotocamera in una posizione stabile, ad esempio, appendendo il cavo sopra una scatola o una lattina, oppure fissando la fotocamera a una scatola con del nastro biadesivo.
    * Se stai utilizzando un dispositivo IoT virtuale, dovrai installare CounterFit e il CounterFit PyCamera shim. Se intendi utilizzare immagini statiche, cattura alcune immagini che il tuo rilevatore di oggetti non ha ancora visto. Se invece utilizzerai la webcam, assicurati che sia posizionata in modo da vedere gli oggetti che stai rilevando.

1. Replica i passaggi da [lezione 2 del progetto di produzione](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) per catturare immagini dalla fotocamera.

1. Replica i passaggi da [lezione 2 del progetto di produzione](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) per chiamare il classificatore di immagini. La maggior parte di questo codice verrà riutilizzata per rilevare oggetti.

## Modifica il codice da classificatore a rilevatore di immagini

Il codice che hai utilizzato per classificare le immagini è molto simile al codice per rilevare oggetti. La principale differenza è il metodo chiamato sul Custom Vision SDK e i risultati della chiamata.

### Attività - modifica il codice da classificatore a rilevatore di immagini

1. Elimina le tre righe di codice che classificano l'immagine e elaborano le previsioni:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Rimuovi queste tre righe.

1. Aggiungi il seguente codice per rilevare oggetti nell'immagine:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Questo codice chiama il metodo `detect_image` sul predittore per eseguire il rilevatore di oggetti. Successivamente raccoglie tutte le previsioni con una probabilità superiore a una soglia, stampandole sulla console.

    A differenza di un classificatore di immagini che restituisce solo un risultato per tag, il rilevatore di oggetti restituirà più risultati, quindi quelli con una bassa probabilità devono essere filtrati.

1. Esegui questo codice e catturerà un'immagine, inviandola al rilevatore di oggetti, e stamperà gli oggetti rilevati. Se stai utilizzando un dispositivo IoT virtuale, assicurati di avere un'immagine appropriata impostata in CounterFit, oppure che la tua webcam sia selezionata. Se stai utilizzando un Raspberry Pi, assicurati che la tua fotocamera sia puntata verso gli oggetti su uno scaffale.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Potresti dover regolare la `threshold` a un valore appropriato per le tue immagini.

    Sarai in grado di vedere l'immagine catturata e questi valori nella scheda **Predictions** in Custom Vision.

    ![4 lattine di concentrato di pomodoro su uno scaffale con previsioni per i 4 rilevamenti di 35.8%, 33.5%, 25.7% e 16.6%](../../../../../translated_images/it/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Puoi trovare questo codice nella cartella [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) o [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 Il tuo programma di conteggio degli stock è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche potrebbero contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si consiglia una traduzione professionale eseguita da un traduttore umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.