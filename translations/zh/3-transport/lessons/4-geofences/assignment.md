<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-25T00:43:18+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "zh"
}
-->
# 使用 Twilio 发送通知

## 说明

在目前的代码中，你只是记录了到地理围栏的距离。在本次任务中，当 GPS 坐标位于地理围栏内时，你需要添加一个通知，可以是短信或电子邮件。

Azure Functions 提供了多种绑定选项，包括与第三方服务的集成，例如 Twilio，一个通信平台。

* 在 [Twilio.com](https://www.twilio.com) 注册一个免费账户
* 阅读 [Microsoft 文档 Twilio 绑定 Azure Functions 页面](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python) 上关于将 Azure Functions 绑定到 Twilio SMS 的文档。
* 阅读 [Microsoft 文档 Azure Functions SendGrid 绑定页面](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python) 上关于将 Azure Functions 绑定到 Twilio SendGrid 以发送电子邮件的文档。
* 将绑定添加到你的 Functions 应用中，以便在 GPS 坐标位于地理围栏内或外时收到通知——但不能同时通知两种情况。

## 评分标准

| 标准 | 卓越 | 合格 | 需要改进 |
| -------- | --------- | -------- | ----------------- |
| 配置函数绑定并接收电子邮件或短信 | 能够配置函数绑定，并在地理围栏内或外时收到电子邮件或短信，但不能同时通知两种情况 | 能够配置绑定，但无法发送电子邮件或短信，或者只能在坐标同时位于地理围栏内和外时发送 | 无法配置绑定并发送电子邮件或短信 |

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。我们对于因使用本翻译而引起的任何误解或误读不承担责任。