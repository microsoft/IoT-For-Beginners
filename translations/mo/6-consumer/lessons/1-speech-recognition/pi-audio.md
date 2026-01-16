<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-27T00:18:58+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "mo"
}
-->
# 捕捉音頻 - Raspberry Pi

在本課程的這部分，你將撰寫程式碼以在 Raspberry Pi 上捕捉音頻。音頻捕捉將由按鈕控制。

## 硬體

Raspberry Pi 需要一個按鈕來控制音頻捕捉。

你將使用的是 Grove 按鈕。這是一種數位感測器，可以開啟或關閉信號。這些按鈕可以配置為在按下時發送高信號，未按下時發送低信號，或者按下時發送低信號，未按下時發送高信號。

如果你使用的是 ReSpeaker 2-Mics Pi HAT 作為麥克風，那麼不需要額外連接按鈕，因為這個 HAT 已經內建了一個按鈕。直接跳到下一部分。

### 連接按鈕

按鈕可以連接到 Grove 基座 HAT。

#### 任務 - 連接按鈕

![Grove 按鈕](../../../../../translated_images/mo/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. 將 Grove 電纜的一端插入按鈕模組上的插座。它只能以一種方式插入。

1. 在 Raspberry Pi 關閉電源的情況下，將 Grove 電纜的另一端連接到 Pi 上 Grove 基座 HAT 的數位插座 **D5**。這個插座位於 GPIO 引腳旁邊的一排插座中，從左數第二個。

![Grove 按鈕連接到插座 D5](../../../../../translated_images/mo/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## 捕捉音頻

你可以使用 Python 程式碼從麥克風捕捉音頻。

### 任務 - 捕捉音頻

1. 啟動 Raspberry Pi，並等待其完成啟動。

1. 啟動 VS Code，可以直接在 Pi 上操作，或者通過 Remote SSH 擴展連接。

1. PyAudio Pip 套件提供了錄製和播放音頻的功能。此套件依賴於一些音頻庫，需先安裝這些庫。在終端中執行以下命令進行安裝：

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. 安裝 PyAudio Pip 套件。

    ```sh
    pip3 install pyaudio
    ```

1. 建立一個名為 `smart-timer` 的新資料夾，並在此資料夾中新增一個名為 `app.py` 的檔案。

1. 在檔案的頂部新增以下導入：

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    這將導入 `pyaudio` 模組、一些處理 WAV 檔案的標準 Python 模組，以及 `grove.factory` 模組以導入用於建立按鈕類的 `Factory`。

1. 在此之下，新增程式碼以建立 Grove 按鈕。

    如果你使用的是 ReSpeaker 2-Mics Pi HAT，請使用以下程式碼：

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    這會在 **D17** 埠上建立一個按鈕，該埠是 ReSpeaker 2-Mics Pi HAT 上按鈕所連接的埠。此按鈕設定為在按下時發送低信號。

    如果你未使用 ReSpeaker 2-Mics Pi HAT，而是使用連接到基座 HAT 的 Grove 按鈕，請使用以下程式碼：

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    這會在 **D5** 埠上建立一個按鈕，該按鈕設定為在按下時發送高信號。

1. 在此之下，建立一個 PyAudio 類的實例以處理音頻：

    ```python
    audio = pyaudio.PyAudio()
    ```

1. 宣告麥克風和揚聲器的硬體卡號。這將是你在本課程早些時候執行 `arecord -l` 和 `aplay -l` 時找到的卡號。

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    將 `<microphone card number>` 替換為你的麥克風卡號。

    將 `<speaker card number>` 替換為你的揚聲器卡號，與你在 `alsa.conf` 檔案中設定的卡號相同。

1. 在此之下，宣告用於音頻捕捉和播放的採樣率。根據你使用的硬體，可能需要更改此值。

    ```python
    rate = 48000 #48KHz
    ```

    如果在稍後執行此程式碼時出現採樣率錯誤，請將此值更改為 `44100` 或 `16000`。值越高，音質越好。

1. 在此之下，建立一個名為 `capture_audio` 的新函數。此函數將用於從麥克風捕捉音頻：

    ```python
    def capture_audio():
    ```

1. 在此函數內，新增以下程式碼以捕捉音頻：

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

    此程式碼使用 PyAudio 物件開啟音頻輸入流。該流將以 16KHz 的速率從麥克風捕捉音頻，並以 4096 字節的緩衝區大小進行捕捉。

    程式碼會在 Grove 按鈕被按下時進行迴圈，每次將這些 4096 字節的緩衝區讀入一個陣列。

    > 💁 你可以在 [PyAudio 文件](https://people.csail.mit.edu/hubert/pyaudio/docs/) 中了解更多關於傳遞給 `open` 方法的選項。

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

    此程式碼建立一個二進制緩衝區，並將所有捕捉到的音頻以 [WAV 檔案](https://wikipedia.org/wiki/WAV) 的形式寫入。這是一種標準的未壓縮音頻檔案格式。該緩衝區隨後被返回。

1. 新增以下 `play_audio` 函數以播放音頻緩衝區：

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

    此函數開啟另一個音頻流，這次是用於輸出 - 播放音頻。它使用與輸入流相同的設定。緩衝區被作為 WAV 檔案開啟，並以 4096 字節的塊寫入輸出流，播放音頻。流隨後被關閉。

1. 在 `capture_audio` 函數下方新增以下程式碼，以迴圈直到按鈕被按下。一旦按鈕被按下，音頻將被捕捉並播放。

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. 執行程式碼。按下按鈕並對著麥克風說話。完成後釋放按鈕，你將聽到錄音。

    在建立 PyAudio 實例時，你可能會遇到一些 ALSA 錯誤。這是由於 Pi 上的音頻設備配置問題，這些設備你可能並未擁有。可以忽略這些錯誤。

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    如果你遇到以下錯誤：

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    請將 `rate` 更改為 `44100` 或 `16000`。

> 💁 你可以在 [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) 資料夾中找到此程式碼。

😀 恭喜！你的音頻錄製程式成功了！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。