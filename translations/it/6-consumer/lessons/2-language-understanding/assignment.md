<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-25T17:44:06+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "it"
}
-->
# Annulla il timer

## Istruzioni

Finora in questa lezione hai addestrato un modello per comprendere come impostare un timer. Un'altra funzione utile è annullare un timer - magari il pane è pronto e può essere tolto dal forno prima che il timer scada.

Aggiungi un nuovo intento alla tua app LUIS per annullare il timer. Non avrà bisogno di entità, ma richiederà alcune frasi di esempio. Gestisci questo nel tuo codice serverless se è l'intento principale, registrando che l'intento è stato riconosciuto e restituendo una risposta appropriata.

## Criteri di valutazione

| Criteri | Esemplare | Adeguato | Da migliorare |
| -------- | --------- | -------- | ----------------- |
| Aggiungere l'intento di annullare il timer all'app LUIS | È stato in grado di aggiungere l'intento e addestrare il modello | È stato in grado di aggiungere l'intento ma non di addestrare il modello | Non è stato in grado di aggiungere l'intento e addestrare il modello |
| Gestire l'intento nell'app serverless | È stato in grado di rilevare l'intento come intento principale e registrarlo | È stato in grado di rilevare l'intento come intento principale | Non è stato in grado di rilevare l'intento come intento principale |

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.