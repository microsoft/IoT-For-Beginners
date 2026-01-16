<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-24T23:13:31+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "tw"
}
-->
# 建立夜燈 - Raspberry Pi

在本課程的這部分，你將為 Raspberry Pi 添加一個光線感測器。

## 硬體

本課程使用的感測器是一個**光線感測器**，它利用[光電二極體](https://wikipedia.org/wiki/Photodiode)將光轉換為電信號。這是一個類比感測器，會傳送一個介於 0 到 1,000 的整數值，表示相對的光量，但這個值並不對應於任何標準的測量單位，例如 [lux](https://wikipedia.org/wiki/Lux)。

光線感測器是一個外部的 Grove 感測器，需要連接到 Raspberry Pi 上的 Grove Base hat。

### 連接光線感測器

用於檢測光線強度的 Grove 光線感測器需要連接到 Raspberry Pi。

#### 任務 - 連接光線感測器

連接光線感測器

![Grove 光線感測器](../../../../../translated_images/tw/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. 將 Grove 線纜的一端插入光線感測器模組上的插槽。它只能以一種方向插入。

1. 在 Raspberry Pi 關機的情況下，將 Grove 線纜的另一端連接到 Grove Base hat 上標記為 **A0** 的類比插槽。這個插槽位於 GPIO 引腳旁邊的一排插槽中，從右數第二個。

![Grove 光線感測器連接到 A0 插槽](../../../../../translated_images/tw/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## 編寫光線感測器程式

現在可以使用 Grove 光線感測器來編寫程式。

### 任務 - 編寫光線感測器程式

編寫裝置程式。

1. 啟動 Raspberry Pi，並等待其完成開機。

1. 在 VS Code 中打開你在本作業前一部分中建立的夜燈專案，可以直接在 Pi 上運行，或者使用 Remote SSH 擴展連接。

1. 打開 `app.py` 文件，並刪除其中的所有程式碼。

1. 在 `app.py` 文件中添加以下程式碼以匯入一些必要的庫：

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time` 語句匯入了 `time` 模組，稍後在本作業中會用到。

    `from grove.grove_light_sensor_v1_2 import GroveLightSensor` 語句從 Grove Python 庫中匯入了 `GroveLightSensor`。這個庫包含與 Grove 光線感測器互動的程式碼，並在 Pi 設置過程中已全域安裝。

1. 在上述程式碼之後添加以下程式碼，創建一個管理光線感測器的類別實例：

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    `light_sensor = GroveLightSensor(0)` 這一行創建了一個 `GroveLightSensor` 類別的實例，並連接到引腳 **A0**——光線感測器所連接的 Grove 類比引腳。

1. 在上述程式碼之後添加一個無限迴圈，用於輪詢光線感測器的值並將其輸出到控制台：

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    這段程式碼會使用 `GroveLightSensor` 類別的 `light` 屬性讀取當前光線強度，範圍為 0-1,023。該屬性從引腳讀取類比值，然後將該值輸出到控制台。

1. 在迴圈的最後添加一個一秒的延遲，因為光線強度不需要被連續檢查。延遲可以減少裝置的功耗。

    ```python
    time.sleep(1)
    ```

1. 在 VS Code 的終端中，運行以下命令來執行你的 Python 應用程式：

    ```sh
    python3 app.py
    ```

    光線值將輸出到控制台。遮住或移開光線感測器，值會隨之改變：

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 你可以在 [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi) 資料夾中找到這段程式碼。

😀 為你的夜燈程式添加感測器成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤讀概不負責。