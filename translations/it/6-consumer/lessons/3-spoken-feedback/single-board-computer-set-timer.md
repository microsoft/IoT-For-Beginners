<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-25T17:44:31+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "it"
}
-->
# Imposta un timer - Hardware IoT virtuale e Raspberry Pi

In questa parte della lezione, chiamerai il tuo codice serverless per comprendere il discorso e impostare un timer sul tuo dispositivo IoT virtuale o Raspberry Pi in base ai risultati.

## Imposta un timer

Il testo che viene restituito dalla chiamata di riconoscimento vocale deve essere inviato al tuo codice serverless per essere elaborato da LUIS, ottenendo così il numero di secondi per il timer. Questo numero di secondi può essere utilizzato per impostare un timer.

I timer possono essere impostati utilizzando la classe `threading.Timer` di Python. Questa classe accetta un tempo di ritardo e una funzione, ed esegue la funzione dopo il tempo di ritardo.

### Attività - invia il testo alla funzione serverless

1. Apri il progetto `smart-timer` in VS Code e assicurati che l'ambiente virtuale sia caricato nel terminale se stai utilizzando un dispositivo IoT virtuale.

1. Sopra la funzione `process_text`, dichiara una funzione chiamata `get_timer_time` per chiamare l'endpoint REST che hai creato:

    ```python
    def get_timer_time(text):
    ```

1. Aggiungi il seguente codice a questa funzione per definire l'URL da chiamare:

    ```python
    url = '<URL>'
    ```

    Sostituisci `<URL>` con l'URL del tuo endpoint REST che hai costruito nella lezione precedente, sia sul tuo computer che nel cloud.

1. Aggiungi il seguente codice per impostare il testo come una proprietà passata come JSON alla chiamata:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Sotto questo, recupera i `seconds` dal payload della risposta, restituendo 0 se la chiamata non è riuscita:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Le chiamate HTTP riuscite restituiscono un codice di stato nella gamma 200, e il tuo codice serverless restituisce 200 se il testo è stato elaborato e riconosciuto come intento di impostazione del timer.

### Attività - imposta un timer su un thread in background

1. Aggiungi la seguente istruzione di importazione all'inizio del file per importare la libreria Python threading:

    ```python
    import threading
    ```

1. Sopra la funzione `process_text`, aggiungi una funzione per pronunciare una risposta. Per ora, questa scriverà semplicemente sulla console, ma più avanti in questa lezione pronuncerà il testo.

    ```python
    def say(text):
        print(text)
    ```

1. Sotto questa, aggiungi una funzione che verrà chiamata da un timer per annunciare che il timer è terminato:

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    Questa funzione prende il numero di minuti e secondi del timer e costruisce una frase per dire che il timer è terminato. Controlla il numero di minuti e secondi e include solo ciascuna unità di tempo se ha un valore. Ad esempio, se il numero di minuti è 0, vengono inclusi solo i secondi nel messaggio. Questa frase viene quindi inviata alla funzione `say`.

1. Sotto questa, aggiungi la seguente funzione `create_timer` per creare un timer:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Questa funzione prende il numero totale di secondi per il timer che verrà inviato nel comando e lo converte in minuti e secondi. Quindi crea e avvia un oggetto timer utilizzando il numero totale di secondi, passando la funzione `announce_timer` e una lista contenente i minuti e i secondi. Quando il timer scade, chiamerà la funzione `announce_timer` e passerà il contenuto di questa lista come parametri: quindi il primo elemento della lista viene passato come parametro `minutes` e il secondo elemento come parametro `seconds`.

1. Alla fine della funzione `create_timer`, aggiungi del codice per costruire un messaggio da pronunciare all'utente per annunciare che il timer sta iniziando:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Anche in questo caso, include solo l'unità di tempo che ha un valore. Questa frase viene quindi inviata alla funzione `say`.

1. Aggiungi il seguente codice alla fine della funzione `process_text` per ottenere il tempo per il timer dal testo, quindi crea il timer:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Il timer viene creato solo se il numero di secondi è maggiore di 0.

1. Esegui l'app e assicurati che l'applicazione della funzione sia in esecuzione. Imposta alcuni timer e l'output mostrerà che il timer è stato impostato e poi mostrerà quando scade:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Puoi trovare questo codice nella cartella [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) o [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Il tuo programma timer è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.