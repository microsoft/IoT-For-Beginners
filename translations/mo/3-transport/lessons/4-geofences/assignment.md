<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-27T00:41:47+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "mo"
}
-->
# 使用 Twilio 發送通知

## 說明

在目前的程式碼中，你僅記錄了與地理圍欄的距離。在這次作業中，你需要新增通知功能，當 GPS 座標進入地理圍欄時，發送簡訊或電子郵件。

Azure Functions 提供多種綁定選項，包括與第三方服務的整合，例如 Twilio，一個通訊平台。

* 在 [Twilio.com](https://www.twilio.com) 註冊免費帳戶
* 閱讀 [Microsoft 文件 Twilio 與 Azure Functions 綁定頁面](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python) 上的 Twilio SMS 綁定相關說明。
* 閱讀 [Microsoft 文件 Azure Functions SendGrid 綁定頁面](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python) 上的 SendGrid 發送電子郵件綁定相關說明。
* 將綁定新增至你的 Functions 應用程式，以便在 GPS 座標進入或離開地理圍欄時收到通知——僅選擇其中一種情況，而非兩者。

## 評分標準

| 評分項目 | 優秀 | 合格 | 需要改進 |
| -------- | ---- | ---- | -------- |
| 配置函數綁定並接收電子郵件或簡訊 | 成功配置函數綁定，並在座標進入或離開地理圍欄時收到電子郵件或簡訊，但僅限其中一種情況 | 成功配置綁定，但無法發送電子郵件或簡訊，或僅在座標同時進入和離開地理圍欄時發送 | 無法配置綁定，也無法發送電子郵件或簡訊 |

---

**免責聲明**：  
此文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。