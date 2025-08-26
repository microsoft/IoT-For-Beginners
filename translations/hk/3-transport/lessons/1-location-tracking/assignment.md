<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bded364fc06ce37d7a76aed3be1ba73a",
  "translation_date": "2025-08-26T15:49:08+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/assignment.md",
  "language_code": "hk"
}
-->
# 探索其他 GPS 數據

## 指引

從您的 GPS 感測器接收到的 NMEA 訊息除了位置資訊外，還包含其他數據。探索這些額外的數據，並在您的 IoT 裝置中加以利用。

例如 - 您能否獲取當前的日期和時間？如果您使用的是微控制器，能否像在上一個項目中使用 NTP 信號設置時鐘一樣，使用 GPS 數據來設置時鐘？您能否獲取海拔高度（您距離海平面的高度）或當前速度？

如果您使用的是虛擬 IoT 裝置，則可以通過使用工具 [nmeagen.org](https://www.nmeagen.org) 生成的 NMEA 訊息來獲取部分數據。

## 評分標準

| 評分標準 | 卓越 | 合格 | 需要改進 |
| -------- | ----- | ---- | -------- |
| 獲取更多 GPS 數據 | 能夠獲取並使用更多 GPS 數據，作為遙測數據或用於設置 IoT 裝置 | 能夠獲取更多 GPS 數據，但無法使用它 | 無法獲取更多 GPS 數據 |

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業的人工作翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解讀概不負責。