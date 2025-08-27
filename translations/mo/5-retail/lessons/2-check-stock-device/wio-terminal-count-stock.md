<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-26T21:34:04+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "mo"
}
-->
# 從您的 IoT 設備計算庫存 - Wio Terminal

結合預測結果和其邊界框，可以用來計算圖像中的庫存數量。

## 計算庫存

![4 罐番茄醬，每罐周圍都有邊界框](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f1271828d3be412671d950e87625c5597ea97c90f11e01097.mo.jpg)

在上圖中，邊界框之間有些微重疊。如果這種重疊程度更大，邊界框可能會表示同一個物體。為了正確計算物體數量，您需要忽略那些有顯著重疊的框。

### 任務 - 忽略重疊計算庫存

1. 如果尚未打開您的 `stock-counter` 專案，請將其打開。

1. 在 `processPredictions` 函數的上方，新增以下程式碼：

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    這段程式碼定義了邊界框被認為是同一物體之前允許的重疊百分比。0.20 表示 20% 的重疊。

1. 在此程式碼下方，`processPredictions` 函數的上方，新增以下程式碼以計算兩個矩形的重疊區域：

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    這段程式碼定義了一個 `Point` 結構來存儲圖像上的點，以及一個 `Rect` 結構來使用左上角和右下角座標定義矩形。接著，它定義了一個 `area` 函數，該函數根據左上角和右下角座標計算矩形的面積。

    然後，它定義了一個 `overlappingArea` 函數，用於計算兩個矩形的重疊區域。如果它們沒有重疊，則返回 0。

1. 在 `overlappingArea` 函數的下方，宣告一個函數以將邊界框轉換為 `Rect`：

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    這段程式碼從物體檢測器的預測中提取邊界框，並使用邊界框上的值來定義矩形。右側是由左側加上寬度計算得出。底部是由頂部加上高度計算得出。

1. 需要將預測結果彼此進行比較，如果兩個預測的重疊超過閾值，則需要刪除其中一個。重疊閾值是一個百分比，因此需要乘以最小邊界框的大小，以檢查重疊是否超過邊界框的給定百分比，而不是整個圖像的給定百分比。首先，刪除 `processPredictions` 函數的內容。

1. 在空的 `processPredictions` 函數中新增以下程式碼：

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    這段程式碼宣告了一個向量來存儲不重疊的預測結果。然後，它遍歷所有的預測結果，從邊界框創建一個 `Rect`。

    接著，這段程式碼遍歷剩餘的預測結果，從當前預測的下一個開始。這樣可以避免重複比較預測結果——一旦比較了 1 和 2，就不需要再比較 2 和 1，只需比較 2 和 3、4 等。

    對於每對預測，計算重疊區域。然後將其與最小邊界框的面積進行比較——如果重疊超過最小邊界框的閾值百分比，則該預測被標記為未通過。如果在比較所有重疊後，該預測通過了檢查，則將其添加到 `passed_predictions` 集合中。

    > 💁 這是一種非常簡單的方式來移除重疊，只是刪除重疊對中的第一個。在生產代碼中，您可能需要加入更多邏輯，例如考慮多個物體之間的重疊，或者一個邊界框是否被另一個包含。

1. 在此之後，新增以下程式碼以將通過的預測結果的詳細資訊發送到序列監視器：

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    這段程式碼遍歷通過的預測結果，並將其詳細資訊打印到序列監視器。

1. 在此之下，新增程式碼以將計算出的物品數量打印到序列監視器：

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    然後可以將此數據發送到 IoT 服務，以在庫存水平過低時發出警報。

1. 上傳並運行您的程式碼。將相機對準架子上的物品，然後按下 C 按鈕。嘗試調整 `overlap_threshold` 值，觀察預測結果被忽略的情況。

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 您可以在 [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) 資料夾中找到此程式碼。

😀 您的庫存計數程式大功告成！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。