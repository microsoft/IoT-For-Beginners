<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-24T23:00:44+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "zh"
}
-->
# 通过互联网控制夜灯 - 虚拟物联网硬件和树莓派

在本节课程中，您将从树莓派或虚拟物联网设备向 MQTT broker 发送光照水平的遥测数据。

## 发布遥测数据

下一步是创建一个包含遥测数据的 JSON 文档，并将其发送到 MQTT broker。

### 任务

将遥测数据发布到 MQTT broker。

1. 在 VS Code 中打开夜灯项目。

1. 如果您使用的是虚拟物联网设备，请确保终端正在运行虚拟环境。如果您使用的是树莓派，则无需使用虚拟环境。

1. 在 `app.py` 文件顶部添加以下导入：

    ```python
    import json
    ```

    `json` 库用于将遥测数据编码为 JSON 文档。

1. 在 `client_name` 声明之后添加以下内容：

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` 是设备将光照水平发布到的 MQTT 主题。

1. 将文件末尾的 `while True:` 循环内容替换为以下内容：

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    此代码将光照水平打包为 JSON 文档并发布到 MQTT broker。然后它会休眠以减少消息发送的频率。

1. 以与之前任务相同的方式运行代码。如果您使用的是虚拟物联网设备，请确保 CounterFit 应用正在运行，并且光传感器和 LED 已在正确的引脚上创建。

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 您可以在 [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) 文件夹或 [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) 文件夹中找到此代码。

😀 您已成功从设备发送遥测数据。

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。因使用本翻译而引起的任何误解或误读，我们概不负责。