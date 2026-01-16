<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9095c61445c2bca7245ef9b59a186a11",
  "translation_date": "2025-08-25T00:55:20+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/README.md",
  "language_code": "zh"
}
-->
# 可视化位置数据

![本课的手绘笔记概览](../../../../../translated_images/zh/lesson-13.a259db1485021be7d7c72e90842fbe0ab977529e8684c179b5fb1ea75e92b3ef.jpg)

> 手绘笔记由 [Nitya Narasimhan](https://github.com/nitya) 提供。点击图片查看更大版本。

这段视频概述了 Azure Maps 与 IoT 的功能，这是本课将要讲解的服务。

[![Azure Maps - Microsoft Azure 企业级位置平台](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 点击上方图片观看视频

## 课前测验

[课前测验](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## 简介

在上一课中，你学习了如何从传感器获取 GPS 数据并使用无服务器代码将其保存到云端的存储容器中。现在，你将学习如何在 Azure 地图上可视化这些点。你将学习如何在网页上创建地图，了解 GeoJSON 数据格式，并使用它在地图上绘制所有捕获的 GPS 点。

本课内容包括：

* [什么是数据可视化](../../../../../3-transport/lessons/3-visualize-location-data)
* [地图服务](../../../../../3-transport/lessons/3-visualize-location-data)
* [创建 Azure Maps 资源](../../../../../3-transport/lessons/3-visualize-location-data)
* [在网页上显示地图](../../../../../3-transport/lessons/3-visualize-location-data)
* [GeoJSON 格式](../../../../../3-transport/lessons/3-visualize-location-data)
* [使用 GeoJSON 在地图上绘制 GPS 数据](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 本课将涉及少量 HTML 和 JavaScript。如果你想了解更多关于使用 HTML 和 JavaScript 进行网页开发的内容，请查看 [Web development for beginners](https://github.com/microsoft/Web-Dev-For-Beginners)。

## 什么是数据可视化

数据可视化，顾名思义，是通过视觉化的方式展示数据，使人类更容易理解。它通常与图表和图形相关，但实际上是任何以图像形式表示数据的方法，帮助人类更好地理解数据并做出决策。

举个简单的例子——在农场项目中，你捕获了土壤湿度数据。2021 年 6 月 1 日每小时捕获的土壤湿度数据表可能如下：

| 日期             | 读数   |
| ---------------- | ------: |
| 01/06/2021 00:00 |     257 |
| 01/06/2021 01:00 |     268 |
| 01/06/2021 02:00 |     295 |
| 01/06/2021 03:00 |     305 |
| 01/06/2021 04:00 |     325 |
| 01/06/2021 05:00 |     359 |
| 01/06/2021 06:00 |     398 |
| 01/06/2021 07:00 |     410 |
| 01/06/2021 08:00 |     429 |
| 01/06/2021 09:00 |     451 |
| 01/06/2021 10:00 |     460 |
| 01/06/2021 11:00 |     452 |
| 01/06/2021 12:00 |     420 |
| 01/06/2021 13:00 |     408 |
| 01/06/2021 14:00 |     431 |
| 01/06/2021 15:00 |     462 |
| 01/06/2021 16:00 |     432 |
| 01/06/2021 17:00 |     402 |
| 01/06/2021 18:00 |     387 |
| 01/06/2021 19:00 |     360 |
| 01/06/2021 20:00 |     358 |
| 01/06/2021 21:00 |     354 |
| 01/06/2021 22:00 |     356 |
| 01/06/2021 23:00 |     362 |

对于人类来说，理解这些数据可能很困难。这是一堆没有意义的数字。作为可视化这些数据的第一步，可以将其绘制成折线图：

![上述数据的折线图](../../../../../translated_images/zh/chart-soil-moisture.fd6d9d0cdc0b5f75e78038ecb8945dfc84b38851359de99d84b16e3336d6d7c2.png)

进一步优化，可以添加一条线，表示当土壤湿度读数达到 450 时自动浇水系统启动的时间点：

![带有 450 线的土壤湿度折线图](../../../../../translated_images/zh/chart-soil-moisture-relay.fbb391236d34a64d0abf1df396e9197e0a24df14150620b9cc820a64a55c9326.png)

这个图表可以快速显示土壤湿度水平以及浇水系统启动的时间点。

图表并不是唯一的可视化工具。追踪天气的 IoT 设备可以通过网页应用或移动应用使用符号来可视化天气状况，例如用云朵符号表示阴天，用雨云符号表示雨天等等。可视化数据的方法有很多种，有些严肃，有些有趣。

✅ 想一想你见过的数据可视化方式。哪些方式最清晰，能让你最快做出决策？

最好的可视化方式能让人类快速做出决策。例如，显示工业机器各种读数的仪表墙很难处理，但当某些东西出问题时，一个闪烁的红灯可以让人快速做出决策。有时候，最好的可视化方式就是一个闪烁的灯！

在处理 GPS 数据时，最清晰的可视化方式是将数据绘制在地图上。例如，显示送货卡车的地图可以帮助加工厂的工作人员了解卡车的到达时间。如果这张地图不仅显示卡车当前位置，还显示卡车的货物信息，那么加工厂的工作人员可以提前计划——如果他们看到一辆冷藏卡车接近，他们就知道需要准备冷藏空间。

## 地图服务

处理地图是一个有趣的练习，有许多地图服务可供选择，例如 Bing Maps、Leaflet、Open Street Maps 和 Google Maps。在本课中，你将学习 [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) 以及如何使用它来显示你的 GPS 数据。

![Azure Maps 标志](../../../../../translated_images/zh/azure-maps-logo.35d01dcfbd81fe6140e94257aaa1538f785a58c91576d14e0ebe7a2f6c694b99.png)

Azure Maps 是“一组地理空间服务和 SDK，使用最新的地图数据为网页和移动应用提供地理背景。”开发者可以使用这些工具创建美观、交互式的地图，这些地图可以提供推荐的交通路线、交通事故信息、室内导航、搜索功能、海拔信息、天气服务等。

✅ 试试一些 [地图代码示例](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)

你可以将地图显示为空白画布、瓦片、卫星图像、带有道路叠加的卫星图像、各种类型的灰度地图、带有阴影的地图以显示海拔、夜视地图以及高对比度地图。通过与 [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn) 集成，你可以在地图上获得实时更新。你可以通过启用各种控件来控制地图的行为和外观，使地图对事件如缩放、拖动和点击做出反应。为了控制地图的外观，你可以添加包括气泡、线条、多边形、热图等的图层。选择哪种地图样式取决于你选择的 SDK。

你可以通过以下方式访问 Azure Maps API：[REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest)、[Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn) 或者如果你正在构建移动应用，可以使用 [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android)。

在本课中，你将使用 Web SDK 绘制地图并显示传感器的 GPS 位置路径。

## 创建 Azure Maps 资源

第一步是创建一个 Azure Maps 账户。

### 任务 - 创建 Azure Maps 资源

1. 在终端或命令提示符中运行以下命令，在你的 `gps-sensor` 资源组中创建一个 Azure Maps 资源：

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    这将创建一个名为 `gps-sensor` 的 Azure Maps 资源。使用的层级是 `S1`，这是一个付费层级，包含一系列功能，但提供了大量免费的调用。

    > 💁 要查看使用 Azure Maps 的费用，请访问 [Azure Maps 定价页面](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn)。

1. 你需要一个地图资源的 API 密钥。使用以下命令获取该密钥：

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    复制 `PrimaryKey` 的值。

## 在网页上显示地图

接下来，你可以在网页上显示地图。我们将使用一个 `html` 文件来构建一个小型网页应用；请注意，在生产或团队环境中，你的网页应用可能会有更多的组件。

### 任务 - 在网页上显示地图

1. 在本地计算机的某个文件夹中创建一个名为 index.html 的文件。添加 HTML 标记以容纳地图：

    ```html
    <html>
    <head>
        <style>
            #myMap {
                width:100%;
                height:100%;
            }
        </style>
    </head>
    
    <body onload="init()">
        <div id="myMap"></div>
    </body>
    </html>
    ```

    地图将加载到 `myMap` 的 `div` 中。一些样式允许它占据页面的宽度和高度。

    > 🎓 `div` 是网页中的一个部分，可以命名和设置样式。

1. 在打开的 `<head>` 标签下，添加一个外部样式表来控制地图显示，以及一个来自 Web SDK 的外部脚本来管理地图行为：

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    这个样式表包含地图外观的设置，而脚本文件包含加载地图的代码。添加这些代码类似于包含 C++ 头文件或导入 Python 模块。

1. 在该脚本下方，添加一个脚本块以启动地图。

    ```javascript
    <script type='text/javascript'>
        function init() {
            var map = new atlas.Map('myMap', {
                center: [-122.26473, 47.73444],
                zoom: 12,
                authOptions: {
                    authType: "subscriptionKey",
                    subscriptionKey: "<subscription_key>",

                }
            });
        }
    </script>
    ```

    将 `<subscription_key>` 替换为你的 Azure Maps 账户的 API 密钥。

    如果你在浏览器中打开你的 `index.html` 页面，你应该会看到一个地图加载并聚焦在西雅图地区。

    ![显示西雅图的地图，西雅图是美国华盛顿州的一个城市](../../../../../translated_images/zh/map-image.8fb2c53eb23ef39c1c0a4410a5282e879b3b452b707eb066ff04c5488d3d72b7.png)

    ✅ 尝试调整缩放和中心参数以更改地图显示。你可以添加与你数据的纬度和经度对应的不同坐标来重新定位地图。

> 💁 在本地运行网页应用的更好方法是安装 [http-server](https://www.npmjs.com/package/http-server)。你需要先安装 [node.js](https://nodejs.org/) 和 [npm](https://www.npmjs.com/)。安装这些工具后，你可以导航到 `index.html` 文件所在的位置并输入 `http-server`。网页应用将会在本地服务器上打开 [http://127.0.0.1:8080/](http://127.0.0.1:8080/)。

## GeoJSON 格式

现在你已经设置了网页应用并显示了地图，接下来需要从存储账户中提取 GPS 数据，并在地图上添加标记层显示这些数据。在此之前，我们先来了解 Azure Maps 所需的 [GeoJSON](https://wikipedia.org/wiki/GeoJSON) 格式。

[GeoJSON](https://geojson.org/) 是一种开放标准的 JSON 规范，具有专门的格式设计，用于处理地理相关数据。你可以通过测试示例数据来了解它，例如使用 [geojson.io](https://geojson.io)，这也是一个调试 GeoJSON 文件的有用工具。

示例 GeoJSON 数据如下所示：

```json
{
  "type": "FeatureCollection",
  "features": [
    {
      "type": "Feature",
      "geometry": {
        "type": "Point",
        "coordinates": [
          -2.10237979888916,
          57.164918677004714
        ]
      }
    }
  ]
}
```

特别需要注意的是数据如何嵌套为 `Feature`，并包含在 `FeatureCollection` 中。在该对象中可以找到 `geometry`，其中 `coordinates` 指示纬度和经度。

✅ 在构建你的 GeoJSON 时，请注意对象中 `latitude` 和 `longitude` 的顺序，否则你的点可能不会出现在正确的位置！GeoJSON 期望点数据的顺序为 `lon,lat`，而不是 `lat,lon`。

`Geometry` 可以有不同的类型，例如单点或多边形。在这个例子中，它是一个点，指定了两个坐标：经度和纬度。
✅ Azure Maps 支持标准 GeoJSON，并提供一些[增强功能](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn)，包括绘制圆形和其他几何图形的能力。

## 使用 GeoJSON 在地图上绘制 GPS 数据

现在，您已经准备好使用上一课中构建的存储中的数据。提醒一下，这些数据存储为 Blob 存储中的多个文件，因此您需要检索这些文件并解析它们，以便 Azure Maps 可以使用这些数据。

### 任务 - 配置存储以便从网页访问

如果您调用存储以获取数据，可能会惊讶地发现浏览器控制台中出现错误。这是因为您需要为此存储设置 [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) 权限，以允许外部网页应用读取其数据。

> 🎓 CORS 代表“跨域资源共享”，通常需要在 Azure 中显式设置以确保安全性。它可以阻止您不期望的网站访问您的数据。

1. 运行以下命令以启用 CORS：

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    将 `<storage_name>` 替换为您的存储账户名称。将 `<key1>` 替换为您的存储账户的账户密钥。

    此命令允许任何网站（通配符 `*` 表示任何网站）向您的存储账户发出 *GET* 请求，即获取数据。`--services b` 表示仅对 Blob 应用此设置。

### 任务 - 从存储加载 GPS 数据

1. 将 `init` 函数的全部内容替换为以下代码：

    ```javascript
    fetch("https://<storage_name>.blob.core.windows.net/gps-data/?restype=container&comp=list")
        .then(response => response.text())
        .then(str => new window.DOMParser().parseFromString(str, "text/xml"))
        .then(xml => {
            let blobList = Array.from(xml.querySelectorAll("Url"));
                blobList.forEach(async blobUrl => {
                    loadJSON(blobUrl.innerHTML)                
        });
    })
    .then( response => {
        map = new atlas.Map('myMap', {
            center: [-122.26473, 47.73444],
            zoom: 14,
            authOptions: {
                authType: "subscriptionKey",
                subscriptionKey: "<subscription_key>",
    
            }
        });
        map.events.add('ready', function () {
            var source = new atlas.source.DataSource();
            map.sources.add(source);
            map.layers.add(new atlas.layer.BubbleLayer(source));
            source.add(features);
        })
    })
    ```

    将 `<storage_name>` 替换为您的存储账户名称。将 `<subscription_key>` 替换为您的 Azure Maps 账户的 API 密钥。

    这里发生了几件事。首先，代码通过使用您的存储账户名称构建的 URL 端点从 Blob 容器中获取您的 GPS 数据。此 URL 从 `gps-data` 中检索，表明资源类型是容器（`restype=container`），并列出所有 Blob 的信息。此列表不会返回 Blob 本身，但会返回每个 Blob 的 URL，可用于加载 Blob 数据。

    > 💁 您可以将此 URL 放入浏览器中查看容器中所有 Blob 的详细信息。每个项目都会有一个 `Url` 属性，您也可以在浏览器中加载以查看 Blob 的内容。

    然后，此代码加载每个 Blob，调用一个 `loadJSON` 函数（将在下一步中创建）。接着，它创建地图控件，并向 `ready` 事件添加代码。此事件在地图显示在网页上时被调用。

    `ready` 事件创建了一个 Azure Maps 数据源——一个包含 GeoJSON 数据的容器，稍后将填充此数据源。然后使用此数据源创建一个气泡图层——即地图上的一组圆形，中心点位于 GeoJSON 中的每个点。

1. 在 `init` 函数下方的脚本块中添加 `loadJSON` 函数：

    ```javascript
    var map, features;

    function loadJSON(file) {
        var xhr = new XMLHttpRequest();
        features = [];
        xhr.onreadystatechange = function () {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status === 200) {
                    gps = JSON.parse(xhr.responseText)
                    features.push(
                        new atlas.data.Feature(new atlas.data.Point([parseFloat(gps.gps.lon), parseFloat(gps.gps.lat)]))
                    )
                }
            }
        };
        xhr.open("GET", file, true);
        xhr.send();
    }    
    ```

    此函数由 fetch 例程调用，用于解析 JSON 数据并将其转换为经度和纬度坐标作为 GeoJSON 读取。
    解析完成后，数据被设置为 GeoJSON 的一个 `Feature`。地图将被初始化，并且小气泡会出现在数据路径周围：

1. 在浏览器中加载 HTML 页面。页面将加载地图，然后从存储中加载所有 GPS 数据并将其绘制在地图上。

    ![西雅图附近圣爱德华州立公园的地图，显示公园边缘路径上的圆形标记](../../../../../translated_images/zh/map-path.896832e72dc696ffe20650e4051027d4855442d955f93fdbb80bb417ca8a406f.png)

> 💁 您可以在 [code](../../../../../3-transport/lessons/3-visualize-location-data/code) 文件夹中找到此代码。

---

## 🚀 挑战

在地图上显示静态数据作为标记是很不错的。您能否增强此网页应用，添加动画并显示标记随时间变化的路径，使用带时间戳的 JSON 文件？以下是一些[使用地图动画的示例](https://azuremapscodesamples.azurewebsites.net/)。

## 课后测验

[课后测验](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## 复习与自学

Azure Maps 在处理 IoT 设备时特别有用。

* 在 [Microsoft Docs 上的 Azure Maps 文档](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn)中研究一些使用案例。
* 通过 [Microsoft Learn 上的 Azure Maps 自学模块](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn)加深您对地图制作和航点的了解。

## 作业

[部署您的应用](assignment.md)

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。对于因使用本翻译而引起的任何误解或误读，我们概不负责。