<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-25T18:13:19+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "it"
}
-->
# Indagare sui binding delle funzioni

## Istruzioni

I binding delle funzioni consentono al tuo codice di salvare blob nello storage blob restituendoli dalla funzione `main`. L'account di archiviazione di Azure, la raccolta e altri dettagli sono configurati nel file `function.json`.

Quando lavori con Azure o altre tecnologie Microsoft, la migliore fonte di informazioni è [la documentazione Microsoft su docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). In questo compito dovrai leggere la documentazione sui binding di Azure Functions per capire come configurare il binding di output.

Alcune pagine da consultare per iniziare sono:

* [Concetti sui trigger e binding di Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Panoramica dei binding per lo storage blob di Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Binding di output per lo storage blob di Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Griglia di valutazione

| Criteri | Esemplare | Adeguato | Da migliorare |
| -------- | --------- | -------- | ------------- |
| Configurare il binding di output per lo storage blob | È stato in grado di configurare il binding di output, restituire il blob e salvarlo correttamente nello storage blob | È stato in grado di configurare il binding di output o restituire il blob, ma non è riuscito a salvarlo correttamente nello storage blob | Non è stato in grado di configurare il binding di output |

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.