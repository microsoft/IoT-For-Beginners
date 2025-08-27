<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T20:38:21+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "no"
}
-->
# Opprett en virtuell maskin som kjører IoT Edge

I Azure kan du opprette en virtuell maskin - en datamaskin i skyen som du kan konfigurere akkurat slik du ønsker og kjøre din egen programvare på.

> 💁 Du kan lese mer om virtuelle maskiner på [Wikipedia-siden om virtuelle maskiner](https://wikipedia.org/wiki/Virtual_machine).

## Oppgave - Sett opp en IoT Edge virtuell maskin

1. Kjør følgende kommando for å opprette en VM som allerede har Azure IoT Edge forhåndsinstallert:

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

    Erstatt `<vm_name>` med et navn for denne virtuelle maskinen. Dette må være globalt unikt, så bruk noe som `fruit-quality-detector-vm-` med ditt navn eller en annen verdi på slutten.

    Erstatt `<username>` og `<password>` med et brukernavn og passord for å logge inn på VM-en. Disse må være relativt sikre, så du kan ikke bruke admin/password.

    Erstatt `<connection_string>` med tilkoblingsstrengen til din `fruit-quality-detector-edge` IoT Edge-enhet.

    Dette vil opprette en VM konfigurert som en `DS1 v2` virtuell maskin. Disse kategoriene indikerer hvor kraftig maskinen er, og dermed hvor mye den koster. Denne VM-en har 1 CPU og 3,5 GB RAM.

    > 💰 Du kan se de gjeldende prisene for disse VM-ene på [Azure Virtual Machine prisguide](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Når VM-en er opprettet, vil IoT Edge-runtime bli installert automatisk og konfigurert til å koble til din IoT Hub som din `fruit-quality-detector-edge`-enhet.

1. Du vil trenge enten IP-adressen eller DNS-navnet til VM-en for å kunne bruke bildeklassifiseringen fra den. Kjør følgende kommando for å hente dette:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Ta en kopi av enten `PublicIps`-feltet eller `Fqdns`-feltet.

1. Virtuelle maskiner koster penger. På tidspunktet for skrivingen koster en DS1 VM omtrent $0,06 per time. For å holde kostnadene nede bør du slå av VM-en når du ikke bruker den, og slette den når du er ferdig med prosjektet.

    Du kan konfigurere VM-en din til å slå seg av automatisk på et bestemt tidspunkt hver dag. Dette betyr at hvis du glemmer å slå den av, vil du ikke bli fakturert for mer enn tiden frem til den automatiske avstengningen. Bruk følgende kommando for å sette dette opp:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Erstatt `<vm_name>` med navnet på din virtuelle maskin.

    Erstatt `<shutdown_time_utc>` med UTC-tiden du vil at VM-en skal slå seg av, ved å bruke 4 sifre som HHMM. For eksempel, hvis du vil slå av ved midnatt UTC, setter du dette til `0000`. For kl. 19:30 på vestkysten av USA, bruker du 0230 (19:30 på vestkysten av USA er 02:30 UTC).

1. Din bildeklassifisering vil kjøre på denne edge-enheten, og lytte på port 80 (standard HTTP-port). Som standard har virtuelle maskiner blokkert innkommende porter, så du må aktivere port 80. Porter aktiveres på nettverkssikkerhetsgrupper, så først må du vite navnet på nettverkssikkerhetsgruppen for din VM, som du kan finne med følgende kommando:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Kopier verdien av `Name`-feltet.

1. Kjør følgende kommando for å legge til en regel som åpner port 80 i nettverkssikkerhetsgruppen:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Erstatt `<nsg name>` med navnet på nettverkssikkerhetsgruppen fra forrige steg.

### Oppgave - administrer din VM for å redusere kostnader

1. Når du ikke bruker din VM, bør du slå den av. For å slå av VM-en, bruk følgende kommando:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Erstatt `<vm_name>` med navnet på din virtuelle maskin.

    > 💁 Det finnes en `az vm stop`-kommando som vil stoppe VM-en, men den holder datamaskinen allokert til deg, så du betaler fortsatt som om den kjørte.

1. For å starte VM-en på nytt, bruk følgende kommando:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Erstatt `<vm_name>` med navnet på din virtuelle maskin.

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.