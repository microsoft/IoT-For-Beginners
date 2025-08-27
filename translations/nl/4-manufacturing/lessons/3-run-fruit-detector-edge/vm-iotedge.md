<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T20:51:26+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "nl"
}
-->
# Een virtuele machine maken met IoT Edge

In Azure kun je een virtuele machine maken - een computer in de cloud die je naar wens kunt configureren en waarop je je eigen software kunt draaien.

> 💁 Je kunt meer lezen over virtuele machines op de [Wikipedia-pagina over virtuele machines](https://wikipedia.org/wiki/Virtual_machine).

## Taak - Een IoT Edge virtuele machine instellen

1. Voer de volgende opdracht uit om een VM te maken waarop Azure IoT Edge al vooraf is geïnstalleerd:

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

    Vervang `<vm_name>` door een naam voor deze virtuele machine. Deze naam moet wereldwijd uniek zijn, dus gebruik iets als `fruit-quality-detector-vm-` met je naam of een andere waarde aan het einde.

    Vervang `<username>` en `<password>` door een gebruikersnaam en wachtwoord om in te loggen op de VM. Deze moeten redelijk veilig zijn, dus je kunt geen admin/password gebruiken.

    Vervang `<connection_string>` door de verbindingsreeks van je `fruit-quality-detector-edge` IoT Edge-apparaat.

    Dit maakt een VM die is geconfigureerd als een `DS1 v2` virtuele machine. Deze categorieën geven aan hoe krachtig de machine is, en dus hoeveel deze kost. Deze VM heeft 1 CPU en 3,5 GB RAM.

    > 💰 Je kunt de huidige prijzen van deze VMs bekijken in de [Azure Virtual Machine prijsgids](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Zodra de VM is gemaakt, wordt de IoT Edge-runtime automatisch geïnstalleerd en geconfigureerd om verbinding te maken met je IoT Hub als je `fruit-quality-detector-edge` apparaat.

1. Je hebt het IP-adres of de DNS-naam van de VM nodig om de beeldclassificator vanaf daar aan te roepen. Voer de volgende opdracht uit om dit te verkrijgen:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Kopieer het veld `PublicIps` of het veld `Fqdns`.

1. VMs kosten geld. Op het moment van schrijven kost een DS1 VM ongeveer $0,06 per uur. Om de kosten laag te houden, moet je de VM uitschakelen wanneer je deze niet gebruikt en verwijderen wanneer je klaar bent met dit project.

    Je kunt je VM zo configureren dat deze automatisch wordt uitgeschakeld op een bepaald tijdstip elke dag. Dit betekent dat als je vergeet de VM uit te schakelen, je niet meer wordt gefactureerd dan de tijd tot de automatische uitschakeling. Gebruik de volgende opdracht om dit in te stellen:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Vervang `<vm_name>` door de naam van je virtuele machine.

    Vervang `<shutdown_time_utc>` door de UTC-tijd waarop je wilt dat de VM wordt uitgeschakeld, met 4 cijfers als HHMM. Bijvoorbeeld, als je wilt uitschakelen om middernacht UTC, stel je dit in op `0000`. Voor 19:30 uur aan de westkust van de VS gebruik je 0230 (19:30 uur aan de westkust van de VS is 2:30 uur UTC).

1. Je beeldclassificator draait op dit edge-apparaat en luistert op poort 80 (de standaard HTTP-poort). Standaard hebben virtuele machines geblokkeerde inkomende poorten, dus je moet poort 80 inschakelen. Poorten worden ingeschakeld op netwerkbeveiligingsgroepen, dus eerst moet je de naam van de netwerkbeveiligingsgroep voor je VM weten, die je kunt vinden met de volgende opdracht:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Kopieer de waarde van het veld `Name`.

1. Voer de volgende opdracht uit om een regel toe te voegen om poort 80 te openen in de netwerkbeveiligingsgroep:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Vervang `<nsg name>` door de naam van de netwerkbeveiligingsgroep uit de vorige stap.

### Taak - Beheer je VM om kosten te verlagen

1. Wanneer je je VM niet gebruikt, moet je deze uitschakelen. Gebruik de volgende opdracht om de VM uit te schakelen:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Vervang `<vm_name>` door de naam van je virtuele machine.

    > 💁 Er is een `az vm stop` opdracht die de VM stopt, maar deze houdt de computer aan jou toegewezen, dus je betaalt nog steeds alsof deze actief is.

1. Om de VM opnieuw te starten, gebruik je de volgende opdracht:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Vervang `<vm_name>` door de naam van je virtuele machine.

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.