<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-24T21:12:34+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "tw"
}
-->
# 從您的 IoT 裝置計算庫存 - 虛擬 IoT 硬體與 Raspberry Pi

結合預測結果及其邊界框可以用來計算影像中的庫存數量。

## 顯示邊界框

作為一個有用的除錯步驟，您不僅可以將邊界框列印出來，還可以將它們繪製在捕捉影像時寫入磁碟的影像上。

### 任務 - 列印邊界框

1. 確保 `stock-counter` 專案已在 VS Code 中開啟，並且如果您使用的是虛擬 IoT 裝置，虛擬環境已啟動。

1. 將 `for` 迴圈中的 `print` 語句更改為以下內容，以便在主控台中列印邊界框：

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. 將相機對準架子上的一些庫存並運行應用程式。邊界框將列印到主控台，並顯示左、上、寬度和高度的值，範圍為 0-1。

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### 任務 - 在影像上繪製邊界框

1. Pip 套件 [Pillow](https://pypi.org/project/Pillow/) 可用於在影像上繪製。使用以下命令安裝：

    ```sh
    pip3 install pillow
    ```

    如果您使用的是虛擬 IoT 裝置，請確保在啟動的虛擬環境中執行此命令。

1. 在 `app.py` 文件的頂部添加以下導入語句：

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    這將導入編輯影像所需的程式碼。

1. 在 `app.py` 文件的末尾添加以下程式碼：

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    此程式碼打開之前保存的影像進行編輯。然後迴圈遍歷預測結果，獲取邊界框，並使用 0-1 的邊界框值計算右下角座標。這些值通過乘以影像的相關維度轉換為影像座標。例如，如果左值為 0.5，影像寬度為 600 像素，則轉換為 300 (0.5 x 600 = 300)。

    每個邊界框都使用紅線繪製在影像上。最後，編輯後的影像被保存，覆蓋原始影像。

1. 將相機對準架子上的一些庫存並運行應用程式。您將在 VS Code 的檔案瀏覽器中看到 `image.jpg` 文件，並可以選擇它來查看邊界框。

    ![4 罐番茄醬，每罐周圍都有邊界框](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.tw.jpg)

## 計算庫存

在上圖中，邊界框有些許重疊。如果這種重疊更大，邊界框可能表示同一個物件。為了正確計算物件數量，您需要忽略具有顯著重疊的框。

### 任務 - 忽略重疊計算庫存

1. Pip 套件 [Shapely](https://pypi.org/project/Shapely/) 可用於計算交集。如果您使用的是 Raspberry Pi，您需要先安裝一個庫依賴：

    ```sh
    sudo apt install libgeos-dev
    ```

1. 安裝 Shapely Pip 套件：

    ```sh
    pip3 install shapely
    ```

    如果您使用的是虛擬 IoT 裝置，請確保在啟動的虛擬環境中執行此命令。

1. 在 `app.py` 文件的頂部添加以下導入語句：

    ```python
    from shapely.geometry import Polygon
    ```

    這將導入創建多邊形以計算重疊所需的程式碼。

1. 在繪製邊界框的程式碼上方添加以下程式碼：

    ```python
    overlap_threshold = 0.20
    ```

    這定義了邊界框被視為同一物件之前允許的重疊百分比。0.20 定義了 20% 的重疊。

1. 為了使用 Shapely 計算重疊，邊界框需要轉換為 Shapely 多邊形。添加以下函數來完成此操作：

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    此函數使用預測的邊界框創建一個多邊形。

1. 移除重疊物件的邏輯涉及比較所有邊界框，如果任何一對預測的邊界框重疊超過閾值，則刪除其中一個預測。為了比較所有預測，您需要將預測 1 與 2、3、4 等進行比較，然後將 2 與 3、4 等進行比較。以下程式碼完成此操作：

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    使用 Shapely 的 `Polygon.intersection` 方法計算重疊，該方法返回具有重疊的多邊形。然後從該多邊形計算面積。此重疊閾值不是絕對值，而是需要作為邊界框的百分比，因此找到最小的邊界框，並使用重疊閾值計算重疊面積不能超過最小邊界框的百分比重疊閾值。如果重疊超過此值，則該預測被標記為刪除。

    一旦預測被標記為刪除，就不需要再次檢查，因此內部迴圈跳出以檢查下一個預測。您不能在迴圈中刪除列表中的項目，因此重疊超過閾值的邊界框被添加到 `to_delete` 列表中，然後在最後刪除。

    最後，庫存數量被列印到主控台。這可以發送到 IoT 服務以在庫存水平低時發出警報。所有這些程式碼都在繪製邊界框之前，因此您將在生成的影像上看到沒有重疊的庫存預測。

    > 💁 這是一種非常簡單的移除重疊方式，只移除重疊對中的第一個。在生產程式碼中，您可能需要在此處添加更多邏輯，例如考慮多個物件之間的重疊，或者如果一個邊界框被另一個邊界框包含。

1. 將相機對準架子上的一些庫存並運行應用程式。輸出將顯示超過閾值的無重疊邊界框的數量。嘗試調整 `overlap_threshold` 值以查看被忽略的預測。

> 💁 您可以在 [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) 或 [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device) 文件夾中找到此程式碼。

😀 您的庫存計數程式成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原文文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤讀概不負責。