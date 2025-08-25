<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-25T00:23:19+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "zh"
}
-->
# 语音转文字 - 虚拟物联网设备

在本节课程中，您将编写代码，将从麦克风捕获的语音通过语音服务转换为文字。

## 将语音转换为文字

在 Windows、Linux 和 macOS 上，可以使用语音服务的 Python SDK 监听您的麦克风，并将检测到的语音转换为文字。它会持续监听，检测音频水平，并在音频水平下降时（例如在一段语音结束时）将语音发送进行文字转换。

### 任务 - 将语音转换为文字

1. 在您的电脑上创建一个名为 `smart-timer` 的文件夹，并在其中创建一个名为 `app.py` 的单文件 Python 应用程序，同时创建一个 Python 虚拟环境。

1. 安装语音服务的 Pip 包。确保您是在激活了虚拟环境的终端中安装的。

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ 如果您遇到以下错误：
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > 您需要更新 Pip。使用以下命令更新，然后再次尝试安装该包：
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. 在 `app.py` 文件中添加以下导入：

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    这些导入了一些用于语音识别的类。

1. 添加以下代码以声明一些配置：

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    将 `<key>` 替换为您的语音服务的 API 密钥。将 `<location>` 替换为您创建语音服务资源时使用的位置。

    将 `<language>` 替换为您将使用的语言的区域名称，例如 `en-GB` 表示英语，或 `zn-HK` 表示粤语。您可以在 [Microsoft 文档上的语言和语音支持文档](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) 中找到支持的语言及其区域名称列表。

    这些配置将用于创建一个 `SpeechConfig` 对象，用于配置语音服务。

1. 添加以下代码以创建一个语音识别器：

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. 语音识别器在后台线程上运行，监听音频并将其中的语音转换为文字。您可以通过回调函数获取转换后的文字——定义一个函数并将其传递给识别器。每次检测到语音时，都会调用该回调函数。添加以下代码以定义一个回调函数，并将其传递给识别器，同时定义一个函数来处理文字并将其写入控制台：

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. 识别器只有在您显式启动时才会开始监听。添加以下代码以启动识别。这将在后台运行，因此您的应用程序还需要一个无限循环并进入休眠状态以保持应用程序运行。

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. 运行此应用程序。对着麦克风说话，转换后的文字将输出到控制台。

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    尝试不同类型的句子，以及一些发音相同但含义不同的句子。例如，如果您使用英语，可以说“我想买两个香蕉和一个苹果也”，注意它会根据单词的上下文正确使用 to、two 和 too，而不仅仅是根据发音。

> 💁 您可以在 [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) 文件夹中找到此代码。

😀 您的语音转文字程序成功了！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用本翻译而引起的任何误解或误读不承担责任。