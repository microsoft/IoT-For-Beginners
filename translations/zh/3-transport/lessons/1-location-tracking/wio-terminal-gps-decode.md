<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-25T00:54:32+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "zh"
}
-->
# 解码 GPS 数据 - Wio Terminal

在本节课程中，您将解码从 Wio Terminal 的 GPS 传感器读取的 NMEA 消息，并提取纬度和经度。

## 解码 GPS 数据

一旦从串口读取到原始的 NMEA 数据，就可以使用开源的 NMEA 库对其进行解码。

### 任务 - 解码 GPS 数据

编程设备以解码 GPS 数据。

1. 如果尚未打开 `gps-sensor` 应用项目，请将其打开。

1. 在项目的 `platformio.ini` 文件中添加 [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) 库的依赖项。该库包含解码 NMEA 数据的代码。

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. 在 `main.cpp` 中，为 TinyGPSPlus 库添加一个 include 指令：

    ```cpp
    #include <TinyGPS++.h>
    ```

1. 在 `Serial3` 声明的下方，声明一个 TinyGPSPlus 对象，用于处理 NMEA 语句：

    ```cpp
    TinyGPSPlus gps;
    ```

1. 将 `printGPSData` 函数的内容更改为以下内容：

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    这段代码从 UART 串口读取下一个字符到 `gps` NMEA 解码器中。每读取一个字符后，它会检查解码器是否读取到有效的语句，然后检查是否读取到有效的位置。如果位置有效，它会将其发送到串口监视器，同时显示参与定位的卫星数量。

1. 构建并上传代码到 Wio Terminal。

1. 上传完成后，您可以使用串口监视器查看 GPS 位置信息。

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 您可以在 [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) 文件夹中找到这段代码。

😀 您的 GPS 传感器程序成功实现了数据解码！

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用此翻译而引起的任何误解或误读不承担责任。