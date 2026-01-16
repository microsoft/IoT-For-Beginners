<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-25T00:16:38+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "zh"
}
-->
# 捕捉音频 - 树莓派

在本节课程中，您将编写代码在树莓派上捕捉音频。音频捕捉将通过一个按钮来控制。

## 硬件

树莓派需要一个按钮来控制音频捕捉。

您将使用的是一个 Grove 按钮。这是一个数字传感器，可以打开或关闭信号。这些按钮可以配置为在按下时发送高信号，未按下时发送低信号，或者按下时发送低信号，未按下时发送高信号。

如果您使用的是 ReSpeaker 2-Mics Pi HAT 作为麦克风，那么无需连接按钮，因为这个 HAT 已经自带一个按钮。直接跳到下一节。

### 连接按钮

按钮可以连接到 Grove 基座 HAT。

#### 任务 - 连接按钮

![一个 Grove 按钮](../../../../../translated_images/zh/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. 将 Grove 电缆的一端插入按钮模块上的插座。它只能以一种方式插入。

1. 在树莓派断电的情况下，将 Grove 电缆的另一端连接到 Grove 基座 HAT 上标记为 **D5** 的数字插座。这个插座位于 GPIO 引脚旁边的一排插座中，从左数第二个。

![Grove 按钮连接到 D5 插座](../../../../../translated_images/zh/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## 捕捉音频

您可以使用 Python 代码从麦克风捕捉音频。

### 任务 - 捕捉音频

1. 启动树莓派并等待其启动完成。

1. 启动 VS Code，可以直接在树莓派上运行，也可以通过 Remote SSH 扩展连接。

1. PyAudio Pip 包提供了录制和回放音频的功能。此包依赖于一些需要先安装的音频库。在终端中运行以下命令来安装这些库：

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. 安装 PyAudio Pip 包。

    ```sh
    pip3 install pyaudio
    ```

1. 创建一个名为 `smart-timer` 的新文件夹，并在此文件夹中添加一个名为 `app.py` 的文件。

1. 在文件顶部添加以下导入：

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    这将导入 `pyaudio` 模块、一些用于处理 WAV 文件的标准 Python 模块，以及 `grove.factory` 模块以导入用于创建按钮类的 `Factory`。

1. 在此之后，添加代码以创建一个 Grove 按钮。

    如果您使用的是 ReSpeaker 2-Mics Pi HAT，请使用以下代码：

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    这将在端口 **D17** 上创建一个按钮，该端口连接到 ReSpeaker 2-Mics Pi HAT 上的按钮。此按钮设置为在按下时发送低信号。

    如果您未使用 ReSpeaker 2-Mics Pi HAT，而是使用连接到基座 HAT 的 Grove 按钮，请使用以下代码：

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    这将在端口 **D5** 上创建一个按钮，该按钮设置为在按下时发送高信号。

1. 在此之后，创建一个 PyAudio 类的实例来处理音频：

    ```python
    audio = pyaudio.PyAudio()
    ```

1. 声明麦克风和扬声器的硬件卡号。这将是您在本课程前面通过运行 `arecord -l` 和 `aplay -l` 找到的卡号。

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    将 `<microphone card number>` 替换为您的麦克风卡号。

    将 `<speaker card number>` 替换为您的扬声器卡号，与您在 `alsa.conf` 文件中设置的卡号相同。

1. 在此之后，声明用于音频捕捉和回放的采样率。根据您使用的硬件，可能需要更改此值。

    ```python
    rate = 48000 #48KHz
    ```

    如果稍后运行代码时出现采样率错误，请将此值更改为 `44100` 或 `16000`。值越高，音质越好。

1. 在此之后，创建一个名为 `capture_audio` 的新函数。此函数将用于从麦克风捕捉音频：

    ```python
    def capture_audio():
    ```

1. 在此函数中，添加以下代码以捕捉音频：

    ```python
    stream = audio.open(format = pyaudio.paInt16,
                        rate = rate,
                        channels = 1, 
                        input_device_index = microphone_card_number,
                        input = True,
                        frames_per_buffer = 4096)

    frames = []

    while button.is_pressed():
        frames.append(stream.read(4096))

    stream.stop_stream()
    stream.close()
    ```

    此代码使用 PyAudio 对象打开一个音频输入流。该流将以 16KHz 的采样率从麦克风捕捉音频，并以 4096 字节大小的缓冲区捕捉。

    然后代码在 Grove 按钮被按下时循环运行，每次将这些 4096 字节的缓冲区读取到一个数组中。

    > 💁 您可以在 [PyAudio 文档](https://people.csail.mit.edu/hubert/pyaudio/docs/) 中了解更多关于传递给 `open` 方法的选项。

    一旦按钮被释放，流将停止并关闭。

1. 在此函数的末尾添加以下代码：

    ```python
    wav_buffer = io.BytesIO()
    with wave.open(wav_buffer, 'wb') as wavefile:
        wavefile.setnchannels(1)
        wavefile.setsampwidth(audio.get_sample_size(pyaudio.paInt16))
        wavefile.setframerate(rate)
        wavefile.writeframes(b''.join(frames))
        wav_buffer.seek(0)

    return wav_buffer
    ```

    此代码创建一个二进制缓冲区，并将所有捕捉到的音频以 [WAV 文件](https://wikipedia.org/wiki/WAV) 的形式写入其中。这是一种将未压缩音频写入文件的标准方式。然后返回此缓冲区。

1. 添加以下 `play_audio` 函数以回放音频缓冲区：

    ```python
    def play_audio(buffer):
        stream = audio.open(format = pyaudio.paInt16,
                            rate = rate,
                            channels = 1,
                            output_device_index = speaker_card_number,
                            output = True)
    
        with wave.open(buffer, 'rb') as wf:
            data = wf.readframes(4096)
    
            while len(data) > 0:
                stream.write(data)
                data = wf.readframes(4096)
    
            stream.close()
    ```

    此函数打开另一个音频流，这次是用于输出 - 播放音频。它使用与输入流相同的设置。缓冲区被作为 WAV 文件打开，并以 4096 字节块的形式写入输出流，从而播放音频。然后关闭流。

1. 在 `capture_audio` 函数下方添加以下代码，以循环检测按钮是否被按下。一旦按钮被按下，音频将被捕捉并播放。

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. 运行代码。按下按钮并对着麦克风说话。完成后释放按钮，您将听到录音。

    在创建 PyAudio 实例时，您可能会看到一些 ALSA 错误。这是由于树莓派上为您未使用的音频设备配置所致。可以忽略这些错误。

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    如果您收到以下错误：

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    请将 `rate` 更改为 44100 或 16000。

> 💁 您可以在 [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) 文件夹中找到此代码。

😀 您的音频录制程序成功了！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。对于因使用本翻译而引起的任何误解或误读，我们概不负责。