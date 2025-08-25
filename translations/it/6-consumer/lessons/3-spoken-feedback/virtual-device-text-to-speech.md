<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-25T17:49:48+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "it"
}
-->
# Sintesi vocale - Dispositivo IoT virtuale

In questa parte della lezione, scriverai del codice per convertire il testo in voce utilizzando il servizio di sintesi vocale.

## Convertire testo in voce

L'SDK dei servizi vocali che hai utilizzato nella lezione precedente per convertire la voce in testo può essere usato per convertire il testo nuovamente in voce. Quando richiedi la sintesi vocale, devi fornire la voce da utilizzare, poiché la voce può essere generata utilizzando una varietà di voci diverse.

Ogni lingua supporta una gamma di voci differenti, e puoi ottenere l'elenco delle voci supportate per ogni lingua dall'SDK dei servizi vocali.

### Attività - convertire testo in voce

1. Apri il progetto `smart-timer` in VS Code e assicurati che l'ambiente virtuale sia caricato nel terminale.

1. Importa il `SpeechSynthesizer` dal pacchetto `azure.cognitiveservices.speech` aggiungendolo agli import esistenti:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Sopra la funzione `say`, crea una configurazione vocale da utilizzare con il sintetizzatore vocale:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Questo utilizza la stessa chiave API, posizione e lingua che sono stati usati dal riconoscitore.

1. Sotto questo, aggiungi il seguente codice per ottenere una voce e impostarla nella configurazione vocale:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Questo recupera un elenco di tutte le voci disponibili, quindi trova la prima voce che corrisponde alla lingua utilizzata.

    > 💁 Puoi ottenere l'elenco completo delle voci supportate dalla [documentazione sul supporto delle lingue e delle voci su Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Se desideri utilizzare una voce specifica, puoi rimuovere questa funzione e impostare manualmente la voce utilizzando il nome della voce dalla documentazione. Ad esempio:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Aggiorna il contenuto della funzione `say` per generare SSML per la risposta:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Sotto questo, interrompi il riconoscimento vocale, pronuncia l'SSML, quindi riavvia il riconoscimento:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Il riconoscimento viene interrotto mentre il testo viene pronunciato per evitare che l'annuncio dell'avvio del timer venga rilevato, inviato a LUIS e possibilmente interpretato come una richiesta per impostare un nuovo timer.

    > 💁 Puoi testarlo commentando le righe per interrompere e riavviare il riconoscimento. Imposta un timer e potresti scoprire che l'annuncio imposta un nuovo timer, causando un nuovo annuncio, che porta a un nuovo timer, e così via all'infinito!

1. Esegui l'app e assicurati che l'applicazione funzione sia anch'essa in esecuzione. Imposta alcuni timer e sentirai una risposta vocale che ti informa che il tuo timer è stato impostato, seguita da un'altra risposta vocale quando il timer è completato.

> 💁 Puoi trovare questo codice nella cartella [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Il tuo programma timer è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.