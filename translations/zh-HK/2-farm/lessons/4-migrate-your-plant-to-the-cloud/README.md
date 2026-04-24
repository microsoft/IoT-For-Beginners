# 將你的植物遷移到雲端

![本課程的手繪筆記概覽](../../../../../translated_images/zh-HK/lesson-8.3f21f3c11159e6a0.webp)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大版本。

本課程是 [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) 的 [IoT for Beginners Project 2 - Digital Agriculture 系列](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) 的一部分。

[![使用 Azure IoT Hub 將設備連接到雲端](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## 簡介

在上一課中，你學會了如何將植物連接到 MQTT broker，並通過本地運行的伺服器代碼控制繼電器。這構成了從家中單株植物到商業農場所使用的互聯網自動灌溉系統的核心。

IoT 設備通過公共 MQTT broker 進行通信，這是一種展示原理的方法，但並不是最可靠或安全的方式。在本課中，你將學習雲端以及公共雲服務提供的 IoT 功能，並學習如何將你的植物從公共 MQTT broker 遷移到這些雲服務之一。

在本課中，我們將涵蓋：

* [什麼是雲端？](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [創建雲端訂閱](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [雲端 IoT 服務](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [在雲端創建 IoT 服務](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [與 IoT Hub 通信](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [將設備連接到 IoT 服務](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## 什麼是雲端？

在雲端出現之前，當公司想為員工（例如數據庫或文件存儲）或公眾（例如網站）提供服務時，他們需要建立並運營一個數據中心。這可能是一個裝有少量電腦的房間，也可能是一棟裝有大量電腦的大樓。公司需要管理所有事情，包括：

* 購買電腦
* 硬件維護
* 電力和冷卻
* 網絡連接
* 安全性，包括建築物的安全和電腦軟件的安全
* 軟件安裝和更新

這樣做成本非常高，還需要各種專業技能的員工，並且在需要變更時速度非常慢。例如，如果一家在線商店需要為繁忙的假期季節做準備，他們需要提前幾個月計劃購買更多硬件，進行配置，安裝軟件以運行銷售流程。假期結束後，銷售量下降，他們就會留下閒置的電腦，直到下一個繁忙季節。

✅ 你認為這樣的方式能讓公司快速應對變化嗎？如果一家在線服裝零售商因為某位名人穿著他們的衣服而突然走紅，他們能否快速增加計算能力以支持突然湧入的訂單？

### 別人的電腦

雲端經常被戲稱為「別人的電腦」。最初的想法很簡單——與其購買電腦，不如租用別人的電腦。雲計算提供商會管理大型數據中心，負責購買和安裝硬件，管理電力和冷卻、網絡連接、建築安全、硬件和軟件更新等所有事情。作為客戶，你只需租用所需的電腦，需求增加時租用更多，需求減少時減少租用數量。這些雲端數據中心遍布全球。

![一個 Microsoft 雲端數據中心](../../../../../translated_images/zh-HK/azure-region-existing.73f704604f2aa6cb.webp)
![一個 Microsoft 雲端數據中心的擴建計劃](../../../../../translated_images/zh-HK/azure-region-planned-expansion.a5074a1e8af74f15.webp)

這些數據中心的面積可以達到數平方公里。上圖是幾年前拍攝的 Microsoft 雲端數據中心，展示了初始規模以及擴建計劃。擴建所清理的區域超過 5 平方公里。

> 💁 這些數據中心需要消耗大量電力，因此有些數據中心甚至擁有自己的發電站。由於其規模和雲提供商的投資，這些數據中心通常非常環保。它們比大量小型數據中心更高效，主要使用可再生能源運行，雲提供商還致力於減少浪費、降低用水量，並重新種植森林以補償為建設數據中心而砍伐的樹木。你可以在 [Azure 可持續性網站](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn) 上了解更多關於雲提供商如何推動可持續發展的信息。

✅ 做一些研究：查閱主要的雲服務提供商，例如 [Microsoft 的 Azure](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) 或 [Google 的 GCP](https://cloud.google.com)。他們有多少個數據中心？這些數據中心分佈在哪些地方？

使用雲端可以幫助公司降低成本，讓他們專注於自己的核心業務，將雲計算的專業知識交給提供商。公司不再需要租用或購買數據中心空間，向不同的供應商支付連接和電力費用，或僱用專家。相反，他們只需向雲提供商支付一張月費賬單，所有事情都由雲提供商處理。

雲提供商則可以利用規模經濟降低成本，例如批量購買電腦以獲得更低價格，投資工具以減少維護工作量，甚至設計和製造自己的硬件以改進雲服務。

### Microsoft Azure

Azure 是 Microsoft 的開發者雲端，這是你在本課中將使用的雲端。以下視頻簡要介紹了 Azure：

[![Azure 概覽視頻](../../../../../translated_images/zh-HK/what-is-azure-video-thumbnail.20174db09e03bbb8.webp)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## 創建雲端訂閱

要使用雲端服務，你需要向雲提供商註冊一個訂閱。在本課中，你將註冊一個 Microsoft Azure 訂閱。如果你已經有 Azure 訂閱，可以跳過此任務。以下描述的訂閱詳情在撰寫本文時是準確的，但可能會有所變更。

> 💁 如果你是通過學校學習本課程，你可能已經擁有一個 Azure 訂閱。請向你的老師確認。

Azure 提供兩種類型的免費訂閱：

* **Azure for Students** - 這是為 18 歲以上學生設計的訂閱。註冊時不需要信用卡，你可以使用學校的電子郵件地址驗證你的學生身份。註冊後，你將獲得 100 美元的雲資源使用額，以及包括 IoT 服務免費版本在內的免費服務。此訂閱有效期為 12 個月，每年可續訂一次，只要你仍是學生。

* **Azure 免費訂閱** - 這是為非學生設計的訂閱。註冊時需要提供信用卡，但不會扣款，僅用於驗證你是真人而非機器人。你將獲得 200 美元的信用額度，可在前 30 天內用於任何服務，此外還有 Azure 服務的免費層級。一旦信用額度用完，除非你轉為按需付費訂閱，否則不會向你的信用卡收費。

> 💁 Microsoft 還為 18 歲以下學生提供 Azure for Students Starter 訂閱，但在撰寫本文時，該訂閱不支持任何 IoT 服務。

### 任務 - 註冊免費雲端訂閱

如果你是 18 歲以上的學生，可以註冊 Azure for Students 訂閱。你需要使用學校的電子郵件地址進行驗證。你可以通過以下兩種方式之一完成：

* 在 [education.github.com/pack](https://education.github.com/pack) 註冊 GitHub 學生開發者包。這將為你提供一系列工具和優惠，包括 GitHub 和 Microsoft Azure。註冊開發者包後，你可以啟用 Azure for Students 優惠。

* 直接在 [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn) 註冊 Azure for Students 帳戶。

> ⚠️ 如果你的學校電子郵件地址未被識別，請在 [此 repo 提交問題](https://github.com/Microsoft/IoT-For-Beginners/issues)，我們將查看是否可以將其添加到 Azure for Students 的允許列表中。

如果你不是學生，或者沒有有效的學校電子郵件地址，可以註冊 Azure 免費訂閱。

* 在 [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn) 註冊 Azure 免費訂閱。

## 雲端 IoT 服務

你之前使用的公共測試 MQTT broker 是一個很好的學習工具，但作為商業用途的工具存在一些缺點：

* 可靠性 - 它是一個免費服務，沒有任何保證，隨時可能關閉
* 安全性 - 它是公共的，因此任何人都可以監聽你的數據或發送命令控制你的硬件
* 性能 - 它設計用於少量測試消息，無法處理大量消息的傳輸
* 發現性 - 無法知道有哪些設備已連接

雲端 IoT 服務解決了這些問題。這些服務由大型雲提供商維護，他們在可靠性方面投入巨大，並隨時解決可能出現的問題。這些服務內建安全性，防止黑客讀取你的數據或發送惡意命令。它們還具有高性能，能夠每天處理數百萬條消息，並利用雲端按需擴展。

> 💁 雖然這些優勢需要每月支付費用，但大多數雲提供商提供免費版本的 IoT 服務，限制每日消息數量或可連接的設備數量。這些免費版本通常足夠開發者學習使用。在本課中，你將使用免費版本。

IoT 設備可以通過設備 SDK（提供與服務功能交互的代碼庫）或直接使用通信協議（如 MQTT 或 HTTP）連接到雲服務。設備 SDK 通常是最簡單的路徑，因為它處理了所有細節，例如知道要發布或訂閱的主題，以及如何處理安全性。

![設備通過設備 SDK 連接到服務。伺服器代碼也通過 SDK 連接到服務](../../../../../translated_images/zh-HK/iot-service-connectivity.7e873847921a5d6f.webp)

你的設備然後通過該服務與應用程序的其他部分通信——類似於你之前通過 MQTT 發送遙測數據和接收命令的方式。這通常使用服務 SDK 或類似的庫。消息從設備發送到服務，應用程序的其他組件可以讀取這些消息，並將消息發送回設備。

![沒有有效密鑰的設備無法連接到 IoT 服務](../../../../../translated_images/zh-HK/iot-service-allowed-denied-connection.818b0063ac213fb8.webp)

這些服務通過了解所有可以連接並發送數據的設備來實現安全性，這可以通過預先註冊設備或為設備提供密鑰或證書來完成，設備在首次連接時使用這些密鑰或證書進行註冊。未知設備無法連接，如果嘗試連接，服務會拒絕並忽略其發送的消息。

✅ 做一些研究：開放式 IoT 服務允許任何設備或代碼連接會有哪些缺點？你能找到黑客利用這種情況的具體例子嗎？

應用程序的其他組件可以連接到 IoT 服務，了解所有已連接或已註冊的設備，並直接與它們進行單個或批量通信。
💁 物聯網服務亦提供額外功能，雲端供應商亦有額外的服務和應用程式可以連接到該服務。例如，如果你想將所有設備發送的遙測訊息存儲到資料庫中，通常只需在雲端供應商的配置工具中點擊幾下，就可以將服務連接到資料庫並將數據流入。
## 在雲端建立 IoT 服務

現在你已擁有 Azure 訂閱，可以註冊一個 IoT 服務。Microsoft 的 IoT 服務叫做 Azure IoT Hub。

![Azure IoT Hub 標誌](../../../../../translated_images/zh-HK/azure-iot-hub-logo.28a19de76d0a1932.webp)

以下影片簡要介紹了 Azure IoT Hub：

[![Azure IoT Hub 概述影片](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 點擊上方圖片觀看影片

✅ 花點時間進行研究，閱讀 [Microsoft IoT Hub 文件](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn) 中的 IoT Hub 概述。

Azure 提供的雲端服務可以透過網頁式入口網站或命令列介面 (CLI) 進行配置。這次任務中，你將使用 CLI。

### 任務 - 安裝 Azure CLI

要使用 Azure CLI，首先需要在你的 PC 或 Mac 上安裝它。

1. 按照 [Azure CLI 文件](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) 中的指示安裝 CLI。

1. Azure CLI 支援多種擴展功能，這些功能可用於管理各種 Azure 服務。透過命令列或終端執行以下指令來安裝 IoT 擴展功能：

    ```sh
    az extension add --name azure-iot
    ```

1. 從命令列或終端執行以下指令，使用 Azure CLI 登錄你的 Azure 訂閱。

    ```sh
    az login
    ```

    預設瀏覽器將開啟一個網頁。使用你註冊 Azure 訂閱的帳戶登錄。登錄完成後，可以關閉瀏覽器標籤。

1. 如果你有多個 Azure 訂閱，例如學校提供的訂閱和自己的 Azure for Students 訂閱，你需要選擇要使用的訂閱。執行以下指令列出你有權訪問的所有訂閱：

    ```sh
    az account list --output table
    ```

    在輸出中，你將看到每個訂閱的名稱及其 `SubscriptionId`。

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    使用以下指令選擇你要使用的訂閱：

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    將 `<SubscriptionId>` 替換為你想使用的訂閱 ID。執行此指令後，重新執行列出帳戶的指令。你會看到 `IsDefault` 列被標記為 `True`，表示你剛剛設置的訂閱。

### 任務 - 建立資源群組

Azure 服務，例如 IoT Hub 實例、虛擬機器、資料庫或 AI 服務，被稱為 **資源**。每個資源都必須屬於一個 **資源群組**，資源群組是一個或多個資源的邏輯分組。

> 💁 使用資源群組可以一次管理多個服務。例如，完成此專案的所有課程後，你可以刪除資源群組，所有資源將自動刪除。

1. Azure 在全球有多個數據中心，分布於不同的地區。當你建立 Azure 資源或資源群組時，必須指定其建立位置。執行以下指令以獲取位置列表：

    ```sh
    az account list-locations --output table
    ```

    你將看到一個位置列表。這個列表會很長。

    > 💁 截至撰寫本文時，你可以部署到 65 個位置。

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    記下距離你最近的地區的 `Name` 列值。你可以在 [Azure 地理位置頁面](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn) 上找到地區的地圖。

1. 執行以下指令建立名為 `soil-moisture-sensor` 的資源群組。資源群組名稱在你的訂閱中必須是唯一的。

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    將 `<location>` 替換為你在上一步選擇的位置。

### 任務 - 建立 IoT Hub

現在你可以在資源群組中建立 IoT Hub 資源。

1. 使用以下指令建立你的 IoT Hub 資源：

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    將 `<hub_name>` 替換為你的 Hub 名稱。此名稱必須是全球唯一的——即任何人建立的 IoT Hub 都不能有相同的名稱。此名稱將用於指向 Hub 的 URL，因此需要唯一。使用類似 `soil-moisture-sensor-` 的名稱，並在末尾添加唯一標識符，例如隨機字或你的名字。

    `--sku F1` 選項表示使用免費層。免費層每天支援 8,000 條消息，並提供大部分付費層的功能。

    > 🎓 Azure 服務的不同定價級別被稱為層。每個層都有不同的成本，並提供不同的功能或數據量。

    > 💁 如果你想了解更多定價資訊，可以查看 [Azure IoT Hub 定價指南](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn)。

    `--partition-count 2` 選項定義 IoT Hub 支援的數據流數量。更多分區可以減少多個設備讀寫 IoT Hub 時的數據阻塞。分區超出了這些課程的範疇，但此值需要設置以建立免費層 IoT Hub。

    > 💁 每個訂閱只能有一個免費層 IoT Hub。

IoT Hub 將被建立。這可能需要一分鐘左右完成。

## 與 IoT Hub 通訊

在上一課中，你使用 MQTT 並在不同的主題上來回發送消息，每個主題有不同的用途。與其通過不同的主題發送消息，IoT Hub 提供了多種定義的方式供設備與 Hub 通訊，或 Hub 與設備通訊。

> 💁 在底層，IoT Hub 與設備之間的通訊可以使用 MQTT、HTTPS 或 AMQP。

* 設備到雲端 (D2C) 消息 - 這些是從設備發送到 IoT Hub 的消息，例如遙測數據。應用程式代碼可以從 IoT Hub 讀取這些消息。

    > 🎓 在底層，IoT Hub 使用一個 Azure 服務叫做 [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn)。當你編寫代碼來讀取發送到 Hub 的消息時，這些通常被稱為事件。

* 雲端到設備 (C2D) 消息 - 這些是從應用程式代碼通過 IoT Hub 發送到 IoT 設備的消息。

* 直接方法請求 - 這些是從應用程式代碼通過 IoT Hub 發送到 IoT 設備的消息，用於請求設備執行某些操作，例如控制執行器。這些消息需要回應，以便應用程式代碼知道是否成功處理。

* 設備雙胞胎 - 這些是 JSON 文件，保持設備與 IoT Hub 之間的同步，用於存儲設備報告的設置或其他屬性，或 IoT Hub 希望在設備上設置的屬性（稱為期望值）。

IoT Hub 可以存儲消息和直接方法請求一段可配置的時間（默認為一天），因此如果設備或應用程式代碼失去連接，重新連接後仍然可以檢索離線期間發送的消息。設備雙胞胎永久保存在 IoT Hub 中，因此設備可以隨時重新連接並獲取最新的設備雙胞胎。

✅ 進行研究：閱讀 IoT Hub 文件中的 [設備到雲端通訊指南](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn) 和 [雲端到設備通訊指南](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn)。

## 連接你的設備到 IoT 服務

Hub 建立後，你的 IoT 設備可以連接到它。只有註冊的設備才能連接到服務，因此你需要先註冊設備。註冊後，你可以獲得一個連接字串，設備可以使用它來連接。此連接字串是設備專屬的，包含 IoT Hub、設備和允許設備連接的密鑰資訊。

> 🎓 連接字串是一個通用術語，指包含連接詳細資訊的一段文字。它們在連接 IoT Hub、資料庫和許多其他服務時使用。通常包括服務的識別符，例如 URL，以及安全資訊如密鑰。這些字串會傳遞給 SDK 用於連接服務。

> ⚠️ 連接字串應保持安全！安全性將在未來課程中詳細介紹。

### 任務 - 註冊你的 IoT 設備

可以使用 Azure CLI 將 IoT 設備註冊到你的 IoT Hub。

1. 執行以下指令註冊設備：

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    將 `<hub_name>` 替換為你用於 IoT Hub 的名稱。

    這將建立一個 ID 為 `soil-moisture-sensor` 的設備。

1. 當你的 IoT 設備使用 SDK 連接到 IoT Hub 時，需要使用一個連接字串，該字串提供 Hub 的 URL 和密鑰。執行以下指令以獲取連接字串：

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    將 `<hub_name>` 替換為你用於 IoT Hub 的名稱。

1. 保存輸出中顯示的連接字串，稍後你將需要它。

### 任務 - 將你的 IoT 設備連接到雲端

按照相關指南將你的 IoT 設備連接到雲端：

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [單板電腦 - Raspberry Pi/虛擬 IoT 設備](single-board-computer-connect-hub.md)

### 任務 - 監控事件

目前，你不需要更新伺服器代碼。你可以使用 Azure CLI 監控來自 IoT 設備的事件。

1. 確保你的 IoT 設備正在運行並發送土壤濕度遙測值。

1. 在命令提示符或終端中執行以下指令以監控發送到 IoT Hub 的消息：

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    將 `<hub_name>` 替換為你用於 IoT Hub 的名稱。

    你將在控制台輸出中看到消息，這些消息是由你的 IoT 設備發送的。

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 376}"
        }
    },
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    `payload` 的內容將與你的 IoT 設備發送的消息相匹配。

    > 截至撰寫本文時，`az iot` 擴展在 Apple Silicon 上尚未完全運作。如果你使用 Apple Silicon 設備，則需要使用其他方式監控消息，例如 [Visual Studio Code 的 Azure IoT 工具](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging)。

1. 這些消息自動附加了一些屬性，例如發送的時間戳。這些屬性被稱為 *註解*。要查看所有消息註解，使用以下指令：

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    將 `<hub_name>` 替換為你用於 IoT Hub 的名稱。

    你將在控制台輸出中看到消息，這些消息是由你的 IoT 設備發送的。

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "properties": {},
            "annotations": {
                "iothub-connection-device-id": "soil-moisture-sensor",
                "iothub-connection-auth-method": "{\"scope\":\"device\",\"type\":\"sas\",\"issuer\":\"iothub\",\"acceptingIpFilterRule\":null}",
                "iothub-connection-auth-generation-id": "637553997165220462",
                "iothub-enqueuedtime": 1619976150288,
                "iothub-message-source": "Telemetry",
                "x-opt-sequence-number": 1379,
                "x-opt-offset": "550576",
                "x-opt-enqueued-time": 1619976150277
            },
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    註解中的時間值是 [UNIX 時間](https://wikipedia.org/wiki/Unix_time)，表示自 1970 年 1 月 1 日午夜以來的秒數。

    完成後退出事件監控。

### 任務 - 控制你的 IoT 設備

你也可以使用 Azure CLI 對你的 IoT 設備調用直接方法。

1. 在命令提示符或終端中執行以下指令以調用 IoT 設備上的 `relay_on` 方法：

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    將 `
<hub_name>
` 使用你為 IoT Hub 設定的名稱。

這會發送一個直接方法請求，請求的方法由 `method-name` 指定。直接方法可以包含方法所需的數據作為負載，這些數據可以在 `method-payload` 參數中以 JSON 格式指定。

你會看到繼電器打開，並且你的 IoT 裝置會顯示相應的輸出：

```output
    Direct method received -  relay_on
    ```

1. 重複上述步驟，但將 `--method-name` 設定為 `relay_off`。你會看到繼電器關閉，並且 IoT 裝置會顯示相應的輸出。

---

## 🚀 挑戰

IoT Hub 的免費層每天允許 8,000 條消息。你所編寫的程式每 10 秒發送一次遙測消息。每天每 10 秒發送一條消息會產生多少條消息？

思考一下土壤濕度測量應該多頻繁發送？如何修改你的程式以保持在免費層的限制內，同時能夠按需檢查但不過於頻繁？如果你想添加第二個裝置又該怎麼辦？

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## 回顧與自學

IoT Hub SDK 是開源的，適用於 Arduino 和 Python。在 GitHub 的程式碼倉庫中，有許多範例展示如何使用不同的 IoT Hub 功能。

* 如果你使用的是 Wio Terminal，請查看 [GitHub 上的 Arduino 範例](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* 如果你使用的是 Raspberry Pi 或虛擬裝置，請查看 [GitHub 上的 Python 範例](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## 作業

[了解雲端服務](assignment.md)

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為具權威性的來源。對於重要資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。