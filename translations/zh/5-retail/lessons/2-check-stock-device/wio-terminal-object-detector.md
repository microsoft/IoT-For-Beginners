<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-24T21:13:43+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "zh"
}
-->
# 从物联网设备调用您的对象检测器 - Wio Terminal

一旦您的对象检测器发布后，就可以从您的物联网设备上使用它。

## 复制图像分类器项目

您的库存检测器的大部分内容与您在之前课程中创建的图像分类器是相同的。

### 任务 - 复制图像分类器项目

1. 按照[制造项目第2课](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera)中的步骤，将您的 ArduCam 连接到 Wio Terminal。

    您可能还需要将摄像头固定在一个位置，例如，将电缆挂在一个盒子或罐子上，或者用双面胶将摄像头固定在盒子上。

1. 使用 PlatformIO 创建一个全新的 Wio Terminal 项目。将此项目命名为 `stock-counter`。

1. 按照[制造项目第2课](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device)中的步骤，从摄像头捕获图像。

1. 按照[制造项目第2课](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device)中的步骤调用图像分类器。大部分代码将被重复使用来检测对象。

## 将代码从分类器更改为图像检测器

您用于分类图像的代码与用于检测对象的代码非常相似。主要区别在于您从 Custom Vision 获取的调用 URL，以及调用的结果。

### 任务 - 将代码从分类器更改为图像检测器

1. 在 `main.cpp` 文件顶部添加以下 include 指令：

    ```cpp
    #include <vector>
    ```

1. 将 `classifyImage` 函数重命名为 `detectStock`，包括函数名称和在 `buttonPressed` 函数中的调用。

1. 在 `detectStock` 函数上方声明一个阈值，用于过滤掉概率较低的检测结果：

    ```cpp
    const float threshold = 0.3f;
    ```

    与图像分类器每个标签只返回一个结果不同，对象检测器会返回多个结果，因此需要过滤掉概率较低的结果。

1. 在 `detectStock` 函数上方声明一个函数，用于处理预测结果：

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    该函数接收一个预测列表并将其打印到串口监视器。

1. 在 `detectStock` 函数中，将循环遍历预测结果的 `for` 循环内容替换为以下内容：

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    这段代码会遍历预测结果，将概率与阈值进行比较。所有概率高于阈值的预测结果会被添加到一个 `list` 中，并传递给 `processPredictions` 函数。

1. 上传并运行您的代码。将摄像头对准货架上的物品并按下 C 按钮。您将在串口监视器中看到输出：

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 您可能需要根据您的图像调整 `threshold` 到一个合适的值。

    您将能够看到拍摄的图像，以及这些值在 Custom Vision 的 **Predictions** 标签中显示。

    ![货架上的4罐番茄酱及预测结果，概率分别为35.8%、33.5%、25.7%和16.6%](../../../../../translated_images/zh/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 您可以在 [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) 文件夹中找到此代码。

😀 您的库存计数程序成功了！

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。原始语言的文档应被视为权威来源。对于关键信息，建议使用专业人工翻译。我们不对因使用此翻译而产生的任何误解或误读承担责任。