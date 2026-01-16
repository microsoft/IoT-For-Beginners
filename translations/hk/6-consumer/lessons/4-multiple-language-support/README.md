<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c16de27b0074abe81d6a8bad5e5b1a6b",
  "translation_date": "2025-08-26T15:21:00+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/README.md",
  "language_code": "hk"
}
-->
# 支援多語言

![本課程的手繪筆記概覽](../../../../../translated_images/hk/lesson-24.4246968ed058510ab275052e87ef9aa89c7b2f938915d103c605c04dc6cd5bb7.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大版本。

這段影片概述了 Azure 語音服務，涵蓋了前幾課的語音轉文字和文字轉語音功能，以及本課將探討的語音翻譯主題：

[![使用少量 Python 程式碼進行語音識別（來自 Microsoft Build 2020）](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 點擊上方圖片觀看影片

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## 簡介

在過去的三節課中，你學習了如何將語音轉換為文字、語言理解，以及將文字轉換為語音，這些功能都由 AI 提供支持。AI 還可以幫助人類溝通的另一個領域是語言翻譯——將一種語言轉換為另一種語言，例如從英語翻譯成法語。

在本課中，你將學習如何使用 AI 進行文字翻譯，讓你的智慧計時器能夠與多語言用戶互動。

本課將涵蓋以下內容：

* [翻譯文字](../../../../../6-consumer/lessons/4-multiple-language-support)
* [翻譯服務](../../../../../6-consumer/lessons/4-multiple-language-support)
* [建立翻譯資源](../../../../../6-consumer/lessons/4-multiple-language-support)
* [透過翻譯支援應用程式的多語言功能](../../../../../6-consumer/lessons/4-multiple-language-support)
* [使用 AI 服務翻譯文字](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 這是本專案的最後一課，因此在完成本課和作業後，別忘了清理你的雲端服務。你需要這些服務來完成作業，所以請確保先完成作業。
>
> 如有需要，請參考[清理專案指南](../../../clean-up.md)以獲取相關指示。

## 翻譯文字

文字翻譯是一個已經研究了超過 70 年的計算機科學問題，直到最近，隨著 AI 和計算能力的進步，才接近解決，達到幾乎與人類翻譯員相媲美的水準。

> 💁 其起源可以追溯到更早的時代，例如 9 世紀的阿拉伯密碼學家 [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi)，他開發了語言翻譯的技術。

### 機器翻譯

文字翻譯最初是一種稱為機器翻譯（Machine Translation, MT）的技術，可以在不同語言對之間進行翻譯。機器翻譯的原理是將一種語言中的單詞替換為另一種語言中的單詞，並加入一些技術來選擇正確的短語或句子部分的翻譯方式，避免逐字翻譯時出現不合邏輯的情況。

> 🎓 當翻譯工具支援在兩種語言之間進行翻譯時，這些被稱為「語言對」（language pairs）。不同的工具支援的語言對可能不完全。例如，一個翻譯工具可能支援英語到西班牙語的語言對，以及西班牙語到義大利語的語言對，但不支援英語到義大利語。

例如，將 "Hello world" 從英語翻譯成法語可以通過替換完成——"Hello" 替換為 "Bonjour"，"world" 替換為 "le monde"，最終得到正確的翻譯 "Bonjour le monde"。

但替換法在某些情況下並不適用，因為不同語言表達相同意思的方式可能不同。例如，英語句子 "My name is Jim" 翻譯成法語是 "Je m'appelle Jim"，字面意思是「我叫自己 Jim」。"Je" 是法語中的「我」，"moi" 是「我自己」，但由於動詞以元音開頭，會與動詞結合成 "m'"，"appelle" 是「叫」，而 "Jim" 作為名字不會被翻譯。詞序也會成為問題——如果簡單地將 "Je m'appelle Jim" 替換為 "I myself call Jim"，詞序就與英語不同。

> 💁 有些詞永遠不會被翻譯——無論使用哪種語言介紹自己，我的名字始終是 Jim。當翻譯成使用不同字母表或不同發音的語言時，這些詞可能會被「音譯」，即選擇能發出相同聲音的字母或字符，使其聽起來與原詞相同。

成語也是翻譯中的一大難題。成語是指那些字面意思與實際含義不同的短語。例如，英語中的成語 "I've got ants in my pants" 並不是真的指褲子裡有螞蟻，而是指坐立不安。如果將其翻譯成德語，可能會讓聽者感到困惑，因為德語的表達是 "I have bumble bees in the bottom"。

> 💁 不同地區的語言會增加翻譯的複雜性。例如，在美式英語中，"pants" 指的是外褲，而在英式英語中，"pants" 指的是內褲。

✅ 如果你會多種語言，試著想一些無法直接翻譯的短語。

機器翻譯系統依賴於大量的規則數據庫，這些規則描述了如何翻譯特定短語和成語，並結合統計方法從可能的選項中選擇最合適的翻譯。這些統計方法使用由人類翻譯成多種語言的大型數據庫，來選擇最可能的翻譯，這種技術被稱為「統計機器翻譯」（statistical machine translation）。其中一些系統使用中間語言表示法，允許一種語言先翻譯成中間語言，再從中間語言翻譯成另一種語言。這樣，添加更多語言時，只需翻譯到和從中間語言翻譯，而不需要直接翻譯到所有其他語言。

### 神經翻譯

神經翻譯利用 AI 的強大功能進行翻譯，通常使用一個模型翻譯整個句子。這些模型基於由人類翻譯的大型數據集進行訓練，例如網頁、書籍和聯合國文件。

神經翻譯模型通常比機器翻譯模型更小，因為它們不需要龐大的短語和成語數據庫。現代 AI 翻譯服務通常結合多種技術，將統計機器翻譯和神經翻譯結合使用。

任何語言對之間都不存在 1:1 的翻譯。不同的翻譯模型會根據訓練數據的不同產生略有差異的結果。翻譯並不總是對稱的——即如果將一句話從一種語言翻譯成另一種語言，再翻譯回原語言，可能會得到略有不同的句子。

✅ 試用不同的在線翻譯工具，例如 [Bing 翻譯](https://www.bing.com/translator)、[Google 翻譯](https://translate.google.com) 或 Apple 翻譯應用。比較幾個句子的翻譯版本。也可以嘗試在一個工具中翻譯，再在另一個工具中翻譯回來。

## 翻譯服務

有許多 AI 服務可以用於應用程式中進行語音和文字翻譯。

### 認知服務語音服務

![語音服務標誌](../../../../../translated_images/hk/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.png)

你在過去幾課中使用的語音服務具有語音識別的翻譯功能。當你進行語音識別時，可以請求不僅獲取相同語言的文字，還可以獲取其他語言的翻譯文字。

> 💁 這僅適用於語音 SDK，REST API 不內建翻譯功能。

### 認知服務翻譯服務

![翻譯服務標誌](../../../../../translated_images/hk/azure-translator-logo.c6ed3a4a433edfd2f11577eca105412c50b8396b194cbbd730723dd1d0793bcd.png)

翻譯服務是一個專門的翻譯服務，可以將文字從一種語言翻譯成一種或多種目標語言。除了翻譯，它還支援許多額外功能，例如屏蔽不雅詞語。它還允許你為特定單詞或句子提供特定翻譯，以處理不希望翻譯的術語或具有特定知名翻譯的術語。

例如，當翻譯句子 "I have a Raspberry Pi"（指的是單板電腦）成另一種語言（如法語）時，你可能希望保留 "Raspberry Pi" 的名稱不變，而不是翻譯成其他意思，得到 "J’ai un Raspberry Pi" 而不是 "J’ai une pi aux framboises"。

## 建立翻譯資源

在本課中，你將需要一個翻譯資源。你將使用 REST API 來翻譯文字。

### 任務 - 建立翻譯資源

1. 在終端或命令提示字元中執行以下命令，在你的 `smart-timer` 資源群組中建立一個翻譯資源。

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    將 `<location>` 替換為建立資源群組時使用的位置。

1. 獲取翻譯服務的金鑰：

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    複製其中一個金鑰。

## 透過翻譯支援應用程式的多語言功能

在理想情況下，你的整個應用程式應該能理解盡可能多的語言，從語音識別到語言理解，再到語音回應。這需要大量工作，而翻譯服務可以加速應用程式的交付時間。

![智慧計時器架構：將日語翻譯成英語，處理後再翻譯回日語](../../../../../translated_images/hk/translated-smart-timer.08ac20057fdc5c37.webp)

假設你正在構建一個智慧計時器，該計時器從頭到尾使用英語，理解英語語音並將其轉換為文字，用英語進行語言理解，生成英語回應，並以英語語音回應。如果你想添加日語支援，可以先將日語語音翻譯成英語文字，然後保持應用程式的核心部分不變，最後將回應文字翻譯成日語，並以日語語音回應。這樣可以快速添加日語支援，並在以後擴展到提供完整的日語端到端支援。

> 💁 依賴機器翻譯的缺點是，不同語言和文化對相同事物的表達方式可能不同，因此翻譯可能無法匹配你期望的表達方式。

機器翻譯還為應用程式和設備提供了翻譯用戶創建內容的可能性。科幻作品中經常出現「通用翻譯器」，這些設備可以將外星語言翻譯成（通常是）美式英語。如果忽略外星部分，這些設備已經不再是科幻，而是科學事實。已經有應用程式和設備可以實現語音和文字的即時翻譯，這些功能結合了語音和翻譯服務。

一個例子是 [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn) 手機應用程式，以下影片展示了其功能：

[![Microsoft Translator 即時功能展示](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 點擊上方圖片觀看影片

想像一下擁有這樣的設備，特別是在旅行或與不懂其語言的人互動時。在機場或醫院中使用自動翻譯設備，將大大提升無障礙性。

✅ 做一些研究：市面上是否有任何翻譯 IoT 設備？智慧設備中是否內建翻譯功能？

> 👽 雖然目前還沒有真正的通用翻譯器可以讓我們與外星人交談，但 [Microsoft Translator 支援克林貢語](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn)。Qapla’！

## 使用 AI 服務翻譯文字

你可以使用 AI 服務為你的智慧計時器添加翻譯功能。

### 任務 - 使用 AI 服務翻譯文字

按照相關指南，將翻譯功能添加到你的 IoT 設備：

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [單板電腦 - Raspberry Pi](pi-translate-speech.md)
* [單板電腦 - 虛擬設備](virtual-device-translate-speech.md)

---

## 🚀 挑戰

機器翻譯如何在智慧設備以外的其他 IoT 應用中發揮作用？想想翻譯如何幫助處理不僅是語音，還包括文字。

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## 回顧與自學

* 閱讀更多關於機器翻譯的內容，請參考 [Wikipedia 上的機器翻譯頁面](https://wikipedia.org/wiki/Machine_translation)
* 閱讀更多關於神經機器翻譯的內容，請參考 [Wikipedia 上的神經機器翻譯頁面](https://wikipedia.org/wiki/Neural_machine_translation)
* 查看 Microsoft 語音服務支援的語言列表，請參考 [Microsoft Docs 上的語音服務語言和語音支援文檔](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## 作業

[構建一個通用翻譯器](assignment.md)

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。