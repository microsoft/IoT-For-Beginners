<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-24T21:12:13+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "zh"
}
-->
# 从您的物联网设备统计库存 - 虚拟物联网硬件和树莓派

结合预测结果及其边界框，可以用来统计图像中的库存。

## 显示边界框

作为一个有用的调试步骤，您不仅可以打印出边界框，还可以将它们绘制在捕获图像时保存到磁盘的图像上。

### 任务 - 打印边界框

1. 确保在 VS Code 中打开了 `stock-counter` 项目，并且如果您使用的是虚拟物联网设备，请激活虚拟环境。

1. 将 `for` 循环中的 `print` 语句更改为以下内容，以将边界框打印到控制台：

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. 运行应用程序，并将摄像头对准货架上的一些库存。边界框将打印到控制台，左、上、宽度和高度的值范围为 0-1。

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### 任务 - 在图像上绘制边界框

1. Pip 包 [Pillow](https://pypi.org/project/Pillow/) 可用于在图像上绘制内容。使用以下命令安装它：

    ```sh
    pip3 install pillow
    ```

    如果您使用的是虚拟物联网设备，请确保在激活的虚拟环境中运行此命令。

1. 在 `app.py` 文件的顶部添加以下导入语句：

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    这将导入编辑图像所需的代码。

1. 在 `app.py` 文件的末尾添加以下代码：

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    这段代码打开之前保存的图像进行编辑。然后，它遍历预测结果，获取边界框，并使用 0-1 范围的边界框值计算右下角坐标。这些值通过乘以图像的相关维度转换为图像坐标。例如，如果左值为 0.5，而图像宽度为 600 像素，则转换为 300 (0.5 x 600 = 300)。

    每个边界框都用红线绘制在图像上。最后，编辑后的图像被保存，覆盖原始图像。

1. 运行应用程序，并将摄像头对准货架上的一些库存。您将在 VS Code 的资源管理器中看到 `image.jpg` 文件，并可以选择它查看边界框。

    ![4 罐番茄酱，每罐周围都有边界框](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.zh.jpg)

## 统计库存

在上图中，边界框有一些小的重叠。如果这种重叠更大，则边界框可能表示同一个对象。为了正确统计对象数量，您需要忽略具有显著重叠的边界框。

### 任务 - 忽略重叠统计库存

1. Pip 包 [Shapely](https://pypi.org/project/Shapely/) 可用于计算交集。如果您使用的是树莓派，您需要先安装一个库依赖项：

    ```sh
    sudo apt install libgeos-dev
    ```

1. 安装 Shapely Pip 包：

    ```sh
    pip3 install shapely
    ```

    如果您使用的是虚拟物联网设备，请确保在激活的虚拟环境中运行此命令。

1. 在 `app.py` 文件的顶部添加以下导入语句：

    ```python
    from shapely.geometry import Polygon
    ```

    这将导入创建多边形以计算重叠所需的代码。

1. 在绘制边界框的代码上方，添加以下代码：

    ```python
    overlap_threshold = 0.20
    ```

    这定义了允许的重叠百分比，超过该百分比的边界框将被视为同一个对象。0.20 定义了 20% 的重叠。

1. 要使用 Shapely 计算重叠，边界框需要转换为 Shapely 多边形。添加以下函数来完成此操作：

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    这会使用预测的边界框创建一个多边形。

1. 删除重叠对象的逻辑涉及比较所有边界框，如果任何预测对的边界框重叠超过阈值，则删除其中一个预测。为了比较所有预测，您需要将预测 1 与 2、3、4 等进行比较，然后将预测 2 与 3、4 等进行比较。以下代码实现了这一点：

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    重叠通过 Shapely 的 `Polygon.intersection` 方法计算，该方法返回一个表示重叠的多边形。然后从该多边形计算面积。此重叠阈值不是绝对值，而是需要作为边界框的百分比，因此找到最小的边界框，并使用重叠阈值计算允许的重叠面积。如果重叠超过此值，则将该预测标记为删除。

    一旦预测被标记为删除，就不需要再次检查，因此内层循环会跳出以检查下一个预测。您不能在遍历列表时删除列表中的项目，因此超过阈值的重叠边界框会被添加到 `to_delete` 列表中，然后在最后删除。

    最后，库存数量会打印到控制台。然后可以将其发送到物联网服务，以在库存水平较低时发出警报。所有这些代码都在绘制边界框之前，因此您将在生成的图像上看到没有重叠的库存预测。

    > 💁 这是一种非常简单的去除重叠的方法，仅删除重叠对中的第一个。在生产代码中，您可能需要添加更多逻辑，例如考虑多个对象之间的重叠，或者一个边界框是否被另一个边界框包含。

1. 运行应用程序，并将摄像头对准货架上的一些库存。输出将显示超过阈值的重叠被忽略后的边界框数量。尝试调整 `overlap_threshold` 值，观察预测被忽略的情况。

> 💁 您可以在 [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) 或 [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device) 文件夹中找到此代码。

😀 您的库存统计程序成功了！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。我们对于因使用此翻译而引起的任何误解或误读不承担责任。