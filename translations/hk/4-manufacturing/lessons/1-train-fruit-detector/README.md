<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f5e63c916d2dd97d58be12aaf76bd9f1",
  "translation_date": "2025-08-26T14:06:57+00:00",
  "source_file": "4-manufacturing/lessons/1-train-fruit-detector/README.md",
  "language_code": "hk"
}
-->
# 訓練水果品質檢測器

![本課程概述的手繪筆記](../../../../../translated_images/lesson-15.843d21afdc6fb2bba70cd9db7b7d2f91598859fafda2078b0bdc44954194b6c0.hk.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大版本。

這段影片概述了 Azure Custom Vision 服務，這是本課程將涵蓋的內容。

[![Custom Vision – 機器學習變得簡單 | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 點擊上方圖片觀看影片

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## 簡介

人工智能 (AI) 和機器學習 (ML) 的快速發展為現今的開發者提供了廣泛的能力。ML 模型可以被訓練來識別圖像中的不同事物，包括未成熟的水果，這可以用於物聯網設備來幫助在收割或工廠或倉庫的加工過程中進行分類。

在本課程中，您將學習圖像分類——使用 ML 模型來區分不同事物的圖像。您將學習如何訓練圖像分類器來區分品質良好的水果和品質不佳的水果，例如未成熟、過熟、碰傷或腐爛的水果。

本課程將涵蓋以下內容：

* [使用 AI 和 ML 來分類食品](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [通過機器學習進行圖像分類](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [訓練圖像分類器](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [測試您的圖像分類器](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [重新訓練您的圖像分類器](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## 使用 AI 和 ML 來分類食品

養活全球人口是一項艱難的任務，尤其是在確保食品價格對所有人都負擔得起的情況下。勞動力成本是其中最大的支出之一，因此農民越來越多地轉向自動化和物聯網等工具來降低勞動力成本。手工收割勞動強度大（且通常是非常辛苦的工作），在富裕國家正逐漸被機械取代。儘管使用機械收割降低了成本，但也有一個缺點——無法在收割時對食品進行分類。

並非所有作物都能均勻成熟。例如，番茄在大多數果實準備收割時，藤上可能仍有一些未成熟的綠色果實。雖然提前收割這些果實是一種浪費，但農民使用機械收割所有果實並在後期處理未成熟的果實會更便宜、更方便。

✅ 看看您附近農場或花園中正在生長的不同水果或蔬菜，或者商店中的水果或蔬菜。它們是否都成熟一致，還是您能看到成熟度的差異？

自動化收割的興起將食品分類從收割階段移到了工廠。食品會在長長的輸送帶上運輸，人工團隊挑選出不符合品質標準的食品。儘管使用機械收割降低了成本，但人工分類食品仍然需要一定的費用。

![如果檢測到紅色番茄，它會繼續不受干擾地前進。如果檢測到綠色番茄，則會被槓桿彈入廢料箱](../../../../../translated_images/optical-tomato-sorting.61aa134bdda4e5b1bfb16a212c1e35a6ef0c426cbb8b1c975f79d7bfbf48d068.hk.png)

下一步的演進是使用機器進行分類，這些機器可以內置於收割機中或安裝在加工廠中。第一代這些機器使用光學傳感器檢測顏色，並控制執行器將綠色番茄推入廢料箱，使用槓桿或氣流，讓紅色番茄繼續在輸送帶網絡上前進。

在這段影片中，當番茄從一條輸送帶掉到另一條輸送帶時，綠色番茄被檢測到並用槓桿彈入廢料箱。

✅ 在工廠或田地中，光學傳感器需要什麼條件才能正常工作？

最新一代的分類機器利用 AI 和 ML，使用訓練過的模型來區分品質良好的食品和品質不佳的食品，不僅僅是通過明顯的顏色差異（例如綠色番茄與紅色番茄），還包括外觀上的微妙差異，例如疾病或碰傷。

## 通過機器學習進行圖像分類

傳統編程是將數據輸入，應用算法，然後獲得輸出。例如，在上一個項目中，您輸入了 GPS 坐標和地理圍欄，應用了 Azure Maps 提供的算法，並獲得了該點是否在地理圍欄內或外的結果。輸入更多數據，您就能獲得更多輸出。

![傳統開發是輸入數據和算法，然後獲得輸出。機器學習則是使用輸入和輸出數據來訓練模型，該模型可以使用新輸入數據生成新輸出](../../../../../translated_images/traditional-vs-ml.5c20c169621fa539.hk.png)

機器學習則顛覆了這一過程——您從數據和已知輸出開始，機器學習算法從數據中學習。然後，您可以使用這個訓練過的算法（稱為 *機器學習模型* 或 *模型*），輸入新數據並獲得新輸出。

> 🎓 機器學習算法從數據中學習的過程稱為 *訓練*。輸入和已知輸出稱為 *訓練數據*。

例如，您可以提供數百萬張未成熟香蕉的圖片作為輸入訓練數據，並將訓練輸出設為 `未成熟`，再提供數百萬張成熟香蕉的圖片作為訓練數據，輸出設為 `成熟`。ML 算法會根據這些數據創建一個模型。然後，您可以將這個模型輸入一張新的香蕉圖片，它會預測該香蕉是成熟還是未成熟。

> 🎓 ML 模型的結果稱為 *預測*

![兩根香蕉，一根成熟的香蕉預測為 99.7% 成熟，0.3% 未成熟；另一根未成熟的香蕉預測為 1.4% 成熟，98.6% 未成熟](../../../../../translated_images/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50ece4e4589e724b142da0681f35470fe3db3f7d51240f69c85.hk.png)

ML 模型不會給出二元答案，而是提供概率。例如，模型可能會給出一張香蕉的圖片，預測 `成熟` 為 99.7%，`未成熟` 為 0.3%。您的代碼會選擇最佳預測並判斷該香蕉是成熟的。

用於檢測此類圖像的 ML 模型稱為 *圖像分類器*——它接收標記的圖像，並根據這些標記分類新圖像。

> 💁 這是一種簡化的解釋，還有許多其他訓練模型的方法，不一定需要標記的輸出，例如無監督學習。如果您想了解更多有關 ML 的知識，可以查看 [ML 初學者課程，一個包含 24 節課的機器學習課程](https://aka.ms/ML-beginners)。

## 訓練圖像分類器

要成功訓練圖像分類器，您需要數百萬張圖片。然而，事實證明，一旦您擁有一個基於數百萬或數十億張各種圖片訓練的圖像分類器，您可以重用它並使用少量圖片重新訓練它，並通過一種稱為 *遷移學習* 的過程獲得良好的結果。

> 🎓 遷移學習是指將現有 ML 模型的學習成果轉移到基於新數據的新模型中。

一旦圖像分類器已經針對各種圖片進行了訓練，它的內部就能很好地識別形狀、顏色和模式。遷移學習允許模型利用它已經學會的識別圖像部分的能力，來識別新圖像。

![一旦能識別形狀，它們可以被組合成不同的配置來形成船或貓](../../../../../translated_images/shapes-to-images.1a309f0ea88dd66f.hk.png)

您可以將其想像成兒童的形狀書籍，一旦您能識別半圓形、矩形和三角形，您就能根據這些形狀的配置識別出帆船或貓——或者成熟的香蕉。

有許多工具可以幫助您完成這項工作，包括基於雲的服務，這些服務可以幫助您訓練模型，然後通過 Web API 使用它。

> 💁 訓練這些模型需要大量的計算能力，通常通過圖形處理單元 (GPU) 實現。使 Xbox 遊戲看起來令人驚嘆的同樣專用硬件也可以用來訓練機器學習模型。通過使用雲端，您可以租用強大計算機的 GPU 訓練這些模型，只需支付您需要的時間。

## Custom Vision

Custom Vision 是一個基於雲的工具，用於訓練圖像分類器。它允許您僅使用少量圖片訓練分類器。您可以通過 Web 入口、Web API 或 SDK 上傳圖片，並為每張圖片提供一個 *標籤*，該標籤表示該圖片的分類。然後，您可以訓練模型並測試其性能。一旦您對模型感到滿意，您可以發布版本，通過 Web API 或 SDK 訪問。

![Azure Custom Vision 標誌](../../../../../translated_images/custom-vision-logo.d3d4e7c8a87ec9daf825e72e210576c3cbf60312577be7a139e22dd97ab7f1e6.hk.png)

> 💁 您可以使用每個分類僅 5 張圖片訓練 Custom Vision 模型，但更多圖片效果更好。至少 30 張圖片可以獲得更好的結果。

Custom Vision 是 Microsoft 提供的一系列 AI 工具的一部分，稱為 Cognitive Services。這些 AI 工具可以在不需要任何訓練或僅需少量訓練的情況下使用，包括語音識別和翻譯、語言理解和圖像分析。這些工具在 Azure 中提供免費層。

> 💁 免費層足以創建模型、訓練模型，然後用於開發工作。您可以在 [Microsoft Docs 上的 Custom Vision 限制和配額頁面](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn) 閱讀免費層的限制。

### 任務 - 創建 Cognitive Services 資源

要使用 Custom Vision，您需要使用 Azure CLI 在 Azure 中創建兩個 Cognitive Services 資源，一個用於 Custom Vision 訓練，另一個用於 Custom Vision 預測。

1. 為此項目創建一個名為 `fruit-quality-detector` 的資源組。

1. 使用以下命令創建一個免費的 Custom Vision 訓練資源：

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    將 `<location>` 替換為您創建資源組時使用的位置。

    這將在您的資源組中創建一個 Custom Vision 訓練資源。它將被命名為 `fruit-quality-detector-training`，並使用 `F0` sku，即免費層。`--yes` 選項表示您同意 Cognitive Services 的條款和條件。

> 💁 如果您已經使用任何 Cognitive Services 創建了免費帳戶，請使用 `S0` sku。

1. 使用以下命令創建一個免費的 Custom Vision 預測資源：

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    將 `<location>` 替換為您創建資源組時使用的位置。

    這將在您的資源組中創建一個 Custom Vision 預測資源。它將被命名為 `fruit-quality-detector-prediction`，並使用 `F0` sku，即免費層。`--yes` 選項表示您同意 Cognitive Services 的條款和條件。

### 任務 - 創建圖像分類器項目

1. 打開 [CustomVision.ai](https://customvision.ai) 的 Custom Vision 入口，並使用您 Azure 帳戶的 Microsoft 帳戶登錄。

1. 按照 [Microsoft Docs 上的快速入門指南中“創建新項目”部分](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project) 創建新的 Custom Vision 項目。UI 可能會有所變化，這些文檔始終是最新的參考。

    將您的項目命名為 `fruit-quality-detector`。

    創建項目時，請確保使用您之前創建的 `fruit-quality-detector-training` 資源。使用 *分類* 項目類型、*多類* 分類類型和 *食品* 領域。

    ![Custom Vision 項目的設置，名稱設為 fruit-quality-detector，無描述，資源設為 fruit-quality-detector-training，項目類型設為分類，分類類型設為多類，領域設為食品](../../../../../translated_images/custom-vision-create-project.cf46325b92d8b131089f6647cf5e07b664cb77850e106d66e3c057b6b69756c6.hk.png)

✅ 花些時間探索您的圖像分類器的 Custom Vision UI。

### 任務 - 訓練您的圖像分類器項目

要訓練圖像分類器，您需要多張水果的圖片，包括品質良好和品質不佳的水果，並標記為良好和不良，例如成熟和過熟的香蕉。
💁 這些分類器可以分類任何圖像，因此如果你手邊沒有不同品質的水果，你可以使用兩種不同類型的水果，或者貓和狗！
理想情況下，每張圖片應該只包含水果，背景要保持一致或有多種背景選擇。確保背景中沒有任何與成熟或未成熟水果相關的特定元素。

> 💁 背景或與標籤分類無關的特定物品不應出現在圖片中，否則分類器可能會根據背景進行分類。有一個皮膚癌分類器曾經用正常和癌症痣的圖片進行訓練，而癌症痣的圖片中都有尺子用來測量大小。結果分類器幾乎100%準確地識別了圖片中的尺子，而不是癌症痣。

圖片分類器的運行分辨率非常低。例如，Custom Vision可以接受最大10240x10240的訓練和預測圖片，但模型實際訓練和運行的圖片分辨率為227x227。較大的圖片會被縮小到這個尺寸，因此確保您要分類的物品在圖片中占據較大部分，否則在分類器使用的小圖片中可能會太小。

1. 收集分類器所需的圖片。每個標籤至少需要5張圖片來訓練分類器，但越多越好。您還需要一些額外的圖片來測試分類器。這些圖片應該是同一物品的不同圖片。例如：

    * 使用2根成熟的香蕉，從不同角度拍攝每根香蕉的幾張圖片，至少拍攝7張（5張用於訓練，2張用於測試），但理想情況下更多。

        ![2根不同香蕉的照片](../../../../../translated_images/banana-training-images.530eb203346d73bc23b8b990fb4609470bf4ff7c942ccc13d4cfffeed9be1ad4.hk.png)

    * 使用2根未成熟的香蕉重複相同的過程。

    您應該至少有10張訓練圖片，其中至少5張成熟，5張未成熟，還有4張測試圖片，2張成熟，2張未成熟。您的圖片應該是png或jpeg格式，大小小於6MB。如果您使用iPhone拍攝，它們可能是高分辨率的HEIC圖片，因此需要進行格式轉換並可能縮小尺寸。圖片越多越好，並且成熟和未成熟的數量應該相近。

    如果您沒有成熟和未成熟的水果，可以使用不同的水果，或者任何您手頭上的兩種物品。您也可以在[images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images)文件夾中找到一些成熟和未成熟香蕉的示例圖片供您使用。

1. 按照[Microsoft文檔中建立分類器快速入門的上傳和標記圖片部分](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images)的指引上傳您的訓練圖片。將成熟的水果標記為`ripe`，未成熟的水果標記為`unripe`。

    ![上傳成熟和未成熟香蕉圖片的對話框](../../../../../translated_images/image-upload-bananas.0751639f3815e0ec42bdbc6254d1e4357a185834d1ae10c9948a0e7d6d336695.hk.png)

1. 按照[Microsoft文檔中建立分類器快速入門的訓練分類器部分](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier)的指引，使用您上傳的圖片訓練圖片分類器。

    您將會看到訓練類型的選擇。選擇**快速訓練**。

分類器將開始訓練。訓練完成需要幾分鐘。

> 🍌 如果您在分類器訓練期間決定吃掉您的水果，請確保您有足夠的圖片進行測試！

## 測試您的圖片分類器

分類器訓練完成後，您可以通過提供新的圖片進行分類測試。

### 任務 - 測試您的圖片分類器

1. 按照[Microsoft文檔中測試模型的指引](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model)測試您的圖片分類器。使用您之前創建的測試圖片，而不是任何用於訓練的圖片。

    ![一根未成熟香蕉被預測為未成熟，概率為98.9%，成熟概率為1.1%](../../../../../translated_images/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64886422438850ea14f0be6ac918c217ea3b255c685abfabe7.hk.png)

1. 嘗試使用您所有的測試圖片並觀察概率。

## 重新訓練您的圖片分類器

當您測試分類器時，它可能不會給出您期望的結果。圖片分類器使用機器學習根據圖片中的特定特徵來預測它是否匹配某個標籤。它並不理解圖片中的內容——它不知道什麼是香蕉，也不理解什麼使香蕉成為香蕉而不是船。您可以通過使用分類器錯誤的圖片重新訓練來改進分類器。

每次使用快速測試選項進行預測時，圖片和結果都會被存儲。您可以使用這些圖片重新訓練您的模型。

### 任務 - 重新訓練您的圖片分類器

1. 按照[Microsoft文檔中使用預測圖片進行訓練的指引](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training)重新訓練您的模型，為每張圖片使用正確的標籤。

1. 模型重新訓練完成後，使用新的圖片進行測試。

---

## 🚀 挑戰

如果您使用一張草莓的圖片測試一個訓練了香蕉的模型，或者使用一張充氣香蕉的圖片、一個穿香蕉服的人、甚至一個黃色卡通角色（例如《辛普森一家》中的角色），您認為會發生什麼？

試試看，看看預測結果是什麼。您可以使用[Bing圖片搜索](https://www.bing.com/images/trending)找到圖片進行測試。

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## 回顧與自學

* 當您訓練分類器時，您會看到*Precision*、*Recall*和*AP*的值，這些值用於評估所創建的模型。通過[Microsoft文檔中建立分類器快速入門的評估分類器部分](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier)了解這些值的含義。
* 通過[Microsoft文檔中如何改進您的Custom Vision模型](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn)了解如何改進您的分類器。

## 作業

[為多種水果和蔬菜訓練您的分類器](assignment.md)

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言版本的文件應被視為具權威性的來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。