<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-26T15:07:03+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "hk"
}
-->
# 建造夜燈 - 虛擬物聯網硬件

在本課程的這部分，你將為虛擬物聯網設備添加一個 LED，並用它來創建一個夜燈。

## 虛擬硬件

夜燈需要一個執行器，通過 CounterFit 應用程序創建。

這個執行器是一個 **LED**。在實體物聯網設備中，它是一個[發光二極管](https://wikipedia.org/wiki/Light-emitting_diode)，當電流通過時會發光。這是一個數字執行器，具有兩種狀態：開和關。發送值 1 會打開 LED，發送值 0 會關閉 LED。

夜燈邏輯的偽代碼如下：

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### 在 CounterFit 中添加執行器

要使用虛擬 LED，你需要將它添加到 CounterFit 應用程序中。

#### 任務 - 在 CounterFit 中添加執行器

將 LED 添加到 CounterFit 應用程序。

1. 確保 CounterFit 網頁應用程序正在運行（從本作業的上一部分開始）。如果未運行，請啟動它並重新添加光線感應器。

1. 創建一個 LED：

    1. 在 *Actuator* 面板的 *Create actuator* 框中，打開 *Actuator type* 下拉框並選擇 *LED*。

    1. 將 *Pin* 設置為 *5*。

    1. 選擇 **Add** 按鈕，在 Pin 5 上創建 LED。

    ![LED 設置](../../../../../translated_images/hk/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    LED 將被創建並顯示在執行器列表中。

    ![已創建的 LED](../../../../../translated_images/hk/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    LED 創建後，你可以使用 *Color* 選擇器更改顏色。選擇顏色後，點擊 **Set** 按鈕即可更改顏色。

### 編程夜燈

現在可以使用 CounterFit 的光線感應器和 LED 來編程夜燈。

#### 任務 - 編程夜燈

編程夜燈。

1. 在 VS Code 中打開你在本作業上一部分創建的夜燈項目。如果需要，終止並重新創建終端以確保它使用虛擬環境運行。

1. 打開 `app.py` 文件。

1. 在 `app.py` 文件的頂部，其他 `import` 行之下，添加以下代碼以導入所需的庫：

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    `from counterfit_shims_grove.grove_led import GroveLed` 語句從 CounterFit Grove shim Python 庫中導入 `GroveLed`。此庫包含與 CounterFit 應用程序中創建的 LED 交互的代碼。

1. 在 `light_sensor` 聲明之後添加以下代碼，以創建管理 LED 的類的實例：

    ```python
    led = GroveLed(5)
    ```

    `led = GroveLed(5)` 行創建了一個 `GroveLed` 類的實例，連接到 Pin **5**——CounterFit Grove 的 LED 所連接的 Pin。

1. 在 `while` 循環內，`time.sleep` 之前添加檢查光線水平並打開或關閉 LED 的代碼：

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    此代碼檢查 `light` 值。如果該值小於 300，則調用 `GroveLed` 類的 `on` 方法，向 LED 發送數字值 1，打開 LED。如果光線值大於或等於 300，則調用 `off` 方法，向 LED 發送數字值 0，關閉 LED。

    > 💁 此代碼應與 `print('Light level:', light)` 行保持相同的縮進級別，以確保它在 while 循環內！

1. 從 VS Code 終端運行以下命令以運行你的 Python 應用程序：

    ```sh
    python3 app.py
    ```

    光線值將輸出到控制台。

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. 更改 *Value* 或 *Random* 設置，使光線水平在 300 以上和以下變化。LED 將會打開和關閉。

![CounterFit 應用程序中的 LED 隨光線水平變化而打開和關閉](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 你可以在 [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device) 文件夾中找到此代碼。

😀 你的夜燈程序成功了！

---

**免責聲明**：  
此文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤詮釋概不負責。