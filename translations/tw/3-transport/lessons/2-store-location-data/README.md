<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e345843ccfeb7261d81500d19c64d476",
  "translation_date": "2025-08-25T01:01:32+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/README.md",
  "language_code": "tw"
}
-->
# 儲存位置數據

![本課程的手繪筆記概覽](../../../../../translated_images/lesson-12.ca7f53039712a3ec14ad6474d8445361c84adab643edc53fa6269b77895606bb.tw.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大版本。

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## 簡介

在上一課中，你學會了如何使用 GPS 感測器來捕捉位置數據。為了將這些數據用於可視化一輛載滿食物的卡車的位置及其行程，這些數據需要被傳送到雲端的 IoT 服務，然後存儲在某個地方。

在本課中，你將學習不同的 IoT 數據存儲方式，並學會如何使用無伺服器代碼來存儲來自 IoT 服務的數據。

本課將涵蓋以下內容：

* [結構化數據與非結構化數據](../../../../../3-transport/lessons/2-store-location-data)
* [將 GPS 數據發送到 IoT Hub](../../../../../3-transport/lessons/2-store-location-data)
* [熱路徑、溫路徑與冷路徑](../../../../../3-transport/lessons/2-store-location-data)
* [使用無伺服器代碼處理 GPS 事件](../../../../../3-transport/lessons/2-store-location-data)
* [Azure 儲存帳戶](../../../../../3-transport/lessons/2-store-location-data)
* [將無伺服器代碼連接到存儲](../../../../../3-transport/lessons/2-store-location-data)

## 結構化數據與非結構化數據

計算機系統處理數據，而這些數據的形狀和大小各不相同。它可以是單一的數字、大量的文本、視頻和圖像，甚至是 IoT 數據。數據通常可以分為兩類——*結構化數據* 和 *非結構化數據*。

* **結構化數據** 是具有明確定義、固定結構的數據，這種結構通常不會改變，並且通常對應於具有關聯性的數據表。例如，一個人的詳細信息，包括姓名、出生日期和地址。

* **非結構化數據** 是沒有明確定義、固定結構的數據，包括結構可能經常變化的數據。例如，書面文件或電子表格。

✅ 做些研究：你能想到其他結構化和非結構化數據的例子嗎？

> 💁 還有一種半結構化數據，它具有結構但不符合固定的數據表格式。

IoT 數據通常被認為是非結構化數據。

想像一下，你正在為一家大型商業農場的車隊添加 IoT 設備。你可能希望為不同類型的車輛使用不同的設備。例如：

* 對於像拖拉機這樣的農用車輛，你需要 GPS 數據來確保它們在正確的田地上工作。
* 對於運送食品到倉庫的送貨卡車，你需要 GPS 數據以及速度和加速度數據，以確保駕駛員安全駕駛，還需要駕駛身份和啟動/停止數據，以確保駕駛員遵守當地關於工作時間的法律。
* 對於冷藏卡車，你還需要溫度數據，以確保食品在運輸過程中不會過熱或過冷而變質。

這些數據可能會不斷變化。例如，如果 IoT 設備位於卡車駕駛室內，那麼當拖車更換時，它發送的數據可能會改變，例如只有在使用冷藏拖車時才發送溫度數據。

✅ 還有什麼其他 IoT 數據可能被捕捉到？想想卡車可能運載的貨物類型，以及維護數據。

這些數據因車輛而異，但它們都會被發送到同一個 IoT 服務進行處理。IoT 服務需要能夠處理這些非結構化數據，並以一種既能搜索或分析，又能適應這些數據不同結構的方式進行存儲。

### SQL 與 NoSQL 存儲

數據庫是一種允許你存儲和查詢數據的服務。數據庫分為兩種類型——SQL 和 NoSQL。

#### SQL 數據庫

最早的數據庫是關聯式數據庫管理系統（RDBMS），也稱為關聯式數據庫。這些數據庫也被稱為 SQL 數據庫，因為它們使用結構化查詢語言（SQL）來添加、刪除、更新或查詢數據。這些數據庫由一個模式（schema）組成——一組明確定義的數據表，類似於電子表格。每個表都有多個命名列。當你插入數據時，你會向表中添加一行，將值放入每個列中。這使得數據保持非常固定的結構——儘管你可以留空某些列，但如果你想添加新列，則必須在數據庫中執行此操作，並為現有行填充值。這些數據庫是關聯式的——即一個表可以與另一個表有關聯。

![一個關聯式數據庫，其中用戶表的 ID 與購買表的用戶 ID 列相關，產品表的 ID 與購買表的產品 ID 列相關](../../../../../translated_images/sql-database.be160f12bfccefd3ca718a66468c2c4c89c53e5aad4c295324d576da87f9dfdd.tw.png)

例如，如果你將用戶的個人詳細信息存儲在一個表中，你會為每個用戶分配某種內部唯一 ID，該 ID 用於包含用戶姓名和地址的表中的一行。如果你想在另一個表中存儲該用戶的其他詳細信息，例如購買記錄，你會在新表中為該用戶的 ID 添加一列。當你查詢用戶時，可以使用他們的 ID 從一個表中獲取個人詳細信息，並從另一個表中獲取購買記錄。

SQL 數據庫非常適合存儲結構化數據，並且當你希望確保數據符合模式時非常有用。

✅ 如果你之前沒有使用過 SQL，花點時間閱讀 [Wikipedia 上的 SQL 頁面](https://wikipedia.org/wiki/SQL)。

一些知名的 SQL 數據庫包括 Microsoft SQL Server、MySQL 和 PostgreSQL。

✅ 做些研究：閱讀一些這些 SQL 數據庫及其功能。

#### NoSQL 數據庫

NoSQL 數據庫之所以被稱為 NoSQL，是因為它們沒有 SQL 數據庫那樣的固定結構。它們也被稱為文檔數據庫，因為它們可以存儲非結構化數據，例如文檔。

> 💁 儘管名稱如此，一些 NoSQL 數據庫允許你使用 SQL 查詢數據。

![NoSQL 數據庫中的文件夾中的文檔](../../../../../translated_images/noqsl-database.62d24ccf5b73f60d35c245a8533f1c7147c0928e955b82cb290b2e184bb434df.tw.png)

NoSQL 數據庫沒有預定義的模式來限制數據的存儲方式，相反，你可以插入任何非結構化數據，通常使用 JSON 文檔。這些文檔可以組織成文件夾，類似於計算機上的文件。每個文檔可以與其他文檔具有不同的字段——例如，如果你存儲來自農場車輛的 IoT 數據，有些可能有加速度計和速度數據字段，其他可能有拖車內部溫度的字段。如果你添加了一種新型卡車，例如內置秤來跟蹤運輸的貨物重量，那麼你的 IoT 設備可以添加這個新字段，並且可以在不更改數據庫的情況下存儲它。

一些知名的 NoSQL 數據庫包括 Azure CosmosDB、MongoDB 和 CouchDB。

✅ 做些研究：閱讀一些這些 NoSQL 數據庫及其功能。

在本課中，你將使用 NoSQL 存儲來存儲 IoT 數據。

## 將 GPS 數據發送到 IoT Hub

在上一課中，你從連接到 IoT 設備的 GPS 感測器捕捉了 GPS 數據。為了將這些 IoT 數據存儲到雲端，你需要將其發送到 IoT 服務。你將再次使用 Azure IoT Hub，這是你在上一個項目中使用的相同 IoT 雲服務。

![將 GPS 遙測數據從 IoT 設備發送到 IoT Hub](../../../../../translated_images/gps-telemetry-iot-hub.8115335d51cd2c1285d20e9d1b18cf685e59a8e093e7797291ef173445af6f3d.tw.png)

### 任務 - 將 GPS 數據發送到 IoT Hub

1. 使用免費層創建一個新的 IoT Hub。

    > ⚠️ 如果需要，可以參考 [項目 2，第 4 課中創建 IoT Hub 的說明](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud)。

    記得創建一個新的資源組。將新資源組命名為 `gps-sensor`，並為新的 IoT Hub 命名一個基於 `gps-sensor` 的唯一名稱，例如 `gps-sensor-<你的名字>`。

    > 💁 如果你仍然保留上一個項目的 IoT Hub，可以重複使用它。記得在創建其他服務時使用該 IoT Hub 的名稱及其所在的資源組。

1. 在 IoT Hub 中添加一個新設備。將該設備命名為 `gps-sensor`，並獲取該設備的連接字串。

1. 更新你的設備代碼，使用上一步中的設備連接字串將 GPS 數據發送到新的 IoT Hub。

    > ⚠️ 如果需要，可以參考 [項目 2，第 4 課中將設備連接到 IoT 的說明](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service)。

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

1. 每分鐘發送一次 GPS 數據，以免用完每日消息配額。

如果你使用的是 Wio Terminal，記得添加所有必要的庫，並使用 NTP 伺服器設置時間。你的代碼還需要確保在發送 GPS 位置之前已從串口讀取所有數據，使用上一課中的現有代碼。使用以下代碼構建 JSON 文檔：

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

如果你使用的是虛擬 IoT 設備，記得使用虛擬環境安裝所有必要的庫。

對於 Raspberry Pi 和虛擬 IoT 設備，使用上一課中的現有代碼獲取緯度和經度值，然後使用以下代碼以正確的 JSON 格式發送它們：

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 你可以在 [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal)、[code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi) 或 [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device) 文件夾中找到這些代碼。

運行你的設備代碼，並使用 `az iot hub monitor-events` CLI 命令確保消息正在流入 IoT Hub。

## 熱路徑、溫路徑與冷路徑

從 IoT 設備流向雲端的數據並不總是需要實時處理。有些數據需要實時處理，有些數據可以稍後處理，而其他數據可以在更晚的時間處理。數據流向不同服務以在不同時間進行處理的方式被稱為熱路徑、溫路徑和冷路徑。

### 熱路徑

熱路徑指需要實時或接近實時處理的數據。你可以使用熱路徑數據來觸發警報，例如當車輛接近倉庫時，或者當冷藏卡車內的溫度過高時。

要使用熱路徑數據，你的代碼需要在雲服務接收到事件時立即響應。

### 溫路徑

溫路徑指可以在接收後稍作延遲處理的數據，例如用於報告或短期分析。你可以使用溫路徑數據生成每日車輛里程報告，使用前一天收集的數據。

溫路徑數據在被雲服務接收後會存儲在某種可以快速訪問的存儲中。

### 冷路徑

冷路徑指歷史數據，將數據長期存儲以便在需要時處理。例如，你可以使用冷路徑生成車輛的年度里程報告，或者對路線進行分析以找到最優路線以降低燃料成本。

冷路徑數據存儲在數據倉庫中——這些數據庫專為存儲大量不會更改的數據而設計，並且可以快速輕鬆地查詢。通常，你的雲應用程序會定期執行一個任務，每天、每週或每月將數據從溫路徑存儲移動到數據倉庫。

✅ 想一想你在這些課程中捕捉到的數據。它是熱路徑、溫路徑還是冷路徑數據？

## 使用無伺服器代碼處理 GPS 事件

一旦數據流入你的 IoT Hub，你可以編寫一些無伺服器代碼來監聽發佈到 Event-Hub 兼容端點的事件。這是溫路徑——這些數據將被存儲，並在下一課中用於行程報告。

![將 GPS 遙測數據從 IoT 設備發送到 IoT Hub，然後通過事件中心觸發器發送到 Azure Functions](../../../../../translated_images/gps-telemetry-iot-hub-functions.24d3fa5592455e9f4e2fe73856b40c3915a292b90263c31d652acfd976cfedd8.tw.png)

### 任務 - 使用無伺服器代碼處理 GPS 事件

1. 使用 Azure Functions CLI 創建一個 Azure Functions 應用程序。使用 Python 運行時，並在名為 `gps-trigger` 的文件夾中創建它，並使用相同的名稱作為 Functions App 項目名稱。確保創建一個虛擬環境來使用它。
> ⚠️ 您可以參考[從第2部分，第5課建立 Azure Functions 專案的指導](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application)（如有需要）。
1. 新增一個 IoT Hub 事件觸發器，使用 IoT Hub 的 Event Hub 相容端點。

    > ⚠️ 如果需要，可以參考[專案 2，第 5 課中建立 IoT Hub 事件觸發器的指引](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger)。

1. 在 `local.settings.json` 文件中設定 Event Hub 相容端點的連接字串，並在 `function.json` 文件中使用該條目的鍵值。

1. 使用 Azurite 應用程式作為本地儲存模擬器。

1. 執行您的 Functions 應用程式，確保它能接收來自 GPS 裝置的事件。確保您的 IoT 裝置也正在運行並傳送 GPS 數據。

    ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Azure 儲存帳戶

![Azure Storage 標誌](../../../../../translated_images/azure-storage-logo.605c0f602c640d482a80f1b35a2629a32d595711b7ab1d7ceea843250615ff32.tw.png)

Azure 儲存帳戶是一種通用的儲存服務，可以以多種不同的方式儲存數據。您可以將數據儲存為 Blob、佇列、表格或檔案，並且可以同時使用這些方式。

### Blob 儲存

*Blob* 是指二進制大型物件，但已成為任何非結構化數據的術語。您可以將任何數據儲存在 Blob 儲存中，從包含 IoT 數據的 JSON 文件到圖片和影片檔案。Blob 儲存具有 *容器* 的概念，這些容器是命名的存儲桶，類似於關聯式資料庫中的表格。這些容器可以包含一個或多個資料夾來儲存 Blob，每個資料夾可以包含其他資料夾，類似於電腦硬碟上的檔案存儲方式。

在本課中，您將使用 Blob 儲存來儲存 IoT 數據。

✅ 做一些研究：閱讀 [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)

### 表格儲存

表格儲存允許您儲存半結構化數據。表格儲存實際上是一種 NoSQL 資料庫，因此不需要事先定義表格，但它設計用於在一個或多個表格中儲存數據，並使用唯一鍵來定義每一行。

✅ 做一些研究：閱讀 [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)

### 佇列儲存

佇列儲存允許您在佇列中儲存大小最多為 64KB 的訊息。您可以將訊息添加到佇列的尾部，並從佇列的頭部讀取。佇列會無限期地儲存訊息，只要還有儲存空間，因此允許訊息長期儲存，並在需要時讀取。例如，如果您想每月執行一次處理 GPS 數據的工作，可以每天將數據添加到佇列，然後在月底處理所有訊息。

✅ 做一些研究：閱讀 [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)

### 檔案儲存

檔案儲存是將檔案儲存在雲端，任何應用程式或裝置都可以使用業界標準協議進行連接。您可以將檔案寫入檔案儲存，然後將其掛載為 PC 或 Mac 上的磁碟。

✅ 做一些研究：閱讀 [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)

## 將無伺服器代碼連接到儲存

您的 Functions 應用程式現在需要連接到 Blob 儲存，以儲存來自 IoT Hub 的訊息。有兩種方式可以實現：

* 在函數代碼內，使用 Blob 儲存的 Python SDK 連接到 Blob 儲存並將數據寫入 Blob。
* 使用輸出函數綁定，將函數的返回值綁定到 Blob 儲存，並自動將 Blob 儲存。

在本課中，您將使用 Python SDK 來了解如何與 Blob 儲存進行互動。

![從 IoT 裝置傳送 GPS 遙測數據到 IoT Hub，然後通過事件觸發器傳送到 Azure Functions，最後儲存到 Blob 儲存](../../../../../translated_images/save-telemetry-to-storage-from-functions.ed3b1820980097f143d9f0570072da11304c2bc7906359dfa075b4d9b253c20f.tw.png)

數據將以以下格式儲存為 JSON Blob：

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

### 任務 - 將無伺服器代碼連接到儲存

1. 建立一個 Azure 儲存帳戶。命名為類似 `gps<您的名字>` 的名稱。

    > ⚠️ 如果需要，可以參考[專案 2，第 5 課中建立儲存帳戶的指引](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources)。

    如果您在上一個專案中已經有一個儲存帳戶，可以重複使用。

    > 💁 您稍後可以使用相同的儲存帳戶來部署 Azure Functions 應用程式。

1. 執行以下命令以獲取儲存帳戶的連接字串：

    ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

    將 `<storage_name>` 替換為您在上一步中建立的儲存帳戶名稱。

1. 在 `local.settings.json` 文件中為儲存帳戶連接字串新增一個條目，使用上一步的值。命名為 `STORAGE_CONNECTION_STRING`。

1. 在 `requirements.txt` 文件中新增以下內容以安裝 Azure 儲存的 Pip 套件：

    ```sh
    azure-storage-blob
    ```

    在您的虛擬環境中從此文件安裝套件。

    > 如果出現錯誤，請在虛擬環境中使用以下命令將您的 Pip 版本升級到最新版本，然後重試：
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. 在 `iot-hub-trigger` 的 `__init__.py` 文件中，新增以下匯入語句：

    ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

    `json` 系統模組將用於讀取和寫入 JSON，`os` 系統模組將用於讀取連接字串，`uuid` 系統模組將用於為 GPS 讀數生成唯一 ID。

    `azure.storage.blob` 套件包含用於與 Blob 儲存交互的 Python SDK。

1. 在 `main` 方法之前，新增以下輔助函數：

    ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

    Python 的 Blob SDK 沒有輔助方法來在容器不存在時創建容器。此代碼將從 `local.settings.json` 文件（或部署到雲端後的應用程式設定）中加載連接字串，然後從中創建一個 `BlobServiceClient` 類來與 Blob 儲存帳戶交互。接著，它會遍歷 Blob 儲存帳戶的所有容器，尋找具有提供名稱的容器——如果找到，將返回一個可以與該容器交互以創建 Blob 的 `ContainerClient` 類。如果未找到，則會創建容器並返回新容器的客戶端。

    當新容器被創建時，會授予公共訪問權限以查詢容器中的 Blob。在下一課中，這將用於在地圖上可視化 GPS 數據。

1. 與土壤濕度不同，這段代碼需要儲存每個事件，因此在 `main` 函數中的 `for event in events:` 迴圈內，`logging` 語句下方新增以下代碼：

    ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

    此代碼從事件元數據中獲取裝置 ID，然後使用它來創建 Blob 名稱。Blob 可以儲存在資料夾中，裝置 ID 將用作資料夾名稱，因此每個裝置的所有 GPS 事件都將儲存在一個資料夾中。Blob 名稱是該資料夾，後跟一個文檔名稱，兩者之間用正斜杠分隔，類似於 Linux 和 macOS 的路徑（也類似於 Windows，但 Windows 使用反斜杠）。文檔名稱是使用 Python 的 `uuid` 模組生成的唯一 ID，檔案類型為 `json`。

    例如，對於 `gps-sensor` 裝置 ID，Blob 名稱可能是 `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`。

1. 在此代碼下方新增以下代碼：

    ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

    此代碼使用 `get_or_create_container` 輔助類獲取容器客戶端，然後使用 Blob 名稱獲取 Blob 客戶端物件。這些 Blob 客戶端可以引用現有的 Blob，或者像這裡一樣，引用新的 Blob。

1. 在此代碼後新增以下代碼：

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

    這會構建將寫入 Blob 儲存的 Blob 主體。它是一個包含裝置 ID、遙測數據發送到 IoT Hub 的時間以及遙測中的 GPS 座標的 JSON 文檔。

    > 💁 使用訊息的排隊時間而不是當前時間來獲取訊息發送的時間非常重要。如果 Functions 應用程式未運行，訊息可能會在 Hub 上停留一段時間。

1. 在此代碼下方新增以下內容：

    ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

    此代碼記錄即將寫入的 Blob 及其詳細信息，然後將 Blob 主體上傳為新 Blob 的內容。

1. 執行 Functions 應用程式。您將在輸出中看到為所有 GPS 事件寫入的 Blob：

    ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

    > 💁 確保您未同時運行 IoT Hub 事件監視器。

> 💁 您可以在 [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions) 資料夾中找到此代碼。

### 任務 - 驗證上傳的 Blob

1. 要查看創建的 Blob，您可以使用 [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn)，這是一個免費工具，允許您查看和管理儲存帳戶，或者使用 CLI。

    1. 若要使用 CLI，首先需要一個帳戶金鑰。執行以下命令以獲取此金鑰：

        ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

        將 `<storage_name>` 替換為儲存帳戶的名稱。

        複製 `key1` 的值。

    1. 執行以下命令以列出容器中的 Blob：

        ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

        將 `<storage_name>` 替換為儲存帳戶的名稱，將 `<key1>` 替換為您在上一步中複製的 `key1` 值。

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

        將 `<storage_name>` 替換為儲存帳戶的名稱，將 `<key1>` 替換為您之前複製的 `key1` 值。

        將 `<blob_name>` 替換為上一步輸出中 `Name` 欄位的完整名稱，包括資料夾名稱。將 `<file_name>` 替換為要儲存 Blob 的本地檔案名稱。

    下載後，您可以在 VS Code 中打開 JSON 文件，您將看到包含 GPS 位置詳細信息的 Blob：

    ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### 任務 - 將 Functions 應用程式部署到雲端

現在您的 Functions 應用程式已經可以運行，您可以將其部署到雲端。

1. 建立一個新的 Azure Functions 應用程式，使用您之前建立的儲存帳戶。命名為類似 `gps-sensor-` 並在末尾添加一個唯一標識符，例如一些隨機單詞或您的名字。

    > ⚠️ 如果需要，可以參考[專案 2，第 5 課中建立 Functions 應用程式的指引](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources)。

1. 將 `IOT_HUB_CONNECTION_STRING` 和 `STORAGE_CONNECTION_STRING` 值上傳到應用程式設定。

    > ⚠️ 如果需要，可以參考[專案 2，第 5 課中上傳應用程式設定的指引](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings)。

1. 將本地 Functions 應用程式部署到雲端。
> ⚠️ 您可以參考[第2個專案，第5課中有關部署您的 Functions 應用程式的指導說明](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud)，如有需要。
## 🚀 挑戰

GPS 數據並非完全準確，檢測到的位置可能會有幾米甚至更多的誤差，特別是在隧道和高樓林立的區域。

想一想衛星導航如何克服這個問題？您的衛星導航擁有哪些數據可以幫助它更準確地預測您的位置？

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## 回顧與自學

* 閱讀 [維基百科上的數據模型頁面](https://wikipedia.org/wiki/Data_model) 了解結構化數據
* 閱讀 [維基百科上的半結構化數據頁面](https://wikipedia.org/wiki/Semi-structured_data) 了解半結構化數據
* 閱讀 [維基百科上的非結構化數據頁面](https://wikipedia.org/wiki/Unstructured_data) 了解非結構化數據
* 閱讀 [Azure 儲存體文件](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn) 了解 Azure 儲存體及其不同的儲存類型

## 作業

[調查函數綁定](assignment.md)

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解讀概不負責。