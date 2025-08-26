<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-26T14:20:08+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "hk"
}
-->
# 使用基於 IoT Edge 的影像分類器進行影像分類 - Wio Terminal

在本課程中，您將使用運行於 IoT Edge 裝置上的影像分類器。

## 使用 IoT Edge 分類器

IoT 裝置可以重新定向以使用 IoT Edge 影像分類器。影像分類器的 URL 是 `http://<IP address or name>/image`，將 `<IP address or name>` 替換為運行 IoT Edge 的電腦的 IP 地址或主機名稱。

### 任務 - 使用 IoT Edge 分類器

1. 如果尚未打開 `fruit-quality-detector` 應用程式專案，請將其打開。

1. 影像分類器作為使用 HTTP 的 REST API 運行，而非 HTTPS，因此需要使用僅支援 HTTP 呼叫的 WiFi 客戶端。這意味著不需要憑證。刪除 `config.h` 文件中的 `CERTIFICATE`。

1. 需要將 `config.h` 文件中的預測 URL 更新為新的 URL。您也可以刪除 `PREDICTION_KEY`，因為這不再需要。

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    將 `<URL>` 替換為您的分類器的 URL。

1. 在 `main.cpp` 中，將 WiFi Client Secure 的 include 指令更改為導入標準的 HTTP 版本：

    ```cpp
    #include <WiFiClient.h>
    ```

1. 將 `WiFiClient` 的宣告更改為 HTTP 版本：

    ```cpp
    WiFiClient client;
    ```

1. 找到設置 WiFi 客戶端憑證的那一行。在 `connectWiFi` 函數中，移除 `client.setCACert(CERTIFICATE);` 這一行。

1. 在 `classifyImage` 函數中，移除設置預測金鑰的這一行：`httpClient.addHeader("Prediction-Key", PREDICTION_KEY);`。

1. 上傳並運行您的程式。將相機對準一些水果，然後按下 C 按鈕。您將在序列監視器中看到輸出：

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 您可以在 [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) 資料夾中找到此程式碼。

😀 您的水果品質分類器程式成功了！

---

**免責聲明**：  
此文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議使用專業的人類翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解讀概不負責。