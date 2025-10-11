<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-10-11T11:39:15+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "et"
}
-->
# Loo IoT Edge'iga töötav virtuaalmasin

Azure'is saad luua virtuaalmasina - pilves asuva arvuti, mida saad konfigureerida vastavalt oma vajadustele ja millele saad paigaldada oma tarkvara.

> 💁 Virtuaalmasinate kohta saad rohkem lugeda [Virtuaalmasinate lehelt Wikipedias](https://wikipedia.org/wiki/Virtual_machine).

## Ülesanne - Seadista IoT Edge virtuaalmasin

1. Käivita järgmine käsk, et luua virtuaalmasin, millel on Azure IoT Edge juba eelinstallitud:

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

    Asenda `<vm_name>` virtuaalmasina nimega. See peab olema globaalselt unikaalne, seega kasuta midagi sellist nagu `fruit-quality-detector-vm-` koos oma nime või mõne muu väärtusega lõpus.

    Asenda `<username>` ja `<password>` kasutajanime ja parooliga, mida kasutatakse virtuaalmasinasse sisselogimiseks. Need peavad olema suhteliselt turvalised, seega ei saa kasutada näiteks admin/password kombinatsiooni.

    Asenda `<connection_string>` oma `fruit-quality-detector-edge` IoT Edge seadme ühenduse stringiga.

    See käsk loob virtuaalmasina, mis on konfigureeritud kui `DS1 v2` virtuaalmasin. Need kategooriad näitavad, kui võimas masin on ja seega, kui palju see maksab. Sellel virtuaalmasinal on 1 CPU ja 3.5GB RAM-i.

    > 💰 Praeguseid virtuaalmasinate hindu saad vaadata [Azure virtuaalmasinate hinnakirjast](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn).

    Kui virtuaalmasin on loodud, paigaldatakse IoT Edge runtime automaatselt ja konfigureeritakse ühendus sinu IoT Hub'iga kui `fruit-quality-detector-edge` seade.

1. Sul on vaja kas virtuaalmasina IP-aadressi või DNS-nime, et sellelt pildiklassifikaatorit kasutada. Käivita järgmine käsk, et seda saada:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Kopeeri kas `PublicIps` väli või `Fqdns` väli.

1. Virtuaalmasinad maksavad raha. Kirjutamise hetkel maksab DS1 virtuaalmasin umbes $0.06 tunnis. Kulude vähendamiseks peaksid virtuaalmasina välja lülitama, kui sa seda ei kasuta, ja projekti lõppedes selle kustutama.

    Sa saad konfigureerida oma virtuaalmasina automaatselt iga päev kindlal ajal välja lülituma. See tähendab, et kui unustad selle välja lülitada, ei arvestata sulle rohkem kui automaatse väljalülitamiseni kulunud aega. Kasuta järgmist käsku, et seda seadistada:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Asenda `<vm_name>` oma virtuaalmasina nimega.

    Asenda `<shutdown_time_utc>` UTC ajaga, millal soovid virtuaalmasina välja lülitada, kasutades 4 numbrit kujul HHMM. Näiteks, kui soovid välja lülitada keskööl UTC aja järgi, seadista see `0000`. USA lääneranniku kella 19:30 jaoks kasutaksid `0230` (kella 19:30 läänerannikul vastab UTC aja järgi kella 2:30-le).

1. Sinu pildiklassifikaator töötab sellel edge-seadmel, kuulates porti 80 (standardne HTTP port). Vaikimisi on virtuaalmasinate sissetulevad pordid blokeeritud, seega pead lubama porti 80. Pordid lubatakse võrgu turvagruppides, seega esmalt pead teadma oma virtuaalmasina võrgu turvagrupi nime, mille leiad järgmise käsuga:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Kopeeri `Name` väli.

1. Käivita järgmine käsk, et lisada reegel võrgu turvagruppi, mis avab porti 80:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Asenda `<nsg name>` võrgu turvagrupi nimega eelmisest sammust.

### Ülesanne - halda oma virtuaalmasinat kulude vähendamiseks

1. Kui sa oma virtuaalmasinat ei kasuta, peaksid selle välja lülitama. Virtuaalmasina väljalülitamiseks kasuta järgmist käsku:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Asenda `<vm_name>` oma virtuaalmasina nimega.

    > 💁 On olemas käsk `az vm stop`, mis peatab virtuaalmasina, kuid hoiab arvuti endiselt sulle eraldatuna, mistõttu maksad ikkagi nagu see töötaks.

1. Virtuaalmasina taaskäivitamiseks kasuta järgmist käsku:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Asenda `<vm_name>` oma virtuaalmasina nimega.

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.