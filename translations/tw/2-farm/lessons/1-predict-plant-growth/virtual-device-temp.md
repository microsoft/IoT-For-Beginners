<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "70e5a428b607cd5a9a4f422c2a4df03d",
  "translation_date": "2025-08-24T22:06:40+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/virtual-device-temp.md",
  "language_code": "tw"
}
-->
# 測量溫度 - 虛擬物聯網硬體

在本課程中，您將為虛擬物聯網設備添加一個溫度感測器。

## 虛擬硬體

虛擬物聯網設備將使用模擬的 Grove 數位濕度和溫度感測器。這使得本實驗與使用 Raspberry Pi 和實體 Grove DHT11 感測器的操作保持一致。

該感測器結合了**溫度感測器**和**濕度感測器**，但在本實驗中，您只需關注溫度感測器部分。在實體物聯網設備中，溫度感測器通常是一個[熱敏電阻](https://wikipedia.org/wiki/Thermistor)，它通過感測溫度變化時的電阻變化來測量溫度。溫度感測器通常是數位感測器，內部會將測得的電阻轉換為攝氏（或開氏、華氏）溫度。

### 將感測器添加到 CounterFit

要使用虛擬濕度和溫度感測器，您需要將這兩個感測器添加到 CounterFit 應用程式中。

#### 任務 - 將感測器添加到 CounterFit

將濕度和溫度感測器添加到 CounterFit 應用程式中。

1. 在您的電腦上建立一個名為 `temperature-sensor` 的資料夾，並在其中建立一個名為 `app.py` 的 Python 應用程式，設置 Python 虛擬環境，並添加 CounterFit 的 pip 套件。

    > ⚠️ 如果需要，您可以參考[第 1 課中建立和設置 CounterFit Python 專案的指導](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md)。

1. 安裝額外的 Pip 套件以安裝 DHT11 感測器的 CounterFit shim。確保您在啟動虛擬環境的終端中執行此操作。

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. 確保 CounterFit 網頁應用程式正在運行。

1. 建立濕度感測器：

    1. 在 *Sensors* 面板的 *Create sensor* 框中，展開 *Sensor type* 下拉框並選擇 *Humidity*。

    1. 保持 *Units* 設置為 *Percentage*。

    1. 確保 *Pin* 設置為 *5*。

    1. 選擇 **Add** 按鈕以在 Pin 5 上建立濕度感測器。

    ![濕度感測器設置](../../../../../translated_images/tw/counterfit-create-humidity-sensor.2750e27b6f30e09cf4e22101defd5252710717620816ab41ba688f91f757c49a.png)

    濕度感測器將被建立並顯示在感測器列表中。

    ![濕度感測器已建立](../../../../../translated_images/tw/counterfit-humidity-sensor.7b12f7f339e430cb26c8211d2dba4ef75261b353a01da0932698b5bebd693f27.png)

1. 建立溫度感測器：

    1. 在 *Sensors* 面板的 *Create sensor* 框中，展開 *Sensor type* 下拉框並選擇 *Temperature*。

    1. 保持 *Units* 設置為 *Celsius*。

    1. 確保 *Pin* 設置為 *6*。

    1. 選擇 **Add** 按鈕以在 Pin 6 上建立溫度感測器。

    ![溫度感測器設置](../../../../../translated_images/tw/counterfit-create-temperature-sensor.199350ed34f7343d79dccbe95eaf6c11d2121f03d1c35ab9613b330c23f39b29.png)

    溫度感測器將被建立並顯示在感測器列表中。

    ![溫度感測器已建立](../../../../../translated_images/tw/counterfit-temperature-sensor.f0560236c96a9016bafce7f6f792476fe3367bc6941a1f7d5811d144d4bcbfff.png)

## 編寫溫度感測器應用程式

現在可以使用 CounterFit 感測器編寫溫度感測器應用程式。

### 任務 - 編寫溫度感測器應用程式

編寫溫度感測器應用程式。

1. 確保 `temperature-sensor` 應用程式已在 VS Code 中開啟。

1. 打開 `app.py` 文件。

1. 在 `app.py` 文件的頂部添加以下程式碼以連接應用程式到 CounterFit：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. 在 `app.py` 文件中添加以下程式碼以匯入所需的庫：

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    `from seeed_dht import DHT` 語句匯入了 `DHT` 感測器類，用於通過 `counterfit_shims_seeed_python_dht` 模組與虛擬 Grove 溫度感測器進行交互。

1. 在上述程式碼之後添加以下程式碼，以建立管理虛擬濕度和溫度感測器的類實例：

    ```python
    sensor = DHT("11", 5)
    ```

    這聲明了一個 `DHT` 類的實例，用於管理虛擬**數位濕度和溫度感測器**。第一個參數告訴程式碼使用的是虛擬 *DHT11* 感測器。第二個參數告訴程式碼感測器連接到端口 `5`。

    > 💁 CounterFit 通過連接到兩個感測器來模擬這個濕度和溫度感測器，濕度感測器連接到建立 `DHT` 類時指定的引腳，而溫度感測器則運行在下一個引腳上。如果濕度感測器在引腳 5 上，shim 預期溫度感測器在引腳 6 上。

1. 在上述程式碼之後添加一個無限迴圈，以輪詢溫度感測器的值並將其打印到控制台：

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    `sensor.read()` 的調用返回一個包含濕度和溫度的元組。您只需要溫度值，因此可以忽略濕度。然後將溫度值打印到控制台。

1. 在迴圈的末尾添加一個十秒的小延遲，因為不需要持續檢查溫度水平。延遲可以減少設備的功耗。

    ```python
    time.sleep(10)
    ```

1. 在啟動虛擬環境的 VS Code 終端中，執行以下命令以運行您的 Python 應用程式：

    ```sh
    python app.py
    ```

1. 在 CounterFit 應用程式中更改溫度感測器的值，該值將被應用程式讀取。您可以通過以下兩種方式進行更改：

    * 在溫度感測器的 *Value* 框中輸入一個數字，然後選擇 **Set** 按鈕。您輸入的數字將是感測器返回的值。

    * 勾選 *Random* 選框，並輸入 *Min* 和 *Max* 值，然後選擇 **Set** 按鈕。每次感測器讀取值時，它將讀取介於 *Min* 和 *Max* 之間的隨機數字。

    您應該能在控制台中看到您設置的值。更改 *Value* 或 *Random* 設置以查看值的變化。

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 您可以在 [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device) 資料夾中找到此程式碼。

😀 您的溫度感測器程式成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤讀概不負責。