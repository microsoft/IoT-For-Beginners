<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T20:37:51+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "sv"
}
-->
# Skapa en virtuell maskin med IoT Edge

I Azure kan du skapa en virtuell maskin - en dator i molnet som du kan konfigurera precis som du vill och köra din egen mjukvara på.

> 💁 Du kan läsa mer om virtuella maskiner på [Wikipedia-sidan om virtuella maskiner](https://wikipedia.org/wiki/Virtual_machine).

## Uppgift - Ställ in en IoT Edge virtuell maskin

1. Kör följande kommando för att skapa en VM som redan har Azure IoT Edge förinstallerat:

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

    Ersätt `<vm_name>` med ett namn för denna virtuella maskin. Namnet måste vara globalt unikt, så använd något som `fruit-quality-detector-vm-` med ditt namn eller ett annat värde i slutet.

    Ersätt `<username>` och `<password>` med ett användarnamn och lösenord för att logga in på VM. Dessa måste vara relativt säkra, så du kan inte använda admin/password.

    Ersätt `<connection_string>` med anslutningssträngen för din `fruit-quality-detector-edge` IoT Edge-enhet.

    Detta kommer att skapa en VM konfigurerad som en `DS1 v2` virtuell maskin. Dessa kategorier anger hur kraftfull maskinen är, och därmed hur mycket den kostar. Denna VM har 1 CPU och 3,5 GB RAM.

    > 💰 Du kan se aktuella priser för dessa VMs på [Azure Virtual Machine prisguide](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    När VM har skapats kommer IoT Edge-runtime att installeras automatiskt och konfigureras för att ansluta till din IoT Hub som din `fruit-quality-detector-edge`-enhet.

1. Du kommer att behöva antingen IP-adressen eller DNS-namnet för VM för att kunna anropa bildklassificeraren från den. Kör följande kommando för att få detta:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Kopiera antingen värdet från fältet `PublicIps` eller fältet `Fqdns`.

1. VMs kostar pengar. Vid tidpunkten för skrivandet kostar en DS1 VM cirka $0,06 per timme. För att hålla kostnaderna nere bör du stänga av VM när du inte använder den och ta bort den när du är klar med projektet.

    Du kan konfigurera din VM att automatiskt stängas av vid en viss tidpunkt varje dag. Detta innebär att om du glömmer att stänga av den, kommer du inte att debiteras för mer än tiden fram till den automatiska avstängningen. Använd följande kommando för att ställa in detta:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Ersätt `<vm_name>` med namnet på din virtuella maskin.

    Ersätt `<shutdown_time_utc>` med UTC-tiden då du vill att VM ska stängas av, med 4 siffror som HHMM. Till exempel, om du vill stänga av vid midnatt UTC, ställer du in detta till `0000`. För 19:30 på USA:s västkust använder du 0230 (19:30 på USA:s västkust är 02:30 UTC).

1. Din bildklassificerare kommer att köras på denna edge-enhet och lyssna på port 80 (den standard HTTP-porten). Som standard har virtuella maskiner blockerade inkommande portar, så du måste aktivera port 80. Portar aktiveras på nätverkssäkerhetsgrupper, så först måste du veta namnet på nätverkssäkerhetsgruppen för din VM, vilket du kan hitta med följande kommando:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Kopiera värdet från fältet `Name`.

1. Kör följande kommando för att lägga till en regel som öppnar port 80 i nätverkssäkerhetsgruppen:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Ersätt `<nsg name>` med namnet på nätverkssäkerhetsgruppen från föregående steg.

### Uppgift - hantera din VM för att minska kostnader

1. När du inte använder din VM bör du stänga av den. För att stänga av VM, använd följande kommando:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Ersätt `<vm_name>` med namnet på din virtuella maskin.

    > 💁 Det finns ett kommando `az vm stop` som stoppar VM, men det håller datorn tilldelad till dig, så du betalar fortfarande som om den fortfarande kördes.

1. För att starta om VM, använd följande kommando:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Ersätt `<vm_name>` med namnet på din virtuella maskin.

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.