<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-26T15:50:21+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "hk"
}
-->
# 解碼 GPS 數據 - Wio Terminal

在這部分課程中，你將解碼從 Wio Terminal 的 GPS 感測器讀取的 NMEA 訊息，並提取緯度和經度。

## 解碼 GPS 數據

一旦從序列埠讀取到原始的 NMEA 數據，就可以使用開源的 NMEA 函式庫進行解碼。

### 任務 - 解碼 GPS 數據

編寫程式讓裝置解碼 GPS 數據。

1. 如果尚未開啟，請打開 `gps-sensor` 應用程式專案。

1. 在專案的 `platformio.ini` 檔案中，新增 [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) 函式庫的依賴項目。這個函式庫包含解碼 NMEA 數據的程式碼。

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. 在 `main.cpp` 中，新增一行包含 TinyGPSPlus 函式庫的指令：

    ```cpp
    #include <TinyGPS++.h>
    ```

1. 在 `Serial3` 宣告的下方，宣告一個 TinyGPSPlus 物件來處理 NMEA 訊息：

    ```cpp
    TinyGPSPlus gps;
    ```

1. 將 `printGPSData` 函式的內容更改為以下內容：

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

    這段程式碼會從 UART 序列埠讀取下一個字元並傳入 `gps` NMEA 解碼器。每讀取一個字元後，它會檢查解碼器是否已讀取到有效的訊息，然後檢查是否已讀取到有效的位置。如果位置有效，它會將位置資料和參與定位的衛星數量一起傳送到序列監控器。

1. 編譯並上傳程式碼到 Wio Terminal。

1. 上傳完成後，你可以使用序列監控器來監控 GPS 位置數據。

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 你可以在 [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) 資料夾中找到這段程式碼。

😀 你的 GPS 感測器程式成功解碼數據了！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，請注意自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。