<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-25T00:04:25+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "zh"
}
-->
# 设置计时器 - 虚拟物联网硬件和树莓派

在本课的这一部分中，您将调用无服务器代码来理解语音，并根据结果在虚拟物联网设备或树莓派上设置计时器。

## 设置计时器

从语音转文本调用返回的文本需要发送到您的无服务器代码，由 LUIS 处理，并返回计时器的秒数。这个秒数可以用来设置计时器。

计时器可以使用 Python 的 `threading.Timer` 类来设置。这个类接受一个延迟时间和一个函数，在延迟时间后执行该函数。

### 任务 - 将文本发送到无服务器函数

1. 在 VS Code 中打开 `smart-timer` 项目，并确保如果您使用的是虚拟物联网设备，终端中已加载虚拟环境。

1. 在 `process_text` 函数上方，声明一个名为 `get_timer_time` 的函数，用于调用您创建的 REST 端点：

    ```python
    def get_timer_time(text):
    ```

1. 在该函数中添加以下代码以定义要调用的 URL：

    ```python
    url = '<URL>'
    ```

    将 `<URL>` 替换为您在上一课中构建的 REST 端点的 URL，无论是在您的计算机上还是在云端。

1. 添加以下代码，将文本设置为以 JSON 格式传递给调用的属性：

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. 在此代码下方，从响应负载中检索 `seconds`，如果调用失败则返回 0：

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    成功的 HTTP 调用会返回 200 范围内的状态码，如果文本被处理并识别为设置计时器意图，您的无服务器代码会返回 200。

### 任务 - 在后台线程上设置计时器

1. 在文件顶部添加以下导入语句以导入 Python 的 threading 库：

    ```python
    import threading
    ```

1. 在 `process_text` 函数上方，添加一个函数用于响应语音输出。现在这个函数只会写入控制台，但在本课稍后会用来输出语音：

    ```python
    def say(text):
        print(text)
    ```

1. 在此函数下方，添加一个函数，该函数将在计时器完成时被调用以宣布计时器已完成：

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    这个函数接收计时器的分钟数和秒数，并构建一条消息，说明计时器已完成。它会检查分钟数和秒数的值，仅在有值时才包含相应的时间单位。例如，如果分钟数为 0，则消息中只包含秒数。然后将这条消息发送到 `say` 函数。

1. 在此函数下方，添加以下 `create_timer` 函数以创建计时器：

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    这个函数接收命令中发送的计时器总秒数，并将其转换为分钟和秒数。然后，它使用总秒数创建并启动一个计时器对象，将 `announce_timer` 函数和包含分钟数和秒数的列表传递给计时器。当计时器到期时，它会调用 `announce_timer` 函数，并将该列表的内容作为参数传递——列表的第一个项目作为 `minutes` 参数，第二个项目作为 `seconds` 参数。

1. 在 `create_timer` 函数的末尾，添加一些代码，用于构建一条消息，告诉用户计时器正在启动：

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    同样，这条消息只包含有值的时间单位。然后将这条消息发送到 `say` 函数。

1. 在 `process_text` 函数的末尾添加以下内容，从文本中获取计时器的时间，然后创建计时器：

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    仅当秒数大于 0 时才会创建计时器。

1. 运行应用程序，并确保函数应用程序也在运行。设置一些计时器，输出将显示计时器的设置情况，并在计时器到期时显示相关信息：

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 您可以在 [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) 或 [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device) 文件夹中找到此代码。

😀 您的计时器程序成功了！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。我们对于因使用此翻译而引起的任何误解或误读不承担责任。