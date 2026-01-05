<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f2d2f4a5a023c93ab34a0cc5b47c0c4",
  "translation_date": "2025-08-24T22:20:07+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/README.md",
  "language_code": "zh"
}
-->
# 将应用程序逻辑迁移到云端

![本课的手绘笔记概览](../../../../../translated_images/lesson-9.dfe99c8e891f48e179724520da9f5794392cf9a625079281ccdcbf09bd85e1b6.zh.jpg)

> 手绘笔记由 [Nitya Narasimhan](https://github.com/nitya) 提供。点击图片查看更大版本。

本课程是 [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) 的 [IoT 初学者项目 2 - 数字农业系列](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) 的一部分。

[![使用无服务器代码控制您的 IoT 设备](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## 课前测验

[课前测验](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## 简介

在上一课中，您学习了如何将植物土壤湿度监测和继电器控制连接到基于云的 IoT 服务。下一步是将控制继电器定时的服务器代码迁移到云端。在本课中，您将学习如何使用无服务器函数来完成这一任务。

本课内容包括：

* [什么是无服务器？](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [创建无服务器应用程序](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [创建 IoT Hub 事件触发器](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [从无服务器代码发送直接方法请求](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [将无服务器代码部署到云端](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## 什么是无服务器？

无服务器（或无服务器计算）是指创建在云端运行的小型代码块，这些代码块会根据不同类型的事件触发运行。当事件发生时，您的代码会运行，并接收有关事件的数据。这些事件可以来自许多不同的来源，包括网络请求、队列中的消息、数据库中的数据变化，或 IoT 设备发送到 IoT 服务的消息。

![事件从 IoT 服务发送到无服务器服务，同时由多个函数处理](../../../../../translated_images/iot-messages-to-serverless.0194da1cc0732bb7d0f823aed3fce54735c6b1ad3bf36089804d8aaefc0a774f.zh.png)

> 💁 如果您之前使用过数据库触发器，可以将其类比为代码因事件（如插入一行数据）而触发。

![当许多事件同时发送时，无服务器服务会扩展以同时运行所有事件](../../../../../translated_images/serverless-scaling.f8c769adf0413fd1.zh.png)

您的代码仅在事件发生时运行，其他时间不会保持活动状态。事件发生时，代码会被加载并运行。这使得无服务器非常具有扩展性——如果许多事件同时发生，云提供商可以根据需要同时运行您的函数，利用其可用的服务器资源。缺点是，如果需要在事件之间共享信息，必须将其存储在数据库等地方，而不能存储在内存中。

您的代码以函数的形式编写，函数会将事件的详细信息作为参数传递。您可以使用多种编程语言来编写这些无服务器函数。

> 🎓 无服务器也被称为函数即服务（FaaS），因为每个事件触发器都在代码中实现为一个函数。

尽管名字叫“无服务器”，但实际上还是使用了服务器。之所以命名为“无服务器”，是因为作为开发者，您无需关心运行代码所需的服务器，只需关心代码是否因事件而运行。云提供商有一个无服务器*运行时*，负责管理服务器分配、网络、存储、CPU、内存以及运行代码所需的一切。这种模式意味着您无法按服务器付费，而是按代码运行的时间和使用的内存付费。

> 💰 无服务器是运行云端代码最经济的方式之一。例如，在撰写本文时，一家云提供商允许您的所有无服务器函数每月总共执行 1,000,000 次，超过后每 1,000,000 次执行收费 0.20 美元。当您的代码未运行时，您无需支付费用。

作为 IoT 开发者，无服务器模型非常理想。您可以编写一个函数，响应任何连接到云托管 IoT 服务的 IoT 设备发送的消息。您的代码将处理所有发送的消息，但仅在需要时运行。

✅ 回顾您编写的服务器代码，该代码通过 MQTT 监听消息。如何在云端使用无服务器运行这些代码？您认为代码需要做哪些修改以支持无服务器计算？

> 💁 无服务器模型正在扩展到其他云服务，不仅限于运行代码。例如，云端的无服务器数据库使用无服务器定价模型，按对数据库的请求（如查询或插入）收费，通常基于完成请求所需的工作量定价。例如，针对主键选择一行的简单查询成本低于连接多个表并返回数千行的复杂操作。

## 创建无服务器应用程序

Microsoft 的无服务器计算服务称为 Azure Functions。

![Azure Functions 标志](../../../../../translated_images/azure-functions-logo.1cfc8e3204c9c44aaf80fcf406fc8544d80d7f00f8d3e8ed6fed764563e17564.zh.png)

以下短视频概述了 Azure Functions：

[![Azure Functions 概述视频](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 点击上方图片观看视频

✅ 花点时间研究并阅读 [Microsoft Azure Functions 文档](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn) 中的 Azure Functions 概述。

要编写 Azure Functions，您需要选择一种编程语言并创建 Azure Functions 应用程序。Azure Functions 原生支持 Python、JavaScript、TypeScript、C#、F#、Java 和 Powershell。在本课中，您将学习如何使用 Python 编写 Azure Functions 应用程序。

> 💁 Azure Functions 还支持自定义处理程序，因此您可以使用任何支持 HTTP 请求的语言编写函数，包括较旧的语言如 COBOL。

Functions 应用程序由一个或多个*触发器*组成——响应事件的函数。一个 Functions 应用程序可以包含多个触发器，共享通用配置。例如，您的 Functions 应用程序的配置文件可以包含 IoT Hub 的连接详细信息，应用程序中的所有函数都可以使用这些信息来连接并监听事件。

### 任务 - 安装 Azure Functions 工具

> 在撰写本文时，Azure Functions 的代码工具在 Apple Silicon 上的 Python 项目中尚未完全工作。您需要使用基于 Intel 的 Mac、Windows PC 或 Linux PC。

Azure Functions 的一个重要功能是可以在本地运行。云端使用的运行时可以在您的计算机上运行，允许您编写响应 IoT 消息的代码并在本地运行。您甚至可以在处理事件时调试代码。一旦对代码满意，可以将其部署到云端。

Azure Functions 工具以 CLI 的形式提供，称为 Azure Functions Core Tools。

1. 按照 [Azure Functions Core Tools 文档](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn) 中的说明安装 Azure Functions Core Tools。

1. 安装 VS Code 的 Azure Functions 扩展。此扩展提供创建、调试和部署 Azure Functions 的支持。请参考 [Azure Functions 扩展文档](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) 了解如何在 VS Code 中安装此扩展。

当您将 Azure Functions 应用程序部署到云端时，它需要使用少量云存储来存储应用程序文件和日志文件等内容。当您在本地运行 Functions 应用程序时，仍需连接到云存储，但可以使用名为 [Azurite](https://github.com/Azure/Azurite) 的存储模拟器代替实际云存储。它在本地运行，但行为类似于云存储。

> 🎓 在 Azure 中，Azure Functions 使用的存储是 Azure Storage Account。这些账户可以存储文件、Blob、表中的数据或队列中的数据。您可以在多个应用程序之间共享一个存储账户，例如 Functions 应用程序和 Web 应用程序。

1. Azurite 是一个 Node.js 应用程序，因此您需要安装 Node.js。您可以在 [Node.js 网站](https://nodejs.org/) 上找到下载和安装说明。如果您使用 Mac，也可以通过 [Homebrew](https://formulae.brew.sh/formula/node) 安装。

1. 使用以下命令安装 Azurite（`npm` 是安装 Node.js 时附带的工具）：

    ```sh
    npm install -g azurite
    ```

1. 创建一个名为 `azurite` 的文件夹供 Azurite 存储数据：

    ```sh
    mkdir azurite
    ```

1. 运行 Azurite，并传递此新文件夹：

    ```sh
    azurite --location azurite
    ```

    Azurite 存储模拟器将启动并准备好供本地 Functions 运行时连接。

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### 任务 - 创建 Azure Functions 项目

Azure Functions CLI 可用于创建新的 Functions 应用程序。

1. 创建一个文件夹用于存放 Functions 应用程序，并导航到该文件夹。命名为 `soil-moisture-trigger`：

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. 在此文件夹中创建一个 Python 虚拟环境：

    ```sh
    python3 -m venv .venv
    ```

1. 激活虚拟环境：

    * 在 Windows 上：
        * 如果使用命令提示符或通过 Windows Terminal 使用命令提示符，运行：

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * 如果使用 PowerShell，运行：

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * 在 macOS 或 Linux 上，运行：

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 这些命令应在您创建虚拟环境的同一位置运行。您无需导航到 `.venv` 文件夹，只需在创建虚拟环境的文件夹中运行激活命令以及安装包或运行代码的命令。

1. 运行以下命令在此文件夹中创建 Functions 应用程序：

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    这将在当前文件夹中创建三个文件：

    * `host.json` - 此 JSON 文档包含 Functions 应用程序的设置。您无需修改这些设置。
    * `local.settings.json` - 此 JSON 文档包含应用程序在本地运行时使用的设置，例如 IoT Hub 的连接字符串。这些设置仅用于本地，不应添加到源代码控制中。当您将应用程序部署到云端时，这些设置不会被部署，而是从应用程序设置中加载。这将在本课后面介绍。
    * `requirements.txt` - 这是一个 [Pip requirements 文件](https://pip.pypa.io/en/stable/user_guide/#requirements-files)，包含运行 Functions 应用程序所需的 Pip 包。

1. `local.settings.json` 文件中有一个设置用于 Functions 应用程序使用的存储账户。默认值为空，需要设置。要连接到 Azurite 本地存储模拟器，请将此值设置为以下内容：

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. 使用 requirements 文件安装必要的 Pip 包：

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 必需的 Pip 包需要在此文件中，以便在将 Functions 应用程序部署到云端时，运行时可以确保安装正确的包。

1. 为测试一切是否正常运行，可以启动 Functions 运行时。运行以下命令启动：

    ```sh
    func start
    ```

    您将看到运行时启动并报告未找到任何作业函数（触发器）。

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ 如果收到防火墙通知，请授予访问权限，因为 `func` 应用需要能够读取和写入您的网络。
> ⚠️ 如果您使用的是 macOS，输出中可能会出现警告：
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> 只要 Functions 应用程序能够正确启动并列出正在运行的函数，您可以忽略这些警告。如 [Microsoft Docs Q&A 中的这个问题](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn) 所述，这些警告可以忽略。

1. 按 `ctrl+c` 停止 Functions 应用程序。

1. 在 VS Code 中打开当前文件夹，可以通过打开 VS Code 后再打开此文件夹，或者运行以下命令：

    ```sh
    code .
    ```

    VS Code 会检测到您的 Functions 项目，并显示一条通知：

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![通知](../../../../../translated_images/vscode-azure-functions-init-notification.bd19b49229963edb.zh.png)

    在通知中选择 **Yes**。

1. 确保 Python 虚拟环境在 VS Code 终端中运行。如果需要，可以终止并重新启动。

## 创建 IoT Hub 事件触发器

Functions 应用程序是无服务器代码的外壳。为了响应 IoT Hub 的事件，您可以向此应用程序添加一个 IoT Hub 触发器。此触发器需要连接到发送到 IoT Hub 的消息流并对其进行响应。为了获取这些消息流，您的触发器需要连接到 IoT Hub 的 *事件中心兼容端点*。

IoT Hub 基于另一个 Azure 服务——Azure Event Hubs。Event Hubs 是一个允许发送和接收消息的服务，而 IoT Hub 扩展了它以添加 IoT 设备的功能。连接到 IoT Hub 读取消息的方式与使用 Event Hubs 的方式相同。

✅ 做一些研究：阅读 [Azure Event Hubs 文档](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn) 中的概述。基本功能与 IoT Hub 有何不同？

为了让 IoT 设备连接到 IoT Hub，它需要使用一个密钥来确保只有允许的设备可以连接。同样，当连接以读取消息时，您的代码需要一个包含密钥的连接字符串以及 IoT Hub 的详细信息。

> 💁 默认的连接字符串具有 **iothubowner** 权限，这使得任何使用它的代码都可以完全访问 IoT Hub。理想情况下，您应该使用最低权限级别进行连接。这将在下一课中介绍。

一旦触发器连接成功，函数中的代码将会对发送到 IoT Hub 的每条消息进行调用，无论消息来自哪个设备。触发器会将消息作为参数传递。

### 任务 - 获取事件中心兼容端点的连接字符串

1. 在 VS Code 终端中运行以下命令以获取 IoT Hub 的事件中心兼容端点的连接字符串：

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    将 `<hub_name>` 替换为您为 IoT Hub 使用的名称。

1. 在 VS Code 中打开 `local.settings.json` 文件。在 `Values` 部分中添加以下值：

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    将 `<connection string>` 替换为上一步中的值。您需要在上一行后添加一个逗号以使其成为有效的 JSON。

### 任务 - 创建事件触发器

现在您可以创建事件触发器了。

1. 在 VS Code 终端中，从 `soil-moisture-trigger` 文件夹中运行以下命令：

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    这将创建一个名为 `iot-hub-trigger` 的新函数。触发器将连接到 IoT Hub 的事件中心兼容端点，因此您可以使用事件中心触发器。没有特定的 IoT Hub 触发器。

这将在 `soil-moisture-trigger` 文件夹中创建一个名为 `iot-hub-trigger` 的文件夹，其中包含此函数。此文件夹将包含以下文件：

* `__init__.py` - 这是包含触发器的 Python 代码文件，使用标准的 Python 文件命名约定将此文件夹转换为 Python 模块。

    此文件将包含以下代码：

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    触发器的核心是 `main` 函数。每当 IoT Hub 发送消息时，此函数都会被调用，并将消息作为 `event` 参数传递，同时还会传递与上一课中看到的注释相同的属性。

    此函数的核心是记录事件。

* `function.json` - 此文件包含触发器的配置。主要配置在名为 `bindings` 的部分中。绑定是 Azure Functions 与其他 Azure 服务之间连接的术语。此函数有一个输入绑定到事件中心——它连接到事件中心并接收数据。

    > 💁 您还可以添加输出绑定，以便函数的输出发送到另一个服务。例如，您可以添加一个输出绑定到数据库，并从函数返回 IoT Hub 事件，它将自动插入到数据库中。

    ✅ 做一些研究：阅读 [Azure Functions 触发器和绑定概念文档](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python) 中的绑定相关内容。

    `bindings` 部分包括绑定的配置。以下值值得关注：

  * `"type": "eventHubTrigger"` - 指定函数需要监听来自事件中心的事件
  * `"name": "events"` - 这是事件中心事件的参数名称，与 Python 代码中 `main` 函数的参数名称匹配
  * `"direction": "in"` - 这是一个输入绑定，事件中心的数据进入函数
  * `"connection": ""` - 定义读取连接字符串的设置名称。在本地运行时，将从 `local.settings.json` 文件中读取此设置。

    > 💁 连接字符串不能存储在 `function.json` 文件中，必须从设置中读取。这是为了防止意外暴露连接字符串。

1. 由于 [Azure Functions 模板中的一个错误](https://github.com/Azure/azure-functions-templates/issues/1250)，`function.json` 文件中的 `cardinality` 字段值不正确。将此字段从 `many` 更新为 `one`：

    ```json
    "cardinality": "one",
    ```

1. 更新 `function.json` 文件中 `"connection"` 的值，使其指向您在 `local.settings.json` 文件中添加的新值：

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 请记住 - 这里需要指向设置，而不是包含实际的连接字符串。

1. 连接字符串包含 `eventHubName` 值，因此 `function.json` 文件中的此值需要清空。将此值更新为空字符串：

    ```json
    "eventHubName": "",
    ```

### 任务 - 运行事件触发器

1. 确保您没有运行 IoT Hub 事件监视器。如果事件监视器与 Functions 应用程序同时运行，Functions 应用程序将无法连接并消费事件。

    > 💁 多个应用程序可以使用不同的 *消费者组* 连接到 IoT Hub 的端点。这将在后续课程中介绍。

1. 要运行 Functions 应用程序，请从 VS Code 终端运行以下命令：

    ```sh
    func start
    ```

    Functions 应用程序将启动，并发现 `iot-hub-trigger` 函数。它将处理过去一天内发送到 IoT Hub 的任何事件。

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    每次调用函数时，输出中都会显示 `Executing 'Functions.iot-hub-trigger'` 和 `Executed 'Functions.iot-hub-trigger'` 块，您可以看到每次函数调用处理了多少消息。

1. 确保您的 IoT 设备正在运行，您将在 Functions 应用程序中看到新的土壤湿度消息。

1. 停止并重新启动 Functions 应用程序。您会发现它不会再次处理之前的消息，只会处理新的消息。

> 💁 VS Code 还支持调试您的 Functions。您可以通过点击代码行开始处的边框设置断点，或者将光标放在代码行上并选择 *Run -> Toggle breakpoint*，或者按 `F9`。您可以通过选择 *Run -> Start debugging*，按 `F5`，或选择 *Run and debug* 面板并点击 **Start debugging** 按钮启动调试器。通过这样做，您可以查看正在处理的事件的详细信息。

#### 故障排除

* 如果出现以下错误：

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    检查 Azurite 是否正在运行，并且您已在 `local.settings.json` 文件中将 `AzureWebJobsStorage` 设置为 `UseDevelopmentStorage=true`。

* 如果出现以下错误：

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    检查您是否已将 `function.json` 文件中的 `cardinality` 设置为 `one`。

* 如果出现以下错误：

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    检查您是否已将 `function.json` 文件中的 `eventHubName` 设置为空字符串。

## 从无服务器代码发送直接方法请求

到目前为止，您的 Functions 应用程序正在使用事件中心兼容端点监听来自 IoT Hub 的消息。现在，您需要向 IoT 设备发送命令。这可以通过 IoT Hub 的 *注册管理器* 连接来完成。注册管理器是一个工具，允许您查看注册到 IoT Hub 的设备，并通过发送云到设备消息、直接方法请求或更新设备双向通信与这些设备进行交互。您还可以使用它注册、更新或删除 IoT Hub 中的 IoT 设备。

要连接到注册管理器，您需要一个连接字符串。

### 任务 - 获取注册管理器连接字符串

1. 要获取连接字符串，请运行以下命令：

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    将 `<hub_name>` 替换为您为 IoT Hub 使用的名称。

    连接字符串是为 *ServiceConnect* 策略请求的，使用 `--policy-name service` 参数。当您请求连接字符串时，可以指定该连接字符串允许的权限。ServiceConnect 策略允许您的代码连接并向 IoT 设备发送消息。

    ✅ 做一些研究：阅读 [IoT Hub 权限文档](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn) 中的不同策略。

1. 在 VS Code 中打开 `local.settings.json` 文件。在 `Values` 部分中添加以下值：

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    将 `<connection string>` 替换为上一步中的值。您需要在上一行后添加一个逗号以使其成为有效的 JSON。

### 任务 - 向设备发送直接方法请求

1. 注册管理器的 SDK 可通过 Pip 包获得。向 `requirements.txt` 文件添加以下行以添加对该包的依赖：

    ```sh
    azure-iot-hub
    ```

1. 确保 VS Code 终端已激活虚拟环境，并运行以下命令安装 Pip 包：

    ```sh
    pip install -r requirements.txt
    ```

1. 向 `__init__.py` 文件添加以下导入：

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    这导入了一些系统库，以及与注册管理器交互并发送直接方法请求的库。

1. 删除 `main` 方法中的代码，但保留方法本身。

1. 在 `main` 方法中添加以下代码：

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    此代码提取事件的主体，其中包含 IoT 设备发送的 JSON 消息。

    然后从消息的注释中获取设备 ID。事件的主体包含作为遥测发送的消息，`iothub_metadata` 字典包含 IoT Hub 设置的属性，例如发送者的设备 ID 和消息发送的时间。

    此信息随后被记录。您将在本地运行 Functions 应用程序时在终端中看到这些日志。

1. 在此代码下方添加以下代码：

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    此代码从消息中获取土壤湿度值。然后检查土壤湿度值，并根据值创建一个辅助类，用于 `relay_on` 或 `relay_off` 直接方法请求。方法请求不需要负载，因此发送一个空的 JSON 文档。

1. 在此代码下方添加以下代码：

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
此代码从 `local.settings.json` 文件中加载 `REGISTRY_MANAGER_CONNECTION_STRING`。该文件中的值会作为环境变量提供，可以通过 `os.environ` 函数读取，该函数返回一个包含所有环境变量的字典。

> 💁 当此代码部署到云端时，`local.settings.json` 文件中的值将被设置为 *应用程序设置*，并可以通过环境变量读取。

然后代码使用连接字符串创建了一个 Registry Manager 辅助类的实例。

1. 在下面添加以下代码：

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    此代码指示注册管理器向发送遥测数据的设备发送直接方法请求。

    > 💁 在之前课程中使用 MQTT 创建的应用版本中，继电器控制命令会发送到所有设备。代码假设您只有一个设备。而此版本的代码将方法请求发送到单个设备，因此如果您有多个湿度传感器和继电器的设置，它可以向正确的设备发送正确的直接方法请求。

1. 运行 Functions 应用程序，并确保您的 IoT 设备正在发送数据。您将看到消息被处理并发送直接方法请求。将土壤湿度传感器插入或移出土壤，观察值的变化以及继电器的开关状态。

> 💁 您可以在 [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions) 文件夹中找到此代码。

## 将您的无服务器代码部署到云端

您的代码现在已经在本地运行，下一步是将 Functions 应用程序部署到云端。

### 任务 - 创建云资源

您的 Functions 应用程序需要部署到 Azure 中的 Functions 应用资源，该资源位于您为 IoT Hub 创建的资源组中。您还需要在 Azure 中创建一个存储账户，以替代您在本地运行的模拟存储。

1. 运行以下命令以创建存储账户：

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    将 `<storage_name>` 替换为您的存储账户名称。此名称需要在全球范围内唯一，因为它是访问存储账户的 URL 的一部分。此名称只能使用小写字母和数字，不能包含其他字符，并且限制为 24 个字符。可以使用类似 `sms` 的名称，并在末尾添加唯一标识符，例如一些随机单词或您的名字。

    `--sku Standard_LRS` 选项选择定价层，选择最低成本的通用账户。存储没有免费层，您需要为使用的部分付费。成本相对较低，最贵的存储每月每存储 1GB 的费用不到 0.05 美元。

    ✅ 在 [Azure 存储账户定价页面](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn) 上了解定价信息。

1. 运行以下命令以创建 Functions 应用程序：

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    将 `<location>` 替换为您在上一课中创建资源组时使用的位置。

    将 `<storage_name>` 替换为您在上一步中创建的存储账户名称。

    将 `<functions_app_name>` 替换为您的 Functions 应用程序的唯一名称。此名称需要在全球范围内唯一，因为它是访问 Functions 应用程序的 URL 的一部分。可以使用类似 `soil-moisture-sensor-` 的名称，并在末尾添加唯一标识符，例如一些随机单词或您的名字。

    `--functions-version 3` 选项设置 Azure Functions 的版本。版本 3 是最新版本。

    `--os-type Linux` 告诉 Functions 运行时使用 Linux 作为托管这些函数的操作系统。Functions 可以托管在 Linux 或 Windows 上，具体取决于使用的编程语言。Python 应用程序仅支持 Linux。

### 任务 - 上传您的应用程序设置

在开发 Functions 应用程序时，您将一些设置存储在 `local.settings.json` 文件中，用于 IoT Hub 的连接字符串。这些设置需要写入 Azure 中的 Functions 应用程序的应用程序设置，以便您的代码可以使用它们。

> 🎓 `local.settings.json` 文件仅用于本地开发设置，不应提交到源代码控制系统（如 GitHub）。当部署到云端时，会使用应用程序设置。应用程序设置是托管在云端的键值对，可以通过代码或运行时从环境变量中读取，用于将代码连接到 IoT Hub。

1. 运行以下命令以在 Functions 应用程序的应用程序设置中设置 `IOT_HUB_CONNECTION_STRING`：

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    将 `<functions_app_name>` 替换为您为 Functions 应用程序使用的名称。

    将 `<connection string>` 替换为 `local.settings.json` 文件中的 `IOT_HUB_CONNECTION_STRING` 的值。

1. 重复上述步骤，但将 `REGISTRY_MANAGER_CONNECTION_STRING` 的值设置为 `local.settings.json` 文件中的对应值。

运行这些命令后，它们还会输出 Functions 应用程序的所有应用程序设置列表。您可以使用此列表检查值是否设置正确。

> 💁 您会看到一个已经设置的 `AzureWebJobsStorage` 值。在您的 `local.settings.json` 文件中，此值被设置为使用本地存储模拟器。当您创建 Functions 应用程序时，传递存储账户作为参数，此设置会自动设置。

### 任务 - 将您的 Functions 应用程序部署到云端

现在 Functions 应用程序已经准备好，可以部署您的代码。

1. 从 VS Code 终端运行以下命令以发布您的 Functions 应用程序：

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    将 `<functions_app_name>` 替换为您为 Functions 应用程序使用的名称。

代码将被打包并发送到 Functions 应用程序，在那里它将被部署并启动。会有大量的控制台输出，最后确认部署完成并列出已部署的函数。在此情况下，列表中只会包含触发器。

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

确保您的 IoT 设备正在运行。通过调整土壤湿度或将传感器插入或移出土壤来改变湿度水平。您将看到继电器随着土壤湿度的变化而打开和关闭。

---

## 🚀 挑战

在上一课中，您通过在继电器打开时以及关闭后的一段时间内取消订阅 MQTT 消息来管理继电器的计时。在这里您无法使用此方法——您无法取消订阅 IoT Hub 触发器。

思考在 Functions 应用程序中可以使用哪些不同的方法来处理这一问题。

## 课后测验

[课后测验](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## 复习与自学

* 在 [维基百科的无服务器计算页面](https://wikipedia.org/wiki/Serverless_computing) 上阅读有关无服务器计算的内容
* 阅读关于在 Azure 中使用无服务器的内容，包括更多示例：[Azure 博客文章 - 为您的 IoT 需求选择无服务器](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* 在 [Azure Functions YouTube 频道](https://www.youtube.com/c/AzureFunctions) 上了解更多关于 Azure Functions 的内容

## 作业

[添加手动继电器控制](assignment.md)

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用此翻译而引起的任何误解或误读不承担责任。