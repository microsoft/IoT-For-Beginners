<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-11-18T18:46:55+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "pcm"
}
-->
# Create virtual machine wey dey run IoT Edge

For Azure, you fit create virtual machine - na computer wey dey for cloud wey you fit configure anyhow you like and run your own software for am.

> 💁 You fit read more about virtual machines for [Virtual Machine page for Wikipedia](https://wikipedia.org/wiki/Virtual_machine).

## Task - Set up IoT Edge virtual machine

1. Run dis command to create VM wey don get Azure IoT Edge pre-installed:

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

    Change `<vm_name>` to name wey you wan give dis virtual machine. E go need dey unique for everywhere, so use something like `fruit-quality-detector-vm-` with your name or another value for the end.

    Change `<username>` and `<password>` to username and password wey you go use take log in to the VM. E need dey secure well, so you no fit use admin/password.

    Change `<connection_string>` to connection string of your `fruit-quality-detector-edge` IoT Edge device.

    Dis command go create VM wey be `DS1 v2` virtual machine. Dis category dey show how powerful the machine be, and how much e go cost. Dis VM get 1 CPU and 3.5GB RAM.

    > 💰 You fit check the current price of dis VMs for [Azure Virtual Machine pricing guide](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Once the VM don create finish, IoT Edge runtime go install by itself, and e go configure make e connect to your IoT Hub as your `fruit-quality-detector-edge` device.

1. You go need either the IP address or DNS name of the VM to call the image classifier from am. Run dis command to get am:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Copy either the `PublicIps` field, or the `Fqdns` field.

1. VMs dey cost money. As at the time wey dem write dis, DS1 VM dey cost about $0.06 per hour. To reduce cost, you suppose shut down the VM when you no dey use am, and delete am when you don finish dis project.

    You fit configure your VM make e dey shut down by itself for certain time every day. Dis one mean say if you forget to shut am down, you no go pay pass the time wey e go take reach the automatic shutdown. Use dis command to set am:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Change `<vm_name>` to the name of your virtual machine.

    Change `<shutdown_time_utc>` to the UTC time wey you wan make the VM shut down using 4 digits as HHMM. For example, if you wan shutdown for midnight UTC, you go set am to `0000`. For 7:30PM for west coast of USA, you go use 0230 (7:30PM for US west coast na 2:30AM UTC).

1. Your image classifier go dey run for dis edge device, dey listen for port 80 (the standard HTTP port). Normally, virtual machines dey block inbound ports, so you go need enable port 80. Ports dey enable for network security groups, so first you go need know the name of the network security group for your VM, wey you fit find with dis command:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Copy the value of the `Name` field.

1. Run dis command to add rule wey go open port 80 for the network security group:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Change `<nsg name>` to the network security group name wey you get from the previous step.

### Task - manage your VM to reduce costs

1. When you no dey use your VM, you suppose shut am down. To shut down the VM, use dis command:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Change `<vm_name>` to the name of your virtual machine.

    > 💁 E get `az vm stop` command wey fit stop the VM, but e go still keep the computer allocated to you, so you go still dey pay as if e still dey run.

1. To restart the VM, use dis command:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Change `<vm_name>` to the name of your virtual machine.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI transleshion service [Co-op Translator](https://github.com/Azure/co-op-translator) do di transleshion. Even as we dey try make am accurate, abeg make you sabi say automatik transleshion fit get mistake or no dey correct well. Di original dokyument wey dey for im native language na di one wey you go take as di main source. For important informashon, e good make you use professional human transleshion. We no go fit take blame for any misunderstanding or wrong meaning wey fit happen because you use dis transleshion.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->