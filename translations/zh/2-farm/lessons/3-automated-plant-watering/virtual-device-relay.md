<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-24T22:18:50+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "zh"
}
-->
# 控制继电器 - 虚拟物联网硬件

在本节课程中，您将为虚拟物联网设备添加一个继电器，除了土壤湿度传感器外，还可以根据土壤湿度水平来控制继电器。

## 虚拟硬件

虚拟物联网设备将使用模拟的 Grove 继电器。这使得本实验与使用带有物理 Grove 继电器的 Raspberry Pi 的操作保持一致。

在物理物联网设备中，继电器通常是常开型继电器（即当没有信号发送到继电器时，输出电路是断开的或未连接的）。这种继电器可以处理高达 250V 和 10A 的输出电路。

### 将继电器添加到 CounterFit

要使用虚拟继电器，您需要将其添加到 CounterFit 应用中。

#### 任务

将继电器添加到 CounterFit 应用。

1. 如果尚未打开，请在 VS Code 中打开上一节课中的 `soil-moisture-sensor` 项目。您将基于此项目进行添加。

1. 确保 CounterFit 网页应用正在运行。

1. 创建一个继电器：

    1. 在 *Actuators* 面板的 *Create actuator* 框中，点击 *Actuator type* 下拉框并选择 *Relay*。

    1. 将 *Pin* 设置为 *5*。

    1. 点击 **Add** 按钮，在 Pin 5 上创建继电器。

    ![继电器设置](../../../../../translated_images/zh/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    继电器将被创建并显示在执行器列表中。

    ![创建的继电器](../../../../../translated_images/zh/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## 编程继电器

现在可以为土壤湿度传感器应用编程以使用虚拟继电器。

### 任务

编程虚拟设备。

1. 如果尚未打开，请在 VS Code 中打开上一节课中的 `soil-moisture-sensor` 项目。您将基于此项目进行添加。

1. 在现有的导入代码下方，将以下代码添加到 `app.py` 文件中：

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    此语句从 Grove Python shim 库中导入 `GroveRelay`，以与虚拟 Grove 继电器交互。

1. 在 `ADC` 类的声明下方添加以下代码，以创建一个 `GroveRelay` 实例：

    ```python
    relay = GroveRelay(5)
    ```

    这将在 Pin **5** 上创建一个继电器，这是您连接继电器的引脚。

1. 为测试继电器是否正常工作，在 `while True:` 循环中添加以下代码：

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    代码将继电器打开，等待 0.5 秒，然后关闭继电器。

1. 运行 Python 应用。继电器将每 10 秒打开和关闭一次，打开和关闭之间有半秒的延迟。您将在 CounterFit 应用中看到虚拟继电器随着继电器的打开和关闭而闭合和断开。

    ![虚拟继电器打开和关闭](../../../../../images/virtual-relay-turn-on-off.gif)

## 根据土壤湿度控制继电器

现在继电器可以正常工作了，可以根据土壤湿度读数来控制它。

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

    此代码从土壤湿度传感器检查土壤湿度水平。如果湿度值高于 450，则打开继电器；如果低于 450，则关闭继电器。

    > 💁 请记住，电容式土壤湿度传感器的读数越低，土壤中的湿度越高，反之亦然。

1. 运行 Python 应用。您将看到继电器根据土壤湿度水平打开或关闭。更改土壤湿度传感器的 *Value* 或 *Random* 设置以查看值变化。

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 您可以在 [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device) 文件夹中找到此代码。

😀 恭喜！您的虚拟土壤湿度传感器成功控制了继电器程序！

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。原始语言的文档应被视为权威来源。对于重要信息，建议使用专业人工翻译。我们对因使用此翻译而产生的任何误解或误读不承担责任。