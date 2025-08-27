<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T00:12:00+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "mo"
}
-->
# 設定計時器 - Wio Terminal

在本課程中，您將呼叫無伺服器代碼來理解語音，並根據結果在 Wio Terminal 上設定計時器。

## 設定計時器

從語音轉文字呼叫返回的文字需要傳送到您的無伺服器代碼，透過 LUIS 處理後，獲取計時器的秒數。這個秒數可以用來設定計時器。

微控制器在 Arduino 中並不原生支援多執行緒，因此不像在 Python 或其他高階語言中那樣有標準的計時器類別。相反，您可以使用計時器函式庫，透過在 `loop` 函數中測量經過的時間，並在時間到時呼叫函數來實現。

### 任務 - 傳送文字到無伺服器函數

1. 如果尚未開啟，請在 VS Code 中開啟 `smart-timer` 專案。

1. 開啟 `config.h` 標頭檔案，並新增您的函數應用程式的 URL：

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    將 `<URL>` 替換為您在上一課最後一步中獲取的函數應用程式 URL，指向執行函數應用程式的本機機器的 IP 位址。

1. 在 `src` 資料夾中建立一個名為 `language_understanding.h` 的新檔案。這將用於定義一個類別，將識別的語音傳送到您的函數應用程式，並使用 LUIS 轉換為秒數。

1. 在此檔案的頂部新增以下內容：

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    這包含了一些必要的標頭檔案。

1. 定義一個名為 `LanguageUnderstanding` 的類別，並宣告此類別的一個實例：

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. 要呼叫您的函數應用程式，您需要宣告一個 WiFi 客戶端。在類別的 `private` 區域中新增以下內容：

    ```cpp
    WiFiClient _client;
    ```

1. 在 `public` 區域中，宣告一個名為 `GetTimerDuration` 的方法，用於呼叫函數應用程式：

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. 在 `GetTimerDuration` 方法中，新增以下代碼以構建要傳送到函數應用程式的 JSON：

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    這將傳遞給 `GetTimerDuration` 方法的文字轉換為以下 JSON：

    ```json
    {
        "text" : "<text>"
    }
    ```

    其中 `<text>` 是傳遞給函數的文字。

1. 在此代碼下方，新增以下代碼以呼叫函數應用程式：

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    這會向函數應用程式發送一個 POST 請求，傳遞 JSON 主體並獲取回應代碼。

1. 在此代碼下方新增以下代碼：

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    此代碼檢查回應代碼。如果是 200（成功），則從回應主體中檢索計時器的秒數。否則，將錯誤訊息發送到序列監視器，並將秒數設為 0。

1. 在此方法的結尾新增以下代碼以關閉 HTTP 連線並返回秒數：

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. 在 `main.cpp` 檔案中，包含這個新的標頭檔案：

    ```cpp
    #include "speech_to_text.h"
    ```

1. 在 `processAudio` 函數的結尾，呼叫 `GetTimerDuration` 方法以獲取計時器的秒數：

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    這將從 `SpeechToText` 類別的呼叫中將文字轉換為計時器的秒數。

### 任務 - 設定計時器

這個秒數可以用來設定計時器。

1. 在 `platformio.ini` 檔案中新增以下函式庫依賴項，以新增一個用於設定計時器的函式庫：

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. 在 `main.cpp` 檔案中新增此函式庫的 include 指令：

    ```cpp
    #include <arduino-timer.h>
    ```

1. 在 `processAudio` 函數上方，新增以下代碼：

    ```cpp
    auto timer = timer_create_default();
    ```

    此代碼宣告了一個名為 `timer` 的計時器。

1. 在此代碼下方，新增以下代碼：

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    此 `say` 函數最終將把文字轉換為語音，但目前它只會將傳入的文字寫入序列監視器。

1. 在 `say` 函數下方，新增以下代碼：

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    這是一個回呼函數，當計時器到期時會被呼叫。當計時器到期時，它會傳遞一個訊息。計時器可以重複執行，這可以透過回呼的返回值來控制——此處返回 `false`，表示計時器不再重複執行。

1. 在 `processAudio` 函數的結尾新增以下代碼：

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    此代碼檢查總秒數，如果為 0，則從函數呼叫中返回，這樣就不會設定計時器。然後將總秒數轉換為分鐘和秒。

1. 在此代碼下方，新增以下代碼以建立計時器啟動時的訊息：

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. 在此代碼下方，新增類似的代碼以建立計時器到期時的訊息：

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. 在此代碼之後，說出計時器啟動的訊息：

    ```cpp
    say(begin_message);
    ```

1. 在此函數的結尾，啟動計時器：

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    這會觸發計時器。計時器是以毫秒為單位設定的，因此總秒數乘以 1,000 轉換為毫秒。`timerExpired` 函數作為回呼傳遞，`end_message` 作為參數傳遞給回呼。此回呼僅接受 `void *` 參數，因此字串被適當地轉換。

1. 最後，計時器需要在 `loop` 函數中 *tick*。在 `loop` 函數的結尾新增以下代碼：

    ```cpp
    timer.tick();
    ```

1. 編譯此代碼，將其上傳到您的 Wio Terminal，並透過序列監視器進行測試。一旦您在序列監視器中看到 `Ready`，按下 C 按鈕（左側靠近電源開關的按鈕），然後說話。4 秒的音頻將被捕獲，轉換為文字，然後傳送到您的函數應用程式，並設定一個計時器。確保您的函數應用程式正在本地執行。

    您將看到計時器啟動和結束的時間。

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 您可以在 [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) 資料夾中找到此代碼。

😀 您的計時器程式成功了！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。