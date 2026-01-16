<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c16de27b0074abe81d6a8bad5e5b1a6b",
  "translation_date": "2025-08-24T23:51:19+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/README.md",
  "language_code": "tw"
}
-->
# 支援多語言

![本課程的手繪筆記概述](../../../../../translated_images/tw/lesson-24.4246968ed058510ab275052e87ef9aa89c7b2f938915d103c605c04dc6cd5bb7.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大的版本。

這段影片概述了 Azure 語音服務，涵蓋了之前課程中的語音轉文字和文字轉語音功能，以及本課程中討論的語音翻譯：

[![使用少量 Python 程式碼進行語音識別（Microsoft Build 2020）](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 點擊上方圖片觀看影片

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## 簡介

在過去的三節課中，你學習了如何將語音轉換為文字、語言理解以及將文字轉換為語音，這些功能都由 AI 驅動。AI 還可以幫助人類溝通的另一個領域——語言翻譯，將一種語言轉換為另一種語言，例如從英語翻譯成法語。

在本課程中，你將學習如何使用 AI 進行文字翻譯，使你的智慧計時器能夠與多語言使用者互動。

本課程將涵蓋以下內容：

* [翻譯文字](../../../../../6-consumer/lessons/4-multiple-language-support)
* [翻譯服務](../../../../../6-consumer/lessons/4-multiple-language-support)
* [建立翻譯資源](../../../../../6-consumer/lessons/4-multiple-language-support)
* [透過翻譯在應用程式中支援多語言](../../../../../6-consumer/lessons/4-multiple-language-support)
* [使用 AI 服務翻譯文字](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 這是本專案的最後一課，因此在完成本課程和作業後，別忘了清理你的雲端服務。你需要這些服務來完成作業，因此請確保先完成作業。
>
> 如有需要，請參考[清理專案指南](../../../clean-up.md)以獲取相關指示。

## 翻譯文字

文字翻譯是一個已經研究了超過 70 年的計算機科學問題，直到最近，由於 AI 和計算能力的進步，才接近解決，並達到幾乎與人類翻譯員相媲美的水平。

> 💁 其起源可以追溯到更早的時期，例如 9 世紀的阿拉伯密碼學家 [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi)，他開發了語言翻譯的技術。

### 機器翻譯

文字翻譯最初是一種被稱為機器翻譯（Machine Translation, MT）的技術，可以在不同語言對之間進行翻譯。MT 的工作原理是用一種語言的單詞替換另一種語言的單詞，並添加技術來選擇正確的翻譯方式，當簡單的逐字翻譯不合理時，翻譯短語或句子的一部分。

> 🎓 當翻譯工具支援在一種語言和另一種語言之間進行翻譯時，這些被稱為*語言對*。不同的工具支援不同的語言對，這些可能並不完整。例如，一個翻譯工具可能支援英語到西班牙語的語言對，以及西班牙語到義大利語的語言對，但不支援英語到義大利語。

例如，將 "Hello world" 從英語翻譯成法語可以通過替換完成——"Bonjour" 替換 "Hello"，"le monde" 替換 "world"，最終得到正確的翻譯 "Bonjour le monde"。

當不同語言使用不同的方式表達相同的意思時，替換方法就不起作用了。例如，英語句子 "My name is Jim" 翻譯成法語是 "Je m'appelle Jim"，字面意思是 "我叫自己 Jim"。"Je" 是法語中的 "我"，"moi" 是 "我自己"，但由於動詞以元音開頭，會與動詞結合成 "m'"，"appelle" 是 "叫"，而 "Jim" 不翻譯，因為它是名字，而不是可以翻譯的單詞。單詞順序也成為問題——簡單替換 "Je m'appelle Jim" 會變成 "I myself call Jim"，與英語的單詞順序不同。

> 💁 有些單詞永遠不會被翻譯——我的名字是 Jim，無論使用哪種語言介紹我。當翻譯到使用不同字母或不同聲音的語言時，單詞可以被*音譯*，即選擇適當的字母或字符，使其聽起來與原單詞相同。

成語也是翻譯的一個難題。這些是具有特定理解意義的短語，其含義與單詞的直接解釋不同。例如，在英語中，成語 "I've got ants in my pants" 並不是真的指衣服裡有螞蟻，而是指坐立不安。如果你將其翻譯成德語，可能會讓聽者感到困惑，因為德語版本是 "I have bumble bees in the bottom"。

> 💁 不同的地區會增加不同的複雜性。以成語 "ants in your pants" 為例，在美式英語中 "pants" 指外衣，而在英式英語中，"pants" 指內衣。

✅ 如果你會多種語言，想想一些無法直接翻譯的短語。

機器翻譯系統依賴於大型規則數據庫，描述如何翻譯特定短語和成語，並使用統計方法從可能的選項中選擇適當的翻譯。這些統計方法使用由人類翻譯成多種語言的大型數據庫，來選擇最可能的翻譯，這種技術被稱為*統計機器翻譯*。其中一些使用語言的中間表示，允許一種語言翻譯成中間表示，再從中間表示翻譯成另一種語言。這樣，添加更多語言只需翻譯到和從中間表示，而不是翻譯到和從所有其他語言。

### 神經翻譯

神經翻譯利用 AI 的力量進行翻譯，通常使用一個模型翻譯整個句子。這些模型基於由人類翻譯的大型數據集進行訓練，例如網頁、書籍和聯合國文件。

神經翻譯模型通常比機器翻譯模型更小，因為不需要大型短語和成語數據庫。現代 AI 翻譯服務通常混合多種技術，結合統計機器翻譯和神經翻譯。

任何語言對之間都沒有 1:1 的翻譯。不同的翻譯模型會根據訓練模型的數據產生略有不同的結果。翻譯並不總是對稱的——即如果你將一個句子從一種語言翻譯成另一種語言，再翻譯回原語言，可能會得到略有不同的句子。

✅ 試試不同的線上翻譯工具，例如 [Bing 翻譯](https://www.bing.com/translator)、[Google 翻譯](https://translate.google.com) 或 Apple 翻譯應用程式。比較幾個句子的翻譯版本。也可以嘗試在一個工具中翻譯，再在另一個工具中翻譯回來。

## 翻譯服務

有許多 AI 服務可以從你的應用程式中用來翻譯語音和文字。

### 認知服務語音服務

![語音服務標誌](../../../../../translated_images/tw/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.png)

你在過去幾節課中使用的語音服務具有語音識別的翻譯功能。當你識別語音時，可以要求不僅提供相同語言的文字，還可以提供其他語言的文字。

> 💁 這僅適用於語音 SDK，REST API 不內建翻譯功能。

### 認知服務翻譯服務

![翻譯服務標誌](../../../../../translated_images/tw/azure-translator-logo.c6ed3a4a433edfd2f11577eca105412c50b8396b194cbbd730723dd1d0793bcd.png)

翻譯服務是一個專門的翻譯服務，可以將文字從一種語言翻譯成一種或多種目標語言。除了翻譯，它還支援許多額外功能，包括屏蔽不雅詞語。它還允許你為特定單詞或句子提供特定翻譯，以處理你不希望翻譯的術語或具有特定知名翻譯的術語。

例如，當翻譯句子 "I have a Raspberry Pi"（指的是單板電腦）到另一種語言如法語時，你可能希望保留 "Raspberry Pi" 的名稱不變，而不是翻譯它，得到 "J’ai un Raspberry Pi" 而不是 "J’ai une pi aux framboises"。

## 建立翻譯資源

在本課程中，你需要一個翻譯資源。你將使用 REST API 來翻譯文字。

### 任務 - 建立翻譯資源

1. 從你的終端或命令提示符執行以下命令，在你的 `smart-timer` 資源群組中建立翻譯資源。

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    將 `<location>` 替換為你建立資源群組時使用的位置。

1. 獲取翻譯服務的金鑰：

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    複製其中一個金鑰。

## 透過翻譯在應用程式中支援多語言

在理想情況下，你的整個應用程式應該能夠理解盡可能多的不同語言，從語音識別到語言理解，再到語音回應。這需要大量工作，因此翻譯服務可以加速應用程式的交付時間。

![智慧計時器架構：將日語翻譯成英語，使用英語處理，再翻譯回日語](../../../../../translated_images/tw/translated-smart-timer.08ac20057fdc5c37.webp)

假設你正在建立一個智慧計時器，使用英語端到端處理，包括理解英語語音並將其轉換為文字、使用英語進行語言理解、用英語構建回應並以英語語音回應。如果你想添加日語支援，可以先將日語語音翻譯成英語文字，然後保持應用程式的核心部分不變，最後將回應文字翻譯成日語，再用日語語音回應。這樣可以快速添加日語支援，並且你可以稍後擴展到提供完整的端到端日語支援。

> 💁 依賴機器翻譯的缺點是不同語言和文化有不同的表達方式，因此翻譯可能與你期望的表達不符。

機器翻譯還為應用程式和設備提供了翻譯使用者創建內容的可能性。科幻作品中經常出現 "通用翻譯器"，這些設備可以將外星語言翻譯成（通常是）美式英語。如果忽略外星部分，這些設備已經不再是科幻，而是科學事實。已經有應用程式和設備可以實現語音和文字的即時翻譯，結合語音和翻譯服務。

其中一個例子是 [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn) 手機應用程式，以下影片展示了其功能：

[![Microsoft Translator 即時功能展示](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 點擊上方圖片觀看影片

想像一下擁有這樣的設備，尤其是在旅行或與不懂其語言的人互動時。在機場或醫院中使用自動翻譯設備將提供急需的無障礙改進。

✅ 做些研究：是否有任何商業化的翻譯物聯網設備？智慧設備中是否內建翻譯功能？

> 👽 雖然目前沒有真正的通用翻譯器可以讓我們與外星人交流，但 [Microsoft Translator 支援克林貢語](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn)。Qapla’！

## 使用 AI 服務翻譯文字

你可以使用 AI 服務為你的智慧計時器添加翻譯功能。

### 任務 - 使用 AI 服務翻譯文字

按照相關指南，將文字翻譯功能添加到你的物聯網設備：

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [單板電腦 - Raspberry Pi](pi-translate-speech.md)
* [單板電腦 - 虛擬設備](virtual-device-translate-speech.md)

---

## 🚀 挑戰

機器翻譯如何在智慧設備以外的其他物聯網應用程式中受益？思考翻譯如何幫助，不僅是語音，還包括文字。

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## 回顧與自學

* 閱讀更多關於機器翻譯的內容：[機器翻譯 Wikipedia 頁面](https://wikipedia.org/wiki/Machine_translation)
* 閱讀更多關於神經機器翻譯的內容：[神經機器翻譯 Wikipedia 頁面](https://wikipedia.org/wiki/Neural_machine_translation)
* 查看 Microsoft 語音服務支援的語言列表：[語音服務文件中的語言和語音支援](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## 作業

[建立一個通用翻譯器](assignment.md)

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對於因使用此翻譯而引起的任何誤解或誤讀概不負責。