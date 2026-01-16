<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-26T14:11:42+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "hk"
}
-->
# 分類圖片 - 虛擬 IoT 硬件及 Raspberry Pi

在本課程的這部分，你將把相機捕捉的圖片發送到 Custom Vision 服務進行分類。

## 發送圖片到 Custom Vision

Custom Vision 服務提供了一個 Python SDK，可用於分類圖片。

### 任務 - 發送圖片到 Custom Vision

1. 在 VS Code 中打開 `fruit-quality-detector` 文件夾。如果你使用的是虛擬 IoT 設備，請確保虛擬環境已在終端中運行。

1. 用於發送圖片到 Custom Vision 的 Python SDK 是一個 Pip 套件。使用以下命令安裝它：

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. 在 `app.py` 文件的頂部添加以下導入語句：

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    這將引入一些 Custom Vision 庫中的模組，一個用於使用預測密鑰進行身份驗證，另一個提供可以調用 Custom Vision 的預測客戶端類。

1. 在文件末尾添加以下代碼：

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    將 `<prediction_url>` 替換為你在本課程早些時候從 *Prediction URL* 對話框中複製的 URL。將 `<prediction key>` 替換為你從同一對話框中複製的預測密鑰。

1. *Prediction URL* 對話框提供的預測 URL 是為直接調用 REST 端點而設計的。Python SDK 在不同的地方使用 URL 的部分。添加以下代碼以拆分此 URL，提取所需的部分：

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    這將拆分 URL，提取 `https://<location>.api.cognitive.microsoft.com` 的端點、項目 ID 和已發布迭代的名稱。

1. 創建一個預測器對象以執行預測，使用以下代碼：

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` 將預測密鑰封裝起來。然後使用這些憑證創建一個指向端點的預測客戶端對象。

1. 使用以下代碼將圖片發送到 Custom Vision：

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    這會將圖片回卷到起始位置，然後將其發送到預測客戶端。

1. 最後，使用以下代碼顯示結果：

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    這將遍歷所有返回的預測並在終端上顯示它們。返回的概率是 0-1 的浮點數，其中 0 表示與標籤匹配的可能性為 0%，1 表示與標籤匹配的可能性為 100%。

    > 💁 圖片分類器將返回所有使用過的標籤的百分比。每個標籤都會有一個圖片與該標籤匹配的概率。

1. 運行你的代碼，讓相機對準一些水果，或者使用適當的圖片集，或者如果使用虛擬 IoT 硬件，讓水果在你的網絡攝像頭中可見。你將在控制台中看到輸出：

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    你將能看到拍攝的圖片，以及這些值在 Custom Vision 的 **Predictions** 標籤中。

    ![一根香蕉在 Custom Vision 中被預測為成熟的概率為 56.8%，未成熟的概率為 43.1%](../../../../../translated_images/hk/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 你可以在 [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) 或 [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) 文件夾中找到這段代碼。

😀 你的水果品質分類器程序成功了！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。