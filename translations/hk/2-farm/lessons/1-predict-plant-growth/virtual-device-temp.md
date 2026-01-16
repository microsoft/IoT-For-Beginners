<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "70e5a428b607cd5a9a4f422c2a4df03d",
  "translation_date": "2025-08-26T14:30:39+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/virtual-device-temp.md",
  "language_code": "hk"
}
-->
# 測量溫度 - 虛擬物聯網硬件

在本課程中，你將為虛擬物聯網設備添加一個溫度感應器。

## 虛擬硬件

虛擬物聯網設備將使用模擬的 Grove 數字濕度和溫度感應器。這使得本實驗與使用 Raspberry Pi 和實體 Grove DHT11 感應器的操作保持一致。

該感應器結合了**溫度感應器**和**濕度感應器**，但在本實驗中，你只需關注溫度感應器部分。在實體物聯網設備中，溫度感應器通常是一個[熱敏電阻](https://wikipedia.org/wiki/Thermistor)，通過感應溫度變化時的電阻變化來測量溫度。溫度感應器通常是數字感應器，內部會將測量到的電阻轉換為攝氏（或開氏、華氏）溫度。

### 添加感應器到 CounterFit

要使用虛擬濕度和溫度感應器，你需要將這兩個感應器添加到 CounterFit 應用中。

#### 任務 - 添加感應器到 CounterFit

將濕度和溫度感應器添加到 CounterFit 應用中。

1. 在你的電腦上創建一個名為 `temperature-sensor` 的新 Python 應用，包含一個名為 `app.py` 的文件和一個 Python 虛擬環境，並添加 CounterFit 的 pip 套件。

    > ⚠️ 如果需要，你可以參考[第 1 課中創建和設置 CounterFit Python 項目的指導](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md)。

1. 安裝額外的 Pip 套件以安裝 DHT11 感應器的 CounterFit shim。確保你是在啟動虛擬環境的終端中進行安裝。

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. 確保 CounterFit 網頁應用正在運行。

1. 創建濕度感應器：

    1. 在 *Sensors* 面板的 *Create sensor* 框中，展開 *Sensor type* 下拉框並選擇 *Humidity*。

    1. 保持 *Units* 設置為 *Percentage*。

    1. 確保 *Pin* 設置為 *5*。

    1. 點擊 **Add** 按鈕，在 Pin 5 上創建濕度感應器。

    ![濕度感應器設置](../../../../../translated_images/hk/counterfit-create-humidity-sensor.2750e27b6f30e09cf4e22101defd5252710717620816ab41ba688f91f757c49a.png)

    濕度感應器將被創建並顯示在感應器列表中。

    ![濕度感應器已創建](../../../../../translated_images/hk/counterfit-humidity-sensor.7b12f7f339e430cb26c8211d2dba4ef75261b353a01da0932698b5bebd693f27.png)

1. 創建溫度感應器：

    1. 在 *Sensors* 面板的 *Create sensor* 框中，展開 *Sensor type* 下拉框並選擇 *Temperature*。

    1. 保持 *Units* 設置為 *Celsius*。

    1. 確保 *Pin* 設置為 *6*。

    1. 點擊 **Add** 按鈕，在 Pin 6 上創建溫度感應器。

    ![溫度感應器設置](../../../../../translated_images/hk/counterfit-create-temperature-sensor.199350ed34f7343d79dccbe95eaf6c11d2121f03d1c35ab9613b330c23f39b29.png)

    溫度感應器將被創建並顯示在感應器列表中。

    ![溫度感應器已創建](../../../../../translated_images/hk/counterfit-temperature-sensor.f0560236c96a9016bafce7f6f792476fe3367bc6941a1f7d5811d144d4bcbfff.png)

## 編寫溫度感應器應用

現在可以使用 CounterFit 感應器編寫溫度感應器應用。

### 任務 - 編寫溫度感應器應用

編寫溫度感應器應用。

1. 確保 `temperature-sensor` 應用已在 VS Code 中打開。

1. 打開 `app.py` 文件。

1. 在 `app.py` 文件的頂部添加以下代碼以連接應用到 CounterFit：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. 在 `app.py` 文件中添加以下代碼以導入所需的庫：

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    `from seeed_dht import DHT` 語句導入了 `DHT` 感應器類，用於通過 `counterfit_shims_seeed_python_dht` 模塊的 shim 與虛擬 Grove 溫度感應器交互。

1. 在上述代碼之後添加以下代碼以創建管理虛擬濕度和溫度感應器的類實例：

    ```python
    sensor = DHT("11", 5)
    ```

    這聲明了一個 `DHT` 類的實例，用於管理虛擬**數字濕度和溫度感應器**。第一個參數告訴代碼使用的是虛擬 *DHT11* 感應器。第二個參數告訴代碼感應器連接到端口 `5`。

    > 💁 CounterFit 通過連接到兩個感應器來模擬這個濕度和溫度感應器，濕度感應器連接到創建 `DHT` 類時指定的引腳，而溫度感應器則運行在下一個引腳上。如果濕度感應器在引腳 5 上，shim 預期溫度感應器在引腳 6 上。

1. 在上述代碼之後添加一個無限循環以輪詢溫度感應器的值並將其打印到控制台：

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    調用 `sensor.read()` 返回一個包含濕度和溫度的元組。你只需要溫度值，因此可以忽略濕度。然後將溫度值打印到控制台。

1. 在循環的末尾添加一個十秒的小延遲，因為不需要持續檢查溫度水平。延遲可以減少設備的功耗。

    ```python
    time.sleep(10)
    ```

1. 在啟動虛擬環境的 VS Code 終端中運行以下命令以運行你的 Python 應用：

    ```sh
    python app.py
    ```

1. 在 CounterFit 應用中更改溫度感應器的值，該值將被應用讀取。你可以通過以下兩種方式進行更改：

    * 在溫度感應器的 *Value* 框中輸入一個數字，然後點擊 **Set** 按鈕。你輸入的數字將是感應器返回的值。

    * 勾選 *Random* 選項框，並輸入 *Min* 和 *Max* 值，然後點擊 **Set** 按鈕。每次感應器讀取值時，它將讀取 *Min* 和 *Max* 之間的隨機數字。

    你應該能在控制台中看到你設置的值。更改 *Value* 或 *Random* 設置以查看值的變化。

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 你可以在 [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device) 文件夾中找到此代碼。

😀 你的溫度感應器程序成功了！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。