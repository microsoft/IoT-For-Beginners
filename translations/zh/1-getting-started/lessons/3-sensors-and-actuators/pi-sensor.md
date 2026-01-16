<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-24T23:13:20+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "zh"
}
-->
# 制作一个夜灯 - Raspberry Pi

在本课的这一部分，你将为你的 Raspberry Pi 添加一个光传感器。

## 硬件

本课使用的传感器是一个**光传感器**，它通过[光电二极管](https://wikipedia.org/wiki/Photodiode)将光转换为电信号。这是一个模拟传感器，会发送一个从 0 到 1,000 的整数值，表示相对光量，但不对应任何标准测量单位，例如[lux](https://wikipedia.org/wiki/Lux)。

光传感器是一个外部 Grove 传感器，需要连接到 Raspberry Pi 上的 Grove Base hat。

### 连接光传感器

用于检测光线强度的 Grove 光传感器需要连接到 Raspberry Pi。

#### 任务 - 连接光传感器

连接光传感器

![一个 Grove 光传感器](../../../../../translated_images/zh/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. 将 Grove 电缆的一端插入光传感器模块上的插座。电缆只能以一种方向插入。

1. 在 Raspberry Pi 断电的情况下，将 Grove 电缆的另一端连接到 Grove Base hat 上标记为 **A0** 的模拟插座。该插座位于 GPIO 引脚旁边插座排的第二个位置。

![连接到 A0 插座的 Grove 光传感器](../../../../../translated_images/zh/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## 编程光传感器

现在可以使用 Grove 光传感器对设备进行编程。

### 任务 - 编程光传感器

编程设备。

1. 启动 Raspberry Pi 并等待其完成启动。

1. 在 VS Code 中打开你在本任务前一部分创建的夜灯项目，可以直接在 Pi 上运行，也可以通过 Remote SSH 扩展连接。

1. 打开 `app.py` 文件，并删除其中的所有代码。

1. 在 `app.py` 文件中添加以下代码以导入一些所需的库：

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time` 语句导入了 `time` 模块，该模块将在本任务后续部分使用。

    `from grove.grove_light_sensor_v1_2 import GroveLightSensor` 语句从 Grove Python 库中导入了 `GroveLightSensor`。该库包含与 Grove 光传感器交互的代码，并在设置 Pi 时已全局安装。

1. 在上述代码之后添加以下代码，以创建一个管理光传感器的类实例：

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    `light_sensor = GroveLightSensor(0)` 这一行代码创建了一个连接到 **A0** 引脚的 `GroveLightSensor` 类实例——光传感器连接的 Grove 模拟引脚。

1. 在上述代码之后添加一个无限循环，用于轮询光传感器的值并将其打印到控制台：

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    这段代码将使用 `GroveLightSensor` 类的 `light` 属性读取当前光线强度，范围为 0-1,023。该属性从引脚读取模拟值，然后将该值打印到控制台。

1. 在循环的末尾添加一个一秒的短暂休眠，因为不需要连续检查光线强度。休眠可以降低设备的功耗。

    ```python
    time.sleep(1)
    ```

1. 在 VS Code 的终端中运行以下命令以运行你的 Python 应用程序：

    ```sh
    python3 app.py
    ```

    光线值将输出到控制台。遮挡或移开光传感器，值会发生变化：

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 你可以在 [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi) 文件夹中找到这段代码。

😀 为你的夜灯程序添加传感器成功了！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们尽力确保准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。对于因使用本翻译而引起的任何误解或误读，我们概不负责。