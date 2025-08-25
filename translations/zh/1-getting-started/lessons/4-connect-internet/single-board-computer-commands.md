<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-24T22:59:55+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "zh"
}
-->
# 通过互联网控制你的夜灯 - 虚拟物联网硬件和树莓派

在本课的这一部分，你将订阅从 MQTT broker 发送到你的树莓派或虚拟物联网设备的命令。

## 订阅命令

下一步是订阅从 MQTT broker 发送的命令并对其作出响应。

### 任务

订阅命令。

1. 在 VS Code 中打开夜灯项目。

1. 如果你使用的是虚拟物联网设备，请确保终端正在运行虚拟环境。如果你使用的是树莓派，则无需使用虚拟环境。

1. 在 `client_telemetry_topic` 定义之后添加以下代码：

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` 是设备订阅以接收 LED 命令的 MQTT 主题。

1. 在主循环的上方、`mqtt_client.loop_start()` 行之后添加以下代码：

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    这段代码定义了一个函数 `handle_command`，它将消息读取为 JSON 文档，并查找 `led_on` 属性的值。如果该值为 `True`，则打开 LED，否则关闭 LED。

    MQTT 客户端会订阅服务器发送消息的主题，并设置在接收到消息时调用 `handle_command` 函数。

    > 💁 `on_message` 处理器会被所有订阅的主题调用。如果你之后编写代码监听多个主题，可以从传递给处理器函数的 `message` 对象中获取消息发送的主题。

1. 按照上一部分作业运行代码的方式运行代码。如果你使用的是虚拟物联网设备，请确保 CounterFit 应用正在运行，并且光传感器和 LED 已在正确的引脚上创建。

1. 调整你的物理或虚拟设备检测到的光线水平。接收到的消息和发送的命令会写入终端。LED 也会根据光线水平打开或关闭。

> 💁 你可以在 [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) 文件夹或 [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi) 文件夹中找到这段代码。

😀 恭喜！你已经成功编写了设备代码，使其能够响应来自 MQTT broker 的命令。

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。因使用本翻译而导致的任何误解或误读，我们概不负责。