<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-25T00:54:41+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "tw"
}
-->
# 解碼 GPS 數據 - Wio Terminal

在本課程中，您將解碼從 Wio Terminal 的 GPS 感測器讀取的 NMEA 訊息，並提取緯度和經度。

## 解碼 GPS 數據

一旦從串列埠讀取到原始 NMEA 數據，就可以使用開源的 NMEA 庫進行解碼。

### 任務 - 解碼 GPS 數據

編程設備以解碼 GPS 數據。

1. 如果尚未開啟，請打開 `gps-sensor` 應用程式專案

1. 在專案的 `platformio.ini` 文件中添加 [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) 庫的依賴。該庫包含解碼 NMEA 數據的程式碼。

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. 在 `main.cpp` 中，添加 TinyGPSPlus 庫的 include 指令：

    ```cpp
    #include <TinyGPS++.h>
    ```

1. 在 `Serial3` 的宣告下，宣告一個 TinyGPSPlus 物件以處理 NMEA 訊息：

    ```cpp
    TinyGPSPlus gps;
    ```

1. 將 `printGPSData` 函數的內容更改為以下內容：

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    此程式碼從 UART 串列埠讀取下一個字元到 `gps` NMEA 解碼器中。每讀取一個字元後，它會檢查解碼器是否已讀取到有效的訊息，然後檢查是否已讀取到有效的位置。如果位置有效，它會將位置和參與此定位的衛星數量發送到串列監視器。

1. 編譯並上傳程式碼到 Wio Terminal。

1. 上傳完成後，您可以使用串列監視器監控 GPS 位置數據。

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 您可以在 [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) 資料夾中找到此程式碼。

😀 您的 GPS 感測器程式成功解碼數據！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而產生的任何誤解或錯誤解讀概不負責。