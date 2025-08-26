<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-26T15:00:39+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "hk"
}
-->
# 通過互聯網控制你的夜燈 - 虛擬物聯網硬件與樹莓派

物聯網設備需要編寫程式碼，通過 MQTT 與 *test.mosquitto.org* 通信，發送包含光感應器讀數的遙測值，並接收控制 LED 的指令。

在本課程的這部分，你將把你的樹莓派或虛擬物聯網設備連接到 MQTT broker。

## 安裝 MQTT 客戶端套件

為了與 MQTT broker 通信，你需要在樹莓派或虛擬設備的虛擬環境中安裝 MQTT 的 pip 套件。

### 任務

安裝 pip 套件

1. 在 VS Code 中打開夜燈項目。

1. 如果你使用的是虛擬物聯網設備，請確保終端正在運行虛擬環境。如果你使用的是樹莓派，則不需要使用虛擬環境。

1. 運行以下命令來安裝 MQTT 的 pip 套件：

    ```sh
    pip3 install paho-mqtt
    ```

## 編寫設備程式碼

設備已準備好編寫程式碼。

### 任務

編寫設備程式碼。

1. 在 `app.py` 文件的頂部添加以下導入：

    ```python
    import paho.mqtt.client as mqtt
    ```

    `paho.mqtt.client` 庫允許你的應用通過 MQTT 進行通信。

1. 在光感應器和 LED 的定義之後添加以下程式碼：

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    將 `<ID>` 替換為一個唯一的 ID，該 ID 將用作此設備客戶端的名稱，並在稍後用於此設備發布和訂閱的主題名稱。*test.mosquitto.org* broker 是公共的，許多人都在使用，包括其他完成此作業的學生。擁有唯一的 MQTT 客戶端名稱和主題名稱可以確保你的程式碼不會與其他人的程式碼衝突。在稍後創建伺服器程式碼時，你也需要使用此 ID。

    > 💁 你可以使用像 [GUIDGen](https://www.guidgen.com) 這樣的網站來生成唯一的 ID。

    `client_name` 是此 MQTT 客戶端在 broker 上的唯一名稱。

1. 在這段新程式碼的下方添加以下程式碼，以創建 MQTT 客戶端對象並連接到 MQTT broker：

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    此程式碼創建客戶端對象，連接到公共 MQTT broker，並啟動一個處理循環，該循環在後台執行緒中運行，監聽任何訂閱主題的消息。

1. 以與作業上一部分相同的方式運行程式碼。如果你使用的是虛擬物聯網設備，請確保 CounterFit 應用正在運行，並且光感應器和 LED 已在正確的引腳上創建。

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 你可以在 [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) 文件夾或 [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi) 文件夾中找到此程式碼。

😀 你已成功將設備連接到 MQTT broker。

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為具權威性的來源。對於重要信息，建議使用專業的人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。