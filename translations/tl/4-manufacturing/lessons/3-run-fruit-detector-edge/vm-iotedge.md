<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T21:13:22+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "tl"
}
-->
# Gumawa ng Virtual Machine na Tumatakbo sa IoT Edge

Sa Azure, maaari kang lumikha ng virtual machine - isang computer sa cloud na maaari mong i-configure ayon sa gusto mo at patakbuhin ang sarili mong software dito.

> 💁 Maaari mong basahin ang higit pa tungkol sa virtual machines sa [Virtual Machine page sa Wikipedia](https://wikipedia.org/wiki/Virtual_machine).

## Gawain - I-set up ang isang IoT Edge virtual machine

1. Patakbuhin ang sumusunod na command upang lumikha ng VM na may pre-installed na Azure IoT Edge:

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

    Palitan ang `<vm_name>` ng pangalan para sa virtual machine na ito. Kailangang ito ay globally unique, kaya gumamit ng isang bagay tulad ng `fruit-quality-detector-vm-` na may kasamang pangalan mo o ibang halaga sa dulo.

    Palitan ang `<username>` at `<password>` ng username at password na gagamitin upang mag-log in sa VM. Kailangang medyo secure ang mga ito, kaya hindi mo maaaring gamitin ang admin/password.

    Palitan ang `<connection_string>` ng connection string ng iyong `fruit-quality-detector-edge` IoT Edge device.

    Ito ay lilikha ng VM na naka-configure bilang isang `DS1 v2` virtual machine. Ang mga kategoryang ito ay nagpapahiwatig kung gaano kalakas ang makina, at kung magkano ang halaga nito. Ang VM na ito ay may 1 CPU at 3.5GB ng RAM.

    > 💰 Maaari mong tingnan ang kasalukuyang presyo ng mga VM na ito sa [Azure Virtual Machine pricing guide](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Kapag nalikha na ang VM, ang IoT Edge runtime ay awtomatikong mai-install at iko-configure upang kumonekta sa iyong IoT Hub bilang iyong `fruit-quality-detector-edge` device.

1. Kakailanganin mo ang IP address o ang DNS name ng VM upang tawagan ang image classifier mula rito. Patakbuhin ang sumusunod na command upang makuha ito:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Kopyahin ang alinman sa `PublicIps` field o ang `Fqdns` field.

1. Ang mga VM ay may kaukulang gastos. Sa kasalukuyang panahon ng pagsulat, ang isang DS1 VM ay nagkakahalaga ng humigit-kumulang $0.06 kada oras. Upang mabawasan ang gastos, dapat mong i-shut down ang VM kapag hindi mo ito ginagamit, at i-delete ito kapag tapos ka na sa proyektong ito.

    Maaari mong i-configure ang iyong VM upang awtomatikong mag-shut down sa isang tiyak na oras bawat araw. Nangangahulugan ito na kung makalimutan mong i-shut down ito, hindi ka sisingilin nang lampas sa oras hanggang sa awtomatikong pag-shut down. Gamitin ang sumusunod na command upang i-set ito:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Palitan ang `<vm_name>` ng pangalan ng iyong virtual machine.

    Palitan ang `<shutdown_time_utc>` ng UTC time na gusto mong mag-shut down ang VM gamit ang 4 na digit bilang HHMM. Halimbawa, kung gusto mong mag-shut down sa hatinggabi UTC, itakda ito sa `0000`. Para sa 7:30PM sa west coast ng USA, gamitin ang 0230 (7:30PM sa west coast ng USA ay 2:30AM UTC).

1. Ang iyong image classifier ay tatakbo sa edge device na ito, nakikinig sa port 80 (ang standard na HTTP port). Sa default, ang mga virtual machine ay may mga inbound port na naka-block, kaya kakailanganin mong i-enable ang port 80. Ang mga port ay na-enable sa network security groups, kaya una, kailangan mong malaman ang pangalan ng network security group para sa iyong VM, na makikita mo gamit ang sumusunod na command:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Kopyahin ang halaga ng `Name` field.

1. Patakbuhin ang sumusunod na command upang magdagdag ng rule para buksan ang port 80 sa network security group:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Palitan ang `<nsg name>` ng pangalan ng network security group mula sa nakaraang hakbang.

### Gawain - pamahalaan ang iyong VM upang mabawasan ang gastos

1. Kapag hindi mo ginagamit ang iyong VM, dapat mo itong i-shut down. Upang i-shut down ang VM, gamitin ang sumusunod na command:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Palitan ang `<vm_name>` ng pangalan ng iyong virtual machine.

    > 💁 Mayroong `az vm stop` command na magpapatigil sa VM, ngunit mananatili ang computer na naka-allocate sa iyo, kaya magbabayad ka pa rin na parang tumatakbo ito.

1. Upang i-restart ang VM, gamitin ang sumusunod na command:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Palitan ang `<vm_name>` ng pangalan ng iyong virtual machine.

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakatandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.