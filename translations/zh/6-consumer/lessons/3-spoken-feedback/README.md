<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b73fe10ec6b580fba2affb6f6e0a5c4d",
  "translation_date": "2025-08-25T00:05:39+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/README.md",
  "language_code": "zh"
}
-->
# 设置计时器并提供语音反馈

![本课的手绘笔记概览](../../../../../translated_images/zh/lesson-23.f38483e1d4df4828990d3f02d60e46c978b075d384ae7cb4f7bab738e107c850.jpg)

> 手绘笔记由 [Nitya Narasimhan](https://github.com/nitya) 提供。点击图片查看更大版本。

## 课前测验

[课前测验](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/45)

## 介绍

智能助手并不是单向的通信设备。你对它说话，它会回应：

“Alexa，设置一个3分钟的计时器。”

“好的，您的计时器已设置为3分钟。”

在前两节课中，你学习了如何将语音转换为文本，然后从文本中提取设置计时器的请求。在本课中，你将学习如何在物联网设备上设置计时器，通过语音向用户确认计时器已设置，并在计时器结束时提醒用户。

本课将涵盖以下内容：

* [文本转语音](../../../../../6-consumer/lessons/3-spoken-feedback)
* [设置计时器](../../../../../6-consumer/lessons/3-spoken-feedback)
* [将文本转换为语音](../../../../../6-consumer/lessons/3-spoken-feedback)

## 文本转语音

文本转语音，顾名思义，是将文本转换为包含该文本的语音的过程。其基本原理是将文本中的单词分解为构成声音的基本单位（称为音素），然后通过预录音频或AI模型生成音频，将这些声音拼接起来。

![典型文本转语音系统的三个阶段](../../../../../translated_images/zh/tts-overview.193843cf3f5ee09f.webp)

文本转语音系统通常分为三个阶段：

* 文本分析
* 语言分析
* 波形生成

### 文本分析

文本分析是将提供的文本转换为可以用于生成语音的单词。例如，如果你转换“Hello world”，不需要进行文本分析，这两个单词可以直接转换为语音。但如果是“1234”，则可能需要根据上下文将其转换为“One thousand, two hundred thirty four”或“One, two, three, four”。例如，“I have 1234 apples”应转换为“One thousand, two hundred thirty four”，而“The child counted 1234”则应转换为“One, two, three, four”。

单词的生成不仅因语言而异，还因语言的地区差异而不同。例如，在美式英语中，120是“One hundred twenty”，而在英式英语中则是“One hundred and twenty”，其中“and”用于连接百位数。

✅ 其他需要文本分析的例子包括“in”作为英寸的缩写，以及“st”作为圣徒或街道的缩写。你能想到在你的语言中有哪些类似的例子吗？

定义好单词后，它们会被送去进行语言分析。

### 语言分析

语言分析将单词分解为音素。音素不仅基于单词中的字母，还基于单词中的其他字母。例如，在英语中，“car”和“care”中的“a”发音不同。英语中26个字母对应44个不同的音素，有些音素由不同的字母共享，例如“circle”和“serpent”开头的音素相同。

✅ 做一些研究：你的语言有哪些音素？

单词被转换为音素后，这些音素还需要额外的数据来支持语调，根据上下文调整音调或时长。例如，在英语中，音调的升高可以将一个句子转换为一个问题，最后一个单词的音调升高表示这是一个问题。

例如，句子“You have an apple”是一个陈述，表示你有一个苹果。如果最后一个单词“apple”的音调升高，就变成了一个问题“You have an apple?”，询问你是否有一个苹果。语言分析需要使用句末的问号来决定是否升高音调。

生成音素后，它们会被送去波形生成以产生音频输出。

### 波形生成

最早的电子文本转语音系统为每个音素使用单一的音频录制，导致语音听起来非常单调、机械化。语言分析生成音素后，这些音素会从音频数据库中加载并拼接成音频。

✅ 做一些研究：找一些早期语音合成系统的音频录制，与现代语音合成（如智能助手使用的语音合成）进行比较。

更现代的波形生成使用基于深度学习的机器学习模型（非常大的神经网络，类似于大脑中的神经元）来生成更自然的语音，甚至可以与人类语音难以区分。

> 💁 一些机器学习模型可以通过迁移学习重新训练，使其听起来像真实的人。这意味着使用语音作为安全系统（例如银行越来越多地尝试使用语音验证）不再是一个好主意，因为任何人只需几分钟的语音录音就可以模仿你。

这些大型机器学习模型正在被训练为将三个步骤结合起来，形成端到端的语音合成器。

## 设置计时器

要设置计时器，你的物联网设备需要调用你使用无服务器代码创建的REST端点，然后使用返回的秒数来设置计时器。

### 任务 - 调用无服务器函数以获取计时器时间

按照相关指南从你的物联网设备调用REST端点，并设置所需时间的计时器：

* [Arduino - Wio Terminal](wio-terminal-set-timer.md)
* [单板计算机 - Raspberry Pi/虚拟物联网设备](single-board-computer-set-timer.md)

## 将文本转换为语音

你用来将语音转换为文本的语音服务也可以用来将文本转换回语音，并通过物联网设备上的扬声器播放。要转换的文本会发送到语音服务，同时指定所需的音频类型（例如采样率），然后返回包含音频的二进制数据。

发送此请求时，你需要使用*语音合成标记语言*（SSML），一种基于XML的语音合成应用标记语言。它不仅定义了要转换的文本，还定义了文本的语言、使用的语音，甚至可以定义某些或所有单词的速度、音量和音调。

例如，以下SSML定义了一个请求，将文本“Your 3 minute 5 second time has been set”转换为语音，使用名为`en-GB-MiaNeural`的英式英语语音。

```xml
<speak version='1.0' xml:lang='en-GB'>
    <voice xml:lang='en-GB' name='en-GB-MiaNeural'>
        Your 3 minute 5 second time has been set
    </voice>
</speak>
```

> 💁 大多数文本转语音系统为不同语言提供多种语音选项，包括相关的口音，例如英式英语语音带有英国口音，新西兰英语语音带有新西兰口音。

### 任务 - 将文本转换为语音

按照相关指南使用你的物联网设备将文本转换为语音：

* [Arduino - Wio Terminal](wio-terminal-text-to-speech.md)
* [单板计算机 - Raspberry Pi](pi-text-to-speech.md)
* [单板计算机 - 虚拟设备](virtual-device-text-to-speech.md)

---

## 🚀 挑战

SSML可以改变单词的发音方式，例如对某些单词添加强调、添加停顿或改变音调。尝试使用不同的SSML从你的物联网设备发送请求，并比较输出效果。你可以在[万维网联盟的语音合成标记语言（SSML）1.1版规范](https://www.w3.org/TR/speech-synthesis11/)中阅读更多关于SSML的信息，包括如何改变单词的发音方式。

## 课后测验

[课后测验](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/46)

## 复习与自学

* 在[维基百科的语音合成页面](https://wikipedia.org/wiki/Speech_synthesis)上阅读更多关于语音合成的内容
* 在[BBC新闻关于假声音“帮助网络犯罪分子窃取现金”的报道](https://www.bbc.com/news/technology-48908736)中阅读更多关于犯罪分子如何利用语音合成进行盗窃
* 在[Vice关于TikTok诉讼如何凸显AI对配音演员的影响的文章](https://www.vice.com/en/article/z3xqwj/this-tiktok-lawsuit-is-highlighting-how-ai-is-screwing-over-voice-actors)中了解更多关于语音合成对配音演员的风险

## 作业

[取消计时器](assignment.md)

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。对于因使用本翻译而引起的任何误解或误读，我们概不负责。