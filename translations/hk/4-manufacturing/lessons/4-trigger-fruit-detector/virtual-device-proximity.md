<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-26T14:24:32+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "hk"
}
-->
# 檢測接近 - 虛擬物聯網硬件

在本課程的這部分，你將為虛擬物聯網設備添加一個接近傳感器，並從中讀取距離。

## 硬件

虛擬物聯網設備將使用模擬的距離傳感器。

在實體物聯網設備中，你會使用帶有激光測距模塊的傳感器來檢測距離。

### 在 CounterFit 中添加距離傳感器

要使用虛擬距離傳感器，你需要在 CounterFit 應用中添加一個。

#### 任務 - 在 CounterFit 中添加距離傳感器

在 CounterFit 應用中添加距離傳感器。

1. 在 VS Code 中打開 `fruit-quality-detector` 代碼，並確保虛擬環境已啟動。

1. 安裝額外的 Pip 套件，以安裝一個 CounterFit shim，它可以通過模擬 [rpi-vl53l0x Pip 套件](https://pypi.org/project/rpi-vl53l0x/) 與距離傳感器通信。這是一個與 [VL53L0X 飛行時間距離傳感器](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/) 交互的 Python 套件。確保你是在啟動虛擬環境的終端中進行安裝。

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. 確保 CounterFit 網頁應用正在運行。

1. 創建一個距離傳感器：

    1. 在 *Sensors* 面板的 *Create sensor* 框中，打開 *Sensor type* 下拉框並選擇 *Distance*。

    1. 將 *Units* 保持為 `Millimeter`。

    1. 此傳感器是一個 I²C 傳感器，因此將地址設置為 `0x29`。如果你使用的是實體 VL53L0X 傳感器，它的地址會被硬編碼為此。

    1. 點擊 **Add** 按鈕以創建距離傳感器。

    ![距離傳感器設置](../../../../../translated_images/hk/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.png)

    距離傳感器將被創建並顯示在傳感器列表中。

    ![已創建的距離傳感器](../../../../../translated_images/hk/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.png)

## 編程距離傳感器

虛擬物聯網設備現在可以編程以使用模擬的距離傳感器。

### 任務 - 編程飛行時間傳感器

1. 在 `fruit-quality-detector` 項目中創建一個名為 `distance-sensor.py` 的新文件。

    > 💁 模擬多個物聯網設備的一個簡單方法是將每個設備的代碼放在不同的 Python 文件中，然後同時運行它們。

1. 使用以下代碼啟動與 CounterFit 的連接：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. 在此代碼下方添加以下代碼：

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    這會導入 VL53L0X 飛行時間傳感器的傳感器庫 shim。

1. 在此代碼下方添加以下代碼以訪問傳感器：

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    此代碼聲明了一個距離傳感器，然後啟動該傳感器。

1. 最後，添加一個無限循環以讀取距離：

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    此代碼等待傳感器準備好讀取值，然後將其打印到控制台。

1. 運行此代碼。

    > 💁 別忘了這個文件名是 `distance-sensor.py`！確保通過 Python 運行它，而不是 `app.py`。

1. 你會在控制台中看到距離測量值。更改 CounterFit 中的值以查看此值的變化，或者使用隨機值。

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 你可以在 [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device) 文件夾中找到此代碼。

😀 你的接近傳感器程序成功了！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。