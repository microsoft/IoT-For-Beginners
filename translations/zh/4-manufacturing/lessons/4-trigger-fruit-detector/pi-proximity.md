<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-24T21:53:26+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "zh"
}
-->
# 检测接近 - 树莓派

在本课的这一部分，你将为树莓派添加一个接近传感器，并读取其测量的距离。

## 硬件

树莓派需要一个接近传感器。

你将使用的传感器是 [Grove 飞行时间距离传感器](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)。该传感器使用激光测距模块来检测距离，测量范围为 10mm 到 2000mm（1cm - 2m）。在此范围内，它可以非常准确地报告距离，超过 1000mm 的距离会被报告为 8109mm。

激光测距仪位于传感器背面，与 Grove 插座相对的一侧。

这是一个 I²C 传感器。

### 连接飞行时间传感器

Grove 飞行时间传感器可以连接到树莓派。

#### 任务 - 连接飞行时间传感器

连接飞行时间传感器。

![一个 Grove 飞行时间传感器](../../../../../translated_images/zh/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. 将 Grove 电缆的一端插入飞行时间传感器上的插座。电缆只能以一种方向插入。

1. 在树莓派断电的情况下，将 Grove 电缆的另一端连接到 Grove Base Hat 上标有 **I²C** 的插座之一。这些插座位于底部一排，与 GPIO 引脚相对的一端，靠近摄像头电缆插槽。

![Grove 飞行时间传感器连接到 I²C 插座](../../../../../translated_images/zh/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## 编程飞行时间传感器

现在可以为树莓派编写程序，以使用连接的飞行时间传感器。

### 任务 - 编程飞行时间传感器

为设备编写程序。

1. 启动树莓派并等待其启动完成。

1. 在 VS Code 中打开 `fruit-quality-detector` 代码，可以直接在树莓派上操作，也可以通过 Remote SSH 扩展连接。

1. 安装 rpi-vl53l0x Pip 包，这是一个用于与 VL53L0X 飞行时间距离传感器交互的 Python 包。使用以下 pip 命令安装：

    ```sh
    pip install rpi-vl53l0x
    ```

1. 在该项目中创建一个名为 `distance-sensor.py` 的新文件。

    > 💁 模拟多个 IoT 设备的一个简单方法是为每个设备创建一个单独的 Python 文件，然后同时运行它们。

1. 将以下代码添加到该文件中：

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    这段代码导入了 Grove I²C 总线库，以及用于 Grove 飞行时间传感器核心硬件的传感器库。

1. 在此代码下方，添加以下代码以访问传感器：

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    这段代码使用 Grove I²C 总线声明了一个距离传感器，然后启动了传感器。

1. 最后，添加一个无限循环以读取距离：

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    这段代码等待传感器准备好读取值，然后将其打印到控制台。

1. 运行此代码。

    > 💁 别忘了这个文件名是 `distance-sensor.py`！确保通过 Python 运行它，而不是 `app.py`。

1. 你将在控制台中看到距离测量值。将物体放置在传感器附近，你会看到距离测量值：

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    测距仪位于传感器背面，因此在测量距离时请确保使用正确的一侧。

    ![飞行时间传感器背面的测距仪对准一根香蕉](../../../../../translated_images/zh/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 你可以在 [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi) 文件夹中找到这段代码。

😀 你的接近传感器程序运行成功！

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用此翻译而引起的任何误解或误读不承担责任。