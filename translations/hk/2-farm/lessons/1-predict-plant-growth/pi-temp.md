<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-26T14:31:35+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "hk"
}
-->
# 測量溫度 - Raspberry Pi

在本課程中，你將為 Raspberry Pi 添加一個溫度感應器。

## 硬件

你將使用的感應器是 [DHT11 濕度和溫度感應器](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)，它將兩個感應器結合在一個封裝中。這是一款相當流行的感應器，市面上有許多商業化的感應器結合了溫度、濕度，有時還包括大氣壓力。溫度感應器部分是一個負溫度係數（NTC）熱敏電阻，這是一種電阻隨溫度升高而減少的熱敏電阻。

這是一個數字感應器，因此它內置了一個 ADC（模數轉換器），用於生成包含溫度和濕度數據的數字信號，供微控制器讀取。

### 連接溫度感應器

Grove 溫度感應器可以連接到 Raspberry Pi。

#### 任務

連接溫度感應器

![Grove 溫度感應器](../../../../../translated_images/hk/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. 將 Grove 電纜的一端插入濕度和溫度感應器上的插座。它只能以一種方式插入。

1. 在 Raspberry Pi 關閉電源的情況下，將 Grove 電纜的另一端連接到 Pi 上 Grove Base hat 的數字插座 **D5**。此插座位於 GPIO 引腳旁邊的一排插座中，從左數第二個。

![Grove 溫度感應器連接到插座 A0](../../../../../translated_images/hk/pi-temperature-sensor.3ff82fff672c8e565ef25a39d26d111de006b825a7e0867227ef4e7fbff8553c.png)

## 編程溫度感應器

現在可以編程設備以使用已連接的溫度感應器。

### 任務

編程設備。

1. 啟動 Raspberry Pi，並等待其啟動。

1. 啟動 VS Code，可以直接在 Pi 上啟動，也可以通過 Remote SSH 擴展連接。

    > ⚠️ 如果需要，可以參考 [第 1 課中設置和啟動 VS Code 的說明](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md)。

1. 在終端中，為 `pi` 用戶的主目錄創建一個名為 `temperature-sensor` 的新文件夾。在此文件夾中創建一個名為 `app.py` 的文件：

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. 在 VS Code 中打開此文件夾。

1. 要使用溫度和濕度感應器，需要安裝一個額外的 Pip 套件。在 VS Code 的終端中，運行以下命令以在 Pi 上安裝此 Pip 套件：

    ```sh
    pip3 install seeed-python-dht
    ```

1. 將以下代碼添加到 `app.py` 文件中以導入所需的庫：

    ```python
    import time
    from seeed_dht import DHT
    ```

    `from seeed_dht import DHT` 語句從 `seeed_dht` 模塊中導入 `DHT` 感應器類，用於與 Grove 溫度感應器交互。

1. 在上述代碼之後添加以下代碼，以創建管理溫度感應器的類的實例：

    ```python
    sensor = DHT("11", 5)
    ```

    這聲明了一個 `DHT` 類的實例，用於管理 **D**igital **H**umidity 和 **T**emperature 感應器。第一個參數告訴代碼使用的是 *DHT11* 感應器——你使用的庫支持此感應器的其他變體。第二個參數告訴代碼感應器連接到 Grove Base hat 的數字端口 `D5`。

    > ✅ 記住，所有插座都有唯一的引腳編號。引腳 0、2、4 和 6 是模擬引腳，引腳 5、16、18、22、24 和 26 是數字引腳。

1. 在上述代碼之後添加一個無限循環，以輪詢溫度感應器的值並將其打印到控制台：

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    調用 `sensor.read()` 返回一個包含濕度和溫度的元組。你只需要溫度值，因此濕度被忽略。然後將溫度值打印到控制台。

1. 在循環的末尾添加一個十秒的小延遲，因為不需要連續檢查溫度水平。延遲可以減少設備的功耗。

    ```python
    time.sleep(10)
    ```

1. 從 VS Code 的終端運行以下命令以運行你的 Python 應用：

    ```sh
    python3 app.py
    ```

    你應該會看到溫度值輸出到控制台。使用某些物品加熱感應器，例如用拇指按壓感應器或使用風扇，觀察值的變化：

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 你可以在 [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi) 文件夾中找到此代碼。

😀 你的溫度感應器程式成功了！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。