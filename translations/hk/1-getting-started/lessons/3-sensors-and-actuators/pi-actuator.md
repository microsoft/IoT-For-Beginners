<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-26T15:05:29+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "hk"
}
-->
# 建造夜燈 - Raspberry Pi

在這部分課程中，你將在 Raspberry Pi 上添加一個 LED，並用它來製作一個夜燈。

## 硬件

夜燈現在需要一個執行器。

執行器是一個 **LED**，即[發光二極管](https://wikipedia.org/wiki/Light-emitting_diode)，當電流通過時會發光。這是一個數字執行器，具有兩種狀態：開和關。發送值 1 會打開 LED，發送值 0 則會關閉 LED。LED 是一個外部 Grove 執行器，需要連接到 Raspberry Pi 上的 Grove Base hat。

夜燈邏輯的伪代码如下：

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### 連接 LED

Grove LED 是一個模塊，包含多種顏色的 LED，讓你可以選擇喜歡的顏色。

#### 任務 - 連接 LED

連接 LED。

![一個 Grove LED](../../../../../translated_images/hk/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. 選擇你喜歡的 LED，並將 LED 的腳插入 LED 模塊上的兩個孔中。

    LED 是發光二極管，而二極管是一種只能單向導電的電子元件。這意味著 LED 必須以正確的方向連接，否則無法工作。

    LED 的其中一隻腳是正極，另一隻是負極。LED 並不是完全圓形的，其中一側稍微平坦一些。稍微平坦的一側是負極。當你將 LED 連接到模塊時，確保圓形一側的腳連接到模塊外側標記為 **+** 的插座，而平坦一側的腳連接到模塊中間附近的插座。

1. LED 模塊有一個旋轉按鈕，可以用來控制亮度。首先用小型十字螺絲刀將其逆時針旋轉到最大亮度。

1. 將 Grove 電纜的一端插入 LED 模塊上的插座。電纜只能以一種方向插入。

1. 在 Raspberry Pi 關閉電源的情況下，將 Grove 電纜的另一端連接到 Grove Base hat 上標記為 **D5** 的數字插座。這個插座位於 GPIO 插針旁邊的一排插座中，從左數第二個。

![Grove LED 連接到 D5 插座](../../../../../translated_images/hk/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## 編程夜燈

現在可以使用 Grove 光線感測器和 Grove LED 來編程夜燈。

### 任務 - 編程夜燈

編程夜燈。

1. 啟動 Raspberry Pi，並等待其完成啟動。

1. 在 VS Code 中打開你在上一部分作業中創建的夜燈項目，可以直接在 Raspberry Pi 上運行，也可以通過 Remote SSH 擴展連接。

1. 在 `app.py` 文件中添加以下代碼以導入所需的庫。這段代碼應該添加到其他 `import` 行的下方。

    ```python
    from grove.grove_led import GroveLed
    ```

    `from grove.grove_led import GroveLed` 語句從 Grove Python 庫中導入了 `GroveLed`。這個庫包含與 Grove LED 交互的代碼。

1. 在 `light_sensor` 聲明之後添加以下代碼，以創建管理 LED 的類的實例：

    ```python
    led = GroveLed(5)
    ```

    `led = GroveLed(5)` 這一行創建了一個 `GroveLed` 類的實例，並連接到 **D5** 插針——即 LED 所連接的 Grove 數字插針。

    > 💁 每個插座都有唯一的插針號碼。插針 0、2、4 和 6 是模擬插針，插針 5、16、18、22、24 和 26 是數字插針。

1. 在 `while` 循環內部，並在 `time.sleep` 之前添加一個檢查光線水平的代碼，用於控制 LED 的開啟或關閉：

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    這段代碼檢查 `light` 值。如果該值小於 300，則調用 `GroveLed` 類的 `on` 方法，向 LED 發送數字值 1，打開 LED。如果光線值大於或等於 300，則調用 `off` 方法，向 LED 發送數字值 0，關閉 LED。

    > 💁 這段代碼應該與 `print('Light level:', light)` 行保持相同的縮進級別，以確保它在 while 循環內部！

    > 💁 當向執行器發送數字值時，值 0 表示 0V，值 1 表示設備的最大電壓。對於 Raspberry Pi 使用的 Grove 感測器和執行器，值 1 的電壓為 3.3V。

1. 在 VS Code 的終端中運行以下命令以運行你的 Python 應用：

    ```sh
    python3 app.py
    ```

    光線值將輸出到控制台。

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. 遮住和移開光線感測器。注意當光線水平小於或等於 300 時，LED 會亮起；當光線水平大於 300 時，LED 會熄滅。

    > 💁 如果 LED 沒有亮起，請確保它的連接方向正確，並且旋轉按鈕已設置為最大亮度。

![LED 連接到 Raspberry Pi，隨光線水平變化而亮起和熄滅](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 你可以在 [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi) 文件夾中找到這段代碼。

😀 你的夜燈程式成功了！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。