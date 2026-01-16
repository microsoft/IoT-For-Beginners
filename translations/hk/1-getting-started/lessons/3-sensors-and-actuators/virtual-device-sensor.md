<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-26T15:07:36+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "hk"
}
-->
# 建立夜燈 - 虛擬物聯網硬件

在本課程的這部分，你將為虛擬物聯網設備添加一個光線感應器。

## 虛擬硬件

夜燈需要一個感應器，通過 CounterFit 應用程式創建。

這個感應器是一個 **光線感應器**。在實體物聯網設備中，它會是一個 [光電二極管](https://wikipedia.org/wiki/Photodiode)，將光線轉換為電信號。光線感應器是一種模擬感應器，會傳送一個整數值，表示相對的光線量，但不會映射到任何標準測量單位，例如 [勒克斯](https://wikipedia.org/wiki/Lux)。

### 在 CounterFit 中添加感應器

要使用虛擬光線感應器，你需要將其添加到 CounterFit 應用程式中。

#### 任務 - 在 CounterFit 中添加感應器

將光線感應器添加到 CounterFit 應用程式中。

1. 確保 CounterFit 網頁應用程式正在運行，這是上一部分任務的要求。如果尚未運行，請啟動它。

1. 創建一個光線感應器：

    1. 在 *Sensors* 面板的 *Create sensor* 框中，點擊 *Sensor type* 下拉框並選擇 *Light*。

    1. 將 *Units* 保持為 *NoUnits*。

    1. 確保 *Pin* 設置為 *0*。

    1. 點擊 **Add** 按鈕，在 Pin 0 上創建光線感應器。

    ![光線感應器設置](../../../../../translated_images/hk/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    光線感應器將被創建並顯示在感應器列表中。

    ![已創建的光線感應器](../../../../../translated_images/hk/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## 編程光線感應器

現在可以編程設備以使用內建的光線感應器。

### 任務 - 編程光線感應器

編程設備。

1. 在 VS Code 中打開你在上一部分任務中創建的夜燈項目。如果需要，終止並重新創建終端以確保它正在使用虛擬環境。

1. 打開 `app.py` 文件。

1. 在 `app.py` 文件的頂部添加以下代碼，與其他 `import` 語句一起，用於導入所需的庫：

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time` 語句導入了 Python 的 `time` 模組，稍後在本任務中會使用。

    `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` 語句從 CounterFit Grove shim Python 庫中導入了 `GroveLightSensor`。這個庫包含與 CounterFit 應用程式中創建的光線感應器交互的代碼。

1. 在文件底部添加以下代碼，用於創建管理光線感應器的類的實例：

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    `light_sensor = GroveLightSensor(0)` 這一行創建了一個 `GroveLightSensor` 類的實例，連接到 Pin **0**——CounterFit Grove 的光線感應器所連接的 Pin。

1. 在上述代碼之後添加一個無限循環，用於輪詢光線感應器的值並將其打印到控制台：

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    這將使用 `GroveLightSensor` 類的 `light` 屬性讀取當前的光線水平。該屬性從 Pin 讀取模擬值，然後將該值打印到控制台。

1. 在 `while` 循環的末尾添加一秒的短暫休眠，因為光線水平不需要連續檢查。休眠可以減少設備的功耗。

    ```python
    time.sleep(1)
    ```

1. 從 VS Code 的終端運行以下命令以運行你的 Python 應用程式：

    ```sh
    python3 app.py
    ```

    光線值將輸出到控制台。初始值將為 0。

1. 從 CounterFit 應用程式更改光線感應器的值，該值將被應用程式讀取。你可以通過以下兩種方式進行更改：

    * 在光線感應器的 *Value* 框中輸入一個數字，然後點擊 **Set** 按鈕。你輸入的數字將是感應器返回的值。

    * 勾選 *Random* 選項框，並輸入 *Min* 和 *Max* 值，然後點擊 **Set** 按鈕。每次感應器讀取值時，它將讀取一個介於 *Min* 和 *Max* 之間的隨機數。

    你設置的值將輸出到控制台。更改 *Value* 或 *Random* 設置以使值發生變化。

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 你可以在 [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device) 文件夾中找到這段代碼。

😀 你的夜燈程式成功了！

---

**免責聲明**：  
此文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解讀概不負責。