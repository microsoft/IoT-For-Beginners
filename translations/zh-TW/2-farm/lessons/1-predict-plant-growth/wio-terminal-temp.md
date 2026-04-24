# 測量溫度 - Wio Terminal

在本課程中，您將為 Wio Terminal 添加一個溫度感測器，並從中讀取溫度值。

## 硬體

Wio Terminal 需要一個溫度感測器。

您將使用的是 [DHT11 濕度與溫度感測器](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)，它將兩個感測器結合在一個裝置中。這是一款相當受歡迎的感測器，市面上有許多結合溫度、濕度，有時甚至是大氣壓力的感測器。溫度感測部分是一個負溫度係數（NTC）熱敏電阻，這是一種隨著溫度升高電阻會降低的熱敏電阻。

這是一個數位感測器，因此內建了一個 ADC（類比數位轉換器），用於生成包含溫度和濕度數據的數位信號，供微控制器讀取。

### 連接溫度感測器

Grove 溫度感測器可以連接到 Wio Terminal 的數位埠。

#### 任務 - 連接溫度感測器

連接溫度感測器。

![一個 Grove 溫度感測器](../../../../../translated_images/zh-TW/grove-dht11.07f8eafceee17004.webp)

1. 將 Grove 線纜的一端插入濕度與溫度感測器的插槽中。它只能以一種方式插入。

1. 在 Wio Terminal 未連接到電腦或其他電源的情況下，將 Grove 線纜的另一端連接到 Wio Terminal 螢幕右側的 Grove 插槽。這是距離電源按鈕最遠的插槽。

![Grove 溫度感測器連接到右側插槽](../../../../../translated_images/zh-TW/wio-temperature-sensor.2934928f38c7f79a.webp)

## 編寫溫度感測器程式

現在可以為 Wio Terminal 編寫程式來使用已連接的溫度感測器。

### 任務 - 編寫溫度感測器程式

編寫裝置程式。

1. 使用 PlatformIO 建立一個全新的 Wio Terminal 專案。將此專案命名為 `temperature-sensor`。在 `setup` 函式中添加程式碼以配置序列埠。

    > ⚠️ 如果需要，您可以參考 [專案 1，第 1 課中建立 PlatformIO 專案的指導](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project)。

1. 在專案的 `platformio.ini` 檔案中，為 Seeed Grove 濕度與溫度感測器庫添加一個庫依賴：

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ 如果需要，您可以參考 [專案 1，第 4 課中為 PlatformIO 專案添加庫的指導](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries)。

1. 在檔案頂部的 `#include <Arduino.h>` 下方添加以下 `#include` 指令：

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    這些指令導入了與感測器互動所需的檔案。`DHT.h` 標頭檔包含感測器本身的程式碼，而添加 `SPI.h` 標頭檔則確保在應用程式編譯時鏈接到與感測器通訊所需的程式碼。

1. 在 `setup` 函式之前，宣告 DHT 感測器：

    ```cpp
    DHT dht(D0, DHT11);
    ```

    這宣告了一個 `DHT` 類的實例，用於管理數位濕度與溫度感測器。此感測器連接到 Wio Terminal 的 `D0` 埠，也就是右側的 Grove 插槽。第二個參數告訴程式使用的是 *DHT11* 感測器——您使用的庫支援此感測器的其他變體。

1. 在 `setup` 函式中，添加程式碼以設置序列連接：

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. 在 `setup` 函式的最後一個 `delay` 之後，添加啟動 DHT 感測器的呼叫：

    ```cpp
    dht.begin();
    ```

1. 在 `loop` 函式中，添加程式碼以呼叫感測器並將溫度打印到序列埠：

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    此程式碼宣告了一個包含兩個浮點數的空陣列，並將其傳遞給 `DHT` 實例的 `readTempAndHumidity` 呼叫。此呼叫會將兩個值填入陣列——濕度存入陣列的第 0 項（請記住，在 C++ 中，陣列是從 0 開始的，因此第 0 項是陣列的「第一」項），溫度存入第 1 項。

    溫度從陣列的第 1 項讀取，並打印到序列埠。

    > 🇺🇸 溫度以攝氏度讀取。對於美國人，若要將攝氏溫度轉換為華氏溫度，請將讀取的攝氏值除以 5，然後乘以 9，最後加上 32。例如，20°C 的溫度讀數轉換為 ((20/5)*9) + 32 = 68°F。

1. 編譯並將程式碼上傳到 Wio Terminal。

    > ⚠️ 如果需要，您可以參考 [專案 1，第 1 課中建立 PlatformIO 專案的指導](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app)。

1. 上傳完成後，您可以使用序列監視器監控溫度：

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 您可以在 [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal) 資料夾中找到此程式碼。

😀 您的溫度感測器程式成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對於因使用此翻譯而引起的任何誤解或誤讀概不負責。