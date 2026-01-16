<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1c9e5fa8b7be726c75a97232b1e41c97",
  "translation_date": "2025-08-26T21:32:07+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/README.md",
  "language_code": "mo"
}
-->
# 從物聯網設備檢查庫存

![本課程的手繪筆記概覽](../../../../../translated_images/mo/lesson-20.0211df9551a8abb300fc8fcf7dc2789468dea2eabe9202273ac077b0ba37f15e.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大版本。

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## 簡介

在上一課中，你學習了物件偵測在零售中的不同應用，也學會了如何訓練物件偵測器來識別庫存。在本課中，你將學習如何從物聯網設備使用你的物件偵測器來計算庫存。

本課內容包括：

* [庫存計算](../../../../../5-retail/lessons/2-check-stock-device)
* [從物聯網設備調用物件偵測器](../../../../../5-retail/lessons/2-check-stock-device)
* [邊界框](../../../../../5-retail/lessons/2-check-stock-device)
* [重新訓練模型](../../../../../5-retail/lessons/2-check-stock-device)
* [計算庫存](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 這是本專案的最後一課，因此在完成本課和作業後，別忘了清理你的雲端服務。你需要這些服務來完成作業，所以請確保先完成作業。
>
> 如有需要，請參考[清理專案指南](../../../clean-up.md)以獲取相關指導。

## 庫存計算

物件偵測器可以用於檢查庫存，無論是計算庫存數量還是確保庫存位於正確位置。配備攝像頭的物聯網設備可以部署在商店的各個地方來監控庫存，尤其是那些需要頻繁補貨的熱點區域，例如存放少量高價值商品的區域。

例如，如果一個攝像頭對準一組可以容納8罐番茄醬的貨架，而物件偵測器只偵測到7罐，那麼就缺少了一罐，需要補貨。

![貨架上有7罐番茄醬，頂排4罐，下排3罐](../../../../../translated_images/mo/stock-7-cans-tomato-paste.f86059cc573d7bec.webp)

在上圖中，物件偵測器偵測到貨架上有7罐番茄醬，而該貨架可以容納8罐。不僅物聯網設備可以發送補貨通知，它甚至可以提供缺失物品的位置資訊，這對於使用機器人補貨的情況尤為重要。

> 💁 根據商店和商品的受歡迎程度，如果只缺少一罐，可能不會立即補貨。你需要根據產品、顧客和其他標準建立一個決定何時補貨的演算法。

✅ 在哪些其他情境下，你可以結合物件偵測和機器人技術？

有時候，貨架上可能會出現錯誤的庫存。這可能是補貨時的人為錯誤，或者是顧客改變購買決定後將商品放回第一個可用空間。如果是罐裝食品等非易腐商品，這只是個小麻煩；但如果是冷凍或冷藏食品等易腐商品，則可能導致商品無法再出售，因為無法確定該商品離開冷凍區的時間。

物件偵測可以用來偵測意外出現的物品，並通知人員或機器人盡快將其歸位。

![番茄醬貨架上的一罐玉米罐頭](../../../../../translated_images/mo/stock-rogue-corn.be1f3ada8c457854.webp)

在上圖中，一罐玉米罐頭被放在了番茄醬的貨架上。物件偵測器偵測到了這一情況，使物聯網設備能夠通知人員或機器人將罐頭歸位。

## 從物聯網設備調用物件偵測器

你在上一課中訓練的物件偵測器可以從物聯網設備調用。

### 任務 - 發佈物件偵測器的迭代版本

迭代版本可以從 Custom Vision 入口網站發佈。

1. 打開 [CustomVision.ai](https://customvision.ai) 並登入，如果尚未開啟，請打開你的 `stock-detector` 專案。

1. 從頂部選項中選擇 **Performance** 標籤。

1. 從側邊的 *Iterations* 列表中選擇最新的迭代版本。

1. 點擊該迭代版本的 **Publish** 按鈕。

    ![發佈按鈕](../../../../../translated_images/mo/custom-vision-object-detector-publish-button.34ee379fc650ccb9856c3868d0003f413b9529f102fc73c37168c98d721cc293.png)

1. 在 *Publish Model* 對話框中，將 *Prediction resource* 設置為你在上一課中創建的 `stock-detector-prediction` 資源。保持名稱為 `Iteration2`，然後選擇 **Publish** 按鈕。

1. 發佈後，選擇 **Prediction URL** 按鈕。這將顯示預測 API 的詳細資訊，你需要這些資訊來從物聯網設備調用模型。下方標記為 *If you have an image file* 的部分是你需要的詳細資訊。複製顯示的 URL，該 URL 可能類似於：

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    其中 `<location>` 是你創建 Custom Vision 資源時使用的位置，`<id>` 是由字母和數字組成的一個長 ID。

    同時複製 *Prediction-Key* 值。這是一個安全密鑰，調用模型時必須傳遞該密鑰。只有傳遞此密鑰的應用程式才能使用模型，其他應用程式將被拒絕。

    ![預測 API 對話框顯示 URL 和密鑰](../../../../../translated_images/mo/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ 當發佈新的迭代版本時，它會有不同的名稱。你認為應該如何更改物聯網設備使用的迭代版本？

### 任務 - 從物聯網設備調用物件偵測器

按照以下相關指南，從你的物聯網設備使用物件偵測器：

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [單板電腦 - Raspberry Pi/虛擬設備](single-board-computer-object-detector.md)

## 邊界框

使用物件偵測器時，你不僅會獲得被偵測物件的標籤和概率，還會獲得物件的邊界框。這些邊界框定義了物件偵測器以給定概率偵測到物件的位置。

> 💁 邊界框是一個框，用於定義包含被偵測物件的區域，框的邊界即為物件的範圍。

在 Custom Vision 的 **Predictions** 標籤中，預測結果會在發送進行預測的圖像上繪製邊界框。

![貨架上4罐番茄醬的預測結果，分別為35.8%、33.5%、25.7%和16.6%](../../../../../translated_images/mo/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

在上圖中，偵測到4罐番茄醬。在結果中，每個被偵測物件的圖像上都疊加了一個紅色方框，表示該物件的邊界框。

✅ 打開 Custom Vision 的預測結果，查看邊界框。

邊界框由4個值定義：上（top）、左（left）、高（height）和寬（width）。這些值的範圍是0到1，表示相對於圖像大小的百分比位置。原點（0,0）是圖像的左上角，因此上值是距離頂部的距離，而邊界框的底部是上值加上高度。

![番茄醬罐頭周圍的邊界框](../../../../../translated_images/mo/bounding-box.1420a7ea0d3d15f71e1ffb5cf4b2271d184fac051f990abc541975168d163684.png)

上圖的寬度為600像素，高度為800像素。邊界框從320像素處開始，對應的上值為0.4（800 x 0.4 = 320）。從左側開始，邊界框距離240像素，對應的左值為0.4（600 x 0.4 = 240）。邊界框的高度為240像素，對應的高值為0.3（800 x 0.3 = 240）。邊界框的寬度為120像素，對應的寬值為0.2（600 x 0.2 = 120）。

| 座標   | 值    |
| ------ | ----: |
| 上     | 0.4   |
| 左     | 0.4   |
| 高度   | 0.3   |
| 寬度   | 0.2   |

使用0到1的百分比值意味著無論圖像被縮放到什麼大小，邊界框都會從0.4的位置開始，並且高度為0.3，寬度為0.2。

你可以結合邊界框和概率來評估偵測的準確性。例如，物件偵測器可能會偵測到多個重疊的物件，例如一個罐頭在另一個罐頭內部。你的程式碼可以檢查邊界框，判斷這是不可能的，並忽略任何與其他物件有顯著重疊的物件。

![兩個重疊的邊界框圍繞一罐番茄醬](../../../../../translated_images/mo/overlap-object-detection.d431e03cae75072a2760430eca7f2c5fdd43045bfd72dadcbf12711f7cd6c2ae.png)

在上圖中，一個邊界框表示一罐番茄醬，預測概率為78.3%。另一個邊界框稍小，位於第一個邊界框內部，概率為64.3%。你的程式碼可以檢查邊界框，發現它們完全重疊，並忽略較低概率的邊界框，因為不可能一個罐頭在另一個罐頭內部。

✅ 你能想到哪些情境下，偵測到一個物件在另一個物件內部是合理的？

## 重新訓練模型

與圖像分類器類似，你可以使用物聯網設備捕獲的數據重新訓練模型。使用這些真實世界的數據可以確保模型在物聯網設備上運行良好。

與圖像分類器不同的是，你不能僅僅標記一張圖像。相反，你需要檢查模型偵測到的每個邊界框。如果邊界框圍繞錯誤的物件，則需要刪除；如果位置不正確，則需要調整。

### 任務 - 重新訓練模型

1. 確保你已使用物聯網設備捕獲了一系列圖像。

1. 在 **Predictions** 標籤中，選擇一張圖像。你會看到紅色框，表示偵測到的物件的邊界框。

1. 檢查每個邊界框。首先選擇它，你會看到一個彈出視窗顯示標籤。如果需要，使用邊界框角上的控制點調整大小。如果標籤錯誤，使用 **X** 按鈕刪除並添加正確的標籤。如果邊界框不包含物件，使用垃圾桶按鈕刪除它。

1. 完成後關閉編輯器，圖像將從 **Predictions** 標籤移至 **Training Images** 標籤。對所有預測重複此過程。

1. 使用 **Train** 按鈕重新訓練模型。訓練完成後，發佈新的迭代版本，並更新物聯網設備以使用新迭代版本的 URL。

1. 重新部署程式碼並測試你的物聯網設備。

## 計算庫存

結合偵測到的物件數量和邊界框，你可以計算貨架上的庫存。

### 任務 - 計算庫存

按照以下相關指南，使用物件偵測器的結果從你的物聯網設備計算庫存：

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [單板電腦 - Raspberry Pi/虛擬設備](single-board-computer-count-stock.md)

---

## 🚀 挑戰

你能偵測到錯誤的庫存嗎？訓練你的模型以識別多種物件，然後更新你的應用程式，在偵測到錯誤的庫存時發出警報。

甚至可以進一步嘗試，偵測同一貨架上的並排庫存，並通過定義邊界框的限制來檢查是否有物品被放錯位置。

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## 回顧與自學

* 了解更多關於如何設計端到端庫存偵測系統，請參考 [Microsoft Docs 上的邊緣缺貨偵測模式指南](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn)。
* 觀看 [Behind the scenes of a retail solution - Hands On!](https://www.youtube.com/watch?v=m3Pc300x2Mw) 的 YouTube 視頻，了解如何結合多種物聯網和雲端服務構建端到端零售解決方案。

## 作業

[在邊緣使用你的物件偵測器](assignment.md)

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。