<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-25T16:38:37+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "it"
}
-->
# Classificare un'immagine utilizzando un classificatore di immagini basato su IoT Edge - Hardware IoT Virtuale e Raspberry Pi

In questa parte della lezione, utilizzerai il classificatore di immagini in esecuzione sul dispositivo IoT Edge.

## Utilizzare il classificatore IoT Edge

Il dispositivo IoT può essere reindirizzato per utilizzare il classificatore di immagini IoT Edge. L'URL del classificatore di immagini è `http://<IP address or name>/image`, sostituendo `<IP address or name>` con l'indirizzo IP o il nome host del computer su cui è in esecuzione IoT Edge.

La libreria Python per Custom Vision funziona solo con modelli ospitati nel cloud, non con modelli ospitati su IoT Edge. Questo significa che sarà necessario utilizzare l'API REST per chiamare il classificatore.

### Attività - utilizzare il classificatore IoT Edge

1. Apri il progetto `fruit-quality-detector` in VS Code, se non è già aperto. Se stai utilizzando un dispositivo IoT virtuale, assicurati che l'ambiente virtuale sia attivato.

1. Apri il file `app.py` e rimuovi le istruzioni di importazione da `azure.cognitiveservices.vision.customvision.prediction` e `msrest.authentication`.

1. Aggiungi il seguente import all'inizio del file:

    ```python
    import requests
    ```

1. Elimina tutto il codice dopo che l'immagine è stata salvata in un file, da `image_file.write(image.read())` fino alla fine del file.

1. Aggiungi il seguente codice alla fine del file:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Sostituisci `<URL>` con l'URL del tuo classificatore.

    Questo codice effettua una richiesta REST POST al classificatore, inviando l'immagine come corpo della richiesta. I risultati vengono restituiti in formato JSON, che viene decodificato per stampare le probabilità.

1. Esegui il tuo codice, puntando la tua fotocamera verso della frutta, un set di immagini appropriato o della frutta visibile sulla tua webcam se stai utilizzando hardware IoT virtuale. Vedrai l'output nella console:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Puoi trovare questo codice nella cartella [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) o [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Il tuo programma per classificare la qualità della frutta è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.