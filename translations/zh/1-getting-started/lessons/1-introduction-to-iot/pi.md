<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-24T23:34:33+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "zh"
}
-->
# 树莓派

[树莓派](https://raspberrypi.org) 是一款单板计算机。你可以通过各种设备和生态系统添加传感器和执行器，在这些课程中，我们将使用一个名为 [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html) 的硬件生态系统。你将使用 Python 编写代码来控制树莓派并访问 Grove 传感器。

![树莓派 4](../../../../../translated_images/zh/raspberry-pi-4.fd4590d308c3d456.webp)

## 设置

如果你使用树莓派作为物联网硬件，有两种选择——你可以直接在树莓派上完成所有课程并编写代码，或者通过远程连接到一个“无头”树莓派，从你的电脑上进行编程。

在开始之前，你还需要将 Grove 基座帽连接到树莓派。

### 任务 - 设置

安装 Grove 基座帽并配置树莓派

1. 将 Grove 基座帽连接到树莓派。基座帽上的插槽与树莓派的所有 GPIO 引脚对接，滑动到底部，牢固地固定在基座上。它覆盖在树莓派上。

    ![安装 Grove 基座帽](../../../../../images/pi-grove-hat-fitting.gif)

1. 决定如何编程树莓派，然后进入以下相关部分：

    * [直接在树莓派上工作](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [远程访问树莓派进行编程](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### 直接在树莓派上工作

如果你想直接在树莓派上工作，可以使用树莓派 OS 的桌面版本并安装所需的所有工具。

#### 任务 - 直接在树莓派上工作

为开发设置树莓派。

1. 按照 [树莓派设置指南](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) 中的说明设置树莓派，连接键盘/鼠标/显示器，连接到 WiFi 或以太网网络，并更新软件。

为了使用 Grove 传感器和执行器编程树莓派，你需要安装一个编辑器来编写设备代码，以及与 Grove 硬件交互的各种库和工具。

1. 树莓派重启后，点击顶部菜单栏的 **Terminal** 图标启动终端，或者选择 *Menu -> Accessories -> Terminal*

1. 运行以下命令以确保操作系统和已安装的软件是最新的：

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. 运行以下命令安装 Grove 硬件所需的所有库：

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    这首先安装了 Git 和用于安装 Python 包的 Pip。

    Python 的一个强大功能是可以安装 [Pip 包](https://pypi.org)——这些是其他人编写并发布到互联网的代码包。你可以通过一个命令将 Pip 包安装到你的电脑上，然后在代码中使用该包。

    Seeed Grove 的 Python 包需要从源码安装。这些命令将克隆包含该包源码的仓库，然后在本地安装。

    > 💁 默认情况下，当你安装一个包时，它会在你的电脑上全局可用，这可能会导致包版本问题——例如，一个应用程序依赖于某个版本的包，而另一个应用程序安装新版本时可能会导致问题。为了解决这个问题，你可以使用 [Python 虚拟环境](https://docs.python.org/3/library/venv.html)，它本质上是一个专用文件夹中的 Python 副本，当你安装 Pip 包时，它们只会安装到该文件夹中。在使用树莓派时，你不会使用虚拟环境。Grove 安装脚本会全局安装 Grove 的 Python 包，因此如果你想使用虚拟环境，需要先设置虚拟环境，然后手动重新安装 Grove 包到该环境中。使用全局包更简单，尤其是许多树莓派开发者会为每个项目重新刷写干净的 SD 卡。

    最后，这启用了 I<sup>2</sup>C 接口。

1. 使用菜单或在终端中运行以下命令重启树莓派：

    ```sh
    sudo reboot
    ```

1. 树莓派重启后，重新启动终端并运行以下命令安装 [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)——这是你将用来用 Python 编写设备代码的编辑器。

    ```sh
    sudo apt install code
    ```

    安装完成后，VS Code 可以从顶部菜单中访问。

    > 💁 如果你有偏好的工具，可以自由使用任何 Python IDE 或编辑器完成这些课程，但课程中的说明将基于 VS Code。

1. 安装 Pylance。这是 VS Code 的一个扩展，提供 Python 语言支持。参考 [Pylance 扩展文档](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) 了解如何在 VS Code 中安装此扩展。

### 远程访问树莓派进行编程

与直接在树莓派上编程不同，它可以运行“无头”模式，即不连接键盘/鼠标/显示器，并通过你的电脑进行配置和编程，使用 Visual Studio Code。

#### 设置树莓派操作系统

要远程编程，需要在 SD 卡上安装树莓派操作系统。

##### 任务 - 设置树莓派操作系统

设置无头树莓派操作系统。

1. 从 [树莓派操作系统软件页面](https://www.raspberrypi.org/software/) 下载 **树莓派镜像工具** 并安装

1. 将 SD 卡插入你的电脑，必要时使用适配器

1. 启动树莓派镜像工具

1. 在树莓派镜像工具中，选择 **CHOOSE OS** 按钮，然后选择 *Raspberry Pi OS (Other)*，接着选择 *Raspberry Pi OS Lite (32-bit)*

    ![树莓派镜像工具选择 Raspberry Pi OS Lite](../../../../../translated_images/zh/raspberry-pi-imager.24aedeab9e233d84.webp)

    > 💁 Raspberry Pi OS Lite 是树莓派操作系统的一个版本，没有桌面 UI 或基于 UI 的工具。这些对于无头树莓派来说是不需要的，并且使安装更小，启动时间更快。

1. 选择 **CHOOSE STORAGE** 按钮，然后选择你的 SD 卡

1. 按下 `Ctrl+Shift+X` 启动 **高级选项**。这些选项允许在将操作系统写入 SD 卡之前进行一些预配置。

    1. 勾选 **Enable SSH** 复选框，并为 `pi` 用户设置密码。这是你稍后登录树莓派时使用的密码。

    1. 如果你计划通过 WiFi 连接到树莓派，勾选 **Configure WiFi** 复选框，并输入你的 WiFi SSID 和密码，同时选择你的 WiFi 国家。如果你将使用以太网线，则无需执行此操作。确保你连接的网络与你的电脑在同一个网络中。

    1. 勾选 **Set locale settings** 复选框，并设置你的国家和时区

    1. 选择 **SAVE** 按钮

1. 选择 **WRITE** 按钮将操作系统写入 SD 卡。如果你使用 macOS，系统会要求你输入密码，因为写入磁盘镜像的底层工具需要特权访问。

操作系统将被写入 SD 卡，完成后操作系统会弹出 SD 卡，并通知你。将 SD 卡从电脑中取出，插入树莓派，启动树莓派并等待大约 2 分钟让其正常启动。

#### 连接到树莓派

下一步是远程访问树莓派。你可以使用 `ssh` 来完成，这在 macOS、Linux 和最新版本的 Windows 上都可用。

##### 任务 - 连接到树莓派

远程访问树莓派。

1. 启动终端或命令提示符，输入以下命令连接到树莓派：

    ```sh
    ssh pi@raspberrypi.local
    ```

    如果你使用的是旧版本的 Windows，没有安装 `ssh`，可以使用 OpenSSH。安装说明可以在 [OpenSSH 安装文档](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn) 中找到。

1. 这将连接到你的树莓派并要求输入密码。

    通过 `<hostname>.local` 在网络中找到计算机是 Linux 和 Windows 最近添加的功能。如果你使用 Linux 或 Windows 并收到关于找不到主机名的错误，则需要安装额外的软件以启用 ZeroConf 网络（Apple 称为 Bonjour）：

    1. 如果你使用 Linux，运行以下命令安装 Avahi：

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. 如果你使用 Windows，启用 ZeroConf 的最简单方法是安装 [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999)。你也可以安装 [iTunes for Windows](https://www.apple.com/itunes/download/) 来获取更新版本的工具（独立版本不可用）。

    > 💁 如果你无法使用 `raspberrypi.local` 连接，可以使用树莓派的 IP 地址。参考 [树莓派 IP 地址文档](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) 了解获取 IP 地址的多种方法。

1. 输入你在树莓派镜像工具高级选项中设置的密码

#### 配置树莓派上的软件

连接到树莓派后，需要确保操作系统是最新的，并安装与 Grove 硬件交互的各种库和工具。

##### 任务 - 配置树莓派上的软件

配置已安装的树莓派软件并安装 Grove 库。

1. 在你的 `ssh` 会话中，运行以下命令更新并重启树莓派：

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    树莓派将被更新并重启。树莓派重启时，`ssh` 会话将结束，因此等待大约 30 秒后重新连接。

1. 在重新连接的 `ssh` 会话中，运行以下命令安装 Grove 硬件所需的所有库：

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    这首先安装了 Git 和用于安装 Python 包的 Pip。

    Python 的一个强大功能是可以安装 [Pip 包](https://pypi.org)——这些是其他人编写并发布到互联网的代码包。你可以通过一个命令将 Pip 包安装到你的电脑上，然后在代码中使用该包。

    Seeed Grove 的 Python 包需要从源码安装。这些命令将克隆包含该包源码的仓库，然后在本地安装。

    > 💁 默认情况下，当你安装一个包时，它会在你的电脑上全局可用，这可能会导致包版本问题——例如，一个应用程序依赖于某个版本的包，而另一个应用程序安装新版本时可能会导致问题。为了解决这个问题，你可以使用 [Python 虚拟环境](https://docs.python.org/3/library/venv.html)，它本质上是一个专用文件夹中的 Python 副本，当你安装 Pip 包时，它们只会安装到该文件夹中。在使用树莓派时，你不会使用虚拟环境。Grove 安装脚本会全局安装 Grove 的 Python 包，因此如果你想使用虚拟环境，需要先设置虚拟环境，然后手动重新安装 Grove 包到该环境中。使用全局包更简单，尤其是许多树莓派开发者会为每个项目重新刷写干净的 SD 卡。

    最后，这启用了 I<sup>2</sup>C 接口。

1. 运行以下命令重启树莓派：

    ```sh
    sudo reboot
    ```

    树莓派重启时，`ssh` 会话将结束。无需重新连接。

#### 配置 VS Code 进行远程访问

树莓派配置完成后，你可以使用 Visual Studio Code (VS Code) 从你的电脑连接到它——这是一个免费的开发文本编辑器，你将用它用 Python 编写设备代码。

##### 任务 - 配置 VS Code 进行远程访问

安装所需软件并远程连接到树莓派。

1. 按照 [VS Code 文档](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) 的说明在你的电脑上安装 VS Code

1. 按照 [VS Code 使用 SSH 进行远程开发文档](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) 的说明安装所需组件

1. 按照相同的说明，将 VS Code 连接到树莓派

1. 连接后，按照 [管理扩展](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) 的说明，将 [Pylance 扩展](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) 远程安装到树莓派上

## Hello world
在学习一门新的编程语言或技术时，通常会从创建一个“Hello World”应用程序开始。这是一个小型应用程序，用于输出类似于 `"Hello World"` 的文本，以验证所有工具是否已正确配置。

针对树莓派的 Hello World 应用程序将确保您正确安装了 Python 和 Visual Studio Code。

这个应用程序将存放在一个名为 `nightlight` 的文件夹中。在本任务的后续部分中，我们会在此基础上添加不同的代码，最终构建一个夜灯应用程序。

### 任务 - Hello World

创建 Hello World 应用程序。

1. 启动 VS Code，可以直接在树莓派上运行，也可以通过 Remote SSH 扩展在您的电脑上连接到树莓派运行。

1. 通过选择 *Terminal -> New Terminal* 或按下 `` CTRL+` `` 打开 VS Code 的终端。终端会默认打开到 `pi` 用户的主目录。

1. 运行以下命令，为您的代码创建一个目录，并在该目录中创建一个名为 `app.py` 的 Python 文件：

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. 在 VS Code 中打开这个文件夹，选择 *File -> Open...*，然后选择 *nightlight* 文件夹，最后点击 **OK**。

    ![VS Code 的打开对话框显示了 nightlight 文件夹](../../../../../translated_images/zh/vscode-open-nightlight-remote.d3d2a4011e30d535.webp)

1. 从 VS Code 的资源管理器中打开 `app.py` 文件，并添加以下代码：

    ```python
    print('Hello World!')
    ```

    `print` 函数会将传递给它的内容打印到控制台。

1. 在 VS Code 的终端中运行以下命令来运行您的 Python 应用程序：

    ```sh
    python app.py
    ```

    > 💁 如果您的设备同时安装了 Python 2 和 Python 3，可能需要显式调用 `python3` 来运行此代码。如果调用 `python`，系统可能会默认使用 Python 2 而不是 Python 3。默认情况下，最新版本的树莓派操作系统只安装了 Python 3。

    终端中会显示以下输出：

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 您可以在 [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi) 文件夹中找到这段代码。

😀 恭喜！您的 'Hello World' 程序运行成功！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。原始语言的文档应被视为权威来源。对于重要信息，建议使用专业人工翻译。我们对因使用此翻译而产生的任何误解或误读不承担责任。