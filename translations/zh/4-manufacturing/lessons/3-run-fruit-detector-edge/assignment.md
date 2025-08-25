<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-24T21:44:47+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "zh"
}
-->
# 在边缘运行其他服务

## 说明

不仅仅是图像分类器可以在边缘运行，任何可以打包成容器的内容都可以部署到 IoT Edge 设备上。无服务器代码（如你在之前课程中创建的触发器）可以作为 Azure Functions 运行在容器中，因此也可以运行在 IoT Edge 上。

选择之前的某一课程，尝试将 Azure Functions 应用程序运行在 IoT Edge 容器中。你可以在 [教程：将 Azure Functions 部署为 IoT Edge 模块 - Microsoft 文档](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11) 中找到一个使用不同 Functions 应用项目的指南。

## 评分标准

| 标准 | 卓越 | 合格 | 需要改进 |
| ---- | ---- | ---- | -------- |
| 将 Azure Functions 应用部署到 IoT Edge | 成功将 Azure Functions 应用部署到 IoT Edge，并使用 IoT 设备运行 IoT 数据触发器 | 成功将 Functions 应用部署到 IoT Edge，但未能触发触发器 | 未能将 Functions 应用部署到 IoT Edge |

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。原始语言的文档应被视为权威来源。对于重要信息，建议使用专业人工翻译。我们对因使用此翻译而产生的任何误解或误读不承担责任。