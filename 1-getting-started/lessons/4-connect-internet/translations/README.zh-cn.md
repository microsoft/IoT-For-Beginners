# 将您的设备连接到互联网

![本课的 sketchnote 概述](../../../../sketchnotes/lesson-4.jpg)

> [Nitya Narasimhan](https://github.com/nitya) 的草图笔记。单击图像可查看更大的版本。

本课程是 [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) 的 [Hello IoT 系列](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) 的一部分。本课程以 2 个视频的形式进行授课 - 一个 1 小时的课程，以及一个 1 小时的办公时间，深入探讨课程的各个部分，并回答问题。

[![第 4 课：将设备连接到互联网](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![第 4 课：将您的设备连接到互联网 - 办公时间](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q ）

> 🎥 点击上图观看视频

## 课前测验

[课前测验](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## 简介
---
IoT 中的 **I** 代表 **Internet** - 云连接和服务支持物联网设备的许多功能，从收集连接到设备的传感器的测量结果，到发送消息来控制执行器。IoT 设备通常使用标准通信协议连接到单个云 IoT 服务，并且该服务连接到 IoT 应用程序的其余部分，从用于围绕数据做出智能决策的 AI 服务，到用于控制或报告的 Web 应用程序。

> 🎓 从传感器收集并发送到云端的数据称为遥测。

物联网设备可以从云端接收消息。通常，消息包含命令 - 即内部执行操作（例如重新启动或更新固件）或使用执行器的指令（例如打开灯）。

本课程介绍物联网设备可用于连接到云的一些通信协议，以及它们可能发送或接收的数据类型。您还将亲身体验它们，为您的夜灯添加互联网控制，将 LED 控制逻辑移至本地运行的“服务器”代码。

在本课中，我们将介绍：

* [通信协议](#communication-protocols)
* [消息队列遥测传输 (MQTT)](#message-queueing-telemetry-transport-mqtt)
* [遥测](#遥测)
* [命令](#命令)

## 通讯协议
---
物联网设备使用多种流行的通信协议与互联网进行通信。最流行的是基于通过某种代理发布/订阅消息传递。IoT 设备连接到代理并发布遥测数据并订阅命令。云服务还连接到代理并订阅所有遥测消息，并向特定设备或设备组发布命令。

![物联网设备连接到代理并发布遥测数据并订阅命令。云服务连接到代理并订阅所有遥测并向特定设备发送命令。](../../../../images/pub-sub.png)

MQTT 是最流​​行的物联网设备通信协议，本课程将对此进行介绍。其他协议包括 AMQP 和 HTTP/HTTPS。

## 消息队列遥测传输 (MQTT)
---
[MQTT](http://mqtt.org) 是一种轻量级的、开放标准消息协议，可以在设备之间发送消息。它于 1999年设计，用于监控石油管道，15年后由 IBM 作为开放标准发布。

MQTT 有一个代理和多个客户端。所有客户端都连接到代理，然后代理将消息路由到相关客户端。消息使用命名主题进行路由，而不是直接发送到单个客户端。客户端可以发布到某个主题，任何订阅该主题的客户端都将收到该消息。

![IoT 设备在 /telemetry 主题上发布遥测数据，以及订阅该主题的云服务](../../../../images/mqtt.png)

✅ 做一些研究。如果您有很多 IoT 设备，如何确保您的 MQTT 代理能够处理所有消息？

### 将您的 IoT 设备连接到 MQTT

为夜灯添加互联网控制的第一步是将其连接到 MQTT 代理。

#### 任务

将您的设备连接到 MQTT 代理。

在课程的这一部分中，您将把 IoT 夜灯连接到互联网，以便对其进行远程控制。在本课程的后面部分，您的 IoT 设备将通过 MQTT 将遥测消息发送到具有轻级别的公共 MQTT 代理，您将在其中编写的一些服务器代码将拾取该消息。此代码将检查灯光级别并向设备发送回命令消息，告诉其打开或关闭 LED。

这种设置的实际用例可能是在有大量灯光的地方（例如体育场），在决定打开灯光之前从多个光传感器收集数据。如果只有一个传感器被云层或鸟覆盖，但其他传感器检测到足够的光线，这可能会阻止灯打开。

✅ 还有哪些其他情况需要在发送命令之前评估来自多个传感器的数据？

您可以使用运行 [Eclipse Mosquitto](https://www.mosquitto.org)（一个开源 MQTT 代理）的公共测试服务器，而不是在此任务中处理设置 MQTT 代理的复杂性。该测试代理可在 [test.mosquitto.org](https://test.mosquitto.org) 上公开获取，并且不需要设置帐户，这使其成为测试 MQTT 客户端和服务器的绝佳工具。

> 💁 该测试经纪人是公开的且不安全。任何人都可以收听您发布的内容，因此不应将其与任何需要保密的数据一起使用

![分配的流程图，显示正在读取和检查的光级别，以及开始控制 LED](../../../../images/assignment-1-internet-flow.png)

请按照以下相关步骤将您的设备连接到 MQTT 代理：

* [Arduino - Wio 终端](wio-terminal-mqtt.md)
* [单板计算机-Raspberry Pi/虚拟物联网设备](single-board-computer-mqtt.md)

### 深入了解 MQTT

主题可以具有层次结构，并且客户端可以使用通配符订阅层次结构的不同级别。例如，您可以将温度遥测消息发送到 `/telemetry/Temperature` 主题，将湿度消息发送到 `/telemetry/humidity` 主题，然后在云应用程序中订阅 `/telemetry/*`主题以接收温度和湿度遥测消息。

消息可以在服务质量 (QoS) 的情况下发送，这决定了消息接收的保证。

* 最多一次 - 消息仅发送一次，客户端和代理无需采取任何额外步骤来确认发送（即发即忘）。
* 至少一次 - 发送者多次重试消息，直到收到确认（确认发送）。
* 恰好一次 - 发送者和接收者进行两级握手，以确保只收到消息的一份副本（保证传递）。

✅ 什么情况下可能需要保证消息传递，而不是只发送消息,不关心消息是否发送成功？

虽然名称是消息队列（MQTT 的缩写），但它实际上并不支持消息队列。这意味着，如果客户端断开连接，然后重新连接，它将不会接收在断开连接期间发送的消息，除了那些已经开始使用 QoS 进程处理的消息。消息上可以设置保留标志。如果设置了此选项，MQTT 代理将存储在带有此标志的主题上发送的最后一条消息，并将其发送给以后订阅该主题的任何客户端。这样，客户将始终收到最新消息。

MQTT 还支持保持活动功能，该功能可在消息之间的较长间隔期间检查连接是否仍然活动。

> 🦟 [来自 Eclipse 基金会的 Mosquitto](https://mosquitto.org) 有一个免费的 MQTT 代理，您可以自己运行以试验 MQTT，还有一个公共 MQTT 代理，您可以使用它来测试您的代码，托管在 [test .mosquitto.org](https://test.mosquitto.org)。

MQTT 连接可以是公共和开放的，也可以使用用户名和密码或证书进行加密和保护。

> 💁 MQTT 通过 TCP/IP 进行通信，TCP/IP 与 HTTP 具有相同的底层网络协议，但端口不同。您还可以使用 MQTT 通过 Websocket 与浏览器中运行的 Web 应用程序进行通信，或者在防火墙或其他网络规则阻止标准 MQTT 连接的情况下进行通信。

## 遥测
---
遥测一词源自希腊语词根，意思是远程测量。遥测是从传感器收集数据并将其发送到云端的行为。

> 💁 最早的遥测设备之一于 1874 年在法国发明，可将实时天气和雪深从勃朗峰发送到巴黎。它使用物理线路，因为当时还没有无线技术。

让我们回顾一下第 1 课中智能恒温器的示例。

![使用多个房间传感器的互联网连接恒温器](../../../../images/telemetry.png)

恒温器具有温度传感器来收集遥测数据。它很可能内置一个温度传感器，并且可能通过无线协议（例如[蓝牙低功耗](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE)）连接到多个外部温度传感器。

它将发送的遥测数据的示例可能是：

| 名称 | 价值| 描述 |
| ---- | -----| ----------- |
| `恒温器温度` | 18°C | 温控器内置温度传感器测量的温度 |
| `客厅温度` | 19°C | 由远程温度传感器测量的温度，该传感器被命名为`客厅`，以识别其所在的房间 |
| `卧室温度` | 21°C | 由远程温度传感器测量的温度，该传感器被命名为`卧室`，以识别其所在的房间 |

然后，云服务可以使用此遥测数据来决定发送哪些命令来控制加热。

### 从您的 IoT 设备发送遥测数据

向夜灯添加互联网控制的下一部分是将灯光级别遥测数据发送到有关遥测主题的 MQTT 代理。

#### 任务 - 从 IoT 设备发送遥测数据

将光级遥测数据发送到 MQTT 代理。

数据以 JSON 形式编码发送 - JavaScript 对象表示法的缩写，一种使用键/值对进行文本数据编码的标准。

✅ 如果您之前没有接触过 JSON，您可以在 [JSON.org 文档](https://www.json.org/) 上了解更多信息。

请按照以下相关步骤将遥测数据从您的设备发送到 MQTT 代理：

* [Arduino - Wio 终端](wio-terminal-telemetry.md)
* [单板计算机-Raspberry Pi/虚拟物联网设备](single-board-computer-telemetry.md)

### 从 MQTT 代理接收遥测数据

如果另一端没有任何东西可以侦听，那么发送遥测数据就没有意义。光级遥测需要一些东西来监听它来处理数据。此“服务器”代码是您将作为大型物联网应用程序的一部分部署到云服务的代码，但在这里您将在您的计算机上本地运行此代码（如果您直接在树莓派上编码，则在您的 Pi 上运行） ）。服务器代码由一个 Python 应用程序组成，该应用程序通过 MQTT 监听具有光级别的遥测消息。在本课程的后面部分，您将让它回复一条命令消息，其中包含打开或关闭 LED 的说明。

✅ 做一些研究：如果没有监听器，MQTT 消息会发生什么？

#### 安装 Python 和 VS Code

如果本地没有安装 Python 和 VS Code，则需要安装它们才能对服务器进行编码。如果您正在使用虚拟 IoT 设备，或者正在使用 Raspberry Pi，您可以跳过此步骤，因为您应该已经安装并配置了此设备。

##### 任务 - 安装 Python 和 VS Code

安装 Python 和 VS Code。

1. 安装 Python。有关安装最新版本 Python 的说明，请参阅 [Python 下载页面](https://www.python.org/downloads/)。

1. 安装 Visual Studio 代码（VS代码）。这是您将用来用 Python 编写虚拟设备代码的编辑器。有关安装 VS Code 的说明，请参阅 [VS Code 文档](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)。

    > 💁 如果您有首选工具，您可以自由使用任何 Python IDE 或编辑器来学习这些课程，但课程将根据使用 VS Code 提供说明。

1. 安装 VS Code Pylance 扩展。这是 VS Code 的扩展，提供 Python 语言支持。有关在 VS Code 中安装此扩展的说明，请参阅 [Pylance 扩展文档](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance)。

#### 配置Python虚拟环境

Python 的强大功能之一是能够安装 [pip 包](https://pypi.org) - 这些是由其他人编写并发布到 Internet 的代码包。您可以使用一个命令将 pip 包安装到计算机上，然后在代码中使用该包。您将使用 pip 安装包以通过 MQTT 进行通信。

默认情况下，当您安装软件包时，它在计算机上的任何位置都可用，这可能会导致软件包版本出现问题 - 例如，一个应用程序依赖于软件包的一个版本，当您为不同的应用程序安装新版本时，该版本就会中断。要解决此问题，您可以使用 [Python 虚拟环境](https://docs.python.org/3/library/venv.html)，本质上是专用文件夹中的 Python 副本，并且在安装 pip 时他们只安装到该文件夹​​的软件包。

##### 任务-配置Python虚拟环境

配置Python虚拟环境并安装 MQTT pip 包。

1. 从终端或命令行，在您选择的位置运行以下命令以创建并导航到新目录：

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. 现在运行以下命令在 `.venv` 文件夹中创建虚拟环境
 
    ```sh
    python3 -m venv .venv
    ```

    > 💁 如果您除了 Python 3（最新版本）之外还安装了 Python 2，则需要显式调用 `python3` 来创建虚拟环境。如果您安装了 Python2，那么调用 `python` 将使用 Python 2 而不是 Python 3

1. 激活虚拟环境：

    * 在 Windows 上：
        * 如果您使用命令提示符或通过 Windows 终端使用命令提示符，请运行：

            ````cmd
            venv\Scripts\activate.bat
            ````

        * 如果您使用 PowerShell，请运行：

            ````powershell
            .\.venv\Scripts\Activate.ps1
            ````

    * 在 macOS 或 Linux 上，运行：

        ````cmd
        source ./.venv/bin/activate
        ````

    > 💁 这些命令应该从运行创建虚拟环境的命令的同一位置运行。您永远不需要导航到 `.venv` 文件夹，您应该始终运行 activate 命令和任何命令来安装软件包或运行创建虚拟环境时所在文件夹中的代码。

1. 激活虚拟环境后，默认的“python”命令将运行用于创建虚拟环境的 Python 版本。运行以下命令获取版本：

    ````sh
    python --version
    ````

    输出将类似于以下内容：

    ````output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 你的 Python 版本可能不同 - 只要是 3.6 或更高版本就可以。如果没有，请删除此文件夹，安装较新版本的 Python，然后重试。

1. 运行以下命令安装流行的 MQTT 库 [Paho-MQTT](https://pypi.org/project/paho-mqtt/) 的 pip 包。

    ```sh
    pip install paho-mqtt
    ```

    此 pip 包仅安装在虚拟环境中，在虚拟环境之外不可用。

#### 编写服务器代码

服务器代码现在可以用 Python 编写。

##### 任务 - 编写服务器代码

编写服务器代码。

1. 从终端或命令行，在虚拟环境中运行以下命令以创建名为 `app.py` 的 Python 文件：

    * 从 Windows 运行：

        ```cmd
        type nul > app.py
        ```

    * 在 macOS 或 Linux 上，运行：

        ```cmd
        touch app.py
        ```

1. 在 VS Code 中打开当前文件夹：

    ```sh
    code .
    ```

1. VS Code启动时，会激活Python虚拟环境。这将在底部状态栏中报告：

    ![显示所选虚拟环境的 VS Code](../../../../images/vscode-virtual-env.png)

1. 如果 VS Code 启动时 VS Code 终端已在运行，则不会在其中激活虚拟环境。最简单的方法是使用 **终止活动终端实例** 按钮终止终端：

    ![VS Code 终止活动终端实例按钮](../../../../images/vscode-kill-terminal.png)

1. 通过选择 *Terminal -> New Terminal 或按 `` CTRL+` `` 启动新的 VS Code 终端。新终端将加载虚拟环境，并在终端中调用激活虚拟环境。虚拟环境的名称（`.venv`）也会出现在提示符中：

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. 从 VS Code 资源管理器中打开 `app.py` 文件并添加以下代码：

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    替换第 6 行 `<ID>`，包含您在创建设备代码时使用的唯一 `ID`。

    ⚠️ 此 `ID` **必须**与您在设备上使用的 `ID` 相同，否则服务器代码将无法订阅或发布到正确的主题。

    此代码创建一个具有唯一名称的 MQTT 客户端，并连接到 *test.mosquitto.org* 代理。然后，它启动一个处理循环，该循环在后台线程上运行，侦听任何订阅主题的消息。

    然后，客户端订阅有关遥测主题的消息，并定义一个在收到消息时调用的函数。当收到遥测消息时，将调用 `handle_telemetry` 函数，将收到的消息打印到控制台。

    最后，无限循环使应用程序保持运行。MQTT 客户端正在后台线程上侦听消息，并在主应用程序运行时始终运行。

1. 从 VS Code 终端，运行以下命令来运行您的 Python 应用程序：

    ```sh
    python app.py
    ```

    该应用程序将开始侦听来自 IoT 设备的消息。

1. 确保您的设备正在运行并发送遥测消息。调整物理或虚拟设备检测到的亮度级别。收到的消息将打印到终端。

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    nightlight 虚拟环境中的 app.py 文件必须运行，nightlight-server 虚拟环境中的 app.py 文件才能接收正在发送的消息。

> 💁 您可以在 [code-server/server](code-server/server) 文件夹中找到此代码。

### 遥测数据应多久发送一次？

遥测的一个重要考虑因素是测量和发送数据的频率？答案是——这取决于情况。如果您经常测量，您可以更快地响应测量变化，但您会使用更多电量、更多带宽、生成更多数据并需要更多云资源来处理。您需要足够频繁地测量，但不要太频繁。

对于恒温器来说，每隔几分钟测量一次可能就足够了，因为温度不会经常变化。如果您每天只测量一次，那么您最终可能会在阳光明媚的中午为房屋供暖以获得夜间温度，而如果您每秒测量一次，您将获得数千次不必要的重复温度测量，这将影响用户的互联网速度和带宽（对于带宽计划有限的人来说是一个问题），使用更多的电量，这对于远程传感器等电池供电的设备来说可能是一个问题，并增加了提供商云计算资源处理和存储它们的成本。

如果您正在监控工厂中一台机器周围的数据，如果它发生故障可能会导致灾难性损坏和数百万美元的收入损失，那么可能需要每秒多次测量。浪费带宽比错过遥测要好，遥测表明机器需要在机器损坏之前停止并修复。

> 💁 在这种情况下，您可能会考虑使用边缘设备首先处理遥测数据，以减少对互联网的依赖。

### 失去连接

互联网连接可能不可靠，经常出现中断。在这种情况下，物联网设备应该做什么——应该丢失数据，还是应该存储数据直到连接恢复？同样，答案是视情况而定。

对于恒温器来说，一旦进行新的温度测量，数据可能会丢失。供暖系统并不关心 20 分钟前的温度是 20.5°C，如果现在的温度是 19°C，则由现在的温度决定是否应该打开或关闭供暖。

对于机械，您可能希望保留数据，尤其是用于寻找趋势时。有些机器学习模型可以通过查看定义时间段（例如最后一小时）的数据并发现异常数据来检测数据流中的异常情况。这通常用于预测性维护，寻找某些东西可能很快就会损坏的迹象，以便您可以在损坏发生之前修复或更换它。您可能希望发送机器的所有遥测数据，以便对其进行处理以进行异常检测，因此一旦物联网设备可以重新连接，它将发送互联网中断期间生成的所有遥测数据。

物联网设备设计人员还应考虑物联网设备是否可以在因位置原因造成的互联网中断或信号丢失期间使用。如果智能恒温器由于断电而无法将遥测数据发送到云端，它应该能够做出一些有限的决定来控制加热。

[![这辆法拉利变砖了，因为有人试图在没有手机信号的地下升级它](../../../../images/bricked-car.png)](https://twitter.com/internetofshit/状态/1315736960082808832）

对于 MQTT 处理连接丢失的情况，设备和服务器代码需要负责确保消息传递（如果需要），例如要求所有发送的消息都由回复主题上的附加消息进行回复，如果不需要它们被手动排队以便稍后重播。

## 命令
---
命令是云发送到设备的消息，指示设备执行某些操作。大多数情况下，这涉及通过执行器提供某种输出，但它可以是设备本身的指令，例如重新启动，或收集额外的遥测数据并将其作为对命令的响应返回。

![连接互联网的恒温器接收打开供暖的命令](../../../../images/commands.png)

恒温器可以接收来自云端的命令来打开供暖。根据所有传感器的遥测数据，如果云服务决定应该打开供暖，则会发送相关命令。

### 向 MQTT 代理发送命令

我们的互联网控制夜灯的下一步是服务器代码将命令发送回物联网设备，以根据其感应到的光强度来控制灯光。

1.在 VS Code 中打开服务器代码

1. 在 `client_telemetry_topic` 声明后添加以下行，以定义向哪个主题发送命令：

    ```python
    server_command_topic = id + '/commands'
    ```

1. 在 `handle_telemetry` 函数末尾添加以下代码：

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    这会向命令主题发送一条 JSON 消息，其中 `led_on` 的值设置为 true 或 false，具体取决于灯光是否小于 300。如果亮度小于 300，则发送 true 以指示设备打开 LED。

1. 像以前一样运行代码

1. 调整物理或虚拟设备检测到的亮度级别。正在接收的消息和正在发送的命令将被写入终端：

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 遥测和命令分别针对一个主题发送。这意味着来自多个设备的遥测数据将显示在同一遥测主题上，并且针对多个设备的命令将显示在同一命令主题上。如果您想向特定设备发送命令，您可以使用多个主题，并以唯一的设备 ID 命名，例如 `/commands/device1`、`/commands/device2`。这样，设备就可以侦听专门针对该设备的消息。

> 💁 您可以在 [code-commands/server](code-commands/server) 文件夹中找到此代码。

### 处理 IoT 设备上的命令

现在命令已从服务器发送，您现在可以向 IoT 设备添加代码来处理它们并控制 LED。

请按照以下相关步骤侦听来自 MQTT 代理的命令：

* [Arduino - Wio 终端](wio-terminal-commands.md)
* [单板计算机-Raspberry Pi/虚拟物联网设备](single-board-computer-commands.md)

编写并运行此代码后，请尝试改变光照级别。观察服务器和设备的输出，并在更改灯光级别时观察 LED。

### 失去连接

如果云服务需要向离线的物联网设备发送命令，该怎么办？同样，答案是视情况而定。

如果最新的命令覆盖了较早的命令，则较早的命令可能会被忽略。如果云服务发送打开加热的命令，然后发送关闭加热的命令，则可以忽略打开命令并且不重新发送。

如果需要按顺序处理命令，例如向上移动机器人手臂，然后关闭抓取器，则需要在连接恢复后按顺序发送命令。

✅ 如果需要，设备或服务器代码如何确保命令始终通过 MQTT 按顺序发送和处理？



##  🚀 挑战
---
过去三课的挑战是列出尽可能多的家庭、学校或工作场所中的物联网设备，并确定它们是围绕微控制器还是单板计算机构建，甚至是两者的混合构建，并考虑他们使用什么传感器和执行器。

对于这些设备，请考虑它们可能发送或接收哪些消息。他们发送什么遥测数据？他们可能会收到什么消息或命令？你认为他们安全吗？

## 课后测验
---
[课后测验](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## 复习与自学
---
在 [MQTT 维基百科页面](https://wikipedia.org/wiki/MQTT) 上了解有关 MQTT 的更多信息。

尝试使用 [Mosquitto](https://www.mosquitto.org) 自行运行 MQTT 代理，并从 IoT 设备和服务器代码连接到它。

> 💁 提示 - 默认情况下 Mosquitto 不允许匿名连接（即没有用户名和密码的连接），并且不允许来自其运行的计算机外部的连接。
> 您可以使用 [`mosquitto.conf` 配置文件](https://www.mosquitto.org/man/mosquitto-conf-5.html) 修复此问题，内容如下：
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## 作业
---
[MQTT与其他通信协议的比较和对比](assignment.md)

    
   
