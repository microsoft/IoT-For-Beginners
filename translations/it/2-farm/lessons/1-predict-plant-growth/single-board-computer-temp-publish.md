<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-25T16:45:40+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "it"
}
-->
# Pubblicare la temperatura - Hardware IoT Virtuale e Raspberry Pi

In questa parte della lezione, pubblicherai i valori di temperatura rilevati dal Raspberry Pi o dal dispositivo IoT virtuale tramite MQTT, in modo che possano essere utilizzati successivamente per calcolare i GDD.

## Pubblicare la temperatura

Una volta letta la temperatura, può essere pubblicata tramite MQTT a un codice 'server' che leggerà i valori e li memorizzerà pronti per essere utilizzati nel calcolo dei GDD.

### Attività - pubblicare la temperatura

Programma il dispositivo per pubblicare i dati della temperatura.

1. Apri il progetto dell'app `temperature-sensor` se non è già aperto.

1. Ripeti i passaggi che hai eseguito nella lezione 4 per connetterti a MQTT e inviare telemetria. Utilizzerai lo stesso broker pubblico Mosquitto.

    I passaggi sono:

    - Aggiungi il pacchetto pip MQTT
    - Aggiungi il codice per connetterti al broker MQTT
    - Aggiungi il codice per pubblicare la telemetria

    > ⚠️ Consulta le [istruzioni per connettersi a MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) e le [istruzioni per inviare telemetria](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) dalla lezione 4, se necessario.

1. Assicurati che il `client_name` rifletta il nome di questo progetto:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Per la telemetria, invece di inviare un valore di luce, invia il valore della temperatura letto dal sensore DHT in una proprietà del documento JSON chiamata `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Non è necessario leggere il valore della temperatura molto spesso, poiché non cambierà molto in un breve periodo di tempo. Imposta quindi il `time.sleep` a 10 minuti:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 La funzione `sleep` prende il tempo in secondi, quindi per renderlo più leggibile il valore viene passato come risultato di un calcolo. 60 secondi in un minuto, quindi 10 x (60 secondi in un minuto) dà un ritardo di 10 minuti.

1. Esegui il codice nello stesso modo in cui hai eseguito il codice della parte precedente dell'assegnamento. Se stai utilizzando un dispositivo IoT virtuale, assicurati che l'app CounterFit sia in esecuzione e che i sensori di umidità e temperatura siano stati creati sui pin corretti.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Puoi trovare questo codice nella cartella [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) o nella cartella [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Hai pubblicato con successo la temperatura come telemetria dal tuo dispositivo.

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione AI [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un esperto umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.