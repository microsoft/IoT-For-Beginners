<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T20:38:07+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "da"
}
-->
# Opret en virtuel maskine med IoT Edge

I Azure kan du oprette en virtuel maskine - en computer i skyen, som du kan konfigurere, som du ønsker, og køre din egen software på.

> 💁 Du kan læse mere om virtuelle maskiner på [Wikipedia-siden om virtuelle maskiner](https://wikipedia.org/wiki/Virtual_machine).

## Opgave - Opsæt en IoT Edge virtuel maskine

1. Kør følgende kommando for at oprette en VM, der allerede har Azure IoT Edge forudinstalleret:

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

    Erstat `<vm_name>` med et navn til denne virtuelle maskine. Navnet skal være globalt unikt, så brug noget som `fruit-quality-detector-vm-` med dit navn eller en anden værdi tilføjet.

    Erstat `<username>` og `<password>` med et brugernavn og en adgangskode til at logge ind på VM'en. Disse skal være relativt sikre, så du kan ikke bruge admin/password.

    Erstat `<connection_string>` med forbindelsesstrengen for din `fruit-quality-detector-edge` IoT Edge-enhed.

    Dette vil oprette en VM konfigureret som en `DS1 v2` virtuel maskine. Disse kategorier angiver, hvor kraftfuld maskinen er, og dermed hvor meget den koster. Denne VM har 1 CPU og 3,5 GB RAM.

    > 💰 Du kan se de aktuelle priser for disse VMs på [Azure Virtual Machine prisguiden](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Når VM'en er oprettet, vil IoT Edge-runtime automatisk blive installeret og konfigureret til at forbinde til din IoT Hub som din `fruit-quality-detector-edge` enhed.

1. Du skal bruge enten IP-adressen eller DNS-navnet på VM'en for at kunne kalde billedklassifikatoren fra den. Kør følgende kommando for at få dette:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Tag en kopi af enten `PublicIps`-feltet eller `Fqdns`-feltet.

1. VMs koster penge. På tidspunktet for denne skrivning koster en DS1 VM cirka $0,06 per time. For at holde omkostningerne nede bør du lukke VM'en, når du ikke bruger den, og slette den, når du er færdig med dette projekt.

    Du kan konfigurere din VM til automatisk at lukke ned på et bestemt tidspunkt hver dag. Dette betyder, at hvis du glemmer at lukke den ned, vil du ikke blive faktureret for mere end tiden indtil den automatiske nedlukning. Brug følgende kommando for at indstille dette:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Erstat `<vm_name>` med navnet på din virtuelle maskine.

    Erstat `<shutdown_time_utc>` med UTC-tiden, hvor du ønsker, at VM'en skal lukke ned, ved hjælp af 4 cifre som HHMM. For eksempel, hvis du vil lukke ned ved midnat UTC, skal du sætte dette til `0000`. For kl. 19:30 på vestkysten af USA skal du bruge 0230 (19:30 på vestkysten af USA er 02:30 UTC).

1. Din billedklassifikator vil køre på denne edge-enhed og lytte på port 80 (den standard HTTP-port). Som standard har virtuelle maskiner blokerede indgående porte, så du skal aktivere port 80. Porte aktiveres på netværkssikkerhedsgrupper, så først skal du kende navnet på netværkssikkerhedsgruppen for din VM, som du kan finde med følgende kommando:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Kopiér værdien af `Name`-feltet.

1. Kør følgende kommando for at tilføje en regel, der åbner port 80 i netværkssikkerhedsgruppen:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Erstat `<nsg name>` med navnet på netværkssikkerhedsgruppen fra det foregående trin.

### Opgave - administrer din VM for at reducere omkostninger

1. Når du ikke bruger din VM, bør du lukke den ned. For at lukke VM'en ned skal du bruge følgende kommando:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Erstat `<vm_name>` med navnet på din virtuelle maskine.

    > 💁 Der findes en `az vm stop`-kommando, som vil stoppe VM'en, men den holder computeren allokeret til dig, så du betaler stadig, som om den stadig kører.

1. For at genstarte VM'en skal du bruge følgende kommando:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Erstat `<vm_name>` med navnet på din virtuelle maskine.

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.