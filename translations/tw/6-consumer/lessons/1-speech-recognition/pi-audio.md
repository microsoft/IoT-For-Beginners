<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-25T00:16:59+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "tw"
}
-->
# 捕捉音訊 - Raspberry Pi

在本課程中，您將撰寫程式碼以在 Raspberry Pi 上捕捉音訊。音訊捕捉將由按鈕控制。

## 硬體

Raspberry Pi 需要一個按鈕來控制音訊捕捉。

您將使用的是 Grove 按鈕。這是一種數位感測器，可將訊號開啟或關閉。這些按鈕可以配置為在按下時發送高訊號，未按下時發送低訊號，或者在按下時發送低訊號，未按下時發送高訊號。

如果您使用的是 ReSpeaker 2-Mics Pi HAT 作為麥克風，那麼不需要額外連接按鈕，因為此 HAT 已經內建了一個按鈕。直接跳到下一部分。

### 連接按鈕

按鈕可以連接到 Grove 基座 HAT。

#### 任務 - 連接按鈕

![Grove 按鈕](../../../../../translated_images/tw/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. 將 Grove 電纜的一端插入按鈕模組上的插座。它只能以一種方式插入。

1. 在 Raspberry Pi 關機的情況下，將 Grove 電纜的另一端連接到 Pi 上 Grove 基座 HAT 的數位插座 **D5**。此插座位於 GPIO 引腳旁邊的一排插座中，從左數第二個。

![Grove 按鈕連接到插座 D5](../../../../../translated_images/tw/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## 捕捉音訊

您可以使用 Python 程式碼從麥克風捕捉音訊。

### 任務 - 捕捉音訊

1. 啟動 Raspberry Pi，並等待其完成啟動。

1. 啟動 VS Code，可以直接在 Pi 上啟動，或者通過 Remote SSH 擴展連接。

1. PyAudio Pip 套件提供了錄製和播放音訊的功能。此套件依賴於一些音訊庫，需先安裝這些庫。在終端中執行以下命令以安裝：

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. 安裝 PyAudio Pip 套件。

    ```sh
    pip3 install pyaudio
    ```

1. 建立一個名為 `smart-timer` 的新資料夾，並在此資料夾中新增一個名為 `app.py` 的檔案。

1. 在檔案的頂部新增以下匯入：

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    這匯入了 `pyaudio` 模組、一些處理 WAV 檔案的標準 Python 模組，以及 `grove.factory` 模組以匯入用於建立按鈕類別的 `Factory`。

1. 在此之下，新增程式碼以建立 Grove 按鈕。

    如果您使用的是 ReSpeaker 2-Mics Pi HAT，請使用以下程式碼：

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    這會在 **D17** 埠上建立一個按鈕，該埠是 ReSpeaker 2-Mics Pi HAT 上按鈕所連接的埠。此按鈕設定為在按下時發送低訊號。

    如果您未使用 ReSpeaker 2-Mics Pi HAT，而是使用連接到基座 HAT 的 Grove 按鈕，請使用以下程式碼：

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    這會在 **D5** 埠上建立一個按鈕，該按鈕設定為在按下時發送高訊號。

1. 在此之下，建立一個 PyAudio 類別的實例以處理音訊：

    ```python
    audio = pyaudio.PyAudio()
    ```

1. 宣告麥克風和揚聲器的硬體卡號。這將是您在本課程中早些時候執行 `arecord -l` 和 `aplay -l` 時找到的卡號。

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    將 `<microphone card number>` 替換為您的麥克風卡號。

    將 `<speaker card number>` 替換為您的揚聲器卡號，與您在 `alsa.conf` 檔案中設定的卡號相同。

1. 在此之下，宣告用於音訊捕捉和播放的採樣率。根據您使用的硬體，可能需要更改此值。

    ```python
    rate = 48000 #48KHz
    ```

    如果稍後執行此程式碼時出現採樣率錯誤，請將此值更改為 `44100` 或 `16000`。值越高，音質越好。

1. 在此之下，建立一個名為 `capture_audio` 的新函數。此函數將用於從麥克風捕捉音訊：

    ```python
    def capture_audio():
    ```

1. 在此函數內，新增以下程式碼以捕捉音訊：

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

    此程式碼使用 PyAudio 物件開啟音訊輸入流。此流將以 16KHz 的速率從麥克風捕捉音訊，並以 4096 字節大小的緩衝區捕捉。

    程式碼會在 Grove 按鈕被按下時進行迴圈，每次將這些 4096 字節的緩衝區讀入陣列。

    > 💁 您可以在 [PyAudio 文件](https://people.csail.mit.edu/hubert/pyaudio/docs/) 中了解更多關於傳遞給 `open` 方法的選項。

    一旦按鈕被釋放，流將停止並關閉。

1. 在此函數的結尾新增以下程式碼：

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

    此程式碼建立一個二進位緩衝區，並將所有捕捉的音訊以 [WAV 檔案](https://wikipedia.org/wiki/WAV) 的形式寫入其中。這是一種將未壓縮音訊寫入檔案的標準方式。然後返回此緩衝區。

1. 新增以下 `play_audio` 函數以播放音訊緩衝區：

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

    此函數開啟另一個音訊流，這次是用於輸出 - 播放音訊。它使用與輸入流相同的設定。緩衝區被作為 WAV 檔案開啟，並以 4096 字節的塊寫入輸出流，播放音訊。然後流被關閉。

1. 在 `capture_audio` 函數下方新增以下程式碼以進行迴圈，直到按鈕被按下。一旦按鈕被按下，音訊將被捕捉並播放。

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. 執行程式碼。按下按鈕並對著麥克風說話。完成後釋放按鈕，您將聽到錄音。

    在建立 PyAudio 實例時，您可能會遇到一些 ALSA 錯誤。這是由於 Pi 上音訊設備的配置問題，您可以忽略這些錯誤。

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    如果您遇到以下錯誤：

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    請將 `rate` 更改為 44100 或 16000。

> 💁 您可以在 [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) 資料夾中找到此程式碼。

😀 您的音訊錄製程式成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原文文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。