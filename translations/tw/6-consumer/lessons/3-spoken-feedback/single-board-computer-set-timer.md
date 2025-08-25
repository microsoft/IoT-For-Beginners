<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-25T00:04:39+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "tw"
}
-->
# 設置計時器 - 虛擬 IoT 硬體與 Raspberry Pi

在本課程的這部分，你將調用無伺服器代碼來理解語音，並根據結果在虛擬 IoT 設備或 Raspberry Pi 上設置計時器。

## 設置計時器

從語音轉文字調用返回的文本需要發送到無伺服器代碼，通過 LUIS 處理，獲取計時器的秒數。這個秒數可以用來設置計時器。

計時器可以使用 Python 的 `threading.Timer` 類來設置。這個類接受一個延遲時間和一個函數，延遲時間結束後，該函數會被執行。

### 任務 - 將文本發送到無伺服器函數

1. 在 VS Code 中打開 `smart-timer` 專案，並確保如果你使用的是虛擬 IoT 設備，終端中已加載虛擬環境。

1. 在 `process_text` 函數上方，聲明一個名為 `get_timer_time` 的函數，用於調用你創建的 REST 端點：

    ```python
    def get_timer_time(text):
    ```

1. 在該函數中添加以下代碼來定義要調用的 URL：

    ```python
    url = '<URL>'
    ```

    將 `<URL>` 替換為你在上一課中構建的 REST 端點的 URL，可以是你的電腦上的 URL 或雲端的 URL。

1. 添加以下代碼，將文本作為 JSON 屬性傳遞給調用：

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. 在這段代碼下方，從響應的有效負載中檢索 `seconds`，如果調用失敗則返回 0：

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    成功的 HTTP 調用會返回 200 範圍內的狀態碼，而你的無伺服器代碼會在文本被處理並識別為設置計時器意圖時返回 200。

### 任務 - 在後台執行緒上設置計時器

1. 在文件頂部添加以下導入語句以導入 Python 的 threading 庫：

    ```python
    import threading
    ```

1. 在 `process_text` 函數上方，添加一個函數來播報回應。目前這個函數只會將文本輸出到控制台，但在本課程稍後會用於語音播報。

    ```python
    def say(text):
        print(text)
    ```

1. 在這段代碼下方，添加一個函數，該函數將由計時器調用以宣布計時器完成：

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

    該函數接受計時器的分鐘數和秒數，並構建一個句子來宣布計時器完成。它會檢查分鐘數和秒數，僅在有數值時才包含相應的時間單位。例如，如果分鐘數為 0，則僅包含秒數。這個句子隨後會被發送到 `say` 函數。

1. 在這段代碼下方，添加以下 `create_timer` 函數來創建計時器：

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    該函數接受將在命令中發送的計時器總秒數，並將其轉換為分鐘和秒數。然後，它使用總秒數創建並啟動一個計時器對象，傳遞 `announce_timer` 函數和包含分鐘數與秒數的列表。當計時器到期時，它會調用 `announce_timer` 函數，並將該列表的內容作為參數傳遞——列表中的第一項作為 `minutes` 參數，第二項作為 `seconds` 參數。

1. 在 `create_timer` 函數的末尾，添加一些代碼來構建一條消息，告訴用戶計時器正在啟動：

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    同樣，這條消息僅包含有值的時間單位。這個句子隨後會被發送到 `say` 函數。

1. 在 `process_text` 函數的末尾添加以下內容，從文本中獲取計時器的時間，然後創建計時器：

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    只有當秒數大於 0 時，計時器才會被創建。

1. 運行應用程序，並確保函數應用程序也在運行。設置一些計時器，輸出將顯示計時器被設置，並在計時器到期時顯示：

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 你可以在 [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) 或 [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device) 文件夾中找到這段代碼。

😀 你的計時器程序成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原文文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤讀概不負責。