<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-26T23:09:53+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "mo"
}
-->
# 通過網絡控制夜燈 - 虛擬物聯網硬件與樹莓派

在本課程的這部分，你將訂閱從 MQTT broker 發送到樹莓派或虛擬物聯網設備的指令。

## 訂閱指令

下一步是訂閱從 MQTT broker 發送的指令並對其作出回應。

### 任務

訂閱指令。

1. 在 VS Code 中打開夜燈項目。

1. 如果你使用的是虛擬物聯網設備，請確保終端正在運行虛擬環境。如果你使用的是樹莓派，則不需要使用虛擬環境。

1. 在 `client_telemetry_topic` 定義之後添加以下代碼：

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` 是設備將訂閱以接收 LED 指令的 MQTT 主題。

1. 在主循環的上方，`mqtt_client.loop_start()` 行之後添加以下代碼：

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    此代碼定義了一個函數 `handle_command`，該函數將消息作為 JSON 文檔讀取，並查找 `led_on` 屬性的值。如果該屬性設置為 `True`，則 LED 會被打開，否則會被關閉。

    MQTT 客戶端會訂閱服務器發送消息的主題，並設置在接收到消息時調用 `handle_command` 函數。

    > 💁 `on_message` 處理器會對所有訂閱的主題進行回調。如果你之後編寫的代碼需要監聽多個主題，可以從傳遞給處理函數的 `message` 對象中獲取消息所屬的主題。

1. 以與上一部分作業相同的方式運行代碼。如果你使用的是虛擬物聯網設備，請確保 CounterFit 應用正在運行，並且光傳感器和 LED 已經在正確的引腳上創建。

1. 調整你的物理或虛擬設備檢測到的光線水平。接收到的消息和發送的指令將顯示在終端上。LED 也會根據光線水平開啟或關閉。

> 💁 你可以在 [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) 文件夾或 [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi) 文件夾中找到這段代碼。

😀 恭喜！你已成功編寫代碼，使你的設備能夠響應來自 MQTT broker 的指令。

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。