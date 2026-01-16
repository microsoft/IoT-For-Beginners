<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "70e5a428b607cd5a9a4f422c2a4df03d",
  "translation_date": "2025-08-26T22:20:24+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/virtual-device-temp.md",
  "language_code": "mo"
}
-->
# 測量溫度 - 虛擬物聯網硬體

在本課程中，您將為虛擬物聯網設備添加一個溫度感測器。

## 虛擬硬體

虛擬物聯網設備將使用模擬的 Grove 數位濕度與溫度感測器。這樣的設置與使用搭載實體 Grove DHT11 感測器的 Raspberry Pi 相同。

該感測器結合了一個**溫度感測器**和一個**濕度感測器**，但在本實驗中，您只需關注溫度感測器的部分。在實體物聯網設備中，溫度感測器通常是一個[熱敏電阻](https://wikipedia.org/wiki/Thermistor)，通過感應電阻隨溫度變化的改變來測量溫度。溫度感測器通常是數位感測器，內部會將測量到的電阻轉換為攝氏度（或開氏度、華氏度）的溫度。

### 將感測器添加到 CounterFit

要使用虛擬濕度和溫度感測器，您需要將這兩個感測器添加到 CounterFit 應用中。

#### 任務 - 將感測器添加到 CounterFit

將濕度和溫度感測器添加到 CounterFit 應用中。

1. 在您的電腦上建立一個名為 `temperature-sensor` 的資料夾，並在其中創建一個名為 `app.py` 的單一檔案，設置 Python 虛擬環境，並添加 CounterFit 的 pip 套件。

    > ⚠️ 如果需要，您可以參考[第 1 課中有關創建和設置 CounterFit Python 專案的指導](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md)。

1. 安裝一個額外的 Pip 套件，用於安裝 DHT11 感測器的 CounterFit shim。確保您是在啟用虛擬環境的終端中進行安裝。

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. 確保 CounterFit 網頁應用正在運行。

1. 創建一個濕度感測器：

    1. 在 *Sensors* 面板的 *Create sensor* 框中，展開 *Sensor type* 下拉框並選擇 *Humidity*。

    1. 將 *Units* 保持為 *Percentage*。

    1. 確保 *Pin* 設置為 *5*。

    1. 點擊 **Add** 按鈕，在 Pin 5 上創建濕度感測器。

    ![濕度感測器設置](../../../../../translated_images/mo/counterfit-create-humidity-sensor.2750e27b6f30e09cf4e22101defd5252710717620816ab41ba688f91f757c49a.png)

    濕度感測器將被創建並顯示在感測器列表中。

    ![已創建的濕度感測器](../../../../../translated_images/mo/counterfit-humidity-sensor.7b12f7f339e430cb26c8211d2dba4ef75261b353a01da0932698b5bebd693f27.png)

1. 創建一個溫度感測器：

    1. 在 *Sensors* 面板的 *Create sensor* 框中，展開 *Sensor type* 下拉框並選擇 *Temperature*。

    1. 將 *Units* 保持為 *Celsius*。

    1. 確保 *Pin* 設置為 *6*。

    1. 點擊 **Add** 按鈕，在 Pin 6 上創建溫度感測器。

    ![溫度感測器設置](../../../../../translated_images/mo/counterfit-create-temperature-sensor.199350ed34f7343d79dccbe95eaf6c11d2121f03d1c35ab9613b330c23f39b29.png)

    溫度感測器將被創建並顯示在感測器列表中。

    ![已創建的溫度感測器](../../../../../translated_images/mo/counterfit-temperature-sensor.f0560236c96a9016bafce7f6f792476fe3367bc6941a1f7d5811d144d4bcbfff.png)

## 編寫溫度感測器應用程式

現在可以使用 CounterFit 感測器來編寫溫度感測器應用程式。

### 任務 - 編寫溫度感測器應用程式

編寫溫度感測器應用程式。

1. 確保 `temperature-sensor` 應用已在 VS Code 中打開。

1. 打開 `app.py` 檔案。

1. 在 `app.py` 的頂部添加以下程式碼，將應用連接到 CounterFit：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. 在 `app.py` 檔案中添加以下程式碼以匯入所需的函式庫：

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    `from seeed_dht import DHT` 語句匯入了 `DHT` 感測器類，用於通過 `counterfit_shims_seeed_python_dht` 模組的 shim 與虛擬 Grove 溫度感測器進行互動。

1. 在上述程式碼之後添加以下程式碼，創建一個管理虛擬濕度和溫度感測器的類別實例：

    ```python
    sensor = DHT("11", 5)
    ```

    這聲明了一個 `DHT` 類的實例，用於管理虛擬的**數位濕度與溫度感測器**。第一個參數告訴程式使用的是虛擬 *DHT11* 感測器。第二個參數告訴程式感測器連接到埠 `5`。

    > 💁 CounterFit 通過連接兩個感測器來模擬這個結合的濕度與溫度感測器，一個濕度感測器連接到創建 `DHT` 類時指定的埠，另一個溫度感測器運行在下一個埠。如果濕度感測器在埠 5 上，shim 預期溫度感測器在埠 6 上。

1. 在上述程式碼之後添加一個無限迴圈，用於輪詢溫度感測器的值並將其打印到控制台：

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    調用 `sensor.read()` 會返回一個包含濕度和溫度的元組。您只需要溫度值，因此可以忽略濕度值。然後將溫度值打印到控制台。

1. 在 `loop` 的末尾添加一個 10 秒的小延遲，因為不需要連續檢查溫度水平。延遲可以減少設備的功耗。

    ```python
    time.sleep(10)
    ```

1. 在啟用虛擬環境的 VS Code 終端中，運行以下命令來執行您的 Python 應用程式：

    ```sh
    python app.py
    ```

1. 在 CounterFit 應用中更改溫度感測器的值，該值將被應用程式讀取。您可以通過以下兩種方式進行更改：

    * 在溫度感測器的 *Value* 框中輸入一個數字，然後點擊 **Set** 按鈕。您輸入的數字將成為感測器返回的值。

    * 勾選 *Random* 選框，並輸入 *Min* 和 *Max* 值，然後點擊 **Set** 按鈕。每次感測器讀取值時，將讀取一個介於 *Min* 和 *Max* 之間的隨機數。

    您應該能在控制台中看到您設置的值。更改 *Value* 或 *Random* 設置以查看值的變化。

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 您可以在 [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device) 資料夾中找到此程式碼。

😀 恭喜！您的溫度感測器程式成功運行！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。