<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-24T23:24:08+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "zh"
}
-->
# 制作一个夜灯 - 虚拟物联网硬件

在本节课程中，您将为虚拟物联网设备添加一个光传感器。

## 虚拟硬件

夜灯需要一个传感器，通过 CounterFit 应用程序创建。

这个传感器是一个**光传感器**。在实际的物联网设备中，它会是一个[光电二极管](https://wikipedia.org/wiki/Photodiode)，将光转换为电信号。光传感器是一种模拟传感器，它发送一个整数值，表示相对的光量，但这个值并不对应任何标准的测量单位，例如 [lux](https://wikipedia.org/wiki/Lux)。

### 将传感器添加到 CounterFit

要使用虚拟光传感器，您需要将其添加到 CounterFit 应用程序中。

#### 任务 - 将传感器添加到 CounterFit

将光传感器添加到 CounterFit 应用程序中。

1. 确保 CounterFit Web 应用程序正在运行（从本作业的上一部分开始）。如果没有，请启动它。

1. 创建一个光传感器：

    1. 在 *Sensors* 面板的 *Create sensor* 框中，点击 *Sensor type* 下拉框并选择 *Light*。

    1. 将 *Units* 保持为 *NoUnits*。

    1. 确保 *Pin* 设置为 *0*。

    1. 点击 **Add** 按钮，在 Pin 0 上创建光传感器。

    ![光传感器设置](../../../../../translated_images/zh/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    光传感器将被创建并显示在传感器列表中。

    ![光传感器已创建](../../../../../translated_images/zh/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## 编程光传感器

现在可以对设备进行编程，以使用内置的光传感器。

### 任务 - 编程光传感器

对设备进行编程。

1. 在 VS Code 中打开您在本作业上一部分中创建的夜灯项目。如果需要，请终止并重新创建终端，以确保它正在使用虚拟环境运行。

1. 打开 `app.py` 文件。

1. 在 `app.py` 文件顶部的 `import` 语句部分添加以下代码，以导入一些所需的库：

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time` 语句导入了 Python 的 `time` 模块，该模块将在本作业后续部分使用。

    `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` 语句从 CounterFit Grove shim Python 库中导入了 `GroveLightSensor`。该库包含与 CounterFit 应用程序中创建的光传感器交互的代码。

1. 在文件底部添加以下代码，以创建管理光传感器的类实例：

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    `light_sensor = GroveLightSensor(0)` 这一行创建了一个连接到 Pin **0** 的 `GroveLightSensor` 类实例——这是光传感器连接到的 CounterFit Grove 引脚。

1. 在上述代码之后添加一个无限循环，用于轮询光传感器的值并将其打印到控制台：

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    这段代码将使用 `GroveLightSensor` 类的 `light` 属性读取当前光照水平。该属性从引脚读取模拟值，然后将该值打印到控制台。

1. 在 `while` 循环的末尾添加一个一秒的延迟，因为光照水平不需要被连续检查。延迟可以减少设备的功耗。

    ```python
    time.sleep(1)
    ```

1. 在 VS Code 的终端中运行以下命令以运行您的 Python 应用程序：

    ```sh
    python3 app.py
    ```

    光照值将输出到控制台。初始值将为 0。

1. 在 CounterFit 应用程序中更改光传感器的值，该值将被应用程序读取。您可以通过以下两种方式更改：

    * 在光传感器的 *Value* 框中输入一个数字，然后点击 **Set** 按钮。您输入的数字将是传感器返回的值。

    * 勾选 *Random* 复选框，并输入 *Min* 和 *Max* 值，然后点击 **Set** 按钮。每次传感器读取值时，它将读取一个介于 *Min* 和 *Max* 之间的随机数。

    您设置的值将输出到控制台。更改 *Value* 或 *Random* 设置以使值发生变化。

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 您可以在 [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device) 文件夹中找到这段代码。

😀 您的夜灯程序成功了！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。对于因使用本翻译而引起的任何误解或误读，我们概不负责。