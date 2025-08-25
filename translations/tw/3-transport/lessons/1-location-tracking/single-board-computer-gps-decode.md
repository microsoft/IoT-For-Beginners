<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-25T00:52:10+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "tw"
}
-->
# 解碼 GPS 數據 - 虛擬 IoT 硬體與 Raspberry Pi

在本課程的這部分，你將解碼由 Raspberry Pi 或虛擬 IoT 裝置從 GPS 感測器讀取的 NMEA 訊息，並提取緯度和經度。

## 解碼 GPS 數據

一旦從串列埠讀取到原始的 NMEA 數據，就可以使用開源的 NMEA 庫進行解碼。

### 任務 - 解碼 GPS 數據

編寫程式以解碼 GPS 數據。

1. 如果尚未開啟 `gps-sensor` 應用程式專案，請將其打開。

1. 安裝 `pynmea2` Pip 套件。此套件包含解碼 NMEA 訊息的程式碼。

    ```sh
    pip3 install pynmea2
    ```

1. 在 `app.py` 檔案的匯入部分新增以下程式碼，以匯入 `pynmea2` 模組：

    ```python
    import pynmea2
    ```

1. 將 `print_gps_data` 函數的內容替換為以下程式碼：

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    此程式碼將使用 `pynmea2` 庫解析從 UART 串列埠讀取的行。

    如果訊息的句子類型是 `GGA`，則表示這是一個位置固定訊息，並進行處理。緯度和經度值將從訊息中讀取，並從 NMEA `(d)ddmm.mmmm` 格式轉換為十進制度數。`dm_to_sd` 函數負責進行此轉換。

    接著檢查緯度的方向，如果緯度是南方，則將其值轉換為負數。同樣地，如果經度是西方，也將其轉換為負數。

    最後，座標以及用於定位的衛星數量將被列印到控制台。

1. 執行程式碼。如果你使用的是虛擬 IoT 裝置，請確保 CounterFit 應用程式正在運行，並且 GPS 數據正在傳送。

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 你可以在 [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) 資料夾或 [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi) 資料夾中找到此程式碼。

😀 你的 GPS 感測器程式成功解碼數據！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用本翻譯而引起的任何誤解或錯誤解讀概不負責。