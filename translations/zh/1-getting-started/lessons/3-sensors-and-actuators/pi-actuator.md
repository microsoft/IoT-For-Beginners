<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-24T23:20:06+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "zh"
}
-->
# 制作一个夜灯 - 树莓派

在本课的这一部分，你将为树莓派添加一个LED，并用它来制作一个夜灯。

## 硬件

夜灯现在需要一个执行器。

执行器是一个**LED**，即[发光二极管](https://wikipedia.org/wiki/Light-emitting_diode)，当电流通过时会发光。这是一种数字执行器，具有两种状态：开和关。发送值1会点亮LED，发送值0会关闭LED。LED是一个外部的Grove执行器，需要连接到树莓派上的Grove Base帽。

夜灯的逻辑伪代码如下：

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### 连接LED

Grove LED是一个模块，提供多种颜色的LED供选择。

#### 任务 - 连接LED

连接LED。

![一个Grove LED](../../../../../translated_images/zh/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. 选择你喜欢的LED，将其引脚插入LED模块上的两个孔中。

    LED是发光二极管，而二极管是一种只能单向导电的电子器件。这意味着LED必须以正确的方向连接，否则无法工作。

    LED的一个引脚是正极，另一个是负极。LED并不是完全圆形的一端会稍微平一些。稍微平的一侧是负极。当你将LED连接到模块时，请确保圆形一侧的引脚连接到模块外侧标有**+**的插座，而平的一侧连接到模块中间较近的插座。

1. LED模块有一个旋钮，可以控制亮度。首先用小号十字螺丝刀将其逆时针旋转到最大亮度。

1. 将Grove电缆的一端插入LED模块上的插座。电缆只能以一种方向插入。

1. 在树莓派断电的情况下，将Grove电缆的另一端连接到树莓派上Grove Base帽的数字插座**D5**。这个插座位于GPIO引脚旁边的一排插座中，从左数第二个。

![连接到D5插座的Grove LED](../../../../../translated_images/zh/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## 编程夜灯

现在可以使用Grove光传感器和Grove LED来编程夜灯。

### 任务 - 编程夜灯

编程夜灯。

1. 启动树莓派并等待其启动。

1. 在VS Code中打开你在本作业前一部分中创建的夜灯项目，可以直接在树莓派上运行，也可以通过Remote SSH扩展连接。

1. 在`app.py`文件顶部的其他`import`行下面添加以下代码以导入所需的库：

    ```python
    from grove.grove_led import GroveLed
    ```

    `from grove.grove_led import GroveLed`语句从Grove Python库中导入`GroveLed`。这个库包含与Grove LED交互的代码。

1. 在`light_sensor`声明之后添加以下代码，以创建管理LED的类实例：

    ```python
    led = GroveLed(5)
    ```

    `led = GroveLed(5)`这行代码创建了一个连接到引脚**D5**的`GroveLed`类实例——LED连接的数字Grove引脚。

    > 💁 每个插座都有唯一的引脚编号。引脚0、2、4和6是模拟引脚，引脚5、16、18、22、24和26是数字引脚。

1. 在`while`循环内添加一个检查，在`time.sleep`之前检查光线水平并打开或关闭LED：

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    这段代码检查`light`值。如果值小于300，则调用`GroveLed`类的`on`方法，向LED发送数字值1，点亮LED。如果光线值大于或等于300，则调用`off`方法，发送数字值0，关闭LED。

    > 💁 这段代码应该与`print('Light level:', light)`行保持相同的缩进级别，以确保它在`while`循环内！

    > 💁 向执行器发送数字值时，值0表示0V，值1表示设备的最大电压。对于树莓派使用的Grove传感器和执行器，值1的电压为3.3V。

1. 在VS Code终端中运行以下命令以运行你的Python应用程序：

    ```sh
    python3 app.py
    ```

    光线值将输出到控制台。

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. 遮挡和移开光传感器。注意当光线水平为300或以下时，LED会点亮；当光线水平大于300时，LED会熄灭。

    > 💁 如果LED没有点亮，请确保它连接的方向正确，并且旋钮已调到最大亮度。

![LED连接到树莓派并随着光线水平变化而亮灭](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 你可以在[code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi)文件夹中找到这段代码。

😀 你的夜灯程序成功了！

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对于因使用本翻译而引起的任何误解或误读不承担责任。