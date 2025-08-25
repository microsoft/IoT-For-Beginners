<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-24T22:02:03+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "zh"
}
-->
# 发布温度 - 虚拟物联网硬件和树莓派

在本课的这一部分中，您将通过 MQTT 发布树莓派或虚拟物联网设备检测到的温度值，以便稍后用于计算 GDD。

## 发布温度

一旦读取了温度值，就可以通过 MQTT 发布到某些“服务器”代码，这些代码将读取这些值并存储起来，以便用于 GDD 计算。

### 任务 - 发布温度

编程设备以发布温度数据。

1. 如果尚未打开，请打开 `temperature-sensor` 应用项目。

1. 重复您在第 4 课中完成的步骤以连接到 MQTT 并发送遥测数据，您将使用相同的公共 Mosquitto broker。

    这些步骤包括：

    - 添加 MQTT pip 包
    - 添加连接到 MQTT broker 的代码
    - 添加发布遥测数据的代码

    > ⚠️ 如果需要，请参考第 4 课中的[连接到 MQTT 的说明](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md)和[发送遥测数据的说明](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md)。

1. 确保 `client_name` 反映此项目的名称：

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. 对于遥测数据，不再发送光照值，而是发送从 DHT 传感器读取的温度值，并将其作为 JSON 文档中的 `temperature` 属性：

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. 温度值不需要频繁读取——在短时间内不会有太大变化，因此将 `time.sleep` 设置为 10 分钟：

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 `sleep` 函数以秒为单位接收时间，为了更容易理解，时间值是通过计算得出的。1 分钟有 60 秒，因此 10 x (1 分钟的 60 秒) 得到 10 分钟的延迟。

1. 以与之前任务代码相同的方式运行代码。如果您使用的是虚拟物联网设备，请确保 CounterFit 应用正在运行，并且湿度和温度传感器已在正确的引脚上创建。

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 您可以在 [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) 文件夹或 [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi) 文件夹中找到此代码。

😀 您已成功将设备的温度作为遥测数据发布。

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。因使用本翻译而引起的任何误解或误读，我们概不负责。