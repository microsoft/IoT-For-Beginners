<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-24T23:09:50+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "tw"
}
-->
# 通過互聯網控制夜燈 - 虛擬 IoT 硬體與 Raspberry Pi

IoT 裝置需要使用 MQTT 與 *test.mosquitto.org* 通信，通過光感測器讀取值來發送遙測數據，並接收控制 LED 的指令。

在本課程的這部分，你將把你的 Raspberry Pi 或虛擬 IoT 裝置連接到 MQTT broker。

## 安裝 MQTT 客戶端套件

為了與 MQTT broker 通信，你需要在 Raspberry Pi 或虛擬裝置的虛擬環境中安裝一個 MQTT 的 pip 套件。

### 任務

安裝 pip 套件

1. 在 VS Code 中打開夜燈專案。

1. 如果你使用的是虛擬 IoT 裝置，請確保終端機正在運行虛擬環境。如果你使用的是 Raspberry Pi，則不需要使用虛擬環境。

1. 執行以下命令來安裝 MQTT 的 pip 套件：

    ```sh
    pip3 install paho-mqtt
    ```

## 編寫裝置程式碼

裝置已準備好進行編碼。

### 任務

撰寫裝置程式碼。

1. 在 `app.py` 文件的頂部添加以下匯入：

    ```python
    import paho.mqtt.client as mqtt
    ```

    `paho.mqtt.client` 函式庫允許你的應用程式通過 MQTT 進行通信。

1. 在光感測器和 LED 的定義之後添加以下程式碼：

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    將 `<ID>` 替換為一個唯一的 ID，該 ID 將用作此裝置客戶端的名稱，並在稍後用於該裝置發佈和訂閱的主題名稱。*test.mosquitto.org* broker 是公開的，許多人都在使用，包括其他完成此作業的學生。擁有唯一的 MQTT 客戶端名稱和主題名稱可以確保你的程式碼不會與其他人的程式碼衝突。在稍後創建伺服器程式碼時，你也會需要這個 ID。

    > 💁 你可以使用像 [GUIDGen](https://www.guidgen.com) 這樣的網站來生成一個唯一的 ID。

    `client_name` 是此 MQTT 客戶端在 broker 上的唯一名稱。

1. 在這段新程式碼的下方添加以下程式碼，以創建一個 MQTT 客戶端物件並連接到 MQTT broker：

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    這段程式碼創建了客戶端物件，連接到公共 MQTT broker，並啟動了一個處理循環，該循環在後台執行緒中運行，用於監聽任何已訂閱主題的消息。

1. 以與作業前一部分相同的方式運行程式碼。如果你使用的是虛擬 IoT 裝置，請確保 CounterFit 應用程式正在運行，並且光感測器和 LED 已在正確的引腳上創建。

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 你可以在 [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) 資料夾或 [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi) 資料夾中找到這段程式碼。

😀 你已成功將裝置連接到 MQTT broker。

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。