<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "078ae664c7b686bf069545e9a5fc95b2",
  "translation_date": "2025-08-25T00:37:24+00:00",
  "source_file": "3-transport/lessons/4-geofences/README.md",
  "language_code": "tw"
}
-->
# 地理圍欄

![本課程的手繪筆記概述](../../../../../translated_images/lesson-14.63980c5150ae3c153e770fb71d044c1845dce79248d86bed9fc525adf3ede73c.tw.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大版本。

這段影片概述了地理圍欄以及如何在 Azure Maps 中使用它們，這些是本課程將涵蓋的主題：

[![Microsoft Developer IoT 節目中的 Azure Maps 地理圍欄](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 點擊上方圖片觀看影片

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## 簡介

在過去的三節課中，您已使用物聯網技術定位從農場運送到加工中心的卡車。您捕獲了 GPS 數據，將其發送到雲端存儲，並在地圖上進行可視化。提高供應鏈效率的下一步是當卡車即將到達加工中心時收到警報，這樣卸貨所需的工作人員就可以準備好叉車和其他設備，確保車輛一到就能快速卸貨。這樣可以減少卡車和司機的等待時間。

在本課程中，您將學習地理圍欄——定義的地理空間區域，例如加工中心周圍 2 公里車程範圍內的區域，以及如何測試 GPS 坐標是否在地理圍欄內或外，以便判斷您的 GPS 傳感器是否已進入或離開某個區域。

本課程將涵蓋以下內容：

* [什麼是地理圍欄](../../../../../3-transport/lessons/4-geofences)
* [定義地理圍欄](../../../../../3-transport/lessons/4-geofences)
* [測試點是否在地理圍欄內](../../../../../3-transport/lessons/4-geofences)
* [從無伺服器代碼中使用地理圍欄](../../../../../3-transport/lessons/4-geofences)

> 🗑 這是本專案的最後一課，因此完成本課程和作業後，請記得清理您的雲端服務。您需要這些服務來完成作業，因此請確保先完成作業。
>
> 如有需要，請參考[清理專案指南](../../../clean-up.md)以獲取相關指示。

## 什麼是地理圍欄

地理圍欄是一個虛擬的邊界，用於真實世界的地理區域。地理圍欄可以是以點和半徑定義的圓形（例如建築物周圍 100 米的圓形），或者是覆蓋某個區域的多邊形，例如學校區域、城市邊界或大學或辦公園區。

![一些地理圍欄的例子，顯示 Microsoft 公司商店周圍的圓形地理圍欄，以及 Microsoft 西園區周圍的多邊形地理圍欄](../../../../../translated_images/geofence-examples.172fbc534665769f6e1a1ddcf75e3b25183cd10354c80cc603ba44b635390e1a.tw.png)

> 💁 您可能已經在不知情的情況下使用過地理圍欄。如果您曾使用 iOS 提醒應用程式或 Google Keep 根據位置設置提醒，那麼您就使用了地理圍欄。這些應用程式會根據提供的位置設置地理圍欄，並在您的手機進入地理圍欄時提醒您。

以下是您可能需要知道車輛是否在地理圍欄內或外的幾個原因：

* **卸貨準備** - 收到車輛到達現場的通知可以讓工作人員準備卸貨，減少車輛等待時間。這可以讓司機在一天內完成更多次的交付，減少等待時間。
* **稅務合規** - 某些國家（例如紐西蘭）根據車輛重量僅在公共道路上行駛時徵收柴油車輛的道路稅。使用地理圍欄可以追蹤車輛在公共道路上行駛的里程，而不是在農場或伐木區等私人道路上行駛的里程。
* **盜竊監控** - 如果車輛應該僅停留在某個區域（例如農場），但離開了地理圍欄，則可能是被盜。
* **位置合規** - 工作場地、農場或工廠的某些區域可能禁止某些車輛進入，例如將運送人工肥料和農藥的車輛遠離種植有機農產品的田地。如果進入地理圍欄，則車輛處於不合規狀態，司機可以收到通知。

✅ 您能想到其他地理圍欄的用途嗎？

Azure Maps（您在上一課中用於可視化 GPS 數據的服務）允許您定義地理圍欄，然後測試某個點是否在地理圍欄內或外。

## 定義地理圍欄

地理圍欄使用 GeoJSON 定義，與上一課中添加到地圖上的點相同。在這種情況下，它不是包含 `Point` 值的 `FeatureCollection`，而是包含 `Polygon` 的 `FeatureCollection`。

```json
{
   "type": "FeatureCollection",
   "features": [
     {
       "type": "Feature",
       "geometry": {
         "type": "Polygon",
         "coordinates": [
           [
             [
               -122.13393688201903,
               47.63829579223815
             ],
             [
               -122.13389128446579,
               47.63782047131512
             ],
             [
               -122.13240802288054,
               47.63783312249837
             ],
             [
               -122.13238388299942,
               47.63829037035086
             ],
             [
               -122.13393688201903,
               47.63829579223815
             ]
           ]
         ]
       },
       "properties": {
         "geometryId": "1"
       }
     }
   ]
}
```

多邊形上的每個點都定義為一個經度和緯度的配對，並以數組的形式表示，這些點的數組設置為 `coordinates`。在上一課中的 `Point` 中，`coordinates` 是包含兩個值（緯度和經度）的數組，而在 `Polygon` 中，它是一個包含多個數組的數組，每個數組包含兩個值（經度和緯度）。

> 💁 請記住，GeoJSON 使用 `經度, 緯度` 表示點，而不是 `緯度, 經度`

多邊形的坐標數組總是比多邊形上的點數多一個，最後一個條目與第一個條目相同，用於閉合多邊形。例如，對於矩形，會有 5 個點。

![一個矩形及其坐標](../../../../../translated_images/polygon-points.302193da381cb415.tw.png)

在上圖中，有一個矩形。多邊形坐標從左上角的 47,-122 開始，然後向右移動到 47,-121，再向下移動到 46,-121，然後向左移動到 46,-122，最後回到起始點 47,-122。這樣多邊形就有 5 個點——左上角、右上角、右下角、左下角，然後是左上角以閉合多邊形。

✅ 嘗試使用 [GeoJSON.io](https://geojson.io/) 等工具創建一個圍繞您家或學校的 GeoJSON 多邊形。

### 任務 - 定義地理圍欄

要在 Azure Maps 中使用地理圍欄，首先需要將其上傳到您的 Azure Maps 帳戶。一旦上傳，您將獲得一個唯一的 ID，您可以使用該 ID 測試某個點是否在地理圍欄內。要將地理圍欄上傳到 Azure Maps，您需要使用地圖 Web API。您可以使用名為 [curl](https://curl.se) 的工具調用 Azure Maps Web API。

> 🎓 Curl 是一個命令行工具，用於對 Web 端點發出請求

1. 如果您使用的是 Linux、macOS 或 Windows 10 的最新版本，您可能已經安裝了 curl。從終端或命令行運行以下命令進行檢查：

    ```sh
    curl --version
    ```

    如果未顯示 curl 的版本信息，您需要從 [curl 下載頁面](https://curl.se/download.html) 安裝它。

    > 💁 如果您熟悉 Postman，您也可以選擇使用它。

1. 創建一個包含多邊形的 GeoJSON 文件。您將使用您的 GPS 傳感器測試此文件，因此請在您的當前位置周圍創建一個多邊形。您可以手動編輯上面提供的 GeoJSON 示例來創建，也可以使用 [GeoJSON.io](https://geojson.io) 等工具。

    GeoJSON 需要包含一個 `FeatureCollection`，其中包含一個 `geometry` 類型為 `Polygon` 的 `Feature`。

    您**必須**在與 `geometry` 元素同一層級添加一個 `properties` 元素，並且該元素必須包含一個 `geometryId`：

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    如果您使用 [GeoJSON.io](https://geojson.io)，則需要手動將此項目添加到空的 `properties` 元素中，可以在下載 JSON 文件後添加，也可以在應用程式的 JSON 編輯器中添加。

    此 `geometryId` 必須在此文件中唯一。您可以在同一 GeoJSON 文件中的 `FeatureCollection` 中上傳多個地理圍欄作為多個 `Feature`，只要每個地理圍欄具有不同的 `geometryId`。如果多邊形是從不同的文件在不同的時間上傳的，它們可以具有相同的 `geometryId`。

1. 將此文件保存為 `geofence.json`，並在終端或控制台中導航到保存位置。

1. 運行以下 curl 命令以創建地理圍欄：

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    將 URL 中的 `<subscription_key>` 替換為您的 Azure Maps 帳戶的 API 密鑰。

    該 URL 用於通過 `https://atlas.microsoft.com/mapData/upload` API 上傳地圖數據。調用包括一個 `api-version` 參數，用於指定使用哪個 Azure Maps API，這是為了允許 API 隨時間變化但保持向後兼容。上傳的數據格式設置為 `geojson`。

    此命令將向上傳 API 發出 POST 請求，並返回一系列響應標頭，其中包括名為 `location` 的標頭。

    ```output
    content-type: application/json
    location: https://us.atlas.microsoft.com/mapData/operations/1560ced6-3a80-46f2-84b2-5b1531820eab?api-version=1.0
    x-ms-azuremaps-region: West US 2
    x-content-type-options: nosniff
    strict-transport-security: max-age=31536000; includeSubDomains
    x-cache: CONFIG_NOCACHE
    date: Sat, 22 May 2021 21:34:57 GMT
    content-length: 0
    ```

    > 🎓 在調用 Web 端點時，您可以通過在 URL 後添加 `?`，然後以 `key=value` 的形式添加鍵值對，並用 `&` 分隔鍵值對來傳遞參數。

1. Azure Maps 不會立即處理此請求，因此您需要使用 `location` 標頭中提供的 URL 檢查上傳請求是否已完成。通過向該 URL 發出 GET 請求來查看狀態。您需要在 `location` URL 的末尾添加您的訂閱密鑰，方法是添加 `&subscription-key=<subscription_key>`，並將 `<subscription_key>` 替換為您的 Azure Maps 帳戶的 API 密鑰。運行以下命令：

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    將 `<location>` 替換為 `location` 標頭的值，並將 `<subscription_key>` 替換為您的 Azure Maps 帳戶的 API 密鑰。

1. 檢查響應中的 `status` 值。如果不是 `Succeeded`，請等待一分鐘後再試。

1. 一旦狀態返回為 `Succeeded`，查看響應中的 `resourceLocation`。這包含 GeoJSON 對象的唯一 ID（稱為 UDID）的詳細信息。UDID 是 `metadata/` 之後的值，不包括 `api-version`。例如，如果 `resourceLocation` 是：

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    那麼 UDID 將是 `7c3776eb-da87-4c52-ae83-caadf980323a`。

    保存此 UDID，因為您將需要它來測試地理圍欄。

## 測試點是否在地理圍欄內

一旦多邊形上傳到 Azure Maps，您可以測試某個點是否在地理圍欄內或外。您可以通過發出 Web API 請求，傳遞地理圍欄的 UDID，以及要測試的點的緯度和經度來完成此操作。

在發出此請求時，您還可以傳遞一個名為 `searchBuffer` 的值。這告訴 Maps API 返回結果時的精確度。原因是 GPS 並不完全準確，有時位置可能會偏差幾米甚至更多。`searchBuffer` 的默認值為 50 米，但您可以設置 0 米到 500 米之間的值。

當 API 調用返回結果時，結果的一部分是測量到地理圍欄邊緣最近點的 `distance`，如果點在地理圍欄外則為正值，若在地理圍欄內則為負值。如果此距離小於 `searchBuffer`，則返回實際距離（以米為單位），否則值為 999 或 -999。999 表示該點距地理圍欄超過 `searchBuffer`，-999 表示該點距地理圍欄內超過 `searchBuffer`。

![地理圍欄及其周圍 50 米的搜索緩衝區](../../../../../translated_images/search-buffer-and-distance.e6a79af3898183c7.tw.png)

在上圖中，地理圍欄有一個 50 米的搜索緩衝區。

* 地理圍欄中心的一個點，遠遠在搜索緩衝區內，距離為 **-999**
* 一個遠遠在搜索緩衝區外的點，距離為 **999**
* 一個在地理圍欄內且在搜索緩衝區內的點，距地理圍欄 6 米，距離為 **6 米**
* 一個在地理圍欄外且在搜索緩衝區內的點，距地理圍欄 39 米，距離為 **39 米**

了解到地理圍欄邊緣的距離並結合其他信息（例如其他 GPS 讀數、速度和道路數據）在基於車輛位置做出決策時非常重要。

例如，假設 GPS 讀數顯示車輛沿著一條道路行駛，該道路最終與地理圍欄相鄰。如果單個 GPS 值不準確並將車輛定位在地理圍欄內，儘管沒有車輛通行的入口，那麼可以忽略該值。

![GPS 路徑顯示車輛沿著 520 公路經過 Microsoft 園區，GPS 讀數沿著道路分佈，除了其中一個在園區內，位於地理圍欄內](../../../../../translated_images/geofence-crossing-inaccurate-gps.6a3ed911202ad9cabb66d3964888cec03a42c61d5b8f536ad5bdc99716b370f5.tw.png)
在上圖中，有一個地理圍欄覆蓋了部分 Microsoft 校園。紅線顯示了一輛卡車沿著 520 行駛，圓圈表示 GPS 讀數。大多數讀數是準確的，並且位於 520 上，但有一個不準確的讀數出現在地理圍欄內。這個讀數不可能是正確的——卡車不可能突然從 520 偏離進入校園，然後再回到 520。檢查地理圍欄的程式碼需要在執行地理圍欄測試結果之前考慮之前的讀數。

✅ 需要檢查哪些額外的數據來判斷 GPS 讀數是否可以被認為是正確的？

### 任務 - 測試點是否在地理圍欄內

1. 首先構建用於 Web API 查詢的 URL。格式如下：

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    將 `<subscription_key>` 替換為您的 Azure Maps 帳戶的 API 金鑰。

    將 `<UDID>` 替換為上一個任務中地理圍欄的 UDID。

    將 `<lat>` 和 `<lon>` 替換為您想要測試的緯度和經度。

    此 URL 使用 `https://atlas.microsoft.com/spatial/geofence/json` API 查詢使用 GeoJSON 定義的地理圍欄。它針對 `1.0` API 版本。`deviceId` 參數是必需的，應該是緯度和經度來源設備的名稱。

    預設的搜索緩衝區是 50 米，您可以通過傳遞額外的參數 `searchBuffer=<distance>` 來更改此值，將 `<distance>` 設置為以米為單位的搜索緩衝區距離，範圍為 0 到 500。

1. 使用 curl 對此 URL 發出 GET 請求：

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 如果您收到 `BadRequest` 的響應代碼，並出現以下錯誤：
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > 那麼您的 GeoJSON 缺少帶有 `geometryId` 的 `properties` 部分。您需要修復您的 GeoJSON，然後重複上述步驟重新上傳並獲取新的 UDID。

1. 響應將包含一個 `geometries` 列表，每個幾何體對應於用於創建地理圍欄的 GeoJSON 中定義的多邊形。每個幾何體有三個感興趣的字段：`distance`、`nearestLat` 和 `nearestLon`。

    ```output
    {
        "geometries": [
            {
                "deviceId": "gps-sensor",
                "udId": "7c3776eb-da87-4c52-ae83-caadf980323a",
                "geometryId": "1",
                "distance": 999.0,
                "nearestLat": 47.645875,
                "nearestLon": -122.142713
            }
        ],
        "expiredGeofenceGeometryId": [],
        "invalidPeriodGeofenceGeometryId": []
    }
    ```

    * `nearestLat` 和 `nearestLon` 是地理圍欄邊緣上最接近測試位置的點的緯度和經度。

    * `distance` 是測試位置到地理圍欄邊緣最近點的距離。負數表示在地理圍欄內，正數表示在外。此值將小於 50（預設搜索緩衝區）或 999。

1. 使用地理圍欄內部和外部的位置多次重複此操作。

## 從無伺服器代碼中使用地理圍欄

現在，您可以為 Functions 應用新增一個觸發器，以測試 IoT Hub GPS 事件數據是否符合地理圍欄。

### 消費者組

正如您在之前的課程中記得的，IoT Hub 允許您重播已接收但未處理的事件。但如果多個觸發器連接會發生什麼？它如何知道哪個觸發器處理了哪些事件？

答案是它無法知道！因此，您可以定義多個單獨的連接來讀取事件，每個連接可以管理未讀消息的重播。這些被稱為 *消費者組*。當您連接到端點時，可以指定要連接的消費者組。應用程式的每個組件將連接到不同的消費者組。

![一個 IoT Hub 與 3 個消費者組分發相同的消息到 3 個不同的 Functions 應用](../../../../../translated_images/consumer-groups.a3262e26fc27ba2092863678ad57af15c7223416e388a23f330c058cf4358630.tw.png)

理論上，每個消費者組最多可以連接 5 個應用程式，並且它們都會在消息到達時接收消息。最佳實踐是每個消費者組僅由一個應用程式訪問，以避免重複處理消息，並確保在重新啟動時所有排隊的消息都能正確處理。例如，如果您在本地啟動了 Functions 應用並同時在雲端運行，它們都會處理消息，導致存儲帳戶中存儲的 Blob 重複。

如果您查看之前課程中創建的 IoT Hub 觸發器的 `function.json` 文件，您將在事件中心觸發器綁定部分看到消費者組：

```json
"consumerGroup": "$Default"
```

當您創建 IoT Hub 時，系統會預設創建 `$Default` 消費者組。如果您想新增一個觸發器，可以使用新的消費者組來新增。

> 💁 在本課程中，您將使用與存儲 GPS 數據的觸發器不同的函數來測試地理圍欄。這是為了展示如何使用消費者組並分離代碼以使其更易於閱讀和理解。在生產應用程式中，您可能會以多種方式設計此功能——將兩者放在一個函數中，使用存儲帳戶上的觸發器運行函數來檢查地理圍欄，或使用多個函數。沒有“正確的方式”，這取決於您的應用程式和需求。

### 任務 - 創建一個新的消費者組

1. 運行以下命令為您的 IoT Hub 創建一個名為 `geofence` 的新消費者組：

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    將 `<hub_name>` 替換為您用於 IoT Hub 的名稱。

1. 如果您想查看 IoT Hub 的所有消費者組，請運行以下命令：

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    將 `<hub_name>` 替換為您用於 IoT Hub 的名稱。這將列出所有消費者組。

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 當您在之前的課程中運行 IoT Hub 事件監視器時，它連接到了 `$Default` 消費者組。這就是為什麼您無法同時運行事件監視器和事件觸發器。如果您想同時運行兩者，則可以為所有 Functions 應用使用其他消費者組，並將 `$Default` 保留給事件監視器。

### 任務 - 創建一個新的 IoT Hub 觸發器

1. 在您之前課程中創建的 `gps-trigger` Functions 應用中新增一個 IoT Hub 事件觸發器。將此函數命名為 `geofence-trigger`。

    > ⚠️ 如果需要，您可以參考[項目 2，第 5 課中創建 IoT Hub 事件觸發器的指導](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger)。

1. 在 `function.json` 文件中配置 IoT Hub 連接字串。`local.settings.json` 在 Functions 應用中的所有觸發器之間共享。

1. 更新 `function.json` 文件中 `consumerGroup` 的值，以引用新的 `geofence` 消費者組：

    ```json
    "consumerGroup": "geofence"
    ```

1. 您需要在此觸發器中使用 Azure Maps 帳戶的訂閱金鑰，因此在 `local.settings.json` 文件中新增一個名為 `MAPS_KEY` 的條目。

1. 運行 Functions 應用以確保它正在連接並處理消息。之前課程中的 `iot-hub-trigger` 也將運行並將 Blob 上傳到存儲。

    > 為了避免在 Blob 存儲中重複 GPS 讀數，您可以停止在雲端運行的 Functions 應用。為此，請使用以下命令：
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > 將 `<functions_app_name>` 替換為您用於 Functions 應用的名稱。
    >
    > 您可以稍後使用以下命令重新啟動它：
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > 將 `<functions_app_name>` 替換為您用於 Functions 應用的名稱。

### 任務 - 從觸發器測試地理圍欄

在本課程的早些時候，您使用 curl 查詢地理圍欄以查看某個點是否位於內部或外部。您可以從觸發器內部發出類似的 Web 請求。

1. 要查詢地理圍欄，您需要其 UDID。在 `local.settings.json` 文件中新增一個名為 `GEOFENCE_UDID` 的條目，並填入此值。

1. 打開新觸發器 `geofence-trigger` 的 `__init__.py` 文件。

1. 在文件頂部新增以下導入：

    ```python
    import json
    import os
    import requests
    ```

    `requests` 套件允許您發出 Web API 調用。Azure Maps 沒有 Python SDK，您需要通過 Web API 調用來從 Python 代碼中使用它。

1. 在 `main` 方法的開頭新增以下兩行以獲取 Maps 訂閱金鑰：

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. 在 `for event in events` 迴圈內，新增以下代碼以從每個事件中獲取緯度和經度：

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    此代碼將事件主體中的 JSON 轉換為字典，然後從 `gps` 字段中提取 `lat` 和 `lon`。

1. 使用 `requests` 時，與使用 curl 構建長 URL 不同，您可以僅使用 URL 部分並將參數作為字典傳遞。新增以下代碼以定義要調用的 URL 並配置參數：

    ```python
    url = 'https://atlas.microsoft.com/spatial/geofence/json'

    params = {
        'api-version': 1.0,
        'deviceId': 'gps-sensor',
        'subscription-key': maps_key,
        'udid' : geofence_udid,
        'lat' : lat,
        'lon' : lon
    }
    ```

    `params` 字典中的項目將與您通過 curl 調用 Web API 時使用的鍵值對匹配。

1. 新增以下代碼以調用 Web API：

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    這將使用參數調用 URL，並返回一個響應對象。

1. 在此代碼下方新增以下代碼：

    ```python
    distance = response_body['geometries'][0]['distance']

    if distance == 999:
        logging.info('Point is outside geofence')
    elif distance > 0:
        logging.info(f'Point is just outside geofence by a distance of {distance}m')
    elif distance == -999:
        logging.info(f'Point is inside geofence')
    else:
        logging.info(f'Point is just inside geofence by a distance of {distance}m')
    ```

    此代碼假設只有一個幾何體，並從該幾何體中提取距離。然後根據距離記錄不同的消息。

1. 運行此代碼。您將在日誌輸出中看到 GPS 坐標是否在地理圍欄內，或者如果點在 50 米內，則顯示距離。使用基於 GPS 傳感器位置的不同地理圍欄嘗試此代碼，嘗試移動傳感器（例如通過手機的 WiFi 共享，或使用虛擬 IoT 設備上的不同坐標）以查看此變化。

1. 當您準備好時，將此代碼部署到雲端的 Functions 應用中。不要忘記部署新的應用程式設置。

    > ⚠️ 如果需要，您可以參考[項目 2，第 5 課中上傳應用程式設置的指導](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings)。

    > ⚠️ 如果需要，您可以參考[項目 2，第 5 課中部署 Functions 應用的指導](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud)。

> 💁 您可以在 [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions) 文件夾中找到此代碼。

---

## 🚀 挑戰

在本課程中，您使用帶有單個多邊形的 GeoJSON 文件新增了一個地理圍欄。您可以同時上傳多個多邊形，只要它們在 `properties` 部分中具有不同的 `geometryId` 值。

嘗試上傳包含多個多邊形的 GeoJSON 文件，並調整您的代碼以找到 GPS 坐標最接近或位於其中的多邊形。

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## 回顧與自學

* 在 [Wikipedia 的地理圍欄頁面](https://en.wikipedia.org/wiki/Geo-fence) 上閱讀更多關於地理圍欄及其一些使用案例的內容。
* 在 [Microsoft Azure Maps Spatial - Get Geofence 文檔](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn) 上閱讀更多關於 Azure Maps 地理圍欄 API 的內容。
* 在 [Microsoft Docs 上的 Azure Event Hubs 功能和術語 - 事件消費者文檔](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers) 中閱讀更多關於消費者組的內容。

## 作業

[使用 Twilio 發送通知](assignment.md)

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤讀概不負責。