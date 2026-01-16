<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-24T21:11:03+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "zh"
}
-->
# 使用物联网设备 Wio Terminal 统计库存

结合预测结果和它们的边界框，可以用来统计图像中的库存。

## 统计库存

![4罐番茄酱，每罐周围都有边界框](../../../../../translated_images/zh/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

在上图中，边界框之间有一些小的重叠。如果这种重叠更大，那么边界框可能会指向同一个物体。为了正确统计物体数量，需要忽略那些有显著重叠的边界框。

### 任务 - 忽略重叠统计库存

1. 如果尚未打开，请打开你的 `stock-counter` 项目。

1. 在 `processPredictions` 函数的上方，添加以下代码：

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    这段代码定义了边界框被认为是同一物体之前允许的重叠百分比。0.20 表示允许 20% 的重叠。

1. 在此代码下方，并在 `processPredictions` 函数的上方，添加以下代码以计算两个矩形之间的重叠面积：

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    这段代码定义了一个 `Point` 结构体，用于存储图像上的点，以及一个 `Rect` 结构体，用于使用左上角和右下角坐标定义矩形。然后定义了一个 `area` 函数，用于根据左上角和右下角坐标计算矩形的面积。

    接下来定义了一个 `overlappingArea` 函数，用于计算两个矩形的重叠面积。如果它们没有重叠，则返回 0。

1. 在 `overlappingArea` 函数的下方，声明一个函数，将边界框转换为 `Rect`：

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    该函数从对象检测器的预测中提取边界框，并使用边界框上的值定义一个矩形。右侧通过左侧加上宽度计算得出。底部通过顶部加上高度计算得出。

1. 需要将预测结果相互比较，如果两个预测的重叠超过阈值，则需要删除其中一个。重叠阈值是一个百分比，因此需要乘以最小边界框的大小，以检查重叠是否超过边界框的给定百分比，而不是整个图像的给定百分比。首先，删除 `processPredictions` 函数的内容。

1. 在空的 `processPredictions` 函数中添加以下内容：

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    这段代码声明了一个向量，用于存储没有重叠的预测结果。然后遍历所有预测结果，从边界框创建一个 `Rect`。

    接下来，这段代码遍历剩余的预测结果，从当前预测的下一个开始。这可以防止预测结果被多次比较——一旦 1 和 2 被比较过，就不需要再比较 2 和 1，只需要比较 2 和 3、4 等。

    对于每一对预测，计算它们的重叠面积。然后将其与最小边界框的面积进行比较——如果重叠超过最小边界框的阈值百分比，则该预测被标记为未通过。如果在比较所有重叠后，预测通过了检查，则将其添加到 `passed_predictions` 集合中。

    > 💁 这是一种非常简单的方式来移除重叠，只是移除了重叠对中的第一个。在生产代码中，你可能需要在这里加入更多逻辑，例如考虑多个物体之间的重叠，或者一个边界框是否被另一个边界框包含。

1. 在此之后，添加以下代码，将通过检查的预测结果的详细信息发送到串行监视器：

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    这段代码遍历通过检查的预测结果，并将它们的详细信息打印到串行监视器。

1. 在此代码下方，添加代码，将统计的物品数量打印到串行监视器：

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    然后可以将此数据发送到物联网服务，以在库存水平较低时发出警报。

1. 上传并运行你的代码。将摄像头对准货架上的物品并按下 C 按钮。尝试调整 `overlap_threshold` 值，观察预测结果被忽略的情况。

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 你可以在 [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) 文件夹中找到此代码。

😀 你的库存统计程序大获成功！

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用此翻译而引起的任何误解或误读不承担责任。