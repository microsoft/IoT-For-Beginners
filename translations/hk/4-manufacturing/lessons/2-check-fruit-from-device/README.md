<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-26T14:09:15+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "hk"
}
-->
# 從 IoT 裝置檢查水果品質

![本課程的手繪筆記概覽](../../../../../translated_images/hk/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片以查看更大版本。

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## 簡介

在上一課中，你學習了關於影像分類器的知識，以及如何訓練它們來檢測優質和劣質水果。要在 IoT 應用中使用這個影像分類器，你需要能夠使用某種攝影機捕捉影像，並將該影像發送到雲端進行分類。

在本課中，你將學習攝影機感測器的相關知識，以及如何將它們與 IoT 裝置結合使用來捕捉影像。此外，你還會學習如何從 IoT 裝置呼叫影像分類器。

本課內容包括：

* [攝影機感測器](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [使用 IoT 裝置捕捉影像](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [發佈你的影像分類器](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [從 IoT 裝置分類影像](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [改進模型](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## 攝影機感測器

顧名思義，攝影機感測器是可以連接到 IoT 裝置的攝影機。它們可以拍攝靜態影像或錄製串流影片。有些會返回原始影像數據，而另一些則會將影像數據壓縮成 JPEG 或 PNG 等影像檔案。通常，與 IoT 裝置配合使用的攝影機比你習慣使用的攝影機要小得多，解析度也較低，但你也可以找到解析度高到可以媲美高端手機的攝影機。你還可以選擇各種可更換鏡頭、多攝影機配置、紅外線熱成像攝影機或紫外線攝影機。

![場景中的光線通過鏡頭並聚焦在 CMOS 感測器上](../../../../../translated_images/hk/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.png)

大多數攝影機感測器使用影像感測器，其中每個像素都是一個光電二極管。鏡頭將影像聚焦到影像感測器上，數千或數百萬個光電二極管檢測落在每個二極管上的光線，並將其記錄為像素數據。

> 💁 鏡頭會將影像倒置，攝影機感測器會將影像翻轉回正確方向。這與你的眼睛相同——你看到的影像在眼睛後部是倒置的，而你的大腦會將其校正。

> 🎓 影像感測器被稱為主動像素感測器（Active-Pixel Sensor, APS），最常見的 APS 類型是互補金屬氧化物半導體感測器（CMOS）。你可能聽說過 CMOS 感測器這個術語。

攝影機感測器是數位感測器，通常借助提供通訊的函式庫以數位數據的形式傳輸影像數據。攝影機使用像 SPI 這樣的協議進行連接，以便傳輸大量數據——影像的數據量遠大於溫度感測器等感測器的單一數值。

✅ IoT 裝置在影像大小方面有哪些限制？請考慮特別是微控制器硬體的限制。

## 使用 IoT 裝置捕捉影像

你可以使用 IoT 裝置捕捉影像進行分類。

### 任務 - 使用 IoT 裝置捕捉影像

按照相關指南，使用你的 IoT 裝置捕捉影像：

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [單板電腦 - Raspberry Pi](pi-camera.md)
* [單板電腦 - 虛擬裝置](virtual-device-camera.md)

## 發佈你的影像分類器

你在上一課中訓練了你的影像分類器。在你能從 IoT 裝置使用它之前，你需要先發佈該模型。

### 模型迭代

當你在上一課中訓練模型時，你可能注意到 **Performance** 標籤的側邊顯示了迭代次數。當你第一次訓練模型時，你會看到訓練中的 *Iteration 1*。當你使用預測影像改進模型時，你會看到訓練中的 *Iteration 2*。

每次訓練模型時，你都會得到一個新的迭代版本。這是一種記錄基於不同數據集訓練的模型不同版本的方法。當你進行 **Quick Test** 時，可以使用下拉選單選擇迭代版本，從而比較多個迭代版本的結果。

當你對某個迭代版本感到滿意時，可以將其發佈，使其能夠被外部應用使用。這樣，你可以有一個已發佈的版本供裝置使用，然後在多次迭代中改進新版本，並在滿意後發佈。

### 任務 - 發佈一個迭代版本

迭代版本可以從 Custom Vision 入口網站發佈。

1. 開啟 [CustomVision.ai](https://customvision.ai) 入口網站並登入（如果尚未開啟）。然後打開你的 `fruit-quality-detector` 專案。

1. 從頂部選項中選擇 **Performance** 標籤。

1. 從側邊的 *Iterations* 列表中選擇最新的迭代版本。

1. 選擇該迭代版本的 **Publish** 按鈕。

    ![發佈按鈕](../../../../../translated_images/hk/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.png)

1. 在 *Publish Model* 對話框中，將 *Prediction resource* 設置為你在上一課中創建的 `fruit-quality-detector-prediction` 資源。將名稱保留為 `Iteration2`，然後選擇 **Publish** 按鈕。

1. 發佈後，選擇 **Prediction URL** 按鈕。這將顯示預測 API 的詳細資訊，你需要這些資訊來從 IoT 裝置呼叫模型。下方部分標記為 *If you have an image file*，這是你需要的詳細資訊。複製顯示的 URL，該 URL 可能類似於：

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    其中 `<location>` 是你創建 Custom Vision 資源時使用的位置，而 `<id>` 是由字母和數字組成的長 ID。

    同時複製 *Prediction-Key* 值。這是一個安全密鑰，當你呼叫模型時必須傳遞該密鑰。只有傳遞此密鑰的應用程式才能使用該模型，其他應用程式將被拒絕。

    ![預測 API 對話框顯示 URL 和密鑰](../../../../../translated_images/hk/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ 當發佈一個新迭代版本時，它會有一個不同的名稱。你認為應該如何更改 IoT 裝置使用的迭代版本？

## 從 IoT 裝置分類影像

現在你可以使用這些連接詳細資訊從 IoT 裝置呼叫影像分類器。

### 任務 - 從 IoT 裝置分類影像

按照相關指南，使用你的 IoT 裝置分類影像：

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [單板電腦 - Raspberry Pi/虛擬 IoT 裝置](single-board-computer-classify-image.md)

## 改進模型

你可能會發現，使用連接到 IoT 裝置的攝影機時獲得的結果與你預期的不符。預測結果並不總是像從電腦上傳的影像那樣準確。這是因為模型的訓練數據與用於預測的數據不同。

為了讓影像分類器獲得最佳結果，你需要使用與預測影像盡可能相似的影像來訓練模型。例如，如果你使用手機攝影機捕捉影像進行訓練，那麼影像的質量、清晰度和顏色將與連接到 IoT 裝置的攝影機不同。

![兩張香蕉圖片，一張是 IoT 裝置拍攝的低解析度影像，另一張是手機拍攝的高解析度影像](../../../../../translated_images/hk/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.png)

在上圖中，左側的香蕉圖片是使用 Raspberry Pi 攝影機拍攝的，右側的圖片是使用 iPhone 在相同位置拍攝的同一根香蕉。兩者的質量有明顯差異——iPhone 的圖片更清晰，顏色更鮮豔，對比度更高。

✅ 還有哪些因素可能導致 IoT 裝置捕捉的影像預測不準確？請考慮 IoT 裝置可能使用的環境，哪些因素會影響捕捉的影像？

為了改進模型，你可以使用 IoT 裝置捕捉的影像重新訓練模型。

### 任務 - 改進模型

1. 使用你的 IoT 裝置分類多張成熟和未成熟水果的影像。

1. 在 Custom Vision 入口網站中，使用 *Predictions* 標籤上的影像重新訓練模型。

    > ⚠️ 如果需要，可以參考[第一課中重新訓練分類器的指導](../1-train-fruit-detector/README.md#retrain-your-image-classifier)。

1. 如果你的影像與最初用於訓練的影像差異很大，可以通過在 *Training Images* 標籤中選擇影像並點擊 **Delete** 按鈕刪除所有原始影像。將游標移到影像上會出現一個勾選框，點擊該框即可選擇或取消選擇影像。

1. 訓練模型的新迭代版本，並按照上述步驟發佈。

1. 更新程式碼中的端點 URL，並重新運行應用程式。

1. 重複這些步驟，直到你對預測結果感到滿意。

---

## 🚀 挑戰

影像解析度或光線對預測有多大影響？

嘗試在裝置程式碼中更改影像的解析度，看看是否對影像質量產生影響。同時嘗試更改光線條件。

如果你要製作一個銷售給農場或工廠的生產裝置，你會如何確保它始終提供一致的結果？

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## 回顧與自學

你使用入口網站訓練了自訂視覺模型。這依賴於擁有可用的影像——而在現實世界中，你可能無法獲得與裝置攝影機捕捉的影像相匹配的訓練數據。你可以通過使用訓練 API 直接從裝置進行訓練來解決這個問題，從而使用 IoT 裝置捕捉的影像訓練模型。

* 閱讀 [使用 Custom Vision SDK 快速入門](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python) 中的訓練 API 相關內容。

## 作業

[回應分類結果](assignment.md)

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，請注意自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。