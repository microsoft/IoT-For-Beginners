<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-26T22:21:40+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "mo"
}
-->
# 測量溫度 - Raspberry Pi

在本課程的這部分，你將為 Raspberry Pi 添加一個溫度感測器。

## 硬體

你將使用的感測器是 [DHT11 濕度與溫度感測器](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)，它將兩個感測器結合在一個模組中。這是一款相當受歡迎的感測器，市面上有許多結合溫度、濕度，有時甚至包含大氣壓力的感測器。溫度感測器部分是一個負溫度係數（NTC）熱敏電阻，這是一種電阻會隨著溫度升高而降低的熱敏電阻。

這是一個數位感測器，因此內建了一個 ADC（模數轉換器），用於生成包含溫度和濕度數據的數位信號，供微控制器讀取。

### 連接溫度感測器

Grove 溫度感測器可以連接到 Raspberry Pi。

#### 任務

連接溫度感測器

![Grove 溫度感測器](../../../../../translated_images/mo/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. 將 Grove 線纜的一端插入濕度與溫度感測器的插座。它只能以一種方式插入。

1. 在 Raspberry Pi 關機的情況下，將 Grove 線纜的另一端連接到 Pi 上 Grove Base Hat 的數位插座 **D5**。這個插座位於 GPIO 引腳旁邊的一排插座中，從左數第二個。

![Grove 溫度感測器連接到插座 A0](../../../../../translated_images/mo/pi-temperature-sensor.3ff82fff672c8e56.webp)

## 編寫溫度感測器程式

現在可以編寫程式來使用已連接的溫度感測器。

### 任務

編寫程式。

1. 啟動 Raspberry Pi，等待其完成開機。

1. 啟動 VS Code，可以直接在 Raspberry Pi 上啟動，也可以通過 Remote SSH 擴展連接。

    > ⚠️ 如果需要，可以參考[第 1 課中有關設置和啟動 VS Code 的說明](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md)。

1. 在終端中，於 `pi` 使用者的主目錄中創建一個名為 `temperature-sensor` 的新資料夾。在該資料夾中創建一個名為 `app.py` 的檔案：

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. 在 VS Code 中打開這個資料夾。

1. 要使用溫度與濕度感測器，需要安裝一個額外的 Pip 套件。在 VS Code 的終端中執行以下命令，將該 Pip 套件安裝到 Raspberry Pi 上：

    ```sh
    pip3 install seeed-python-dht
    ```

1. 在 `app.py` 檔案中添加以下程式碼以匯入所需的函式庫：

    ```python
    import time
    from seeed_dht import DHT
    ```

    `from seeed_dht import DHT` 語句從 `seeed_dht` 模組中匯入了 `DHT` 感測器類別，用於與 Grove 溫度感測器互動。

1. 在上述程式碼之後添加以下程式碼，創建一個管理溫度感測器的類別實例：

    ```python
    sensor = DHT("11", 5)
    ```

    這段程式碼聲明了一個 `DHT` 類別的實例，用於管理**數位濕度與溫度感測器**。第一個參數告訴程式使用的是 *DHT11* 感測器——你使用的函式庫還支援該感測器的其他變體。第二個參數告訴程式感測器連接到 Grove Base Hat 的數位插座 `D5`。

    > ✅ 請記住，每個插座都有唯一的引腳編號。引腳 0、2、4 和 6 是類比引腳，引腳 5、16、18、22、24 和 26 是數位引腳。

1. 在上述程式碼之後添加一個無限迴圈，用於輪詢溫度感測器的值並將其輸出到控制台：

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    呼叫 `sensor.read()` 會返回一個包含濕度和溫度的元組。你只需要溫度值，因此可以忽略濕度值。然後將溫度值輸出到控制台。

1. 在迴圈的最後添加一個 10 秒的延遲，因為不需要持續檢查溫度值。延遲可以減少裝置的功耗。

    ```python
    time.sleep(10)
    ```

1. 在 VS Code 的終端中執行以下命令來運行你的 Python 應用程式：

    ```sh
    python3 app.py
    ```

    你應該會看到溫度值輸出到控制台。使用某些東西來加熱感測器，例如用手指按住它，或者使用風扇，觀察數值的變化：

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 你可以在 [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi) 資料夾中找到這段程式碼。

😀 你的溫度感測器程式成功運行了！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。