<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-24T21:29:02+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "zh"
}
-->
# 捕捉图像 - 树莓派

在本课程的这一部分，你将为树莓派添加一个摄像头传感器，并从中读取图像。

## 硬件

树莓派需要一个摄像头。

你将使用的摄像头是 [树莓派摄像头模块](https://www.raspberrypi.org/products/camera-module-v2/)。这个摄像头专为树莓派设计，通过树莓派上的专用连接器连接。

> 💁 这个摄像头使用 [摄像头串行接口（Camera Serial Interface），一种由移动产业处理器接口联盟开发的协议](https://wikipedia.org/wiki/Camera_Serial_Interface)，简称 MIPI-CSI。这是一种专用的图像传输协议。

## 连接摄像头

摄像头可以通过一条扁平电缆连接到树莓派。

### 任务 - 连接摄像头

![树莓派摄像头](../../../../../translated_images/zh/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. 关闭树莓派的电源。

1. 将摄像头附带的扁平电缆连接到摄像头上。为此，轻轻拉动插座中的黑色塑料夹，使其稍微弹出，然后将电缆滑入插座，蓝色一面朝向镜头外侧，金属针脚条朝向镜头。插入到位后，将黑色塑料夹推回原位。

    你可以在 [树莓派摄像头模块入门文档](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2) 中找到一个动画，展示如何打开夹子并插入电缆。

    ![扁平电缆插入摄像头模块](../../../../../translated_images/zh/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. 从树莓派上移除 Grove Base Hat。

1. 将扁平电缆穿过 Grove Base Hat 的摄像头插槽。确保电缆的蓝色一面朝向标有 **A0**、**A1** 等的模拟端口。

    ![扁平电缆穿过 Grove Base Hat](../../../../../translated_images/zh/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. 将扁平电缆插入树莓派上的摄像头端口。同样，拉起黑色塑料夹，插入电缆，然后将夹子推回。电缆的蓝色一面应朝向 USB 和以太网端口。

    ![扁平电缆连接到树莓派的摄像头插座](../../../../../translated_images/zh/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. 重新安装 Grove Base Hat。

## 编程摄像头

现在可以使用 [PiCamera](https://pypi.org/project/picamera/) Python 库对树莓派进行编程以使用摄像头。

### 任务 - 启用传统摄像头模式

不幸的是，随着树莓派操作系统 Bullseye 的发布，操作系统附带的摄像头软件发生了变化，默认情况下 PiCamera 不再工作。目前正在开发一个替代方案，名为 PiCamera2，但尚未准备好使用。

目前，你可以将树莓派设置为传统摄像头模式，以使 PiCamera 工作。摄像头插座默认也是禁用的，但启用传统摄像头软件会自动启用插座。

1. 启动树莓派并等待其完成启动。

1. 启动 VS Code，可以直接在树莓派上运行，也可以通过 Remote SSH 扩展连接。

1. 在终端中运行以下命令：

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    这将切换设置以启用传统摄像头软件，然后重启树莓派以使设置生效。

1. 等待树莓派重启，然后重新启动 VS Code。

### 任务 - 编程摄像头

对设备进行编程。

1. 在终端中，在 `pi` 用户的主目录中创建一个名为 `fruit-quality-detector` 的新文件夹。在此文件夹中创建一个名为 `app.py` 的文件。

1. 在 VS Code 中打开此文件夹。

1. 要与摄像头交互，可以使用 PiCamera Python 库。使用以下命令安装 Pip 包：

    ```sh
    pip3 install picamera
    ```

1. 将以下代码添加到你的 `app.py` 文件中：

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    这段代码导入了一些需要的库，包括 `PiCamera` 库。

1. 在此代码下方添加以下代码以初始化摄像头：

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    这段代码创建了一个 PiCamera 对象，并将分辨率设置为 640x480。虽然支持更高的分辨率（最高 3280x2464），但图像分类器使用的图像尺寸要小得多（227x227），因此无需捕获和发送更大的图像。

    `camera.rotation = 0` 行设置图像的旋转角度。扁平电缆从摄像头底部进入，但如果你的摄像头旋转过以便更容易对准你想要分类的物品，则可以将此行更改为旋转的角度。

    ![摄像头悬挂在饮料罐上方](../../../../../translated_images/zh/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    例如，如果你将扁平电缆悬挂在某物上，使其位于摄像头顶部，则将旋转设置为 180：

    ```python
    camera.rotation = 180
    ```

    摄像头需要几秒钟启动，因此有 `time.sleep(2)`。

1. 在此代码下方添加以下代码以将图像捕获为二进制数据：

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    这段代码创建了一个 `BytesIO` 对象来存储二进制数据。图像以 JPEG 文件的形式从摄像头读取并存储在此对象中。此对象有一个位置指示器，用于指示数据中的当前位置，以便需要时可以将更多数据写入末尾，因此 `image.seek(0)` 行将位置移回起始位置，以便稍后可以读取所有数据。

1. 在此代码下方添加以下代码以将图像保存到文件：

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    这段代码打开一个名为 `image.jpg` 的文件进行写入，然后从 `BytesIO` 对象中读取所有数据并写入该文件。

    > 💁 你可以直接将图像捕获到文件，而不是使用 `BytesIO` 对象，只需将文件名传递给 `camera.capture` 调用即可。使用 `BytesIO` 对象的原因是稍后在本课程中你可以将图像发送到图像分类器。

1. 将摄像头对准某物并运行此代码。

1. 图像将被捕获并保存为当前文件夹中的 `image.jpg`。你将在 VS Code 的资源管理器中看到此文件。选择该文件以查看图像。如果需要旋转，请根据需要更新 `camera.rotation = 0` 行并重新拍摄照片。

> 💁 你可以在 [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi) 文件夹中找到此代码。

😀 你的摄像头程序运行成功！

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本作为权威来源。对于关键信息，建议使用专业人工翻译。我们对于因使用本翻译而引起的任何误解或误读不承担责任。