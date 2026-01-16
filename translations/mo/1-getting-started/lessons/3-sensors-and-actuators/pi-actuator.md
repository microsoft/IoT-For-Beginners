<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-26T23:27:22+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "mo"
}
-->
# 建造夜燈 - Raspberry Pi

在本課程中，您將在 Raspberry Pi 上添加 LED，並使用它來製作夜燈。

## 硬體

夜燈現在需要一個致動器。

致動器是一個 **LED**，即[發光二極管](https://wikipedia.org/wiki/Light-emitting_diode)，當電流通過時會發光。這是一個數位致動器，具有兩種狀態：開啟和關閉。傳送值 1 會使 LED 開啟，傳送值 0 則會使其關閉。LED 是一個外部 Grove 致動器，需要連接到 Raspberry Pi 上的 Grove Base hat。

夜燈邏輯的偽代碼如下：

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### 連接 LED

Grove LED 是一個模組，包含多種 LED，您可以選擇喜歡的顏色。

#### 任務 - 連接 LED

連接 LED。

![Grove LED](../../../../../translated_images/mo/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. 選擇您喜歡的 LED，並將其腳插入 LED 模組上的兩個孔中。

    LED 是發光二極管，而二極管是一種只能單向導電的電子元件。這意味著 LED 必須以正確的方向連接，否則無法工作。

    LED 的其中一隻腳是正極引腳，另一隻是負極引腳。LED 並非完全圓形，其中一側稍微平坦一些。稍微平坦的一側是負極引腳。當您將 LED 連接到模組時，請確保圓形一側的引腳連接到模組外側標記為 **+** 的插座，而平坦一側的引腳連接到模組中間較近的插座。

1. LED 模組有一個旋鈕，可以用來調節亮度。首先使用小型十字螺絲刀將其逆時針旋轉到最亮。

1. 將 Grove 電纜的一端插入 LED 模組上的插座。電纜只能以一種方向插入。

1. 在 Raspberry Pi 關閉電源的情況下，將 Grove 電纜的另一端連接到 Grove Base hat 上標記為 **D5** 的數位插座。此插座位於 GPIO 引腳旁邊的一排插座中，從左數第二個。

![Grove LED 連接到 D5 插座](../../../../../translated_images/mo/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## 程式設計夜燈

現在可以使用 Grove 光線感測器和 Grove LED 來程式設計夜燈。

### 任務 - 程式設計夜燈

程式設計夜燈。

1. 啟動 Raspberry Pi，並等待其完成啟動。

1. 在 VS Code 中打開您在本作業前一部分中建立的夜燈專案，可以直接在 Pi 上運行，也可以使用 Remote SSH 擴展連接。

1. 在 `app.py` 文件中添加以下程式碼以匯入所需的庫。這段程式碼應添加到頂部，其他 `import` 行的下方。

    ```python
    from grove.grove_led import GroveLed
    ```

    `from grove.grove_led import GroveLed` 語句從 Grove Python 庫中匯入 `GroveLed`。此庫包含與 Grove LED 互動的程式碼。

1. 在 `light_sensor` 宣告之後添加以下程式碼，以建立管理 LED 的類別實例：

    ```python
    led = GroveLed(5)
    ```

    `led = GroveLed(5)` 行建立了一個 `GroveLed` 類的實例，並連接到 **D5** 引腳——即 LED 所連接的 Grove 數位引腳。

    > 💁 每個插座都有唯一的引腳編號。引腳 0、2、4 和 6 是類比引腳，引腳 5、16、18、22、24 和 26 是數位引腳。

1. 在 `while` 迴圈內，並在 `time.sleep` 之前添加檢查光線水平的程式碼，以控制 LED 的開啟或關閉：

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    此程式碼檢查 `light` 值。如果該值小於 300，則調用 `GroveLed` 類的 `on` 方法，向 LED 傳送數位值 1，將其開啟。如果光線值大於或等於 300，則調用 `off` 方法，傳送數位值 0，將其關閉。

    > 💁 此程式碼應與 `print('Light level:', light)` 行保持相同的縮排級別，以確保它位於 while 迴圈內！

    > 💁 當向致動器傳送數位值時，值 0 表示 0V，值 1 表示設備的最大電壓。對於 Raspberry Pi 使用的 Grove 感測器和致動器，值 1 的電壓為 3.3V。

1. 在 VS Code 的終端中運行以下命令以執行您的 Python 應用程式：

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

1. 遮住並移開光線感測器。注意當光線水平小於或等於 300 時，LED 會亮起；當光線水平大於 300 時，LED 會熄滅。

    > 💁 如果 LED 沒有亮起，請確保其連接方向正確，並且旋鈕已調至最亮。

![LED 連接到 Pi，隨光線水平變化而開啟和關閉](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 您可以在 [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi) 資料夾中找到此程式碼。

😀 您的夜燈程式成功了！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。