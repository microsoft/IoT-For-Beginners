<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-25T16:26:12+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "it"
}
-->
# Produzione e lavorazione - utilizzare l'IoT per migliorare la lavorazione degli alimenti

Una volta che il cibo arriva a un hub centrale o a un impianto di lavorazione, non sempre viene semplicemente spedito ai supermercati. Molto spesso il cibo passa attraverso una serie di fasi di lavorazione, come la selezione per qualità. Questo processo era in passato manuale: iniziava nei campi, dove i raccoglitori sceglievano solo i frutti maturi, e poi in fabbrica i frutti venivano trasportati su un nastro trasportatore e gli operai rimuovevano manualmente quelli ammaccati o marci. Avendo raccolto e selezionato fragole personalmente come lavoro estivo durante la scuola, posso testimoniare che non è un lavoro divertente.

Configurazioni più moderne si affidano all'IoT per la selezione. Alcuni dei primi dispositivi, come i selezionatori di [Weco](https://wecotek.com), utilizzano sensori ottici per rilevare la qualità dei prodotti, scartando ad esempio i pomodori verdi. Questi dispositivi possono essere utilizzati direttamente sui macchinari di raccolta in azienda agricola o negli impianti di lavorazione.

Con i progressi nell'Intelligenza Artificiale (AI) e nel Machine Learning (ML), queste macchine possono diventare più avanzate, utilizzando modelli ML addestrati per distinguere tra frutti e oggetti estranei come pietre, terra o insetti. Questi modelli possono anche essere addestrati per rilevare la qualità dei frutti, non solo quelli ammaccati ma anche per una rilevazione precoce di malattie o altri problemi delle colture.

> 🎓 Il termine *modello ML* si riferisce al risultato dell'addestramento di un software di machine learning su un set di dati. Ad esempio, è possibile addestrare un modello ML per distinguere tra pomodori maturi e acerbi, e poi utilizzare il modello su nuove immagini per verificare se i pomodori sono maturi o meno.

In queste 4 lezioni imparerai come addestrare modelli AI basati su immagini per rilevare la qualità dei frutti, come utilizzarli da un dispositivo IoT e come eseguirli al limite - ovvero su un dispositivo IoT piuttosto che nel cloud.

> 💁 Queste lezioni utilizzeranno alcune risorse cloud. Se non completi tutte le lezioni di questo progetto, assicurati di [pulire il tuo progetto](../clean-up.md).

## Argomenti

1. [Addestrare un rilevatore di qualità dei frutti](./lessons/1-train-fruit-detector/README.md)
1. [Verificare la qualità dei frutti da un dispositivo IoT](./lessons/2-check-fruit-from-device/README.md)
1. [Eseguire il rilevatore di qualità dei frutti al limite](./lessons/3-run-fruit-detector-edge/README.md)
1. [Attivare il rilevamento della qualità dei frutti da un sensore](./lessons/4-trigger-fruit-detector/README.md)

## Crediti

Tutte le lezioni sono state scritte con ♥️ da [Jen Fox](https://github.com/jenfoxbot) e [Jim Bennett](https://GitHub.com/JimBobBennett)

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.