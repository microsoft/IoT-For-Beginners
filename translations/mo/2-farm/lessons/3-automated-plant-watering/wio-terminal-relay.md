<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-26T22:29:08+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "mo"
}
-->
# 控制繼電器 - Wio Terminal

在本課程中，您將在 Wio Terminal 上添加一個繼電器，除了土壤濕度傳感器外，還可以根據土壤濕度水平來控制它。

## 硬體

Wio Terminal 需要一個繼電器。

您將使用的是 [Grove 繼電器](https://www.seeedstudio.com/Grove-Relay.html)，這是一個常開型繼電器（意味著當沒有信號發送到繼電器時，輸出電路是開路或斷開的），它可以處理最高 250V 和 10A 的輸出電路。

這是一個數位執行器，因此需要連接到 Wio Terminal 的數位引腳。模擬/數位組合端口已經被土壤濕度傳感器使用，因此繼電器需要插入另一個端口，該端口是組合 I

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。