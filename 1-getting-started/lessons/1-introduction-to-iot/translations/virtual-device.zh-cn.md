# 虚拟单板机

除了买一个 IoT 设备、传感器和执行器，你也可以用你的电脑来模拟 IoT 硬件。[CounterFit 项目](https://github.com/CounterFit-IoT/CounterFit) 让你在自己的电脑上运行模拟 IoT 硬件（如传感器和执行器）的应用，并从本地Python代码访问传感器和执行器，代码的编写方式，与使用Raspberry Pi物理硬件相同。

## 设置

使用 CounterFit 前，你必须在你的电脑上安装一些免费的软件。 

### 任务

安装需要的软件。

1. 安装 Python。 在 [Python 的下载页](https://www.python.org/downloads/) 找到最新版本Python的安装指示。

1. 安装 Visual Studio Code (VS Code)。 这是你将用来写虚拟设备的 Python代码的代码编辑器。在 [VS Code 文档](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) 找到VS Code的安装指示。

    > 💁 如果你对其它平台比较熟悉，你当然可以用你较喜欢的 Python IDE 或 代码编辑器，但注意这个课程将根据VS Code提供说明。

1. 安装 VS Code 的 Pylance 扩展。 这个 VS Code 扩展提供 Python 语言支持。在 [Pylance 扩展文档](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) 找安装扩展的指示。

我们将在日后的作业中提供安装及设置 CounterFit 的说明，因为我们需要在每个项目中安装它。

## Hello world（你好，世界）

第一次用新的编程语言或技术，通常以创建一个“Hello World”应用开始——一个输出类似`"Hello World"`文本的小小应用，以确保所有的工具被设置好。

这个虚拟 IoT 硬件的“Hello World”应用将确保你安装好 Python 与 Visual Studio Code。它也会连接到 CounterFit以获取虚拟 IoT 传感器和执行器。它不会用到任何硬件，它只会以正确连接来证明每个部分运作良好。

这个应用放在名为`nightlight`的文件夹中，稍后将和其他代码结合，以构建夜灯应用。

### 配置 Python 虚拟环境

Python 的强大功能之一是能够安装 [pip 软件包](https://pypi.org)；这些是由其他人编写并发布到互联网上的代码包。只需一条命令就可以在你的电脑上安装pip 软件包，并在你的代码中使用它。你将用 pip 安装一个软件包，来与CounterFit 沟通。

默认情况下，当你安装软件包时，在计算机的任何位置都是可用的，而这可能会造成软件包版本问题，例如：当你为新应用安装软件包的新版本，依靠旧版本的另一应用就有可能出现状况。为了避免这种问题，你可以使用 [Python 虚拟环境](https://docs.python.org/3/library/venv.html)，本质上是一个专用文件夹中的 Python 副本，当你安装 pip 软件包时，它们只会安装到那个文件夹中。

#### 任务：配置一个 Python 虚拟环境

配置一个 Python 虚拟环境便安装为 CounterFit 的 pip 软件包。

1. 从你的终端或命令行，在你选的地方运行以下的程序，来创建和导航到一个新目录：

    ```sh
    mkdir nightlight
    cd nightlight
    ```

2. 现在，运行以下的程序来在`.venv` 文件夹中创建一个虚拟环境

    ```sh
    python3 -m venv .venv
    ```

    > 💁 为了创建虚拟环境，你必须明确地调用 `python3`，万一 Python 3 （最新版本）以外你也曾经安装过 Python 2。如果你安装过 Python 2，那调用 `python` 将用到 Python 2 而不是 Python 3。

3. 激活虚拟环境：

    * 在 Windows 运行：

        ```cmd
        .venv\Scripts\activate.bat
        ```

    * 在 macOS 或 Linux，运行：

        ```cmd
        source ./.venv/bin/activate
        ```

4. 虚拟环境一被激活，默认的 `python` 命令将运行用来创建虚拟环境的 Python 版本。为了拿到版本，运行以下的程序：

    ```sh
    python --version
    ```

    输出应该包括一下：

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 你的 Python 版本有可能不一样，但只要版本是 3.6 或以上就没事。不然，请删除这个文件夹，并安装较新的 Python 版本，再试一试。

5. 运行以下的命令来安装CounterFit 软件包。这些软件包包括主要的 CounterFit 应用以及 Grove 硬件的[垫片](https://zh.wikipedia.org/wiki/%E5%9E%AB%E7%89%87_(%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1))。这些垫片让你就像用来自 Grove 生态系统的物理传感器和执行器一样写代码，但把它连接到虚拟 IoT 设备。

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

这些 pip 软件包只会在虚拟环境中安装，而你无法在虚拟环境外访问它。

### 编写代码

一旦Python 虚拟环境被准备好，你就能为 “Hello World” 应用写代码。

#### 任务：编写代码

创建一个 Python 应用在控制台上打印`"Hello World"` 输出。

1. 从你的终端或命令行，在虚拟环境中运行以下的程序来创建一个叫做`app.py` 的 Python 文件：

    * 在 Windows 运行：

        ```cmd
        type nul > app.py
        ```

    * 在 macOS 或 Linux，运行：

        ```cmd
        touch app.py
        ```

2. 在 VS Code 打开当前的文件夹：

    ```sh
    code .
    ```

    > 💁 如果你的终端在 macOS 返回`command not found`，那就代表 VS Code 还未被加进你的 PATH。为了把 VS Code 加进你的 PATH，你可以按照 [Launching from the command line section of the VS Code 文档](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) 的指示，然后运行命令。在 Windows 和 Linux，VS Code 默认被加进你的 PATH。

3. 当 VS Code 被启动，它会激活 Python 虚拟环境。被选择的虚拟环境将在底部状态栏出现：

    ![ 被选择的虚拟环境将在 VS Code的底部状态栏出现](../../../images/vscode-virtual-env.png)

4. 如果VS Code 被启动时VS Code 终端已经正在运行，虚拟环境不会被激活。这时，最容易做的是用 **Kill the active terminal instance** 的按钮：

    ![VS Code Kill the active terminal instance 按钮](../../../images/vscode-kill-terminal.png)

    虚拟环境的名字将是终端提示的字首，所以你可以把它用来确认虚拟环境已经被激活。例如，它可能是：

    ```sh
    (.venv) ➜  nightlight
    ```

    如果你没有 `.venv` 的字首在提示上，虚拟环境不在终端中活动。

5. 为了启动一个新的 VS Code 终端，选择*Terminal -> New Terminal 或按`` CTRL+` ``。这个新终端将加载虚拟环境，以及激活它的调用将在终端中出现。提示也会有虚拟环境的名字（`.venv`）：

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

6. 从 VS Code explorer 打开 `app.py` 文件，并添加以下的代码：

    ```python
    print('Hello World!')
    ```

    `print` 函数将在控制台打印出函数中的任何东西。

7. 从 VS Code 终端，运行以下的程序来运行你的 Python 应用：

    ```sh
    python app.py
    ```

    以下将在输出中：

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 你的 “Hello World” 编码成功了！

### 连接“硬件”

你的第二个“Hello World”步骤，是运行 CounterFit 应用并连接你的代码。这相当于把一些 IoT 硬件插入开发者套件。

#### 任务：连接“硬件”

1. 从 VS Code 终端，用以下的命令启动 CounterFit 应用：

    ```sh
    CounterFit
    ```

    应用将开始运行以及在你的网页浏览器打开：

    ![CounterFit 应用在网页浏览器运行](../../../../images/counterfit-first-run.png)

    他会有个 *Disconnected*（断开连接）的标记，右上角的 LED 也会关着。

2. 在 `app.py` 上加以下的代码：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

这个代码从 `counterfit_connection` 模块进口`CounterFitConnection` 类；这个模块来自你刚才安装的 `counterfit-connection` pip 软件包。然后，它初始化跟 CounterFit 应用的连接。应用在`127.0.0.1` 运行着；它是一个IP 地址，而你一直可以用它在端口 5000 访问你的本地电脑（通常被叫为*localhost*）。

   > 💁 如果你有其它应用正在端口 5000 运行着，你可以在代码更新端口，再用 `CounterFit --port <port_number>` 运行 CounterFit，在`<port_number>` 填着你想用的端口。

3. 你必须选择 **Create a new integrated terminal** 按钮来启动一个新 VS Code 终端。这是因为 CounterFit 应用正在当前终端运行着。

    ![VS Code Create a new integrated terminal 按钮](../../../../images/vscode-new-terminal.png)

4. 在这个新终端，像以前一样运行`app.py` 文件。CounterFit 的状态将改成 **Connected** （连接），LED也会开着。

    ![CounterFit 被连接了](../../../../images/counterfit-connected.png)

> 💁 你可以在 [code/virtual-device](../code/virtual-device) 文件夹找到这个代码。

😀 你的硬件连接成功了！
