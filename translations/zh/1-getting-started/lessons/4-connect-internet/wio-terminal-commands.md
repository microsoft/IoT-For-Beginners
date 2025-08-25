<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-24T23:12:30+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "zh"
}
-->
# 通过互联网控制夜灯 - Wio Terminal

在本节课程中，您将订阅从 MQTT broker 发送到 Wio Terminal 的命令。

## 订阅命令

下一步是订阅从 MQTT broker 发送的命令，并对其作出响应。

### 任务

订阅命令。

1. 在 VS Code 中打开夜灯项目。

1. 在 `config.h` 文件的底部添加以下代码，以定义命令的主题名称：

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` 是设备将订阅以接收 LED 命令的主题。

1. 在 `reconnectMQTTClient` 函数的末尾添加以下代码行，以便在 MQTT 客户端重新连接时订阅命令主题：

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. 在 `reconnectMQTTClient` 函数下方添加以下代码：

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

    此函数将作为回调，当 MQTT 客户端从服务器接收到消息时调用。

    消息以无符号 8 位整数数组的形式接收，因此需要转换为字符数组才能作为文本处理。

    消息包含一个 JSON 文档，并使用 ArduinoJson 库进行解码。读取 JSON 文档的 `led_on` 属性，根据其值决定是否打开或关闭 LED。

1. 在 `createMQTTClient` 函数中添加以下代码：

    ```cpp
    client.setCallback(clientCallback);
    ```

    此代码将 `clientCallback` 设置为当从 MQTT broker 接收到消息时调用的回调函数。

    > 💁 `clientCallback` 处理程序会为所有订阅的主题调用。如果您稍后编写监听多个主题的代码，可以通过回调函数传递的 `topic` 参数获取消息发送的主题。

1. 将代码上传到您的 Wio Terminal，并使用串口监视器查看发送到 MQTT broker 的光线强度数据。

1. 调整您的物理或虚拟设备检测到的光线强度。您将在终端中看到接收到的消息和发送的命令。根据光线强度，您还会看到 LED 被打开或关闭。

> 💁 您可以在 [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal) 文件夹中找到此代码。

😀 您已成功编写代码，使设备能够响应来自 MQTT broker 的命令。

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。原始语言的文档应被视为权威来源。对于关键信息，建议使用专业人工翻译。我们不对因使用此翻译而产生的任何误解或误读承担责任。