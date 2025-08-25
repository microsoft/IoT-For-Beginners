<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-25T01:07:12+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "zh"
}
-->
# 调查函数绑定

## 说明

函数绑定允许您的代码通过从 `main` 函数返回数据块，将其保存到 Blob 存储中。Azure 存储账户、集合以及其他详细信息在 `function.json` 文件中进行配置。

在使用 Azure 或其他 Microsoft 技术时，最好的信息来源是 [Microsoft 文档](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn)。在本次任务中，您需要阅读 Azure Functions 绑定文档，以了解如何设置输出绑定。

以下是一些可以帮助您入门的页面：

* [Azure Functions 触发器和绑定概念](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Functions 的 Azure Blob 存储绑定概述](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Functions 的 Azure Blob 存储输出绑定](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## 评分标准

| 标准 | 卓越 | 合格 | 需要改进 |
| -------- | --------- | -------- | ----------------- |
| 配置 Blob 存储输出绑定 | 能够成功配置输出绑定，返回数据块并将其成功存储到 Blob 存储中 | 能够配置输出绑定或返回数据块，但未能成功将其存储到 Blob 存储中 | 无法配置输出绑定 |

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。原始语言的文档应被视为权威来源。对于关键信息，建议使用专业人工翻译。我们不对因使用此翻译而产生的任何误解或误读承担责任。