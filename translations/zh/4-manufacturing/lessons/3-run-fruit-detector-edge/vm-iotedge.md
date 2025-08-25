<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-24T21:45:27+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "zh"
}
-->
# 创建运行 IoT Edge 的虚拟机

在 Azure 中，你可以创建一台虚拟机——一台云端的计算机，你可以根据自己的需求进行配置并运行自己的软件。

> 💁 你可以在 [维基百科的虚拟机页面](https://wikipedia.org/wiki/Virtual_machine) 上了解更多关于虚拟机的信息。

## 任务 - 设置 IoT Edge 虚拟机

1. 运行以下命令来创建一台已经预装了 Azure IoT Edge 的虚拟机：

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

    将 `<vm_name>` 替换为这台虚拟机的名称。这个名称需要在全球范围内唯一，因此可以使用类似 `fruit-quality-detector-vm-` 的名称，并在后面加上你的名字或其他值。

    将 `<username>` 和 `<password>` 替换为用于登录虚拟机的用户名和密码。这些需要相对安全，因此不能使用类似 admin/password 的简单组合。

    将 `<connection_string>` 替换为 `fruit-quality-detector-edge` IoT Edge 设备的连接字符串。

    这将创建一台配置为 `DS1 v2` 的虚拟机。这些类别表示机器的性能，也决定了其成本。这台虚拟机有 1 个 CPU 和 3.5GB 的内存。

    > 💰 你可以在 [Azure 虚拟机定价指南](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn) 上查看这些虚拟机的当前定价。

    一旦虚拟机创建完成，IoT Edge 运行时将自动安装，并配置为连接到你的 IoT Hub，作为你的 `fruit-quality-detector-edge` 设备。

1. 你需要虚拟机的 IP 地址或 DNS 名称来从中调用图像分类器。运行以下命令获取这些信息：

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    复制 `PublicIps` 字段或 `Fqdns` 字段的值。

1. 虚拟机是需要花费费用的。截至撰写本文时，一台 DS1 虚拟机的费用大约是每小时 $0.06。为了节省成本，你应该在不使用虚拟机时将其关闭，并在完成项目后删除它。

    你可以配置虚拟机在每天的某个时间自动关闭。如果你忘记手动关闭，它将确保你不会被计费超过自动关闭的时间。使用以下命令设置自动关闭：

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    将 `<vm_name>` 替换为你的虚拟机名称。

    将 `<shutdown_time_utc>` 替换为你希望虚拟机关闭的 UTC 时间，使用 4 位数字表示为 HHMM。例如，如果你希望在 UTC 时间午夜关闭，可以设置为 `0000`。如果是美国西海岸的晚上 7:30，则使用 `0230`（美国西海岸的晚上 7:30 是 UTC 时间的凌晨 2:30）。

1. 你的图像分类器将在这个边缘设备上运行，监听 80 端口（标准 HTTP 端口）。默认情况下，虚拟机的入站端口是被阻止的，因此你需要启用 80 端口。端口是在网络安全组上启用的，因此首先需要知道虚拟机的网络安全组名称，可以通过以下命令找到：

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    复制 `Name` 字段的值。

1. 运行以下命令，为网络安全组添加一条规则以打开 80 端口：

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    将 `<nsg name>` 替换为上一步中获取的网络安全组名称。

### 任务 - 管理虚拟机以降低成本

1. 当你不使用虚拟机时，应该将其关闭。使用以下命令关闭虚拟机：

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    将 `<vm_name>` 替换为你的虚拟机名称。

    > 💁 还有一个 `az vm stop` 命令可以停止虚拟机，但它会保留计算资源分配给你，因此你仍然需要支付与运行状态相同的费用。

1. 要重新启动虚拟机，使用以下命令：

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    将 `<vm_name>` 替换为你的虚拟机名称。

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。因使用本翻译而引起的任何误解或误读，我们概不负责。