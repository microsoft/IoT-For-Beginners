<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-24T21:33:33+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "zh"
}
-->
# 捕获图像 - 虚拟物联网硬件

在本课程的这一部分，您将为虚拟物联网设备添加一个摄像头传感器，并从中读取图像。

## 硬件

虚拟物联网设备将使用一个模拟摄像头，该摄像头可以发送文件中的图像或来自您的网络摄像头的图像。

### 将摄像头添加到 CounterFit

要使用虚拟摄像头，您需要将其添加到 CounterFit 应用程序中。

#### 任务 - 将摄像头添加到 CounterFit

将摄像头添加到 CounterFit 应用程序。

1. 在您的计算机上创建一个名为 `fruit-quality-detector` 的文件夹，并在其中创建一个名为 `app.py` 的单一文件和一个 Python 虚拟环境，然后添加 CounterFit 的 pip 包。

    > ⚠️ 如果需要，您可以参考[第 1 课中创建和设置 CounterFit Python 项目的说明](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md)。

1. 安装一个额外的 Pip 包，用于安装一个 CounterFit shim，它可以通过模拟部分 [Picamera Pip 包](https://pypi.org/project/picamera/) 来与摄像头传感器通信。确保您是在激活虚拟环境的终端中安装此包。

    ```sh
    pip install counterfit-shims-picamera
    ```

1. 确保 CounterFit 网页应用程序正在运行。

1. 创建一个摄像头：

    1. 在 *Sensors* 面板的 *Create sensor* 框中，点击 *Sensor type* 下拉框并选择 *Camera*。

    1. 将 *Name* 设置为 `Picamera`。

    1. 选择 **Add** 按钮以创建摄像头。

    ![摄像头设置](../../../../../translated_images/zh/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    摄像头将被创建并显示在传感器列表中。

    ![摄像头已创建](../../../../../translated_images/zh/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## 编程摄像头

现在可以为虚拟物联网设备编程以使用虚拟摄像头。

### 任务 - 编程摄像头

为设备编程。

1. 确保 `fruit-quality-detector` 应用程序已在 VS Code 中打开。

1. 打开 `app.py` 文件。

1. 在 `app.py` 文件顶部添加以下代码以连接应用程序到 CounterFit：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. 在您的 `app.py` 文件中添加以下代码：

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    此代码导入了一些所需的库，包括来自 counterfit_shims_picamera 库的 `PiCamera` 类。

1. 在此代码下方添加以下代码以初始化摄像头：

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    此代码创建了一个 PiCamera 对象，并将分辨率设置为 640x480。虽然支持更高的分辨率，但图像分类器处理的图像尺寸较小（227x227），因此无需捕获和发送更大的图像。

    `camera.rotation = 0` 行设置图像的旋转角度（以度为单位）。如果需要旋转来自网络摄像头或文件的图像，请根据需要设置。例如，如果您想将网络摄像头中横向模式的香蕉图像更改为纵向模式，请设置 `camera.rotation = 90`。

1. 在此代码下方添加以下代码以将图像捕获为二进制数据：

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    此代码创建了一个 `BytesIO` 对象来存储二进制数据。图像以 JPEG 文件的形式从摄像头读取并存储在此对象中。此对象有一个位置指示器，用于指示数据的当前位置，以便可以在需要时将更多数据写入末尾，因此 `image.seek(0)` 行将此位置移回起始位置，以便稍后可以读取所有数据。

1. 在此代码下方添加以下代码以将图像保存到文件：

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    此代码打开一个名为 `image.jpg` 的文件进行写入，然后从 `BytesIO` 对象中读取所有数据并写入该文件。

    > 💁 您可以直接将图像捕获到文件，而不是使用 `BytesIO` 对象，只需将文件名传递给 `camera.capture` 调用即可。使用 `BytesIO` 对象的原因是稍后在本课程中，您可以将图像发送到您的图像分类器。

1. 配置 CounterFit 中摄像头将捕获的图像。您可以将 *Source* 设置为 *File*，然后上传一个图像文件，或者将 *Source* 设置为 *WebCam*，图像将从您的网络摄像头捕获。确保在选择图片或网络摄像头后点击 **Set** 按钮。

    ![CounterFit 中设置为文件的图像源，以及设置为网络摄像头显示一个人手持香蕉的预览](../../../../../translated_images/zh/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. 图像将被捕获并保存为当前文件夹中的 `image.jpg`。您将在 VS Code 的资源管理器中看到此文件。选择该文件以查看图像。如果需要旋转，请根据需要更新 `camera.rotation = 0` 行并重新拍摄图片。

> 💁 您可以在 [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device) 文件夹中找到此代码。

😀 您的摄像头程序运行成功！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。原始语言的文档应被视为权威来源。对于关键信息，建议使用专业人工翻译。我们不对因使用此翻译而产生的任何误解或误读承担责任。