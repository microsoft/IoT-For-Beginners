<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-26T22:02:48+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "mo"
}
-->
# 建立運行 IoT Edge 的虛擬機器

在 Azure 中，你可以建立一台虛擬機器——一台雲端中的電腦，你可以隨意配置並在其上運行自己的軟體。

> 💁 你可以在 [維基百科的虛擬機器頁面](https://wikipedia.org/wiki/Virtual_machine) 上了解更多關於虛擬機器的資訊。

## 任務 - 設置 IoT Edge 虛擬機器

1. 執行以下指令來建立一台已預先安裝 Azure IoT Edge 的虛擬機器：

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

    將 `<vm_name>` 替換為這台虛擬機器的名稱。這個名稱需要在全球範圍內唯一，因此可以使用類似 `fruit-quality-detector-vm-` 加上你的名字或其他值作為結尾。

    將 `<username>` 和 `<password>` 替換為用於登入虛擬機器的使用者名稱和密碼。這些需要相對安全，因此不能使用 admin/password 這樣的簡單組合。

    將 `<connection_string>` 替換為你的 `fruit-quality-detector-edge` IoT Edge 裝置的連接字串。

    這將建立一台配置為 `DS1 v2` 類型的虛擬機器。這些類別表示機器的性能，也因此影響成本。這台虛擬機器有 1 顆 CPU 和 3.5GB 的記憶體。

    > 💰 你可以在 [Azure 虛擬機器定價指南](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn) 上查看這些虛擬機器的最新價格。

    一旦虛擬機器建立完成，IoT Edge 執行環境將自動安裝，並配置為連接到你的 IoT Hub 作為 `fruit-quality-detector-edge` 裝置。

1. 你需要虛擬機器的 IP 位址或 DNS 名稱來從中調用影像分類器。執行以下指令來獲取這些資訊：

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    複製 `PublicIps` 欄位或 `Fqdns` 欄位的值。

1. 虛擬機器是需要花費金錢的。截至撰寫本文時，一台 DS1 虛擬機器的成本約為每小時 $0.06。為了降低成本，你應該在不使用時關閉虛擬機器，並在完成此專案後刪除它。

    你可以配置虛擬機器在每天的特定時間自動關閉。這樣即使你忘記手動關閉，也不會被收取超過自動關機時間的費用。使用以下指令來設置：

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    將 `<vm_name>` 替換為你的虛擬機器名稱。

    將 `<shutdown_time_utc>` 替換為你希望虛擬機器關機的 UTC 時間，使用 4 位數字表示 HHMM。例如，如果你希望在 UTC 午夜關機，則設置為 `0000`。如果是美國西岸晚上 7:30，則設置為 `0230`（美國西岸晚上 7:30 對應 UTC 時間為凌晨 2:30）。

1. 你的影像分類器將在這個邊緣裝置上運行，並監聽 80 埠（標準 HTTP 埠）。預設情況下，虛擬機器的入站埠是被封鎖的，因此你需要啟用 80 埠。埠是通過網路安全群組啟用的，因此首先你需要知道虛擬機器的網路安全群組名稱，可以通過以下指令獲取：

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    複製 `Name` 欄位的值。

1. 執行以下指令，為網路安全群組新增一條規則以開啟 80 埠：

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    將 `<nsg name>` 替換為上一個步驟中獲取的網路安全群組名稱。

### 任務 - 管理你的虛擬機器以降低成本

1. 當你不使用虛擬機器時，應該將其關閉。使用以下指令關閉虛擬機器：

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    將 `<vm_name>` 替換為你的虛擬機器名稱。

    > 💁 也有一個 `az vm stop` 指令可以停止虛擬機器，但這會保留電腦資源分配給你，因此仍然會像虛擬機器在運行時一樣收費。

1. 要重新啟動虛擬機器，使用以下指令：

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    將 `<vm_name>` 替換為你的虛擬機器名稱。

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。