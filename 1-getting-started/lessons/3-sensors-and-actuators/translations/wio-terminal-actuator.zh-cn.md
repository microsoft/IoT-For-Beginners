# # 制作夜灯 - 利用 Wio 终端

在这部分课程里，你将向 Wio 终端添加 LED 灯，并使用其制作夜灯。

## 硬件

夜灯需要添加执行器。

该执行器就是 **LED**。 它是 [发光二极管](https://wikipedia.org/wiki/Light-emitting_diode)， 通电时会发光。这是一个具有 2 种状态的数字执行器，分别为打开和关闭。发送 1 将打开 LED，发送 0 将其关闭。这是一个外部 Grove 执行器，需要连接到 Wio 终端。

夜灯的伪代码逻辑如下：

```output
检查当前光线强度
如果光线强度低于 300
    打开 LED
否则
    关闭 LED
```

### 连接 LED

Grove LED 作为模块提供，其带有多种 LED，可供选择颜色。

#### 任务 - 连接 LED

连接 LED。

![A grove LED](../../../images/grove-led.png)

1. 选择喜欢的 LED 并将针脚插入 LED 模块上的两个孔中。

    LED 是发光二极管，二极管只能单向承载电流。这意味着 LED 需要以正确的针脚顺序连接，否则将无法工作。

    LED 的一个针脚是正极，另一个是负极。LED 不是完美的圆形，一侧略微平坦。稍平坦的一面是负极。将 LED 连接到模块时，请确保圆角边的针脚连接到模块外部标记为 **+** 的插座，平坦的一面连接到靠近模块中间的插座。

2. LED 模块有一个旋转按钮，可用其控制亮度。使用小型十字头螺丝刀逆时针旋转它到最亮。

3. 将 Grove 电缆的一端插入 LED 模块上的插座。此操作只有一种方式。

4. 断开 Wio 终端与计算机或其他电源的连接，在查看屏幕时将 Grove 线缆的另一端连接到 Wio 终端右侧 Grove 插座。这是离电源按钮最远的插座。

    > 💁 右侧的 Grove 插座可与模拟或数字传感器和执行器一起使用。左边的插座是 I<sup>2</sup>C 和数字传感器和执行器。 I<sup>2</sup>C 将在后续课程中介绍。

![The grove LED connected to the right hand socket](../../../images/wio-led.png)

## 对夜灯进行编程

The nightlight can now be programmed using the built in light sensor and the Grove LED.
现在可使用内置光传感器和 Grove LED 对夜灯进行编程。

### 任务 - 对夜灯进行编程

对夜灯进行编程。

1. 在 VS Code 中打开上一部分创建的夜灯项目。

1. 将以下代码添加到 `setup` 函数的尾部：

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    此行代码用于初始化与传感器通信的引脚。

    `D0` 引脚是右侧 Grove 插座的数字引脚。此引脚设置为 `OUTPUT`，表示将其连接到执行器，数据将写入引脚。

2. 将以下代码直接添加到 loop 循环的 `delay` 函数前：

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

    此代码检查 `light` 的值。如果小于 300，则向引脚发送 1，打开 LED。如果指示灯大于或等于 300，则会向引脚发送 0，从而关闭 LED。

    > 💁 向执行器发送数字值时，低压值为 0v，高压值为器件的最大电压。对于 Wio 终端，高压值为 3.3V。

3. 将 Wio 终端重新连接到计算机，然后像之前一样上传此代码。

4. 连接串行监视器。光线值将在终端输出。

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

5. 盖上或揭开 Wio 终端背面的光传感器。可以看到当光线亮度值小于等于 300 时 LED 灯打开，亮度值高于 300 时 LED 灯关闭。

![The LED connected to the WIO turning on and off as the light level changes](../../../images/wio-running-assignment-1-1.gif)

> 💁 你可以在 [code-actuator/wio-terminal](code-actuator/wio-terminal) 文件夹中找到此代码。

😀 你的夜灯程序很成功！
