<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-26T22:52:07+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "mo"
}
-->
# 測量土壤濕度 - 虛擬物聯網硬體

在本課程中，您將為虛擬物聯網設備添加一個電容式土壤濕度傳感器，並從中讀取數據。

## 虛擬硬體

虛擬物聯網設備將使用模擬的 Grove 電容式土壤濕度傳感器。這樣的設置與使用 Raspberry Pi 和實體 Grove 電容式土壤濕度傳感器的操作方式相同。

在實體物聯網設備中，土壤濕度傳感器是一種電容式傳感器，通過檢測土壤的電容來測量濕度。當土壤濕度改變時，電容也會隨之改變。隨著土壤濕度的增加，電壓會降低。

這是一個模擬傳感器，因此使用模擬的 10 位 ADC（模數轉換器）來報告 1 到 1,023 的數值。

### 將土壤濕度傳感器添加到 CounterFit

要使用虛擬土壤濕度傳感器，您需要將其添加到 CounterFit 應用中。

#### 任務 - 將土壤濕度傳感器添加到 CounterFit

將土壤濕度傳感器添加到 CounterFit 應用中。

1. 在您的電腦上創建一個名為 `soil-moisture-sensor` 的資料夾，並在其中創建一個名為 `app.py` 的單一文件，設置一個 Python 虛擬環境，並添加 CounterFit 的 pip 套件。

    > ⚠️ 如果需要，您可以參考[第 1 課中有關創建和設置 CounterFit Python 專案的說明](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md)。

1. 確保 CounterFit 網頁應用正在運行。

1. 創建一個土壤濕度傳感器：

    1. 在 *Sensors* 面板的 *Create sensor* 框中，展開 *Sensor type* 下拉框並選擇 *Soil Moisture*。

    1. 將 *Units* 保持為 *NoUnits*。

    1. 確保 *Pin* 設置為 *0*。

    1. 點擊 **Add** 按鈕，在 Pin 0 上創建 *Soil Moisture* 傳感器。

    ![土壤濕度傳感器設置](../../../../../translated_images/mo/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    土壤濕度傳感器將被創建並顯示在傳感器列表中。

    ![已創建的土壤濕度傳感器](../../../../../translated_images/mo/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## 編寫土壤濕度傳感器應用程式

現在可以使用 CounterFit 傳感器來編寫土壤濕度傳感器應用程式。

### 任務 - 編寫土壤濕度傳感器應用程式

編寫土壤濕度傳感器應用程式。

1. 確保 `soil-moisture-sensor` 應用已在 VS Code 中打開。

1. 打開 `app.py` 文件。

1. 在 `app.py` 文件的頂部添加以下代碼，以連接應用到 CounterFit：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. 在 `app.py` 文件中添加以下代碼以導入一些必要的庫：

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    `import time` 語句導入了 `time` 模組，稍後將在此任務中使用。

    `from counterfit_shims_grove.adc import ADC` 語句導入了 `ADC` 類，用於與可連接到 CounterFit 傳感器的虛擬模擬到數字轉換器進行交互。

1. 在此代碼下方添加以下代碼以創建 `ADC` 類的實例：

    ```python
    adc = ADC()
    ```

1. 添加一個無限循環，從 Pin 0 的 ADC 讀取數據，並將結果寫入控制台。該循環可以在每次讀取之間休眠 10 秒。

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. 在 CounterFit 應用中更改土壤濕度傳感器的值，該值將被應用讀取。您可以通過以下兩種方式進行更改：

    * 在土壤濕度傳感器的 *Value* 框中輸入一個數字，然後點擊 **Set** 按鈕。您輸入的數字將是傳感器返回的值。

    * 勾選 *Random* 選框，並輸入 *Min* 和 *Max* 值，然後點擊 **Set** 按鈕。每次傳感器讀取值時，將讀取 *Min* 和 *Max* 範圍內的隨機數字。

1. 運行 Python 應用。您將在控制台中看到土壤濕度測量值。更改 *Value* 或 *Random* 設置以查看值的變化。

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 您可以在 [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device) 資料夾中找到此代碼。

😀 您的土壤濕度傳感器程式運行成功！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。