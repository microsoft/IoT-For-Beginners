<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-25T01:07:19+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "tw"
}
-->
# 調查函數綁定

## 說明

函數綁定允許您的程式碼透過從 `main` 函數返回數據塊（blob）來將其儲存到 Blob 儲存體中。Azure 儲存體帳戶、集合及其他詳細資訊在 `function.json` 檔案中進行配置。

在使用 Azure 或其他 Microsoft 技術時，最佳的資訊來源是 [Microsoft 官方文件](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn)。在此作業中，您需要閱讀 Azure Functions 綁定的相關文件，以了解如何設置輸出綁定。

以下是一些可以幫助您入門的頁面：

* [Azure Functions 觸發器與綁定概念](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Functions 的 Azure Blob 儲存體綁定概述](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Functions 的 Azure Blob 儲存體輸出綁定](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## 評分標準

| 評分項目 | 優秀 | 合格 | 需要改進 |
| -------- | ---- | ---- | -------- |
| 配置 Blob 儲存體輸出綁定 | 能夠成功配置輸出綁定，返回數據塊並將其成功儲存到 Blob 儲存體中 | 能夠配置輸出綁定或返回數據塊，但無法成功將其儲存到 Blob 儲存體中 | 無法配置輸出綁定 |

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要信息，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。