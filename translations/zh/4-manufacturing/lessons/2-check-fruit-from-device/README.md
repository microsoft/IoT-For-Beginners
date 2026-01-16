<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-24T21:25:38+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "zh"
}
-->
# 从物联网设备检查水果质量

![本课的手绘笔记概览](../../../../../translated_images/zh/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.jpg)

> 手绘笔记由 [Nitya Narasimhan](https://github.com/nitya) 提供。点击图片查看大图。

## 课前测验

[课前测验](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## 简介

在上一课中，你学习了图像分类器以及如何训练它们来检测优质和劣质水果。要在物联网应用中使用这个图像分类器，你需要能够通过某种摄像头捕获图像，并将图像发送到云端进行分类。

在本课中，你将学习摄像头传感器，以及如何将它们与物联网设备结合使用来捕获图像。同时，你还将学习如何从物联网设备调用图像分类器。

本课内容包括：

* [摄像头传感器](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [使用物联网设备捕获图像](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [发布你的图像分类器](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [从物联网设备分类图像](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [改进模型](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## 摄像头传感器

顾名思义，摄像头传感器是可以连接到物联网设备的摄像头。它们可以拍摄静态图像或捕获流媒体视频。有些会返回原始图像数据，而有些会将图像数据压缩成如 JPEG 或 PNG 格式的图像文件。通常，与物联网设备配套的摄像头比你习惯使用的摄像头要小得多，分辨率也较低，但你也可以找到分辨率媲美高端手机的摄像头。你还可以选择各种可更换镜头、多摄像头配置、红外热成像摄像头或紫外线摄像头。

![场景中的光线通过镜头聚焦到 CMOS 传感器上](../../../../../translated_images/zh/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.png)

大多数摄像头传感器使用图像传感器，其中每个像素是一个光电二极管。镜头将图像聚焦到图像传感器上，成千上万个光电二极管检测到落在其上的光线，并将其记录为像素数据。

> 💁 镜头会将图像倒置，摄像头传感器会将图像翻转回正确的方向。这与你的眼睛相同——你看到的图像在眼睛后部是倒置的，而你的大脑会将其校正。

> 🎓 图像传感器被称为有源像素传感器（APS），最常见的 APS 类型是互补金属氧化物半导体传感器，简称 CMOS。你可能听说过 CMOS 传感器这个术语。

摄像头传感器是数字传感器，通过数字数据发送图像数据，通常借助提供通信功能的库。摄像头使用像 SPI 这样的协议连接，以便发送大量数据——图像的数据量远大于温度传感器等传感器的单个数值。

✅ 物联网设备在图像大小方面有哪些限制？请思考特别是微控制器硬件的约束。

## 使用物联网设备捕获图像

你可以使用物联网设备捕获图像以进行分类。

### 任务 - 使用物联网设备捕获图像

按照相关指南，使用你的物联网设备捕获图像：

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [单板计算机 - 树莓派](pi-camera.md)
* [单板计算机 - 虚拟设备](virtual-device-camera.md)

## 发布你的图像分类器

你在上一课中训练了图像分类器。在从物联网设备使用它之前，你需要发布模型。

### 模型迭代

在上一课中训练模型时，你可能注意到 **性能** 选项卡的侧边显示了迭代。当你第一次训练模型时，会看到 *Iteration 1*。当你使用预测图像改进模型时，会看到 *Iteration 2*。

每次训练模型时，都会生成一个新的迭代。这是一种跟踪模型在不同数据集上训练的不同版本的方法。当你进行 **快速测试** 时，可以使用下拉菜单选择迭代，以便比较多个迭代的结果。

当你对某个迭代满意时，可以将其发布，使其可供外部应用使用。这样，你可以有一个已发布的版本供设备使用，同时在多个迭代中改进新版本，直到满意后再发布。

### 任务 - 发布一个迭代

迭代可以通过 Custom Vision 门户发布。

1. 打开 [CustomVision.ai](https://customvision.ai) 并登录（如果尚未打开）。然后打开你的 `fruit-quality-detector` 项目。

1. 从顶部选项中选择 **性能** 选项卡。

1. 从侧边的 *迭代* 列表中选择最新的迭代。

1. 点击该迭代的 **发布** 按钮。

    ![发布按钮](../../../../../translated_images/zh/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.png)

1. 在 *发布模型* 对话框中，将 *预测资源* 设置为你在上一课中创建的 `fruit-quality-detector-prediction` 资源。将名称保留为 `Iteration2`，然后点击 **发布** 按钮。

1. 发布后，点击 **预测 URL** 按钮。这将显示预测 API 的详细信息，你需要这些信息来从物联网设备调用模型。下方部分标记为 *如果你有一个图像文件*，这是你需要的详细信息。复制显示的 URL，类似于：

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    其中 `<location>` 是你创建自定义视觉资源时使用的位置，`<id>` 是由字母和数字组成的长 ID。

    同时复制 *预测密钥* 值。这是一个安全密钥，调用模型时必须传递。只有传递此密钥的应用程序才被允许使用模型，其他应用程序将被拒绝。

    ![预测 API 对话框显示 URL 和密钥](../../../../../translated_images/zh/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ 当一个新迭代被发布时，它会有一个不同的名称。你认为如何更改物联网设备使用的迭代？

## 从物联网设备分类图像

现在你可以使用这些连接详细信息从物联网设备调用图像分类器。

### 任务 - 从物联网设备分类图像

按照相关指南，使用你的物联网设备分类图像：

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [单板计算机 - 树莓派/虚拟物联网设备](single-board-computer-classify-image.md)

## 改进模型

你可能会发现，使用连接到物联网设备的摄像头时，预测结果与预期不符。预测的准确性可能不如从电脑上传的图像。这是因为模型是用不同的数据训练的，而不是用于预测的数据。

为了获得最佳的图像分类器结果，你需要用与预测图像尽可能相似的图像训练模型。例如，如果你用手机摄像头捕获图像进行训练，图像质量、清晰度和颜色会与物联网设备连接的摄像头不同。

![两张香蕉图片，一张是物联网设备拍摄的低分辨率、光线较差的图片，另一张是手机拍摄的高分辨率、光线良好的图片](../../../../../translated_images/zh/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.png)

在上图中，左边的香蕉图片是用树莓派摄像头拍摄的，右边的图片是用 iPhone 在同一位置拍摄的同一香蕉。可以明显看出质量差异——iPhone 的图片更清晰，颜色更鲜艳，对比度更高。

✅ 还有什么可能导致物联网设备捕获的图像预测不准确？思考物联网设备可能使用的环境，哪些因素会影响图像的捕获？

为了改进模型，你可以使用物联网设备捕获的图像重新训练它。

### 任务 - 改进模型

1. 使用你的物联网设备分类多张成熟和未成熟水果的图像。

1. 在 Custom Vision 门户中，使用 *预测* 选项卡上的图像重新训练模型。

    > ⚠️ 如果需要，可以参考 [第 1 课中重新训练分类器的说明](../1-train-fruit-detector/README.md#retrain-your-image-classifier)。

1. 如果你的图像与用于训练的原始图像差异很大，可以通过在 *训练图像* 选项卡中选择它们并点击 **删除** 按钮删除所有原始图像。将光标移到图像上会出现一个勾选框，点击勾选框即可选择或取消选择图像。

1. 训练模型的新迭代，并按照上述步骤发布。

1. 更新代码中的端点 URL，并重新运行应用程序。

1. 重复这些步骤，直到对预测结果满意为止。

---

## 🚀 挑战

图像分辨率或光线对预测的影响有多大？

尝试在设备代码中更改图像的分辨率，看看是否会影响图像质量。同时尝试更改光线条件。

如果你要创建一个用于销售给农场或工厂的生产设备，如何确保它始终提供一致的结果？

## 课后测验

[课后测验](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## 复习与自学

你使用门户训练了自定义视觉模型。这依赖于已有的图像——而在现实世界中，你可能无法获得与设备摄像头捕获的图像匹配的训练数据。你可以通过使用训练 API 直接从设备训练模型来解决这个问题，从而使用物联网设备捕获的图像进行训练。

* 阅读 [使用 Custom Vision SDK 快速入门](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python) 中的训练 API。

## 作业

[响应分类结果](assignment.md)

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。我们对于因使用本翻译而引起的任何误解或误读不承担责任。