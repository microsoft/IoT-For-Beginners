<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-26T14:56:25+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "hk"
}
-->
# 通過互聯網控制你的夜燈 - 虛擬物聯網硬件與 Raspberry Pi

在本課程的這部分，你將訂閱從 MQTT broker 發送到你的 Raspberry Pi 或虛擬物聯網設備的指令。

## 訂閱指令

下一步是訂閱從 MQTT broker 發送的指令並對其作出回應。

### 任務

訂閱指令。

1. 在 VS Code 中打開夜燈項目。

1. 如果你使用的是虛擬物聯網設備，請確保終端正在運行虛擬環境。如果你使用的是 Raspberry Pi，則不需要使用虛擬環境。

1. 在 `client_telemetry_topic` 定義之後添加以下代碼：

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` 是設備訂閱以接收 LED 指令的 MQTT topic。

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

    此代碼定義了一個函數 `handle_command`，該函數將消息作為 JSON 文檔讀取，並查找 `led_on` 屬性的值。如果設置為 `True`，則 LED 會被打開，否則會被關閉。

    MQTT 客戶端訂閱服務器將發送消息的 topic，並設置 `handle_command` 函數在接收到消息時被調用。

    > 💁 `on_message` 處理器會被所有訂閱的 topic 調用。如果你之後編寫的代碼需要監聽多個 topic，可以從傳遞給處理函數的 `message` 對象中獲取消息所屬的 topic。

1. 以與之前部分作業相同的方式運行代碼。如果你使用的是虛擬物聯網設備，請確保 CounterFit 應用正在運行，並且光傳感器和 LED 已在正確的引腳上創建。

1. 調整你的物理或虛擬設備檢測到的光線水平。接收到的消息和發送的指令將顯示在終端上。LED 也會根據光線水平開啟或關閉。

> 💁 你可以在 [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) 文件夾或 [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi) 文件夾中找到此代碼。

😀 你已成功編寫代碼，使你的設備能夠響應來自 MQTT broker 的指令。

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。