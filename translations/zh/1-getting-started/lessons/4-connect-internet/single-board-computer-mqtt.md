<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-24T23:09:40+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "zh"
}
-->
# 通过互联网控制你的夜灯 - 虚拟物联网硬件和树莓派

物联网设备需要通过 MQTT 与 *test.mosquitto.org* 通信，以发送包含光传感器读数的遥测值，并接收控制 LED 的命令。

在本课程的这一部分，你将把树莓派或虚拟物联网设备连接到 MQTT broker。

## 安装 MQTT 客户端包

为了与 MQTT broker 通信，你需要在树莓派或虚拟设备的虚拟环境中安装一个 MQTT 库的 pip 包。

### 任务

安装 pip 包

1. 在 VS Code 中打开夜灯项目。

1. 如果你使用的是虚拟物联网设备，请确保终端正在运行虚拟环境。如果你使用的是树莓派，则无需使用虚拟环境。

1. 运行以下命令以安装 MQTT pip 包：

    ```sh
    pip3 install paho-mqtt
    ```

## 编写设备代码

设备已经准备好进行编码。

### 任务

编写设备代码。

1. 在 `app.py` 文件顶部添加以下导入：

    ```python
    import paho.mqtt.client as mqtt
    ```

    `paho.mqtt.client` 库允许你的应用通过 MQTT 进行通信。

1. 在光传感器和 LED 的定义之后添加以下代码：

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    将 `<ID>` 替换为一个唯一的 ID，该 ID 将用作此设备客户端的名称，并在后续用于此设备发布和订阅的主题名称。*test.mosquitto.org* broker 是公共的，许多人都在使用，包括其他完成此任务的学生。拥有一个唯一的 MQTT 客户端名称和主题名称可以确保你的代码不会与其他人的代码冲突。在稍后的任务中创建服务器代码时，你也需要使用此 ID。

    > 💁 你可以使用像 [GUIDGen](https://www.guidgen.com) 这样的网站生成一个唯一的 ID。

    `client_name` 是此 MQTT 客户端在 broker 上的唯一名称。

1. 在这段新代码的下方添加以下代码，以创建一个 MQTT 客户端对象并连接到 MQTT broker：

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    此代码创建客户端对象，连接到公共 MQTT broker，并启动一个处理循环，该循环在后台线程中运行，监听任何已订阅主题的消息。

1. 以与完成任务的上一部分代码相同的方式运行代码。如果你使用的是虚拟物联网设备，请确保 CounterFit 应用正在运行，并且光传感器和 LED 已在正确的引脚上创建。

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 你可以在 [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) 文件夹或 [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi) 文件夹中找到此代码。

😀 你已成功将设备连接到 MQTT broker。

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档为权威来源。对于关键信息，建议使用专业人工翻译。因使用本翻译而导致的任何误解或误读，我们概不负责。