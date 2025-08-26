<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-26T13:56:55+00:00",
  "source_file": "clean-up.md",
  "language_code": "hk"
}
-->
# 清理您的項目

完成每個項目後，最好刪除您的雲端資源。

在每個項目的課程中，您可能已創建以下資源：

* 資源群組
* IoT Hub
* IoT 設備註冊
* 儲存帳戶
* Functions App
* Azure Maps 帳戶
* 自訂視覺項目
* Azure 容器註冊表
* 認知服務資源

大部分這些資源都不會產生費用——要麼完全免費，要麼您使用的是免費層級。對於需要付費層級的服務，您可能使用的是包含在免費配額內的層級，或者僅需支付幾分錢。

即使成本相對較低，完成後刪除這些資源仍然是值得的。例如，您只能擁有一個使用免費層級的 IoT Hub，因此如果您想創建另一個，就需要使用付費層級。

所有的服務都被創建在資源群組內，這使得管理更加方便。您可以刪除資源群組，資源群組內的所有服務也會一併刪除。

要刪除資源群組，請在您的終端或命令提示符中執行以下指令：

```sh
az group delete --name <resource-group-name>
```

將 `<resource-group-name>` 替換為您感興趣的資源群組名稱。

系統會出現確認提示：

```output
Are you sure you want to perform this operation? (y/n): 
```

輸入 `y` 以確認並刪除資源群組。

刪除所有服務可能需要一些時間。

> 💁 您可以在 [Microsoft Docs 上的 Azure 資源管理器資源群組和資源刪除文件](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli) 閱讀更多相關資訊。

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原文檔的母語版本作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤詮釋概不負責。