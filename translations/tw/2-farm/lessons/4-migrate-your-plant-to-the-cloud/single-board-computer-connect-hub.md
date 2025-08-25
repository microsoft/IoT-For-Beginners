<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-24T22:48:42+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "tw"
}
-->
# 將您的 IoT 裝置連接到雲端 - 虛擬 IoT 硬體與 Raspberry Pi

在本課程的這部分，您將把虛擬 IoT 裝置或 Raspberry Pi 連接到您的 IoT Hub，以傳送遙測數據並接收指令。

## 將您的裝置連接到 IoT Hub

下一步是將您的裝置連接到 IoT Hub。

### 任務 - 連接到 IoT Hub

1. 在 VS Code 中打開 `soil-moisture-sensor` 資料夾。如果您使用的是虛擬 IoT 裝置，請確保虛擬環境已在終端中運行。

1. 安裝一些額外的 Pip 套件：

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` 是一個用於與 IoT Hub 通訊的庫。

1. 在 `app.py` 文件的頂部，現有的導入語句下方添加以下導入：

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    此代碼導入了與 IoT Hub 通訊的 SDK。

1. 移除 `import paho.mqtt.client as mqtt` 這行代碼，因為此庫已不再需要。移除所有 MQTT 相關代碼，包括主題名稱、所有使用 `mqtt_client` 的代碼以及 `handle_command`。保留 `while True:` 循環，只需刪除此循環中的 `mqtt_client.publish` 行。

1. 在導入語句下方添加以下代碼：

    ```python
    connection_string = "<connection string>"
    ```

    將 `<connection string>` 替換為您在本課程早些時候為裝置檢索到的連接字串。

    > 💁 這並不是最佳做法。連接字串不應存儲在源代碼中，因為它可能被檢入源代碼控制並被任何人發現。我們在這裡這樣做是為了簡化操作。理想情況下，您應使用環境變數和像 [`python-dotenv`](https://pypi.org/project/python-dotenv/) 這樣的工具。您將在即將到來的課程中學到更多相關內容。

1. 在此代碼下方添加以下代碼，以創建一個可以與 IoT Hub 通訊的裝置客戶端對象並連接它：

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. 運行此代碼。您將看到您的裝置已成功連接。

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## 傳送遙測數據

現在您的裝置已連接，您可以將遙測數據傳送到 IoT Hub，而不是 MQTT broker。

### 任務 - 傳送遙測數據

1. 在 `while True` 循環內，睡眠之前添加以下代碼：

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    此代碼創建了一個包含土壤濕度讀數的 JSON 字串的 IoT Hub `Message`，然後將其作為裝置到雲端的消息傳送到 IoT Hub。

## 處理指令

您的裝置需要處理來自伺服器代碼的指令，以控制繼電器。這是通過直接方法請求發送的。

## 任務 - 處理直接方法請求

1. 在 `while True` 循環之前添加以下代碼：

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    這定義了一個方法 `handle_method_request`，當 IoT Hub 調用直接方法時會被調用。每個直接方法都有一個名稱，此代碼期望名為 `relay_on` 的方法用於打開繼電器，以及名為 `relay_off` 的方法用於關閉繼電器。

    > 💁 這也可以通過單一的直接方法請求來實現，將所需的繼電器狀態作為有效負載傳遞，該有效負載可以通過方法請求傳遞並從 `request` 對象中獲取。

1. 直接方法需要一個響應，以告訴調用代碼它們已被處理。在 `handle_method_request` 函數的末尾添加以下代碼，以創建對請求的響應：

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    此代碼向直接方法請求發送一個 HTTP 狀態碼為 200 的響應，並將其返回到 IoT Hub。

1. 在此函數定義下方添加以下代碼：

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    此代碼告訴 IoT Hub 客戶端在調用直接方法時調用 `handle_method_request` 函數。

> 💁 您可以在 [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) 或 [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device) 資料夾中找到此代碼。

😀 您的土壤濕度感測器程式已成功連接到您的 IoT Hub！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用本翻譯而引起的任何誤解或誤釋不承擔責任。