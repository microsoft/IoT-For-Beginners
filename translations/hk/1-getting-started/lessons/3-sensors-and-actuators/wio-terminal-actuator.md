<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "db44083b4dc6fb06eac83c4f16448940",
  "translation_date": "2025-08-26T15:06:12+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-actuator.md",
  "language_code": "hk"
}
-->
# 製作夜燈 - Wio Terminal

在這部分課程中，你將為 Wio Terminal 添加一個 LED，並用它來製作一個夜燈。

## 硬件

夜燈現在需要一個執行器。

這個執行器是一個 **LED**，即[發光二極管](https://wikipedia.org/wiki/Light-emitting_diode)，當電流通過時會發光。這是一個數字執行器，只有兩種狀態：開和關。傳送值 1 會打開 LED，傳送值 0 會關閉它。這是一個外部的 Grove 執行器，需要連接到 Wio Terminal。

夜燈邏輯的偽代碼如下：

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### 連接 LED

Grove LED 是一個模組，內含多種顏色的 LED，讓你可以選擇喜歡的顏色。

#### 任務 - 連接 LED

連接 LED。

![一個 Grove LED](../../../../../translated_images/hk/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. 選擇你喜歡的 LED，將其引腳插入 LED 模組上的兩個孔中。

   LED 是發光二極管，而二極管是一種只能單向導電的電子元件。這意味著 LED 必須以正確的方向連接，否則無法工作。

   LED 的一個引腳是正極，另一個是負極。LED 並非完全圓形，其中一側稍微扁平一些。稍微扁平的一側是負極。當你將 LED 連接到模組時，確保圓形一側的引腳連接到模組外側標有 **+** 的插座，而扁平一側連接到模組中間較近的插座。

1. LED 模組上有一個旋鈕，可以用來調節亮度。使用小型十字螺絲刀將其逆時針旋轉到最亮的位置。

1. 將 Grove 電纜的一端插入 LED 模組上的插座。電纜只能以一種方向插入。

1. 在 Wio Terminal 與電腦或其他電源斷開連接的情況下，將 Grove 電纜的另一端連接到 Wio Terminal 上屏幕右側的 Grove 插座。這是距離電源按鈕最遠的插座。

   > 💁 右側的 Grove 插座可用於模擬或數字傳感器和執行器。左側插座僅用於 I2C 和數字傳感器及執行器。

![Grove LED 連接到右側插座](../../../../../translated_images/hk/wio-led.265a1897e72d7f21.webp)

## 編程夜燈

現在可以使用內建的光線傳感器和 Grove LED 來編程夜燈。

### 任務 - 編程夜燈

編程夜燈。

1. 在 VS Code 中打開你在本次作業的上一部分中創建的夜燈項目。

1. 在 `setup` 函數的底部添加以下一行代碼：

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    這行代碼配置了用於通過 Grove 端口與 LED 通信的引腳。

    `D0` 引腳是右側 Grove 插座的數字引腳。這個引腳被設置為 `OUTPUT`，表示它連接到執行器，並將數據寫入該引腳。

1. 在 `loop` 函數中的 `delay` 之前立即添加以下代碼：

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    這段代碼檢查 `light` 值。如果該值小於 300，則向 `D0` 數字引腳發送 `HIGH` 值。`HIGH` 值為 1，會打開 LED。如果光線值大於或等於 300，則向引腳發送 `LOW` 值，`LOW` 值為 0，會關閉 LED。

    > 💁 當向執行器發送數字值時，`LOW` 值為 0v，`HIGH` 值為設備的最大電壓。對於 Wio Terminal，`HIGH` 電壓為 3.3V。

1. 將 Wio Terminal 重新連接到你的電腦，並像之前一樣上傳新代碼。

1. 連接串行監視器。光線值將輸出到終端。

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

1. 遮住和移開光線傳感器。注意當光線值為 300 或更低時，LED 會亮起；當光線值大於 300 時，LED 會熄滅。

![LED 連接到 Wio，隨著光線值變化亮起和熄滅](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 你可以在 [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal) 文件夾中找到這段代碼。

😀 你的夜燈程序成功了！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。