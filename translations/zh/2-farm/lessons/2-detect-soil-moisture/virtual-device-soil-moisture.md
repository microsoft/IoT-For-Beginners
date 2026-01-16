<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-24T22:39:06+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "zh"
}
-->
# 测量土壤湿度 - 虚拟物联网硬件

在本课的这一部分中，您将为虚拟物联网设备添加一个电容式土壤湿度传感器，并读取其数值。

## 虚拟硬件

虚拟物联网设备将使用模拟的 Grove 电容式土壤湿度传感器。这使得本实验与使用 Raspberry Pi 和物理 Grove 电容式土壤湿度传感器的操作保持一致。

在物理物联网设备中，土壤湿度传感器是一个电容式传感器，通过检测土壤的电容来测量土壤湿度。随着土壤湿度的变化，电容也会发生变化。当土壤湿度增加时，电压会降低。

这是一个模拟传感器，因此使用模拟的 10 位 ADC 来报告 1-1,023 范围内的数值。

### 将土壤湿度传感器添加到 CounterFit

要使用虚拟土壤湿度传感器，您需要将其添加到 CounterFit 应用中。

#### 任务 - 将土壤湿度传感器添加到 CounterFit

将土壤湿度传感器添加到 CounterFit 应用中。

1. 在您的电脑上创建一个名为 `soil-moisture-sensor` 的文件夹，并在其中创建一个名为 `app.py` 的单一文件，同时设置一个 Python 虚拟环境，并添加 CounterFit 的 pip 包。

    > ⚠️ 如果需要，可以参考[第 1 课中关于创建和设置 CounterFit Python 项目的说明](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md)。

1. 确保 CounterFit 网页应用正在运行。

1. 创建一个土壤湿度传感器：

    1. 在 *Sensors* 面板的 *Create sensor* 框中，点击 *Sensor type* 下拉框并选择 *Soil Moisture*。

    1. 将 *Units* 保持为 *NoUnits*。

    1. 确保 *Pin* 设置为 *0*。

    1. 点击 **Add** 按钮，在 Pin 0 上创建 *Soil Moisture* 传感器。

    ![土壤湿度传感器设置](../../../../../translated_images/zh/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    土壤湿度传感器将被创建并显示在传感器列表中。

    ![已创建的土壤湿度传感器](../../../../../translated_images/zh/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## 编写土壤湿度传感器应用程序

现在可以使用 CounterFit 传感器编写土壤湿度传感器应用程序。

### 任务 - 编写土壤湿度传感器应用程序

编写土壤湿度传感器应用程序。

1. 确保 `soil-moisture-sensor` 应用已在 VS Code 中打开。

1. 打开 `app.py` 文件。

1. 在 `app.py` 文件顶部添加以下代码，以连接应用到 CounterFit：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. 在 `app.py` 文件中添加以下代码以导入一些所需的库：

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    `import time` 语句导入了 `time` 模块，该模块将在后续任务中使用。

    `from counterfit_shims_grove.adc import ADC` 语句导入了 `ADC` 类，用于与虚拟模拟到数字转换器交互，该转换器可以连接到 CounterFit 传感器。

1. 在此代码下方添加以下代码，以创建 `ADC` 类的实例：

    ```python
    adc = ADC()
    ```

1. 添加一个无限循环，从 Pin 0 的 ADC 读取数据并将结果写入控制台。此循环可以在每次读取之间休眠 10 秒。

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. 在 CounterFit 应用中更改土壤湿度传感器的值，该值将被应用程序读取。您可以通过以下两种方式进行更改：

    * 在土壤湿度传感器的 *Value* 框中输入一个数字，然后点击 **Set** 按钮。您输入的数字将是传感器返回的值。

    * 勾选 *Random* 复选框，并输入 *Min* 和 *Max* 值，然后点击 **Set** 按钮。每次传感器读取值时，它将读取一个介于 *Min* 和 *Max* 之间的随机数。

1. 运行 Python 应用程序。您将在控制台中看到土壤湿度测量值。更改 *Value* 或 *Random* 设置以查看值的变化。

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 您可以在 [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device) 文件夹中找到此代码。

😀 您的土壤湿度传感器程序运行成功！

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。因使用本翻译而引起的任何误解或误读，我们概不负责。