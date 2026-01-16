<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "506d21b544d5de47406c89ad496a21cd",
  "translation_date": "2025-08-25T17:01:59+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/assignment.md",
  "language_code": "it"
}
-->
# Calibra il tuo sensore

## Istruzioni

In questa lezione hai raccolto letture del sensore di umidità del suolo, misurate come valori da 0 a 1023. Per convertirle in letture effettive di umidità del suolo, devi calibrare il tuo sensore. Puoi farlo prendendo letture da campioni di terreno e calcolando il contenuto di umidità gravimetrica del suolo da questi campioni.

Dovrai ripetere questi passaggi più volte per ottenere le letture necessarie, con diversi livelli di umidità del suolo ogni volta.

1. Prendi una lettura di umidità del suolo utilizzando il sensore di umidità del suolo. Annota questa lettura.

1. Prendi un campione di terreno e pesalo. Annota questo peso.

1. Asciuga il terreno - un forno caldo a 110°C (230°F) per alcune ore è il metodo migliore, puoi farlo alla luce del sole o posizionarlo in un luogo caldo e asciutto fino a quando il terreno è completamente asciutto. Dovrebbe essere polveroso e sciolto.

    > 💁 In un laboratorio, per ottenere risultati più accurati, dovresti asciugare il terreno in un forno per 48-72 ore. Se nella tua scuola ci sono forni per essiccazione, verifica se puoi usarli per un periodo più lungo. Più lungo è il tempo di essiccazione, più asciutto sarà il campione e più accurati saranno i risultati.

1. Pesa di nuovo il terreno.

    > 🔥 Se lo hai asciugato in un forno, assicurati che si sia raffreddato prima!

L'umidità gravimetrica del suolo si calcola come:

![% di umidità del suolo è il peso del terreno bagnato meno il peso del terreno asciutto, diviso per il peso del terreno asciutto, moltiplicato per 100](../../../../../translated_images/it/gsm-calculation.6da38c6201eec14e7573bb2647aa18892883193553d23c9d77e5dc681522dfb2.png)

* W  
- il peso del terreno bagnato  
* W  
- il peso del terreno asciutto  

Ad esempio, supponiamo di avere un campione di terreno che pesa 212g bagnato e 197g asciutto.

![Calcolo compilato](../../../../../translated_images/it/gsm-calculation-example.99f9803b4f29e97668e7c15412136c0c399ab12dbba0b89596fdae9d8aedb6fb.png)

* W = 212g  
* W = 197g  
* 212 - 197 = 15  
* 15 / 197 = 0,076  
* 0,076 * 100 = 7,6%

In questo esempio, il terreno ha un'umidità gravimetrica del suolo del 7,6%.

Una volta ottenute le letture di almeno 3 campioni, traccia un grafico della % di umidità del suolo rispetto alla lettura del sensore di umidità del suolo e aggiungi una linea che meglio si adatta ai punti. Puoi quindi utilizzare questa linea per calcolare il contenuto di umidità gravimetrica del suolo per una determinata lettura del sensore leggendo il valore dalla linea.

## Rubrica

| Criteri | Esemplare | Adeguato | Necessita miglioramenti |
| -------- | --------- | -------- | ----------------------- |
| Raccogli dati di calibrazione | Raccogli almeno 3 campioni di calibrazione | Raccogli almeno 2 campioni di calibrazione | Raccogli almeno 1 campione di calibrazione |
| Effettua una lettura calibrata | Traccia con successo il grafico di calibrazione e effettua una lettura dal sensore, convertendola in contenuto di umidità gravimetrica del suolo | Traccia con successo il grafico di calibrazione | Non riesce a tracciare il grafico |

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.