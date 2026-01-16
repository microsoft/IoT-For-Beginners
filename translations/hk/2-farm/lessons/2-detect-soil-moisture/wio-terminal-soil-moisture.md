<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-26T14:44:38+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "hk"
}
-->
# 測量土壤濕度 - Wio Terminal

在本課程中，你將為 Wio Terminal 添加一個電容式土壤濕度傳感器，並從中讀取數據。

## 硬件

Wio Terminal 需要一個電容式土壤濕度傳感器。

你將使用的傳感器是 [電容式土壤濕度傳感器](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)，它通過檢測土壤的電容來測量土壤濕度，這是一個會隨著土壤濕度變化而改變的特性。當土壤濕度增加時，電壓會下降。

這是一個模擬傳感器，因此需要連接到 Wio Terminal 的模擬引腳，並使用內置的 ADC（模數轉換器）生成 0-1,023 的數值。

### 連接土壤濕度傳感器

Grove 土壤濕度傳感器可以連接到 Wio Terminal 的可配置模擬/數字端口。

#### 任務 - 連接土壤濕度傳感器

連接土壤濕度傳感器。

![Grove 土壤濕度傳感器](../../../../../translated_images/hk/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. 將 Grove 電纜的一端插入土壤濕度傳感器的插座中。電纜只能以一種方式插入。

1. 在 Wio Terminal 未連接到電腦或其他電源的情況下，將 Grove 電纜的另一端連接到 Wio Terminal 屏幕右側的 Grove 插座。這是距離電源按鈕最遠的插座。

![Grove 土壤濕度傳感器連接到右側插座](../../../../../translated_images/hk/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. 將土壤濕度傳感器插入土壤中。傳感器上有一條“最高位置線”——一條白線。將傳感器插入到該線以下，但不要超過該線。

![Grove 土壤濕度傳感器插入土壤中](../../../../../translated_images/hk/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. 現在可以將 Wio Terminal 連接到電腦。

## 編程土壤濕度傳感器

現在可以為 Wio Terminal 編程以使用連接的土壤濕度傳感器。

### 任務 - 編程土壤濕度傳感器

為設備編程。

1. 使用 PlatformIO 創建一個全新的 Wio Terminal 項目。將此項目命名為 `soil-moisture-sensor`。在 `setup` 函數中添加代碼以配置串口。

    > ⚠️ 如果需要，可以參考 [項目 1，第 1 課中創建 PlatformIO 項目的說明](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project)。

1. 該傳感器沒有專用的庫，但你可以使用內置的 Arduino [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) 函數從模擬引腳讀取數據。首先，在 `setup` 函數中配置模擬引腳為輸入，以便可以從中讀取數據，添加以下代碼：

    ```cpp
    pinMode(A0, INPUT);
    ```

    這將 `A0` 引腳（模擬/數字組合引腳）設置為輸入引腳，以便可以讀取電壓。

1. 在 `loop` 函數中添加以下代碼以從該引腳讀取電壓：

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. 在此代碼下方，添加以下代碼將數值打印到串口：

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. 最後，在末尾添加一個 10 秒的延遲：

    ```cpp
    delay(10000);
    ```

1. 編譯並將代碼上傳到 Wio Terminal。

    > ⚠️ 如果需要，可以參考 [項目 1，第 1 課中創建 PlatformIO 項目的說明](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app)。

1. 上傳完成後，你可以使用串口監視器監控土壤濕度。向土壤中添加一些水，或者將傳感器從土壤中取出，觀察數值的變化。

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

    在上面的示例輸出中，你可以看到隨著水的添加，電壓下降。

> 💁 你可以在 [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) 文件夾中找到此代碼。

😀 你的土壤濕度傳感器程序成功了！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。