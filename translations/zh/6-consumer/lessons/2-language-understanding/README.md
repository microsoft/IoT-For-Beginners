<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-24T23:57:28+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "zh"
}
-->
# 理解语言

![本课的手绘笔记概览](../../../../../translated_images/zh/lesson-22.6148ea28500d9e00c396aaa2649935fb6641362c8f03d8e5e90a676977ab01dd.jpg)

> 手绘笔记由 [Nitya Narasimhan](https://github.com/nitya) 提供。点击图片查看更大版本。

## 课前测验

[课前测验](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## 简介

在上一课中，你将语音转换为文本。为了将其用于编写智能计时器程序，你的代码需要理解所说的内容。你可以假设用户会说固定短语，例如“设置一个3分钟的计时器”，并解析该表达式以确定计时器的时长，但这对用户来说并不友好。如果用户说“设置一个计时器，时间为3分钟”，你或我可以理解他们的意思，但你的代码却无法理解，因为它期待的是固定短语。

这就是语言理解的作用所在，它使用AI模型来解释文本并返回所需的细节。例如，它可以同时理解“设置一个3分钟的计时器”和“设置一个计时器，时间为3分钟”，并知道需要设置一个3分钟的计时器。

在本课中，你将学习语言理解模型，如何创建、训练它们，以及如何在代码中使用它们。

本课内容包括：

* [语言理解](../../../../../6-consumer/lessons/2-language-understanding)
* [创建语言理解模型](../../../../../6-consumer/lessons/2-language-understanding)
* [意图和实体](../../../../../6-consumer/lessons/2-language-understanding)
* [使用语言理解模型](../../../../../6-consumer/lessons/2-language-understanding)

## 语言理解

人类已经使用语言进行交流数十万年。我们通过词语、声音或动作进行交流，并理解所说的内容，包括词语、声音或动作的含义以及它们的上下文。我们能够理解真诚和讽刺，使得相同的词语在不同的语气下表达不同的意思。

✅ 想一想你最近的一些对话。哪些部分的对话对计算机来说可能很难理解，因为它需要上下文？

语言理解，也称为自然语言理解，是人工智能领域的一部分，属于自然语言处理（NLP）。它涉及阅读理解，试图理解词语或句子的细节。如果你使用过语音助手，例如Alexa或Siri，那么你已经使用过语言理解服务。这些服务是幕后AI服务，将“Alexa，播放Taylor Swift的最新专辑”转换为我女儿在客厅里随着她最喜欢的音乐跳舞。

> 💁 尽管计算机取得了许多进步，但它们在真正理解文本方面仍有很长的路要走。当我们提到计算机的语言理解时，并不是指任何接近人类交流的高级能力，而是指从一些词语中提取关键细节。

作为人类，我们无需思考就能理解语言。如果我让另一个人“播放Taylor Swift的最新专辑”，他们会本能地知道我的意思。对于计算机来说，这就困难得多。它需要将词语从语音转换为文本，并解析以下信息：

* 需要播放音乐
* 音乐是由艺术家Taylor Swift创作的
* 具体的音乐是一整张专辑，包含多首按顺序排列的曲目
* Taylor Swift有许多专辑，因此需要按时间顺序排序，最新发布的专辑是所需的

✅ 想一想你在提出请求时说过的一些句子，例如点咖啡或让家人递给你某样东西。试着将这些句子分解为计算机需要提取的信息。

语言理解模型是AI模型，旨在从语言中提取特定细节，然后通过迁移学习针对特定任务进行训练，就像你使用一小组图像训练自定义视觉模型一样。你可以使用一个模型，然后通过你希望它理解的文本对其进行训练。

## 创建语言理解模型

![LUIS标志](../../../../../translated_images/zh/luis-logo.5cb4f3e88c020ee6df4f614e8831f4a4b6809a7247bf52085fb48d629ef9be52.png)

你可以使用LUIS（Language Understanding Intelligent Service）创建语言理解模型，这是微软认知服务的一部分。

### 任务 - 创建一个创作资源

要使用LUIS，你需要创建一个创作资源。

1. 使用以下命令在你的`smart-timer`资源组中创建一个创作资源：

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    将`<location>`替换为创建资源组时使用的位置。

    > ⚠️ LUIS并非在所有地区都可用，如果你收到以下错误：
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > 请选择其他地区。

    这将创建一个免费级别的LUIS创作资源。

### 任务 - 创建一个语言理解应用

1. 在浏览器中打开LUIS门户 [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn)，并使用你用于Azure的同一账户登录。

1. 按照对话框中的说明选择你的Azure订阅，然后选择刚刚创建的`smart-timer-luis-authoring`资源。

1. 从*对话应用*列表中，选择**新建应用**按钮以创建一个新应用。将新应用命名为`smart-timer`，并将*文化*设置为你的语言。

    > 💁 有一个预测资源字段。你可以创建一个单独的资源用于预测，但免费创作资源每月允许1000次预测，足够开发使用，因此可以留空。

1. 阅读创建应用后出现的指南，了解训练语言理解模型所需的步骤。完成后关闭该指南。

## 意图和实体

语言理解基于*意图*和*实体*。意图是词语的目的，例如播放音乐、设置计时器或点餐。实体是意图所指的内容，例如专辑、计时器的时长或食物类型。模型解释的每个句子至少应有一个意图，并可选地包含一个或多个实体。

一些示例：

| 句子                                                | 意图             | 实体                                       |
| --------------------------------------------------- | ---------------- | ------------------------------------------ |
| “播放Taylor Swift的最新专辑”                        | *播放音乐*       | *Taylor Swift的最新专辑*                   |
| “设置一个3分钟的计时器”                             | *设置计时器*     | *3分钟*                                    |
| “取消我的计时器”                                    | *取消计时器*     | 无                                         |
| “点3个大号菠萝披萨和一个凯撒沙拉”                   | *点餐*           | *3个大号菠萝披萨*，*凯撒沙拉*              |

✅ 回想你之前想到的句子，这些句子的意图和实体是什么？

要训练LUIS，首先需要设置实体。这些实体可以是固定术语列表，也可以从文本中学习。例如，你可以提供菜单中可用食物的固定列表，并为每个词提供变体（或同义词），例如*茄子*和*eggplant*作为*茄子*的变体。LUIS还提供了可用的预定义实体，例如数字和位置。

对于设置计时器，你可以使用预定义的数字实体为时间创建一个实体，并为单位（如分钟和秒）创建另一个实体。每个单位可以有多个变体以涵盖单数和复数形式，例如minute和minutes。

定义实体后，你需要创建意图。这些意图是通过你提供的示例句子（称为话语）由模型学习的。例如，对于*设置计时器*意图，你可以提供以下句子：

* `设置一个1秒计时器`
* `设置一个计时器，时间为1分12秒`
* `设置一个3分钟计时器`
* `设置一个9分30秒计时器`

然后你需要告诉LUIS这些句子的哪些部分映射到实体：

![句子“设置一个计时器，时间为1分12秒”分解为实体](../../../../../translated_images/zh/sentence-as-intent-entities.301401696f992259.webp)

句子`设置一个计时器，时间为1分12秒`的意图是`设置计时器`。它还有2个实体，每个实体有2个值：

|            | 时间 | 单位   |
| ---------- | ---: | ------ |
| 1分钟      | 1    | 分钟   |
| 12秒       | 12   | 秒     |

为了训练一个好的模型，你需要提供一系列不同的示例句子，以涵盖人们可能提出相同请求的多种方式。

> 💁 与任何AI模型一样，训练时使用的数据越多且越准确，模型效果越好。

✅ 想一想你可能用不同方式提出相同请求并期望人类理解的情况。

### 任务 - 向语言理解模型添加实体

对于计时器，你需要添加2个实体——一个用于时间单位（分钟或秒），另一个用于分钟或秒的数量。

你可以在微软文档的[快速入门：在LUIS门户中构建应用](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn)中找到使用LUIS门户的说明。

1. 在LUIS门户中，选择*实体*选项卡并通过选择**添加预定义实体**按钮添加*数字*预定义实体，然后从列表中选择*数字*。

1. 使用**创建**按钮创建一个新的实体。将实体命名为`时间单位`，并将类型设置为*列表*。在*标准化值*列表中添加`分钟`和`秒`，并在*同义词*列表中添加单数和复数形式。每添加一个同义词后按`回车`键将其添加到列表中。

    | 标准化值 | 同义词          |
    | -------- | --------------- |
    | 分钟     | 分钟，分钟们    |
    | 秒       | 秒，秒们        |

### 任务 - 向语言理解模型添加意图

1. 在*意图*选项卡中，选择**创建**按钮以创建一个新意图。将此意图命名为`设置计时器`。

1. 在示例中，输入不同方式设置计时器的句子，包括分钟、秒以及分钟和秒的组合。示例可以包括：

    * `设置一个1秒计时器`
    * `设置一个4分钟计时器`
    * `设置一个四分钟六秒计时器`
    * `设置一个9分30秒计时器`
    * `设置一个计时器，时间为1分12秒`
    * `设置一个计时器，时间为3分钟`
    * `设置一个计时器，时间为3分1秒`
    * `设置一个计时器，时间为三分一秒`
    * `设置一个计时器，时间为1分1秒`
    * `设置一个计时器，时间为30秒`
    * `设置一个计时器，时间为1秒`

    混合使用数字的文字形式和数字形式，以便模型学习处理两者。

1. 每输入一个示例，LUIS会开始检测实体，并会下划线并标记它找到的任何实体。

    ![LUIS对示例中的数字和时间单位进行下划线标记](../../../../../translated_images/zh/luis-intent-examples.25716580b2d2723cf1bafdf277d015c7f046d8cfa20f27bddf3a0873ec45fab7.png)

### 任务 - 训练和测试模型

1. 配置好实体和意图后，可以使用顶部菜单中的**训练**按钮训练模型。选择此按钮，模型应在几秒钟内完成训练。训练期间按钮会变灰，完成后会重新启用。

1. 从顶部菜单中选择**测试**按钮以测试语言理解模型。输入文本，例如`设置一个计时器，时间为5分4秒`，然后按回车键。句子会出现在你输入的文本框下方的一个框中，下面会显示*最高意图*，即检测到的概率最高的意图。此意图应为`设置计时器`。意图名称后会显示检测到正确意图的概率。

1. 选择**检查**选项以查看结果的详细信息。你会看到最高得分意图及其百分比概率，以及检测到的实体列表。

1. 完成测试后关闭*测试*窗格。

### 任务 - 发布模型

要从代码中使用此模型，你需要发布它。从LUIS发布时，可以发布到测试环境或生产环境。在本课中，测试环境即可。

1. 在LUIS门户中，选择顶部菜单中的**发布**按钮。

1. 确保选择了*测试槽*，然后选择**完成**。发布应用后会看到通知。

1. 你可以使用curl进行测试。要构建curl命令，你需要三个值——端点、应用ID（App ID）和API密钥。这些值可以从顶部菜单中选择的**管理**选项卡中访问。

    1. 从*设置*部分复制应用ID
1. 在 *Azure Resources* 部分中，选择 *Authoring Resource*，然后复制 *Primary Key* 和 *Endpoint URL*。

1. 在命令提示符或终端中运行以下 curl 命令：

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    将 `<endpoint url>` 替换为 *Azure Resources* 部分中的 Endpoint URL。

    将 `<app id>` 替换为 *Settings* 部分中的 App ID。

    将 `<primary key>` 替换为 *Azure Resources* 部分中的 Primary Key。

    将 `<sentence>` 替换为您想要测试的句子。

1. 此调用的输出将是一个 JSON 文档，其中详细说明了查询、最高意图以及按类型分类的实体列表。

    ```JSON
    {
        "query": "set a timer for 45 minutes and 12 seconds",
        "prediction": {
            "topIntent": "set timer",
            "intents": {
                "set timer": {
                    "score": 0.97031575
                },
                "None": {
                    "score": 0.02205793
                }
            },
            "entities": {
                "number": [
                    45,
                    12
                ],
                "time-unit": [
                    [
                        "minute"
                    ],
                    [
                        "second"
                    ]
                ]
            }
        }
    }
    ```

    上述 JSON 是通过查询 `set a timer for 45 minutes and 12 seconds` 得到的：

    * `set timer` 是最高意图，概率为 97%。
    * 检测到两个 *number* 实体，分别是 `45` 和 `12`。
    * 检测到两个 *time-unit* 实体，分别是 `minute` 和 `second`。

## 使用语言理解模型

一旦发布，LUIS 模型可以通过代码调用。在之前的课程中，您使用了 IoT Hub 来处理与云服务的通信，发送遥测数据并监听命令。这种方式是非常异步的——一旦发送了遥测数据，代码不会等待响应，如果云服务宕机，您也不会知道。

对于智能计时器，我们希望立即获得响应，以便告诉用户计时器已设置，或者提醒他们云服务不可用。为此，我们的 IoT 设备将直接调用一个 Web 端点，而不是依赖 IoT Hub。

与其从 IoT 设备直接调用 LUIS，您可以使用无服务器代码并采用不同类型的触发器——HTTP 触发器。这允许您的函数应用监听 REST 请求并对其作出响应。这个函数将成为您的设备可以调用的 REST 端点。

> 💁 尽管您可以直接从 IoT 设备调用 LUIS，但使用类似无服务器代码的方式更好。这样，当您想更换调用的 LUIS 应用（例如训练了更好的模型或不同语言的模型）时，您只需更新云端代码，而无需重新部署到可能成千上万甚至数百万的 IoT 设备上。

### 任务 - 创建无服务器函数应用

1. 创建一个名为 `smart-timer-trigger` 的 Azure Functions 应用，并在 VS Code 中打开它。

1. 在此应用中添加一个名为 `speech-trigger` 的 HTTP 触发器，使用以下命令从 VS Code 终端中运行：

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    这将创建一个名为 `text-to-timer` 的 HTTP 触发器。

1. 通过运行函数应用来测试 HTTP 触发器。当它运行时，您将在输出中看到列出的端点：

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    通过在浏览器中加载 [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) URL 进行测试。

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### 任务 - 使用语言理解模型

1. LUIS 的 SDK 可通过 Pip 包获取。在 `requirements.txt` 文件中添加以下行以添加对该包的依赖：

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. 确保 VS Code 终端已激活虚拟环境，并运行以下命令安装 Pip 包：

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 如果遇到错误，您可能需要使用以下命令升级 pip：
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. 在 `local.settings.json` 文件中为您的 LUIS API Key、Endpoint URL 和 App ID 添加新条目，这些信息可以从 LUIS 门户的 **MANAGE** 选项卡中获取：

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    将 `<endpoint url>` 替换为 **MANAGE** 选项卡中 *Azure Resources* 部分的 Endpoint URL。格式为 `https://<location>.api.cognitive.microsoft.com/`。

    将 `<app id>` 替换为 **MANAGE** 选项卡中 *Settings* 部分的 App ID。

    将 `<primary key>` 替换为 **MANAGE** 选项卡中 *Azure Resources* 部分的 Primary Key。

1. 在 `__init__.py` 文件中添加以下导入：

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    这将导入一些系统库以及与 LUIS 交互的库。

1. 删除 `main` 方法的内容，并添加以下代码：

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    这将加载您在 `local.settings.json` 文件中为 LUIS 应用添加的值，创建一个带有 API Key 的凭据对象，然后创建一个 LUIS 客户端对象以与您的 LUIS 应用交互。

1. 这个 HTTP 触发器将通过 JSON 格式传递要理解的文本，文本位于名为 `text` 的属性中。以下代码从 HTTP 请求的正文中提取该值，并将其记录到控制台中。将此代码添加到 `main` 函数中：

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. 通过发送预测请求（包含要预测的文本的 JSON 文档）向 LUIS 请求预测。使用以下代码创建此请求：

    ```python
    prediction_request = { 'query' : text }
    ```

1. 然后可以将此请求发送到 LUIS，使用您的应用发布到的 staging 插槽：

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. 预测响应包含最高意图（预测分数最高的意图）以及实体。如果最高意图是 `set timer`，则可以读取实体以获取计时器所需的时间：

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    `number` 实体将是一个数字数组。例如，如果您说 *"Set a four minute 17 second timer."*，那么 `number` 数组将包含两个整数 - 4 和 17。

    `time unit` 实体将是一个字符串数组的数组，每个时间单位作为数组中的一个字符串。例如，如果您说 *"Set a four minute 17 second timer."*，那么 `time unit` 数组将包含两个数组，每个数组中有一个值 - `['minute']` 和 `['second']`。

    *"Set a four minute 17 second timer."* 的这些实体的 JSON 版本为：

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    此代码还定义了一个计时器总时间（以秒为单位）的计数器。该计数器将由实体中的值填充。

1. 实体之间没有直接关联，但我们可以对它们做一些假设。它们将按照语音中的顺序排列，因此可以使用数组中的位置来确定哪个数字对应哪个时间单位。例如：

    * *"Set a 30 second timer"* - 这将有一个数字 `30` 和一个时间单位 `second`，因此单个数字将匹配单个时间单位。
    * *"Set a 2 minute and 30 second timer"* - 这将有两个数字 `2` 和 `30`，以及两个时间单位 `minute` 和 `second`，因此第一个数字对应第一个时间单位（2 分钟），第二个数字对应第二个时间单位（30 秒）。

    以下代码获取数字实体中的项目数量，并使用该数量从每个数组中提取第一个项目，然后是第二个，依此类推。将此代码添加到 `if` 块中。

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    对于 *"Set a four minute 17 second timer."*，这将循环两次，给出以下值：

    | 循环计数 | `number` | `time_unit` |
    | -------: | -------: | ----------- |
    | 0        | 4        | minute      |
    | 1        | 17       | second      |

1. 在此循环中，使用数字和时间单位计算计时器的总时间，为每分钟添加 60 秒，为每秒添加相应的秒数。

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. 在遍历实体的循环之外，记录计时器的总时间：

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. 需要将秒数作为 HTTP 响应从函数返回。在 `if` 块的末尾添加以下内容：

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    此代码创建一个包含计时器总秒数的有效负载，将其转换为 JSON 字符串，并以状态码 200（表示调用成功）作为 HTTP 结果返回。

1. 最后，在 `if` 块之外，处理未识别意图的情况，返回错误代码：

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 是 *未找到* 的状态码。

1. 运行函数应用并使用 curl 进行测试。

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    将 `<text>` 替换为您的请求文本，例如 `set a 2 minutes 27 second timer`。

    您将看到函数应用的以下输出：

    ```output
    Functions:

            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    
    For detailed output, run func with --verbose flag.
    [2021-06-26T19:45:14.502Z] Worker process started and initialized.
    [2021-06-26T19:45:19.338Z] Host lock lease acquired by instance ID '000000000000000000000000951CAE4E'.
    [2021-06-26T19:45:52.059Z] Executing 'Functions.text-to-timer' (Reason='This function was programmatically called via the host APIs.', Id=f68bfb90-30e4-47a5-99da-126b66218e81)
    [2021-06-26T19:45:53.577Z] Timer required for 147 seconds
    [2021-06-26T19:45:53.746Z] Executed 'Functions.text-to-timer' (Succeeded, Id=f68bfb90-30e4-47a5-99da-126b66218e81, Duration=1750ms)
    ```

    curl 调用将返回以下内容：

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    计时器的秒数在 `"seconds"` 值中。

> 💁 您可以在 [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions) 文件夹中找到此代码。

### 任务 - 使您的函数可供 IoT 设备使用

1. 为了让您的 IoT 设备调用 REST 端点，它需要知道 URL。当您之前访问它时，您使用了 `localhost`，这是一个访问本地机器上 REST 端点的快捷方式。为了让 IoT 设备能够访问，您需要将其发布到云端，或者获取您的 IP 地址以便本地访问。

    > ⚠️ 如果您使用的是 Wio Terminal，建议本地运行函数应用，因为会有一些依赖库，导致无法像之前那样部署函数应用。如果您确实想部署到云端，后续课程将提供相关信息。

    * 发布 Functions 应用 - 按照之前课程中的说明将函数应用发布到云端。发布后，URL 将为 `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`，其中 `<APP_NAME>` 是您的函数应用名称。确保同时发布本地设置。

      使用 HTTP 触发器时，它们默认通过函数应用密钥进行保护。要获取此密钥，请运行以下命令：

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      从 `functionKeys` 部分复制 `default` 条目的值。

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      此密钥需要作为查询参数添加到 URL 中，因此最终的 URL 将为 `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`，其中 `<APP_NAME>` 是您的函数应用名称，`<FUNCTION_KEY>` 是您的默认函数密钥。

      > 💁 您可以通过修改 `function.json` 文件中的 `authlevel` 设置更改 HTTP 触发器的授权类型。您可以在 [Microsoft 文档中 Azure Functions HTTP 触发器文档的配置部分](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration) 中阅读更多内容。

    * 本地运行函数应用并通过 IP 地址访问 - 您可以获取计算机在本地网络中的 IP 地址，并使用该地址构建 URL。

      查找您的 IP 地址：

      * 在 Windows 10 上，按照 [查找 IP 地址指南](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn)。
      * 在 macOS 上，按照 [如何在 Mac 上查找 IP 地址指南](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac)。
      * 在 Linux 上，按照 [如何在 Linux 中查找 IP 地址指南](https://opensource.com/article/18/5/how-find-ip-address-linux) 中查找私有 IP 地址的部分。

      一旦您获取了 IP 地址，您将能够通过 `http://`
<IP地址>
:7071/api/text-to-timer`，其中 `<IP_ADDRESS>` 是你的IP地址，例如 `http://192.168.1.10:7071/api/text-to-timer`。

      > 💁 请注意，这里使用的是端口7071，因此在IP地址后需要加上 `:7071`。

      > 💁 这仅在你的IoT设备与电脑处于同一网络时有效。

1. 使用curl测试该端点。

---

## 🚀 挑战

设置一个计时器有很多种请求方式。想一想不同的表达方式，并将它们作为示例添加到你的LUIS应用中。测试这些表达方式，看看你的模型能否处理多种请求计时器的方式。

## 课后测验

[课后测验](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## 复习与自学

* 在 [Microsoft文档上的语言理解（LUIS）页面](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn) 阅读更多关于LUIS及其功能的信息
* 在 [维基百科的自然语言理解页面](https://wikipedia.org/wiki/Natural-language_understanding) 阅读更多关于语言理解的信息
* 在 [Microsoft文档上的Azure Functions HTTP触发器页面](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python) 阅读更多关于HTTP触发器的信息

## 作业

[取消计时器](assignment.md)

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用此翻译而引起的任何误解或误读不承担责任。