<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-25T16:57:40+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "it"
}
-->
# Aggiungere il controllo manuale del relè

## Istruzioni

Il codice serverless può essere attivato da molteplici eventi, inclusi richieste HTTP. Puoi utilizzare i trigger HTTP per aggiungere un controllo manuale al tuo relè, permettendo a qualcuno di accendere o spegnere il relè tramite una richiesta web.

Per questo compito, devi aggiungere due trigger HTTP alla tua Functions App per accendere e spegnere il relè, riutilizzando ciò che hai imparato in questa lezione per inviare comandi al dispositivo.

Alcuni suggerimenti:

* Puoi aggiungere un trigger HTTP alla tua Functions App esistente con il seguente comando:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Sostituisci `<trigger name>` con il nome del tuo trigger HTTP. Usa qualcosa come `relay_on` e `relay_off`.

* I trigger HTTP possono avere un controllo di accesso. Per impostazione predefinita, richiedono una chiave API specifica della funzione da passare con l'URL per essere eseguiti. Per questo compito, puoi rimuovere questa restrizione in modo che chiunque possa eseguire la funzione. Per farlo, aggiorna l'impostazione `authLevel` nel file `function.json` per i trigger HTTP con il seguente valore:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Puoi leggere di più su questo controllo di accesso nella [documentazione sulle chiavi di accesso delle funzioni](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* I trigger HTTP supportano di default richieste GET e POST. Questo significa che puoi chiamarli utilizzando il tuo browser web - i browser web effettuano richieste GET.

    Quando esegui la tua Functions App localmente, vedrai l'URL del trigger:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Incolla l'URL nel tuo browser e premi `Invio`, oppure `Ctrl+clic` (`Cmd+clic` su macOS) sul link nella finestra del terminale in VS Code per aprirlo nel browser predefinito. Questo eseguirà il trigger.

    > 💁 Nota che l'URL contiene `/api` - i trigger HTTP sono di default nel sottodominio `api`.

* Quando distribuisci la Functions App, l'URL del trigger HTTP sarà:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Dove `<functions app name>` è il nome della tua Functions App, e `<trigger name>` è il nome del tuo trigger.

## Rubrica

| Criteri | Esemplare | Adeguato | Da migliorare |
| -------- | --------- | -------- | ------------- |
| Creare trigger HTTP | Creati 2 trigger per accendere e spegnere il relè, con nomi appropriati | Creato un trigger con un nome appropriato | Non è stato possibile creare alcun trigger |
| Controllare il relè dai trigger HTTP | È stato possibile collegare entrambi i trigger a IoT Hub e controllare il relè correttamente | È stato possibile collegare un trigger a IoT Hub e controllare il relè correttamente | Non è stato possibile collegare i trigger a IoT Hub |

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa deve essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale eseguita da un traduttore umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.