<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-24T22:17:26+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "zh"
}
-->
# 控制继电器 - 树莓派

在本节课程中，您将为树莓派添加一个继电器，除了土壤湿度传感器外，还可以根据土壤湿度水平控制继电器。

## 硬件

树莓派需要一个继电器。

您将使用的继电器是 [Grove 继电器](https://www.seeedstudio.com/Grove-Relay.html)，这是一个常开继电器（意味着当没有信号发送到继电器时，输出电路是断开的）。它可以处理高达 250V 和 10A 的输出电路。

这是一个数字执行器，因此需要连接到 Grove Base Hat 上的数字引脚。

### 连接继电器

Grove 继电器可以连接到树莓派。

#### 任务

连接继电器。

![一个 Grove 继电器](../../../../../translated_images/zh/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. 将 Grove 电缆的一端插入继电器上的插座。它只能以一种方式插入。

1. 在树莓派断电的情况下，将 Grove 电缆的另一端连接到 Grove Base Hat 上标记为 **D5** 的数字插座。这个插座位于 GPIO 引脚旁边的一排插座中，从左数第二个。保持土壤湿度传感器连接到 **A0** 插座。

![Grove 继电器连接到 D5 插座，土壤湿度传感器连接到 A0 插座](../../../../../translated_images/zh/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. 如果土壤湿度传感器还没有插入土壤，请将其插入土壤中（如果您在上一节课程中已经插入，则无需重复操作）。

## 编程继电器

现在可以为树莓派编程以使用连接的继电器。

### 任务

编程设备。

1. 启动树莓派并等待其启动完成。

1. 在 VS Code 中打开上一节课程中的 `soil-moisture-sensor` 项目（如果尚未打开）。您将在此项目中进行添加。

1. 在现有的导入语句下，向 `app.py` 文件添加以下代码：

    ```python
    from grove.grove_relay import GroveRelay
    ```

    这条语句从 Grove Python 库中导入 `GroveRelay`，以便与 Grove 继电器交互。

1. 在 `ADC` 类的声明下方添加以下代码，以创建一个 `GroveRelay` 实例：

    ```python
    relay = GroveRelay(5)
    ```

    这将在您连接继电器的数字引脚 **D5** 上创建一个继电器。

1. 为了测试继电器是否正常工作，在 `while True:` 循环中添加以下代码：

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    这段代码会打开继电器，等待 0.5 秒，然后关闭继电器。

1. 运行 Python 应用程序。继电器将每 10 秒打开和关闭一次，每次打开和关闭之间有 0.5 秒的延迟。您会听到继电器点击打开然后点击关闭。当继电器打开时，Grove 板上的 LED 会亮起，当继电器关闭时，LED 会熄灭。

    ![继电器打开和关闭](../../../../../images/relay-turn-on-off.gif)

## 根据土壤湿度控制继电器

现在继电器可以正常工作了，可以根据土壤湿度传感器的读数来控制它。

### 任务

控制继电器。

1. 删除您添加的用于测试继电器的 3 行代码。用以下代码替换它们：

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    这段代码会从土壤湿度传感器读取土壤湿度水平。如果湿度值高于 450，则打开继电器；如果低于 450，则关闭继电器。

    > 💁 请记住，电容式土壤湿度传感器的读数越低，土壤中的湿度越高，反之亦然。

1. 运行 Python 应用程序。您会看到继电器根据土壤湿度水平打开或关闭。尝试在干燥的土壤中测试，然后加水。

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 您可以在 [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi) 文件夹中找到这段代码。

😀 恭喜！您的土壤湿度传感器成功控制了继电器！

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。原始语言的文档应被视为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用此翻译而产生的任何误解或误读不承担责任。