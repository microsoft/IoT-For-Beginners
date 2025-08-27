<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-27T00:07:51+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "mo"
}
-->
# 設定計時器 - 虛擬 IoT 硬體與 Raspberry Pi

在本課程的這部分，你將呼叫無伺服器代碼來理解語音，並根據結果在虛擬 IoT 裝置或 Raspberry Pi 上設定計時器。

## 設定計時器

從語音轉文字呼叫返回的文字需要傳送到你的無伺服器代碼，並由 LUIS 處理，返回計時器的秒數。這個秒數可以用來設定計時器。

計時器可以使用 Python 的 `threading.Timer` 類別來設定。這個類別需要一個延遲時間和一個函數，延遲時間過後，該函數會被執行。

### 任務 - 將文字傳送到無伺服器函數

1. 在 VS Code 中打開 `smart-timer` 專案，並確保如果你使用的是虛擬 IoT 裝置，終端機中已載入虛擬環境。

1. 在 `process_text` 函數上方，宣告一個名為 `get_timer_time` 的函數，用來呼叫你建立的 REST 端點：

    ```python
    def get_timer_time(text):
    ```

1. 在此函數中加入以下代碼以定義要呼叫的 URL：

    ```python
    url = '<URL>'
    ```

    將 `<URL>` 替換為你在上一課中建立的 REST 端點的 URL，無論是在你的電腦上還是雲端中。

1. 加入以下代碼，將文字作為 JSON 屬性傳送到呼叫中：

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. 在此之下，從回應的有效負載中檢索 `seconds`，如果呼叫失敗則返回 0：

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    成功的 HTTP 呼叫會返回 200 範圍內的狀態碼，而你的無伺服器代碼在文字被處理並識別為設定計時器意圖時會返回 200。

### 任務 - 在背景執行緒中設定計時器

1. 在檔案頂部加入以下 import 語句以導入 Python 的 threading 庫：

    ```python
    import threading
    ```

1. 在 `process_text` 函數上方，加入一個函數來說出回應。目前這只會寫入到控制台，但在本課程稍後會讓它說出文字。

    ```python
    def say(text):
        print(text)
    ```

1. 在此之下加入一個函數，該函數會由計時器呼叫以宣布計時器完成：

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    此函數接收計時器的分鐘數和秒數，並構建一個句子來宣布計時器完成。它會檢查分鐘數和秒數，並僅在有數值時才包含每個時間單位。例如，如果分鐘數為 0，則只包含秒數。然後將此句子傳送到 `say` 函數。

1. 在此之下，加入以下 `create_timer` 函數以建立計時器：

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    此函數接收命令中傳送的計時器總秒數，並將其轉換為分鐘和秒數。然後使用總秒數建立並啟動計時器物件，傳入 `announce_timer` 函數以及包含分鐘和秒數的列表。當計時器到期時，它會呼叫 `announce_timer` 函數，並將此列表的內容作為參數傳遞——列表中的第一項作為 `minutes` 參數，第二項作為 `seconds` 參數。

1. 在 `create_timer` 函數的結尾，加入一些代碼以構建一個消息，向使用者宣布計時器正在啟動：

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    同樣，這只包含有數值的時間單位。然後將此句子傳送到 `say` 函數。

1. 在 `process_text` 函數的結尾加入以下內容，以從文字中獲取計時器的時間，然後建立計時器：

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    只有當秒數大於 0 時才會建立計時器。

1. 執行應用程式，並確保函數應用程式也在執行。設定一些計時器，輸出將顯示計時器正在設定，並在到期時顯示：

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 你可以在 [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) 或 [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device) 資料夾中找到這段代碼。

😀 你的計時器程式成功了！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。