<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-25T18:02:18+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "it"
}
-->
# Invia notifiche utilizzando Twilio

## Istruzioni

Nel tuo codice finora hai solo registrato la distanza dalla geofence. In questo esercizio dovrai aggiungere una notifica, che sia un messaggio di testo o un'email, quando le coordinate GPS si trovano all'interno della geofence.

Azure Functions offre molte opzioni per i binding, inclusi servizi di terze parti come Twilio, una piattaforma di comunicazione.

* Registrati per un account gratuito su [Twilio.com](https://www.twilio.com)
* Leggi la documentazione sui binding di Azure Functions per gli SMS di Twilio nella [pagina della documentazione Microsoft sui binding Twilio per Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Leggi la documentazione sui binding di Azure Functions per Twilio SendGrid per inviare email nella [pagina della documentazione Microsoft sui binding SendGrid per Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Aggiungi il binding alla tua app Functions per ricevere notifiche sulle coordinate GPS sia all'interno che all'esterno della geofence - ma non entrambe.

## Criteri di valutazione

| Criteri | Esemplare | Adeguato | Da migliorare |
| -------- | --------- | -------- | ------------- |
| Configurare i binding delle funzioni e ricevere un'email o un SMS | È stato in grado di configurare i binding delle funzioni e ricevere un'email o un SMS quando si trovava all'interno o all'esterno della geofence, ma non entrambe | È stato in grado di configurare i binding ma non è riuscito a inviare l'email o l'SMS, oppure è riuscito a inviare solo quando le coordinate erano sia all'interno che all'esterno | Non è stato in grado di configurare i binding e inviare un'email o un SMS |

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.