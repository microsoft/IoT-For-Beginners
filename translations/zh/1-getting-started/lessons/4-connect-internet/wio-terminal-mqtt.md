<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-24T23:10:36+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "zh"
}
-->
# 通过互联网控制夜灯 - Wio Terminal

需要为物联网设备编写代码，使其通过 MQTT 与 *test.mosquitto.org* 通信，发送包含光传感器读数的遥测值，并接收控制 LED 的命令。

在本节课程中，您将把 Wio Terminal 连接到一个 MQTT 代理。

## 安装 WiFi 和 MQTT Arduino 库

为了与 MQTT 代理通信，您需要安装一些 Arduino 库，以便使用 Wio Terminal 的 WiFi 芯片并与 MQTT 通信。在为 Arduino 设备开发时，您可以使用大量包含开源代码的库，这些库实现了广泛的功能。Seeed 发布了适用于 Wio Terminal 的库，使其能够通过 WiFi 通信。其他开发者也发布了与 MQTT 代理通信的库，您将使用这些库与设备进行交互。

这些库以源代码的形式提供，可以自动导入到 PlatformIO 中并为您的设备编译。通过这种方式，Arduino 库可以在支持 Arduino 框架的任何设备上运行，前提是设备具备该库所需的特定硬件。例如，Seeed WiFi 库是针对特定硬件的。

库可以全局安装并在需要时编译，也可以安装到特定项目中。在本次任务中，库将被安装到项目中。

✅ 您可以在 [PlatformIO 库文档](https://docs.platformio.org/en/latest/librarymanager/index.html) 中了解更多关于库管理以及如何查找和安装库的信息。

### 任务 - 安装 WiFi 和 MQTT Arduino 库

安装 Arduino 库。

1. 在 VS Code 中打开夜灯项目。

1. 在 `platformio.ini` 文件的末尾添加以下内容：

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    这将导入 Seeed WiFi 库。`@ <number>` 语法指的是库的特定版本号。

    > 💁 您可以删除 `@ <number>` 以始终使用库的最新版本，但无法保证后续版本能与以下代码正常工作。这里的代码已使用该版本的库进行了测试。

    这就是添加库所需的全部操作。下次 PlatformIO 构建项目时，它将下载这些库的源代码并将其编译到您的项目中。

1. 在 `lib_deps` 中添加以下内容：

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    这将导入 [PubSubClient](https://github.com/knolleary/pubsubclient)，一个 Arduino MQTT 客户端。

## 连接到 WiFi

现在可以将 Wio Terminal 连接到 WiFi。

### 任务 - 连接到 WiFi

将 Wio Terminal 连接到 WiFi。

1. 在 `src` 文件夹中创建一个名为 `config.h` 的新文件。您可以通过选择 `src` 文件夹或其中的 `main.cpp` 文件，然后从资源管理器中选择 **新建文件** 按钮来完成此操作。此按钮仅在光标悬停在资源管理器上时显示。

    ![新建文件按钮](../../../../../translated_images/vscode-new-file-button.182702340fe6723c.zh.png)

1. 在此文件中添加以下代码以定义 WiFi 凭据的常量：

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    将 `<SSID>` 替换为您的 WiFi SSID，将 `<PASSWORD>` 替换为您的 WiFi 密码。

1. 打开 `main.cpp` 文件。

1. 在文件顶部添加以下 `#include` 指令：

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    这将包含您之前添加的库的头文件以及配置头文件。这些头文件用于告诉 PlatformIO 引入库中的代码。如果未显式包含这些头文件，某些代码将不会被编译，您会遇到编译错误。

1. 在 `setup` 函数上方添加以下代码：

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    这段代码会在设备未连接到 WiFi 时循环，并尝试使用配置头文件中的 SSID 和密码进行连接。

1. 在 `setup` 函数底部、引脚配置完成后调用此函数。

    ```cpp
    connectWiFi();
    ```

1. 将此代码上传到您的设备以检查 WiFi 连接是否正常工作。您应该在串行监视器中看到以下内容：

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## 连接到 MQTT

一旦 Wio Terminal 连接到 WiFi，就可以连接到 MQTT 代理。

### 任务 - 连接到 MQTT

连接到 MQTT 代理。

1. 在 `config.h` 文件底部添加以下代码以定义 MQTT 代理的连接详细信息：

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    将 `<ID>` 替换为一个唯一的 ID，该 ID 将用作此设备客户端的名称，并在稍后用于设备发布和订阅的主题。*test.mosquitto.org* 代理是公共的，许多人都会使用，包括其他完成此任务的学生。拥有唯一的 MQTT 客户端名称和主题名称可以确保您的代码不会与其他人的代码冲突。稍后在创建服务器代码时，您也需要此 ID。

    > 💁 您可以使用类似 [GUIDGen](https://www.guidgen.com) 的网站生成一个唯一 ID。

    `BROKER` 是 MQTT 代理的 URL。

    `CLIENT_NAME` 是此 MQTT 客户端在代理上的唯一名称。

1. 打开 `main.cpp` 文件，在 `connectWiFi` 函数下方、`setup` 函数上方添加以下代码：

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    这段代码使用 Wio Terminal WiFi 库创建一个 WiFi 客户端，并使用它创建一个 MQTT 客户端。

1. 在此代码下方添加以下内容：

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    此函数测试与 MQTT 代理的连接，如果未连接则重新连接。它会在未连接时循环并尝试使用配置头文件中定义的唯一客户端名称进行连接。

    如果连接失败，它会在 5 秒后重试。

1. 在 `reconnectMQTTClient` 函数下方添加以下代码：

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    这段代码为客户端设置 MQTT 代理，并设置接收到消息时的回调函数。然后尝试连接到代理。

1. 在 WiFi 连接完成后，在 `setup` 函数中调用 `createMQTTClient` 函数。

1. 将整个 `loop` 函数替换为以下内容：

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    这段代码首先重新连接到 MQTT 代理。这些连接很容易中断，因此定期检查并在必要时重新连接是值得的。然后调用 MQTT 客户端的 `loop` 方法来处理订阅主题上收到的任何消息。此应用是单线程的，因此无法在后台线程接收消息，因此需要在主线程上分配时间来处理网络连接上等待的任何消息。

    最后，2 秒的延迟确保光线水平不会发送得太频繁，从而降低设备的功耗。

1. 将代码上传到您的 Wio Terminal，并使用串行监视器查看设备连接到 WiFi 和 MQTT。

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 您可以在 [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) 文件夹中找到此代码。

😀 您已成功将设备连接到 MQTT 代理。

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。因使用本翻译而引起的任何误解或误读，我们概不负责。