<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T20:50:50+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "cs"
}
-->
# Vytvoření virtuálního počítače s IoT Edge

V Azure můžete vytvořit virtuální počítač – počítač v cloudu, který můžete nakonfigurovat podle svých potřeb a spustit na něm vlastní software.

> 💁 Více o virtuálních počítačích si můžete přečíst na [stránce o virtuálních počítačích na Wikipedii](https://wikipedia.org/wiki/Virtual_machine).

## Úkol - Nastavení virtuálního počítače s IoT Edge

1. Spusťte následující příkaz pro vytvoření virtuálního počítače, který má již předinstalovaný Azure IoT Edge:

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

    Nahraďte `<vm_name>` názvem pro tento virtuální počítač. Tento název musí být globálně unikátní, takže použijte něco jako `fruit-quality-detector-vm-` s vaším jménem nebo jinou hodnotou na konci.

    Nahraďte `<username>` a `<password>` uživatelským jménem a heslem, které použijete pro přihlášení do virtuálního počítače. Tyto údaje musí být relativně bezpečné, takže nemůžete použít například admin/password.

    Nahraďte `<connection_string>` připojovacím řetězcem vašeho zařízení IoT Edge `fruit-quality-detector-edge`.

    Tento příkaz vytvoří virtuální počítač nakonfigurovaný jako `DS1 v2`. Tyto kategorie označují výkon počítače, a tím pádem i jeho cenu. Tento virtuální počítač má 1 CPU a 3,5 GB RAM.

    > 💰 Aktuální ceny těchto virtuálních počítačů si můžete prohlédnout na [průvodci cenami virtuálních počítačů Azure](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn).

    Jakmile bude virtuální počítač vytvořen, IoT Edge runtime se automaticky nainstaluje a nakonfiguruje pro připojení k vašemu IoT Hub jako zařízení `fruit-quality-detector-edge`.

1. Budete potřebovat buď IP adresu, nebo DNS název virtuálního počítače, abyste mohli z něj volat klasifikátor obrázků. Spusťte následující příkaz pro získání těchto informací:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Zkopírujte buď hodnotu pole `PublicIps`, nebo pole `Fqdns`.

1. Virtuální počítače stojí peníze. V době psaní tohoto textu stojí DS1 VM přibližně $0.06 za hodinu. Abyste udrželi náklady na nízké úrovni, měli byste virtuální počítač vypnout, když ho nepoužíváte, a smazat ho, jakmile dokončíte tento projekt.

    Můžete nakonfigurovat svůj virtuální počítač tak, aby se automaticky vypnul v určitou dobu každý den. To znamená, že pokud zapomenete počítač vypnout, nebudete účtováni za více než čas do automatického vypnutí. Použijte následující příkaz pro nastavení:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Nahraďte `<vm_name>` názvem vašeho virtuálního počítače.

    Nahraďte `<shutdown_time_utc>` časem UTC, kdy chcete, aby se virtuální počítač vypnul, pomocí 4 číslic ve formátu HHMM. Například pokud chcete vypnutí o půlnoci UTC, nastavte hodnotu na `0000`. Pro 19:30 na západním pobřeží USA použijte `0230` (19:30 na západním pobřeží USA je 2:30 UTC).

1. Váš klasifikátor obrázků bude běžet na tomto edge zařízení, naslouchající na portu 80 (standardní HTTP port). Ve výchozím nastavení mají virtuální počítače blokované příchozí porty, takže budete muset povolit port 80. Porty se povolují na skupinách zabezpečení sítě, takže nejprve potřebujete znát název skupiny zabezpečení sítě pro váš virtuální počítač, který zjistíte pomocí následujícího příkazu:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Zkopírujte hodnotu pole `Name`.

1. Spusťte následující příkaz pro přidání pravidla, které otevře port 80 ve skupině zabezpečení sítě:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Nahraďte `<nsg name>` názvem skupiny zabezpečení sítě z předchozího kroku.

### Úkol - správa virtuálního počítače pro snížení nákladů

1. Když svůj virtuální počítač nepoužíváte, měli byste ho vypnout. Pro vypnutí virtuálního počítače použijte následující příkaz:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Nahraďte `<vm_name>` názvem vašeho virtuálního počítače.

    > 💁 Existuje příkaz `az vm stop`, který zastaví virtuální počítač, ale ponechá počítač přidělený vám, takže stále platíte, jako by byl stále spuštěný.

1. Pro opětovné spuštění virtuálního počítače použijte následující příkaz:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Nahraďte `<vm_name>` názvem vašeho virtuálního počítače.

---

**Upozornění**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za závazný zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za jakékoli nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.