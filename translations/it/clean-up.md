<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-25T16:17:20+00:00",
  "source_file": "clean-up.md",
  "language_code": "it"
}
-->
# Pulisci il tuo progetto

Dopo aver completato ogni progetto, è buona norma eliminare le risorse cloud.

Nelle lezioni di ciascun progetto, potresti aver creato alcune delle seguenti risorse:

* Un Gruppo di Risorse
* Un IoT Hub
* Registrazioni di dispositivi IoT
* Un Account di Archiviazione
* Un'App Functions
* Un account Azure Maps
* Un progetto di visione personalizzata
* Un Registro di Contenitori Azure
* Una risorsa di servizi cognitivi

La maggior parte di queste risorse non avrà alcun costo: o sono completamente gratuite, oppure stai utilizzando un livello gratuito. Per i servizi che richiedono un livello a pagamento, li avresti utilizzati a un livello incluso nell'allocazione gratuita, o ti costeranno solo pochi centesimi.

Anche con costi relativamente bassi, vale la pena eliminare queste risorse quando hai finito. Ad esempio, puoi avere un solo IoT Hub che utilizza il livello gratuito, quindi se vuoi crearne un altro dovrai utilizzare un livello a pagamento.

Tutti i tuoi servizi sono stati creati all'interno di Gruppi di Risorse, e questo rende la gestione più semplice. Puoi eliminare il Gruppo di Risorse, e tutti i servizi in quel Gruppo di Risorse verranno eliminati insieme ad esso.

Per eliminare il Gruppo di Risorse, esegui il seguente comando nel tuo terminale o prompt dei comandi:

```sh
az group delete --name <resource-group-name>
```

Sostituisci `<resource-group-name>` con il nome del Gruppo di Risorse che ti interessa.

Apparirà una conferma:

```output
Are you sure you want to perform this operation? (y/n): 
```

Inserisci `y` per confermare ed eliminare il Gruppo di Risorse.

Ci vorrà un po' di tempo per eliminare tutti i servizi.

> 💁 Puoi leggere di più sull'eliminazione dei gruppi di risorse nella [documentazione di Microsoft Docs sulla gestione ed eliminazione dei gruppi di risorse di Azure Resource Manager](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione AI [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un esperto umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.