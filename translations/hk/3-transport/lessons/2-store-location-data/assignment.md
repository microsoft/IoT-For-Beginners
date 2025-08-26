<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-26T15:56:19+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "hk"
}
-->
# 調查函數綁定

## 指引

函數綁定允許你的程式碼透過從 `main` 函數返回來將 blob 儲存到 blob 儲存體。Azure 儲存帳戶、集合及其他細節是在 `function.json` 文件中配置的。

在使用 Azure 或其他 Microsoft 技術時，最好的資訊來源是 [Microsoft 的官方文件 docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn)。在這個作業中，你需要閱讀 Azure Functions 綁定的相關文件，以了解如何設置輸出綁定。

以下是一些可以幫助你入門的頁面：

* [Azure Functions 觸發器和綁定概念](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Functions 的 Azure Blob 儲存綁定概述](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Functions 的 Azure Blob 儲存輸出綁定](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## 評分標準

| 評分標準 | 優秀 | 合格 | 需要改進 |
| -------- | ---- | ---- | -------- |
| 配置 blob 儲存輸出綁定 | 能夠成功配置輸出綁定，返回 blob 並成功儲存到 blob 儲存體 | 能夠配置輸出綁定或返回 blob，但無法成功儲存到 blob 儲存體 | 無法配置輸出綁定 |

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。