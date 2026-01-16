<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-26T22:53:12+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "mo"
}
-->
# 測量土壤濕度 - Raspberry Pi

在本課程中，您將為 Raspberry Pi 添加一個電容式土壤濕度傳感器，並從中讀取數據。

## 硬體

Raspberry Pi 需要一個電容式土壤濕度傳感器。

您將使用的傳感器是 [電容式土壤濕度傳感器](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)，它通過檢測土壤的電容來測量土壤濕度，這是一個會隨著土壤濕度變化而改變的特性。當土壤濕度增加時，電壓會降低。

這是一個類比傳感器，因此使用類比引腳，並通過 Pi 上的 Grove Base Hat 中的 10 位 ADC 將電壓轉換為 1-1,023 的數位信號。然後通過 Pi 的 GPIO 引腳以 I²C 傳輸。

### 連接土壤濕度傳感器

Grove 土壤濕度傳感器可以連接到 Raspberry Pi。

#### 任務 - 連接土壤濕度傳感器

連接土壤濕度傳感器。

![Grove 土壤濕度傳感器](../../../../../translated_images/mo/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. 將 Grove 電纜的一端插入土壤濕度傳感器上的插座。它只能以一種方式插入。

1. 在 Raspberry Pi 關機的情況下，將 Grove 電纜的另一端連接到 Pi 上 Grove Base Hat 的類比插座 **A0**。這個插座位於 GPIO 引腳旁邊的一排插座中，從右數第二個。

![Grove 土壤濕度傳感器連接到 A0 插座](../../../../../translated_images/mo/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.png)

1. 將土壤濕度傳感器插入土壤中。傳感器上有一條“最高位置線”——一條白線。將傳感器插入到該線以下但不要超過該線。

![Grove 土壤濕度傳感器插入土壤中](../../../../../translated_images/mo/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

## 編程土壤濕度傳感器

現在可以為 Raspberry Pi 編程以使用連接的土壤濕度傳感器。

### 任務 - 編程土壤濕度傳感器

編程設備。

1. 啟動 Raspberry Pi，並等待其啟動完成。

1. 啟動 VS Code，可以直接在 Pi 上啟動，或者通過 Remote SSH 擴展連接。

    > ⚠️ 如果需要，您可以參考 [夜燈課程 1 中的設置和啟動 VS Code 的說明](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md)。

1. 在終端中，於 `pi` 用戶的主目錄中創建一個名為 `soil-moisture-sensor` 的新資料夾。在此資料夾中創建一個名為 `app.py` 的檔案。

1. 在 VS Code 中打開此資料夾。

1. 將以下程式碼添加到 `app.py` 檔案中以匯入一些所需的庫：

    ```python
    import time
    from grove.adc import ADC
    ```

    `import time` 語句匯入了 `time` 模組，稍後將在此任務中使用。

    `from grove.adc import ADC` 語句從 Grove Python 庫中匯入了 `ADC`。此庫包含與 Pi Base Hat 上的類比數位轉換器互動並從類比傳感器讀取電壓的程式碼。

1. 在此程式碼下方添加以下程式碼以創建 `ADC` 類的實例：

    ```python
    adc = ADC()
    ```

1. 添加一個無限迴圈，從 A0 引腳上的 ADC 讀取數據，並將結果寫入控制台。此迴圈可以在每次讀取之間休眠 10 秒。

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. 運行 Python 應用程式。您將在控制台中看到土壤濕度的測量值。向土壤中添加一些水，或者將傳感器從土壤中取出，觀察數值的變化。

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    在上述範例輸出中，您可以看到隨著水的添加，電壓下降。

> 💁 您可以在 [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi) 資料夾中找到此程式碼。

😀 您的土壤濕度傳感器程式成功了！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。