<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-24T21:06:27+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "zh"
}
-->
# 从物联网设备调用对象检测器 - 虚拟物联网硬件和树莓派

一旦你的对象检测器发布后，就可以从物联网设备中使用它。

## 复制图像分类器项目

你的库存检测器的大部分内容与之前课程中创建的图像分类器相同。

### 任务 - 复制图像分类器项目

1. 创建一个名为 `stock-counter` 的文件夹，如果你使用的是虚拟物联网设备，可以在你的电脑上创建；如果你使用的是树莓派，则在树莓派上创建。如果使用虚拟物联网设备，请确保设置虚拟环境。

1. 设置摄像头硬件。

    * 如果你使用的是树莓派，需要安装 PiCamera。你可能还需要将摄像头固定在一个位置，例如，将电缆挂在一个盒子或罐子上，或者用双面胶将摄像头固定在一个盒子上。
    * 如果你使用的是虚拟物联网设备，则需要安装 CounterFit 和 CounterFit PyCamera shim。如果你打算使用静态图像，请捕获一些对象检测器尚未见过的图像；如果你打算使用网络摄像头，请确保摄像头的位置能够看到你要检测的库存。

1. 复制[制造项目第 2 课](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device)中的步骤，从摄像头捕获图像。

1. 复制[制造项目第 2 课](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device)中的步骤，调用图像分类器。大部分代码将被重用来检测对象。

## 将代码从分类器更改为图像检测器

用于分类图像的代码与用于检测对象的代码非常相似。主要区别在于调用 Custom Vision SDK 的方法以及调用的结果。

### 任务 - 将代码从分类器更改为图像检测器

1. 删除用于分类图像和处理预测的三行代码：

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    删除这三行代码。

1. 添加以下代码以检测图像中的对象：

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    这段代码调用预测器的 `detect_image` 方法来运行对象检测器。然后收集所有概率高于阈值的预测，并将它们打印到控制台。

    与图像分类器每个标签只返回一个结果不同，对象检测器会返回多个结果，因此需要过滤掉概率较低的结果。

1. 运行这段代码，它将捕获一张图像，发送到对象检测器，并打印出检测到的对象。如果你使用的是虚拟物联网设备，请确保在 CounterFit 中设置了合适的图像，或者选择了网络摄像头。如果你使用的是树莓派，请确保摄像头对准了货架上的物品。

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 你可能需要调整 `threshold` 的值以适应你的图像。

    你将能够在 Custom Vision 的 **Predictions** 标签中看到拍摄的图像和这些预测值。

    ![货架上有 4 罐番茄酱，预测结果为 35.8%、33.5%、25.7% 和 16.6%](../../../../../translated_images/zh/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 你可以在 [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) 或 [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device) 文件夹中找到这段代码。

😀 你的库存计数程序成功了！

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用本翻译而引起的任何误解或误读不承担责任。