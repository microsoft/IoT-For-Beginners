<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-24T23:23:07+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "tw"
}
-->
# 建立夜燈 - 虛擬物聯網硬體

在本課程的這部分，你將為虛擬物聯網設備添加一個 LED，並使用它來創建一個夜燈。

## 虛擬硬體

夜燈需要一個執行器，這是在 CounterFit 應用中創建的。

這個執行器是一個 **LED**。在實體物聯網設備中，它是一個[發光二極管](https://wikipedia.org/wiki/Light-emitting_diode)，當電流通過時會發光。這是一個數位執行器，具有兩種狀態：開和關。傳送值 1 會打開 LED，傳送值 0 會關閉 LED。

夜燈邏輯的偽代碼如下：

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### 將執行器添加到 CounterFit

要使用虛擬 LED，你需要將它添加到 CounterFit 應用中。

#### 任務 - 將執行器添加到 CounterFit

將 LED 添加到 CounterFit 應用中。

1. 確保 CounterFit 網頁應用正在運行（從本作業的上一部分開始）。如果未運行，啟動它並重新添加光感測器。

1. 創建一個 LED：

    1. 在 *Actuator* 面板的 *Create actuator* 框中，展開 *Actuator type* 下拉框並選擇 *LED*。

    1. 將 *Pin* 設置為 *5*。

    1. 選擇 **Add** 按鈕，在 Pin 5 上創建 LED。

    ![LED 設定](../../../../../translated_images/tw/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    LED 將被創建並顯示在執行器列表中。

    ![已創建的 LED](../../../../../translated_images/tw/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    LED 創建後，你可以使用 *Color* 選擇器更改顏色。選擇 **Set** 按鈕以更改顏色。

### 編寫夜燈程式

現在可以使用 CounterFit 光感測器和 LED 編寫夜燈程式。

#### 任務 - 編寫夜燈程式

編寫夜燈程式。

1. 在 VS Code 中打開你在本作業上一部分中創建的夜燈專案。如果需要，終止並重新創建終端以確保它使用虛擬環境運行。

1. 打開 `app.py` 文件。

1. 在 `app.py` 文件中添加以下程式碼以匯入所需的庫。這段程式碼應添加在其他 `import` 行的下方。

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    `from counterfit_shims_grove.grove_led import GroveLed` 語句從 CounterFit Grove shim Python 庫中匯入 `GroveLed`。該庫包含與 CounterFit 應用中創建的 LED 互動的程式碼。

1. 在 `light_sensor` 聲明之後添加以下程式碼，以創建管理 LED 的類的實例：

    ```python
    led = GroveLed(5)
    ```

    `led = GroveLed(5)` 行創建了一個 `GroveLed` 類的實例，連接到 Pin **5**——CounterFit Grove 中 LED 所連接的 Pin。

1. 在 `while` 迴圈內部並在 `time.sleep` 之前添加一個檢查，用於檢查光線水平並打開或關閉 LED：

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    此程式碼檢查 `light` 值。如果該值小於 300，則調用 `GroveLed` 類的 `on` 方法，向 LED 傳送數位值 1，將其打開。如果光線值大於或等於 300，則調用 `off` 方法，傳送數位值 0，將其關閉。

    > 💁 此程式碼應與 `print('Light level:', light)` 行保持相同的縮排級別，以確保它位於 while 迴圈內！

1. 從 VS Code 的終端執行以下命令以運行你的 Python 應用：

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

1. 更改 *Value* 或 *Random* 設定，使光線水平在 300 以上和以下變化。LED 將會開啟和關閉。

![CounterFit 應用中 LED 隨光線水平變化而開啟和關閉](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 你可以在 [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device) 資料夾中找到此程式碼。

😀 你的夜燈程式成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於關鍵資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。