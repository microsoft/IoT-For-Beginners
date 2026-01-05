<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c16de27b0074abe81d6a8bad5e5b1a6b",
  "translation_date": "2025-08-24T23:50:42+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/README.md",
  "language_code": "zh"
}
-->
# 支持多语言

![本课的手绘笔记概览](../../../../../translated_images/lesson-24.4246968ed058510ab275052e87ef9aa89c7b2f938915d103c605c04dc6cd5bb7.zh.jpg)

> 手绘笔记由 [Nitya Narasimhan](https://github.com/nitya) 提供。点击图片查看大图。

这段视频概述了 Azure 语音服务，涵盖了前几课中的语音转文本和文本转语音内容，以及本课将讨论的语音翻译：

[![用几行 Python 代码识别语音 - 来自 Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 点击上方图片观看视频

## 课前测验

[课前测验](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## 简介

在过去的三节课中，你学习了如何将语音转换为文本、语言理解以及将文本转换为语音，这些都由 AI 提供支持。AI 还能帮助人类沟通的另一个领域是语言翻译——将一种语言转换为另一种语言，例如从英语翻译成法语。

在本课中，你将学习如何使用 AI 翻译文本，使你的智能计时器能够与多语言用户互动。

本课内容包括：

* [翻译文本](../../../../../6-consumer/lessons/4-multiple-language-support)
* [翻译服务](../../../../../6-consumer/lessons/4-multiple-language-support)
* [创建翻译资源](../../../../../6-consumer/lessons/4-multiple-language-support)
* [通过翻译在应用程序中支持多语言](../../../../../6-consumer/lessons/4-multiple-language-support)
* [使用 AI 服务翻译文本](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 这是本项目的最后一课，因此在完成本课和作业后，不要忘记清理你的云服务。你需要这些服务来完成作业，所以请确保先完成作业。
>
> 如果需要，请参考 [清理项目指南](../../../clean-up.md) 了解如何操作。

## 翻译文本

文本翻译是一个计算机科学问题，已经被研究了 70 多年。得益于 AI 和计算能力的进步，如今它已经接近解决，翻译效果几乎可以媲美人类翻译。

> 💁 其起源可以追溯到更早的 [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi)，一位 9 世纪的阿拉伯密码学家，他开发了语言翻译的技术。

### 机器翻译

文本翻译最初是一种被称为机器翻译（MT）的技术，可以在不同语言对之间进行翻译。机器翻译通过将一种语言中的单词替换为另一种语言中的单词，并添加技术来选择正确的短语或句子部分的翻译方式，以避免逐字翻译时出现不通顺的情况。

> 🎓 当翻译器支持在一种语言和另一种语言之间进行翻译时，这些被称为 *语言对*。不同的工具支持不同的语言对，这些支持可能并不完整。例如，一个翻译器可能支持英语到西班牙语的语言对，以及西班牙语到意大利语的语言对，但不支持英语到意大利语。

例如，将“Hello world”从英语翻译成法语可以通过替换完成——“Bonjour”替换“Hello”，“le monde”替换“world”，最终得到正确的翻译“Bonjour le monde”。

但替换法在不同语言表达相同意思的方式不同的情况下就不起作用了。例如，英语句子“My name is Jim”翻译成法语是“Je m'appelle Jim”，字面意思是“我叫自己 Jim”。“Je”是法语中的“我”，“moi”是“我自己”，但由于动词以元音开头，因此缩写为“m'”，“appelle”是“叫”，“Jim”是名字，不会被翻译。单词顺序也会成为问题——简单替换“Je m'appelle Jim”会变成“I myself call Jim”，与英语的单词顺序不同。

> 💁 有些单词永远不会被翻译——无论使用哪种语言介绍我，我的名字始终是 Jim。当翻译成使用不同字母表或不同发音的语言时，单词可能会被 *音译*，即选择适当的字母或字符，使其发音与原单词相同。

习语也是翻译中的一个难题。这些短语的含义与单词的直接解释不同。例如，英语中的习语“I've got ants in my pants”并不是字面意思指裤子里有蚂蚁，而是指坐立不安。如果将其翻译成德语，可能会让听者感到困惑，因为德语的表达是“I have bumble bees in the bottom”。

> 💁 不同的地区会增加不同的复杂性。例如，在习语“ants in your pants”中，美式英语中的“pants”指外裤，而英式英语中的“pants”指内裤。

✅ 如果你会多种语言，想想有哪些短语无法直接翻译。

机器翻译系统依赖于描述如何翻译特定短语和习语的大型规则数据库，以及使用统计方法从可能的选项中选择最合适翻译的技术。这些统计方法使用由人类翻译成多种语言的大型数据库来选择最可能的翻译，这种技术被称为 *统计机器翻译*。其中一些使用语言的中间表示形式，使一种语言可以翻译成中间语言，再从中间语言翻译成另一种语言。这样，添加更多语言时只需翻译到中间语言和从中间语言翻译，而不需要与所有其他语言之间的翻译。

### 神经翻译

神经翻译利用 AI 的强大功能进行翻译，通常使用一个模型翻译整个句子。这些模型通过人类翻译的大型数据集进行训练，例如网页、书籍和联合国文档。

神经翻译模型通常比机器翻译模型更小，因为它们不需要庞大的短语和习语数据库。现代 AI 翻译服务通常混合多种技术，将统计机器翻译和神经翻译结合起来。

任何语言对之间都不存在 1:1 的翻译。不同的翻译模型会根据训练模型的数据生成略有不同的结果。翻译并不总是对称的——即如果你将一个句子从一种语言翻译成另一种语言，然后再翻译回原语言，可能会得到略有不同的句子。

✅ 试试不同的在线翻译器，例如 [Bing 翻译](https://www.bing.com/translator)、[Google 翻译](https://translate.google.com) 或 Apple 翻译应用。比较几句话的翻译版本。还可以尝试在一个翻译器中翻译，然后在另一个翻译器中翻译回去。

## 翻译服务

有许多 AI 服务可以从你的应用程序中调用，用于翻译语音和文本。

### 认知服务语音服务

![语音服务标志](../../../../../translated_images/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.zh.png)

你在过去几课中使用的语音服务具有语音识别的翻译功能。当你识别语音时，可以请求不仅以相同语言显示的文本，还可以请求其他语言的文本。

> 💁 这仅在语音 SDK 中可用，REST API 不支持内置翻译。

### 认知服务翻译器服务

![翻译器服务标志](../../../../../translated_images/azure-translator-logo.c6ed3a4a433edfd2f11577eca105412c50b8396b194cbbd730723dd1d0793bcd.zh.png)

翻译器服务是一个专门的翻译服务，可以将文本从一种语言翻译成一种或多种目标语言。除了翻译，它还支持许多额外功能，包括屏蔽不雅词汇。它还允许你为特定单词或句子提供特定翻译，以处理你不希望翻译的术语，或具有特定公认翻译的术语。

例如，当将句子“I have a Raspberry Pi”翻译成另一种语言（如法语）时，提到单板计算机 Raspberry Pi，你会希望保留“Raspberry Pi”这个名称，而不是翻译它，得到“J’ai un Raspberry Pi”而不是“J’ai une pi aux framboises”。

## 创建翻译资源

在本课中，你将需要一个翻译器资源。你将使用 REST API 翻译文本。

### 任务 - 创建翻译器资源

1. 在终端或命令提示符中运行以下命令，在你的 `smart-timer` 资源组中创建一个翻译器资源。

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    将 `<location>` 替换为创建资源组时使用的位置。

1. 获取翻译器服务的密钥：

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    复制其中一个密钥。

## 通过翻译在应用程序中支持多语言

在理想情况下，你的整个应用程序应该能够理解尽可能多的语言，从语音识别到语言理解，再到语音响应。这需要大量工作，而翻译服务可以加快应用程序的交付时间。

![一个智能计时器架构，将日语翻译成英语，在英语中处理，然后再翻译回日语](../../../../../translated_images/translated-smart-timer.08ac20057fdc5c37.zh.png)

想象你正在构建一个智能计时器，它从头到尾使用英语，理解英语语音并将其转换为文本，在英语中运行语言理解，用英语构建响应并用英语语音回复。如果你想添加日语支持，可以先将日语语音翻译成英语文本，然后保持应用程序的核心部分不变，再将响应文本翻译成日语，最后用日语语音回复。这将使你能够快速添加日语支持，之后可以扩展为提供完整的端到端日语支持。

> 💁 依赖机器翻译的缺点是，不同语言和文化表达相同意思的方式不同，因此翻译可能与预期的表达不符。

机器翻译还为应用程序和设备提供了翻译用户生成内容的可能性。科幻作品中经常出现“通用翻译器”，这些设备可以将外星语言翻译成（通常是）美式英语。如果忽略外星部分，这些设备已经不再是科幻，而是科学事实。已经有应用程序和设备可以实时翻译语音和书面文本，结合语音和翻译服务。

一个例子是 [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn) 手机应用程序，在这段视频中进行了演示：

[![Microsoft Translator 实时功能演示](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 点击上方图片观看视频

想象一下拥有这样一个设备，尤其是在旅行或与不懂其语言的人互动时。在机场或医院中拥有自动翻译设备将大大提高无障碍性。

✅ 做一些研究：市面上是否有任何翻译 IoT 设备？智能设备中是否内置了翻译功能？

> 👽 尽管目前还没有真正的通用翻译器可以让我们与外星人交流，但 [Microsoft Translator 支持克林贡语](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn)。Qapla’！

## 使用 AI 服务翻译文本

你可以使用 AI 服务为你的智能计时器添加翻译功能。

### 任务 - 使用 AI 服务翻译文本

按照相关指南，在你的 IoT 设备上实现文本翻译：

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [单板计算机 - Raspberry Pi](pi-translate-speech.md)
* [单板计算机 - 虚拟设备](virtual-device-translate-speech.md)

---

## 🚀 挑战

机器翻译如何在智能设备之外的其他 IoT 应用中受益？想想翻译如何帮助其他场景，不仅限于口语，还包括文本。

## 课后测验

[课后测验](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## 复习与自学

* 在 [Wikipedia 的机器翻译页面](https://wikipedia.org/wiki/Machine_translation) 上阅读更多关于机器翻译的内容
* 在 [Wikipedia 的神经机器翻译页面](https://wikipedia.org/wiki/Neural_machine_translation) 上阅读更多关于神经机器翻译的内容
* 查看 Microsoft 语音服务支持的语言列表，参见 [Microsoft Docs 上语音服务的语言和语音支持文档](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## 作业

[构建一个通用翻译器](assignment.md)

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。因使用本翻译而引起的任何误解或误读，我们概不负责。