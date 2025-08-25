<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-24T22:05:20+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "zh"
}
-->
# 发布温度 - Wio Terminal

在本节课程中，您将通过 MQTT 发布 Wio Terminal 检测到的温度值，以便后续用于计算 GDD。

## 发布温度

一旦读取到温度值，就可以通过 MQTT 发布到某些“服务器”代码，这些代码将读取这些值并存储起来，以便用于 GDD 计算。微控制器不会直接从互联网读取时间，也不会默认使用实时时钟来跟踪时间，设备需要进行编程才能实现这一功能，前提是它具备必要的硬件。

为了简化本课程的内容，传感器数据不会附带时间信息，而是由服务器代码在接收到消息后添加时间。

### 任务

编程设备以发布温度数据。

1. 打开 `temperature-sensor` Wio Terminal 项目

1. 重复您在第 4 课中完成的步骤，连接到 MQTT 并发送遥测数据。您将使用相同的公共 Mosquitto broker。

    具体步骤如下：

    - 将 Seeed WiFi 和 MQTT 库添加到 `.ini` 文件
    - 添加配置文件和连接 WiFi 的代码
    - 添加连接到 MQTT broker 的代码
    - 添加发布遥测数据的代码

    > ⚠️ 如果需要，请参考 [连接到 MQTT 的说明](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) 和 [发送遥测数据的说明](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md)（第 4 课）。

1. 确保 `config.h` 头文件中的 `CLIENT_NAME` 反映了当前项目：

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. 对于遥测数据，不再发送光照值，而是发送从 DHT 传感器读取的温度值，并将其作为 JSON 文档中的 `temperature` 属性。为此，请修改 `main.cpp` 中的 `loop` 函数：

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. 温度值不需要频繁读取——在短时间内它不会有太大变化，因此将 `loop` 函数中的 `delay` 设置为 10 分钟：

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 `delay` 函数的时间单位是毫秒，为了便于阅读，时间以计算结果的形式传递。1,000 毫秒为 1 秒，60 秒为 1 分钟，因此 10 x (60 秒/分钟) x (1000 毫秒/秒) 得到 10 分钟的延迟。

1. 将代码上传到您的 Wio Terminal，并使用串口监视器查看温度值是否已发送到 MQTT broker。

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 您可以在 [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) 文件夹中找到此代码。

😀 您已成功将设备的温度值作为遥测数据发布。

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用此翻译而引起的任何误解或误读不承担责任。