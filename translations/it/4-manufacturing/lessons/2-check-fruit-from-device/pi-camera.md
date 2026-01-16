<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-25T16:30:49+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "it"
}
-->
# Catturare un'immagine - Raspberry Pi

In questa parte della lezione, aggiungerai un sensore della fotocamera al tuo Raspberry Pi e leggerai immagini da esso.

## Hardware

Il Raspberry Pi necessita di una fotocamera.

La fotocamera che utilizzerai è un [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/). Questa fotocamera è progettata per funzionare con il Raspberry Pi e si collega tramite un connettore dedicato sul Pi.

> 💁 Questa fotocamera utilizza il [Camera Serial Interface, un protocollo dell'alleanza Mobile Industry Processor Interface](https://wikipedia.org/wiki/Camera_Serial_Interface), noto come MIPI-CSI. Si tratta di un protocollo dedicato per l'invio di immagini.

## Collegare la fotocamera

La fotocamera può essere collegata al Raspberry Pi utilizzando un cavo a nastro.

### Attività - collegare la fotocamera

![Una fotocamera Raspberry Pi](../../../../../translated_images/it/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. Spegni il Raspberry Pi.

1. Collega il cavo a nastro fornito con la fotocamera alla fotocamera stessa. Per farlo, tira delicatamente la clip di plastica nera nel supporto in modo che si apra leggermente, quindi inserisci il cavo nella presa, con il lato blu rivolto lontano dall'obiettivo e le strisce metalliche rivolte verso l'obiettivo. Una volta inserito completamente, spingi la clip di plastica nera per fissarlo.

    Puoi trovare un'animazione che mostra come aprire la clip e inserire il cavo nella [documentazione introduttiva del modulo fotocamera Raspberry Pi](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

    ![Il cavo a nastro inserito nel modulo fotocamera](../../../../../translated_images/it/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. Rimuovi il Grove Base Hat dal Raspberry Pi.

1. Fai passare il cavo a nastro attraverso lo slot per la fotocamera nel Grove Base Hat. Assicurati che il lato blu del cavo sia rivolto verso le porte analogiche etichettate **A0**, **A1**, ecc.

    ![Il cavo a nastro che passa attraverso il Grove Base Hat](../../../../../translated_images/it/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. Inserisci il cavo a nastro nella porta della fotocamera sul Raspberry Pi. Ancora una volta, solleva la clip di plastica nera, inserisci il cavo, quindi spingi la clip per fissarlo. Il lato blu del cavo dovrebbe essere rivolto verso le porte USB ed Ethernet.

    ![Il cavo a nastro collegato alla presa della fotocamera sul Raspberry Pi](../../../../../translated_images/it/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. Rimonta il Grove Base Hat.

## Programmare la fotocamera

Ora il Raspberry Pi può essere programmato per utilizzare la fotocamera tramite la libreria Python [PiCamera](https://pypi.org/project/picamera/).

### Attività - abilitare la modalità fotocamera legacy

Purtroppo, con il rilascio di Raspberry Pi OS Bullseye, il software della fotocamera incluso nel sistema operativo è cambiato, il che significa che di default PiCamera non funziona più. È in fase di sviluppo un sostituto, chiamato PiCamera2, ma non è ancora pronto per l'uso.

Per ora, puoi impostare il tuo Raspberry Pi in modalità fotocamera legacy per consentire il funzionamento di PiCamera. La presa della fotocamera è anche disabilitata di default, ma l'attivazione del software legacy della fotocamera abilita automaticamente la presa.

1. Accendi il Raspberry Pi e attendi che si avvii.

1. Avvia VS Code, direttamente sul Raspberry Pi o connettendoti tramite l'estensione Remote SSH.

1. Esegui i seguenti comandi dal terminale:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    Questo comando attiverà un'impostazione per abilitare il software legacy della fotocamera, quindi riavvierà il Raspberry Pi per applicare l'impostazione.

1. Attendi che il Raspberry Pi si riavvii, quindi riapri VS Code.

### Attività - programmare la fotocamera

Programma il dispositivo.

1. Dal terminale, crea una nuova cartella nella directory home dell'utente `pi` chiamata `fruit-quality-detector`. Crea un file in questa cartella chiamato `app.py`.

1. Apri questa cartella in VS Code.

1. Per interagire con la fotocamera, puoi utilizzare la libreria Python PiCamera. Installa il pacchetto Pip con il seguente comando:

    ```sh
    pip3 install picamera
    ```

1. Aggiungi il seguente codice al file `app.py`:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Questo codice importa alcune librerie necessarie, inclusa la libreria `PiCamera`.

1. Aggiungi il seguente codice sotto per inizializzare la fotocamera:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Questo codice crea un oggetto PiCamera e imposta la risoluzione a 640x480. Sebbene siano supportate risoluzioni più alte (fino a 3280x2464), il classificatore di immagini funziona con immagini molto più piccole (227x227), quindi non è necessario catturare e inviare immagini più grandi.

    La riga `camera.rotation = 0` imposta la rotazione dell'immagine. Il cavo a nastro entra nella parte inferiore della fotocamera, ma se la fotocamera è stata ruotata per puntare meglio verso l'oggetto da classificare, puoi modificare questa riga con il numero di gradi di rotazione.

    ![La fotocamera sospesa sopra una lattina](../../../../../translated_images/it/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    Ad esempio, se sospendi il cavo a nastro sopra qualcosa in modo che si trovi nella parte superiore della fotocamera, imposta la rotazione a 180:

    ```python
    camera.rotation = 180
    ```

    La fotocamera impiega alcuni secondi per avviarsi, da qui la riga `time.sleep(2)`.

1. Aggiungi il seguente codice sotto per catturare l'immagine come dati binari:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Questo codice crea un oggetto `BytesIO` per memorizzare i dati binari. L'immagine viene letta dalla fotocamera come file JPEG e memorizzata in questo oggetto. Questo oggetto ha un indicatore di posizione per sapere dove si trova nei dati, quindi la riga `image.seek(0)` sposta questa posizione all'inizio in modo che tutti i dati possano essere letti successivamente.

1. Sotto questo, aggiungi il seguente codice per salvare l'immagine in un file:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Questo codice apre un file chiamato `image.jpg` per la scrittura, quindi legge tutti i dati dall'oggetto `BytesIO` e li scrive nel file.

    > 💁 Puoi catturare l'immagine direttamente in un file invece che in un oggetto `BytesIO` passando il nome del file alla chiamata `camera.capture`. Il motivo per utilizzare l'oggetto `BytesIO` è che più avanti in questa lezione potrai inviare l'immagine al tuo classificatore di immagini.

1. Punta la fotocamera verso qualcosa ed esegui questo codice.

1. Un'immagine verrà catturata e salvata come `image.jpg` nella cartella corrente. Vedrai questo file nell'esploratore di VS Code. Seleziona il file per visualizzare l'immagine. Se necessita di rotazione, aggiorna la riga `camera.rotation = 0` come necessario e scatta un'altra foto.

> 💁 Puoi trovare questo codice nella cartella [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi).

😀 Il tuo programma per la fotocamera è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche potrebbero contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.