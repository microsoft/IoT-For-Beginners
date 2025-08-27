<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T00:24:13+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "mo"
}
-->
# 語音轉文字 - 虛擬物聯網設備

在本課程的這部分，你將撰寫程式碼，使用語音服務將從麥克風捕捉的語音轉換為文字。

## 將語音轉換為文字

在 Windows、Linux 和 macOS 上，可以使用語音服務的 Python SDK 來監聽你的麥克風，並將檢測到的語音轉換為文字。它會持續監聽，檢測音量水平，並在音量下降（例如在一段語音結束時）時將語音發送進行文字轉換。

### 任務 - 將語音轉換為文字

1. 在你的電腦上建立一個名為 `smart-timer` 的資料夾，並在其中建立一個名為 `app.py` 的單一檔案，以及一個 Python 虛擬環境。

1. 安裝語音服務的 Pip 套件。確保你是在啟動虛擬環境的終端中進行安裝。

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ 如果你遇到以下錯誤：
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > 你需要更新 Pip。使用以下指令更新，然後再次嘗試安裝套件：
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. 在 `app.py` 檔案中加入以下匯入：

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    這些匯入了一些用於語音識別的類別。

1. 加入以下程式碼來宣告一些配置：

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    將 `<key>` 替換為你的語音服務的 API 金鑰。將 `<location>` 替換為你建立語音服務資源時使用的位置。

    將 `<language>` 替換為你將使用的語言的地區名稱，例如 `en-GB` 表示英語，或 `zn-HK` 表示粵語。你可以在 [Microsoft Docs 的語言和語音支持文件](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) 中找到支持的語言及其地區名稱列表。

    此配置將用於建立一個 `SpeechConfig` 物件，用來配置語音服務。

1. 加入以下程式碼來建立語音識別器：

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. 語音識別器在背景執行緒上運行，監聽音頻並將其中的語音轉換為文字。你可以使用回調函數來獲取文字——定義一個函數並傳遞給識別器。每次檢測到語音時，回調函數都會被調用。加入以下程式碼來定義回調函數，並將此回調函數傳遞給識別器，同時定義一個函數來處理文字，將其輸出到控制台：

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. 識別器只有在你明確啟動時才會開始監聽。加入以下程式碼來啟動識別。這會在背景執行，因此你的應用程式還需要一個無限迴圈，通過休眠來保持應用程式運行。

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. 執行此應用程式。對著你的麥克風說話，轉換為文字的音頻將輸出到控制台。

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    嘗試不同類型的句子，以及一些詞音相同但意思不同的句子。例如，如果你使用英語，說「I want to buy two bananas and an apple too」，並注意它如何根據詞的上下文正確使用 to、two 和 too，而不僅僅是根據它的發音。

> 💁 你可以在 [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) 資料夾中找到這段程式碼。

😀 你的語音轉文字程式成功了！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。