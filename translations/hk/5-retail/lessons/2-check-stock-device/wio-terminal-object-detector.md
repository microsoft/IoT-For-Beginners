<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-26T14:03:53+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "hk"
}
-->
# 從物聯網設備呼叫物件檢測器 - Wio Terminal

當你的物件檢測器已經發布後，就可以從你的物聯網設備上使用它。

## 複製影像分類器專案

你的庫存檢測器大部分內容與你在之前課程中建立的影像分類器相同。

### 任務 - 複製影像分類器專案

1. 按照[製造專案第 2 課](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera)中的步驟，將 ArduCam 連接到 Wio Terminal。

   你可能還需要將相機固定在一個位置，例如，將電纜掛在盒子或罐子上，或者用雙面膠將相機固定在盒子上。

1. 使用 PlatformIO 建立一個全新的 Wio Terminal 專案，將此專案命名為 `stock-counter`。

1. 按照[製造專案第 2 課](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device)中的步驟，從相機捕捉影像。

1. 按照[製造專案第 2 課](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device)中的步驟，呼叫影像分類器。大部分的程式碼將被重複使用來檢測物件。

## 將程式碼從分類器改為影像檢測器

用於分類影像的程式碼與用於檢測物件的程式碼非常相似。主要的區別在於從 Custom Vision 獲得的 URL 以及呼叫的結果。

### 任務 - 將程式碼從分類器改為影像檢測器

1. 在 `main.cpp` 檔案的頂部新增以下 include 指令：

    ```cpp
    #include <vector>
    ```

1. 將 `classifyImage` 函數重新命名為 `detectStock`，包括函數名稱以及在 `buttonPressed` 函數中的呼叫。

1. 在 `detectStock` 函數上方，宣告一個閾值，用於過濾掉任何機率較低的檢測結果：

    ```cpp
    const float threshold = 0.3f;
    ```

    與影像分類器只返回每個標籤的一個結果不同，物件檢測器會返回多個結果，因此需要過濾掉任何機率較低的結果。

1. 在 `detectStock` 函數上方，宣告一個函數來處理預測結果：

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    這個函數會接收一個預測結果的列表，並將其輸出到序列監控器。

1. 在 `detectStock` 函數中，將迴圈處理預測結果的 `for` 迴圈內容替換為以下內容：

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    這段程式碼會遍歷預測結果，將機率與閾值進行比較。所有機率高於閾值的預測結果會被加入到一個 `list` 中，並傳遞給 `processPredictions` 函數。

1. 上傳並執行你的程式碼。將相機對準架子上的物件，然後按下 C 按鈕。你會在序列監控器中看到輸出：

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 你可能需要根據你的影像調整 `threshold` 到一個合適的值。

    你將能夠看到拍攝的影像，並在 Custom Vision 的 **Predictions** 標籤中看到這些值。

    ![架子上有 4 罐番茄醬，檢測結果分別為 35.8%、33.5%、25.7% 和 16.6%](../../../../../translated_images/hk/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 你可以在 [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) 資料夾中找到這段程式碼。

😀 你的庫存計數程式成功了！

---

**免責聲明**：  
此文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議使用專業的人工作翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤詮釋概不負責。