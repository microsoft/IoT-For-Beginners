<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-24T22:57:18+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "tw"
}
-->
# 在您的設備代碼中使用 X.509 憑證 - 虛擬 IoT 硬體與 Raspberry Pi

在本課程的這部分，您將使用 X.509 憑證將虛擬 IoT 設備或 Raspberry Pi 連接到您的 IoT Hub。

## 將設備連接到 IoT Hub

下一步是使用 X.509 憑證將您的設備連接到 IoT Hub。

### 任務 - 連接到 IoT Hub

1. 將密鑰和憑證檔案複製到包含您 IoT 設備代碼的資料夾中。如果您是通過 VS Code Remote SSH 使用 Raspberry Pi，並且在您的 PC 或 Mac 上創建了密鑰，您可以將檔案拖放到 VS Code 的檔案總管中以完成複製。

1. 打開 `app.py` 檔案

1. 要使用 X.509 憑證進行連接，您需要 IoT Hub 的主機名稱和 X.509 憑證。首先，在創建設備客戶端之前，新增以下代碼來創建一個包含主機名稱的變數：

    ```python
    host_name = "<host_name>"
    ```

    將 `<host_name>` 替換為您的 IoT Hub 的主機名稱。您可以從 `connection_string` 的 `HostName` 部分獲取主機名稱。它將是您的 IoT Hub 的名稱，並以 `.azure-devices.net` 結尾。

1. 在此代碼下方，宣告一個包含設備 ID 的變數：

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. 您需要一個包含 X.509 檔案的 `X509` 類別實例。將 `X509` 新增到從 `azure.iot.device` 模組匯入的類別列表中：

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. 使用您的憑證和密鑰檔案創建一個 `X509` 類別實例，將以下代碼新增到 `host_name` 宣告的下方：

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    這將使用之前創建的 `soil-moisture-sensor-x509-cert.pem` 和 `soil-moisture-sensor-x509-key.pem` 檔案來創建 `X509` 類別。

1. 將使用連接字串創建 `device_client` 的代碼行替換為以下內容：

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    這將使用 X.509 憑證而非連接字串進行連接。

1. 刪除包含 `connection_string` 變數的代碼行。

1. 執行您的代碼。監控發送到 IoT Hub 的訊息，並像之前一樣發送直接方法請求。您將看到設備連接並發送土壤濕度讀數，同時接收直接方法請求。

> 💁 您可以在 [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) 或 [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device) 資料夾中找到此代碼。

😀 您的土壤濕度感測器程式已使用 X.509 憑證成功連接到您的 IoT Hub！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤讀概不負責。