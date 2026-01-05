<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-25T00:31:42+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "zh"
}
-->
# 配置麦克风和扬声器 - Wio Terminal

在本课程的这一部分中，您将为 Wio Terminal 添加扬声器。Wio Terminal 已内置麦克风，可用于捕捉语音。

## 硬件

Wio Terminal 已内置麦克风，可用于捕捉音频以进行语音识别。

![Wio Terminal 上的麦克风](../../../../../translated_images/wio-mic.3f8c843dbe8ad917.zh.png)

要添加扬声器，您可以使用 [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)。这是一个外部板，包含两个 MEMS 麦克风，以及一个扬声器连接器和耳机插孔。

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab16.zh.png)

您需要添加耳机、带有 3.5mm 插头的扬声器，或者带有 JST 接口的扬声器，例如 [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)。

要连接 ReSpeaker 2-Mics Pi Hat，您需要 40 根针对针（也称为公对公）跳线。

> 💁 如果您熟悉焊接，可以使用 [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) 来连接 ReSpeaker。

您还需要一张 SD 卡，用于下载和播放音频。Wio Terminal 仅支持最大 16GB 的 SD 卡，并且这些卡需要格式化为 FAT32 或 exFAT。

### 任务 - 连接 ReSpeaker Pi Hat

1. 在 Wio Terminal 关闭电源的情况下，使用跳线和 Wio Terminal 背面的 GPIO 插座将 ReSpeaker 2-Mics Pi Hat 连接到 Wio Terminal：

    引脚需要按以下方式连接：

    ![引脚图](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa65081038.zh.png)

1. 将 ReSpeaker 和 Wio Terminal 放置好，使 GPIO 插座面朝上，并位于左侧。

1. 从 ReSpeaker GPIO 插座左上角的插孔开始。将一根针对针跳线从 ReSpeaker 左上角插孔连接到 Wio Terminal 左上角插孔。

1. 按此方式连接左侧 GPIO 插座的所有插孔。确保引脚牢固插入。

    ![左侧引脚连接到 Wio Terminal 左侧引脚的 ReSpeaker](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba2400.zh.png)

    ![左侧引脚连接到 Wio Terminal 左侧引脚的 ReSpeaker](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f.zh.png)

    > 💁 如果您的跳线是连接成带状的，请保持它们整齐排列——这样可以更容易确保所有线缆按顺序连接。

1. 使用 ReSpeaker 和 Wio Terminal 的右侧 GPIO 插座重复上述过程。这些线缆需要绕过已经连接的线缆。

    ![右侧引脚连接到 Wio Terminal 右侧引脚的 ReSpeaker](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa930.zh.png)

    ![右侧引脚连接到 Wio Terminal 右侧引脚的 ReSpeaker](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437.zh.png)

    > 💁 如果您的跳线是连接成带状的，请将它们分成两组带状线缆。分别从现有线缆的两侧通过。

    > 💁 您可以使用胶带将引脚固定成一个块，以防止在连接过程中引脚脱落。
    >
    > ![用胶带固定的引脚](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3.zh.png)

1. 您需要添加一个扬声器。

    * 如果您使用的是带有 JST 线缆的扬声器，请将其连接到 ReSpeaker 的 JST 接口。

      ![通过 JST 线缆连接到 ReSpeaker 的扬声器](../../../../../translated_images/respeaker-jst-speaker.a441d177809df945.zh.png)

    * 如果您使用的是带有 3.5mm 插头的扬声器或耳机，请将其插入 3.5mm 插孔。

      ![通过 3.5mm 插孔连接到 ReSpeaker 的扬声器](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751.zh.png)

### 任务 - 设置 SD 卡

1. 将 SD 卡连接到您的电脑，如果没有 SD 卡插槽，请使用外部读卡器。

1. 使用电脑上的适当工具格式化 SD 卡，确保使用 FAT32 或 exFAT 文件系统。

1. 将 SD 卡插入 Wio Terminal 左侧的 SD 卡插槽，插槽位于电源按钮下方。确保卡完全插入并卡住——您可能需要使用薄工具或另一张 SD 卡帮助将其完全推入。

    ![将 SD 卡插入电源开关下方的 SD 卡插槽](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f.zh.png)

    > 💁 要弹出 SD 卡，您需要稍微按压卡片，它会弹出。您可能需要使用薄工具，例如平头螺丝刀或另一张 SD 卡。

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用本翻译而引起的任何误解或误读不承担责任。