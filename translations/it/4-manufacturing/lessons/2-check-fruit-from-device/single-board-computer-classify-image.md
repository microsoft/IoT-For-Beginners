<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-25T16:31:28+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "it"
}
-->
# Classificare un'immagine - Hardware IoT Virtuale e Raspberry Pi

In questa parte della lezione, invierai l'immagine catturata dalla fotocamera al servizio Custom Vision per classificarla.

## Inviare immagini a Custom Vision

Il servizio Custom Vision dispone di un SDK Python che puoi utilizzare per classificare le immagini.

### Attività - inviare immagini a Custom Vision

1. Apri la cartella `fruit-quality-detector` in VS Code. Se stai utilizzando un dispositivo IoT virtuale, assicurati che l'ambiente virtuale sia in esecuzione nel terminale.

1. L'SDK Python per inviare immagini a Custom Vision è disponibile come pacchetto Pip. Installalo con il seguente comando:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Aggiungi le seguenti istruzioni di importazione all'inizio del file `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Questo importa alcuni moduli dalle librerie di Custom Vision, uno per autenticarsi con la chiave di predizione e uno per fornire una classe client di predizione che può chiamare Custom Vision.

1. Aggiungi il seguente codice alla fine del file:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Sostituisci `<prediction_url>` con l'URL che hai copiato dalla finestra di dialogo *Prediction URL* in precedenza in questa lezione. Sostituisci `<prediction key>` con la chiave di predizione che hai copiato dalla stessa finestra di dialogo.

1. L'URL di predizione fornito dalla finestra di dialogo *Prediction URL* è progettato per essere utilizzato quando si chiama direttamente l'endpoint REST. L'SDK Python utilizza parti dell'URL in posizioni diverse. Aggiungi il seguente codice per suddividere questo URL nelle parti necessarie:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Questo divide l'URL, estraendo l'endpoint `https://<location>.api.cognitive.microsoft.com`, l'ID del progetto e il nome dell'iterazione pubblicata.

1. Crea un oggetto predictor per eseguire la predizione con il seguente codice:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    Le `prediction_credentials` avvolgono la chiave di predizione. Queste vengono poi utilizzate per creare un oggetto client di predizione che punta all'endpoint.

1. Invia l'immagine a Custom Vision utilizzando il seguente codice:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Questo riavvolge l'immagine all'inizio, quindi la invia al client di predizione.

1. Infine, mostra i risultati con il seguente codice:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Questo scorrerà tutte le predizioni che sono state restituite e le mostrerà nel terminale. Le probabilità restituite sono numeri in virgola mobile da 0 a 1, dove 0 rappresenta una probabilità dello 0% di corrispondenza con il tag, e 1 rappresenta una probabilità del 100%.

    > 💁 I classificatori di immagini restituiranno le percentuali per tutti i tag che sono stati utilizzati. Ogni tag avrà una probabilità che l'immagine corrisponda a quel tag.

1. Esegui il tuo codice, puntando la fotocamera verso della frutta, o utilizzando un set di immagini appropriato, o frutta visibile sulla tua webcam se stai utilizzando hardware IoT virtuale. Vedrai l'output nella console:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Sarai in grado di vedere l'immagine scattata e questi valori nella scheda **Predictions** in Custom Vision.

    ![Una banana in Custom Vision predetta come matura al 56,8% e acerba al 43,1%](../../../../../translated_images/it/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Puoi trovare questo codice nella cartella [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) o [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Il tuo programma per classificare la qualità della frutta è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.