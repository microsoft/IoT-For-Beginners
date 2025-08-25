<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-25T00:11:49+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "zh"
}
-->
# 文本转语音 - Wio Terminal

在本课的这一部分，你将把文本转换为语音，以提供语音反馈。

## 文本转语音

在上一课中你使用的语音服务 SDK 将语音转换为文本，现在可以用来将文本转换回语音。

## 获取语音列表

在请求语音时，你需要提供使用的语音，因为语音可以通过多种不同的声音生成。每种语言支持一系列不同的语音，你可以通过语音服务 SDK 获取每种语言支持的语音列表。然而，这里会受到微控制器的限制——获取文本转语音服务支持的语音列表的调用会返回一个大小超过 77KB 的 JSON 文档，这远远超出了 Wio Terminal 的处理能力。截至撰写本文时，完整的语音列表包含 215 种语音，每种语音由如下所示的 JSON 文档定义：

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

这是 **Aria** 语音的 JSON，它有多种语音风格。在将文本转换为语音时，只需要短名称 `en-US-AriaNeural`。

与其在微控制器上下载和解码整个列表，不如编写一些无服务器代码来获取你所使用语言的语音列表，并从 Wio Terminal 调用它。你的代码可以从列表中选择一个合适的语音，例如找到的第一个语音。

### 任务 - 创建一个无服务器函数以获取语音列表

1. 在 VS Code 中打开你的 `smart-timer-trigger` 项目，并确保虚拟环境已激活。如果没有，请终止并重新创建终端。

1. 打开 `local.settings.json` 文件，并为语音 API 密钥和位置添加设置：

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    将 `<key>` 替换为你的语音服务资源的 API 密钥。将 `<location>` 替换为你创建语音服务资源时使用的位置。

1. 使用以下命令在 VS Code 终端中函数应用项目的根文件夹内添加一个名为 `get-voices` 的 HTTP 触发器：

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    这将创建一个名为 `get-voices` 的 HTTP 触发器。

1. 将 `get-voices` 文件夹中的 `__init__.py` 文件内容替换为以下内容：

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    这段代码向端点发出 HTTP 请求以获取语音列表。语音列表是一个包含所有语言语音的大型 JSON 块，因此会过滤出请求体中指定语言的语音，然后提取并返回短名称作为 JSON 列表。短名称是将文本转换为语音所需的值，因此只返回该值。

    > 💁 你可以根据需要更改过滤器以选择你想要的语音。

    这将数据大小从 77KB（撰写本文时）减少到一个更小的 JSON 文档。例如，对于美国语音，这个文档大小为 408 字节。

1. 在本地运行你的函数应用。然后可以使用类似 curl 的工具调用它，就像测试 `text-to-timer` HTTP 触发器一样。确保以 JSON 格式传递语言：

    ```json
    {
        "language":"<language>"
    }
    ```

    将 `<language>` 替换为你的语言，例如 `en-GB` 或 `zh-CN`。

> 💁 你可以在 [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) 文件夹中找到这段代码。

### 任务 - 从 Wio Terminal 获取语音

1. 如果尚未打开，请在 VS Code 中打开 `smart-timer` 项目。

1. 打开 `config.h` 头文件，并添加你的函数应用的 URL：

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    将 `<URL>` 替换为你的函数应用中 `get-voices` HTTP 触发器的 URL。这将与 `TEXT_TO_TIMER_FUNCTION_URL` 的值相同，只是函数名称从 `text-to-timer` 改为 `get-voices`。

1. 在 `src` 文件夹中创建一个名为 `text_to_speech.h` 的新文件。这将用于定义一个类以实现从文本到语音的转换。

1. 在新的 `text_to_speech.h` 文件顶部添加以下 include 指令：

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. 在此之下添加以下代码，声明 `TextToSpeech` 类，以及一个可以在应用程序的其余部分中使用的实例：

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. 为了调用函数应用，你需要声明一个 WiFi 客户端。在类的 `private` 部分添加以下内容：

    ```cpp
    WiFiClient _client;
    ```

1. 在 `private` 部分添加一个字段以存储选定的语音：

    ```cpp
    String _voice;
    ```

1. 在 `public` 部分添加一个 `init` 函数，用于获取第一个语音：

    ```cpp
    void init()
    {
    }
    ```

1. 为了获取语音，需要向函数应用发送一个包含语言的 JSON 文档。在 `init` 函数中添加以下代码以创建该 JSON 文档：

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. 接下来创建一个 `HTTPClient`，然后使用它调用函数应用以获取语音，发送 JSON 文档：

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. 在此之下添加代码以检查响应代码，如果是 200（成功），则提取语音列表并从列表中获取第一个语音：

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. 在此之后，结束 HTTP 客户端连接：

    ```cpp
    httpClient.end();
    ```

1. 打开 `main.cpp` 文件，在顶部添加以下 include 指令以包含这个新头文件：

    ```cpp
    #include "text_to_speech.h"
    ```

1. 在 `setup` 函数中，在调用 `speechToText.init();` 的下面添加以下内容以初始化 `TextToSpeech` 类：

    ```cpp
    textToSpeech.init();
    ```

1. 构建代码，将其上传到你的 Wio Terminal，并通过串口监视器进行测试。确保你的函数应用正在运行。

    你将看到函数应用返回的可用语音列表，以及选定的语音。

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## 将文本转换为语音

一旦你有了一个可用的语音，就可以用它将文本转换为语音。与语音列表相同的内存限制也适用于将文本转换为语音，因此你需要将语音写入 SD 卡，以便通过 ReSpeaker 播放。

> 💁 在本项目的早期课程中，你使用闪存存储从麦克风捕获的语音。本课使用 SD 卡，因为使用 Seeed 音频库从 SD 卡播放音频更为方便。

还有另一个限制需要考虑，即语音服务提供的音频数据和 Wio Terminal 支持的格式。与完整的计算机不同，微控制器的音频库对支持的音频格式可能非常有限。例如，Seeed Arduino Audio 库仅支持 44.1KHz 采样率的音频。而 Azure 语音服务可以提供多种格式的音频，但没有一种使用 44.1KHz，它们仅提供 8KHz、16KHz、24KHz 和 48KHz。这意味着音频需要重新采样为 44.1KHz，这需要比 Wio Terminal 拥有的更多资源，尤其是内存。

在需要处理此类数据时，通常更适合使用无服务器代码，尤其是当数据通过网络调用获取时。Wio Terminal 可以调用一个无服务器函数，传递要转换的文本，而无服务器函数可以调用语音服务将文本转换为语音，同时将音频重新采样为所需的采样率。然后，它可以以 Wio Terminal 所需的格式返回音频，以便存储在 SD 卡上并通过 ReSpeaker 播放。

### 任务 - 创建一个无服务器函数以将文本转换为语音

1. 在 VS Code 中打开你的 `smart-timer-trigger` 项目，并确保虚拟环境已激活。如果没有，请终止并重新创建终端。

1. 使用以下命令在 VS Code 终端中函数应用项目的根文件夹内添加一个名为 `text-to-speech` 的 HTTP 触发器：

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    这将创建一个名为 `text-to-speech` 的 HTTP 触发器。

1. [librosa](https://librosa.org) Pip 包提供了重新采样音频的功能，因此将其添加到 `requirements.txt` 文件中：

    ```sh
    librosa
    ```

    添加后，使用以下命令从 VS Code 终端安装 Pip 包：

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ 如果你使用的是 Linux，包括 Raspberry Pi OS，可能需要使用以下命令安装 `libsndfile`：
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. 要将文本转换为语音，你不能直接使用语音 API 密钥，而是需要请求一个访问令牌，并使用 API 密钥对访问令牌请求进行身份验证。从 `text-to-speech` 文件夹中打开 `__init__.py` 文件，并将其中的所有代码替换为以下内容：

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    这定义了从设置中读取的位置和语音密钥常量。然后定义了 `get_access_token` 函数，用于检索语音服务的访问令牌。

1. 在这段代码下面，添加以下内容：

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    这定义了将文本转换为语音的 HTTP 触发器。它从发送到请求的 JSON 主体中提取要转换的文本、语言和语音，构建一些 SSML 来请求语音，然后调用相关的 REST API，并使用访问令牌进行身份验证。此 REST API 调用返回编码为 16 位、48KHz 单声道 WAV 文件的音频，由 `playback_format` 的值定义，并发送到 REST API 调用。

    然后，`librosa` 将此音频从 48KHz 的采样率重新采样为 44.1KHz 的采样率，接着将此音频保存到一个二进制缓冲区中并返回。

1. 在本地运行你的函数应用，或者将其部署到云端。然后可以使用类似 curl 的工具调用它，就像测试 `text-to-timer` HTTP 触发器一样。确保以 JSON 格式传递语言、语音和文本：

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    将 `<language>` 替换为你的语言，例如 `en-GB` 或 `zh-CN`。将 `<voice>` 替换为你想要使用的语音。将 `<text>` 替换为你想要转换为语音的文本。你可以将输出保存到文件中，并使用任何可以播放 WAV 文件的音频播放器播放它。

    例如，要使用美国英语的 Jenny Neural 语音将 "Hello" 转换为语音，并在本地运行函数应用，可以使用以下 curl 命令：

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    这将在当前目录中将音频保存为 `hello.wav`。

> 💁 你可以在 [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) 文件夹中找到这段代码。

### 任务 - 从 Wio Terminal 获取语音

1. 如果尚未打开，请在 VS Code 中打开 `smart-timer` 项目。

1. 打开 `config.h` 头文件，并添加你的函数应用的 URL：

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    将 `<URL>` 替换为你的函数应用中 `text-to-speech` HTTP 触发器的 URL。这将与 `TEXT_TO_TIMER_FUNCTION_URL` 的值相同，只是函数名称从 `text-to-timer` 改为 `text-to-speech`。

1. 打开 `text_to_speech.h` 头文件，并在 `TextToSpeech` 类的 `public` 部分添加以下方法：

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. 在 `convertTextToSpeech` 方法中，添加以下代码以创建发送到函数应用的 JSON：

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    这会将语言、语音和文本写入 JSON 文档，然后将其序列化为字符串。

1. 在此之下，添加以下代码以调用函数应用：

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    这会创建一个 HTTPClient，然后使用 JSON 文档向文本转语音 HTTP 触发器发出 POST 请求。

1. 如果调用成功，从函数应用调用返回的原始二进制数据可以流式传输到 SD 卡上的文件中。添加以下代码以实现此操作：

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    这段代码检查响应，如果是 200（成功），则将二进制数据流式传输到 SD 卡根目录中的一个名为 `SPEECH.WAV` 的文件中。

1. 在此方法的末尾，关闭 HTTP 连接：

    ```cpp
    httpClient.end();
    ```

1. 现在可以将要说的文本转换为音频。在 `main.cpp` 文件中，在 `say` 函数的末尾添加以下行，将要说的文本转换为音频：
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### 任务 - 从 Wio Terminal 播放音频

**即将推出**

## 将函数应用部署到云端

在本地运行函数应用的原因是，Linux 上的 `librosa` Pip 包依赖于一个默认未安装的库，而在函数应用运行之前需要先安装这个库。函数应用是无服务器的——没有可以自行管理的服务器，因此无法提前安装这个库。

解决方法是使用 Docker 容器来部署函数应用。每当云端需要启动函数应用的新实例时（例如，当需求超过可用资源时，或者函数应用长时间未使用而被关闭时），都会部署这个容器。

您可以在 [Microsoft Docs 上关于使用自定义容器在 Linux 上创建函数的文档](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python) 中找到设置函数应用并通过 Docker 部署的说明。

一旦部署完成，您可以将 Wio Terminal 的代码移植以访问这个函数：

1. 将 Azure Functions 证书添加到 `config.h` 中：

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. 将所有包含的 `<WiFiClient.h>` 更改为 `<WiFiClientSecure.h>`。

1. 将所有 `WiFiClient` 字段更改为 `WiFiClientSecure`。

1. 在每个包含 `WiFiClientSecure` 字段的类中，添加一个构造函数，并在该构造函数中设置证书：

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对于因使用本翻译而引起的任何误解或误读不承担责任。