<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-24T23:08:16+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "zh"
}
-->
# 通过互联网控制夜灯 - Wio Terminal

在本节课程中，您将把 Wio Terminal 的光照强度数据作为遥测信息发送到 MQTT 代理。

## 安装 JSON Arduino 库

使用 JSON 是通过 MQTT 发送消息的一种常见方式。Arduino 提供了一个 JSON 库，可以更轻松地读取和写入 JSON 文档。

### 任务

安装 Arduino JSON 库。

1. 在 VS Code 中打开夜灯项目。

1. 在 `platformio.ini` 文件的 `lib_deps` 列表中添加以下内容作为额外一行：

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    这将导入 [ArduinoJson](https://arduinojson.org)，一个 Arduino 的 JSON 库。

## 发布遥测数据

下一步是创建一个包含遥测数据的 JSON 文档，并将其发送到 MQTT 代理。

### 任务 - 发布遥测数据

将遥测数据发布到 MQTT 代理。

1. 在 `config.h` 文件底部添加以下代码，以定义 MQTT 代理的遥测主题名称：

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` 是设备将光照强度数据发布到的主题。

1. 打开 `main.cpp` 文件。

1. 在文件顶部添加以下 `#include` 指令：

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. 在 `loop` 函数中，在 `delay` 之前添加以下代码：

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    这段代码读取光照强度，并使用 ArduinoJson 创建一个包含该强度的 JSON 文档。随后将其序列化为字符串，并通过 MQTT 客户端发布到遥测 MQTT 主题。

1. 将代码上传到您的 Wio Terminal，并使用串口监视器查看发送到 MQTT 代理的光照强度数据。

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 您可以在 [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) 文件夹中找到这段代码。

😀 您已成功从设备发送遥测数据。

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。对于因使用本翻译而引起的任何误解或误读，我们概不负责。