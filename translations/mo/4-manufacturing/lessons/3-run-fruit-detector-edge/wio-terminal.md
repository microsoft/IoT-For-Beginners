<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-26T22:03:41+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "mo"
}
-->
# 使用 IoT Edge 基於影像分類器進行影像分類 - Wio Terminal

在本課程的這部分，您將使用運行在 IoT Edge 裝置上的影像分類器。

## 使用 IoT Edge 影像分類器

IoT 裝置可以重新導向使用 IoT Edge 影像分類器。影像分類器的 URL 是 `http://<IP address or name>/image`，其中 `<IP address or name>` 需要替換為運行 IoT Edge 的電腦的 IP 地址或主機名稱。

### 任務 - 使用 IoT Edge 影像分類器

1. 如果尚未打開 `fruit-quality-detector` 應用程式專案，請打開它。

1. 影像分類器作為 REST API 運行，使用的是 HTTP 而非 HTTPS，因此呼叫需要使用僅支援 HTTP 呼叫的 WiFi 客戶端。這意味著不需要憑證。刪除 `config.h` 文件中的 `CERTIFICATE`。

1. `config.h` 文件中的預測 URL 需要更新為新的 URL。您也可以刪除 `PREDICTION_KEY`，因為這不再需要。

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    將 `<URL>` 替換為您的分類器的 URL。

1. 在 `main.cpp` 中，將 WiFi Client Secure 的 include 指令改為導入標準的 HTTP 版本：

    ```cpp
    #include <WiFiClient.h>
    ```

1. 將 `WiFiClient` 的宣告更改為 HTTP 版本：

    ```cpp
    WiFiClient client;
    ```

1. 找到在 WiFi 客戶端上設置憑證的那一行。從 `connectWiFi` 函數中移除 `client.setCACert(CERTIFICATE);` 這一行。

1. 在 `classifyImage` 函數中，移除 `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` 這一行，該行用於在標頭中設置預測密鑰。

1. 上傳並運行您的程式。將相機對準一些水果並按下 C 按鈕。您將在序列監視器中看到輸出：

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 您可以在 [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) 資料夾中找到這段程式碼。

😀 您的水果品質分類器程式成功了！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。