<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-24T21:01:35+00:00",
  "source_file": "hardware.md",
  "language_code": "zh"
}
-->
# 硬件

IoT中的**T**代表**Things**，指的是与周围环境交互的设备。每个项目都基于学生和爱好者可以获得的真实硬件。我们提供了两种IoT硬件选择，具体取决于个人偏好、编程语言知识或喜好、学习目标以及硬件的可用性。此外，对于那些无法获得硬件或希望在购买前了解更多信息的人，我们还提供了“虚拟硬件”版本。

> 💁 完成这些任务不需要购买任何IoT硬件。你可以使用虚拟IoT硬件完成所有内容。

物理硬件选择包括Arduino和Raspberry Pi。每个平台都有其优点和缺点，这些内容会在初始课程中详细介绍。如果你还没有决定使用哪种硬件平台，可以查看[第一个项目的第二课](./1-getting-started/lessons/2-deeper-dive/README.md)，以决定你最感兴趣学习的硬件平台。

我们选择了特定的硬件以减少课程和任务的复杂性。虽然其他硬件可能也能工作，但我们无法保证所有任务都能在你的设备上支持，除非额外添加硬件。例如，许多Arduino设备没有WiFi功能，而连接云端需要WiFi——我们选择了Wio Terminal，因为它内置了WiFi。

此外，你还需要一些非技术性的物品，比如土壤或盆栽植物，以及水果或蔬菜。

## 购买套件

![Seeed Studios的标志](../../translated_images/seeed-logo.74732b6b482b6e8e.zh.png)

Seeed Studios非常贴心地将所有硬件整理成易于购买的套件：

### Arduino - Wio Terminal

**[适用于初学者的IoT套件 - Seeed和Microsoft合作的Wio Terminal入门套件](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Wio Terminal硬件套件](../../translated_images/wio-hardware-kit.4c70c48b85e4283a.zh.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[适用于初学者的IoT套件 - Seeed和Microsoft合作的Raspberry Pi 4入门套件](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Raspberry Pi硬件套件](../../translated_images/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.zh.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

所有Arduino设备代码均使用C++编写。完成所有任务需要以下内容：

### Arduino硬件

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *可选* - USB-C线或USB-A转USB-C适配器。Wio Terminal有一个USB-C端口，并附带USB-C到USB-A线。如果你的PC或Mac只有USB-C端口，你需要一个USB-C线或USB-A转USB-C适配器。

### Arduino专用传感器和执行器

这些传感器和执行器专用于Wio Terminal Arduino设备，与Raspberry Pi无关。

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [面包板跳线](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* 耳机或其他带3.5mm插孔的扬声器，或JST扬声器，例如：
  * [单声道封闭式扬声器 - 2W 6欧姆](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* 16GB或以下的microSD卡，以及一个用于连接SD卡到电脑的适配器（如果电脑没有内置SD卡插槽）。**注意** - Wio Terminal仅支持容量不超过16GB的SD卡，不支持更高容量。

## Raspberry Pi

所有Raspberry Pi设备代码均使用Python编写。完成所有任务需要以下内容：

### Raspberry Pi硬件

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 从Pi 2B及以上版本都可以完成这些课程中的任务。如果你计划直接在Pi上运行VS Code，则需要Pi 4且至少2GB内存。如果你打算远程访问Pi，则任何Pi 2B及以上版本都可以使用。
* microSD卡（你可以购买带有microSD卡的Raspberry Pi套件），以及一个用于连接SD卡到电脑的适配器（如果电脑没有内置SD卡插槽）。
* USB电源（你可以购买带有电源的Raspberry Pi 4套件）。如果你使用的是Raspberry Pi 4，则需要USB-C电源，早期设备需要micro-USB电源。

### Raspberry Pi专用传感器和执行器

这些传感器和执行器专用于Raspberry Pi，与Arduino设备无关。

* [Grove Pi基座帽](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi摄像头模块](https://www.raspberrypi.org/products/camera-module-v2/)
* 麦克风和扬声器：

  使用以下任意一种（或等效设备）：
  * 任意USB麦克风和USB扬声器，或带3.5mm插孔的扬声器，或使用HDMI音频输出（如果你的Raspberry Pi连接到带扬声器的显示器或电视）
  * 带内置麦克风的任意USB耳机
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)以及
    * 耳机或其他带3.5mm插孔的扬声器，或JST扬声器，例如：
    * [单声道封闭式扬声器 - 2W 6欧姆](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB会议扬声器](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove光传感器](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove按钮](https://www.seeedstudio.com/Grove-Button.html)

## 传感器和执行器

大多数传感器和执行器适用于Arduino和Raspberry Pi学习路径：

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove湿度和温度传感器](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove电容式土壤湿度传感器](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove继电器](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove飞行时间距离传感器](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## 可选硬件

自动浇水课程使用继电器。作为选项，你可以将继电器连接到一个通过USB供电的水泵，使用以下硬件：

* [6V水泵](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB端子](https://www.adafruit.com/product/3628)
* 硅胶管
* 红色和黑色电线
* 小型平头螺丝刀

## 虚拟硬件

虚拟硬件路径将提供传感器和执行器的模拟器，使用Python实现。根据你的硬件可用性，你可以在普通开发设备（如Mac、PC）上运行，也可以在Raspberry Pi上运行并仅模拟你没有的硬件。例如，如果你有Raspberry Pi摄像头但没有Grove传感器，你可以在Pi上运行虚拟设备代码，模拟Grove传感器，同时使用物理摄像头。

虚拟硬件将使用[CounterFit项目](https://github.com/CounterFit-IoT/CounterFit)。

完成这些课程需要一个网络摄像头、麦克风和音频输出设备（如扬声器或耳机）。这些设备可以是内置的或外接的，并需要配置为与操作系统兼容，确保所有应用程序都可以使用。

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。因使用本翻译而导致的任何误解或误读，我们概不负责。