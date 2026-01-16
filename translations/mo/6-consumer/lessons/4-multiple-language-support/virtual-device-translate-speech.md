<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-26T23:59:00+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "mo"
}
-->
# 翻譯語音 - 虛擬物聯網設備

在本課程的這部分，您將撰寫程式碼，使用語音服務將語音轉換為文字時進行翻譯，然後使用翻譯服務將文字翻譯後生成語音回應。

## 使用語音服務翻譯語音

語音服務不僅可以將語音轉換為相同語言的文字，還可以將輸出翻譯為其他語言。

### 任務 - 使用語音服務翻譯語音

1. 在 VS Code 中打開 `smart-timer` 專案，並確保虛擬環境已在終端中載入。

1. 在現有的匯入語句下方新增以下匯入語句：

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    這將匯入用於翻譯語音的類別，以及稍後在本課程中用於呼叫翻譯服務的 `requests` 函式庫。

1. 您的智慧計時器將設定兩種語言——用於訓練 LUIS 的伺服器語言（同樣的語言也用於構建與使用者對話的訊息），以及使用者所說的語言。更新 `language` 變數為使用者將使用的語言，並新增一個名為 `server_language` 的變數，用於設定訓練 LUIS 的語言：

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    將 `<user language>` 替換為您將使用的語言的區域名稱，例如法語為 `fr-FR`，或粵語為 `zn-HK`。

    將 `<server language>` 替換為用於訓練 LUIS 的語言的區域名稱。

    您可以在 [Microsoft Docs 上的語言和語音支援文件](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) 中找到支援的語言及其區域名稱的列表。

    > 💁 如果您不會多種語言，可以使用像 [Bing 翻譯](https://www.bing.com/translator) 或 [Google 翻譯](https://translate.google.com) 這樣的服務，將您的首選語言翻譯為您選擇的語言。這些服務還可以播放翻譯後文字的音頻。請注意，語音識別器可能會忽略來自您設備的一些音頻輸出，因此您可能需要使用額外的設備來播放翻譯後的文字。
    >
    > 例如，如果您用英語訓練 LUIS，但希望使用法語作為使用者語言，您可以使用 Bing 翻譯將像 "set a 2 minute and 27 second timer" 這樣的句子從英語翻譯為法語，然後使用 **聆聽翻譯** 按鈕將翻譯內容說入您的麥克風。
    >
    > ![Bing 翻譯上的聆聽翻譯按鈕](../../../../../translated_images/mo/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. 用以下內容替換 `recognizer_config` 和 `recognizer` 的宣告：

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    這會創建一個翻譯配置，用於識別使用者語言的語音，並生成使用者語言和伺服器語言的翻譯。然後使用此配置創建一個翻譯識別器——一個可以將語音識別的輸出翻譯為多種語言的語音識別器。

    > 💁 必須在 `target_languages` 中指定原始語言，否則您將無法獲得任何翻譯。

1. 更新 `recognized` 函數，將函數的全部內容替換為以下內容：

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    此程式碼檢查是否因為語音被翻譯而觸發了識別事件（此事件也可能在其他情況下觸發，例如語音被識別但未翻譯）。如果語音被翻譯，它會在 `args.result.translations` 字典中找到與伺服器語言匹配的翻譯。

    `args.result.translations` 字典的鍵是區域設置的語言部分，而不是整個設置。例如，如果您請求將法語翻譯為 `fr-FR`，字典中將包含一個 `fr` 的條目，而不是 `fr-FR`。

    翻譯後的文字將被發送到 IoT Hub。

1. 執行此程式碼以測試翻譯功能。確保您的函數應用程式正在運行，並用使用者語言請求計時器，可以是您自己說該語言，也可以使用翻譯應用程式。

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## 使用翻譯服務翻譯文字

語音服務不支援將翻譯後的文字轉回語音，您可以使用翻譯服務將文字翻譯。此服務提供一個 REST API，您可以用來翻譯文字。

### 任務 - 使用翻譯資源翻譯文字

1. 在 `speech_api_key` 下方新增翻譯 API 金鑰：

    ```python
    translator_api_key = '<key>'
    ```

    將 `<key>` 替換為您的翻譯服務資源的 API 金鑰。

1. 在 `say` 函數上方，定義一個 `translate_text` 函數，用於將文字從伺服器語言翻譯為使用者語言：

    ```python
    def translate_text(text):
    ```

1. 在此函數內，定義 REST API 呼叫的 URL 和標頭：

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    此 API 的 URL 並非特定於位置，而是將位置作為標頭傳遞。API 金鑰直接使用，因此與語音服務不同，無需從令牌發行 API 獲取訪問令牌。

1. 在此下方定義呼叫的參數和主體：

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` 定義了傳遞給 API 呼叫的參數，指定翻譯的來源語言和目標語言。此呼叫將把 `from` 語言的文字翻譯為 `to` 語言。

    `body` 包含要翻譯的文字。這是一個陣列，因為可以在一次呼叫中翻譯多段文字。

1. 呼叫 REST API 並獲取回應：

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    返回的回應是一個 JSON 陣列，其中包含一個項目，該項目包含翻譯結果。此項目有一個陣列，包含所有在主體中傳遞的項目的翻譯。

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. 返回陣列中第一個項目中第一個翻譯的 `text` 屬性：

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. 更新 `say` 函數，在生成 SSML 之前翻譯要說的文字：

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    此程式碼還會將原始文字和翻譯後的文字打印到控制台。

1. 執行您的程式碼。確保您的函數應用程式正在運行，並用使用者語言請求計時器，可以是您自己說該語言，也可以使用翻譯應用程式。

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 由於不同語言表達方式的差異，您可能會得到與您提供給 LUIS 的範例略有不同的翻譯。如果是這種情況，請向 LUIS 添加更多範例，重新訓練並重新發布模型。

> 💁 您可以在 [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) 資料夾中找到此程式碼。

😀 您的多語言計時器程式大獲成功！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。