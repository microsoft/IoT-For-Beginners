<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-24T23:32:01+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "zh"
}
-->
# 虚拟单板计算机

与其购买物联网设备以及传感器和执行器，不如使用您的计算机来模拟物联网硬件。[CounterFit 项目](https://github.com/CounterFit-IoT/CounterFit) 允许您在本地运行一个应用程序，该应用程序可以模拟传感器和执行器等物联网硬件，并通过本地 Python 代码访问这些传感器和执行器。这些代码的编写方式与您在 Raspberry Pi 上使用物理硬件时的代码相同。

## 设置

要使用 CounterFit，您需要在计算机上安装一些免费软件。

### 任务

安装所需的软件。

1. 安装 Python。请参考 [Python 下载页面](https://www.python.org/downloads/) 了解如何安装最新版本的 Python。

1. 安装 Visual Studio Code (VS Code)。这是您将用来编写虚拟设备 Python 代码的编辑器。请参考 [VS Code 文档](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) 了解如何安装 VS Code。

    > 💁 如果您有偏好的工具，可以自由选择任何 Python IDE 或编辑器来完成这些课程，但课程将基于使用 VS Code 的说明。

1. 安装 VS Code 的 Pylance 扩展。这是一个为 VS Code 提供 Python 语言支持的扩展。请参考 [Pylance 扩展文档](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) 了解如何在 VS Code 中安装此扩展。

安装和配置 CounterFit 应用程序的说明将在作业说明的相关时间给出，因为它是按项目安装的。

## Hello World

在学习一种新的编程语言或技术时，通常会创建一个 "Hello World" 应用程序——一个小型应用程序，输出类似 `"Hello World"` 的文本，以显示所有工具已正确配置。

虚拟物联网硬件的 Hello World 应用程序将确保您正确安装了 Python 和 Visual Studio Code。它还将连接到 CounterFit，用于虚拟物联网传感器和执行器。它不会使用任何硬件，只是连接以证明一切正常。

此应用程序将位于名为 `nightlight` 的文件夹中，并将在作业的后续部分中重复使用不同的代码来构建夜灯应用程序。

### 配置 Python 虚拟环境

Python 的一个强大功能是能够安装 [Pip 包](https://pypi.org)——这些是由其他人编写并发布到互联网的代码包。您可以通过一个命令在计算机上安装一个 Pip 包，然后在代码中使用该包。您将使用 Pip 安装一个包来与 CounterFit 通信。

默认情况下，当您安装一个包时，它在计算机上的任何地方都可用，这可能会导致包版本问题——例如，一个应用程序依赖于一个包的版本，而另一个应用程序安装新版本时可能会导致问题。为了解决这个问题，您可以使用 [Python 虚拟环境](https://docs.python.org/3/library/venv.html)，它本质上是一个专用文件夹中的 Python 副本，当您安装 Pip 包时，它们只会安装到该文件夹中。

> 💁 如果您使用的是 Raspberry Pi，那么您没有在该设备上设置虚拟环境来管理 Pip 包，而是使用全局包，因为 Grove 包是通过安装脚本全局安装的。

#### 任务 - 配置 Python 虚拟环境

配置 Python 虚拟环境并安装 CounterFit 的 Pip 包。

1. 在终端或命令行中，在您选择的位置运行以下命令以创建并导航到一个新目录：

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. 现在运行以下命令，在 `.venv` 文件夹中创建一个虚拟环境：

    ```sh
    python3 -m venv .venv
    ```

    > 💁 您需要显式调用 `python3` 来创建虚拟环境，以防您同时安装了 Python 2 和 Python 3（最新版本）。如果您安装了 Python 2，那么调用 `python` 将使用 Python 2 而不是 Python 3。

1. 激活虚拟环境：

    * 在 Windows 上：
        * 如果您使用的是命令提示符或通过 Windows Terminal 使用命令提示符，请运行：

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * 如果您使用的是 PowerShell，请运行：

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > 如果您收到关于系统禁用脚本运行的错误，您需要通过设置适当的执行策略来启用脚本运行。您可以以管理员身份启动 PowerShell，然后运行以下命令：

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            当被要求确认时输入 `Y`。然后重新启动 PowerShell 并重试。

            如果需要，您可以稍后重置此执行策略。您可以在 [Microsoft Docs 的执行策略页面](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn) 上阅读更多相关信息。

    * 在 macOS 或 Linux 上，运行：

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 这些命令应在您运行创建虚拟环境命令的同一位置运行。您永远不需要导航到 `.venv` 文件夹，您应该始终从创建虚拟环境时所在的文件夹运行激活命令以及任何安装包或运行代码的命令。

1. 激活虚拟环境后，默认的 `python` 命令将运行用于创建虚拟环境的 Python 版本。运行以下命令以获取版本：

    ```sh
    python --version
    ```

    输出应包含以下内容：

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 您的 Python 版本可能不同——只要是 3.6 或更高版本即可。如果不是，请删除此文件夹，安装更新版本的 Python，然后重试。

1. 运行以下命令以安装 CounterFit 的 Pip 包。这些包包括主要的 CounterFit 应用程序以及 Grove 硬件的 shims。这些 shims 允许您像编写使用 Grove 生态系统中的物理传感器和执行器的代码一样编写代码，但连接到虚拟物联网设备。

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    这些 Pip 包将仅安装在虚拟环境中，无法在其外部使用。

### 编写代码

准备好 Python 虚拟环境后，您可以编写 "Hello World" 应用程序的代码。

#### 任务 - 编写代码

创建一个 Python 应用程序，在控制台打印 `"Hello World"`。

1. 在虚拟环境中，从终端或命令行运行以下命令以创建一个名为 `app.py` 的 Python 文件：

    * 在 Windows 上运行：

        ```cmd
        type nul > app.py
        ```

    * 在 macOS 或 Linux 上运行：

        ```cmd
        touch app.py
        ```

1. 在 VS Code 中打开当前文件夹：

    ```sh
    code .
    ```

    > 💁 如果您的终端在 macOS 上返回 `command not found`，这意味着 VS Code 尚未添加到您的 PATH。您可以通过遵循 [VS Code 文档中从命令行启动部分](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) 的说明将 VS Code 添加到 PATH，然后运行命令。VS Code 在 Windows 和 Linux 上默认安装到 PATH。

1. 当 VS Code 启动时，它将激活 Python 虚拟环境。选定的虚拟环境将显示在底部状态栏中：

    ![VS Code 显示选定的虚拟环境](../../../../../translated_images/zh/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. 如果 VS Code Terminal 在 VS Code 启动时已经运行，它将不会激活虚拟环境。最简单的方法是使用 **Kill the active terminal instance** 按钮关闭终端：

    ![VS Code Kill the active terminal instance 按钮](../../../../../translated_images/zh/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    您可以通过终端提示的前缀来判断终端是否激活了虚拟环境。例如，它可能是：

    ```sh
    (.venv) ➜  nightlight
    ```

    如果提示中没有 `.venv` 作为前缀，则终端未激活虚拟环境。

1. 通过选择 *Terminal -> New Terminal* 或按 `` CTRL+` `` 启动一个新的 VS Code Terminal。新终端将加载虚拟环境，并在终端中显示激活此环境的调用。提示也会带有虚拟环境的名称 (`.venv`)：

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. 从 VS Code 的资源管理器中打开 `app.py` 文件，并添加以下代码：

    ```python
    print('Hello World!')
    ```

    `print` 函数会将传递给它的内容打印到控制台。

1. 从 VS Code 的终端运行以下命令以运行您的 Python 应用程序：

    ```sh
    python app.py
    ```

    输出将包含以下内容：

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 您的 "Hello World" 程序运行成功！

### 连接“硬件”

作为第二个 "Hello World" 步骤，您将运行 CounterFit 应用程序并将代码连接到它。这是将一些物联网硬件插入开发套件的虚拟等效操作。

#### 任务 - 连接“硬件”

1. 从 VS Code 的终端运行以下命令启动 CounterFit 应用程序：

    ```sh
    counterfit
    ```

    应用程序将开始运行并在您的浏览器中打开：

    ![在浏览器中运行的 Counter Fit 应用程序](../../../../../translated_images/zh/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.png)

    它将显示为 *Disconnected*，右上角的 LED 将关闭。

1. 在 `app.py` 顶部添加以下代码：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    此代码从您之前安装的 `counterfit-connection` pip 包中导入 `CounterFitConnection` 类。然后它初始化一个连接到运行在 `127.0.0.1` 上的 CounterFit 应用程序，这是一个可以始终用于访问本地计算机的 IP 地址（通常称为 *localhost*），端口为 5000。

    > 💁 如果您有其他应用程序运行在端口 5000，您可以通过更新代码中的端口并使用 `CounterFit --port <port_number>` 运行 CounterFit 来更改此端口，将 `<port_number>` 替换为您想使用的端口。

1. 您需要通过选择 **Create a new integrated terminal** 按钮启动一个新的 VS Code 终端。这是因为 CounterFit 应用程序正在当前终端中运行。

    ![VS Code Create a new integrated terminal 按钮](../../../../../translated_images/zh/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. 在这个新终端中，像之前一样运行 `app.py` 文件。CounterFit 的状态将变为 **Connected**，LED 将亮起。

    ![Counter Fit 显示为已连接](../../../../../translated_images/zh/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.png)

> 💁 您可以在 [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device) 文件夹中找到此代码。

😀 您成功连接到硬件！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。原始语言的文档应被视为权威来源。对于关键信息，建议使用专业人工翻译。我们不对因使用此翻译而产生的任何误解或误读承担责任。