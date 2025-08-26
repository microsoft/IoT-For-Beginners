<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-26T14:20:36+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "hk"
}
-->
# 使用 IoT Edge 基於影像分類器對圖片進行分類 - 虛擬 IoT 硬件及 Raspberry Pi

在這部分課程中，你將使用運行於 IoT Edge 設備上的影像分類器。

## 使用 IoT Edge 分類器

IoT 設備可以被重新定向以使用 IoT Edge 影像分類器。影像分類器的 URL 是 `http://<IP address or name>/image`，將 `<IP address or name>` 替換為運行 IoT Edge 的電腦的 IP 地址或主機名稱。

Custom Vision 的 Python 庫僅適用於雲端託管的模型，而不適用於 IoT Edge 託管的模型。這意味著你需要使用 REST API 來調用分類器。

### 任務 - 使用 IoT Edge 分類器

1. 如果尚未打開，請在 VS Code 中打開 `fruit-quality-detector` 專案。如果你正在使用虛擬 IoT 設備，請確保虛擬環境已啟動。

1. 打開 `app.py` 文件，刪除來自 `azure.cognitiveservices.vision.customvision.prediction` 和 `msrest.authentication` 的 import 語句。

1. 在文件頂部添加以下 import 語句：

    ```python
    import requests
    ```

1. 刪除從 `image_file.write(image.read())` 到文件末尾的所有代碼。

1. 在文件末尾添加以下代碼：

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

    將 `<URL>` 替換為你的分類器的 URL。

    這段代碼會向分類器發送一個 REST POST 請求，將圖片作為請求的主體發送。結果以 JSON 格式返回，並被解碼以打印出概率。

1. 運行你的代碼，將相機對準一些水果，或者使用適當的圖片集，或者如果使用虛擬 IoT 硬件，則讓水果在你的網絡攝像頭中可見。你會在控制台中看到輸出：

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 你可以在 [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) 或 [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) 文件夾中找到這段代碼。

😀 你的水果品質分類器程序運行成功了！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。