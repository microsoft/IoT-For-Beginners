<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-25T16:37:50+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "it"
}
-->
# Creare una macchina virtuale con IoT Edge

In Azure, puoi creare una macchina virtuale - un computer nel cloud che puoi configurare come desideri e su cui puoi eseguire il tuo software.

> 💁 Puoi leggere di più sulle macchine virtuali nella [pagina Wikipedia sulle macchine virtuali](https://wikipedia.org/wiki/Virtual_machine).

## Attività - Configurare una macchina virtuale con IoT Edge

1. Esegui il seguente comando per creare una VM con Azure IoT Edge già preinstallato:

    ```sh
    az deployment group create \
                --resource-group fruit-quality-detector \
                --template-uri https://raw.githubusercontent.com/Azure/iotedge-vm-deploy/1.2.0/edgeDeploy.json \
                --parameters dnsLabelPrefix=<vm_name> \
                --parameters adminUsername=<username> \
                --parameters deviceConnectionString="<connection_string>" \
                --parameters authenticationType=password \
                --parameters adminPasswordOrKey="<password>"
    ```

    Sostituisci `<vm_name>` con un nome per questa macchina virtuale. Deve essere un nome univoco a livello globale, quindi usa qualcosa come `fruit-quality-detector-vm-` seguito dal tuo nome o un altro valore.

    Sostituisci `<username>` e `<password>` con un nome utente e una password da utilizzare per accedere alla VM. Devono essere relativamente sicuri, quindi non puoi usare admin/password.

    Sostituisci `<connection_string>` con la stringa di connessione del tuo dispositivo IoT Edge `fruit-quality-detector-edge`.

    Questo comando creerà una VM configurata come macchina virtuale `DS1 v2`. Queste categorie indicano la potenza della macchina e, di conseguenza, il costo. Questa VM ha 1 CPU e 3.5GB di RAM.

    > 💰 Puoi consultare i prezzi attuali di queste VM nella [guida ai prezzi delle macchine virtuali Azure](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Una volta creata la VM, il runtime IoT Edge verrà installato automaticamente e configurato per connettersi al tuo IoT Hub come dispositivo `fruit-quality-detector-edge`.

1. Avrai bisogno dell'indirizzo IP o del nome DNS della VM per chiamare il classificatore di immagini da essa. Esegui il seguente comando per ottenerlo:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Copia il valore del campo `PublicIps` o del campo `Fqdns`.

1. Le VM hanno un costo. Al momento della scrittura, una VM DS1 costa circa $0.06 all'ora. Per ridurre i costi, dovresti spegnere la VM quando non la stai utilizzando e eliminarla quando hai terminato il progetto.

    Puoi configurare la tua VM per spegnersi automaticamente a un determinato orario ogni giorno. Questo significa che, se dimentichi di spegnerla, non ti verrà addebitato più del tempo fino allo spegnimento automatico. Usa il seguente comando per impostarlo:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Sostituisci `<vm_name>` con il nome della tua macchina virtuale.

    Sostituisci `<shutdown_time_utc>` con l'orario UTC in cui desideri che la VM si spenga, utilizzando 4 cifre nel formato HHMM. Ad esempio, se vuoi spegnere a mezzanotte UTC, imposta `0000`. Per le 19:30 sulla costa ovest degli USA, usa `0230` (le 19:30 sulla costa ovest degli USA corrispondono alle 2:30 UTC).

1. Il tuo classificatore di immagini sarà in esecuzione su questo dispositivo edge, ascoltando sulla porta 80 (la porta HTTP standard). Per impostazione predefinita, le macchine virtuali hanno le porte in entrata bloccate, quindi dovrai abilitare la porta 80. Le porte vengono abilitate sui gruppi di sicurezza di rete, quindi prima devi conoscere il nome del gruppo di sicurezza di rete della tua VM, che puoi trovare con il seguente comando:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Copia il valore del campo `Name`.

1. Esegui il seguente comando per aggiungere una regola che apra la porta 80 al gruppo di sicurezza di rete:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Sostituisci `<nsg name>` con il nome del gruppo di sicurezza di rete ottenuto nel passaggio precedente.

### Attività - Gestire la tua VM per ridurre i costi

1. Quando non stai utilizzando la tua VM, dovresti spegnerla. Per spegnere la VM, usa il seguente comando:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Sostituisci `<vm_name>` con il nome della tua macchina virtuale.

    > 💁 Esiste un comando `az vm stop` che fermerà la VM, ma manterrà il computer allocato a te, quindi continuerai a pagare come se fosse ancora in esecuzione.

1. Per riavviare la VM, usa il seguente comando:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Sostituisci `<vm_name>` con il nome della tua macchina virtuale.

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche potrebbero contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.