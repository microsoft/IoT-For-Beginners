<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-26T14:18:48+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "hk"
}
-->
# 在邊緣設備上運行其他服務

## 指引

不僅僅是影像分類器可以在邊緣設備上運行，任何可以打包成容器的應用都可以部署到 IoT Edge 設備上。無伺服器代碼（如 Azure Functions）也可以在容器中運行，因此可以在 IoT Edge 上執行，例如你在之前課程中創建的觸發器。

選擇之前的其中一課，嘗試將 Azure Functions 應用運行在 IoT Edge 容器中。你可以在 [教程：將 Azure Functions 部署為 IoT Edge 模組 - Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11) 中找到使用不同 Functions 應用項目進行操作的指南。

## 評分標準

| 評分標準 | 卓越 | 合格 | 需要改進 |
| -------- | --------- | -------- | ----------------- |
| 將 Azure Functions 應用部署到 IoT Edge | 成功將 Azure Functions 應用部署到 IoT Edge，並能與 IoT 設備配合使用，從 IoT 數據觸發執行 | 成功將 Functions 應用部署到 IoT Edge，但無法成功觸發執行 | 無法將 Functions 應用部署到 IoT Edge |

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。