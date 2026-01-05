<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e345843ccfeb7261d81500d19c64d476",
  "translation_date": "2025-08-26T15:53:37+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/README.md",
  "language_code": "hk"
}
-->
# 儲存位置數據

![本課程的手繪筆記概述](../../../../../translated_images/lesson-12.ca7f53039712a3ec14ad6474d8445361c84adab643edc53fa6269b77895606bb.hk.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大版本。

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## 簡介

在上一課中，你學習了如何使用 GPS 感應器來捕捉位置數據。要將這些數據用於可視化一輛載滿食物的卡車的位置及其行程，需要將數據發送到雲端的 IoT 服務，並存儲在某個地方。

在本課中，你將學習存儲 IoT 數據的不同方法，並學習如何使用無伺服器代碼來存儲來自 IoT 服務的數據。

本課將涵蓋以下內容：

* [結構化數據與非結構化數據](../../../../../3-transport/lessons/2-store-location-data)
* [將 GPS 數據發送到 IoT Hub](../../../../../3-transport/lessons/2-store-location-data)
* [熱路徑、暖路徑和冷路徑](../../../../../3-transport/lessons/2-store-location-data)
* [使用無伺服器代碼處理 GPS 事件](../../../../../3-transport/lessons/2-store-location-data)
* [Azure 儲存帳戶](../../../../../3-transport/lessons/2-store-location-data)
* [將無伺服器代碼連接到儲存](../../../../../3-transport/lessons/2-store-location-data)

## 結構化數據與非結構化數據

計算機系統處理數據，而這些數據的形狀和大小各不相同。它可以是單一的數字、大量的文本、視頻和圖片，或者 IoT 數據。數據通常可以分為兩類——*結構化數據* 和 *非結構化數據*。

* **結構化數據** 是具有明確定義、固定結構的數據，通常映射到具有關聯的數據表。例如，一個人的詳細信息，包括姓名、出生日期和地址。

* **非結構化數據** 是沒有明確定義、固定結構的數據，包括結構可能頻繁變化的數據。例如，文檔如書面文件或電子表格。

✅ 做些研究：你能想到其他結構化和非結構化數據的例子嗎？

> 💁 還有一種半結構化數據，它具有結構但不符合固定的數據表。

IoT 數據通常被認為是非結構化數據。

想像一下，你正在為一家大型商業農場的車隊添加 IoT 設備。你可能希望為不同類型的車輛使用不同的設備。例如：

* 對於農場車輛如拖拉機，你需要 GPS 數據以確保它們在正確的田地工作
* 對於運送食物到倉庫的送貨卡車，你需要 GPS 數據以及速度和加速度數據，以確保司機安全駕駛，還需要駕駛身份和啟動/停止數據以確保司機遵守當地法律的工作時間規定
* 對於冷藏卡車，你還需要溫度數據以確保食物在運輸過程中不會過熱或過冷而變質

這些數據可能會不斷變化。例如，如果 IoT 設備位於卡車駕駛室中，那麼它發送的數據可能會隨著拖車的更換而改變，例如只有在使用冷藏拖車時才發送溫度數據。

✅ 還有什麼其他 IoT 數據可能被捕捉到？想想卡車可能運載的貨物類型，以及維護數據。

這些數據因車輛而異，但它們都被發送到同一個 IoT 服務進行處理。IoT 服務需要能夠處理這些非結構化數據，並以一種既能搜索或分析又能適應不同數據結構的方式存儲它。

### SQL 與 NoSQL 儲存

數據庫是允許存儲和查詢數據的服務。數據庫分為兩種類型——SQL 和 NoSQL。

#### SQL 數據庫

最早的數據庫是關係型數據庫管理系統 (RDBMS)，或稱為關係型數據庫。它們也被稱為 SQL 數據庫，因為它們使用結構化查詢語言 (SQL) 與數據庫交互以添加、刪除、更新或查詢數據。這些數據庫由一個模式組成——一組明確定義的數據表，類似於電子表格。每個表有多個命名列。插入數據時，你向表中添加一行，並將值放入每個列中。這使得數據保持非常固定的結構——儘管你可以留空列，但如果你想添加新列，必須在數據庫中進行操作，並為現有行填充值。這些數據庫是關係型的——即一個表可以與另一個表有關聯。

![一個關係型數據庫，其中用戶表的 ID 與購買表的用戶 ID 列相關，產品表的 ID 與購買表的產品 ID 列相關](../../../../../translated_images/sql-database.be160f12bfccefd3.hk.png)

例如，如果你在一個表中存儲用戶的個人詳細信息，你會為每個用戶設置某種內部唯一 ID，該 ID 用於存儲用戶的姓名和地址。如果你想在另一個表中存儲該用戶的其他詳細信息，例如購買記錄，你會在新表中設置一列來存儲該用戶的 ID。當你查詢用戶時，可以使用其 ID 從一個表中獲取個人詳細信息，並從另一個表中獲取購買記錄。

SQL 數據庫非常適合存儲結構化數據，並且可以確保數據符合你的模式。

✅ 如果你之前沒有使用過 SQL，請花點時間閱讀 [Wikipedia 上的 SQL 頁面](https://wikipedia.org/wiki/SQL)。

一些知名的 SQL 數據庫包括 Microsoft SQL Server、MySQL 和 PostgreSQL。

✅ 做些研究：閱讀一些這些 SQL 數據庫及其功能。

#### NoSQL 數據庫

NoSQL 數據庫之所以被稱為 NoSQL，是因為它們沒有 SQL 數據庫的固定結構。它們也被稱為文檔數據庫，因為它們可以存儲非結構化數據，例如文檔。

> 💁 儘管名稱如此，一些 NoSQL 數據庫允許使用 SQL 查詢數據。

![NoSQL 數據庫中的文件夾中的文檔](../../../../../translated_images/noqsl-database.62d24ccf5b73f60d35c245a8533f1c7147c0928e955b82cb290b2e184bb434df.hk.png)

NoSQL 數據庫沒有預定義的模式來限制數據存儲方式，你可以插入任何非結構化數據，通常使用 JSON 文檔。這些文檔可以像電腦上的文件一樣組織到文件夾中。每個文檔可以與其他文檔有不同的字段——例如，如果你存儲農場車輛的 IoT 數據，有些可能有加速度計和速度數據字段，其他可能有拖車內部溫度字段。如果你添加了一種新型卡車，例如內置秤來跟蹤運載的農產品重量，那麼你的 IoT 設備可以添加這個新字段，並且可以在不更改數據庫的情況下存儲。

一些知名的 NoSQL 數據庫包括 Azure CosmosDB、MongoDB 和 CouchDB。

✅ 做些研究：閱讀一些這些 NoSQL 數據庫及其功能。

在本課中，你將使用 NoSQL 儲存來存儲 IoT 數據。

## 將 GPS 數據發送到 IoT Hub

在上一課中，你從連接到 IoT 設備的 GPS 感應器捕捉了 GPS 數據。要在雲端存儲這些 IoT 數據，你需要將其發送到 IoT 服務。你將再次使用 Azure IoT Hub，這是你在上一個項目中使用的同一個 IoT 雲服務。

![將 GPS 遙測數據從 IoT 設備發送到 IoT Hub](../../../../../translated_images/gps-telemetry-iot-hub.8115335d51cd2c1285d20e9d1b18cf685e59a8e093e7797291ef173445af6f3d.hk.png)

### 任務 - 將 GPS 數據發送到 IoT Hub

1. 使用免費層創建一個新的 IoT Hub。

    > ⚠️ 如果需要，可以參考 [項目 2，第 4 課中創建 IoT Hub 的指導](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud)。

    記得創建一個新的資源組。將新的資源組命名為 `gps-sensor`，並為新的 IoT Hub 命名一個基於 `gps-sensor` 的唯一名稱，例如 `gps-sensor-<你的名字>`。

    > 💁 如果你仍然保留上一個項目的 IoT Hub，可以重複使用它。創建其他服務時，記得使用該 IoT Hub 的名稱及其所在的資源組。

1. 在 IoT Hub 中添加一個新設備。將此設備命名為 `gps-sensor`。獲取該設備的連接字符串。

1. 更新你的設備代碼，使用上一步中的設備連接字符串將 GPS 數據發送到新的 IoT Hub。

    > ⚠️ 如果需要，可以參考 [項目 2，第 4 課中將設備連接到 IoT 的指導](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service)。

1. 發送 GPS 數據時，請使用以下 JSON 格式：

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. 每分鐘發送一次 GPS 數據，以免超過每日消息配額。

如果你使用 Wio Terminal，記得添加所有必要的庫，並使用 NTP 伺服器設置時間。你的代碼還需要確保在發送 GPS 位置之前已從串口讀取所有數據，使用上一課的現有代碼。使用以下代碼構建 JSON 文檔：

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

如果你使用虛擬 IoT 設備，記得使用虛擬環境安裝所有需要的庫。

對於 Raspberry Pi 和虛擬 IoT 設備，使用上一課的現有代碼獲取緯度和經度值，然後使用以下代碼以正確的 JSON 格式發送它們：

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 你可以在 [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal)、[code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi) 或 [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device) 文件夾中找到這些代碼。

運行你的設備代碼，並使用 `az iot hub monitor-events` CLI 命令確保消息流入 IoT Hub。

## 熱路徑、暖路徑和冷路徑

從 IoT 設備流向雲端的數據並不總是實時處理。有些數據需要實時處理，其他數據可以稍後處理，還有一些數據可以更晚處理。數據流向不同服務以在不同時間處理的方式被稱為熱路徑、暖路徑和冷路徑。

### 熱路徑

熱路徑指需要實時或接近實時處理的數據。你可以使用熱路徑數據進行警報，例如接收到車輛接近倉庫的警報，或者冷藏卡車內溫度過高的警報。

要使用熱路徑數據，你的代碼需要在雲服務接收到事件時立即做出響應。

### 暖路徑

暖路徑指可以在接收到數據後稍作處理的數據，例如報告或短期分析。你可以使用暖路徑數據生成每日車輛里程報告，使用前一天收集的數據。

暖路徑數據在雲服務接收到後存儲在某種可以快速訪問的儲存中。

### 冷路徑

冷路徑指歷史數據，存儲長期數據以便隨時處理。例如，你可以使用冷路徑生成年度車輛里程報告，或者對路線進行分析以找到最優路線以降低燃料成本。

冷路徑數據存儲在數據倉庫中——設計用於存儲大量不會更改且可以快速輕鬆查詢的數據的數據庫。通常，你的雲應用程序會定期運行任務，每天、每週或每月定期將數據從暖路徑儲存移動到數據倉庫。

✅ 思考一下你在這些課程中捕捉到的數據。它是熱路徑、暖路徑還是冷路徑數據？

## 使用無伺服器代碼處理 GPS 事件

一旦數據流入你的 IoT Hub，你可以編寫一些無伺服器代碼來監聽發佈到 Event-Hub 兼容端點的事件。這是暖路徑——這些數據將被存儲並在下一課中用於報告行程。

![將 GPS 遙測數據從 IoT 設備發送到 IoT Hub，然後通過事件中心觸發器發送到 Azure Functions](../../../../../translated_images/gps-telemetry-iot-hub-functions.24d3fa5592455e9f4e2fe73856b40c3915a292b90263c31d652acfd976cfedd8.hk.png)

### 任務 - 使用無伺服器代碼處理 GPS 事件

1. 使用 Azure Functions CLI 創建一個 Azure Functions 應用。使用 Python 運行時，並在名為 `gps-trigger` 的文件夾中創建它，並使用相同的名稱作為 Functions App 項目名稱。確保創建一個虛擬環境來使用它。
> ⚠️ 你可以參考[如何從第2部分，第5課建立 Azure Functions 專案的指引](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application)（如有需要）。
1. 添加一個 IoT Hub 事件觸發器，使用 IoT Hub 的 Event Hub 兼容端點。

    > ⚠️ 如果需要，可以參考[項目 2，第 5 課中創建 IoT Hub 事件觸發器的指引](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger)。

1. 在 `local.settings.json` 文件中設置 Event Hub 兼容端點的連接字串，並在 `function.json` 文件中使用該條目的鍵。

1. 使用 Azurite 應用作為本地存儲模擬器。

1. 運行你的 Functions 應用，確保它能接收來自 GPS 設備的事件。確保你的 IoT 設備也在運行並發送 GPS 數據。

    ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Azure 存儲帳戶

![Azure Storage 標誌](../../../../../translated_images/azure-storage-logo.605c0f602c640d482a80f1b35a2629a32d595711b7ab1d7ceea843250615ff32.hk.png)

Azure 存儲帳戶是一種通用存儲服務，可以以多種方式存儲數據。你可以存儲數據為 Blob、隊列、表或文件，並且可以同時使用這些方式。

### Blob 存儲

*Blob* 的意思是二進制大型對象，但已成為任何非結構化數據的術語。你可以在 Blob 存儲中存儲任何數據，從包含 IoT 數據的 JSON 文檔到圖片和影片文件。Blob 存儲有 *容器* 的概念，容器是命名的存儲桶，用於存儲數據，類似於關係型數據庫中的表。這些容器可以包含一個或多個文件夾來存儲 Blob，每個文件夾可以包含其他文件夾，類似於電腦硬碟上的文件存儲方式。

在本課中，你將使用 Blob 存儲來存儲 IoT 數據。

✅ 做一些研究：閱讀 [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)

### 表存儲

表存儲允許你存儲半結構化數據。表存儲實際上是一個 NoSQL 數據庫，因此不需要事先定義表，但它設計用於在一個或多個表中存儲數據，每行都有唯一鍵。

✅ 做一些研究：閱讀 [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)

### 隊列存儲

隊列存儲允許你在隊列中存儲最多 64KB 的消息。你可以將消息添加到隊列的末尾，並從隊列的前端讀取。隊列會長期存儲消息，只要還有存儲空間，因此允許消息長期存儲，然後在需要時讀取。例如，如果你想每月運行一次作業來處理 GPS 數據，你可以每天將數據添加到隊列中，然後在月底處理所有消息。

✅ 做一些研究：閱讀 [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)

### 文件存儲

文件存儲是雲端的文件存儲，任何應用或設備都可以使用行業標準協議進行連接。你可以將文件寫入文件存儲，然後將其掛載為 PC 或 Mac 上的驅動器。

✅ 做一些研究：閱讀 [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)

## 將無伺服器代碼連接到存儲

你的 Functions 應用現在需要連接到 Blob 存儲，以存儲來自 IoT Hub 的消息。有兩種方法可以做到：

* 在函數代碼內，使用 Blob 存儲的 Python SDK 連接到 Blob 存儲並將數據寫入 Blob。
* 使用輸出函數綁定，將函數的返回值綁定到 Blob 存儲，並自動保存 Blob。

在本課中，你將使用 Python SDK 來了解如何與 Blob 存儲交互。

![將 GPS 遙測數據從 IoT 設備發送到 IoT Hub，然後通過事件觸發器發送到 Azure Functions，最後保存到 Blob 存儲](../../../../../translated_images/save-telemetry-to-storage-from-functions.ed3b1820980097f1.hk.png)

數據將保存為以下格式的 JSON Blob：

```json
{
    "device_id": <device_id>,
    "timestamp" : <time>,
    "gps" :
    {
        "lat" : <latitude>,
        "lon" : <longitude>
    }
}
```

### 任務 - 將無伺服器代碼連接到存儲

1. 創建一個 Azure 存儲帳戶。命名為類似 `gps<你的名字>`。

    > ⚠️ 如果需要，可以參考[項目 2，第 5 課中創建存儲帳戶的指引](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources)。

    如果你在之前的項目中已經有存儲帳戶，可以重複使用。

    > 💁 你可以在本課稍後部署 Azure Functions 應用時使用相同的存儲帳戶。

1. 運行以下命令以獲取存儲帳戶的連接字串：

    ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

    將 `<storage_name>` 替換為你在上一步中創建的存儲帳戶名稱。

1. 在 `local.settings.json` 文件中為存儲帳戶連接字串添加一個新條目，使用上一步的值。命名為 `STORAGE_CONNECTION_STRING`。

1. 在 `requirements.txt` 文件中添加以下內容，以安裝 Azure 存儲的 Pip 套件：

    ```sh
    azure-storage-blob
    ```

    在你的虛擬環境中安裝此文件中的套件。

    > 如果出現錯誤，請使用以下命令將虛擬環境中的 Pip 版本升級到最新版本，然後重試：
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. 在 `iot-hub-trigger` 的 `__init__.py` 文件中，添加以下導入語句：

    ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

    `json` 系統模組將用於讀寫 JSON，`os` 系統模組將用於讀取連接字串，`uuid` 系統模組將用於生成 GPS 讀數的唯一 ID。

    `azure.storage.blob` 套件包含與 Blob 存儲交互的 Python SDK。

1. 在 `main` 方法之前，添加以下輔助函數：

    ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

    Python Blob SDK 沒有輔助方法來創建不存在的容器。此代碼將從 `local.settings.json` 文件（或部署到雲端後的應用設置）中加載連接字串，然後從中創建一個 `BlobServiceClient` 類以與 Blob 存儲帳戶交互。接著，它會遍歷 Blob 存儲帳戶的所有容器，尋找具有提供名稱的容器——如果找到，則返回一個可以與容器交互以創建 Blob 的 `ContainerClient` 類。如果未找到，則創建容器並返回新容器的客戶端。

    當新容器被創建時，授予公共訪問權限以查詢容器中的 Blob。這將在下一課中用於在地圖上可視化 GPS 數據。

1. 與土壤濕度不同，這段代碼需要存儲每個事件，因此在 `main` 函數中的 `for event in events:` 循環內，`logging` 語句下方添加以下代碼：

    ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

    此代碼從事件元數據中獲取設備 ID，然後使用它創建 Blob 名稱。Blob 可以存儲在文件夾中，設備 ID 將用作文件夾名稱，因此每個設備的所有 GPS 事件都將存儲在一個文件夾中。Blob 名稱是該文件夾，後跟文檔名稱，用正斜杠分隔，類似於 Linux 和 macOS 路徑（也類似於 Windows，但 Windows 使用反斜杠）。文檔名稱是使用 Python `uuid` 模組生成的唯一 ID，文件類型為 `json`。

    例如，對於 `gps-sensor` 設備 ID，Blob 名稱可能是 `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`。

1. 在此代碼下方添加以下內容：

    ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

    此代碼使用 `get_or_create_container` 輔助類獲取容器客戶端，然後使用 Blob 名稱獲取 Blob 客戶端對象。這些 Blob 客戶端可以引用現有 Blob，也可以像此處一樣引用新 Blob。

1. 在此代碼後添加以下內容：

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

    此代碼構建將寫入 Blob 存儲的 Blob 主體。它是一個 JSON 文檔，包含設備 ID、消息發送到 IoT Hub 的時間以及遙測中的 GPS 坐標。

    > 💁 使用消息的入隊時間而不是當前時間來獲取消息發送的時間非常重要。如果 Functions 應用未運行，消息可能會在 Hub 上停留一段時間。

1. 在此代碼下方添加以下內容：

    ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

    此代碼記錄即將寫入的 Blob 及其詳細信息，然後將 Blob 主體上傳為新 Blob 的內容。

1. 運行 Functions 應用。你將看到所有 GPS 事件的 Blob 被寫入輸出：

    ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

    > 💁 確保你未同時運行 IoT Hub 事件監視器。

> 💁 你可以在 [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions) 文件夾中找到此代碼。

### 任務 - 驗證上傳的 Blob

1. 要查看創建的 Blob，你可以使用 [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn)，這是一個免費工具，允許你查看和管理存儲帳戶，或者使用 CLI。

    1. 要使用 CLI，首先需要一個帳戶密鑰。運行以下命令以獲取此密鑰：

        ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

        將 `<storage_name>` 替換為存儲帳戶的名稱。

        複製 `key1` 的值。

    1. 運行以下命令以列出容器中的 Blob：

        ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

        將 `<storage_name>` 替換為存儲帳戶的名稱，並將 `<key1>` 替換為你在上一步中複製的 `key1` 值。

        這將列出容器中的所有 Blob：

        ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

    1. 使用以下命令下載其中一個 Blob：

        ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

        將 `<storage_name>` 替換為存儲帳戶的名稱，並將 `<key1>` 替換為你之前步驟中複製的 `key1` 值。

        將 `<blob_name>` 替換為上一步輸出中 `Name` 列的完整名稱，包括文件夾名稱。將 `<file_name>` 替換為保存 Blob 的本地文件名。

    一旦下載完成，你可以在 VS Code 中打開 JSON 文件，並看到包含 GPS 位置詳細信息的 Blob：

    ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### 任務 - 將 Functions 應用部署到雲端

現在你的 Functions 應用已正常運行，可以將其部署到雲端。

1. 創建一個新的 Azure Functions 應用，使用你之前創建的存儲帳戶。命名為類似 `gps-sensor-`，並在末尾添加一個唯一標識符，例如一些隨機單詞或你的名字。

    > ⚠️ 如果需要，可以參考[項目 2，第 5 課中創建 Functions 應用的指引](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources)。

1. 將 `IOT_HUB_CONNECTION_STRING` 和 `STORAGE_CONNECTION_STRING` 值上傳到應用設置。

    > ⚠️ 如果需要，可以參考[項目 2，第 5 課中上傳應用設置的指引](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings)。

1. 將本地 Functions 應用部署到雲端。
> ⚠️ 你可以參考[第2個項目，第5課中有關部署 Functions 應用程式的指引](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud)，如有需要。
## 🚀 挑戰

GPS 數據並非完全準確，檢測到的位置可能會有幾米甚至更多的誤差，特別是在隧道和高樓林立的地區。

想一想衛星導航如何克服這個問題？你的衛星導航擁有什麼數據可以幫助它更準確地預測你的位置？

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## 回顧與自學

* 閱讀 [維基百科上的數據模型頁面](https://wikipedia.org/wiki/Data_model) 了解結構化數據
* 閱讀 [維基百科上的半結構化數據頁面](https://wikipedia.org/wiki/Semi-structured_data) 了解半結構化數據
* 閱讀 [維基百科上的非結構化數據頁面](https://wikipedia.org/wiki/Unstructured_data) 了解非結構化數據
* 閱讀 [Azure 儲存體文件](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn) 了解 Azure 儲存體及其不同的儲存類型

## 作業

[研究函數綁定](assignment.md)

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。