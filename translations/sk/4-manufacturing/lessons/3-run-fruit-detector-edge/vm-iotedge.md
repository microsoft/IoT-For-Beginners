<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-28T08:35:27+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "sk"
}
-->
# Vytvorenie virtuálneho počítača s IoT Edge

V Azure môžete vytvoriť virtuálny počítač - počítač v cloude, ktorý môžete nakonfigurovať podľa svojich potrieb a spustiť na ňom vlastný softvér.

> 💁 Viac o virtuálnych počítačoch si môžete prečítať na [stránke o virtuálnych počítačoch na Wikipédii](https://wikipedia.org/wiki/Virtual_machine).

## Úloha - Nastavenie virtuálneho počítača s IoT Edge

1. Spustite nasledujúci príkaz na vytvorenie virtuálneho počítača, ktorý už má predinštalovaný Azure IoT Edge:

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

    Nahraďte `<vm_name>` názvom pre tento virtuálny počítač. Tento názov musí byť globálne jedinečný, takže použite niečo ako `fruit-quality-detector-vm-` s vaším menom alebo inou hodnotou na konci.

    Nahraďte `<username>` a `<password>` používateľským menom a heslom, ktoré použijete na prihlásenie do virtuálneho počítača. Tieto údaje musia byť relatívne bezpečné, takže nemôžete použiť admin/password.

    Nahraďte `<connection_string>` reťazcom pripojenia vášho zariadenia IoT Edge `fruit-quality-detector-edge`.

    Tento príkaz vytvorí virtuálny počítač nakonfigurovaný ako `DS1 v2`. Tieto kategórie označujú výkon počítača, a teda aj jeho cenu. Tento virtuálny počítač má 1 CPU a 3,5 GB RAM.

    > 💰 Aktuálne ceny týchto virtuálnych počítačov si môžete pozrieť na [príručke cien virtuálnych počítačov Azure](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn).

    Po vytvorení virtuálneho počítača sa runtime IoT Edge automaticky nainštaluje a nakonfiguruje na pripojenie k vášmu IoT Hub ako zariadenie `fruit-quality-detector-edge`.

1. Na volanie klasifikátora obrázkov z virtuálneho počítača budete potrebovať buď IP adresu, alebo DNS názov. Spustite nasledujúci príkaz na získanie týchto údajov:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Skopírujte hodnotu z poľa `PublicIps` alebo `Fqdns`.

1. Virtuálne počítače stoja peniaze. V čase písania tohto textu stojí DS1 VM približne $0.06 za hodinu. Aby ste minimalizovali náklady, mali by ste virtuálny počítač vypnúť, keď ho nepoužívate, a odstrániť ho, keď dokončíte tento projekt.

    Virtuálny počítač môžete nakonfigurovať tak, aby sa automaticky vypol v určitom čase každý deň. To znamená, že ak zabudnete počítač vypnúť, nebudete účtovaní za čas po automatickom vypnutí. Použite nasledujúci príkaz na nastavenie:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Nahraďte `<vm_name>` názvom vášho virtuálneho počítača.

    Nahraďte `<shutdown_time_utc>` časom UTC, kedy chcete, aby sa virtuálny počítač vypol, pomocou 4 číslic vo formáte HHMM. Napríklad, ak chcete vypnúť o polnoci UTC, nastavte hodnotu na `0000`. Pre 19:30 na západnom pobreží USA použite hodnotu 0230 (19:30 na západnom pobreží USA je 2:30 UTC).

1. Váš klasifikátor obrázkov bude bežať na tomto edge zariadení, počúvajúc na porte 80 (štandardný HTTP port). Virtuálne počítače majú predvolene blokované prichádzajúce porty, takže budete musieť povoliť port 80. Porty sa povolujú na skupinách zabezpečenia siete, takže najprv potrebujete vedieť názov skupiny zabezpečenia siete pre váš virtuálny počítač, ktorý môžete zistiť pomocou nasledujúceho príkazu:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Skopírujte hodnotu z poľa `Name`.

1. Spustite nasledujúci príkaz na pridanie pravidla na otvorenie portu 80 v skupine zabezpečenia siete:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Nahraďte `<nsg name>` názvom skupiny zabezpečenia siete z predchádzajúceho kroku.

### Úloha - správa vášho virtuálneho počítača na zníženie nákladov

1. Keď svoj virtuálny počítač nepoužívate, mali by ste ho vypnúť. Na vypnutie virtuálneho počítača použite nasledujúci príkaz:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Nahraďte `<vm_name>` názvom vášho virtuálneho počítača.

    > 💁 Existuje príkaz `az vm stop`, ktorý zastaví virtuálny počítač, ale ponechá počítač pridelený vám, takže stále platíte, akoby bol stále spustený.

1. Na opätovné spustenie virtuálneho počítača použite nasledujúci príkaz:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Nahraďte `<vm_name>` názvom vášho virtuálneho počítača.

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre dôležité informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.