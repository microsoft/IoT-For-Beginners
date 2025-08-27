<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bded364fc06ce37d7a76aed3be1ba73a",
  "translation_date": "2025-08-27T00:49:23+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/assignment.md",
  "language_code": "mo"
}
-->
# 調查其他 GPS 數據

## 說明

從您的 GPS 感測器接收到的 NMEA 訊息中，除了位置資訊外，還包含其他數據。請調查這些額外的數據，並將其應用於您的 IoT 裝置中。

例如 - 您能否獲取當前的日期和時間？如果您使用的是微控制器，是否可以像在上一個專案中使用 NTP 信號設置時鐘一樣，使用 GPS 數據來設置時鐘？您能否獲取海拔高度（即海平面以上的高度）或當前速度？

如果您使用的是虛擬 IoT 裝置，則可以使用工具 [nmeagen.org](https://www.nmeagen.org) 生成的 NMEA 訊息來獲取其中一些數據。

## 評分標準

| 評分標準 | 優秀 | 合格 | 需要改進 |
| -------- | ---- | ---- | -------- |
| 獲取更多 GPS 數據 | 能夠獲取並使用更多 GPS 數據，無論是作為遙測數據還是用於設置 IoT 裝置 | 能夠獲取更多 GPS 數據，但無法使用這些數據 | 無法獲取更多 GPS 數據 |

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。