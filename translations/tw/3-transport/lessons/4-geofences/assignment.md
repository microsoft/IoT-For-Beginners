<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-25T00:43:26+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "tw"
}
-->
# 使用 Twilio 發送通知

## 指導說明

在目前的程式碼中，你只是記錄了與地理圍欄的距離。在這次作業中，你需要新增一個通知功能，當 GPS 座標位於地理圍欄內時，發送一則簡訊或電子郵件。

Azure Functions 提供多種綁定選項，包括與第三方服務（如 Twilio，一個通訊平台）的整合。

* 在 [Twilio.com](https://www.twilio.com) 註冊一個免費帳戶
* 閱讀 [Microsoft 文件中 Azure Functions 與 Twilio SMS 綁定的頁面](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python) 以了解如何綁定 Twilio SMS。
* 閱讀 [Microsoft 文件中 Azure Functions 與 Twilio SendGrid 綁定的頁面](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python) 以了解如何使用 Twilio SendGrid 發送電子郵件。
* 將綁定新增到你的 Functions 應用程式中，當 GPS 座標位於地理圍欄內或外時收到通知，但不要同時處理內外兩種情況。

## 評分標準

| 評分項目 | 優秀 | 合格 | 需要改進 |
| -------- | ---- | ---- | -------- |
| 配置函數綁定並接收電子郵件或簡訊 | 能夠成功配置函數綁定，並在地理圍欄內或外時接收到電子郵件或簡訊，但不包括同時處理內外兩種情況 | 能夠配置綁定，但無法成功發送電子郵件或簡訊，或僅能在座標同時位於內外時發送 | 無法配置綁定，也無法發送電子郵件或簡訊 |

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而產生的任何誤解或錯誤解讀概不負責。