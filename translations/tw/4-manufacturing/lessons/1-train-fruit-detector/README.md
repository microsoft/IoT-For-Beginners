<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f5e63c916d2dd97d58be12aaf76bd9f1",
  "translation_date": "2025-08-24T21:21:01+00:00",
  "source_file": "4-manufacturing/lessons/1-train-fruit-detector/README.md",
  "language_code": "tw"
}
-->
# 訓練水果品質檢測器

![本課程概述的手繪筆記](../../../../../translated_images/lesson-15.843d21afdc6fb2bba70cd9db7b7d2f91598859fafda2078b0bdc44954194b6c0.tw.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大版本。

此影片概述了 Azure Custom Vision 服務，這是本課程中將介紹的服務。

[![Custom Vision – 機器學習變得簡單 | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 點擊上方圖片觀看影片

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## 簡介

人工智慧 (AI) 和機器學習 (ML) 的快速發展為現代開發者提供了廣泛的能力。ML 模型可以被訓練來識別影像中的不同事物，包括未成熟的水果，這可以用於物聯網 (IoT) 設備中，幫助在收穫或工廠及倉庫加工過程中進行產品分類。

在本課程中，您將學習影像分類——使用 ML 模型來區分不同事物的影像。您將學習如何訓練影像分類器，以區分品質良好的水果和品質不佳的水果，例如未成熟、過熟、碰傷或腐爛的水果。

本課程將涵蓋以下內容：

* [使用 AI 和 ML 進行食品分類](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [透過機器學習進行影像分類](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [訓練影像分類器](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [測試您的影像分類器](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [重新訓練您的影像分類器](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## 使用 AI 和 ML 進行食品分類

養活全球人口是一項艱鉅的任務，尤其是在以所有人都能負擔得起的價格提供食物的情況下。勞動力成本是其中最大的支出之一，因此農民越來越多地轉向自動化和物聯網等工具來降低勞動力成本。手工收割勞動強度大（且通常是非常辛苦的工作），在富裕國家正逐漸被機械取代。儘管使用機械收割降低了成本，但也有一個缺點——無法在收割時對食品進行分類。

並非所有作物都能均勻成熟。例如，番茄在大多數果實準備收割時，藤上可能仍有一些未成熟的綠色果實。雖然提前收割這些果實是一種浪費，但對農民來說，使用機械收割所有果實並在後期處理未成熟的果實更便宜、更方便。

✅ 看看您附近農場或花園中正在生長的不同水果或蔬菜，或者商店中的水果或蔬菜。它們是否都成熟一致，還是您能看到成熟度的差異？

自動化收割的興起將產品分類從收割階段移到了工廠。食品會在長長的輸送帶上運輸，人工團隊挑選出不符合品質標準的產品。儘管使用機械收割降低了成本，但人工分類食品仍然需要付出成本。

![如果檢測到紅色番茄，它會繼續前進。如果檢測到綠色番茄，則會被槓桿推入廢料箱](../../../../../translated_images/optical-tomato-sorting.61aa134bdda4e5b1bfb16a212c1e35a6ef0c426cbb8b1c975f79d7bfbf48d068.tw.png)

下一步的演進是使用機器進行分類，這些機器可以內建於收割機中或位於加工廠內。第一代這些機器使用光學感測器檢測顏色，並控制執行器將綠色番茄推入廢料箱，使用槓桿或氣流將紅色番茄留在輸送帶網絡上繼續前進。

在這段影片中，當番茄從一條輸送帶掉落到另一條輸送帶時，綠色番茄被檢測到並用槓桿推入廢料箱。

✅ 在工廠或田地中，光學感測器需要什麼條件才能正常工作？

最新一代的分類機器利用 AI 和 ML，使用訓練模型來區分品質良好的產品和品質不佳的產品，不僅僅是通過顏色差異（如綠色番茄與紅色番茄），還包括外觀上的微妙差異，例如疾病或碰傷。

## 透過機器學習進行影像分類

傳統編程是將數據與算法結合，並生成輸出。例如，在上一個項目中，您使用 GPS 坐標和地理圍欄，應用 Azure Maps 提供的算法，並獲得該點是否在地理圍欄內或外的結果。輸入更多數據，您就能獲得更多輸出。

![傳統開發使用輸入和算法生成輸出。機器學習使用輸入和輸出數據訓練模型，該模型可以使用新輸入數據生成新輸出](../../../../../translated_images/traditional-vs-ml.5c20c169621fa539.tw.png)

機器學習則顛覆了這一過程——您從數據和已知輸出開始，機器學習算法從數據中學習。然後，您可以使用這個訓練好的算法（稱為 *機器學習模型* 或 *模型*），輸入新數據並獲得新輸出。

> 🎓 機器學習算法從數據中學習的過程稱為 *訓練*。輸入和已知輸出稱為 *訓練數據*。

例如，您可以提供數百萬張未成熟香蕉的圖片作為輸入訓練數據，並將訓練輸出設為 `未成熟`，同時提供數百萬張成熟香蕉的圖片作為訓練數據，輸出設為 `成熟`。ML 算法將基於這些數據創建一個模型。然後，您可以將一張新的香蕉圖片提供給這個模型，它將預測該香蕉是成熟還是未成熟。

> 🎓 ML 模型的結果稱為 *預測*

![兩根香蕉，一根成熟的香蕉預測為 99.7% 成熟，0.3% 未成熟；另一根未成熟的香蕉預測為 1.4% 成熟，98.6% 未成熟](../../../../../translated_images/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50ece4e4589e724b142da0681f35470fe3db3f7d51240f69c85.tw.png)

ML 模型不會給出二元答案，而是提供概率。例如，模型可能會給出一張香蕉的圖片，預測 `成熟` 的概率為 99.7%，`未成熟` 的概率為 0.3%。您的代碼將選擇最佳預測並判斷該香蕉是成熟的。

用於檢測影像的 ML 模型稱為 *影像分類器*——它接收標記的影像，並根據這些標記分類新影像。

> 💁 這是一種簡化的說法，還有許多其他訓練模型的方法，不一定需要標記的輸出，例如無監督學習。如果您想了解更多關於 ML 的知識，請查看 [ML 初學者課程，一個包含 24 篇課程的機器學習課程](https://aka.ms/ML-beginners)。

## 訓練影像分類器

要成功訓練影像分類器，您需要數百萬張影像。然而，事實證明，一旦您擁有一個基於數百萬或數十億張各種影像訓練的影像分類器，您可以重複使用它並通過少量影像重新訓練它，並獲得良好的結果，這個過程稱為 *遷移學習*。

> 🎓 遷移學習是指將現有 ML 模型的學習成果轉移到基於新數據的新模型中。

一旦影像分類器已經針對各種影像進行訓練，它的內部就能很好地識別形狀、顏色和模式。遷移學習允許模型利用它已經學會的影像部分識別能力，來識別新影像。

![一旦能識別形狀，它們可以以不同的配置組成船或貓](../../../../../translated_images/shapes-to-images.1a309f0ea88dd66f.tw.png)

您可以將其類比為兒童的形狀書籍，一旦您能識別半圓形、矩形和三角形，您就能根據這些形狀的配置識別帆船或貓。影像分類器可以識別形狀，而遷移學習則教它什麼樣的組合構成帆船或貓——或者成熟的香蕉。

有許多工具可以幫助您完成這項工作，包括基於雲的服務，這些服務可以幫助您訓練模型，然後通過 Web API 使用它。

> 💁 訓練這些模型需要大量的計算能力，通常通過圖形處理單元 (GPU) 實現。與 Xbox 上讓遊戲畫面看起來令人驚嘆的專用硬件相同，GPU 也可以用於訓練機器學習模型。通過使用雲端，您可以租用強大計算機的 GPU 訓練模型，只需支付您需要的時間。

## Custom Vision

Custom Vision 是一種基於雲的工具，用於訓練影像分類器。它允許您僅使用少量影像訓練分類器。您可以通過 Web 入口、Web API 或 SDK 上傳影像，並為每張影像提供 *標籤*，以標記該影像的分類。然後，您可以訓練模型並測試其性能。一旦您對模型感到滿意，您可以發布版本，通過 Web API 或 SDK 訪問它。

![Azure Custom Vision 標誌](../../../../../translated_images/custom-vision-logo.d3d4e7c8a87ec9daf825e72e210576c3cbf60312577be7a139e22dd97ab7f1e6.tw.png)

> 💁 您可以僅使用每個分類 5 張影像訓練 Custom Vision 模型，但影像越多效果越好。至少 30 張影像可以獲得更好的結果。

Custom Vision 是 Microsoft 提供的一系列 AI 工具的一部分，稱為 Cognitive Services。這些 AI 工具可以在不需要任何訓練或僅需少量訓練的情況下使用，包括語音識別和翻譯、語言理解和影像分析。這些工具在 Azure 中提供免費層。

> 💁 免費層足以創建模型、訓練模型，然後用於開發工作。您可以在 [Microsoft Docs 上的 Custom Vision 限制和配額頁面](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn) 閱讀免費層的限制。

### 任務 - 創建 Cognitive Services 資源

要使用 Custom Vision，您需要使用 Azure CLI 在 Azure 中創建兩個 Cognitive Services 資源，一個用於 Custom Vision 訓練，另一個用於 Custom Vision 預測。

1. 為此項目創建一個名為 `fruit-quality-detector` 的資源群組。

1. 使用以下命令創建一個免費的 Custom Vision 訓練資源：

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    將 `<location>` 替換為您創建資源群組時使用的位置。

    這將在您的資源群組中創建一個 Custom Vision 訓練資源。它將被命名為 `fruit-quality-detector-training`，並使用 `F0` sku，即免費層。`--yes` 選項表示您同意 Cognitive Services 的條款和條件。

> 💁 如果您已經有一個使用任何 Cognitive Services 的免費帳戶，請使用 `S0` sku。

1. 使用以下命令創建一個免費的 Custom Vision 預測資源：

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    將 `<location>` 替換為您創建資源群組時使用的位置。

    這將在您的資源群組中創建一個 Custom Vision 預測資源。它將被命名為 `fruit-quality-detector-prediction`，並使用 `F0` sku，即免費層。`--yes` 選項表示您同意 Cognitive Services 的條款和條件。

### 任務 - 創建影像分類器項目

1. 打開 [CustomVision.ai](https://customvision.ai) 的 Custom Vision 入口，並使用您 Azure 帳戶的 Microsoft 帳戶登錄。

1. 按照 Microsoft Docs 上 [建立分類器快速入門的創建新項目部分](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project) 創建新的 Custom Vision 項目。UI 可能會更改，這些文檔始終是最新的參考。

    將您的項目命名為 `fruit-quality-detector`。

    創建項目時，請確保使用您之前創建的 `fruit-quality-detector-training` 資源。使用 *分類* 項目類型、*多類別* 分類類型以及 *食品* 領域。

    ![Custom Vision 項目的設置，名稱設為 fruit-quality-detector，無描述，資源設為 fruit-quality-detector-training，項目類型設為分類，分類類型設為多類別，領域設為食品](../../../../../translated_images/custom-vision-create-project.cf46325b92d8b131089f6647cf5e07b664cb77850e106d66e3c057b6b69756c6.tw.png)

✅ 花些時間探索您的影像分類器的 Custom Vision UI。

### 任務 - 訓練您的影像分類器項目

要訓練影像分類器，您需要多張水果的圖片，包括品質良好和品質不佳的水果，並標記為良好和不良，例如成熟和過熟的香蕉。
💁 這些分類器可以用來分類任何東西的圖片，所以如果你手邊沒有不同品質的水果，你可以使用兩種不同類型的水果，或者貓和狗！
理想情況下，每張照片應該只包含水果，背景要保持一致或有多種背景。確保背景中沒有任何與成熟或未成熟水果相關的特定元素。

> 💁 非常重要的是，背景或與標籤分類無關的特定物品不應出現在照片中，否則分類器可能會根據背景進行分類。有一個皮膚癌分類器曾經用正常和癌症痣的照片進行訓練，而癌症痣的照片中都放置了尺子來測量大小。結果分類器幾乎100%準確地識別了照片中的尺子，而不是癌症痣。

影像分類器以非常低的解析度運行。例如，Custom Vision可以處理最大10240x10240的訓練和預測影像，但模型實際上是在227x227的影像上進行訓練和運行。較大的影像會縮小到這個尺寸，因此請確保您要分類的物品在影像中占據較大的部分，否則在分類器使用的小影像中可能會太小。

1. 收集分類器所需的照片。每個標籤至少需要5張照片來訓練分類器，但越多越好。此外，還需要一些額外的照片來測試分類器。這些照片應該是同一物品的不同照片。例如：

    * 使用2根成熟的香蕉，從不同角度拍攝每根香蕉的幾張照片，至少拍攝7張（5張用於訓練，2張用於測試），但最好更多。

        ![2根不同香蕉的照片](../../../../../translated_images/banana-training-images.530eb203346d73bc23b8b990fb4609470bf4ff7c942ccc13d4cfffeed9be1ad4.tw.png)

    * 使用2根未成熟的香蕉重複相同的過程。

    您應該至少有10張訓練照片，其中至少5張成熟、5張未成熟，還有4張測試照片，2張成熟、2張未成熟。您的照片應該是png或jpeg格式，大小小於6MB。如果您使用iPhone拍攝，可能會生成高解析度的HEIC格式照片，因此需要進行轉換並可能縮小尺寸。照片越多越好，並且成熟和未成熟的數量應該相近。

    如果您沒有成熟和未成熟的水果，可以使用不同的水果，或者任何您手邊的兩個物品。您也可以在[images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images)文件夾中找到一些成熟和未成熟香蕉的示例照片供您使用。

1. 按照[Microsoft文檔中建立分類器快速入門的上傳和標記影像部分](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images)的指引，上傳您的訓練影像。將成熟的水果標記為`ripe`，未成熟的水果標記為`unripe`。

    ![上傳成熟和未成熟香蕉照片的對話框](../../../../../translated_images/image-upload-bananas.0751639f3815e0ec42bdbc6254d1e4357a185834d1ae10c9948a0e7d6d336695.tw.png)

1. 按照[Microsoft文檔中建立分類器快速入門的訓練分類器部分](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier)的指引，使用您上傳的影像訓練影像分類器。

    您將可以選擇訓練類型。選擇**快速訓練**。

分類器將開始訓練。訓練完成需要幾分鐘。

> 🍌 如果您在分類器訓練期間決定吃掉您的水果，請確保您已經準備好足夠的測試影像！

## 測試您的影像分類器

一旦您的分類器訓練完成，您可以通過提供新的影像來測試它的分類能力。

### 任務 - 測試您的影像分類器

1. 按照[Microsoft文檔中測試模型的指引](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model)，使用您之前準備的測試影像測試您的影像分類器，而不是使用訓練影像。

    ![一根未成熟香蕉被預測為未成熟，概率為98.9%，成熟概率為1.1%](../../../../../translated_images/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64886422438850ea14f0be6ac918c217ea3b255c685abfabe7.tw.png)

1. 嘗試使用您所有的測試影像並觀察概率。

## 重新訓練您的影像分類器

當您測試分類器時，它可能不會給出您期望的結果。影像分類器使用機器學習根據影像中的特定特徵來預測影像是否符合某個標籤的概率。它並不理解影像中的內容——它不知道什麼是香蕉，也不理解什麼使香蕉成為香蕉而不是船。您可以通過使用分類器錯誤的影像重新訓練來改進分類器。

每次使用快速測試選項進行預測時，影像和結果都會被存儲。您可以使用這些影像重新訓練您的模型。

### 任務 - 重新訓練您的影像分類器

1. 按照[Microsoft文檔中使用預測影像進行訓練的指引](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training)，使用每張影像的正確標籤重新訓練您的模型。

1. 一旦您的模型重新訓練完成，請使用新的影像進行測試。

---

## 🚀 挑戰

如果您使用一張草莓的照片測試一個訓練過香蕉的模型，或者使用一張充氣香蕉的照片、一個穿香蕉服的人、甚至是像《辛普森一家》中的黃色卡通人物的照片，您認為會發生什麼？

試試看，看看預測結果如何。您可以使用[Bing影像搜索](https://www.bing.com/images/trending)找到可以嘗試的影像。

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## 回顧與自學

* 當您訓練分類器時，您會看到*Precision*、*Recall*和*AP*的值，這些值用來評估所建立的模型。請閱讀[Microsoft文檔中建立分類器快速入門的評估分類器部分](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier)，了解這些值的含義。
* 閱讀[Microsoft文檔中如何改進您的Custom Vision模型](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn)的內容，了解如何改進您的分類器。

## 作業

[為多種水果和蔬菜訓練您的分類器](assignment.md)

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。