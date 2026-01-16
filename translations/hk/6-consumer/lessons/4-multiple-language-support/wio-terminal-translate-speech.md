<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-26T15:20:08+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "hk"
}
-->
# 翻譯語音 - Wio Terminal

在本課程的這部分，你將撰寫程式碼，使用翻譯服務來翻譯文字。

## 使用翻譯服務將文字轉換為語音

語音服務的 REST API 不支援直接翻譯，但你可以使用翻譯服務將語音轉文字服務生成的文字，以及語音回應的文字進行翻譯。此服務提供 REST API 可用於翻譯文字，但為了更方便使用，將其包裝在函數應用程式中的另一個 HTTP 觸發器中。

### 任務 - 建立無伺服器函數來翻譯文字

1. 在 VS Code 中開啟你的 `smart-timer-trigger` 專案，並確保虛擬環境已啟動。如果未啟動，請終止並重新建立終端機。

1. 開啟 `local.settings.json` 檔案，並新增翻譯 API 金鑰和位置的設定：

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    將 `<key>` 替換為你的翻譯服務資源的 API 金鑰。將 `<location>` 替換為你建立翻譯服務資源時使用的位置。

1. 在函數應用程式專案的根目錄中，使用以下指令新增一個名為 `translate-text` 的 HTTP 觸發器：

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    這將建立一個名為 `translate-text` 的 HTTP 觸發器。

1. 將 `translate-text` 資料夾中的 `__init__.py` 檔案內容替換為以下內容：

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    此程式碼從 HTTP 請求中提取文字和語言，然後向翻譯 REST API 發出請求，將語言作為 URL 的參數，並將要翻譯的文字作為主體。最後返回翻譯結果。

1. 在本地執行你的函數應用程式。你可以使用像 curl 這樣的工具來呼叫它，就像測試 `text-to-timer` HTTP 觸發器一樣。確保以 JSON 主體的形式傳遞要翻譯的文字和語言：

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    此範例將 *Définir une minuterie de 30 secondes* 從法語翻譯為美式英語。它將返回 *Set a 30-second timer*。

> 💁 你可以在 [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) 資料夾中找到此程式碼。

### 任務 - 使用翻譯函數來翻譯文字

1. 如果尚未開啟，請在 VS Code 中開啟 `smart-timer` 專案。

1. 你的智慧計時器將設定兩種語言——用於訓練 LUIS 的伺服器語言（同時也用於構建與使用者對話的訊息），以及使用者說的語言。在 `config.h` 標頭檔案中，將 `LANGUAGE` 常數更新為使用者將使用的語言，並新增一個名為 `SERVER_LANGUAGE` 的常數，用於訓練 LUIS 的語言：

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    將 `<user language>` 替換為你將使用的語言的區域名稱，例如法語為 `fr-FR`，或粵語為 `zn-HK`。

    將 `<server language>` 替換為用於訓練 LUIS 的語言的區域名稱。

    你可以在 [Microsoft Docs 的語言和語音支援文件](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) 中找到支援的語言及其區域名稱的清單。

    > 💁 如果你不會多種語言，可以使用像 [Bing 翻譯](https://www.bing.com/translator) 或 [Google 翻譯](https://translate.google.com) 這樣的服務，將你的首選語言翻譯成其他語言。這些服務還可以播放翻譯後的文字音頻。
    >
    > 例如，如果你用英語訓練 LUIS，但希望使用法語作為使用者語言，你可以使用 Bing 翻譯將 "set a 2 minute and 27 second timer" 從英語翻譯成法語，然後使用 **聆聽翻譯** 按鈕將翻譯語音說入麥克風。
    >
    > ![Bing 翻譯上的聆聽翻譯按鈕](../../../../../translated_images/hk/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. 在 `SPEECH_LOCATION` 下方新增翻譯 API 金鑰和位置：

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    將 `<KEY>` 替換為你的翻譯服務資源的 API 金鑰。將 `<LOCATION>` 替換為你建立翻譯服務資源時使用的位置。

1. 在 `VOICE_URL` 下方新增翻譯觸發器的 URL：

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    將 `<URL>` 替換為函數應用程式中 `translate-text` HTTP 觸發器的 URL。這將與 `TEXT_TO_TIMER_FUNCTION_URL` 的值相同，但函數名稱為 `translate-text` 而非 `text-to-timer`。

1. 在 `src` 資料夾中新增一個名為 `text_translator.h` 的檔案。

1. 此新的 `text_translator.h` 標頭檔案將包含一個用於翻譯文字的類別。在此檔案中新增以下內容以宣告此類別：

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    這宣告了 `TextTranslator` 類別，以及此類別的一個實例。該類別有一個用於 WiFi 客戶端的欄位。

1. 在此類別的 `public` 區域中，新增一個用於翻譯文字的方法：

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    此方法接收要翻譯的來源語言和目標語言。在處理語音時，語音將從使用者語言翻譯為 LUIS 伺服器語言，而在提供回應時，則從 LUIS 伺服器語言翻譯為使用者語言。

1. 在此方法中，新增程式碼以構建包含要翻譯文字和語言的 JSON 主體：

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. 在此下方，新增以下程式碼以將主體發送到無伺服器函數應用程式：

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. 接下來，新增程式碼以獲取回應：

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. 最後，新增程式碼以關閉連線並返回翻譯後的文字：

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### 任務 - 翻譯識別的語音和回應

1. 開啟 `main.cpp` 檔案。

1. 在檔案頂部新增一個包含 `TextTranslator` 類別標頭檔案的指令：

    ```cpp
    #include "text_translator.h"
    ```

1. 設定計時器或計時器到期時說出的文字需要被翻譯。為此，在 `say` 函數的第一行新增以下內容：

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    這將把文字翻譯成使用者語言。

1. 在 `processAudio` 函數中，透過 `String text = speechToText.convertSpeechToText();` 呼叫從捕獲的音頻中檢索文字。在此呼叫之後，翻譯文字：

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    這將把文字從使用者語言翻譯成伺服器使用的語言。

1. 建置此程式碼，將其上傳到你的 Wio Terminal，並透過序列監視器進行測試。一旦你在序列監視器中看到 `Ready`，按下 C 按鈕（左側靠近電源開關的按鈕），然後說話。確保你的函數應用程式正在執行，並用使用者語言請求計時器，可以是你自己說該語言，或者使用翻譯應用程式。

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 你可以在 [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) 資料夾中找到此程式碼。

😀 你的多語言計時器程式大功告成！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。