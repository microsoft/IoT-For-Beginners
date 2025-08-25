<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-24T21:45:42+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "tw"
}
-->
# 建立運行 IoT Edge 的虛擬機器

在 Azure 中，您可以建立虛擬機器——一台雲端中的電腦，您可以隨意配置並在其上運行自己的軟體。

> 💁 您可以在 [Wikipedia 的虛擬機器頁面](https://wikipedia.org/wiki/Virtual_machine) 上了解更多關於虛擬機器的資訊。

## 任務 - 設置 IoT Edge 虛擬機器

1. 執行以下命令來建立一台已預先安裝 Azure IoT Edge 的虛擬機器：

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

    將 `<vm_name>` 替換為此虛擬機器的名稱。此名稱需要是全域唯一的，因此可以使用類似 `fruit-quality-detector-vm-` 的名稱，並在後面加上您的名字或其他值。

    將 `<username>` 和 `<password>` 替換為用於登錄虛擬機器的使用者名稱和密碼。這些需要相對安全，因此不能使用 admin/password。

    將 `<connection_string>` 替換為您的 `fruit-quality-detector-edge` IoT Edge 裝置的連接字串。

    這將建立一台配置為 `DS1 v2` 類型的虛擬機器。這些類型表示機器的性能以及成本。此虛擬機器具有 1 個 CPU 和 3.5GB 的 RAM。

    > 💰 您可以在 [Azure 虛擬機器定價指南](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn) 上查看這些虛擬機器的最新定價。

    一旦虛擬機器建立完成，IoT Edge 執行環境將自動安裝，並配置為連接到您的 IoT Hub 作為 `fruit-quality-detector-edge` 裝置。

1. 您需要虛擬機器的 IP 地址或 DNS 名稱才能從中調用影像分類器。執行以下命令以獲取此資訊：

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    複製 `PublicIps` 欄位或 `Fqdns` 欄位的值。

1. 虛擬機器是需要花費費用的。截至撰寫本文時，DS1 類型的虛擬機器每小時約需 $0.06。為了降低成本，您應在不使用虛擬機器時將其關閉，並在完成此專案後刪除它。

    您可以配置虛擬機器每天在特定時間自動關閉。這樣即使您忘記關閉，也不會被收取超過自動關閉時間的費用。使用以下命令進行設置：

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    將 `<vm_name>` 替換為您的虛擬機器名稱。

    將 `<shutdown_time_utc>` 替換為您希望虛擬機器關閉的 UTC 時間，使用 4 位數字表示為 HHMM。例如，如果您希望在 UTC 時間午夜關閉，則設置為 `0000`。如果是美國西岸晚上 7:30，則設置為 `0230`（美國西岸晚上 7:30 對應 UTC 時間凌晨 2:30）。

1. 您的影像分類器將在此邊緣裝置上運行，並監聽 80 埠（標準 HTTP 埠）。默認情況下，虛擬機器的入站埠是被阻止的，因此您需要啟用 80 埠。埠是在網路安全群組上啟用的，因此首先需要知道虛擬機器的網路安全群組名稱，可以通過以下命令找到：

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    複製 `Name` 欄位的值。

1. 執行以下命令，向網路安全群組添加規則以開啟 80 埠：

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    將 `<nsg name>` 替換為上一步中獲取的網路安全群組名稱。

### 任務 - 管理您的虛擬機器以降低成本

1. 當您不使用虛擬機器時，應將其關閉。使用以下命令關閉虛擬機器：

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    將 `<vm_name>` 替換為您的虛擬機器名稱。

    > 💁 還有一個 `az vm stop` 命令可以停止虛擬機器，但它會保留計算資源分配給您，因此費用仍然與運行時相同。

1. 要重新啟動虛擬機器，使用以下命令：

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    將 `<vm_name>` 替換為您的虛擬機器名稱。

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原文文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。