<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-24T21:54:43+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "tw"
}
-->
# 偵測距離 - Wio Terminal

在本課程中，您將為 Wio Terminal 添加一個距離感測器，並從中讀取距離數據。

## 硬體

Wio Terminal 需要一個距離感測器。

您將使用的感測器是 [Grove 飛行時間距離感測器](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)。此感測器使用雷射測距模組來偵測距離。此感測器的量測範圍為 10mm 至 2000mm（1cm - 2m），並能相當準確地報告該範圍內的距離值，超過 1000mm 的距離將報告為 8109mm。

雷射測距儀位於感測器的背面，也就是 Grove 插座的相對面。

這是一個 I2C 感測器。

### 連接飛行時間感測器

Grove 飛行時間感測器可以連接到 Wio Terminal。

#### 任務 - 連接飛行時間感測器

連接飛行時間感測器。

![Grove 飛行時間感測器](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.tw.png)

1. 將 Grove 電纜的一端插入飛行時間感測器上的插座。電纜只能以一種方向插入。

1. 在 Wio Terminal 未連接到電腦或其他電源的情況下，將 Grove 電纜的另一端連接到 Wio Terminal 左側的 Grove 插座（面向螢幕）。這是靠近電源按鈕的插座，該插座是數位和 I2C 的組合插座。

![Grove 飛行時間感測器連接到左側插座](../../../../../translated_images/wio-time-of-flight-sensor.c4c182131d2ea73d.tw.png)

1. 現在可以將 Wio Terminal 連接到您的電腦。

## 程式設計飛行時間感測器

現在可以為 Wio Terminal 編寫程式以使用已連接的飛行時間感測器。

### 任務 - 程式設計飛行時間感測器

1. 使用 PlatformIO 創建一個全新的 Wio Terminal 專案。將此專案命名為 `distance-sensor`。在 `setup` 函數中添加程式碼以配置序列埠。

1. 在專案的 `platformio.ini` 文件中添加 Seeed Grove 飛行時間距離感測器庫的依賴項：

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. 在 `main.cpp` 中，將以下程式碼添加到現有的 include 指令下方，以宣告一個 `Seeed_vl53l0x` 類的實例，用於與飛行時間感測器互動：

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. 在 `setup` 函數的底部添加以下程式碼以初始化感測器：

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. 在 `loop` 函數中，從感測器讀取一個值：

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    此程式碼初始化一個資料結構以讀取數據，然後將其傳遞給 `PerformSingleRangingMeasurement` 方法，該方法會填充距離測量值。

1. 在此程式碼下方，輸出距離測量值，然後延遲 1 秒：

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. 建置、上傳並執行此程式碼。您將能夠使用序列監視器查看距離測量值。將物體放置在感測器附近，您將看到距離測量值：

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    測距儀位於感測器的背面，因此在測量距離時請確保使用正確的一側。

    ![飛行時間感測器背面的測距儀指向一根香蕉](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4.tw.png)

> 💁 您可以在 [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal) 資料夾中找到此程式碼。

😀 您的距離感測器程式成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原文文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。