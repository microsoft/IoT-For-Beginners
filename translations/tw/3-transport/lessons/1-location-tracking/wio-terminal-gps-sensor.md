<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-25T00:44:19+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "tw"
}
-->
# 讀取 GPS 數據 - Wio Terminal

在本課程中，您將為 Wio Terminal 添加一個 GPS 感測器，並從中讀取數據。

## 硬體

Wio Terminal 需要一個 GPS 感測器。

您將使用的感測器是 [Grove GPS Air530 感測器](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)。此感測器可以連接到多個 GPS 系統，以快速且精確地定位。該感測器由兩部分組成——感測器的核心電子元件，以及通過細線連接的外部天線，用於接收來自衛星的無線電波。

這是一個 UART 感測器，因此它通過 UART 傳輸 GPS 數據。

### 連接 GPS 感測器

Grove GPS 感測器可以連接到 Wio Terminal。

#### 任務 - 連接 GPS 感測器

連接 GPS 感測器。

![一個 Grove GPS 感測器](../../../../../translated_images/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.tw.png)

1. 將 Grove 線纜的一端插入 GPS 感測器上的插槽。它只能以一種方式插入。

1. 在 Wio Terminal 未連接到電腦或其他電源的情況下，將 Grove 線纜的另一端連接到 Wio Terminal 左側的 Grove 插槽（面向螢幕時）。這是靠近電源按鈕的插槽。

    ![Grove GPS 感測器連接到左側插槽](../../../../../translated_images/wio-gps-sensor.19fd52b81ce58095.tw.png)

1. 將 GPS 感測器放置在附帶的天線可以看到天空的位置——理想情況下靠近窗戶或在室外。天線周圍沒有障礙物時，信號會更清晰。

1. 現在可以將 Wio Terminal 連接到您的電腦。

1. GPS 感測器有兩個 LED 指示燈——藍色 LED 在傳輸數據時閃爍，綠色 LED 在接收來自衛星的數據時每秒閃爍一次。當您啟動 Wio Terminal 時，確保藍色 LED 正在閃爍。幾分鐘後，綠色 LED 會開始閃爍——如果沒有，您可能需要重新調整天線的位置。

## 編程 GPS 感測器

現在可以為 Wio Terminal 編寫程式，以使用連接的 GPS 感測器。

### 任務 - 編程 GPS 感測器

為設備編寫程式。

1. 使用 PlatformIO 創建一個全新的 Wio Terminal 專案。將此專案命名為 `gps-sensor`。在 `setup` 函數中添加程式碼以配置串列埠。

1. 在 `main.cpp` 文件的頂部添加以下 include 指令。這將包含一個用於配置左側 Grove 埠為 UART 的標頭文件。

    ```cpp
    #include <wiring_private.h>
    ```

1. 在此之下，添加以下程式碼行以聲明一個與 UART 埠的串列埠連接：

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. 您需要添加一些程式碼，將一些內部信號處理程序重定向到此串列埠。在 `Serial3` 聲明的下方添加以下程式碼：

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. 在 `setup` 函數中，`Serial` 埠配置的下方，使用以下程式碼配置 UART 串列埠：

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. 在 `setup` 函數中的此程式碼下方，添加以下程式碼以將 Grove 引腳連接到串列埠：

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. 在 `loop` 函數之前，添加以下函數以將 GPS 數據發送到串列監視器：

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. 在 `loop` 函數中，添加以下程式碼以從 UART 串列埠讀取數據並將輸出打印到串列監視器：

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    此程式碼從 UART 串列埠讀取數據。`readStringUntil` 函數會讀取直到終止符（在此情況下為換行符）的內容。這將讀取整個 NMEA 語句（NMEA 語句以換行符結尾）。只要可以從 UART 串列埠讀取數據，就會讀取數據並通過 `printGPSData` 函數發送到串列監視器。一旦無法再讀取數據，`loop` 將延遲 1 秒（1,000 毫秒）。

1. 編譯並將程式碼上傳到 Wio Terminal。

1. 上傳完成後，您可以使用串列監視器監控 GPS 數據。

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 您可以在 [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal) 資料夾中找到此程式碼。

😀 您的 GPS 感測器程式成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對於因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。