<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-26T14:40:36+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "hk"
}
-->
# 添加手動繼電器控制

## 指示

無伺服器代碼可以由多種方式觸發，包括 HTTP 請求。你可以使用 HTTP 觸發器為你的繼電器控制添加手動覆蓋功能，讓使用者可以通過網絡請求開啟或關閉繼電器。

在這個任務中，你需要為你的 Functions App 添加兩個 HTTP 觸發器，用於開啟和關閉繼電器，並重用你在本課中學到的知識來向設備發送指令。

一些提示：

* 你可以使用以下命令為現有的 Functions App 添加 HTTP 觸發器：

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    將 `<trigger name>` 替換為你的 HTTP 觸發器的名稱。可以使用類似 `relay_on` 和 `relay_off` 的名稱。

* HTTP 觸發器可以設置訪問控制。默認情況下，它們需要在 URL 中傳遞特定於函數的 API 密鑰才能運行。對於這個任務，你可以移除這個限制，讓任何人都可以運行該函數。為此，更新 HTTP 觸發器的 `function.json` 文件中的 `authLevel` 設置為以下內容：

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 你可以在 [Function access keys documentation](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys) 中閱讀更多關於訪問控制的內容。

* HTTP 觸發器默認支持 GET 和 POST 請求。這意味著你可以使用網絡瀏覽器調用它們——網絡瀏覽器會發送 GET 請求。

    當你在本地運行你的 Functions App 時，你會看到觸發器的 URL：

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    將 URL 粘貼到瀏覽器中並按 `return`，或者在 VS Code 的終端窗口中 `Ctrl+點擊`（macOS 上為 `Cmd+點擊`）鏈接以在默認瀏覽器中打開。這將運行觸發器。

    > 💁 注意 URL 中包含 `/api`——HTTP 觸發器默認位於 `api` 子域中。

* 當你部署 Functions App 時，HTTP 觸發器的 URL 將是：

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    其中 `<functions app name>` 是你的 Functions App 的名稱，`<trigger name>` 是你的觸發器的名稱。

## 評分標準

| 評分標準 | 優秀 | 合格 | 需要改進 |
| -------- | --------- | -------- | ----------------- |
| 創建 HTTP 觸發器 | 創建了兩個觸發器來開啟和關閉繼電器，並使用了適當的名稱 | 創建了一個具有適當名稱的觸發器 | 未能創建任何觸發器 |
| 從 HTTP 觸發器控制繼電器 | 能夠將兩個觸發器連接到 IoT Hub 並適當地控制繼電器 | 能夠將一個觸發器連接到 IoT Hub 並適當地控制繼電器 | 未能將觸發器連接到 IoT Hub |

---

**免責聲明**：  
此文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解讀概不負責。