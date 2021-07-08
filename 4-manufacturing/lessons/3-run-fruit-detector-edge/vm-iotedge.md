# Create a virtual machine running IoT Edge

In Azure, you can create a virtual machine - a computer in the cloud that you can configure any way you wish and run your own software on it.

> 💁 You can read more about virtual machines on the [Virtual Machine page on Wikipedia](https://wikipedia.org/wiki/Virtual_machine).

## Task - Set up an IoT Edge virtual machine

1. Run the following command to create a VM that has Azure IoT Edge already pre-installed:

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

    Replace `<vm_name>` with a name for this virtual machine. This needs to be globally unique, so use something like `fruit-quality-detector-vm-` with your name or another value on the end.

    Replace `<username>` and `<password>` with a username and password to use to log in to the VM. These need to be relatively secure, so you can't use admin/password.

    Replace `<connection_string>` with the connection string of your `fruit-quality-detector-edge` IoT Edge device.

    This will create a VM configured as a `DS1 v2` virtual machine. These categories indicate how powerful the machine is, and therefor how much it costs. This VM has 1 CPU and 3.5GB of RAM.

    > 💰 You can see the current pricing of these VMs on the [Azure Virtual Machine pricing guide](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Once the VM has been created, the IoT Edge runtime will be installed automatically, and configured you connect to your IoT Hub as your `fruit-quality-detector-edge` device.

1. You will need either the IP address or the DNS name of the VM to call the image classifier from it. Run the following command to get this:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Take a copy of either the `PublicIps` field, or the `Fqdns` field.

1. VMs cost money. At the time of writing, a DS1 VM costs about $0.06 per hour. To keep costs down, you should shut down the VM when you are not using it, and delete it when you are finished with this project.

    You can configure your VM to automatically shut down at a certain time each day. This means if you forget to shut it down, you won't be billed for more than the time till the automatic shutdown. Use the following command to set this:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Replace `<vm_name>` with the name of your virtual machine.

    Replace `<shutdown_time_utc>` with the UTC time that you want the VM to shut down using 4 digits as HHMM. For example, if you want to shutdown at midnight UTC, you would set this to `0000`. For 7:30PM on the west coast of the USA, you would use 0230 (7:30PM on the US west coast is 2:30AM UTC).

1. Your image classifier will be running on this edge device, listening on port 80 (the standard HTTP port). By default, virtual machines have inbound ports blocked, so you will need to enable port 80. Ports are enabled on network security groups, so first you need to know the name of the network security group for your VM, which you can find with the following command:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Copy the value of the `Name` field.

1. Run the following command to add a rule to open port 80 to the network security group:

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

### Task - manage your VM to reduce costs

1. When you are not using your VM, you should shut it down. To shut down the VM, use the following command:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Replace `<vm_name>` with the name of your virtual machine.

    > 💁 There is an `az vm stop` command which will stop the VM, but it keeps the computer allocated to you, so you still pay as if it was still running.

1. To restart the VM, use the following command:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Replace `<vm_name>` with the name of your virtual machine.
