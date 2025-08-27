<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-27T00:50:08+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "mo"
}
-->
# 解碼 GPS 數據 - 虛擬 IoT 硬體與 Raspberry Pi

在本課程的這部分，你將解碼由 Raspberry Pi 或虛擬 IoT 裝置從 GPS 感測器讀取的 NMEA 訊息，並提取緯度和經度。

## 解碼 GPS 數據

一旦從串口讀取到原始 NMEA 數據，就可以使用開源 NMEA 庫進行解碼。

### 任務 - 解碼 GPS 數據

編寫程式以解碼 GPS 數據。

1. 如果尚未開啟，請打開 `gps-sensor` 應用程式專案。

1. 安裝 `pynmea2` 的 Pip 套件。此套件包含解碼 NMEA 訊息的程式碼。

    ```sh
    pip3 install pynmea2
    ```

1. 在 `app.py` 文件的導入部分新增以下程式碼，以導入 `pynmea2` 模組：

    ```python
    import pynmea2
    ```

1. 用以下內容替換 `print_gps_data` 函數的內容：

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

    此程式碼將使用 `pynmea2` 庫解析從 UART 串口讀取的行。

    如果訊息的句子類型是 `GGA`，則表示這是一個位置固定訊息，並進行處理。緯度和經度值將從訊息中讀取，並從 NMEA `(d)ddmm.mmmm` 格式轉換為十進制度數。`dm_to_sd` 函數執行此轉換。

    接著檢查緯度的方向，如果緯度是南方，則將其值轉換為負數。同樣地，若經度是西方，也會轉換為負數。

    最後，座標將與用於定位的衛星數量一起打印到控制台。

1. 執行程式碼。如果你使用的是虛擬 IoT 裝置，請確保 CounterFit 應用程式正在運行，並且 GPS 數據正在傳送。

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 你可以在 [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) 資料夾或 [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi) 資料夾中找到此程式碼。

😀 你的 GPS 感測器程式成功解碼數據！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。