<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-24T22:36:59+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "tw"
}
-->
# 測量土壤濕度 - Wio Terminal

在本課程中，您將為 Wio Terminal 添加一個電容式土壤濕度傳感器，並從中讀取數值。

## 硬體

Wio Terminal 需要一個電容式土壤濕度傳感器。

您將使用的傳感器是 [電容式土壤濕度傳感器](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)，它通過檢測土壤的電容來測量土壤濕度，這是一種會隨土壤濕度變化而改變的特性。當土壤濕度增加時，電壓會降低。

這是一個類比傳感器，因此需要連接到 Wio Terminal 的類比引腳，並使用內建的 ADC（類比數位轉換器）生成 0-1,023 的數值。

### 連接土壤濕度傳感器

Grove 土壤濕度傳感器可以連接到 Wio Terminal 的可配置類比/數位埠。

#### 任務 - 連接土壤濕度傳感器

連接土壤濕度傳感器。

![Grove 土壤濕度傳感器](../../../../../translated_images/tw/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. 將 Grove 電纜的一端插入土壤濕度傳感器的插座中。它只能以一種方式插入。

1. 在 Wio Terminal 未連接到電腦或其他電源的情況下，將 Grove 電纜的另一端連接到 Wio Terminal 螢幕右側的 Grove 插座。這是距離電源按鈕最遠的插座。

![Grove 土壤濕度傳感器連接到右側插座](../../../../../translated_images/tw/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. 將土壤濕度傳感器插入土壤中。傳感器上有一條“最高位置線”——一條白線。將傳感器插入到該線以下但不要超過該線。

![土壤中的 Grove 土壤濕度傳感器](../../../../../translated_images/tw/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. 現在可以將 Wio Terminal 連接到您的電腦。

## 編程土壤濕度傳感器

現在可以為 Wio Terminal 編程以使用連接的土壤濕度傳感器。

### 任務 - 編程土壤濕度傳感器

為設備編程。

1. 使用 PlatformIO 創建一個全新的 Wio Terminal 專案。將此專案命名為 `soil-moisture-sensor`。在 `setup` 函數中添加代碼以配置序列埠。

    > ⚠️ 如果需要，您可以參考 [專案 1，第 1 課中創建 PlatformIO 專案的說明](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project)。

1. 此傳感器沒有專用的庫，您可以使用內建的 Arduino [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) 函數從類比引腳讀取數值。首先，在 `setup` 函數中配置類比引腳為輸入，以便可以從中讀取數值，添加以下代碼：

    ```cpp
    pinMode(A0, INPUT);
    ```

    這將 `A0` 引腳（類比/數位組合引腳）設置為輸入引腳，以便可以讀取電壓。

1. 在 `loop` 函數中添加以下代碼以從該引腳讀取電壓：

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. 在此代碼下方，添加以下代碼以將數值打印到序列埠：

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. 最後，在末尾添加一個 10 秒的延遲：

    ```cpp
    delay(10000);
    ```

1. 編譯並將代碼上傳到 Wio Terminal。

    > ⚠️ 如果需要，您可以參考 [專案 1，第 1 課中創建 PlatformIO 專案的說明](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app)。

1. 上傳完成後，您可以使用序列監視器監控土壤濕度。向土壤中添加一些水，或將傳感器從土壤中取出，觀察數值變化。

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    在上面的範例輸出中，您可以看到隨著水的添加，電壓下降。

> 💁 您可以在 [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) 資料夾中找到此代碼。

😀 您的土壤濕度傳感器程式成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原文文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤讀概不負責。