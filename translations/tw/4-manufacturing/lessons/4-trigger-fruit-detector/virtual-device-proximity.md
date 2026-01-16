<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-24T21:55:51+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "tw"
}
-->
# 偵測接近 - 虛擬物聯網硬體

在本課程中，您將為虛擬物聯網設備添加一個接近感測器，並從中讀取距離。

## 硬體

虛擬物聯網設備將使用模擬的距離感測器。

在實體物聯網設備中，您會使用帶有雷射測距模組的感測器來偵測距離。

### 將距離感測器添加到 CounterFit

要使用虛擬距離感測器，您需要在 CounterFit 應用程式中添加一個。

#### 任務 - 將距離感測器添加到 CounterFit

將距離感測器添加到 CounterFit 應用程式。

1. 在 VS Code 中打開 `fruit-quality-detector` 程式碼，並確保虛擬環境已啟動。

1. 安裝額外的 Pip 套件，以安裝一個 CounterFit shim，該 shim 可以通過模擬 [rpi-vl53l0x Pip 套件](https://pypi.org/project/rpi-vl53l0x/) 與距離感測器通信。這是一個與 [VL53L0X 飛行時間距離感測器](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/) 互動的 Python 套件。確保您是在啟動虛擬環境的終端中進行安裝。

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. 確保 CounterFit 網頁應用程式正在運行。

1. 創建一個距離感測器：

    1. 在 *Sensors* 面板的 *Create sensor* 框中，展開 *Sensor type* 下拉框並選擇 *Distance*。

    1. 將 *Units* 保持為 `Millimeter`。

    1. 此感測器是一個 I2C 感測器，因此將地址設置為 `0x29`。如果您使用的是實體 VL53L0X 感測器，它的地址會被硬編碼為此。

    1. 選擇 **Add** 按鈕以創建距離感測器。

    ![距離感測器設置](../../../../../translated_images/tw/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.png)

    距離感測器將被創建並顯示在感測器列表中。

    ![距離感測器已創建](../../../../../translated_images/tw/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.png)

## 程式化距離感測器

現在可以程式化虛擬物聯網設備以使用模擬的距離感測器。

### 任務 - 程式化飛行時間感測器

1. 在 `fruit-quality-detector` 專案中創建一個名為 `distance-sensor.py` 的新檔案。

    > 💁 模擬多個物聯網設備的一個簡單方法是將每個設備放在不同的 Python 檔案中，然後同時運行它們。

1. 使用以下程式碼啟動與 CounterFit 的連接：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. 在此程式碼下方添加以下程式碼：

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    這會導入 VL53L0X 飛行時間感測器的感測器庫 shim。

1. 在此程式碼下方添加以下程式碼以訪問感測器：

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    此程式碼宣告了一個距離感測器，然後啟動該感測器。

1. 最後，添加一個無限迴圈以讀取距離：

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    此程式碼等待感測器準備好讀取值，然後將其打印到控制台。

1. 運行此程式碼。

    > 💁 別忘了此檔案名為 `distance-sensor.py`！請確保通過 Python 運行此檔案，而不是 `app.py`。

1. 您將在控制台中看到距離測量值。更改 CounterFit 中的值以查看此值的變化，或者使用隨機值。

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 您可以在 [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device) 資料夾中找到此程式碼。

😀 您的接近感測器程式成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。