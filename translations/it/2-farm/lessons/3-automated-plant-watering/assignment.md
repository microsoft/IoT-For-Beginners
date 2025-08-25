<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-25T16:51:51+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "it"
}
-->
# Costruire un ciclo di irrigazione più efficiente

## Istruzioni

Questa lezione ha trattato come controllare un relè tramite i dati di un sensore, e quel relè potrebbe a sua volta controllare una pompa per un sistema di irrigazione. Per una determinata quantità di terreno, far funzionare una pompa per un periodo di tempo fisso dovrebbe sempre avere lo stesso impatto sull'umidità del suolo. Questo significa che puoi avere un'idea di quanti secondi di irrigazione corrispondono a una certa diminuzione nella lettura dell'umidità del suolo. Utilizzando questi dati, puoi costruire un sistema di irrigazione più controllato.

Per questo compito, calcolerai quanto tempo la pompa dovrebbe funzionare per ottenere un determinato aumento dell'umidità del suolo.

> ⚠️ Se stai utilizzando hardware IoT virtuale, puoi seguire questo processo, ma simulare i risultati aumentando manualmente la lettura dell'umidità del suolo di una quantità fissa per ogni secondo in cui il relè è attivo.

1. Inizia con il terreno asciutto. Misura l'umidità del suolo.

1. Aggiungi una quantità fissa di acqua, sia facendo funzionare la pompa per 1 secondo sia versando una quantità fissa.

    > La pompa dovrebbe sempre funzionare a una velocità costante, quindi ogni secondo che la pompa funziona dovrebbe fornire la stessa quantità di acqua.

1. Aspetta che il livello di umidità del suolo si stabilizzi e prendi una lettura.

1. Ripeti questo processo più volte e crea una tabella con i risultati. Un esempio di questa tabella è fornito qui sotto.

    | Tempo totale della pompa | Umidità del suolo | Diminuzione |
    | --- | --: | -: |
    | Asciutto | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Calcola un aumento medio dell'umidità del suolo per ogni secondo di acqua. Nell'esempio sopra, ogni secondo di acqua diminuisce la lettura di una media di 20,3.

1. Utilizza questi dati per migliorare l'efficienza del codice del tuo server, facendo funzionare la pompa per il tempo necessario per portare l'umidità del suolo al livello desiderato.

## Rubrica

| Criteri | Esemplare | Adeguato | Da migliorare |
| -------- | --------- | -------- | ------------- |
| Acquisizione dei dati sull'umidità del suolo | È in grado di acquisire più letture dopo aver aggiunto quantità fisse di acqua | È in grado di acquisire alcune letture con quantità fisse di acqua | È in grado di acquisire solo una o due letture, o non è in grado di utilizzare quantità fisse di acqua |
| Calibrazione del codice del server | È in grado di calcolare una diminuzione media nella lettura dell'umidità del suolo e aggiornare il codice del server per utilizzarla | È in grado di calcolare una diminuzione media, ma non può aggiornare il codice del server, o non è in grado di calcolare correttamente una media, ma utilizza questo valore per aggiornare correttamente il codice del server | Non è in grado di calcolare una media o aggiornare il codice del server |

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche potrebbero contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.