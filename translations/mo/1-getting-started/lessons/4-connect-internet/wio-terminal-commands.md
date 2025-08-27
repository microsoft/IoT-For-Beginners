<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-26T23:21:21+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "mo"
}
-->
# 通過網絡控制你的夜燈 - Wio Terminal

在本課程的這部分，你將訂閱從 MQTT broker 發送到 Wio Terminal 的指令。

## 訂閱指令

下一步是訂閱從 MQTT broker 發送的指令，並對其作出響應。

### 任務

訂閱指令。

1. 在 VS Code 中打開夜燈項目。

1. 在 `config.h` 文件的底部添加以下代碼，以定義指令的主題名稱：

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` 是設備訂閱以接收 LED 指令的主題。

1. 在 `reconnectMQTTClient` 函數的末尾添加以下行，以便在 MQTT 客戶端重新連接時訂閱指令主題：

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. 在 `reconnectMQTTClient` 函數下方添加以下代碼。

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    此函數將作為 MQTT 客戶端在接收到來自服務器的消息時調用的回調函數。

    消息以無符號 8 位整數數組的形式接收，因此需要轉換為字符數組才能作為文本處理。

    消息包含一個 JSON 文檔，並使用 ArduinoJson 庫進行解碼。JSON 文檔的 `led_on` 屬性被讀取，根據其值來控制 LED 的開啟或關閉。

1. 在 `createMQTTClient` 函數中添加以下代碼：

    ```cpp
    client.setCallback(clientCallback);
    ```

    此代碼將 `clientCallback` 設置為在從 MQTT broker 接收到消息時調用的回調函數。

    > 💁 `clientCallback` 處理器會針對所有訂閱的主題被調用。如果你之後編寫代碼來監聽多個主題，可以從回調函數傳遞的 `topic` 參數中獲取消息所屬的主題。

1. 將代碼上傳到你的 Wio Terminal，並使用串行監視器查看發送到 MQTT broker 的光線水平。

1. 調整你的物理或虛擬設備檢測到的光線水平。你將看到消息被接收以及指令在終端中被發送。你還會看到 LED 根據光線水平的變化而開啟或關閉。

> 💁 你可以在 [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal) 文件夾中找到這段代碼。

😀 恭喜！你已成功編寫代碼，使你的設備能夠響應來自 MQTT broker 的指令。

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。