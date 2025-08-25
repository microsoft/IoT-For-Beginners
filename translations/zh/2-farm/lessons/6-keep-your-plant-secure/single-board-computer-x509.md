<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-24T22:57:09+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "zh"
}
-->
# 在设备代码中使用 X.509 证书 - 虚拟 IoT 硬件和 Raspberry Pi

在本课程的这一部分中，您将使用 X.509 证书将虚拟 IoT 设备或 Raspberry Pi 连接到您的 IoT Hub。

## 将设备连接到 IoT Hub

下一步是使用 X.509 证书将设备连接到 IoT Hub。

### 任务 - 连接到 IoT Hub

1. 将密钥和证书文件复制到包含 IoT 设备代码的文件夹中。如果您通过 VS Code Remote SSH 使用 Raspberry Pi，并在您的 PC 或 Mac 上创建了密钥，可以将文件拖放到 VS Code 的资源管理器中以完成复制。

1. 打开 `app.py` 文件

1. 要使用 X.509 证书进行连接，您需要 IoT Hub 的主机名和 X.509 证书。首先，通过在创建设备客户端之前添加以下代码来创建一个包含主机名的变量：

    ```python
    host_name = "<host_name>"
    ```

    将 `<host_name>` 替换为您的 IoT Hub 的主机名。您可以从 `connection_string` 的 `HostName` 部分获取主机名。它将是您的 IoT Hub 的名称，以 `.azure-devices.net` 结尾。

1. 在此代码下方，声明一个包含设备 ID 的变量：

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. 您需要一个包含 X.509 文件的 `X509` 类实例。从 `azure.iot.device` 模块导入的类列表中添加 `X509`：

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. 使用您的证书和密钥文件创建一个 `X509` 类实例，在 `host_name` 声明下方添加以下代码：

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    这将使用之前创建的 `soil-moisture-sensor-x509-cert.pem` 和 `soil-moisture-sensor-x509-key.pem` 文件创建 `X509` 类。

1. 将创建 `device_client` 的代码行替换为以下内容：

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    这将使用 X.509 证书而不是连接字符串进行连接。

1. 删除包含 `connection_string` 变量的代码行。

1. 运行您的代码。监控发送到 IoT Hub 的消息，并像之前一样发送直接方法请求。您将看到设备连接并发送土壤湿度读数，同时接收直接方法请求。

> 💁 您可以在 [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) 或 [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device) 文件夹中找到此代码。

😀 您的土壤湿度传感器程序已使用 X.509 证书成功连接到您的 IoT Hub！

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。原始语言的文档应被视为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用此翻译而产生的任何误解或误读不承担责任。