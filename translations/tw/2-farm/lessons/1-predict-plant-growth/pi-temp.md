<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-24T22:08:12+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "tw"
}
-->
# 測量溫度 - Raspberry Pi

在本課程中，您將為 Raspberry Pi 添加一個溫度感測器。

## 硬體

您將使用的感測器是 [DHT11 濕度與溫度感測器](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)，它將兩個感測器結合在一個裝置中。這是一款相當受歡迎的感測器，許多市售感測器都結合了溫度、濕度，有時還包括大氣壓力。溫度感測器的元件是一個負溫度係數（NTC）熱敏電阻，這是一種隨著溫度升高而電阻降低的熱敏電阻。

這是一個數位感測器，因此內建了一個 ADC（類比數位轉換器），用於生成包含溫度和濕度數據的數位信號，供微控制器讀取。

### 連接溫度感測器

Grove 溫度感測器可以連接到 Raspberry Pi。

#### 任務

連接溫度感測器

![一個 Grove 溫度感測器](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.tw.png)

1. 將 Grove 電纜的一端插入濕度與溫度感測器上的插槽。它只能以一種方式插入。

1. 在 Raspberry Pi 關機的情況下，將 Grove 電纜的另一端連接到安裝在 Pi 上的 Grove Base Hat 上標記為 **D5** 的數位插槽。此插槽位於 GPIO 引腳旁邊的一排插槽中，從左數第二個。

![Grove 溫度感測器連接到 A0 插槽](../../../../../translated_images/pi-temperature-sensor.3ff82fff672c8e56.tw.png)

## 編寫溫度感測器程式

現在可以為裝置編寫程式來使用已連接的溫度感測器。

### 任務

編寫裝置程式。

1. 啟動 Raspberry Pi，並等待其完成啟動。

1. 啟動 VS Code，可以直接在 Pi 上啟動，或者通過 Remote SSH 擴展連接。

    > ⚠️ 如果需要，您可以參考 [第 1 課中有關設置和啟動 VS Code 的說明](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md)。

1. 在終端中，於 `pi` 使用者的主目錄中建立一個名為 `temperature-sensor` 的新資料夾。在此資料夾中建立一個名為 `app.py` 的檔案：

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. 在 VS Code 中打開此資料夾。

1. 要使用溫度與濕度感測器，需要安裝一個額外的 Pip 套件。在 VS Code 的終端中，執行以下命令以在 Pi 上安裝此 Pip 套件：

    ```sh
    pip3 install seeed-python-dht
    ```

1. 將以下程式碼添加到 `app.py` 檔案中以匯入所需的函式庫：

    ```python
    import time
    from seeed_dht import DHT
    ```

    `from seeed_dht import DHT` 語句從 `seeed_dht` 模組中匯入 `DHT` 感測器類別，用於與 Grove 溫度感測器互動。

1. 在上述程式碼之後添加以下程式碼，以建立管理溫度感測器的類別實例：

    ```python
    sensor = DHT("11", 5)
    ```

    這聲明了一個 `DHT` 類別的實例，用於管理 **D**igital **H**umidity 和 **T**emperature 感測器。第一個參數告訴程式使用的是 *DHT11* 感測器——您使用的函式庫支援此感測器的其他變體。第二個參數告訴程式感測器連接到 Grove Base Hat 的數位插槽 `D5`。

    > ✅ 請記住，所有插槽都有唯一的引腳編號。引腳 0、2、4 和 6 是類比引腳，引腳 5、16、18、22、24 和 26 是數位引腳。

1. 在上述程式碼之後添加一個無限迴圈，用於輪詢溫度感測器的值並將其輸出到控制台：

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    呼叫 `sensor.read()` 會返回一個包含濕度和溫度的元組。您只需要溫度值，因此可以忽略濕度值。然後將溫度值輸出到控制台。

1. 在迴圈的末尾添加一個 10 秒的小延遲，因為不需要連續檢查溫度水平。延遲可以減少裝置的功耗。

    ```python
    time.sleep(10)
    ```

1. 在 VS Code 的終端中執行以下命令以運行您的 Python 應用程式：

    ```sh
    python3 app.py
    ```

    您應該會看到溫度值輸出到控制台。使用某些東西來加熱感測器，例如用拇指按住它，或者使用風扇，觀察值的變化：

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 您可以在 [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi) 資料夾中找到此程式碼。

😀 您的溫度感測器程式成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。