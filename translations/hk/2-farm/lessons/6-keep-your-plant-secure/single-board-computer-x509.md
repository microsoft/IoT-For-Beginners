<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-26T14:55:02+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "hk"
}
-->
# 在您的設備代碼中使用 X.509 憑證 - 虛擬 IoT 硬件和 Raspberry Pi

在本課程的這部分，您將使用 X.509 憑證將虛擬 IoT 設備或 Raspberry Pi 連接到您的 IoT Hub。

## 將設備連接到 IoT Hub

下一步是使用 X.509 憑證將您的設備連接到 IoT Hub。

### 任務 - 連接到 IoT Hub

1. 將密鑰和憑證文件複製到包含您 IoT 設備代碼的文件夾中。如果您通過 VS Code Remote SSH 使用 Raspberry Pi，並且在您的 PC 或 Mac 上創建了密鑰，您可以將文件拖放到 VS Code 的資源管理器中以完成複製。

1. 打開 `app.py` 文件

1. 要使用 X.509 憑證進行連接，您需要 IoT Hub 的主機名稱和 X.509 憑證。首先，在創建設備客戶端之前，添加以下代碼來創建一個包含主機名稱的變量：

    ```python
    host_name = "<host_name>"
    ```

    將 `<host_name>` 替換為您的 IoT Hub 的主機名稱。您可以從 `connection_string` 的 `HostName` 部分獲取此名稱。它將是您的 IoT Hub 的名稱，並以 `.azure-devices.net` 結尾。

1. 在此代碼下方，聲明一個包含設備 ID 的變量：

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. 您需要一個包含 X.509 文件的 `X509` 類實例。將 `X509` 添加到從 `azure.iot.device` 模組導入的類列表中：

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. 使用您的憑證和密鑰文件創建一個 `X509` 類實例，將以下代碼添加到 `host_name` 聲明的下方：

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    這將使用之前創建的 `soil-moisture-sensor-x509-cert.pem` 和 `soil-moisture-sensor-x509-key.pem` 文件來創建 `X509` 類。

1. 用以下代碼替換從連接字串創建 `device_client` 的那一行代碼：

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    這將使用 X.509 憑證而不是連接字串進行連接。

1. 刪除包含 `connection_string` 變量的那一行代碼。

1. 運行您的代碼。監控發送到 IoT Hub 的消息，並像之前一樣發送直接方法請求。您將看到設備連接並發送土壤濕度讀數，同時接收直接方法請求。

> 💁 您可以在 [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) 或 [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device) 文件夾中找到此代碼。

😀 您的土壤濕度傳感器程序已使用 X.509 憑證成功連接到您的 IoT Hub！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原文檔的母語版本作為權威來源。對於關鍵資訊，建議尋求專業的人類翻譯服務。我們對因使用此翻譯而引起的任何誤解或錯誤詮釋概不負責。