<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-24T22:16:17+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "zh"
}
-->
# 控制继电器 - Wio Terminal

在本节课程中，您将为 Wio Terminal 添加一个继电器，除了土壤湿度传感器外，还可以根据土壤湿度水平控制继电器。

## 硬件

Wio Terminal 需要一个继电器。

您将使用的是 [Grove 继电器](https://www.seeedstudio.com/Grove-Relay.html)，这是一个常开继电器（意味着当没有信号发送到继电器时，输出电路是断开的）。它可以处理高达 250V 和 10A 的输出电路。

这是一个数字执行器，因此需要连接到 Wio Terminal 的数字引脚。模拟/数字组合端口已经被土壤湿度传感器占用，因此继电器需要插入另一个端口，这是一个组合 I

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用本翻译而引起的任何误解或误读不承担责任。