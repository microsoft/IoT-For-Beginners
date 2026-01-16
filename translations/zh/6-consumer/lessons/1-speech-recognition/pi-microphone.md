<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-25T00:30:10+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "zh"
}
-->
# 配置麦克风和扬声器 - 树莓派

在本课程的这一部分，您将为树莓派添加麦克风和扬声器。

## 硬件

树莓派需要一个麦克风。

树莓派没有内置麦克风，您需要添加一个外部麦克风。有多种方式可以实现：

* USB麦克风
* USB耳机
* USB一体式会议扬声器
* USB音频适配器和带3.5mm插孔的麦克风
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 蓝牙麦克风并非都支持树莓派，因此如果您使用蓝牙麦克风或耳机，可能会遇到配对或录音问题。

树莓派配有一个3.5mm耳机插孔。您可以使用它连接耳机、耳麦或扬声器。您也可以通过以下方式添加扬声器：

* 通过显示器或电视的HDMI音频
* USB扬声器
* USB耳机
* USB一体式会议扬声器
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)，可以通过3.5mm插孔或JST端口连接扬声器

## 连接并配置麦克风和扬声器

麦克风和扬声器需要连接并进行配置。

### 任务 - 连接并配置麦克风

1. 使用适当的方法连接麦克风。例如，通过一个USB端口连接。

1. 如果您使用的是ReSpeaker 2-Mics Pi HAT，可以移除Grove基座帽，然后将ReSpeaker帽安装到位。

    ![带有ReSpeaker帽的树莓派](../../../../../translated_images/zh/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    在本课程后续部分，您将需要一个Grove按钮，但此帽子内置了一个按钮，因此不需要Grove基座帽。

    安装帽子后，您需要安装一些驱动程序。请参考[Seeed入门指南](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started)获取驱动程序安装说明。

    > ⚠️ 说明中使用了`git`来克隆一个仓库。如果您的树莓派上没有安装`git`，可以运行以下命令进行安装：
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. 在树莓派的终端中运行以下命令，或者通过VS Code和远程SSH会话连接运行，以查看已连接麦克风的信息：

    ```sh
    arecord -l
    ```

    您将看到已连接麦克风的列表，类似如下：

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    假设您只有一个麦克风，您应该只看到一个条目。在Linux上配置麦克风可能会比较复杂，因此最好只使用一个麦克风并拔掉其他麦克风。

    记下卡号，稍后您将需要使用它。在上述输出中，卡号为1。

### 任务 - 连接并配置扬声器

1. 使用适当的方法连接扬声器。

1. 在树莓派的终端中运行以下命令，或者通过VS Code和远程SSH会话连接运行，以查看已连接扬声器的信息：

    ```sh
    aplay -l
    ```

    您将看到已连接扬声器的列表，类似如下：

    ```output
    pi@raspberrypi:~ $ aplay -l
    **** List of PLAYBACK Hardware Devices ****
    card 0: Headphones [bcm2835 Headphones], device 0: bcm2835 Headphones [bcm2835 Headphones]
      Subdevices: 8/8
      Subdevice #0: subdevice #0
      Subdevice #1: subdevice #1
      Subdevice #2: subdevice #2
      Subdevice #3: subdevice #3
      Subdevice #4: subdevice #4
      Subdevice #5: subdevice #5
      Subdevice #6: subdevice #6
      Subdevice #7: subdevice #7
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    您总是会看到`card 0: Headphones`，因为这是内置耳机插孔。如果您添加了额外的扬声器，例如USB扬声器，也会显示在列表中。

1. 如果您使用的是额外的扬声器，而不是连接到内置耳机插孔的扬声器或耳机，则需要将其配置为默认设备。为此，请运行以下命令：

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    这将打开一个配置文件，使用`nano`终端文本编辑器。使用键盘上的箭头键向下滚动，直到找到以下行：

    ```output
    defaults.pcm.card 0
    ```

    将值从`0`更改为您希望使用的卡号，该卡号来自`aplay -l`命令返回的列表。例如，在上述输出中，有一个名为`card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`的第二个声卡，卡号为1。要使用它，我会将该行更新为：

    ```output
    defaults.pcm.card 1
    ```

    将此值设置为适当的卡号。您可以使用键盘上的箭头键导航到数字位置，然后像编辑普通文本文件一样删除并输入新数字。

1. 按`Ctrl+x`保存更改并关闭文件。按`y`保存文件，然后按`回车`选择文件名。

### 任务 - 测试麦克风和扬声器

1. 运行以下命令，通过麦克风录制5秒音频：

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    在命令运行时，对着麦克风发出声音，例如说话、唱歌、打节奏、演奏乐器或任何您喜欢的方式。

1. 5秒后，录音将停止。运行以下命令播放录音：

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    您将听到通过扬声器播放的音频。根据需要调整扬声器的输出音量。

1. 如果需要调整内置麦克风端口的音量或麦克风的增益，可以使用`alsamixer`工具。您可以在[Linux alsamixer手册页](https://linux.die.net/man/1/alsamixer)上阅读更多关于此工具的信息。

1. 如果播放音频时出现错误，请检查您在`alsa.conf`文件中设置的`defaults.pcm.card`卡号是否正确。

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。对于因使用本翻译而引起的任何误解或误读，我们概不负责。