<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-24T23:54:28+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "zh"
}
-->
# 翻译语音 - 树莓派

在本课的这一部分中，您将编写代码，通过翻译服务来翻译文本。

## 使用翻译服务将文本转换为语音

语音服务的 REST API 不支持直接翻译，但您可以使用翻译服务来翻译由语音转文本服务生成的文本，以及语音响应的文本。此服务提供了一个 REST API，您可以用来翻译文本。

### 任务 - 使用翻译资源翻译文本

1. 您的智能计时器将设置两种语言——用于训练 LUIS 的服务器语言（同样用于构建与用户交流的消息），以及用户所说的语言。更新 `language` 变量为用户将使用的语言，并添加一个名为 `server_language` 的新变量，用于表示训练 LUIS 的语言：

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    将 `<user language>` 替换为您将使用的语言的区域名称，例如法语的 `fr-FR` 或粤语的 `zn-HK`。

    将 `<server language>` 替换为用于训练 LUIS 的语言的区域名称。

    您可以在 [Microsoft 文档上的语言和语音支持文档](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) 中找到支持的语言及其区域名称的列表。

    > 💁 如果您不懂多种语言，可以使用像 [必应翻译](https://www.bing.com/translator) 或 [谷歌翻译](https://translate.google.com) 这样的服务，将您的首选语言翻译成您选择的语言。这些服务还可以播放翻译文本的音频。
    >
    > 例如，如果您用英语训练 LUIS，但希望使用法语作为用户语言，您可以使用必应翻译将像“设置一个2分27秒的计时器”这样的句子从英语翻译成法语，然后使用 **听翻译** 按钮将翻译内容通过麦克风说出。
    >
    > ![必应翻译上的听翻译按钮](../../../../../translated_images/zh/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. 在 `speech_api_key` 下添加翻译 API 密钥：

    ```python
    translator_api_key = '<key>'
    ```

    将 `<key>` 替换为您的翻译服务资源的 API 密钥。

1. 在 `say` 函数上方定义一个 `translate_text` 函数，用于将文本从服务器语言翻译成用户语言：

    ```python
    def translate_text(text, from_language, to_language):
    ```

    此函数接收源语言和目标语言——您的应用需要在识别语音时将用户语言转换为服务器语言，在提供语音反馈时将服务器语言转换为用户语言。

1. 在此函数内定义 REST API 调用的 URL 和头信息：

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    此 API 的 URL 不受位置限制，而是通过头信息传递位置。API 密钥直接使用，因此与语音服务不同，不需要从令牌发行 API 获取访问令牌。

1. 在此定义调用的参数和请求体：

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` 定义了传递给 API 调用的参数，传递源语言和目标语言。此调用将把 `from` 语言的文本翻译成 `to` 语言。

    `body` 包含要翻译的文本。这是一个数组，因为可以在同一个调用中翻译多个文本块。

1. 调用 REST API，并获取响应：

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    返回的响应是一个 JSON 数组，其中包含一个项目，该项目包含翻译内容。此项目有一个数组，包含传递给请求体的所有文本的翻译。

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. 返回数组中第一个翻译的第一个项目的 `test` 属性：

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. 更新 `while True` 循环，将用户通过 `convert_speech_to_text` 调用的文本从用户语言翻译成服务器语言：

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    此代码还会将原始文本和翻译后的文本打印到控制台。

1. 更新 `say` 函数，将要说的文本从服务器语言翻译成用户语言：

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    此代码还会将原始文本和翻译后的文本打印到控制台。

1. 运行您的代码。确保您的函数应用正在运行，并用用户语言请求计时器，可以自己说该语言，也可以使用翻译应用。

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 由于不同语言表达方式的差异，您可能会得到与您提供给 LUIS 的示例略有不同的翻译。如果出现这种情况，请向 LUIS 添加更多示例，重新训练并重新发布模型。

> 💁 您可以在 [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) 文件夹中找到此代码。

😀 您的多语言计时器程序大获成功！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。对于因使用本翻译而引起的任何误解或误读，我们概不负责。