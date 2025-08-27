<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T00:33:05+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "mo"
}
-->
# 語音轉文字 - Raspberry Pi

在這部分課程中，你將撰寫程式碼，使用語音服務將錄製的音訊轉換為文字。

## 將音訊發送至語音服務

可以使用 REST API 將音訊發送至語音服務。要使用語音服務，首先需要請求一個存取權杖，然後使用該權杖訪問 REST API。這些存取權杖每 10 分鐘會過期，因此你的程式碼應定期請求新的權杖，以確保它們始終是最新的。

### 任務 - 獲取存取權杖

1. 在你的 Raspberry Pi 上打開 `smart-timer` 專案。

1. 刪除 `play_audio` 函數。這已經不再需要，因為你不希望智慧計時器重複你所說的話。

1. 在 `app.py` 檔案的頂部新增以下匯入：

    ```python
    import requests
    ```

1. 在 `while True` 迴圈的上方新增以下程式碼，來宣告語音服務的一些設定：

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    將 `<key>` 替換為你的語音服務資源的 API 金鑰。將 `<location>` 替換為你建立語音服務資源時使用的位置。

    將 `<language>` 替換為你將使用的語言的地區名稱，例如英語使用 `en-GB`，粵語使用 `zn-HK`。你可以在 [Microsoft Docs 的語言與語音支援文件](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) 中找到支援的語言及其地區名稱列表。

1. 在這段程式碼的下方，新增以下函數以獲取存取權杖：

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    這會呼叫一個權杖發放端點，並將 API 金鑰作為標頭傳遞。此呼叫會返回一個存取權杖，可用於呼叫語音服務。

1. 在這段程式碼的下方，宣告一個函數，使用 REST API 將錄製的音訊中的語音轉換為文字：

    ```python
    def convert_speech_to_text(buffer):
    ```

1. 在這個函數內，設定 REST API 的 URL 和標頭：

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    這會使用語音服務資源的位置來構建一個 URL。然後使用 `get_access_token` 函數獲取的存取權杖填充標頭，並加入錄製音訊時使用的取樣率。最後，定義一些參數，這些參數會與 URL 一起傳遞，包含音訊中的語言。

1. 在這段程式碼的下方，新增以下程式碼以呼叫 REST API 並獲取返回的文字：

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    這會呼叫該 URL，並解碼回應中的 JSON 值。回應中的 `RecognitionStatus` 值表示是否成功將語音轉換為文字。如果該值為 `Success`，則函數會返回文字，否則返回空字串。

1. 在 `while True:` 迴圈的上方，定義一個函數來處理語音轉文字服務返回的文字。這個函數目前只會將文字輸出到控制台。

    ```python
    def process_text(text):
        print(text)
    ```

1. 最後，在 `while True` 迴圈中，將 `play_audio` 的呼叫替換為 `convert_speech_to_text` 函數的呼叫，並將文字傳遞給 `process_text` 函數：

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. 執行程式碼。按下按鈕並對著麥克風說話。完成後鬆開按鈕，音訊將被轉換為文字並輸出到控制台。

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    嘗試不同類型的句子，以及一些發音相同但意思不同的句子。例如，如果你使用英語，說「I want to buy two bananas and an apple too」，並注意它如何根據上下文正確使用 to、two 和 too，而不僅僅是根據發音。

> 💁 你可以在 [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) 資料夾中找到這段程式碼。

😀 你的語音轉文字程式成功了！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。