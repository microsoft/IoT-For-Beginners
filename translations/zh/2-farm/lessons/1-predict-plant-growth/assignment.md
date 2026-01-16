<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-24T22:02:56+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "zh"
}
-->
# 使用 Jupyter Notebook 可视化 GDD 数据

## 说明

在本课中，你使用 IoT 传感器收集了 GDD 数据。为了获得高质量的 GDD 数据，你需要收集多天的数据。为了帮助可视化温度数据并计算 GDD，你可以使用像 [Jupyter Notebooks](https://jupyter.org) 这样的工具来分析数据。

首先，收集几天的数据。你需要确保服务器代码在 IoT 设备运行时始终保持运行状态，可以通过调整电源管理设置或运行类似于 [这个保持系统活跃的 Python 脚本](https://github.com/jaqsparow/keep-system-active) 来实现。

一旦你有了温度数据，就可以使用此仓库中的 Jupyter Notebook 来可视化数据并计算 GDD。Jupyter Notebook 将代码和说明混合在称为 *单元格* 的块中，通常是 Python 代码。你可以阅读说明，然后逐块运行代码块。你还可以编辑代码。例如，在这个 Notebook 中，你可以编辑用于计算植物 GDD 的基准温度。

1. 创建一个名为 `gdd-calculation` 的文件夹

1. 下载 [gdd.ipynb](../../../../../2-farm/lessons/1-predict-plant-growth/code-notebook/gdd.ipynb) 文件并将其复制到 `gdd-calculation` 文件夹中。

1. 复制由 MQTT 服务器创建的 `temperature.csv` 文件

1. 在 `gdd-calculation` 文件夹中创建一个新的 Python 虚拟环境。

1. 安装一些用于 Jupyter Notebook 的 pip 包，以及管理和绘制数据所需的库：

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. 在 Jupyter 中运行 Notebook：

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter 将启动并在浏览器中打开 Notebook。按照 Notebook 中的说明操作，可视化测量的温度并计算生长度日（GDD）。

    ![Jupyter Notebook 示例](../../../../../translated_images/zh/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## 评分标准

| 标准 | 优秀 | 合格 | 需要改进 |
| ---- | ---- | ---- | -------- |
| 数据采集 | 至少采集 2 天完整数据 | 至少采集 1 天完整数据 | 采集了一些数据 |
| GDD 计算 | 成功运行 Notebook 并计算 GDD | 成功运行 Notebook | 无法运行 Notebook |

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用此翻译而引起的任何误解或误读不承担责任。