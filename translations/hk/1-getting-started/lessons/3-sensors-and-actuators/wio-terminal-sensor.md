<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-26T15:08:11+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "hk"
}
-->
# 添加感應器 - Wio Terminal

在這部分課程中，你將使用 Wio Terminal 上的光感應器。

## 硬件

本課程使用的感應器是**光感應器**，它利用[光電二極管](https://wikipedia.org/wiki/Photodiode)將光轉換為電信號。這是一個模擬感應器，會傳送一個介於 0 到 1,023 的整數值，表示相對光量，但不對應任何標準測量單位，例如 [lux](https://wikipedia.org/wiki/Lux)。

光感應器內建於 Wio Terminal 中，透過背面的透明塑膠窗口可以看到。

![Wio Terminal 背面的光感應器](../../../../../translated_images/wio-light-sensor.b1f529f3c95f5165.hk.png)

## 編程光感應器

現在可以編程設備以使用內建的光感應器。

### 任務

編程設備。

1. 在 VS Code 中打開你在前一部分作業中創建的夜燈項目。

1. 在 `setup` 函數的底部添加以下一行：

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    這一行配置了用於與感應器硬件通信的引腳。

    `WIO_LIGHT` 引腳是連接到內建光感應器的 GPIO 引腳編號。該引腳被設置為 `INPUT`，表示它連接到感應器並將從引腳讀取數據。

1. 刪除 `loop` 函數的內容。

1. 在現在空的 `loop` 函數中添加以下代碼。

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    此代碼從 `WIO_LIGHT` 引腳讀取模擬值。這會從內建光感應器讀取一個介於 0 到 1,023 的值。該值隨後被發送到串口，當此代碼運行時，你可以在串口監視器中讀取它。`Serial.print` 會寫入文本但不附加換行符，因此每行都會以 `Light value:` 開始，並以實際的光值結束。

1. 在 `loop` 的末尾添加一個一秒（1,000 毫秒）的短暫延遲，因為光線水平不需要被連續檢查。延遲可以減少設備的功耗。

    ```cpp
    delay(1000);
    ```

1. 將 Wio Terminal 重新連接到你的電腦，並像之前一樣上傳新代碼。

1. 連接串口監視器。光值將輸出到終端。遮住或移開 Wio Terminal 背面的光感應器，值將會改變。

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 你可以在 [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal) 文件夾中找到此代碼。

😀 成功將感應器添加到你的夜燈程序！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，請注意自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為具權威性的來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。