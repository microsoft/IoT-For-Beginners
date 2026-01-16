<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-24T23:25:33+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "tw"
}
-->
# 添加感測器 - Wio Terminal

在本課程中，您將使用 Wio Terminal 上的光感測器。

## 硬體

本課程使用的感測器是**光感測器**，它利用[光電二極體](https://wikipedia.org/wiki/Photodiode)將光轉換為電信號。這是一個類比感測器，會傳送一個從 0 到 1,023 的整數值，表示相對的光量，但不對應於任何標準的測量單位，例如 [lux](https://wikipedia.org/wiki/Lux)。

光感測器內建於 Wio Terminal 中，可以透過背面的透明塑膠窗看到。

![Wio Terminal 背面的光感測器](../../../../../translated_images/tw/wio-light-sensor.b1f529f3c95f5165.webp)

## 程式設計光感測器

現在可以為裝置編寫程式來使用內建的光感測器。

### 任務

為裝置編寫程式。

1. 在 VS Code 中打開您在本作業前一部分中建立的夜燈專案。

1. 在 `setup` 函數的底部新增以下這一行：

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    這一行配置了用於與感測器硬體通信的引腳。

    `WIO_LIGHT` 引腳是連接到內建光感測器的 GPIO 引腳編號。此引腳被設置為 `INPUT`，表示它連接到感測器，並將從該引腳讀取數據。

1. 刪除 `loop` 函數的內容。

1. 在現在空的 `loop` 函數中新增以下程式碼。

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    此程式碼從 `WIO_LIGHT` 引腳讀取一個類比值。這會從內建光感測器讀取一個 0 到 1,023 的值。該值隨後被發送到序列埠，因此當此程式碼運行時，您可以在序列監視器中讀取它。`Serial.print` 會輸出文字但不換行，因此每行會以 `Light value:` 開頭，並以實際的光值結尾。

1. 在 `loop` 的結尾新增一個一秒（1,000 毫秒）的短暫延遲，因為光線水平不需要被連續檢查。延遲可以減少裝置的功耗。

    ```cpp
    delay(1000);
    ```

1. 將 Wio Terminal 重新連接到您的電腦，並像之前一樣上傳新程式碼。

1. 連接序列監視器。光值將輸出到終端機。遮住或移開 Wio Terminal 背面的光感測器，數值將會改變。

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

> 💁 您可以在 [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal) 資料夾中找到此程式碼。

😀 成功將感測器添加到您的夜燈程式中！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。