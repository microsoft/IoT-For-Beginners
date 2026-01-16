<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-26T15:40:12+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "hk"
}
-->
# 配置你的麥克風和喇叭 - Raspberry Pi

在這部分課程中，你將為你的 Raspberry Pi 添加麥克風和喇叭。

## 硬件

Raspberry Pi 需要一個麥克風。

Pi 本身並沒有內建麥克風，你需要添加一個外接麥克風。有多種方式可以做到：

* USB 麥克風
* USB 耳機
* USB 一體式會議麥克風
* USB 音頻轉接器和帶 3.5mm 插孔的麥克風
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 並非所有藍牙麥克風都能在 Raspberry Pi 上使用，因此如果你有藍牙麥克風或耳機，可能會遇到配對或錄音問題。

Raspberry Pi 配備了一個 3.5mm 耳機插孔。你可以使用它來連接耳機、耳機組或喇叭。你也可以通過以下方式添加喇叭：

* 通過顯示器或電視的 HDMI 音頻
* USB 喇叭
* USB 耳機
* USB 一體式會議麥克風
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)，並通過 3.5mm 插孔或 JST 接口連接喇叭

## 連接並配置麥克風和喇叭

麥克風和喇叭需要連接並進行配置。

### 任務 - 連接並配置麥克風

1. 使用合適的方法連接麥克風。例如，通過 USB 端口連接。

1. 如果你使用的是 ReSpeaker 2-Mics Pi HAT，可以移除 Grove 基座帽，然後將 ReSpeaker 帽安裝到其位置。

    ![一個安裝了 ReSpeaker 帽的 Raspberry Pi](../../../../../translated_images/hk/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    在本課程的後續部分，你將需要一個 Grove 按鈕，但此帽子內建了一個按鈕，因此不需要 Grove 基座帽。

    安裝帽子後，你需要安裝一些驅動程式。請參考 [Seeed 的入門指南](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) 了解驅動程式安裝的詳細說明。

    > ⚠️ 說明中使用了 `git` 來克隆一個倉庫。如果你的 Pi 上尚未安裝 `git`，可以通過以下命令進行安裝：
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. 在 Pi 的終端中運行以下命令，或者通過 VS Code 和遠程 SSH 會話連接，查看已連接的麥克風信息：

    ```sh
    arecord -l
    ```

    你將看到已連接的麥克風列表，類似如下：

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    假設你只有一個麥克風，你應該只看到一個條目。在 Linux 上配置麥克風可能會比較棘手，因此最好只使用一個麥克風並拔掉其他的。

    記下卡號，稍後你會用到。在上述輸出中，卡號是 1。

### 任務 - 連接並配置喇叭

1. 使用合適的方法連接喇叭。

1. 在 Pi 的終端中運行以下命令，或者通過 VS Code 和遠程 SSH 會話連接，查看已連接的喇叭信息：

    ```sh
    aplay -l
    ```

    你將看到已連接的喇叭列表，類似如下：

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

    你總是會看到 `card 0: Headphones`，因為這是內建的耳機插孔。如果你添加了額外的喇叭，例如 USB 喇叭，你也會看到它列出。

1. 如果你使用的是額外的喇叭，而不是連接到內建耳機插孔的喇叭或耳機，你需要將其配置為默認設備。為此，運行以下命令：

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    這將在 `nano` 中打開一個配置文件，`nano` 是一個基於終端的文本編輯器。使用鍵盤上的箭頭鍵向下滾動，直到找到以下行：

    ```output
    defaults.pcm.card 0
    ```

    將值從 `0` 更改為你想使用的卡號，該卡號來自 `aplay -l` 命令的返回列表。例如，在上述輸出中，有一個名為 `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]` 的第二個聲卡，使用卡號 1。要使用它，我會將該行更新為：

    ```output
    defaults.pcm.card 1
    ```

    將此值設置為合適的卡號。你可以使用鍵盤上的箭頭鍵導航到該數字，然後像編輯普通文本文件一樣刪除並輸入新數字。

1. 按 `Ctrl+x` 保存更改並關閉文件。按 `y` 保存文件，然後按 `return` 確定文件名。

### 任務 - 測試麥克風和喇叭

1. 運行以下命令，通過麥克風錄製 5 秒音頻：

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    在命令運行期間，對著麥克風發出聲音，例如說話、唱歌、打節奏、演奏樂器或任何你喜歡的方式。

1. 5 秒後，錄音將停止。運行以下命令播放音頻：

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    你將聽到音頻通過喇叭播放。根據需要調整喇叭的輸出音量。

1. 如果需要調整內建麥克風端口的音量或麥克風的增益，可以使用 `alsamixer` 工具。你可以在 [Linux alsamixer 手冊頁](https://linux.die.net/man/1/alsamixer) 上了解更多關於此工具的信息。

1. 如果播放音頻時出現錯誤，檢查你在 `alsa.conf` 文件中設置的 `defaults.pcm.card` 卡號是否正確。

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，請注意自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。