<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-25T16:30:03+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "it"
}
-->
# Rispondere ai risultati della classificazione

## Istruzioni

Il tuo dispositivo ha classificato le immagini e ha i valori delle previsioni. Può utilizzare queste informazioni per fare qualcosa: potrebbe inviarle a IoT Hub per l'elaborazione da parte di altri sistemi, oppure potrebbe controllare un attuatore, come un LED, per accendersi quando il frutto non è maturo.

Aggiungi codice al tuo dispositivo per rispondere in un modo a tua scelta: inviare dati a un IoT Hub, controllare un attuatore, o combinare le due cose e inviare dati a un IoT Hub con del codice serverless che determina se il frutto è maturo o meno e invia un comando per controllare un attuatore.

## Criteri di valutazione

| Criteri | Esemplare | Adeguato | Da migliorare |
| -------- | --------- | -------- | ------------- |
| Rispondere alle previsioni | È stato in grado di implementare una risposta alle previsioni che funziona in modo coerente con previsioni dello stesso valore. | È stato in grado di implementare una risposta che non dipende dalle previsioni, come semplicemente inviare dati grezzi a un IoT Hub. | Non è stato in grado di programmare il dispositivo per rispondere alle previsioni. |

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche potrebbero contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un esperto umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.