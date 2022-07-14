# 应用物联网预测植物生长

![这个课程概述的涂鸦笔记（sketchnote）](../../../../sketchnotes/lesson-5.jpg)

> Sketchnote by [Nitya Narasimhan](https://github.com/nitya). 如果你想看比较大的图片，请点击它。

## 课前测验

[课前测验](https://thankful-pond-0eba8f10f.1.azurestaticapps.net/quiz/9)

## 介绍

植物需要一些东西才能生长 - 水，二氧化碳，养分，光照，还有热。在这节课程中，你将会学习怎样通过测量空气温度来计算植物的生长和成熟率。

这节课程将包含：

* [数字农业](#数字农业)
* [为什么温度在耕作中很重要？](#为什么温度在耕作中很重要？)
* [测量环境温度](#测量环境温度)
* [生长度日 (GDD)](#生长度日)
* [用温度传感器数据计算 GDD](#用温度传感器数据计算 GDD)

## 数字农业

通过使用工具来收集、存储和分析耕作数据，数字农业 (Digital Agriculture) 正在改变我们的耕作方式。我们目前正处于被世界经济论坛描述为“第四次工业革命”的时期，而数字农业的崛起也被称为“第四次农业革命”，或“农业4.0”。

> 🎓 数字农业一词也包括整个“农业价值链”，即从农场到餐桌的整个过程。它包括在食品运输和加工过程中跟踪农产品质量，仓库和电子商务系统，甚至拖拉机租赁应用程序！

这些改变使得农民们能够提高产量，减少肥料和农药的使用，并更有效率地浇水。尽管主要在富裕国家中使用，传感器和其它设备的价格在慢慢降低，使得它们在发展中国家也更容易被使用了。

数字农业所促成的技术包括：

* 温度测量——测量温度使农民能够预测植物的生长和成熟度。
* 自动浇水——测量土壤湿度，在土壤过于干燥时开启灌溉系统，而不是定时浇水。定时浇水可能导致作物在高温干旱时浇水不足，或在下雨时浇水过多。通过只有在土壤需要时才浇水的方式，农民可以优化水资源的使用。
* 虫害控制——农民可以使用自动机器人或无人机上的摄像头来检查虫害，然后只在需要的地方施用农药。这样不仅能减少农药的使用量，也能减少流入当地水源中的农药量。

✅ 做些研究。还有哪些技术是用来提高农业产量的？

> 🎓 “精准农业”一词被用来定义在某块田地，甚至在某块田地的部分区域的尺度上，对作物进行的观察、测量和反应。这包括测量水、养分和虫害程度，并作出准确的反应，例如只对一小部分田地进行浇灌。
>

## 为什么温度在耕作中很重要？

在学习植物时，大多数学生都了解了水、光、二氧化碳 (CO<sub>2</sub>) 和养分的必要性。其实植物的生长也需要温暖——这就是为什么植物在春天随着温度的升高而开花，为什么雪钟花或水仙花会因为短暂的暖流而提前发芽，以及为什么暖房和温室能里的植物生长得很好。

> 🎓 暖房和温室挺类似的，但它们有一个重要区别。暖房是人工加热的，农民能够更准确地控制温度，而温室依靠太阳取暖，通常唯一的控制是利用窗户或其他开口来让热量散发出去。

植物有基础温度或者说最低温度、最佳温度和最高温度，所有这些都基于日平均温度。

* 基础温度 (Base temperature) - 这是植物生长所需的最低日平均温度。
* 最佳温度 (Optimum temperature) - 这是能够使植物获得最多生长的最佳日平均温度。
* 最高温度 (Maximum temperature) - 这是植物可以承受的最高温度。超过这个温度，植物就会停止生长，以节省水分和保持存活。

> 💁 这些都是平均温度，是每日和每夜温度的平均值。植物也需要昼夜不同的温度以帮助它们更有效地进行光合作用并在夜间节省能量。

每种植物都有不同的基础、最佳、最高温度值。这就是为什么一些植物能够在炎热的地区茁壮成长，而另一些则更适应寒冷地区。

✅ 做些研究。对于那些花园、学校或当地公园里的植物，你是否可以找到其基础温度。

![本图展示了生长率随着温度的升高而增长，然后在温度过高时下跌的过程](../../../../images/plant-growth-temp-graph.png)

上图显示了一个生长率与温度关系图的例子。在最低温度之前植物不会生长。随着温度升高生长率增加，并在最佳温度处达到这个峰值，然后下降。在最高温度处，生长停止。

该图的形状因植物种类的不同而不同。有些植物在最佳温度之后有较明显的下降，有些植物从最低温度到最佳温度的增长更加缓慢。

> 💁 对于农民来说，要想让作物长得更好，他们需要知道这三个温度值，并了解他们所种植的作物的图形形状。

如果农民能够控制温度，比如在商业暖房中，那么他们可以为其作物进行温度的优化。例如，一个种植西红柿的商业暖房可以在白天将温度设置为25°C而在晚上设置为20°C，这样能够获得最快的生长。

> 🍅 将温控与人工照明、肥料和 CO<sub>2</sub> 水平控制相结合能够能够实现全年的种植和收获。

## 测量环境温度

温度传感器可与物联网设备一起使用来测量环境温度。

### 任务 - 测量温度

通过以下这些相关指南，应用你的物联网设备监测温度：

* [Arduino - Wio Terminal](../wio-terminal-temp.md)
* [单板机 - Raspberry Pi](../pi-temp.md)
* [单板机 - 虚拟设备](../virtual-device-temp.md)

## 生长度日

生长度日 (Growing degree days)，也称为生长度单位 (growing degree units)，是根据温度衡量植物生长的一种方式。假设一株植物具有足够的水分、养分和二氧化碳，温度将会决定植物的生长率。

生长度日，或称 GDD，是以每日中高于植物基础温度的的平均温度（摄氏度）来计算的。每个植物需要一定数量的生长度日来生长、开花、成熟。每天的 GDD 越多，植物的生长就越快。

> 🇺🇸 For Americans, growing degree days can also be calculated using Fahrenheit. 5 GDD<sup>C</sup> (growing degree days in Celsius) is the equivalent of 9 GDD<sup>F</sup> (growing degree days in Fahrenheit).	<= 华氏度计算

GDD 的完整公式有点复杂，大多是情况下使用一个简化方程就能得到一个很好的近似值：

![GDD = T max + T min 除以 2，再减去 T base](../../../../images/gdd-calculation.png)

* **GDD** - 生长度日的数量
* **T<sub>max</sub>** - 每日最高温度，单位是摄氏度
* **T<sub>min</sub>** - 每日最低温度，单位是摄氏度
* **T<sub>base</sub>** - 植物的基础温度，单位是摄氏度。

> 💁 T<sub>max</sub> 高于 30°C 或者 T<sub>min</sub> 低于 T<sub>base</sub> 的情况下有所不同，但是我们暂且忽略。

### 例子 - 玉米 🌽

根据品种的不同，玉米大概需要 800 到 2,700 的 GDD 来成熟，基础温度是 10°C。

在高于基础温度的第一天，测量的温度值如下：

| 测量 | 温度 °C |
| :--- | :-----: |
| 最高 |   16    |
| 最低 |   12    |

把这些数字代入公式中：

* T<sub>max</sub> = 16
* T<sub>min</sub> = 12
* T<sub>base</sub> = 10

可得：

![GDD = 16 + 12 除以 2，再减去 10，得到答案为 4](../../../../images/gdd-calculation-corn.png)

玉米在这一天获得了4 GDD。假设这个品种的玉米需要800 GDD，那么它还需要796 GDD 才能成熟。

✅ 做些研究。对于那些花园、学校或当地公园里的植物，你是否能找它们成熟所需的 GDD 数量。

## 用温度传感器数据计算 GDD

植物的生长时间不是固定的——例如，你不可能种下一粒种子并知道它会刚好在100天后开花结果。然而，作为一个农民，你也许有一个生长所需时间的粗略概念，然后你每天检查作物是否成熟。

对于一些大型农场来说这是一个巨大的劳动力影响，而且农民有可能错过意外提前成熟的作物。通过测量温度，农民可以计算出植物所累积的 GDD，这样可以就能只在接近预期成熟度时进行检查。

通过使用物联网设备收集温度数据，农民可以在植物接近成熟时自动收到通知。这方面的典型架构是让物联网设备测量温度，然后使用类似 MQTT 的协议在互联网上发布这些遥测数据。接着服务器代码监听这些数据并将其保存在某个地方，比如数据库。这意味着之后能够对这些数据进行分析，比如在每晚计算当天的 GDD，对每种作物的 GDD 进行累计，如果植物接近成熟就发出警报。

![遥测数据被发送到一个服务器上然后被保存至数据库中](../../../../images/save-telemetry-database.png)

服务器代码也可以通过添加额外的信息来增强数据。例如，物联网设备可通过一个标识符以表明它是哪个设备，而服务器代码可以使用这个标识符来查找设备的位置以及它正在监测哪些作物。还可以添加一些基本数据，如当前时间，因为一些物联网设备没有追踪时间的必要的硬件或者是需要额外的代码来通过互联网读取当前时间。

✅ 你觉得为什么不同地方的温度可能会不同？

### 任务 - 发布温度信息

通过以下这些相关指南，应用你的物联网设备通过 MQTT 发布温度数据，以便之后的分析：

* [Arduino - Wio Terminal](../wio-terminal-temp-publish.md)
* [单板机 - Raspberry Pi/虚拟物联网设备](../single-board-computer-temp-publish.md)

### 任务 - 捕获并存储温度信息

如果物联网设备成功发布遥测数据，就可以开始编写服务器代码来订阅这些数据并将其存储起来。服务器代码将其保存到 CSV 文件中而非使用数据库来存储。CSV文件以文本形式存储数据，每个值用逗号隔开，每个记录占一行。它是一种方便的、人类可读的、受到良好支持的保存数据为文件的方式。

CSV 文件将有两列 - *时间 (date)*和*温度 (temperature)*。*时间*列将存储服务器收到消息时的日期和时间，*温度*列存储遥测信息。

1. 重复第4课的步骤，创建服务器代码以订阅遥测数据。你不需要添加代码来发布命令。

   具体步骤：

   * 配置并激活一个 Python 虚拟环境

   * 安装 paho-mqtt pip 包

   * 编写代码来监听发布在遥测主题上的 MQTT 消息

     > ⚠️ 如果需要的话你可以参考 [课程 4 中关于创建 Python 应用来接受遥测数据的说明](../../../../1-getting-started/lessons/4-connect-internet/README.md#receive-telemetry-from-the-mqtt-broker)。

   这个项目的文件夹名是 `temperature-sensor-server`。

1. 确保 `client_name` 反映该项目：

   ```cpp
   client_name = id + 'temperature_sensor_server'
   ```

1. 在文件开头，已有导入的下方，添加下列导入：

   ```python
   from os import path
   import csv
   from datetime import datetime
   ```

   这将会导入一个用于读取文件的库，一个与 CSV 文件交互的库，和一个关于日期和时间的库。

1. 添加下面的代码至 `handle_telemetry` 函数前：

   ```python
   temperature_file_name = 'temperature.csv'
   fieldnames = ['date', 'temperature']
   
   if not path.exists(temperature_file_name):
       with open(temperature_file_name, mode='w') as csv_file:
           writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
           writer.writeheader()
   ```

   这段代码声明了一些用于写入文件的文件名和 CSV 文件列标题名的常量。传统上，CSV 文件的第一行包含由逗号分隔的列标题。

   然后代码会检查 CSV 文件是否已经存在。如果不存在，则在第一行创建列标题。

1. 添加下面的代码至 `handle_telemetry` 函数末尾：

   ```python
   with open(temperature_file_name, mode='a') as temperature_file:        
       temperature_writer = csv.DictWriter(temperature_file, fieldnames=fieldnames)
       temperature_writer.writerow({'date' : datetime.now().astimezone().replace(microsecond=0).isoformat(), 'temperature' : payload['temperature']})
   ```

   这段代码会打开 CSV 文件，然后在末尾添加一个新行。这一行会包含当前的日期和时间（可阅读格式），紧跟着从物联网设备中接收到的温度。时间数据将以 [ISO 8601 format](https://wikipedia.org/wiki/ISO_8601) 进行保存，包含时区，但是不包含毫秒。

1. 以与之前相同的方式运行此代码，确保你的物联网设备正在发送数据。一个名为 `temperature.csv` 的 CSV 文件将在同一文件夹中创建。如果你查看它，你应该能看到日期/时间和温度数据：

   ```output
   date,temperature
   2021-04-19T17:21:36-07:00,25
   2021-04-19T17:31:36-07:00,24
   2021-04-19T17:41:36-07:00,25
   ```

1. 运行这段代码一段时间以获取数据。理想情况下，你应该运行它一整天来收集足够的数据用于 GDD 的计算。

   > 💁 如果你正在使用虚拟物联网设备，选择随机复选框并设置一个范围来避免每次返回温度时都得到同样的值。
   > ![Select the random checkbox and set a range](../../../../images/select-the-random-checkbox-and-set-a-range.png) 

   > 💁 如果你想运行一整天，那么你需要确保用于服务器代码运行的电脑不会进入休眠，你可以改变电源设置，或者运行 [这个保持系统活跃的 Python 脚本](https://github.com/jaqsparow/keep-system-active)。

> 💁 你可以在 [code-server/temperature-sensor-server](../code-server/temperature-sensor-server) 文件夹内找到需要的代码。

### 任务 - 使用存储的数据计算出 GDD

一旦服务器采集了温度数据，就可以计算出植物的 GDD。

手动操作的步骤是：

1. 找到该植物的基础温度。例如，对于草莓来说，基础温度是10℃

1. 根据 `temperature.csv`，找到一天中的最低温度和最高温度

1. 使用之前给出的公式来计算 GDD

例如，如果这一天最高温度是 25°C，最低温度是 12°C：

![GDD = 25 + 12 除以 2，然后减去 10 得到 8.5](../../../../images/gdd-calculation-strawberries.png)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

所以草莓获得了 **8.5** GDD。草莓需要大概 250 GDD 来结果，看来还得等一会儿呢。

---

## 🚀 挑战

植物的生长，除了热量以外，还需要些什么？

对于这些（其它因素），寻找是否有可以测量它们的传感器。那么控制它们水平的执行器呢？你会如何把一个或多个物联网设备放在一起，以优化植物的生长？

## 课后测验

[课后测验](https://thankful-pond-0eba8f10f.1.azurestaticapps.net/quiz/10)

## 复习 & 自学

* 在 [Digital Agriculture Wikipedia page](https://wikipedia.org/wiki/Digital_agriculture) 上阅读更多关于数字农业的知识。在 [Precision Agriculture Wikipedia page](https://wikipedia.org/wiki/Precision_agriculture) 上阅读更多关于精准农业的知识。
* 完整的生长度日计算比这里给出的简化计算更复杂。在 [Growing Degree Day Wikipedia page](https://wikipedia.org/wiki/Growing_degree-day) 上查看更复杂的方程以及处理低温条件的方法。
* 即使我们仍然使用相同的耕作方法，未来的食物也可能是稀缺的。在 [Hi-Tech Farms of Future video on YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8) 上了解更多高科技种植手段。

## 作业

[使用 Jupyter Notebook 进行 GDD 数据的可视化](../assignment.md)