<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-24T23:48:47+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "zh"
}
-->
# 翻译语音 - Wio Terminal

在本课的这一部分中，您将编写代码，通过翻译服务来翻译文本。

## 使用翻译服务将文本转换为语音

语音服务的 REST API 不支持直接翻译，但您可以使用翻译服务来翻译由语音转文本服务生成的文本，以及语音响应的文本。该服务提供了一个 REST API，您可以用来翻译文本，但为了简化使用，您可以将其封装在函数应用中的另一个 HTTP 触发器中。

### 任务 - 创建一个无服务器函数来翻译文本

1. 在 VS Code 中打开您的 `smart-timer-trigger` 项目，并确保虚拟环境已激活。如果未激活，请终止并重新创建终端。

1. 打开 `local.settings.json` 文件，并添加翻译器 API 密钥和位置的设置：

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    将 `<key>` 替换为您的翻译服务资源的 API 密钥。将 `<location>` 替换为您创建翻译服务资源时使用的位置。

1. 使用以下命令在 VS Code 终端中函数应用项目的根文件夹内，为此应用添加一个名为 `translate-text` 的新 HTTP 触发器：

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    这将创建一个名为 `translate-text` 的 HTTP 触发器。

1. 将 `translate-text` 文件夹中的 `__init__.py` 文件内容替换为以下内容：

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    此代码从 HTTP 请求中提取文本和语言，然后向翻译器 REST API 发出请求，将语言作为 URL 的参数，文本作为请求体传递。最后返回翻译结果。

1. 在本地运行您的函数应用。您可以使用类似 curl 的工具来调用它，就像测试 `text-to-timer` HTTP 触发器一样。确保以 JSON 格式的请求体传递要翻译的文本和语言：

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    此示例将 *Définir une minuterie de 30 secondes* 从法语翻译为美式英语。它将返回 *Set a 30-second timer*。

> 💁 您可以在 [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) 文件夹中找到此代码。

### 任务 - 使用翻译器函数翻译文本

1. 如果尚未打开，请在 VS Code 中打开 `smart-timer` 项目。

1. 您的智能计时器将设置两种语言——用于训练 LUIS 的服务器语言（同样用于构建与用户交流的消息），以及用户使用的语言。更新 `config.h` 头文件中的 `LANGUAGE` 常量为用户将使用的语言，并添加一个名为 `SERVER_LANGUAGE` 的新常量，用于训练 LUIS 的语言：

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    将 `<user language>` 替换为您将使用的语言的区域名称，例如法语的 `fr-FR` 或粤语的 `zn-HK`。

    将 `<server language>` 替换为用于训练 LUIS 的语言的区域名称。

    您可以在 [Microsoft 文档上的语言和语音支持文档](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) 中找到支持的语言及其区域名称的列表。

    > 💁 如果您不说多种语言，可以使用像 [Bing Translate](https://www.bing.com/translator) 或 [Google Translate](https://translate.google.com) 这样的服务，将您的首选语言翻译成您选择的语言。这些服务还可以播放翻译文本的音频。
    >
    > 例如，如果您用英语训练 LUIS，但希望使用法语作为用户语言，您可以使用 Bing Translate 将诸如 "set a 2 minute and 27 second timer" 的句子从英语翻译成法语，然后使用 **Listen translation** 按钮将翻译语音播放到您的麦克风中。
    >
    > ![Bing Translate 的听翻译按钮](../../../../../translated_images/zh/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. 在 `SPEECH_LOCATION` 下添加翻译器 API 密钥和位置：

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    将 `<KEY>` 替换为您的翻译服务资源的 API 密钥。将 `<LOCATION>` 替换为您创建翻译服务资源时使用的位置。

1. 在 `VOICE_URL` 下添加翻译器触发器 URL：

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    将 `<URL>` 替换为函数应用中 `translate-text` HTTP 触发器的 URL。此值与 `TEXT_TO_TIMER_FUNCTION_URL` 的值相同，只是函数名称从 `text-to-timer` 改为 `translate-text`。

1. 在 `src` 文件夹中添加一个新文件，命名为 `text_translator.h`。

1. 此新的 `text_translator.h` 头文件将包含一个用于翻译文本的类。在此文件中添加以下内容以声明此类：

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    这声明了 `TextTranslator` 类以及该类的一个实例。该类有一个用于 WiFi 客户端的字段。

1. 在此类的 `public` 部分中，添加一个用于翻译文本的方法：

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    此方法接收要翻译的源语言和目标语言。在处理语音时，语音将从用户语言翻译为 LUIS 服务器语言；在给出响应时，将从 LUIS 服务器语言翻译为用户语言。

1. 在此方法中，添加代码以构造包含要翻译文本和语言的 JSON 请求体：

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. 在此代码下方，添加以下代码以将请求体发送到无服务器函数应用：

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. 接下来，添加代码以获取响应：

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. 最后，添加代码以关闭连接并返回翻译后的文本：

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### 任务 - 翻译识别的语音和响应

1. 打开 `main.cpp` 文件。

1. 在文件顶部添加一个包含 `TextTranslator` 类头文件的指令：

    ```cpp
    #include "text_translator.h"
    ```

1. 设置计时器或计时器到期时说出的文本需要被翻译。为此，在 `say` 函数的第一行添加以下内容：

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    这将文本翻译为用户语言。

1. 在 `processAudio` 函数中，通过 `String text = speechToText.convertSpeechToText();` 调用从捕获的音频中检索文本。在此调用之后，翻译文本：

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    这将文本从用户语言翻译为服务器使用的语言。

1. 构建此代码，将其上传到您的 Wio Terminal，并通过串行监视器进行测试。当您在串行监视器中看到 `Ready` 时，按下 C 按钮（左侧靠近电源开关的按钮），然后开始说话。确保您的函数应用正在运行，并以用户语言请求计时器，无论是自己说该语言，还是使用翻译应用。

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 您可以在 [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) 文件夹中找到此代码。

😀 您的多语言计时器程序大获成功！

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用此翻译而引起的任何误解或误读不承担责任。