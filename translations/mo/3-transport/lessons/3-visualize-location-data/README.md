<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9095c61445c2bca7245ef9b59a186a11",
  "translation_date": "2025-08-27T00:55:35+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/README.md",
  "language_code": "mo"
}
-->
# 視覺化位置數據

![本課程的手繪筆記概述](../../../../../translated_images/lesson-13.a259db1485021be7d7c72e90842fbe0ab977529e8684c179b5fb1ea75e92b3ef.mo.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大版本。

這段影片概述了 Azure Maps 與 IoT 的功能，這是本課程將涵蓋的服務。

[![Azure Maps - 微軟 Azure 企業位置平台](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 點擊上方圖片觀看影片

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## 簡介

在上一課中，您學習了如何從感測器獲取 GPS 數據並使用無伺服器代碼將其保存到雲端的存儲容器中。現在，您將探索如何在 Azure 地圖上視覺化這些點。您將學習如何在網頁上創建地圖，了解 GeoJSON 數據格式以及如何使用它在地圖上繪製所有捕獲的 GPS 點。

在本課程中，我們將涵蓋：

* [什麼是數據視覺化](../../../../../3-transport/lessons/3-visualize-location-data)
* [地圖服務](../../../../../3-transport/lessons/3-visualize-location-data)
* [創建 Azure Maps 資源](../../../../../3-transport/lessons/3-visualize-location-data)
* [在網頁上顯示地圖](../../../../../3-transport/lessons/3-visualize-location-data)
* [GeoJSON 格式](../../../../../3-transport/lessons/3-visualize-location-data)
* [使用 GeoJSON 在地圖上繪製 GPS 數據](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 本課程將涉及少量 HTML 和 JavaScript。如果您想了解更多關於使用 HTML 和 JavaScript 進行網頁開發的內容，請查看 [Web development for beginners](https://github.com/microsoft/Web-Dev-For-Beginners)。

## 什麼是數據視覺化

數據視覺化，顧名思義，是以更容易讓人類理解的方式來視覺化數據。它通常與圖表和圖形相關，但任何以圖像方式呈現數據以幫助人類更好地理解數據並做出決策的方式都屬於數據視覺化。

舉個簡單的例子——在農場項目中，您捕獲了土壤濕度的數據。以下是 2021 年 6 月 1 日每小時捕獲的土壤濕度數據表：

| 日期             | 讀數   |
| ---------------- | ------: |
| 01/06/2021 00:00 |     257 |
| 01/06/2021 01:00 |     268 |
| 01/06/2021 02:00 |     295 |
| 01/06/2021 03:00 |     305 |
| 01/06/2021 04:00 |     325 |
| 01/06/2021 05:00 |     359 |
| 01/06/2021 06:00 |     398 |
| 01/06/2021 07:00 |     410 |
| 01/06/2021 08:00 |     429 |
| 01/06/2021 09:00 |     451 |
| 01/06/2021 10:00 |     460 |
| 01/06/2021 11:00 |     452 |
| 01/06/2021 12:00 |     420 |
| 01/06/2021 13:00 |     408 |
| 01/06/2021 14:00 |     431 |
| 01/06/2021 15:00 |     462 |
| 01/06/2021 16:00 |     432 |
| 01/06/2021 17:00 |     402 |
| 01/06/2021 18:00 |     387 |
| 01/06/2021 19:00 |     360 |
| 01/06/2021 20:00 |     358 |
| 01/06/2021 21:00 |     354 |
| 01/06/2021 22:00 |     356 |
| 01/06/2021 23:00 |     362 |

對於人類來說，理解這些數據可能很困難。這是一堵沒有意義的數字牆。作為視覺化這些數據的第一步，可以將其繪製成折線圖：

![上述數據的折線圖](../../../../../translated_images/chart-soil-moisture.fd6d9d0cdc0b5f75e78038ecb8945dfc84b38851359de99d84b16e3336d6d7c2.mo.png)

這可以進一步改進，添加一條線來指示自動灌溉系統在土壤濕度讀數達到 450 時啟動的時間：

![土壤濕度折線圖，顯示 450 的一條線](../../../../../translated_images/chart-soil-moisture-relay.fbb391236d34a64d0abf1df396e9197e0a24df14150620b9cc820a64a55c9326.mo.png)

這張圖表不僅快速顯示了土壤濕度水平，還顯示了灌溉系統啟動的點。

圖表並不是唯一的數據視覺化工具。追蹤天氣的 IoT 設備可以通過網頁應用或移動應用使用符號來視覺化天氣條件，例如用雲朵符號表示陰天，用雨雲符號表示雨天等等。視覺化數據的方法有很多，有些是嚴肅的，有些是有趣的。

✅ 想一想您曾經見過的數據視覺化方式。哪些方法最清晰，能讓您最快做出決策？

最好的視覺化方式能讓人類快速做出決策。例如，展示工業機械所有讀數的儀表牆可能很難處理，但當某些事情出錯時，閃爍的紅燈能讓人類迅速做出決策。有時候，最好的視覺化方式就是一盞閃爍的燈！

在處理 GPS 數據時，最清晰的視覺化方式是將數據繪製在地圖上。例如，顯示送貨卡車的地圖可以幫助加工廠的工人了解卡車何時到達。如果這張地圖不僅顯示卡車當前位置的圖片，還提供卡車內容的概念，那麼加工廠的工人就可以相應地進行計劃——如果他們看到一輛冷藏卡車接近，他們就知道要準備冷藏空間。

## 地圖服務

使用地圖是一項有趣的練習，有許多選擇，例如 Bing Maps、Leaflet、Open Street Maps 和 Google Maps。在本課程中，您將了解 [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) 以及如何使用它們顯示您的 GPS 數據。

![Azure Maps 標誌](../../../../../translated_images/azure-maps-logo.35d01dcfbd81fe6140e94257aaa1538f785a58c91576d14e0ebe7a2f6c694b99.mo.png)

Azure Maps 是“一組地理空間服務和 SDK，使用最新的地圖數據為網頁和移動應用提供地理背景。”開發者可以使用工具創建美觀的互動地圖，這些地圖可以提供推薦的交通路線、交通事故信息、室內導航、搜索功能、海拔信息、天氣服務等。

✅ 試試一些 [地圖代碼範例](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)

您可以將地圖顯示為空白畫布、瓦片、衛星圖像、疊加道路的衛星圖像、各種灰度地圖、顯示海拔的陰影地圖、夜景地圖以及高對比度地圖。通過與 [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn) 集成，您可以在地圖上獲得實時更新。您可以啟用各種控制來控制地圖的行為和外觀，使地圖能夠對事件（如捏合、拖動和點擊）做出反應。為了控制地圖的外觀，您可以添加包括氣泡、線條、多邊形、熱圖等的圖層。您選擇的 SDK 決定了您實現的地圖樣式。

您可以通過使用其 [REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest)、其 [Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn) 或者如果您正在構建移動應用，則使用其 [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android) 來訪問 Azure Maps API。

在本課程中，您將使用 Web SDK 繪製地圖並顯示感測器的 GPS 位置路徑。

## 創建 Azure Maps 資源

第一步是創建 Azure Maps 帳戶。

### 任務 - 創建 Azure Maps 資源

1. 從終端或命令提示符運行以下命令，在您的 `gps-sensor` 資源組中創建 Azure Maps 資源：

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    這將創建一個名為 `gps-sensor` 的 Azure Maps 資源。使用的層級是 `S1`，這是一個付費層級，包含一系列功能，但提供了大量免費的調用。

    > 💁 要查看使用 Azure Maps 的成本，請查看 [Azure Maps 價格頁面](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn)。

1. 您需要獲取地圖資源的 API 密鑰。使用以下命令獲取此密鑰：

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    複製 `PrimaryKey` 的值。

## 在網頁上顯示地圖

現在您可以進行下一步，將地圖顯示在網頁上。我們將僅使用一個 `html` 文件來構建您的小型網頁應用；請記住，在生產或團隊環境中，您的網頁應用可能會有更多的組件！

### 任務 - 在網頁上顯示地圖

1. 在本地電腦的某個文件夾中創建一個名為 index.html 的文件。添加 HTML 標記以容納地圖：

    ```html
    <html>
    <head>
        <style>
            #myMap {
                width:100%;
                height:100%;
            }
        </style>
    </head>
    
    <body onload="init()">
        <div id="myMap"></div>
    </body>
    </html>
    ```

    地圖將加載到 `myMap` 的 `div` 中。一些樣式使其可以跨越頁面的寬度和高度。

    > 🎓 `div` 是網頁的一個部分，可以命名和設置樣式。

1. 在開頭的 `<head>` 標籤下，添加一個外部樣式表來控制地圖顯示，以及一個來自 Web SDK 的外部腳本來管理其行為：

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    此樣式表包含地圖外觀的設置，而腳本文件包含加載地圖的代碼。添加此代碼類似於包含 C++ 頭文件或導入 Python 模塊。

1. 在該腳本下方，添加一個腳本塊以啟動地圖。

    ```javascript
    <script type='text/javascript'>
        function init() {
            var map = new atlas.Map('myMap', {
                center: [-122.26473, 47.73444],
                zoom: 12,
                authOptions: {
                    authType: "subscriptionKey",
                    subscriptionKey: "<subscription_key>",

                }
            });
        }
    </script>
    ```

    將 `<subscription_key>` 替換為您的 Azure Maps 帳戶的 API 密鑰。

    如果您在網頁瀏覽器中打開 `index.html` 文件，您應該會看到一張地圖加載並聚焦在西雅圖地區。

    ![顯示西雅圖（美國華盛頓州的一個城市）的地圖](../../../../../translated_images/map-image.8fb2c53eb23ef39c1c0a4410a5282e879b3b452b707eb066ff04c5488d3d72b7.mo.png)

    ✅ 嘗試調整縮放和中心參數以更改地圖顯示。您可以添加與數據的緯度和經度相對應的不同坐標來重新定位地圖。

> 💁 在本地工作網頁應用的更好方式是安裝 [http-server](https://www.npmjs.com/package/http-server)。您需要先安裝 [node.js](https://nodejs.org/) 和 [npm](https://www.npmjs.com/) 才能使用此工具。安裝這些工具後，您可以導航到 `index.html` 文件所在的位置並輸入 `http-server`。網頁應用將在本地網頁伺服器上打開 [http://127.0.0.1:8080/](http://127.0.0.1:8080/)。

## GeoJSON 格式

現在您已經設置了顯示地圖的網頁應用，接下來需要從存儲帳戶中提取 GPS 數據並在地圖上顯示一層標記。在此之前，我們先來了解 Azure Maps 所需的 [GeoJSON](https://wikipedia.org/wiki/GeoJSON) 格式。

[GeoJSON](https://geojson.org/) 是一種開放標準的 JSON 規範，具有專門設計用於處理地理相關數據的特殊格式。您可以通過測試示例數據來了解它，使用 [geojson.io](https://geojson.io) 也是一個調試 GeoJSON 文件的有用工具。

示例 GeoJSON 數據如下所示：

```json
{
  "type": "FeatureCollection",
  "features": [
    {
      "type": "Feature",
      "geometry": {
        "type": "Point",
        "coordinates": [
          -2.10237979888916,
          57.164918677004714
        ]
      }
    }
  ]
}
```

特別需要注意的是數據如何嵌套在 `FeatureCollection` 中的 `Feature`。在該對象中可以找到 `geometry`，其中的 `coordinates` 指示緯度和經度。

✅ 在構建您的 GeoJSON 時，請注意對象中 `latitude` 和 `longitude` 的順序，否則您的點將不會出現在正確的位置！GeoJSON 期望點的數據順序為 `lon,lat`，而不是 `lat,lon`。

`Geometry` 可以有不同的類型，例如單個點或多邊形。在此示例中，它是一個點，指定了兩個坐標：經度和緯度。
✅ Azure Maps 支援標準的 GeoJSON，並且包含一些[增強功能](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn)，例如繪製圓形和其他幾何圖形的能力。

## 使用 GeoJSON 在地圖上繪製 GPS 數據

現在你已準備好使用上一課中建立的儲存資料。提醒一下，這些資料以多個檔案的形式存儲在 Blob 儲存中，因此你需要檢索這些檔案並解析它們，以便 Azure Maps 能夠使用這些數據。

### 任務 - 配置儲存以便從網頁訪問

如果你嘗試從儲存中調用數據，你可能會驚訝地發現瀏覽器的控制台中出現錯誤。這是因為你需要在此儲存上設置 [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) 權限，以允許外部網頁應用程式讀取其數據。

> 🎓 CORS 代表 "跨來源資源共享"，通常需要在 Azure 中明確設置以確保安全性。它可以防止未預期的網站訪問你的數據。

1. 執行以下命令以啟用 CORS：

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    將 `<storage_name>` 替換為你的儲存帳戶名稱。將 `<key1>` 替換為你的儲存帳戶的帳戶金鑰。

    此命令允許任何網站（通配符 `*` 表示任何網站）發出 *GET* 請求，也就是從你的儲存帳戶獲取數據。`--services b` 表示僅對 Blob 應用此設置。

### 任務 - 從儲存中加載 GPS 數據

1. 將 `init` 函數的全部內容替換為以下代碼：

    ```javascript
    fetch("https://<storage_name>.blob.core.windows.net/gps-data/?restype=container&comp=list")
        .then(response => response.text())
        .then(str => new window.DOMParser().parseFromString(str, "text/xml"))
        .then(xml => {
            let blobList = Array.from(xml.querySelectorAll("Url"));
                blobList.forEach(async blobUrl => {
                    loadJSON(blobUrl.innerHTML)                
        });
    })
    .then( response => {
        map = new atlas.Map('myMap', {
            center: [-122.26473, 47.73444],
            zoom: 14,
            authOptions: {
                authType: "subscriptionKey",
                subscriptionKey: "<subscription_key>",
    
            }
        });
        map.events.add('ready', function () {
            var source = new atlas.source.DataSource();
            map.sources.add(source);
            map.layers.add(new atlas.layer.BubbleLayer(source));
            source.add(features);
        })
    })
    ```

    將 `<storage_name>` 替換為你的儲存帳戶名稱。將 `<subscription_key>` 替換為你的 Azure Maps 帳戶的 API 金鑰。

    這裡有幾個步驟。首先，代碼通過使用你的儲存帳戶名稱構建的 URL 端點從 Blob 容器中檢索 GPS 數據。此 URL 從 `gps-data` 中檢索，表示資源類型為容器（`restype=container`），並列出所有 Blob 的信息。此列表不會返回 Blob 本身，但會返回每個 Blob 的 URL，可用於加載 Blob 數據。

    > 💁 你可以將此 URL 放入瀏覽器中查看容器中所有 Blob 的詳細信息。每個項目都會有一個 `Url` 屬性，你也可以在瀏覽器中加載該屬性以查看 Blob 的內容。

    然後，代碼加載每個 Blob，調用 `loadJSON` 函數（稍後會創建）。接著，它創建地圖控制項，並添加代碼到 `ready` 事件。此事件在地圖顯示於網頁時被調用。

    `ready` 事件創建了一個 Azure Maps 數據源——一個包含 GeoJSON 數據的容器，稍後會填充此數據源。然後此數據源用於創建一個氣泡圖層——即地圖上的一組圓形，圓心位於 GeoJSON 中的每個點。

1. 在 `init` 函數下方的腳本塊中添加 `loadJSON` 函數：

    ```javascript
    var map, features;

    function loadJSON(file) {
        var xhr = new XMLHttpRequest();
        features = [];
        xhr.onreadystatechange = function () {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status === 200) {
                    gps = JSON.parse(xhr.responseText)
                    features.push(
                        new atlas.data.Feature(new atlas.data.Point([parseFloat(gps.gps.lon), parseFloat(gps.gps.lat)]))
                    )
                }
            }
        };
        xhr.open("GET", file, true);
        xhr.send();
    }    
    ```

    此函數由 fetch 例程調用，用於解析 JSON 數據並將其轉換為經緯度座標作為 GeoJSON。
    解析完成後，數據被設置為 GeoJSON 的 `Feature`。地圖將被初始化，並且小圓點會出現在你的數據所繪製的路徑周圍：

1. 在瀏覽器中加載 HTML 頁面。它將加載地圖，然後從儲存中加載所有 GPS 數據並將其繪製在地圖上。

    ![西雅圖附近的聖愛德華州立公園地圖，顯示公園邊緣路徑上的圓形](../../../../../translated_images/map-path.896832e72dc696ffe20650e4051027d4855442d955f93fdbb80bb417ca8a406f.mo.png)

> 💁 你可以在 [code](../../../../../3-transport/lessons/3-visualize-location-data/code) 資料夾中找到此代碼。

---

## 🚀 挑戰

能夠在地圖上顯示靜態數據作為標記非常棒。你能否增強此網頁應用程式，添加動畫並顯示標記隨時間移動的路徑，使用帶有時間戳的 JSON 文件？這裡有一些[範例](https://azuremapscodesamples.azurewebsites.net/)展示如何在地圖中使用動畫。

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## 回顧與自學

Azure Maps 對於處理 IoT 設備特別有用。

* 在 [Microsoft Docs 的 Azure Maps 文件](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn) 中研究一些用途。
* 通過 [Microsoft Learn 上的 Azure Maps 自學模組](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn)，加深你對地圖製作和航點的知識。

## 作業

[部署你的應用程式](assignment.md)

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。