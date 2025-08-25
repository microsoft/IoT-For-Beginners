<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-25T00:08:41+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "zh"
}
-->
# 设置计时器 - Wio Terminal

在本课的这一部分中，您将调用无服务器代码来理解语音，并根据结果在 Wio Terminal 上设置计时器。

## 设置计时器

从语音转文本调用返回的文本需要发送到您的无服务器代码，由 LUIS 处理，返回计时器的秒数。这个秒数可以用来设置计时器。

微控制器在 Arduino 中本身不支持多线程，因此没有像在 Python 或其他高级语言中常见的标准计时器类。相反，您可以使用计时器库，这些库通过在 `loop` 函数中测量经过的时间并在时间结束时调用函数来工作。

### 任务 - 将文本发送到无服务器函数

1. 如果尚未打开，请在 VS Code 中打开 `smart-timer` 项目。

1. 打开 `config.h` 头文件，并添加您的函数应用的 URL：

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    将 `<URL>` 替换为您在上一课最后一步中获得的函数应用的 URL，指向运行函数应用的本地机器的 IP 地址。

1. 在 `src` 文件夹中创建一个名为 `language_understanding.h` 的新文件。此文件将用于定义一个类，将识别的语音发送到您的函数应用，并使用 LUIS 转换为秒数。

1. 在文件顶部添加以下内容：

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    这包括一些必要的头文件。

1. 定义一个名为 `LanguageUnderstanding` 的类，并声明该类的一个实例：

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. 要调用您的函数应用，您需要声明一个 WiFi 客户端。在类的 `private` 部分添加以下内容：

    ```cpp
    WiFiClient _client;
    ```

1. 在 `public` 部分，声明一个名为 `GetTimerDuration` 的方法，用于调用函数应用：

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. 在 `GetTimerDuration` 方法中，添加以下代码以构建要发送到函数应用的 JSON：

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    这会将传递给 `GetTimerDuration` 方法的文本转换为以下 JSON：

    ```json
    {
        "text" : "<text>"
    }
    ```

    其中 `<text>` 是传递给函数的文本。

1. 在此代码下方，添加以下代码以调用函数应用：

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    这会向函数应用发送一个 POST 请求，传递 JSON 正文并获取响应代码。

1. 在此代码下方添加以下内容：

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    此代码检查响应代码。如果是 200（成功），则从响应正文中检索计时器的秒数。否则，将错误发送到串行监视器，并将秒数设置为 0。

1. 在此方法的末尾添加以下代码以关闭 HTTP 连接并返回秒数：

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. 在 `main.cpp` 文件中，包含这个新的头文件：

    ```cpp
    #include "speech_to_text.h"
    ```

1. 在 `processAudio` 函数的末尾，调用 `GetTimerDuration` 方法以获取计时器时长：

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    这会将从 `SpeechToText` 类调用返回的文本转换为计时器的秒数。

### 任务 - 设置计时器

秒数可以用来设置计时器。

1. 在 `platformio.ini` 文件中添加以下库依赖项，以添加一个设置计时器的库：

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. 在 `main.cpp` 文件中添加该库的 include 指令：

    ```cpp
    #include <arduino-timer.h>
    ```

1. 在 `processAudio` 函数上方，添加以下代码：

    ```cpp
    auto timer = timer_create_default();
    ```

    此代码声明一个名为 `timer` 的计时器。

1. 在此代码下方，添加以下内容：

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    此 `say` 函数最终会将文本转换为语音，但目前它只会将传入的文本写入串行监视器。

1. 在 `say` 函数下方，添加以下代码：

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    这是一个回调函数，当计时器到期时会被调用。它会传递一个消息，当计时器到期时说出该消息。计时器可以重复运行，这可以通过回调的返回值来控制——此处返回 `false`，表示计时器不再运行。

1. 在 `processAudio` 函数的末尾添加以下代码：

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    此代码检查总秒数，如果为 0，则从函数调用中返回，以便不设置计时器。然后将总秒数转换为分钟和秒。

1. 在此代码下方，添加以下内容以创建一个计时器启动时的消息：

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. 在此代码下方，添加类似的代码以创建一个计时器到期时的消息：

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. 在此之后，说出计时器启动的消息：

    ```cpp
    say(begin_message);
    ```

1. 在此函数的末尾，启动计时器：

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    这会触发计时器。计时器是以毫秒为单位设置的，因此总秒数乘以 1,000 转换为毫秒。`timerExpired` 函数作为回调传递，`end_message` 作为参数传递给回调。此回调仅接受 `void *` 参数，因此字符串被适当地转换。

1. 最后，计时器需要 *tick*，这在 `loop` 函数中完成。在 `loop` 函数的末尾添加以下代码：

    ```cpp
    timer.tick();
    ```

1. 构建此代码，将其上传到您的 Wio Terminal，并通过串行监视器进行测试。当您在串行监视器中看到 `Ready` 时，按下 C 按钮（左侧靠近电源开关的按钮），然后说话。将捕获 4 秒的音频，转换为文本，然后发送到您的函数应用，并设置一个计时器。确保您的函数应用在本地运行。

    您将看到计时器启动和结束的时间。

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 您可以在 [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) 文件夹中找到此代码。

😀 您的计时器程序成功了！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。因使用本翻译而导致的任何误解或误读，我们概不负责。