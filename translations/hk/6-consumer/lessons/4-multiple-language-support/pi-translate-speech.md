<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-26T15:22:48+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "hk"
}
-->
# 翻譯語音 - Raspberry Pi

在這部分課程中，你將撰寫程式碼，使用翻譯服務來翻譯文字。

## 使用翻譯服務將文字轉換為語音

語音服務的 REST API 不支援直接翻譯，但你可以使用翻譯服務來翻譯由語音轉文字服務生成的文字，以及語音回應的文字。這個服務提供 REST API，讓你可以用來翻譯文字。

### 任務 - 使用翻譯資源翻譯文字

1. 你的智能計時器將設定兩種語言：用於訓練 LUIS 的伺服器語言（同時也用於生成與使用者對話的訊息），以及使用者所說的語言。更新 `language` 變數為使用者將使用的語言，並新增一個名為 `server_language` 的變數，用於設定訓練 LUIS 的語言：

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    將 `<user language>` 替換為你將使用的語言的地區名稱，例如法語為 `fr-FR`，或粵語為 `zn-HK`。

    將 `<server language>` 替換為用於訓練 LUIS 的語言的地區名稱。

    你可以在 [Microsoft Docs 上的語言和語音支援文件](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) 中找到支援的語言及其地區名稱列表。

    > 💁 如果你不會多種語言，可以使用像 [Bing 翻譯](https://www.bing.com/translator) 或 [Google 翻譯](https://translate.google.com) 這樣的服務，將你的首選語言翻譯成其他語言。這些服務還可以播放翻譯後的文字音頻。
    >
    > 例如，如果你用英文訓練 LUIS，但希望使用法語作為使用者語言，你可以使用 Bing 翻譯將「設置一個 2 分 27 秒的計時器」這樣的句子從英文翻譯成法語，然後使用 **聆聽翻譯** 按鈕，將翻譯後的內容說入麥克風。
    >
    > ![Bing 翻譯上的聆聽翻譯按鈕](../../../../../translated_images/hk/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. 在 `speech_api_key` 下方新增翻譯 API 金鑰：

    ```python
    translator_api_key = '<key>'
    ```

    將 `<key>` 替換為你的翻譯服務資源的 API 金鑰。

1. 在 `say` 函數上方，定義一個 `translate_text` 函數，用於將文字從伺服器語言翻譯成使用者語言：

    ```python
    def translate_text(text, from_language, to_language):
    ```

    此函數會接收來源語言和目標語言作為參數——你的應用程式需要在辨識語音時，將使用者語言轉換為伺服器語言；在提供語音回饋時，則需將伺服器語言轉換為使用者語言。

1. 在此函數內，定義 REST API 呼叫的 URL 和標頭：

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    此 API 的 URL 並非特定於地區，而是將地區作為標頭傳遞。API 金鑰直接使用，因此不像語音服務那樣需要從 Token 發行 API 獲取存取權杖。

1. 在此之下定義呼叫的參數和主體：

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` 定義了傳遞給 API 呼叫的參數，指定來源語言和目標語言。此呼叫會將 `from` 語言的文字翻譯成 `to` 語言。

    `body` 包含要翻譯的文字。這是一個陣列，因為在一次呼叫中可以翻譯多段文字。

1. 呼叫 REST API 並獲取回應：

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    回應是一個 JSON 陣列，其中包含一個項目，該項目包含所有傳遞到主體中的文字的翻譯結果。

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. 從陣列中的第一個項目中返回第一個翻譯的 `text` 屬性：

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. 更新 `while True` 迴圈，將從使用者語言到伺服器語言的文字翻譯加入 `convert_speech_to_text` 呼叫中：

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    此程式碼還會將原始文字和翻譯後的文字輸出到控制台。

1. 更新 `say` 函數，將要說的文字從伺服器語言翻譯成使用者語言：

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    此程式碼還會將原始文字和翻譯後的文字輸出到控制台。

1. 執行你的程式碼。確保你的函數應用程式正在運行，並用使用者語言請求計時器，可以自己說該語言，或者使用翻譯應用程式。

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 由於不同語言表達方式的差異，你可能會得到與你提供給 LUIS 的範例略有不同的翻譯。如果是這種情況，請為 LUIS 添加更多範例，重新訓練並重新發布模型。

> 💁 你可以在 [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) 資料夾中找到這段程式碼。

😀 你的多語言計時器程式大功告成！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。