<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-26T22:04:19+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "mo"
}
-->
# 使用基於 IoT Edge 的影像分類器來分類影像 - 虛擬 IoT 硬體與 Raspberry Pi

在本課程的這部分，您將使用運行於 IoT Edge 裝置上的影像分類器。

## 使用 IoT Edge 分類器

IoT 裝置可以重新導向以使用 IoT Edge 影像分類器。影像分類器的 URL 是 `http://<IP address or name>/image`，將 `<IP address or name>` 替換為運行 IoT Edge 的電腦的 IP 位址或主機名稱。

Custom Vision 的 Python 函式庫僅適用於雲端託管的模型，而不適用於 IoT Edge 上的模型。這意味著您需要使用 REST API 來呼叫分類器。

### 任務 - 使用 IoT Edge 分類器

1. 如果尚未開啟，請在 VS Code 中開啟 `fruit-quality-detector` 專案。如果您使用的是虛擬 IoT 裝置，請確保虛擬環境已啟動。

1. 開啟 `app.py` 檔案，並移除來自 `azure.cognitiveservices.vision.customvision.prediction` 和 `msrest.authentication` 的匯入語句。

1. 在檔案頂部新增以下匯入語句：

    ```python
    import requests
    ```

1. 刪除從 `image_file.write(image.read())` 到檔案結尾的所有程式碼。

1. 在檔案結尾新增以下程式碼：

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    將 `<URL>` 替換為您的分類器的 URL。

    此程式碼會向分類器發送一個 REST POST 請求，將影像作為請求的主體發送。結果以 JSON 格式返回，並解碼以列印出概率。

1. 執行您的程式碼，將相機對準一些水果，或使用適當的影像集，或者如果使用虛擬 IoT 硬體，則讓水果在您的網路攝影機中可見。您將在控制台中看到輸出：

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 您可以在 [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) 或 [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) 資料夾中找到此程式碼。

😀 您的水果品質分類器程式成功了！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。