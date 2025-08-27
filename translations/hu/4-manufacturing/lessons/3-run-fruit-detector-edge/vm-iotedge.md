<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T20:50:34+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "hu"
}
-->
# Hozz létre egy IoT Edge virtuális gépet

Az Azure-ban létrehozhatsz egy virtuális gépet - egy felhőben futó számítógépet, amelyet tetszés szerint konfigurálhatsz, és saját szoftveredet futtathatod rajta.

> 💁 További információt a virtuális gépekről a [Wikipedia Virtuális gép oldalán](https://wikipedia.org/wiki/Virtual_machine) olvashatsz.

## Feladat - Állíts be egy IoT Edge virtuális gépet

1. Futtasd az alábbi parancsot egy előre telepített Azure IoT Edge VM létrehozásához:

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

    Cseréld ki a `<vm_name>` helyére a virtuális gép nevét. Ennek globálisan egyedinek kell lennie, ezért használj például olyasmit, mint `fruit-quality-detector-vm-`, a neveddel vagy más értékkel a végén.

    Cseréld ki a `<username>` és `<password>` helyére a VM-be való bejelentkezéshez használt felhasználónevet és jelszót. Ezeknek viszonylag biztonságosnak kell lenniük, ezért nem használhatsz olyasmit, mint admin/password.

    Cseréld ki a `<connection_string>` helyére a `fruit-quality-detector-edge` IoT Edge eszköz kapcsolatláncát.

    Ez egy `DS1 v2` típusú virtuális gépet hoz létre. Ezek a kategóriák jelzik, hogy mennyire erős a gép, és ennek megfelelően mennyibe kerül. Ez a VM 1 CPU-val és 3,5 GB RAM-mal rendelkezik.

    > 💰 Az aktuális árakat az [Azure Virtuális Gépek árképzési útmutatójában](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn) találod.

    Miután a VM létrejött, az IoT Edge futtatókörnyezet automatikusan telepítésre kerül, és konfigurálva lesz, hogy csatlakozzon az IoT Hub-hoz mint `fruit-quality-detector-edge` eszköz.

1. Szükséged lesz a VM IP-címére vagy DNS nevére, hogy képes legyél hívni az image classifier-t. Futtasd az alábbi parancsot ennek megszerzéséhez:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Másold ki a `PublicIps` vagy az `Fqdns` mező értékét.

1. A virtuális gépek pénzbe kerülnek. A jelenlegi információk szerint egy DS1 VM körülbelül 0,06 dollárba kerül óránként. A költségek csökkentése érdekében le kell állítanod a VM-et, amikor nem használod, és törölnöd kell, amikor befejezted a projektet.

    Beállíthatod, hogy a VM automatikusan leálljon minden nap egy adott időpontban. Ez azt jelenti, hogy ha elfelejted leállítani, akkor sem számláznak többet, mint az automatikus leállításig eltelt idő. Használd az alábbi parancsot ennek beállításához:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Cseréld ki a `<vm_name>` helyére a virtuális gép nevét.

    Cseréld ki a `<shutdown_time_utc>` helyére azt az UTC időpontot, amikor szeretnéd, hogy a VM leálljon, 4 számjegy formátumban (HHMM). Például, ha éjfélkor szeretnéd leállítani, állítsd be `0000`-ra. Ha az USA nyugati partján este 7:30-kor szeretnéd leállítani, akkor használd az `0230` értéket (az USA nyugati partján este 7:30 UTC idő szerint 2:30).

1. Az image classifier az edge eszközön fog futni, a 80-as porton (a szabványos HTTP port). Alapértelmezés szerint a virtuális gépek bejövő portjai blokkolva vannak, ezért engedélyezned kell a 80-as portot. A portokat a hálózati biztonsági csoportokon engedélyezheted, ezért először meg kell tudnod a VM hálózati biztonsági csoportjának nevét, amelyet az alábbi parancs segítségével találhatsz meg:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Másold ki a `Name` mező értékét.

1. Futtasd az alábbi parancsot, hogy szabályt adj hozzá a 80-as port megnyitásához a hálózati biztonsági csoportban:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Cseréld ki a `<nsg name>` helyére az előző lépésben kapott hálózati biztonsági csoport nevét.

### Feladat - Kezeld a VM-et a költségek csökkentése érdekében

1. Amikor nem használod a VM-et, le kell állítanod. A VM leállításához használd az alábbi parancsot:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Cseréld ki a `<vm_name>` helyére a virtuális gép nevét.

    > 💁 Létezik egy `az vm stop` parancs, amely leállítja a VM-et, de a számítógépet továbbra is hozzád rendeli, így ugyanannyit fizetsz, mintha még mindig futna.

1. A VM újraindításához használd az alábbi parancsot:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Cseréld ki a `<vm_name>` helyére a virtuális gép nevét.

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.