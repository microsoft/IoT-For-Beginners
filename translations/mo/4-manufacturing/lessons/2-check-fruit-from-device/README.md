<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-26T21:47:29+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "mo"
}
-->
# 從物聯網設備檢查水果品質

![本課程的手繪筆記概述](../../../../../translated_images/mo/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大版本。

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## 簡介

在上一課中，你學習了影像分類器，以及如何訓練它來檢測好壞水果。要在物聯網應用中使用這個影像分類器，你需要能夠使用某種相機捕捉影像，並將影像傳送到雲端進行分類。

在本課中，你將學習相機感測器，以及如何使用物聯網設備捕捉影像。你還將學習如何從物聯網設備調用影像分類器。

本課將涵蓋以下內容：

* [相機感測器](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [使用物聯網設備捕捉影像](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [發布你的影像分類器](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [從物聯網設備分類影像](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [改進模型](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## 相機感測器

相機感測器，顧名思義，是可以連接到物聯網設備的相機。它們可以拍攝靜態影像或捕捉串流視頻。有些會返回原始影像數據，其他則會將影像數據壓縮成如 JPEG 或 PNG 的影像文件。通常，與物聯網設備配合使用的相機比你習慣的相機要小得多，解析度也較低，但你也可以獲得解析度高的相機，媲美高端手機。你可以選擇各種可互換鏡頭、多相機設置、紅外熱成像相機或紫外線相機。

![場景中的光線通過鏡頭並聚焦在 CMOS 感測器上](../../../../../translated_images/mo/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.png)

大多數相機感測器使用影像感測器，其中每個像素都是一個光電二極管。鏡頭將影像聚焦到影像感測器上，數千或數百萬個光電二極管檢測落在每個二極管上的光線，並將其記錄為像素數據。

> 💁 鏡頭會將影像倒置，相機感測器會將影像翻轉回正確方向。你的眼睛也是如此——你看到的影像在眼睛後部是倒置的，而你的大腦會將其校正。

> 🎓 影像感測器被稱為主動像素感測器（APS），最流行的 APS 類型是互補金屬氧化物半導體感測器，簡稱 CMOS。你可能聽過 CMOS 感測器這個術語用於相機感測器。

相機感測器是數位感測器，通過數位數據傳送影像數據，通常需要使用提供通信的庫。相機使用像 SPI 這樣的協議進行連接，以便傳送大量數據——影像的大小遠大於溫度感測器等感測器的單一數值。

✅ 物聯網設備在影像大小方面有哪些限制？請思考微控制器硬體的限制。

## 使用物聯網設備捕捉影像

你可以使用物聯網設備捕捉影像進行分類。

### 任務 - 使用物聯網設備捕捉影像

按照相關指南使用物聯網設備捕捉影像：

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [單板電腦 - Raspberry Pi](pi-camera.md)
* [單板電腦 - 虛擬設備](virtual-device-camera.md)

## 發布你的影像分類器

你在上一課中訓練了影像分類器。在你能從物聯網設備使用它之前，你需要發布模型。

### 模型迭代

當你在上一課中訓練模型時，你可能注意到 **Performance** 標籤顯示了側邊的迭代。在你第一次訓練模型時，你會看到 *Iteration 1*。當你使用預測影像改進模型時，你會看到 *Iteration 2*。

每次訓練模型時，你都會得到一個新的迭代。這是一種跟蹤基於不同數據集訓練的模型版本的方法。當你進行 **Quick Test** 時，有一個下拉選單可以用來選擇迭代，這樣你就可以比較多次迭代的結果。

當你對某次迭代感到滿意時，你可以發布它，使其可供外部應用使用。這樣，你可以有一個已發布的版本供設備使用，然後基於多次迭代工作在新版本上，當你對新版本感到滿意時再發布。

### 任務 - 發布迭代

迭代是從 Custom Vision 入口網站發布的。

1. 打開 [CustomVision.ai](https://customvision.ai) 並登入，如果尚未打開。然後打開你的 `fruit-quality-detector` 專案。

1. 從頂部選項中選擇 **Performance** 標籤。

1. 從側邊的 *Iterations* 列表中選擇最新的迭代。

1. 為該迭代選擇 **Publish** 按鈕。

    ![發布按鈕](../../../../../translated_images/mo/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.png)

1. 在 *Publish Model* 對話框中，將 *Prediction resource* 設置為你在上一課中創建的 `fruit-quality-detector-prediction` 資源。名稱保持為 `Iteration2`，然後選擇 **Publish** 按鈕。

1. 發布後，選擇 **Prediction URL** 按鈕。這將顯示預測 API 的詳細信息，你需要這些信息來從物聯網設備調用模型。下方部分標記為 *If you have an image file*，這是你需要的詳細信息。複製顯示的 URL，類似於：

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    其中 `<location>` 是你創建 Custom Vision 資源時使用的位置，`<id>` 是由字母和數字組成的長 ID。

    同時複製 *Prediction-Key* 值。這是一個安全密鑰，當你調用模型時必須傳遞。只有傳遞此密鑰的應用可以使用模型，其他應用將被拒絕。

    ![預測 API 對話框顯示 URL 和密鑰](../../../../../translated_images/mo/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ 當新迭代發布時，它會有不同的名稱。你認為如何更改物聯網設備使用的迭代？

## 從物聯網設備分類影像

現在你可以使用這些連接詳細信息從物聯網設備調用影像分類器。

### 任務 - 從物聯網設備分類影像

按照相關指南使用物聯網設備分類影像：

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [單板電腦 - Raspberry Pi/虛擬物聯網設備](single-board-computer-classify-image.md)

## 改進模型

你可能會發現，使用連接到物聯網設備的相機時，結果與你的預期不符。預測結果並不總是像使用從電腦上傳的影像那樣準確。這是因為模型是基於不同的數據進行訓練的，而不是用於預測的數據。

要獲得影像分類器的最佳結果，你需要使用與預測影像盡可能相似的影像來訓練模型。例如，如果你使用手機相機捕捉影像進行訓練，影像的質量、清晰度和顏色會與連接到物聯網設備的相機不同。

![兩張香蕉圖片，一張是物聯網設備拍攝的低解析度影像，光線較差；另一張是手機拍攝的高解析度影像，光線良好](../../../../../translated_images/mo/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.png)

在上圖中，左邊的香蕉圖片是使用 Raspberry Pi 相機拍攝的，右邊的圖片是使用 iPhone 在相同位置拍攝的同一香蕉。可以明顯看到質量差異——iPhone 的圖片更清晰，顏色更亮，對比度更高。

✅ 還有哪些因素可能導致物聯網設備捕捉的影像預測不準確？請思考物聯網設備可能使用的環境，哪些因素會影響捕捉的影像？

要改進模型，你可以使用物聯網設備捕捉的影像重新訓練模型。

### 任務 - 改進模型

1. 使用物聯網設備分類多張成熟和未成熟水果的影像。

1. 在 Custom Vision 入口網站中，使用 *Predictions* 標籤上的影像重新訓練模型。

    > ⚠️ 如果需要，可以參考 [第一課中重新訓練分類器的指導](../1-train-fruit-detector/README.md#retrain-your-image-classifier)。

1. 如果你的影像與用於訓練的原始影像差異很大，可以在 *Training Images* 標籤中選擇所有原始影像並選擇 **Delete** 按鈕刪除它們。要選擇影像，將光標移到影像上，會出現一個勾選，選擇該勾選即可選擇或取消選擇影像。

1. 訓練模型的新迭代並按照上述步驟發布。

1. 更新程式碼中的端點 URL，重新運行應用程式。

1. 重複這些步驟，直到你對預測結果感到滿意。

---

## 🚀 挑戰

影像解析度或光線對預測有多大影響？

嘗試在設備程式碼中更改影像解析度，看看是否對影像質量有影響。也嘗試更改光線。

如果你要製作一個生產設備出售給農場或工廠，你會如何確保它始終提供一致的結果？

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## 回顧與自學

你使用入口網站訓練了自訂視覺模型。這依賴於有可用的影像——在現實世界中，你可能無法獲得與設備相機捕捉的影像匹配的訓練數據。你可以通過使用訓練 API 直接從設備進行訓練，使用物聯網設備捕捉的影像訓練模型來解決這個問題。

* 閱讀 [使用 Custom Vision SDK 快速入門](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python) 中的訓練 API。

## 作業

[回應分類結果](assignment.md)

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。