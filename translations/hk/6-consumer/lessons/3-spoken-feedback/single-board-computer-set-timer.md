<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-26T15:27:47+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "hk"
}
-->
# 設定計時器 - 虛擬 IoT 硬件與 Raspberry Pi

在本課程的這部分，你將調用無伺服器代碼來理解語音，並根據結果在虛擬 IoT 設備或 Raspberry Pi 上設定計時器。

## 設定計時器

從語音轉文字調用返回的文本需要發送到無伺服器代碼，通過 LUIS 處理，獲取計時器的秒數。這個秒數可以用來設定計時器。

可以使用 Python 的 `threading.Timer` 類來設定計時器。這個類需要一個延遲時間和一個函數，延遲時間過後，該函數將被執行。

### 任務 - 將文本發送到無伺服器函數

1. 在 VS Code 中打開 `smart-timer` 項目，並確保如果你使用的是虛擬 IoT 設備，終端中已加載虛擬環境。

1. 在 `process_text` 函數上方，聲明一個名為 `get_timer_time` 的函數，用於調用你創建的 REST 端點：

    ```python
    def get_timer_time(text):
    ```

1. 在此函數中添加以下代碼來定義要調用的 URL：

    ```python
    url = '<URL>'
    ```

    將 `<URL>` 替換為你在上一課中構建的 REST 端點的 URL，可以是你電腦上的本地 URL 或雲端的 URL。

1. 添加以下代碼，將文本作為 JSON 屬性傳遞給調用：

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. 在此之下，從響應的有效載荷中檢索 `seconds`，如果調用失敗則返回 0：

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    成功的 HTTP 調用會返回 200 範圍內的狀態碼，而你的無伺服器代碼在文本被處理並識別為設定計時器意圖時會返回 200。

### 任務 - 在後台線程中設定計時器

1. 在文件頂部添加以下導入語句以導入 Python 的 threading 庫：

    ```python
    import threading
    ```

1. 在 `process_text` 函數上方，添加一個函數來播報響應。目前這個函數只會將文本寫入控制台，但在本課程稍後部分，這將用於語音播報。

    ```python
    def say(text):
        print(text)
    ```

1. 在此之下，添加一個函數，該函數將由計時器調用以宣布計時器完成：

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

    該函數接收計時器的分鐘數和秒數，並構建一個句子來宣布計時器完成。它會檢查分鐘數和秒數，並僅在有數值時才包括該時間單位。例如，如果分鐘數為 0，則消息中只包括秒數。這個句子隨後被發送到 `say` 函數。

1. 在此之下，添加以下 `create_timer` 函數來創建計時器：

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    該函數接收命令中發送的計時器總秒數，並將其轉換為分鐘數和秒數。然後，它使用總秒數創建並啟動一個計時器對象，傳遞 `announce_timer` 函數和包含分鐘數與秒數的列表。當計時器到期時，它將調用 `announce_timer` 函數，並將該列表的內容作為參數傳遞——列表的第一項作為 `minutes` 參數，第二項作為 `seconds` 參數。

1. 在 `create_timer` 函數的末尾，添加一些代碼來構建一條消息，向用戶播報計時器正在啟動：

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    同樣，這只包括有數值的時間單位。這個句子隨後被發送到 `say` 函數。

1. 在 `process_text` 函數的末尾添加以下內容，從文本中獲取計時器的時間，然後創建計時器：

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    只有當秒數大於 0 時，計時器才會被創建。

1. 運行應用程序，並確保函數應用程序也在運行。設定一些計時器，輸出將顯示計時器被設定，並在到期時顯示：

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 你可以在 [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) 或 [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device) 文件夾中找到這段代碼。

😀 你的計時器程序成功了！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。