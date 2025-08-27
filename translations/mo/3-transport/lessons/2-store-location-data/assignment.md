<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-27T01:03:27+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "mo"
}
-->
# 調查函數綁定

## 說明

函數綁定允許您的程式碼透過從 `main` 函數返回資料塊（blob），將其儲存到 Blob 儲存體中。Azure 儲存體帳戶、集合及其他詳細資訊是在 `function.json` 檔案中設定的。

在使用 Azure 或其他 Microsoft 技術時，最好的資訊來源是 [Microsoft 文件網站 docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn)。在這個作業中，您需要閱讀 Azure Functions 綁定的相關文件，以了解如何設定輸出綁定。

一些可以幫助您入門的頁面包括：

* [Azure Functions 觸發器與綁定概念](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Functions 的 Azure Blob 儲存體綁定概述](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Functions 的 Azure Blob 儲存體輸出綁定](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## 評分標準

| 評分標準 | 優異 | 合格 | 需要改進 |
| -------- | ---- | ---- | -------- |
| 設定 Blob 儲存體輸出綁定 | 能夠成功設定輸出綁定，返回資料塊並將其成功儲存到 Blob 儲存體中 | 能夠設定輸出綁定或返回資料塊，但無法成功將其儲存到 Blob 儲存體中 | 無法設定輸出綁定 |

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。