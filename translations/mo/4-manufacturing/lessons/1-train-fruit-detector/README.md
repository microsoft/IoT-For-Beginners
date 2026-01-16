<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f5e63c916d2dd97d58be12aaf76bd9f1",
  "translation_date": "2025-08-26T21:44:01+00:00",
  "source_file": "4-manufacturing/lessons/1-train-fruit-detector/README.md",
  "language_code": "mo"
}
-->
# 訓練水果品質檢測器

![本課程的手繪筆記概覽](../../../../../translated_images/mo/lesson-15.843d21afdc6fb2bba70cd9db7b7d2f91598859fafda2078b0bdc44954194b6c0.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大版本。

這段影片概述了 Azure Custom Vision 服務，這是本課程將涵蓋的主題。

[![Custom Vision – 機器學習變得簡單 | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 點擊上方圖片觀看影片

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## 簡介

人工智慧（AI）和機器學習（ML）的快速發展為當今的開發者提供了廣泛的功能。ML 模型可以被訓練來識別圖像中的不同事物，包括未成熟的水果，這些技術可以應用於物聯網（IoT）設備中，幫助在收穫或工廠、倉庫的加工過程中對農產品進行分類。

在本課程中，您將學習圖像分類——使用 ML 模型來區分不同事物的圖像。您將學會如何訓練一個圖像分類器來區分品質好的水果和品質差的水果，例如未成熟、過熟、碰傷或腐爛的水果。

本課程將涵蓋以下內容：

* [使用 AI 和 ML 進行食品分類](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [通過機器學習進行圖像分類](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [訓練圖像分類器](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [測試您的圖像分類器](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [重新訓練您的圖像分類器](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## 使用 AI 和 ML 進行食品分類

養活全球人口是一項艱鉅的任務，尤其是在確保食品價格對所有人都負擔得起的情況下。勞動力成本是其中最大的開支之一，因此農民越來越多地轉向自動化和物聯網等工具來降低勞動成本。手工收穫勞動強度大（且通常是非常辛苦的工作），在富裕國家尤其被機械化所取代。然而，儘管使用機械收穫降低了成本，但也帶來了一個缺點——無法在收穫時對食品進行分類。

並非所有作物都能均勻成熟。例如，番茄在大多數果實成熟時，藤上可能仍有一些綠色果實。雖然提前收穫這些果實是一種浪費，但對農民來說，使用機械一次性收穫所有果實，然後再處理未成熟的果實，成本更低且更方便。

✅ 看看您附近農場或花園中正在生長的水果或蔬菜，或者商店裡的水果或蔬菜。它們是否都達到了相同的成熟度，還是存在差異？

自動化收穫的興起將農產品的分類從田間轉移到了工廠。食品會通過長長的傳送帶，人工團隊會挑選出不符合質量標準的產品。雖然機械化收穫降低了成本，但手動分類食品仍然需要一定的開支。

![如果檢測到紅色番茄，它會繼續前進。如果檢測到綠色番茄，槓桿會將其彈入廢料箱](../../../../../translated_images/mo/optical-tomato-sorting.61aa134bdda4e5b1bfb16a212c1e35a6ef0c426cbb8b1c975f79d7bfbf48d068.png)

下一代技術是使用機器進行分類，這些機器可以內置於收穫機中，也可以用於加工廠。第一代這類機器使用光學傳感器檢測顏色，通過控制執行器將綠色番茄推入廢料箱，而紅色番茄則繼續沿著傳送帶網絡前進。

在這段影片中，當番茄從一條傳送帶掉落到另一條時，綠色番茄會被檢測到並通過槓桿彈入廢料箱。

✅ 在工廠或田間，這些光學傳感器需要什麼條件才能正常工作？

最新一代的分類機器利用 AI 和 ML 的優勢，使用經過訓練的模型來區分優質和劣質的農產品，不僅僅是通過顏色差異（如綠色番茄與紅色番茄），還包括能夠表明疾病或碰傷的更細微的外觀差異。

## 通過機器學習進行圖像分類

傳統編程是將數據與算法結合，然後獲得輸出。例如，在上一個項目中，您將 GPS 坐標和地理圍欄作為輸入，應用 Azure Maps 提供的算法，並獲得該點是否在地理圍欄內的結果。輸入更多數據，就會獲得更多輸出。

![傳統開發使用輸入和算法生成輸出。機器學習使用輸入和輸出數據來訓練模型，該模型可以使用新輸入數據生成新輸出](../../../../../translated_images/mo/traditional-vs-ml.5c20c169621fa539.webp)

機器學習則反其道而行之——您從數據和已知輸出開始，機器學習算法從數據中學習。然後，您可以使用這個經過訓練的算法（稱為 *機器學習模型* 或 *模型*），輸入新數據並獲得新輸出。

> 🎓 機器學習算法從數據中學習的過程稱為 *訓練*。輸入和已知輸出稱為 *訓練數據*。

例如，您可以向模型提供數百萬張未成熟香蕉的圖片作為輸入訓練數據，並將訓練輸出設置為 `未成熟`，同時提供數百萬張成熟香蕉的圖片作為訓練數據，輸出設置為 `成熟`。ML 算法會基於這些數據創建一個模型。然後，您可以向該模型提供一張新的香蕉圖片，它會預測該香蕉是成熟還是未成熟。

> 🎓 ML 模型的結果稱為 *預測*

![兩根香蕉，一根成熟的預測為 99.7% 成熟，0.3% 未成熟；另一根未成熟的預測為 1.4% 成熟，98.6% 未成熟](../../../../../translated_images/mo/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50ece4e4589e724b142da0681f35470fe3db3f7d51240f69c85.png)

ML 模型不會給出二元答案，而是提供概率。例如，模型可能會給出一張香蕉圖片，預測 `成熟` 的概率為 99.7%，`未成熟` 的概率為 0.3%。您的代碼會選擇最可能的預測，並判斷該香蕉是成熟的。

用於檢測這類圖像的 ML 模型稱為 *圖像分類器*——它接收帶標籤的圖像，然後根據這些標籤對新圖像進行分類。

> 💁 這是一種簡化的描述，還有許多其他訓練模型的方法，例如無需標籤輸出的無監督學習。如果您想深入了解 ML，請參考 [ML for beginners，一個包含 24 節課的機器學習課程](https://aka.ms/ML-beginners)。

## 訓練圖像分類器

要成功訓練一個圖像分類器，您需要數百萬張圖片。然而，事實證明，一旦您擁有一個基於數百萬或數十億張各類圖片訓練的圖像分類器，您可以通過一小部分圖片重新訓練它，並獲得出色的結果，這個過程稱為 *遷移學習*。

> 🎓 遷移學習是將現有 ML 模型的學習成果轉移到基於新數據的新模型上的過程。

一旦圖像分類器已經針對各種圖像進行了訓練，它的內部結構就非常擅長識別形狀、顏色和模式。遷移學習允許模型利用它已經學會的圖像部分識別能力，來識別新圖像。

![一旦您能識別形狀，這些形狀可以組合成不同的配置，例如船或貓](../../../../../translated_images/mo/shapes-to-images.1a309f0ea88dd66f.webp)

您可以將其想像成兒童的形狀書籍，一旦您能識別半圓形、矩形和三角形，您就能根據這些形狀的配置識別出帆船或貓。圖像分類器可以識別形狀，而遷移學習則教會它什麼樣的組合構成帆船或貓——或者成熟的香蕉。

有許多工具可以幫助您完成這一過程，包括基於雲的服務，這些服務可以幫助您訓練模型，然後通過 Web API 使用它。

> 💁 訓練這些模型需要大量的計算能力，通常通過圖形處理單元（GPU）實現。與 Xbox 上讓遊戲畫面看起來令人驚嘆的專用硬件相同，GPU 也可以用來訓練機器學習模型。通過使用雲服務，您可以租用配備 GPU 的強大計算機來訓練這些模型，只需支付您使用的時間。

## Custom Vision

Custom Vision 是一種基於雲的工具，用於訓練圖像分類器。它允許您僅使用少量圖片來訓練分類器。您可以通過 Web 入口、Web API 或 SDK 上傳圖片，並為每張圖片添加 *標籤*，以標識該圖片的分類。然後，您可以訓練模型並測試其性能。一旦對模型感到滿意，您可以發布模型的版本，通過 Web API 或 SDK 訪問它。

![Azure Custom Vision 標誌](../../../../../translated_images/mo/custom-vision-logo.d3d4e7c8a87ec9daf825e72e210576c3cbf60312577be7a139e22dd97ab7f1e6.png)

> 💁 您可以使用每個分類僅 5 張圖片來訓練 Custom Vision 模型，但圖片越多效果越好。至少 30 張圖片可以獲得更好的結果。

Custom Vision 是 Microsoft 提供的一系列 AI 工具（稱為 Cognitive Services）的一部分。這些 AI 工具可以在無需訓練或僅需少量訓練的情況下使用，包括語音識別與翻譯、語言理解和圖像分析。這些工具在 Azure 上提供免費層。

> 💁 免費層足以創建模型、訓練模型，然後用於開發工作。您可以在 [Microsoft 文檔上的 Custom Vision 限制與配額頁面](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn) 上了解免費層的限制。

### 任務 - 創建認知服務資源

要使用 Custom Vision，您需要先使用 Azure CLI 在 Azure 中創建兩個認知服務資源，一個用於 Custom Vision 訓練，另一個用於 Custom Vision 預測。

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

    將 `<location>` 替換為創建資源組時使用的位置。

    這將在您的資源組中創建一個 Custom Vision 訓練資源。它將被命名為 `fruit-quality-detector-training`，並使用免費層的 `F0` SKU。`--yes` 選項表示您同意認知服務的條款和條件。

> 💁 如果您已經有一個免費帳戶正在使用任何認知服務，請使用 `S0` SKU。

1. 使用以下命令創建一個免費的 Custom Vision 預測資源：

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    將 `<location>` 替換為創建資源組時使用的位置。

    這將在您的資源組中創建一個 Custom Vision 預測資源。它將被命名為 `fruit-quality-detector-prediction`，並使用免費層的 `F0` SKU。`--yes` 選項表示您同意認知服務的條款和條件。

### 任務 - 創建圖像分類器項目

1. 打開 [CustomVision.ai](https://customvision.ai) 的 Custom Vision 入口，並使用您 Azure 帳戶的 Microsoft 帳戶登錄。

1. 按照 [Microsoft 文檔中分類器快速入門的創建新項目部分](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project) 的指導創建一個新的 Custom Vision 項目。UI 可能會有所變化，這些文檔始終是最新的參考。

    將您的項目命名為 `fruit-quality-detector`。

    創建項目時，請確保使用您之前創建的 `fruit-quality-detector-training` 資源。選擇 *分類* 項目類型、*多分類* 分類類型，並選擇 *食品* 領域。

    ![Custom Vision 項目的設置，名稱設置為 fruit-quality-detector，無描述，資源設置為 fruit-quality-detector-training，項目類型設置為分類，分類類型設置為多分類，領域設置為食品](../../../../../translated_images/mo/custom-vision-create-project.cf46325b92d8b131089f6647cf5e07b664cb77850e106d66e3c057b6b69756c6.png)

✅ 花些時間探索您的圖像分類器的 Custom Vision UI。

### 任務 - 訓練您的圖像分類器項目

要訓練圖像分類器，您需要多張水果的圖片，包括品質好的和品質差的，並將其標記為好或壞，例如成熟的香蕉和過熟的香蕉。
💁 這些分類器可以用來分類任何圖像，因此如果你手邊沒有品質不同的水果，你可以使用兩種不同類型的水果，或者貓和狗！
理想情況下，每張照片應該只包含水果，背景要保持一致或有多種背景選擇。確保背景中沒有任何與成熟或未成熟水果相關的特定元素。

> 💁 很重要的是不要有特定的背景或與分類標籤無關的物品，否則分類器可能會根據背景進行分類。有一個皮膚癌分類器曾經用正常和癌症痣的照片進行訓練，而癌症痣的照片中都有尺子用來測量大小。結果分類器幾乎100%準確地識別了照片中的尺子，而不是癌症痣。

影像分類器運行時解析度非常低。例如，Custom Vision可以處理最大10240x10240的訓練和預測影像，但模型實際訓練和運行時使用的是227x227的影像。較大的影像會縮小到這個尺寸，因此確保您要分類的物品在影像中占據較大的部分，否則在縮小的影像中可能會太小而無法被分類器識別。

1. 收集分類器所需的照片。每個標籤至少需要5張照片來訓練分類器，但越多越好。此外，還需要一些額外的照片來測試分類器。這些照片應該是同一物品的不同照片。例如：

    * 使用2根成熟的香蕉，從不同角度拍攝每根香蕉的幾張照片，至少拍攝7張（5張用於訓練，2張用於測試），但最好更多。

        ![2根不同香蕉的照片](../../../../../translated_images/mo/banana-training-images.530eb203346d73bc23b8b990fb4609470bf4ff7c942ccc13d4cfffeed9be1ad4.png)

    * 使用2根未成熟的香蕉重複相同的過程。

    您應該至少有10張訓練照片，其中至少5張成熟，5張未成熟，還有4張測試照片，2張成熟，2張未成熟。您的照片應該是png或jpeg格式，大小小於6MB。如果您使用iPhone拍攝，它可能是高解析度的HEIC格式，需進行轉換並可能縮小尺寸。照片越多越好，並且成熟和未成熟的數量應該相近。

    如果您沒有成熟和未成熟的水果，可以使用不同的水果或任何可用的兩種物品。您也可以在[images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images)文件夾中找到一些成熟和未成熟香蕉的示例照片供您使用。

1. 按照[Microsoft Docs上的分類器快速入門中上傳和標記影像的部分](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images)上傳您的訓練影像。將成熟的水果標記為`ripe`，未成熟的水果標記為`unripe`。

    ![上傳成熟和未成熟香蕉照片的對話框](../../../../../translated_images/mo/image-upload-bananas.0751639f3815e0ec42bdbc6254d1e4357a185834d1ae10c9948a0e7d6d336695.png)

1. 按照[Microsoft Docs上的分類器快速入門中訓練分類器的部分](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier)訓練影像分類器。

    您將看到訓練類型的選擇。選擇**快速訓練**。

分類器將開始訓練。訓練完成需要幾分鐘。

> 🍌 如果您在分類器訓練期間決定吃掉您的水果，請確保您已經準備好足夠的測試影像！

## 測試您的影像分類器

分類器訓練完成後，您可以通過提供新的影像進行分類測試。

### 任務 - 測試您的影像分類器

1. 按照[Microsoft Docs上的測試模型文檔](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model)測試您的影像分類器。使用您之前創建的測試影像，而不是任何用於訓練的影像。

    ![一根未成熟香蕉被預測為未成熟，概率為98.9%，成熟概率為1.1%](../../../../../translated_images/mo/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64886422438850ea14f0be6ac918c217ea3b255c685abfabe7.png)

1. 嘗試使用您所有的測試影像並觀察概率。

## 重新訓練您的影像分類器

當您測試分類器時，它可能不會給出您期望的結果。影像分類器使用機器學習根據影像中的特定特徵來預測影像是否匹配某個標籤。它並不理解影像中的內容——它不知道香蕉是什麼，也不理解什麼使香蕉成為香蕉而不是船。您可以通過使用分類器錯誤的影像重新訓練來改進分類器。

每次使用快速測試選項進行預測時，影像和結果都會被存儲。您可以使用這些影像重新訓練您的模型。

### 任務 - 重新訓練您的影像分類器

1. 按照[Microsoft Docs上的使用預測影像進行訓練文檔](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training)使用每張影像的正確標籤重新訓練您的模型。

1. 模型重新訓練完成後，使用新的影像進行測試。

---

## 🚀 挑戰

如果您使用一張草莓的照片測試一個訓練過香蕉的模型，或者使用一張充氣香蕉的照片、一個穿香蕉服的人、甚至一個黃色卡通角色（例如辛普森家族中的角色），您認為會發生什麼？

試試看，看看預測結果是什麼。您可以使用[Bing影像搜索](https://www.bing.com/images/trending)找到影像進行測試。

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## 回顧與自學

* 當您訓練分類器時，您會看到*Precision*、*Recall*和*AP*的值，這些值用於評估所創建的模型。通過[Microsoft Docs上的分類器快速入門中評估分類器的部分](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier)了解這些值的含義。
* 通過[Microsoft Docs上的如何改進您的Custom Vision模型](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn)了解如何改進您的分類器。

## 作業

[為多種水果和蔬菜訓練您的分類器](assignment.md)

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。