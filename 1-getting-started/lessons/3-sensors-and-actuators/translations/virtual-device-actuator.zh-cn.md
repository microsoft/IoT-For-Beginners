# 制作夜灯 - 利用虚拟 IOT 硬件

在这部分课程里，你将向虚拟 IOT 硬件添加 LED 灯，并使用其制作夜灯。

## 虚拟硬件

制作夜灯需要在 CounterFit 应用程序中添加一个执行器。

该执行器就是 **LED**。 在实际的 IOT 设备中，它是 [发光二极管](https://wikipedia.org/wiki/Light-emitting_diode)， 通电时会发光。这是一个具有 2 种状态的数字执行器，分别为打开和关闭。发送 1 将打开 LED，发送 0 将其关闭。

夜灯的伪代码逻辑如下：

```output
检查当前光线强度
如果光线强度低于 300
    打开 LED
否则
    关闭 LED
```

### 添加执行器到 CounterFit

要使用虚拟 LED，需将其添加到 CounterFit 应用程序中

#### 任务 - 在 CounterFit 中添加执行器

在 CounterFit 应用程序中添加 LED。

1. 请确保 CounterFit web 应用接着上一部分的任务继续运行。否则，开启应用程序并重新添加光传感器。

2. 添加 LED:

    1. 在 *Actuator* 窗格的 *Create actuator* 框中，下拉 *Actuator type* 并选择 *LED*

    1. 将 *pin* 设置为 **5**

    1. 选择 **Add** 按钮以在 *pin 5* 上添加 LED

    ![LED 设置](../../../images/counterfit-create-led.png)

	LED 将被添加并显示在执行器列表中。

    ![LED 成功添加](../../../images/counterfit-led.png)

	成功添加 LED 后，你可使颜色选择器修改颜色。选择 **Set** 按钮来修改颜色。

### 对夜灯进行编程

现在可使用 CounterFit 光传感器和 LED 对夜灯进行编程。

#### 任务 - 对夜灯进行编程

对夜灯进行编程。

1. 在 VS Code 中打开上一部分创建的夜灯项目。如有必要，重启终端以确保它使用虚拟环境运行。

1. 打开 `app.py`

1. 将以下代码添加到 `app.py` 以添加依赖库。该代码需添加在开头，`import` 后。

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

	`from counterfit_shims_grove.grove_led import GroveLed` 语句从 CounterFit Grove shim Python 库导入 `GroveLed` 模块。其作用是在 CounterFit 应用中与 LED 进行交互。

1. 在 `light_sensor` 被声明后添加以下代码，以初始化管理 LED 的实例：

    ```python
    led = GroveLed(5)
    ```

    `led = GroveLed(5)` 语句创建 `GroveLed` 实例 - 并将 LED 连接到 CounterFit Grove 的引脚 **5** 上。

1. 在 `while` 循环中添加判断， 在执行 `time.sleep` 前检查光线亮度来开关 LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    此代码检查 `light` 的值。若光线亮度小于 300 调用 `GroveLed` 的 `on` 方法向 LED 发送 1， 即将其打开。若亮度大于等于 300 则调用 `off` 方法向 LED 发送 0，将其关闭。

    > 💁 此代码应与 while 循环内 `print('Light level:', light)` 语句缩进相同！

1. 在 VS 代码终端中，执行以下 Python 程序：

    ```sh
    python3 app.py
    ```

    光线亮度值将在控制台显示。

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. 修改 *Value* 或 *Random* 选项来控制光线亮度在 300 上下波动， LED 将打开或关闭。

![CounterFit 中的 LED 将根据光线强度打开或关闭](../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 你可以在 [code-actuator/virtual-device](code-actuator/virtual-device) 文件夹中找到此代码。

😀 你的夜灯程序很成功！
