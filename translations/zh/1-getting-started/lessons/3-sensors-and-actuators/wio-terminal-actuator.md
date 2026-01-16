<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "db44083b4dc6fb06eac83c4f16448940",
  "translation_date": "2025-08-24T23:21:33+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-actuator.md",
  "language_code": "zh"
}
-->
# 制作一个夜灯 - Wio Terminal

在本节课程中，您将为 Wio Terminal 添加一个 LED，并用它来制作一个夜灯。

## 硬件

现在夜灯需要一个执行器。

执行器是一个 **LED**，即[发光二极管](https://wikipedia.org/wiki/Light-emitting_diode)，当电流通过时会发光。这是一个数字执行器，只有两种状态：开和关。发送值 1 会点亮 LED，发送值 0 会关闭 LED。这是一个外部的 Grove 执行器，需要连接到 Wio Terminal。

夜灯的逻辑伪代码如下：

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### 连接 LED

Grove LED 是一个模块，包含多种颜色的 LED，您可以选择自己喜欢的颜色。

#### 任务 - 连接 LED

连接 LED。

![一个 Grove LED](../../../../../translated_images/zh/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. 选择您喜欢的 LED，将其引脚插入 LED 模块上的两个孔中。

    LED 是发光二极管，而二极管是一种只能单向导电的电子器件。这意味着 LED 必须以正确的方向连接，否则无法工作。

    LED 的一个引脚是正极，另一个是负极。LED 并不是完全圆形的，其中一侧稍微平一些。稍微平一些的一侧是负极。当您将 LED 连接到模块时，请确保圆润一侧的引脚连接到模块外侧标有 **+** 的插座，而平坦一侧的引脚连接到模块中间较近的插座。

1. LED 模块上有一个旋钮，可以用来调节亮度。使用小号十字螺丝刀将其逆时针旋转到最亮的位置。

1. 将 Grove 电缆的一端插入 LED 模块上的插座。电缆只能以一种方向插入。

1. 在 Wio Terminal 未连接到电脑或其他电源的情况下，将 Grove 电缆的另一端连接到 Wio Terminal 屏幕右侧的 Grove 插座。这是离电源按钮最远的插座。

    > 💁 右侧的 Grove 插座可以用于模拟或数字传感器和执行器。左侧插座仅用于 I2C 和数字传感器及执行器。

![Grove LED 连接到右侧插座](../../../../../translated_images/zh/wio-led.265a1897e72d7f21.webp)

## 编程夜灯

现在可以使用内置的光传感器和 Grove LED 来编程夜灯。

### 任务 - 编程夜灯

编程夜灯。

1. 在 VS Code 中打开您在本作业前一部分中创建的夜灯项目。

1. 在 `setup` 函数的底部添加以下代码行：

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    这行代码配置了用于通过 Grove 端口与 LED 通信的引脚。

    `D0` 引脚是右侧 Grove 插座的数字引脚。该引脚被设置为 `OUTPUT`，表示它连接到一个执行器，并将数据写入该引脚。

1. 在 `loop` 函数中的 `delay` 之前立即添加以下代码：

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    这段代码检查 `light` 值。如果该值小于 300，则向 `D0` 数字引脚发送 `HIGH` 值。`HIGH` 值为 1，会点亮 LED。如果光线值大于或等于 300，则向引脚发送 `LOW` 值，关闭 LED。

    > 💁 当向执行器发送数字值时，`LOW` 值为 0V，`HIGH` 值为设备的最大电压。对于 Wio Terminal，`HIGH` 电压为 3.3V。

1. 重新将 Wio Terminal 连接到您的电脑，并像之前一样上传新代码。

1. 连接串口监视器。光线值将输出到终端。

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

1. 遮住和移开光传感器。注意，当光线值小于或等于 300 时，LED 会点亮；当光线值大于 300 时，LED 会熄灭。

![LED 连接到 Wio，根据光线变化亮灭](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 您可以在 [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal) 文件夹中找到这段代码。

😀 您的夜灯程序成功了！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。因使用本翻译而引起的任何误解或误读，我们概不负责。