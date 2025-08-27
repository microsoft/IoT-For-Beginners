<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-26T23:07:42+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "mo"
}
-->
# 使用 X.509 憑證連接您的設備程式碼 - 虛擬 IoT 硬體與 Raspberry Pi

在本課程的這部分，您將使用 X.509 憑證將虛擬 IoT 設備或 Raspberry Pi 連接到您的 IoT Hub。

## 將設備連接到 IoT Hub

下一步是使用 X.509 憑證將您的設備連接到 IoT Hub。

### 任務 - 連接到 IoT Hub

1. 將密鑰和憑證檔案複製到包含您 IoT 設備程式碼的資料夾。如果您透過 VS Code Remote SSH 使用 Raspberry Pi 並在您的 PC 或 Mac 上建立了密鑰，您可以將檔案拖放到 VS Code 的檔案總管中以完成複製。

1. 打開 `app.py` 檔案

1. 要使用 X.509 憑證進行連接，您需要 IoT Hub 的主機名稱以及 X.509 憑證。首先，在建立設備客戶端之前，新增以下程式碼以建立包含主機名稱的變數：

    ```python
    host_name = "<host_name>"
    ```

    將 `<host_name>` 替換為您的 IoT Hub 的主機名稱。您可以從 `connection_string` 中的 `HostName` 部分獲取主機名稱。它將是您的 IoT Hub 的名稱，結尾為 `.azure-devices.net`

1. 在此程式碼下方，宣告一個包含設備 ID 的變數：

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. 您需要一個包含 X.509 檔案的 `X509` 類別實例。將 `X509` 新增到從 `azure.iot.device` 模組匯入的類別列表中：

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. 使用您的憑證和密鑰檔案建立一個 `X509` 類別實例，將以下程式碼新增到 `host_name` 宣告的下方：

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    這將使用之前建立的 `soil-moisture-sensor-x509-cert.pem` 和 `soil-moisture-sensor-x509-key.pem` 檔案來建立 `X509` 類別。

1. 將使用連接字串建立 `device_client` 的程式碼行替換為以下程式碼：

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    這將使用 X.509 憑證進行連接，而不是使用連接字串。

1. 刪除包含 `connection_string` 變數的程式碼行。

1. 執行您的程式碼。監控發送到 IoT Hub 的訊息，並像之前一樣發送直接方法請求。您將看到設備連接並發送土壤濕度讀數，同時接收直接方法請求。

> 💁 您可以在 [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) 或 [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device) 資料夾中找到此程式碼。

😀 您的土壤濕度感測器程式已使用 X.509 憑證成功連接到您的 IoT Hub！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。