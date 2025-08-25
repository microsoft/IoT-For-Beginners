<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-24T21:44:53+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "tw"
}
-->
# 在邊緣設備上運行其他服務

## 說明

不僅僅是影像分類器可以在邊緣設備上運行，任何可以打包成容器的應用都可以部署到 IoT Edge 設備上。無伺服器代碼（如您在之前課程中創建的觸發器）可以作為 Azure Functions 運行在容器中，因此也可以運行在 IoT Edge 上。

選擇之前的一節課，嘗試將 Azure Functions 應用運行在 IoT Edge 容器中。您可以參考 [教學：將 Azure Functions 部署為 IoT Edge 模組 - Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11)，該指南展示了如何使用不同的 Functions 應用專案來完成此操作。

## 評分標準

| 評分標準 | 優秀 | 合格 | 需要改進 |
| -------- | ---- | ---- | -------- |
| 將 Azure Functions 應用部署到 IoT Edge | 能夠成功將 Azure Functions 應用部署到 IoT Edge，並使用 IoT 設備觸發 IoT 數據的觸發器 | 能夠將 Functions 應用部署到 IoT Edge，但無法成功觸發 | 無法將 Functions 應用部署到 IoT Edge |

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。