<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-26T15:45:26+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "hk"
}
-->
# 使用 Twilio 發送通知

## 指引

在你的程式碼中，目前只記錄了進入地理圍欄的距離。在這次作業中，你需要新增通知功能，當 GPS 座標進入地理圍欄時，發送一則簡訊或電子郵件。

Azure Functions 提供多種綁定選項，包括與第三方服務的整合，例如 Twilio，一個通訊平台。

* 在 [Twilio.com](https://www.twilio.com) 註冊一個免費帳戶
* 閱讀 [Microsoft 文件 Twilio 綁定 Azure Functions 頁面](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python) 上的 Twilio SMS 綁定文件
* 閱讀 [Microsoft 文件 Azure Functions SendGrid 綁定頁面](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python) 上的 SendGrid 發送電子郵件綁定文件
* 將綁定新增到你的 Functions 應用程式中，當 GPS 座標進入或離開地理圍欄時收到通知——但不能同時處理兩種情況。

## 評分標準

| 評分項目 | 優秀 | 合格 | 需要改進 |
| -------- | ---- | ---- | -------- |
| 配置 Functions 綁定並接收電子郵件或簡訊 | 成功配置 Functions 綁定，並在進入或離開地理圍欄時接收到電子郵件或簡訊，但不能同時處理兩種情況 | 成功配置綁定，但無法發送電子郵件或簡訊，或僅能在座標同時進入和離開地理圍欄時發送 | 無法配置綁定並發送電子郵件或簡訊 |

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。