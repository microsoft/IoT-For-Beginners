<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-24T21:47:29+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "zh"
}
-->
# 使用基于 IoT Edge 的图像分类器对图像进行分类 - 虚拟 IoT 硬件和 Raspberry Pi

在本课的这一部分中，您将使用运行在 IoT Edge 设备上的图像分类器。

## 使用 IoT Edge 分类器

IoT 设备可以被重新配置为使用 IoT Edge 图像分类器。图像分类器的 URL 是 `http://<IP address or name>/image`，将 `<IP address or name>` 替换为运行 IoT Edge 的计算机的 IP 地址或主机名。

Custom Vision 的 Python 库仅支持云托管的模型，而不支持托管在 IoT Edge 上的模型。这意味着您需要使用 REST API 来调用分类器。

### 任务 - 使用 IoT Edge 分类器

1. 如果尚未打开，请在 VS Code 中打开 `fruit-quality-detector` 项目。如果您使用的是虚拟 IoT 设备，请确保虚拟环境已激活。

1. 打开 `app.py` 文件，删除从 `azure.cognitiveservices.vision.customvision.prediction` 和 `msrest.authentication` 导入的语句。

1. 在文件顶部添加以下导入：

    ```python
    import requests
    ```

1. 删除保存图像到文件后从 `image_file.write(image.read())` 到文件末尾的所有代码。

1. 在文件末尾添加以下代码：

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    将 `<URL>` 替换为您的分类器的 URL。

    这段代码通过 REST POST 请求向分类器发送图像作为请求的主体。结果以 JSON 格式返回，并被解码以打印出概率。

1. 运行您的代码，使用摄像头对准一些水果，或者使用适当的图像集，或者如果使用虚拟 IoT 硬件，则确保水果在您的网络摄像头中可见。您将在控制台中看到输出：

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 您可以在 [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) 或 [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) 文件夹中找到这段代码。

😀 您的水果质量分类器程序运行成功！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对于因使用此翻译而引起的任何误解或误读不承担责任。