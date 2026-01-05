<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-26T14:46:23+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "hk"
}
-->
# 測量土壤濕度 - Raspberry Pi

在本課程中，你將為 Raspberry Pi 添加一個電容式土壤濕度傳感器，並從中讀取數值。

## 硬件

Raspberry Pi 需要一個電容式土壤濕度傳感器。

你將使用的傳感器是 [電容式土壤濕度傳感器](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)，它通過檢測土壤的電容來測量濕度，這是一種隨著土壤濕度變化而改變的特性。當土壤濕度增加時，電壓會下降。

這是一個模擬傳感器，因此使用模擬引腳，並通過 Raspberry Pi 上的 Grove Base Hat 的 10 位 ADC 將電壓轉換為 1-1,023 的數字信號。然後通過 Pi 的 GPIO 引腳以 I²C 的方式傳輸。

### 連接土壤濕度傳感器

Grove 土壤濕度傳感器可以連接到 Raspberry Pi。

#### 任務 - 連接土壤濕度傳感器

連接土壤濕度傳感器。

![Grove 土壤濕度傳感器](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.hk.png)

1. 將 Grove 電纜的一端插入土壤濕度傳感器上的插座。它只能以一種方式插入。

1. 在 Raspberry Pi 關機的情況下，將 Grove 電纜的另一端連接到 Pi 上 Grove Base Hat 的模擬插座 **A0**。該插座位於 GPIO 引腳旁邊的一排插座中，從右數第二個。

![Grove 土壤濕度傳感器連接到 A0 插座](../../../../../translated_images/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.hk.png)

1. 將土壤濕度傳感器插入土壤中。傳感器上有一條“最高位置線”——一條白線。將傳感器插入土壤，直到但不超過這條線。

![Grove 土壤濕度傳感器插入土壤中](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.hk.png)

## 編程土壤濕度傳感器

現在可以編程 Raspberry Pi 以使用連接的土壤濕度傳感器。

### 任務 - 編程土壤濕度傳感器

編程設備。

1. 啟動 Raspberry Pi，並等待其完成啟動。

1. 啟動 VS Code，可以直接在 Pi 上啟動，也可以通過 Remote SSH 擴展連接。

    > ⚠️ 如果需要，可以參考 [夜燈課程第 1 課中設置和啟動 VS Code 的指導](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md)。

1. 在終端中，於 `pi` 用戶的主目錄中創建一個名為 `soil-moisture-sensor` 的新文件夾。在此文件夾中創建一個名為 `app.py` 的文件。

1. 在 VS Code 中打開此文件夾。

1. 在 `app.py` 文件中添加以下代碼以導入所需的庫：

    ```python
    import time
    from grove.adc import ADC
    ```

    `import time` 語句導入了 `time` 模塊，稍後將在此任務中使用。

    `from grove.adc import ADC` 語句從 Grove Python 庫中導入了 `ADC`。該庫包含與 Pi Base Hat 上的模擬到數字轉換器交互並從模擬傳感器讀取電壓的代碼。

1. 在此代碼下方添加以下代碼以創建 `ADC` 類的實例：

    ```python
    adc = ADC()
    ```

1. 添加一個無限循環，從 A0 引腳上的 ADC 讀取數據，並將結果寫入控制台。該循環可以在每次讀取之間休眠 10 秒。

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. 運行 Python 應用程序。你將看到土壤濕度測量值顯示在控制台上。向土壤中添加一些水，或者將傳感器從土壤中移除，觀察數值的變化。

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    在上述示例輸出中，你可以看到隨著水的添加，電壓下降。

> 💁 你可以在 [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi) 文件夾中找到此代碼。

😀 你的土壤濕度傳感器程序成功了！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。