<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-25T16:41:02+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "it"
}
-->
# Costruire un rilevatore di qualità della frutta

## Istruzioni

Costruisci il rilevatore di qualità della frutta!

Utilizza tutto ciò che hai imparato finora per creare il prototipo del rilevatore di qualità della frutta. Attiva la classificazione delle immagini basandoti sulla prossimità utilizzando un modello di intelligenza artificiale che opera sul dispositivo edge, archivia i risultati della classificazione in uno storage e controlla un LED in base al grado di maturazione della frutta.

Dovresti essere in grado di assemblare tutto questo utilizzando il codice che hai scritto in precedenza in tutte le lezioni.

## Criteri di valutazione

| Criteri | Esemplare | Adeguato | Da migliorare |
| -------- | --------- | -------- | ----------------- |
| Configurare tutti i servizi | È stato in grado di configurare un IoT Hub, un'applicazione Azure Functions e uno storage Azure | È stato in grado di configurare l'IoT Hub, ma non l'app Azure Functions o lo storage Azure | Non è stato in grado di configurare alcun servizio IoT |
| Monitorare la prossimità e inviare i dati a IoT Hub se un oggetto è più vicino di una distanza predefinita e attivare la fotocamera tramite un comando | È stato in grado di misurare la distanza e inviare un messaggio a IoT Hub quando un oggetto era abbastanza vicino, e inviare un comando per attivare la fotocamera | È stato in grado di misurare la prossimità e inviare i dati a IoT Hub, ma non è riuscito a inviare un comando alla fotocamera | Non è stato in grado di misurare la distanza e inviare un messaggio a IoT Hub, né di attivare un comando |
| Catturare un'immagine, classificarla e inviare i risultati a IoT Hub | È stato in grado di catturare un'immagine, classificarla utilizzando un dispositivo edge e inviare i risultati a IoT Hub | È stato in grado di classificare l'immagine ma non utilizzando un dispositivo edge, oppure non è riuscito a inviare i risultati a IoT Hub | Non è stato in grado di classificare un'immagine |
| Accendere o spegnere il LED in base ai risultati della classificazione utilizzando un comando inviato a un dispositivo | È stato in grado di accendere un LED tramite un comando se il frutto era acerbo | È stato in grado di inviare il comando al dispositivo ma non di controllare il LED | Non è stato in grado di inviare un comando per controllare il LED |

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.