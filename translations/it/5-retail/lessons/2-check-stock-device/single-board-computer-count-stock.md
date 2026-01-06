<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-25T16:23:12+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "it"
}
-->
# Conta il magazzino dal tuo dispositivo IoT - Hardware IoT virtuale e Raspberry Pi

Una combinazione delle previsioni e dei loro riquadri di delimitazione può essere utilizzata per contare il magazzino in un'immagine.

## Mostra i riquadri di delimitazione

Come passaggio utile per il debug, puoi non solo stampare i riquadri di delimitazione, ma anche disegnarli sull'immagine salvata su disco quando un'immagine è stata catturata.

### Attività - stampa i riquadri di delimitazione

1. Assicurati che il progetto `stock-counter` sia aperto in VS Code e che l'ambiente virtuale sia attivato se stai utilizzando un dispositivo IoT virtuale.

1. Modifica l'istruzione `print` nel ciclo `for` con la seguente per stampare i riquadri di delimitazione sulla console:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Esegui l'app con la fotocamera puntata su alcuni articoli su uno scaffale. I riquadri di delimitazione verranno stampati sulla console, con valori di sinistra, alto, larghezza e altezza compresi tra 0 e 1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Attività - disegna i riquadri di delimitazione sull'immagine

1. Il pacchetto Pip [Pillow](https://pypi.org/project/Pillow/) può essere utilizzato per disegnare sulle immagini. Installa questo pacchetto con il seguente comando:

    ```sh
    pip3 install pillow
    ```

    Se stai utilizzando un dispositivo IoT virtuale, assicurati di eseguire questo comando all'interno dell'ambiente virtuale attivato.

1. Aggiungi la seguente istruzione di importazione all'inizio del file `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Questo importa il codice necessario per modificare l'immagine.

1. Aggiungi il seguente codice alla fine del file `app.py`:

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    Questo codice apre l'immagine salvata in precedenza per la modifica. Successivamente, esegue un ciclo sulle previsioni ottenendo i riquadri di delimitazione e calcola la coordinata in basso a destra utilizzando i valori del riquadro di delimitazione compresi tra 0 e 1. Questi valori vengono poi convertiti in coordinate dell'immagine moltiplicandoli per la dimensione rilevante dell'immagine. Ad esempio, se il valore sinistro fosse 0.5 su un'immagine larga 600 pixel, questo verrebbe convertito in 300 (0.5 x 600 = 300).

    Ogni riquadro di delimitazione viene disegnato sull'immagine utilizzando una linea rossa. Infine, l'immagine modificata viene salvata, sovrascrivendo l'immagine originale.

1. Esegui l'app con la fotocamera puntata su alcuni articoli su uno scaffale. Vedrai il file `image.jpg` nell'esploratore di VS Code e potrai selezionarlo per vedere i riquadri di delimitazione.

    ![4 lattine di concentrato di pomodoro con riquadri di delimitazione attorno a ciascuna lattina](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.it.jpg)

## Conta il magazzino

Nell'immagine mostrata sopra, i riquadri di delimitazione hanno un piccolo sovrapposizione. Se questa sovrapposizione fosse molto più grande, i riquadri di delimitazione potrebbero indicare lo stesso oggetto. Per contare correttamente gli oggetti, è necessario ignorare i riquadri con una sovrapposizione significativa.

### Attività - conta il magazzino ignorando la sovrapposizione

1. Il pacchetto Pip [Shapely](https://pypi.org/project/Shapely/) può essere utilizzato per calcolare l'intersezione. Se stai utilizzando un Raspberry Pi, dovrai prima installare una dipendenza della libreria:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Installa il pacchetto Pip Shapely:

    ```sh
    pip3 install shapely
    ```

    Se stai utilizzando un dispositivo IoT virtuale, assicurati di eseguire questo comando all'interno dell'ambiente virtuale attivato.

1. Aggiungi la seguente istruzione di importazione all'inizio del file `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    Questo importa il codice necessario per creare poligoni e calcolare la sovrapposizione.

1. Sopra il codice che disegna i riquadri di delimitazione, aggiungi il seguente codice:

    ```python
    overlap_threshold = 0.20
    ```

    Questo definisce la percentuale di sovrapposizione consentita prima che i riquadri di delimitazione vengano considerati lo stesso oggetto. 0.20 definisce una sovrapposizione del 20%.

1. Per calcolare la sovrapposizione utilizzando Shapely, i riquadri di delimitazione devono essere convertiti in poligoni Shapely. Aggiungi la seguente funzione per farlo:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Questa funzione crea un poligono utilizzando il riquadro di delimitazione di una previsione.

1. La logica per rimuovere gli oggetti sovrapposti prevede di confrontare tutti i riquadri di delimitazione e, se una coppia di previsioni ha riquadri di delimitazione che si sovrappongono oltre la soglia, eliminare una delle previsioni. Per confrontare tutte le previsioni, si confronta la previsione 1 con 2, 3, 4, ecc., poi la 2 con 3, 4, ecc. Il seguente codice esegue questa operazione:

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    La sovrapposizione viene calcolata utilizzando il metodo `Polygon.intersection` di Shapely, che restituisce un poligono che rappresenta la sovrapposizione. L'area viene quindi calcolata da questo poligono. La soglia di sovrapposizione non è un valore assoluto, ma deve essere una percentuale del riquadro di delimitazione, quindi viene trovato il riquadro più piccolo e la soglia di sovrapposizione viene utilizzata per calcolare quale area può essere sovrapposta senza superare la percentuale di soglia di sovrapposizione del riquadro più piccolo. Se la sovrapposizione supera questa soglia, la previsione viene contrassegnata per l'eliminazione.

    Una volta che una previsione è stata contrassegnata per l'eliminazione, non è necessario controllarla di nuovo, quindi il ciclo interno si interrompe per controllare la previsione successiva. Non è possibile eliminare elementi da una lista mentre si sta iterando su di essa, quindi i riquadri di delimitazione che si sovrappongono oltre la soglia vengono aggiunti alla lista `to_delete`, quindi eliminati alla fine.

    Infine, il conteggio del magazzino viene stampato sulla console. Questo potrebbe poi essere inviato a un servizio IoT per avvisare se i livelli di magazzino sono bassi. Tutto questo codice viene eseguito prima che i riquadri di delimitazione vengano disegnati, quindi vedrai le previsioni del magazzino senza sovrapposizioni sulle immagini generate.

    > 💁 Questo è un modo molto semplice per rimuovere le sovrapposizioni, eliminando semplicemente il primo in una coppia sovrapposta. Per il codice di produzione, vorresti aggiungere più logica qui, come considerare le sovrapposizioni tra più oggetti o se un riquadro di delimitazione è contenuto da un altro.

1. Esegui l'app con la fotocamera puntata su alcuni articoli su uno scaffale. L'output indicherà il numero di riquadri di delimitazione senza sovrapposizioni che superano la soglia. Prova a regolare il valore `overlap_threshold` per vedere le previsioni ignorate.

> 💁 Puoi trovare questo codice nella cartella [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) o [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Il tuo programma per il conteggio del magazzino è stato un successo!

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.