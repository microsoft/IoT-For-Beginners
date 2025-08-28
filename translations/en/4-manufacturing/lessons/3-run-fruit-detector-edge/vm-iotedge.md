<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-28T19:06:58+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "en"
}
-->
# Create a virtual machine running IoT Edge

In Azure, you can create a virtual machine—a computer in the cloud that you can configure however you like and run your own software on.

> 💁 You can learn more about virtual machines on the [Virtual Machine page on Wikipedia](https://wikipedia.org/wiki/Virtual_machine).

## Task - Set up an IoT Edge virtual machine

1. Run the following command to create a VM with Azure IoT Edge pre-installed:

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

    Replace `<vm_name>` with a name for this virtual machine. This name must be globally unique, so use something like `fruit-quality-detector-vm-` followed by your name or another unique identifier.

    Replace `<username>` and `<password>` with a username and password for logging into the VM. These credentials need to be secure, so avoid using something simple like admin/password.

    Replace `<connection_string>` with the connection string of your `fruit-quality-detector-edge` IoT Edge device.

    This command will create a VM configured as a `DS1 v2` virtual machine. These categories indicate the machine's performance level and, consequently, its cost. This VM has 1 CPU and 3.5GB of RAM.

    > 💰 You can check the current pricing for these VMs on the [Azure Virtual Machine pricing guide](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Once the VM is created, the IoT Edge runtime will be installed automatically and configured to connect to your IoT Hub as the `fruit-quality-detector-edge` device.

1. To call the image classifier from the VM, you will need either its IP address or DNS name. Run the following command to retrieve this information:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Copy either the `PublicIps` field or the `Fqdns` field.

1. Virtual machines incur costs. At the time of writing, a DS1 VM costs approximately $0.06 per hour. To minimize expenses, you should shut down the VM when not in use and delete it once you’ve completed the project.

    You can configure your VM to automatically shut down at a specific time each day. This ensures that if you forget to shut it down, you won’t be billed for more than the time until the automatic shutdown. Use the following command to set this up:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Replace `<vm_name>` with the name of your virtual machine.

    Replace `<shutdown_time_utc>` with the UTC time you want the VM to shut down, using a 4-digit format (HHMM). For example, to shut down at midnight UTC, set this to `0000`. For 7:30 PM on the US West Coast, use `0230` (since 7:30 PM PST is 2:30 AM UTC).

1. Your image classifier will run on this edge device, listening on port 80 (the standard HTTP port). By default, virtual machines block inbound ports, so you’ll need to enable port 80. Ports are managed through network security groups, so first, you need to find the name of the network security group for your VM. Use the following command to retrieve this information:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Copy the value of the `Name` field.

1. Run the following command to add a rule that opens port 80 in the network security group:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Replace `<nsg name>` with the network security group name from the previous step.

### Task - Manage your VM to reduce costs

1. When you’re not using your VM, you should shut it down. Use the following command to shut down the VM:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Replace `<vm_name>` with the name of your virtual machine.

    > 💁 There is an `az vm stop` command that stops the VM, but it keeps the computer allocated to you, so you’ll still be charged as if it were running.

1. To restart the VM, use the following command:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Replace `<vm_name>` with the name of your virtual machine.

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.