<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-24T23:22:52+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "zh"
}
-->
# 制作一个夜灯 - 虚拟物联网硬件

在本节课程中，您将为虚拟物联网设备添加一个LED，并用它来创建一个夜灯。

## 虚拟硬件

夜灯需要一个执行器，在 CounterFit 应用中创建。

这个执行器是一个 **LED**。在物理物联网设备中，它是一个[发光二极管](https://wikipedia.org/wiki/Light-emitting_diode)，当电流通过时会发光。这是一个数字执行器，具有两种状态：开和关。发送值1会点亮LED，发送值0会关闭它。

夜灯逻辑的伪代码如下：

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### 在 CounterFit 中添加执行器

要使用虚拟LED，您需要将其添加到 CounterFit 应用中。

#### 任务 - 在 CounterFit 中添加执行器

将LED添加到 CounterFit 应用中。

1. 确保 CounterFit 网页应用正在运行（从本作业的上一部分开始）。如果没有运行，请启动它并重新添加光传感器。

1. 创建一个LED：

    1. 在 *Actuator* 面板的 *Create actuator* 框中，点击 *Actuator type* 下拉框并选择 *LED*。

    1. 将 *Pin* 设置为 *5*。

    1. 点击 **Add** 按钮，在引脚5上创建LED。

    ![LED设置](../../../../../translated_images/zh/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    LED将被创建并显示在执行器列表中。

    ![创建的LED](../../../../../translated_images/zh/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    创建LED后，您可以使用 *Color* 选择器更改颜色。选择颜色后，点击 **Set** 按钮以更改颜色。

### 编程夜灯

现在可以使用 CounterFit 光传感器和LED来编程夜灯。

#### 任务 - 编程夜灯

编程夜灯。

1. 打开您在本作业上一部分中创建的夜灯项目（VS Code）。如果需要，终止并重新创建终端以确保它使用虚拟环境运行。

1. 打开 `app.py` 文件。

1. 在 `app.py` 文件顶部的其他 `import` 行下方，添加以下代码以导入所需的库：

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    `from counterfit_shims_grove.grove_led import GroveLed` 语句从 CounterFit Grove shim Python 库中导入 `GroveLed`。该库包含与 CounterFit 应用中创建的LED交互的代码。

1. 在 `light_sensor` 声明之后，添加以下代码以创建管理LED的类实例：

    ```python
    led = GroveLed(5)
    ```

    这行代码 `led = GroveLed(5)` 创建了一个 `GroveLed` 类的实例，连接到引脚 **5**，即 CounterFit Grove 中连接LED的引脚。

1. 在 `while` 循环内、`time.sleep` 之前添加一个检查，用于检测光线水平并打开或关闭LED：

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    这段代码检查 `light` 值。如果小于300，则调用 `GroveLed` 类的 `on` 方法，向LED发送数字值1，点亮LED。如果光线值大于或等于300，则调用 `off` 方法，发送数字值0，关闭LED。

    > 💁 这段代码应与 `print('Light level:', light)` 行保持相同的缩进级别，以确保它位于 while 循环内！

1. 在 VS Code 的终端中运行以下命令以运行您的 Python 应用：

    ```sh
    python3 app.py
    ```

    光线值将输出到控制台。

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. 更改 *Value* 或 *Random* 设置，使光线水平在300以上和以下变化。LED将会亮起和熄灭。

![CounterFit 应用中LED随着光线水平变化而亮灭](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 您可以在 [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device) 文件夹中找到此代码。

😀 您的夜灯程序成功了！

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用此翻译而引起的任何误解或误读不承担责任。