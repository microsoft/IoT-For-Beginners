<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-24T22:49:39+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "zh"
}
-->
# 将您的 IoT 设备连接到云端 - Wio Terminal

在本课程的这一部分，您将把 Wio Terminal 连接到 IoT Hub，以发送遥测数据并接收命令。

## 将设备连接到 IoT Hub

下一步是将您的设备连接到 IoT Hub。

### 任务 - 连接到 IoT Hub

1. 在 VS Code 中打开 `soil-moisture-sensor` 项目。

1. 打开 `platformio.ini` 文件。移除 `knolleary/PubSubClient` 库依赖项。该库用于连接到公共 MQTT 代理，但连接到 IoT Hub时不需要。

1. 添加以下库依赖项：

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    `Seeed Arduino RTC` 库提供与 Wio Terminal 的实时时钟交互的代码，用于跟踪时间。其余库允许您的 IoT 设备连接到 IoT Hub。

1. 在 `platformio.ini` 文件底部添加以下内容：

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    这设置了一个编译器标志，在编译 Arduino IoT Hub 代码时需要。

1. 打开 `config.h` 头文件。移除所有 MQTT 设置，并添加以下设备连接字符串常量：

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    将 `<connection string>` 替换为您之前复制的设备连接字符串。

1. 连接到 IoT Hub 使用基于时间的令牌。这意味着 IoT 设备需要知道当前时间。与 Windows、macOS 或 Linux 等操作系统不同，微控制器不会自动通过互联网同步当前时间。这意味着您需要添加代码从 [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) 服务器获取当前时间。一旦时间被检索，可以将其存储在 Wio Terminal 的实时时钟中，允许在设备未断电的情况下稍后请求正确时间。添加一个名为 `ntp.h` 的新文件，并包含以下代码：

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    这些代码的细节超出了本课程的范围。它定义了一个名为 `initTime` 的函数，该函数从 NTP 服务器获取当前时间并用它设置 Wio Terminal 的时钟。

1. 打开 `main.cpp` 文件，移除所有 MQTT 代码，包括 `PubSubClient.h` 头文件、`PubSubClient` 变量的声明、`reconnectMQTTClient` 和 `createMQTTClient` 方法，以及对这些变量和方法的任何调用。该文件应仅包含连接到 WiFi、获取土壤湿度并创建 JSON 文档的代码。

1. 在 `main.cpp` 文件顶部添加以下 `#include` 指令，以包含 IoT Hub 库和设置时间的头文件：

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. 在 `setup` 函数末尾添加以下调用以设置当前时间：

    ```cpp
    initTime();
    ```

1. 在文件顶部的 `#include` 指令下方添加以下变量声明：

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    这声明了一个 `IOTHUB_DEVICE_CLIENT_LL_HANDLE`，用于连接到 IoT Hub 的句柄。

1. 在此下方添加以下代码：

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    这声明了一个回调函数，当连接到 IoT Hub 的状态发生变化（例如连接或断开连接）时会被调用。状态会发送到串口。

1. 在此下方添加一个函数以连接到 IoT Hub：

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    此代码初始化 IoT Hub 库代码，然后使用 `config.h` 头文件中的连接字符串创建连接。此连接基于 MQTT。如果连接失败，错误信息会发送到串口——如果您在输出中看到此信息，请检查连接字符串。最后设置连接状态回调。

1. 在 `setup` 函数中调用此函数，位置在 `initTime` 调用下方：

    ```cpp
    connectIoTHub();
    ```

1. 与 MQTT 客户端类似，此代码运行在单线程上，因此需要时间处理由 Hub 发送和发送到 Hub 的消息。在 `loop` 函数顶部添加以下内容以实现此功能：

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. 构建并上传此代码。您将在串口监视器中看到连接：

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    在输出中，您可以看到 NTP 时间被获取，然后设备客户端连接。连接可能需要几秒钟，因此在设备连接时，您可能会在输出中看到土壤湿度。

    > 💁 您可以使用像 [unixtimestamp.com](https://www.unixtimestamp.com) 这样的网站将 NTP 的 UNIX 时间转换为更易读的格式。

## 发送遥测数据

现在您的设备已连接，您可以将遥测数据发送到 IoT Hub，而不是 MQTT 代理。

### 任务 - 发送遥测数据

1. 在 `setup` 函数上方添加以下函数：

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    此代码从传递的字符串参数创建一个 IoT Hub 消息，将其发送到 Hub，然后清理消息对象。

1. 在 `loop` 函数中调用此代码，位置在将遥测数据发送到串口的行之后：

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## 处理命令

您的设备需要处理来自服务器代码的命令以控制继电器。这是通过直接方法请求发送的。

## 任务 - 处理直接方法请求

1. 在 `connectIoTHub` 函数之前添加以下代码：

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    此代码定义了一个回调方法，当 IoT Hub 库收到直接方法请求时会调用该方法。请求的方法通过 `method_name` 参数传递。此函数将调用的方法打印到串口，然后根据方法名称打开或关闭继电器。

    > 💁 这也可以通过单个直接方法请求实现，将继电器的期望状态作为有效负载传递，该有效负载可以通过方法请求传递并从 `payload` 参数中获取。

1. 在 `directMethodCallback` 函数末尾添加以下代码：

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    直接方法请求需要响应，响应分为两部分——文本响应和返回码。此代码将创建以下 JSON 文档作为结果：

    ```JSON
    {
        "Result": ""
    }
    ```

    然后将其复制到 `response` 参数中，并在 `response_size` 参数中设置响应的大小。此代码随后返回 `IOTHUB_CLIENT_OK`，表示方法已正确处理。

1. 在 `connectIoTHub` 函数末尾添加以下代码以连接回调：

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. `loop` 函数将调用 `IoTHubDeviceClient_LL_DoWork` 函数以处理 IoT Hub 发送的事件。由于 `delay` 的原因，这仅每 10 秒调用一次，这意味着直接方法每 10 秒才会处理一次。为了提高效率，可以将 10 秒的延迟分成多个较短的延迟，每次调用 `IoTHubDeviceClient_LL_DoWork`。为此，在 `loop` 函数上方添加以下代码：

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    此代码将重复循环，调用 `IoTHubDeviceClient_LL_DoWork` 并每次延迟 100 毫秒。它会根据 `delay_time` 参数的值重复多次。这意味着设备最多等待 100 毫秒来处理直接方法请求。

1. 在 `loop` 函数中，移除对 `IoTHubDeviceClient_LL_DoWork` 的调用，并将 `delay(10000)` 替换为以下代码以调用新函数：

    ```cpp
    work_delay(10000);
    ```

> 💁 您可以在 [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) 文件夹中找到此代码。

😀 您的土壤湿度传感器程序已连接到 IoT Hub！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。原始语言的文档应被视为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用此翻译而产生的任何误解或误读不承担责任。