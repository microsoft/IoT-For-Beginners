<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-24T22:27:43+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "tw"
}
-->
# 添加手動繼電器控制

## 說明

無伺服器代碼可以由多種方式觸發，包括 HTTP 請求。您可以使用 HTTP 觸發器為您的繼電器控制添加手動覆蓋功能，允許某人通過網頁請求開啟或關閉繼電器。

在這項任務中，您需要為您的 Functions App 添加兩個 HTTP 觸發器來開啟和關閉繼電器，並重用您在本課中學到的知識來向設備發送命令。

一些提示：

* 您可以使用以下命令為現有的 Functions App 添加 HTTP 觸發器：

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    將 `<trigger name>` 替換為您的 HTTP 觸發器名稱。可以使用類似 `relay_on` 和 `relay_off` 的名稱。

* HTTP 觸發器可以設置訪問控制。默認情況下，它們需要在 URL 中傳遞特定於函數的 API 金鑰才能運行。對於這項任務，您可以移除此限制，讓任何人都能運行該函數。為此，請更新 HTTP 觸發器的 `function.json` 文件中的 `authLevel` 設置為以下內容：

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 您可以在 [Function access keys documentation](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys) 中閱讀更多關於此訪問控制的內容。

* HTTP 觸發器默認支持 GET 和 POST 請求。這意味著您可以使用網頁瀏覽器調用它們——網頁瀏覽器會發送 GET 請求。

    當您在本地運行 Functions App 時，您將看到觸發器的 URL：

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    將 URL 粘貼到瀏覽器中並按下 `回車鍵`，或者在 VS Code 的終端窗口中 `Ctrl+點擊`（macOS 上為 `Cmd+點擊`）該鏈接以在默認瀏覽器中打開它。這將運行觸發器。

    > 💁 注意 URL 中包含 `/api`——HTTP 觸發器默認位於 `api` 子域中。

* 當您部署 Functions App 時，HTTP 觸發器的 URL 將是：

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    其中 `<functions app name>` 是您的 Functions App 的名稱，`<trigger name>` 是您的觸發器名稱。

## 評分標準

| 評分項目 | 優秀 | 合格 | 需要改進 |
| -------- | ---- | ---- | -------- |
| 創建 HTTP 觸發器 | 創建了兩個觸發器來開啟和關閉繼電器，並使用了合適的名稱 | 創建了一個具有合適名稱的觸發器 | 未能創建任何觸發器 |
| 從 HTTP 觸發器控制繼電器 | 能夠將兩個觸發器連接到 IoT Hub 並正確控制繼電器 | 能夠將一個觸發器連接到 IoT Hub 並正確控制繼電器 | 未能將觸發器連接到 IoT Hub |

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議使用專業人工翻譯。我們對因使用此翻譯而產生的任何誤解或錯誤解釋不承擔責任。