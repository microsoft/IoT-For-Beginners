<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-24T23:20:19+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "tw"
}
-->
# 建造夜燈 - Raspberry Pi

在本課程的這部分，你將為 Raspberry Pi 添加一個 LED，並用它來製作一個夜燈。

## 硬體

夜燈現在需要一個執行器。

執行器是一個 **LED**，即[發光二極管](https://wikipedia.org/wiki/Light-emitting_diode)，當電流通過時會發光。這是一個數位執行器，具有兩種狀態：開和關。傳送值 1 會打開 LED，而傳送值 0 會關閉它。LED 是一個外部的 Grove 執行器，需要連接到 Raspberry Pi 上的 Grove Base hat。

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

![一個 Grove LED](../../../../../translated_images/tw/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. 選擇你喜歡的 LED，將其引腳插入 LED 模組上的兩個孔中。

    LED 是發光二極管，而二極管是一種只能讓電流單向通過的電子元件。這意味著 LED 必須以正確的方向連接，否則無法工作。

    LED 的一個引腳是正極，另一個是負極。LED 並非完全圓形，其中一側稍微扁平一些。稍微扁平的一側是負極。當你將 LED 連接到模組時，確保圓形一側的引腳連接到模組外側標有 **+** 的插槽，而扁平一側的引腳連接到模組中間較近的插槽。

1. LED 模組有一個旋鈕，可以用來調節亮度。使用小型十字螺絲起子將其逆時針旋轉到最亮的位置。

1. 將 Grove 電纜的一端插入 LED 模組上的插槽。電纜只能以一種方向插入。

1. 在 Raspberry Pi 關機的情況下，將 Grove 電纜的另一端連接到 Grove Base hat 上標有 **D5** 的數位插槽。這個插槽位於 GPIO 引腳旁邊的一排插槽中，從左數第二個。

![Grove LED 連接到 D5 插槽](../../../../../translated_images/tw/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## 編寫夜燈程式

現在可以使用 Grove 光感測器和 Grove LED 來編寫夜燈程式。

### 任務 - 編寫夜燈程式

編寫夜燈程式。

1. 啟動 Raspberry Pi，等待其完成啟動。

1. 在 VS Code 中打開你在本作業前一部分中建立的夜燈專案，可以直接在 Raspberry Pi 上運行，也可以使用 Remote SSH 擴展連接。

1. 在 `app.py` 文件的頂部其他 `import` 行下方，添加以下程式碼以匯入所需的庫。

    ```python
    from grove.grove_led import GroveLed
    ```

    `from grove.grove_led import GroveLed` 語句從 Grove Python 庫中匯入 `GroveLed`。該庫包含與 Grove LED 互動的程式碼。

1. 在 `light_sensor` 宣告之後，添加以下程式碼來建立管理 LED 的類別實例：

    ```python
    led = GroveLed(5)
    ```

    `led = GroveLed(5)` 這一行建立了一個 `GroveLed` 類別的實例，連接到 **D5** 引腳——即 LED 所連接的數位 Grove 引腳。

    > 💁 每個插槽都有唯一的引腳編號。引腳 0、2、4 和 6 是類比引腳，引腳 5、16、18、22、24 和 26 是數位引腳。

1. 在 `while` 迴圈內、`time.sleep` 之前添加一個檢查，用於檢查光線水平並開啟或關閉 LED：

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    此程式碼檢查 `light` 值。如果該值小於 300，則調用 `GroveLed` 類別的 `on` 方法，向 LED 傳送數位值 1，將其打開。如果光線值大於或等於 300，則調用 `off` 方法，傳送數位值 0，將其關閉。

    > 💁 此程式碼應與 `print('Light level:', light)` 行保持相同的縮排級別，以確保它位於 while 迴圈內！

    > 💁 當向執行器傳送數位值時，值 0 表示 0V，而值 1 表示設備的最大電壓。對於使用 Grove 感測器和執行器的 Raspberry Pi，值 1 的電壓為 3.3V。

1. 在 VS Code 的終端中，運行以下命令來執行你的 Python 應用程式：

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

1. 遮住並移開光感測器。注意當光線值小於或等於 300 時，LED 會亮起；當光線值大於 300 時，LED 會熄滅。

    > 💁 如果 LED 沒有亮起，請確保它的連接方向正確，並且旋鈕已調至最亮。

![LED 連接到 Raspberry Pi，隨光線水平變化而亮起和熄滅](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 你可以在 [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi) 資料夾中找到此程式碼。

😀 你的夜燈程式成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用本翻譯而引起的任何誤解或錯誤解讀概不負責。