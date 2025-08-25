<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-25T00:52:02+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "zh"
}
-->
# 解码GPS数据 - 虚拟物联网硬件和树莓派

在本节课程中，您将解码树莓派或虚拟物联网设备从GPS传感器读取的NMEA消息，并提取纬度和经度。

## 解码GPS数据

一旦从串口读取到原始NMEA数据，就可以使用开源NMEA库进行解码。

### 任务 - 解码GPS数据

编程设备以解码GPS数据。

1. 如果尚未打开，请打开 `gps-sensor` 应用项目

1. 安装 `pynmea2` Pip包。此包包含用于解码NMEA消息的代码。

    ```sh
    pip3 install pynmea2
    ```

1. 在 `app.py` 文件的导入部分添加以下代码以导入 `pynmea2` 模块：

    ```python
    import pynmea2
    ```

1. 用以下内容替换 `print_gps_data` 函数的内容：

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    此代码将使用 `pynmea2` 库解析从UART串口读取的行。

    如果消息的句子类型是 `GGA`，那么这是一条位置固定消息，并将被处理。纬度和经度值将从消息中读取，并从NMEA `(d)ddmm.mmmm` 格式转换为十进制度。`dm_to_sd` 函数完成此转换。

    然后检查纬度的方向，如果纬度是南方，则将其值转换为负数。同样地，如果经度是西方，则将其转换为负数。

    最后，坐标将打印到控制台，同时显示用于定位的卫星数量。

1. 运行代码。如果您使用的是虚拟物联网设备，请确保CounterFit应用正在运行并且GPS数据正在发送。

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 您可以在 [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) 文件夹或 [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi) 文件夹中找到此代码。

😀 您的GPS传感器程序成功解码数据！

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。因使用本翻译而引起的任何误解或误读，我们概不负责。