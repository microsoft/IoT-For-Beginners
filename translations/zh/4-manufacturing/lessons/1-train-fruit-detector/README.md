<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f5e63c916d2dd97d58be12aaf76bd9f1",
  "translation_date": "2025-08-24T21:20:11+00:00",
  "source_file": "4-manufacturing/lessons/1-train-fruit-detector/README.md",
  "language_code": "zh"
}
-->
# 训练水果质量检测器

![本课的手绘笔记概览](../../../../../translated_images/lesson-15.843d21afdc6fb2bba70cd9db7b7d2f91598859fafda2078b0bdc44954194b6c0.zh.jpg)

> 手绘笔记由 [Nitya Narasimhan](https://github.com/nitya) 提供。点击图片查看大图。

这段视频概述了 Azure Custom Vision 服务，这是本课将要介绍的服务。

[![Custom Vision – 让机器学习变得简单 | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 点击上方图片观看视频

## 课前测验

[课前测验](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## 简介

近年来，人工智能（AI）和机器学习（ML）的兴起为当今的开发者提供了广泛的能力。通过训练机器学习模型，可以识别图像中的不同事物，包括未成熟的水果。这些技术可以应用于物联网设备，帮助在收获或工厂、仓库的加工过程中对农产品进行分类。

在本课中，您将学习图像分类——使用机器学习模型区分不同事物的图像。您将学习如何训练一个图像分类器，以区分优质水果和劣质水果，例如未成熟、过熟、碰伤或腐烂的水果。

本课内容包括：

* [使用 AI 和 ML 对食品进行分类](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [通过机器学习进行图像分类](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [训练图像分类器](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [测试您的图像分类器](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [重新训练您的图像分类器](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## 使用 AI 和 ML 对食品进行分类

养活全球人口是一项艰巨的任务，尤其是在确保食品价格对所有人都负担得起的情况下。劳动力成本是其中最大的开支之一，因此农民越来越多地转向自动化和物联网等工具来降低劳动力成本。手工收割劳动强度大（且常常是非常辛苦的工作），在富裕国家尤其被机械化所取代。然而，尽管使用机械收割降低了成本，但也带来了一个问题——无法在收割时对食品进行分类。

并非所有作物都会均匀成熟。例如，西红柿在大部分成熟时，藤上可能仍有一些绿色果实。尽管提前收割这些果实是一种浪费，但对农民来说，用机械一次性收割所有果实并在之后处理未成熟的果实更便宜、更方便。

✅ 观察一下您附近农场或花园中生长的水果或蔬菜，或者商店里的水果或蔬菜。它们是否都成熟度一致，还是存在差异？

自动化收割的兴起将农产品的分类从田间转移到了工厂。在工厂中，食品通过长长的传送带运输，由人工团队挑选出不符合质量标准的产品。尽管机械化收割降低了收割成本，但人工分类仍然需要一定的费用。

![如果检测到红色西红柿，它会继续前进。如果检测到绿色西红柿，杠杆会将其弹入废料箱](../../../../../translated_images/optical-tomato-sorting.61aa134bdda4e5b1bfb16a212c1e35a6ef0c426cbb8b1c975f79d7bfbf48d068.zh.png)

下一步的进化是使用机器进行分类，这些机器可以内置在收割机中或位于加工厂中。第一代此类机器使用光学传感器检测颜色，通过控制执行器将绿色西红柿用杠杆或气流弹入废料箱，而红色西红柿则继续沿传送带网络前进。

在这段视频中，当西红柿从一个传送带掉到另一个传送带时，绿色西红柿会被检测到并用杠杆弹入废料箱。

✅ 在工厂或田间，这些光学传感器需要什么样的条件才能正常工作？

最新一代的分类机器利用了 AI 和 ML 的优势，使用经过训练的模型来区分优质和劣质农产品。不仅可以通过明显的颜色差异（如绿色西红柿与红色西红柿）进行区分，还可以通过更细微的外观差异（如疾病或碰伤）来判断。

## 通过机器学习进行图像分类

传统编程是将数据与算法结合，生成输出。例如，在上一个项目中，您将 GPS 坐标和地理围栏作为输入，应用 Azure Maps 提供的算法，得到点是否在地理围栏内的结果。输入更多数据，就会得到更多输出。

![传统开发使用输入和算法生成输出。机器学习使用输入和输出数据训练模型，该模型可以用新输入数据生成新输出](../../../../../translated_images/traditional-vs-ml.5c20c169621fa539.zh.png)

机器学习则颠倒了这一过程——您从数据和已知输出开始，机器学习算法从数据中学习。然后，您可以将训练好的算法（称为*机器学习模型*或*模型*）应用于新数据，生成新的输出。

> 🎓 机器学习算法从数据中学习的过程称为*训练*。输入和已知输出称为*训练数据*。

例如，您可以向模型提供数百万张未成熟香蕉的图片作为输入训练数据，并将训练输出设置为 `未成熟`，同时提供数百万张成熟香蕉的图片作为训练数据，并将输出设置为 `成熟`。机器学习算法会根据这些数据创建一个模型。然后，您可以向该模型提供一张新的香蕉图片，它会预测这张图片中的香蕉是成熟还是未成熟。

> 🎓 机器学习模型的结果称为*预测*

![两根香蕉，一根成熟的预测为 99.7% 成熟，0.3% 未成熟；另一根未成熟的预测为 1.4% 成熟，98.6% 未成熟](../../../../../translated_images/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50ece4e4589e724b142da0681f35470fe3db3f7d51240f69c85.zh.png)

机器学习模型不会给出二元答案，而是提供概率。例如，一个模型可能会对一张香蕉图片预测 `成熟` 的概率为 99.7%，`未成熟` 的概率为 0.3%。您的代码会选择最优预测，并判断这根香蕉是成熟的。

用于检测图像的机器学习模型称为*图像分类器*——它接收带标签的图像，然后根据这些标签对新图像进行分类。

> 💁 这是一个简化的描述，还有许多其他训练模型的方法，例如无需带标签输出的无监督学习。如果您想了解更多关于机器学习的知识，可以查看 [机器学习初学者课程，一个包含 24 节课的机器学习课程](https://aka.ms/ML-beginners)。

## 训练图像分类器

要成功训练一个图像分类器，您需要数百万张图片。然而，事实证明，一旦您拥有一个经过数百万或数十亿张各种图片训练的图像分类器，您可以通过一个称为*迁移学习*的过程，使用少量图片重新训练它，并获得出色的结果。

> 🎓 迁移学习是将现有机器学习模型的学习成果转移到基于新数据的新模型中。

一旦图像分类器经过广泛的图片训练，其内部结构就非常擅长识别形状、颜色和模式。迁移学习允许模型利用其已经学会的图像部分识别能力，来识别新图像。

![一旦您能识别形状，它们可以以不同的配置组成一艘船或一只猫](../../../../../translated_images/shapes-to-images.1a309f0ea88dd66f.zh.png)

您可以将其类比为儿童的形状书，一旦您能识别半圆形、矩形和三角形，您就能根据这些形状的配置识别出一艘帆船或一只猫。图像分类器可以识别这些形状，而迁移学习则教会它什么样的组合是船或猫——或者是成熟的香蕉。

有许多工具可以帮助您完成这一过程，包括可以帮助您训练模型并通过 Web API 使用它的基于云的服务。

> 💁 训练这些模型需要大量的计算能力，通常通过图形处理单元（GPU）实现。与让 Xbox 游戏画面看起来惊艳的硬件类似，GPU 也可以用来训练机器学习模型。通过云服务，您可以租用配备 GPU 的强大计算机来训练这些模型，仅在需要时使用所需的计算能力。

## Custom Vision

Custom Vision 是一个基于云的工具，用于训练图像分类器。它允许您仅使用少量图片训练分类器。您可以通过 Web 门户、Web API 或 SDK 上传图片，并为每张图片添加一个*标签*，表示该图片的分类。然后，您可以训练模型并测试其性能。一旦对模型满意，您可以发布其版本，通过 Web API 或 SDK 访问。

![Azure Custom Vision 标志](../../../../../translated_images/custom-vision-logo.d3d4e7c8a87ec9daf825e72e210576c3cbf60312577be7a139e22dd97ab7f1e6.zh.png)

> 💁 您可以用每个分类仅 5 张图片训练一个 Custom Vision 模型，但图片越多效果越好。至少 30 张图片可以获得更好的结果。

Custom Vision 是 Microsoft 提供的一系列 AI 工具（称为 Cognitive Services）的一部分。这些 AI 工具可以无需训练或仅需少量训练即可使用，包括语音识别与翻译、语言理解和图像分析。这些服务在 Azure 中提供免费层。

> 💁 免费层足以创建模型、训练它并用于开发工作。您可以在 [Microsoft 文档上的 Custom Vision 限制和配额页面](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn) 阅读免费层的限制。

### 任务 - 创建认知服务资源

要使用 Custom Vision，您需要先使用 Azure CLI 在 Azure 中创建两个认知服务资源，一个用于 Custom Vision 训练，一个用于 Custom Vision 预测。

1. 为此项目创建一个名为 `fruit-quality-detector` 的资源组。

1. 使用以下命令创建一个免费的 Custom Vision 训练资源：

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    将 `<location>` 替换为创建资源组时使用的位置。

    这将会在您的资源组中创建一个 Custom Vision 训练资源。它将被命名为 `fruit-quality-detector-training`，并使用 `F0` SKU（免费层）。`--yes` 选项表示您同意认知服务的条款和条件。

> 💁 如果您已经在任何认知服务中使用了免费账户，请使用 `S0` SKU。

1. 使用以下命令创建一个免费的 Custom Vision 预测资源：

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    将 `<location>` 替换为创建资源组时使用的位置。

    这将会在您的资源组中创建一个 Custom Vision 预测资源。它将被命名为 `fruit-quality-detector-prediction`，并使用 `F0` SKU（免费层）。`--yes` 选项表示您同意认知服务的条款和条件。

### 任务 - 创建图像分类器项目

1. 打开 [CustomVision.ai](https://customvision.ai) 的 Custom Vision 门户，并使用您的 Azure 账户关联的 Microsoft 账户登录。

1. 按照 [Microsoft 文档中构建分类器快速入门的“创建新项目”部分](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project) 创建一个新的 Custom Vision 项目。UI 可能会有所变化，这些文档始终是最新的参考。

    将您的项目命名为 `fruit-quality-detector`。

    创建项目时，请确保使用之前创建的 `fruit-quality-detector-training` 资源。选择*分类*项目类型、*多分类*分类类型，并选择*食品*领域。

    ![Custom Vision 项目的设置，名称为 fruit-quality-detector，无描述，资源为 fruit-quality-detector-training，项目类型为分类，分类类型为多分类，领域为食品](../../../../../translated_images/custom-vision-create-project.cf46325b92d8b131089f6647cf5e07b664cb77850e106d66e3c057b6b69756c6.zh.png)

✅ 花些时间探索您的图像分类器的 Custom Vision UI。

### 任务 - 训练您的图像分类器项目

要训练图像分类器，您需要多张水果的图片，包括优质和劣质的水果图片，并为其添加标签，例如成熟和过熟的香蕉。
💁 这些分类器可以对任何图像进行分类，所以如果你手头没有质量不同的水果，你可以用两种不同类型的水果，或者猫和狗！
理想情况下，每张图片应该只包含水果，背景要么保持一致，要么有多种背景。确保背景中没有任何与成熟或未成熟水果相关的特定内容。

> 💁 重要的是不要使用特定的背景或与分类标签无关的物品，否则分类器可能会根据背景进行分类。例如，有一个皮肤癌分类器，它被训练用来区分正常和癌变的痣，而癌变的痣旁边总是有尺子用来测量大小。结果发现，这个分类器几乎100%准确地识别图片中的尺子，而不是癌变的痣。

图像分类器运行时分辨率非常低。例如，Custom Vision可以处理最大10240x10240的训练和预测图像，但模型实际上是在227x227的图像上训练和运行的。较大的图像会被缩小到这个尺寸，因此确保你要分类的物体在图像中占据较大的部分，否则在分类器使用的小图像中可能会太小。

1. 收集分类器所需的图片。每个标签至少需要5张图片来训练分类器，但越多越好。此外，还需要一些额外的图片来测试分类器。这些图片应该是同一物体的不同图片。例如：

    * 使用2个成熟的香蕉，从不同角度为每个香蕉拍摄几张图片，至少拍摄7张（5张用于训练，2张用于测试），但理想情况下更多。

        ![两根不同香蕉的照片](../../../../../translated_images/banana-training-images.530eb203346d73bc23b8b990fb4609470bf4ff7c942ccc13d4cfffeed9be1ad4.zh.png)

    * 对2个未成熟的香蕉重复相同的过程。

    你应该至少有10张训练图片，其中至少5张成熟的，5张未成熟的，以及4张测试图片，2张成熟的，2张未成熟的。图片格式应为png或jpeg，大小小于6MB。如果你使用iPhone拍摄，它们可能是高分辨率的HEIC格式图片，因此需要转换并可能缩小。图片越多越好，并且成熟和未成熟的图片数量应该相近。

    如果你没有成熟和未成熟的水果，可以使用不同的水果，或者任何你手头上的两个物体。你也可以在[images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images)文件夹中找到一些成熟和未成熟香蕉的示例图片供你使用。

1. 按照[Microsoft文档中构建分类器快速入门的上传和标记图片部分](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images)上传你的训练图片。将成熟的水果标记为`ripe`，未成熟的水果标记为`unripe`。

    ![上传成熟和未成熟香蕉图片的对话框](../../../../../translated_images/image-upload-bananas.0751639f3815e0ec42bdbc6254d1e4357a185834d1ae10c9948a0e7d6d336695.zh.png)

1. 按照[Microsoft文档中构建分类器快速入门的训练分类器部分](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier)训练你的图像分类器。

    你将会看到训练类型的选择。选择**快速训练**。

分类器将开始训练。训练完成需要几分钟时间。

> 🍌 如果你决定在分类器训练期间吃掉你的水果，请确保你有足够的图片用于测试！

## 测试你的图像分类器

分类器训练完成后，你可以通过提供一张新图片来测试它的分类能力。

### 任务 - 测试你的图像分类器

1. 按照[Microsoft文档中测试模型的文档](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model)测试你的图像分类器。使用你之前创建的测试图片，而不是任何用于训练的图片。

    ![一个未成熟香蕉被预测为未成熟，概率为98.9%，成熟概率为1.1%](../../../../../translated_images/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64886422438850ea14f0be6ac918c217ea3b255c685abfabe7.zh.png)

1. 尝试使用你所有的测试图片，并观察概率。

## 重新训练你的图像分类器

当你测试分类器时，它可能不会给出你预期的结果。图像分类器使用机器学习根据图像中的特定特征来预测它是否匹配某个标签。这是基于概率的，而不是理解图像中的内容——它不知道什么是香蕉，也不理解香蕉为什么是香蕉而不是船。你可以通过使用分类器错误分类的图片重新训练它来改进分类器。

每次使用快速测试选项进行预测时，图片和结果都会被存储。你可以使用这些图片重新训练你的模型。

### 任务 - 重新训练你的图像分类器

1. 按照[Microsoft文档中使用预测图片进行训练的文档](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training)重新训练你的模型，为每张图片使用正确的标签。

1. 模型重新训练完成后，使用新图片进行测试。

---

## 🚀 挑战

你认为如果使用一张草莓的图片测试一个训练了香蕉的模型会发生什么？或者使用充气香蕉的图片、穿香蕉服装的人的图片，甚至是黄色卡通人物（比如《辛普森一家》中的角色）会发生什么？

试试看，观察预测结果。你可以使用[Bing图片搜索](https://www.bing.com/images/trending)找到图片进行尝试。

## 课后测验

[课后测验](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## 复习与自学

* 当你训练分类器时，你会看到*Precision*（精度）、*Recall*（召回率）和*AP*（平均精度）等值，这些值用于评估创建的模型。通过[Microsoft文档中构建分类器快速入门的评估分类器部分](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier)了解这些值的含义。
* 阅读[Microsoft文档中如何改进你的Custom Vision模型](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn)以了解如何改进你的分类器。

## 作业

[为多种水果和蔬菜训练你的分类器](assignment.md)

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。原始语言的文档应被视为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用此翻译而产生的任何误解或误读不承担责任。