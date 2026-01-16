<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-25T16:46:05+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "it"
}
-->
# Visualizza i dati GDD utilizzando un Jupyter Notebook

## Istruzioni

In questa lezione hai raccolto dati GDD utilizzando un sensore IoT. Per ottenere buoni dati GDD, è necessario raccogliere dati per più giorni. Per aiutarti a visualizzare i dati sulla temperatura e calcolare i GDD, puoi utilizzare strumenti come [Jupyter Notebooks](https://jupyter.org) per analizzare i dati.

Inizia raccogliendo dati per alcuni giorni. Dovrai assicurarti che il codice del tuo server sia in esecuzione per tutto il tempo in cui il tuo dispositivo IoT è attivo, regolando le impostazioni di gestione dell'alimentazione o utilizzando qualcosa come [questo script Python per mantenere attivo il sistema](https://github.com/jaqsparow/keep-system-active).

Una volta che hai i dati sulla temperatura, puoi utilizzare il Jupyter Notebook in questo repository per visualizzarli e calcolare i GDD. I Jupyter Notebook combinano codice e istruzioni in blocchi chiamati *celle*, spesso con codice in Python. Puoi leggere le istruzioni, quindi eseguire ogni blocco di codice, uno alla volta. Puoi anche modificare il codice. In questo notebook, ad esempio, puoi modificare la temperatura base utilizzata per calcolare i GDD per la tua pianta.

1. Crea una cartella chiamata `gdd-calculation`

1. Scarica il file [gdd.ipynb](../../../../../2-farm/lessons/1-predict-plant-growth/code-notebook/gdd.ipynb) e copialo nella cartella `gdd-calculation`.

1. Copia il file `temperature.csv` creato dal server MQTT.

1. Crea un nuovo ambiente virtuale Python nella cartella `gdd-calculation`.

1. Installa alcuni pacchetti pip per i Jupyter Notebook, insieme alle librerie necessarie per gestire e rappresentare graficamente i dati:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Esegui il notebook in Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter si avvierà e aprirà il notebook nel tuo browser. Segui le istruzioni nel notebook per visualizzare le temperature misurate e calcolare i gradi giorno di crescita.

    ![Il jupyter notebook](../../../../../translated_images/it/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Rubrica

| Criteri | Esemplare | Adeguato | Da Migliorare |
| -------- | --------- | -------- | ------------- |
| Raccolta dati | Raccogli almeno 2 giorni completi di dati | Raccogli almeno 1 giorno completo di dati | Raccogli alcuni dati |
| Calcolo GDD | Esegui con successo il notebook e calcola i GDD | Esegui con successo il notebook | Non riesci a eseguire il notebook |

**Disclaimer (Avviso di esclusione di responsabilità)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche potrebbero contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si consiglia una traduzione professionale eseguita da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.