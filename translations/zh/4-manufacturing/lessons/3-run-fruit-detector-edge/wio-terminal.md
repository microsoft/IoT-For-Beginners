<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-24T21:46:40+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "zh"
}
-->
# 使用基于 IoT Edge 的图像分类器对图像进行分类 - Wio Terminal

在本节课程中，您将使用运行在 IoT Edge 设备上的图像分类器。

## 使用 IoT Edge 分类器

IoT 设备可以被重新定向以使用 IoT Edge 图像分类器。图像分类器的 URL 是 `http://<IP address or name>/image`，将 `<IP address or name>` 替换为运行 IoT Edge 的计算机的 IP 地址或主机名。

### 任务 - 使用 IoT Edge 分类器

1. 如果尚未打开 `fruit-quality-detector` 应用项目，请将其打开。

1. 图像分类器作为一个使用 HTTP 的 REST API 运行，而不是 HTTPS，因此调用需要使用仅支持 HTTP 调用的 WiFi 客户端。这意味着不需要证书。从 `config.h` 文件中删除 `CERTIFICATE`。

1. 需要将 `config.h` 文件中的预测 URL 更新为新 URL。您还可以删除 `PREDICTION_KEY`，因为它不再需要。

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    将 `<URL>` 替换为您的分类器的 URL。

1. 在 `main.cpp` 中，将 WiFi Client Secure 的 include 指令更改为导入标准 HTTP 版本：

    ```cpp
    #include <WiFiClient.h>
    ```

1. 将 `WiFiClient` 的声明更改为 HTTP 版本：

    ```cpp
    WiFiClient client;
    ```

1. 找到设置 WiFi 客户端证书的那一行。从 `connectWiFi` 函数中删除 `client.setCACert(CERTIFICATE);` 这一行。

1. 在 `classifyImage` 函数中，删除设置预测密钥的这一行：`httpClient.addHeader("Prediction-Key", PREDICTION_KEY);`。

1. 上传并运行您的代码。将摄像头对准一些水果并按下 C 按钮。您将在串行监视器中看到输出：

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 您可以在 [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) 文件夹中找到此代码。

😀 您的水果质量分类器程序运行成功！

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用此翻译而引起的任何误解或误读不承担责任。