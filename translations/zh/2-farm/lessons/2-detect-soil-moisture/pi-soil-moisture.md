<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-24T22:40:28+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "zh"
}
-->
# 测量土壤湿度 - 树莓派

在本节课程中，您将为树莓派添加一个电容式土壤湿度传感器，并从中读取数据。

## 硬件

树莓派需要一个电容式土壤湿度传感器。

您将使用的传感器是[电容式土壤湿度传感器](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)，它通过检测土壤的电容来测量湿度，这种特性会随着土壤湿度的变化而变化。随着土壤湿度的增加，电压会降低。

这是一个模拟传感器，因此使用模拟引脚，并通过树莓派上的 Grove Base Hat 中的 10 位 ADC 将电压转换为 1-1,023 的数字信号。然后通过树莓派的 GPIO 引脚以 I²C 的方式传输。

### 连接土壤湿度传感器

Grove 土壤湿度传感器可以连接到树莓派。

#### 任务 - 连接土壤湿度传感器

连接土壤湿度传感器。

![一个 Grove 土壤湿度传感器](../../../../../translated_images/zh/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. 将 Grove 电缆的一端插入土壤湿度传感器上的插座。它只能以一种方式插入。

1. 在树莓派断电的情况下，将 Grove 电缆的另一端连接到 Grove Base Hat 上标记为 **A0** 的模拟插座。这个插座位于 GPIO 引脚旁边的一排插座中，从右数第二个。

![Grove 土壤湿度传感器连接到 A0 插座](../../../../../translated_images/zh/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.png)

1. 将土壤湿度传感器插入土壤中。传感器上有一条“最高位置线”——一条横跨传感器的白线。将传感器插入到这条线以下，但不要超过这条线。

![插入土壤中的 Grove 土壤湿度传感器](../../../../../translated_images/zh/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

## 编程土壤湿度传感器

现在可以为树莓派编程以使用连接的土壤湿度传感器。

### 任务 - 编程土壤湿度传感器

为设备编程。

1. 启动树莓派并等待其启动。

1. 启动 VS Code，可以直接在树莓派上运行，也可以通过 Remote SSH 扩展连接。

    > ⚠️ 如果需要，可以参考[夜灯项目 - 第 1 课中设置和启动 VS Code 的说明](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md)。

1. 在终端中，在 `pi` 用户的主目录下创建一个名为 `soil-moisture-sensor` 的新文件夹。在此文件夹中创建一个名为 `app.py` 的文件。

1. 在 VS Code 中打开此文件夹。

1. 在 `app.py` 文件中添加以下代码以导入一些所需的库：

    ```python
    import time
    from grove.adc import ADC
    ```

    `import time` 语句导入了 `time` 模块，该模块将在稍后使用。

    `from grove.adc import ADC` 语句从 Grove Python 库中导入了 `ADC`。该库包含与树莓派 Base Hat 上的模拟数字转换器交互并从模拟传感器读取电压的代码。

1. 在此代码下方添加以下代码以创建 `ADC` 类的实例：

    ```python
    adc = ADC()
    ```

1. 添加一个无限循环，从 A0 引脚上的 ADC 读取数据，并将结果写入控制台。此循环可以在每次读取之间休眠 10 秒。

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. 运行 Python 应用程序。您将在控制台中看到土壤湿度的测量值。向土壤中添加一些水，或者将传感器从土壤中移除，观察值的变化。

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    在上面的示例输出中，您可以看到随着水的添加，电压下降。

> 💁 您可以在 [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi) 文件夹中找到此代码。

😀 您的土壤湿度传感器程序运行成功！

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。因使用本翻译而引起的任何误解或误读，我们概不负责。