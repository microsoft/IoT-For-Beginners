<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-25T17:38:49+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "it"
}
-->
# Costruire un traduttore universale

## Istruzioni

Un traduttore universale è un dispositivo che può tradurre tra più lingue, permettendo a persone che parlano lingue diverse di comunicare. Usa ciò che hai imparato nelle lezioni precedenti per costruire un traduttore universale utilizzando 2 dispositivi IoT.

> Se non hai 2 dispositivi, segui i passaggi delle lezioni precedenti per configurare un dispositivo IoT virtuale come uno dei dispositivi IoT.

Dovresti configurare un dispositivo per una lingua e l'altro per un'altra. Ogni dispositivo dovrebbe accettare il discorso, convertirlo in testo, inviarlo all'altro dispositivo tramite IoT Hub e un'app Functions, quindi tradurlo e riprodurre il discorso tradotto.

> 💁 Suggerimento: Quando invii il discorso da un dispositivo all'altro, invia anche la lingua in cui è stato pronunciato, rendendo più facile la traduzione. Potresti persino far registrare ogni dispositivo utilizzando IoT Hub e un'app Functions per primo, passando la lingua che supportano per essere memorizzata in Azure Storage. Potresti quindi utilizzare un'app Functions per effettuare le traduzioni, inviando il testo tradotto al dispositivo IoT.

## Valutazione

| Criteri | Esemplare | Adeguato | Da migliorare |
| ------- | --------- | -------- | ------------- |
| Creare un traduttore universale | È stato in grado di costruire un traduttore universale, convertendo il discorso rilevato da un dispositivo in un discorso riprodotto da un altro dispositivo in una lingua diversa | È stato in grado di far funzionare alcune componenti, come la cattura del discorso o la traduzione, ma non è riuscito a costruire la soluzione completa | Non è stato in grado di costruire alcuna parte di un traduttore universale funzionante |

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.