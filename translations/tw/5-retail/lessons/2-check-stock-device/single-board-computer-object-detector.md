<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-24T21:06:41+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "tw"
}
-->
# 從物聯網設備呼叫物件檢測器 - 虛擬物聯網硬體與樹莓派

當你的物件檢測器已發布後，就可以從你的物聯網設備使用它。

## 複製影像分類器專案

你的庫存檢測器大部分內容與你在之前課程中建立的影像分類器相同。

### 任務 - 複製影像分類器專案

1. 建立一個名為 `stock-counter` 的資料夾，若你使用虛擬物聯網設備，則在你的電腦上建立；若使用樹莓派，則在樹莓派上建立。如果使用虛擬物聯網設備，請確保已設置虛擬環境。

1. 設置相機硬體。

    * 如果你使用樹莓派，則需要安裝 PiCamera。你可能還需要將相機固定在一個位置，例如，將相機線纜掛在盒子或罐子上，或者用雙面膠將相機固定在盒子上。
    * 如果你使用虛擬物聯網設備，則需要安裝 CounterFit 和 CounterFit PyCamera shim。如果你打算使用靜態影像，請捕捉一些你的物件檢測器尚未見過的影像；如果你打算使用網路攝影機，請確保它的位置能看到你要檢測的庫存。

1. 複製 [製造專案第 2 課](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) 中的步驟，從相機捕捉影像。

1. 複製 [製造專案第 2 課](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) 中的步驟，呼叫影像分類器。大部分的程式碼將被重複使用來檢測物件。

## 將程式碼從分類器改為影像檢測器

你用來分類影像的程式碼與用來檢測物件的程式碼非常相似。主要的差異在於 Custom Vision SDK 中所呼叫的方法，以及呼叫的結果。

### 任務 - 將程式碼從分類器改為影像檢測器

1. 刪除三行用來分類影像並處理預測結果的程式碼：

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    移除這三行程式碼。

1. 添加以下程式碼來檢測影像中的物件：

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    此程式碼呼叫 `detect_image` 方法，使用預測器執行物件檢測器。接著，它會收集所有超過閾值的預測結果，並將它們打印到控制台。

    與影像分類器只返回每個標籤的一個結果不同，物件檢測器會返回多個結果，因此需要過濾掉任何低概率的結果。

1. 執行此程式碼，它將捕捉一張影像，發送至物件檢測器，並打印出檢測到的物件。如果你使用虛擬物聯網設備，請確保在 CounterFit 中設置了適當的影像，或選擇了網路攝影機。如果你使用樹莓派，請確保你的相機指向架子上的物件。

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 你可能需要調整 `threshold` 的值，使其適合你的影像。

    你將能看到拍攝的影像，以及這些值在 Custom Vision 的 **Predictions** 標籤中。

    ![架子上有 4 罐番茄醬，預測結果分別為 35.8%、33.5%、25.7% 和 16.6%](../../../../../translated_images/tw/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 你可以在 [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) 或 [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device) 資料夾中找到此程式碼。

😀 你的庫存計數程式成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。