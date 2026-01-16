<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-24T23:38:10+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "zh"
}
-->
# Wio Terminal

[Seeed Studios 的 Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) 是一款兼容 Arduino 的微控制器，内置 WiFi 和一些传感器及执行器，同时还提供了端口，可以通过名为 [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html) 的硬件生态系统添加更多传感器和执行器。

![Seeed Studios 的 Wio Terminal](../../../../../translated_images/zh/wio-terminal.b8299ee16587db9a.webp)

## 设置

要使用 Wio Terminal，您需要在计算机上安装一些免费的软件。此外，在将其连接到 WiFi 之前，您还需要更新 Wio Terminal 的固件。

### 任务 - 设置

安装所需的软件并更新固件。

1. 安装 Visual Studio Code (VS Code)。这是您将用来用 C/C++ 编写设备代码的编辑器。请参考 [VS Code 文档](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) 了解安装 VS Code 的说明。

    > 💁 另一个用于 Arduino 开发的流行 IDE 是 [Arduino IDE](https://www.arduino.cc/en/software)。如果您已经熟悉这个工具，那么可以选择使用它而不是 VS Code 和 PlatformIO，但课程将基于使用 VS Code 的说明。

1. 安装 VS Code 的 PlatformIO 扩展。这是一个支持用 C/C++ 编程微控制器的 VS Code 扩展。请参考 [PlatformIO 扩展文档](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) 了解如何在 VS Code 中安装此扩展。此扩展依赖于 Microsoft 的 C/C++ 扩展，安装 PlatformIO 时会自动安装 C/C++ 扩展。

1. 将 Wio Terminal 连接到您的计算机。Wio Terminal 底部有一个 USB-C 接口，需要将其连接到计算机的 USB 接口。Wio Terminal 附带一根 USB-C 到 USB-A 的数据线，但如果您的计算机只有 USB-C 接口，则需要一根 USB-C 数据线或 USB-A 转 USB-C 转接头。

1. 按照 [Wio Terminal Wiki WiFi 概述文档](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) 中的说明设置 Wio Terminal 并更新固件。

## Hello World

在学习一种新的编程语言或技术时，通常会创建一个 "Hello World" 应用程序——一个小型应用程序，用于输出类似 `"Hello World"` 的文本，以验证所有工具是否已正确配置。

Wio Terminal 的 Hello World 应用程序将确保您已正确安装 Visual Studio Code 和 PlatformIO，并完成微控制器开发的设置。

### 创建一个 PlatformIO 项目

第一步是使用为 Wio Terminal 配置的 PlatformIO 创建一个新项目。

#### 任务 - 创建一个 PlatformIO 项目

创建 PlatformIO 项目。

1. 将 Wio Terminal 连接到您的计算机

1. 启动 VS Code

1. 在侧边菜单栏中找到 PlatformIO 图标：

    ![PlatformIO 菜单选项](../../../../../translated_images/zh/vscode-platformio-menu.297be26b9733e5c4.webp)

    选择此菜单项，然后选择 *PIO Home -> Open*

    ![PlatformIO 打开选项](../../../../../translated_images/zh/vscode-platformio-home-open.3f9a41bfd3f4da1c.webp)

1. 在欢迎界面中，选择 **+ New Project** 按钮

    ![新建项目按钮](../../../../../translated_images/zh/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.webp)

1. 在 *Project Wizard* 中配置项目：

    1. 将项目命名为 `nightlight`

    1. 在 *Board* 下拉菜单中输入 `WIO` 以筛选板卡，选择 *Seeeduino Wio Terminal*

    1. 将 *Framework* 保持为 *Arduino*

    1. 可以保持勾选 *Use default location* 复选框，或者取消勾选并选择项目的保存位置

    1. 选择 **Finish** 按钮

    ![完成的项目向导](../../../../../translated_images/zh/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.webp)

    PlatformIO 将下载编译 Wio Terminal 代码所需的组件并创建您的项目。这可能需要几分钟。

### 查看 PlatformIO 项目

VS Code 的资源管理器将显示由 PlatformIO 向导创建的多个文件和文件夹。

#### 文件夹

* `.pio` - 此文件夹包含 PlatformIO 所需的临时数据，例如库或编译后的代码。如果删除，它会自动重新创建。如果您将项目共享到 GitHub 等网站，则无需将此文件夹添加到源代码管理中。
* `.vscode` - 此文件夹包含 PlatformIO 和 VS Code 的配置文件。如果删除，它会自动重新创建。如果您将项目共享到 GitHub 等网站，则无需将此文件夹添加到源代码管理中。
* `include` - 此文件夹用于存放在添加额外库时需要的外部头文件。在这些课程中，您不会使用此文件夹。
* `lib` - 此文件夹用于存放您希望从代码中调用的外部库。在这些课程中，您不会使用此文件夹。
* `src` - 此文件夹包含应用程序的主要源代码。最初，它只包含一个文件——`main.cpp`。
* `test` - 此文件夹用于存放代码的单元测试。

#### 文件

* `main.cpp` - `src` 文件夹中的此文件包含应用程序的入口点。打开此文件，您会看到以下代码：

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    当设备启动时，Arduino 框架会运行一次 `setup` 函数，然后重复运行 `loop` 函数，直到设备关闭。

* `.gitignore` - 此文件列出了在将代码添加到 git 源代码管理（例如上传到 GitHub 仓库）时需要忽略的文件和目录。

* `platformio.ini` - 此文件包含设备和应用程序的配置。打开此文件，您会看到以下代码：

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    `[env:seeed_wio_terminal]` 部分包含 Wio Terminal 的配置。您可以有多个 `env` 部分，以便为多个板卡编译代码。

    其他值与项目向导中的配置相匹配：

  * `platform = atmelsam` 定义了 Wio Terminal 使用的硬件（基于 ATSAMD51 的微控制器）
  * `board = seeed_wio_terminal` 定义了微控制器板卡的类型（Wio Terminal）
  * `framework = arduino` 定义了此项目使用 Arduino 框架。

### 编写 Hello World 应用程序

现在您可以开始编写 Hello World 应用程序了。

#### 任务 - 编写 Hello World 应用程序

编写 Hello World 应用程序。

1. 在 VS Code 中打开 `main.cpp` 文件

1. 将代码更改为以下内容：

    ```cpp
    #include <Arduino.h>

    void setup()
    {
        Serial.begin(9600);

        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    
    void loop()
    {
        Serial.println("Hello World");
        delay(5000);
    }
    ```

    `setup` 函数初始化与串口的连接——在本例中是用于连接 Wio Terminal 和计算机的 USB 接口。参数 `9600` 是 [波特率](https://wikipedia.org/wiki/Symbol_rate)（也称为符号率），即数据通过串口传输的速度，单位是每秒比特数（bps）。此设置表示每秒传输 9,600 比特（0 和 1）。然后，它等待串口准备就绪。

    `loop` 函数将字符串 `Hello World!` 发送到串口，同时附加一个换行符。然后，它会暂停 5,000 毫秒（5 秒）。`loop` 函数结束后会再次运行，如此循环，直到微控制器断电。

1. 将 Wio Terminal 设置为上传模式。每次上传新代码到设备时都需要这样做：

    1. 快速向下拨动电源开关两次——每次都会弹回到开启位置。

    1. 检查 USB 接口右侧的蓝色状态 LED。它应该呈现脉冲状闪烁。
    
    [![如何将 Wio Terminal 设置为上传模式的视频](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    点击上方图片观看操作视频。

1. 编译并上传代码到 Wio Terminal

    1. 打开 VS Code 的命令面板

    1. 输入 `PlatformIO Upload` 搜索上传选项，选择 *PlatformIO: Upload*

        ![命令面板中的 PlatformIO 上传选项](../../../../../translated_images/zh/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.webp)

        如果需要，PlatformIO 会自动编译代码，然后上传。

    1. 代码将被编译并上传到 Wio Terminal

        > 💁 如果您使用的是 macOS，可能会出现 *DISK NOT EJECTED PROPERLY* 的通知。这是因为在闪存过程中，Wio Terminal 会被挂载为一个驱动器，当编译后的代码写入设备时会断开连接。您可以忽略此通知。

    ⚠️ 如果出现上传端口不可用的错误，首先确保 Wio Terminal 已连接到计算机，并通过屏幕左侧的开关打开电源并设置为上传模式。底部的绿灯应亮起，蓝灯应呈现脉冲状闪烁。如果仍然出现错误，请快速向下拨动电源开关两次以强制 Wio Terminal 进入上传模式，然后重试上传。

PlatformIO 提供了一个串口监视器，可以通过 USB 数据线监视从 Wio Terminal 发送的数据。这使您可以监视 `Serial.println("Hello World");` 命令发送的数据。

1. 打开 VS Code 的命令面板

1. 输入 `PlatformIO Serial` 搜索串口监视器选项，选择 *PlatformIO: Serial Monitor*

    ![命令面板中的 PlatformIO 串口监视器选项](../../../../../translated_images/zh/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.webp)

    一个新终端将打开，串口发送的数据将流入此终端：

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` 将每 5 秒打印一次到串口监视器。

> 💁 您可以在 [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal) 文件夹中找到此代码。

😀 恭喜！您的 "Hello World" 程序运行成功！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。原始语言的文档应被视为权威来源。对于重要信息，建议使用专业人工翻译。我们不对因使用此翻译而产生的任何误解或误读承担责任。