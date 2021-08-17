# 树莓派(Raspberry Pi)

[树莓派](https://raspberrypi.org)是一个单板机，你可以用大量的设备和生态系统来给树莓派加上传感器和执行器，在这些课程中我们使用一个叫做[Grove](https://www.seeedstudio.com/category/Grove-c-1003.html)的硬件生态系统，你将会用Python来给你的Pi编程和读取传感器。

![一个树莓派 4](../../../../images/raspberry-pi-4.jpg)

## 设置

如果你要使用树莓派来作为你的物联网硬件，那么你有两个选择来完成这些课程 - 直接在树莓派上编码，或者从你的计算机远程连接到无界面的树莓派上来编码。

在你开始之前，你还需要把Grove基础扩展板连接到你的Pi上。

### 任务 - 设置

安装Grove基础扩展板并配置好你的树莓派

1. 安装Grove基础扩展板到你的树莓派，扩展板上的插孔与Pi上的GPIO引脚一一对应，沿着引脚一路滑下去来压住底部，扩展板会在上面盖住树莓派。

    ![安装grove扩展板](../../../../images/pi-grove-hat-fitting.gif)

2. 决定你要如何来编码你的树莓派，并直接跳到下面相关的部分：

    * [在树莓派上直接编码](#在树莓派上直接编码)
    * [远程连接来编码树莓派](#远程连接来编码树莓派)

### 在树莓派上直接编码

如果你想要直接在树莓派上编码，你可以使用Raspberry Pi OS的桌面版本并安装你需要的所有工具。

#### 任务 - 在树莓派上直接编码

配置树莓派的开发环境。

1. 跟着[树莓派配置指南](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up)的步骤来配置你的树莓派，给它连上一个键盘/鼠标/显示器，把它接入你的Wi-Fi或者以太网络，然后更新软件。你要安装的是**Raspberry Pi OS (32 bit)**，用Raspberry Pi Imager来烧写SD卡的时候一般都会推荐这个操作系统。

想要使用Grove传感器和执行器来给树莓派编程的话，你需要安装一个编辑器来编写设备代码和各种用来与Grove硬件交互的函数库、工具。

1. 当你的树莓派重启后，点击上方菜单栏的**Terminal** 图标或者选择*Menu -> Accessories -> Terminal*来启动终端。

1. 运行下面的命令来确保操作系统和已安装的软件都是最新的：

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. 运行下面的命令来安装所有Grove硬件需要的函数库：

    ```sh
    curl -sL https://github.com/Seeed-Studio/grove.py/raw/master/install.sh | sudo bash -s -
    ```

    Python一个强大的特性是可以安装[pip包](https://pypi.org) - 这些都是其他人编写了发布到网上的软件包，用一个命令你就可以把一个pip包安装到你的计算机上，然后在代码里面使用这个软件包了，这个Grove安装脚本会安装你用Python来操控Grove硬件时将会用到的pip软件包。

1. 用菜单点击或者运行下面的命令来重启树莓派：

    ```sh
    sudo reboot
    ```

1. 树莓派重启后，重新打开终端并运行下面的命令来安装[Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) - 你会使用这个编辑器来编写你的设备Python代码。

    ```sh
    sudo apt install code
    ```

    安装完成后，上面的菜单栏就会出现VS Code了。

    > 💁 如果你有更喜欢的工具，你也可以自由使用任意的Python IDE或者编辑器来学习课程，但是课程中会基于VS Code来给出指示。

1. 安装Pylance，这是给VS Code提供Python语言支持的扩展插件，可以参考这个[Pylance扩展文档](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance)中的指示在VS Code中安装这个插件。

### 远程连接来编码树莓派

除了直接在树莓派上编码，它也可以无界面运行，不连接键盘/鼠标/显示器，使用Visual Studio Code从你的计算机来配置和编码树莓派。

#### 配置树莓派操作系统

树莓派操作系统需要被安装在一张SD卡上才能远程编码。

##### 任务 - 配置树莓派操作系统

配置无界面树莓派系统

1. 从[树莓派操作系统软件页面](https://www.raspberrypi.org/software/)下载**Raspberry Pi Imager**并安装

1. 在你的计算机上插入一张SD卡，必要时需要使用一个转换器

1. 启动Raspberry Pi Imager

1. 在Raspberry Pi Imager点击**CHOOSE OS**，选择*Raspberry Pi OS (Other)*，然后选择*Raspberry Pi OS Lite (32-bit)*

    ![Raspberry Pi Imager选择Raspberry Pi OS Lite](../../../../images/raspberry-pi-imager.png)

    > 💁 Raspberry Pi OS Lite是一个没有桌面UI或者基于UI的工具的操作系统版本，这些对于无界面树莓派来说都是不需要的，而且这样可以安装更小的空间、启动速度也更快。

1. 点击**CHOOSE STORAGE** 按钮，然后选择你的SD卡

1. 按下`Ctrl+Shift+X`来启动**Advanced Options**，这些选项允许你在烧写到SD卡之前对Raspberry Pi OS进行一些预配置。

    1. 勾选**Enable SSH**，然后给用户`pi`设置一个密码，这是你等会用来登录的密码。

    2. 如果你打算通过WiFi连接到树莓派，那么需要勾选**Configure WiFi**，然后输入你WiFi的SSID和密码并选择你的国家码。如果打算使用以太网线缆来连接，那就不需要做这一步了，只需要确保树莓派和你的计算机连接的是同一个网络就行。

    3. 勾选**Set locale settings**，设置你的国家和时区。

    4. 点击 **SAVE** 按钮

2. 点击**WRITE**按钮把OS烧写到SD卡上，如果你使用的是MacOS，你会被要求输入你的密码，因为底层的写磁盘镜像的工具需要访问权限。

操作系统会被烧写到SD卡上，完成之后SD卡会被弹出，并且你会收到通知。从你的计算机拔出SD卡，再把它插到树莓派上并上电启动。

#### 连接到树莓派

接下来的一个步骤是远程连接树莓派，你可以使用`ssh`，这个工具在macOS、Linux和最近几个版本的Windows上都可以直接使用。

##### 任务 - 连接到树莓派

远程连接树莓派。

1. 启动一个终端或者命令提示符，输入下面的命令来连接树莓派：

    ```sh
    ssh pi@raspberrypi.local
    ```

    如果你是在一个老版本没有安装`ssh`的Windows上，可以使用OpenSSH，你可以在[OpenSSH安装文档](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn)里找到安装指南。

2. 这应该会连上你的树莓派，并且会请求密码。

    通过`<hostname>.local`来寻找你的网络中的计算机是Linux和Windows最近才加入的功能，如果你是在使用Linux或者Windows过程中遇到一些Hostname无法找到的问题，你会需要安装一些额外的软件来启用ZeroConf网络（也被Apple称为Bonjour）：

    1. 如果你在使用Linux，用下面的命令来安装Avahi：

        ```sh
        sudo apt-get install avahi-daemon
        ```

    2. 如果你在使用Windows，启用ZeroConf最简单的方法是安装[Bonjour Print Services for Windows](http://support.apple.com/kb/DL999)，你也可以安装[iTunes for Windows](https://www.apple.com/itunes/download/)来获取更新版本的组件（无法独立下载安装）。

    > 💁 如果你无法通过`raspberrypi.local`连接，那么你也可以使用你的树莓派的IP地址，参考[树莓派IP地址文档](https://www.raspberrypi.org/documentation/remote-access/ip-address.md)上大量的获取IP地址的方法。

3. 输入你在Raspberry Pi Imager高级选项中输入的密码

#### 在树莓派上配置软件

当你连接上树莓派之后，你需要确保这个操作系统是最新的，并且安装各类用于和Grove硬件交互的函数库和工具。

##### 任务 - 在树莓派上配置软件

配置已安装的树莓派软件并安装Grove的函数库。

1. 从你的`ssh`会话中，运行下面的命令来更新并重启树莓派：

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    树莓派会被更新并重启，这个`ssh`会话在树莓派重启的时候会中断，等待30秒后重连就行。

2. 从重连的`ssh`会话中，运行下面的命令来安装Grove硬件需要的函数库：

    ```sh
    curl -sL https://github.com/Seeed-Studio/grove.py/raw/master/install.sh | sudo bash -s -
    ```
    Python一个强大的特性是可以安装[pip包](https://pypi.org) - 这些都是其他人编写了发布到网上的软件包，用一个命令你就可以把一个pip包安装到你的计算机上，然后在代码里面使用这个软件包了，这个Grove安装脚本会安装你用Python来操控Grove硬件时将会用到的pip软件包。

3. 用下面的命令来重启树莓派：

    ```sh
    sudo reboot
    ```

    树莓派重启的时候`ssh`会话会中断，不要再重新连接。

#### 配置VS Code的远程连接

树莓派配置完以后，你可以从你的计算机通过Visual Studio Code (VS Code)来连接到它 - 这是一个你将要用Python来写设备代码的免费开发者编辑器。

##### 任务 - 配置VS Code的远程连接

安装需要的软件并远程连接到你的树莓派。

1. 跟着[VS Code 文档](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)在你的计算机上安装 VS Code

2. 根据[VS Code远程SSH开发文档](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn)的步骤来安装需要的组件

3. 根据相同的指示，连接VS Code到树莓派

4. 连接上之后，根据[管理扩展程序](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn)的指示来远程安装[Pylance扩展程序](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance)到树莓派上

## Hello world

开始一门新的编程语言或者技术时创建一个'Hello World'的程序是一个传统 - 一个输出类似于`"Hello World"`文本的小程序，用来证明所有的工具都已经配置正确了。

树莓派的这个Hello World程序可以确保你已经把Python和Visual Studio Code正确安装了。

这个程序会在一个叫`nightlight`的文件夹里面，他会在这个任务后面部分的不同代码里面再次使用，用来构建夜灯程序。

### 任务 - hello world

创建Hello World应用。

1. 直接在树莓派上启动VS Code，或者在你的计算机上用远程SSH扩展来连接到树莓派。

2. 选择 *Terminal -> New Terminal* 或者按下`` CTRL+` `` 来启动VS Code，这会打开在`pi`的home目录。

3. 运行下面的命令来为你的代码创建一个目录，并在目录里创建一个叫`app.py`的Python文件：

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

4. 在VS Code中点击*File -> Open...*并选择*nightlight*文件夹和 **OK** 来打开这个文件夹

    ![VS Code打开nightlight文件夹的对话框](../../../../images/vscode-open-nightlight-remote.png)

5. 从VS Code窗口打开 `app.py` 文件并增加下面的代码：

    ```python
    print('Hello World!')
    ```

    `print`函数会在终端打印任何传递给它的东西。

6. 从VS Code的终端运行下面的命令来运行你的Python应用：

    ```sh
    python3 app.py
    ```

    > 💁 你需要显式的调用`python3`来运行这个代码，以防你除了Python 3（最新版本）还安装了Python 2，如果你安装了Python 2，那么调用`python`命令时会使用Python 2 而不是Python 3

    终端里会出现下面的输出：

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 你可以在[code/pi](../code/pi) 文件夹里找到这个代码

😀 你的'Hello World'程序成功了!
