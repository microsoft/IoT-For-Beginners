<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c16de27b0074abe81d6a8bad5e5b1a6b",
  "translation_date": "2025-08-26T23:55:36+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/README.md",
  "language_code": "mo"
}
-->
# 支援多語言

![本課程的手繪筆記概述](../../../../../translated_images/mo/lesson-24.4246968ed058510ab275052e87ef9aa89c7b2f938915d103c605c04dc6cd5bb7.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大版本。

這段影片概述了 Azure 語音服務，涵蓋了前幾課中的語音轉文字和文字轉語音功能，以及本課程中討論的語音翻譯主題：

[![使用少量 Python 程式碼進行語音識別（Microsoft Build 2020）](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 點擊上方圖片觀看影片

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## 簡介

在過去的三節課中，你學習了如何將語音轉換為文字、理解語言以及將文字轉換為語音，這些功能都由人工智慧提供支持。人工智慧還可以協助人類溝通的另一個領域——語言翻譯，例如將英文翻譯成法文。

在本課程中，你將學習如何使用人工智慧進行文字翻譯，使你的智慧計時器能夠與多語言使用者互動。

本課程將涵蓋以下內容：

* [翻譯文字](../../../../../6-consumer/lessons/4-multiple-language-support)
* [翻譯服務](../../../../../6-consumer/lessons/4-multiple-language-support)
* [建立翻譯資源](../../../../../6-consumer/lessons/4-multiple-language-support)
* [透過翻譯支援應用程式中的多語言](../../../../../6-consumer/lessons/4-multiple-language-support)
* [使用人工智慧服務翻譯文字](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 這是本專案的最後一課，因此在完成本課程和作業後，別忘了清理你的雲端服務。你需要這些服務來完成作業，因此請確保先完成作業。
>
> 如有需要，請參考[專案清理指南](../../../clean-up.md)以獲取相關指示。

## 翻譯文字

文字翻譯是一個已經研究了超過 70 年的計算機科學問題，直到最近，得益於人工智慧和計算能力的進步，才接近解決，並達到幾乎與人類翻譯員相媲美的水平。

> 💁 其起源可以追溯到更早的時期，例如 9 世紀的阿拉伯密碼學家 [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi)，他開發了語言翻譯的技術。

### 機器翻譯

文字翻譯最初是一種被稱為機器翻譯（Machine Translation, MT）的技術，可以在不同語言對之間進行翻譯。機器翻譯的工作原理是將一種語言中的單詞替換為另一種語言中的單詞，並添加技術來選擇正確的翻譯方式，以處理當簡單的逐字翻譯不合理時的情況。

> 🎓 當翻譯工具支援在一種語言和另一種語言之間進行翻譯時，這些被稱為「語言對」（language pairs）。不同的工具支援不同的語言對，並且可能不完整。例如，一個翻譯工具可能支援英文到西班牙文的語言對，以及西班牙文到義大利文的語言對，但不支援英文到義大利文。

例如，將「Hello world」從英文翻譯成法文可以通過替換完成——「Bonjour」替換「Hello」，「le monde」替換「world」，最終得到正確的翻譯「Bonjour le monde」。

然而，替換法在不同語言使用不同表達方式時就不適用了。例如，英文句子「My name is Jim」翻譯成法文是「Je m'appelle Jim」，字面意思是「我叫自己 Jim」。其中「Je」是法文的「我」，「moi」是「我自己」，但由於動詞以元音開頭，會與動詞結合成「m'」，「appelle」是「叫」，而「Jim」作為名字不會被翻譯。詞序也會成為問題——簡單替換「Je m'appelle Jim」會變成「I myself call Jim」，詞序與英文不同。

> 💁 有些詞永遠不會被翻譯——我的名字是 Jim，無論使用哪種語言介紹自己都是如此。當翻譯成使用不同字母或不同聲音的語言時，這些詞可能會被「音譯」，即選擇適當的字母或字符，使其聽起來與原詞相同。

成語也是翻譯中的一個難題。成語是指具有特定理解意義的短語，其意義與字面解釋不同。例如，英文成語「I've got ants in my pants」並不是真的指衣服裡有螞蟻，而是指坐立不安。如果將其翻譯成德文，可能會讓聽者感到困惑，因為德文版本是「I have bumble bees in the bottom」。

> 💁 不同的地區會增加不同的複雜性。例如在美式英文中，「pants」指外衣，而在英式英文中，「pants」指內衣。

✅ 如果你會多種語言，想想有哪些短語無法直接翻譯。

機器翻譯系統依賴於大型規則數據庫，這些規則描述了如何翻譯特定短語和成語，並結合統計方法從可能的選項中選擇最合適的翻譯。這些統計方法使用由人類翻譯成多種語言的大型數據庫，來選擇最可能的翻譯，這種技術被稱為「統計機器翻譯」（statistical machine translation）。其中一些系統使用語言的中間表示，允許一種語言翻譯成中間表示，再從中間表示翻譯成另一種語言。這樣，添加更多語言只需翻譯到中間表示和從中間表示翻譯，而不需要翻譯到所有其他語言。

### 神經翻譯

神經翻譯利用人工智慧的力量進行翻譯，通常使用一個模型翻譯整個句子。這些模型基於由人類翻譯的大型數據集進行訓練，例如網頁、書籍和聯合國文件。

神經翻譯模型通常比機器翻譯模型更小，因為它們不需要大型短語和成語數據庫。現代人工智慧翻譯服務通常混合多種技術，結合統計機器翻譯和神經翻譯。

任何語言對之間都不存在 1:1 的翻譯。不同的翻譯模型會根據訓練數據的不同產生略有差異的結果。翻譯並不總是對稱的——即如果你將一個句子從一種語言翻譯成另一種語言，再翻譯回原語言，可能會得到略有不同的句子。

✅ 試試不同的線上翻譯工具，例如 [Bing 翻譯](https://www.bing.com/translator)、[Google 翻譯](https://translate.google.com) 或 Apple 翻譯應用程式。比較幾個句子的翻譯版本。也可以嘗試在一個工具中翻譯，再在另一個工具中翻譯回來。

## 翻譯服務

有許多人工智慧服務可以從你的應用程式中使用，用於翻譯語音和文字。

### 認知服務語音服務

![語音服務標誌](../../../../../translated_images/mo/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.png)

你在過去幾課中使用的語音服務具有語音識別的翻譯功能。當你識別語音時，可以要求不僅提供相同語言的文字，還可以提供其他語言的文字。

> 💁 這僅適用於語音 SDK，REST API 不內建翻譯功能。

### 認知服務翻譯服務

![翻譯服務標誌](../../../../../translated_images/mo/azure-translator-logo.c6ed3a4a433edfd2f11577eca105412c50b8396b194cbbd730723dd1d0793bcd.png)

翻譯服務是一個專門的翻譯服務，可以將文字從一種語言翻譯成一種或多種目標語言。除了翻譯，它還支援許多額外功能，包括屏蔽不雅詞語。它還允許你為特定單詞或句子提供特定翻譯，以處理不希望翻譯的術語或具有特定知名翻譯的術語。

例如，當翻譯句子「I have a Raspberry Pi」（指的是單板電腦）到另一種語言如法文時，你可能希望保留「Raspberry Pi」的名稱不被翻譯，得到「J’ai un Raspberry Pi」而不是「J’ai une pi aux framboises」。

## 建立翻譯資源

在本課程中，你需要一個翻譯資源。你將使用 REST API 來翻譯文字。

### 任務 - 建立翻譯資源

1. 在終端或命令提示符中執行以下命令，在你的 `smart-timer` 資源群組中建立翻譯資源。

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

## 透過翻譯支援應用程式中的多語言

在理想情況下，整個應用程式應該能理解盡可能多的不同語言，從語音識別到語言理解，再到語音回應。這需要大量工作，而翻譯服務可以加快應用程式的交付時間。

![智慧計時器架構：將日文翻譯成英文，使用英文處理，再翻譯回日文](../../../../../translated_images/mo/translated-smart-timer.08ac20057fdc5c37.webp)

假設你正在建立一個智慧計時器，使用英文進行端到端處理，包括識別英文語音並轉換為文字、使用英文進行語言理解、用英文構建回應並以英文語音回應。如果你想添加日文支援，可以先將日文語音翻譯成英文文字，然後保持應用程式的核心部分不變，最後將回應文字翻譯成日文並以日文語音回應。這樣可以快速添加日文支援，並且你可以稍後擴展到提供完整的端到端日文支援。

> 💁 依賴機器翻譯的缺點是，不同語言和文化有不同的表達方式，因此翻譯可能無法匹配你期望的表達。

機器翻譯還為應用程式和設備提供了翻譯使用者創建內容的可能性。科幻作品中經常出現「通用翻譯器」，這些設備可以將外星語言翻譯成（通常是）美式英文。這些設備已不再是科幻，而是科學事實，當然不包括外星部分。目前已經有應用程式和設備可以實現語音和文字的即時翻譯，結合語音和翻譯服務。

其中一個例子是 [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn) 手機應用程式，以下影片展示了其功能：

[![Microsoft Translator 即時功能展示](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 點擊上方圖片觀看影片

想像一下擁有這樣的設備，尤其是在旅行或與不懂其語言的人互動時。在機場或醫院中使用自動翻譯設備將提供急需的無障礙改進。

✅ 做些研究：是否有任何商業化的翻譯物聯網設備？智慧設備中是否內建翻譯功能？

> 👽 雖然目前還沒有真正的通用翻譯器可以讓我們與外星人交流，但 [Microsoft Translator 支援克林貢語](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn)。Qapla’！

## 使用人工智慧服務翻譯文字

你可以使用人工智慧服務為你的智慧計時器添加翻譯功能。

### 任務 - 使用人工智慧服務翻譯文字

按照相關指南，將文字翻譯功能添加到你的物聯網設備：

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [單板電腦 - Raspberry Pi](pi-translate-speech.md)
* [單板電腦 - 虛擬設備](virtual-device-translate-speech.md)

---

## 🚀 挑戰

機器翻譯如何能夠幫助智慧設備以外的其他物聯網應用程式？想想翻譯如何幫助，不僅是語音，還包括文字。

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## 回顧與自學

* 在 [Wikipedia 的機器翻譯頁面](https://wikipedia.org/wiki/Machine_translation)上閱讀更多關於機器翻譯的內容
* 在 [Wikipedia 的神經機器翻譯頁面](https://wikipedia.org/wiki/Neural_machine_translation)上閱讀更多關於神經機器翻譯的內容
* 查看 Microsoft 語音服務支援的語言列表，請參考 [Microsoft Docs 上的語音服務語言和語音支援文件](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## 作業

[建立一個通用翻譯器](assignment.md)

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。