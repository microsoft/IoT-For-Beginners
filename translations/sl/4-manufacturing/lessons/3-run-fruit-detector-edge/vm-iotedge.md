<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-28T12:21:24+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "sl"
}
-->
# Ustvarite virtualni stroj z IoT Edge

V Azure lahko ustvarite virtualni stroj - računalnik v oblaku, ki ga lahko konfigurirate po svojih željah in na njem zaženete svojo programsko opremo.

> 💁 Več o virtualnih strojih si lahko preberete na [strani o virtualnih strojih na Wikipediji](https://wikipedia.org/wiki/Virtual_machine).

## Naloga - Nastavite IoT Edge virtualni stroj

1. Za ustvarjanje virtualnega stroja z že prednameščenim Azure IoT Edge zaženite naslednji ukaz:

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

    Zamenjajte `<vm_name>` z imenom za ta virtualni stroj. Ime mora biti globalno unikatno, zato uporabite nekaj, kot je `fruit-quality-detector-vm-` z vašim imenom ali drugo vrednostjo na koncu.

    Zamenjajte `<username>` in `<password>` z uporabniškim imenom in geslom za prijavo v virtualni stroj. Geslo mora biti dovolj varno, zato ne morete uporabiti admin/password.

    Zamenjajte `<connection_string>` z nizom za povezavo vaše IoT Edge naprave `fruit-quality-detector-edge`.

    Ta ukaz bo ustvaril virtualni stroj, konfiguriran kot `DS1 v2`. Te kategorije označujejo zmogljivost stroja in s tem tudi stroške. Ta virtualni stroj ima 1 CPU in 3,5 GB RAM-a.

    > 💰 Trenutne cene teh virtualnih strojev si lahko ogledate v [ceniku za Azure Virtual Machines](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Ko bo virtualni stroj ustvarjen, bo IoT Edge runtime samodejno nameščen in konfiguriran za povezavo z vašim IoT Hub kot naprava `fruit-quality-detector-edge`.

1. Za klicanje klasifikatorja slik iz virtualnega stroja boste potrebovali IP naslov ali DNS ime stroja. Za pridobitev teh podatkov zaženite naslednji ukaz:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Kopirajte vrednost iz polja `PublicIps` ali `Fqdns`.

1. Virtualni stroji stanejo denar. V času pisanja tega dokumenta DS1 VM stane približno 0,06 USD na uro. Da zmanjšate stroške, ugasnite virtualni stroj, ko ga ne uporabljate, in ga izbrišite, ko končate projekt.

    Virtualni stroj lahko nastavite tako, da se samodejno ugasne ob določenem času vsak dan. To pomeni, da če pozabite ugasniti stroj, ne boste zaračunani za več kot čas do samodejnega izklopa. Za nastavitev uporabite naslednji ukaz:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Zamenjajte `<vm_name>` z imenom vašega virtualnega stroja.

    Zamenjajte `<shutdown_time_utc>` z UTC časom, ko želite, da se virtualni stroj ugasne, v obliki 4 števk HHMM. Na primer, če želite izklop ob polnoči UTC, nastavite na `0000`. Za 19:30 na zahodni obali ZDA uporabite `0230` (19:30 na zahodni obali ZDA je 2:30 UTC).

1. Vaš klasifikator slik bo deloval na tej IoT Edge napravi in poslušal na vratih 80 (privzeta vrata za HTTP). Privzeto so vhodna vrata na virtualnih strojih blokirana, zato morate omogočiti vrata 80. Vrata se omogočijo na varnostnih skupinah omrežja, zato morate najprej pridobiti ime varnostne skupine omrežja za vaš virtualni stroj, kar lahko storite z naslednjim ukazom:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Kopirajte vrednost iz polja `Name`.

1. Za dodajanje pravila za odpiranje vrat 80 v varnostno skupino omrežja zaženite naslednji ukaz:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Zamenjajte `<nsg name>` z imenom varnostne skupine omrežja iz prejšnjega koraka.

### Naloga - upravljanje virtualnega stroja za zmanjšanje stroškov

1. Ko ne uporabljate virtualnega stroja, ga ugasnite. Za izklop virtualnega stroja uporabite naslednji ukaz:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Zamenjajte `<vm_name>` z imenom vašega virtualnega stroja.

    > 💁 Obstaja ukaz `az vm stop`, ki ustavi virtualni stroj, vendar računalnik ostane dodeljen vam, zato še vedno plačujete, kot da bi bil stroj vklopljen.

1. Za ponovni zagon virtualnega stroja uporabite naslednji ukaz:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Zamenjajte `<vm_name>` z imenom vašega virtualnega stroja.

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.