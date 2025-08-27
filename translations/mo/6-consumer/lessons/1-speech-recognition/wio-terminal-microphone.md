<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-27T00:32:01+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "mo"
}
-->
# 配置你的麥克風和揚聲器 - Wio Terminal

在本課程中，你將為 Wio Terminal 添加揚聲器。Wio Terminal 已內建麥克風，可用於捕捉語音。

## 硬體

Wio Terminal 已內建麥克風，可用於捕捉音訊以進行語音識別。

![Wio Terminal 上的麥克風](../../../../../translated_images/wio-mic.3f8c843dbe8ad917424037a93e3d25c62634add00a04dd8e091317b5a7a90088.mo.png)

若要添加揚聲器，你可以使用 [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)。這是一塊外接板，包含兩個 MEMS 麥克風，以及一個揚聲器連接器和耳機插孔。

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab1676d24ac2764e64fac5339046ae07be8b45ce07633d61b79b.mo.png)

你需要添加耳機、一個帶有 3.5mm 插頭的揚聲器，或者像 [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html) 這樣的帶有 JST 接頭的揚聲器。

要連接 ReSpeaker 2-Mics Pi Hat，你需要 40 根針對針（也稱為公對公）的跳線。

> 💁 如果你熟悉焊接，可以使用 [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) 來連接 ReSpeaker。

你還需要一張 SD 卡來下載和播放音訊。Wio Terminal 僅支持最大 16GB 的 SD 卡，並且需要格式化為 FAT32 或 exFAT。

### 任務 - 連接 ReSpeaker Pi Hat

1. 在 Wio Terminal 關機的情況下，使用跳線將 ReSpeaker 2-Mics Pi Hat 連接到 Wio Terminal 的 GPIO 插座：

    需要按照以下方式連接引腳：

    ![引腳圖](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa6508103880d256cdf99ee7219e190db257c7261e4aec219759dc67b9.mo.png)

1. 將 ReSpeaker 和 Wio Terminal 放置好，GPIO 插座朝上，位於左側。

1. 從 ReSpeaker GPIO 插座左上角的插孔開始，使用針對針跳線將 ReSpeaker 左上角的插孔連接到 Wio Terminal 左上角的插孔。

1. 按此方式依次連接 GPIO 插座左側的所有引腳。確保引腳插牢。

    ![ReSpeaker 左側引腳連接到 Wio Terminal 左側引腳](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba24004824ee5e06b83b6d10952550003a3efb603182121521b0ef.mo.png)

    ![ReSpeaker 左側引腳連接到 Wio Terminal 左側引腳](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f8ffe56f9294794f4a8fa123860d76067a79e9ea385d1bf56.mo.png)

    > 💁 如果你的跳線是連成一條排線，保持它們在一起會更容易確保所有線都按順序連接。

1. 使用 ReSpeaker 和 Wio Terminal 的右側 GPIO 插座重複此過程。這些線需要繞過已經連接的線。

    ![ReSpeaker 右側引腳連接到 Wio Terminal 右側引腳](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa9307a6a954f9ae8a71b77e39ada6a5ef1a059d341dc850fd90c.mo.png)

    ![ReSpeaker 右側引腳連接到 Wio Terminal 右側引腳](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437de720cba2719d83992413caed1b620b6148f6c8924889afb.mo.png)

    > 💁 如果你的跳線是連成一條排線，將它們分成兩條排線。分別從已連接的線兩側穿過。

    > 💁 你可以使用膠帶將引腳固定成一個塊，這樣可以防止在連接過程中引腳脫落。
    >
    > ![用膠帶固定的引腳](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3cd656ccd8f4053f8845d6aaa3af164d24cb7dbd54a4bb470.mo.png)

1. 你需要添加一個揚聲器。

    * 如果你使用的是帶有 JST 線的揚聲器，將其連接到 ReSpeaker 的 JST 接口。

      ![使用 JST 線連接到 ReSpeaker 的揚聲器](../../../../../translated_images/respeaker-jst-speaker.a441d177809df9458041a2012dd336dbb22c00a5c9642647109d2940a50d6fcc.mo.png)

    * 如果你使用的是帶有 3.5mm 插頭的揚聲器或耳機，將其插入 3.5mm 插孔。

      ![使用 3.5mm 插孔連接到 ReSpeaker 的揚聲器](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751f0abf854869b6b779c90c12ae3e48909944a7e48aeee3c7e.mo.png)

### 任務 - 設置 SD 卡

1. 將 SD 卡連接到你的電腦，如果電腦沒有 SD 卡插槽，請使用外接讀卡器。

1. 使用電腦上的適當工具格式化 SD 卡，確保使用 FAT32 或 exFAT 文件系統。

1. 將 SD 卡插入 Wio Terminal 左側電源按鈕下方的 SD 卡插槽。確保卡完全插入並卡住——你可能需要使用一個細小的工具或另一張 SD 卡來幫助將其完全推入。

    ![將 SD 卡插入電源開關下方的 SD 卡插槽](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f8f9c8cc015b3263964bb26ab5c7e25b41747988cc5280d64.mo.png)

    > 💁 要取出 SD 卡，你需要稍微按入卡片，它會彈出。你可能需要使用像平頭螺絲刀或另一張 SD 卡這樣的細小工具來完成此操作。

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。