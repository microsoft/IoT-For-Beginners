<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3b2448c7ab4e9673e77e35a50c5e350d",
  "translation_date": "2025-08-25T00:52:46+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/pi-gps-sensor.md",
  "language_code": "zh"
}
-->
# 读取 GPS 数据 - 树莓派

在本节课程中，您将为树莓派添加一个 GPS 传感器，并从中读取数据。

## 硬件

树莓派需要一个 GPS 传感器。

您将使用的传感器是 [Grove GPS Air530 传感器](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)。该传感器可以连接到多个 GPS 系统，以实现快速、准确的定位。传感器由两部分组成——传感器的核心电子部分，以及通过细线连接的外部天线，用于接收来自卫星的无线电波。

这是一个 UART 传感器，因此通过 UART 发送 GPS 数据。

## 连接 GPS 传感器

Grove GPS 传感器可以连接到树莓派。

### 任务 - 连接 GPS 传感器

连接 GPS 传感器。

![一个 Grove GPS 传感器](../../../../../translated_images/zh/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. 将 Grove 电缆的一端插入 GPS 传感器上的插座。它只能以一种方式插入。

1. 在树莓派断电的情况下，将 Grove 电缆的另一端连接到树莓派上 Grove Base Hat 的 **UART** 插座。该插座位于中间一排，靠近 SD 卡插槽的一侧，与 USB 端口和以太网插座相对。

    ![Grove GPS 传感器连接到 UART 插座](../../../../../translated_images/zh/pi-gps-sensor.1f99ee2b2f6528915047ec78967bd362e0e4ee0ed594368a3837b9cf9cdaca64.png)

1. 将 GPS 传感器放置好，使连接的天线能够看到天空——理想情况下靠近窗户或在室外。天线周围没有障碍物时，信号会更清晰。

## 编程 GPS 传感器

现在可以为树莓派编程以使用连接的 GPS 传感器。

### 任务 - 编程 GPS 传感器

为设备编程。

1. 启动树莓派并等待其启动完成。

1. GPS 传感器有两个 LED 指示灯——一个蓝色 LED，当数据传输时会闪烁；一个绿色 LED，当从卫星接收数据时每秒闪烁一次。启动树莓派时，确保蓝色 LED 闪烁。几分钟后，绿色 LED 会开始闪烁——如果没有，可能需要重新调整天线的位置。

1. 启动 VS Code，可以直接在树莓派上运行，也可以通过 Remote SSH 扩展连接。

    > ⚠️ 如果需要，可以参考[第 1 课中设置和启动 VS Code 的说明](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md)。

1. 对于支持蓝牙的新版本树莓派，蓝牙使用的串口与 Grove UART 端口使用的串口存在冲突。为了解决这个问题，请执行以下操作：

    1. 在 VS Code 的终端中，使用以下命令编辑 `/boot/config.txt` 文件。`nano` 是一个内置的终端文本编辑器：

        ```sh
        sudo nano /boot/config.txt
        ```

        > 由于需要 `sudo` 权限（提升的权限）才能编辑此文件，因此无法通过 VS Code 编辑。

    1. 使用光标键导航到文件末尾，然后将以下代码复制并粘贴到文件末尾：

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        您可以使用设备的常规键盘快捷键粘贴（Windows、Linux 或树莓派 OS 上为 `Ctrl+v`，macOS 上为 `Cmd+v`）。

    1. 按 `Ctrl+x` 保存文件并退出 nano。当被询问是否保存修改的缓冲区时，按 `y`，然后按 `Enter` 确认覆盖 `/boot/config.txt`。

        > 如果出错，可以不保存退出，然后重复这些步骤。

    1. 使用以下命令在 nano 中编辑 `/boot/cmdline.txt` 文件：

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. 此文件包含多个用空格分隔的键值对。删除任何键为 `console` 的键值对。它们可能看起来像这样：

        ```output
        console=serial0,115200 console=tty1 
        ```

        您可以使用光标键导航到这些条目，然后使用常规的 `del` 或 `backspace` 键删除。

        例如，如果您的原始文件如下所示：

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        新版本将如下所示：

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. 按上述步骤保存此文件并退出 nano。

    1. 重启树莓派，重启后重新连接到 VS Code。

1. 在终端中，在 `pi` 用户的主目录中创建一个名为 `gps-sensor` 的新文件夹。在此文件夹中创建一个名为 `app.py` 的文件。

1. 在 VS Code 中打开此文件夹。

1. GPS 模块通过串口发送 UART 数据。安装 `pyserial` Pip 包，以便从 Python 代码与串口通信：

    ```sh
    pip3 install pyserial
    ```

1. 将以下代码添加到您的 `app.py` 文件中：

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    这段代码从 `pyserial` Pip 包中导入了 `serial` 模块。然后它连接到 `/dev/ttyAMA0` 串口——这是 Grove Pi Base Hat 用于其 UART 端口的串口地址。接着，它清除了此串口连接中的任何现有数据。

    接下来定义了一个名为 `print_gps_data` 的函数，用于将传递给它的行打印到控制台。

    然后代码进入一个无限循环，在每次循环中读取串口中的多行文本。它为每一行调用 `print_gps_data` 函数。

    读取完所有数据后，循环会休眠 1 秒，然后再次尝试。

1. 运行此代码。您将看到来自 GPS 传感器的原始输出，类似如下内容：

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > 如果在停止和重新启动代码时遇到以下错误之一，请在 while 循环中添加一个 `try - except` 块。

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 您可以在 [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi) 文件夹中找到此代码。

😀 恭喜！您的 GPS 传感器程序运行成功！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。因使用本翻译而引起的任何误解或误读，我们概不负责。